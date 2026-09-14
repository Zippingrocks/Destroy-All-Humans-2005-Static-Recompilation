#include <stdint.h>
#include <stdio.h>
#include <string.h>
static uint32_t memory[16];
static uint32_t eax,ebx,ecx,edx,esi,edi,esp;
#define MEM32(a) memory[(a)/4u]
#define POP32(s,v) do { (v)=MEM32(s); (s)+=4u; } while(0)
#include "vm_name_lookup_fixture.inc"
int main(void)
{
    const uint32_t values[]={0,1,0xFFFFFFFF,0x80000000,0x0243F02C,0x00700094,0xAABBCCDD,0xCCDD0011};
    unsigned cases=0;
    for(unsigned i=0;i<8;++i)for(unsigned j=0;j<8;++j)for(unsigned k=0;k<8;++k){
        uint32_t before[16];memset(memory,0xCD,sizeof(memory));
        esp=32;MEM32(32)=values[i];MEM32(36)=values[j];MEM32(40)=values[k];
        memcpy(before,memory,sizeof(memory));eax=0x0D;ebx=0x11112222;ecx=2;edx=0x0B;esi=0x0C;edi=0x0240EF50;
        sub_00191FAA();++cases;
        if(eax || esp!=44 || edi!=values[i] || esi!=values[j] || ebx!=0x11112222 || ecx!=2 || edx!=0x0B || memcmp(memory,before,sizeof(memory))){
            fprintf(stderr,"FAIL unwind case%u esp=%X edi=%X esi=%X eax=%X\n",cases,esp,edi,esi,eax);return 1;
        }
    }
    printf("PASS: %u exact-production name-lookup unwind cases; saved registers, return consumption, guest stack unchanged\n",cases);
    return 0;
}
