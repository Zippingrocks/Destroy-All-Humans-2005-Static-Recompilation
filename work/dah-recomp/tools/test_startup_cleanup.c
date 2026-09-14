/* Complete production wrappers, with external callees mocked to check ABI. */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
static uint8_t ram[0x300000];
static uint32_t eax, ebx, ecx, edx, esi, edi, esp;
static uint32_t clock_value, event_result;
static unsigned seen, query_count;
static int found;
static const uint32_t stack = 0x10000, object = 0x20000;
#define CHECK(x) do { if (!(x)) { fprintf(stderr,"line %d: %s\n",__LINE__,#x); exit(1); } } while (0)
static void *ptr(uint32_t a, size_t n) { CHECK(a <= sizeof(ram) && n <= sizeof(ram)-a); return ram+a; }
#define MEM32(a) (*(uint32_t*)ptr((uint32_t)(a),4))
#define MEM16(a) (*(uint16_t*)ptr((uint32_t)(a),2))
#define MEM8(a) (*(uint8_t*)ptr((uint32_t)(a),1))
#define PUSH32(s,v) do { uint32_t pv=(uint32_t)(v); (s)-=4; MEM32(s)=pv; } while(0)
#define POP32(s,v) do { (v)=MEM32(s); (s)+=4; } while(0)
#define TEST_Z(a,b) (((a)&(b))==0)
#define TEST_NZ(a,b) (((a)&(b))!=0)
#define CMP_EQ(a,b) ((a)==(b))
#define CMP_NE(a,b) ((a)!=(b))
#define CMP_B(a,b) ((uint32_t)(a)<(uint32_t)(b))
#define LO8(a) ((uint8_t)(a))
#define SET_LO8(a,v) ((a)=((a)&0xffffff00u)|(uint8_t)(v))
#define ZX16(a) ((uint32_t)(uint16_t)(a))
#define g_esp esp
static void sub_000D83E0(void) { CHECK(MEM32(esp)==0x6352d); eax=clock_value; ecx=0xdeadcafe; seen|=4096; esp+=4; }
static void sub_00063320(void) { CHECK(ecx==object&&MEM32(esp)==0x6353c); seen|=8192; esp+=4; }
static void sub_000FDFD0(void) { CHECK(ecx==object&&MEM32(esp)==0x63544&&MEM32(esp+4)==0x29000); seen|=16384; eax=event_result; esp+=8; }
static void sub_00068220(void) { CHECK(ecx==object); seen|=1; esp+=4; }
static void sub_0006B710(void) { CHECK(MEM32(esp+4)==object); seen|=2; esp+=4; }
static void sub_0018DE10(void) { CHECK(ecx==object); seen|=4; esp+=4; }
static void indirect(uint32_t target,uint32_t prior) {
    CHECK(target==0x12345678 && ecx==0x21000);
    CHECK(MEM32(esp+4)==object && MEM32(esp+8)==0xfedc && MEM32(esp+12)==6);
    esp+=16; CHECK(esp==prior); seen|=8;
}
#define RECOMP_ICALL_SAFE(t,s) indirect(t,s)
static void sub_000E3200(void) { CHECK(ecx==0x22000 && MEM32(esp+4)==0x76543210); seen|=16; esp+=8; }
static void sub_000CE640(void) { CHECK(ecx==0x23000 && MEM32(esp+4)==0x76543210); ++query_count; eax=found?27:UINT32_MAX; esp+=8; }
static void sub_000CE6C0(void) { CHECK(ecx==0x23000 && MEM32(esp+4)==27); seen|=32; esp+=8; }
static void sub_001F15EB(void) { CHECK(ecx==0x24000 && MEM32(esp+4)==object+3*32+0x88); seen|=64; esp+=8; }
static void sub_0020E840(void) { CHECK(MEM32(esp+4)==0x25000 && MEM32(esp+8)==object+0xfc); seen|=128; esp+=12; }
static void sub_001EDC45(void) { CHECK(MEM32(esp+4)==0x26000); seen|=256; esp+=8; }
static void sub_001EC9DC(void) { CHECK(MEM32(esp+4)==0x26000 && MEM32(object+0xa4)==1); seen|=512; esp+=8; }
static void sub_0017BD40(void) { CHECK(MEM32(esp+4)==0x27000 && MEM32(object+0x7c)==0); seen|=1024; esp+=8; }
static void sub_001EC9C1(void) { CHECK(MEM32(esp+4)==0x28000); seen|=2048; esp+=8; }
#pragma warning(push)
#pragma warning(disable:4101 4102 4189)
#include "startup_cleanup_fixture.inc"
#pragma warning(pop)
static void setup(void) {
    memset(ram,0,sizeof(ram)); esp=stack; MEM32(esp)=0xfeedface;
    MEM32(esp+20)=0xdeadbeef; esi=0xaabbccdd; ecx=object; seen=query_count=0;
}
static void done(unsigned bytes) { CHECK(esp==stack+bytes && esi==0xaabbccdd && MEM32(stack+20)==0xdeadbeef); }
int main(void) {
    unsigned cases=0;
    for(unsigned flag=0;flag<4;flag++) {
        setup(); MEM32(stack+4)=flag; sub_00068B50(); done(8);
        CHECK(eax==object && seen==(1u|((flag&1)?2u:0u))); ++cases;
        setup(); MEM32(stack+4)=flag; MEM16(object+4)=0xfedc;
        MEM32(0x270a80)=0x21000; MEM32(0x21000)=0x21800; MEM32(0x21814)=0x12345678;
        sub_00188750(); done(8); CHECK(eax==object && seen==(4u|((flag&1)?8u:0u))); ++cases;
    }
    for(found=0;found<=1;found++) {
        setup(); MEM32(object+4)=0x76543210; MEM32(0x250ec4)=0x22000; MEM32(0x2745b4)=0x23000;
        sub_000F7180(); done(4); CHECK(seen==(16u|(found?32u:0u)) && query_count==(found?2u:1u)); ++cases;
    }
    setup(); MEM32(stack+4)=3; MEM32(stack+8)=0x11223344; MEM32(stack+12)=0x89abcdef;
    MEM32(stack+16)=0xfedcba98; MEM32(object+8)=0x24000;
    sub_001F4ADB(); done(20); CHECK(seen==64 && MEM32(object+0xe8+0x18)==0x11223344 &&
        MEM32(object+0xe8+0x1c)==0x89abcdef && MEM32(object+0xe8+0x14)==0xfedcba98); ++cases;
    setup(); MEM32(stack+4)=object; MEM32(0x28eecc)=0x25000;
    sub_0020B060(); done(8); CHECK(seen==128); ++cases;
    for(unsigned open=0;open<2;open++) for(unsigned count=1;count<3;count++)
    for(unsigned enabled=0;enabled<2;enabled++) for(unsigned state=0;state<3;state++) {
        const uint32_t handle=state==0?0:(state==1?UINT32_MAX:0x28000);
        const int release=open && count==1 && enabled && state==2;
        setup(); MEM32(stack+4)=object; MEM32(object+0x7c)=open?0x26000:0;
        MEM32(object+0x80)=0x27000; MEM32(0x292914)=5; MEM32(0x29292c)=count;
        MEM32(0x292910)=enabled; MEM32(0x29290c)=handle;
        sub_0020E010(); done(8); CHECK(MEM32(object+0x7c)==0);
        CHECK(seen==(open?(256u|512u|1024u|(release?2048u:0u)):0u));
        CHECK(MEM32(object+0xa4)==open && MEM32(0x292914)==5-open && MEM32(0x29292c)==count-open);
        CHECK(MEM32(0x29290c)==(release?UINT32_MAX:handle)); ++cases;
    }
    {
        static const char *input[]={"", "1", "100", "1.0", "1.2300", "-0.000", "1.000e+12", "1.2500E-10", "1.0010", ".000", "12.", "nan", "1,2000"};
        static const char *output[]={"", "1", "100", "1", "1.23", "-0", "1e+12", "1.25E-10", "1.001", "", "12", "nan", "1,2"};
        for(unsigned i=0;i<sizeof(input)/sizeof(input[0]);i++) {
            setup(); ebx=0xabcdef90; MEM32(stack+4)=object; MEM8(0x259bf4)=i==12?',':'.';
            strcpy_s((char*)ram+object,128,input[i]); sub_0013C5A6(); done(4);
            CHECK(ebx==0xabcdef90 && strcmp((char*)ram+object,output[i])==0); ++cases;
        }
    }
    {
        static const uint32_t clocks[]={0,1,0x7fffffffu,0x80000000u,0xffffffffu};
        for(unsigned type=14;type<=16;type++) for(unsigned flag=0;flag<3;flag++)
        for(unsigned now=0;now<5;now++) for(unsigned deadline=0;deadline<5;deadline++)
        for(unsigned result=0;result<4;result++) {
            setup();edi=0x11223344;ebx=0x99887766;MEM32(stack+4)=0x29000;
            MEM32(0x29004)=type;MEM8(object+0x98)=(uint8_t)flag;MEM32(object+0x9c)=clocks[deadline];
            clock_value=clocks[now];event_result=result?0xabcdef00u+result:0;
            sub_00063510();done(8);
            CHECK(edi==0x11223344&&ebx==0x99887766&&eax==event_result);
            CHECK(seen==(16384u|((type==15&&flag)?4096u|((clocks[now]>=clocks[deadline])?8192u:0u):0u)));++cases;
        }
    }
    printf("PASS: %u startup cleanup/event cases, eight complete wrappers, guest ABI and branch effects\n",cases);
    return 0;
}
