#include <windows.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <xbox/xboxrecomp.h>
#include "dah_event_trace.h"

enum { DAH_EVENT_CAPACITY = 16384, DAH_EVENT_NAME = 64 };
enum { DAH_EVENT_AI_STATE = 1, DAH_EVENT_FRAME = 2,
       DAH_EVENT_ABILITY_FLAG = 3, DAH_EVENT_TAG_ABILITY = 4,
       DAH_EVENT_PHYSICS_BODY_COMMAND = 5 };

typedef struct DahTraceEvent {
    uint64_t sequence;
    uint32_t world_tick;
    uint32_t type;
    union {
        struct {
            uint32_t manager, owner;
            uint32_t old_state, new_state;
            uint32_t old_id, new_id;
            uint32_t old_name_pointer, new_name_pointer;
            uint32_t caller;
            char old_name[DAH_EVENT_NAME];
            char new_name[DAH_EVENT_NAME];
        } ai;
        struct {
            uint64_t host_frame;
            uint32_t loop;
            uint32_t interval_us, target_us;
            uint32_t logic_us, render_us, present_us, total_us;
            uint32_t draw_count, draw_delta;
            uint32_t present_result, flags;
        } frame;
        struct {
            uint32_t command, owner, offset;
            uint32_t old_value, new_value, caller;
        } ability;
        struct {
            uint32_t ability_hash, actor, offset;
            uint32_t old_value, new_value, caller;
        } tag_ability;
        struct {
            uint32_t tag_hash, filter_hash, actor, forceable;
            uint32_t requested_enable, caller;
        } physics_body_command;
    } payload;
} DahTraceEvent;

static DahTraceEvent events[DAH_EVENT_CAPACITY];
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
    DWORD last_flush = GetTickCount();
    (void)unused;
    SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_BELOW_NORMAL);
    while (InterlockedCompareExchange(&running, 0, 0) ||
           InterlockedCompareExchange(&read_index, 0, 0) !=
           InterlockedCompareExchange(&write_index, 0, 0)) {
        LONG read = InterlockedCompareExchange(&read_index, 0, 0);
        LONG write = InterlockedCompareExchange(&write_index, 0, 0);
        while (read != write) {
            const DahTraceEvent *event = &events[(uint32_t)read &
                                                  (DAH_EVENT_CAPACITY - 1u)];
            if (event->type == DAH_EVENT_AI_STATE) fprintf(output,
                    "{\"event\":\"ai-state-commit\",\"sequence\":%llu,"
                    "\"worldTick\":%u,\"manager\":\"%08X\","
                    "\"owner\":\"%08X\",\"oldState\":\"%08X\","
                    "\"newState\":\"%08X\",\"oldStateId\":\"%08X\","
                    "\"newStateId\":\"%08X\",\"oldStateName\":\"%s\","
                    "\"newStateName\":\"%s\",\"oldNamePointer\":\"%08X\","
                    "\"newNamePointer\":\"%08X\",\"caller\":\"%08X\"}\n",
                    (unsigned long long)event->sequence, event->world_tick,
                    event->payload.ai.manager, event->payload.ai.owner,
                    event->payload.ai.old_state, event->payload.ai.new_state,
                    event->payload.ai.old_id, event->payload.ai.new_id,
                    event->payload.ai.old_name, event->payload.ai.new_name,
                    event->payload.ai.old_name_pointer,
                    event->payload.ai.new_name_pointer,
                    event->payload.ai.caller);
            else if (event->type == DAH_EVENT_FRAME) fprintf(output,
                    "{\"event\":\"frame\",\"sequence\":%llu,"
                    "\"worldTick\":%u,\"hostFrame\":%llu,\"loop\":%u,"
                    "\"intervalUs\":%u,\"targetUs\":%u,\"logicUs\":%u,"
                    "\"renderUs\":%u,\"presentUs\":%u,\"totalUs\":%u,"
                    "\"drawCount\":%u,\"drawDelta\":%u,"
                    "\"presentResult\":\"%08X\",\"flags\":%u}\n",
                    (unsigned long long)event->sequence, event->world_tick,
                    (unsigned long long)event->payload.frame.host_frame,
                    event->payload.frame.loop, event->payload.frame.interval_us,
                    event->payload.frame.target_us, event->payload.frame.logic_us,
                    event->payload.frame.render_us, event->payload.frame.present_us,
                    event->payload.frame.total_us, event->payload.frame.draw_count,
                    event->payload.frame.draw_delta,
                    event->payload.frame.present_result, event->payload.frame.flags);
            else if (event->type == DAH_EVENT_ABILITY_FLAG) fprintf(output,
                    "{\"event\":\"ability-flag\",\"sequence\":%llu,"
                    "\"worldTick\":%u,\"ability\":\"jetpack-enabled\","
                    "\"command\":\"%08X\",\"owner\":\"%08X\","
                    "\"offset\":\"%X\",\"oldStoredDisable\":%u,"
                    "\"newStoredDisable\":%u,\"oldEnabled\":%u,"
                    "\"newEnabled\":%u,\"caller\":\"%08X\"}\n",
                    (unsigned long long)event->sequence, event->world_tick,
                    event->payload.ability.command, event->payload.ability.owner,
                    event->payload.ability.offset,
                    event->payload.ability.old_value,
                    event->payload.ability.new_value,
                    event->payload.ability.old_value ? 0u : 1u,
                    event->payload.ability.new_value ? 0u : 1u,
                    event->payload.ability.caller);
            else if (event->type == DAH_EVENT_TAG_ABILITY) fprintf(output,
                    "{\"event\":\"tag-alien-ability\",\"sequence\":%llu,"
                    "\"worldTick\":%u,\"abilityHash\":\"%08X\","
                    "\"actor\":\"%08X\",\"offset\":\"%X\","
                    "\"oldStoredDisable\":%u,\"newStoredDisable\":%u,"
                    "\"oldEnabled\":%u,\"newEnabled\":%u,"
                    "\"caller\":\"%08X\"}\n",
                    (unsigned long long)event->sequence, event->world_tick,
                    event->payload.tag_ability.ability_hash,
                    event->payload.tag_ability.actor,
                    event->payload.tag_ability.offset,
                    event->payload.tag_ability.old_value,
                    event->payload.tag_ability.new_value,
                    event->payload.tag_ability.old_value ? 0u : 1u,
                    event->payload.tag_ability.new_value ? 0u : 1u,
                    event->payload.tag_ability.caller);
            else if (event->type == DAH_EVENT_PHYSICS_BODY_COMMAND) fprintf(output,
                    "{\"event\":\"physics-body-command\",\"sequence\":%llu,"
                    "\"worldTick\":%u,\"tagHash\":\"%08X\","
                    "\"filterHash\":\"%08X\",\"actor\":\"%08X\","
                    "\"forceable\":\"%08X\",\"requestedEnable\":%u,"
                    "\"caller\":\"%08X\"}\n",
                    (unsigned long long)event->sequence, event->world_tick,
                    event->payload.physics_body_command.tag_hash,
                    event->payload.physics_body_command.filter_hash,
                    event->payload.physics_body_command.actor,
                    event->payload.physics_body_command.forceable,
                    event->payload.physics_body_command.requested_enable,
                    event->payload.physics_body_command.caller);
            ++read;
            InterlockedExchange(&read_index, read);
        }
        if (GetTickCount() - last_flush >= 1000u) {
            fflush(output);
            last_flush = GetTickCount();
        }
        if (InterlockedCompareExchange(&running, 0, 0))
            WaitForSingleObject(wake_event, 50u);
    }
    return 0;
}

void dah_event_trace_initialize(const char *run_id, const char *started_utc,
                                uint64_t executable_hash)
{
    const char *path = getenv("DAH_EVENT_TRACE");
    /* Always retain the most recent run so a one-frame hitch or transient AI
     * state is available after the fact. A custom path is useful for parity
     * sessions; DAH_EVENT_TRACE=0 is the explicit opt-out. */
    if (path && !strcmp(path, "0")) return;
    if (!path || !*path) path = "dah_event_trace.jsonl";
    output = fopen(path, "wb");
    if (!output) return;
    setvbuf(output, NULL, _IOFBF, 64u * 1024u);
    fprintf(output,
            "{\"event\":\"run-start\",\"schema\":1,\"runId\":\"%s\","
            "\"pid\":%lu,\"startedUtc\":\"%s\","
            "\"executableFnv1a64\":\"%016llX\"}\n",
            run_id, GetCurrentProcessId(), started_utc,
            (unsigned long long)executable_hash);
    fflush(output);
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
    DahTraceEvent *event;
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
    event->type = DAH_EVENT_AI_STATE;
    world = guest_u32(0x00286768u);
    event->world_tick = guest_range(world, 12u) ? guest_u32(world + 8u) : 0u;
    event->payload.ai.manager = manager;
    event->payload.ai.owner = owner;
    event->payload.ai.old_state = old_state;
    event->payload.ai.new_state = new_state;
    event->payload.ai.old_id = old_id;
    event->payload.ai.new_id = new_id;
    event->payload.ai.old_name_pointer = old_name;
    event->payload.ai.new_name_pointer = new_name;
    event->payload.ai.caller = caller;
    guest_name(old_name, event->payload.ai.old_name);
    guest_name(new_name, event->payload.ai.new_name);
    MemoryBarrier();
    InterlockedExchange(&write_index, write + 1);
}

void dah_event_trace_frame(uint64_t host_frame, uint32_t loop,
                           uint32_t interval_us, uint32_t target_us,
                           uint32_t logic_us, uint32_t render_us,
                           uint32_t present_us, uint32_t total_us,
                           uint32_t draw_count, uint32_t draw_delta,
                           uint32_t present_result, uint32_t flags)
{
    LONG write, read;
    DahTraceEvent *event;
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
    event->type = DAH_EVENT_FRAME;
    world = guest_u32(0x00286768u);
    event->world_tick = guest_range(world, 12u) ? guest_u32(world + 8u) : 0u;
    event->payload.frame.host_frame = host_frame;
    event->payload.frame.loop = loop;
    event->payload.frame.interval_us = interval_us;
    event->payload.frame.target_us = target_us;
    event->payload.frame.logic_us = logic_us;
    event->payload.frame.render_us = render_us;
    event->payload.frame.present_us = present_us;
    event->payload.frame.total_us = total_us;
    event->payload.frame.draw_count = draw_count;
    event->payload.frame.draw_delta = draw_delta;
    event->payload.frame.present_result = present_result;
    event->payload.frame.flags = flags;
    MemoryBarrier();
    InterlockedExchange(&write_index, write + 1);
}

void dah_event_trace_ability_flag(uint32_t command, uint32_t owner,
                                  uint32_t offset, uint32_t old_value,
                                  uint32_t new_value, uint32_t caller)
{
    LONG write, read;
    DahTraceEvent *event;
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
    event->type = DAH_EVENT_ABILITY_FLAG;
    world = guest_u32(0x00286768u);
    event->world_tick = guest_range(world, 12u) ? guest_u32(world + 8u) : 0u;
    event->payload.ability.command = command;
    event->payload.ability.owner = owner;
    event->payload.ability.offset = offset;
    event->payload.ability.old_value = old_value;
    event->payload.ability.new_value = new_value;
    event->payload.ability.caller = caller;
    MemoryBarrier();
    InterlockedExchange(&write_index, write + 1);
}

void dah_event_trace_tag_ability(uint32_t ability_hash, uint32_t actor,
                                 uint32_t offset, uint32_t old_value,
                                 uint32_t new_value, uint32_t caller)
{
    LONG write, read;
    DahTraceEvent *event;
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
    event->type = DAH_EVENT_TAG_ABILITY;
    world = guest_u32(0x00286768u);
    event->world_tick = guest_range(world, 12u) ? guest_u32(world + 8u) : 0u;
    event->payload.tag_ability.ability_hash = ability_hash;
    event->payload.tag_ability.actor = actor;
    event->payload.tag_ability.offset = offset;
    event->payload.tag_ability.old_value = old_value;
    event->payload.tag_ability.new_value = new_value;
    event->payload.tag_ability.caller = caller;
    MemoryBarrier();
    InterlockedExchange(&write_index, write + 1);
}

void dah_event_trace_physics_body_command(uint32_t tag_hash,
                                          uint32_t filter_hash,
                                          uint32_t actor,
                                          uint32_t forceable,
                                          uint32_t requested_enable,
                                          uint32_t caller)
{
    LONG write, read;
    DahTraceEvent *event;
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
    event->type = DAH_EVENT_PHYSICS_BODY_COMMAND;
    world = guest_u32(0x00286768u);
    event->world_tick = guest_range(world, 12u) ? guest_u32(world + 8u) : 0u;
    event->payload.physics_body_command.tag_hash = tag_hash;
    event->payload.physics_body_command.filter_hash = filter_hash;
    event->payload.physics_body_command.actor = actor;
    event->payload.physics_body_command.forceable = forceable;
    event->payload.physics_body_command.requested_enable = requested_enable;
    event->payload.physics_body_command.caller = caller;
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
