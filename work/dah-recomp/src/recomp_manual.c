#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <setjmp.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#if defined(_MSC_VER)
#include <windows.h>
#include <intrin.h>
#endif
#include <xbox/xboxrecomp.h>
#include "xinput_xbox.h"
#include "recomp_types.h"

extern volatile uint64_t g_icall_count;
static RECOMP_TLS uint32_t g_dah_last_error;

/* Dependencies of the byte-verified Rockwell vtable callbacks. */
extern void sub_000417A0(void);
extern void sub_00017EA0(void);
extern void sub_000221A0(void);
extern void sub_0007A130(void);
extern void sub_000A6F60(void);
extern void sub_000817D0(void);
extern void sub_000817E0(void);
extern void sub_00084CB0(void);
extern void sub_00133E80(void);
extern void sub_0012AC30(void);

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
extern void sub_0006F5E0(void);
extern void sub_00139520(void);
extern void sub_0006E240(void);
extern void sub_001394F0(void);
extern void sub_000D54A0(void);
extern void sub_000891F0(void);
extern void sub_00022270(void);
extern void sub_000232D0(void);
extern void sub_001586B0(void);
extern void sub_00016E30(void);
extern void sub_00081B70(void);
static int dah_input_is_internal(void);
static unsigned g_dah_input_state_calls;
/* Read-only diagnostic mirrors used to correlate guest math with the logical
 * pad sample that drove the current frame. */
volatile int dah_trace_input_lx;
volatile int dah_trace_input_ly;
volatile int dah_trace_input_rx;
volatile int dah_trace_input_ry;

/* Apply an actor rotation through the retail setter so the physics object and
 * the cached scene transform change together.  Generated functions operate on
 * the emulated CPU globals, so preserve the interrupted guest call completely. */
static void dah_player_set_physics_rotation(uint32_t actor, float z, float w)
{
    uint32_t saved_eax = g_eax, saved_ebx = g_ebx;
    uint32_t saved_ecx = g_ecx, saved_edx = g_edx;
    uint32_t saved_esi = g_esi, saved_edi = g_edi;
    uint32_t saved_ebp = g_ebp, saved_seh_ebp = g_seh_ebp;
    uint32_t saved_esp = g_esp, quaternion;
    unsigned saved_fp_top = g_fp_top;
    double saved_fp_stack[8];
    RecompXmm saved_xmm[8];
    uint16_t saved_fp_control = g_fp_control_word;
    int saved_fp_cmp = g_fp_cmp;

    memcpy(saved_fp_stack, g_fp_stack, sizeof(saved_fp_stack));
    saved_xmm[0]=g_xmm0; saved_xmm[1]=g_xmm1;
    saved_xmm[2]=g_xmm2; saved_xmm[3]=g_xmm3;
    saved_xmm[4]=g_xmm4; saved_xmm[5]=g_xmm5;
    saved_xmm[6]=g_xmm6; saved_xmm[7]=g_xmm7;

    g_esp -= 16u;
    quaternion = g_esp;
    MEMF(quaternion) = 0.0f;
    MEMF(quaternion + 4u) = 0.0f;
    MEMF(quaternion + 8u) = z;
    MEMF(quaternion + 12u) = w;
    PUSH32(g_esp, 1u);
    PUSH32(g_esp, quaternion);
    g_ecx = actor + 0x18u;
    PUSH32(g_esp, 0u);
    sub_00081B70();

    g_eax=saved_eax; g_ebx=saved_ebx; g_ecx=saved_ecx; g_edx=saved_edx;
    g_esi=saved_esi; g_edi=saved_edi; g_ebp=saved_ebp;
    g_seh_ebp=saved_seh_ebp; g_esp=saved_esp;
    g_fp_top=saved_fp_top; g_fp_cmp=saved_fp_cmp;
    memcpy(g_fp_stack, saved_fp_stack, sizeof(saved_fp_stack));
    g_xmm0=saved_xmm[0]; g_xmm1=saved_xmm[1];
    g_xmm2=saved_xmm[2]; g_xmm3=saved_xmm[3];
    g_xmm4=saved_xmm[4]; g_xmm5=saved_xmm[5];
    g_xmm6=saved_xmm[6]; g_xmm7=saved_xmm[7];
    g_fp_control_word=saved_fp_control;
}

/* Intercept the retail physics body's set-linear-velocity call at the point
 * where its vector is still writable and before integration consumes it. */
void dah_player_velocity_compat(uint32_t physics_body, uint32_t vector)
{
    static int enabled = -1;
    uint32_t system, player, actor, camera, camera_node;
    float lx, ly, expected_x, expected_y, expected_length;
    float velocity_x, velocity_y, speed;

    static unsigned s_vc_trace_count;
    if (enabled < 0) {
        const char *flag = getenv("DAH_PLAYER_MOVEMENT_COMPAT");
        enabled = flag ? (flag[0] && flag[0] != '0') : 1;
    }
    if (!enabled || vector < 0x10000u || vector > 0x08000000u - 12u)
        return;
    system = MEM32(0x0025FCECu);
    if (system < 0x10000u || system > 0x08000000u - 0x3Cu) {
        if (s_vc_trace_count++ < 4u) fprintf(stderr, "[VC-SKIP] no system\n");
        return;
    }
    player = MEM32(system + 0x38u);
    if (player < 0x10000u || player > 0x08000000u - 0x3Cu) {
        if (s_vc_trace_count++ < 4u) fprintf(stderr, "[VC-SKIP] no player\n");
        return;
    }
    actor = MEM32(player + 0x38u);
    if (actor < 0x10000u || actor > 0x08000000u - 0x4A4u ||
        MEM32(actor) != 0x0022C9F8u || MEM32(actor + 0x110u) != physics_body) {
        if (s_vc_trace_count++ < 8u)
            fprintf(stderr, "[VC-SKIP] actor=%08X vtable=%08X actor110=%08X body=%08X\n",
                    actor, actor >= 0x10000u ? MEM32(actor) : 0u,
                    actor >= 0x10000u ? MEM32(actor + 0x110u) : 0u,
                    physics_body);
        return;
    }
    lx = dah_trace_input_lx < 0 ?
         (float)dah_trace_input_lx / 32768.0f :
         (float)dah_trace_input_lx / 32767.0f;
    ly = dah_trace_input_ly < 0 ?
         (float)dah_trace_input_ly / 32768.0f :
         (float)dah_trace_input_ly / 32767.0f;
    if (fabsf(lx) <= 0.02f && fabsf(ly) <= 0.02f) return;
    camera = MEM32(0x00250E60u);
    if (camera < 0x10000u || camera > 0x08000000u - 0xF0u) return;
    camera_node = MEM32(camera + 0xECu);
    if (camera_node < 0x10000u || camera_node > 0x08000000u - 0x70u) {
        if (s_vc_trace_count++ < 4u)
            fprintf(stderr, "[VC-SKIP] camera=%08X camera_node=%08X\n", camera, camera_node);
        return;
    }
    expected_x = MEMF(camera_node + 0x50u) * lx -
                 MEMF(camera_node + 0x60u) * ly;
    expected_y = MEMF(camera_node + 0x54u) * lx -
                 MEMF(camera_node + 0x64u) * ly;
    velocity_x = MEMF(vector);
    velocity_y = MEMF(vector + 4u);
    speed = sqrtf(velocity_x * velocity_x + velocity_y * velocity_y);
    expected_length = sqrtf(expected_x * expected_x + expected_y * expected_y);
    if (speed <= 0.00001f || expected_length <= 0.00001f) return;
    if (s_vc_trace_count++ < 16u)
        fprintf(stderr, "[VC] lx=%.3f ly=%.3f cam_r=%.3f,%.3f cam_f=%.3f,%.3f "
                "vel_in=%.3f,%.3f exp=%.3f,%.3f vel_out=%.3f,%.3f\n",
                (double)lx, (double)ly,
                (double)MEMF(camera_node + 0x50u), (double)MEMF(camera_node + 0x54u),
                (double)MEMF(camera_node + 0x60u), (double)MEMF(camera_node + 0x64u),
                (double)velocity_x, (double)velocity_y,
                (double)expected_x, (double)expected_y,
                (double)(speed * expected_x / expected_length),
                (double)(speed * expected_y / expected_length));
    MEMF(vector) = speed * expected_x / expected_length;
    MEMF(vector + 4u) = speed * expected_y / expected_length;
}

/* Rebuild Crypto's facing from the signed camera-relative input vector.  The
 * current script handoff reflects one horizontal component, so its generated
 * facing can disagree with the direction selected on the stick. */
static void dah_player_movement_compat_apply(void)
{
    static int enabled = -1;
    static int trace_enabled = -1;
    static unsigned last_trace_poll;
    static unsigned component_dump_mask;
    uint32_t system, player, actor, node, actor_object, camera, camera_node;
    float lx, ly, expected_x;
    float desired_yaw, half_yaw, c, s;

    if (enabled < 0) {
        const char *flag = getenv("DAH_PLAYER_MOVEMENT_COMPAT");
        enabled = flag ? (flag[0] && flag[0] != '0') : 1;
    }
    if (trace_enabled < 0) {
        const char *flag = getenv("DAH_PLAYER_MOVEMENT_TRACE");
        trace_enabled = flag && flag[0] && flag[0] != '0';
    }
    if (!enabled) return;
    system = MEM32(0x0025FCECu);
    if (system < 0x10000u || system > 0x08000000u - 0x3Cu) return;
    player = MEM32(system + 0x38u);
    if (player < 0x10000u || player > 0x08000000u - 0x3Cu) return;
    actor = MEM32(player + 0x38u);
    if (actor < 0x10000u || actor > 0x08000000u - 0x4A4u ||
        MEM32(actor) != 0x0022C9F8u) return;
    node = MEM32(actor + 0x4A0u);
    if (node < 0x10000u || node > 0x08000000u - 0x80u) return;
    camera = MEM32(0x00250E60u);
    if (camera < 0x10000u || camera > 0x08000000u - 0xF0u) return;
    camera_node = MEM32(camera + 0xECu);
    if (camera_node < 0x10000u || camera_node > 0x08000000u - 0x70u) return;
    lx = dah_trace_input_lx < 0 ?
         (float)dah_trace_input_lx / 32768.0f :
         (float)dah_trace_input_lx / 32767.0f;
    ly = dah_trace_input_ly < 0 ?
         (float)dah_trace_input_ly / 32768.0f :
         (float)dah_trace_input_ly / 32767.0f;
    expected_x = MEMF(camera_node + 0x50u) * lx -
                 MEMF(camera_node + 0x60u) * ly;
    /* Face the signed camera-relative vector.  The node quaternion
     * is x,y,z,w and the on-foot character remains upright. */
    if (fabsf(lx) > 0.02f || fabsf(ly) > 0.02f) {
        float expected_y = MEMF(camera_node + 0x54u) * lx -
                           MEMF(camera_node + 0x64u) * ly;
        desired_yaw = atan2f(expected_x, -expected_y);
        half_yaw = desired_yaw * 0.5f;
        s = sinf(half_yaw);
        c = cosf(half_yaw);
        MEMF(node + 0x40u) = 0.0f;
        MEMF(node + 0x44u) = 0.0f;
        MEMF(node + 0x48u) = s;
        MEMF(node + 0x4Cu) = c;
        MEMF(node + 0x50u) = cosf(desired_yaw);
        MEMF(node + 0x54u) = sinf(desired_yaw);
        MEMF(node + 0x58u) = 0.0f;
        MEMF(node + 0x60u) = -sinf(desired_yaw);
        MEMF(node + 0x64u) = cosf(desired_yaw);
        MEMF(node + 0x68u) = 0.0f;
        MEMF(node + 0x70u) = 0.0f;
        MEMF(node + 0x74u) = 0.0f;
        MEMF(node + 0x78u) = 1.0f;

        /* The scene node above is only the rendered character.  Use retail's
         * actor setter as well: it forwards the quaternion into the physics
         * controller before updating actor->object and its dirty flag. */
        actor_object = MEM32(actor + 0x28u);
        if (actor_object >= 0x10000u &&
            actor_object <= 0x08000000u - 0x50u) {
            dah_player_set_physics_rotation(actor, s, c);
        }
        if (trace_enabled && g_dah_input_state_calls != last_trace_poll &&
            (g_dah_input_state_calls % 30u) == 0u) {
            uint32_t component = MEM32(actor + 0x138u);
            fprintf(stderr,
                    "[DAH-PLAYER-MOVEMENT] poll=%u sticks=%d,%d actor=%08X object=%08X component=%08X "
                    "actor_xyz=%.6g,%.6g,%.6g object_xyz=%.6g,%.6g,%.6g "
                    "object_q=%.6g,%.6g,%.6g,%.6g component_pos=%.6g,%.6g,%.6g "
                    "component_axes=%.6g,%.6g,%.6g;%.6g,%.6g,%.6g;%.6g,%.6g,%.6g\n",
                    g_dah_input_state_calls, dah_trace_input_lx,
                    dah_trace_input_ly, actor, actor_object, component,
                    (double)MEMF(actor + 0x14Cu),
                    (double)MEMF(actor + 0x150u),
                    (double)MEMF(actor + 0x154u),
                    (double)MEMF(actor_object + 0x2Cu),
                    (double)MEMF(actor_object + 0x30u),
                    (double)MEMF(actor_object + 0x34u),
                    (double)MEMF(actor_object + 0x38u),
                    (double)MEMF(actor_object + 0x3Cu),
                    (double)MEMF(actor_object + 0x40u),
                    (double)MEMF(actor_object + 0x44u),
                    (double)MEMF(component + 0x88u),
                    (double)MEMF(component + 0x94u),
                    (double)MEMF(component + 0xA0u),
                    (double)MEMF(component + 0x58u),
                    (double)MEMF(component + 0x5Cu),
                    (double)MEMF(component + 0x60u),
                    (double)MEMF(component + 0x64u),
                    (double)MEMF(component + 0x68u),
                    (double)MEMF(component + 0x6Cu),
                    (double)MEMF(component + 0x70u),
                    (double)MEMF(component + 0x74u),
                    (double)MEMF(component + 0x78u));
            last_trace_poll = g_dah_input_state_calls;
        }
        if (trace_enabled) {
            unsigned sign_bit = dah_trace_input_ly > 0 ? 1u :
                                dah_trace_input_ly < 0 ? 2u :
                                dah_trace_input_lx > 0 ? 4u : 8u;
            if (!(component_dump_mask & sign_bit)) {
                uint32_t component = MEM32(actor + 0x138u);
                uint32_t physics_iface = actor + 0xC0u;
                uint32_t physics_iface_vtable = MEM32(physics_iface);
                uint32_t physics_body = MEM32(physics_iface + 0x50u);
                uint32_t physics_body_vtable = MEM32(physics_body);
                unsigned offset;
                component_dump_mask |= sign_bit;
                fprintf(stderr,
                        "[DAH-PLAYER-COMPONENT-DUMP] poll=%u sticks=%d,%d component=%08X words=",
                        g_dah_input_state_calls, dah_trace_input_lx,
                        dah_trace_input_ly, component);
                if (component >= 0x10000u && component <= 0x08000000u - 0x180u) {
                    for (offset = 0; offset < 0x180u; offset += 4u)
                        fprintf(stderr, "%08X%s", MEM32(component + offset),
                                offset + 4u == 0x180u ? "" : ",");
                }
                fprintf(stderr, "\n");
                fprintf(stderr,
                        "[DAH-PLAYER-PHYSICS-IFACE] actor=%08X iface=%08X vtable=%08X getter=%08X body=%08X body_vtable=%08X setpos=%08X setrot=%08X setvelocity=%08X component=%08X\n",
                        actor, physics_iface, physics_iface_vtable,
                        MEM32(physics_iface_vtable + 8u), physics_body,
                        physics_body_vtable,
                        MEM32(physics_body_vtable + 0x48u),
                        MEM32(physics_body_vtable + 0x50u),
                        MEM32(physics_body_vtable + 0x90u), component);
                fprintf(stderr, "[DAH-PLAYER-PHYSICS-BODY] poll=%u words=",
                        g_dah_input_state_calls);
                if (physics_body >= 0x10000u &&
                    physics_body <= 0x08000000u - 0x200u) {
                    for (offset = 0; offset < 0x200u; offset += 4u)
                        fprintf(stderr, "%08X%s", MEM32(physics_body + offset),
                                offset + 4u == 0x200u ? "" : ",");
                }
                fprintf(stderr, "\n");
            }
        }
    }
}

/* Gameplay-camera compatibility path.  Retail receives the correct
 * signed right-stick value, but its script camera currently stops updating
 * the view matrix after the first pitch movement.  Apply an accumulated,
 * clamped local-X rotation immediately before the renderer consumes that
 * matrix.  It can be disabled with DAH_CAMERA_PITCH_COMPAT=0 while the
 * missing retail update is being recovered. */
void dah_camera_pitch_compat_apply(void)
{
    static int enabled = -1;
    static uint32_t last_poll;
    static int have_output;
    static float pitch;
    static float last_base[16];
    static float last_output[16];
    static unsigned trace_count;
    uint32_t system, player, actor, camera;
    float base[16], output[16];
    float *view;
    float c, s, normalized;
    int current_is_output = 1;
    unsigned row, i;

    if (enabled < 0) {
        const char *flag = getenv("DAH_CAMERA_PITCH_COMPAT");
        enabled = flag ? (flag[0] && flag[0] != '0') : 1;
    }
    dah_player_movement_compat_apply();
    if (!enabled) return;

    system = MEM32(0x0025FCECu);
    if (system < 0x10000u || system > 0x08000000u - 0x3Cu) return;
    player = MEM32(system + 0x38u);
    if (player < 0x10000u || player > 0x08000000u - 0x3Cu) return;
    actor = MEM32(player + 0x38u);
    if (actor < 0x10000u || actor > 0x08000000u - 0x158u) return;
    camera = MEM32(0x00250E60u);
    if (camera < 0x10000u || camera > 0x08000000u - 0x90u) return;
    view = (float *)XBOX_PTR(camera + 0x50u);

    if (g_dah_input_state_calls != last_poll) {
        normalized = dah_trace_input_ry < 0 ?
            (float)dah_trace_input_ry / 32768.0f :
            (float)dah_trace_input_ry / 32767.0f;
        if (fabsf(normalized) > 0.12f) {
            pitch += normalized * (1.35f / 30.0f);
            if (pitch > 0.90f) pitch = 0.90f;
            if (pitch < -0.90f) pitch = -0.90f;
        }
        last_poll = g_dah_input_state_calls;
    }

    if (have_output) {
        for (i = 0; i < 16u; ++i) {
            if (fabsf(view[i] - last_output[i]) > 0.00001f) {
                current_is_output = 0;
                break;
            }
        }
    } else {
        current_is_output = 0;
    }
    memcpy(base, current_is_output ? last_base : view, sizeof(base));

    /* Row-vector view matrix: post-multiply by a local X rotation. */
    c = cosf(pitch);
    s = sinf(pitch);
    memcpy(output, base, sizeof(output));
    for (row = 0; row < 4u; ++row) {
        const float y = base[row * 4u + 1u];
        const float z = base[row * 4u + 2u];
        output[row * 4u + 1u] = y * c - z * s;
        output[row * 4u + 2u] = y * s + z * c;
    }
    memcpy(view, output, sizeof(output));
    memcpy(last_base, base, sizeof(base));
    memcpy(last_output, output, sizeof(output));
    have_output = 1;

    if (dah_trace_input_ry && trace_count++ < 64u) {
        fprintf(stderr,
                "[DAH-CAMERA-PITCH-COMPAT] poll=%u ry=%d pitch=%.6g row2=%.6g,%.6g,%.6g translation=%.6g,%.6g,%.6g\n",
                g_dah_input_state_calls, dah_trace_input_ry, (double)pitch,
                (double)output[8], (double)output[9], (double)output[10],
                (double)output[12], (double)output[13], (double)output[14]);
    }
}

/* A private, one-command-at-a-time probe of the original generic actor
 * dispatcher. The file lives inside the isolated development save. */
static RECOMP_TLS uint32_t g_dah_dev_npc_hash;
static RECOMP_TLS uint32_t g_dah_dev_npc_actor;
static RECOMP_TLS int g_dah_dev_npc_active;
static RECOMP_TLS int g_dah_dev_npc_result;
static unsigned g_dah_dev_npc_sequence;
static unsigned g_dah_dev_npc_count;
static uint32_t g_dah_console_npc_hash;
static unsigned g_dah_console_muted_ports;
extern int dah_console_is_open(void);
extern int dah_console_key_blocked(int virtual_key);
extern int dah_host_has_input_focus(void);
extern void dah_console_write(const char *format, ...);
extern int dah_console_take_command(char *line, size_t capacity);
extern int dah_request_frame_capture(void);
/* Implemented using the original game's level request API. */
static int dah_console_load_level(const char *alias);

int dah_dev_npc_accept_spawn(uint32_t resource_hash, uint32_t actor)
{
    if (!g_dah_dev_npc_active) return 0;
    if (resource_hash != g_dah_dev_npc_hash || !actor ||
        MEM32(actor) != 0x00226C60u) {
        fprintf(stderr,
                "[DAH-DEV-NPC] dispatcher rejected hash=%08X actor=%08X expected=%08X\n",
                resource_hash, actor, g_dah_dev_npc_hash);
        g_dah_dev_npc_result = -1;
        return -1;
    }
    g_dah_dev_npc_actor = actor;
    g_dah_dev_npc_result = 1;
    return 1;
}

static int dah_dev_npc_private_session(void)
{
    const char *enabled = getenv("DAH_NPC_SPAWN");
    const char *level = getenv("DAH_DEV_LEVEL");
    const char *save_dir = getenv("DAH_SAVE_DIR");
    static const char *const levels[] = {
        "farm", "rockwell", "santa", "area42", "union", "capitol", "cptlboss"
    };
    size_t i, n;
    if (!enabled || strcmp(enabled, "1") || !level || !save_dir ||
        !dah_input_is_internal()) return 0;
    for (i = 0; i < sizeof(levels) / sizeof(levels[0]); ++i)
        if (!strcmp(level, levels[i])) break;
    if (i == sizeof(levels) / sizeof(levels[0])) return 0;
    if (!strstr(save_dir, "\\dev_commands\\sessions\\") &&
        !strstr(save_dir, "/dev_commands/sessions/")) return 0;
    n = strlen(save_dir);
    return n >= 6u && (!strcmp(save_dir + n - 6u, "\\saves") ||
                       !strcmp(save_dir + n - 6u, "/saves"));
}

static int dah_dev_npc_hash_allowed(uint32_t hash)
{
    static const uint32_t hashes[] = {
        0x5AE49481u, 0xE8337A18u, 0x93E45661u,
        0x8FA4309Fu, 0x9AC0FD1Eu, 0x41348393u
    };
    size_t i;
    for (i = 0; i < sizeof(hashes) / sizeof(hashes[0]); ++i)
        if (hash == hashes[i]) return 1;
    return 0;
}

static int dah_dev_npc_guest_ptr(uint32_t pointer)
{
    return pointer >= 0x00010000u && pointer < 0x07FFFFC0u;
}

/* Retail player.GetPlayer and player.GetCharacter locate Crypto. The actor's
 * +0x14C position was verified against a live Farm actor and moves with him. */
static int dah_dev_npc_player_position(float *x, float *y, float *z)
{
    uint32_t system = MEM32(0x0025FCECu), player, character;
    if (!dah_dev_npc_guest_ptr(system)) return 0;
    player = MEM32(system + 0x38u);
    if (!dah_dev_npc_guest_ptr(player)) return 0;
    character = MEM32(player + 0x38u);
    if (!dah_dev_npc_guest_ptr(character)) return 0;
    if (MEM32(character) != 0x0022C9F8u) return 0;
    *x = MEMF(character + 0x14Cu) + 2.5f;
    *y = MEMF(character + 0x150u) + 2.5f;
    *z = MEMF(character + 0x154u);
    return isfinite(*x) && isfinite(*y) && isfinite(*z);
}

static void dah_dev_npc_poll(void)
{
    const char *save_dir;
    char command_path[1024], line[256], mode[16], extra;
    unsigned sequence, hash;
    float x, y, z;
    int auto_position;
    FILE *file;
    uint32_t saved_eax, saved_ebx, saved_ecx, saved_edx;
    uint32_t saved_esi, saved_edi, saved_ebp, saved_seh_ebp, saved_esp;
    unsigned saved_fp_top;
    double saved_fp_stack[8];
    RecompXmm saved_xmm[8];
    uint16_t saved_fp_control;
    int saved_fp_cmp;
    int from_console = g_dah_console_npc_hash != 0u;
    if (g_dah_dev_npc_active) return;
    if (from_console) {
        hash = g_dah_console_npc_hash;
        g_dah_console_npc_hash = 0;
        sequence = g_dah_dev_npc_sequence + 1;
        auto_position = 1;
        goto request_ready;
    }
    if (g_dah_dev_npc_count >= 6u || (g_dah_input_state_calls % 30u) != 0u ||
        !dah_dev_npc_private_session()) return;
    save_dir = getenv("DAH_SAVE_DIR");
    if (snprintf(command_path, sizeof(command_path), "%s\\npc-command.txt",
                 save_dir) >= (int)sizeof(command_path)) return;
    file = fopen(command_path, "rb");
    if (!file) return;
    if (!fgets(line, sizeof(line), file)) { fclose(file); return; }
    fclose(file);
    auto_position = sscanf(line, "%u %x %15s %c", &sequence, &hash,
                           mode, &extra) == 3 && !strcmp(mode, "auto");
    if (!auto_position &&
        sscanf(line, "%u %x %f %f %f %c", &sequence, &hash, &x, &y, &z,
               &extra) != 5) return;
    if (sequence <= g_dah_dev_npc_sequence) return;
request_ready:
    g_dah_dev_npc_sequence = sequence;
    if (!dah_dev_npc_hash_allowed(hash)) {
        fprintf(stderr, "[DAH-DEV-NPC] invalid hash seq=%u hash=%08X\n",
                sequence, hash);
        return;
    }
    if (auto_position && !dah_dev_npc_player_position(&x, &y, &z)) {
        fprintf(stderr, "[DAH-DEV-NPC] Crypto position unavailable seq=%u\n",
                sequence);
        if (from_console) dah_console_write("Spawn requires active on-foot gameplay with Crypto loaded.");
        return;
    }
    if (!isfinite(x) || !isfinite(y) ||
        !isfinite(z) || fabsf(x) > 100000.0f || fabsf(y) > 100000.0f ||
        fabsf(z) > 100000.0f) {
        fprintf(stderr, "[DAH-DEV-NPC] invalid position seq=%u hash=%08X\n",
                sequence, hash);
        return;
    }
    if (!MEM32(0x0025AB54u) || !MEM32(0x00286768u)) {
        fprintf(stderr, "[DAH-DEV-NPC] world unavailable seq=%u\n", sequence);
        if (from_console) dah_console_write("Spawn unavailable while a level is loading.");
        return;
    }
    saved_eax = g_eax; saved_ebx = g_ebx; saved_ecx = g_ecx;
    saved_edx = g_edx; saved_esi = g_esi; saved_edi = g_edi;
    saved_ebp = g_ebp; saved_seh_ebp = g_seh_ebp; saved_esp = g_esp;
    saved_fp_top = g_fp_top; saved_fp_cmp = g_fp_cmp;
    memcpy(saved_fp_stack, g_fp_stack, sizeof(saved_fp_stack));
    saved_xmm[0]=g_xmm0; saved_xmm[1]=g_xmm1; saved_xmm[2]=g_xmm2; saved_xmm[3]=g_xmm3;
    saved_xmm[4]=g_xmm4; saved_xmm[5]=g_xmm5; saved_xmm[6]=g_xmm6; saved_xmm[7]=g_xmm7;
    saved_fp_control=g_fp_control_word;
    g_dah_dev_npc_hash = hash;
    g_dah_dev_npc_actor = 0u;
    g_dah_dev_npc_result = 0;
    g_dah_dev_npc_active = 1;
    g_esp -= 12u;
    MEMF(g_esp) = x; MEMF(g_esp + 4u) = y; MEMF(g_esp + 8u) = z;
    g_edx = g_esp;
    g_ecx = hash;
    PUSH32(g_esp, 0x00000000u); sub_000891F0();
    g_dah_dev_npc_active = 0;
    if (g_dah_dev_npc_result == 1) {
        uint32_t actor = g_dah_dev_npc_actor;
        if (dah_dev_npc_guest_ptr(actor) &&
            MEM32(actor) == 0x00226C60u &&
            MEM32(actor + 0x14u) == 0x00226C44u &&
            MEM32(0x00226C4Cu) == 0x00016E30u) {
            uint32_t before = MEM32(actor + 0x98u);
            /* Retail world wrappers 0xAB170/0xAB4A0 perform this exact
             * interface call with arg 0 after the generic dispatcher when
             * activating an actor. The powerup wrapper above omits it. */
            g_ecx = actor + 0x14u;
            PUSH32(g_esp, 0u);
            PUSH32(g_esp, 0x000AB1FFu);
            sub_00016E30();
            fprintf(stderr,
                    "[DAH-DEV-NPC] activation actor=%08X model_before=%08X model_after=%08X\n",
                    actor, before, MEM32(actor + 0x98u));
            {
                uint32_t attachment = MEM32(actor + 0x98u);
                uint32_t entry;
                uint32_t alpha_before, alpha_after;
                if (!dah_dev_npc_guest_ptr(attachment) ||
                    MEM32(attachment) == 0u || MEM32(attachment) > 120u) {
                    g_dah_dev_npc_result = -2;
                } else {
                    entry = MEM32(attachment + 8u);
                    if (!dah_dev_npc_guest_ptr(entry)) {
                        g_dah_dev_npc_result = -4;
                    } else {
                        alpha_before = MEM32(entry + 0x0Cu);
                        /* Normal world wrappers start the model at alpha 0
                         * and later advance it to 1. The private one-shot
                         * wrapper has no update life cycle, so complete
                         * that same retail interface transition here. */
                        g_ecx = actor + 0x14u;
                        PUSH32(g_esp, 0x3F800000u);
                        PUSH32(g_esp, 0x000AB1FFu);
                        sub_00016E30();
                        alpha_after = MEM32(entry + 0x0Cu);
                        fprintf(stderr,
                                "[DAH-DEV-NPC] opacity actor=%08X before=%08X after=%08X\n",
                                actor, alpha_before, alpha_after);
                        if (alpha_after != 0x3F800000u)
                            g_dah_dev_npc_result = -5;
                    }
                }
            }
        } else {
            fprintf(stderr, "[DAH-DEV-NPC] activation rejected actor=%08X\n", actor);
            g_dah_dev_npc_result = -3;
        }
    }
    fprintf(stderr,
            "[DAH-DEV-NPC] seq=%u hash=%08X xyz=(%.2f,%.2f,%.2f) actor=%08X result=%d stack=%08X\n",
            sequence, hash, x, y, z, g_dah_dev_npc_actor,
            g_dah_dev_npc_result, g_esp);
    fflush(stderr);
    g_dah_dev_npc_count++;
    if (from_console) {
        if (g_dah_dev_npc_result == 1)
            dah_console_write("NPC spawned near Crypto (actor %08X).", g_dah_dev_npc_actor);
        else
            dah_console_write("NPC unavailable in this map, or constructor rejected it (result %d).", g_dah_dev_npc_result);
    }
    g_eax = saved_eax; g_ebx = saved_ebx; g_ecx = saved_ecx;
    g_edx = saved_edx; g_esi = saved_esi; g_edi = saved_edi;
    g_ebp = saved_ebp; g_seh_ebp = saved_seh_ebp; g_esp = saved_esp;
    g_fp_top = saved_fp_top; g_fp_cmp = saved_fp_cmp;
    memcpy(g_fp_stack, saved_fp_stack, sizeof(saved_fp_stack));
    g_xmm0=saved_xmm[0]; g_xmm1=saved_xmm[1]; g_xmm2=saved_xmm[2]; g_xmm3=saved_xmm[3];
    g_xmm4=saved_xmm[4]; g_xmm5=saved_xmm[5]; g_xmm6=saved_xmm[6]; g_xmm7=saved_xmm[7];
    g_fp_control_word=saved_fp_control;
}

#include "dah_console_level.h"

/* Every weapon.* progression key observed across the retail unlock bundles
 * in dah_console_level.h (UnlockSite, common_profile.lua 0x6ABAF), collected
 * here once so give_weapon/giveall_weapons don't hand-maintain two copies.
 * The retail equip name passed to SetWeapon is the same string with the
 * "weapon." prefix stripped -- confirmed for zapomatic (see history below);
 * assumed to hold for the rest by the same site_weapon.lua convention until
 * proven otherwise by an actual equip attempt. */
static const char *const dah_console_weapon_keys[] = {
    "weapon.cortex", "weapon.brainextractor", "weapon.zapomatic",
    "weapon.analprobe", "weapon.mattermove", "weapon.abducto",
    "weapon.holobob", "weapon.holobobhelper", "weapon.hypnoray",
    "weapon.deathray", "weapon.destructoray", "weapon.iondetonator",
    "weapon.sonicboom", "weapon.quantum", "weapon.brainray",
};
#define DAH_CONSOLE_WEAPON_COUNT (sizeof(dah_console_weapon_keys)/sizeof(dah_console_weapon_keys[0]))

/* Grant an on-foot weapon through the retail progression store, then equip
 * it through the same native manager path site_weapon.lua's
 * SetWeaponByNameAlien uses (playerCharacter.SetWeapon), so a script can
 * fire it immediately rather than needing to navigate the in-game weapon-
 * select wheel. Originally hardcoded to zapomatic only; generalized to any
 * known weapon key so every weapon can be exercised for crash-hunting, not
 * just the one the retail Farm tutorial happens to grant first. */
static int dah_console_give_weapon(const char *alias)
{
    struct dah_console_guest_registers saved;
    uint32_t store, scratch, system, player, character, manager;
    float x, y, z;
    int granted, equipped = 0;
    const char *key = NULL, *name = NULL;
    size_t i;
    if (alias) {
        for (i = 0; i < DAH_CONSOLE_WEAPON_COUNT; ++i) {
            const char *candidate = dah_console_weapon_keys[i] + 7; /* skip "weapon." */
            if (!_stricmp(alias, candidate)) { key = dah_console_weapon_keys[i]; name = candidate; break; }
        }
    }
    if (!key) {
        dah_console_write("Unknown weapon. Use help or giveall_weapons for the full list.");
        return -1;
    }
    if (dah_console_level_is_busy()) {
        dah_console_write("Wait for the level to finish loading before granting a weapon.");
        return 0;
    }
    if (!dah_dev_npc_player_position(&x, &y, &z)) {
        dah_console_write("Crypto must be active in a level before granting a weapon.");
        return 0;
    }
    if (!dah_console_level_store_ready(&store)) {
        dah_console_write("The original progression store is not ready.");
        return 0;
    }
    system = MEM32(0x0025FCECu);
    player = dah_dev_npc_guest_ptr(system) ? MEM32(system + 0x38u) : 0u;
    character = dah_dev_npc_guest_ptr(player) ? MEM32(player + 0x38u) : 0u;
    manager = dah_dev_npc_guest_ptr(character) ? MEM32(character + 0x138u) : 0u;
    fprintf(stderr,
            "[DAH-CONSOLE-WEAPON-STATE] phase=before character=%08X manager=%08X "
            "slots=%08X,%08X,%08X active=%08X list=%08X,%08X\n",
            character, manager,
            dah_dev_npc_guest_ptr(manager) ? MEM32(manager + 0x4Cu) : 0u,
            dah_dev_npc_guest_ptr(manager) ? MEM32(manager + 0x50u) : 0u,
            dah_dev_npc_guest_ptr(manager) ? MEM32(manager + 0x54u) : 0u,
            dah_dev_npc_guest_ptr(manager) ? MEM32(manager + 0x58u) : 0u,
            dah_dev_npc_guest_ptr(manager) ? MEM32(manager + 0x10u) : 0u,
            dah_dev_npc_guest_ptr(manager) ? MEM32(manager + 0x14u) : 0u);
    dah_console_level_save(&saved);
    g_esp -= 0x200u;
    scratch = g_esp;
    granted = dah_console_level_add_key(store, scratch, key);
    /* site_weapon.lua's SetWeaponByNameAlien(name) ultimately calls
     * playerCharacter.SetWeapon with the name, which selects the matching
     * retail weapon object from this manager's already loaded object list.
     * Use that same native manager path here; adding the profile key alone
     * only makes the weapon eligible for normal menu cycling. */
    if (granted && dah_dev_npc_guest_ptr(manager) && strlen(name) < 60u) {
        uint32_t call_stack = g_esp;
        memcpy(XBOX_PTR(scratch), name, strlen(name) + 1u);
        g_ecx = manager;
        PUSH32(g_esp, 0u);       /* silent/force flag */
        PUSH32(g_esp, 0u);       /* alien primary weapon slot */
        PUSH32(g_esp, scratch);  /* retail weapon name */
        PUSH32(g_esp, 0u);       /* synthetic return address */
        sub_0009DF10();
        equipped = g_esp == call_stack && (g_eax & 255u) != 0u &&
                   MEM32(manager + 0x4Cu) != 0u &&
                   MEM32(manager + 0x58u) == MEM32(manager + 0x4Cu);
    }
    fprintf(stderr, "[DAH-CONSOLE-WEAPON] alias=%s key=%s granted=%d equipped=%d stack=%08X\n",
            name, key, granted, equipped, g_esp);
    fflush(stderr);
    dah_console_level_restore(&saved);
    fprintf(stderr,
            "[DAH-CONSOLE-WEAPON-STATE] phase=after character=%08X manager=%08X "
            "slots=%08X,%08X,%08X active=%08X list=%08X,%08X\n",
            character, manager,
            dah_dev_npc_guest_ptr(manager) ? MEM32(manager + 0x4Cu) : 0u,
            dah_dev_npc_guest_ptr(manager) ? MEM32(manager + 0x50u) : 0u,
            dah_dev_npc_guest_ptr(manager) ? MEM32(manager + 0x54u) : 0u,
            dah_dev_npc_guest_ptr(manager) ? MEM32(manager + 0x58u) : 0u,
            dah_dev_npc_guest_ptr(manager) ? MEM32(manager + 0x10u) : 0u,
            dah_dev_npc_guest_ptr(manager) ? MEM32(manager + 0x14u) : 0u);
    if (equipped)
        dah_console_write("%s equipped. Use the right trigger to fire.", name);
    else if (granted)
        dah_console_write("%s unlocked, but the original weapon manager could not equip it.", name);
    else
        dah_console_write("The original weapon manager rejected the %s grant.", name);
    return granted;
}

/* Unlock every known weapon key at once (progression store only -- this
 * never force-equips anything, unlike give_weapon). Intended for systematic
 * crash-hunting: once every weapon is eligible, the retail weapon-select
 * wheel can cycle through all of them via its own normal input path, or
 * give_weapon <name> can equip each one directly to test firing/alt-fire
 * without navigating that UI blind under scripted input. */
static int dah_console_giveall_weapons(void)
{
    struct dah_console_guest_registers saved;
    uint32_t store, scratch;
    float x, y, z;
    size_t i, granted = 0;
    if (dah_console_level_is_busy()) {
        dah_console_write("Wait for the level to finish loading before granting weapons.");
        return 0;
    }
    if (!dah_dev_npc_player_position(&x, &y, &z)) {
        dah_console_write("Crypto must be active in a level before granting weapons.");
        return 0;
    }
    if (!dah_console_level_store_ready(&store)) {
        dah_console_write("The original progression store is not ready.");
        return 0;
    }
    dah_console_level_save(&saved);
    g_esp -= 0x200u;
    scratch = g_esp;
    for (i = 0; i < DAH_CONSOLE_WEAPON_COUNT; ++i)
        if (dah_console_level_add_key(store, scratch, dah_console_weapon_keys[i])) ++granted;
    dah_console_level_restore(&saved);
    fprintf(stderr, "[DAH-CONSOLE-WEAPON] giveall granted=%zu/%zu\n", granted, DAH_CONSOLE_WEAPON_COUNT);
    fflush(stderr);
    dah_console_write("Unlocked %u/%u weapons in the progression store. "
                       "Use give_weapon <name> to equip one, or cycle weapons normally.",
                       (unsigned)granted, (unsigned)DAH_CONSOLE_WEAPON_COUNT);
    return granted == DAH_CONSOLE_WEAPON_COUNT;
}

/* Opt-in, internal-only stand-in for a human typing "load_level <alias>" into
 * the developer console. Bounded runs have no keyboard/window focus, so this
 * retries the exact same original-game load_level path on a throttled cadence
 * until dah_console_load_level accepts it or the attempt budget is spent.
 * Never active outside DAH_INTERNAL_RUN; a normal or hidden-scripted launch
 * never touches this. */
static void dah_console_autoload_poll(void)
{
    static int state = -1; /* -1=unchecked, 0=armed, 1=finished */
    static unsigned ticks, attempts;
    const char *target;
    if (state < 0) {
        target = dah_input_is_internal() ? getenv("DAH_CONSOLE_AUTOLOAD_LEVEL") : NULL;
        state = (target && *target) ? 0 : 1;
    }
    if (state != 0) return;
    if (++ticks % 30u) return; /* about twice a second at the internal 30 Hz frame rate */
    target = getenv("DAH_CONSOLE_AUTOLOAD_LEVEL");
    if (++attempts > 400u) {
        dah_console_write("Automatic load_level %s timed out waiting for a ready state.", target);
        state = 1;
        return;
    }
    if (dah_console_load_level(target) > 0) state = 1;
}

/* Opt-in, internal-only automation for systematic weapon crash-hunting:
 * once gameplay is idle and Crypto is active, optionally unlock every
 * weapon (DAH_CONSOLE_AUTO_GIVEALL_WEAPONS=1) and/or equip one specific
 * weapon by name (DAH_CONSOLE_AUTO_EQUIP_WEAPON=<name>) -- the same two
 * console commands a human would type, just without needing keyboard focus
 * on a hidden window. Equipping one weapon per run (rather than trying to
 * hold all of them at once, which the retail manager was never designed
 * for) keeps a crash attributable to a single, known weapon. */
static void dah_console_autoweapons_poll(void)
{
    static int state = -1; /* -1=unchecked, 0=armed, 1=finished */
    static unsigned ticks, attempts;
    if (state < 0) {
        const char *giveall = dah_input_is_internal() ? getenv("DAH_CONSOLE_AUTO_GIVEALL_WEAPONS") : NULL;
        const char *equip = dah_input_is_internal() ? getenv("DAH_CONSOLE_AUTO_EQUIP_WEAPON") : NULL;
        state = ((giveall && !strcmp(giveall, "1")) || (equip && *equip)) ? 0 : 1;
    }
    if (state != 0) return;
    if (++ticks % 30u) return;
    if (++attempts > 400u) {
        dah_console_write("Automatic weapon grant timed out waiting for a ready state.");
        state = 1;
        return;
    }
    if (dah_console_level_is_busy()) return;
    {
        const char *giveall = getenv("DAH_CONSOLE_AUTO_GIVEALL_WEAPONS");
        const char *equip = getenv("DAH_CONSOLE_AUTO_EQUIP_WEAPON");
        float x, y, z;
        if (!dah_dev_npc_player_position(&x, &y, &z)) return; /* not in gameplay yet */
        if (giveall && !strcmp(giveall, "1")) dah_console_giveall_weapons();
        if (equip && *equip) dah_console_give_weapon(equip);
        state = 1;
    }
}

/* These requests execute once at the retail main-loop frame boundary.
 * The Windows message thread only queues plain text. */
static void dah_console_poll(void)
{
    static const char *const names[] = { "cow", "farmer", "cop", "soldier", "scientist", "gman" };
    static const uint32_t hashes[] = { 0x5AE49481u, 0xE8337A18u, 0x93E45661u, 0x8FA4309Fu, 0x9AC0FD1Eu, 0x41348393u };
    char line[192], command[32], arg[64], extra;
    unsigned i;
    int tokens;
    float x, y, z;
    dah_console_level_poll_switch();
    dah_console_autoload_poll();
    dah_console_autoweapons_poll();
    if (!dah_console_take_command(line, sizeof(line))) return;
    tokens = sscanf(line, "%31s %63s %c", command, arg, &extra);
    if (tokens == 1 && !_stricmp(command, "capture")) {
        if (dah_request_frame_capture()) dah_console_write("Queued the next two game frames; capture paths will appear in the game log.");
        else dah_console_write("Frame capture is unavailable or the capture limit has been reached.");
        return;
    }
    if (tokens == 1 && !_stricmp(command, "status")) {
        if (dah_console_level_is_busy())
            dah_console_write("The original game is starting or loading a level.");
        else if (dah_dev_npc_player_position(&x, &y, &z))
            dah_console_write("Crypto at %.1f, %.1f, %.1f. Original gameplay is active.", x-2.5f, y-2.5f, z);
        else dah_console_write("Frontend or level transition; Crypto is not currently available.");
        return;
    }
    if (tokens == 2 && !_stricmp(command, "load_level")) {
        if (!dah_console_load_level(arg)) dah_console_write("Level load is not ready; wait for the current transition to finish.");
        return;
    }
    if (tokens == 2 && !_stricmp(command, "give_weapon")) {
        dah_console_give_weapon(arg);
        return;
    }
    if (tokens == 1 && !_stricmp(command, "giveall_weapons")) {
        dah_console_giveall_weapons();
        return;
    }
    if (tokens == 2 && !_stricmp(command, "spawn")) {
        const char *name = !_strnicmp(arg, "npc_", 4) ? arg+4 : arg;
        if (dah_console_level_is_busy()) {
            dah_console_write("Wait for the level to finish loading before spawning an NPC.");
            return;
        }
        for (i = 0; i < sizeof(names)/sizeof(names[0]); ++i)
            if (!_stricmp(name, names[i])) { g_dah_console_npc_hash = hashes[i]; break; }
        if (!g_dah_console_npc_hash) dah_console_write("Unknown NPC. Type help for the six supported names.");
        return;
    }
    dah_console_write("Unknown command or arguments. Type help for supported commands.");
}

/* Input can stop polling while the original driver switches worlds. Pump
 * commands from the main-loop boundary so capture/status and the pending
 * ReadyToSwitch/Switch handoff continue independently of active input UI.
 * Original API calls may alter guest registers; leave the interrupted retail
 * main-loop context intact on every normal return. */
void dah_console_poll_game_thread(void)
{
    static RECOMP_TLS int polling;
    struct dah_console_guest_registers saved;
    if (polling) return;
    polling = 1;
    dah_console_level_save(&saved);
    dah_console_poll();
    dah_console_level_restore(&saved);
    polling = 0;
}

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

/* Explicit background input test permission is independent of internal-run
 * rendering/audio/loader settings. A normal launch, or a script path alone,
 * never gains background input. Settings are fixed at process launch. */
static int dah_input_is_hidden_scripted(void)
{
    static int enabled = -1;
    if (enabled < 0) {
        const char *hidden = getenv("DAH_TEST_WINDOW_HIDDEN");
        const char *script = getenv("DAH_INPUT_SCRIPT");
        enabled = hidden && strcmp(hidden, "1") == 0 && script && *script;
    }
    return enabled;
}

static int dah_input_uses_neutral_pad(void)
{
    return dah_input_is_internal() || dah_input_is_hidden_scripted();
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
    if (dah_input_uses_neutral_pad() || dah_console_is_open() || !dah_host_has_input_focus())
        return 0;
    if (dah_console_key_blocked(virtual_key)) return 0;
    return (GetAsyncKeyState(virtual_key) & 0x8000) != 0;
}

#include "dah_scripted_input.h"

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
        g_dah_autostart_enabled = v ? (atoi(v) != 0 ? 1 : 0) : 0;
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
        g_dah_autostart2_enabled = v ? (atoi(v) != 0 ? 1 : 0) : 0;
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
        g_dah_autoa_enabled = v ? (atoi(v) != 0 ? 1 : 0) : 0;
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
    if (dah_key_down('P')) {
        key_mask |= 1u << 11;
        state->Gamepad.wButtons |= XBOX_GAMEPAD_START;
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
    dah_apply_scripted_input(state);
}

/* Opt-in, read-only Rockwell pose trace at the actual controller bridge.
 * The guest pointer chain and actor XYZ were established by the retail NPC
 * probe. No guest state is changed by this diagnostic. */
static int dah_rockwell_trace_range(uint32_t address, uint32_t bytes)
{
    return address >= 0x00010000u && bytes <= 0x08000000u &&
           address <= 0x08000000u - bytes;
}

static void dah_trace_rockwell_player_camera(const XBOX_INPUT_STATE *state)
{
    static int enabled = -1;
    static unsigned samples, last_transition;
    static int last_lx, last_ly, last_rx, last_ry;
    uint32_t system, player = 0, actor = 0, camera, node = 0, parent = 0, world;
    uint32_t vtable = 0, zbits = 0;
    float px = 0.0f, py = 0.0f, pz = 0.0f;
    float view_x = 0.0f, view_y = 0.0f, view_z = 0.0f;
    float view_fwd_x = 0.0f, view_fwd_y = 0.0f, view_fwd_z = 0.0f;
    float node_x = 0.0f, node_y = 0.0f, node_z = 0.0f;
    float quat_w = 0.0f, quat_x = 0.0f, quat_y = 0.0f, quat_z = 0.0f;
    float node_world_x = 0.0f, node_world_y = 0.0f, node_world_z = 0.0f;
    float parent_x = 0.0f, parent_y = 0.0f, parent_z = 0.0f;
    float world_time = 0.0f;
    unsigned tick = g_dah_input_state_calls;
    int lx = state->Gamepad.sThumbLX, ly = state->Gamepad.sThumbLY;
    int rx = state->Gamepad.sThumbRX, ry = state->Gamepad.sThumbRY;
    int changed, active, recent;

    if (enabled < 0) {
        const char *flag = getenv("DAH_ROCKWELL_PLAYER_TRACE");
        enabled = flag ? strcmp(flag, "0") != 0 : !dah_input_is_internal();
    }
    /* Rockwell assets start near poll 3000; AUTOINTRO changes focus and
     * starts approach_ticketseller between polls 3900 and 4200. */
    if (!enabled || samples >= 256u || tick < 1000u || tick > 30000u)
        return;
    changed = lx != last_lx || ly != last_ly ||
              rx != last_rx || ry != last_ry;
    active = lx || ly || rx || ry;
    if (changed) last_transition = tick;
    last_lx = lx; last_ly = ly; last_rx = rx; last_ry = ry;
    recent = tick >= last_transition &&
             (tick - last_transition == 30u ||
              tick - last_transition == 90u ||
              tick - last_transition == 180u);
    if (!changed && !recent && tick % 300u != 0u &&
        !(active && tick % 30u == 0u)) return;

    system = MEM32(0x0025FCECu);
    if (dah_rockwell_trace_range(system, 0x3Cu)) {
        player = MEM32(system + 0x38u);
        if (dah_rockwell_trace_range(player, 0x3Cu))
            actor = MEM32(player + 0x38u);
    }
    if (dah_rockwell_trace_range(actor, 0x158u)) {
        vtable = MEM32(actor);
        px = MEMF(actor + 0x14Cu);
        py = MEMF(actor + 0x150u);
        pz = MEMF(actor + 0x154u);
        zbits = MEM32(actor + 0x154u);
    }
    camera = MEM32(0x00250E60u);
    if (dah_rockwell_trace_range(camera, 0xF0u)) {
        view_x = MEMF(camera + 0x80u);
        view_y = MEMF(camera + 0x84u);
        view_z = MEMF(camera + 0x88u);
        view_fwd_x = MEMF(camera + 0x70u);
        view_fwd_y = MEMF(camera + 0x74u);
        view_fwd_z = MEMF(camera + 0x78u);
        node = MEM32(camera + 0xECu);
    }
    if (dah_rockwell_trace_range(node, 0x8Cu)) {
        parent = MEM32(node + 8u);
        node_x = MEMF(node + 0x20u);
        node_y = MEMF(node + 0x24u);
        node_z = MEMF(node + 0x28u);
        quat_w = MEMF(node + 0x40u);
        quat_x = MEMF(node + 0x44u);
        quat_y = MEMF(node + 0x48u);
        quat_z = MEMF(node + 0x4Cu);
        node_world_x = MEMF(node + 0x80u);
        node_world_y = MEMF(node + 0x84u);
        node_world_z = MEMF(node + 0x88u);
    }
    if (dah_rockwell_trace_range(parent, 0x2Cu)) {
        parent_x = MEMF(parent + 0x20u);
        parent_y = MEMF(parent + 0x24u);
        parent_z = MEMF(parent + 0x28u);
    }
    world = MEM32(0x00286768u);
    if (dah_rockwell_trace_range(world, 0x10u))
        world_time = MEMF(world + 0x0Cu);
    fprintf(stderr,
            "[DAH-ROCKWELL-POSE] tick=%u sticks=%d,%d,%d,%d A=%u B=%u "
            "system=%08X player=%08X actor=%08X vt=%08X "
            "xyz=%.6g,%.6g,%.6g zbits=%08X "
            "camera=%08X node=%08X parent=%08X "
            "view_t=%.6g,%.6g,%.6g "
            "view_fwd=%.6g,%.6g,%.6g "
            "node_local=%.6g,%.6g,%.6g "
            "quat=%.6g,%.6g,%.6g,%.6g "
            "node_world=%.6g,%.6g,%.6g "
            "parent_local=%.6g,%.6g,%.6g time=%.6g\n",
            tick, lx, ly, rx, ry,
            (unsigned)state->Gamepad.bAnalogButtons[XBOX_BUTTON_A],
            (unsigned)state->Gamepad.bAnalogButtons[XBOX_BUTTON_B],
            system, player, actor, vtable, (double)px, (double)py,
            (double)pz, zbits, camera, node, parent,
            (double)view_x, (double)view_y, (double)view_z,
            (double)view_fwd_x, (double)view_fwd_y, (double)view_fwd_z,
            (double)node_x, (double)node_y, (double)node_z,
            (double)quat_w, (double)quat_x, (double)quat_y, (double)quat_z,
            (double)node_world_x, (double)node_world_y, (double)node_world_z,
            (double)parent_x, (double)parent_y, (double)parent_z,
            (double)world_time);
    if (active) {
        uint32_t chain = node;
        unsigned depth;
        for (depth = 0; depth < 6u &&
                        dah_rockwell_trace_range(chain, 0x90u); ++depth) {
            fprintf(stderr,
                    "[DAH-ROCKWELL-CAMERA-CHAIN] tick=%u depth=%u node=%08X "
                    "parent=%08X flags=%08X "
                    "local_pos=%.6g,%.6g,%.6g scale=%.6g "
                    "quat=%.6g,%.6g,%.6g,%.6g "
                    "row0=%.6g,%.6g,%.6g row1=%.6g,%.6g,%.6g "
                    "row2=%.6g,%.6g,%.6g world_pos=%.6g,%.6g,%.6g\n",
                    tick, depth, chain, MEM32(chain + 8u), MEM32(chain + 0x2Cu),
                    (double)MEMF(chain + 0x20u), (double)MEMF(chain + 0x24u),
                    (double)MEMF(chain + 0x28u), (double)MEMF(chain + 0x30u),
                    (double)MEMF(chain + 0x40u), (double)MEMF(chain + 0x44u),
                    (double)MEMF(chain + 0x48u), (double)MEMF(chain + 0x4Cu),
                    (double)MEMF(chain + 0x50u), (double)MEMF(chain + 0x54u),
                    (double)MEMF(chain + 0x58u), (double)MEMF(chain + 0x60u),
                    (double)MEMF(chain + 0x64u), (double)MEMF(chain + 0x68u),
                    (double)MEMF(chain + 0x70u), (double)MEMF(chain + 0x74u),
                    (double)MEMF(chain + 0x78u), (double)MEMF(chain + 0x80u),
                    (double)MEMF(chain + 0x84u), (double)MEMF(chain + 0x88u));
            chain = MEM32(chain + 8u);
        }
    }
    ++samples;
}

/* Read-only camera-struct memory diff dump: assembly-agnostic way to
 * find which bytes in the global camera object (0x00250E60) respond to
 * controller Y input, without needing a disassembler. Never changes guest
 * state; just periodically hex-dumps a window of camera memory so two
 * snapshots (e.g. stick-up vs stick-down) can be diffed by hand afterward.
 * It defaults on for an ordinary interactive build while this controller bug
 * is under investigation, remains off for internal/headless tests, and can be
 * explicitly overridden with DAH_CAMERA_MEMDIFF_TRACE=0 or =1. */
static void dah_camera_memdiff_poll(const XBOX_INPUT_STATE *state)
{
    static int enabled = -1;
    static unsigned ticks;
    uint32_t camera;
    if (enabled < 0) {
        const char *v = getenv("DAH_CAMERA_MEMDIFF_TRACE");
        /* Internal mode deliberately replaces the physical pad with
         * neutral/scripted input, so its default is quiet. */
        enabled = v ? (strcmp(v, "0") != 0) : !dah_input_is_internal();
    }
    if (!enabled) return;
    if (++ticks % 30u) return;
    camera = MEM32(0x00250E60u);
    if (camera < 0x10000u || camera > 0x08000000u - 0x200u) return;
    {
        unsigned i;
        fprintf(stderr,
                "[DAH-CAMERA-MEMDIFF] tick=%u camera=%08X sticks=%d,%d,%d,%d bytes=",
                g_dah_input_state_calls, camera,
                state ? (int)state->Gamepad.sThumbLX : 0,
                state ? (int)state->Gamepad.sThumbLY : 0,
                state ? (int)state->Gamepad.sThumbRX : 0,
                state ? (int)state->Gamepad.sThumbRY : 0);
        for (i = 0; i < 0x200u; i += 4u) {
            fprintf(stderr, "%08X", MEM32(camera + i));
        }
        fprintf(stderr, "\n");
        fflush(stderr);
    }
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
        result = dah_input_uses_neutral_pad() ? ERROR_SUCCESS :
                 xbox_InputGetState(port, &state);
        if (result != ERROR_SUCCESS) {
            /* A neutral logical controller keeps retail's frontend alive on
             * keyboard-only systems; the overlay below adds PC controls. */
            memset(&state, 0, sizeof(state));
            result = ERROR_SUCCESS;
        }
        dah_apply_keyboard_overlay(&state);
        /* Reflect the horizontal axis without turning an exact neutral value
         * into -1.  The previous one's-complement mapping made idle input
         * look active and could trigger movement diagnostics during startup. */
        state.Gamepad.sThumbLX = state.Gamepad.sThumbLX == (SHORT)-32768 ?
            (SHORT)32767 : (SHORT)-state.Gamepad.sThumbLX;
        dah_trace_input_lx = state.Gamepad.sThumbLX;
        dah_trace_input_ly = state.Gamepad.sThumbLY;
        dah_trace_input_rx = state.Gamepad.sThumbRX;
        dah_trace_input_ry = state.Gamepad.sThumbRY;
        if (dah_console_is_open() || (!dah_input_uses_neutral_pad() && !dah_host_has_input_focus())) {
            memset(&state, 0, sizeof(state));
            if (!dah_input_uses_neutral_pad() && !(g_dah_console_muted_ports & (1u << port))) {
                XBOX_VIBRATION silent = {0};
                xbox_InputSetState(port, &silent);
                g_dah_console_muted_ports |= (1u << port);
            }
        } else g_dah_console_muted_ports &= ~(1u << port);
        dah_trace_rockwell_player_camera(&state);
        /* furonlog records the final logical pad delivered to retail code.
         * State changes are lossless; a heartbeat every 300 polls proves a
         * held/neutral controller without flooding one row per poll. */
        {
            static XBOX_INPUT_STATE last_logged;
            static int have_last_logged;
            int changed = !have_last_logged || memcmp(&last_logged, &state, sizeof(state)) != 0;
            if (changed || (g_dah_input_state_calls % 300u) == 0u) {
                fprintf(stderr,
                    "[FURON-INPUT] poll=%u changed=%d packet=%u buttons=%04X "
                    "analog=A:%u,B:%u,X:%u,Y:%u,BLACK:%u,WHITE:%u,LT:%u,RT:%u "
                    "sticks=%d,%d,%d,%d console=%d focus=%d\n",
                    g_dah_input_state_calls, changed, state.dwPacketNumber,
                    state.Gamepad.wButtons,
                    (unsigned)state.Gamepad.bAnalogButtons[XBOX_BUTTON_A],
                    (unsigned)state.Gamepad.bAnalogButtons[XBOX_BUTTON_B],
                    (unsigned)state.Gamepad.bAnalogButtons[XBOX_BUTTON_X],
                    (unsigned)state.Gamepad.bAnalogButtons[XBOX_BUTTON_Y],
                    (unsigned)state.Gamepad.bAnalogButtons[XBOX_BUTTON_BLACK],
                    (unsigned)state.Gamepad.bAnalogButtons[XBOX_BUTTON_WHITE],
                    (unsigned)state.Gamepad.bAnalogButtons[XBOX_BUTTON_LTRIGGER],
                    (unsigned)state.Gamepad.bAnalogButtons[XBOX_BUTTON_RTRIGGER],
                    (int)state.Gamepad.sThumbLX, (int)state.Gamepad.sThumbLY,
                    (int)state.Gamepad.sThumbRX, (int)state.Gamepad.sThumbRY,
                    dah_console_is_open(), dah_host_has_input_focus());
                fflush(stderr);
                last_logged = state;
                have_last_logged = 1;
            }
        }
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
    dah_camera_memdiff_poll(&state);
    dah_dev_npc_poll();
}

void dah_xinput_set_state_bridge(void)
{
    uint32_t handle = MEM32(g_esp + 4u);
    uint32_t vibration = MEM32(g_esp + 8u);
    uint32_t port;
    XBOX_VIBRATION state = {0};
    DWORD result = ERROR_DEVICE_NOT_CONNECTED;

    if (dah_input_handle_port(handle, &port) && vibration != 0u) {
        if (dah_input_uses_neutral_pad()) {
            result = ERROR_SUCCESS;
        } else {
            if (!dah_console_is_open() && dah_host_has_input_focus()) {
                state.wLeftMotorSpeed = MEM16(vibration);
                state.wRightMotorSpeed = MEM16(vibration + 2u);
            }
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
extern void sub_000F5B70(void);
extern void sub_00011F20(void);
extern void sub_0003A810(void);
extern void sub_00056830(void);
extern void sub_0007F130(void);
extern void sub_000A2B70(void);
extern void sub_000C0330(void);
extern void sub_000E1240(void);
extern void sub_0012B690(void);
extern void sub_001376B0(void);
extern void sub_0007F370(void);
extern void sub_000816A0(void);
extern void sub_00087F30(void);
extern void sub_001890A0(void);
extern void sub_000121B0(void);
extern void sub_00136CF0(void);
extern void sub_0008DC70(void);
extern void sub_000435D0(void);
extern void sub_0007E330(void);
extern void sub_000122E0(void);
extern void sub_0007E4A0(void);
extern void sub_000804D0(void);
extern void sub_000806B0(void);
extern void sub_00080700(void);
extern void sub_0007E530(void);
extern void sub_00011FA0(void);
extern void sub_00011FD0(void);
extern void sub_000861B0(void);
extern void sub_000818D0(void);
extern void sub_00082290(void);
extern void sub_000822B0(void);
extern void sub_000822D0(void);
extern void sub_000822F0(void);
extern void sub_000E0C30(void);
extern void sub_000586A0(void);
extern void sub_001351B0(void);
extern void sub_001351A0(void);
extern void sub_001377C0(void);
extern void sub_001377D0(void);
extern void sub_001377E0(void);
extern void sub_00135630(void);
extern void sub_00135660(void);
extern void sub_00137850(void);
extern void sub_001359F0(void);
extern void sub_00135A20(void);
extern void sub_00135A30(void);
extern void sub_00135A40(void);
extern void sub_00135A50(void);
extern void sub_00135A60(void);
extern void sub_00135A70(void);
extern void sub_00135A80(void);
extern void sub_00080510(void);
extern void sub_00081890(void);
extern void sub_000818A0(void);
extern void sub_00012120(void);
extern void sub_00012130(void);
extern void sub_00081870(void);
extern void sub_00012150(void);
extern void sub_00081880(void);
extern void sub_00012170(void);
extern void sub_00012180(void);
extern void sub_00012190(void);
extern void sub_000121A0(void);
extern void sub_000121D0(void);
extern void sub_000121C0(void);
extern void sub_000121E0(void);
extern void sub_000121F0(void);
extern void sub_00012200(void);
extern void sub_00012210(void);
extern void sub_00012220(void);
extern void sub_00012230(void);
extern void sub_00012250(void);
extern void sub_00012240(void);
extern void sub_00012260(void);
extern void sub_00012270(void);
extern void sub_0007D430(void);
extern void sub_0005E640(void);
extern void sub_00081790(void);
extern void sub_00043600(void);
extern void sub_001376F0(void);
extern void sub_0012B6A0(void);
extern void sub_00137810(void);
extern void sub_000A2E20(void);
extern void sub_00097BF0(void);
extern void sub_000A34F0(void);
extern void sub_00124F40(void);
extern void sub_0010D0D0(void);
extern void sub_0007EFF0(void);
extern void sub_0009B7A0(void);
extern void sub_00123F70(void);
extern void sub_00101E60(void);
extern void sub_00061D40(void);
extern void sub_00055D20(void);
extern void sub_0010EAB0(void);
extern void sub_0010EAC0(void);
extern void sub_0010EAD0(void);
extern void sub_0010EAE0(void);
extern void sub_0001AF50(void);
extern void sub_000214A0(void);
extern void sub_0009ECF0(void);
extern void sub_0010E110(void);
extern void sub_0001AF80(void);
extern void sub_0012B7E0(void);
extern void sub_00137820(void);
extern void sub_00135520(void);
extern void sub_0007F3B0(void);
extern void sub_00087F60(void);
extern void sub_00011B10(void);
extern void sub_00011FE0(void);
extern void sub_00018B40(void);
extern void sub_00088B40(void);
extern void sub_0008C1E0(void);
extern void sub_00011270(void);
extern void sub_00017470(void);
extern void sub_00018A10(void);
extern void sub_000174F0(void);
extern void sub_00018AE0(void);
extern void sub_000112E0(void);
extern void sub_00017B60(void);
extern void sub_00019D40(void);
extern void sub_0008C370(void);
extern void sub_0008C1D0(void);
extern void sub_00088A20(void);
extern void sub_00088D40(void);
extern void sub_000122D0(void);
extern void sub_00043610(void);
extern void sub_000A54A0(void);
extern void sub_000A2D70(void);
extern void sub_00043370(void);
extern void sub_00042C70(void);
extern void sub_000A4EE0(void);
extern void sub_000A2D50(void);
extern void sub_0016EDC0(void);
extern void sub_0016E6A0(void);
extern void sub_00172A50(void);
extern void sub_00186130(void);
extern void sub_00191F80(void);
extern void sub_00195BB0(void);
extern void sub_00199720(void);
extern void sub_001A6080(void);
extern void sub_001A6EE0(void);
extern void sub_001A72B0(void);
extern void sub_001A72A0(void);
extern void sub_00194190(void);
extern void sub_000A1E80(void);
extern void sub_0011A110(void);
extern void sub_0015D220(void);
extern void sub_000E6770(void);
extern void sub_000E8270(void);
extern void sub_000FFC60(void);
extern void sub_00100AC0(void);
extern void sub_00100B20(void);
extern void sub_000E0C20(void);
extern void sub_000139C0(void);
extern void sub_0003C650(void);
extern void sub_00012A70(void);
extern void sub_00013AB0(void);
extern void sub_00016E30(void);
extern void sub_00033D20(void);
extern void sub_0003B750(void);
extern void sub_0004E090(void);
extern void sub_001444E0(void);
extern void sub_0015D0C0(void);
extern void sub_00163630(void);
extern void sub_00013EA0(void);
extern void sub_000152D0(void);
extern void sub_00033350(void);
extern void sub_00015570(void);
extern void sub_00023470(void);
extern void sub_00025D50(void);
extern void sub_00028560(void);
extern void sub_00029480(void);
extern void sub_00059260(void);
extern void sub_000592E0(void);
extern void sub_0005F580(void);
extern void sub_00098EC0(void);
extern void sub_000A2B80(void);
extern void sub_000AC2E0(void);
extern void sub_000E7DC0(void);
extern void sub_000F59E0(void);
extern void sub_000FC300(void);
extern void sub_0011DDB0(void);
extern void sub_00128A60(void);
extern void sub_00136100(void);
extern void sub_000299D0(void);
extern void sub_0009A970(void);
extern void sub_0009F790(void);
extern void sub_000ABDE0(void);
extern void sub_000AB9C0(void);
extern void sub_0011FA30(void);
extern void sub_0013FF59(void);
extern void sub_00143689(void);
extern void sub_001EF162(void);
extern void sub_001EE1F9(void);
extern void sub_0008A3F0(void);
extern void sub_0008BC00(void);
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

/* The matching XAPI getter must read the same per-thread last-error value.
 * The guest KPCR/TEB path is not yet backed by the host runtime. */
uint32_t dah_xapi_get_last_error(void)
{
    return g_dah_last_error;
}

/* Retail vtable thunk 0x18AC0, absent from direct-call disassembly.
 * The final jmp is a tail call: its callee consumes the original caller's
 * return address. Do not push another return address here. */
static void dah_retail_18ac0_vtable_tail(void)
{
    g_ecx -= 0x228u;
    PUSH32(g_esp, 0x00018ACBu);
    sub_000112E0();
    g_edx = MEM32(g_eax);
    g_ecx = g_eax;
    RECOMP_ITAIL(MEM32(g_edx));
}

/* Retail 0x12EE90-0x12EF07, called during world return. It copies a
 * three-float vector when +0x58 is absent, then optionally updates members.
 * The original method has two stack arguments and ends with ret 8. */
static void dah_retail_12ee90(void)
{
    PUSH32(g_esp, g_esi);
    g_esi = g_ecx;
    g_eax = MEM32(g_esi + 0x58u);
    if (g_eax != 0u) {
        uint32_t saved_esp = g_esp;
        g_edx = MEM32(g_esp + 8u);
        g_ecx = g_eax;
        g_eax = MEM32(g_ecx);
        PUSH32(g_esp, g_edx);
        {
            uint32_t target = MEM32(g_eax + 0x18u);
            PUSH32(g_esp, 0x0012EEA6u);
            #define eax g_eax
            RECOMP_ICALL_SAFE(target, saved_esp);
            #undef eax
        }
        POP32(g_esp, g_esi);
        g_esp += 12u;
        return;
    }

    g_eax = MEM32(g_esp + 8u);
    g_ecx = MEM32(g_eax);
    MEM32(g_esi + 0x60u) = g_ecx;
    g_edx = MEM32(g_eax + 4u);
    MEM32(g_esi + 0x64u) = g_edx;
    g_eax = MEM32(g_eax + 8u);
    MEM32(g_esi + 0x68u) = g_eax;
    if (MEM8(g_esp + 0xCu) != 0u) {
        g_ecx = MEM32(g_esi + 0x8Cu);
        PUSH32(g_esp, g_edi);
        g_edi = MEM32(g_esi + 0x88u);
        g_edx = g_edi;
        g_eax = g_edx + g_ecx * 4u;
        while (g_edi != g_eax) {
            g_ecx = MEM32(g_edi);
            PUSH32(g_esp, 0x278BECu);
            PUSH32(g_esp, 0x0012EEECu);
            sub_0012CF70();
            g_ecx = MEM32(g_esi + 0x8Cu);
            g_edx = MEM32(g_esi + 0x88u);
            g_edi += 4u;
            g_eax = g_edx + g_ecx * 4u;
        }
        POP32(g_esp, g_edi);
    }
    POP32(g_esp, g_esi);
    g_esp += 12u;
}

/* Retail 0x184430-0x184438: an interior vtable tail jump. Preserve the
 * original caller's return address and let the target consume its args. */
static void dah_retail_184430(void)
{
    g_ecx = MEM32(g_ecx + 0x20u);
    g_eax = MEM32(g_ecx);
    RECOMP_ITAIL(MEM32(g_eax + 0x28u));
}

/* Exact retail 0x234E0-0x23522 vtable method reached by spawned cop.
 * Its two jumps are tail calls and must use the original caller's frame. */
static void dah_retail_234e0(void)
{
    g_edx = MEM32(g_esp + 4u);
    g_eax = MEM32(g_edx);
    g_eax -= 5u;
    if (g_eax == 0u) {
        PUSH32(g_esp, 0x0002351Fu);
        sub_000232D0();
        g_esp += 12u;
        return;
    }
    g_eax -= 2u;
    if (g_eax != 0u) {
        MEM32(g_esp + 4u) = g_edx;
        sub_00022270();
        return;
    }
    g_eax = MEM32(g_ecx + 0xC8u);
    if (g_eax == 0u) {
        g_esp += 12u;
        return;
    }
    g_ecx = g_eax;
    g_edx = MEM32(g_ecx);
    MEM32(g_esp + 8u) = 0u;
    MEM32(g_esp + 4u) = 0u;
    RECOMP_ITAIL(MEM32(g_edx + 0x4Cu));
}

/* Exact retail 0x81910-0x8193D position getter. A spawned cop uses this
 * through Crypto's component vtable while tracking his world position. */
static void dah_retail_81910(void)
{
    uint32_t saved_esp, target;
    g_eax = MEM32(g_ecx + 4u);
    g_esp -= 12u;
    g_ecx += 4u;
    g_edx = g_esp;
    saved_esp = g_esp;
    PUSH32(g_esp, g_edx);
    target = MEM32(g_eax + 0x18u);
    PUSH32(g_esp, 0x00081920u);
    #define eax g_eax
    RECOMP_ICALL_SAFE(target, saved_esp);
    #undef eax
    g_fp_top = (g_fp_top + 7u) & 7u;
    g_fp_stack[g_fp_top] = MEMF(g_esp);
    g_eax = MEM32(g_esp + 0x10u);
    g_ecx = MEM32(g_esp + 4u);
    MEMF(g_eax) = (float)g_fp_stack[g_fp_top];
    g_fp_top = (g_fp_top + 1u) & 7u;
    g_edx = MEM32(g_esp + 8u);
    MEM32(g_eax + 4u) = g_ecx;
    MEM32(g_eax + 8u) = g_edx;
    g_esp += 20u; /* local 12 bytes and original ret 4 */
}

/* Exact retail 0x18DE20-0x18DEA0 object factory, reached only after the
 * spawned cop began running its behavior. The XBE's SEH frame is preserved. */
static void dah_retail_18de20(void)
{
    uint32_t saved_esp = g_esp, target;
    PUSH32(g_esp, 0xFFFFFFFFu);
    PUSH32(g_esp, 0x001ADD5Bu);
    g_eax = MEM32(0u);
    PUSH32(g_esp, g_eax);
    MEM32(0u) = g_esp;
    PUSH32(g_esp, g_ecx);
    g_ecx = MEM32(0x00270A80u);
    g_eax = MEM32(g_ecx);
    PUSH32(g_esp, g_esi);
    PUSH32(g_esp, 0x1Au);
    PUSH32(g_esp, 0x100u);
    target = MEM32(g_eax + 0x10u);
    PUSH32(g_esp, 0x0018DE49u);
    #define eax g_eax
    RECOMP_ICALL_SAFE(target, saved_esp);
    #undef eax
    g_esi = g_eax;
    MEM16(g_esi + 4u) = 0x100u;
    MEM32(g_esp + 4u) = g_esi;
    g_ecx = MEM32(g_esp + 0x24u);
    g_edx = MEM32(g_esp + 0x1Cu);
    g_eax = MEM32(g_esp + 0x18u);
    PUSH32(g_esp, g_ecx);
    PUSH32(g_esp, g_edx);
    PUSH32(g_esp, g_eax);
    g_ecx = g_esi;
    MEM32(g_esp + 0x1Cu) = 0u;
    PUSH32(g_esp, 0x0018DE73u);
    sub_001586B0();
    g_ecx = MEM32(g_esp + 8u);
    MEM32(g_esi) = 0x0023E418u;
    MEM32(g_esi + 0xF0u) = 0u;
    g_eax = g_esi;
    POP32(g_esp, g_esi);
    MEM32(0u) = g_ecx;
    g_esp += 20u; /* SEH frame 16 bytes and ret */
}

/* Retail 0x18FD10 is an interior entry of generated sub_0018FD00. That
 * function's sole prefix subtracts eight from ECX before the exact suffix. */
static void dah_retail_18fd10(void)
{
    g_ecx += 8u;
    sub_0018FD00();
}

/* Exact retail 0xA1DF0-0xA1E0A: virtual cleanup, component cleanup,
 * then a tail jump to 0x97C50 using the original caller's return address. */
static void dah_retail_a1df0(void)
{
    PUSH32(g_esp, g_esi);
    g_esi = g_ecx;
    g_eax = MEM32(g_esi);
    {
        uint32_t saved_esp = g_esp;
        uint32_t target = MEM32(g_eax + 0x60u);
        PUSH32(g_esp, 0u);
        PUSH32(g_esp, 0x000A1DFAu);
        #define eax g_eax
        RECOMP_ICALL_SAFE(target, saved_esp);
        #undef eax
    }
    g_ecx = g_esi + 0x4Cu;
    PUSH32(g_esp, 0x000A1E02u);
    sub_0009C190();
    g_ecx = g_esi;
    POP32(g_esp, g_esi);
    sub_00097C50();
}

/* Retail 0xA7B60-0xA7B9C: attach the owner component to one primary and
 * four referenced components. All three callees are existing generated code. */
static void dah_retail_a7b60(void)
{
    PUSH32(g_esp, g_ebx);
    PUSH32(g_esp, g_esi);
    PUSH32(g_esp, g_edi);
    g_esi = g_ecx;
    PUSH32(g_esp, 0x000A7B6Au);
    sub_00097C10();
    g_eax = MEM32(g_esi + 0x2Cu) + 0x68u;
    PUSH32(g_esp, g_eax);
    g_ecx = g_esi + 0x44u;
    PUSH32(g_esp, 0x000A7B79u);
    sub_0009B6E0();
    g_edi = g_esi + 0x718u;
    g_ebx = 4u;
    do {
        g_ecx = MEM32(g_esi + 0x2Cu) + 0x68u;
        PUSH32(g_esp, g_ecx);
        g_ecx = MEM32(g_edi);
        PUSH32(g_esp, 0x000A7B92u);
        sub_0009B6E0();
        g_edi += 4u;
        --g_ebx;
    } while (g_ebx != 0u);
    POP32(g_esp, g_edi);
    POP32(g_esp, g_esi);
    POP32(g_esp, g_ebx);
    g_esp += 4u;
}

/* Retail 0xA1DD0-0xA1DE1: initialize base, then tail-call the component
 * method with the original return address still on the guest stack. */
static void dah_retail_a1dd0(void)
{
    PUSH32(g_esp, g_esi);
    g_esi = g_ecx;
    PUSH32(g_esp, 0x000A1DD8u);
    sub_00097C10();
    g_ecx = g_esi + 0x4Cu;
    POP32(g_esp, g_esi);
    sub_0009B7C0();
}

/* Exact original XBE code at 0x26710: test the first argument, then
 * optionally call 0x3A3E0 with ECX+0x48. The retail method ends in ret 8. */
static void dah_retail_26710(void)
{
    uint32_t argument = MEM32(g_esp + 4u);
    if (MEM32(argument) == 0u) {
        g_ecx += 0x48u;
        PUSH32(g_esp, 0x00026721u);
        sub_0003A3E0();
    }
    g_esp += 12u;
}

/* Exact original XBE code at 0xA12C0: a two-load virtual accessor. */
static void dah_retail_a12c0(void)
{
    g_eax = MEM32(g_ecx + 0xD4u);
    g_eax = MEM32(g_eax);
    g_esp += 4u;
}

/* Original XBE 0xA3750-0xA37FD: actor/resource lookup virtual method.
 * Preserve the exact branch order, indirect calls, and stdcall ret 8. */
#define eax g_eax
static void dah_retail_a3750(void)
{
    uint32_t saved_esp = g_esp;
    g_eax = MEM32(g_esp + 8u);
    MEM32(g_eax) = 0u;
    g_edx = MEM32(g_ecx);
    {
        uint32_t target = MEM32(g_edx + 0xA4u);
        PUSH32(g_esp, 0x000A3762u);
        RECOMP_ICALL_SAFE(target, saved_esp);
    }
    if (g_eax != 0xD08C8E0Bu && g_eax != 0x12067E39u) {
        g_eax = UINT32_MAX;
        g_esp += 12u;
        return;
    }
    PUSH32(g_esp, 0x6A1D032Du);
    PUSH32(g_esp, 0x000A377Au);
    sub_00089840();
    g_ecx = g_eax;
    PUSH32(g_esp, 0x000A3781u);
    sub_0008AD10();
    if (!g_eax) {
        g_eax = UINT32_MAX;
        g_esp += 12u;
        return;
    }
    g_ecx = MEM32(g_esp + 4u);
    g_eax = MEM32(g_ecx);
    PUSH32(g_esp, g_esi);
    saved_esp = g_esp;
    {
        uint32_t target = MEM32(g_eax + 0x10u);
        PUSH32(g_esp, 0x000A3795u);
        RECOMP_ICALL_SAFE(target, saved_esp);
    }
    g_esi = g_eax;
    if (!g_esi) goto fail;
    g_edx = MEM32(g_esi);
    saved_esp = g_esp;
    PUSH32(g_esp, 0x54473A6Eu);
    g_ecx = g_esi;
    {
        uint32_t target = MEM32(g_edx + 0x1Cu);
        PUSH32(g_esp, 0x000A37A7u);
        RECOMP_ICALL_SAFE(target, saved_esp);
    }
    if (!(g_eax & 0xFFu)) goto fail;
    g_eax = MEM32(g_esi + 0xBCu);
    g_ecx = g_esi + 0xBCu;
    saved_esp = g_esp;
    {
        uint32_t target = MEM32(g_eax + 0x48u);
        PUSH32(g_esp, 0x000A37BAu);
        RECOMP_ICALL_SAFE(target, saved_esp);
    }
    if (g_eax & 0xFFu) goto fail;
    if (!MEM8(g_esi + 0x3D1u)) goto fail;
    g_ecx = MEM32(g_esi + 0x1Cu);
    if (!MEM8(g_ecx + 0x519u)) goto fail;
    g_edx = MEM32(g_esi);
    g_ecx = g_esi;
    saved_esp = g_esp;
    {
        uint32_t target = MEM32(g_edx + 0xDCu);
        PUSH32(g_esp, 0x000A37DFu);
        RECOMP_ICALL_SAFE(target, saved_esp);
    }
    if (g_eax & 0xFFu) {
        g_eax = MEM32(g_esi + 0x10Cu);
        g_ecx = MEM32(g_eax + 0x14u);
        if (g_ecx) goto fail;
    }
    g_eax = MEM32(g_esi + 0x24u);
    POP32(g_esp, g_esi);
    g_esp += 12u;
    return;
fail:
    g_eax = UINT32_MAX;
    POP32(g_esp, g_esi);
    g_esp += 12u;
}

#undef eax

/* Exact retail 0x21020-0x2102E: call the generated component method with
 * its original argument and return address, then consume one caller argument. */
static void dah_retail_21020(void)
{
    g_ecx = MEM32(g_esp + 4u);
    PUSH32(g_esp, 5u);
    PUSH32(g_esp, 0x0002102Bu);
    sub_000417A0();
    g_esp += 8u;
}

/* Exact retail 0xB6DA0-0xB6DA6: constant virtual return value. */
static void dah_retail_b6da0(void)
{
    g_eax = 0x16u;
    g_esp += 4u;
}

/* Exact XBE 0x850B0-0x850FC and 0x9D100-0x9D22A; 23 and 99
 * instructions respectively were byte-checked against the retail image. */
#define eax g_eax
#define ecx g_ecx
#define edx g_edx
#define esp g_esp
#define ebx g_ebx
#define esi g_esi
#define edi g_edi

/**
 * sub_000850B0
 * Original: 0x000850B0 - 0x000850FC (76 bytes, 23 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
static void dah_retail_850b0(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_000850B0: ;
    eax = MEM32(esp + 4);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0x9E7EDF34u) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0x9E7EDF34u (32-bit) */
    PUSH32(esp, esi);
    esi = ecx;
    if (CMP_NE(_fa, _fb)) goto loc_000850CF; /* jne: not equal / not zero */

loc_000850BE: ;
    ecx = MEM32(esi + 0x34);
    PUSH32(esp, 0x334);
    PUSH32(esp, 0x000850CBu); sub_000817E0(); /* call 0x000817E0 */

loc_000850CB: ;
    POP32(esp, esi);
    esp += 12; return; /* ret 8 */

loc_000850CF: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0x37EC8C25) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0x37EC8C25 (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_000850F8; /* je: equal / zero */

loc_000850D6: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0xBDF7C019u) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0xBDF7C019u (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_000850F8; /* jne: not equal / not zero */

loc_000850DD: ;
    ecx = MEM32(esi + 0x34);
    PUSH32(esp, 0x000850E5u); sub_000817D0(); /* call 0x000817D0 */

loc_000850E5: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0x258) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0x258 (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_000850F8; /* jne: not equal / not zero */

loc_000850EC: ;
    PUSH32(esp, 0x9D77F44Cu);
    ecx = esi;
    PUSH32(esp, 0x000850F8u); sub_00084CB0(); /* call 0x00084CB0 */

loc_000850F8: ;
    POP32(esp, esi);
    esp += 12; return; /* ret 8 */

}


/**
 * sub_0009D100
 * Original: 0x0009D100 - 0x0009D22A (298 bytes, 99 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
static void dah_retail_9d100(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    #define fp_push(v) do { double _fp_value = (v); \
        g_fp_top = (g_fp_top + 7u) & 7u; \
        g_fp_stack[g_fp_top] = _fp_value; } while (0)
    #define fp_pop() (g_fp_top = (g_fp_top + 1u) & 7u)
    #define fp_top() g_fp_stack[g_fp_top]
    #define fp_st(i) g_fp_stack[(g_fp_top + (i)) & 7u]
    #define fp_st1() fp_st(1)
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_0009D100: ;
    esp = esp - 0xC;
    PUSH32(esp, ebp);
    PUSH32(esp, esi);
    esi = ecx;
    eax = MEM32(esi + 0x44);
    eax = eax - 0;
    ebp = MEM32(esi + 0x10);
    if ((eax == 0)) goto loc_0009D204; /* je: equal / zero */

loc_0009D116: ;
    eax = eax - 1;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fas = (int32_t)(int32_t)_fa; /* dec flags snapshot */
    if ((_fa == 0)) goto loc_0009D140; /* je: equal / zero */

loc_0009D119: ;
    eax = eax - 1;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fas = (int32_t)(int32_t)_fa; /* dec flags snapshot */
    if ((_fa != 0)) goto loc_0009D222; /* jne: not equal / not zero */

loc_0009D120: ;
    fp_push(MEMF(esi + 0x18)); /* fld float */
    g_fp_cmp = RECOMP_FCMP(fp_top(), MEMF(ebp + 0x48)); fp_pop(); /* fcomp dword ptr [ebp + 0x48] */
    eax = (eax & 0xFFFF0000u) | (uint32_t)(uint16_t)(((g_fp_top & 7u) << 11) | (g_fp_cmp == 2 ? 0x4500u : g_fp_cmp < 0 ? 0x0100u : g_fp_cmp > 0 ? 0x0000u : 0x4000u)); /* fnstsw ax <- fpu status */
    _fa = (uint32_t)(HI8(eax)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test HI8(eax), 1 (8-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_0009D222; /* jne: not equal / not zero */

loc_0009D131: ;
    MEM32(esi + 0x44) = 0;
    POP32(esp, esi);
    POP32(esp, ebp);
    esp = esp + 0xC;
    esp += 8; return; /* ret 4 */

loc_0009D140: ;
    SET_LO8(eax, MEM8(esi + 0x34));
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0009D1EC; /* je: equal / zero */

loc_0009D14B: ;
    fp_push(MEMF(esi + 0x18)); /* fld float */
    g_fp_cmp = RECOMP_FCMP(fp_top(), MEMF(0x225C20)); fp_pop(); /* fcomp dword ptr [0x225c20] */
    eax = (eax & 0xFFFF0000u) | (uint32_t)(uint16_t)(((g_fp_top & 7u) << 11) | (g_fp_cmp == 2 ? 0x4500u : g_fp_cmp < 0 ? 0x0100u : g_fp_cmp > 0 ? 0x0000u : 0x4000u)); /* fnstsw ax <- fpu status */
    _fa = (uint32_t)(HI8(eax)) & 0xFFu; _fb = (uint32_t)(0x41) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test HI8(eax), 0x41 (8-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_0009D1EC; /* jne: not equal / not zero */

loc_0009D15F: ;
    eax = MEM32(esi + 0x20);
    ecx = MEM32(eax + 0x138);
    PUSH32(esp, ebx);
    PUSH32(esp, edi);
    PUSH32(esp, 0x0009D16Fu); sub_000221A0(); /* call 0x000221A0 */

loc_0009D16F: ;
    ecx = MEM32(esi + 0x20);
    ebx = MEM32(esi + 0x10);
    edx = esp + 0x10;
    ecx = ecx + 0x18;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, edx);
    edi = eax;
    MEM32(esp + 0x14) = 0;
    MEM32(esp + 0x18) = 0;
    MEM32(esp + 0x1C) = 0;
    eax = MEM32(ecx);
    PUSH32(esp, esi);
    { uint32_t _icall_target = MEM32(eax); PUSH32(esp, 0x0009D19Cu); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_0009D19C: ;
    fp_push(MEMF(esp + 0x28)); /* fld float */
    fp_top() = fp_top() * MEMF(ebx + 0x6C); /* fmul dword ptr [ebx + 0x6c] */
    PUSH32(esp, eax);
    PUSH32(esp, ecx);
    ebx = ebx + 0x58;
    MEMF(esp) = (float)fp_top(); fp_pop(); /* fstp */
    PUSH32(esp, ebx);
    ecx = edi;
    PUSH32(esp, 0x0009D1B3u); sub_000A6F60(); /* call 0x000A6F60 */

loc_0009D1B3: ;
    edx = eax;
    ecx = edi;
    PUSH32(esp, 0x0009D1BCu); sub_0007A130(); /* call 0x0007A130 */

loc_0009D1BC: ;
    SET_LO8(eax, MEM8(0x2867AC));
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    POP32(esp, edi);
    POP32(esp, ebx);
    if (TEST_NZ(_fa, _fb)) goto loc_0009D222; /* jne: not equal / not zero */

loc_0009D1C7: ;
    fp_push(MEMF(esp + 0x18)); /* fld float */
    PUSH32(esp, 0x3F800000);
    fp_top() = fp_top() * MEMF(ebp + 0x40); /* fmul dword ptr [ebp + 0x40] */
    PUSH32(esp, ecx);
    fp_top() = MEMF(esi + 0x18) - fp_top(); /* fsubr dword ptr [esi + 0x18] */
    MEMF(esp) = (float)fp_top(); fp_pop(); /* fstp */
    PUSH32(esp, 0);
    PUSH32(esp, 0x0009D1E1u); sub_00017EA0(); /* call 0x00017EA0 */

loc_0009D1E1: ;
    MEMF(esi + 0x18) = (float)fp_top(); fp_pop(); /* fstp */
    POP32(esp, esi);
    POP32(esp, ebp);
    esp = esp + 0xC;
    esp += 8; return; /* ret 4 */

loc_0009D1EC: ;
    edx = MEM32(esi);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 1);
    ecx = esi;
    { uint32_t _icall_target = MEM32(edx + 0x60); PUSH32(esp, 0x0009D1F5u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_0009D1F5: ;
    MEM32(esi + 0x44) = 2;
    POP32(esp, esi);
    POP32(esp, ebp);
    esp = esp + 0xC;
    esp += 8; return; /* ret 4 */

loc_0009D204: ;
    SET_LO8(eax, MEM8(esi + 0x34));
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0009D222; /* je: equal / zero */

loc_0009D20B: ;
    fp_push(MEMF(esi + 0x18)); /* fld float */
    g_fp_cmp = RECOMP_FCMP(fp_top(), MEMF(0x225C20)); fp_pop(); /* fcomp dword ptr [0x225c20] */
    eax = (eax & 0xFFFF0000u) | (uint32_t)(uint16_t)(((g_fp_top & 7u) << 11) | (g_fp_cmp == 2 ? 0x4500u : g_fp_cmp < 0 ? 0x0100u : g_fp_cmp > 0 ? 0x0000u : 0x4000u)); /* fnstsw ax <- fpu status */
    _fa = (uint32_t)(HI8(eax)) & 0xFFu; _fb = (uint32_t)(0x41) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test HI8(eax), 0x41 (8-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_0009D222; /* jne: not equal / not zero */

loc_0009D21B: ;
    MEM32(esi + 0x44) = 1;

loc_0009D222: ;
    POP32(esp, esi);
    POP32(esp, ebp);
    esp = esp + 0xC;
    esp += 8; return; /* ret 4 */

    #undef fp_push
    #undef fp_pop
    #undef fp_top
    #undef fp_st
    #undef fp_st1
}


#undef eax
#undef ecx
#undef edx
#undef esp
#undef ebx
#undef esi
#undef edi

/* Retail XBE 0x0012B560..0x0012B5D4. This is a real callback table entry.
 * The adjacent 0x12B345 address is an interior epilogue of 0x12B2F0 and
 * must not be registered as a standalone callback.
 *
 * Dependencies already present in generated code: sub_00133E80,
 * sub_0012AC30. Virtual calls use the original vtable slots and ret sites.
 */
static void dah_retail_cop_icall(uint32_t target, uint32_t ret, uint32_t saved_esp)
{
    PUSH32(g_esp, ret);
#define eax g_eax
    RECOMP_ICALL_SAFE(target, saved_esp);
#undef eax
}

static void dah_retail_12b560(void)
{
    uint32_t saved_esp, target;

    g_eax = MEM32(g_esp + 4u);                 /* mov eax,[esp+4] */
    PUSH32(g_esp, g_ebp);
    g_ebp = MEM32(g_esp + 0x14u);             /* fourth stack argument */
    PUSH32(g_esp, g_esi);
    g_esi = MEM32(g_eax + 4u);
    PUSH32(g_esp, g_edi);
    g_ecx = g_ebp;
    PUSH32(g_esp, 0x0012B575u);
    sub_00133E80();
    g_edi = g_eax;
    if (!g_esi || !g_edi) goto done;

    g_edx = MEM32(g_esi);
    g_ecx = g_esi;
    saved_esp = g_esp;
    target = MEM32(g_edx + 0x48u);
    dah_retail_cop_icall(target, 0x0012B586u, saved_esp);
    if (!g_eax) goto done;

    g_eax = MEM32(g_edi);
    g_ecx = g_edi;
    saved_esp = g_esp;
    target = MEM32(g_eax + 0x48u);
    dah_retail_cop_icall(target, 0x0012B591u, saved_esp);
    if (!g_eax) goto done;

    g_edx = MEM32(g_esi);
    PUSH32(g_esp, g_ebx);
    g_ebx = MEM32(g_esp + 0x18u);            /* second stack argument */
    PUSH32(g_esp, 3u);
    PUSH32(g_esp, g_ebx);
    g_ecx = g_esi;
    saved_esp = g_esp + 8u;
    target = MEM32(g_edx + 0x38u);
    dah_retail_cop_icall(target, 0x0012B5A4u, saved_esp);

    g_eax = MEM32(g_edi);
    PUSH32(g_esp, 3u);
    PUSH32(g_esp, g_ebx);
    g_ecx = g_edi;
    saved_esp = g_esp + 8u;
    target = MEM32(g_eax + 0x38u);
    dah_retail_cop_icall(target, 0x0012B5AEu, saved_esp);

    g_edx = MEM32(g_esp + 0x24u);            /* fifth stack argument */
    g_ebx = MEM32(0x00286888u);
    g_ecx = g_ebp;
    PUSH32(g_esp, 0x0012B5BFu);
    sub_0012AC30();
    MEM32(g_ebx + 0x10u) = g_eax;
    g_ecx = MEM32(0x00286888u);
    g_edx = MEM32(g_ecx);
    PUSH32(g_esp, g_edi);
    PUSH32(g_esp, g_esi);
    saved_esp = g_esp + 8u;
    target = MEM32(g_edx + 0x20u);
    dah_retail_cop_icall(target, 0x0012B5CFu, saved_esp);
    POP32(g_esp, g_ebx);

done:
    POP32(g_esp, g_edi);
    POP32(g_esp, g_esi);
    POP32(g_esp, g_ebp);
    g_esp += 4u;                              /* original ret, no arguments */
}

/* Exact retail XBE callbacks 0x133E90..0x133EF0 and 0x133EF0..0x133F50.
 * Both are real function-table entries at 0x22A7FC/0x22A800 and
 * 0x237D34/0x237D38, observed in Rockwell after spawning a cop.
 * Keep in Cwork until coordinated D install and live retest. */
extern void sub_0012D350(void);

static void dah_npc_component_icall(uint32_t target, uint32_t ret, uint32_t saved_esp)
{
    PUSH32(g_esp, ret);
#define eax g_eax
    RECOMP_ICALL_SAFE(target, saved_esp);
#undef eax
}

static void dah_npc_component_pair(uint32_t command, uint32_t ret_base, uint32_t callee_bytes)
{
    uint32_t target;
    PUSH32(g_esp, g_ebx);
    PUSH32(g_esp, g_esi);
    g_ebx = g_ecx;
    g_ecx = MEM32(g_esp + 0xCu);
    PUSH32(g_esp, g_edi);
    PUSH32(g_esp, ret_base + 0xEu);
    sub_0012D350();
    g_ecx = MEM32(g_esp + 0x14u);
    g_esi = g_eax;
    PUSH32(g_esp, ret_base + 0x19u);
    sub_0012D350();
    g_edi = g_eax;
    if (g_esi == 0u || g_edi == 0u) goto done;

    g_eax = MEM32(g_esi);
    g_ecx = g_esi;
    target = MEM32(g_eax + 0x48u);
    dah_npc_component_icall(target, ret_base + 0x2Au, g_esp);
    if (g_eax == 0u) goto done;

    g_edx = MEM32(g_edi);
    g_ecx = g_edi;
    target = MEM32(g_edx + 0x48u);
    dah_npc_component_icall(target, ret_base + 0x35u, g_esp);
    if (g_eax == 0u) goto done;

    g_eax = MEM32(g_esi);
    PUSH32(g_esp, 3u);
    PUSH32(g_esp, command);
    g_ecx = g_esi;
    target = MEM32(g_eax + 0x38u);
    dah_npc_component_icall(target, ret_base + 0x44u, g_esp + 8u);

    g_edx = MEM32(g_edi);
    PUSH32(g_esp, 3u);
    PUSH32(g_esp, command);
    g_ecx = g_edi;
    target = MEM32(g_edx + 0x38u);
    dah_npc_component_icall(target, ret_base + 0x4Fu, g_esp + 8u);

    g_eax = MEM32(g_ebx - 8u);
    g_ecx = g_ebx - 8u;
    PUSH32(g_esp, g_edi);
    PUSH32(g_esp, g_esi);
    target = MEM32(g_eax + 0x20u);
    dah_npc_component_icall(target, ret_base + 0x5Au, g_esp + 8u);

done:
    POP32(g_esp, g_edi);
    POP32(g_esp, g_esi);
    POP32(g_esp, g_ebx);
    g_esp += 4u + callee_bytes;
}

static void dah_retail_133e90(void)
{
    dah_npc_component_pair(0xFFFFFFFFu, 0x00133E90u, 12u);
}

static void dah_retail_133ef0(void)
{
    dah_npc_component_pair(0u, 0x00133EF0u, 8u);
}

/* Exact retail XBE 0x18DA20..0x18DA48. Observed Rockwell cop runtime
 * callback through the original table at 0x23E360. Cwork preparation only. */
extern void sub_0018D760(void);

static void dah_retail_18da20(void)
{
    uint32_t target;
    PUSH32(g_esp, g_esi);
    g_esi = g_ecx;
    PUSH32(g_esp, 0x0018DA28u);
    sub_0018D760();
    if (MEM8(g_esp + 8u) & 1u) {
        g_edx = MEM16(g_esi + 4u);
        g_ecx = MEM32(0x00270A80u);
        g_eax = MEM32(g_ecx);
        PUSH32(g_esp, 0x22u);
        PUSH32(g_esp, g_edx);
        PUSH32(g_esp, g_esi);
        target = MEM32(g_eax + 0x14u);
        {
            uint32_t saved_esp = g_esp + 12u;
            PUSH32(g_esp, 0x0018DA42u);
#define eax g_eax
            RECOMP_ICALL_SAFE(target, saved_esp);
#undef eax
        }
    }
    g_eax = g_esi;
    POP32(g_esp, g_esi);
    g_esp += 8u; /* RET 4 */
}

/* The retail XBE's 0x0006FC30..0x0006FCA3 switch-used objective callback.
 * It is the 0x0022BA94 vtable's event handler. All three event paths and
 * the default delegation retain the original guest stack and return sites.
 */
static void dah_retail_6fc30(void)
{
    g_eax = MEM32(g_esp + 4u);
    PUSH32(g_esp, g_esi);
    g_esi = g_ecx;

    if (g_eax == 0x67EA54C9u) {
        g_edx = MEM32(g_esp + 0xCu);
        g_ecx = MEM32(g_esi + 0x50u);
        PUSH32(g_esp, g_edx);
        PUSH32(g_esp, 0x0006FC91u);
        sub_00139520();
        g_edx = 0u;
        g_ecx = g_eax;
        PUSH32(g_esp, 0x0006FC9Au);
        sub_000D54A0();
        MEM32(g_esi + 0x64u) = g_eax;
        g_eax = 0u;
        POP32(g_esp, g_esi);
        g_esp += 12u;                     /* ret 8 */
        return;
    }

    if (g_eax == 0x776AB225u) {
        g_ecx = MEM32(g_esi + 0x50u);
        PUSH32(g_esp, g_ebx);
        g_ebx = MEM32(g_esp + 0x10u);    /* second event parameter */
        PUSH32(g_esp, g_edi);
        PUSH32(g_esp, g_ebx);
        g_edi = g_esi + 0x68u;
        PUSH32(g_esp, 0x0006FC68u);
        sub_00139520();
        PUSH32(g_esp, g_eax);
        g_ecx = g_edi;
        PUSH32(g_esp, 0x0006FC70u);
        sub_0006E240();
        g_ecx = MEM32(g_esi + 0x50u);
        g_ebx++;
        PUSH32(g_esp, g_ebx);
        PUSH32(g_esp, 0x0006FC7Au);
        sub_001394F0();
        MEM32(g_edi) = g_eax;
        POP32(g_esp, g_edi);
        POP32(g_esp, g_ebx);
        g_eax = 0u;
        POP32(g_esp, g_esi);
        g_esp += 12u;                     /* ret 8 */
        return;
    }

    g_ecx = MEM32(g_esp + 0xCu);        /* second event parameter */
    PUSH32(g_esp, g_ecx);
    PUSH32(g_esp, g_eax);
    g_ecx = g_esi;
    PUSH32(g_esp, 0x0006FC52u);
    sub_0006F5E0();
    POP32(g_esp, g_esi);
    g_esp += 12u;                         /* ret 8 */
}

/* Exact retail XBE 0x00085720..0x0008574A, vtable slot 0x0022DF2C.
 * First new unresolved callback after cop spawn in Farm PID 27120.
 * Prepared in Cwork; install after that process has stopped. */
extern void sub_000825A0(void);

static void dah_retail_85720(void)
{
    PUSH32(g_esp, g_esi);
    g_esi = g_ecx;
    g_eax = MEM32(g_esi + 4u);
    g_ecx = MEM32(g_eax);
    g_ecx = MEM32(g_ecx + 0x12Cu);
    PUSH32(g_esp, 0x0022DF1Cu);
    PUSH32(g_esp, 0x00085738u);
    sub_000825A0();
    g_eax = MEM32(0x00286768u);
    g_edx = MEM32(g_esi + 4u);
    g_ecx = MEM32(g_eax + 0xCu);
    MEM32(g_edx + 0x20u) = g_ecx;
    POP32(g_esp, g_esi);
    g_esp += 8u; /* RET 4 */
}

/* Retail XBE 0x0004A460..0x0004A47B (27 bytes, 8 instructions) and
 * 0x00015AB0..0x00015AE0 (48 bytes, 14 instructions). These omitted
 * virtual type queries return a boolean in AL, retaining EAX's upper
 * 24 bits from the requested type hash and consuming one argument.
 * The instruction bytes are checked by verify-area42-type-callbacks.py.
 */
static void dah_retail_4a460(void)
{
    g_eax = MEM32(g_esp + 4u);
    if (g_eax == 0x6FC7A9F5u || g_eax == 0xA955731Bu)
        g_eax = (g_eax & 0xFFFFFF00u) | 1u;
    else
        g_eax &= 0xFFFFFF00u;
    g_esp += 8u; /* RET 4 */
}

static void dah_retail_15ab0(void)
{
    g_eax = MEM32(g_esp + 4u);
    if (g_eax == 0x177F1145u || g_eax == 0xB405C7B6u ||
        g_eax == 0x883240FCu || g_eax == 0x38082939u ||
        g_eax == 0xA75FFAEBu)
        g_eax = (g_eax & 0xFFFFFF00u) | 1u;
    else
        g_eax &= 0xFFFFFF00u;
    g_esp += 8u; /* RET 4 */
}

/* Retail DSOUND stream callback 0x001F2178..0x001F2200.
 * Vtable 0x239530 + 0x18, called by 0x1F3471 at return 0x1F34CA.
 * Every original instruction is checked by prepare-audio-stream-callback.py.
 * This services real packet/voice lifecycle operations; no stop is fabricated.
 */
extern void sub_001F17AD(void);
extern void sub_001F1FA4(void);
extern void sub_001F2094(void);
extern void sub_001F1991(void);
extern void sub_001F35AE(void);

static void dah_retail_1f2178(void)
{
    const uint32_t caller_frame = g_ebp;
    PUSH32(g_esp, g_esi);
    g_esi = g_ecx;
    PUSH32(g_esp, g_edi);
    g_edi = g_esi + 0x68u;
    PUSH32(g_esp, 3u);
    g_ecx = g_edi;
    PUSH32(g_esp, 0x001F2188u);
    sub_001F17AD();
    if (g_eax != 0u) {
        g_eax = MEM32(g_edi);
        MEM8(g_eax + 0x3Fu) = 0x80u;
        g_eax = g_esi + 0x12u;
        if (MEM16(g_eax) & 0x1000u) {
            MEM16(g_eax) &= 0xEFFFu;
            g_ecx = (g_ecx & 0xFFFF0000u) | MEM16(g_eax);
            g_ecx |= 0x2000u;
            MEM16(g_eax) = (uint16_t)g_ecx;
        }
        PUSH32(g_esp, 1u);
        g_ecx = g_esi;
        g_ebp = caller_frame;
        PUSH32(g_esp, 0x001F21B5u);
        sub_001F1FA4();
        goto done;
    }

    g_eax = (g_eax & 0xFFFFFF00u) | (MEM8(g_esi + 0x12u) & 3u);
    if ((uint8_t)g_eax != 3u) goto done;
    g_ecx = g_esi;
    g_ebp = caller_frame;
    PUSH32(g_esp, 0x001F21C7u);
    sub_001F2094();
    g_eax = (g_eax & 0xFFFFFF00u) | ((uint8_t)g_eax & 3u);
    if ((uint8_t)g_eax != 1u || MEM32(g_esi + 0x194u) != 0u) goto done;
    if (MEM16(g_esi + 0x12u) & 0x2800u) {
        g_ecx = g_esi;
        g_ebp = caller_frame;
        PUSH32(g_esp, 0x001F21E5u);
        sub_001F1991();
        goto done;
    }
    g_eax = 0x400u;
    if (MEM16(g_esi + 0x12u) & (uint16_t)g_eax) goto done;
    PUSH32(g_esp, g_eax);
    g_ecx = g_esi;
    g_ebp = caller_frame;
    PUSH32(g_esp, 0x001F21FAu);
    sub_001F35AE();

done:
    g_eax = 0u;
    POP32(g_esp, g_edi);
    ++g_eax;
    POP32(g_esp, g_esi);
    g_ebp = caller_frame;
    g_esp += 4u; /* RET, no stack arguments. */
}

/* Retail XBE 0x000A8540..0x000A8569: 41 bytes, 12 instructions.
 * A virtual type query: MOV EAX,[ESP+4], compare four exact type IDs,
 * MOV/SETE AL, RET 4. EAX's upper 24 bits come from the argument;
 * ECX and every other guest register/memory location remain unchanged.
 * Verified against the complete original bytes by verify-area42-a8540.py.
 */
static void dah_retail_a8540(void)
{
    g_eax = MEM32(g_esp + 4u);
    if (g_eax == 0x448598FEu || g_eax == 0x1DE7E3DAu ||
        g_eax == 0x3BE6820Cu || g_eax == 0xA75FFAEBu)
        g_eax = (g_eax & 0xFFFFFF00u) | 1u;
    else
        g_eax &= 0xFFFFFF00u;
    g_esp += 8u; /* Pop return address and one argument: RET 4. */
}

/* Retail 0003C770..0003C86A, with the original four-way table at 0003C86C.
 * Keep the shared guest x87 stack and the FNSTSW/TEST-AH/JP result: the
 * transition requires a strictly negative value; zero and unordered return.
 */
extern void sub_0003D360(void);
extern void sub_000D42C0(void);
extern void sub_0010BC40(void);

static int dah_retail_3c770_compare_pop(void)
{
    g_fp_cmp = RECOMP_FCMP(g_fp_stack[g_fp_top], MEMF(0x00225C20u));
    g_fp_top = (g_fp_top + 1u) & 7u;
    g_eax = (g_eax & 0xFFFF0000u) |
        (uint32_t)(uint16_t)(((g_fp_top & 7u) << 11) |
        (g_fp_cmp == 2 ? 0x4500u : g_fp_cmp < 0 ? 0x0100u :
         g_fp_cmp > 0 ? 0x0000u : 0x4000u));
    return RECOMP_PARITY8((g_eax >> 8) & 5u);
}

static void dah_retail_3c770(void)
{
    uint32_t target;
#define DAH_3C770_PUSH_FP(value) do { double v_3c770 = (value); \
    g_fp_top = (g_fp_top + 7u) & 7u; g_fp_stack[g_fp_top] = v_3c770; } while (0)
#define DAH_3C770_POP_FP() (g_fp_top = (g_fp_top + 1u) & 7u)
#define DAH_3C770_ST0 g_fp_stack[g_fp_top]
    g_eax = MEM32(g_esp + 4u);
    PUSH32(g_esp, g_esi);
    PUSH32(g_esp, g_eax);
    g_esi = g_ecx;
    PUSH32(g_esp, 0x0003C77Du);
    sub_0003D360();
    g_eax = MEM32(g_esi + 0x30u);
    g_eax -= 1u;
    if (g_eax > 3u) goto done_3c770;

    switch (g_eax) {
    case 0u: /* table -> 0003C791 */
        DAH_3C770_PUSH_FP(MEMF(g_esi + 0x38u));
        DAH_3C770_ST0 -= MEMF(g_esp + 8u);
        MEMF(g_esi + 0x38u) = (float)DAH_3C770_ST0;
        if (dah_retail_3c770_compare_pop()) goto done_3c770;
        PUSH32(g_esp, g_edi);
        g_edi = MEM32(g_esi + 4u);
        g_ecx = 0x00278A58u;
        g_edi += 0xC8u;
        PUSH32(g_esp, 0x0003C7C0u);
        sub_000D42C0();
        DAH_3C770_ST0 *= MEMF(g_edi + 4u);
        DAH_3C770_ST0 += MEMF(g_edi);
        POP32(g_esp, g_edi);
        MEM32(g_esi + 0x30u) = 2u;
        MEMF(g_esi + 0x18u) = (float)DAH_3C770_ST0;
        DAH_3C770_POP_FP();
        break;

    case 1u: /* table -> 0003C7D4 */
        DAH_3C770_PUSH_FP(MEMF(g_esi + 0x3Cu));
        g_eax = MEM32(g_esi + 0x34u);
        DAH_3C770_ST0 -= MEMF(g_esp + 8u);
        MEMF(g_esi + 0x3Cu) = (float)DAH_3C770_ST0;
        DAH_3C770_POP_FP();
        if (!g_eax) goto virtual_3c809;
        g_eax = MEM32(g_esi + 0x14u);
        g_ecx = g_esi + 0x14u;
        if (g_eax == 0xFFFFFFFFu) goto virtual_3c809;
        PUSH32(g_esp, 0x0003C7F5u);
        sub_0010BC40();
        if (!g_eax) goto virtual_3c809;
        DAH_3C770_PUSH_FP(MEMF(g_esi + 0x3Cu));
        if (dah_retail_3c770_compare_pop()) goto done_3c770;
virtual_3c809:
        g_edx = MEM32(g_esi);
        g_ecx = g_esi;
        target = MEM32(g_edx + 0x20u);
        dah_retail_cop_icall(target, 0x0003C810u, g_esp);
        break;

    case 2u: /* table -> 0003C814 */
        DAH_3C770_PUSH_FP(MEMF(g_esi + 0x40u));
        DAH_3C770_ST0 -= MEMF(g_esp + 8u);
        MEMF(g_esi + 0x40u) = (float)DAH_3C770_ST0;
        if (dah_retail_3c770_compare_pop()) goto done_3c770;
        g_eax = MEM32(g_esi + 4u);
        g_ecx = MEM32(g_eax + 0x20u);
        MEM32(g_esi + 0x44u) = g_ecx;
        MEM32(g_esi + 0x30u) = 4u;
        break;

    case 3u: /* table -> 0003C83F */
        DAH_3C770_PUSH_FP(MEMF(g_esi + 0x44u));
        DAH_3C770_ST0 -= MEMF(g_esp + 8u);
        MEMF(g_esi + 0x44u) = (float)DAH_3C770_ST0;
        if (dah_retail_3c770_compare_pop()) goto done_3c770;
        g_edx = MEM32(g_esi + 4u);
        g_eax = MEM32(g_edx + 0x14u);
        MEM32(g_esi + 0x34u) = g_eax;
        MEM32(g_esi + 0x30u) = 0u;
        break;
    }

done_3c770:
    POP32(g_esp, g_esi);
    g_esp += 8u; /* RET 4 */
#undef DAH_3C770_PUSH_FP
#undef DAH_3C770_POP_FP
#undef DAH_3C770_ST0
}

/* Byte-verified retail callbacks observed during Farm -> Area42 transitions.
 * Keep original tail dispatch, destructor ordering, flags and guest stack.
 */
extern void sub_000CFB60(void);
extern void sub_0003D080(void);
extern void sub_0006B710(void);
extern void sub_0009C180(void);
extern void sub_000A7BA0(void);

static void dah_retail_12140(void)
{
    g_ecx = MEM32(g_ecx + 0x50u);
    g_eax = MEM32(g_ecx);
    RECOMP_ITAIL(MEM32(g_eax + 0x90u));
}

static void dah_retail_12160(void)
{
    g_ecx = MEM32(g_ecx + 0x50u);
    g_eax = MEM32(g_ecx);
    RECOMP_ITAIL(MEM32(g_eax + 0x98u));
}

static void dah_retail_3c660(void)
{
    PUSH32(g_esp, g_esi);
    g_esi = g_ecx;
    g_ecx = g_esi + 0x48u;
    MEM32(g_esi) = 0x00228BA8u;
    PUSH32(g_esp, 0x0003C671u); sub_000CFB60();
    g_ecx = g_esi;
    PUSH32(g_esp, 0x0003C678u); sub_0003D080();
    if (MEM8(g_esp + 8u) & 1u) {
        PUSH32(g_esp, g_esi);
        PUSH32(g_esp, 0x0003C685u); sub_0006B710();
        g_esp += 4u;
    }
    g_eax = g_esi;
    POP32(g_esp, g_esi);
    g_esp += 8u;
}

static void dah_retail_a8100(void)
{
    PUSH32(g_esp, g_ebx);
    PUSH32(g_esp, g_esi);
    g_ebx = g_ecx;
    PUSH32(g_esp, g_edi);
    g_ecx = g_ebx + 0x44u;
    PUSH32(g_esp, 0x000A810Du); sub_0009C180();
    g_esi = g_ebx + 0x718u;
    g_edi = 4u;
    do {
        g_ecx = MEM32(g_esi);
        PUSH32(g_esp, 0x000A811Fu); sub_0009C180();
        g_esi += 4u;
        --g_edi;
    } while (g_edi);
    POP32(g_esp, g_edi);
    POP32(g_esp, g_esi);
    g_ecx = g_ebx;
    POP32(g_esp, g_ebx);
    sub_000A7BA0();
}

/* Exact retail callbacks; instruction bytes audited by lift-union-area42-callbacks.py. */
extern void sub_00013F60(void);
extern void sub_0001DB00(void);
extern void sub_0001E200(void);
extern void sub_000325F0(void);
extern void sub_000326F0(void);
extern void sub_00032F10(void);
extern void sub_000380F0(void);
extern void sub_00074A00(void);
extern void sub_0007DDE0(void);
extern void sub_000D41A0(void);
extern void sub_000D42C0(void);
extern void sub_000D4680(void);
extern void sub_000D4770(void);
extern void sub_000D4A10(void);
extern void sub_000D5010(void);
extern void sub_001083B0(void);
extern void sub_00109F70(void);
#define eax g_eax
#define ecx g_ecx
#define edx g_edx
#define esp g_esp
#define ebx g_ebx
#define esi g_esi
#define edi g_edi

/**
 * sub_00035650
 * Original: 0x00035650 - 0x0003575C (268 bytes, 85 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
static void dah_retail_35650(void)
{
    const uint32_t caller_ebp = g_ebp, caller_seh = g_seh_ebp;
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    #define fp_push(v) do { double _fp_value = (v); \
        g_fp_top = (g_fp_top + 7u) & 7u; \
        g_fp_stack[g_fp_top] = _fp_value; } while (0)
    #define fp_pop() (g_fp_top = (g_fp_top + 1u) & 7u)
    #define fp_top() g_fp_stack[g_fp_top]
    #define fp_st(i) g_fp_stack[(g_fp_top + (i)) & 7u]
    #define fp_st1() fp_st(1)

loc_00035650: ;
    esp = esp - 0x28;
    PUSH32(esp, esi);
    esi = ecx;
    g_ebp = caller_ebp;
    PUSH32(esp, 0x0003565Bu); sub_00032F10(); /* call 0x00032F10 */
    g_ebp = caller_ebp; g_seh_ebp = caller_seh;

loc_0003565B: ;
    ecx = MEM32(esi + 0x60);
    eax = MEM32(ecx + 8);
    edx = MEM32(eax);
    eax = MEM32(edx);
    fp_push(MEMF(eax + 0xC)); /* fld float */
    fp_push(MEMF(esi + 0x30)); /* fld float */
    fp_top() = fp_top() * MEMF(0x225DCC); /* fmul dword ptr [0x225dcc] */
    MEMF(esp + 4) = (float)fp_top(); fp_pop(); /* fstp */
    g_fp_cmp = RECOMP_FCMP(fp_top(), MEMF(esp + 4)); /* fcom dword ptr [esp + 4] */
    eax = (eax & 0xFFFF0000u) | (uint32_t)(uint16_t)(((g_fp_top & 7u) << 11) | (g_fp_cmp == 2 ? 0x4500u : g_fp_cmp < 0 ? 0x0100u : g_fp_cmp > 0 ? 0x0000u : 0x4000u)); /* fnstsw ax <- fpu status */
    _fa = (uint32_t)(HI8(eax)) & 0xFFu; _fb = (uint32_t)(5) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test HI8(eax), 5 (8-bit) */
    if (RECOMP_PARITY8((_fa) & (_fb))) goto loc_00035686; /* jp: parity */

loc_00035680: ;
    fp_pop(); /* fstp st(0) */
    fp_push(MEMF(esp + 4)); /* fld float */

loc_00035686: ;
    fp_top() = fp_top() + MEMF(esi + 0x64); /* fadd dword ptr [esi + 0x64] */
    MEMF(esp + 4) = (float)fp_top(); /* fst */
    edx = MEM32(esp + 4);
    MEMF(esi + 0x2C) = (float)fp_top(); fp_pop(); /* fstp */
    PUSH32(esp, edx);
    PUSH32(esp, ecx);
    edx = esp + 0x10;
    ecx = esp + 0x1C;
    g_ebp = caller_ebp;
    PUSH32(esp, 0x000356A3u); sub_000325F0(); /* call 0x000325F0 */
    g_ebp = caller_ebp; g_seh_ebp = caller_seh;

loc_000356A3: ;
    eax = MEM32(esp + 8);
    PUSH32(esp, eax);
    g_ebp = caller_ebp;
    PUSH32(esp, 0x000356ADu); sub_000D41A0(); /* call 0x000D41A0 */
    g_ebp = caller_ebp; g_seh_ebp = caller_seh;

loc_000356AD: ;
    g_fp_cmp = RECOMP_FCMP(fp_top(), MEMF(0x228970)); fp_pop(); /* fcomp dword ptr [0x228970] */
    eax = (eax & 0xFFFF0000u) | (uint32_t)(uint16_t)(((g_fp_top & 7u) << 11) | (g_fp_cmp == 2 ? 0x4500u : g_fp_cmp < 0 ? 0x0100u : g_fp_cmp > 0 ? 0x0000u : 0x4000u)); /* fnstsw ax <- fpu status */
    _fa = (uint32_t)(HI8(eax)) & 0xFFu; _fb = (uint32_t)(5) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test HI8(eax), 5 (8-bit) */
    if (RECOMP_PARITY8((_fa) & (_fb))) goto loc_000356D1; /* jp: parity */

loc_000356BA: ;
    ecx = MEM32(esp + 0xC);
    PUSH32(esp, ecx);
    g_ebp = caller_ebp;
    PUSH32(esp, 0x000356C4u); sub_000D41A0(); /* call 0x000D41A0 */
    g_ebp = caller_ebp; g_seh_ebp = caller_seh;

loc_000356C4: ;
    g_fp_cmp = RECOMP_FCMP(fp_top(), MEMF(0x228970)); fp_pop(); /* fcomp dword ptr [0x228970] */
    eax = (eax & 0xFFFF0000u) | (uint32_t)(uint16_t)(((g_fp_top & 7u) << 11) | (g_fp_cmp == 2 ? 0x4500u : g_fp_cmp < 0 ? 0x0100u : g_fp_cmp > 0 ? 0x0000u : 0x4000u)); /* fnstsw ax <- fpu status */
    _fa = (uint32_t)(HI8(eax)) & 0xFFu; _fb = (uint32_t)(5) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test HI8(eax), 5 (8-bit) */
    if ((!RECOMP_PARITY8((_fa) & (_fb)))) goto loc_000356F6; /* jnp: not parity */

loc_000356D1: ;
    fp_push(MEMF(esp + 0xC)); /* fld float */
    ecx = esp + 8;
    fp_top() = -fp_top(); /* fchs */
    MEM32(esp + 0x10) = 0;
    fp_push(MEMF(esp + 8)); /* fld float */
    { double _t = fp_top(); fp_top() = fp_st1(); fp_st1() = _t; } /* fxch st(1) */
    MEMF(esp + 8) = (float)fp_top(); fp_pop(); /* fstp */
    MEMF(esp + 0xC) = (float)fp_top(); fp_pop(); /* fstp */
    g_ebp = caller_ebp;
    PUSH32(esp, 0x000356F6u); sub_000D5010(); /* call 0x000D5010 */
    g_ebp = caller_ebp; g_seh_ebp = caller_seh;

loc_000356F6: ;
    edx = MEM32(esi + 0x60);
    eax = MEM32(edx + 8);
    ecx = MEM32(eax);
    edx = MEM32(ecx);
    fp_push(MEMF(edx + 0xC)); /* fld float */
    PUSH32(esp, ecx);
    fp_top() = fp_top() * MEMF(esi + 0x68); /* fmul dword ptr [esi + 0x68] */
    edx = esp + 0xC;
    ecx = edx;
    MEMF(esp) = (float)fp_top(); fp_pop(); /* fstp */
    g_ebp = caller_ebp;
    PUSH32(esp, 0x00035715u); sub_000D4A10(); /* call 0x000D4A10 */
    g_ebp = caller_ebp; g_seh_ebp = caller_seh;

loc_00035715: ;
    eax = esp + 8;
    edx = esp + 0x14;
    PUSH32(esp, eax);
    ecx = edx;
    g_ebp = caller_ebp;
    PUSH32(esp, 0x00035725u); sub_000D4770(); /* call 0x000D4770 */
    g_ebp = caller_ebp; g_seh_ebp = caller_seh;

loc_00035725: ;
    eax = MEM32(esi + 0x70);
    edx = MEM32(eax + 0x18);
    ecx = eax + 0x18;
    { uint32_t _icall_esp = g_esp;
    g_ebp = caller_ebp;
    { uint32_t _icall_target = MEM32(edx); PUSH32(esp, 0x00035730u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    g_ebp = caller_ebp; g_seh_ebp = caller_seh;
    }

loc_00035730: ;
    fp_push(MEMF(esp + 0x14)); /* fld float */
    fp_top() = fp_top() - MEMF(eax); /* fsub dword ptr [eax] */
    MEMF(esp + 0x20) = (float)fp_top(); fp_pop(); /* fstp */
    ecx = MEM32(esp + 0x20);
    fp_push(MEMF(esp + 0x18)); /* fld float */
    fp_top() = fp_top() - MEMF(eax + 4); /* fsub dword ptr [eax + 4] */
    MEMF(esp + 0x24) = (float)fp_top(); fp_pop(); /* fstp */
    eax = MEM32(esp + 0x24);
    PUSH32(esp, eax);
    PUSH32(esp, ecx);
    g_ebp = caller_ebp;
    PUSH32(esp, 0x00035754u); sub_000D4680(); /* call 0x000D4680 */
    g_ebp = caller_ebp; g_seh_ebp = caller_seh;

loc_00035754: ;
    MEMF(esi + 0x28) = (float)fp_top(); fp_pop(); /* fstp */
    POP32(esp, esi);
    esp = esp + 0x28;
    esp += 4; g_ebp = caller_ebp; g_seh_ebp = caller_seh; return; /* ret */

    #undef fp_push
    #undef fp_pop
    #undef fp_top
    #undef fp_st
    #undef fp_st1
}


/**
 * sub_0001CB50
 * Original: 0x0001CB50 - 0x0001CD34 (484 bytes, 154 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
static void dah_retail_1cb50(void)
{
    const uint32_t caller_ebp = g_ebp, caller_seh = g_seh_ebp;
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    #define fp_push(v) do { double _fp_value = (v); \
        g_fp_top = (g_fp_top + 7u) & 7u; \
        g_fp_stack[g_fp_top] = _fp_value; } while (0)
    #define fp_pop() (g_fp_top = (g_fp_top + 1u) & 7u)
    #define fp_top() g_fp_stack[g_fp_top]
    #define fp_st(i) g_fp_stack[(g_fp_top + (i)) & 7u]
    #define fp_st1() fp_st(1)

loc_0001CB50: ;
    PUSH32(esp, ecx);
    eax = MEM32(esp + 8);
    PUSH32(esp, esi);
    PUSH32(esp, eax);
    esi = ecx;
    g_ebp = ebp;
    PUSH32(esp, 0x0001CB5Eu); sub_0001E200(); /* call 0x0001E200 */
    g_ebp = ebp; g_seh_ebp = caller_seh;

loc_0001CB5E: ;
    ecx = MEM32(esi + 8);
    SET_LO8(eax, MEM8(ecx + 0x58));
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0001CCBD; /* je: equal / zero */

loc_0001CB6C: ;
    ecx = MEM32(esi + 4);
    edx = MEM32(ecx);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, ebx);
    g_ebp = ebp;
    { uint32_t _icall_target = MEM32(edx + 0xF8); PUSH32(esp, 0x0001CB78u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    g_ebp = ebp; g_seh_ebp = caller_seh;
    }

loc_0001CB78: ;
    ebx = eax;
    eax = MEM32(esi + 4);
    ecx = MEM32(eax + 0x12C);
    ecx = ecx >> 6;
    _fa = (uint32_t)(LO8(ecx)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(ecx), 1 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0001CCC2; /* je: equal / zero */

loc_0001CB8F: ;
    _fa = (uint32_t)(MEM32(ebx + 0x10)) & 0xFFFFFFFFu; _fb = (uint32_t)(4) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(ebx + 0x10), 4 (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_0001CCBC; /* je: equal / zero */

loc_0001CB99: ;
    edx = MEM32(ebx + 0x30);
    eax = edx;
    PUSH32(esp, eax);
    MEM32(esp + 0xC) = edx;
    g_ebp = ebp;
    PUSH32(esp, 0x0001CBA8u); sub_000D41A0(); /* call 0x000D41A0 */
    g_ebp = ebp; g_seh_ebp = caller_seh;

loc_0001CBA8: ;
    g_fp_cmp = RECOMP_FCMP(fp_top(), MEMF(0x227090)); fp_pop(); /* fcomp dword ptr [0x227090] */
    eax = (eax & 0xFFFF0000u) | (uint32_t)(uint16_t)(((g_fp_top & 7u) << 11) | (g_fp_cmp == 2 ? 0x4500u : g_fp_cmp < 0 ? 0x0100u : g_fp_cmp > 0 ? 0x0000u : 0x4000u)); /* fnstsw ax <- fpu status */
    _fa = (uint32_t)(HI8(eax)) & 0xFFu; _fb = (uint32_t)(0x41) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test HI8(eax), 0x41 (8-bit) */
    if (RECOMP_PARITY8((_fa) & (_fb))) goto loc_0001CCBC; /* jp: parity */

loc_0001CBB9: ;
    eax = MEM32(esi + 4);
    PUSH32(esp, ebp);
    ecx = eax + 0x4E8;
    g_ebp = ebp;
    PUSH32(esp, 0x0001CBC8u); sub_00109F70(); /* call 0x00109F70 */
    g_ebp = ebp; g_seh_ebp = caller_seh;

loc_0001CBC8: ;
    ebp = eax;
    _fa = (uint32_t)(ebp) & 0xFFFFFFFFu; _fb = (uint32_t)(ebp) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ebp, ebp (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0001CCBB; /* je: equal / zero */

loc_0001CBD2: ;
    edx = MEM32(esi + 4);
    eax = MEM32(edx + 0x198);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    PUSH32(esp, edi);
    edi = edx + 0x198;
    if (TEST_Z(_fa, _fb)) goto loc_0001CCBA; /* je: equal / zero */

loc_0001CBEA: ;
    ecx = edi;
    g_ebp = ebp;
    PUSH32(esp, 0x0001CBF1u); sub_000326F0(); /* call 0x000326F0 */
    g_ebp = ebp; g_seh_ebp = caller_seh;

loc_0001CBF1: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0001CBFD; /* je: equal / zero */

loc_0001CBF5: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(ebp) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, ebp (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_0001CCBA; /* je: equal / zero */

loc_0001CBFD: ;
    fp_push(MEMF(esi + 0x50)); /* fld float */
    fp_top() = fp_top() - MEMF(esp + 0x18); /* fsub dword ptr [esp + 0x18] */
    MEMF(esi + 0x50) = (float)fp_top(); /* fst */
    g_fp_cmp = RECOMP_FCMP(fp_top(), MEMF(0x225C20)); fp_pop(); /* fcomp dword ptr [0x225c20] */
    eax = (eax & 0xFFFF0000u) | (uint32_t)(uint16_t)(((g_fp_top & 7u) << 11) | (g_fp_cmp == 2 ? 0x4500u : g_fp_cmp < 0 ? 0x0100u : g_fp_cmp > 0 ? 0x0000u : 0x4000u)); /* fnstsw ax <- fpu status */
    _fa = (uint32_t)(HI8(eax)) & 0xFFu; _fb = (uint32_t)(5) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test HI8(eax), 5 (8-bit) */
    if (RECOMP_PARITY8((_fa) & (_fb))) goto loc_0001CCBA; /* jp: parity */

loc_0001CC18: ;
    edx = MEM32(edi + 8);
    eax = MEM32(edx);
    edx = MEM32(eax);
    eax = MEM32(edx + 0x18);
    ecx = MEM32(0x25AB64);
    edx = esp + 0x18;
    PUSH32(esp, edx);
    MEM32(esp + 0x1C) = eax;
    g_ebp = ebp;
    PUSH32(esp, 0x0001CC36u); sub_000380F0(); /* call 0x000380F0 */
    g_ebp = ebp; g_seh_ebp = caller_seh;

loc_0001CC36: ;
    ebp = eax;
    _fa = (uint32_t)(ebp) & 0xFFFFFFFFu; _fb = (uint32_t)(ebp) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ebp, ebp (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0001CCA7; /* je: equal / zero */

loc_0001CC3C: ;
    ecx = MEM32(esi + 4);
    eax = MEM32(ecx + 0x1C);
    fp_push(MEMF(eax + 0x190)); /* fld float */
    g_fp_cmp = RECOMP_FCMP(fp_top(), MEMF(0x2270AC)); fp_pop(); /* fcomp dword ptr [0x2270ac] */
    eax = (eax & 0xFFFF0000u) | (uint32_t)(uint16_t)(((g_fp_top & 7u) << 11) | (g_fp_cmp == 2 ? 0x4500u : g_fp_cmp < 0 ? 0x0100u : g_fp_cmp > 0 ? 0x0000u : 0x4000u)); /* fnstsw ax <- fpu status */
    _fa = (uint32_t)(HI8(eax)) & 0xFFu; _fb = (uint32_t)(5) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test HI8(eax), 5 (8-bit) */
    if (RECOMP_PARITY8((_fa) & (_fb))) goto loc_0001CCA7; /* jp: parity */

loc_0001CC55: ;
    fp_push(MEMF(ecx + 0x4EC)); /* fld float */
    fp_top() = fp_top() - MEMF(ecx + 0x4F8); /* fsub dword ptr [ecx + 0x4f8] */
    fp_push(MEMF(ecx + 0x4F0)); /* fld float */
    fp_top() = fp_top() - MEMF(ecx + 0x4FC); /* fsub dword ptr [ecx + 0x4fc] */
    { double _t = fp_top(); fp_push(_t); } /* fld st(0) */
    fp_top() = fp_top() * fp_st1(); /* fmul st(1) */
    { double _t = g_fp_stack[(g_fp_top + 2) & 7]; fp_push(_t); } /* fld st(2) */
    fp_top() = fp_top() * g_fp_stack[(g_fp_top + 3) & 7]; /* fmul st(3) */
    fp_st1() = fp_st1() + fp_top(); fp_pop(); /* faddp st(1) */
    g_fp_cmp = RECOMP_FCMP(fp_top(), MEMF(0x2270A8)); fp_pop(); /* fcomp dword ptr [0x2270a8] */
    eax = (eax & 0xFFFF0000u) | (uint32_t)(uint16_t)(((g_fp_top & 7u) << 11) | (g_fp_cmp == 2 ? 0x4500u : g_fp_cmp < 0 ? 0x0100u : g_fp_cmp > 0 ? 0x0000u : 0x4000u)); /* fnstsw ax <- fpu status */
    fp_pop(); /* fstp st(0) */
    _fa = (uint32_t)(HI8(eax)) & 0xFFu; _fb = (uint32_t)(0x41) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test HI8(eax), 0x41 (8-bit) */
    fp_pop(); /* fstp st(0) */
    if (TEST_Z(_fa, _fb)) goto loc_0001CC9F; /* je: equal / zero */

loc_0001CC88: ;
    ecx = 0x278A58;
    g_ebp = ebp;
    PUSH32(esp, 0x0001CC92u); sub_000D42C0(); /* call 0x000D42C0 */
    g_ebp = ebp; g_seh_ebp = caller_seh;

loc_0001CC92: ;
    g_fp_cmp = RECOMP_FCMP(fp_top(), MEMF(0x2270B0)); fp_pop(); /* fcomp dword ptr [0x2270b0] */
    eax = (eax & 0xFFFF0000u) | (uint32_t)(uint16_t)(((g_fp_top & 7u) << 11) | (g_fp_cmp == 2 ? 0x4500u : g_fp_cmp < 0 ? 0x0100u : g_fp_cmp > 0 ? 0x0000u : 0x4000u)); /* fnstsw ax <- fpu status */
    _fa = (uint32_t)(HI8(eax)) & 0xFFu; _fb = (uint32_t)(5) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test HI8(eax), 5 (8-bit) */
    if (RECOMP_PARITY8((_fa) & (_fb))) goto loc_0001CCA7; /* jp: parity */

loc_0001CC9F: ;
    PUSH32(esp, ebp);
    ecx = esi;
    g_ebp = ebp;
    PUSH32(esp, 0x0001CCA7u); sub_0001DB00(); /* call 0x0001DB00 */
    g_ebp = ebp; g_seh_ebp = caller_seh;

loc_0001CCA7: ;
    esi = MEM32(esi + 8);
    eax = MEM32(esi + 0x50);
    ecx = MEM32(esi + 0x54);
    edx = MEM32(ebx);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, eax);
    PUSH32(esp, ecx);
    PUSH32(esp, edi);
    ecx = ebx;
    g_ebp = ebp;
    { uint32_t _icall_target = MEM32(edx + 0x2C); PUSH32(esp, 0x0001CCBAu); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    g_ebp = ebp; g_seh_ebp = caller_seh;
    }

loc_0001CCBA: ;
    POP32(esp, edi);

loc_0001CCBB: ;
    POP32(esp, ebp);

loc_0001CCBC: ;
    POP32(esp, ebx);

loc_0001CCBD: ;
    POP32(esp, esi);
    POP32(esp, ecx);
    esp += 8; g_ebp = caller_ebp; g_seh_ebp = caller_seh; return; /* ret 4 */

loc_0001CCC2: ;
    ecx = 0x278A58;
    g_ebp = ebp;
    PUSH32(esp, 0x0001CCCCu); sub_000D42C0(); /* call 0x000D42C0 */
    g_ebp = ebp; g_seh_ebp = caller_seh;

loc_0001CCCC: ;
    fp_top() = fp_top() + MEMF(0x225C28); /* fadd dword ptr [0x225c28] */
    fp_top() = fp_top() * MEMF(0x2270A4); /* fmul dword ptr [0x2270a4] */
    MEMF(esi + 0x50) = (float)fp_top(); fp_pop(); /* fstp */
    eax = MEM32(ebx + 0x10);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(4) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 4 (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_0001CCBC; /* jne: not equal / not zero */

loc_0001CCE3: ;
    edx = MEM32(ebx + 0x28);
    eax = MEM32(ebx + 0x44);
    ecx = edx;
    MEM32(esp + 0x10) = edx;
    PUSH32(esp, ecx);
    edx = eax;
    PUSH32(esp, edx);
    MEM32(esp + 0x10) = eax;
    g_ebp = ebp;
    PUSH32(esp, 0x0001CCFCu); sub_00013F60(); /* call 0x00013F60 */
    g_ebp = ebp; g_seh_ebp = caller_seh;

loc_0001CCFC: ;
    PUSH32(esp, ecx);
    MEMF(esp) = (float)fp_top(); fp_pop(); /* fstp */
    g_ebp = ebp;
    PUSH32(esp, 0x0001CD05u); sub_000D41A0(); /* call 0x000D41A0 */
    g_ebp = ebp; g_seh_ebp = caller_seh;

loc_0001CD05: ;
    g_fp_cmp = RECOMP_FCMP(fp_top(), MEMF(0x244F20)); fp_pop(); /* fcomp dword ptr [0x244f20] */
    eax = (eax & 0xFFFF0000u) | (uint32_t)(uint16_t)(((g_fp_top & 7u) << 11) | (g_fp_cmp == 2 ? 0x4500u : g_fp_cmp < 0 ? 0x0100u : g_fp_cmp > 0 ? 0x0000u : 0x4000u)); /* fnstsw ax <- fpu status */
    _fa = (uint32_t)(HI8(eax)) & 0xFFu; _fb = (uint32_t)(5) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test HI8(eax), 5 (8-bit) */
    if (RECOMP_PARITY8((_fa) & (_fb))) goto loc_0001CCBC; /* jp: parity */

loc_0001CD12: ;
    eax = MEM32(esi + 8);
    ecx = MEM32(eax + 0x50);
    eax = MEM32(eax + 0x54);
    edx = MEM32(ebx);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, ecx);
    ecx = MEM32(esi + 4);
    ecx = ecx + 0x198;
    PUSH32(esp, eax);
    PUSH32(esp, ecx);
    ecx = ebx;
    g_ebp = ebp;
    { uint32_t _icall_target = MEM32(edx + 0x20); PUSH32(esp, 0x0001CD2Eu); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    g_ebp = ebp; g_seh_ebp = caller_seh;
    }

loc_0001CD2E: ;
    POP32(esp, ebx);
    POP32(esp, esi);
    POP32(esp, ecx);
    esp += 8; g_ebp = caller_ebp; g_seh_ebp = caller_seh; return; /* ret 4 */

    #undef fp_push
    #undef fp_pop
    #undef fp_top
    #undef fp_st
    #undef fp_st1
}


/**
 * sub_000566A0
 * Original: 0x000566A0 - 0x00056830 (400 bytes, 120 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
static void dah_retail_566a0(void)
{
    const uint32_t caller_ebp = g_ebp, caller_seh = g_seh_ebp;
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_000566A0: ;
    eax = MEM32(edx + 4);
    esp = esp - 0xC;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0x9E7EDF34u) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0x9E7EDF34u (32-bit) */
    PUSH32(esp, esi);
    esi = ecx;
    if (CMP_A(_fa, _fb)) goto loc_000567A0; /* ja: above (unsigned >) */

loc_000566B4: ;
    if (CMP_EQ(_fa, _fb)) goto loc_000566FB; /* je: equal / zero */

loc_000566B6: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0x37EC8C25) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0x37EC8C25 (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_00056829; /* je: equal / zero */

loc_000566C1: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0x768FCBA6) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0x768FCBA6 (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_000567A7; /* jne: not equal / not zero */

loc_000566CC: ;
    edx = MEM32(edx + 0xC);
    _fa = (uint32_t)(edx) & 0xFFFFFFFFu; _fb = (uint32_t)(1) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edx, 1 (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_000567CA; /* je: equal / zero */

loc_000566D8: ;
    _fa = (uint32_t)(edx) & 0xFFFFFFFFu; _fb = (uint32_t)(0x6E) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edx, 0x6E (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_000567CA; /* je: equal / zero */

loc_000566E1: ;
    _fa = (uint32_t)(edx) & 0xFFFFFFFFu; _fb = (uint32_t)(0x104) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edx, 0x104 (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_000567CA; /* je: equal / zero */

loc_000566ED: ;
    eax = MEM32(esp + 0x14);
    MEM8(eax) = 0;
    POP32(esp, esi);
    esp = esp + 0xC;
    esp += 8; g_ebp = caller_ebp; g_seh_ebp = caller_seh; return; /* ret 4 */

loc_000566FB: ;
    ecx = MEM32(esi + 0x6C);
    edx = MEM32(ecx + 0x138);
    eax = MEM32(edx + 0x58);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0005672B; /* je: equal / zero */

loc_0005670B: ;
    edx = MEM32(eax);
    ecx = eax;
    { uint32_t _icall_esp = g_esp;
    g_ebp = caller_ebp;
    { uint32_t _icall_target = MEM32(edx + 0x44); PUSH32(esp, 0x00056712u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    g_ebp = caller_ebp; g_seh_ebp = caller_seh;
    }

loc_00056712: ;
    ecx = MEM32(esi + 0x6C);
    PUSH32(esp, 0);
    PUSH32(esp, 0);
    PUSH32(esp, 0);
    PUSH32(esp, 0);
    PUSH32(esp, 0);
    PUSH32(esp, 0x5D0271AC);
    PUSH32(esp, 0x5D0271AC);
    goto loc_0005673F;

loc_0005672B: ;
    PUSH32(esp, 0);
    PUSH32(esp, 0);
    PUSH32(esp, 0);
    PUSH32(esp, 0);
    PUSH32(esp, 0);
    PUSH32(esp, 0xF9489FF2u);
    PUSH32(esp, 0xF9489FF2u);

loc_0005673F: ;
    g_ebp = caller_ebp;
    PUSH32(esp, 0x00056744u); sub_0007DDE0(); /* call 0x0007DDE0 */
    g_ebp = caller_ebp; g_seh_ebp = caller_seh;

loc_00056744: ;
    eax = MEM32(esi + 0x6C);
    ecx = MEM32(eax + 0x28);
    PUSH32(esp, 0);
    PUSH32(esp, 0);
    g_ebp = caller_ebp;
    PUSH32(esp, 0x00056753u); sub_001083B0(); /* call 0x001083B0 */
    g_ebp = caller_ebp; g_seh_ebp = caller_seh;

loc_00056753: ;
    ecx = MEM32(0x24763C);
    PUSH32(esp, 0);
    PUSH32(esp, 0);
    PUSH32(esp, 0);
    PUSH32(esp, ecx);
    ecx = MEM32(esi + 0x6C);
    PUSH32(esp, 1);
    PUSH32(esp, 0);
    PUSH32(esp, 0);
    g_ebp = caller_ebp;
    PUSH32(esp, 0x0005676Eu); sub_0007DDE0(); /* call 0x0007DDE0 */
    g_ebp = caller_ebp; g_seh_ebp = caller_seh;

loc_0005676E: ;
    esi = MEM32(esi + 0x6C);
    ecx = esi + 0xC0;
    eax = esp + 4;
    MEM32(esp + 4) = 0;
    MEM32(esp + 8) = 0;
    MEM32(esp + 0xC) = 0;
    edx = MEM32(ecx);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, eax);
    g_ebp = caller_ebp;
    { uint32_t _icall_target = MEM32(edx + 0x1C); PUSH32(esp, 0x00056799u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    g_ebp = caller_ebp; g_seh_ebp = caller_seh;
    }

loc_00056799: ;
    POP32(esp, esi);
    esp = esp + 0xC;
    esp += 8; g_ebp = caller_ebp; g_seh_ebp = caller_seh; return; /* ret 4 */

loc_000567A0: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0xCEE59BD2u) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0xCEE59BD2u (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_000567DC; /* je: equal / zero */

loc_000567A7: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0x2C4F6A80) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0x2C4F6A80 (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_000567CA; /* je: equal / zero */

loc_000567AE: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0x768FCBA6) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0x768FCBA6 (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_000567CA; /* je: equal / zero */

loc_000567B5: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0xC530488Bu) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0xC530488Bu (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_00056829; /* jne: not equal / not zero */

loc_000567BC: ;
    MEM8(esi + 0x28F) = 0;
    POP32(esp, esi);
    esp = esp + 0xC;
    esp += 8; g_ebp = caller_ebp; g_seh_ebp = caller_seh; return; /* ret 4 */

loc_000567CA: ;
    eax = MEM32(esp + 0x14);
    MEM8(eax) = 1;
    MEM8(eax + 1) = 1;
    POP32(esp, esi);
    esp = esp + 0xC;
    esp += 8; g_ebp = caller_ebp; g_seh_ebp = caller_seh; return; /* ret 4 */

loc_000567DC: ;
    eax = MEM32(edx + 0xC);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_00056829; /* jne: not equal / not zero */

loc_000567E3: ;
    eax = MEM32(edx + 0x1C);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_00056829; /* jne: not equal / not zero */

loc_000567EA: ;
    _fa = (uint32_t)(MEM32(edx + 0x10)) & 0xFFFFFFFFu; _fb = (uint32_t)(0xB2C53B91u) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(edx + 0x10), 0xB2C53B91u (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_00056829; /* jne: not equal / not zero */

loc_000567F3: ;
    edx = MEM32(edx + 0x14);
    _fa = (uint32_t)(edx) & 0xFFFFFFFFu; _fb = (uint32_t)(0xF9489FF2u) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edx, 0xF9489FF2u (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_00056806; /* je: equal / zero */

loc_000567FE: ;
    _fa = (uint32_t)(edx) & 0xFFFFFFFFu; _fb = (uint32_t)(0x5D0271AC) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edx, 0x5D0271AC (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_00056829; /* jne: not equal / not zero */

loc_00056806: ;
    eax = MEM32(esi + 0x6C);
    edx = MEM32(eax + 0xC0);
    ecx = eax + 0xC0;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 1);
    PUSH32(esp, 1);
    g_ebp = caller_ebp;
    { uint32_t _icall_target = MEM32(edx + 0x38); PUSH32(esp, 0x0005681Cu); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    g_ebp = caller_ebp; g_seh_ebp = caller_seh;
    }

loc_0005681C: ;
    PUSH32(esp, 0xFFFFFFFEu);
    PUSH32(esp, 0x6E);
    PUSH32(esp, esi);
    ecx = esi + 0x30;
    g_ebp = caller_ebp;
    PUSH32(esp, 0x00056829u); sub_00074A00(); /* call 0x00074A00 */
    g_ebp = caller_ebp; g_seh_ebp = caller_seh;

loc_00056829: ;
    POP32(esp, esi);
    esp = esp + 0xC;
    esp += 8; g_ebp = caller_ebp; g_seh_ebp = caller_seh; return; /* ret 4 */

}

#undef eax
#undef ecx
#undef edx
#undef esp
#undef ebx
#undef esi
#undef edi

recomp_func_t recomp_lookup_manual(uint32_t xbox_va)
{
    if (xbox_va == 0x001F2178u) return dah_retail_1f2178;
    if(xbox_va>=0x000F8000u && xbox_va<0x00110000u && g_dah_input_state_calls>=6900u && g_dah_input_state_calls<7600u && MEM32(g_esp)==0x0019288Du && getenv("DAH_LEVEL_EVENT_TRACE")) {
        static unsigned api_count;
        if(api_count++<20000u) {
            fprintf(stderr,"[DAH-SCRIPT-API] tick=%u target=%08X this=%08X caller=%08X args=",g_dah_input_state_calls,xbox_va,g_ecx,MEM32(g_esp));
            for(unsigned i=1;i<9;i++)fprintf(stderr," %08X",MEM32(g_esp+i*4));fputc('\n',stderr);
        }
    }

    if(xbox_va==0x0005A3C0u && MEM32(g_esp+4)!=0x1AE7CEFDu && getenv("DAH_LEVEL_EVENT_TRACE")) {
        static unsigned count;
        if(count++<128u){
            fprintf(stderr,"[DAH-LEVEL-EVENT] tick=%u this=%08X event=%08X arg=%08X caller=%08X trace=",g_dah_input_state_calls,g_ecx,MEM32(g_esp+4),MEM32(g_esp+8),MEM32(g_esp));
            uint32_t end=g_icall_trace_idx;
            for(unsigned i=0;i<ICALL_TRACE_SIZE;i++)fprintf(stderr," %08X",g_icall_trace[(end-ICALL_TRACE_SIZE+i)&(ICALL_TRACE_SIZE-1u)]);
            fprintf(stderr," stack=");for(unsigned i=0;i<32;i++)fprintf(stderr," %08X",MEM32(g_esp+i*4));fputc('\n',stderr);
        }
    }
    /* Compile the static overrides as balanced dispatch instead of a linear scan. */
    switch (xbox_va) {
    case 0x00035650u: return dah_retail_35650;
    case 0x0001CB50u: return dah_retail_1cb50;
    case 0x000566A0u: return dah_retail_566a0;
    case 0x00012140u: return dah_retail_12140;
    case 0x00012160u: return dah_retail_12160;
    case 0x0003C660u: return dah_retail_3c660;
    case 0x000A8100u: return dah_retail_a8100;
    case 0x0003C770u: return dah_retail_3c770;
    case 0x000A8540u: return dah_retail_a8540;
    case 0x0012B560u: return dah_retail_12b560;
    case 0x00133E90u: return dah_retail_133e90;
    case 0x00133EF0u: return dah_retail_133ef0;
    case 0x0018DA20u: return dah_retail_18da20;
    case 0x00085720u: return dah_retail_85720;
    case 0x0006FC30u: return dah_retail_6fc30;
    case 0x0004A460u: return dah_retail_4a460;
    case 0x00015AB0u: return dah_retail_15ab0;
    case 0x00063510u: return sub_00063510;
    case 0x001E0436u: return sub_001E0436;
    case 0x001E045Du: return sub_001E045D;
    case 0x001E0489u: return sub_001E0489;
    case 0x001E0497u: return sub_001E0497;
    case 0x001E049Eu: return sub_001E049E;
    case 0x001E04ACu: return sub_001E04AC;
    case 0x001E04B3u: return sub_001E04B3;
    case 0x001E04BAu: return sub_001E04BA;
    case 0x001E04C1u: return sub_001E04C1;
    case 0x001E04C4u: return sub_001E04C4;
    case 0x001E04D5u: return sub_001E04D5;
    case 0x0006B790u: return trace_game_boot;
    case 0x000DB150u: return sub_000DB150;
    case 0x000DB220u: return sub_000DB220;
    case 0x000DB3C0u: return sub_000DB3C0;
    case 0x000DB500u: return sub_000DB500;
    case 0x000DB540u: return sub_000DB540;
    case 0x000DCD40u: return sub_000DCD40;
    case 0x000DCDE0u: return sub_000DCDE0;
    case 0x000E0F50u: return sub_000E0F50;
    case 0x000F0D10u: return sub_000F0D10;
    case 0x000F1800u: return sub_000F1800;
    case 0x00122980u: return sub_00122980;
    case 0x00217680u: return sub_00217680;
    case 0x00217B70u: return sub_00217B70;
    case 0x00218530u: return sub_00218530;
    case 0x0021F040u: return sub_0021F040;
    case 0x0021F200u: return sub_0021F200;
    case 0x0021F480u: return sub_0021F480;
    case 0x0021F7A0u: return sub_0021F7A0;
    case 0x001A18E0u: return sub_001A18E0;
    case 0x00195BD6u: return sub_00195BD6;
    case 0x00195BDDu: return sub_00195BDD;
    case 0x0019200Cu: return sub_0019200C;
    case 0x00191FAAu: return sub_00191FAA;
    case 0x00192022u: return sub_00192022;
    case 0x0019203Au: return sub_0019203A;
    case 0x00192607u: return sub_00192607;
    case 0x00199738u: return sub_00199738;
    case 0x001997C4u: return sub_001997C4;
    case 0x00199837u: return sub_00199837;
    case 0x001998F5u: return sub_001998F5;
    case 0x00197006u: return sub_00197006;
    case 0x0019703Cu: return sub_0019703C;
    case 0x0019704Au: return sub_0019704A;
    case 0x00197060u: return sub_00197060;
    case 0x00196A1Eu: return sub_00196A1E;
    case 0x00196A39u: return sub_00196A39;
    case 0x00196917u: return sub_00196917;
    case 0x0019695Du: return sub_0019695D;
    case 0x001969DBu: return sub_001969DB;
    case 0x0019683Fu: return sub_0019683F;
    case 0x00196815u: return sub_00196815;
    case 0x00196853u: return sub_00196853;
    case 0x0019685Eu: return sub_0019685E;
    case 0x0019687Fu: return sub_0019687F;
    case 0x0019689Bu: return sub_0019689B;
    case 0x001968B9u: return sub_001968B9;
    case 0x001968DEu: return sub_001968DE;
    case 0x001968FBu: return sub_001968FB;
    case 0x0008B9A0u: return sub_0008B9A0;
    case 0x000BBA10u: return sub_000BBA10;
    case 0x000FE7B0u: return sub_000FE7B0;
    case 0x0013C5A6u: return sub_0013C5A6;
    case 0x0013B5A0u: return sub_0013B5A0;
    case 0x0013F420u: return sub_0013F420;
    case 0x0013F459u: return sub_0013F459;
    case 0x0013F45Bu: return sub_0013F45B;
    case 0x0013F483u: return sub_0013F483;
    case 0x0013F4C2u: return sub_0013F4C2;
    case 0x0008BA90u: return sub_0008BA90;
    case 0x000E3BE0u: return sub_000E3BE0;
    case 0x0011C180u: return sub_0011C180;
    case 0x001F225Du: return sub_001F225D;
    case 0x001F1C82u: return sub_001F1C82;
    case 0x001F24F3u: return sub_001F24F3;
    case 0x001933D0u: return sub_001933D0;
    case 0x0013E6CFu: return sub_0013E6CF;
    case 0x000E0510u: return sub_000E0510;
    case 0x001F24A8u: return sub_001F24A8;
    case 0x001ED372u: return sub_001ED372;
    case 0x001ED270u: return sub_001ED270;
    case 0x001ED3BDu: return sub_001ED3BD;
    case 0x001022D0u: return sub_001022D0;
    case 0x001023E0u: return sub_001023E0;
    case 0x00103F20u: return sub_00103F20;
    case 0x00101220u: return sub_00101220;
    case 0x00104480u: return sub_00104480;
    case 0x00104510u: return sub_00104510;
    case 0x0019693Du: return sub_0019693D;
    case 0x00196978u: return sub_00196978;
    case 0x00196993u: return sub_00196993;
    case 0x00196A02u: return sub_00196A02;
    case 0x00196A66u: return sub_00196A66;
    case 0x00196B05u: return sub_00196B05;
    case 0x00196B5Au: return sub_00196B5A;
    case 0x00196BB7u: return sub_00196BB7;
    case 0x00196C61u: return sub_00196C61;
    case 0x00196CB6u: return sub_00196CB6;
    case 0x00196CD9u: return sub_00196CD9;
    case 0x00196D45u: return sub_00196D45;
    case 0x00196DBEu: return sub_00196DBE;
    case 0x00196DDCu: return sub_00196DDC;
    case 0x00196DF0u: return sub_00196DF0;
    case 0x00196E0Fu: return sub_00196E0F;
    case 0x00196E6Au: return sub_00196E6A;
    case 0x00196E78u: return sub_00196E78;
    case 0x00196E8Au: return sub_00196E8A;
    case 0x00196EA4u: return sub_00196EA4;
    case 0x00196F35u: return sub_00196F35;
    case 0x00196F85u: return sub_00196F85;
    case 0x00196FD1u: return sub_00196FD1;
    case 0x0020B060u: return sub_0020B060;
    case 0x0020E010u: return sub_0020E010;
    case 0x001F4ADBu: return sub_001F4ADB;
    case 0x00068B50u: return sub_00068B50;
    case 0x00188750u: return sub_00188750;
    case 0x000F7180u: return sub_000F7180;
    case 0x001ECE7Eu: return sub_001ECE7E;
    case 0x001F50FFu: return sub_001F50FF;
    case 0x000F5B70u: return sub_000F5B70;
    case 0x00011F20u: return sub_00011F20;
    case 0x0003A810u: return sub_0003A810;
    case 0x00056830u: return sub_00056830;
    case 0x0007F130u: return sub_0007F130;
    case 0x000A2B70u: return sub_000A2B70;
    case 0x000C0330u: return sub_000C0330;
    case 0x000E1240u: return sub_000E1240;
    case 0x0012B690u: return sub_0012B690;
    case 0x001376B0u: return sub_001376B0;
    case 0x0007F370u: return sub_0007F370;
    case 0x000816A0u: return sub_000816A0;
    case 0x00087F30u: return sub_00087F30;
    case 0x001890A0u: return sub_001890A0;
    case 0x000121B0u: return sub_000121B0;
    case 0x00136CF0u: return sub_00136CF0;
    case 0x0008DC70u: return sub_0008DC70;
    case 0x000435D0u: return sub_000435D0;
    case 0x0007E330u: return sub_0007E330;
    case 0x000122E0u: return sub_000122E0;
    case 0x0007E4A0u: return sub_0007E4A0;
    case 0x000804D0u: return sub_000804D0;
    case 0x000806B0u: return sub_000806B0;
    case 0x00080700u: return sub_00080700;
    case 0x0007E530u: return sub_0007E530;
    case 0x00011FA0u: return sub_00011FA0;
    case 0x00011FD0u: return sub_00011FD0;
    case 0x000861B0u: return sub_000861B0;
    case 0x000818D0u: return sub_000818D0;
    case 0x00082290u: return sub_00082290;
    case 0x000822B0u: return sub_000822B0;
    case 0x000822D0u: return sub_000822D0;
    case 0x000822F0u: return sub_000822F0;
    case 0x000E0C30u: return sub_000E0C30;
    case 0x000586A0u: return sub_000586A0;
    case 0x001351B0u: return sub_001351B0;
    case 0x001351A0u: return sub_001351A0;
    case 0x001377C0u: return sub_001377C0;
    case 0x001377D0u: return sub_001377D0;
    case 0x001377E0u: return sub_001377E0;
    case 0x00135630u: return sub_00135630;
    case 0x00135660u: return sub_00135660;
    case 0x00137850u: return sub_00137850;
    case 0x001359F0u: return sub_001359F0;
    case 0x00135A20u: return sub_00135A20;
    case 0x00135A30u: return sub_00135A30;
    case 0x00135A40u: return sub_00135A40;
    case 0x00135A50u: return sub_00135A50;
    case 0x00135A60u: return sub_00135A60;
    case 0x00135A70u: return sub_00135A70;
    case 0x00135A80u: return sub_00135A80;
    case 0x00080510u: return sub_00080510;
    case 0x00081890u: return sub_00081890;
    case 0x000818A0u: return sub_000818A0;
    case 0x00012120u: return sub_00012120;
    case 0x00012130u: return sub_00012130;
    case 0x00081870u: return sub_00081870;
    case 0x00012150u: return sub_00012150;
    case 0x00081880u: return sub_00081880;
    case 0x00012170u: return sub_00012170;
    case 0x00012180u: return sub_00012180;
    case 0x00012190u: return sub_00012190;
    case 0x000121A0u: return sub_000121A0;
    case 0x000121D0u: return sub_000121D0;
    case 0x000121C0u: return sub_000121C0;
    case 0x000121E0u: return sub_000121E0;
    case 0x000121F0u: return sub_000121F0;
    case 0x00012200u: return sub_00012200;
    case 0x00012210u: return sub_00012210;
    case 0x00012220u: return sub_00012220;
    case 0x00012230u: return sub_00012230;
    case 0x00012250u: return sub_00012250;
    case 0x00012240u: return sub_00012240;
    case 0x00012260u: return sub_00012260;
    case 0x00012270u: return sub_00012270;
    case 0x0007D430u: return sub_0007D430;
    case 0x0005E640u: return sub_0005E640;
    case 0x00081790u: return sub_00081790;
    case 0x00043600u: return sub_00043600;
    case 0x001376F0u: return sub_001376F0;
    case 0x0012B6A0u: return sub_0012B6A0;
    case 0x00137810u: return sub_00137810;
    case 0x000A2E20u: return sub_000A2E20;
    case 0x00097BF0u: return sub_00097BF0;
    case 0x000A34F0u: return sub_000A34F0;
    case 0x00124F40u: return sub_00124F40;
    case 0x0010D0D0u: return sub_0010D0D0;
    case 0x0007EFF0u: return sub_0007EFF0;
    case 0x0009B7A0u: return sub_0009B7A0;
    case 0x00123F70u: return sub_00123F70;
    case 0x00101E60u: return sub_00101E60;
    case 0x00061D40u: return sub_00061D40;
    case 0x00055D20u: return sub_00055D20;
    case 0x0010EAB0u: return sub_0010EAB0;
    case 0x0010EAC0u: return sub_0010EAC0;
    case 0x0010EAD0u: return sub_0010EAD0;
    case 0x0010EAE0u: return sub_0010EAE0;
    case 0x0001AF50u: return sub_0001AF50;
    case 0x000214A0u: return sub_000214A0;
    case 0x0009ECF0u: return sub_0009ECF0;
    case 0x0010E110u: return sub_0010E110;
    case 0x0001AF80u: return sub_0001AF80;
    case 0x0012B7E0u: return sub_0012B7E0;
    case 0x00137820u: return sub_00137820;
    case 0x00135520u: return sub_00135520;
    case 0x0007F3B0u: return sub_0007F3B0;
    case 0x00087F60u: return sub_00087F60;
    case 0x00011B10u: return sub_00011B10;
    case 0x00011FE0u: return sub_00011FE0;
    case 0x00018B40u: return sub_00018B40;
    case 0x00088B40u: return sub_00088B40;
    case 0x0008C1E0u: return sub_0008C1E0;
    case 0x00011270u: return sub_00011270;
    case 0x00017470u: return sub_00017470;
    case 0x00018A10u: return sub_00018A10;
    case 0x000174F0u: return sub_000174F0;
    case 0x00018AC0u: return dah_retail_18ac0_vtable_tail;
    case 0x0012EE90u: return dah_retail_12ee90;
    case 0x00184430u: return dah_retail_184430;
    case 0x00021020u: return dah_retail_21020;
    case 0x000B6DA0u: return dah_retail_b6da0;
    case 0x000850B0u: return dah_retail_850b0;
    case 0x0009D100u: return dah_retail_9d100;
    case 0x000234E0u: return dah_retail_234e0;
    case 0x00081910u: return dah_retail_81910;
    case 0x0018DE20u: return dah_retail_18de20;
    case 0x0018FD10u: return dah_retail_18fd10;
    case 0x00194190u: return sub_00194190;
    case 0x000A1DF0u: return dah_retail_a1df0;
    case 0x000A1E80u: return sub_000A1E80;
    case 0x000A7B60u: return dah_retail_a7b60;
    case 0x000A1DD0u: return dah_retail_a1dd0;
    case 0x00026710u: return dah_retail_26710;
    case 0x000A12C0u: return dah_retail_a12c0;
    case 0x000A3750u: return dah_retail_a3750;
    case 0x00018AE0u: return sub_00018AE0;
    case 0x00017B60u: return sub_00017B60;
    case 0x00019D40u: return sub_00019D40;
    case 0x0008C370u: return sub_0008C370;
    case 0x0008C1D0u: return sub_0008C1D0;
    case 0x00088A20u: return sub_00088A20;
    case 0x00088D40u: return sub_00088D40;
    case 0x000122D0u: return sub_000122D0;
    case 0x00043610u: return sub_00043610;
    case 0x000A54A0u: return sub_000A54A0;
    case 0x000A2D70u: return sub_000A2D70;
    case 0x00043370u: return sub_00043370;
    case 0x00042C70u: return sub_00042C70;
    case 0x000A4EE0u: return sub_000A4EE0;
    case 0x000A2D50u: return sub_000A2D50;
    case 0x0016EDC0u: return sub_0016EDC0;
    case 0x0016E6A0u: return sub_0016E6A0;
    case 0x00172A50u: return sub_00172A50;
    case 0x00186130u: return sub_00186130;
    case 0x00191F80u: return sub_00191F80;
    case 0x00195BB0u: return sub_00195BB0;
    case 0x00199720u: return sub_00199720;
    case 0x001A6080u: return sub_001A6080;
    case 0x001A6EE0u: return sub_001A6EE0;
    case 0x001A72B0u: return sub_001A72B0;
    case 0x001A72A0u: return sub_001A72A0;
    case 0x0011A110u: return sub_0011A110;
    case 0x0015D220u: return sub_0015D220;
    case 0x000E6770u: return sub_000E6770;
    case 0x000E8270u: return sub_000E8270;
    case 0x000FFC60u: return sub_000FFC60;
    case 0x00100AC0u: return sub_00100AC0;
    case 0x00100B20u: return sub_00100B20;
    case 0x000E0C20u: return sub_000E0C20;
    case 0x000139C0u: return sub_000139C0;
    case 0x0003C650u: return sub_0003C650;
    case 0x00012A70u: return sub_00012A70;
    case 0x00013AB0u: return sub_00013AB0;
    case 0x00016E30u: return sub_00016E30;
    case 0x00033D20u: return sub_00033D20;
    case 0x0003B750u: return sub_0003B750;
    case 0x0004E090u: return sub_0004E090;
    case 0x001444E0u: return sub_001444E0;
    case 0x0015D0C0u: return sub_0015D0C0;
    case 0x00163630u: return sub_00163630;
    case 0x00013EA0u: return sub_00013EA0;
    case 0x000152D0u: return sub_000152D0;
    case 0x00033350u: return sub_00033350;
    case 0x00015570u: return sub_00015570;
    case 0x00023470u: return sub_00023470;
    case 0x00025D50u: return sub_00025D50;
    case 0x00028560u: return sub_00028560;
    case 0x00029480u: return sub_00029480;
    case 0x00059260u: return sub_00059260;
    case 0x000592E0u: return sub_000592E0;
    case 0x0005F580u: return sub_0005F580;
    case 0x00098EC0u: return sub_00098EC0;
    case 0x000A2B80u: return sub_000A2B80;
    case 0x000AC2E0u: return sub_000AC2E0;
    case 0x000E7DC0u: return sub_000E7DC0;
    case 0x000F59E0u: return sub_000F59E0;
    case 0x000FC300u: return sub_000FC300;
    case 0x0011DDB0u: return sub_0011DDB0;
    case 0x00128A60u: return sub_00128A60;
    case 0x00136100u: return sub_00136100;
    case 0x000299D0u: return sub_000299D0;
    case 0x0009A970u: return sub_0009A970;
    case 0x0009F790u: return sub_0009F790;
    case 0x000ABDE0u: return sub_000ABDE0;
    case 0x000AB9C0u: return sub_000AB9C0;
    case 0x0011FA30u: return sub_0011FA30;
    case 0x0013FF59u: return sub_0013FF59;
    case 0x00143689u: return sub_00143689;
    case 0x001EF162u: return sub_001EF162;
    case 0x001EE1F9u: return sub_001EE1F9;
    case 0x0008A3F0u: return sub_0008A3F0;
    case 0x0008BC00u: return sub_0008BC00;
    case 0x001EC7B9u: return sub_001EC7B9;
    case 0x001F49F9u: return sub_001F49F9;
    case 0x001EE1DEu: return sub_001EE1DE;
    case 0x001F514Eu: return sub_001F514E;
    case 0x001EF685u: return sub_001EF685;
    case 0x00196E42u: return sub_00196E42;
    case 0x00196E56u: return sub_00196E56;
    case 0x00196D92u: return sub_00196D92;
    case 0x00196DA7u: return sub_00196DA7;
    case 0x00196D66u: return sub_00196D66;
    case 0x00196C0Cu: return sub_00196C0C;
    case 0x00196D04u: return sub_00196D04;
    case 0x00196AB8u: return sub_00196AB8;
    case 0x00139A80u: return sub_00139A80;
    case 0x0005A530u: return sub_0005A530;
    case 0x0005A540u: return sub_0005A540;
    case 0x000E09F0u: return sub_000E09F0;
    case 0x00181780u: return sub_00181780;
    case 0x000E32E0u: return sub_000E32E0;
    case 0x000DB750u: return sub_000DB750;
    case 0x000F5700u: return sub_000F5700;
    case 0x000F32E0u: return sub_000F32E0;
    case 0x000E4E50u: return sub_000E4E50;
    case 0x00081300u: return sub_00081300;
    case 0x000838F0u: return sub_000838F0;
    case 0x000F85E0u: return sub_000F85E0;
    case 0x000FEA90u: return sub_000FEA90;
    case 0x00070610u: return sub_00070610;
    case 0x0005B8D0u: return sub_0005B8D0;
    case 0x0004F540u: return sub_0004F540;
    case 0x000E6E20u: return sub_000E6E20;
    case 0x00195BC7u: return sub_00195BC7;
    case 0x001EC7ACu: return sub_001EC7AC;
    case 0x001ECE37u: return sub_001ECE37;
    case 0x001F4FE5u: return sub_001F4FE5;
    case 0x002206E2u: return sub_002206E2;
    case 0x0021FA38u: return sub_0021FA38;
    case 0x0021FADBu: return sub_0021FADB;
    }
    return NULL;
}

void recomp_icall_fail_log(uint32_t va)
{
    struct fail_site { uint32_t va, ret; uint64_t count; };
    static RECOMP_TLS struct fail_site sites[64];
    static RECOMP_TLS unsigned used;
    uint32_t guest_return = MEM32(g_esp);
    /* Once-only diagnostic: enumerate interface tables referenced by the live
     * game arena at the first missing method, before its fallback can cascade. */
    { static int captured;
      if (!captured && getenv("DAH_LIVE_VTABLE_TRACE") && va >= 0x11000u && va < 0x220000u) {
        uint32_t seen[1024]; unsigned count = 0;
        uint32_t manager = MEM32(0x250A9Cu);
        captured = 1;
        if (manager >= 0x250000u && manager < 0x300000u) {
          uint32_t begin = MEM32(manager + 0x24), end = MEM32(manager + 0x28);
          if (begin >= 0xF80000u && begin < end && end <= 0x08000000u) {
            for (uint32_t address = begin; address + 4u <= end; address += 4u) {
              uint32_t table = MEM32(address);
              if ((table & 3u) || table < 0x225C00u || table >= 0x248000u) continue;
              uint32_t a=MEM32(table),b=MEM32(table+4),c=MEM32(table+8);
              if(a<0x11000u||a>=0x220000u||b<0x11000u||b>=0x220000u||c<0x11000u||c>=0x220000u)continue;
              unsigned j; for(j=0;j<count;j++)if(seen[j]==table)break;
              if(j==count&&count<1024){seen[count++]=table;fprintf(stderr,"[DAH-LIVE-VTABLE] table=%08X object=%08X\n",table,address);}
            }
          }
        }
      }
    }
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
