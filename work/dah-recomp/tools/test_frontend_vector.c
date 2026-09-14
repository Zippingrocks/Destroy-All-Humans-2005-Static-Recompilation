/* Isolated actual 104480 body; expected argument addresses calculated from
 * retail stack offsets at 1044D1/E1/ED/F2, independent of lifted code. */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
static uint32_t ram[0x10000/4];
static uint32_t eax,ebx,ecx,edx,esi,edi,esp,g_ebp;
static unsigned queries,values,vectors,dispatches,forwards,cases;
static uint32_t first,last,index,hash;
static const uint32_t stack=0x9000,object=0x2000,backend=0x3000;
#define CHECK(x) do {if(!(x)){fprintf(stderr,"case%u line%d %s\n",cases,__LINE__,#x);exit(1);}}while(0)
#define MEM32(a) (*(uint32_t*)((uint8_t*)ram+(a)))
#define PUSH32(s,v) do {uint32_t pv=(v);(s)-=4;MEM32(s)=pv;}while(0)
#define POP32(s,v) do {(v)=MEM32(s);(s)+=4;}while(0)
static void sub_000F99F0(void) {
    CHECK(ecx==object && MEM32(esp)==0x10449e && MEM32(esp+4)==hash && MEM32(esp+8)==index);
    ++forwards; eax=0xbaadf00d; ecx=edx=0xdeadbeef; esp+=12;
}
static void sub_000FBCB0(void) {
    CHECK(queries<2 && MEM32(esp+4)==index+queries);
    CHECK(MEM32(esp)==(queries?0x1044c4u:0x1044b2u));
    ++queries; eax=0x6100; ecx=edx=0xdeadbeef; esp+=8;
}
static void sub_001394F0(void) {
    CHECK(ecx==0x6100 && queries==values+1);
    CHECK(MEM32(esp)==(values?0x1044cbu:0x1044b9u));
    eax=values?last:first; ++values; ecx=edx=0xdeadbeef; esp+=4;
}
static void sub_000F8800(void) {
    const uint32_t destination=vectors?stack-0x20u:stack-0x10u;
    CHECK(vectors<2 && ecx==object && MEM32(esp+4)==destination);
    CHECK(MEM32(esp+8)==index+(vectors?6u:2u));
    CHECK(MEM32(esp)==(vectors?0x1044edu:0x1044ddu));
    for(unsigned n=0;n<4;n++) MEM32(destination+n*4)=0x76540000u+vectors*16+n;
    ++vectors; eax=ecx=edx=0xdeadbeef; esp+=12;
}
static void sub_001A3400(void) {
    CHECK(ecx==backend && MEM32(esp)==0x104504);
    CHECK(MEM32(esp+4)==first && MEM32(esp+8)==last);
    CHECK(MEM32(esp+12)==stack-0x10 && MEM32(esp+16)==stack-0x20);
    for(unsigned n=0;n<4;n++) {
        CHECK(MEM32(MEM32(esp+12)+n*4)==0x76540000u+n);
        CHECK(MEM32(MEM32(esp+16)+n*4)==0x76540010u+n);
    }
    ++dispatches; eax=ecx=edx=0xdeadbeef; esp+=20;
}
#include "frontend_vector_fixture.inc"
int main(void) {
    for(unsigned n=0;n<256;n++) for(unsigned mode=0;mode<2;mode++) {
        ++cases; memset(ram,0xcd,sizeof(ram));
        queries=values=vectors=dispatches=forwards=0;
        esp=stack; ecx=object; ebx=0xabcdef12; esi=0x12345678; edi=0xfedcba98; g_ebp=0x81234567;
        hash=mode?0xa71a3d94u:0xc2888755u; index=n*13u;
        first=0x80000000u+n; last=0xfedcba98u-n;
        MEM32(stack)=0xfeedface; MEM32(stack+4)=hash; MEM32(stack+8)=index; MEM32(object+0xb0)=backend;
        sub_00104480();
        CHECK(esp==stack+12 && ebx==0xabcdef12 && esi==0x12345678 && edi==0xfedcba98 && g_ebp==0x81234567);
        CHECK(MEM32(stack)==0xfeedface && MEM32(stack+12)==0xcdcdcdcd);
        if(mode) CHECK(queries==2 && values==2 && vectors==2 && dispatches==1 && !forwards && eax==0);
        else CHECK(!queries && !values && !vectors && !dispatches && forwards==1 && eax==0xbaadf00d);
    }
    printf("PASS: %u exact 104480 cases, distinct vector layout/order, two values, forwarding and ABI\n",cases);
}
