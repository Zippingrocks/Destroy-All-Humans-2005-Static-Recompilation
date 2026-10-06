#include <windows.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tlhelp32.h>
#include <io.h>
#include <xbox/xboxrecomp.h>
#include "dah_frame.h"
#include "dah_crashlog.h"
#include "dah_event_trace.h"
#include "dah_renderdoc.h"

#define DAH_ENTRY_POINT 0x000B27BBu
#define WM_DAH_RENDERER_READY (WM_APP + 0x52u)

typedef void (*recomp_func_t)(void);
extern recomp_func_t recomp_lookup(uint32_t xbox_va);
extern int recomp_dispatch_init(void);
extern RECOMP_TLS uint32_t g_eax, g_ecx, g_edx, g_esp;
extern RECOMP_TLS uint32_t g_ebx, g_esi, g_edi, g_ebp;

static HWND g_game_window;
static HWND g_game_overlay;
static HANDLE g_window_ready_event;
static volatile LONG g_window_init_result;
static volatile LONG g_dah_has_real_draw;
static uint32_t g_dah_ltcg_ring;
static uintptr_t g_kpcr_watch_base;
static RECOMP_TLS int g_kpcr_watch_rearm;

#include "dah_console.h"

static uint64_t dah_hash_file_w(const wchar_t *path)
{
    uint64_t hash = 1469598103934665603ull;
    unsigned char buffer[64u * 1024u];
    FILE *file = _wfopen(path, L"rb");
    size_t count;
    if (!file) return 0;
    while ((count = fread(buffer, 1, sizeof(buffer), file)) != 0) {
        for (size_t i = 0; i < count; ++i) {
            hash ^= buffer[i];
            hash *= 1099511628211ull;
        }
    }
    fclose(file);
    return hash;
}

static void dah_write_json_string(FILE *file, const char *text)
{
    fputc('"', file);
    for (; text && *text; ++text) {
        unsigned char value = (unsigned char)*text;
        if (value == '"' || value == '\\') fputc('\\', file);
        if (value >= 32u) fputc(value, file);
    }
    fputc('"', file);
}

static void dah_write_run_manifest(const char *run_id, const char *started_utc,
                                   uint64_t executable_hash,
                                   const char *log_path, const char *event_path,
                                   const char *status)
{
    FILE *file = fopen("dah_current_run.json", "wb");
    if (!file) return;
    fprintf(file, "{\n  \"schema\": 1,\n  \"runId\": ");
    dah_write_json_string(file, run_id);
    fprintf(file, ",\n  \"pid\": %lu,\n  \"startedUtc\": ", GetCurrentProcessId());
    dah_write_json_string(file, started_utc);
    fprintf(file, ",\n  \"executableFnv1a64\": \"%016llX\",\n  \"logPath\": ",
            (unsigned long long)executable_hash);
    dah_write_json_string(file, log_path);
    fprintf(file, ",\n  \"eventTracePath\": ");
    dah_write_json_string(file, event_path);
    fprintf(file, ",\n  \"status\": ");
    dah_write_json_string(file, status);
    fprintf(file, "\n}\n");
    fclose(file);
}


static int dah_internal_run(void)
{
    static int internal_run = -1;
    if (internal_run < 0) {
        const char *setting = getenv("DAH_INTERNAL_RUN");
        internal_run = setting && strcmp(setting, "1") == 0;
    }
    return internal_run;
}

/* A test-only presentation option. It deliberately does not change the
 * normal input initialization, save paths, or renderer/runtime defaults. */
static int dah_test_window_hidden(void)
{
    static int hidden = -1;
    if (hidden < 0) {
        const char *value = getenv("DAH_TEST_WINDOW_HIDDEN");
        hidden = value && !strcmp(value, "1");
    }
    return hidden;
}

static void dah_report_startup_error(const char *message, UINT flags)
{
    fprintf(stderr, "[DAH-STARTUP] %s\n", message);
    fflush(stderr);
    if (!dah_internal_run() && !dah_test_window_hidden())
        MessageBoxA(NULL, message, "Destroy All Humans! Recomp", flags);
}

/* Windows 11 otherwise paints the resize border from transient active-window
 * state.  The game presents a fixed 640x480 client surface, so keep the
 * nonclient edge a stable black without changing the title bar or client. */
static void dah_set_stable_window_border(HWND hwnd)
{
    typedef HRESULT (WINAPI *DwmSetWindowAttributeFn)(HWND, DWORD, LPCVOID, DWORD);
    HMODULE dwm = LoadLibraryA("dwmapi.dll");
    if (dwm) {
        DwmSetWindowAttributeFn set_attribute =
            (DwmSetWindowAttributeFn)GetProcAddress(dwm, "DwmSetWindowAttribute");
        if (set_attribute) {
            const DWORD dwmwa_border_color = 34u;
            const COLORREF black = RGB(0, 0, 0);
            set_attribute(hwnd, dwmwa_border_color, &black, sizeof(black));
        }
        FreeLibrary(dwm);
    }
}
static void position_diagnostic_overlay(void)
{
    RECT rect;
    static int logged;
    if (!g_game_window || !g_game_overlay || !GetWindowRect(g_game_window, &rect))
        return;
    SetWindowPos(g_game_overlay, HWND_TOP,
                 rect.left, rect.top,
                 rect.right - rect.left, rect.bottom - rect.top,
                 SWP_NOACTIVATE | SWP_SHOWWINDOW);
    if (!logged++) {
        fprintf(stderr, "[DAH-WINDOW] parent rect=%ld,%ld-%ld,%ld style=%08lX exstyle=%08lX\n",
                (long)rect.left, (long)rect.top, (long)rect.right, (long)rect.bottom,
                (unsigned long)GetWindowLongA(g_game_window, GWL_STYLE),
                (unsigned long)GetWindowLongA(g_game_window, GWL_EXSTYLE));
        fflush(stderr);
    }
}

/* Keep a visible, honest diagnostic surface until the retail renderer
 * submits its first real primitive.  This is not game art: it prevents a
 * missing UI/movie path from looking identical to a dead window. */
void dah_host_set_render_activity(int real_draw)
{
    if (real_draw && InterlockedCompareExchange(&g_dah_has_real_draw, 1, 0) == 0) {
        if (g_game_overlay)
            PostMessageA(g_game_overlay, WM_APP + 0x51u, 0, 0);
    }
    if (g_game_window && !InterlockedCompareExchange(&g_dah_has_real_draw, 0, 0))
        InvalidateRect(g_game_window, NULL, FALSE);
}

void dah_reset_ltcg_context(void)
{
    const uint32_t context = 0x001E8970u;
    const uint32_t ring_size = 512u * 1024u;
    ptrdiff_t memory_offset = xbox_GetMemoryOffset();
    uint32_t *global_device =
        (uint32_t *)((uintptr_t)memory_offset + 0x001E8968u);
    uint32_t *device = (uint32_t *)((uintptr_t)memory_offset + context);

    dah_retail_pushbuffer_reset();
    memset(device, 0, 0x928u * sizeof(uint32_t));
    *global_device = context;
    device[0x00 / 4] = g_dah_ltcg_ring;
    device[0x04 / 4] = g_dah_ltcg_ring + 0x8000u - 516u;
    device[0x24 / 4] = g_dah_ltcg_ring;
    device[0x28 / 4] = g_dah_ltcg_ring + ring_size;
    /* Retail's device-submit path dereferences these as the NV2A channel
     * aperture and the base of the NV2A MMIO register aperture.  The alpha's
     * live boot trace independently confirms the normal channel value. */
    device[0x1C20 / 4] = 0xFD800000u;
    device[0x1C28 / 4] = 0xFD000000u;
}

static void paint_diagnostic_surface(HDC dc, const RECT *client)
{
    /* Developer bring-up text used to live here. Keep startup neutral until
     * the first frame from the retail renderer arrives. */
    HBRUSH background = CreateSolidBrush(RGB(0, 0, 0));
    FillRect(dc, client, background);
    DeleteObject(background);
}

static LRESULT CALLBACK diagnostic_overlay_proc(HWND hwnd, UINT message,
                                                WPARAM wparam, LPARAM lparam)
{
    static unsigned paint_count;
    if (message == WM_APP + 0x51u) {
        fprintf(stderr, "[DAH-OVERLAY] hide hwnd=%p after presented content\n", (void *)hwnd);
        fflush(stderr);
        ShowWindow(hwnd, SW_HIDE);
        return 0;
    }
    if (message == WM_PAINT) {
        PAINTSTRUCT paint;
        RECT client;
        HDC dc = BeginPaint(hwnd, &paint);
        GetClientRect(hwnd, &client);
        if (paint_count++ == 0) {
            fprintf(stderr, "[DAH-OVERLAY] first paint hwnd=%p rect=%ldx%ld visible=%u\n",
                    (void *)hwnd, (long)(client.right - client.left),
                    (long)(client.bottom - client.top),
                    (unsigned)IsWindowVisible(hwnd));
            fflush(stderr);
        }
        if (!InterlockedCompareExchange(&g_dah_has_real_draw, 0, 0))
            paint_diagnostic_surface(dc, &client);
        EndPaint(hwnd, &paint);
        return 0;
    }
    if (message == WM_TIMER) {
        if (InterlockedCompareExchange(&g_dah_has_real_draw, 0, 0)) {
            ShowWindow(hwnd, SW_HIDE);
        } else {
            position_diagnostic_overlay();
            InvalidateRect(hwnd, NULL, FALSE);
        }
        return 0;
    }
    if (message == WM_ERASEBKGND)
        return 1;
    return DefWindowProcA(hwnd, message, wparam, lparam);
}

static LRESULT CALLBACK game_window_proc(HWND hwnd, UINT message,
                                         WPARAM wparam, LPARAM lparam)
{
    if (message == WM_DAH_RENDERER_READY) {
        RECT client = {0};
        /* Attach DXGI while the HWND is hidden, then expose the completed
         * presentation target.  Showing the GDI-backed client first can leave
         * DWM composing its initial surface until a manual move/resize forces
         * a redirection-surface refresh, which appears as a black bottom bar. */
        ShowWindow(hwnd, SW_SHOW);
        SetForegroundWindow(hwnd);
        BringWindowToTop(hwnd);
        UpdateWindow(hwnd);
        GetClientRect(hwnd, &client);
        fprintf(stderr,
                "[DAH-WINDOW] renderer attached before show client=%ldx%ld visible=%u\n",
                (long)(client.right - client.left),
                (long)(client.bottom - client.top),
                (unsigned)IsWindowVisible(hwnd));
        fflush(stderr);
        return 0;
    }
    if (message == WM_KEYDOWN && wparam == VK_OEM_3) {
        if (!(lparam & (1L << 30))) dah_console_toggle(!dah_console_is_open());
        return 0;
    }
    if (message == WM_CHAR && (wparam == '`' || wparam == '~')) return 0;
    if (message == WM_SETFOCUS && dah_console_is_open()) {
        SetFocus(g_dah_console_window);
        return 0;
    }
    if (message == WM_SIZE) dah_console_resize();
    if (message == WM_TIMER) {
        if (!InterlockedCompareExchange(&g_dah_has_real_draw, 0, 0))
            InvalidateRect(hwnd, NULL, FALSE);
        return 0;
    }
    if (message == WM_PAINT) {
        PAINTSTRUCT paint;
        HDC dc = BeginPaint(hwnd, &paint);
        if (!InterlockedCompareExchange(&g_dah_has_real_draw, 0, 0)) {
            RECT client;
            SetRect(&client, 0, 0, 640, 480);
            GetClientRect(hwnd, &client);
            paint_diagnostic_surface(dc, &client);
        }
        EndPaint(hwnd, &paint);
        return 0;
    }
    if (message == WM_SIZE && g_game_overlay) {
        position_diagnostic_overlay();
        return 0;
    }
    if (message == WM_CLOSE) {
        fprintf(stderr, "[DAH-WINDOW] WM_CLOSE hwnd=%p\n", (void *)hwnd);
        DestroyWindow(hwnd);
        return 0;
    }
    if (message == WM_DESTROY) {
        KillTimer(hwnd, 0xDA01u);
        if (g_game_overlay) {
            KillTimer(g_game_overlay, 0xDA02u);
            DestroyWindow(g_game_overlay);
            g_game_overlay = NULL;
        }
        fprintf(stderr, "[DAH-WINDOW] WM_DESTROY hwnd=%p\n", (void *)hwnd);
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProcA(hwnd, message, wparam, lparam);
}

static DWORD WINAPI host_window_thread(LPVOID parameter)
{
    HINSTANCE instance = (HINSTANCE)parameter;
    WNDCLASSA window_class = {0};
    WNDCLASSA overlay_class = {0};
    RECT rect = {0, 0, 640, 480};
    int internal_run = dah_internal_run();
    int hidden_window = internal_run || dah_test_window_hidden();

    window_class.lpfnWndProc = game_window_proc;
    window_class.hInstance = instance;
    window_class.hCursor = LoadCursor(NULL, IDC_ARROW);
    window_class.lpszClassName = "DestroyAllHumansRecompWindow";
    window_class.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    if (!RegisterClassA(&window_class) && GetLastError() != ERROR_CLASS_ALREADY_EXISTS) {
        fprintf(stderr, "[DAH-WINDOW] RegisterClass failed error=%lu\n", GetLastError());
        InterlockedExchange(&g_window_init_result, -1);
        SetEvent(g_window_ready_event);
        return 0;
    }

    overlay_class.lpfnWndProc = diagnostic_overlay_proc;
    overlay_class.hInstance = instance;
    overlay_class.hCursor = LoadCursor(NULL, IDC_ARROW);
    overlay_class.lpszClassName = "DestroyAllHumansRecompOverlay";
    overlay_class.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    if (!RegisterClassA(&overlay_class) && GetLastError() != ERROR_CLASS_ALREADY_EXISTS) {
        fprintf(stderr, "[DAH-WINDOW] RegisterClass overlay failed error=%lu\n", GetLastError());
        InterlockedExchange(&g_window_init_result, -1);
        SetEvent(g_window_ready_event);
        return 0;
    }

    AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);
    g_game_window = CreateWindowA(window_class.lpszClassName,
        "Destroy All Humans! (2005) - Native Recomp",
        WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN, CW_USEDEFAULT, CW_USEDEFAULT,
        rect.right - rect.left, rect.bottom - rect.top,
        NULL, NULL, instance, NULL);
    if (!g_game_window) {
        fprintf(stderr, "[DAH-WINDOW] CreateWindow failed error=%lu\n", GetLastError());
        InterlockedExchange(&g_window_init_result, -1);
        SetEvent(g_window_ready_event);
        return 0;
    }
    dah_set_stable_window_border(g_game_window);


    if (!dah_console_create(instance))
        fprintf(stderr, "[DAH-CONSOLE] failed to create console error=%lu\n", GetLastError());

    /* A normal player window is intentionally kept hidden until the D3D11
     * swap chain and NV2A renderer are attached.  init_host_renderer posts
     * WM_DAH_RENDERER_READY back to this owning UI thread. */
    /* An opaque owned popup covers the DXGI target and can itself make
     * Present report occlusion. Use the swapchain diagnostic clear normally;
     * retain this popup only for explicit window-composition diagnostics. */
    if (!hidden_window && getenv("DAH_DIAGNOSTIC_OVERLAY") && atoi(getenv("DAH_DIAGNOSTIC_OVERLAY")))
        g_game_overlay = CreateWindowExA(
        WS_EX_TOOLWINDOW | WS_EX_NOACTIVATE,
        overlay_class.lpszClassName, "",
        WS_POPUP | WS_VISIBLE,
        0, 0, 640, 480,
        g_game_window, NULL, instance, NULL);
    if (g_game_overlay) {
        EnableWindow(g_game_overlay, FALSE);
        position_diagnostic_overlay();
        SetTimer(g_game_overlay, 0xDA02u, 100u, NULL);
        fprintf(stderr, "[DAH-WINDOW] diagnostic overlay hwnd=%p visible=%u\n",
                (void *)g_game_overlay, (unsigned)IsWindowVisible(g_game_overlay));
    }
    SetTimer(g_game_window, 0xDA01u, 100u, NULL);
    fprintf(stderr, "[DAH-WINDOW] ready hwnd=%p thread=%lu visible=%u\n",
            (void *)g_game_window, GetCurrentThreadId(),
            (unsigned)IsWindowVisible(g_game_window));
    InterlockedExchange(&g_window_init_result, 1);
    SetEvent(g_window_ready_event);

    {
        MSG msg;
        while (GetMessageA(&msg, NULL, 0, 0) > 0) {
            TranslateMessage(&msg);
            DispatchMessageA(&msg);
        }
    }
    fprintf(stderr, "[DAH-WINDOW] message thread exited hwnd=%p\n",
            (void *)g_game_window);
    /* Closing the visible game must also stop its guest workers. The guest
     * scheduler does not consume the host UI thread's WM_QUIT. */
    fflush(stderr);
    ExitProcess(0);
    return 0;
}

static int init_host_renderer(HINSTANCE instance)
{
    D3DPRESENT_PARAMETERS present = {0};
    IDirect3D8 *d3d;
    IDirect3DDevice8 *device = NULL;

    /* Keep the HWND on a dedicated UI thread.  The guest entry point can
     * create and retire many Xbox worker threads, and if it returns from the
     * native thread that originally owned the window Windows destroys that
     * thread's top-level HWND.  A dedicated message thread keeps the visible
     * host window alive independently of the translated guest scheduler. */
    g_window_ready_event = CreateEventA(NULL, TRUE, FALSE, NULL);
    if (!g_window_ready_event) return 0;
    g_window_init_result = 0;
    if (!CreateThread(NULL, 0, host_window_thread, instance, 0, NULL)) {
        CloseHandle(g_window_ready_event);
        g_window_ready_event = NULL;
        return 0;
    }
    if (WaitForSingleObject(g_window_ready_event, 5000) != WAIT_OBJECT_0 ||
        InterlockedCompareExchange(&g_window_init_result, 0, 0) != 1) {
        CloseHandle(g_window_ready_event);
        g_window_ready_event = NULL;
        return 0;
    }
    CloseHandle(g_window_ready_event);
    g_window_ready_event = NULL;

    present.BackBufferWidth = 640;
    present.BackBufferHeight = 480;
    present.BackBufferCount = 1;
    present.MultiSampleType = D3DMULTISAMPLE_NONE;
    present.SwapEffect = D3DSWAPEFFECT_DISCARD;
    present.hDeviceWindow = g_game_window;
    present.Windowed = TRUE;
    present.EnableAutoDepthStencil = TRUE;
    present.AutoDepthStencilFormat = D3DFMT_D24S8;

    d3d = xbox_Direct3DCreate8(0);
    if (!d3d || FAILED(d3d->lpVtbl->CreateDevice(
            d3d, 0, 0, g_game_window, 0, &present, &device)))
        return 0;

    pgraph_d3d11_init();
    fprintf(stderr, "[DAH] Host D3D11 renderer ready (640x480)\n");
    if (!dah_internal_run() && !dah_test_window_hidden())
        PostMessageA(g_game_window, WM_DAH_RENDERER_READY, 0, 0);
    return 1;
}

static int init_dah_ltcg_bootstrap_ring(void)
{
    const uint32_t ring_size = 512u * 1024u;
    uint32_t ring = xbox_HeapAlloc(ring_size, 4096);

    if (!ring) return 0;
    g_dah_ltcg_ring = ring;
    dah_reset_ltcg_context();
    fprintf(stderr,
            "[DAH] seeded LTCG bootstrap ring %08X-%08X at context %08X\n",
            ring, ring + ring_size, 0x001E8970u);
    return 1;
}

static LONG CALLBACK watch_kpcr_writes(EXCEPTION_POINTERS *info)
{
    EXCEPTION_RECORD *record = info->ExceptionRecord;

    if (record->ExceptionCode == EXCEPTION_SINGLE_STEP && g_kpcr_watch_rearm) {
        DWORD old_protect;
        VirtualProtect((void *)g_kpcr_watch_base, 4096u,
                       PAGE_READONLY, &old_protect);
        info->ContextRecord->EFlags &= ~0x100u;
        g_kpcr_watch_rearm = 0;
        return EXCEPTION_CONTINUE_EXECUTION;
    }

    if (record->ExceptionCode == EXCEPTION_ACCESS_VIOLATION &&
        record->NumberParameters >= 2 && record->ExceptionInformation[0] == 1u) {
        uintptr_t address = (uintptr_t)record->ExceptionInformation[1];
        if (address >= g_kpcr_watch_base && address < g_kpcr_watch_base + 4096u) {
            uintptr_t module_base = (uintptr_t)GetModuleHandleA(NULL);
            unsigned offset = (unsigned)(address - g_kpcr_watch_base);
            FILE *log = fopen("kpcr_watch.log", "a");
            if (log) {
                fprintf(log,
                        "write offset=%03X host_rva=%08llX guest_esp=%08X "
                        "eax=%08X ecx=%08X edx=%08X esi=%08X edi=%08X\n",
                        offset,
                        (unsigned long long)((uintptr_t)record->ExceptionAddress - module_base),
                        g_esp, g_eax, g_ecx, g_edx, g_esi, g_edi);
                fclose(log);
            }

            /* fs:[0] is the live SEH chain anchor. Let one native instruction
             * update that dword, then immediately re-arm the page. Any write
             * beginning beyond it is the corruption we are hunting. */
            if (offset < 4u) {
                DWORD old_protect;
                if (VirtualProtect((void *)g_kpcr_watch_base, 4096u,
                                   PAGE_READWRITE, &old_protect)) {
                    g_kpcr_watch_rearm = 1;
                    info->ContextRecord->EFlags |= 0x100u;
                    return EXCEPTION_CONTINUE_EXECUTION;
                }
            }
        }
    }
    return EXCEPTION_CONTINUE_SEARCH;
}

static LONG CALLBACK log_unhandled_exception(EXCEPTION_POINTERS *info)
{
    /* OutputDebugString on Windows is surfaced as this first-chance code.
     * It is expected diagnostic traffic, not a game fault; do not overwrite
     * the crash report with it. */
    if (info->ExceptionRecord->ExceptionCode == 0x40010006u ||
        info->ExceptionRecord->ExceptionCode == 0x4001000Au ||
        /* MSVC's thread-name debugger exception (0x406D1388) is raised by
         * SetThreadDescription-style naming and is not a game fault. */
        info->ExceptionRecord->ExceptionCode == 0x406D1388u)
        return EXCEPTION_CONTINUE_SEARCH;
    FILE *log = fopen("recomp_crash.log", "w");
    if (log) {
        uintptr_t module_base = (uintptr_t)GetModuleHandleA(NULL);
        uintptr_t guest_base = (uintptr_t)xbox_GetMemoryOffset();
        fprintf(log, "exception=%08lX address=%p guest_esp=%08X\n",
                info->ExceptionRecord->ExceptionCode,
                info->ExceptionRecord->ExceptionAddress, g_esp);
        fprintf(log,
                "guest_regs eax=%08X ecx=%08X edx=%08X ebx=%08X "
                "esi=%08X edi=%08X ebp=%08X esp=%08X\n",
                g_eax, g_ecx, g_edx, g_ebx, g_esi, g_edi, g_ebp, g_esp);
        fprintf(log,
                "guest_state tib04=%08X tib08=%08X tib20=%08X tib28=%08X "
                "tls_index_270948=%08X\n",
                *(uint32_t *)(guest_base + 0x04u),
                *(uint32_t *)(guest_base + 0x08u),
                *(uint32_t *)(guest_base + 0x20u),
                *(uint32_t *)(guest_base + 0x28u),
                *(uint32_t *)(guest_base + 0x270948u));
        fprintf(log, "module=%p rva=%08llX\n", (void *)module_base,
                (unsigned long long)((uintptr_t)info->ExceptionRecord->ExceptionAddress - module_base));
        fprintf(log, "parameters=%lu", info->ExceptionRecord->NumberParameters);
        for (DWORD i = 0; i < info->ExceptionRecord->NumberParameters; ++i)
            fprintf(log, " p%lu=%016llX", i,
                    (unsigned long long)info->ExceptionRecord->ExceptionInformation[i]);
        fputc('\n', log);
#if defined(_M_X64)
        fprintf(log, "rip=%016llX rsp=%016llX rbp=%016llX\n",
                (unsigned long long)info->ContextRecord->Rip,
                (unsigned long long)info->ContextRecord->Rsp,
                (unsigned long long)info->ContextRecord->Rbp);
#endif
        {
            void *frames[24];
            USHORT count = CaptureStackBackTrace(0, 24, frames, NULL);
            for (USHORT i = 0; i < count; ++i)
                fprintf(log, "frame[%u]=%p rva=%08llX\n", i, frames[i],
                        (unsigned long long)((uintptr_t)frames[i] - module_base));
        }
        fclose(log);
    }
    return EXCEPTION_CONTINUE_SEARCH;
}

static DWORD WINAPI sample_guest_threads(LPVOID unused)
{
    DWORD process_id = GetCurrentProcessId();
    DWORD sampler_id = GetCurrentThreadId();
    uintptr_t module_base = (uintptr_t)GetModuleHandleA(NULL);
    (void)unused;
    const char *delay = getenv("DAH_WATCHDOG_DELAY_MS");
    if (delay) { unsigned ms = (unsigned)strtoul(delay, NULL, 10); Sleep(ms > 120000u ? 120000u : ms); }
    for (int sample = 0; sample < 8; ++sample) {
        Sleep(3000);
        FILE *log = fopen("recomp_watchdog.log", sample ? "a" : "w");
        HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
        if (!log || snapshot == INVALID_HANDLE_VALUE) {
            if (log) fclose(log);
            continue;
        }
        THREADENTRY32 thread = { sizeof(thread) };
        fprintf(log, "sample=%d tick=%llu\n", sample,
                (unsigned long long)GetTickCount64());
        if (Thread32First(snapshot, &thread)) do {
            if (thread.th32OwnerProcessID != process_id || thread.th32ThreadID == sampler_id)
                continue;
            HANDLE handle = OpenThread(THREAD_SUSPEND_RESUME | THREAD_GET_CONTEXT |
                                       THREAD_QUERY_INFORMATION, FALSE, thread.th32ThreadID);
            if (!handle) continue;
            if (SuspendThread(handle) != (DWORD)-1) {
                CONTEXT context = {0};
                context.ContextFlags = CONTEXT_CONTROL;
                if (GetThreadContext(handle, &context))
                    fprintf(log, "thread=%lu rip=%016llX rva=%08llX\n",
                            thread.th32ThreadID,
                            (unsigned long long)context.Rip,
                            (unsigned long long)((uintptr_t)context.Rip - module_base));
                ResumeThread(handle);
            }
            CloseHandle(handle);
        } while (Thread32Next(snapshot, &thread));
        CloseHandle(snapshot);
        fclose(log);
    }
    return 0;
}

static int load_file(const char *path, void **data, size_t *size)
{
    FILE *file = fopen(path, "rb");
    long length;
    void *buffer;
    if (!file) return 0;
    fseek(file, 0, SEEK_END);
    length = ftell(file);
    fseek(file, 0, SEEK_SET);
    if (length <= 0) { fclose(file); return 0; }
    buffer = malloc((size_t)length);
    if (!buffer || fread(buffer, 1, (size_t)length, file) != (size_t)length) {
        free(buffer);
        fclose(file);
        return 0;
    }
    fclose(file);
    *data = buffer;
    *size = (size_t)length;
    return 1;
}

/* Builds before the retail 64-bit remainder fix could give two profile names
 * the same container directory. Move those folders to the deterministic
 * retail hash derived from SaveMeta.xbx so existing progress remains usable. */
static void dah_migrate_legacy_save_containers(const char *save_dir)
{
    WCHAR raw_base[MAX_PATH], base[MAX_PATH], user_data[MAX_PATH], pattern[MAX_PATH];
    WIN32_FIND_DATAW found;
    HANDLE search;
    if (!save_dir || !*save_dir ||
        !MultiByteToWideChar(CP_UTF8, 0, save_dir, -1, raw_base, MAX_PATH)) return;
    if (!GetFullPathNameW(raw_base, MAX_PATH, base, NULL)) return;
    if (swprintf_s(user_data, MAX_PATH, L"%s\\UserData", base) < 0 ||
        swprintf_s(pattern, MAX_PATH, L"%s\\*", user_data) < 0) return;
    search = FindFirstFileW(pattern, &found);
    if (search == INVALID_HANDLE_VALUE) return;
    do {
        WCHAR meta_path[MAX_PATH], target_path[MAX_PATH], target_name[13];
        uint16_t text[64]; size_t count, start = 0, name_start, name_length, i;
        uint64_t hash = 0;
        FILE *meta;
        if (!(found.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) ||
            !wcscmp(found.cFileName, L".") || !wcscmp(found.cFileName, L"..")) continue;
        if (swprintf_s(meta_path, MAX_PATH, L"%s\\%s\\SaveMeta.xbx",
                       user_data, found.cFileName) < 0) continue;
        meta = _wfopen(meta_path, L"rb");
        if (!meta) continue;
        count = fread(text, sizeof(uint16_t), 64, meta);
        fclose(meta);
        if (count && text[0] == 0xFEFFu) start = 1;
        if (count < start + 6u || text[start] != 'N' || text[start + 1] != 'a' ||
            text[start + 2] != 'm' || text[start + 3] != 'e' || text[start + 4] != '=') continue;
        name_start = start + 5u;
        name_length = 0;
        while (name_start + name_length < count && text[name_start + name_length] != '\r' &&
               text[name_start + name_length] != '\n' && text[name_start + name_length]) ++name_length;
        if (!name_length) continue;
        for (i = 0; i < name_length; ++i) {
            hash = hash * 65536u + text[name_start + i];
            hash %= 0xFFFFFFFFFFFFFFC5ull;
        }
        for (i = 0; i < 12u; ++i) {
            unsigned nibble = (unsigned)((hash >> (44u - i * 4u)) & 0xFu);
            target_name[i] = (WCHAR)(nibble < 10u ? L'0' + nibble : L'A' + nibble - 10u);
        }
        target_name[12] = 0;
        if (!_wcsicmp(found.cFileName, target_name)) continue;
        if (swprintf_s(target_path, MAX_PATH, L"%s\\%s", user_data, target_name) < 0) continue;
        if (GetFileAttributesW(target_path) != INVALID_FILE_ATTRIBUTES) continue;
        {
            WCHAR source_path[MAX_PATH];
            if (swprintf_s(source_path, MAX_PATH, L"%s\\%s", user_data, found.cFileName) < 0) continue;
            if (MoveFileW(source_path, target_path))
                fprintf(stderr, "[DAH-SAVE-MIGRATE] %ls -> %ls\n", found.cFileName, target_name);
        }
    } while (FindNextFileW(search, &found));
    FindClose(search);
}


static uintptr_t dah_watched_address;
static DWORD dah_watched_thread;
static HANDLE dah_watch_ready;
static DWORD dah_watch_delay;
static LONG CALLBACK dah_model_write_exception(EXCEPTION_POINTERS *e)
{
    if(e->ExceptionRecord->ExceptionCode!=EXCEPTION_SINGLE_STEP || !(e->ContextRecord->Dr6&1u)) return EXCEPTION_CONTINUE_SEARCH;
    static unsigned count;
    fprintf(stderr,"[DAH-MODEL-WRITE] count=%u rva=%llX value=%.9g regs=%08X,%08X,%08X,%08X,%08X,%08X esp=%08X stack=",
        ++count,(unsigned long long)(e->ContextRecord->Rip-(uintptr_t)GetModuleHandleA(NULL)),*(float*)dah_watched_address,g_eax,g_ecx,g_edx,g_ebx,g_esi,g_edi,g_esp);
    if(g_esp>=0x10000u && g_esp<0x10000000u)for(unsigned i=0;i<12;i++)fprintf(stderr,"%08X,",*(uint32_t*)(xbox_GetMemoryOffset()+g_esp+i*4));
    fprintf(stderr,"\n");e->ContextRecord->Dr6=0;if(count>=128)e->ContextRecord->Dr7=0;return EXCEPTION_CONTINUE_EXECUTION;
}
static DWORD WINAPI dah_install_model_watch(LPVOID unused)
{
    if(dah_watch_delay)Sleep(dah_watch_delay);
    HANDLE h=OpenThread(THREAD_SUSPEND_RESUME|THREAD_GET_CONTEXT|THREAD_SET_CONTEXT,FALSE,dah_watched_thread);
    if(h){if(SuspendThread(h)!=(DWORD)-1){CONTEXT c={0};c.ContextFlags=CONTEXT_DEBUG_REGISTERS;if(GetThreadContext(h,&c)){c.Dr0=dah_watched_address;c.Dr6=0;c.Dr7=0xD0001;fprintf(stderr,"[DAH-MODEL-WATCH] address=%p installed=%d\n",(void*)dah_watched_address,SetThreadContext(h,&c));}ResumeThread(h);}CloseHandle(h);}SetEvent(dah_watch_ready);if(dah_watch_delay)CloseHandle(dah_watch_ready);return 0;
}
static void dah_start_model_watch(void)
{
    const char *v=getenv("DAH_WATCH_MODEL_ADDRESS");if(!v)return;
    uint32_t address=(uint32_t)strtoul(v,NULL,0);if(address<0x10000u||address>0x8ffffffcu)return;
    const char *delay=getenv("DAH_WATCH_MODEL_DELAY_MS");dah_watch_delay=delay?strtoul(delay,NULL,10):0;
    dah_watched_address=xbox_GetMemoryOffset()+address;dah_watched_thread=GetCurrentThreadId();dah_watch_ready=CreateEventA(NULL,TRUE,FALSE,NULL);AddVectoredExceptionHandler(1,dah_model_write_exception);
    HANDLE h=CreateThread(NULL,0,dah_install_model_watch,NULL,0,NULL);if(h){if(!dah_watch_delay)WaitForSingleObject(dah_watch_ready,5000);CloseHandle(h);}if(!dah_watch_delay)CloseHandle(dah_watch_ready);
}

int WINAPI WinMain(HINSTANCE instance, HINSTANCE previous, LPSTR command_line, int show)
{
    void *xbe = NULL;
    size_t xbe_size = 0;
    recomp_func_t entry;
    WCHAR executable_path[32768];
    WCHAR mutex_name[64];
    WCHAR *directory_end;
    DWORD path_length;
    uint32_t path_hash = 2166136261u;
    uint64_t executable_hash;
    SYSTEMTIME run_time;
    char run_id[96], started_utc[32];
    HANDLE instance_mutex;
    int internal_run = dah_internal_run();
    (void)previous; (void)command_line; (void)show;

    if (internal_run)
        SetErrorMode(SEM_FAILCRITICALERRORS | SEM_NOGPFAULTERRORBOX | SEM_NOOPENFILEERRORBOX);

    /* File associations and launchers need not inherit the exe directory.
     * Resolve all game data, save paths and diagnostics beside this build. */
    path_length = GetModuleFileNameW(NULL, executable_path, 32768);
    if (!path_length || path_length >= 32768) return 1;
    executable_hash = dah_hash_file_w(executable_path);
    GetSystemTime(&run_time);
    sprintf_s(started_utc, sizeof(started_utc),
              "%04u-%02u-%02uT%02u:%02u:%02u.%03uZ",
              run_time.wYear, run_time.wMonth, run_time.wDay,
              run_time.wHour, run_time.wMinute, run_time.wSecond,
              run_time.wMilliseconds);
    sprintf_s(run_id, sizeof(run_id),
              "%04u%02u%02uT%02u%02u%02u%03uZ-p%lu-%016llX",
              run_time.wYear, run_time.wMonth, run_time.wDay,
              run_time.wHour, run_time.wMinute, run_time.wSecond,
              run_time.wMilliseconds, GetCurrentProcessId(),
              (unsigned long long)executable_hash);
    for (DWORD i = 0; i < path_length; ++i)
        path_hash = (path_hash ^ (uint32_t)executable_path[i]) * 16777619u;
    swprintf_s(mutex_name, 64, L"Local\\DAH1Recomp-%08X", path_hash);
    instance_mutex = CreateMutexW(NULL, FALSE, mutex_name);
    if (!instance_mutex) return 1;
    if (GetLastError() == ERROR_ALREADY_EXISTS) {
        CloseHandle(instance_mutex);
        dah_report_startup_error("This build is already running. Close its game window before launching it again.",
                                 MB_OK);
        return internal_run ? 1 : 0;
    }
    directory_end = wcsrchr(executable_path, L'\\');
    if (!directory_end) return 1;
    *directory_end = L'\0';
    if (!SetCurrentDirectoryW(executable_path)) return 1;

    /* GUI launches need only the game window. Both diagnostic streams go
     * to recomp.log, so allocating a separate console creates an empty
     * second window without providing any diagnostic output. */
    const char *dah_log_path=getenv("DAH_LOG_PATH");
    const char *dah_event_path=getenv("DAH_EVENT_TRACE");
    if(!dah_log_path || !*dah_log_path)dah_log_path="furonlog.log";
    if(!dah_event_path || !*dah_event_path)dah_event_path="dah_event_trace.jsonl";
    freopen(dah_log_path, "w", stdout);
    freopen(dah_log_path, "a", stderr);
    /* Both FILE streams must exist even for a hidden GUI process, then
     * share the descriptor's file position to avoid overwriting each other. */
    if (_dup2(_fileno(stdout), _fileno(stderr)) != 0) return 1;
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
    printf("Destroy All Humans! (2005) native static recomp bring-up\n");
    fprintf(stderr,
            "[DAH-RUN] schema=1 id=%s pid=%lu started-utc=%s exe-fnv1a64=%016llX data-directory=%ls log=%s events=%s\n",
            run_id, GetCurrentProcessId(), started_utc,
            (unsigned long long)executable_hash, executable_path,
            dah_log_path, dah_event_path);
    dah_write_run_manifest(run_id, started_utc, executable_hash,
                           dah_log_path, dah_event_path, "running");
    {
        const char *kpcr_watch = getenv("DAH_KPCR_WATCH");
        if (kpcr_watch && atoi(kpcr_watch) != 0)
            AddVectoredExceptionHandler(1, watch_kpcr_writes);
    }
    /* crashlog is a separate persistent crash-only archive.  Keep the
     * existing recomp crash handler and detailed runtime log intact. */
    dah_crashlog_initialize(dah_log_path);
    dah_event_trace_initialize(run_id, started_utc, executable_hash);
    AddVectoredExceptionHandler(0, log_unhandled_exception);
    /* Stack-sampling suspends the game thread by design.  Keep it available
     * for crash investigations, but do not let the diagnostic distort normal
     * frame-pacing measurements or gameplay input. */
    {
        const char *watchdog = getenv("DAH_WATCHDOG");
        if (watchdog && atoi(watchdog) != 0)
            CloseHandle(CreateThread(NULL, 0, sample_guest_threads, NULL, 0, NULL));
    }

    if (!load_file("default.xbe", &xbe, &xbe_size)) {
        dah_report_startup_error("default.xbe must be beside the game executable", MB_ICONERROR);
        return 1;
    }
    /* Keep physical-memory probes and the host-side XAPI heap in distinct
     * headroom. The original unified allocator otherwise fragments retail
     * 64 MiB during the title's startup probe before its main arena is made. */
    xbox_SetTotalRam(XBOX_DEVKIT_RAM);
    /* The XBE occupies physical pages; the relocated heap's address gap does
     * not. Keep the retail budget while allowing separate host address space. */
    {
        uint32_t image_bytes = *(const uint32_t *)((const uint8_t *)xbe + 0x10C);
        uint32_t image_pages = (image_bytes + 4095u) & ~4095u;
        xbox_SetContiguousAllocationLimit(XBOX_TOTAL_RAM - image_pages);
    }
    if (!xbox_MemoryLayoutInit(xbe, xbe_size)) {
        dah_report_startup_error("Xbox memory initialization failed", MB_ICONERROR);
        free(xbe);
        return 2;
    }

    xbox_kernel_init();
    /* Internal level automation uses a copy of the build's test saves.
     * Normal desktop launches retain the original per-build save directory. */
    {
        const char *save_override = internal_run ? getenv("DAH_SAVE_DIR") : NULL;
        if (save_override && *save_override) {
            size_t length = strlen(save_override);
            if (length >= MAX_PATH || length < 3u || save_override[1] != ':' ||
                (save_override[2] != '\\' && save_override[2] != '/')) {
                dah_report_startup_error("DAH_SAVE_DIR must be an absolute local path shorter than MAX_PATH.", MB_ICONERROR);
                return 1;
            }
            dah_migrate_legacy_save_containers(save_override);
            xbox_path_init(".", save_override);
            fprintf(stderr, "[DAH-SAVE] internal save directory=%s\n", save_override);
        } else {
            dah_migrate_legacy_save_containers(".\\saves");
            xbox_path_init(".", ".\\saves");
        }
    }
    xbox_kernel_bridge_init();
    if (!init_dah_ltcg_bootstrap_ring()) {
        dah_report_startup_error("Xbox D3D bootstrap ring allocation failed", MB_ICONERROR);
        return 5;
    }
    dah_renderdoc_init();
    if (!init_host_renderer(instance)) {
        dah_report_startup_error("Host D3D11 renderer initialization failed", MB_ICONERROR);
        return 4;
    }
    g_esp = XBOX_STACK_TOP;
    recomp_dispatch_init();

    /* Bring-up diagnostic: catch the first write through a RAM mirror.  Such
     * a write currently poisons the fake KPCR at guest VA 0 before the retail
     * CRT indexes its TLS slot.  Page protection is opt-in because every
     * legitimate KPCR write otherwise becomes a debugger trap on the frame
     * path. */
    {
        const char *kpcr_watch = getenv("DAH_KPCR_WATCH");
        if (kpcr_watch && atoi(kpcr_watch) != 0) {
            xbox_ProtectMirrorsForDebug();
            {
                DWORD old_protect;
                g_kpcr_watch_base = (uintptr_t)xbox_GetMemoryOffset();
                if (VirtualProtect((void *)g_kpcr_watch_base, 4096u,
                                   PAGE_READONLY, &old_protect))
                    fprintf(stderr, "[DAH-DIAG] protected fake KPCR page\n");
            }
        } else {
            fprintf(stderr, "[DAH-DIAG] KPCR/mirror watcher disabled for normal run\n");
        }
    }

    entry = recomp_lookup(DAH_ENTRY_POINT);
    if (!entry) {
        fprintf(stderr, "Entry point 0x%08X was not translated.\n", DAH_ENTRY_POINT);
        return 3;
    }
    printf("Launching translated entry point 0x%08X...\n", DAH_ENTRY_POINT);
    dah_start_model_watch();
    entry();
    dah_event_trace_shutdown();
    dah_write_run_manifest(run_id, started_utc, executable_hash,
                           dah_log_path, dah_event_path, "completed");
    printf("The translated game returned to the host.\n");
    xbox_kernel_shutdown();
    xbox_MemoryLayoutShutdown();
    free(xbe);
    return 0;
}
