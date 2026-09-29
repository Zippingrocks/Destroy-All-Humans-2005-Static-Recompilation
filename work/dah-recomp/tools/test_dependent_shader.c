/* Actual production mode decoder, HLSL generator, shader cache and constant
 * upload rendered through offscreen WARP. No window or physical GPU required. */
#define _CRT_SECURE_NO_WARNINGS
#include <math.h>
#include "../../../third_party/xboxrecomp/src/d3d/d3d8_combiners.c"
#define CHECK(x) do { if (!(x)) { fprintf(stderr, "FAIL line %d: %s\n", __LINE__, #x); exit(1); } } while (0)
#define HR(x) do { HRESULT result_ = (x); if (FAILED(result_)) { fprintf(stderr, "FAIL line %d HRESULT %08lX: %s\n", __LINE__, (unsigned long)result_, #x); exit(1); } } while (0)
static ID3D11Device *device;
static ID3D11DeviceContext *context;
static DWORD render_states[512];
ID3D11Device *d3d8_GetD3D11Device(void) { return device; }
ID3D11DeviceContext *d3d8_GetD3D11Context(void) { return context; }
const DWORD *d3d8_GetRenderStates(void) { return render_states; }
static ID3DBlob *compile(const char *text, const char *profile)
{
    ID3DBlob *code = NULL, *errors = NULL;
    HRESULT hr = D3DCompile(text, strlen(text), "test_dependent", NULL, NULL, "main", profile,
                           D3DCOMPILE_ENABLE_STRICTNESS, 0, &code, &errors);
    if (errors) { fprintf(stderr, "%s", (char *)ID3D10Blob_GetBufferPointer(errors)); ID3D10Blob_Release(errors); }
    HR(hr); return code;
}
static ID3D11ShaderResourceView *texture(unsigned width, unsigned height, DXGI_FORMAT format,
    const void *data, unsigned pitch)
{
    D3D11_TEXTURE2D_DESC desc = {0};
    desc.Width = width; desc.Height = height; desc.MipLevels = desc.ArraySize = 1;
    desc.Format = format; desc.SampleDesc.Count = 1;
    desc.Usage = D3D11_USAGE_IMMUTABLE; desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
    D3D11_SUBRESOURCE_DATA source = {data, pitch, 0};
    ID3D11Texture2D *image = NULL; ID3D11ShaderResourceView *view = NULL;
    HR(ID3D11Device_CreateTexture2D(device, &desc, &source, &image));
    HR(ID3D11Device_CreateShaderResourceView(device, (ID3D11Resource *)image, NULL, &view));
    ID3D11Texture2D_Release(image); return view;
}
static void table_color(unsigned row, unsigned column, uint8_t rgba[4])
{
    rgba[0] = (uint8_t)(row*17 + column*73 + 11);
    rgba[1] = (uint8_t)(row*29 + column*31 + 53);
    rgba[2] = (uint8_t)(row*43 + column*97 + 101);
    rgba[3] = (uint8_t)(row*7 + column*47 + 151);
}
static unsigned run(unsigned table_width, int linear, int negative)
{
    float source[256][4]; uint8_t table[256*2*4];
    for (unsigned i = 0; i < 256; ++i) {
        source[i][0] = (i + 0.5f)/256;
        source[i][1] = 0.7f; source[i][2] = 0.9f;
        source[i][3] = ((i%table_width) + 0.5f)/table_width;
        for (unsigned col = 0; col < table_width; ++col) {
            uint8_t rgba[4]; table_color(i, col, rgba);
            uint8_t *d = table+(i*table_width+col)*4;
            d[0]=rgba[2]; d[1]=rgba[1]; d[2]=rgba[0]; d[3]=rgba[3];
        }
    }
    ID3D11ShaderResourceView *views[] = {
        texture(256, 1, DXGI_FORMAT_R32G32B32A32_FLOAT, source, sizeof(source)),
        texture(table_width, 256, DXGI_FORMAT_B8G8R8A8_UNORM, table, table_width*4)
    };
    D3D11_SAMPLER_DESC sampler_desc = {0};
    sampler_desc.Filter = linear ? D3D11_FILTER_MIN_MAG_LINEAR_MIP_POINT : D3D11_FILTER_MIN_MAG_MIP_POINT;
    sampler_desc.AddressU = sampler_desc.AddressV = sampler_desc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
    sampler_desc.MaxLOD = D3D11_FLOAT32_MAX;
    ID3D11SamplerState *sampler = NULL;
    HR(ID3D11Device_CreateSamplerState(device, &sampler_desc, &sampler));
    ID3D11SamplerState *samplers[] = {sampler, sampler};
    ID3D11DeviceContext_PSSetShaderResources(context, 0, 2, views);
    ID3D11DeviceContext_PSSetSamplers(context, 0, 2, samplers);
    uint32_t words[8] = {0};
    /* Final RGB=D=T1; alpha=G=T1.a. No color arithmetic can hide errors. */
    d3d8_combiners_set_nv2a(0, 0x1e1u, words, words, words, words, words, words, 9u, 0x1900u);
    CHECK(g_combiner_state.tex_mode[0] == NV2A_TEXMODE_2D);
    CHECK(g_combiner_state.tex_mode[1] == NV2A_TEXMODE_DEPENDENT_AR_T0);
    if (negative == 1) g_combiner_state.tex_mode[1] = NV2A_TEXMODE_NONE;
    if (negative == 2) g_combiner_state.tex_mode[1] = NV2A_TEXMODE_2D;
    CHECK(d3d8_combiners_prepare_draw());
    D3D11_TEXTURE2D_DESC desc = {0};
    desc.Width=256; desc.Height=1; desc.MipLevels=desc.ArraySize=1;
    desc.Format=DXGI_FORMAT_R8G8B8A8_UNORM; desc.SampleDesc.Count=1;
    desc.Usage=D3D11_USAGE_DEFAULT; desc.BindFlags=D3D11_BIND_RENDER_TARGET;
    ID3D11Texture2D *target=NULL, *staging=NULL; ID3D11RenderTargetView *rtv=NULL;
    HR(ID3D11Device_CreateTexture2D(device, &desc, NULL, &target));
    HR(ID3D11Device_CreateRenderTargetView(device, (ID3D11Resource *)target, NULL, &rtv));
    desc.Usage=D3D11_USAGE_STAGING; desc.BindFlags=0; desc.CPUAccessFlags=D3D11_CPU_ACCESS_READ;
    HR(ID3D11Device_CreateTexture2D(device, &desc, NULL, &staging));
    const D3D11_VIEWPORT viewport={0,0,256,1,0,1};
    const float clear[4]={1,0,1,0};
    ID3D11DeviceContext_RSSetViewports(context, 1, &viewport);
    ID3D11DeviceContext_OMSetRenderTargets(context, 1, &rtv, NULL);
    ID3D11DeviceContext_ClearRenderTargetView(context, rtv, clear);
    ID3D11DeviceContext_Draw(context, 3, 0);
    ID3D11DeviceContext_OMSetRenderTargets(context, 0, NULL, NULL);
    ID3D11DeviceContext_CopyResource(context, (ID3D11Resource *)staging, (ID3D11Resource *)target);
    D3D11_MAPPED_SUBRESOURCE mapped;
    HR(ID3D11DeviceContext_Map(context, (ID3D11Resource *)staging, 0, D3D11_MAP_READ, 0, &mapped));
    unsigned checked=0;
    for (unsigned i=0; i<256; ++i) {
        uint8_t expected[4]; table_color(i, i%table_width, expected);
        const uint8_t *actual=(const uint8_t *)mapped.pData+i*4;
        for (unsigned ch=0; ch<4; ++ch) {
            if (abs((int)actual[ch]-(int)expected[ch])>1) {
                fprintf(stderr,"FAIL WARP LUT width=%u filter=%s x=%u channel=%u actual=%u expected=%u\n",
                    table_width,linear?"linear":"point",i,ch,actual[ch],expected[ch]); exit(1);
            }
            ++checked;
        }
    }
    ID3D11DeviceContext_Unmap(context, (ID3D11Resource *)staging, 0);
    ID3D11ShaderResourceView *none[]={NULL,NULL};
    ID3D11DeviceContext_PSSetShaderResources(context,0,2,none);
    ID3D11ShaderResourceView_Release(views[0]); ID3D11ShaderResourceView_Release(views[1]);
    ID3D11SamplerState_Release(sampler); ID3D11Texture2D_Release(target);
    ID3D11Texture2D_Release(staging); ID3D11RenderTargetView_Release(rtv);
    return checked;
}
int main(int argc, char **argv)
{
    int negative=argc==2 && !strcmp(argv[1],"--old-disabled-stage")?1:
                 argc==2 && !strcmp(argv[1],"--wrong-vertex-uv")?2:0;
    D3D_FEATURE_LEVEL level;
    HR(D3D11CreateDevice(NULL,D3D_DRIVER_TYPE_WARP,NULL,0,NULL,0,D3D11_SDK_VERSION,&device,&level,&context));
    HR(d3d8_combiners_init());
    const char *vertex=
        "struct O {float4 p:SV_POSITION; float4 c0:COLOR0; float4 c1:COLOR1; float2 t0:TEXCOORD0; float3 t1:TEXCOORD1; float2 t2:TEXCOORD2; float2 t3:TEXCOORD3;};"
        "O main(uint id:SV_VertexID){O o=(O)0; float2 p=id==0?float2(-1,1):id==1?float2(3,1):float2(-1,-3);"
        "o.p=float4(p,0,1);o.t0=(p+float2(1,-1))*float2(.5,-.5);o.t1=float3(.125,.875,0);return o;}";
    ID3DBlob *code=compile(vertex,"vs_4_0"); ID3D11VertexShader *vs=NULL;
    HR(ID3D11Device_CreateVertexShader(device,ID3D10Blob_GetBufferPointer(code),ID3D10Blob_GetBufferSize(code),NULL,&vs));
    ID3D10Blob_Release(code);
    ID3D11DeviceContext_VSSetShader(context,vs,NULL,0);
    ID3D11DeviceContext_IASetPrimitiveTopology(context,D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    D3D11_RASTERIZER_DESC raster={0}; raster.FillMode=D3D11_FILL_SOLID; raster.CullMode=D3D11_CULL_NONE;
    ID3D11RasterizerState *raster_state=NULL;
    HR(ID3D11Device_CreateRasterizerState(device,&raster,&raster_state));
    ID3D11DeviceContext_RSSetState(context,raster_state);
    unsigned checked=0;
    for(unsigned width=1;width<=2;++width) for(int linear=0;linear<=1;++linear) checked+=run(width,linear,negative);
    ID3D11DeviceContext_ClearState(context); d3d8_combiners_shutdown();
    ID3D11RasterizerState_Release(raster_state); ID3D11VertexShader_Release(vs);
    ID3D11DeviceContext_Release(context); ID3D11Device_Release(device);
    printf("PASS: %u offscreen WARP channel checks from actual production mode decoder/HLSL/cache; 1x256 and 2x256 tables, both AR coordinates, point/linear filters\n",checked);
    return 0;
}
