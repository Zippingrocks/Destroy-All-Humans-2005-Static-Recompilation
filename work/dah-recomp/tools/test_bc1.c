#include <assert.h>
#include <stdio.h>
#include "../../../Repos/xboxrecomp-main/src/nv2a/dah_bc1.h"
int main(void)
{
    uint32_t w,h; size_t bytes; unsigned cases=0;
    uint8_t blocks[32]={0x00,0xf8,0x1f,0x00,0xe4,0xe4,0xe4,0xe4};
    uint8_t out[8*40];
    assert(dah_bc1_shape(0x11110c29,&w,&h,&bytes)&&w==2&&h==2&&bytes==8);
    for(unsigned u=0;u<16;++u)for(unsigned v=0;v<16;++v){
        int ok=dah_bc1_shape(0x00010c29u|u<<20|v<<24,&w,&h,&bytes);
        assert(ok==(u<=12&&v<=12)); if(ok)assert(bytes==(size_t)((w+3)/4)*((h+3)/4)*8);++cases;
    }
    assert(!dah_bc1_shape(0x11110c2d,&w,&h,&bytes));
    assert(!dah_bc1_shape(0x11111e29,&w,&h,&bytes));
    for(unsigned size=1;size<=4;++size){
        const uint32_t expected[4]={0xffff0000u,0xff0000ffu,0xffaa0055u,0xff5500aau};
        memset(out,0xcd,sizeof out);assert(dah_bc1_decode(blocks,8,size,size,out,40));
        for(unsigned y=0;y<size;++y)for(unsigned x=0;x<40;++x){
            if(x<size*4)assert(out[y*40+x]==((expected[x/4]>>(8*(x%4)))&255u));
            else assert(out[y*40+x]==0xcd);
        }++cases;
    }
    /* Four separate row-major blocks: red, green, blue, white. */
    {const uint16_t rgb[4]={0xf800,0x07e0,0x001f,0xffff};
     for(unsigned i=0;i<4;++i){memset(blocks+i*8,0,8);blocks[i*8]=(uint8_t)rgb[i];blocks[i*8+1]=(uint8_t)(rgb[i]>>8);}
     assert(dah_bc1_decode(blocks,32,8,8,out,40));
     for(unsigned y=0;y<8;++y)for(unsigned x=0;x<8;++x){uint32_t actual;memcpy(&actual,out+y*40+x*4,4);assert(actual==dah_bc1_endpoint(rgb[(y/4)*2+x/4]));}}
    memset(blocks,0,sizeof blocks);memset(blocks+4,255,4);
    assert(dah_bc1_decode(blocks,8,2,2,out,40));
    assert(out[0]==0&&out[3]==0&&out[43]==0); /* transparent BC1 selector */
    assert(!dah_bc1_decode(blocks,7,2,2,out,40));
    assert(!dah_bc1_decode(blocks,8,2,2,out,7));
    assert(!dah_bc1_decode(blocks,8,0,2,out,40));
    printf("PASS %u BC1 shape/size cases; endpoint/interpolation/alpha, row-major blocks, small assets, pitch and short-input guards\n",cases);
    return 0;
}
