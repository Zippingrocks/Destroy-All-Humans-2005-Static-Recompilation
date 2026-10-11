/* Compiled by test_ntwait_multiple_ex.mjs with exact production function
 * bodies extracted into ntwait_multiple_ex_fixture.inc. Only guest memory,
 * handle resolution, and host wait/time APIs are mocked; the bridge,
 * dispatcher stack cleanup, timeout conversion, and status mapping are real.
 */
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef _MSC_VER
#define __stdcall
#define RECOMP_TLS _Thread_local
#define TEST_IMPORT
#else
#define RECOMP_TLS __declspec(thread)
#define TEST_IMPORT __declspec(dllimport)
#endif
typedef uint32_t ULONG, DWORD;
typedef int BOOL;
typedef uint8_t BOOLEAN;
typedef void *HANDLE;
typedef int32_t NTSTATUS;
typedef int64_t LONGLONG;
typedef struct { LONGLONG QuadPart; } LARGE_INTEGER, *PLARGE_INTEGER;
typedef struct { DWORD low, high; } FILETIME, *LPFILETIME;
#define TRUE 1
#define FALSE 0
#define INFINITE UINT32_MAX
#define WAIT_OBJECT_0 0u
#define WAIT_ABANDONED_0 0x80u
#define WAIT_IO_COMPLETION 0xC0u
#define WAIT_TIMEOUT 0x102u
#define WAIT_FAILED UINT32_MAX
#define STATUS_SUCCESS ((NTSTATUS)0)
#define STATUS_TIMEOUT ((NTSTATUS)0x102)
#define STATUS_ALERTED ((NTSTATUS)0x101)
#define STATUS_ABANDONED ((NTSTATUS)0x80)
#define STATUS_UNSUCCESSFUL ((NTSTATUS)0xC0000001u)

#define XBOX_KERNEL_THUNK_TABLE_SIZE 4
#define KERNEL_VA_BASE 0xFE000000u
#define KERNEL_VA_END (KERNEL_VA_BASE + XBOX_KERNEL_THUNK_TABLE_SIZE * 4u)
#define GUEST_SIZE 4096u
#define STACK_VA 256u
#define TIMEOUT_VA 768u
#define HANDLES_VA (GUEST_SIZE - 64u * 4u)
#define FIXED_NOW INT64_C(133000000000000000)

typedef void (*bridge_func_t)(void);
typedef void (*recomp_func_t)(void);
static bridge_func_t g_slot_bridges[XBOX_KERNEL_THUNK_TABLE_SIZE];
static int g_slot_arg_bytes[XBOX_KERNEL_THUNK_TABLE_SIZE];
static ULONG g_slot_ordinals[XBOX_KERNEL_THUNK_TABLE_SIZE];
static int g_kernel_call_count = 200;
static uint32_t g_kernel_watch_va;
static RECOMP_TLS uint32_t g_eax, g_esp, g_ebx, g_esi, g_edi, g_ebp;
static RECOMP_TLS union { uint64_t alignment; uint8_t bytes[GUEST_SIZE]; } guest;
static RECOMP_TLS const char *case_name;
static unsigned case_count, resolve_count, timeout_translations;
static uint32_t resolved_tokens[64];

typedef struct HostWait {
    unsigned calls;
    DWORD count, milliseconds, result;
    BOOL wait_all, alertable;
    HANDLE handles[64];
} HostWait;
static HostWait host_wait;

/* Only these synchronization calls reach Win32; host game wait/time APIs
 * remain mocked. The barriers make the old shared selector fail reliably. */
TEST_IMPORT HANDLE __stdcall CreateEventA(void *, BOOL, BOOL, const char *);
TEST_IMPORT HANDLE __stdcall CreateThread(void *, size_t, DWORD (__stdcall *)(void *),
                                         void *, DWORD, DWORD *);
TEST_IMPORT DWORD __stdcall WaitForSingleObject(HANDLE, DWORD);
TEST_IMPORT BOOL __stdcall SetEvent(HANDLE);
TEST_IMPORT BOOL __stdcall CloseHandle(HANDLE);

static void require(int ok, const char *message)
{
    if (!ok) {
        fprintf(stderr, "FAIL [%s]: %s\n", case_name ? case_name : "setup", message);
        exit(1);
    }
}

static void *guest_pointer(uint32_t va, size_t size)
{
    require(va < GUEST_SIZE && size <= GUEST_SIZE - va,
            "guest memory access exceeds fixture bounds (possible handle-array overflow)");
    return guest.bytes + va;
}

static void *translated_pointer(uint32_t va)
{
    if (!va) return NULL;
    require(va == TIMEOUT_VA, "Timeout must come from guest argument 5, not WaitMode/Alertable");
    ++timeout_translations;
    return guest_pointer(va, sizeof(LARGE_INTEGER));
}

#define BRIDGE_MEM32(addr) (*(volatile uint32_t *)guest_pointer((uint32_t)(addr), 4u))
#define STACK_ARG(n) ((uint32_t)BRIDGE_MEM32(g_esp + (n) * 4u))
#define XBOX_TO_NATIVE(va) translated_pointer((uint32_t)(va))

static HANDLE token_to_handle(uint32_t token)
{
    /* High bits ensure the bridge cannot just cast a guest token to HANDLE. */
    return (HANDLE)(uintptr_t)(UINT64_C(0x1234000000000000) | ((uint64_t)token << 4u));
}

static HANDLE bridge_resolve_handle(uint32_t token)
{
    require(resolve_count < 64u, "native handle array must remain bounded to 64 entries");
    resolved_tokens[resolve_count++] = token;
    return token_to_handle(token);
}

static DWORD GetTickCount(void) { return 100u; }
static void GetSystemTimeAsFileTime(LPFILETIME time)
{
    uint64_t bits = (uint64_t)FIXED_NOW;
    memcpy(time, &bits, sizeof(bits));
}

static DWORD WaitForMultipleObjectsEx(DWORD count, const HANDLE *handles,
                                     BOOL wait_all, DWORD milliseconds, BOOL alertable)
{
    unsigned i;
    require(count <= 64u, "host wait received more than 64 handles");
    require(host_wait.calls == 0u, "bridge must issue exactly one host wait");
    host_wait.calls++;
    host_wait.count = count;
    host_wait.wait_all = wait_all;
    host_wait.milliseconds = milliseconds;
    host_wait.alertable = alertable;
    for (i = 0; i < count; ++i) host_wait.handles[i] = handles[i];
    return count ? host_wait.result : WAIT_FAILED;
}

#include "ntwait_multiple_ex_fixture.inc"

static void run_case(const char *name, uint32_t count, uint32_t wait_type,
                     uint32_t wait_mode, uint32_t alertable,
                     int has_timeout, int64_t timeout_value,
                     DWORD expected_ms, DWORD host_result, NTSTATUS expected_status)
{
    uint8_t before[GUEST_SIZE];
    uint32_t expected_count = count > 64u ? 64u : count;
    uint32_t i;
    case_name = name;
    memset(guest.bytes, 0xA5, sizeof(guest.bytes));
    memset(&host_wait, 0, sizeof(host_wait));
    host_wait.result = host_result;
    resolve_count = timeout_translations = 0;
    g_esp = STACK_VA;
    g_eax = 0xBAD0EA00u;
    g_ebx = 0xB0B1B2B3u;
    g_esi = 0x51525354u;
    g_edi = 0xD1D2D3D4u;
    g_ebp = 0xBEBEBEBEu;

    BRIDGE_MEM32(STACK_VA) = 0x000B4276u; /* real retail call-site marker */
    BRIDGE_MEM32(STACK_VA + 4u) = count;
    BRIDGE_MEM32(STACK_VA + 8u) = count ? HANDLES_VA : UINT32_MAX;
    BRIDGE_MEM32(STACK_VA + 12u) = wait_type;
    BRIDGE_MEM32(STACK_VA + 16u) = wait_mode;
    BRIDGE_MEM32(STACK_VA + 20u) = alertable;
    BRIDGE_MEM32(STACK_VA + 24u) = has_timeout ? TIMEOUT_VA : 0u;
    /* Retail caller restores these immediately after the stdcall returns. */
    BRIDGE_MEM32(STACK_VA + 28u) = g_edi;
    BRIDGE_MEM32(STACK_VA + 32u) = g_esi;
    BRIDGE_MEM32(STACK_VA + 36u) = g_ebx;
    BRIDGE_MEM32(STACK_VA + 40u) = 0xCAFED00Du;
    memcpy(guest_pointer(TIMEOUT_VA, 8u), &timeout_value, 8u);
    for (i = 0; i < 64u; ++i) BRIDGE_MEM32(HANDLES_VA + i * 4u) = 0xA000u + i * 7u;
    memcpy(before, guest.bytes, sizeof(before));

    g_kernel_dispatch_slot = 0;
    g_slot_ordinals[0] = 235u;
    g_slot_arg_bytes[0] = stdcall_args_for_ordinal(235u);
    g_slot_bridges[0] = bridge_NtWaitForMultipleObjectsEx;
    kernel_thunk_dispatch();

    require(host_wait.calls == 1u, "one host wait expected");
    require(host_wait.count == expected_count, "Count must preserve current 0/64 clamp contract");
    require(resolve_count == expected_count, "each guest token must be resolved exactly once");
    require(host_wait.wait_all == (wait_type == 0u), "WaitType mapping incorrect");
    require(host_wait.alertable == (BOOLEAN)alertable, "Alertable must come from argument 4");
    require(host_wait.milliseconds == expected_ms, "Timeout conversion/mapping incorrect");
    require(timeout_translations == (unsigned)has_timeout, "Timeout pointer/null mapping incorrect");
    for (i = 0; i < expected_count; ++i) {
        uint32_t token = 0xA000u + i * 7u;
        require(resolved_tokens[i] == token, "guest handles must be read as 32-bit tokens");
        require(host_wait.handles[i] == token_to_handle(token), "resolved 64-bit handle truncated/corrupted");
    }
    require(g_eax == (uint32_t)expected_status, "host wait result must be mapped to guest NTSTATUS");
    require(g_esp == STACK_VA + 28u, "stdcall must pop return plus SIX arguments (28 bytes)");
    require(g_ebx == 0xB0B1B2B3u && g_esi == 0x51525354u &&
            g_edi == 0xD1D2D3D4u && g_ebp == 0xBEBEBEBEu,
            "callee-preserved guest registers changed");
    require(memcmp(before, guest.bytes, sizeof(before)) == 0, "guest stack/data sentinels overwritten");
    require(BRIDGE_MEM32(g_esp) == g_edi && BRIDGE_MEM32(g_esp + 4u) == g_esi &&
            BRIDGE_MEM32(g_esp + 8u) == g_ebx && BRIDGE_MEM32(g_esp + 12u) == 0xCAFED00Du,
            "retail caller would restore registers from wrong stack slots");
    ++case_count;
}

static HANDLE worker0_selected, worker1_selected, worker0_finished;
static RECOMP_TLS unsigned worker_bridge_marker;

static void mark_slot0(void) { worker_bridge_marker = 0xABC000u; }
static void mark_slot1(void) { worker_bridge_marker = 0xABC001u; }

static DWORD __stdcall selector_worker(void *argument)
{
    unsigned slot = (unsigned)(uintptr_t)argument;
    recomp_func_t dispatch;
    case_name = slot ? "selector-worker1" : "selector-worker0";
    if (slot)
        require(WaitForSingleObject(worker0_selected, 5000u) == WAIT_OBJECT_0,
                "worker0 did not reach selection barrier");
    dispatch = recomp_lookup_kernel(KERNEL_VA_BASE + slot * 4u);
    require(dispatch != NULL, "valid synthetic address failed lookup");
    if (!slot) {
        require(SetEvent(worker0_selected), "cannot signal worker0 selection");
        require(WaitForSingleObject(worker1_selected, 5000u) == WAIT_OBJECT_0,
                "worker1 did not reach selection barrier");
    } else {
        require(SetEvent(worker1_selected), "cannot signal worker1 selection");
        require(WaitForSingleObject(worker0_finished, 5000u) == WAIT_OBJECT_0,
                "worker0 did not finish dispatch");
    }
    require(g_kernel_dispatch_slot == (int)slot,
            "another thread replaced this worker's kernel dispatch slot");
    memset(guest.bytes, 0xA5, sizeof(guest.bytes));
    g_esp = STACK_VA;
    g_ebx = 0xB0B1B2B3u; g_esi = 0x51525354u; g_edi = 0xD1D2D3D4u;
    worker_bridge_marker = UINT32_MAX;
    dispatch();
    require(worker_bridge_marker == 0xABC000u + slot, "dispatcher called wrong worker bridge");
    require(g_esp == STACK_VA + 4u + (slot ? 8u : 24u), "wrong slot's stack cleanup applied");
    require(g_ebx == 0xB0B1B2B3u && g_esi == 0x51525354u && g_edi == 0xD1D2D3D4u,
            "dispatch changed worker callee-preserved registers");
    if (!slot) require(SetEvent(worker0_finished), "cannot signal worker0 dispatch completion");
    return 0;
}

static void check_selector_tls(void)
{
    HANDLE threads[2];
    case_name = "two-thread-selector";
    g_slot_bridges[0] = mark_slot0;
    g_slot_bridges[1] = mark_slot1;
    g_slot_ordinals[0] = 235u;
    g_slot_ordinals[1] = 225u;
    g_slot_arg_bytes[0] = stdcall_args_for_ordinal(235u);
    g_slot_arg_bytes[1] = stdcall_args_for_ordinal(225u);
    worker0_selected = CreateEventA(NULL, TRUE, FALSE, NULL);
    worker1_selected = CreateEventA(NULL, TRUE, FALSE, NULL);
    worker0_finished = CreateEventA(NULL, TRUE, FALSE, NULL);
    require(worker0_selected && worker1_selected && worker0_finished, "event creation failed");
    threads[0] = CreateThread(NULL, 0, selector_worker, (void *)(uintptr_t)0u, 0, NULL);
    threads[1] = CreateThread(NULL, 0, selector_worker, (void *)(uintptr_t)1u, 0, NULL);
    require(threads[0] && threads[1], "thread creation failed");
    require(WaitForSingleObject(threads[0], 10000u) == WAIT_OBJECT_0, "worker0 failed to finish");
    require(WaitForSingleObject(threads[1], 10000u) == WAIT_OBJECT_0, "worker1 failed to finish");
    CloseHandle(threads[0]); CloseHandle(threads[1]);
    CloseHandle(worker0_selected); CloseHandle(worker1_selected); CloseHandle(worker0_finished);
    ++case_count;
}

int main(void)
{
    require(sizeof(HANDLE) == 8u, "test requires a 64-bit host");
    run_case("six-argument-distinct-markers", 3, 1, 0xF1230201u, 0,
             1, -1250000, 125, WAIT_OBJECT_0 + 2u, 2);
    run_case("alertable-waitall-infinite", 2, 0, 0, 1,
             0, 0, INFINITE, WAIT_IO_COMPLETION, STATUS_ALERTED);
    run_case("boolean-low-byte", 1, 1, 1, 0x100u,
             1, 0, 0, WAIT_TIMEOUT, STATUS_TIMEOUT);
    run_case("boolean-nonzero-byte", 1, 1, 0, 0xABu,
             1, -1, 1, WAIT_OBJECT_0, STATUS_SUCCESS);
    run_case("absolute-future", 2, 0, 1, 0,
             1, FIXED_NOW + 420000, 42, WAIT_OBJECT_0, STATUS_SUCCESS);
    run_case("absolute-past", 1, 1, 0, 1,
             1, FIXED_NOW - 1, 0, WAIT_TIMEOUT, STATUS_TIMEOUT);
    run_case("zero-count-invalid-array", 0, 0, 1, 0,
             0, 0, INFINITE, WAIT_FAILED, STATUS_UNSUCCESSFUL);
    run_case("maximum-count", 64, 1, 0, 0,
             1, 0, 0, WAIT_OBJECT_0 + 63u, 63);
    run_case("oversize-count-clamped", 65, 1, 1, 1,
             1, -10000, 1, WAIT_TIMEOUT, STATUS_TIMEOUT);
    run_case("uint32-max-count-clamped", UINT32_MAX, 0, 0, 0,
             0, 0, INFINITE, WAIT_FAILED, STATUS_UNSUCCESSFUL);
    run_case("abandoned-status", 1, 1, 1, 0,
             0, 0, INFINITE, WAIT_ABANDONED_0, STATUS_ABANDONED);
    check_selector_tls();
    printf("PASS: %u NtWaitForMultipleObjectsEx cases; exact source bridge/dispatcher/HLE, "
           "six arguments, bounded handles, timeout/status mappings, register/stack sentinels, "
           "deterministic two-thread lookup/dispatch isolation.\n", case_count);
    return 0;
}
