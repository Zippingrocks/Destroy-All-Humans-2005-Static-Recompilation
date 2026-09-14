#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <setjmp.h>
#include <stdlib.h>
#include <string.h>
#if defined(_MSC_VER)
#include <windows.h>
#include <intrin.h>
#endif
#include <xbox/xboxrecomp.h>
#include "xinput_xbox.h"
#include "recomp_types.h"

extern volatile uint64_t g_icall_count;
static RECOMP_TLS uint32_t g_dah_last_error;

typedef void (*recomp_func_t)(void);

/* Original render-target encoder jump-table arms. */
extern void sub_001E0436(void);
extern void sub_001E045D(void);
extern void sub_001E0489(void);
extern void sub_001E0497(void);
extern void sub_001E049E(void);
extern void sub_001E04AC(void);
extern void sub_001E04B3(void);
extern void sub_001E04BA(void);
extern void sub_001E04C1(void);
extern void sub_001E04C4(void);
extern void sub_001E04D5(void);
extern void sub_00063510(void);

/*
 * Retail XPP input hardware boundary.
 *
 * The original XInput library expects the Xbox USB stack to construct an
 * opaque handle. The PC runtime has no Xbox USB bus, but it already has an
 * Xbox-pad-to-Windows-XInput translator. Keep the substitution here, at the
 * library boundary, so no retail game logic or data needs to be changed.
 */
#define DAH_INPUT_HANDLE_BASE 0xDA110000u
static int g_dah_input_initialized;
static int g_dah_input_reported;
static unsigned g_dah_input_state_calls;
static unsigned g_dah_keyboard_trace_count;
static uint32_t g_dah_keyboard_last_mask;
static unsigned g_dah_autostart_frames;
static int g_dah_autostart_enabled = -1;
static unsigned g_dah_autostart_delay;
static int g_dah_autostart_logged;
static int g_dah_autostart2_enabled = -1;
static unsigned g_dah_autostart2_delay;
static unsigned g_dah_autostart2_frames;
static int g_dah_autostart2_logged;
static int g_dah_autoa_enabled = -1;
static unsigned g_dah_autoa_delay;
static unsigned g_dah_autoa_frames;
static int g_dah_autoa_logged;

/* Internal probes run alongside the user's applications.  They expose a
 * neutral logical pad, with only the explicitly enabled scripted presses
 * below, and never inspect or drive physical input devices. */
static int dah_input_is_internal(void)
{
    static int internal_run = -1;
    if (internal_run < 0) {
        const char *value = getenv("DAH_INTERNAL_RUN");
        internal_run = value && strcmp(value, "1") == 0;
    }
    return internal_run;
}

static void dah_input_initialize_once(void)
{
    if (!g_dah_input_initialized) {
        if (!dah_input_is_internal())
            xbox_InputInit();
        g_dah_input_initialized = 1;
        if (dah_input_is_internal()) {
            fprintf(stderr,
                    "[DAH-INPUT] internal run: physical input and vibration disabled; scripted input only\n");
        } else {
            fprintf(stderr,
                    "[DAH-INPUT] PC input bridge initialized; host-pad0=%s, neutral fallback enabled\n",
                    xbox_InputIsConnected(0) ? "connected" : "absent");
        }
    }
}

static int dah_input_handle_port(uint32_t handle, uint32_t *port)
{
    uint32_t candidate = handle - DAH_INPUT_HANDLE_BASE;
    if (candidate >= XBOX_MAX_CONTROLLERS)
        return 0;
    *port = candidate;
    return 1;
}

void dah_xget_devices_bridge(void)
{
    uint32_t type = MEM32(g_esp + 4u);
    dah_input_initialize_once();
    g_dah_input_reported = 1;
    g_eax = 1u; /* Port zero is always available through host/neutral input. */
    g_esp += 8u; /* ret 4 */
    fprintf(stderr, "[DAH-INPUT] XGetDevices type=%08X mask=00000001\n", type);
}

void dah_xget_device_changes_bridge(void)
{
    uint32_t type = MEM32(g_esp + 4u);
    uint32_t inserted_out = MEM32(g_esp + 8u);
    uint32_t removed_out = MEM32(g_esp + 12u);
    uint32_t inserted;

    dah_input_initialize_once();
    inserted = g_dah_input_reported ? 0u : 1u;
    g_dah_input_reported = 1;
    MEM32(inserted_out) = inserted;
    MEM32(removed_out) = 0u;
    g_eax = inserted != 0u;
    g_esp += 16u; /* ret 12 */
    if (inserted)
        fprintf(stderr,
                "[DAH-INPUT] XGetDeviceChanges type=%08X inserted=00000001\n",
                type);
}

void dah_xinput_open_bridge(void)
{
    uint32_t type = MEM32(g_esp + 4u);
    uint32_t port = MEM32(g_esp + 8u);
    uint32_t slot = MEM32(g_esp + 12u);
    uint32_t polling = MEM32(g_esp + 16u);

    dah_input_initialize_once();
    if (port < XBOX_MAX_CONTROLLERS && slot == 0u) {
        g_eax = DAH_INPUT_HANDLE_BASE + port;
        fprintf(stderr,
                "[DAH-INPUT] XInputOpen type=%08X port=%u slot=%u polling=%08X handle=%08X\n",
                type, port, slot, polling, g_eax);
    } else {
        g_eax = 0u;
        fprintf(stderr,
                "[DAH-INPUT] XInputOpen rejected port=%u slot=%u polling=%08X\n",
                port, slot, polling);
    }
    g_esp += 20u; /* ret 16 */
}

void dah_xinput_close_bridge(void)
{
    uint32_t handle = MEM32(g_esp + 4u);
    uint32_t port;
    if (!dah_input_handle_port(handle, &port))
        fprintf(stderr, "[DAH-INPUT] XInputClose unknown handle=%08X\n", handle);
    g_esp += 8u; /* ret 4 */
}

/* Keep the PC build playable when no physical XInput pad is attached.  The
 * overlay is deliberately applied after the real pad poll, so a controller
 * remains authoritative while the keyboard provides a small, conventional
 * fallback for frontend navigation and the first movement test. */
static int dah_key_down(int virtual_key)
{
    if (dah_input_is_internal())
        return 0;
    return (GetAsyncKeyState(virtual_key) & 0x8000) != 0;
}

static void dah_apply_keyboard_overlay(XBOX_INPUT_STATE *state)
{
    uint32_t key_mask = 0;
    int up = dah_key_down(VK_UP) || dah_key_down('W');
    int down = dah_key_down(VK_DOWN) || dah_key_down('S');
    int left = dah_key_down(VK_LEFT) || dah_key_down('A');
    int right = dah_key_down(VK_RIGHT) || dah_key_down('D');
    int action = dah_key_down(VK_RETURN) || dah_key_down(VK_SPACE);

    /* Opt-in boot probe for headless/recomp bring-up. Holding A for a short
     * window exercises the retail title's real frontend transition without
     * changing normal keyboard or controller behavior. */
    if (g_dah_autostart_enabled < 0) {
        const char *v = getenv("DAH_AUTOSTART");
        g_dah_autostart_enabled = v ? (atoi(v) != 0 ? 1 : 0) : 1;
    }
    if (g_dah_autostart_enabled && g_dah_autostart_frames == 0u) {
        const char *delay = getenv("DAH_AUTOSTART_DELAY");
        g_dah_autostart_delay = delay ? (unsigned)strtoul(delay, NULL, 10) : 6u;
        /* Store one-based progress so delay=0 still starts immediately. */
        g_dah_autostart_frames = 1u;
    }
    if (g_dah_autostart_enabled &&
        g_dah_input_state_calls >= g_dah_autostart_delay &&
        g_dah_input_state_calls < g_dah_autostart_delay + 45u) {
        /* The retail title prompt is PRESS START, not the face-button A. */
        state->Gamepad.wButtons |= XBOX_GAMEPAD_START;
        action = 0;
        if (!g_dah_autostart_logged) {
            fprintf(stderr, "[DAH-AUTOSTART] injecting START at input_call=%u delay=%u\n",
                    g_dah_input_state_calls, g_dah_autostart_delay);
            fflush(stderr);
            g_dah_autostart_logged = 1;
        }
        ++g_dah_autostart_frames;
    }

    /* A second, later START is useful for the retail legal/intro gate: the
     * first START leaves the title, while the next one advances the shell's
     * intro screen.  It is independently opt-in for controlled probes. */
    if (g_dah_autostart2_enabled < 0) {
        const char *v = getenv("DAH_AUTOSTART2");
        g_dah_autostart2_enabled = v ? (atoi(v) != 0 ? 1 : 0) : 1;
    }
    if (g_dah_autostart2_enabled && g_dah_autostart2_frames == 0u) {
        const char *delay = getenv("DAH_AUTOSTART2_DELAY");
        g_dah_autostart2_delay = delay ? (unsigned)strtoul(delay, NULL, 10) : 120u;
        g_dah_autostart2_frames = 1u;
    }
    if (g_dah_autostart2_enabled &&
        g_dah_input_state_calls >= g_dah_autostart2_delay &&
        g_dah_input_state_calls < g_dah_autostart2_delay + 30u) {
        state->Gamepad.wButtons |= XBOX_GAMEPAD_START;
        action = 0;
        if (!g_dah_autostart2_logged) {
            fprintf(stderr, "[DAH-AUTOSTART2] injecting START at input_call=%u delay=%u\n",
                    g_dah_input_state_calls, g_dah_autostart2_delay);
            fflush(stderr);
            g_dah_autostart2_logged = 1;
        }
        ++g_dah_autostart2_frames;
    }

    /* Optional second-stage probe: after the title's real START transition,
     * press A once on the shell's default menu item.  This stays opt-in so a
     * normal desktop run never skips the frontend. */
    if (g_dah_autoa_enabled < 0) {
        const char *v = getenv("DAH_AUTOA");
        g_dah_autoa_enabled = v ? (atoi(v) != 0 ? 1 : 0) : 1;
    }
    if (g_dah_autoa_enabled && g_dah_autoa_frames == 0u) {
        const char *delay = getenv("DAH_AUTOA_DELAY");
        g_dah_autoa_delay = delay ? (unsigned)strtoul(delay, NULL, 10) : 180u;
        g_dah_autoa_frames = 1u;
    }
    if (g_dah_autoa_enabled &&
        g_dah_input_state_calls >= g_dah_autoa_delay &&
        g_dah_input_state_calls < g_dah_autoa_delay + 30u) {
        state->Gamepad.bAnalogButtons[XBOX_BUTTON_A] = 255;
        action = 0;
        if (!g_dah_autoa_logged) {
            fprintf(stderr, "[DAH-AUTOA] injecting A at input_call=%u delay=%u\n",
                    g_dah_input_state_calls, g_dah_autoa_delay);
            fflush(stderr);
            g_dah_autoa_logged = 1;
        }
        ++g_dah_autoa_frames;
    }

    if (up) {
        key_mask |= 1u << 0;
        state->Gamepad.wButtons |= XBOX_GAMEPAD_DPAD_UP;
        state->Gamepad.sThumbLY = 32767;
    }
    if (down) {
        key_mask |= 1u << 1;
        state->Gamepad.wButtons |= XBOX_GAMEPAD_DPAD_DOWN;
        state->Gamepad.sThumbLY = -32768;
    }
    if (left) {
        key_mask |= 1u << 2;
        state->Gamepad.wButtons |= XBOX_GAMEPAD_DPAD_LEFT;
        state->Gamepad.sThumbLX = -32768;
    }
    if (right) {
        key_mask |= 1u << 3;
        state->Gamepad.wButtons |= XBOX_GAMEPAD_DPAD_RIGHT;
        state->Gamepad.sThumbLX = 32767;
    }
    if (action) {
        key_mask |= 1u << 4;
        state->Gamepad.bAnalogButtons[XBOX_BUTTON_A] = 255;
    }
    if (dah_key_down('Q')) {
        key_mask |= 1u << 5;
        state->Gamepad.bAnalogButtons[XBOX_BUTTON_B] = 255;
    }
    if (dah_key_down('F')) {
        key_mask |= 1u << 6;
        state->Gamepad.bAnalogButtons[XBOX_BUTTON_X] = 255;
    }
    if (dah_key_down('R')) {
        key_mask |= 1u << 7;
        state->Gamepad.bAnalogButtons[XBOX_BUTTON_Y] = 255;
    }
    if (dah_key_down(VK_ESCAPE)) {
        key_mask |= 1u << 8;
        state->Gamepad.wButtons |= XBOX_GAMEPAD_BACK;
    }
    if (dah_key_down(VK_LSHIFT) || dah_key_down(VK_RSHIFT)) {
        key_mask |= 1u << 9;
        state->Gamepad.bAnalogButtons[XBOX_BUTTON_BLACK] = 255;
    }
    if (dah_key_down(VK_LCONTROL) || dah_key_down(VK_RCONTROL)) {
        key_mask |= 1u << 10;
        state->Gamepad.bAnalogButtons[XBOX_BUTTON_WHITE] = 255;
    }

    /* IJKL gives the right stick a keyboard path without conflicting with
     * WASD movement. */
    if (dah_key_down('I')) state->Gamepad.sThumbRY = 32767;
    if (dah_key_down('K')) state->Gamepad.sThumbRY = -32768;
    if (dah_key_down('J')) state->Gamepad.sThumbRX = -32768;
    if (dah_key_down('L')) state->Gamepad.sThumbRX = 32767;

    if (key_mask != g_dah_keyboard_last_mask && g_dah_keyboard_trace_count < 64u) {
        fprintf(stderr,
                "[DAH-INPUT-KEYBOARD] mask=%08X lx=%d ly=%d rx=%d ry=%d\n",
                key_mask, (int)state->Gamepad.sThumbLX,
                (int)state->Gamepad.sThumbLY, (int)state->Gamepad.sThumbRX,
                (int)state->Gamepad.sThumbRY);
        fflush(stderr);
        g_dah_keyboard_trace_count++;
    }
    g_dah_keyboard_last_mask = key_mask;
}

void dah_xinput_get_state_bridge(void)
{
    uint32_t handle = MEM32(g_esp + 4u);
    uint32_t output = MEM32(g_esp + 8u);
    uint32_t port;
    XBOX_INPUT_STATE state;
    DWORD result;

    memset(&state, 0, sizeof(state));
    dah_input_initialize_once();
    if (!dah_input_handle_port(handle, &port) || output == 0u) {
        result = ERROR_DEVICE_NOT_CONNECTED;
    } else {
        result = dah_input_is_internal() ? ERROR_SUCCESS :
                 xbox_InputGetState(port, &state);
        if (result != ERROR_SUCCESS) {
            /* A neutral logical controller keeps retail's frontend alive on
             * keyboard-only systems; the overlay below adds PC controls. */
            memset(&state, 0, sizeof(state));
            result = ERROR_SUCCESS;
        }
        dah_apply_keyboard_overlay(&state);
        memcpy((void *)((uintptr_t)xbox_GetMemoryOffset() + output),
               &state, 22u);
    }
    g_eax = result;
    g_esp += 12u; /* ret 8 */
    ++g_dah_input_state_calls;
    if (g_dah_input_state_calls <= 4u ||
        (g_dah_input_state_calls % 10000u) == 0u) {
        fprintf(stderr,
                "[DAH-INPUT] XInputGetState call=%u handle=%08X out=%08X result=%u\n",
                g_dah_input_state_calls, handle, output, result);
    }
}

void dah_xinput_set_state_bridge(void)
{
    uint32_t handle = MEM32(g_esp + 4u);
    uint32_t vibration = MEM32(g_esp + 8u);
    uint32_t port;
    XBOX_VIBRATION state = {0};
    DWORD result = ERROR_DEVICE_NOT_CONNECTED;

    if (dah_input_handle_port(handle, &port) && vibration != 0u) {
        if (dah_input_is_internal()) {
            result = ERROR_SUCCESS;
        } else {
            state.wLeftMotorSpeed = MEM16(vibration);
            state.wRightMotorSpeed = MEM16(vibration + 2u);
            result = xbox_InputSetState(port, &state);
        }
        if (result == ERROR_DEVICE_NOT_CONNECTED)
            result = ERROR_SUCCESS;
    }
    g_eax = result;
    g_esp += 12u; /* ret 8 */
}

/* sub_000D83E0 converts the Xbox CPU's 733.3 MHz time-stamp counter to
 * milliseconds.  Host RDTSC is not a compatible substitute because its
 * frequency varies by machine, so expose the equivalent monotonic value. */
uint32_t dah_monotonic_milliseconds(void)
{
    return (uint32_t)GetTickCount64();
}

/* The retail container code uses the CRT setjmp/longjmp pair as a local
 * exception guard.  Guest ESP/register restoration alone cannot unwind the
 * native C calls made by the recomp, so bridge that one active guard through
 * the host CRT as well. */
#define DAH_CONTAINER_JMP_MAX 16u
struct dah_container_jmp_context {
    jmp_buf host;
    uint32_t guest;
    uint32_t frame;
    uint32_t resume_esp;
};
static RECOMP_TLS struct dah_container_jmp_context
    g_dah_container_jmps[DAH_CONTAINER_JMP_MAX];
static RECOMP_TLS uint32_t g_dah_container_jmp_depth;

int dah_try_host_longjmp(uint32_t guest_buffer)
{
    uint32_t i = g_dah_container_jmp_depth;
    while (i != 0u) {
        struct dah_container_jmp_context *context =
            &g_dah_container_jmps[i - 1u];
        if (context->guest == guest_buffer) {
            g_ebx = MEM32(guest_buffer + 4u);
            g_edi = MEM32(guest_buffer + 8u);
            g_esi = MEM32(guest_buffer + 0xCu);
            g_esp = context->resume_esp;
            g_eax = 1u;
            /* Discard any nested guards that this throw bypasses. */
            g_dah_container_jmp_depth = i;
            longjmp(context->host, 1);
        }
        --i;
    }
    return 0;
}

void dah_sub_001925C0_host_guard(void)
{
    uint32_t frame;
    uint32_t object;
    uint32_t target;
    uint32_t saved_ebp;
    volatile uint32_t guard_index;
    struct dah_container_jmp_context *context;
    int jumped;

    if (g_dah_container_jmp_depth >= DAH_CONTAINER_JMP_MAX) {
        fprintf(stderr, "[DAH-CONTAINER] host guard nesting overflow\n");
        g_eax = 0u;
        g_esp += 8u;
        return;
    }
    guard_index = g_dah_container_jmp_depth++;
    context = &g_dah_container_jmps[guard_index];

    /* Recreate sub_001925C0's guest frame exactly through its saved EDI. */
    PUSH32(g_esp, g_ebp);
    frame = g_esp;
    g_ebp = frame;
    g_esp -= 0x5Cu;
    PUSH32(g_esp, g_esi);
    g_esi = g_ecx;
    object = g_esi;

    MEM32(frame - 12u) = MEM32(object + 0x10u);
    MEM32(frame - 28u) = MEM32(object + 0x14u);
    MEM32(frame - 20u) = g_edx;
    MEM32(frame - 16u) = MEM32(object);
    MEM32(frame - 4u) = object;
    MEM32(frame - 8u) = MEM32(object + 0x74u);
    MEM32(frame - 24u) = 0u;
    PUSH32(g_esp, g_edi);

    context->frame = frame;
    context->guest = frame - 0x5Cu;
    context->resume_esp = g_esp;
    MEM32(object + 0x14u) = context->guest;

    /* Populate the guest buffer too: code below the throwing callback reads
     * its fields before reaching the host bridge. */
    MEM32(context->guest) = frame;
    MEM32(context->guest + 4u) = g_ebx;
    MEM32(context->guest + 8u) = g_edi;
    MEM32(context->guest + 0xCu) = g_esi;
    MEM32(context->guest + 0x10u) = g_esp - 12u;
    MEM32(context->guest + 0x14u) = 0x00192607u;
    MEM32(context->guest + 0x20u) = 0x56433230u;

    jumped = setjmp(context->host);
    context = &g_dah_container_jmps[guard_index];
    frame = context->frame;
    object = MEM32(frame - 4u);

    if (jumped != 0) {
        uint32_t begin = MEM32(frame - 16u);
        uint32_t storage;
        uint32_t count;

        g_dah_container_jmp_depth = guard_index;
        g_esp = context->resume_esp;
        MEM32(object + 0x74u) = MEM32(frame - 8u);
        MEM32(object + 0x10u) = MEM32(frame - 12u);
        MEM32(object) = begin;
        storage = MEM32(object + 4u);
        count = (uint32_t)((int32_t)(begin - storage) >> 3);
        g_esi = MEM32(object + 0xCu);

        if ((int32_t)count < (int32_t)(g_esi - 1u))
            MEM32(object + 8u) = storage + g_esi * 8u - 8u;
        MEM32(object + 0x14u) = MEM32(frame - 28u);
    } else {
        uint32_t call_esp;
        target = MEM32(frame - 20u);
        g_edx = MEM32(frame + 8u);
        g_ecx = object;
        call_esp = g_esp;
        PUSH32(g_esp, 0x00192657u);
#define eax g_eax
        RECOMP_ICALL_SAFE(target, call_esp);
#undef eax
        g_dah_container_jmp_depth = guard_index;
        MEM32(object + 0x14u) = MEM32(frame - 28u);
    }

    g_eax = MEM32(frame - 24u);
    POP32(g_esp, g_edi);
    POP32(g_esp, g_esi);
    g_esp = frame;
    POP32(g_esp, saved_ebp);
    g_ebp = saved_ebp;
    g_esp += 8u; /* ret 4 */
}

extern void sub_0006B790(void);
extern void sub_000DB540(void);
extern void sub_000DB500(void);
extern void sub_000DB150(void);
extern void sub_000DB220(void);
extern void sub_000DB3C0(void);
extern void sub_000DCD40(void);
extern void sub_000DCDE0(void);
extern void sub_000E0F50(void);
extern void sub_000F0D10(void);
extern void sub_000F1800(void);
extern void sub_00122980(void);
extern void sub_00217680(void);
extern void sub_00217B70(void);
extern void sub_00218530(void);
extern void sub_0021F040(void);
extern void sub_0021F200(void);
extern void sub_0021F480(void);
extern void sub_0021F7A0(void);
extern void sub_001A18E0(void);
extern void sub_00195BD6(void);
extern void sub_00195BDD(void);
extern void sub_0019200C(void);
extern void sub_00191FAA(void);
extern void sub_00192022(void);
extern void sub_0019203A(void);
extern void sub_00192607(void);
extern void sub_00199738(void);
extern void sub_001997C4(void);
extern void sub_00199837(void);
extern void sub_001998F5(void);
extern void sub_00197006(void);
extern void sub_0019703C(void);
extern void sub_0019704A(void);
extern void sub_00197060(void);
extern void sub_00196A1E(void);
extern void sub_00196A39(void);
extern void sub_00196917(void);
extern void sub_0019695D(void);
extern void sub_001969DB(void);
extern void sub_0019683F(void);
extern void sub_00196815(void);
extern void sub_00196853(void);
extern void sub_0019685E(void);
extern void sub_0019687F(void);
extern void sub_0019689B(void);
extern void sub_001968B9(void);
extern void sub_001968DE(void);
extern void sub_001968FB(void);
extern void sub_0008B9A0(void);
extern void sub_000BBA10(void);
extern void sub_000FE7B0(void);
extern void sub_0013C5A6(void);
extern void sub_0013B5A0(void);
extern void sub_0013F420(void);
extern void sub_0013F459(void);
extern void sub_0013F45B(void);
extern void sub_0013F483(void);
extern void sub_0013F4C2(void);
extern void sub_0008BA90(void);
extern void sub_000E3BE0(void);
extern void sub_0011C180(void);
extern void sub_001F225D(void);
extern void sub_001F1C82(void);
extern void sub_001F24F3(void);
extern void sub_001933D0(void);
extern void sub_0013E6CF(void);
extern void sub_000E0510(void);
extern void sub_001F24A8(void);
extern void sub_001ED372(void);
extern void sub_001ED270(void);
extern void sub_001ED3BD(void);
extern void sub_001022D0(void);
extern void sub_001023E0(void);
extern void sub_00103F20(void);
extern void sub_00101220(void);
extern void sub_00104480(void);
extern void sub_00104510(void);
extern void sub_0019693D(void);
extern void sub_00196978(void);
extern void sub_00196993(void);
extern void sub_00196A02(void);
extern void sub_00196A66(void);
extern void sub_00196B05(void);
extern void sub_00196B5A(void);
extern void sub_00196BB7(void);
extern void sub_00196C61(void);
extern void sub_00196CB6(void);
extern void sub_00196CD9(void);
extern void sub_00196D45(void);
extern void sub_00196DBE(void);
extern void sub_00196DDC(void);
extern void sub_00196DF0(void);
extern void sub_00196E0F(void);
extern void sub_00196E6A(void);
extern void sub_00196E78(void);
extern void sub_00196E8A(void);
extern void sub_00196EA4(void);
extern void sub_00196F35(void);
extern void sub_00196F85(void);
extern void sub_00196FD1(void);
extern void sub_0020B060(void);
extern void sub_0020E010(void);
extern void sub_001F4ADB(void);
extern void sub_00068B50(void);
extern void sub_00188750(void);
extern void sub_000F7180(void);
extern void sub_001ECE7E(void);
extern void sub_001F50FF(void);
extern void sub_001EC7B9(void);
extern void sub_001F49F9(void);
extern void sub_001EE1DE(void);
extern void sub_001F514E(void);
extern void sub_001EF685(void);
extern void sub_00196E42(void);
extern void sub_00196E56(void);
extern void sub_00196D92(void);
extern void sub_00196DA7(void);
extern void sub_00196D66(void);
extern void sub_00196C0C(void);
extern void sub_00196D04(void);
extern void sub_00196AB8(void);
extern void sub_00139A80(void);
extern void sub_0005A530(void);
extern void sub_0005A540(void);
extern void sub_000E09F0(void);
extern void sub_00181780(void);
extern void sub_000E32E0(void);
extern void sub_000DB750(void);
extern void sub_000F5700(void);
extern void sub_000F32E0(void);
extern void sub_000E4E50(void);
extern void sub_00081300(void);
extern void sub_000838F0(void);
extern void sub_000F85E0(void);
extern void sub_000FEA90(void);
extern void sub_00070610(void);
extern void sub_0005B8D0(void);
extern void sub_0004F540(void);
extern void sub_000E6E20(void);
extern void sub_00195BC7(void);
extern void sub_001EC7AC(void);
extern void sub_001ECE37(void);
extern void sub_001F4FE5(void);
extern void sub_002206E2(void);
extern void sub_0021FA38(void);
extern void sub_0021FADB(void);

static void trace_game_boot(void)
{
    fprintf(stderr, "[DAH] entered game bootstrap 0x0006B790 (esp=0x%08X)\n", g_esp);
    fflush(stderr);
    sub_0006B790();
    fprintf(stderr, "[DAH] game bootstrap returned (eax=0x%08X esp=0x%08X)\n",
            g_eax, g_esp);
    fflush(stderr);
}

/* MSVC's optimized memmove uses interior computed jumps into a byte-count
 * table. Those are valid x86 basic-block targets, not separate functions,
 * and must not go through the function dispatcher. A native implementation
 * is both equivalent and avoids manufacturing dozens of false functions. */
void sub_00139DE0(void)
{
    uint32_t destination = MEM32(g_esp + 4);
    uint32_t source = MEM32(g_esp + 8);
    uint32_t count = MEM32(g_esp + 12);
    memmove(XBOX_PTR(destination), XBOX_PTR(source), count);
    g_eax = destination;
    g_esp += 4;
}

/* XAPI normally reads the Xbox HDD's raw partition table through Partition0
 * to discover title-data/cache volumes. A host directory has no raw FATX
 * table, so report the emulated Partition1 for both writable roots. The path
 * layer then redirects T:/U: into the per-title save directory. */
void sub_000B1B34(void)
{
    uint32_t first_partition_out = MEM32(g_esp + 8);
    uint32_t second_partition_out = MEM32(g_esp + 12);
    if (first_partition_out) MEM32(first_partition_out) = 1;
    if (second_partition_out) MEM32(second_partition_out) = 1;
    g_eax = 0;
    g_esp += 16;
}

/* XAPI's mount initialization formats a raw FATX partition when its on-disk
 * volume header is absent. The recomp maps that volume to an ordinary host
 * directory, so there is neither a raw device to format nor any need to do
 * so. Treat the host-backed directory as an already initialized volume. */
void sub_000B30A8(void)
{
    fprintf(stderr, "[DAH] accepting host-backed FATX volume initialization\n");
    g_eax = 1;
    g_esp += 12;
}

/* XapiSetLastError normally writes through the Xbox KPCR/TEB at low virtual
 * addresses 0x20-0x28. Keep the same per-thread state natively until the host
 * kernel exposes a full guest KPCR. */
void sub_000B2855(void)
{
    g_dah_last_error = MEM32(g_esp + 4);
    g_esp += 8;
}

recomp_func_t recomp_lookup_manual(uint32_t xbox_va)
{
    if (xbox_va == 0x00063510u) return sub_00063510;
    if (xbox_va == 0x001E0436u) return sub_001E0436;
    if (xbox_va == 0x001E045Du) return sub_001E045D;
    if (xbox_va == 0x001E0489u) return sub_001E0489;
    if (xbox_va == 0x001E0497u) return sub_001E0497;
    if (xbox_va == 0x001E049Eu) return sub_001E049E;
    if (xbox_va == 0x001E04ACu) return sub_001E04AC;
    if (xbox_va == 0x001E04B3u) return sub_001E04B3;
    if (xbox_va == 0x001E04BAu) return sub_001E04BA;
    if (xbox_va == 0x001E04C1u) return sub_001E04C1;
    if (xbox_va == 0x001E04C4u) return sub_001E04C4;
    if (xbox_va == 0x001E04D5u) return sub_001E04D5;
    if (xbox_va == 0x0006B790u) return trace_game_boot;
    if (xbox_va == 0x000DB150u) return sub_000DB150;
    if (xbox_va == 0x000DB220u) return sub_000DB220;
    if (xbox_va == 0x000DB3C0u) return sub_000DB3C0;
    if (xbox_va == 0x000DB500u) return sub_000DB500;
    if (xbox_va == 0x000DB540u) return sub_000DB540;
    if (xbox_va == 0x000DCD40u) return sub_000DCD40;
    if (xbox_va == 0x000DCDE0u) return sub_000DCDE0;
    if (xbox_va == 0x000E0F50u) return sub_000E0F50;
    if (xbox_va == 0x000F0D10u) return sub_000F0D10;
    if (xbox_va == 0x000F1800u) return sub_000F1800;
    if (xbox_va == 0x00122980u) return sub_00122980;
    if (xbox_va == 0x00217680u) return sub_00217680;
    if (xbox_va == 0x00217B70u) return sub_00217B70;
    if (xbox_va == 0x00218530u) return sub_00218530;
    if (xbox_va == 0x0021F040u) return sub_0021F040;
    if (xbox_va == 0x0021F200u) return sub_0021F200;
    if (xbox_va == 0x0021F480u) return sub_0021F480;
    if (xbox_va == 0x0021F7A0u) return sub_0021F7A0;
    if (xbox_va == 0x001A18E0u) return sub_001A18E0;
    if (xbox_va == 0x00195BD6u) return sub_00195BD6;
    if (xbox_va == 0x00195BDDu) return sub_00195BDD;
    if (xbox_va == 0x0019200Cu) return sub_0019200C;
    if (xbox_va == 0x00191FAAu) return sub_00191FAA;
    if (xbox_va == 0x00192022u) return sub_00192022;
    if (xbox_va == 0x0019203Au) return sub_0019203A;
    if (xbox_va == 0x00192607u) return sub_00192607;
    if (xbox_va == 0x00199738u) return sub_00199738;
    if (xbox_va == 0x001997C4u) return sub_001997C4;
    if (xbox_va == 0x00199837u) return sub_00199837;
    if (xbox_va == 0x001998F5u) return sub_001998F5;
    if (xbox_va == 0x00197006u) return sub_00197006;
    if (xbox_va == 0x0019703Cu) return sub_0019703C;
    if (xbox_va == 0x0019704Au) return sub_0019704A;
    if (xbox_va == 0x00197060u) return sub_00197060;
    if (xbox_va == 0x00196A1Eu) return sub_00196A1E;
    if (xbox_va == 0x00196A39u) return sub_00196A39;
    if (xbox_va == 0x00196917u) return sub_00196917;
    if (xbox_va == 0x0019695Du) return sub_0019695D;
    if (xbox_va == 0x001969DBu) return sub_001969DB;
    if (xbox_va == 0x0019683Fu) return sub_0019683F;
    if (xbox_va == 0x00196815u) return sub_00196815;
    if (xbox_va == 0x00196853u) return sub_00196853;
    if (xbox_va == 0x0019685Eu) return sub_0019685E;
    if (xbox_va == 0x0019687Fu) return sub_0019687F;
    if (xbox_va == 0x0019689Bu) return sub_0019689B;
    if (xbox_va == 0x001968B9u) return sub_001968B9;
    if (xbox_va == 0x001968DEu) return sub_001968DE;
    if (xbox_va == 0x001968FBu) return sub_001968FB;
    if (xbox_va == 0x0008B9A0u) return sub_0008B9A0;
    if (xbox_va == 0x000BBA10u) return sub_000BBA10;
    if (xbox_va == 0x000FE7B0u) return sub_000FE7B0;
    if (xbox_va == 0x0013C5A6u) return sub_0013C5A6;
    if (xbox_va == 0x0013B5A0u) return sub_0013B5A0;
    if (xbox_va == 0x0013F420u) return sub_0013F420;
    if (xbox_va == 0x0013F459u) return sub_0013F459;
    if (xbox_va == 0x0013F45Bu) return sub_0013F45B;
    if (xbox_va == 0x0013F483u) return sub_0013F483;
    if (xbox_va == 0x0013F4C2u) return sub_0013F4C2;
    if (xbox_va == 0x0008BA90u) return sub_0008BA90;
    if (xbox_va == 0x000E3BE0u) return sub_000E3BE0;
    if (xbox_va == 0x0011C180u) return sub_0011C180;
    if (xbox_va == 0x001F225Du) return sub_001F225D;
    if (xbox_va == 0x001F1C82u) return sub_001F1C82;
    if (xbox_va == 0x001F24F3u) return sub_001F24F3;
    if (xbox_va == 0x001933D0u) return sub_001933D0;
    if (xbox_va == 0x0013E6CFu) return sub_0013E6CF;
    if (xbox_va == 0x000E0510u) return sub_000E0510;
    if (xbox_va == 0x001F24A8u) return sub_001F24A8;
    if (xbox_va == 0x001ED372u) return sub_001ED372;
    if (xbox_va == 0x001ED270u) return sub_001ED270;
    if (xbox_va == 0x001ED3BDu) return sub_001ED3BD;
    if (xbox_va == 0x001022D0u) return sub_001022D0;
    if (xbox_va == 0x001023E0u) return sub_001023E0;
    if (xbox_va == 0x00103F20u) return sub_00103F20;
    if (xbox_va == 0x00101220u) return sub_00101220;
    if (xbox_va == 0x00104480u) return sub_00104480;
    if (xbox_va == 0x00104510u) return sub_00104510;
    if (xbox_va == 0x0019693Du) return sub_0019693D;
    if (xbox_va == 0x00196978u) return sub_00196978;
    if (xbox_va == 0x00196993u) return sub_00196993;
    if (xbox_va == 0x00196A02u) return sub_00196A02;
    if (xbox_va == 0x00196A66u) return sub_00196A66;
    if (xbox_va == 0x00196B05u) return sub_00196B05;
    if (xbox_va == 0x00196B5Au) return sub_00196B5A;
    if (xbox_va == 0x00196BB7u) return sub_00196BB7;
    if (xbox_va == 0x00196C61u) return sub_00196C61;
    if (xbox_va == 0x00196CB6u) return sub_00196CB6;
    if (xbox_va == 0x00196CD9u) return sub_00196CD9;
    if (xbox_va == 0x00196D45u) return sub_00196D45;
    if (xbox_va == 0x00196DBEu) return sub_00196DBE;
    if (xbox_va == 0x00196DDCu) return sub_00196DDC;
    if (xbox_va == 0x00196DF0u) return sub_00196DF0;
    if (xbox_va == 0x00196E0Fu) return sub_00196E0F;
    if (xbox_va == 0x00196E6Au) return sub_00196E6A;
    if (xbox_va == 0x00196E78u) return sub_00196E78;
    if (xbox_va == 0x00196E8Au) return sub_00196E8A;
    if (xbox_va == 0x00196EA4u) return sub_00196EA4;
    if (xbox_va == 0x00196F35u) return sub_00196F35;
    if (xbox_va == 0x00196F85u) return sub_00196F85;
    if (xbox_va == 0x00196FD1u) return sub_00196FD1;
    if (xbox_va == 0x0020B060u) return sub_0020B060;
    if (xbox_va == 0x0020E010u) return sub_0020E010;
    if (xbox_va == 0x001F4ADBu) return sub_001F4ADB;
    if (xbox_va == 0x00068B50u) return sub_00068B50;
    if (xbox_va == 0x00188750u) return sub_00188750;
    if (xbox_va == 0x000F7180u) return sub_000F7180;
    if (xbox_va == 0x001ECE7Eu) return sub_001ECE7E;
    if (xbox_va == 0x001F50FFu) return sub_001F50FF;
    if (xbox_va == 0x001EC7B9u) return sub_001EC7B9;
    if (xbox_va == 0x001F49F9u) return sub_001F49F9;
    if (xbox_va == 0x001EE1DEu) return sub_001EE1DE;
    if (xbox_va == 0x001F514Eu) return sub_001F514E;
    if (xbox_va == 0x001EF685u) return sub_001EF685;
    if (xbox_va == 0x00196E42u) return sub_00196E42;
    if (xbox_va == 0x00196E56u) return sub_00196E56;
    if (xbox_va == 0x00196D92u) return sub_00196D92;
    if (xbox_va == 0x00196DA7u) return sub_00196DA7;
    if (xbox_va == 0x00196D66u) return sub_00196D66;
    if (xbox_va == 0x00196C0Cu) return sub_00196C0C;
    if (xbox_va == 0x00196D04u) return sub_00196D04;
    if (xbox_va == 0x00196AB8u) return sub_00196AB8;
    if (xbox_va == 0x00139A80u) return sub_00139A80;
    if (xbox_va == 0x0005A530u) return sub_0005A530;
    if (xbox_va == 0x0005A540u) return sub_0005A540;
    if (xbox_va == 0x000E09F0u) return sub_000E09F0;
    if (xbox_va == 0x00181780u) return sub_00181780;
    if (xbox_va == 0x000E32E0u) return sub_000E32E0;
    if (xbox_va == 0x000DB750u) return sub_000DB750;
    if (xbox_va == 0x000F5700u) return sub_000F5700;
    if (xbox_va == 0x000F32E0u) return sub_000F32E0;
    if (xbox_va == 0x000E4E50u) return sub_000E4E50;
    if (xbox_va == 0x00081300u) return sub_00081300;
    if (xbox_va == 0x000838F0u) return sub_000838F0;
    if (xbox_va == 0x000F85E0u) return sub_000F85E0;
    if (xbox_va == 0x000FEA90u) return sub_000FEA90;
    if (xbox_va == 0x00070610u) return sub_00070610;
    if (xbox_va == 0x0005B8D0u) return sub_0005B8D0;
    if (xbox_va == 0x0004F540u) return sub_0004F540;
    if (xbox_va == 0x000E6E20u) return sub_000E6E20;
    if (xbox_va == 0x00195BC7u) return sub_00195BC7;
    if (xbox_va == 0x001EC7ACu) return sub_001EC7AC;
    if (xbox_va == 0x001ECE37u) return sub_001ECE37;
    if (xbox_va == 0x001F4FE5u) return sub_001F4FE5;
    if (xbox_va == 0x002206E2u) return sub_002206E2;
    if (xbox_va == 0x0021FA38u) return sub_0021FA38;
    if (xbox_va == 0x0021FADBu) return sub_0021FADB;
    return NULL;
}

void recomp_icall_fail_log(uint32_t va)
{
    struct fail_site { uint32_t va, ret; uint64_t count; };
    static RECOMP_TLS struct fail_site sites[64];
    static RECOMP_TLS unsigned used;
    uint32_t guest_return = MEM32(g_esp);
    struct fail_site *site = NULL;
    unsigned i;

    for (i = 0; i < used; ++i) {
        /* Values beyond the retail XBE's code range are corrupt pointers,
         * so key those only by target.  Their changing stack data is not a
         * useful collection of distinct call sites. */
        if (sites[i].va == va &&
            (va > 0x00230000u || sites[i].ret == guest_return)) {
            site = &sites[i];
            break;
        }
    }
    if (!site && used < 64) {
        site = &sites[used++];
        site->va = va;
        site->ret = guest_return;
    }
    if (!site)
        return;
    if (site) {
        site->count++;
        if (site->count > 4 && (site->count & (site->count - 1)) != 0)
            return;
    }
    fprintf(stderr,
            "[ICALL] unresolved Xbox target 0x%08X ret=0x%08X esp=0x%08X "
            "eax=%08X ecx=%08X edx=%08X esi=%08X edi=%08X (call %llu)"
#if defined(_MSC_VER)
            " host_rva=%08llX"
#endif
            "\n",
            va, guest_return, g_esp, g_eax, g_ecx, g_edx, g_esi, g_edi,
            (unsigned long long)g_icall_count
#if defined(_MSC_VER)
            , (unsigned long long)((uintptr_t)_ReturnAddress() -
                                   (uintptr_t)GetModuleHandleW(NULL))
#endif
            );
    if (site->count == 1u) {
        uint32_t trace_end = g_icall_trace_idx;
        fprintf(stderr, "[ICALL-TRACE]");
        for (i = 0; i < ICALL_TRACE_SIZE; ++i) {
            uint32_t index = (trace_end - ICALL_TRACE_SIZE + i) &
                             (ICALL_TRACE_SIZE - 1u);
            fprintf(stderr, " %08X", g_icall_trace[index]);
        }
        fputc('\n', stderr);
    }
    fflush(stderr);
}
