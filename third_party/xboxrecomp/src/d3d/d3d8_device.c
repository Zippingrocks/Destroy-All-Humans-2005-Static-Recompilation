/**
 * D3D8→D3D11 Compatibility Device Implementation
 *
 * Implements the Xbox D3D8 IDirect3DDevice8 interface using D3D11.
 * The game's translated RenderWare code calls D3D8 methods through
 * COM vtables; this layer translates those calls to D3D11 equivalents.
 *
 * Architecture:
 * - D3D11 device and swap chain created during initialization
 * - Render state tracking: D3D8 states mapped to D3D11 state objects
 * - Texture/buffer management: D3D8 resource handles wrap D3D11 resources
 * - Fixed-function pipeline: emulated via D3D11 shaders (the Xbox D3D8
 *   pipeline is configurable but not fully programmable)
 *
 * Build: Requires Windows SDK with d3d11.h and dxgi.h
 */

#include "d3d8_internal.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ================================================================
 * Internal device state
 * ================================================================ */

/* Maximum tracked render states, texture stages, and transforms */
#define MAX_RENDER_STATES    256
#define MAX_TEXTURE_STAGES   4
#define MAX_TSS_STATES       32
#define MAX_TRANSFORMS       512
#define MAX_LIGHTS           8

typedef struct D3D8DeviceState {
    /* D3D11 objects */
    ID3D11Device            *d3d11_device;
    ID3D11DeviceContext     *d3d11_context;
    IDXGISwapChain          *swap_chain;

    /* Default render targets */
    ID3D11RenderTargetView  *default_rtv;
    ID3D11DepthStencilView  *default_dsv;
    ID3D11Texture2D         *default_depth;

    /* Window */
    HWND                    hwnd;
    UINT                    width;
    UINT                    height;
    D3DFORMAT               backbuffer_format;

    /* State tracking */
    DWORD                   render_states[MAX_RENDER_STATES];
    DWORD                   tss[MAX_TEXTURE_STAGES][MAX_TSS_STATES];
    D3DMATRIX               transforms[MAX_TRANSFORMS];
    D3DVIEWPORT8            viewport;
    D3DMATERIAL8            material;
    D3DLIGHT8               lights[MAX_LIGHTS];
    BOOL                    light_enable[MAX_LIGHTS];

    /* Current shader/FVF */
    DWORD                   vertex_shader;
    DWORD                   pixel_shader;

    /* Scene state */
    BOOL                    in_scene;

    /* Reference count */
    LONG                    ref_count;
} D3D8DeviceState;

/* Global device instance (Xbox has a single D3D device) */
static D3D8DeviceState g_device_state;
static IDirect3DDevice8 g_device;
static BOOL g_device_initialized = FALSE;

/* Current resource bindings */
static IDirect3DVertexBuffer8 *g_cur_vb = NULL;
static UINT                    g_cur_vb_stride = 0;
static IDirect3DIndexBuffer8  *g_cur_ib = NULL;
static UINT                    g_cur_ib_base_vertex = 0;
static IDirect3DBaseTexture8  *g_cur_textures[4] = { NULL };
static IDirect3DTexture8      *g_host_frame_texture = NULL;
static UINT                    g_host_frame_width;
static UINT                    g_host_frame_height;

#define PGRAPH_RT_COUNT 8
typedef struct PgraphRenderTarget {
    UINT offset, width, height;
    ID3D11Texture2D *texture;
    ID3D11RenderTargetView *rtv;
    ID3D11ShaderResourceView *srv;
} PgraphRenderTarget;
static PgraphRenderTarget g_pgraph_rt[PGRAPH_RT_COUNT];
static ID3D11RenderTargetView *g_current_rtv;
static ID3D11DepthStencilView *g_current_dsv;
typedef struct { UINT offset,width,height,format; ID3D11Texture2D *texture; ID3D11DepthStencilView *dsv; } PgraphDepth;
static PgraphDepth g_pgraph_depth[PGRAPH_RT_COUNT];
static PgraphRenderTarget *g_current_pgraph_rt;
static BOOL g_current_pgraph_presentable;

/* Forward declarations */
static const IDirect3DDevice8Vtbl g_device_vtbl;
static void up_ring_shutdown(void);
static void pgraph_copy_presentable_to_swapchain(void);

/* Capture the actual swap-chain pixels, including when its HWND is hidden.
 * This diagnostic never draws or substitutes content. GPU readback is
 * synchronous, so its logged capture_ms must be excluded from pacing tests.
 * DAH_FRAME_CAPTURE is a bounded capture count (1..256); INTERVAL and START
 * select zero-based Present frames. Files go to the process working directory.
 */
static unsigned frame_capture_setting(const char *name, unsigned fallback,
                                      unsigned maximum)
{
    const char *value = getenv(name);
    char *end;
    unsigned long parsed;
    if (!value || !*value) return fallback;
    if (*value < '0' || *value > '9') return fallback;
    parsed = strtoul(value, &end, 10);
    if (*end || parsed > maximum) return fallback;
    return (unsigned)parsed;
}

/* Console requests are coalesced and read on the rendering thread. They
 * capture only the game's swapchain, never the desktop. Keep disk usage bounded.
 */
static volatile LONG g_manual_capture_pending;
static volatile LONG g_manual_capture_attempts;

int dah_request_frame_capture(void)
{
    if (InterlockedCompareExchange(&g_manual_capture_attempts, 0, 0) >= 256)
        return 0;
    InterlockedExchange(&g_manual_capture_pending, 1);
    return 1;
}

static void capture_swapchain_frame(void)
{
    static int initialized;
    static unsigned limit, interval, start, attempts;
    static unsigned long long frame;
    unsigned long long current_frame;
    ID3D11Texture2D *backbuffer = NULL, *resolved = NULL, *staging = NULL;
    D3D11_TEXTURE2D_DESC desc = {0};
    D3D11_MAPPED_SUBRESOURCE mapped;
    BITMAPFILEHEADER file_header;
    BITMAPINFOHEADER info_header;
    LARGE_INTEGER started, finished, frequency;
    BYTE *row_buffer = NULL;
    FILE *output = NULL;
    HRESULT hr = E_FAIL;
    UINT row, column;
    unsigned checksum = 2166136261u;
    int rgba, is_mapped = 0, saved = 0, requested;
    static unsigned manual_remaining;
    char path[96];

    if (!initialized) {
        initialized = 1;
        limit = frame_capture_setting("DAH_FRAME_CAPTURE", 0u, 256u);
        interval = frame_capture_setting("DAH_FRAME_CAPTURE_INTERVAL", 30u, 1000000u);
        if (!interval) interval = 1u;
        start = frame_capture_setting("DAH_FRAME_CAPTURE_START", 0u, 1000000000u);
        if (limit) {
            fprintf(stderr, "[DAH-FRAME-CAPTURE] enabled count=%u interval=%u start=%u; synchronous readback affects capture frames\n",
                    limit, interval, start);
            fflush(stderr);
        }
    }
    current_frame = frame++;
    /* Two consecutive frames reveal double-buffer/parity rendering defects. */
    if (InterlockedExchange(&g_manual_capture_pending, 0)) manual_remaining = 2u;
    requested = manual_remaining != 0u;
    if (requested) {
        --manual_remaining;
        if (InterlockedCompareExchange(&g_manual_capture_attempts, 0, 0) >= 256)
            return;
        InterlockedIncrement(&g_manual_capture_attempts);
    } else {
        if (!limit || attempts >= limit) return;
        if (current_frame < start || (current_frame - start) % interval) return;
        attempts++;
    }
    QueryPerformanceCounter(&started);
    snprintf(path, sizeof(path), "dah_frame_%lu_%010llu.bmp",
             (unsigned long)GetCurrentProcessId(), current_frame);

    if (!g_device_state.swap_chain || !g_device_state.d3d11_device ||
        !g_device_state.d3d11_context) goto cleanup;
    hr = IDXGISwapChain_GetBuffer(g_device_state.swap_chain, 0,
                                 &IID_ID3D11Texture2D, (void **)&backbuffer);
    if (FAILED(hr)) goto cleanup;
    ID3D11Texture2D_GetDesc(backbuffer, &desc);
    rgba = desc.Format == DXGI_FORMAT_R8G8B8A8_UNORM ||
           desc.Format == DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
    if (!rgba && desc.Format != DXGI_FORMAT_B8G8R8A8_UNORM &&
        desc.Format != DXGI_FORMAT_B8G8R8A8_UNORM_SRGB &&
        desc.Format != DXGI_FORMAT_B8G8R8X8_UNORM &&
        desc.Format != DXGI_FORMAT_B8G8R8X8_UNORM_SRGB) {
        fprintf(stderr, "[DAH-FRAME-CAPTURE] frame=%llu unsupported DXGI format=%u; no image written\n",
                current_frame, (unsigned)desc.Format);
        hr = E_NOTIMPL;
        goto cleanup;
    }
    /* Keep file-size arithmetic bounded; 16K is the D3D11 2D limit. */
    if (!desc.Width || !desc.Height || desc.Width > 16384u || desc.Height > 16384u) {
        hr = E_INVALIDARG;
        goto cleanup;
    }
    desc.MipLevels = 1;
    desc.ArraySize = 1;
    desc.BindFlags = 0;
    desc.MiscFlags = 0;
    if (desc.SampleDesc.Count > 1) {
        desc.SampleDesc.Count = 1;
        desc.SampleDesc.Quality = 0;
        desc.Usage = D3D11_USAGE_DEFAULT;
        desc.CPUAccessFlags = 0;
        hr = ID3D11Device_CreateTexture2D(g_device_state.d3d11_device,
                                        &desc, NULL, &resolved);
        if (FAILED(hr)) goto cleanup;
        ID3D11DeviceContext_ResolveSubresource(g_device_state.d3d11_context,
                (ID3D11Resource *)resolved, 0,
                (ID3D11Resource *)backbuffer, 0, desc.Format);
    }
    desc.Usage = D3D11_USAGE_STAGING;
    desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
    hr = ID3D11Device_CreateTexture2D(g_device_state.d3d11_device,
                                    &desc, NULL, &staging);
    if (FAILED(hr)) goto cleanup;
    ID3D11DeviceContext_CopyResource(g_device_state.d3d11_context,
            (ID3D11Resource *)staging,
            (ID3D11Resource *)(resolved ? resolved : backbuffer));
    hr = ID3D11DeviceContext_Map(g_device_state.d3d11_context,
            (ID3D11Resource *)staging, 0, D3D11_MAP_READ, 0, &mapped);
    if (FAILED(hr)) goto cleanup;
    is_mapped = 1;
    row_buffer = (BYTE *)malloc((size_t)desc.Width * 4u);
    if (!row_buffer) { hr = E_OUTOFMEMORY; goto cleanup; }

    memset(&file_header, 0, sizeof(file_header));
    memset(&info_header, 0, sizeof(info_header));
    file_header.bfType = 0x4D42;
    file_header.bfOffBits = sizeof(file_header) + sizeof(info_header);
    file_header.bfSize = file_header.bfOffBits + desc.Width * desc.Height * 4u;
    info_header.biSize = sizeof(info_header);
    info_header.biWidth = (LONG)desc.Width;
    info_header.biHeight = -(LONG)desc.Height; /* Preserve top-down row order. */
    info_header.biPlanes = 1;
    info_header.biBitCount = 32;
    info_header.biCompression = BI_RGB;
    info_header.biSizeImage = desc.Width * desc.Height * 4u;
    output = fopen(path, "wb");
    if (!output) { hr = E_FAIL; goto cleanup; }
    if (fwrite(&file_header, sizeof(file_header), 1, output) != 1 ||
        fwrite(&info_header, sizeof(info_header), 1, output) != 1) {
        hr = E_FAIL;
        goto cleanup;
    }
    for (row = 0; row < desc.Height; ++row) {
        const BYTE *source = (const BYTE *)mapped.pData + (size_t)row * mapped.RowPitch;
        for (column = 0; column < desc.Width; ++column) {
            const BYTE *pixel = source + column * 4u;
            BYTE *target = row_buffer + column * 4u;
            /* BMP stores BGRA. Only channel order changes; values are exact. */
            target[0] = pixel[rgba ? 2 : 0];
            target[1] = pixel[1];
            target[2] = pixel[rgba ? 0 : 2];
            target[3] = pixel[3];
            checksum = (checksum ^ target[0]) * 16777619u;
            checksum = (checksum ^ target[1]) * 16777619u;
            checksum = (checksum ^ target[2]) * 16777619u;
        }
        if (fwrite(row_buffer, 4u, desc.Width, output) != desc.Width) {
            hr = E_FAIL;
            goto cleanup;
        }
    }
    if (fclose(output) != 0) { output = NULL; hr = E_FAIL; goto cleanup; }
    output = NULL;
    saved = 1;
    hr = S_OK;

cleanup:
    if (output) fclose(output);
    if (is_mapped) ID3D11DeviceContext_Unmap(g_device_state.d3d11_context,
                                            (ID3D11Resource *)staging, 0);
    free(row_buffer);
    if (staging) ID3D11Texture2D_Release(staging);
    if (resolved) ID3D11Texture2D_Release(resolved);
    if (backbuffer) ID3D11Texture2D_Release(backbuffer);
    QueryPerformanceCounter(&finished);
    QueryPerformanceFrequency(&frequency);
    if (saved)
        fprintf(stderr, "[DAH-FRAME-CAPTURE] frame=%llu file=%s size=%ux%u format=%u rgb_fnv1a=%08X capture_ms=%.3f\n",
                current_frame, path, desc.Width, desc.Height, (unsigned)desc.Format,
                checksum, (finished.QuadPart - started.QuadPart) * 1000.0 / frequency.QuadPart);
    else
        fprintf(stderr, "[DAH-FRAME-CAPTURE] frame=%llu failed hr=0x%08lX attempt=%u/%u\n",
                current_frame, (unsigned long)hr, attempts, limit);
    fflush(stderr);
}

/* ================================================================
 * Public frame pump (called from recompiled game code)
 * ================================================================ */
static BOOL g_full_screen_movie_frame;
static BOOL g_full_screen_movie_transition;
static BOOL g_full_screen_movie_ready_reported;
static unsigned g_full_screen_movie_black_preroll;
static BOOL g_presentation_hold;

void d3d8_SetPresentationHold(int enabled)
{
    g_presentation_hold = enabled ? TRUE : FALSE;
}

HRESULT d3d8_PresentFrameWithInterval(UINT interval)
{
    /* Pump Windows messages */
    MSG msg;
    static unsigned present_trace_count;
    while (PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE)) {
        if (msg.message == WM_QUIT) ExitProcess(0);
        TranslateMessage(&msg);
        DispatchMessageA(&msg);
    }

    if (g_device_state.swap_chain) {
        /* Xbox presents the currently selected color buffer.  Mirror that
         * native surface into DXGI immediately before capture/Present. */
        if (g_full_screen_movie_black_preroll > 0u ||
            (g_full_screen_movie_transition && !g_full_screen_movie_frame)) {
            static const float black[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
            if (g_device_state.d3d11_context && g_device_state.default_rtv)
                ID3D11DeviceContext_ClearRenderTargetView(
                    g_device_state.d3d11_context,
                    g_device_state.default_rtv, black);
            if (g_full_screen_movie_black_preroll > 0u)
                --g_full_screen_movie_black_preroll;
        } else if (!g_presentation_hold) {
            pgraph_copy_presentable_to_swapchain();
        }
        capture_swapchain_frame();
        UINT present_flags = interval ? 0u : DXGI_PRESENT_DO_NOT_WAIT;
        HRESULT result = IDXGISwapChain_Present(g_device_state.swap_chain, interval, present_flags);
        if (result == DXGI_ERROR_WAS_STILL_DRAWING) {
            static unsigned deferred_present_count;
            if (deferred_present_count++ < 8u)
                fprintf(stderr, "[D3D8-PRESENT-DEFERRED] call=%u swap chain still drawing; simulation remains live\n",
                        present_trace_count + 1u);
            result = S_OK;
        }
        if (present_trace_count < 8u || (FAILED(result) && result != DXGI_STATUS_OCCLUDED)) {
            fprintf(stderr, "[D3D8-PRESENT] call=%u interval=%u result=0x%08lX hwnd=%p visible=%u iconic=%u\n",
                    present_trace_count + 1u, interval, (unsigned long)result,
                    (void *)g_device_state.hwnd,
                    g_device_state.hwnd ? (unsigned)IsWindowVisible(g_device_state.hwnd) : 0u,
                    g_device_state.hwnd ? (unsigned)IsIconic(g_device_state.hwnd) : 0u);
            fflush(stderr);
        }
        present_trace_count++;
        g_full_screen_movie_frame = FALSE;
        return result;
    }
    return E_FAIL;
}

/* Visible bring-up fallback for frames where the retail path has not yet
 * emitted any geometry.  Clear the actual swap-chain target rather than
 * relying on WM_PAINT, which is not guaranteed to compose over a DXGI HWND.
 * The caller stops using this as soon as the first real draw is observed. */
void d3d8_ClearFrameDiagnostic(void)
{
    static const float color[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
    static int reported;
    if (g_device_state.d3d11_context && g_device_state.default_rtv) {
        if (!reported) {
            fprintf(stderr, "[DAH-BOOT-SURFACE] neutral black clear active before first retail draw\n");
            fflush(stderr);
            reported = 1;
        }
        ID3D11DeviceContext_ClearRenderTargetView(
            g_device_state.d3d11_context, g_device_state.default_rtv, color);
    }
}

void d3d8_ClearMovieBackground(void)
{
    static const float black[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
    static unsigned calls;
    ID3D11RenderTargetView *target =
        g_current_rtv ? g_current_rtv : g_device_state.default_rtv;
    /* Keep the transition latch set until the decoded full-screen quad has
     * actually reached the host renderer.  The game can call this while the
     * Bink upload or draw is still incomplete, and releasing here exposes the
     * stale mothership render target for one frame. */
    g_full_screen_movie_frame = TRUE;
    if (!g_device_state.d3d11_context || !target) return;
    ID3D11DeviceContext_ClearRenderTargetView(g_device_state.d3d11_context,
                                               target, black);
    if (calls++ < 4u)
        fprintf(stderr,
                "[DAH-MOVIE-BACKGROUND] cleared target before full-screen movie frame rt=%p\n",
                (void *)target);
}

void d3d8_BeginFullScreenMovieTransition(void)
{
    static unsigned calls;
    g_full_screen_movie_transition = TRUE;
    g_full_screen_movie_ready_reported = FALSE;
    /* The Xbox movie player rotates presentable surfaces during startup.
     * Give both old scene buffers time to leave the present queue while Bink
     * decodes behind an intentional black preroll. */
    g_full_screen_movie_black_preroll = 3u;
    if (calls++ < 8u)
        fprintf(stderr, "[DAH-MOVIE-TRANSITION] holding black until first decoded frame\n");
}

void d3d8_MarkFullScreenMovieFrameReady(void)
{
    g_full_screen_movie_frame = TRUE;
    if (g_full_screen_movie_transition && !g_full_screen_movie_ready_reported) {
        g_full_screen_movie_ready_reported = TRUE;
        fprintf(stderr, "[DAH-MOVIE-TRANSITION] first decoded frame ready; guarding inter-frame gaps\n");
    }
}

void d3d8_EndFullScreenMovieTransition(void)
{
    static unsigned calls;
    if (calls++ < 16u)
        fprintf(stderr, "[DAH-MOVIE-TRANSITION-END] active=%u frame=%u\n",
                (unsigned)g_full_screen_movie_transition,
                (unsigned)g_full_screen_movie_frame);
    g_full_screen_movie_transition = FALSE;
    g_full_screen_movie_ready_reported = FALSE;
    g_full_screen_movie_black_preroll = 0u;
}

BOOL d3d8_IsFullScreenMovieFrame(void)
{
    return g_full_screen_movie_frame || g_full_screen_movie_transition;
}

void d3d8_PresentFrame(void)
{
    static ULONGLONG last_frame_tick;
    /* Legacy callers use VSync plus an occlusion fallback. Titles with a
     * separate frame clock call PresentFrameWithInterval directly. */
    d3d8_PresentFrameWithInterval(1u);

    {
        ULONGLONG now = GetTickCount64();
        if (last_frame_tick != 0 && now - last_frame_tick < 16u)
            Sleep((DWORD)(16u - (now - last_frame_tick)));
        last_frame_tick = GetTickCount64();
    }
}

/* ================================================================
 * Internal accessors (used by d3d8_resources/shaders/states)
 * ================================================================ */

IDirect3DDevice8    *d3d8_GetDevice(void) { return &g_device; }
ID3D11Device        *d3d8_GetD3D11Device(void) { return g_device_state.d3d11_device; }
ID3D11DeviceContext *d3d8_GetD3D11Context(void) { return g_device_state.d3d11_context; }
IDXGISwapChain      *d3d8_GetSwapChain(void) { return g_device_state.swap_chain; }
ID3D11RenderTargetView *d3d8_GetDefaultRTV(void) { return g_device_state.default_rtv; }
HWND                 d3d8_GetHWND(void) { return g_device_state.hwnd; }
UINT                 d3d8_GetBackbufferWidth(void) { return g_device_state.width; }
UINT                 d3d8_GetBackbufferHeight(void) { return g_device_state.height; }

static PgraphRenderTarget *pgraph_find_rt(UINT offset)
{
    UINT i;
    for (i = 0; i < PGRAPH_RT_COUNT; ++i)
        if (g_pgraph_rt[i].texture && g_pgraph_rt[i].offset == offset)
            return &g_pgraph_rt[i];
    return NULL;
}
BOOL d3d8_PgraphHasRenderTarget(UINT offset)
{
    return pgraph_find_rt(offset) != NULL;
}

HRESULT d3d8_PgraphBindRenderTarget(UINT offset, BOOL backbuffer,
                                    UINT width, UINT height)
{
    PgraphRenderTarget *rt = NULL;
    ID3D11ShaderResourceView *null_srvs[4] = { NULL, NULL, NULL, NULL };
    HRESULT hr;
    UINT i;

    if (!g_device_state.d3d11_device || !g_device_state.d3d11_context)
        return E_FAIL;
    if (backbuffer) { width = g_device_state.width; height = g_device_state.height; }
    if (!width) width = g_device_state.width;
    if (!height) height = g_device_state.height;
    rt = pgraph_find_rt(offset);
    if (rt && (rt->width != width || rt->height != height)) {
        if (rt->srv) ID3D11ShaderResourceView_Release(rt->srv);
        if (rt->rtv) ID3D11RenderTargetView_Release(rt->rtv);
        if (rt->texture) ID3D11Texture2D_Release(rt->texture);
        memset(rt, 0, sizeof(*rt));
        rt = NULL; /* Recreate the resized resource below. */
    }
    if (!rt) {
        D3D11_TEXTURE2D_DESC td;
        for (i = 0; i < PGRAPH_RT_COUNT; ++i)
            if (!g_pgraph_rt[i].texture) { rt = &g_pgraph_rt[i]; break; }
        if (!rt) return E_OUTOFMEMORY;
        memset(&td, 0, sizeof(td));
        td.Width = width; td.Height = height;
        td.MipLevels = 1; td.ArraySize = 1;
        td.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        td.SampleDesc.Count = 1;
        td.Usage = D3D11_USAGE_DEFAULT;
        td.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
        hr = ID3D11Device_CreateTexture2D(g_device_state.d3d11_device, &td,
                                          NULL, &rt->texture);
        if (FAILED(hr)) return hr;
        hr = ID3D11Device_CreateRenderTargetView(g_device_state.d3d11_device,
                    (ID3D11Resource *)rt->texture, NULL, &rt->rtv);
        if (FAILED(hr)) goto fail;
        hr = ID3D11Device_CreateShaderResourceView(g_device_state.d3d11_device,
                    (ID3D11Resource *)rt->texture, NULL, &rt->srv);
        if (FAILED(hr)) goto fail;
        rt->offset = offset; rt->width = width; rt->height = height;
        fprintf(stderr, "[PGRAPH-RT] created offset=%08X size=%ux%u\n",
                offset, width, height);
        fflush(stderr);
    }

    /* D3D11 forbids one resource being simultaneously bound for input and
     * output.  Clear stale PGRAPH sampling slots before changing targets. */
    ID3D11DeviceContext_PSSetShaderResources(g_device_state.d3d11_context,
                                             0, 4, null_srvs);
    g_current_rtv = rt->rtv;
    g_current_pgraph_rt = rt;
    g_current_pgraph_presentable = backbuffer;
    ID3D11DeviceContext_OMSetRenderTargets(g_device_state.d3d11_context, 1,
                                           &g_current_rtv,
                                           backbuffer ? g_device_state.default_dsv : NULL);
    return S_OK;

fail:
    if (rt->srv) ID3D11ShaderResourceView_Release(rt->srv);
    if (rt->rtv) ID3D11RenderTargetView_Release(rt->rtv);
    if (rt->texture) ID3D11Texture2D_Release(rt->texture);
    memset(rt, 0, sizeof(*rt));
    return hr;
}

HRESULT d3d8_PgraphBindDepthSurface(UINT offset, UINT format)
{
    PgraphDepth *d=NULL; HRESULT hr=S_OK;
    UINT w=g_current_pgraph_rt?g_current_pgraph_rt->width:g_device_state.width;
    UINT h=g_current_pgraph_rt?g_current_pgraph_rt->height:g_device_state.height;
    if(offset && (format==1u || format==2u)) {
        for(unsigned i=0;i<PGRAPH_RT_COUNT;++i)if(g_pgraph_depth[i].texture && g_pgraph_depth[i].offset==offset){d=&g_pgraph_depth[i];break;}
        if(d && (d->width!=w||d->height!=h||d->format!=format)) {
            ID3D11DepthStencilView_Release(d->dsv);ID3D11Texture2D_Release(d->texture);memset(d,0,sizeof(*d));d=NULL;
        }
        if(!d) {
            for(unsigned i=0;i<PGRAPH_RT_COUNT;++i)if(!g_pgraph_depth[i].texture){d=&g_pgraph_depth[i];break;}
            if(!d) return E_OUTOFMEMORY;
            D3D11_TEXTURE2D_DESC td={0};td.Width=w;td.Height=h;td.MipLevels=1;td.ArraySize=1;
            td.Format=format==1u?DXGI_FORMAT_D16_UNORM:DXGI_FORMAT_D24_UNORM_S8_UINT;
            td.SampleDesc.Count=1;td.BindFlags=D3D11_BIND_DEPTH_STENCIL;
            hr=ID3D11Device_CreateTexture2D(g_device_state.d3d11_device,&td,NULL,&d->texture);
            if(FAILED(hr))return hr;
            hr=ID3D11Device_CreateDepthStencilView(g_device_state.d3d11_device,(ID3D11Resource*)d->texture,NULL,&d->dsv);
            if(FAILED(hr)){ID3D11Texture2D_Release(d->texture);memset(d,0,sizeof(*d));return hr;}
            d->offset=offset;d->width=w;d->height=h;d->format=format;
        }
    }
    g_current_dsv=d?d->dsv:NULL;
    ID3D11DeviceContext_OMSetRenderTargets(g_device_state.d3d11_context,1,&g_current_rtv,g_current_dsv);
    return hr;
}

HRESULT d3d8_PgraphBindRenderTargetTexture(DWORD stage, UINT offset)
{
    PgraphRenderTarget *rt;
    static struct { UINT requested, current, reason; } diagnostics[64];
    static UINT diagnostic_count;
    if (stage >= 4 || !g_device_state.d3d11_context) return E_INVALIDARG;
    rt = pgraph_find_rt(offset);
    if (!rt || !rt->srv || rt == g_current_pgraph_rt) {
        UINT current = g_current_pgraph_rt ? g_current_pgraph_rt->offset : 0u;
        UINT reason = !rt ? 1u : !rt->srv ? 2u : 3u;
        BOOL seen = FALSE;
        for (UINT i = 0; i < diagnostic_count; ++i)
            if (diagnostics[i].requested == offset && diagnostics[i].current == current &&
                diagnostics[i].reason == reason) { seen = TRUE; break; }
        if (!seen && diagnostic_count < 64u) {
            diagnostics[diagnostic_count].requested = offset;
            diagnostics[diagnostic_count].current = current;
            diagnostics[diagnostic_count].reason = reason;
            ++diagnostic_count;
            fprintf(stderr, "[PGRAPH-RT-TEXTURE-FAIL] stage=%lu requested=%08X current=%08X reason=%s known=",
                    (unsigned long)stage, offset,
                    g_current_pgraph_rt ? g_current_pgraph_rt->offset : 0u,
                    !rt ? "missing" : !rt->srv ? "no-srv" : "feedback");
            for (UINT i = 0; i < PGRAPH_RT_COUNT; ++i) {
                if (g_pgraph_rt[i].texture)
                    fprintf(stderr, "%s%08X:%ux%u", i ? "," : "",
                            g_pgraph_rt[i].offset, g_pgraph_rt[i].width,
                            g_pgraph_rt[i].height);
            }
            fprintf(stderr, "\n");
            fflush(stderr);
        }
        return E_FAIL;
    }
    ID3D11DeviceContext_PSSetShaderResources(g_device_state.d3d11_context,
                                             stage, 1, &rt->srv);
    return S_OK;
}

BOOL d3d8_PgraphTryBindRenderTargetTexture(DWORD stage, UINT offset)
{
    PgraphRenderTarget *rt;
    if (stage >= 4 || !g_device_state.d3d11_context) return FALSE;
    rt = pgraph_find_rt(offset);
    if (!rt || !rt->srv || rt == g_current_pgraph_rt) return FALSE;
    ID3D11DeviceContext_PSSetShaderResources(g_device_state.d3d11_context,
                                             stage, 1, &rt->srv);
    return TRUE;
}

static void pgraph_copy_presentable_to_swapchain(void)
{
    ID3D11Texture2D *backbuffer = NULL;
    if (!g_current_pgraph_presentable || !g_current_pgraph_rt ||
        !g_current_pgraph_rt->texture || !g_device_state.swap_chain) return;
    if (SUCCEEDED(IDXGISwapChain_GetBuffer(g_device_state.swap_chain, 0,
                    &IID_ID3D11Texture2D, (void **)&backbuffer))) {
        ID3D11DeviceContext_CopyResource(g_device_state.d3d11_context,
            (ID3D11Resource *)backbuffer,
            (ID3D11Resource *)g_current_pgraph_rt->texture);
        ID3D11Texture2D_Release(backbuffer);
    }
}

/* Loading transitions can briefly leave the new color target as a single
 * blue-gray clear before the first cinematic image is drawn. Read a sparse
 * grid from the current Xbox color target so the frame clock can keep the
 * previous loading image presented until real image variation exists. This is
 * used only during the bounded Farm warm-up. */
int d3d8_PresentableHasVisualContent(void)
{
    ID3D11Texture2D *staging = NULL;
    D3D11_TEXTURE2D_DESC desc = {0};
    D3D11_MAPPED_SUBRESOURCE mapped;
    HRESULT hr;
    UINT x, y, step_x, step_y;
    unsigned min_luma = 255u, max_luma = 0u, varied = 0u;
    int mapped_ok = 0, result = -1;

    if (!g_current_pgraph_presentable || !g_current_pgraph_rt ||
        !g_current_pgraph_rt->texture || !g_device_state.d3d11_device ||
        !g_device_state.d3d11_context)
        return -1;
    ID3D11Texture2D_GetDesc(g_current_pgraph_rt->texture, &desc);
    if (!desc.Width || !desc.Height || desc.SampleDesc.Count != 1u ||
        (desc.Format != DXGI_FORMAT_R8G8B8A8_UNORM &&
         desc.Format != DXGI_FORMAT_B8G8R8A8_UNORM &&
         desc.Format != DXGI_FORMAT_B8G8R8X8_UNORM))
        return -1;
    desc.MipLevels = 1u;
    desc.ArraySize = 1u;
    desc.Usage = D3D11_USAGE_STAGING;
    desc.BindFlags = 0u;
    desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
    desc.MiscFlags = 0u;
    hr = ID3D11Device_CreateTexture2D(g_device_state.d3d11_device,
                                      &desc, NULL, &staging);
    if (FAILED(hr)) goto cleanup;
    ID3D11DeviceContext_CopyResource(g_device_state.d3d11_context,
        (ID3D11Resource *)staging,
        (ID3D11Resource *)g_current_pgraph_rt->texture);
    hr = ID3D11DeviceContext_Map(g_device_state.d3d11_context,
        (ID3D11Resource *)staging, 0u, D3D11_MAP_READ, 0u, &mapped);
    if (FAILED(hr)) goto cleanup;
    mapped_ok = 1;
    step_x = desc.Width / 32u; if (!step_x) step_x = 1u;
    step_y = desc.Height / 24u; if (!step_y) step_y = 1u;
    for (y = step_y / 2u; y < desc.Height; y += step_y) {
        const BYTE *row = (const BYTE *)mapped.pData + (size_t)y * mapped.RowPitch;
        for (x = step_x / 2u; x < desc.Width; x += step_x) {
            const BYTE *pixel = row + (size_t)x * 4u;
            unsigned luma = (unsigned)pixel[0] + (unsigned)pixel[1] +
                            (unsigned)pixel[2];
            luma /= 3u;
            if (luma < min_luma) min_luma = luma;
            if (luma > max_luma) max_luma = luma;
            if (max_luma > min_luma + 12u) ++varied;
        }
    }
    result = varied >= 4u ? 1 : 0;

cleanup:
    if (mapped_ok)
        ID3D11DeviceContext_Unmap(g_device_state.d3d11_context,
                                  (ID3D11Resource *)staging, 0u);
    if (staging) ID3D11Texture2D_Release(staging);
    return result;
}
const DWORD         *d3d8_GetRenderStates(void) { return g_device_state.render_states; }
const DWORD         *d3d8_GetTSS(DWORD stage) { return (stage < MAX_TEXTURE_STAGES) ? g_device_state.tss[stage] : NULL; }
const D3DMATRIX     *d3d8_GetTransform(D3DTRANSFORMSTATETYPE type) {
    return ((DWORD)type < MAX_TRANSFORMS) ? &g_device_state.transforms[(DWORD)type] : NULL;
}

const D3DLIGHT8     *d3d8_GetLight(DWORD index) {
    return (index < MAX_LIGHTS) ? &g_device_state.lights[index] : NULL;
}

BOOL                 d3d8_GetLightEnable(DWORD index) {
    return (index < MAX_LIGHTS) ? g_device_state.light_enable[index] : FALSE;
}

const D3DMATERIAL8  *d3d8_GetMaterial(void) {
    return &g_device_state.material;
}

UINT                 d3d8_GetNumLights(void) {
    return MAX_LIGHTS;
}

/* ================================================================
 * D3D11 initialization helpers
 * ================================================================ */

static HRESULT d3d11_create_device_and_swap_chain(
    D3D8DeviceState *state,
    D3DPRESENT_PARAMETERS *pp)
{
    DXGI_SWAP_CHAIN_DESC scd;
    D3D_FEATURE_LEVEL feature_level;
    UINT create_flags = 0;
    HRESULT hr;

#ifdef _DEBUG
    create_flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    memset(&scd, 0, sizeof(scd));
    scd.BufferCount = pp->BackBufferCount ? pp->BackBufferCount : 1;
    scd.BufferDesc.Width = pp->BackBufferWidth ? pp->BackBufferWidth : 640;
    scd.BufferDesc.Height = pp->BackBufferHeight ? pp->BackBufferHeight : 480;
    scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    scd.BufferDesc.RefreshRate.Numerator = 60;
    scd.BufferDesc.RefreshRate.Denominator = 1;
    scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    scd.OutputWindow = pp->hDeviceWindow;
    scd.SampleDesc.Count = 1;
    scd.SampleDesc.Quality = 0;
    scd.Windowed = pp->Windowed;
    scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    /* Flip-model presentation avoids compositor-side stalls observed during
     * sustained gameplay. Keep the legacy path as an explicit diagnostic
     * fallback rather than making affected hosts opt in to the stable path. */
    const char *legacy_swapchain = getenv("DAH_LEGACY_SWAPCHAIN");
    if (!legacy_swapchain || legacy_swapchain[0] != '1' || legacy_swapchain[1] != '\0') {
        scd.BufferCount = 2;
        scd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
        fprintf(stderr, "[D3D8-SWAPCHAIN] flip-model presentation enabled\n");
    } else {
        fprintf(stderr, "[D3D8-SWAPCHAIN] legacy presentation requested\n");
    }

    fprintf(stderr,
            "[D3D8-SWAPCHAIN] hwnd=%p requested-windowed=%u visible=%u iconic=%u "
            "buffer=%ux%u count=%u swap=%u\n",
            (void *)scd.OutputWindow, (unsigned)pp->Windowed,
            scd.OutputWindow ? (unsigned)IsWindowVisible(scd.OutputWindow) : 0u,
            scd.OutputWindow ? (unsigned)IsIconic(scd.OutputWindow) : 0u,
            (unsigned)scd.BufferDesc.Width, (unsigned)scd.BufferDesc.Height,
            (unsigned)scd.BufferCount, (unsigned)scd.SwapEffect);
    fflush(stderr);

    hr = D3D11CreateDeviceAndSwapChain(
        NULL,
        D3D_DRIVER_TYPE_HARDWARE,
        NULL,
        create_flags,
        NULL, 0,
        D3D11_SDK_VERSION,
        &scd,
        &state->swap_chain,
        &state->d3d11_device,
        &feature_level,
        &state->d3d11_context
    );

    if (FAILED(hr)) {
        fprintf(stderr, "D3D8: Failed to create D3D11 device: 0x%08lX\n", hr);
        return hr;
    }

    fprintf(stderr, "[D3D8-SWAPCHAIN] created windowed=%u hwnd=%p hr=0x%08lX\n",
            (unsigned)scd.Windowed, (void *)scd.OutputWindow, (unsigned long)hr);
    fflush(stderr);

    state->hwnd = pp->hDeviceWindow;
    state->width = scd.BufferDesc.Width;
    state->height = scd.BufferDesc.Height;

    return S_OK;
}

static HRESULT d3d11_create_render_targets(D3D8DeviceState *state)
{
    ID3D11Texture2D *back_buffer = NULL;
    D3D11_TEXTURE2D_DESC depth_desc;
    HRESULT hr;

    /* Create render target view from swap chain back buffer */
    hr = IDXGISwapChain_GetBuffer(state->swap_chain, 0,
                                   &IID_ID3D11Texture2D,
                                   (void **)&back_buffer);
    if (FAILED(hr)) return hr;

    hr = ID3D11Device_CreateRenderTargetView(state->d3d11_device,
                                              (ID3D11Resource *)back_buffer,
                                              NULL, &state->default_rtv);
    ID3D11Texture2D_Release(back_buffer);
    if (FAILED(hr)) return hr;

    /* Create depth stencil */
    memset(&depth_desc, 0, sizeof(depth_desc));
    depth_desc.Width = state->width;
    depth_desc.Height = state->height;
    depth_desc.MipLevels = 1;
    depth_desc.ArraySize = 1;
    depth_desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    depth_desc.SampleDesc.Count = 1;
    depth_desc.SampleDesc.Quality = 0;
    depth_desc.Usage = D3D11_USAGE_DEFAULT;
    depth_desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;

    hr = ID3D11Device_CreateTexture2D(state->d3d11_device, &depth_desc,
                                       NULL, &state->default_depth);
    if (FAILED(hr)) return hr;

    hr = ID3D11Device_CreateDepthStencilView(state->d3d11_device,
                                              (ID3D11Resource *)state->default_depth,
                                              NULL, &state->default_dsv);
    if (FAILED(hr)) return hr;

    /* Bind default render targets */
    ID3D11DeviceContext_OMSetRenderTargets(state->d3d11_context, 1,
                                            &state->default_rtv,
                                            state->default_dsv);
    g_current_rtv = state->default_rtv;

    return S_OK;
}

static void d3d8_init_default_states(D3D8DeviceState *state)
{
    /* Set Xbox D3D8 default render states */
    memset(state->render_states, 0, sizeof(state->render_states));
    state->render_states[D3DRS_ZENABLE]           = 1;
    state->render_states[D3DRS_FILLMODE]          = D3DFILL_SOLID;
    state->render_states[D3DRS_SHADEMODE]         = 2; /* D3DSHADE_GOURAUD */
    state->render_states[D3DRS_ZWRITEENABLE]      = TRUE;
    state->render_states[D3DRS_ALPHATESTENABLE]    = FALSE;
    state->render_states[D3DRS_SRCBLEND]          = D3DBLEND_ONE;
    state->render_states[D3DRS_DESTBLEND]         = D3DBLEND_ZERO;
    state->render_states[D3DRS_CULLMODE]          = D3DCULL_CCW;
    state->render_states[D3DRS_ZFUNC]             = D3DCMP_LESSEQUAL;
    state->render_states[D3DRS_ALPHAREF]          = 0;
    state->render_states[D3DRS_ALPHAFUNC]         = D3DCMP_ALWAYS;
    state->render_states[D3DRS_ALPHABLENDENABLE]   = FALSE;
    state->render_states[D3DRS_FOGENABLE]         = FALSE;
    state->render_states[D3DRS_STENCILENABLE]     = FALSE;
    state->render_states[D3DRS_COLORWRITEENABLE]  = 0x0F;

    /* Texture arguments can legitimately be zero (D3DTA_DIFFUSE). Seed
     * defaults here so draw preparation never needs to interpret zero as
     * an unset value and replace a game's explicit diffuse argument. */
    memset(state->tss, 0, sizeof(state->tss));
    for (UINT stage = 0; stage < MAX_TEXTURE_STAGES; ++stage) {
        state->tss[stage][D3DTSS_COLOROP] =
            stage == 0 ? D3DTOP_MODULATE : D3DTOP_DISABLE;
        state->tss[stage][D3DTSS_COLORARG1] = D3DTA_TEXTURE;
        state->tss[stage][D3DTSS_COLORARG2] = D3DTA_CURRENT;
        state->tss[stage][D3DTSS_ALPHAOP] =
            stage == 0 ? D3DTOP_SELECTARG1 : D3DTOP_DISABLE;
        state->tss[stage][D3DTSS_ALPHAARG1] = D3DTA_TEXTURE;
        state->tss[stage][D3DTSS_ALPHAARG2] = D3DTA_CURRENT;
        state->tss[stage][D3DTSS_TEXCOORDINDEX] = stage;
    }

    /* Default viewport */
    state->viewport.X = 0;
    state->viewport.Y = 0;
    state->viewport.Width = state->width;
    state->viewport.Height = state->height;
    state->viewport.MinZ = 0.0f;
    state->viewport.MaxZ = 1.0f;

    /* Identity matrices */
    for (int i = 0; i < MAX_TRANSFORMS; i++) {
        memset(&state->transforms[i], 0, sizeof(D3DMATRIX));
        state->transforms[i]._11 = 1.0f;
        state->transforms[i]._22 = 1.0f;
        state->transforms[i]._33 = 1.0f;
        state->transforms[i]._44 = 1.0f;
    }

    state->vertex_shader = 0;
    state->pixel_shader = 0;
    state->in_scene = FALSE;
}

/* ================================================================
 * IDirect3DDevice8 method implementations
 * ================================================================ */

static HRESULT __stdcall dev_QueryInterface(IDirect3DDevice8 *self, const IID *riid, void **ppv)
{
    (void)self; (void)riid; (void)ppv;
    return E_NOINTERFACE;
}

static ULONG __stdcall dev_AddRef(IDirect3DDevice8 *self)
{
    (void)self;
    return InterlockedIncrement(&g_device_state.ref_count);
}

static ULONG __stdcall dev_Release(IDirect3DDevice8 *self)
{
    (void)self;
    LONG ref = InterlockedDecrement(&g_device_state.ref_count);
    if (ref <= 0) {
        if (g_host_frame_texture) {
            g_host_frame_texture->lpVtbl->Release(g_host_frame_texture);
            g_host_frame_texture = NULL;
            g_host_frame_width = g_host_frame_height = 0;
        }
        /* Cleanup subsystems first */
        up_ring_shutdown();
        d3d8_vsh_shutdown();
        d3d8_combiners_shutdown();
        d3d8_states_shutdown();
        d3d8_shaders_shutdown();

        /* Cleanup D3D11 resources */
        D3D8DeviceState *s = &g_device_state;
        for(unsigned i=0;i<PGRAPH_RT_COUNT;++i){if(g_pgraph_depth[i].dsv)ID3D11DepthStencilView_Release(g_pgraph_depth[i].dsv);if(g_pgraph_depth[i].texture)ID3D11Texture2D_Release(g_pgraph_depth[i].texture);memset(&g_pgraph_depth[i],0,sizeof(g_pgraph_depth[i]));}g_current_dsv=NULL;
        if (s->default_dsv) { ID3D11DepthStencilView_Release(s->default_dsv); s->default_dsv = NULL; }
        if (s->default_depth) { ID3D11Texture2D_Release(s->default_depth); s->default_depth = NULL; }
        for (UINT i = 0; i < PGRAPH_RT_COUNT; ++i) {
            if (g_pgraph_rt[i].srv) ID3D11ShaderResourceView_Release(g_pgraph_rt[i].srv);
            if (g_pgraph_rt[i].rtv) ID3D11RenderTargetView_Release(g_pgraph_rt[i].rtv);
            if (g_pgraph_rt[i].texture) ID3D11Texture2D_Release(g_pgraph_rt[i].texture);
        }
        memset(g_pgraph_rt, 0, sizeof(g_pgraph_rt));
        g_current_rtv = NULL;
        g_current_pgraph_rt = NULL;
        g_current_pgraph_presentable = FALSE;
        if (s->default_rtv) { ID3D11RenderTargetView_Release(s->default_rtv); s->default_rtv = NULL; }
        if (s->swap_chain) { IDXGISwapChain_Release(s->swap_chain); s->swap_chain = NULL; }
        if (s->d3d11_context) { ID3D11DeviceContext_Release(s->d3d11_context); s->d3d11_context = NULL; }
        if (s->d3d11_device) { ID3D11Device_Release(s->d3d11_device); s->d3d11_device = NULL; }
        g_device_initialized = FALSE;
    }
    return (ULONG)ref;
}

static HRESULT __stdcall dev_GetDirect3D(IDirect3DDevice8 *self, IDirect3D8 **ppD3D8)
{
    (void)self; (void)ppD3D8;
    /* TODO: return the factory */
    return E_NOTIMPL;
}

static HRESULT __stdcall dev_GetDeviceCaps(IDirect3DDevice8 *self, void *pCaps)
{
    (void)self; (void)pCaps;
    /* TODO: fill with Xbox NV2A capabilities */
    return S_OK;
}

static HRESULT __stdcall dev_GetDisplayMode(IDirect3DDevice8 *self, void *pMode)
{
    (void)self; (void)pMode;
    return S_OK;
}

static HRESULT __stdcall dev_GetCreationParameters(IDirect3DDevice8 *self, void *pParams)
{
    (void)self; (void)pParams;
    return S_OK;
}

static HRESULT __stdcall dev_Reset(IDirect3DDevice8 *self, D3DPRESENT_PARAMETERS *pPP)
{
    (void)self; (void)pPP;
    /* TODO: resize swap chain */
    return S_OK;
}

static DWORD g_d3d_begin_count = 0;
static DWORD g_d3d_end_count = 0;
static DWORD g_d3d_clear_count = 0;
static DWORD g_d3d_draw_count = 0;
static DWORD g_d3d_settransform_count = 0;
static DWORD g_d3d_setrs_count = 0;
static DWORD g_d3d_settexture_count = 0;

static HRESULT __stdcall dev_Present(IDirect3DDevice8 *self, const RECT *src, const RECT *dst, HWND hWnd, void *pDirty)
{
    static DWORD frame_count = 0;
    static DWORD last_tick = 0;
    (void)self; (void)src; (void)dst; (void)hWnd; (void)pDirty;

    frame_count++;
    DWORD now = GetTickCount();
    if (last_tick == 0) last_tick = now;
    if (now - last_tick >= 2000) {
        fprintf(stderr, "  [D3D] %.1fs: %u present (%.1f fps), %u begin, %u end, "
                "%u clear, %u draw, %u xform, %u rs, %u tex\n",
                (now - last_tick) / 1000.0, frame_count,
                frame_count * 1000.0 / (now - last_tick),
                g_d3d_begin_count, g_d3d_end_count,
                g_d3d_clear_count, g_d3d_draw_count,
                g_d3d_settransform_count, g_d3d_setrs_count,
                g_d3d_settexture_count);
        fflush(stderr);
        frame_count = 0;
        g_d3d_begin_count = g_d3d_end_count = 0;
        g_d3d_clear_count = g_d3d_draw_count = 0;
        g_d3d_settransform_count = g_d3d_setrs_count = 0;
        g_d3d_settexture_count = 0;
        last_tick = now;
    }

    /* Pump Windows messages: the game's internal main loop drives rendering,
     * so our external message pump never runs. Process messages here to keep
     * the window responsive and handle input. */
    MSG msg;
    while (PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE)) {
        if (msg.message == WM_QUIT) {
            ExitProcess(0);
        }
        TranslateMessage(&msg);
        DispatchMessageA(&msg);
    }

    capture_swapchain_frame();
    {
        HRESULT result = IDXGISwapChain_Present(g_device_state.swap_chain, 1, 0);
        g_full_screen_movie_frame = FALSE;
        return result;
    }
}

static HRESULT __stdcall dev_GetBackBuffer(IDirect3DDevice8 *self, INT iBackBuffer, DWORD Type, IDirect3DSurface8 **ppSurface)
{
    (void)self; (void)iBackBuffer; (void)Type; (void)ppSurface;
    /* TODO: wrap back buffer as D3D8 surface */
    return E_NOTIMPL;
}

static HRESULT __stdcall dev_BeginScene(IDirect3DDevice8 *self)
{
    (void)self;
    g_device_state.in_scene = TRUE;
    g_d3d_begin_count++;
    return S_OK;
}

static HRESULT __stdcall dev_EndScene(IDirect3DDevice8 *self)
{
    (void)self;
    g_device_state.in_scene = FALSE;
    g_d3d_end_count++;
    return S_OK;
}

static HRESULT __stdcall dev_Clear(IDirect3DDevice8 *self, DWORD Count, const D3DRECT *pRects, DWORD Flags, D3DCOLOR Color, float Z, DWORD Stencil)
{
    (void)self; (void)Count; (void)pRects; (void)Stencil;
    g_d3d_clear_count++;

    if (Flags & D3DCLEAR_TARGET) {
        float clear_color[4] = {
            ((Color >> 16) & 0xFF) / 255.0f,  /* R */
            ((Color >>  8) & 0xFF) / 255.0f,  /* G */
            ((Color >>  0) & 0xFF) / 255.0f,  /* B */
            ((Color >> 24) & 0xFF) / 255.0f,  /* A */
        };
        ID3D11DeviceContext_ClearRenderTargetView(g_device_state.d3d11_context,
                                                   g_current_rtv ? g_current_rtv : g_device_state.default_rtv,
                                                   clear_color);
    }

    if ((Flags & (D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL)) && (g_current_pgraph_rt ? g_current_dsv : g_device_state.default_dsv)) {
        UINT clear_flags = 0;
        if (Flags & D3DCLEAR_ZBUFFER) clear_flags |= D3D11_CLEAR_DEPTH;
        if (Flags & D3DCLEAR_STENCIL) clear_flags |= D3D11_CLEAR_STENCIL;

        ID3D11DeviceContext_ClearDepthStencilView(g_device_state.d3d11_context,
                                                    g_current_pgraph_rt ? g_current_dsv : g_device_state.default_dsv,
                                                    clear_flags, Z, (UINT8)Stencil);
    }

    return S_OK;
}

static HRESULT __stdcall dev_SetTransform(IDirect3DDevice8 *self, D3DTRANSFORMSTATETYPE State, const D3DMATRIX *pMatrix)
{
    (void)self;
    g_d3d_settransform_count++;
    if ((DWORD)State < MAX_TRANSFORMS && pMatrix) {
        g_device_state.transforms[(DWORD)State] = *pMatrix;
    }
    return S_OK;
}

static HRESULT __stdcall dev_GetTransform(IDirect3DDevice8 *self, D3DTRANSFORMSTATETYPE State, D3DMATRIX *pMatrix)
{
    (void)self;
    if ((DWORD)State < MAX_TRANSFORMS && pMatrix) {
        *pMatrix = g_device_state.transforms[(DWORD)State];
    }
    return S_OK;
}

static HRESULT __stdcall dev_SetRenderState(IDirect3DDevice8 *self, D3DRENDERSTATETYPE State, DWORD Value)
{
    (void)self;
    g_d3d_setrs_count++;
    if ((DWORD)State < MAX_RENDER_STATES) {
        g_device_state.render_states[(DWORD)State] = Value;
    }
    /* Mark combiner state dirty if any PS register combiner state changed */
    if ((DWORD)State >= D3DRS_PSALPHAINPUTS0 && (DWORD)State <= D3DRS_PSINPUTTEXTURE) {
        d3d8_combiners_mark_dirty();
    }
    return S_OK;
}

static HRESULT __stdcall dev_GetRenderState(IDirect3DDevice8 *self, D3DRENDERSTATETYPE State, DWORD *pValue)
{
    (void)self;
    if ((DWORD)State < MAX_RENDER_STATES && pValue) {
        *pValue = g_device_state.render_states[(DWORD)State];
    }
    return S_OK;
}

static HRESULT __stdcall dev_SetTextureStageState(IDirect3DDevice8 *self, DWORD Stage, D3DTEXTURESTAGESTATETYPE Type, DWORD Value)
{
    (void)self;
    if (Stage < MAX_TEXTURE_STAGES && (DWORD)Type < MAX_TSS_STATES) {
        g_device_state.tss[Stage][(DWORD)Type] = Value;
    }
    return S_OK;
}

static HRESULT __stdcall dev_GetTextureStageState(IDirect3DDevice8 *self, DWORD Stage, D3DTEXTURESTAGESTATETYPE Type, DWORD *pValue)
{
    (void)self;
    if (Stage < MAX_TEXTURE_STAGES && (DWORD)Type < MAX_TSS_STATES && pValue) {
        *pValue = g_device_state.tss[Stage][(DWORD)Type];
    }
    return S_OK;
}

static HRESULT __stdcall dev_SetTexture(IDirect3DDevice8 *self, DWORD Stage, IDirect3DBaseTexture8 *pTexture)
{
    (void)self;
    g_d3d_settexture_count++;
    if (Stage >= 4) return E_INVALIDARG;
    g_cur_textures[Stage] = pTexture;

    /* Bind SRV to pixel shader */
    if (pTexture) {
        D3D8Texture *tex = (D3D8Texture *)pTexture;
        if (tex->srv) {
            ID3D11DeviceContext_PSSetShaderResources(g_device_state.d3d11_context,
                Stage, 1, &tex->srv);
        }
        /* Mark texture stage as active */
        if (g_device_state.tss[Stage][D3DTSS_COLOROP] == D3DTOP_DISABLE)
            g_device_state.tss[Stage][D3DTSS_COLOROP] = D3DTOP_MODULATE;
    } else {
        ID3D11ShaderResourceView *null_srv = NULL;
        ID3D11DeviceContext_PSSetShaderResources(g_device_state.d3d11_context,
            Stage, 1, &null_srv);
        g_device_state.tss[Stage][D3DTSS_COLOROP] = D3DTOP_DISABLE;
    }
    return S_OK;
}

static HRESULT __stdcall dev_GetTexture(IDirect3DDevice8 *self, DWORD Stage, IDirect3DBaseTexture8 **ppTexture)
{
    (void)self; (void)Stage; (void)ppTexture;
    return E_NOTIMPL;
}

static HRESULT __stdcall dev_SetStreamSource(IDirect3DDevice8 *self, UINT StreamNumber, IDirect3DVertexBuffer8 *pStreamData, UINT Stride)
{
    (void)self;
    if (StreamNumber != 0) return S_OK; /* Only stream 0 supported */
    g_cur_vb = pStreamData;
    g_cur_vb_stride = Stride;

    if (pStreamData) {
        D3D8VertexBuffer *vb = (D3D8VertexBuffer *)pStreamData;
        UINT offset = 0;
        ID3D11DeviceContext_IASetVertexBuffers(g_device_state.d3d11_context,
            0, 1, &vb->d3d11_buffer, &Stride, &offset);
    }
    return S_OK;
}

static HRESULT __stdcall dev_GetStreamSource(IDirect3DDevice8 *self, UINT StreamNumber, IDirect3DVertexBuffer8 **ppStreamData, UINT *pStride)
{
    (void)self; (void)StreamNumber; (void)ppStreamData; (void)pStride;
    return E_NOTIMPL;
}

static HRESULT __stdcall dev_SetIndices(IDirect3DDevice8 *self, IDirect3DIndexBuffer8 *pIndexData, UINT BaseVertexIndex)
{
    (void)self;
    g_cur_ib = pIndexData;
    g_cur_ib_base_vertex = BaseVertexIndex;

    if (pIndexData) {
        D3D8IndexBuffer *ib = (D3D8IndexBuffer *)pIndexData;
        DXGI_FORMAT fmt = (ib->format == D3DFMT_INDEX32)
            ? DXGI_FORMAT_R32_UINT : DXGI_FORMAT_R16_UINT;
        ID3D11DeviceContext_IASetIndexBuffer(g_device_state.d3d11_context,
            ib->d3d11_buffer, fmt, 0);
    }
    return S_OK;
}

static HRESULT __stdcall dev_GetIndices(IDirect3DDevice8 *self, IDirect3DIndexBuffer8 **ppIndexData, UINT *pBaseVertexIndex)
{
    (void)self; (void)ppIndexData; (void)pBaseVertexIndex;
    return E_NOTIMPL;
}

static D3D11_PRIMITIVE_TOPOLOGY map_primitive_type(D3DPRIMITIVETYPE pt, UINT count, UINT *out_count)
{
    switch (pt) {
    case D3DPT_TRIANGLELIST:  *out_count = count * 3; return D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
    case D3DPT_TRIANGLESTRIP: *out_count = count + 2; return D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
    case D3DPT_TRIANGLEFAN:   *out_count = count * 3; return D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
    case D3DPT_LINELIST:      *out_count = count * 2; return D3D11_PRIMITIVE_TOPOLOGY_LINELIST;
    case D3DPT_LINESTRIP:     *out_count = count + 1; return D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP;
    case D3DPT_POINTLIST:     *out_count = count;     return D3D11_PRIMITIVE_TOPOLOGY_POINTLIST;
    case D3DPT_QUADLIST:      *out_count = count * 6; return D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
    default:                  *out_count = 0;          return D3D11_PRIMITIVE_TOPOLOGY_UNDEFINED;
    }
}

/* ================================================================
 * Triangle fan / quad list → triangle list conversion
 *
 * D3D11 doesn't support triangle fans or quad lists.
 * Convert vertex data in-place to triangle list.
 * Returns malloc'd buffer (caller must free) or NULL if no conversion needed.
 * ================================================================ */

static void *convert_fan_or_quad(D3DPRIMITIVETYPE pt, const void *src,
                                  UINT prim_count, UINT stride,
                                  UINT *out_vertex_count)
{
    BYTE *dst;
    const BYTE *s = (const BYTE *)src;
    UINT i;

    if (pt == D3DPT_TRIANGLEFAN) {
        /* Fan: vertex 0 is the hub, each triangle is (0, i+1, i+2) */
        UINT tri_verts = prim_count * 3;
        dst = (BYTE *)malloc(tri_verts * stride);
        if (!dst) return NULL;

        for (i = 0; i < prim_count; i++) {
            memcpy(dst + (i * 3 + 0) * stride, s, stride);                      /* v0 (hub) */
            memcpy(dst + (i * 3 + 1) * stride, s + (i + 1) * stride, stride);   /* v[i+1] */
            memcpy(dst + (i * 3 + 2) * stride, s + (i + 2) * stride, stride);   /* v[i+2] */
        }
        *out_vertex_count = tri_verts;
        return dst;
    }

    if (pt == D3DPT_QUADLIST) {
        /* Quad list: each quad (v0,v1,v2,v3) → 2 triangles (v0,v1,v2), (v0,v2,v3) */
        UINT tri_verts = prim_count * 6;
        dst = (BYTE *)malloc(tri_verts * stride);
        if (!dst) return NULL;

        for (i = 0; i < prim_count; i++) {
            const BYTE *q = s + i * 4 * stride;
            memcpy(dst + (i * 6 + 0) * stride, q + 0 * stride, stride);  /* v0 */
            memcpy(dst + (i * 6 + 1) * stride, q + 1 * stride, stride);  /* v1 */
            memcpy(dst + (i * 6 + 2) * stride, q + 2 * stride, stride);  /* v2 */
            memcpy(dst + (i * 6 + 3) * stride, q + 0 * stride, stride);  /* v0 */
            memcpy(dst + (i * 6 + 4) * stride, q + 2 * stride, stride);  /* v2 */
            memcpy(dst + (i * 6 + 5) * stride, q + 3 * stride, stride);  /* v3 */
        }
        *out_vertex_count = tri_verts;
        return dst;
    }

    return NULL; /* no conversion needed */
}

/* ================================================================
 * DrawPrimitiveUP ring buffer
 *
 * Instead of creating and destroying a D3D11 buffer on every
 * DrawPrimitiveUP call, use a persistent ring buffer.
 * ================================================================ */

#define UP_RING_BUFFER_SIZE (4 * 1024 * 1024)  /* 4MB ring buffer */

static ID3D11Buffer *g_up_ring_buffer = NULL;
static UINT          g_up_ring_offset = 0;

static HRESULT up_ring_init(void)
{
    D3D11_BUFFER_DESC bd;
    memset(&bd, 0, sizeof(bd));
    bd.ByteWidth = UP_RING_BUFFER_SIZE;
    bd.Usage = D3D11_USAGE_DYNAMIC;
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    return ID3D11Device_CreateBuffer(g_device_state.d3d11_device, &bd, NULL, &g_up_ring_buffer);
}

static void up_ring_shutdown(void)
{
    if (g_up_ring_buffer) {
        ID3D11Buffer_Release(g_up_ring_buffer);
        g_up_ring_buffer = NULL;
    }
    g_up_ring_offset = 0;
}

/* Upload vertex data to ring buffer, returns offset. Returns (UINT)-1 on failure. */
static UINT up_ring_upload(const void *data, UINT size)
{
    D3D11_MAPPED_SUBRESOURCE mapped;
    D3D11_MAP map_type;
    HRESULT hr;
    UINT offset;

    if (!g_up_ring_buffer) {
        if (FAILED(up_ring_init())) return (UINT)-1;
    }

    if (size > UP_RING_BUFFER_SIZE) return (UINT)-1;

    /* Wrap around if not enough space */
    if (g_up_ring_offset + size > UP_RING_BUFFER_SIZE) {
        g_up_ring_offset = 0;
        map_type = D3D11_MAP_WRITE_DISCARD;
    } else {
        map_type = D3D11_MAP_WRITE_NO_OVERWRITE;
    }

    hr = ID3D11DeviceContext_Map(g_device_state.d3d11_context,
        (ID3D11Resource *)g_up_ring_buffer, 0, map_type, 0, &mapped);
    if (FAILED(hr)) return (UINT)-1;

    offset = g_up_ring_offset;
    memcpy((BYTE *)mapped.pData + offset, data, size);

    ID3D11DeviceContext_Unmap(g_device_state.d3d11_context,
        (ID3D11Resource *)g_up_ring_buffer, 0);

    g_up_ring_offset = (offset + size + 15) & ~15;  /* 16-byte align */
    return offset;
}

static HRESULT __stdcall dev_DrawPrimitive(IDirect3DDevice8 *self, D3DPRIMITIVETYPE PrimitiveType, UINT StartVertex, UINT PrimitiveCount)
{
    (void)self;
    g_d3d_draw_count++;
    D3D11_PRIMITIVE_TOPOLOGY topology;
    UINT vertex_count;

    topology = map_primitive_type(PrimitiveType, PrimitiveCount, &vertex_count);
    if (vertex_count == 0) return E_INVALIDARG;

    /* Prepare pipeline: shaders, input layout, constant buffers, render states */
    /* Vertex shader: try programmable VS first, fall back to FVF fixed-function */
    if (!d3d8_vsh_prepare_draw(g_device_state.vertex_shader))
        d3d8_shaders_prepare_draw(g_device_state.vertex_shader);
    d3d8_combiners_prepare_draw(); /* overrides PS if combiner shader is active */
    d3d8_states_apply();

    ID3D11DeviceContext_IASetPrimitiveTopology(g_device_state.d3d11_context, topology);
    ID3D11DeviceContext_Draw(g_device_state.d3d11_context, vertex_count, StartVertex);
    return S_OK;
}

static HRESULT __stdcall dev_DrawIndexedPrimitive(IDirect3DDevice8 *self, D3DPRIMITIVETYPE PrimitiveType, UINT MinVertexIndex, UINT NumVertices, UINT StartIndex, UINT PrimitiveCount)
{
    (void)self; (void)MinVertexIndex; (void)NumVertices;
    g_d3d_draw_count++;
    D3D11_PRIMITIVE_TOPOLOGY topology;
    UINT index_count;

    topology = map_primitive_type(PrimitiveType, PrimitiveCount, &index_count);
    if (index_count == 0) return E_INVALIDARG;

    /* Vertex shader: try programmable VS first, fall back to FVF fixed-function */
    if (!d3d8_vsh_prepare_draw(g_device_state.vertex_shader))
        d3d8_shaders_prepare_draw(g_device_state.vertex_shader);
    d3d8_combiners_prepare_draw(); /* overrides PS if combiner shader is active */
    d3d8_states_apply();

    ID3D11DeviceContext_IASetPrimitiveTopology(g_device_state.d3d11_context, topology);
    ID3D11DeviceContext_DrawIndexed(g_device_state.d3d11_context, index_count, StartIndex, (INT)g_cur_ib_base_vertex);
    return S_OK;
}

static HRESULT __stdcall dev_DrawPrimitiveUP(IDirect3DDevice8 *self, D3DPRIMITIVETYPE PrimitiveType, UINT PrimitiveCount, const void *pVertexData, UINT VertexStreamZeroStride)
{
    (void)self;
    g_d3d_draw_count++;
    D3D11_PRIMITIVE_TOPOLOGY topology;
    UINT vertex_count, vb_size, ring_offset;
    const void *draw_data = pVertexData;
    void *converted = NULL;

    if (!pVertexData || !VertexStreamZeroStride) return E_INVALIDARG;

    topology = map_primitive_type(PrimitiveType, PrimitiveCount, &vertex_count);
    if (vertex_count == 0) return E_INVALIDARG;

    /* Convert triangle fans and quad lists to triangle lists */
    if (PrimitiveType == D3DPT_TRIANGLEFAN || PrimitiveType == D3DPT_QUADLIST) {
        converted = convert_fan_or_quad(PrimitiveType, pVertexData,
                                         PrimitiveCount, VertexStreamZeroStride,
                                         &vertex_count);
        if (converted) draw_data = converted;
    }

    vb_size = vertex_count * VertexStreamZeroStride;

    /* Upload to ring buffer */
    ring_offset = up_ring_upload(draw_data, vb_size);
    if (converted) free(converted);

    if (ring_offset == (UINT)-1) return E_OUTOFMEMORY;

    /* Bind ring buffer at the right offset */
    ID3D11DeviceContext_IASetVertexBuffers(g_device_state.d3d11_context,
        0, 1, &g_up_ring_buffer, &VertexStreamZeroStride, &ring_offset);

    /* Vertex shader: try programmable VS first, fall back to FVF fixed-function */
    if (!d3d8_vsh_prepare_draw(g_device_state.vertex_shader))
        d3d8_shaders_prepare_draw(g_device_state.vertex_shader);
    d3d8_combiners_prepare_draw(); /* overrides PS if combiner shader is active */
    d3d8_states_apply();

    ID3D11DeviceContext_IASetPrimitiveTopology(g_device_state.d3d11_context, topology);
    ID3D11DeviceContext_Draw(g_device_state.d3d11_context, vertex_count, 0);

    /* Restore previous VB binding if any */
    if (g_cur_vb) {
        D3D8VertexBuffer *vb = (D3D8VertexBuffer *)g_cur_vb;
        UINT restore_offset = 0;
        ID3D11DeviceContext_IASetVertexBuffers(g_device_state.d3d11_context,
            0, 1, &vb->d3d11_buffer, &g_cur_vb_stride, &restore_offset);
    }
    return S_OK;
}

static HRESULT __stdcall dev_DrawIndexedPrimitiveUP(IDirect3DDevice8 *self, D3DPRIMITIVETYPE PrimitiveType, UINT MinVertexIndex, UINT NumVertices, UINT PrimitiveCount, const void *pIndexData, D3DFORMAT IndexDataFormat, const void *pVertexData, UINT VertexStreamZeroStride)
{
    (void)self; (void)MinVertexIndex;
    g_d3d_draw_count++;
    D3D11_PRIMITIVE_TOPOLOGY topology;
    D3D11_BUFFER_DESC bd;
    D3D11_SUBRESOURCE_DATA sd;
    ID3D11Buffer *tmp_vb = NULL, *tmp_ib = NULL;
    UINT index_count, vb_size, ib_size, offset = 0;
    UINT idx_bytes;
    DXGI_FORMAT ib_fmt;
    HRESULT hr;

    if (!pVertexData || !pIndexData || !VertexStreamZeroStride) return E_INVALIDARG;

    topology = map_primitive_type(PrimitiveType, PrimitiveCount, &index_count);
    if (index_count == 0) return E_INVALIDARG;

    idx_bytes = (IndexDataFormat == D3DFMT_INDEX32) ? 4 : 2;
    ib_fmt = (IndexDataFormat == D3DFMT_INDEX32) ? DXGI_FORMAT_R32_UINT : DXGI_FORMAT_R16_UINT;
    vb_size = NumVertices * VertexStreamZeroStride;
    ib_size = index_count * idx_bytes;

    /* Create temp vertex buffer */
    memset(&bd, 0, sizeof(bd));
    bd.ByteWidth = vb_size;
    bd.Usage = D3D11_USAGE_IMMUTABLE;
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    memset(&sd, 0, sizeof(sd));
    sd.pSysMem = pVertexData;
    hr = ID3D11Device_CreateBuffer(g_device_state.d3d11_device, &bd, &sd, &tmp_vb);
    if (FAILED(hr)) return hr;

    /* Create temp index buffer */
    bd.ByteWidth = ib_size;
    bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
    sd.pSysMem = pIndexData;
    hr = ID3D11Device_CreateBuffer(g_device_state.d3d11_device, &bd, &sd, &tmp_ib);
    if (FAILED(hr)) { ID3D11Buffer_Release(tmp_vb); return hr; }

    /* Bind, prepare, draw */
    ID3D11DeviceContext_IASetVertexBuffers(g_device_state.d3d11_context,
        0, 1, &tmp_vb, &VertexStreamZeroStride, &offset);
    ID3D11DeviceContext_IASetIndexBuffer(g_device_state.d3d11_context,
        tmp_ib, ib_fmt, 0);

    /* Vertex shader: try programmable VS first, fall back to FVF fixed-function */
    if (!d3d8_vsh_prepare_draw(g_device_state.vertex_shader))
        d3d8_shaders_prepare_draw(g_device_state.vertex_shader);
    d3d8_combiners_prepare_draw(); /* overrides PS if combiner shader is active */
    d3d8_states_apply();

    ID3D11DeviceContext_IASetPrimitiveTopology(g_device_state.d3d11_context, topology);
    ID3D11DeviceContext_DrawIndexed(g_device_state.d3d11_context, index_count, 0, 0);

    /* Cleanup temp buffers */
    ID3D11Buffer_Release(tmp_ib);
    ID3D11Buffer_Release(tmp_vb);

    /* Restore previous bindings */
    if (g_cur_vb) {
        D3D8VertexBuffer *vb = (D3D8VertexBuffer *)g_cur_vb;
        offset = 0;
        ID3D11DeviceContext_IASetVertexBuffers(g_device_state.d3d11_context,
            0, 1, &vb->d3d11_buffer, &g_cur_vb_stride, &offset);
    }
    if (g_cur_ib) {
        D3D8IndexBuffer *ib = (D3D8IndexBuffer *)g_cur_ib;
        DXGI_FORMAT fmt = (ib->format == D3DFMT_INDEX32) ? DXGI_FORMAT_R32_UINT : DXGI_FORMAT_R16_UINT;
        ID3D11DeviceContext_IASetIndexBuffer(g_device_state.d3d11_context,
            ib->d3d11_buffer, fmt, 0);
    }
    return S_OK;
}

/* Draw a host-provided BGRA frame through the same fixed-function D3D8
 * compatibility path used by the game. This is used only by an opt-in
 * bring-up movie probe while the retail Bink/native UI bridge is completed. */
int d3d8_DrawHostFrameBgra(const void *pixels, UINT width, UINT height, UINT pitch)
{
    typedef struct HostVertex {
        float x, y, z, rhw;
        float u, v;
    } HostVertex;
    D3D8Texture *tex;
    HostVertex vertices[4];
    UINT row;
    UINT copy_pitch;
    DWORD fvf = D3DFVF_XYZRHW | D3DFVF_TEX1;
    DWORD old_vertex_shader;
    DWORD old_pixel_shader;
    DWORD old_zenable;
    DWORD old_zwrite;
    DWORD old_alphablend;
    DWORD old_cull;
    DWORD old_colorop;
    DWORD old_colorarg1;
    DWORD old_alphaop;
    DWORD old_alphaarg1;
    IDirect3DBaseTexture8 *old_texture;
    HRESULT draw_result;

    if (!pixels || !width || !height || !pitch ||
        !g_device_state.d3d11_context || !g_device_state.default_rtv)
        return 0;

    if (!g_host_frame_texture || g_host_frame_width != width ||
        g_host_frame_height != height) {
        if (g_host_frame_texture)
            g_host_frame_texture->lpVtbl->Release(g_host_frame_texture);
        g_host_frame_texture = NULL;
        g_host_frame_width = g_host_frame_height = 0;
        if (FAILED(d3d8_CreateTextureImpl(width, height, 1, 0,
                                          D3DFMT_A8R8G8B8,
                                          &g_host_frame_texture)))
            return 0;
        g_host_frame_width = width;
        g_host_frame_height = height;
        fprintf(stderr, "[DAH-HOST-FRAME] texture=%ux%u created\n",
                width, height);
        fflush(stderr);
    }

    tex = (D3D8Texture *)g_host_frame_texture;
    copy_pitch = width * 4u;
    if (pitch < copy_pitch || !tex->d3d11_texture) return 0;
    for (row = 0; row < height; ++row)
        memcpy(tex->sys_mem + row * tex->pitch,
               (const BYTE *)pixels + row * pitch, copy_pitch);
    ID3D11DeviceContext_UpdateSubresource(
        g_device_state.d3d11_context,
        (ID3D11Resource *)tex->d3d11_texture,
        0, NULL, tex->sys_mem, tex->pitch, tex->pitch * height);

    /* Save the tracked retail state. The host quad is a presentation probe,
     * not a new game draw, so the next retail call must see exactly what it
     * left behind. */
    old_vertex_shader = g_device_state.vertex_shader;
    old_pixel_shader = g_device_state.pixel_shader;
    old_zenable = g_device_state.render_states[D3DRS_ZENABLE];
    old_zwrite = g_device_state.render_states[D3DRS_ZWRITEENABLE];
    old_alphablend = g_device_state.render_states[D3DRS_ALPHABLENDENABLE];
    old_cull = g_device_state.render_states[D3DRS_CULLMODE];
    old_colorop = g_device_state.tss[0][D3DTSS_COLOROP];
    old_colorarg1 = g_device_state.tss[0][D3DTSS_COLORARG1];
    old_alphaop = g_device_state.tss[0][D3DTSS_ALPHAOP];
    old_alphaarg1 = g_device_state.tss[0][D3DTSS_ALPHAARG1];
    old_texture = g_cur_textures[0];

    /* Put the host quad over the full backbuffer, independent of the retail
     * transform/state left by the translated frame. */
    g_device_state.vertex_shader = fvf;
    g_device_state.pixel_shader = 0;
    d3d8_combiners_set_pixel_shader(0);
    g_device_state.render_states[D3DRS_ZENABLE] = FALSE;
    g_device_state.render_states[D3DRS_ZWRITEENABLE] = FALSE;
    g_device_state.render_states[D3DRS_ALPHABLENDENABLE] = FALSE;
    g_device_state.render_states[D3DRS_CULLMODE] = D3DCULL_NONE;
    g_device_state.tss[0][D3DTSS_COLOROP] = D3DTOP_SELECTARG1;
    g_device_state.tss[0][D3DTSS_COLORARG1] = D3DTA_TEXTURE;
    g_device_state.tss[0][D3DTSS_ALPHAOP] = D3DTOP_SELECTARG1;
    g_device_state.tss[0][D3DTSS_ALPHAARG1] = D3DTA_TEXTURE;
    dev_SetTexture(&g_device, 0,
                   (IDirect3DBaseTexture8 *)g_host_frame_texture);

    vertices[0] = (HostVertex){ -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f };
    vertices[1] = (HostVertex){ (float)g_device_state.width - 0.5f, -0.5f,
                                0.0f, 1.0f, 1.0f, 0.0f };
    vertices[2] = (HostVertex){ -0.5f, (float)g_device_state.height - 0.5f,
                                0.0f, 1.0f, 0.0f, 1.0f };
    vertices[3] = (HostVertex){ (float)g_device_state.width - 0.5f,
                                (float)g_device_state.height - 0.5f,
                                0.0f, 1.0f, 1.0f, 1.0f };
    draw_result = dev_DrawPrimitiveUP(&g_device, D3DPT_TRIANGLESTRIP,
                                       2, vertices, sizeof(HostVertex));

    g_device_state.vertex_shader = old_vertex_shader;
    g_device_state.pixel_shader = old_pixel_shader;
    g_device_state.render_states[D3DRS_ZENABLE] = old_zenable;
    g_device_state.render_states[D3DRS_ZWRITEENABLE] = old_zwrite;
    g_device_state.render_states[D3DRS_ALPHABLENDENABLE] = old_alphablend;
    g_device_state.render_states[D3DRS_CULLMODE] = old_cull;
    g_device_state.tss[0][D3DTSS_COLOROP] = old_colorop;
    g_device_state.tss[0][D3DTSS_COLORARG1] = old_colorarg1;
    g_device_state.tss[0][D3DTSS_ALPHAOP] = old_alphaop;
    g_device_state.tss[0][D3DTSS_ALPHAARG1] = old_alphaarg1;
    d3d8_combiners_set_pixel_shader(old_pixel_shader);
    dev_SetTexture(&g_device, 0, old_texture);
    return SUCCEEDED(draw_result);
}

static HRESULT __stdcall dev_CreateTexture(IDirect3DDevice8 *self, UINT Width, UINT Height, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DTexture8 **ppTexture)
{
    (void)self; (void)Pool;
    return d3d8_CreateTextureImpl(Width, Height, Levels, Usage, Format, ppTexture);
}

static HRESULT __stdcall dev_CreateVertexBuffer(IDirect3DDevice8 *self, UINT Length, DWORD Usage, DWORD FVF, D3DPOOL Pool, IDirect3DVertexBuffer8 **ppVertexBuffer)
{
    (void)self; (void)Pool;
    return d3d8_CreateVertexBufferImpl(Length, Usage, FVF, ppVertexBuffer);
}

static HRESULT __stdcall dev_CreateIndexBuffer(IDirect3DDevice8 *self, UINT Length, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DIndexBuffer8 **ppIndexBuffer)
{
    (void)self; (void)Pool;
    return d3d8_CreateIndexBufferImpl(Length, Usage, Format, ppIndexBuffer);
}

static HRESULT __stdcall dev_CreateRenderTarget(IDirect3DDevice8 *self, UINT Width, UINT Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample, BOOL Lockable, IDirect3DSurface8 **ppSurface)
{
    (void)self; (void)Width; (void)Height; (void)Format; (void)MultiSample; (void)Lockable; (void)ppSurface;
    return E_NOTIMPL;
}

static HRESULT __stdcall dev_CreateDepthStencilSurface(IDirect3DDevice8 *self, UINT Width, UINT Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample, IDirect3DSurface8 **ppSurface)
{
    (void)self; (void)Width; (void)Height; (void)Format; (void)MultiSample; (void)ppSurface;
    return E_NOTIMPL;
}

static HRESULT __stdcall dev_SetRenderTarget(IDirect3DDevice8 *self, IDirect3DSurface8 *pRenderTarget, IDirect3DSurface8 *pZStencilSurface)
{
    (void)self; (void)pRenderTarget; (void)pZStencilSurface;
    /* TODO: resolve D3D8 surface to D3D11 RTV/DSV */
    return S_OK;
}

static HRESULT __stdcall dev_GetRenderTarget(IDirect3DDevice8 *self, IDirect3DSurface8 **ppRenderTarget)
{
    (void)self; (void)ppRenderTarget;
    return E_NOTIMPL;
}

static HRESULT __stdcall dev_GetDepthStencilSurface(IDirect3DDevice8 *self, IDirect3DSurface8 **ppZStencilSurface)
{
    (void)self; (void)ppZStencilSurface;
    return E_NOTIMPL;
}

static HRESULT __stdcall dev_SetViewport(IDirect3DDevice8 *self, const D3DVIEWPORT8 *pViewport)
{
    (void)self;
    if (pViewport) {
        g_device_state.viewport = *pViewport;

        D3D11_VIEWPORT d3d11_vp;
        d3d11_vp.TopLeftX = (FLOAT)pViewport->X;
        d3d11_vp.TopLeftY = (FLOAT)pViewport->Y;
        d3d11_vp.Width    = (FLOAT)pViewport->Width;
        d3d11_vp.Height   = (FLOAT)pViewport->Height;
        d3d11_vp.MinDepth = pViewport->MinZ;
        d3d11_vp.MaxDepth = pViewport->MaxZ;
        ID3D11DeviceContext_RSSetViewports(g_device_state.d3d11_context, 1, &d3d11_vp);
    }
    return S_OK;
}

static HRESULT __stdcall dev_GetViewport(IDirect3DDevice8 *self, D3DVIEWPORT8 *pViewport)
{
    (void)self;
    if (pViewport) *pViewport = g_device_state.viewport;
    return S_OK;
}

static HRESULT __stdcall dev_SetMaterial(IDirect3DDevice8 *self, const D3DMATERIAL8 *pMaterial)
{
    (void)self;
    if (pMaterial) g_device_state.material = *pMaterial;
    return S_OK;
}

static HRESULT __stdcall dev_GetMaterial(IDirect3DDevice8 *self, D3DMATERIAL8 *pMaterial)
{
    (void)self;
    if (pMaterial) *pMaterial = g_device_state.material;
    return S_OK;
}

static HRESULT __stdcall dev_SetLight(IDirect3DDevice8 *self, DWORD Index, const D3DLIGHT8 *pLight)
{
    (void)self;
    if (Index < MAX_LIGHTS && pLight) g_device_state.lights[Index] = *pLight;
    return S_OK;
}

static HRESULT __stdcall dev_GetLight(IDirect3DDevice8 *self, DWORD Index, D3DLIGHT8 *pLight)
{
    (void)self;
    if (Index < MAX_LIGHTS && pLight) *pLight = g_device_state.lights[Index];
    return S_OK;
}

static HRESULT __stdcall dev_LightEnable(IDirect3DDevice8 *self, DWORD Index, BOOL Enable)
{
    (void)self;
    if (Index < MAX_LIGHTS) g_device_state.light_enable[Index] = Enable;
    return S_OK;
}

static HRESULT __stdcall dev_CreateVertexShader(IDirect3DDevice8 *self, const DWORD *pDeclaration, const DWORD *pFunction, DWORD *pHandle, DWORD Usage)
{
    (void)self; (void)pDeclaration; (void)Usage;
    if (!pHandle) return E_INVALIDARG;
    if (!pFunction) return E_INVALIDARG;
    /* Count instructions: each is 4 DWORDs, last has bit 0 of word[3] set (END flag) */
    {
        int i, num_insns = 0;
        for (i = 0; i < 136; i++) {
            num_insns++;
            if (pFunction[i * 4 + 3] & 1) break;  /* END bit in last word */
        }
        return d3d8_vsh_create_shader(pFunction, num_insns, pHandle);
    }
}

static HRESULT __stdcall dev_SetVertexShader(IDirect3DDevice8 *self, DWORD Handle)
{
    (void)self;
    g_device_state.vertex_shader = Handle;
    return S_OK;
}

static HRESULT __stdcall dev_GetVertexShader(IDirect3DDevice8 *self, DWORD *pHandle)
{
    (void)self;
    if (pHandle) *pHandle = g_device_state.vertex_shader;
    return S_OK;
}

static HRESULT __stdcall dev_SetVertexShaderConstant(IDirect3DDevice8 *self, INT Register, const void *pConstantData, DWORD ConstantCount)
{
    (void)self;
    d3d8_vsh_set_constant(Register, pConstantData, ConstantCount);
    return S_OK;
}

static HRESULT __stdcall dev_SetPixelShader(IDirect3DDevice8 *self, DWORD Handle)
{
    (void)self;
    g_device_state.pixel_shader = Handle;
    d3d8_combiners_set_pixel_shader(Handle);
    return S_OK;
}

static HRESULT __stdcall dev_GetPixelShader(IDirect3DDevice8 *self, DWORD *pHandle)
{
    (void)self;
    if (pHandle) *pHandle = g_device_state.pixel_shader;
    return S_OK;
}

static HRESULT __stdcall dev_SetPixelShaderConstant(IDirect3DDevice8 *self, INT Register, const void *pConstantData, DWORD ConstantCount)
{
    (void)self; (void)Register; (void)pConstantData; (void)ConstantCount;
    return S_OK;
}

static void __stdcall dev_SetGammaRamp(IDirect3DDevice8 *self, DWORD Flags, const D3DGAMMARAMP *pRamp)
{
    (void)self; (void)Flags; (void)pRamp;
}

static void __stdcall dev_GetGammaRamp(IDirect3DDevice8 *self, D3DGAMMARAMP *pRamp)
{
    (void)self; (void)pRamp;
}

static HRESULT __stdcall dev_SetPalette(IDirect3DDevice8 *self, DWORD PaletteNumber, const void *pEntries)
{
    (void)self; (void)PaletteNumber; (void)pEntries;
    return S_OK;
}

static HRESULT __stdcall dev_BeginPush(IDirect3DDevice8 *self, DWORD Count, DWORD **ppPush)
{
    (void)self; (void)Count; (void)ppPush;
    /* TODO: Xbox push buffer emulation */
    return E_NOTIMPL;
}

static HRESULT __stdcall dev_EndPush(IDirect3DDevice8 *self, DWORD *pPush)
{
    (void)self; (void)pPush;
    return E_NOTIMPL;
}

static HRESULT __stdcall dev_Swap(IDirect3DDevice8 *self, DWORD Flags)
{
    (void)self; (void)Flags;

    /* Pump Windows messages (same as dev_Present) */
    MSG msg;
    while (PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE)) {
        if (msg.message == WM_QUIT) {
            ExitProcess(0);
        }
        TranslateMessage(&msg);
        DispatchMessageA(&msg);
    }

    capture_swapchain_frame();
    return IDXGISwapChain_Present(g_device_state.swap_chain, 1, 0);
}

/* ================================================================
 * Vtable
 * ================================================================ */

static const IDirect3DDevice8Vtbl g_device_vtbl = {
    dev_QueryInterface,
    dev_AddRef,
    dev_Release,
    dev_GetDirect3D,
    dev_GetDeviceCaps,
    dev_GetDisplayMode,
    dev_GetCreationParameters,
    dev_Reset,
    dev_Present,
    dev_GetBackBuffer,
    dev_BeginScene,
    dev_EndScene,
    dev_Clear,
    dev_SetTransform,
    dev_GetTransform,
    dev_SetRenderState,
    dev_GetRenderState,
    dev_SetTextureStageState,
    dev_GetTextureStageState,
    dev_SetTexture,
    dev_GetTexture,
    dev_SetStreamSource,
    dev_GetStreamSource,
    dev_SetIndices,
    dev_GetIndices,
    dev_DrawPrimitive,
    dev_DrawIndexedPrimitive,
    dev_DrawPrimitiveUP,
    dev_DrawIndexedPrimitiveUP,
    dev_CreateTexture,
    dev_CreateVertexBuffer,
    dev_CreateIndexBuffer,
    dev_CreateRenderTarget,
    dev_CreateDepthStencilSurface,
    dev_SetRenderTarget,
    dev_GetRenderTarget,
    dev_GetDepthStencilSurface,
    dev_SetViewport,
    dev_GetViewport,
    dev_SetMaterial,
    dev_GetMaterial,
    dev_SetLight,
    dev_GetLight,
    dev_LightEnable,
    dev_SetVertexShader,
    dev_GetVertexShader,
    dev_SetVertexShaderConstant,
    dev_SetPixelShader,
    dev_GetPixelShader,
    dev_SetPixelShaderConstant,
    dev_SetGammaRamp,
    dev_GetGammaRamp,
    dev_SetPalette,
    dev_BeginPush,
    dev_EndPush,
    dev_Swap,
};

/* ================================================================
 * Public API
 * ================================================================ */

IDirect3DDevice8 *xbox_GetD3DDevice(void)
{
    return g_device_initialized ? &g_device : NULL;
}

/* ================================================================
 * IDirect3D8 factory implementation
 * ================================================================ */

static IDirect3D8 g_d3d8;
static LONG g_d3d8_ref = 0;

static HRESULT __stdcall d3d8_QueryInterface(IDirect3D8 *self, const IID *riid, void **ppv)
{
    (void)self; (void)riid; (void)ppv;
    return E_NOINTERFACE;
}

static ULONG __stdcall d3d8_AddRef(IDirect3D8 *self)
{
    (void)self;
    return (ULONG)InterlockedIncrement(&g_d3d8_ref);
}

static ULONG __stdcall d3d8_Release(IDirect3D8 *self)
{
    (void)self;
    return (ULONG)InterlockedDecrement(&g_d3d8_ref);
}

static HRESULT __stdcall d3d8_CreateDevice(IDirect3D8 *self, UINT Adapter, DWORD DeviceType, HWND hFocusWindow, DWORD BehaviorFlags, D3DPRESENT_PARAMETERS *pPP, IDirect3DDevice8 **ppDevice)
{
    (void)self; (void)Adapter; (void)DeviceType; (void)BehaviorFlags;
    HRESULT hr;

    if (!pPP || !ppDevice) return E_INVALIDARG;

    memset(&g_device_state, 0, sizeof(g_device_state));
    g_device_state.ref_count = 1;

    if (!pPP->hDeviceWindow) pPP->hDeviceWindow = hFocusWindow;

    hr = d3d11_create_device_and_swap_chain(&g_device_state, pPP);
    if (FAILED(hr)) return hr;

    hr = d3d11_create_render_targets(&g_device_state);
    if (FAILED(hr)) return hr;

    d3d8_init_default_states(&g_device_state);

    /* Set initial viewport (D3D11 requires explicit viewport) */
    {
        D3D11_VIEWPORT vp;
        vp.TopLeftX = 0.0f;
        vp.TopLeftY = 0.0f;
        vp.Width    = (FLOAT)g_device_state.width;
        vp.Height   = (FLOAT)g_device_state.height;
        vp.MinDepth = 0.0f;
        vp.MaxDepth = 1.0f;
        ID3D11DeviceContext_RSSetViewports(g_device_state.d3d11_context, 1, &vp);
    }

    /* Initialize shader and state subsystems */
    hr = d3d8_shaders_init();
    if (FAILED(hr)) {
        fprintf(stderr, "D3D8: Shader init failed: 0x%08lX\n", hr);
        return hr;
    }

    hr = d3d8_states_init();
    if (FAILED(hr)) {
        fprintf(stderr, "D3D8: State init failed: 0x%08lX\n", hr);
        return hr;
    }

    hr = d3d8_combiners_init();
    if (FAILED(hr)) {
        fprintf(stderr, "D3D8: Combiner init failed: 0x%08lX\n", hr);
        /* Non-fatal: fall back to fixed-function pixel shaders */
    }

    hr = d3d8_vsh_init();
    if (FAILED(hr)) {
        fprintf(stderr, "D3D8: VSH init failed: 0x%08lX\n", hr);
        /* Non-fatal: fall back to FVF vertex shaders */
    }

    g_device.lpVtbl = &g_device_vtbl;
    g_device_initialized = TRUE;

    *ppDevice = &g_device;
    fprintf(stderr, "D3D8: Device created (%ux%u)\n", g_device_state.width, g_device_state.height);
    return S_OK;
}

static const IDirect3D8Vtbl g_d3d8_vtbl = {
    d3d8_QueryInterface,
    d3d8_AddRef,
    d3d8_Release,
    d3d8_CreateDevice,
};

IDirect3D8 *xbox_Direct3DCreate8(UINT SDKVersion)
{
    (void)SDKVersion;
    g_d3d8.lpVtbl = &g_d3d8_vtbl;
    g_d3d8_ref = 1;
    return &g_d3d8;
}
