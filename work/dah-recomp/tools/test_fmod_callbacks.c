#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
static uint8_t memory[4096];
static uint32_t eax, esp, g_ebp;
static double g_fp_stack[8];
static int g_fp_top;
#define MEM8(a) memory[(a)]
#define MEM16(a) (*(uint16_t *)&memory[(a)])
#define MEM32(a) (*(uint32_t *)&memory[(a)])
#define SET_LO16(r,v) ((r)=((r)&0xFFFF0000u)|((uint32_t)(v)&0xFFFFu))
#include "fmod_fixture.inc"
void dah_test_fprem(const uint64_t *,const uint64_t *,uint64_t *,uint16_t *);
void dah_test_faddp(const uint64_t *,const uint64_t *,uint64_t *,uint16_t *);
void dah_test_faddp80(const uint8_t *,const uint8_t *,uint64_t *,uint16_t *);
static unsigned cases, assertions;
static void check(int good,const char *why){++assertions;if(!good){fprintf(stderr,"FAIL case%u %s\n",cases,why);exit(1);}}
static void initialize(unsigned top,uint64_t a,uint64_t b){unsigned i;++cases;memset(memory,0xA5,sizeof memory);for(i=0;i<8;++i)g_fp_stack[i]=(double)(i+100);g_fp_top=(int)top;g_fp_stack[top]=dah_fmod_value(a);g_fp_stack[(top+1u)&7u]=dah_fmod_value(b);g_ebp=2048;esp=1000;eax=0xACEDCAFEu;}
static void abi(unsigned top,uint64_t result){check(g_fp_top==(int)((top+1u)&7u),"x87 stack consumption");check(dah_fmod_bits(g_fp_stack[g_fp_top])==result,"result bits");check(esp==1004,"RET stack consumption");check((eax&0xFFFF0000u)==0xACED0000u,"upper EAX preserved");check(memory[g_ebp-0x9Fu]==0xA5&&memory[g_ebp-0x94u]==0xA5,"scratch bounds");}
static uint64_t rng=0x8B13044BC426077DULL;
static uint64_t random_bits(void){rng^=rng<<13;rng^=rng>>7;rng^=rng<<17;return rng;}
int main(void){
    unsigned i,j,top;
    const uint64_t values[]={0x0000000000000001ULL,0x000FFFFFFFFFFFFFULL,0x0010000000000000ULL,0x3FE0000000000000ULL,0x3FF0000000000000ULL,0x4000000000000000ULL,0x4014000000000000ULL,0x4026000000000000ULL,0x7FEFFFFFFFFFFFFFULL};
    const uint64_t nans[]={0x7FF8000000000001ULL,0xFFF8000000000001ULL,0x7FF9000000000000ULL,0xFFFA000000000004ULL};
    const uint64_t raw_nans[]={0x7FF8000000000001ULL,0xFFF8000000000001ULL,0x7FF8000000000002ULL,0xFFF8000000000002ULL,0x7FF0000000000001ULL,0xFFF0000000000001ULL,0x7FF0000000000002ULL,0xFFF0000000000002ULL};
    for(i=0;i<1500;++i)for(top=0;top<8;++top){uint64_t a,b,out;uint16_t status;unsigned signs;
        if(i<81){a=values[i/9];b=values[i%9];}else{a=random_bits()&0x7FEFFFFFFFFFFFFFULL;b=random_bits()&0x7FEFFFFFFFFFFFFFULL;if(!a)a=1;if(!b)b=1;}
        signs=top&3u;a|=(uint64_t)(signs&1u)<<63;b|=(uint64_t)(signs>>1)<<63;
        dah_test_fprem(&a,&b,&out,&status);initialize(top,b,a);sub_0013B5A0();abi(top,out);
        if((eax&0x4700u)!=(status&0x4700u)){fprintf(stderr,"x=%016llX y=%016llX emu=%04X native=%04X\n",(unsigned long long)a,(unsigned long long)b,(unsigned)(eax&0xFFFFu),status);}
        check((eax&0x4700u)==(status&0x4700u),"FPREM quotient/status conditions");check((eax&0x3800u)==(top<<11),"FNSTSW pre-pop TOP");
    }
    for(top=0;top<8;++top){initialize(top,0xBFF0000000000000ULL,0x8000000000000000ULL);sub_0013F420();abi(top,0);check(eax==0xACEDCAFEu,"zero EAX preserved");}
    for(i=0;i<256;++i)for(top=0;top<8;++top){initialize(top,0,0);MEM8(g_ebp-0x90u)=(uint8_t)i;sub_0013F4C2();abi(top,0xFFF8000000000000ULL);check(MEM8(g_ebp-0x90u)==((int8_t)i>0?i:1),"signed error-byte branch");}
    for(i=0;i<4;++i)for(j=0;j<4;++j)for(top=0;top<8;++top){uint64_t a=nans[i],b=nans[j],out;uint16_t status;dah_test_faddp(&a,&b,&out,&status);initialize(top,a,b);sub_0013F483();abi(top,out);check(MEM8(g_ebp-0x90u)==7,"both quiet NaN error");check(MEM32(g_ebp-0x9Eu)==(uint32_t)(b<<11),"last scratch mantissa low");check(MEM16(g_ebp-0x96u)==(uint16_t)((b>>48)|0x7FFFu),"scratch sign/exponent");}
    for(i=0;i<4;++i)for(top=0;top<8;++top){uint64_t a=nans[i],b=0x4000000000000000ULL,out;uint16_t status;dah_test_faddp(&a,&b,&out,&status);initialize(top,a,b);sub_0013F45B();abi(top,out);check(MEM8(g_ebp-0x90u)==7,"single qNaN code");initialize(top,b,a);sub_0013F459();abi(top,out);}
    /* Quiet/signaling test arms preserve the source quiet-bit decision before
       arithmetic. Direct sNaNs are not loaded through host FLD binary64 here. */
    for(top=0;top<8;++top){initialize(top,0x7FF0000000000001ULL,0x3FF0000000000000ULL);sub_0013F45B();abi(top,0x7FF8000000000001ULL);check(MEM8(g_ebp-0x90u)==1,"signaling code");check(!(MEM8(g_ebp-0x97u)&0x40u),"scratch preserves signaling bit");}
    for(i=0;i<8;++i)for(j=0;j<8;++j)for(top=0;top<8;++top){
        uint64_t a=raw_nans[i],b=raw_nans[j],out;
        uint64_t am=UINT64_C(0x8000000000000000)|((a&UINT64_C(0x000FFFFFFFFFFFFF))<<11),bm=UINT64_C(0x8000000000000000)|((b&UINT64_C(0x000FFFFFFFFFFFFF))<<11);
        uint16_t ae=(uint16_t)(0x7FFFu|((a>>48)&0x8000u)),be=(uint16_t)(0x7FFFu|((b>>48)&0x8000u)),status;
        uint8_t a80[10],b80[10];int aq=(a&UINT64_C(0x0008000000000000))!=0,bq=(b&UINT64_C(0x0008000000000000))!=0;
        memcpy(a80,&am,8);memcpy(a80+8,&ae,2);memcpy(b80,&bm,8);memcpy(b80+8,&be,2);
        dah_test_faddp80(a80,b80,&out,&status);
        initialize(top,a,b);sub_0013F483();abi(top,out);check(MEM8(g_ebp-0x90u)==(aq&&bq?7u:1u),"raw80 signaling error branch");
        check(memcmp(memory+g_ebp-0x9Eu,aq?b80:a80,10)==0,"exact raw80 scratch store and branch order");
    }
    printf("PASS %u production fmod cases, %u assertions; native x87 result/status oracle\n",cases,assertions);return 0;
}
