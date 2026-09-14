/* Exact captured UI geometry/atlas replay against an isolated mock device.
 * No game process, fabricated image, desktop input, or visible window. */
#define main movie_fixture_main
#include "test_movie_pushbuffer.c"
#undef main
typedef struct UiTexture {
    IDirect3DTexture8 iface;
    uint8_t *bytes;
    unsigned width, height, pitch, format;
} UiTexture;
static UiTexture *ui_bound;
static unsigned ui_draws, ui_seen, ui_creations;
static uint8_t *ui_low;
static ULONG __stdcall ui_release(IDirect3DTexture8 *self)
{
    UiTexture *texture = (UiTexture *)self;
    if (ui_bound == texture) ui_bound = NULL;
    free(texture->bytes); free(texture); return 0;
}
static HRESULT __stdcall ui_create(IDirect3DDevice8 *self, UINT width, UINT height, UINT levels,
        DWORD usage, D3DFORMAT format, D3DPOOL pool, IDirect3DTexture8 **out)
{
    UiTexture *texture = (UiTexture *)calloc(1, sizeof(*texture));
    unsigned bpp = format == D3DFMT_LIN_A4R4G4B4 ? 2u : 4u;
    (void)self; (void)usage; (void)pool;
    assert(texture && width == 128 && (height == 480 || height == 16) && levels == 1);
    assert(format == D3DFMT_LIN_A4R4G4B4 || format == D3DFMT_LIN_X8R8G8B8);
    texture->iface.lpVtbl = &test_texture_vtable;
    texture->width = width; texture->height = height; texture->format = format;
    texture->pitch = width * bpp + 16;
    texture->bytes = (uint8_t *)malloc((size_t)texture->pitch * height);
    assert(texture->bytes); memset(texture->bytes, 0xBD, (size_t)texture->pitch * height);
    *out = &texture->iface; ++ui_creations; return S_OK;
}
static HRESULT __stdcall ui_lock(IDirect3DTexture8 *self, UINT level, D3DLOCKED_RECT *out,
        const RECT *rect, DWORD flags)
{
    UiTexture *texture = (UiTexture *)self;
    (void)rect; (void)flags; assert(level == 0);
    out->pBits = texture->bytes; out->Pitch = texture->pitch; return S_OK;
}
static HRESULT __stdcall ui_bind(IDirect3DDevice8 *self, DWORD stage, IDirect3DBaseTexture8 *texture)
{
    (void)self;
    if (stage == 0) ui_bound = (UiTexture *)texture;
    else assert(!texture);
    return S_OK;
}
static HRESULT __stdcall ui_draw(IDirect3DDevice8 *self, D3DPRIMITIVETYPE primitive,
        UINT primitives, const void *data, UINT stride)
{
    const OutputVertex *vertices = (const OutputVertex *)data;
    unsigned bpp = ui_bound && ui_bound->format == D3DFMT_LIN_A4R4G4B4 ? 2u : 4u;
    const uint8_t *source_window = bpp == 2 ? ui_low : test_ram;
    unsigned source_pitch = g_pg.tex[0].control1 >> 16;
    (void)self;
    assert(ui_bound && primitive == D3DPT_TRIANGLESTRIP && primitives + 2 == g_pg.index_count);
    assert(stride == sizeof(OutputVertex));
    for (unsigned i = 0; i < g_pg.index_count; ++i) {
        unsigned index = g_pg.indices[i]; float position[4], uv[2]; uint32_t color;
        memcpy(position, test_ram + g_pg.array_offset[0] + index * 28, sizeof(position));
        memcpy(uv, test_ram + g_pg.array_offset[1] + index * 28, sizeof(uv));
        memcpy(&color, test_ram + g_pg.array_offset[2] + index * 28, sizeof(color));
        assert(vertices[i].x == position[0] && vertices[i].y == position[1] && vertices[i].z == position[2]);
        assert(vertices[i].rhw == position[3] && position[3] == 1 && vertices[i].color == color);
        assert(vertices[i].u == uv[0] / ui_bound->width && vertices[i].v == uv[1] / ui_bound->height);
    }
    for (unsigned y = 0; y < ui_bound->height; ++y) {
        assert(memcmp(ui_bound->bytes + y * ui_bound->pitch,
                      source_window + g_pg.tex[0].offset + y * source_pitch, ui_bound->width * bpp) == 0);
        for (unsigned x = ui_bound->width * bpp; x < ui_bound->pitch; ++x)
            assert(ui_bound->bytes[y * ui_bound->pitch + x] == 0xBD);
    }
    assert(test_stage_states[0][D3DTSS_COLOROP] == D3DTOP_MODULATE2X);
    assert(test_stage_states[0][D3DTSS_ALPHAOP] == D3DTOP_MODULATE);
    if (bpp == 2 && ui_bound->height == 480 && g_pg.index_count == 448) ui_seen |= 1;
    if (bpp == 2 && ui_bound->height == 16 && g_pg.index_count == 6) ui_seen |= 2;
    ++ui_draws; return S_OK;
}
static void load_resources(const char *directory)
{
    char path[768], pattern[768]; WIN32_FIND_DATAA entry; HANDLE find;
    unsigned loaded = 0;
    snprintf(pattern, sizeof(pattern), "%s/dah_resource_16548_*.bin", directory);
    find = FindFirstFileA(pattern, &entry); assert(find != INVALID_HANDLE_VALUE);
    do {
        unsigned pid, submission, address; char kind[24], window[12]; FILE *file;
        assert(sscanf(entry.cFileName, "dah_resource_%u_%u_%23[^_]_%x_%11[^.]", &pid,
                      &submission, kind, &address, window) == 5);
        if (submission != 54 && submission != 55) continue;
        assert(entry.nFileSizeHigh == 0 && (uint64_t)address + entry.nFileSizeLow <= XBOX_CONTIG_SIZE);
        snprintf(path, sizeof(path), "%s/%s", directory, entry.cFileName);
        file = fopen(path, "rb"); assert(file);
        assert(fread((strcmp(window, "low") == 0 ? ui_low : test_ram) + address,
                     1, entry.nFileSizeLow, file) == entry.nFileSizeLow);
        fclose(file); ++loaded;
    } while (FindNextFileA(find, &entry));
    FindClose(find); assert(loaded == 16);
}
int main(int argc, char **argv)
{
    uint8_t *reserved; char path[768]; unsigned before_creations;
    assert(argc == 2);
    _putenv("DAH_PB_CAPTURE=0"); _putenv("DAH_PB_INDEXED_CAPTURE=0"); _putenv("DAH_PB_REJECT_CAPTURE=0");
    reserved = (uint8_t *)VirtualAlloc(NULL, (SIZE_T)XBOX_CONTIG_BASE + XBOX_CONTIG_SIZE, MEM_RESERVE, PAGE_NOACCESS);
    assert(reserved);
    ui_low = (uint8_t *)VirtualAlloc(reserved, XBOX_CONTIG_SIZE, MEM_COMMIT, PAGE_READWRITE);
    test_ram = (uint8_t *)VirtualAlloc(reserved + XBOX_CONTIG_BASE, XBOX_CONTIG_SIZE, MEM_COMMIT, PAGE_READWRITE);
    assert(ui_low == reserved && test_ram == reserved + XBOX_CONTIG_BASE);
    load_resources(argv[1]);
    test_device.lpVtbl = &test_device_vtable;
    test_device_vtable.CreateTexture = ui_create; test_device_vtable.SetRenderState = mock_render_state;
    test_device_vtable.SetTextureStageState = mock_stage_state; test_device_vtable.SetTexture = ui_bind;
    test_device_vtable.SetVertexShader = mock_vertex_shader; test_device_vtable.SetPixelShader = mock_pixel_shader;
    test_device_vtable.BeginScene = mock_begin; test_device_vtable.Clear = mock_clear;
    test_device_vtable.DrawPrimitiveUP = ui_draw;
    test_texture_vtable.Release = ui_release; test_texture_vtable.LockRect = ui_lock;
    test_texture_vtable.UnlockRect = mock_unlock;
    pgraph_d3d11_init();
    for (unsigned i = 1; i <= 4; ++i) {
        snprintf(path, sizeof(path), "%s/dah_pb_16548_%06u.bin", argv[1], i); replay(path);
    }
    for (unsigned i = 54; i <= 55; ++i) {
        snprintf(path, sizeof(path), "%s/dah_pb_rejected_16548_%06u.bin", argv[1], i); replay(path);
    }
    assert(ui_draws >= 2 && ui_seen == 3);
    /* Same dimensions but different pixel format must replace the cached
     * host resource; separate synthetic bytes are only a transport unit test. */
    before_creations = ui_creations;
    g_pg.tex[0].format = 0x00011E29u; g_pg.tex[0].offset = 0x02F00000u;
    g_pg.tex[0].image_rect = 0x00800010u; g_pg.tex[0].control1 = 0x02000000u;
    for (unsigned i = 0; i < 128u * 16u * 4u; ++i) test_ram[0x02F00000u + i] = (uint8_t)(i * 13u + 9u);
    g_pg.array_offset[0] = 0x033F9000u; g_pg.array_offset[1] = 0x033F9010u; g_pg.array_offset[2] = 0x033F9018u;
    g_pg.tex[0].enabled = 1; g_pg.transform_mode = 6;
    draw_test_quad(); assert(ui_creations == before_creations + 1);
    assert(ui_bound->format == D3DFMT_LIN_X8R8G8B8);
    {
        uint32_t expected[4]={0x43A00000u,0xC3700000u,0x49800000u,0};
        pgraph_d3d11_method(0,NV097_SET_TRANSFORM_CONSTANT_LOAD,2);
        for(unsigned i=0;i<4;++i)
            assert(pgraph_d3d11_method(0,NV097_SET_TRANSFORM_CONSTANT+i*4u,expected[i]));
        pgraph_d3d11_method(0,0x1710u,0);
        assert(!memcmp(g_pg.transform_constants+8,expected,sizeof expected));
    }
    {
        uint32_t original_start = g_pg.transform_start;
        /* A 17-slot shader must fit in the 136-slot program store. */
        g_pg.transform_start = 120u; assert(!submit_indexed_3d());
        g_pg.transform_start = UINT32_MAX; assert(!submit_indexed_3d());
        g_pg.transform_start = original_start;
    }
    /* Array-span validation must reject overflow, undersized stride, and a
     * protected hole before issuing any host draw. Exercise the production
     * gate after the known-valid quad established the full shader state. */
    {
        unsigned before = ui_draws;
        uint32_t offset = g_pg.array_offset[0], format0 = g_pg.array_format[0];
        DWORD old_protection;
        g_pg.array_offset[0] = UINT32_MAX - 8u;
        draw_test_quad(); assert(ui_draws == before);
        g_pg.array_offset[0] = offset;
        g_pg.array_format[0] = (8u << 8u) | 0x42u;
        draw_test_quad(); assert(ui_draws == before);
        g_pg.array_format[0] = format0;
        assert(VirtualProtect(test_ram + (offset & ~4095u), 4096, PAGE_NOACCESS, &old_protection));
        draw_test_quad(); assert(ui_draws == before);
        assert(VirtualProtect(test_ram + (offset & ~4095u), 4096, old_protection, &old_protection));
    }
    pgraph_d3d11_shutdown(); VirtualFree(reserved, 0, MEM_RELEASE);
    printf("PASS: %u real captured UI batches + format-switch fixture; exact atlas bytes/alpha, vertex indices/UV/color, low-texture/contiguous-vertex split, padding and cache format verified\n", ui_draws - 1);
    return 0;
}
