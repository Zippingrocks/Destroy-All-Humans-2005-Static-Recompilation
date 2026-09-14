/* Standalone D3D11 WARP verification. No window, swap chain, or game launch. */
#define COBJMACROS
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "xyzrhw_shader_fixture.inc"

#define CHECK(x) do { if (!(x)) { fprintf(stderr, "line %d: %s\n", __LINE__, #x); exit(1); } } while (0)
#define HR(x) do { HRESULT check_hr = (x); if (FAILED(check_hr)) { fprintf(stderr, "line %d HRESULT %08lX: %s\n", __LINE__, (unsigned long)check_hr, #x); exit(2); } } while (0)
typedef struct Vertex {
    float pos[4], normal[3], diffuse[4], specular[4], tex[4][2];
} Vertex;
typedef struct Transform {
    float matrices[48], screen[2]; uint32_t flags; float pad;
    float eye[4], fog[4];
} Transform;
typedef struct Captured { float pos[4], tex[2], diffuse[4]; } Captured;
static ID3D11Device *device;
static ID3D11DeviceContext *context;
static ID3D11VertexShader *vs;
static ID3D11InputLayout *layout;
static ID3D11Buffer *constants;
static unsigned vertex_checks, pixel_checks;

static ID3DBlob *compile(const char *source, const char *entry, const char *profile)
{
    ID3DBlob *code = NULL, *errors = NULL;
    const HRESULT result = D3DCompile(source, strlen(source), "actual-d3d8-ffp",
        NULL, NULL, entry, profile, D3DCOMPILE_ENABLE_STRICTNESS, 0, &code, &errors);
    if (FAILED(result)) {
        if (errors) fprintf(stderr, "%s\n", (char *)ID3D10Blob_GetBufferPointer(errors));
        HR(result);
    }
    if (errors) ID3D10Blob_Release(errors);
    return code;
}
static ID3D11Buffer *buffer(UINT size, UINT bind, const void *data)
{
    D3D11_BUFFER_DESC desc = {0};
    D3D11_SUBRESOURCE_DATA initial = {0};
    ID3D11Buffer *result = NULL;
    desc.ByteWidth = size; desc.Usage = D3D11_USAGE_DEFAULT; desc.BindFlags = bind;
    initial.pSysMem = data;
    HR(ID3D11Device_CreateBuffer(device, &desc, data ? &initial : NULL, &result));
    return result;
}
static void set_screen(float width, float height)
{
    Transform transform = {0};
    transform.screen[0] = width; transform.screen[1] = height;
    transform.flags = 1u | 2u; /* pretransformed + diffuse */
    ID3D11DeviceContext_UpdateSubresource(context, (ID3D11Resource *)constants, 0, NULL, &transform, 0, 0);
}
static void set_vertices(ID3D11Buffer *vertices)
{
    const UINT stride = sizeof(Vertex), offset = 0;
    ID3D11DeviceContext_IASetVertexBuffers(context, 0, 1, &vertices, &stride, &offset);
}
static void init(void)
{
    ID3DBlob *code = compile(g_vs_source, "main", "vs_4_0");
    const D3D_FEATURE_LEVEL levels[] = {D3D_FEATURE_LEVEL_11_0};
    D3D_FEATURE_LEVEL actual;
    HR(D3D11CreateDevice(NULL, D3D_DRIVER_TYPE_WARP, NULL, 0, levels, 1,
        D3D11_SDK_VERSION, &device, &actual, &context));
    CHECK(actual == D3D_FEATURE_LEVEL_11_0 && sizeof(Transform) == 240);
    HR(ID3D11Device_CreateVertexShader(device, ID3D10Blob_GetBufferPointer(code),
        ID3D10Blob_GetBufferSize(code), NULL, &vs));
    const D3D11_INPUT_ELEMENT_DESC inputs[] = {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, offsetof(Vertex, pos), D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, offsetof(Vertex, normal), D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, offsetof(Vertex, diffuse), D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"COLOR", 1, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, offsetof(Vertex, specular), D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, (UINT)offsetof(Vertex, tex[0]), D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"TEXCOORD", 1, DXGI_FORMAT_R32G32_FLOAT, 0, (UINT)offsetof(Vertex, tex[1]), D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"TEXCOORD", 2, DXGI_FORMAT_R32G32_FLOAT, 0, (UINT)offsetof(Vertex, tex[2]), D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"TEXCOORD", 3, DXGI_FORMAT_R32G32_FLOAT, 0, (UINT)offsetof(Vertex, tex[3]), D3D11_INPUT_PER_VERTEX_DATA, 0},
    };
    HR(ID3D11Device_CreateInputLayout(device, inputs, 8, ID3D10Blob_GetBufferPointer(code),
        ID3D10Blob_GetBufferSize(code), &layout));
    ID3D10Blob_Release(code);
    constants = buffer(sizeof(Transform), D3D11_BIND_CONSTANT_BUFFER, NULL);
    ID3D11DeviceContext_VSSetConstantBuffers(context, 0, 1, &constants);
    ID3D11DeviceContext_IASetInputLayout(context, layout);
    ID3D11DeviceContext_VSSetShader(context, vs, NULL, 0);
}
static float as_float(uint32_t bits)
{
    float value; memcpy(&value, &bits, sizeof(value)); return value;
}
static void stream_output(void)
{
    const char *suffix = "\n[maxvertexcount(1)] void capture(point VS_OUT p[1], inout PointStream<VS_OUT> stream) { stream.Append(p[0]); }\n";
    char *source = malloc(strlen(g_vs_source) + strlen(suffix) + 1);
    CHECK(source);
    memcpy(source, g_vs_source, strlen(g_vs_source));
    memcpy(source + strlen(g_vs_source), suffix, strlen(suffix) + 1);
    ID3DBlob *code = compile(source, "capture", "gs_5_0");
    free(source);
    const D3D11_SO_DECLARATION_ENTRY entries[] = {
        {0, "SV_POSITION", 0, 0, 4, 0}, {0, "TEXCOORD", 0, 0, 2, 0},
        {0, "COLOR", 0, 0, 4, 0}
    };
    const UINT stride = sizeof(Captured);
    ID3D11GeometryShader *gs = NULL;
    HR(ID3D11Device_CreateGeometryShaderWithStreamOutput(device,
        ID3D10Blob_GetBufferPointer(code), ID3D10Blob_GetBufferSize(code),
        entries, 3, &stride, 1, D3D11_SO_NO_RASTERIZED_STREAM, NULL, &gs));
    ID3D10Blob_Release(code);
    const uint32_t rhw_bits[] = {
        0x3f800000, 0x3f000000, 0x40000000, 0x3e800000, 0x40800000,
        0xbf800000, 0xbf000000, 0x3d800000, 0x41800000,
        0, 0x80000000, 0x7f800000, 0xff800000, 0x7fc00000, 0xffc00000,
        0x7f800001, 1, 0x80000001
    };
    const unsigned count = sizeof(rhw_bits) / sizeof(rhw_bits[0]);
    Vertex vertices[sizeof(rhw_bits) / sizeof(rhw_bits[0])] = {0};
    for (unsigned i = 0; i < count; ++i) {
        vertices[i].pos[0] = 160; vertices[i].pos[1] = 120;
        vertices[i].pos[2] = 0.375f; vertices[i].pos[3] = as_float(rhw_bits[i]);
        vertices[i].tex[0][0] = 0.25f; vertices[i].tex[0][1] = 0.75f;
        vertices[i].diffuse[0] = 0.125f; vertices[i].diffuse[1] = 0.25f;
        vertices[i].diffuse[2] = 0.5f; vertices[i].diffuse[3] = 1;
    }
    ID3D11Buffer *vb = buffer(sizeof(vertices), D3D11_BIND_VERTEX_BUFFER, vertices);
    ID3D11Buffer *output = buffer(count * sizeof(Captured), D3D11_BIND_STREAM_OUTPUT, NULL);
    D3D11_BUFFER_DESC desc = {0};
    desc.ByteWidth = count * sizeof(Captured); desc.Usage = D3D11_USAGE_STAGING;
    desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
    ID3D11Buffer *staging = NULL;
    HR(ID3D11Device_CreateBuffer(device, &desc, NULL, &staging));
    const UINT offset = 0;
    set_screen(640, 480); set_vertices(vb);
    ID3D11DeviceContext_IASetPrimitiveTopology(context, D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
    ID3D11DeviceContext_GSSetShader(context, gs, NULL, 0);
    ID3D11DeviceContext_SOSetTargets(context, 1, &output, &offset);
    ID3D11DeviceContext_Draw(context, count, 0);
    ID3D11DeviceContext_SOSetTargets(context, 0, NULL, NULL);
    ID3D11DeviceContext_GSSetShader(context, NULL, NULL, 0);
    ID3D11DeviceContext_CopyResource(context, (ID3D11Resource *)staging, (ID3D11Resource *)output);
    D3D11_MAPPED_SUBRESOURCE mapped;
    HR(ID3D11DeviceContext_Map(context, (ID3D11Resource *)staging, 0, D3D11_MAP_READ, 0, &mapped));
    const Captured *actual = mapped.pData;
    for (unsigned i = 0; i < count; ++i) {
        float expected[4] = {0, 0, 0, -1};
        if (i < 9) {
            const float w = 1.0f / vertices[i].pos[3];
            expected[0] = -0.5f * w; expected[1] = 0.5f * w;
            expected[2] = 0.375f * w; expected[3] = w;
        }
        if (memcmp(actual[i].pos, expected, sizeof(expected))) {
            fprintf(stderr, "RHW %08X output=(%g,%g,%g,%g) expected=(%g,%g,%g,%g)\n", rhw_bits[i],
                actual[i].pos[0], actual[i].pos[1], actual[i].pos[2], actual[i].pos[3],
                expected[0], expected[1], expected[2], expected[3]); exit(1);
        }
        CHECK(actual[i].tex[0] == 0.25f && actual[i].tex[1] == 0.75f);
        CHECK(actual[i].diffuse[0] == 0.5f && actual[i].diffuse[1] == 0.25f);
        CHECK(actual[i].diffuse[2] == 0.125f && actual[i].diffuse[3] == 1);
        ++vertex_checks;
    }
    ID3D11DeviceContext_Unmap(context, (ID3D11Resource *)staging, 0);
    ID3D11Buffer_Release(staging); ID3D11Buffer_Release(output); ID3D11Buffer_Release(vb);
    ID3D11GeometryShader_Release(gs);
}
static void raster_triangle(float r0, float r1, float r2)
{
    const char *pixel = "struct PS_IN { float4 pos:SV_POSITION; float4 diffuse:COLOR0; float4 specular:COLOR1; float2 tex0:TEXCOORD0; float2 tex1:TEXCOORD1; float2 tex2:TEXCOORD2; float2 tex3:TEXCOORD3; float fog:TEXCOORD4; }; float4 main(PS_IN i):SV_TARGET { return float4(i.tex0, i.pos.z, 1); }";
    ID3DBlob *code = compile(pixel, "main", "ps_4_0");
    ID3D11PixelShader *ps = NULL;
    HR(ID3D11Device_CreatePixelShader(device, ID3D10Blob_GetBufferPointer(code), ID3D10Blob_GetBufferSize(code), NULL, &ps));
    ID3D10Blob_Release(code);
    Vertex vertices[3] = {0};
    const float positions[3][4] = {{2,2,0.2f,r0},{30,2,0.8f,r1},{2,30,0.5f,r2}};
    for (unsigned i = 0; i < 3; ++i) {
        memcpy(vertices[i].pos, positions[i], sizeof(positions[i]));
        vertices[i].diffuse[0] = vertices[i].diffuse[1] = vertices[i].diffuse[2] = vertices[i].diffuse[3] = 1;
    }
    vertices[1].tex[0][0] = 1; vertices[2].tex[0][1] = 1;
    ID3D11Buffer *vb = buffer(sizeof(vertices), D3D11_BIND_VERTEX_BUFFER, vertices);
    D3D11_TEXTURE2D_DESC desc = {0};
    desc.Width = desc.Height = 32; desc.MipLevels = desc.ArraySize = 1;
    desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT; desc.SampleDesc.Count = 1;
    desc.Usage = D3D11_USAGE_DEFAULT; desc.BindFlags = D3D11_BIND_RENDER_TARGET;
    ID3D11Texture2D *target = NULL, *staging = NULL;
    HR(ID3D11Device_CreateTexture2D(device, &desc, NULL, &target));
    desc.Usage = D3D11_USAGE_STAGING; desc.BindFlags = 0; desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
    HR(ID3D11Device_CreateTexture2D(device, &desc, NULL, &staging));
    ID3D11RenderTargetView *view = NULL;
    HR(ID3D11Device_CreateRenderTargetView(device, (ID3D11Resource *)target, NULL, &view));
    D3D11_RASTERIZER_DESC raster = {0};
    raster.FillMode = D3D11_FILL_SOLID; raster.CullMode = D3D11_CULL_NONE; raster.DepthClipEnable = TRUE;
    ID3D11RasterizerState *state = NULL;
    HR(ID3D11Device_CreateRasterizerState(device, &raster, &state));
    const D3D11_VIEWPORT viewport = {0,0,32,32,0,1};
    const float clear[4] = {-1,-1,-1,-1};
    set_screen(32, 32); set_vertices(vb);
    ID3D11DeviceContext_RSSetState(context, state);
    ID3D11DeviceContext_RSSetViewports(context, 1, &viewport);
    ID3D11DeviceContext_OMSetRenderTargets(context, 1, &view, NULL);
    ID3D11DeviceContext_ClearRenderTargetView(context, view, clear);
    ID3D11DeviceContext_PSSetShader(context, ps, NULL, 0);
    ID3D11DeviceContext_IASetPrimitiveTopology(context, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    ID3D11DeviceContext_Draw(context, 3, 0);
    ID3D11DeviceContext_OMSetRenderTargets(context, 0, NULL, NULL);
    ID3D11DeviceContext_CopyResource(context, (ID3D11Resource *)staging, (ID3D11Resource *)target);
    D3D11_MAPPED_SUBRESOURCE mapped;
    HR(ID3D11DeviceContext_Map(context, (ID3D11Resource *)staging, 0, D3D11_MAP_READ, 0, &mapped));
    for (unsigned y = 0; y < 32; ++y) for (unsigned x = 0; x < 32; ++x) {
        const double b = ((double)x + 0.5 - 2) / 28;
        const double c = ((double)y + 0.5 - 2) / 28;
        const double a = 1 - b - c;
        if (a < 0.075 || b < 0.075 || c < 0.075) continue;
        const double den = a*r0 + b*r1 + c*r2;
        const double wanted[] = {b*r1/den, c*r2/den, a*0.2+b*0.8+c*0.5, 1};
        const float *p = (const float *)((const uint8_t *)mapped.pData + y*mapped.RowPitch) + x*4;
        for (unsigned k = 0; k < 4; ++k) if (fabs(p[k] - wanted[k]) > 0.00002) {
            fprintf(stderr, "Perspective pixel(%u,%u) channel%u RHW=(%g,%g,%g): got%.9g expected%.9g\n",
                x,y,k,r0,r1,r2,p[k],wanted[k]); exit(1);
        }
        ++pixel_checks;
    }
    ID3D11DeviceContext_Unmap(context, (ID3D11Resource *)staging, 0);
    ID3D11RasterizerState_Release(state); ID3D11RenderTargetView_Release(view);
    ID3D11Texture2D_Release(staging); ID3D11Texture2D_Release(target);
    ID3D11Buffer_Release(vb); ID3D11PixelShader_Release(ps);
}
int main(int argc, char **argv)
{
    init();
    if (!(argc == 2 && strcmp(argv[1], "--raster-only") == 0)) stream_output();
    raster_triangle(1, 1, 1); /* movie/UI interpolation unchanged */
    raster_triangle(1, 0.5f, 0.25f);
    raster_triangle(0.25f, 2, 0.5f);
    raster_triangle(4, 0.125f, 1);
    ID3D11DeviceContext_ClearState(context);
    ID3D11Buffer_Release(constants); ID3D11InputLayout_Release(layout);
    ID3D11VertexShader_Release(vs); ID3D11DeviceContext_Release(context); ID3D11Device_Release(device);
    printf("PASS: actual embedded VS compiled vs_4_0; WARP %u exact stream-output vertices, %u perspective/depth pixels; no window\n", vertex_checks, pixel_checks);
    return 0;
}
