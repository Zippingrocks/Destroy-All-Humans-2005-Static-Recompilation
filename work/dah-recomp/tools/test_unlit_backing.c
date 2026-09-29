/* Exercise the complete production indexed draw path with independent low and
 * contiguous RAM. No window, graphics device, or game process is created. */
#define _CRT_SECURE_NO_WARNINGS
#ifndef DAH_PGRAPH_TEST_SOURCE
#define DAH_PGRAPH_TEST_SOURCE "../../../third_party/xboxrecomp/src/nv2a/nv2a_pgraph_d3d11.c"
#endif
#include DAH_PGRAPH_TEST_SOURCE
#define CHECK(x) do { if (!(x)) { fprintf(stderr,"FAIL line %d: %s\n",__LINE__,#x); exit(1); } } while (0)

size_t g_xbox_total_ram = 64u * 1024u * 1024u;
static uint8_t *ram, *contiguous_ram;
static IDirect3DDevice8 device;
static IDirect3DDevice8Vtbl device_vtable;
static unsigned draws, checked_vertices, valid_zero_fixture;
enum { BUFFER_ADDRESS = 0x03EA6000u, FIRST_VERTEX = 599u };
typedef struct { float xyz[3], uv[2]; uint32_t argb; } InputVertex;
static const InputVertex fixture[4] = {
    {{-258.0f,-4.0f,0.0f},{0.0f,1.0f},0xFFFF66AAu},
    {{-258.0f, 2.0f,0.0f},{0.0f,0.0f},0xFFC0FF11u},
    {{-256.0f,-4.0f,0.0f},{1.0f,1.0f},0x807722CCu},
    {{-256.0f, 2.0f,0.0f},{1.0f,0.0f},0x40449933u}
};
void *xbox_GetMemoryBase(void) { return ram; }
ptrdiff_t xbox_GetMemoryOffset(void) { return (ptrdiff_t)ram; }
IDirect3DDevice8 *xbox_GetD3DDevice(void) { return &device; }
/* Link dependencies of the production translation unit. Unexpected resource
 * or readback operations fail instead of silently becoming mock successes. */
void d3d8_MarkFullScreenMovieFrameReady(void) { CHECK(0); }
int d3d8_IsFullScreenMovieFrame(void) { CHECK(0); return 0; }
ID3D11Device *d3d8_GetD3D11Device(void) { CHECK(0); return NULL; }
ID3D11DeviceContext *d3d8_GetD3D11Context(void) { CHECK(0); return NULL; }
const DWORD *d3d8_GetRenderStates(void) { CHECK(0); return NULL; }
HRESULT d3d8_PgraphBindRenderTarget(UINT a,BOOL b,UINT c,UINT d)
{ (void)a;(void)b;(void)c;(void)d;CHECK(0);return E_FAIL; }
HRESULT d3d8_PgraphBindDepthSurface(UINT a,UINT b)
{ (void)a;(void)b;CHECK(0);return E_FAIL; }
HRESULT d3d8_PgraphBindRenderTargetTexture(DWORD a,UINT b)
{ (void)a;(void)b;CHECK(0);return E_FAIL; }
BOOL d3d8_PgraphTryBindRenderTargetTexture(DWORD a,UINT b)
{ (void)a;(void)b;CHECK(0);return FALSE; }
HRESULT d3d8_CreateCubeTextureImpl(UINT a,UINT b,D3DFORMAT c,IDirect3DTexture8 **d)
{ (void)a;(void)b;(void)c;(void)d;CHECK(0);return E_FAIL; }
HRESULT d3d8_UploadCubeTextureImpl(IDirect3DTexture8 *a,const uint8_t *b,size_t c)
{ (void)a;(void)b;(void)c;CHECK(0);return E_FAIL; }
int dah_request_frame_capture(void) { CHECK(0);return 0; }
void d3d8_combiners_set_vertex_fog(int enabled) { CHECK(enabled==1); }
void d3d8_combiners_set_texture_alpha_one_mask(uint32_t mask) { CHECK(mask==0); }
void d3d8_combiners_set_nv2a(uint32_t a,uint32_t b,const uint32_t *c,const uint32_t *d,
    const uint32_t *e,const uint32_t *f,const uint32_t *g,const uint32_t *h,uint32_t i,uint32_t j)
{ (void)a;(void)b;(void)c;(void)d;(void)e;(void)f;(void)g;(void)h;(void)i;(void)j; }
static HRESULT __stdcall render_state(IDirect3DDevice8 *self,D3DRENDERSTATETYPE state,DWORD value)
{ (void)self;(void)state;(void)value;return S_OK; }
static HRESULT __stdcall stage_state(IDirect3DDevice8 *self,DWORD stage,D3DTEXTURESTAGESTATETYPE type,DWORD value)
{ (void)self;(void)type;(void)value;CHECK(stage<4);return S_OK; }
static HRESULT __stdcall set_texture(IDirect3DDevice8 *self,DWORD stage,IDirect3DBaseTexture8 *texture)
{ (void)self;CHECK(stage<4 && texture==NULL);return S_OK; }
static HRESULT __stdcall pixel_shader(IDirect3DDevice8 *self,DWORD shader)
{ (void)self;CHECK(shader==0);return S_OK; }
static HRESULT __stdcall vertex_shader(IDirect3DDevice8 *self,DWORD shader)
{ (void)self;CHECK(shader==(D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX3));return S_OK; }
static HRESULT __stdcall begin_scene(IDirect3DDevice8 *self) { (void)self;return S_OK; }
static HRESULT __stdcall draw(IDirect3DDevice8 *self,D3DPRIMITIVETYPE primitive,
    UINT count,const void *data,UINT stride)
{
    (void)self;CHECK(primitive==D3DPT_TRIANGLESTRIP);
    CHECK(count==g_pg.index_count-2u && stride==sizeof(OutputVertex));
    const OutputVertex *vertices=data;
    for(unsigned i=0;i<g_pg.index_count;++i){
        const InputVertex *input=&fixture[g_pg.indices[i]-FIRST_VERTEX];
        const OutputVertex *v=&vertices[i];
        float x=valid_zero_fixture?330.5f:input->xyz[0]+330.5f;
        float y=valid_zero_fixture?49.0f:input->xyz[1]+49.0f;
        if(v->x!=x || v->y!=y){
            fprintf(stderr,"wrong vertex backing: i=%u actual=%.9g,%.9g expected=%.9g,%.9g\n",i,v->x,v->y,x,y);
            exit(1);
        }
        CHECK(v->z==0.0f && v->rhw==1.0f);
        CHECK(v->u==(valid_zero_fixture?0.0f:input->uv[0]));
        CHECK(v->v==(valid_zero_fixture?0.0f:input->uv[1]));
        CHECK(v->color==(valid_zero_fixture?0u:input->argb));
        ++checked_vertices;
    }
    ++draws;return S_OK;
}
static void setup(unsigned index_count)
{
    memset(&g_pg,0,sizeof(g_pg));
    g_pg.transform_mode=2;g_pg.draw_mode=6;g_pg.index_count=index_count;
    memcpy(g_pg.transform_program,dah_unlit9_program,sizeof(dah_unlit9_program));
    memset(g_pg.transform_valid,1,sizeof(dah_unlit9_program)/sizeof(uint32_t));
    memset(g_pg.transform_constant_valid,1,sizeof(g_pg.transform_constant_valid));
    float (*constants)[4]=(float (*)[4])g_pg.transform_constants;
    constants[1][0]=330.5f;constants[1][1]=49.0f;
    for(unsigned i=0;i<3;++i)constants[2][i]=1.0f;
    for(unsigned i=0;i<4;++i)constants[36+i][i]=1.0f;
    constants[187][0]=1.0f;
    const unsigned offsets[3]={0,12,20},formats[3]={0x1832,0x1822,0x1840};
    for(unsigned i=0;i<3;++i){g_pg.array_offset[i]=BUFFER_ADDRESS+offsets[i];g_pg.array_format[i]=formats[i];}
    for(unsigned i=0;i<index_count;++i)g_pg.indices[i]=FIRST_VERTEX+i%4u;
    g_pg.surface_format=0x124;g_pg.color_mask=0x01010101;
    g_pg.blend_equation=0x8006;
}
int main(void)
{
    CHECK(sizeof(InputVertex)==24);
    ram=VirtualAlloc(NULL,(SIZE_T)XBOX_CONTIG_BASE+g_xbox_total_ram,MEM_RESERVE,PAGE_NOACCESS);
    CHECK(ram);
    CHECK(VirtualAlloc(ram,g_xbox_total_ram,MEM_COMMIT,PAGE_READWRITE)==ram);
    contiguous_ram=ram+XBOX_CONTIG_BASE;
    CHECK(VirtualAlloc(contiguous_ram,g_xbox_total_ram,MEM_COMMIT,PAGE_READWRITE)==contiguous_ram);
    device.lpVtbl=&device_vtable;
    device_vtable.SetRenderState=render_state;device_vtable.SetTextureStageState=stage_state;
    device_vtable.SetTexture=set_texture;device_vtable.SetPixelShader=pixel_shader;
    device_vtable.SetVertexShader=vertex_shader;device_vtable.BeginScene=begin_scene;
    device_vtable.DrawPrimitiveUP=draw;
    size_t address=BUFFER_ADDRESS+FIRST_VERTEX*sizeof(InputVertex);
    /* Reproduce the live mismatch: low bytes are zero, high bytes carry HUD
     * positions, UVs and packed colors. A nonzero first index also tests the
     * offset/range arithmetic used for the 599..759 live shield strip. */
    memcpy(contiguous_ram+address,fixture,sizeof(fixture));
    for(unsigned pass=0;pass<6;++pass){setup(pass<4?4:240);CHECK(submit_indexed_3d()==1);}
    CHECK(draws==6);
    /* Real zeros in the correct backing must not trigger a heuristic fallback
     * to plausible low-memory values. */
    memcpy(ram+address,fixture,sizeof(fixture));
    memset(contiguous_ram+address,0,sizeof(fixture));valid_zero_fixture=1;
    setup(4);CHECK(submit_indexed_3d()==1 && draws==7);
    /* Existing exact signature/declaration guards must continue rejecting
     * unrelated programs and layouts before submitting a vertex. */
    setup(4);g_pg.array_format[2]=0x1844;CHECK(submit_indexed_3d()==0 && draws==7);
    setup(4);g_pg.array_offset[1]+=4;CHECK(submit_indexed_3d()==0 && draws==7);
    setup(4);g_pg.transform_program[34]^=0x100u;CHECK(submit_indexed_3d()==0 && draws==7);
    VirtualFree(ram,0,MEM_RELEASE);
    printf("PASS: %u production indexed draws, %u vertices; separate RAM windows, XYZ/UV/BGRA, repeated-index cache, valid zeros and exact signature/layout guards\n",draws,checked_vertices);
    return 0;
}
