/* Actual production combiner decoder/cache/HLSL on an offscreen WARP device.
 * RGBA-backed render targets viewed as Xbox X8 must sample alpha as one. */
#define main dependent_shader_fixture_main
#include "test_dependent_shader.c"
#undef main

static ID3D11RenderTargetView *x8_rtv;
static ID3D11Texture2D *x8_target, *x8_staging;
static unsigned x8_checked;
static void check_pixels(const char *label, const uint8_t expected[8])
{
    const float stale_red[4]={0.8f,0,0,1};
    CHECK(d3d8_combiners_prepare_draw());
    ID3D11DeviceContext_OMSetRenderTargets(context,1,&x8_rtv,NULL);
    ID3D11DeviceContext_ClearRenderTargetView(context,x8_rtv,stale_red);
    ID3D11DeviceContext_Draw(context,3,0);
    ID3D11DeviceContext_OMSetRenderTargets(context,0,NULL,NULL);
    ID3D11DeviceContext_CopyResource(context,(ID3D11Resource *)x8_staging,(ID3D11Resource *)x8_target);
    D3D11_MAPPED_SUBRESOURCE mapped;
    HR(ID3D11DeviceContext_Map(context,(ID3D11Resource *)x8_staging,0,D3D11_MAP_READ,0,&mapped));
    const uint8_t *actual=mapped.pData;
    for(unsigned i=0;i<8;++i){
        if(abs((int)actual[i]-(int)expected[i])>1){
            fprintf(stderr,"FAIL %s pixel=%u channel=%u actual=%u expected=%u\n",label,i/4,i%4,actual[i],expected[i]);exit(1);
        }
        ++x8_checked;
    }
    ID3D11DeviceContext_Unmap(context,(ID3D11Resource *)x8_staging,0);
}
static void upload_threshold(void)
{
    /* Captured retail Pox pass 64 from dah_pb_54776_012000.bin.
     * RGB = max(T0.rgb - V0.rgb, 0), A = T0.a, alpha GREATER 64/255. */
    const uint32_t rgbin[8]={0xC820C440},rgbout[8]={0x00000C00};
    const uint32_t ain[8]={0xD830D450,0xD8301010},aout[8]={0x00000C00,0x000000C0};
    const uint32_t constants[8]={0};
    d3d8_combiners_set_nv2a(0x00011102,1,0,rgbin,rgbout,ain,aout,constants,constants,0x0000000E,0x00001C80);
    CHECK(g_combiner_state.tex_alpha_one_mask==0);
}
int main(int argc,char **argv)
{
    int negative=argc==2&&!strcmp(argv[1],"--old-stored-alpha");
    D3D_FEATURE_LEVEL level;
    HR(D3D11CreateDevice(NULL,D3D_DRIVER_TYPE_WARP,NULL,0,NULL,0,D3D11_SDK_VERSION,&device,&level,&context));
    HR(d3d8_combiners_init());
    const char *vertex=
        "struct O {float4 p:SV_POSITION; float4 c0:COLOR0; float4 c1:COLOR1; float2 t0:TEXCOORD0; float3 t1:TEXCOORD1; float2 t2:TEXCOORD2; float2 t3:TEXCOORD3;};"
        "O main(uint id:SV_VertexID){O o=(O)0; float2 p=id==0?float2(-1,1):id==1?float2(3,1):float2(-1,-3);"
        "o.p=float4(p,0,1);o.c0=float4(.5,.5,.5,1);o.t0=(p+float2(1,-1))*float2(.5,-.5);o.t1=float3(o.t0,0);o.t2=o.t3=o.t0;return o;}";
    ID3DBlob *code=compile(vertex,"vs_4_0");ID3D11VertexShader *vs=NULL;
    HR(ID3D11Device_CreateVertexShader(device,ID3D10Blob_GetBufferPointer(code),ID3D10Blob_GetBufferSize(code),NULL,&vs));
    ID3D10Blob_Release(code);ID3D11DeviceContext_VSSetShader(context,vs,NULL,0);
    ID3D11DeviceContext_IASetPrimitiveTopology(context,D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    D3D11_RASTERIZER_DESC raster={0};raster.FillMode=D3D11_FILL_SOLID;raster.CullMode=D3D11_CULL_NONE;
    ID3D11RasterizerState *raster_state=NULL;
    HR(ID3D11Device_CreateRasterizerState(device,&raster,&raster_state));ID3D11DeviceContext_RSSetState(context,raster_state);
    const D3D11_VIEWPORT viewport={0,0,2,1,0,1};ID3D11DeviceContext_RSSetViewports(context,1,&viewport);
    D3D11_TEXTURE2D_DESC desc={0};desc.Width=2;desc.Height=1;desc.MipLevels=desc.ArraySize=1;
    desc.Format=DXGI_FORMAT_R8G8B8A8_UNORM;desc.SampleDesc.Count=1;desc.BindFlags=D3D11_BIND_RENDER_TARGET;
    HR(ID3D11Device_CreateTexture2D(device,&desc,NULL,&x8_target));
    HR(ID3D11Device_CreateRenderTargetView(device,(ID3D11Resource *)x8_target,NULL,&x8_rtv));
    desc.Usage=D3D11_USAGE_STAGING;desc.BindFlags=0;desc.CPUAccessFlags=D3D11_CPU_ACCESS_READ;
    HR(ID3D11Device_CreateTexture2D(device,&desc,NULL,&x8_staging));
    const float source[2][4]={{.75f,.25f,.625f,0},{.25f,.875f,.625f,.125f}};
    ID3D11ShaderResourceView *scene=texture(2,1,DXGI_FORMAT_R32G32B32A32_FLOAT,source,sizeof(source));
    ID3D11ShaderResourceView *views[4]={scene,scene,scene,scene};
    ID3D11DeviceContext_PSSetShaderResources(context,0,4,views);
    D3D11_SAMPLER_DESC sd={0};sd.Filter=D3D11_FILTER_MIN_MAG_MIP_POINT;
    sd.AddressU=sd.AddressV=sd.AddressW=D3D11_TEXTURE_ADDRESS_CLAMP;sd.MaxLOD=D3D11_FLOAT32_MAX;
    ID3D11SamplerState *sampler=NULL;HR(ID3D11Device_CreateSamplerState(device,&sd,&sampler));
    ID3D11SamplerState *samplers[4]={sampler,sampler,sampler,sampler};ID3D11DeviceContext_PSSetSamplers(context,0,4,samplers);
    render_states[D3DRS_ALPHATESTENABLE]=1;render_states[D3DRS_ALPHAFUNC]=5;render_states[D3DRS_ALPHAREF]=64;
    const uint8_t threshold[8]={64,0,32,255,0,96,32,255},stale[8]={204,0,0,255,204,0,0,255};
    /* Same resources and combiner repeatedly switch A8/X8 views. This also
     * verifies the format semantic participates in the production cache key. */
    for(unsigned pass=0;pass<4;++pass){
        upload_threshold();
        if(pass&1)d3d8_combiners_set_texture_alpha_one_mask(negative?0:1);
        check_pixels(pass&1?"captured X8 threshold replaces stale red":"A8 threshold preserves legitimate alpha discard",pass&1?threshold:stale);
    }
    render_states[D3DRS_ALPHATESTENABLE]=0;
    const uint32_t zero[8]={0};
    for(unsigned stage=0;stage<4;++stage)for(unsigned x8=0;x8<2;++x8){
        d3d8_combiners_set_nv2a(0,1u<<(stage*5),0,zero,zero,zero,zero,zero,zero,8+stage,(0x18+stage)<<8);
        d3d8_combiners_set_texture_alpha_one_mask(x8?1u<<stage:0);
        uint8_t expected[8]={191,64,159,0,64,223,159,32};
        if(x8)expected[3]=expected[7]=255;
        check_pixels(x8?"X8 per-stage alpha one":"A8 per-stage stored alpha",expected);
    }
    /* A dependent AR lookup must observe T0's format alpha, not the stored
     * alpha: alpha 1 selects the right table column for both source pixels. */
    const uint8_t lut[8]={255,0,0,255,0,0,255,255};
    ID3D11ShaderResourceView *table=texture(2,1,DXGI_FORMAT_R8G8B8A8_UNORM,lut,sizeof(lut));
    ID3D11DeviceContext_PSSetShaderResources(context,1,1,&table);
    d3d8_combiners_set_nv2a(0,0x1e1,0,zero,zero,zero,zero,zero,zero,9,0x1900);
    d3d8_combiners_set_texture_alpha_one_mask(1);
    const uint8_t blue[8]={0,0,255,255,0,0,255,255};check_pixels("dependent AR consumes X8 alpha",blue);
    /* A disabled texture retains its default register contents even if a
     * stale caller mask names the stage. Render-state uploads also reset it. */
    d3d8_combiners_set_nv2a(0,0,0,zero,zero,zero,zero,zero,zero,8,0x1800);
    d3d8_combiners_set_texture_alpha_one_mask(1);
    const uint8_t disabled[8]={0,0,0,0,0,0,0,0};check_pixels("disabled texture",disabled);
    d3d8_combiners_from_render_states(render_states,&g_combiner_state);CHECK(g_combiner_state.tex_alpha_one_mask==0);
    ID3D11DeviceContext_ClearState(context);d3d8_combiners_shutdown();
    ID3D11ShaderResourceView_Release(scene);ID3D11ShaderResourceView_Release(table);ID3D11SamplerState_Release(sampler);
    ID3D11RenderTargetView_Release(x8_rtv);ID3D11Texture2D_Release(x8_target);ID3D11Texture2D_Release(x8_staging);
    ID3D11RasterizerState_Release(raster_state);ID3D11VertexShader_Release(vs);
    ID3D11DeviceContext_Release(context);ID3D11Device_Release(device);
    printf("PASS: %u offscreen WARP channel checks; captured threshold alpha test, A8/X8 cache switching, four stages, dependent AR ordering and upload reset\n",x8_checked);
    return 0;
}
