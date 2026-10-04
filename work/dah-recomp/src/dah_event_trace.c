#include <windows.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <xbox/xboxrecomp.h>
#include "dah_event_trace.h"

enum { DAH_EVENT_CAPACITY = 16384, DAH_EVENT_NAME = 64 };

typedef struct DahAiStateEvent {
    uint64_t sequence;
    uint32_t world_tick;
    uint32_t manager, owner;
    uint32_t old_state, new_state;
    uint32_t old_id, new_id;
    uint32_t old_name_pointer, new_name_pointer;
    uint32_t caller;
    char old_name[DAH_EVENT_NAME];
    char new_name[DAH_EVENT_NAME];
} DahAiStateEvent;

static DahAiStateEvent events[DAH_EVENT_CAPACITY];
static volatile LONG write_index;
static volatile LONG read_index;
static volatile LONG dropped_events;
static volatile LONG running;
static volatile LONG enabled;
static HANDLE wake_event;
static HANDLE writer_thread;
static FILE *output;

static int guest_range(uint32_t address, uint32_t size)
{
    return address >= 0x10000u && address < 0x04000000u &&
           size <= 0x04000000u - address;
}

static uint32_t guest_u32(uint32_t address)
{
    ptrdiff_t offset = xbox_GetMemoryOffset();
    if (!guest_range(address, 4u)) return 0u;
    return *(const uint32_t *)((uintptr_t)offset + address);
}

static void guest_name(uint32_t address, char destination[DAH_EVENT_NAME])
{
    ptrdiff_t offset = xbox_GetMemoryOffset();
    unsigned index;
    destination[0] = '\0';
    if (!guest_range(address, 1u)) return;
    for (index = 0; index + 1u < DAH_EVENT_NAME; ++index) {
        unsigned char value;
        if (!guest_range(address + index, 1u)) break;
        value = *(const unsigned char *)((uintptr_t)offset + address + index);
        if (!value) break;
        destination[index] = value >= 32u && value < 127u && value != '"' &&
                             value != '\\' ? (char)value : '?';
    }
    destination[index] = '\0';
}

static DWORD WINAPI writer_main(void *unused)
{
    (void)unused;
    while (InterlockedCompareExchange(&running, 0, 0) ||
           InterlockedCompareExchange(&read_index, 0, 0) !=
           InterlockedCompareExchange(&write_index, 0, 0)) {
        LONG read = InterlockedCompareExchange(&read_index, 0, 0);
        LONG write = InterlockedCompareExchange(&write_index, 0, 0);
        while (read != write) {
            const DahAiStateEvent *event = &events[(uint32_t)read &
                                                   (DAH_EVENT_CAPACITY - 1u)];
            fprintf(output,
                    "{\"event\":\"ai-state-commit\",\"sequence\":%llu,"
                    "\"worldTick\":%u,\"manager\":\"%08X\","
                    "\"owner\":\"%08X\",\"oldState\":\"%08X\","
                    "\"newState\":\"%08X\",\"oldStateId\":\"%08X\","
                    "\"newStateId\":\"%08X\",\"oldStateName\":\"%s\","
                    "\"newStateName\":\"%s\",\"oldNamePointer\":\"%08X\","
                    "\"newNamePointer\":\"%08X\",\"caller\":\"%08X\"}\n",
                    (unsigned long long)event->sequence, event->world_tick,
                    event->manager, event->owner, event->old_state,
                    event->new_state, event->old_id, event->new_id,
                    event->old_name, event->new_name,
                    event->old_name_pointer, event->new_name_pointer,
                    event->caller);
            ++read;
            InterlockedExchange(&read_index, read);
        }
        fflush(output);
        if (InterlockedCompareExchange(&running, 0, 0))
            WaitForSingleObject(wake_event, 50u);
    }
    return 0;
}

void dah_event_trace_initialize(void)
{
    const char *path = getenv("DAH_EVENT_TRACE");
    if (!path || !*path) return;
    output = fopen(path, "wb");
    if (!output) return;
    setvbuf(output, NULL, _IOFBF, 64u * 1024u);
    wake_event = CreateEventA(NULL, FALSE, FALSE, NULL);
    if (!wake_event) {
        fclose(output);
        output = NULL;
        return;
    }
    InterlockedExchange(&running, 1);
    writer_thread = CreateThread(NULL, 0, writer_main, NULL, 0, NULL);
    if (!writer_thread) {
        InterlockedExchange(&running, 0);
        CloseHandle(wake_event);
        wake_event = NULL;
        fclose(output);
        output = NULL;
        return;
    }
    InterlockedExchange(&enabled, 1);
}

void dah_event_trace_ai_state(uint32_t manager, uint32_t owner,
                              uint32_t old_state, uint32_t new_state,
                              uint32_t old_id, uint32_t new_id,
                              uint32_t old_name, uint32_t new_name,
                              uint32_t caller)
{
    LONG write, read;
    DahAiStateEvent *event;
    uint32_t world;
    if (!InterlockedCompareExchange(&enabled, 0, 0)) return;
    write = InterlockedCompareExchange(&write_index, 0, 0);
    read = InterlockedCompareExchange(&read_index, 0, 0);
    if ((uint32_t)(write - read) >= DAH_EVENT_CAPACITY) {
        InterlockedIncrement(&dropped_events);
        return;
    }
    event = &events[(uint32_t)write & (DAH_EVENT_CAPACITY - 1u)];
    memset(event, 0, sizeof(*event));
    event->sequence = (uint32_t)write;
    world = guest_u32(0x00286768u);
    event->world_tick = guest_range(world, 12u) ? guest_u32(world + 8u) : 0u;
    event->manager = manager;
    event->owner = owner;
    event->old_state = old_state;
    event->new_state = new_state;
    event->old_id = old_id;
    event->new_id = new_id;
    event->old_name_pointer = old_name;
    event->new_name_pointer = new_name;
    event->caller = caller;
    guest_name(old_name, event->old_name);
    guest_name(new_name, event->new_name);
    MemoryBarrier();
    InterlockedExchange(&write_index, write + 1);
}

void dah_event_trace_shutdown(void)
{
    LONG dropped;
    if (!InterlockedExchange(&enabled, 0)) return;
    InterlockedExchange(&running, 0);
    SetEvent(wake_event);
    WaitForSingleObject(writer_thread, 5000u);
    dropped = InterlockedCompareExchange(&dropped_events, 0, 0);
    if (dropped)
        fprintf(output, "{\"event\":\"trace-overflow\",\"dropped\":%ld}\n",
                (long)dropped);
    fflush(output);
    fclose(output);
    output = NULL;
    CloseHandle(writer_thread);
    writer_thread = NULL;
    CloseHandle(wake_event);
    wake_event = NULL;
}
