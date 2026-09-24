/* NV2A format 0x0c: linear rows of BC1 blocks, not Morton tiles.
 * BASE_SIZE_U/V are log2 texel dimensions; IMAGE_RECT is for linear
 * uncompressed textures. Decode small (1/2 texel) assets too, without
 * imposing the host BC resource's block-aligned size restrictions. */
#ifndef DAH_BC1_H
#define DAH_BC1_H
#include <stdint.h>
#include <stddef.h>
#include <string.h>
static int dah_bc1_shape(uint32_t format, uint32_t *w, uint32_t *h, size_t *bytes)
{
    unsigned u=(format>>20)&15u, v=(format>>24)&15u;
    if (((format>>8)&255u)!=12u || ((format>>4)&15u)!=2u ||
        (format&4u) || u>12u || v>12u) return 0;
    *w=1u<<u; *h=1u<<v;
    *bytes=(size_t)((*w+3u)/4u)*((*h+3u)/4u)*8u;
    return 1;
}
static uint32_t dah_bc1_endpoint(uint16_t c)
{
    unsigned r=(c>>11)&31u, g=(c>>5)&63u, b=c&31u;
    return 0xff000000u | ((r<<3|r>>2)<<16) | ((g<<2|g>>4)<<8) | (b<<3|b>>2);
}
static uint32_t dah_bc1_mix(uint32_t a,uint32_t b,unsigned wa,unsigned wb,unsigned divisor)
{
    uint32_t out=0xff000000u;
    for(unsigned shift=0;shift<24;shift+=8)
        out|=((((a>>shift)&255u)*wa+((b>>shift)&255u)*wb)/divisor)<<shift;
    return out;
}
static int dah_bc1_decode(const uint8_t *src,size_t length,uint32_t w,uint32_t h,
                         uint8_t *dst,size_t pitch)
{
    size_t bw=(w+3u)/4u,bh=(h+3u)/4u;
    if(!src||!dst||!w||!h||w>4096||h>4096||pitch<(size_t)w*4u||length<bw*bh*8u)return 0;
    for(size_t y=0;y<bh;++y)for(size_t x=0;x<bw;++x){
        const uint8_t *p=src+(y*bw+x)*8u;
        uint16_t a=(uint16_t)(p[0]|p[1]<<8), b=(uint16_t)(p[2]|p[3]<<8);
        uint32_t indices=(uint32_t)p[4]|(uint32_t)p[5]<<8|(uint32_t)p[6]<<16|(uint32_t)p[7]<<24;
        uint32_t colors[4]={dah_bc1_endpoint(a),dah_bc1_endpoint(b),0,0};
        colors[2]=dah_bc1_mix(colors[0],colors[1],a>b?2u:1u,1u,a>b?3u:2u);
        if(a>b)colors[3]=dah_bc1_mix(colors[0],colors[1],1u,2u,3u);
        for(unsigned row=0;row<4;++row)for(unsigned col=0;col<4;++col){
            size_t px=x*4u+col,py=y*4u+row;
            if(px<w&&py<h){uint32_t color=colors[(indices>>(2u*(row*4u+col)))&3u];
                memcpy(dst+py*pitch+px*4u,&color,4);}
        }
    }
    return 1;
}
#endif
