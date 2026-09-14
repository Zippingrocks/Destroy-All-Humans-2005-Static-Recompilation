#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4101 4102 4189)
static uint8_t ram[0x300000],input[4096],output[4096];
static uint32_t eax,ebx,ecx,edx,esi,edi,esp;
#define MEM8(a) ram[(uint32_t)(a)]
#define MEM16(a) (*(uint16_t *)(void *)(ram+(uint32_t)(a)))
#define MEM32(a) (*(uint32_t *)(void *)(ram+(uint32_t)(a)))
#define LO8(a) ((uint8_t)(a))
#define ZX16(a) ((uint32_t)(uint16_t)(a))
#define CMP_A(a,b) ((uint32_t)(a)>(uint32_t)(b))
#define PUSH32(s,v) do{(s)-=4u;MEM32(s)=(uint32_t)(v);}while(0)
#define POP32(s,v) do{(v)=MEM32(s);(s)+=4u;}while(0)
static unsigned cases,checks,length,produced,flushes,finals,initialized;
static uint32_t buffer,input_mode,mutate_mode,expected_mode,submit_ret;
#define CHECK(c) do{++checks;if(!(c)){fprintf(stderr,"FAIL case%u line%u %s\n",cases,__LINE__,#c);exit(1);}}while(0)
#include "lower_original_table.inc"
static void sub_00191960(void){CHECK(MEM32(esp)==0x1933E9&&ecx==0x2000&&edx==1);CHECK(MEM32(esp+4)==0x8DF0);MEM32(MEM32(esp+4))=length;eax=0x3000;ecx=edx=0xBADDEAD;esp+=8;}
static void sub_001917E0(void){CHECK(MEM32(esp)==0x1933F6&&ecx==0x2000&&edx==0x8DF4);buffer=edx;MEM32(buffer)=buffer+12;MEM32(buffer+4)=0;MEM32(buffer+8)=ecx;eax=buffer+12;ecx=edx=0xBADDEAD;initialized=1;esp+=4;}
static void collect(void){uint32_t count=MEM32(buffer)-buffer-12;CHECK(count<=512&&produced+count<=sizeof output);memcpy(output+produced,ram+buffer+12,count);produced+=count;MEM32(buffer)=buffer+12;}
static void sub_00191620(void){CHECK(initialized&&ecx==buffer&&MEM32(esp)==0x193418);CHECK(MEM32(buffer)==buffer+12+512);collect();++flushes;eax=buffer+12;ecx=edx=0xBADDEAD;esp+=4;}
static void sub_001916D0(void){CHECK(initialized&&ecx==buffer&&MEM32(esp)==0x193446);collect();++finals;eax=ecx=edx=0xBADDEAD;esp+=4;}
static void sub_001DA870(void){CHECK(MEM32(esp)==0xE0522&&ecx==0x2000&&MEM32(0x227C)==input_mode);MEM32(0x227C)=mutate_mode;eax=ecx=edx=0xBADDEAD;esp+=4;}
static void sub_001DAB20(void){CHECK(MEM32(esp)==submit_ret&&MEM32(esp+4)==0x2298);CHECK(MEM32(0x22C8)==expected_mode);CHECK(eax==(mutate_mode>2?mutate_mode-2:0));eax=0xCAFEBABE;ecx=edx=0xBADDEAD;esp+=8;}
#include "frontend_lower_fixture.inc"
static void reset(void){++cases;memset(ram,0xCD,0x10000);memset(output,0xBB,sizeof output);memcpy(ram+0x238B06,original_ctype,sizeof original_ctype);MEM32(0x259BE8)=0x238B08;MEM32(0x259BF0)=1;eax=edx=0x12345678;ecx=0x2000;ebx=0x13579BDF;esi=0x2468ACE0;edi=0xFDB97531;esp=0x9000;MEM32(esp)=0x12345678;produced=flushes=finals=initialized=0;}
static void saved(uint32_t result_esp){CHECK(esp==result_esp&&ebx==0x13579BDF&&esi==0x2468ACE0&&edi==0xFDB97531);CHECK(MEM32(0x9000)==0x12345678&&MEM32(0x9008)==0xCDCDCDCD);}
static uint8_t lower(uint8_t ch){return ch>='A'&&ch<='Z'?(uint8_t)(ch+('a'-'A')):ch;}
int main(void){unsigned n,i,mode;const unsigned lengths[]={0,1,2,255,256,511,512,513,514,1023,1024,1025,1537,4096};const uint32_t locales[]={0,1,2,0xFFFFFFFF,0x80000000,0x7FFFFFFF};const uint32_t states[]={0,1,2,3,0xFFFFFFFF,0x80000000,0x7FFFFFFF};
    for(mode=0;mode<6;++mode)for(i=0;i<257;++i){uint32_t ch=i==256?0xFFFFFFFFu:i;uint32_t want=i==256?ch:lower((uint8_t)ch);reset();MEM32(0x259BF0)=locales[mode];MEM32(esp+4)=ch;sub_0013E6CF();saved(0x9004);CHECK(eax==want);CHECK(MEM32(0x9004)==ch);}
    /* Exercise every classification-bit combination, not just English text. */
    for(mode=0;mode<2;++mode)for(i=0;i<256;++i){reset();MEM32(0x259BF0)=mode?2:1;MEM16(0x238B08+2*0x90)=(uint16_t)i;MEM32(esp+4)=0x90;sub_0013E6CF();saved(0x9004);CHECK(eax==((i&1)?0xB0u:0x90u));}
    for(mode=0;mode<2;++mode)for(n=0;n<sizeof(lengths)/sizeof(lengths[0]);++n)for(unsigned shift=0;shift<8;++shift){reset();length=lengths[n];MEM32(0x259BF0)=mode?2:1;for(i=0;i<length;++i)input[i]=(uint8_t)(i*73u+shift*31u);memcpy(ram+0x3000,input,length);sub_001933D0();saved(0x9004);CHECK(eax==1&&produced==length&&finals==1);CHECK(flushes==(length?((length-1u)/512u):0));for(i=0;i<length;++i)CHECK(output[i]==lower(input[i]));CHECK(memcmp(input,ram+0x3000,length)==0);CHECK(MEM32(0x8DC0)==0xCDCDCDCD);}
    for(mode=0;mode<7;++mode)for(n=0;n<7;++n){reset();input_mode=states[mode];mutate_mode=states[n];MEM32(esp+4)=input_mode;expected_mode=mutate_mode==0?0x80000001u:mutate_mode==1?1u:mutate_mode==2?2u:0xCDCDCDCD;submit_ret=mutate_mode==1?0xE0563:mutate_mode==2?0xE0549:0xE057D;sub_000E0510();saved(0x9008);CHECK(eax==0xCAFEBABE&&MEM32(0x227C)==mutate_mode);}
    printf("PASS %u actual-body lowercase/render-mode cases, %u assertions; empty/embedded-NUL/512-byte flushes and all-byte CRT table paths\n",cases,checks);return 0;
}
