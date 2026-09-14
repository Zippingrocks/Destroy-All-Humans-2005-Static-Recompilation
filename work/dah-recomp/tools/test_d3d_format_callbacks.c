/* Full production format encoder, against the original table data. */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
static uint8_t ram[0x200000];
static uint32_t eax, ecx, edx, esi, esp, g_ebp, g_seh_ebp;
#define g_eax eax
#define g_edx edx
#define g_esp esp
#define CHECK(x) do { if (!(x)) { fprintf(stderr,"line %d: %s\n",__LINE__,#x); exit(1); } } while (0)
static void *ptr(uint32_t a,size_t n) { CHECK(a<sizeof(ram)&&n<=sizeof(ram)-a); return ram+a; }
#define MEM8(a) (*(uint8_t*)ptr((uint32_t)(a),1))
#define MEM32(a) (*(uint32_t*)ptr((uint32_t)(a),4))
#define ZX8(x) ((uint32_t)(uint8_t)(x))
#define LO8(x) ((uint8_t)(x))
#define SET_LO8(x,v) ((x)=((x)&0xffffff00u)|(uint8_t)(v))
#define PUSH32(s,v) do { uint32_t pv=(uint32_t)(v); (s)-=4; MEM32(s)=pv; } while(0)
#define POP32(s,v) do { (v)=MEM32(s); (s)+=4; } while(0)
#define TEST_Z(a,b) (((a)&(b))==0)
#define CMP_A(a,b) ((uint32_t)(a)>(uint32_t)(b))
static void dispatch(uint32_t);
#define RECOMP_ITAIL(t) dispatch(t)
#pragma warning(push)
#pragma warning(disable:4101 4102 4189)
#include "d3d_format_fixture.inc"
#pragma warning(pop)
static void dispatch(uint32_t t) {
    switch(t) {
#define D(t) case 0x##t: sub_##t(); break
    D(001E0436); D(001E045D); D(001E0489); D(001E0490);
    D(001E0497); D(001E049E); D(001E04A5); D(001E04AC);
    D(001E04B3); D(001E04BA); D(001E04C1); D(001E04D5);
#undef D
    default: CHECK(0);
    }
}
int main(void) {
    FILE *f=NULL; CHECK(fopen_s(&f,"tables.bin","rb")==0);
    CHECK(fread(ram+0x1e04dc,1,0x100,f)==0x100);
    CHECK(fread(ram+0x1e64b0,1,256,f)==256); fclose(f);
    unsigned cases=0;
    for(unsigned fmt=0;fmt<31;fmt++) for(unsigned dims=0;dims<16;dims++)
    for(unsigned depth=0;depth<=256;depth++) {
        uint32_t target=MEM32(0x1e04dc+4*MEM8(0x1e0505+fmt));
        uint32_t word=(dims<<20)|((15-dims)<<24)|(fmt<<8);
        uint32_t expected=0,linear=0;
        switch(target) {
        case 0: break; /* Existing unsupported-format guard. */
        case 0x1e0436: expected=8; break;
        case 0x1e0489: expected=4; break;
        case 0x1e0497: expected=3; break;
        case 0x1e04a5: expected=1; break;
        case 0x1e045d: expected=8; linear=1; break;
        case 0x1e0490: expected=4; linear=1; break;
        case 0x1e049e: expected=3; linear=1; break;
        case 0x1e04ac: expected=1; linear=1; break;
        case 0x1e04b3: expected=9; linear=1; break;
        case 0x1e04ba: expected=10; linear=1; break;
        default: CHECK(0);
        }
        if(target) {
            expected|=linear?0x100:(((word&0xf00000)|0x2000)>>4)|(word&0xf000000);
            if(depth==256) expected|=(MEM8(0x1e64b0+fmt)&0x3c)==0x20?0x20:0x10;
            else if(depth>=0x2a&&depth<=0x31) {
                uint32_t tail=MEM32(0x1e0524+4*MEM8(0x1e052c+depth-0x2a));
                CHECK(tail==0x1e04c1||tail==0x1e04d5);
                expected|=tail==0x1e04c1?0x20:0x10;
            }
        }
        esp=0x10000; eax=0xfeedfeed; esi=0x789abcde; g_ebp=g_seh_ebp=0xabcd;
        MEM32(esp)=0xabcdef12; MEM32(esp+4)=0x20000; MEM32(esp+8)=depth==256?0:0x21000;
        MEM32(esp+12)=0xdeadbeef; MEM32(0x2000c)=word; MEM8(0x2100d)=(uint8_t)depth;
        sub_001E0420();
        CHECK(esp==0x1000c&&eax==expected&&esi==0x789abcde&&MEM32(0x1000c)==0xdeadbeef);
        CHECK(g_ebp==0xabcd&&g_seh_ebp==0xabcd); ++cases;
    }
    printf("PASS: %u complete format encoder cases, original two-table dispatch, all dimensions/depth formats and guest ABI\n",cases);
    return 0;
}
