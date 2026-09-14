/* Exact production functions, with only their existing native callees mocked.
 * The state/call oracle is derived from original XBE control flow. */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
static uint8_t ram[0x300000];
#define MEM32(a) (*(uint32_t *)(void *)(ram+(uint32_t)(a)))
#define MEMF(a) (*(float *)(void *)(ram+(uint32_t)(a)))
#define MEM8(a) ram[(uint32_t)(a)]
#define PUSH32(s,v) do{(s)-=4u;MEM32(s)=(uint32_t)(v);}while(0)
#define POP32(s,v) do{(v)=MEM32(s);(s)+=4u;}while(0)
#define LO8(a) ((uint8_t)(a))
#define HI8(a) ((uint8_t)((a)>>8))
#define SET_LO8(a,v) ((a)=((a)&0xFFFFFF00u)|(uint8_t)(v))
#define SET_LO16(a,v) ((a)=((a)&0xFFFF0000u)|(uint16_t)(v))
#define RECOMP_FCMP(a,b) (((a)!=(a)||(b)!=(b))?2:(a)<(b)?-1:(a)>(b)?1:0)
static uint32_t eax,ebx,ecx,edx,esi,edi,esp;
static double g_fp_stack[8];
static unsigned g_fp_top;
static int g_fp_cmp;
static unsigned cases,checks,call_count,expect_count,mode,swap_global;
static uint32_t lookup_result,integer_result;
typedef struct{uint32_t target,ret,self,a,b;}Call;
static Call calls[16],expected[16];
#define CHECK(c) do{++checks;if(!(c)){fprintf(stderr,"FAIL case%u line%u %s\n",cases,__LINE__,#c);exit(1);}}while(0)
static void native(uint32_t target,unsigned args,uint32_t result){Call *c;CHECK(call_count<16);c=&calls[call_count++];c->target=target;c->ret=MEM32(esp);c->self=ecx;c->a=args?MEM32(esp+4u):0;c->b=args>1?MEM32(esp+8u):0;esp+=4u+args*4u;eax=result;ecx=edx=0xDEADBEEFu;}
static void want(uint32_t target,uint32_t ret,uint32_t self,uint32_t a,uint32_t b){Call *c=&expected[expect_count++];c->target=target;c->ret=ret;c->self=self;c->a=a;c->b=b;}
static void sub_00139520(void){native(0x139520,1,0x4400);}
static void sub_000D54A0(void){CHECK(edx==0);native(0xD54A0,0,0x6B823AB1);}
static void sub_00089840(void){native(0x89840,0,0x4800);}
static void sub_0008AD60(void){native(0x8AD60,1,lookup_result);}
static void sub_00139120(void){native(0x139120,1,0xD3D3D3D3);}
static void sub_001390F0(void){native(0x1390F0,0,0xD3D3D3D3);}
static void sub_001394F0(void){native(0x1394F0,1,integer_result);if(swap_global)MEM32(0x250E60)=0x5000;}
static void sub_001391E0(void){native(0x1391E0,1,0xD3D3D3D3);}
static void sub_00139140(void){native(0x139140,1,0xD3D3D3D3);}
static void sub_00139160(void){native(0x139160,1,0xD3D3D3D3);}
static void sub_00139210(void){native(0x139210,2,0xD3D3D3D3);}
static void sub_00111650(void){native(0x111650,1,0x89ABCDEF);}
static void sub_0011C080(void){uint32_t self=ecx;CHECK(MEM32(esp+4)==0&&MEM32(self+0x10)==0);native(0x11C080,1,0xD3D3D3D3);MEM32(self+0x10)=2;MEM32(self+0x18)=0;ecx=self;}
static void virtual_call(uint32_t target,uint32_t before){CHECK(esp+8u==before);native(target,1,0xBADBEEF);}
#define RECOMP_ICALL_SAFE(target,before) virtual_call((target),(before))
#include "frontend_timer_fixture.inc"
static void reset(unsigned top){unsigned k;++cases;memset(ram,0xCD,0x10000);eax=edx=0xABCDEF01;ebx=0x13579BDF;esi=0x2468ACE0;edi=0xFDB97531;ecx=0x2000;esp=0x9000;MEM32(esp)=0x12345678;MEM32(esp+4)=0x3000;g_fp_top=top;g_fp_cmp=2;for(k=0;k<8;++k)g_fp_stack[k]=100.0+k;call_count=expect_count=0;MEM32(0x250E60)=0x4000;MEM32(0x4000)=0x6000;MEM32(0x5000)=0x6100;MEM32(0x6020)=0x1A1B1C1D;MEM32(0x6120)=0x2A2B2C2D;MEM32(0x286768)=0x5000;MEM32(0x8048)=0x7000;MEMF(0x225C20)=0.0f;}
static void finish(unsigned top,uint32_t expected_esp){unsigned k;CHECK(esp==expected_esp&&ebx==0x13579BDF&&esi==0x2468ACE0&&edi==0xFDB97531);CHECK(g_fp_top==top);CHECK(MEM32(0x9000)==0x12345678&&MEM32(0x9008)==0xCDCDCDCD);CHECK(call_count==expect_count);for(k=0;k<call_count;++k){if(memcmp(calls+k,expected+k,sizeof(Call))){fprintf(stderr,"call%u got %X/%X self%X %X,%X expected %X/%X self%X %X,%X\n",k,calls[k].target,calls[k].ret,calls[k].self,calls[k].a,calls[k].b,expected[k].target,expected[k].ret,expected[k].self,expected[k].a,expected[k].b);}CHECK(memcmp(calls+k,expected+k,sizeof(Call))==0);}}
static void timer_case(unsigned top,uint32_t event,uint32_t state,int32_t index,float delta,float total,float start,float duration,unsigned flag,unsigned opt){double sum=(double)delta+(double)total;float wanted_total=total;uint32_t wanted_state=state;int expired=event==0x6BFC080Fu&&state==1&&duration>0.0f&&sum>=(double)start+(double)duration;reset(top);MEM32(0x3004)=event;MEMF(0x3008)=delta;MEM32(0x2010)=state;MEM32(0x2014)=(uint32_t)index;MEMF(0x2018)=total;MEMF(0x201C)=start;MEMF(0x2020)=duration;MEM8(0x2024)=(uint8_t)flag;MEM32(0x2028)=0xABC04048;MEM32(0x202C)=0x89ABCDEF;MEM32(0x2030)=(opt&1)?0x12344321:0;MEM32(0x2034)=(opt&2)?0x77788899:0;
    if(event==0x6BFC080Fu)wanted_total=(float)sum;
    if(expired){wanted_state=flag?2:0;if(flag){wanted_total=0;want(0x11C080,0x11C1E8,0x2000,0,0);want(0x111650,0x11C1EE,0x2000,0x3000,0);}else want(0x111650,0x11C299,0x2000,0x3000,0);}
    else if(event==0x6BFC080Fu&&state==0&&index>=0){want(0x1391E0,0x11C21D,0x7000,(uint32_t)index,0);want(0x139140,0x11C228,0x7000,0xABC04048,0);want(0x139140,0x11C233,0x7000,0x89ABCDEF,0);want((opt&1)?0x139160:0x1390F0,(opt&1)?0x11C242:0x11C249,0x7000,(opt&1)?0x12344321:0,0);want((opt&2)?0x139160:0x1390F0,(opt&2)?0x11C258:0x11C276,0x7000,(opt&2)?0x77788899:0,0);want(0x139210,(opt&2)?0x11C263:0x11C281,0x7000,4,0);want(0x111650,(opt&2)?0x11C26C:0x11C28A,0x2000,0x3000,0);}
    else want(0x111650,0x11C299,0x2000,0x3000,0);
    sub_0011C180();finish(top,0x9008);CHECK(MEM32(0x2010)==wanted_state);CHECK((isnan(wanted_total)&&isnan(MEMF(0x2018)))||memcmp(&wanted_total,ram+0x2018,4)==0);CHECK(MEM8(0x2024)==flag);CHECK(MEM32(0x2024)==(0xCDCDCD00u|flag));CHECK(eax==0x89ABCDEF);
}
int main(void){unsigned i,j,k,n,top,flag;const float vals[]={0.0f,-0.0f,-1.0f,0.25f,1.0f,INFINITY,NAN};const uint32_t ints[]={0,1,0x80000000,0xFFFFFFFF,0x12345678};
    for(i=0;i<2;++i)for(top=0;top<8;++top){reset(top);lookup_result=i?0x4C00:0;MEM32(0x4C08)=0x76543210;want(0x139520,0x8BA9A,0x2000,1,0);want(0xD54A0,0x8BAA3,0x4400,0,0);want(0x89840,0x8BAA9,0xDEADBEEF,0,0);want(0x8AD60,0x8BAB0,0x4800,0x6B823AB1,0);want(i?0x139120:0x1390F0,i?0x8BABF:0x8BACB,0x2000,i?0x76543210:0,0);sub_0008BA90();finish(top,0x9004);CHECK(eax==1);}
    for(i=0;i<5;++i)for(j=0;j<2;++j)for(top=0;top<8;++top){reset(top);integer_result=ints[i];swap_global=j;want(0x1394F0,0xE3BEF,0x2000,1,0);want(0x1A1B1C1D,0xE3BF9,j?0x5000:0x4000,integer_result,0);sub_000E3BE0();finish(top,0x9004);CHECK(eax==0);}
    for(i=0;i<7;++i)for(j=0;j<7;++j)for(k=0;k<7;++k)for(n=0;n<7;++n)for(top=0;top<8;++top)for(flag=0;flag<2;++flag)timer_case(top,0x6BFC080F,1,0,vals[i],vals[j],vals[k],vals[n],flag,0);
    for(i=0;i<5;++i)for(j=0;j<5;++j)for(k=0;k<4;++k)for(top=0;top<8;++top){timer_case(top,0x6BFC080F,ints[i],(int32_t)ints[j],0.25f,1.0f,100.0f,1.0f,0xFF,k);timer_case(top,0x12345678,ints[i],(int32_t)ints[j],0.25f,1.0f,100.0f,1.0f,0xFF,k);}
    /* Float store rounds down to1, while the still-live x87 sum is >1. */
    for(top=0;top<8;++top)timer_case(top,0x6BFC080F,1,0,0x1p-25f,1.0f,0x1p-26f,1.0f,0,0);
    printf("PASS %u exact-production frontend native/timer cases, %u assertions\n",cases,checks);return 0;
}
