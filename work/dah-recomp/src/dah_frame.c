#include <windows.h>
#include <mmsystem.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <dxgi.h>
#include "d3d8_xbox.h"
#include "nv2a_pgraph_d3d11.h"
#include "dah_frame.h"
#include "dah_retail_ring.h"
#include "dah_timing.h"

uint64_t dah_read_tsc(void)
{
    LARGE_INTEGER counter, frequency;
    const uint64_t xbox_hz = 733333333u;
    QueryPerformanceCounter(&counter);
    QueryPerformanceFrequency(&frequency);
    /* Split integer seconds and remainder to avoid long-uptime overflow. */
    return ((uint64_t)counter.QuadPart / (uint64_t)frequency.QuadPart) * xbox_hz +
           (((uint64_t)counter.QuadPart % (uint64_t)frequency.QuadPart) * xbox_hz) /
               (uint64_t)frequency.QuadPart;
}

extern ptrdiff_t g_xbox_mem_offset;
extern void dah_host_set_render_activity(int real_draw);
extern void dah_console_poll_game_thread(void);
extern void d3d8_ClearFrameDiagnostic(void);
extern int d3d8_DrawHostFrameBgra(const void *pixels, UINT width, UINT height,
                                  UINT pitch);

/* A deliberately opt-in presentation probe.  The retail title currently
 * reaches the front-end without submitting UI geometry, so this lets us put
 * a verified frame from the shipped saucer movie on the same D3D target.  It
 * is kept out of the default path so it cannot alter retail rendering. */
static int host_frame_attempted;
static int host_frame_enabled;
static int host_frame_ready;
static uint8_t *host_frame_pixels;

static FILE *host_frame_open(void)
{
    FILE *file = fopen("movies\\saucer_frame_030.raw", "rb");
    if (!file) {
        char module_path[MAX_PATH];
        DWORD length = GetModuleFileNameA(NULL, module_path,
                                          (DWORD)sizeof(module_path));
        if (length && length < sizeof(module_path)) {
            char *slash = strrchr(module_path, '\\');
            if (slash) {
                FILE *fallback;
                slash[1] = '\0';
                strcat_s(module_path, sizeof(module_path),
                         "movies\\saucer_frame_030.raw");
                fallback = fopen(module_path, "rb");
                if (fallback) return fallback;
            }
        }
    }
    return file;
}

static int host_frame_load(void)
{
    FILE *file;
    size_t expected = 640u * 448u * 4u;
    size_t got;
    const char *setting;

    if (host_frame_attempted) return host_frame_ready;
    host_frame_attempted = 1;
    setting = getenv("DAH_HOST_FRAME");
    host_frame_enabled = setting && atoi(setting) != 0;
    if (!host_frame_enabled) return 0;

    file = host_frame_open();
    if (!file) {
        fprintf(stderr, "[DAH-HOST-FRAME] source missing\n");
        fflush(stderr);
        return 0;
    }
    host_frame_pixels = (uint8_t *)malloc(expected);
    if (!host_frame_pixels) {
        fclose(file);
        fprintf(stderr, "[DAH-HOST-FRAME] allocation failed bytes=%zu\n",
                expected);
        fflush(stderr);
        return 0;
    }
    got = fread(host_frame_pixels, 1, expected, file);
    fclose(file);
    if (got != expected) {
        free(host_frame_pixels);
        host_frame_pixels = NULL;
        fprintf(stderr, "[DAH-HOST-FRAME] short read bytes=%zu expected=%zu\n",
                got, expected);
        fflush(stderr);
        return 0;
    }
    host_frame_ready = 1;
    fprintf(stderr, "[DAH-HOST-FRAME] loaded source=saucer_frame_030.raw size=%zux%zu\n",
            (size_t)640, (size_t)448);
    fflush(stderr);
    return 1;
}

/* Retail DAH1's world update at 001049F0 uses a fixed timestep by default:
 * 1/(renderer+238 ? 60 : 50), multiplied by max(renderer+27C, 1).
 * Its renderer rate setter at 000E0510 supports divisors 1 and 2. Pace that
 * existing policy at the full main-loop boundary; a pushbuffer becoming full
 * is not a frame boundary. No alpha game state or timestep override is used. */
typedef struct DahFrameState {
    DWORD thread_id;
    LARGE_INTEGER frequency;
    double next_start;
    double report_start;
    double last_start;
    double frame_start;
    double period;
    double simulation_seconds;
    double interval_sum;
    double interval_min;
    double interval_max;
    double interval_samples[1024];
    uint32_t interval_count;
    uint64_t frames;
    uint64_t draw_frames;
    uint64_t host_probe_frames;
    uint64_t visible_presents;
    uint64_t occluded_presents;
    uint64_t failed_presents;
    uint64_t late_frames;
    uint64_t invalid_steps;
    uint32_t hz;
    uint32_t divisor;
    uint32_t renderer;
    uint32_t world;
    uint32_t draws_before;
    uint32_t timer_resolution;
    uint8_t variable_step;
    int active;
} DahFrameState;

static DahFrameState frame;
/* Windows can coarsen Sleep for background windows. A high-resolution
 * waitable timer waits for the same QPC deadline without altering game time. */
static HANDLE dah_frame_wait_timer;
#ifndef CREATE_WAITABLE_TIMER_HIGH_RESOLUTION
#define CREATE_WAITABLE_TIMER_HIGH_RESOLUTION 0x00000002
#endif

static int compare_interval(const void *left, const void *right)
{
    const double a = *(const double *)left;
    const double b = *(const double *)right;
    return (a > b) - (a < b);
}

static int guest_range(uint32_t address, uint32_t size)
{
    return address >= 0x10000u && address < 0x04000000u &&
           size <= 0x04000000u - address;
}

static uint32_t guest_u32(uint32_t address)
{
    return *(const uint32_t *)((uintptr_t)g_xbox_mem_offset + address);
}

static uint8_t guest_u8(uint32_t address)
{
    return *(const uint8_t *)((uintptr_t)g_xbox_mem_offset + address);
}

static int guest_text_is(uint32_t address, const char *expected)
{
    size_t length = strlen(expected);
    if (!guest_range(address, (uint32_t)length + 1u)) return 0;
    return memcmp((const void *)((uintptr_t)g_xbox_mem_offset + address),
                  expected, length + 1u) == 0;
}

/* Keep the last loading image on screen while Farm commits all three of its
 * retail packages. Once the active backend is complete, render a short hidden
 * warm-up so the first newly presented site frame already has its initial GPU
 * resources, Crypto, camera, and world installed. Simulation is never paused. */
static int dah_farm_presentation_hold(int real_draw)
{
    enum { IDLE, HOLDING, REVEALED };
    static int state;
    static unsigned warm_frames;
    static int visual_ready;
    static unsigned blank_samples;
    static int transition_blank_seen;
    const uint32_t driver = 0x0025B1D0u;
    uint32_t current, pending, system, player, actor, camera, world;
    int current_farm, pending_farm, ready;

    if (guest_u32(driver) != 0x0022B510u) return 0;
    current = guest_u32(driver + 0x4A28u);
    pending = guest_u32(driver + 0x4A2Cu);
    current_farm = guest_range(current, 0x610u) &&
        guest_text_is(current + 0x50Cu, "blocks\\sites\\farm");
    pending_farm = guest_range(pending, 0x610u) &&
        guest_text_is(pending + 0x50Cu, "blocks\\sites\\farm");

    if (state == IDLE && (current_farm || pending_farm)) {
        state = HOLDING;
        warm_frames = 0;
        visual_ready = 0;
        blank_samples = 0;
        transition_blank_seen = 0;
        fprintf(stderr, "[DAH-FARM-PRELOAD] hold=1 current=%08X pending=%08X\n",
                current, pending);
    }
    if (state == REVEALED) {
        if (!current_farm && !pending_farm) state = IDLE;
        return 0;
    }
    if (state != HOLDING) return 0;
    if (!current_farm && !pending_farm) {
        state = IDLE;
        warm_frames = 0;
        visual_ready = 0;
        blank_samples = 0;
        transition_blank_seen = 0;
        return 0;
    }

    system = guest_u32(0x0025FCECu);
    player = guest_range(system, 0x3Cu) ? guest_u32(system + 0x38u) : 0u;
    actor = guest_range(player, 0x3Cu) ? guest_u32(player + 0x38u) : 0u;
    camera = guest_u32(0x00250E60u);
    world = guest_u32(0x00286768u);
    ready = current_farm && pending == 0u && guest_u32(current + 0x10u) == 22u &&
            guest_range(actor, 0x158u) && guest_u32(actor) == 0x0022C9F8u &&
            guest_range(camera, 0xF0u) && guest_range(world, 0x10u) && real_draw;
    if (ready) ++warm_frames;
    else warm_frames = 0;

    if (warm_frames >= 12u && !visual_ready && (warm_frames % 3u) == 0u) {
        int content = d3d8_PresentableHasVisualContent();
        if (content == 0) {
            if (blank_samples < 4u) ++blank_samples;
            if (blank_samples >= 4u) transition_blank_seen = 1;
        } else if (content > 0) {
            if (transition_blank_seen) visual_ready = 1;
            else blank_samples = 0;
        }
    }
    if ((warm_frames >= 12u && visual_ready) || warm_frames >= 360u) {
        state = REVEALED;
        fprintf(stderr,
                "[DAH-FARM-PRELOAD] hold=0 backend=%08X state=22 warm-frames=%u blank-seen=%d visual-ready=%d actor=%08X camera=%08X world=%08X\n",
                current, warm_frames, transition_blank_seen, visual_ready, actor, camera, world);
        return 0;
    }
    return 1;
}

static void guest_write_u32(uint32_t address, uint32_t value)
{
    *(uint32_t *)((uintptr_t)g_xbox_mem_offset + address) = value;
}

static double clock_seconds(void)
{
    LARGE_INTEGER now;
    QueryPerformanceCounter(&now);
    return (double)now.QuadPart / (double)frame.frequency.QuadPart;
}

static double dah_mid_ring_ms;
static uint64_t dah_mid_ring_count;
static uint64_t dah_mid_ring_dwords;

static double dah_guest_render_ms;
static double dah_render_queue_ms;
static double dah_render_post_ms;

double dah_frame_profile_now(void)
{
    return clock_seconds();
}

void dah_frame_record_ring_submit(double start_seconds, uint32_t dwords)
{
    if (!frame.active || GetCurrentThreadId() != frame.thread_id) return;
    dah_mid_ring_ms += (clock_seconds() - start_seconds) * 1000.0;
    dah_mid_ring_count++;
    dah_mid_ring_dwords += dwords;
}

void dah_frame_record_guest_render(double start_seconds)
{
    if (!frame.active || GetCurrentThreadId() != frame.thread_id) return;
    dah_guest_render_ms += (clock_seconds() - start_seconds) * 1000.0;
}

void dah_frame_record_render_stage(unsigned stage, double start_seconds)
{
    if (!frame.active || GetCurrentThreadId() != frame.thread_id) return;
    if (stage == 0) dah_render_queue_ms += (clock_seconds() - start_seconds) * 1000.0;
    if (stage == 1) dah_render_post_ms += (clock_seconds() - start_seconds) * 1000.0;
}

static void shutdown_timer(void)
{
    if (dah_frame_wait_timer) CloseHandle(dah_frame_wait_timer);
    dah_frame_wait_timer = NULL;
    if (frame.timer_resolution) timeEndPeriod(frame.timer_resolution);
}

static void sample_policy(void)
{
    static int rate_override = -1;
    uint32_t renderer = guest_u32(0x00250E60u);
    uint32_t world = guest_u32(0x00286768u);
    uint32_t hz = 60u;
    uint32_t divisor = 1u;
    uint8_t variable_step = 0;

    if (rate_override < 0) {
        const char *value = getenv("DAH_FPS");
        int parsed = value ? atoi(value) : 0;
        rate_override = (parsed == 60) ? 60 : 30;
    }

    if (guest_range(renderer, 0x2CCu)) {
        hz = guest_u32(renderer + 0x238u) ? 60u : 50u;
        divisor = guest_u32(renderer + 0x27Cu);
        if (divisor < 1u || divisor > 2u) divisor = 1u;
    } else {
        renderer = 0;
    }
    if (guest_range(world, 0x303Eu)) {
        variable_step = guest_u8(world + 0x303Du) != 0;
    } else {
        world = 0;
    }

    if (rate_override != 0 && renderer != 0) {
        uint32_t requested_divisor = rate_override == 30u ? 2u : 1u;
        divisor = requested_divisor;
        if (guest_u32(renderer + 0x27Cu) != requested_divisor)
            guest_write_u32(renderer + 0x27Cu, requested_divisor);
    }

    if (hz != frame.hz || divisor != frame.divisor ||
        renderer != frame.renderer || variable_step != frame.variable_step) {
        fprintf(stderr,
                "[DAH-FRAME-POLICY] renderer=%08X world=%08X refresh=%u divisor=%u target=%.3f update-mode=%s interval=%08X\n",
                renderer, world, hz, divisor, (double)hz / divisor,
                variable_step ? "measured-delta" : "retail-fixed-step",
                renderer ? guest_u32(renderer + 0x2C8u) : 0u);
        fflush(stderr);
    }
    frame.renderer = renderer;
    frame.world = world;
    frame.hz = hz;
    frame.divisor = divisor;
    frame.variable_step = variable_step;
    frame.period = (double)divisor / (double)hz;
}

void dah_frame_begin(void)
{
    double now;
    PgraphD3D11Stats stats;

    if (!frame.thread_id) {
        frame.thread_id = GetCurrentThreadId();
        {
            BOOL process_priority = SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS);
            BOOL thread_priority = SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_HIGHEST);
            fprintf(stderr, "[DAH-FRAME-PRIORITY] process-high=%d thread-highest=%d error=%lu\n",
                    process_priority != FALSE, thread_priority != FALSE,
                    (unsigned long)GetLastError());
        }
        QueryPerformanceFrequency(&frame.frequency);
        if (timeBeginPeriod(1u) == TIMERR_NOERROR) frame.timer_resolution = 1u;
        dah_frame_wait_timer = CreateWaitableTimerExW(NULL, NULL,
                CREATE_WAITABLE_TIMER_HIGH_RESOLUTION, TIMER_ALL_ACCESS);
        fprintf(stderr, "[DAH-FRAME-WAIT] high-resolution-timer=%d\n", dah_frame_wait_timer != NULL);
        atexit(shutdown_timer);
        now = clock_seconds();
        frame.next_start = now;
        frame.report_start = now;
        frame.interval_min = 1.0e30;
    }
    if (GetCurrentThreadId() != frame.thread_id || frame.active) return;

    sample_policy();
    now = clock_seconds();
    /* DAH_FRAME_TURBO (internal test runs only): skip real-time pacing so
     * frames run back-to-back as fast as the CPU can compute them, instead
     * of waiting out each 1/30 or 1/60 second. This does not change what is
     * simulated: frame.period and the per-tick delta fed to retail-fixed-step
     * gameplay logic below are untouched, so each dah_frame_begin() call
     * still represents exactly the same fixed game-time slice -- the game
     * just gets there faster in real time. Two things this does NOT speed
     * up: Bink movie/cutscene playback, which is paced by a separate
     * QPC-derived Xbox-TSC clock (dah_read_tsc), not this loop; and the rare
     * "measured-delta" update mode (see sample_policy's variable_step),
     * which reads real elapsed time directly and would see it near zero --
     * harmless for testing (that state just appears to stall/slow-motion,
     * nothing corrupts), but a real reason this stays internal-only. */
    {
        static int turbo = -1;
        if (turbo < 0) {
            const char *internal = getenv("DAH_INTERNAL_RUN");
            const char *setting = getenv("DAH_FRAME_TURBO");
            turbo = internal && !strcmp(internal, "1") &&
                    setting && !strcmp(setting, "1");
            if (turbo) fprintf(stderr, "[DAH-FRAME-TURBO] real-time pacing disabled for this internal run\n");
        }
        if (!turbo) {
            while (now < frame.next_start) {
                double remaining_ms = (frame.next_start - now) * 1000.0;
                if (remaining_ms > 2.0) {
                    LARGE_INTEGER due;
                    due.QuadPart = -(LONGLONG)((remaining_ms - 1.0) * 10000.0);
                    if (!dah_frame_wait_timer ||
                        !SetWaitableTimer(dah_frame_wait_timer, &due, 0, NULL, NULL, FALSE) ||
                        WaitForSingleObject(dah_frame_wait_timer, INFINITE) != WAIT_OBJECT_0)
                        Sleep((DWORD)(remaining_ms - 1.0));
                } else SwitchToThread();
                now = clock_seconds();
            }
        }
    }

    /* Long loads must not cause a burst of fixed simulation steps to catch up.
     * Re-anchor after a missed deadline and report it as a slow frame. */
    if (now - frame.next_start > frame.period * 0.5) {
        frame.late_frames++;
        frame.next_start = now;
    }
    frame.next_start += frame.period;
    if (frame.last_start != 0) {
        double interval = now - frame.last_start;
        frame.interval_sum += interval;
        if (frame.interval_count < 1024u)
            frame.interval_samples[frame.interval_count++] = interval;
        if (interval < frame.interval_min) frame.interval_min = interval;
        if (interval > frame.interval_max) frame.interval_max = interval;
    }
    frame.last_start = now;
    frame.frame_start = now;
    pgraph_d3d11_get_stats(&stats);
    frame.draws_before = stats.draw_calls;
    frame.active = 1;
    dah_console_poll_game_thread();
}

static DahRetailRingCursor dah_retail_cursor;
void dah_retail_pushbuffer_reset(void)
{
    dah_retail_ring_reset(&dah_retail_cursor);
}
static void dah_retail_submit_span(void *opaque, uint32_t start, uint32_t dwords)
{
    (void)opaque;
    pgraph_d3d11_submit_pushbuffer(
        (const uint32_t *)((uintptr_t)g_xbox_mem_offset + start), dwords);
}
uint32_t dah_retail_pushbuffer_commit(uint32_t device, uint32_t put)
{
    uint32_t base = 0u, end = 0u, submitted = UINT32_MAX;
    if (guest_range(device, 0x2Cu)) {
        base = guest_u32(device + 0x24u);
        end = guest_u32(device + 0x28u);
        if (end > base && guest_range(base, end - base))
            submitted = dah_retail_ring_commit(&dah_retail_cursor, device, base, end,
                                              put, dah_retail_submit_span, NULL);
    }
    if (submitted == UINT32_MAX) {
        static unsigned rejected;
        if (rejected++ < 12u)
            fprintf(stderr,"[DAH-RETAIL-PUT] invalid/rewound device=%08X base=%08X end=%08X put=%08X consumed=%08X\n",
                    device,base,end,put,dah_retail_cursor.next);
    }
    return submitted;
}

static void drain_retail_pushbuffer(void)
{
    uint32_t device = guest_u32(0x001E8968u);
    uint32_t base, current, end;
    if (!guest_range(device, 0x2Cu)) return;
    current = guest_u32(device);
    base = guest_u32(device + 0x24u);
    end = guest_u32(device + 0x28u);
    if (current <= base || current > end || !guest_range(base, end - base))
        return;
    if (dah_retail_pushbuffer_commit(device, current) == UINT32_MAX) return;
    guest_write_u32(device, base);
    dah_retail_pushbuffer_reset();
}

void dah_frame_end(void)
{
    PgraphD3D11Stats stats;
    double now, elapsed;
    double phase_start, present_start;
    static double logic_ms, render_ms, present_ms;
    HRESULT result;
    int host_draw = 0;
    int real_draw;
    if (!frame.active || GetCurrentThreadId() != frame.thread_id) return;

    phase_start=clock_seconds();
    logic_ms += (phase_start-frame.frame_start)*1000.0;
    drain_retail_pushbuffer();
    pgraph_d3d11_flush();
    pgraph_d3d11_get_stats(&stats);
    frame.frames++;
    if (stats.draw_calls != frame.draws_before) frame.draw_frames++;
    if (stats.draw_calls == frame.draws_before && host_frame_load()) {
        host_draw = d3d8_DrawHostFrameBgra(host_frame_pixels, 640u, 448u,
                                           640u * 4u);
        if (host_draw) frame.host_probe_frames++;
    }
    real_draw = (stats.draw_calls != frame.draws_before) || host_draw;
    if (!real_draw)
        d3d8_ClearFrameDiagnostic();

    /* QPC pacing owns the title's 50/60 Hz timing, independent of a PC
     * monitor's refresh rate and of DXGI occlusion behavior. */
    d3d8_SetPresentationHold(dah_farm_presentation_hold(real_draw));
    present_start=clock_seconds();
    render_ms += (present_start-phase_start)*1000.0;
    result = d3d8_PresentFrameWithInterval(0u);
    present_ms += (clock_seconds()-present_start)*1000.0;
    if (result == S_OK && real_draw) dah_host_set_render_activity(1);
    if (result == DXGI_STATUS_OCCLUDED) frame.occluded_presents++;
    else if (SUCCEEDED(result)) frame.visible_presents++;
    else frame.failed_presents++;

    if (frame.world) {
        float step = *(const float *)((uintptr_t)g_xbox_mem_offset +
                                      frame.world + 0x10u);
        if (isfinite(step) && step >= 0.0f && step <= 0.2f)
            frame.simulation_seconds += step;
        else frame.invalid_steps++;
    }
    now = clock_seconds();
    elapsed = now - frame.report_start;
    if (elapsed >= 5.0) {
        double p95 = 0.0, p99 = 0.0;
        if (frame.interval_count) {
            qsort(frame.interval_samples, frame.interval_count,
                  sizeof(frame.interval_samples[0]), compare_interval);
            p95 = frame.interval_samples[(95u * frame.interval_count + 99u) / 100u - 1u];
            p99 = frame.interval_samples[(99u * frame.interval_count + 99u) / 100u - 1u];
        }
        fprintf(stderr,
                "[DAH-FRAME] seconds=%.3f target=%.3f loop-fps=%.3f draw-frame-fps=%.3f frames=%llu draw-frames=%llu draws-total=%u presents=%llu occluded=%llu failed=%llu interval-ms=%.3f/%.3f/%.3f late=%llu simulation-seconds=%.6f wall-ratio=%.6f invalid-steps=%llu host-probe-frames=%llu interval-p95-ms=%.3f interval-p99-ms=%.3f interval-samples=%u\n",
                elapsed, (double)frame.hz / frame.divisor,
                frame.frames / elapsed, frame.draw_frames / elapsed,
                (unsigned long long)frame.frames,
                (unsigned long long)frame.draw_frames, stats.draw_calls,
                (unsigned long long)frame.visible_presents,
                (unsigned long long)frame.occluded_presents,
                (unsigned long long)frame.failed_presents,
                frame.interval_min < 1.0e20 ? frame.interval_min * 1000.0 : 0.0,
                frame.interval_count ? frame.interval_sum * 1000.0 / frame.interval_count : 0.0,
                frame.interval_max * 1000.0,
                (unsigned long long)frame.late_frames,
                frame.simulation_seconds, frame.simulation_seconds / elapsed,
                (unsigned long long)frame.invalid_steps,
                (unsigned long long)frame.host_probe_frames,
                p95 * 1000.0, p99 * 1000.0, frame.interval_count);
        fflush(stderr);
        fprintf(stderr, "[DAH-FRAME-PHASE] frames=%llu logic-ms=%.3f drain-ms=%.3f present-ms=%.3f\n",(unsigned long long)frame.frames,logic_ms/frame.frames,render_ms/frame.frames,present_ms/frame.frames);
        fprintf(stderr, "[DAH-FRAME-LOGIC-SPLIT] frames=%llu guest-ms=%.3f render-phase-ms=%.3f queue-ms=%.3f post-ms=%.3f mid-ring-ms=%.3f mid-ring-count=%llu mid-ring-dwords=%llu\n",
                (unsigned long long)frame.frames,
                (logic_ms-dah_mid_ring_ms)/frame.frames,
                dah_guest_render_ms/frame.frames,
                dah_render_queue_ms/frame.frames,
                dah_render_post_ms/frame.frames,
                dah_mid_ring_ms/frame.frames,
                (unsigned long long)dah_mid_ring_count,
                (unsigned long long)dah_mid_ring_dwords);
        dah_mid_ring_ms=0;
        dah_guest_render_ms=0;
        dah_render_queue_ms=dah_render_post_ms=0;
        dah_mid_ring_count=dah_mid_ring_dwords=0;
        logic_ms=render_ms=present_ms=0;
        frame.report_start = now;
        frame.frames = frame.draw_frames = 0;
        frame.host_probe_frames = 0;
        frame.visible_presents = frame.occluded_presents = frame.failed_presents = 0;
        frame.late_frames = frame.invalid_steps = 0;
        frame.simulation_seconds = frame.interval_sum = frame.interval_max = 0;
        frame.interval_min = 1.0e30;
        frame.interval_count = 0;
    }
    frame.active = 0;
}
