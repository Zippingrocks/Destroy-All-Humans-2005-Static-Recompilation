/* Standalone parser/translation regression test, NOT a game or image fixture.
 * Compile this actual production TU with a mock D3D device and isolated RAM,
 * then replay the captured initialization and first indexed command ranges.
 * The synthetic data tests exact vertex/index/texture transport, not visuals.
 */
#define _CRT_SECURE_NO_WARNINGS
#include <assert.h>
#include "../../../Repos/xboxrecomp-main/src/nv2a/nv2a_pgraph_d3d11.c"

size_t g_xbox_total_ram = 64u * 1024u * 1024u;
static uint8_t *test_ram;
static IDirect3DDevice8 test_device;
static IDirect3DDevice8Vtbl test_device_vtable;
static IDirect3DTexture8 test_texture;
static IDirect3DTexture8Vtbl test_texture_vtable;
static uint8_t *test_texture_bytes;
static unsigned test_width, test_height, test_pitch, test_draws;
static unsigned test_render_states[256], test_stage_states[4][64], test_fvf;
static OutputVertex test_vertices[4];

void *xbox_GetMemoryBase(void) { return test_ram; }
ptrdiff_t xbox_GetMemoryOffset(void) { return (ptrdiff_t)test_ram - XBOX_CONTIG_BASE; }
IDirect3DDevice8 *xbox_GetD3DDevice(void) { return &test_device; }
static ULONG __stdcall mock_release(IDirect3DTexture8 *self)
{ (void)self; free(test_texture_bytes); test_texture_bytes = NULL; return 0; }
static HRESULT __stdcall mock_lock(IDirect3DTexture8 *self, UINT level,
        D3DLOCKED_RECT *out, const RECT *rect, DWORD flags)
{
    (void)self; (void)rect; (void)flags; assert(level == 0);
    out->Pitch = test_pitch; out->pBits = test_texture_bytes; return S_OK;
}
static HRESULT __stdcall mock_unlock(IDirect3DTexture8 *self, UINT level)
{ (void)self; assert(level == 0); return S_OK; }
static HRESULT __stdcall mock_create_texture(IDirect3DDevice8 *self, UINT width,
        UINT height, UINT levels, DWORD usage, D3DFORMAT format, D3DPOOL pool,
        IDirect3DTexture8 **out)
{
    (void)self; (void)usage; (void)pool;
    assert(width == 640 && height == 448 && levels == 1 && format == D3DFMT_LIN_X8R8G8B8);
    test_width = width; test_height = height; test_pitch = width * 4 + 16;
    test_texture_bytes = (uint8_t *)malloc((size_t)test_pitch * height);
    assert(test_texture_bytes); memset(test_texture_bytes, 0xBD, (size_t)test_pitch * height);
    *out = &test_texture; return S_OK;
}
static HRESULT __stdcall mock_render_state(IDirect3DDevice8 *self, D3DRENDERSTATETYPE state, DWORD value)
{ (void)self; assert(state < 256); test_render_states[state] = value; return S_OK; }
static HRESULT __stdcall mock_stage_state(IDirect3DDevice8 *self, DWORD stage, D3DTEXTURESTAGESTATETYPE type, DWORD value)
{ (void)self; assert(stage < 4 && type < 64); test_stage_states[stage][type] = value; return S_OK; }
static HRESULT __stdcall mock_texture(IDirect3DDevice8 *self, DWORD stage, IDirect3DBaseTexture8 *texture)
{ (void)self; assert(stage < 4); assert(!texture || texture == (IDirect3DBaseTexture8 *)&test_texture); return S_OK; }
static HRESULT __stdcall mock_vertex_shader(IDirect3DDevice8 *self, DWORD fvf)
{ (void)self; test_fvf = fvf; return S_OK; }
static HRESULT __stdcall mock_pixel_shader(IDirect3DDevice8 *self, DWORD shader)
{ (void)self; assert(shader == 0); return S_OK; }
static HRESULT __stdcall mock_begin(IDirect3DDevice8 *self) { (void)self; return S_OK; }
static HRESULT __stdcall mock_clear(IDirect3DDevice8 *self, DWORD count, const D3DRECT *rect,
        DWORD flags, D3DCOLOR color, float depth, DWORD stencil)
{ (void)self; (void)count; (void)rect; (void)flags; (void)color; (void)depth; (void)stencil; return S_OK; }
static HRESULT __stdcall mock_draw(IDirect3DDevice8 *self, D3DPRIMITIVETYPE primitive,
        UINT count, const void *data, UINT stride)
{
    (void)self;
    assert(primitive == D3DPT_TRIANGLESTRIP && count == 2 && stride == sizeof(OutputVertex));
    assert(test_fvf == (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1));
    memcpy(test_vertices, data, sizeof(test_vertices)); ++test_draws; return S_OK;
}
static void replay(const char *path)
{
    FILE *file = fopen(path, "rb"); long bytes; uint32_t *data;
    assert(file); assert(fseek(file, 0, SEEK_END) == 0); bytes = ftell(file);
    assert(bytes > 0 && bytes < 1024 * 1024 && (bytes % 4) == 0);
    rewind(file); data = (uint32_t *)malloc(bytes); assert(data);
    assert(fread(data, 1, bytes, file) == (size_t)bytes); fclose(file);
    pgraph_d3d11_submit_pushbuffer(data, (uint32_t)bytes / 4u); free(data);
}
static void draw_test_quad(void)
{
    pgraph_d3d11_method(0, NV097_SET_BEGIN_END, 6);
    pgraph_d3d11_method(0, NV097_ARRAY_ELEMENT16, 0x00010000);
    pgraph_d3d11_method(0, NV097_ARRAY_ELEMENT16, 0x00030002);
    pgraph_d3d11_method(0, NV097_SET_BEGIN_END, 0);
}
static void test_rejected_capture(void)
{
    /* Unknown trailing command must survive: capture the whole ring, not
     * merely the parsed method that eventually rejected the draw. */
    const uint32_t ring[] = { 0x000417FC, 6, 0x40081800, 0x00010000,
                             0x00030002, 0x000417FC, 0, 0x00041FF0, 0xA1B2C3D4 };
    char pattern[96]; WIN32_FIND_DATAA info; HANDLE find;
    unsigned captured = 0;
    g_pg.transform_program[1] ^= 1;
    pgraph_d3d11_submit_pushbuffer(ring, 9);
    g_pg.array_offset[0] += 28; /* Same state; changing resource address must dedupe. */
    pgraph_d3d11_submit_pushbuffer(ring, 9);
    g_pg.tex[0].format ^= 0x100;
    pgraph_d3d11_submit_pushbuffer(ring, 9);
    g_pg.array_format[0] ^= 1;
    pgraph_d3d11_submit_pushbuffer(ring, 9);
    g_pg.color_mask = 0;
    pgraph_d3d11_submit_pushbuffer(ring, 9);
    g_pg.tex[0].format ^= 0x200; /* Fifth distinct state must hit the cap. */
    pgraph_d3d11_submit_pushbuffer(ring, 9);
    snprintf(pattern, sizeof(pattern), "dah_pb_rejected_%lu_*.bin", (unsigned long)GetCurrentProcessId());
    find = FindFirstFileA(pattern, &info); assert(find != INVALID_HANDLE_VALUE);
    do {
        uint32_t actual[10]; FILE *file = fopen(info.cFileName, "rb");
        assert(file && fread(actual, sizeof(uint32_t), 10, file) == 9); fclose(file);
        assert(memcmp(actual, ring, sizeof(ring)) == 0); ++captured;
    } while (FindNextFileA(find, &info));
    FindClose(find); assert(captured == 4); assert(test_draws == 2);
    puts("PASS: rejected capture keeps complete raw ring, deduplicates changing resource addresses, caps at four distinct states");
}
int main(int argc, char **argv)
{
    typedef struct { float position[4], uv[2]; uint32_t color; } GuestVertex;
    static const GuestVertex fixture[4] = {
        { { 12.0f, 24.0f, 0.25f, 1.0f }, { 0.5f, 0.5f }, 0xFF122334 },
        { { 628.0f, 24.0f, 0.25f, 1.0f }, { 639.5f, 0.5f }, 0xFF455667 },
        { { 12.0f, 456.0f, 0.25f, 1.0f }, { 0.5f, 447.5f }, 0xFF78899A },
        { { 628.0f, 456.0f, 0.25f, 1.0f }, { 639.5f, 447.5f }, 0xFFABBCCD }
    };
    assert(argc >= 3 && sizeof(GuestVertex) == 28);
    if (getenv("DAH_TEST_REJECT_CAPTURE")) {
        _putenv("DAH_PB_CAPTURE=0"); _putenv("DAH_PB_INDEXED_CAPTURE=0");
        _putenv("DAH_PB_REJECT_CAPTURE=99");
    }
    test_ram = (uint8_t *)VirtualAlloc(NULL, g_xbox_total_ram, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
    assert(test_ram); memcpy(test_ram + 0x0329D000, fixture, sizeof(fixture));
    for (unsigned row = 0; row < 448; ++row)
        for (unsigned byte = 0; byte < 640 * 4; ++byte)
            test_ram[0x03439000 + row * 2560 + byte] = (uint8_t)(row * 17u + byte * 23u);
    test_device.lpVtbl = &test_device_vtable;
    test_texture.lpVtbl = &test_texture_vtable;
    test_device_vtable.CreateTexture = mock_create_texture;
    test_device_vtable.SetRenderState = mock_render_state;
    test_device_vtable.SetTextureStageState = mock_stage_state;
    test_device_vtable.SetTexture = mock_texture;
    test_device_vtable.SetVertexShader = mock_vertex_shader;
    test_device_vtable.SetPixelShader = mock_pixel_shader;
    test_device_vtable.BeginScene = mock_begin;
    test_device_vtable.Clear = mock_clear;
    test_device_vtable.DrawPrimitiveUP = mock_draw;
    test_texture_vtable.Release = mock_release;
    test_texture_vtable.LockRect = mock_lock;
    test_texture_vtable.UnlockRect = mock_unlock;
    pgraph_d3d11_init();
    for (int i = 1; i < argc; ++i) replay(argv[i]);
    assert(test_draws == 1 && g_pg.stats.draw_calls == 1 && g_pg.stats.vertices_submitted == 4);
    for (unsigned i = 0; i < 4; ++i) {
        assert(test_vertices[i].x == fixture[i].position[0]);
        assert(test_vertices[i].y == fixture[i].position[1]);
        assert(test_vertices[i].z == fixture[i].position[2]);
        assert(test_vertices[i].rhw == fixture[i].position[3]);
        assert(test_vertices[i].color == fixture[i].color);
        assert(test_vertices[i].u == fixture[i].uv[0] / 640.0f);
        assert(test_vertices[i].v == fixture[i].uv[1] / 448.0f);
    }
    for (unsigned row = 0; row < test_height; ++row) {
        assert(memcmp(test_texture_bytes + row * test_pitch, test_ram + 0x03439000 + row * 2560, test_width * 4) == 0);
        for (unsigned byte = test_width * 4; byte < test_pitch; ++byte)
            assert(test_texture_bytes[row * test_pitch + byte] == 0xBD);
    }
    assert(test_stage_states[0][D3DTSS_COLOROP] == D3DTOP_MODULATE2X);
    assert(test_stage_states[0][D3DTSS_ALPHAOP] == D3DTOP_MODULATE);
    assert(test_stage_states[0][D3DTSS_ADDRESSU] == D3DTADDRESS_CLAMP);
    assert(test_render_states[D3DRS_ZENABLE] == FALSE);
    /* Unsupported programs, declarations, inaccessible RAM and W must never
     * become a successful host draw or advance renderer draw statistics. */
    g_pg.transform_mode = 6;
    pgraph_d3d11_method(0, NV097_SET_TEXTURE_CONTROL0, 0x4003FFC0u);
    g_pg.transform_program[1] ^= 1; draw_test_quad(); g_pg.transform_program[1] ^= 1;
    g_pg.array_format[0] ^= 1; draw_test_quad(); g_pg.array_format[0] ^= 1;
    g_pg.array_offset[0] = 0xFFFFFFF0; draw_test_quad(); g_pg.array_offset[0] = 0x0329D000;
    ((GuestVertex *)(test_ram + 0x0329D000))->position[3] = 0;
    draw_test_quad(); ((GuestVertex *)(test_ram + 0x0329D000))->position[3] = 1;
    g_pg.transform_start = 0x40000000u; draw_test_quad(); g_pg.transform_start = 0;
    assert(test_draws == 1 && g_pg.stats.draw_calls == 1);
    draw_test_quad(); assert(test_draws == 2 && g_pg.stats.draw_calls == 2);
    if (getenv("DAH_TEST_REJECT_CAPTURE")) test_rejected_capture();
    pgraph_d3d11_shutdown(); VirtualFree(test_ram, 0, MEM_RELEASE);
    puts("PASS: actual captured command replay; real indexed fetch and exact pitched texture transport; 5 rejection cases");
    return 0;
}
