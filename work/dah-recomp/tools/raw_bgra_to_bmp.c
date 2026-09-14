#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#pragma pack(push,1)
typedef struct BmpHeader {
    uint16_t type; uint32_t size; uint16_t r1,r2; uint32_t off;
    uint32_t info; int32_t width,height; uint16_t planes,bits;
    uint32_t compression,image_size; int32_t xppm,yppm;
    uint32_t used,important;
} BmpHeader;
#pragma pack(pop)

int main(int argc,char **argv)
{
    const uint32_t width=640,height=448,pitch=2560;
    uint8_t *row;
    FILE *in,*out;
    BmpHeader h={0};
    if(argc!=3) return 2;
    in=fopen(argv[1],"rb"); out=fopen(argv[2],"wb");
    if(!in||!out) return 3;
    row=(uint8_t*)malloc(pitch); if(!row) return 4;
    h.type=0x4D42; h.off=sizeof h; h.info=40; h.width=(int32_t)width;
    h.height=-(int32_t)height; h.planes=1; h.bits=32;
    h.image_size=pitch*height; h.size=h.off+h.image_size;
    if(fwrite(&h,1,sizeof h,out)!=sizeof h) return 5;
    for(uint32_t y=0;y<height;++y) {
        if(fread(row,1,pitch,in)!=pitch||fwrite(row,1,pitch,out)!=pitch) return 6;
    }
    free(row); fclose(in); fclose(out); return 0;
}
