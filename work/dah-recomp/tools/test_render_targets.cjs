const fs=require('fs'),path=require('path'),os=require('os'),{spawnSync}=require('child_process');
const root=path.resolve(__dirname,'../../..');
const s=fs.readFileSync(root+'/Repos/xboxrecomp-main/src/d3d/d3d8_device.c','utf8');
const globals=s.slice(s.indexOf('#define PGRAPH_RT_COUNT'),s.indexOf('/* Forward declarations */'));
const body=s.slice(s.indexOf('static PgraphRenderTarget *pgraph_find_rt'),s.indexOf('static void pgraph_copy_presentable_to_swapchain',s.indexOf('HRESULT d3d8_PgraphBindRenderTargetTexture')));
const pre=`#define COBJMACROS\n#include <windows.h>\n#include <d3d11.h>\n#include <stdio.h>\n#include <string.h>\nstruct {ID3D11Device *d3d11_device;ID3D11DeviceContext *d3d11_context;ID3D11DepthStencilView *default_dsv;UINT width,height;} g_device_state;\n`;
const main=`
#define CHECK(x) do {if(!(x)){fprintf(stderr,"FAIL line %d: %s\\n",__LINE__,#x);return 1;}}while(0)
int main(void){D3D_FEATURE_LEVEL level;CHECK(SUCCEEDED(D3D11CreateDevice(NULL,D3D_DRIVER_TYPE_WARP,NULL,0,NULL,0,D3D11_SDK_VERSION,&g_device_state.d3d11_device,&level,&g_device_state.d3d11_context)));g_device_state.width=640;g_device_state.height=480;
for(unsigned i=0;i<12;++i){UINT w=i%2?32:64,h=i%2?16:32;CHECK(SUCCEEDED(d3d8_PgraphBindRenderTarget(0x1000,FALSE,w,h)));CHECK(g_current_pgraph_rt&&g_current_pgraph_rt->texture&&g_current_rtv);D3D11_TEXTURE2D_DESC desc;ID3D11Texture2D_GetDesc(g_current_pgraph_rt->texture,&desc);CHECK(desc.Width==w&&desc.Height==h);CHECK(g_current_pgraph_rt->srv!=NULL);}
CHECK(SUCCEEDED(d3d8_PgraphBindRenderTarget(0x2000,FALSE,1,1)));CHECK(g_current_pgraph_rt->width==1&&g_current_pgraph_rt->height==1);
CHECK(FAILED(d3d8_PgraphBindRenderTargetTexture(0,0x2000)));
CHECK(FAILED(d3d8_PgraphBindRenderTargetTexture(0,0xdead)));
CHECK(SUCCEEDED(d3d8_PgraphBindRenderTargetTexture(0,0x1000)));
ID3D11ShaderResourceView *bound=NULL;ID3D11DeviceContext_PSGetShaderResources(g_device_state.d3d11_context,0,1,&bound);CHECK(bound==pgraph_find_rt(0x1000)->srv);ID3D11ShaderResourceView_Release(bound);
CHECK(SUCCEEDED(d3d8_PgraphBindRenderTarget(0x3000,TRUE,1,1)));CHECK(g_current_pgraph_rt->width==640&&g_current_pgraph_rt->height==480&&g_current_pgraph_presentable);
bound=NULL;ID3D11DeviceContext_PSGetShaderResources(g_device_state.d3d11_context,0,1,&bound);CHECK(bound==NULL);
CHECK(SUCCEEDED(d3d8_PgraphBindDepthSurface(0x8000,2)));ID3D11DepthStencilView *saved_depth=g_current_dsv;CHECK(saved_depth);
CHECK(SUCCEEDED(d3d8_PgraphBindRenderTarget(0x4000,FALSE,640,480)));CHECK(SUCCEEDED(d3d8_PgraphBindDepthSurface(0x8000,2)));CHECK(saved_depth==g_current_dsv);
ID3D11DepthStencilView *bound_depth=NULL;ID3D11DeviceContext_OMGetRenderTargets(g_device_state.d3d11_context,0,NULL,&bound_depth);CHECK(bound_depth==saved_depth);ID3D11DepthStencilView_Release(bound_depth);
CHECK(SUCCEEDED(d3d8_PgraphBindDepthSurface(0x9000,2)));CHECK(g_current_dsv&&g_current_dsv!=saved_depth);
CHECK(SUCCEEDED(d3d8_PgraphBindDepthSurface(0,2)));CHECK(!g_current_dsv);
CHECK(SUCCEEDED(d3d8_PgraphBindDepthSurface(0xa000,1)));CHECK(g_current_dsv);
printf("PASS: sampling binding and feedback guards, 12 real WARP target resizes, 1x1 offscreen target, 640x480 presentable target\\n");return 0;}
`;
const dir=fs.mkdtempSync(path.join(os.tmpdir(),'dah-rt-test-'));
for(const negative of [false,true]) {fs.writeFileSync(dir+'/test.c',pre+globals+(negative?body.replace('rt = NULL; /* Recreate the resized resource below. */','/* negative control: missing recreation */'):body)+main);let r=spawnSync('cl.exe',['/nologo','/O2','/std:c11','test.c','d3d11.lib','dxgi.lib','/Fe:test.exe'],{cwd:dir,encoding:'utf8',timeout:120000});if(r.status!==0)throw Error(r.stdout+r.stderr);r=spawnSync(dir+'/test.exe',[],{encoding:'utf8',timeout:30000});console.log(negative?'Negative control:':'Production:',r.stdout,r.stderr);if(r.status!==(negative?1:0))process.exit(1);}

