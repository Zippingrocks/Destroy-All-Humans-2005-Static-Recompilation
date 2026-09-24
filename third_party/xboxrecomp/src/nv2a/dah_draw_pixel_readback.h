#ifndef DAH_DRAW_PIXEL_READBACK_H
#define DAH_DRAW_PIXEL_READBACK_H
#include <stdint.h>

/* Observe the currently bound color RTV. No binds, clears, draws, or desktop
 * capture. At most four point copies and one synchronous map per invocation.
 * RGBA output uses canonical 0xRRGGBBAA regardless of the RT channel layout. */
static HRESULT dah_read_active_rt_pixels(ID3D11DeviceContext *ctx,
    const unsigned xy[][2],unsigned count,uint32_t *rgba)
{
    ID3D11RenderTargetView *rtv=NULL;
    ID3D11Resource *resource=NULL;
    ID3D11Texture2D *source=NULL,*staging=NULL;
    ID3D11Device *device=NULL;
    D3D11_TEXTURE2D_DESC desc;
    D3D11_RENDER_TARGET_VIEW_DESC view_desc;
    D3D11_MAPPED_SUBRESOURCE mapped;
    HRESULT hr=E_INVALIDARG;
    int bgra=0;
    if(!ctx || !xy || !rgba || !count || count>4u)return hr;
    ID3D11DeviceContext_OMGetRenderTargets(ctx,1,&rtv,NULL);
    if(!rtv)return E_FAIL;
    ID3D11RenderTargetView_GetDesc(rtv,&view_desc);
    if(view_desc.ViewDimension!=D3D11_RTV_DIMENSION_TEXTURE2D || view_desc.Texture2D.MipSlice!=0u){hr=E_NOTIMPL;goto cleanup;}
    ID3D11RenderTargetView_GetResource(rtv,&resource);
    hr=ID3D11Resource_QueryInterface(resource,&IID_ID3D11Texture2D,(void**)&source);
    if(FAILED(hr))goto cleanup;
    ID3D11Texture2D_GetDesc(source,&desc);
    if(desc.SampleDesc.Count!=1u || desc.ArraySize!=1u){hr=E_NOTIMPL;goto cleanup;}
    if(desc.Format==DXGI_FORMAT_B8G8R8A8_UNORM || desc.Format==DXGI_FORMAT_B8G8R8A8_UNORM_SRGB)bgra=1;
    else if(desc.Format!=DXGI_FORMAT_R8G8B8A8_UNORM && desc.Format!=DXGI_FORMAT_R8G8B8A8_UNORM_SRGB){hr=E_NOTIMPL;goto cleanup;}
    for(unsigned i=0;i<count;++i)if(xy[i][0]>=desc.Width || xy[i][1]>=desc.Height){hr=E_INVALIDARG;goto cleanup;}
    ID3D11DeviceContext_GetDevice(ctx,&device);
    desc.Width=count;desc.Height=1;desc.MipLevels=1;desc.ArraySize=1;
    desc.SampleDesc.Count=1;desc.SampleDesc.Quality=0;
    desc.Usage=D3D11_USAGE_STAGING;desc.BindFlags=0;desc.CPUAccessFlags=D3D11_CPU_ACCESS_READ;desc.MiscFlags=0;
    hr=ID3D11Device_CreateTexture2D(device,&desc,NULL,&staging);
    if(FAILED(hr))goto cleanup;
    for(unsigned i=0;i<count;++i){
        D3D11_BOX box={xy[i][0],xy[i][1],0,xy[i][0]+1u,xy[i][1]+1u,1};
        ID3D11DeviceContext_CopySubresourceRegion(ctx,(ID3D11Resource*)staging,0,i,0,0,(ID3D11Resource*)source,0,&box);
    }
    hr=ID3D11DeviceContext_Map(ctx,(ID3D11Resource*)staging,0,D3D11_MAP_READ,0,&mapped);
    if(SUCCEEDED(hr)){
        const unsigned char *bytes=(const unsigned char*)mapped.pData;
        for(unsigned i=0;i<count;++i){
            const unsigned char *p=bytes+i*4u;
            unsigned r=p[bgra?2:0],g=p[1],b=p[bgra?0:2],a=p[3];
            rgba[i]=(r<<24)|(g<<16)|(b<<8)|a;
        }
        ID3D11DeviceContext_Unmap(ctx,(ID3D11Resource*)staging,0);
    }
cleanup:
    if(staging)ID3D11Texture2D_Release(staging);
    if(device)ID3D11Device_Release(device);
    if(source)ID3D11Texture2D_Release(source);
    if(resource)ID3D11Resource_Release(resource);
    if(rtv)ID3D11RenderTargetView_Release(rtv);
    return hr;
}
#endif
