/* Exercises the production upload/cache function in isolated mock RAM. */
#define _CRT_SECURE_NO_WARNINGS
#include <assert.h>
#include "../../../third_party/xboxrecomp/src/nv2a/nv2a_pgraph_d3d11.c"

#define CHECK(x) do { if (!(x)) { fprintf(stderr, "FAIL line %d: %s\n", __LINE__, #x); exit(1); } } while (0)
size_t g_xbox_total_ram = 64u * 1024u * 1024u;
static uint8_t *ram, *contiguous_ram;
static IDirect3DDevice8 device;
static IDirect3DDevice8Vtbl device_vtable;
static IDirect3DTexture8Vtbl texture_vtable;
static unsigned creations, uploads, extra_pitch = 16;
typedef struct { IDirect3DTexture8 iface; uint8_t *data; unsigned width, height, pitch; } Texture;
static int postprocess_active;
static unsigned postprocess_draws, postprocess_combiner_calls, postprocess_scene_binds;
static unsigned postprocess_alpha_masks, expected_alpha_mask;
static Texture *bound_table;
void *xbox_GetMemoryBase(void) { return ram; }
ptrdiff_t xbox_GetMemoryOffset(void) { return (ptrdiff_t)ram; }
IDirect3DDevice8 *xbox_GetD3DDevice(void) { return &device; }
/* Full production TU link dependencies. Any accidental use fails the test. */
void d3d8_MarkFullScreenMovieFrameReady(void) { CHECK(0); }
int d3d8_IsFullScreenMovieFrame(void) { CHECK(0); return 0; }
ID3D11Device *d3d8_GetD3D11Device(void) { CHECK(0); return NULL; }
ID3D11DeviceContext *d3d8_GetD3D11Context(void) { CHECK(0); return NULL; }
const DWORD *d3d8_GetRenderStates(void) { CHECK(0); return NULL; }
HRESULT d3d8_PgraphBindRenderTarget(UINT a, BOOL b, UINT c, UINT d)
{ (void)a; (void)b; (void)c; (void)d; CHECK(0); return E_FAIL; }
HRESULT d3d8_PgraphBindDepthSurface(UINT a, UINT b)
{ (void)a; (void)b; CHECK(0); return E_FAIL; }
HRESULT d3d8_PgraphBindRenderTargetTexture(DWORD a, UINT b)
{ CHECK(postprocess_active && a == 0 && b == 0x20000); ++postprocess_scene_binds; return S_OK; }
BOOL d3d8_PgraphTryBindRenderTargetTexture(DWORD a, UINT b)
{ (void)a; (void)b; CHECK(0); return FALSE; }
BOOL d3d8_PgraphTryBindRenderTargetTextureSized(DWORD a, UINT b, UINT c, UINT d)
{
    CHECK(postprocess_active && a == 0 && b == 0x20000 && c == 640 && d == 480);
    ++postprocess_scene_binds;
    return TRUE;
}
void d3d8_SetRasterDepthBias(int a, float b, float c)
{ (void)a; (void)b; (void)c; CHECK(0); }
void dah_renderdoc_begin_effect(const char *label)
{ (void)label; CHECK(0); }
void d3d8_combiners_set_vertex_fog(int a) { (void)a; CHECK(0); }
void d3d8_combiners_set_vertex_fog_constant(float factor) { (void)factor; }
void d3d8_combiners_set_texture_alpha_one_mask(uint32_t mask)
{
    CHECK(postprocess_active && mask == expected_alpha_mask);
    CHECK(postprocess_combiner_calls == postprocess_alpha_masks + 1);
    ++postprocess_alpha_masks;
}
int dah_request_frame_capture(void) { CHECK(0); return 0; }
void d3d8_combiners_set_nv2a(uint32_t a, uint32_t b, const uint32_t *c, const uint32_t *d,
    const uint32_t *e, const uint32_t *f, const uint32_t *g, const uint32_t *h, uint32_t i, uint32_t j)
{
    CHECK(postprocess_active && a == g_pg.combiner_control && b == 0x1e1u);
    CHECK(c == g_pg.color_icw && d == g_pg.color_ocw && e == g_pg.alpha_icw && f == g_pg.alpha_ocw);
    CHECK(g == g_pg.factor0 && h == g_pg.factor1 && i == g_pg.final_cw0 && j == g_pg.final_cw1);
    ++postprocess_combiner_calls;
}
HRESULT d3d8_CreateCubeTextureImpl(UINT size, UINT levels, D3DFORMAT format, IDirect3DTexture8 **out)
{ (void)size; (void)levels; (void)format; (void)out; CHECK(0); return E_FAIL; }
HRESULT d3d8_UploadCubeTextureImpl(IDirect3DTexture8 *texture, const uint8_t *source, size_t stride)
{ (void)texture; (void)source; (void)stride; CHECK(0); return E_FAIL; }
HRESULT d3d8_UploadTextureMipChainImpl(IDirect3DTexture8 *texture, const uint8_t *source, size_t bytes)
{ (void)texture; (void)source; (void)bytes; CHECK(0); return E_FAIL; }
static ULONG __stdcall release(IDirect3DTexture8 *self)
{ Texture *t = (Texture *)self; free(t->data); free(t); return 0; }
static HRESULT __stdcall create(IDirect3DDevice8 *self, UINT width, UINT height, UINT levels,
    DWORD usage, D3DFORMAT format, D3DPOOL pool, IDirect3DTexture8 **out)
{
    Texture *t = calloc(1, sizeof(*t));
    (void)self; (void)usage; (void)pool;
    CHECK(t && levels == 1 && format == D3DFMT_LIN_A8R8G8B8);
    t->iface.lpVtbl = &texture_vtable; t->width = width; t->height = height;
    t->pitch = width * 4 + extra_pitch; t->data = malloc((size_t)t->pitch * height);
    CHECK(t->data); memset(t->data, 0xBD, (size_t)t->pitch * height);
    *out = &t->iface; ++creations; return S_OK;
}
static HRESULT __stdcall lock(IDirect3DTexture8 *self, UINT level, D3DLOCKED_RECT *out,
    const RECT *rect, DWORD flags)
{
    Texture *t = (Texture *)self; (void)rect; (void)flags; CHECK(level == 0);
    out->pBits = t->data; out->Pitch = t->pitch; ++uploads; return S_OK;
}
static HRESULT __stdcall unlock(IDirect3DTexture8 *self, UINT level)
{ (void)self; CHECK(level == 0); return S_OK; }
/* Independent bit-deposit oracle (does not call production swizzle helpers). */
static unsigned offset(unsigned x, unsigned y, unsigned width, unsigned height)
{
    unsigned result = 0, dst_bit = 1;
    for (unsigned bit = 1; bit < width || bit < height; bit <<= 1) {
        if (bit < width) { if (x & bit) result |= dst_bit; dst_bit <<= 1; }
        if (bit < height) { if (y & bit) result |= dst_bit; dst_bit <<= 1; }
    }
    return result * 4;
}
static void verify(Texture *t, const uint8_t *source, int swap)
{
    for (unsigned y = 0; y < t->height; ++y) {
        for (unsigned x = 0; x < t->width; ++x) {
            const uint8_t *s = source + offset(x, y, t->width, t->height);
            const uint8_t *d = t->data + y * t->pitch + x * 4;
            CHECK(d[0] == s[swap ? 2 : 0] && d[1] == s[1] &&
                  d[2] == s[swap ? 0 : 2] && d[3] == s[3]);
        }
        for (unsigned x = t->width * 4; x < t->pitch; ++x) CHECK(t->data[y*t->pitch+x] == 0xBD);
    }
}
static HRESULT __stdcall set_render_state(IDirect3DDevice8 *self, D3DRENDERSTATETYPE state, DWORD value)
{ (void)self; (void)state; (void)value; CHECK(postprocess_active); return S_OK; }
static HRESULT __stdcall set_stage_state(IDirect3DDevice8 *self, DWORD stage, D3DTEXTURESTAGESTATETYPE type, DWORD value)
{ (void)self; (void)type; (void)value; CHECK(postprocess_active && stage < 4); return S_OK; }
static HRESULT __stdcall set_texture(IDirect3DDevice8 *self, DWORD stage, IDirect3DBaseTexture8 *texture)
{
    (void)self; CHECK(postprocess_active && stage < 4);
    if (texture) CHECK(stage == 1);
    if (stage == 1) bound_table = (Texture *)texture;
    return S_OK;
}
static HRESULT __stdcall set_vertex_shader(IDirect3DDevice8 *self, DWORD fvf)
{ (void)self; CHECK(postprocess_active && fvf == (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX4)); return S_OK; }
static HRESULT __stdcall begin_scene(IDirect3DDevice8 *self)
{ (void)self; CHECK(postprocess_active); return S_OK; }
typedef struct { float position[4]; uint32_t color; float uv[4][2]; } PostVertexFixture;
static HRESULT __stdcall draw(IDirect3DDevice8 *self, D3DPRIMITIVETYPE primitive,
    UINT count, const void *data, UINT stride)
{
    const PostVertexFixture *v = data;
    (void)self;
    CHECK(postprocess_active && primitive == D3DPT_TRIANGLESTRIP && count == 2);
    CHECK(stride == sizeof(*v) && bound_table && bound_table->width == 1 && bound_table->height == 256);
    /* This asserts the backing used by the real submit_postprocess call. */
    verify(bound_table, contiguous_ram + g_pg.tex[1].offset, 1);
    for (unsigned i = 0; i < 4; ++i) {
        CHECK(v[i].position[0] == (i&1 ? 640.0f : 0.0f));
        CHECK(v[i].position[1] == (i&2 ? 480.0f : 0.0f));
        CHECK(v[i].position[2] == 0 && v[i].position[3] == 1 && v[i].color == 0xff808080u);
        CHECK(v[i].uv[0][0] == (i&1 ? 1.0f : 0.0f) && v[i].uv[0][1] == (i&2 ? 1.0f : 0.0f));
    }
    ++postprocess_draws; return S_OK;
}
static void setup_postprocess(void)
{
    /* Retail screen-space MOV program and indexed input layout. */
    const uint32_t program[] = {0,0x0020001b,0x0836106c,0x2070f800,
        0,0x0020021b,0x0836106c,0x2070f848,0,0x0020041b,0x0836106c,0x2070f818,
        0,0x00376000,0x0c36106c,0x2070f829};
    typedef struct { float position[4], uv[2]; uint32_t color; } GuestVertex;
    GuestVertex vertices[4] = {0};
    memset(&g_pg, 0, sizeof(g_pg));
    g_pg.draw_mode=6; g_pg.index_count=4; g_pg.transform_mode=2;
    g_pg.color_mask=0x01010101u; g_pg.shader_stage_program=0x1e1u;
    g_pg.surface_format=0x20; g_pg.depth_func=g_pg.alpha_func=0x203;
    memcpy(g_pg.transform_program,program,sizeof(program)); memset(g_pg.transform_valid,1,16);
    g_pg.array_format[0]=(28u<<8)|0x42; g_pg.array_format[1]=(28u<<8)|0x22;
    g_pg.array_format[2]=(28u<<8)|0x40;
    g_pg.array_offset[0]=0x30000; g_pg.array_offset[1]=0x30010; g_pg.array_offset[2]=0x30018;
    g_pg.tex[0].enabled=g_pg.tex[1].enabled=1;
    g_pg.tex[0].format=0x00011229; g_pg.tex[0].offset=0x20000;
    g_pg.tex[0].image_rect=(640u<<16)|480u; g_pg.tex[0].control1=2560u<<16;
    g_pg.tex[0].address=g_pg.tex[1].address=0x303;
    g_pg.tex[1].format=0x08013a29; g_pg.tex[1].offset=0x18000;
    for (unsigned i=0;i<4;++i) {
        g_pg.indices[i]=i;
        vertices[i].position[0]=vertices[i].uv[0]=i&1?640.0f:0.0f;
        vertices[i].position[1]=vertices[i].uv[1]=i&2?480.0f:0.0f;
        vertices[i].position[3]=1; vertices[i].color=0xff808080u;
    }
    memcpy(contiguous_ram+0x30000,vertices,sizeof(vertices));
}
static void test_screen_space_mov_shader_identity(void)
{
    const uint32_t program[] = {
        0,0x0020001b,0x0836106c,0x2070f800,
        0,0x0020021b,0x0836106c,0x2070f848,
        0,0x0020041b,0x0836106c,0x2070f818,
        0,0x00376000,0x0c36106c,0x2070f829
    };
    memset(&g_pg, 0, sizeof(g_pg));
    g_pg.transform_mode = 2u;
    memcpy(g_pg.transform_program, program, sizeof(program));
    memset(g_pg.transform_valid, 1, 16u);
    /* Bink and world-effect cards intentionally have different combiners. */
    g_pg.combiner_control = 0x00011101u;
    g_pg.shader_stage_program = 1u;
    CHECK(screen_space_mov_shader_matches());
    g_pg.combiner_control = 0x00021121u;
    g_pg.shader_stage_program = 0x00000401u;
    g_pg.color_icw[0] = 0x12345678u;
    CHECK(screen_space_mov_shader_matches());
    g_pg.transform_program[5] ^= 1u;
    CHECK(!screen_space_mov_shader_matches());
    g_pg.transform_program[5] ^= 1u;
    g_pg.transform_mode = 0u;
    CHECK(!screen_space_mov_shader_matches());
}
static unsigned test_backing_and_postprocess(int negative)
{
    const uint32_t address=0x18000;
    unsigned checked=0;
    g_pg.active_pushbuffer=NULL; g_pg.tex[1].enabled=1;
    g_pg.tex[1].offset=address; g_pg.tex[1].format=0x08013a29;
    extra_pitch=16;
    for(unsigned scenario=0;scenario<3;++scenario) {
        /* Both windows remain mapped and valid, including all-zero data.
         * Content heuristics cannot tell which backing owns this resource. */
        for(unsigned i=0;i<1024;++i) {
            ram[address+i]=scenario==0?0:(uint8_t)(i*29+13);
            contiguous_ram[address+i]=scenario==1?0:(uint8_t)(i*17+71);
        }
        Texture *t=(Texture *)dah_mesh_texture_window(1,&device,negative?0:1); CHECK(t);
        CHECK(t->width==1 && t->height==256);
        verify(t,contiguous_ram+address,1); ++checked;
        /* Same offset+format must still distinguish a changed source pointer. */
        CHECK((Texture *)dah_mesh_texture(1,&device)==t);
        verify(t,ram+address,1); ++checked;
        CHECK((Texture *)dah_mesh_texture_window(1,&device,1)==t);
        verify(t,contiguous_ram+address,1); ++checked;
        setup_postprocess(); postprocess_active=1;
        /* Actual PGRAPH submission must derive X8's mask from the sampled
         * format and clear it on the following A8 draw, even for one RT. */
        expected_alpha_mask=scenario==1?1u:0u;
        if(scenario==1)g_pg.tex[0].format=0x00011e29;
        unsigned before=postprocess_draws;
        CHECK(submit_postprocess()==1 && postprocess_draws==before+1);
        CHECK(postprocess_combiner_calls==postprocess_draws && postprocess_scene_binds==postprocess_draws);
        CHECK(postprocess_alpha_masks==postprocess_draws);
        /* The documented backing exception is scoped to the observed table. */
        g_pg.tex[1].format^=0x00100000u;
        CHECK(submit_postprocess()==0 && postprocess_draws==before+1);
        g_pg.tex[1].format^=0x00100000u;
        postprocess_active=0; ++checked;
    }
    return checked;
}
int main(int argc, char **argv)
{
    int negative = argc == 2 && strcmp(argv[1], "--old-no-channel-swap") == 0;
    int wrong_window = argc == 2 && strcmp(argv[1], "--wrong-low-window") == 0;
    ram = VirtualAlloc(NULL, (SIZE_T)XBOX_CONTIG_BASE+g_xbox_total_ram, MEM_RESERVE, PAGE_NOACCESS);
    CHECK(ram);
    {
        const float red[4] = { 1.0f, 0.0f, 0.0f, 1.0f };
        const float blue[4] = { 0.0f, 0.0f, 1.0f, 0.5f };
        CHECK(pack_argb(red) == 0xFFFF0000u);
        CHECK(pack_argb(blue) == 0x800000FFu);
        uint32_t packed_red = pack_rgba8(red);
        uint32_t packed_blue = pack_rgba8(blue);
        const uint8_t *red_bytes = (const uint8_t *)&packed_red;
        const uint8_t *blue_bytes = (const uint8_t *)&packed_blue;
        CHECK(red_bytes[0] == 255u && red_bytes[1] == 0u &&
              red_bytes[2] == 0u && red_bytes[3] == 255u);
        CHECK(blue_bytes[0] == 0u && blue_bytes[1] == 0u &&
              blue_bytes[2] == 255u && blue_bytes[3] == 128u);
    }
    {
        float texcoord[4] = { 0.25f, -0.5f, 0.0f, 0.0f };
        dah_complete_static_texcoord(2, texcoord);
        CHECK(texcoord[0] == 0.25f && texcoord[1] == -0.5f &&
              texcoord[2] == 0.0f && texcoord[3] == 1.0f);
    }
    CHECK(VirtualAlloc(ram,g_xbox_total_ram,MEM_COMMIT,PAGE_READWRITE)==ram);
    contiguous_ram=ram+XBOX_CONTIG_BASE;
    CHECK(VirtualAlloc(contiguous_ram,g_xbox_total_ram,MEM_COMMIT,PAGE_READWRITE)==contiguous_ram);
    device.lpVtbl = &device_vtable;
    device_vtable.CreateTexture = create; texture_vtable.Release = release;
    texture_vtable.LockRect = lock; texture_vtable.UnlockRect = unlock;
    device_vtable.SetRenderState=set_render_state; device_vtable.SetTextureStageState=set_stage_state;
    device_vtable.SetTexture=set_texture; device_vtable.SetVertexShader=set_vertex_shader;
    device_vtable.BeginScene=begin_scene; device_vtable.DrawPrimitiveUP=draw;
    test_screen_space_mov_shader_identity();
    for (unsigned i = 0; i < 8192; ++i) ram[0x10000+i] = (uint8_t)(i*29 + (i/4)*7 + 11);
    /* Retail 1x256 table, then wider rectangular texture, then existing ARGB. */
    const uint32_t formats[] = {0x08013A29u, 0x03013A29u, 0x03010629u};
    const unsigned widths[] = {1,1,1}, heights[] = {256,8,8};
    unsigned checked = 0;
    for (unsigned k = 0; k < 4; ++k) {
        unsigned spec = k == 3 ? 1 : k;
        uint32_t fmt = formats[spec];
        if (k == 3) { fmt = 0x03013A29u | (2u << 20); extra_pitch = 0; }
        g_pg.tex[1].enabled = 1; g_pg.tex[1].offset = 0x10000 + k*2048;
        g_pg.tex[1].format = negative && k == 0 ? (fmt & ~0xFF00u) | 0x0600u : fmt;
        g_pg.active_pushbuffer = NULL;
        Texture *t = (Texture *)dah_mesh_texture(1, &device); CHECK(t);
        CHECK(t->width == (k == 3 ? 4 : widths[spec]) && t->height == heights[spec]);
        verify(t, ram + g_pg.tex[1].offset, spec != 2); ++checked;
        unsigned before = uploads, created = creations;
        CHECK((Texture *)dah_mesh_texture(1, &device) == t && uploads == before);
        /* In-place changes must update the same resource on the next call. */
        ram[g_pg.tex[1].offset + 2] ^= 0x7B;
        CHECK((Texture *)dah_mesh_texture(1, &device) == t);
        CHECK(uploads == before + 1 && creations == created);
        verify(t, ram + g_pg.tex[1].offset, spec != 2); ++checked;
        /* A later pushbuffer must observe mutations despite per-submit reuse. */
        const uint32_t marker = 0;
        g_pg.active_pushbuffer = &marker; g_pg.active_submission = 40 + k*2;
        CHECK((Texture *)dah_mesh_texture(1, &device) == t && uploads == before + 1);
        ram[g_pg.tex[1].offset + 3] ^= 0x36; ++g_pg.active_submission;
        CHECK((Texture *)dah_mesh_texture(1, &device) == t && uploads == before + 2);
        verify(t, ram + g_pg.tex[1].offset, spec != 2); ++checked;
    }
    checked+=test_backing_and_postprocess(wrong_window);
    for (unsigned i = 0; i < 256; ++i) if (dah_mesh_textures[i].texture) {
        dah_mesh_textures[i].texture->lpVtbl->Release(dah_mesh_textures[i].texture);
        dah_mesh_texture_snapshot_drop(&dah_mesh_textures[i]);
    }
    VirtualFree(ram, 0, MEM_RELEASE);
    printf("PASS: %u production texture checks; conversion/pitch/Morton/cache mutation, distinct low/contiguous backing including valid zeros, %u real postprocess submissions with scoped format guard and A8/X8/A8 alpha-view routing\n", checked, postprocess_draws);
    return 0;
}
