/* Actual production PGRAPH dispatch/postprocess and D3D8 state translation,
 * rendered to an offscreen WARP target. Reuse the isolated guest RAM fixture. */
#define main dependent_texture_fixture_main
#define d3d8_GetD3D11Device unused_fixture_GetD3D11Device
#define d3d8_GetD3D11Context unused_fixture_GetD3D11Context
#define d3d8_GetRenderStates unused_fixture_GetRenderStates
#include "test_dependent_texture.c"
#undef main
#undef d3d8_GetD3D11Device
#undef d3d8_GetD3D11Context
#undef d3d8_GetRenderStates
#include <d3dcompiler.h>

static ID3D11Device *warp_device;
static ID3D11DeviceContext *warp_context;
static DWORD blend_render_states[512];
static unsigned equation_writes;
ID3D11Device *d3d8_GetD3D11Device(void) { return warp_device; }
ID3D11DeviceContext *d3d8_GetD3D11Context(void) { return warp_context; }
const DWORD *d3d8_GetRenderStates(void) { return blend_render_states; }
const DWORD *d3d8_GetTSS(DWORD stage) { (void)stage; CHECK(0); return NULL; }
#include "../../../third_party/xboxrecomp/src/d3d/d3d8_states.c"

#define HR(x) do { HRESULT result_=(x); if (FAILED(result_)) { fprintf(stderr,"FAIL line %d HRESULT %08lX: %s\n",__LINE__,(unsigned long)result_,#x); exit(1); } } while(0)
static HRESULT __stdcall record_render_state(IDirect3DDevice8 *self, D3DRENDERSTATETYPE state, DWORD value)
{
    (void)self; CHECK(state<512);
    blend_render_states[state]=value;
    if(state==D3DRS_BLENDOP)++equation_writes;
    return S_OK;
}
static ID3DBlob *blend_compile(const char *text, const char *profile)
{
    ID3DBlob *code=NULL,*errors=NULL;
    HRESULT hr=D3DCompile(text,strlen(text),"test_blend_equation",NULL,NULL,"main",profile,
                         D3DCOMPILE_ENABLE_STRICTNESS,0,&code,&errors);
    if(errors){fprintf(stderr,"%s",(char *)ID3D10Blob_GetBufferPointer(errors));ID3D10Blob_Release(errors);}
    HR(hr);return code;
}
static void apply_guest_equation(uint32_t equation)
{
    CHECK(pgraph_d3d11_method(0,NV097_SET_BLEND_ENABLE,1)==1);
    CHECK(pgraph_d3d11_method(0,NV097_SET_BLEND_FUNC_SFACTOR,1)==1);
    CHECK(pgraph_d3d11_method(0,NV097_SET_BLEND_FUNC_DFACTOR,1)==1);
    CHECK(pgraph_d3d11_method(0,NV097_SET_BLEND_EQUATION,equation)==1);
    CHECK(g_pg.blend_equation==equation);
}
int main(int argc,char **argv)
{
    int negative=argc==2&&!strcmp(argv[1],"--old-add-equation");
    ram=VirtualAlloc(NULL,(SIZE_T)XBOX_CONTIG_BASE+g_xbox_total_ram,MEM_RESERVE,PAGE_NOACCESS);
    CHECK(ram && VirtualAlloc(ram,g_xbox_total_ram,MEM_COMMIT,PAGE_READWRITE)==ram);
    contiguous_ram=ram+XBOX_CONTIG_BASE;
    CHECK(VirtualAlloc(contiguous_ram,g_xbox_total_ram,MEM_COMMIT,PAGE_READWRITE)==contiguous_ram);
    device.lpVtbl=&device_vtable;device_vtable.CreateTexture=create;
    device_vtable.SetRenderState=record_render_state;device_vtable.SetTextureStageState=set_stage_state;
    device_vtable.SetTexture=set_texture;device_vtable.SetVertexShader=set_vertex_shader;
    device_vtable.BeginScene=begin_scene;device_vtable.DrawPrimitiveUP=draw;
    texture_vtable.Release=release;texture_vtable.LockRect=lock;texture_vtable.UnlockRect=unlock;
    pgraph_d3d11_init();
    CHECK(g_pg.blend_equation==NV097_SET_BLEND_EQUATION_V_FUNC_ADD);
    CHECK(dah_apply_blend_state(&device,0) && blend_render_states[D3DRS_BLENDOP]==1);

    D3D_FEATURE_LEVEL level;
    HR(D3D11CreateDevice(NULL,D3D_DRIVER_TYPE_WARP,NULL,0,NULL,0,D3D11_SDK_VERSION,&warp_device,&level,&warp_context));
    ID3DBlob *code=blend_compile("float4 main(uint id:SV_VertexID):SV_POSITION {return float4(id==0?float2(-1,1):id==1?float2(3,1):float2(-1,-3),0,1);}","vs_4_0");
    ID3D11VertexShader *vs=NULL;
    HR(ID3D11Device_CreateVertexShader(warp_device,ID3D10Blob_GetBufferPointer(code),ID3D10Blob_GetBufferSize(code),NULL,&vs));
    ID3D10Blob_Release(code);
    code=blend_compile("float4 main():SV_TARGET {return float4(32,64,128,96)/255.0;}","ps_4_0");
    ID3D11PixelShader *ps=NULL;
    HR(ID3D11Device_CreatePixelShader(warp_device,ID3D10Blob_GetBufferPointer(code),ID3D10Blob_GetBufferSize(code),NULL,&ps));
    ID3D10Blob_Release(code);
    ID3D11DeviceContext_VSSetShader(warp_context,vs,NULL,0);
    ID3D11DeviceContext_PSSetShader(warp_context,ps,NULL,0);
    ID3D11DeviceContext_IASetPrimitiveTopology(warp_context,D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    D3D11_RASTERIZER_DESC raster={0};raster.FillMode=D3D11_FILL_SOLID;raster.CullMode=D3D11_CULL_NONE;
    ID3D11RasterizerState *raster_state=NULL;
    HR(ID3D11Device_CreateRasterizerState(warp_device,&raster,&raster_state));
    ID3D11DeviceContext_RSSetState(warp_context,raster_state);
    D3D11_TEXTURE2D_DESC desc={0};desc.Width=desc.Height=2;desc.MipLevels=desc.ArraySize=1;
    desc.Format=DXGI_FORMAT_R8G8B8A8_UNORM;desc.SampleDesc.Count=1;desc.BindFlags=D3D11_BIND_RENDER_TARGET;
    ID3D11Texture2D *target=NULL,*staging=NULL;ID3D11RenderTargetView *rtv=NULL;
    HR(ID3D11Device_CreateTexture2D(warp_device,&desc,NULL,&target));
    HR(ID3D11Device_CreateRenderTargetView(warp_device,(ID3D11Resource *)target,NULL,&rtv));
    desc.Usage=D3D11_USAGE_STAGING;desc.BindFlags=0;desc.CPUAccessFlags=D3D11_CPU_ACCESS_READ;
    HR(ID3D11Device_CreateTexture2D(warp_device,&desc,NULL,&staging));
    const D3D11_VIEWPORT viewport={0,0,2,2,0,1};
    ID3D11DeviceContext_RSSetViewports(warp_context,1,&viewport);
    /* The first state is captured from menu draw 42 in
     * dah_pb_rejected_36788_004357.bin: enable=1, ONE/ONE, equation=0x800B.
     * ADD immediately afterwards also verifies restoration/cache invalidation. */
    const uint32_t equations[]={0x800B,0x8006,0x800A,0x8007,0x8008,0x800B,0x8006};
    const unsigned d3d_ops[]={3,1,2,4,5,3,1};
    const uint8_t expected[][4]={{160,64,0,128},{224,192,192,255},{0,0,64,0},
        {32,64,64,96},{192,128,128,224},{160,64,0,128},{224,192,192,255}};
    unsigned checked=0;
    for(unsigned k=0;k<sizeof(equations)/sizeof(equations[0]);++k){
        setup_postprocess();g_pg.initialized=1;postprocess_active=1;
        apply_guest_equation(equations[k]);
        unsigned before=postprocess_draws,writes_before=equation_writes;
        CHECK(submit_postprocess()==1 && postprocess_draws==before+1);
        CHECK(equation_writes==writes_before+1 && blend_render_states[D3DRS_BLENDOP]==d3d_ops[k]);
        CHECK(blend_render_states[D3DRS_ALPHABLENDENABLE] &&
              blend_render_states[D3DRS_SRCBLEND]==D3DBLEND_ONE &&
              blend_render_states[D3DRS_DESTBLEND]==D3DBLEND_ONE);
        if(negative)blend_render_states[D3DRS_BLENDOP]=1; /* Original missing-equation behavior. */
        update_blend_state(blend_render_states);CHECK(g_blend_state);
        ID3D11DeviceContext_OMSetBlendState(warp_context,g_blend_state,NULL,~0u);
        const float clear[]={192.0f/255,128.0f/255,64.0f/255,224.0f/255};
        ID3D11DeviceContext_OMSetRenderTargets(warp_context,1,&rtv,NULL);
        ID3D11DeviceContext_ClearRenderTargetView(warp_context,rtv,clear);
        ID3D11DeviceContext_Draw(warp_context,3,0);
        ID3D11DeviceContext_OMSetRenderTargets(warp_context,0,NULL,NULL);
        ID3D11DeviceContext_CopyResource(warp_context,(ID3D11Resource *)staging,(ID3D11Resource *)target);
        D3D11_MAPPED_SUBRESOURCE mapped;
        HR(ID3D11DeviceContext_Map(warp_context,(ID3D11Resource *)staging,0,D3D11_MAP_READ,0,&mapped));
        for(unsigned y=0;y<2;++y)for(unsigned x=0;x<2;++x)for(unsigned ch=0;ch<4;++ch){
            unsigned actual=((uint8_t *)mapped.pData)[y*mapped.RowPitch+x*4+ch];
            if(abs((int)actual-(int)expected[k][ch])>1){
                fprintf(stderr,"FAIL WARP equation=%04X channel=%u actual=%u expected=%u\n",equations[k],ch,actual,expected[k][ch]);return 1;
            }
            ++checked;
        }
        ID3D11DeviceContext_Unmap(warp_context,(ID3D11Resource *)staging,0);
    }
    /* Unknown and signed equations must reject instead of reusing stale ADD;
     * an unused equation remains harmless while blending is disabled. */
    const uint32_t unsupported[]={0xDEADu,0xF005u,0xF006u};
    for(unsigned k=0;k<3;++k){
        apply_guest_equation(unsupported[k]);unsigned before=postprocess_draws,writes_before=equation_writes;
        CHECK(submit_postprocess()==0 && postprocess_draws==before && equation_writes==writes_before);
        CHECK(pgraph_d3d11_method(0,NV097_SET_BLEND_ENABLE,0)==1);
        CHECK(submit_postprocess()==1 && postprocess_draws==before+1 && equation_writes==writes_before);
        CHECK(!blend_render_states[D3DRS_ALPHABLENDENABLE]);
    }
    ID3D11DeviceContext_ClearState(warp_context);d3d8_states_shutdown();
    ID3D11RenderTargetView_Release(rtv);ID3D11Texture2D_Release(staging);ID3D11Texture2D_Release(target);
    ID3D11RasterizerState_Release(raster_state);ID3D11PixelShader_Release(ps);ID3D11VertexShader_Release(vs);
    ID3D11DeviceContext_Release(warp_context);ID3D11Device_Release(warp_device);
    for(unsigned i=0;i<256;++i)if(dah_mesh_textures[i].texture){
        dah_mesh_textures[i].texture->lpVtbl->Release(dah_mesh_textures[i].texture);
        dah_mesh_texture_snapshot_drop(&dah_mesh_textures[i]);
    }
    VirtualFree(ram,0,MEM_RELEASE);
    printf("PASS: %u WARP blend-channel checks via actual PGRAPH method/postprocess + D3D8 state code; five equations, ADD restoration, disabled/unsupported/signed guards\n",checked);
    return 0;
}
