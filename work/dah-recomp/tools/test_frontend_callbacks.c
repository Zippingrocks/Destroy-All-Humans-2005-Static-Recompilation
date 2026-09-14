/* Exact production callbacks are included by the runner. Mocks expose only
 * native call ABIs; expected state comes from the original XBE instructions. */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
static uint32_t ram[0x10000 / 4];
#define MEM32(a) (*(uint32_t *)((uint8_t *)ram + (uint32_t)(a)))
#define MEMF(a) (*(float *)((uint8_t *)ram + (uint32_t)(a)))
#define MEM8(a) (*(uint8_t *)((uint8_t *)ram + (uint32_t)(a)))
#define LO8(a) ((uint8_t)(a))
#define PUSH32(s,v) do { (s) -= 4u; MEM32(s) = (uint32_t)(v); } while (0)
#define POP32(s,v) do { (v) = MEM32(s); (s) += 4u; } while (0)
static uint32_t eax, ebx, ecx, edx, esi, edi, esp;
static double g_fp_stack[8];
static unsigned g_fp_top;
static unsigned cases, checks, conversions, forwarded, virtual_calls, gates, events;
static unsigned destroyed, released;
static uint32_t hash, gate_result, virtual_expected, event_return_pc;
static double number;
#define CHECK(c) do { ++checks; if (!(c)) { fprintf(stderr,"FAIL line=%u case=%u %s\n",__LINE__,cases,#c); exit(1); } } while (0)
static void sub_000FBCB0(void)
{
    CHECK(MEM32(esp + 4) == 0x5000); ++conversions;
    eax = 0x6100; ecx = edx = 0xDEADBEEF; esp += 8;
}
static void sub_00139510(void)
{
    CHECK(ecx == 0x6100); CHECK(conversions == 1);
    g_fp_top = (g_fp_top + 7u) & 7u; g_fp_stack[g_fp_top] = number;
    eax = ecx = edx = 0xDEADBEEF; esp += 4;
}
static void sub_000F99F0(void)
{
    CHECK(ecx == 0x2000 && (MEM32(esp) == 0x102359 || MEM32(esp) == 0x101249));
    CHECK(MEM32(esp + 4) == hash && MEM32(esp + 8) == 0x5000);
    ++forwarded; eax = 0xCAFEBABE; ecx = edx = 0xDEADBEEF; esp += 12;
}
static void sub_000F88F0(void)
{
    CHECK(ecx == 0x2000 && MEM32(esp + 4) == 0x2078 && MEM32(esp + 8) == 0x2068);
    CHECK(MEM32(esp) == 0x1023FD || MEM32(esp) == 0x103F3D);
    ++gates; eax = gate_result; ecx = edx = 0xDEADBEEF; esp += 12;
}
static void sub_000F93F0(void)
{
    CHECK(ecx == 0x2000 && MEM32(esp) == event_return_pc && MEM32(esp + 4) == 0x5000);
    ++events; eax = 0xCAFEBABE; ecx = edx = 0xDEADBEEF; esp += 8;
}
static void virtual_call(uint32_t target, uint32_t before)
{
    if (MEM32(esp) == 0x104529) {
        CHECK(target == 0xAABBCC00 && ecx == 0x3000 && esp + 8 == before);
        CHECK(MEM32(esp + 4) == 1u && MEM32(0x2000) == 0x235628);
        ++virtual_calls; eax = ecx = edx = 0xDEADBEEF; esp += 8; return;
    }
    CHECK(target == virtual_expected && ecx == 0x3000 && esp + 4 == before);
    CHECK(MEM32(esp) == 0x102368 || MEM32(esp) == 0x10240C || MEM32(esp) == 0x103F4C);
    ++virtual_calls; eax = ecx = edx = 0xDEADBEEF; esp += 4;
}
static void sub_000F86E0(void)
{
    CHECK(ecx == 0x2000 && MEM32(esp) == 0x104530 && MEM32(0x2000) == 0x235628);
    ++destroyed; eax = ecx = edx = 0xDEADBEEF; esp += 4;
}
static void sub_0006B710(void)
{
    CHECK(MEM32(esp) == 0x10453D && MEM32(esp + 4) == 0x2000 && destroyed == 1);
    ++released; eax = ecx = edx = 0xDEADBEEF; esp += 4; /* cdecl argument remains */
}
#define RECOMP_ICALL_SAFE(target,before) virtual_call((target),(before))
#include "frontend_callbacks_fixture.inc"
static void reset(void)
{
    ++cases; memset(ram,0xCD,sizeof(ram));
    eax = edx = 0xABABABAB; ebx = 0x13579BDF; esi = 0x2468ACE0; edi = 0xFEDCBA98;
    ecx = 0x2000; esp = 0x9000;
    MEM32(esp) = 0x12345678; MEM32(0x20B0) = 0x3000; MEM32(0x3000) = 0x4000;
    MEM32(0x4000) = 0xAABBCC00; MEM32(0x4004) = 0xAABBCC04; MEM32(0x4008) = 0xAABBCC08;
    conversions = forwarded = virtual_calls = gates = events = 0;
    destroyed = released = 0;
}
static void saved(uint32_t expected_esp)
{
    CHECK(esp == expected_esp && esi == 0x2468ACE0 && edi == 0xFEDCBA98 && ebx == 0x13579BDF);
    CHECK(MEM32(0x9000) == 0x12345678 && MEM32(0x900C) == 0xCDCDCDCD);
}
int main(void)
{
    const uint32_t keys[] = {0x42841248,0x3F367A0A,0x90F2A209,0x91F03F7C,0,1,0x80000000,0x90F2A208,0x90F2A20A,0xFFFFFFFF};
    const double values[] = {0.0,-0.0,1.25,-44.5,1.0/3.0,INFINITY,NAN};
    for (unsigned k=0;k<sizeof(keys)/sizeof(keys[0]);++k)
    for (unsigned v=0;v<sizeof(values)/sizeof(values[0]);++v)
    for (unsigned top=0;top<8;++top) {
        reset(); hash=keys[k]; number=values[v]; g_fp_top=top;
        MEM32(esp+4)=hash; MEM32(esp+8)=0x5000; virtual_expected=0xAABBCC08;
        sub_001022D0(); saved(0x900C); CHECK(g_fp_top==top);
        if(k<3) {
            const uint32_t offsets[]={0xB4,0xBC,0xB8}; float expected=(float)number;
            CHECK(conversions==1 && !forwarded && !virtual_calls && eax==0);
            CHECK(isnan(expected) ? isnan(MEMF(0x2000+offsets[k])) : memcmp(&expected,&MEMF(0x2000+offsets[k]),4)==0);
            for(unsigned j=0;j<3;++j) if(j!=k) CHECK(MEM32(0x2000+offsets[j])==0xCDCDCDCD);
        } else if(k==3) CHECK(virtual_calls==1 && !conversions && !forwarded && eax==0);
        else CHECK(forwarded==1 && !virtual_calls && !conversions && eax==0xCAFEBABE);
    }
    const uint32_t gate_values[]={0,1,0x100,0xFF,0xABCDEF00,0xABCDEF01};
    for(unsigned variant=0;variant<2;++variant)
    for(uint32_t type=0;type<18;++type)
    for(unsigned g=0;g<sizeof(gate_values)/sizeof(gate_values[0]);++g) {
        reset(); MEM32(esp+4)=0x5000; MEM32(0x5004)=type; gate_result=gate_values[g];
        virtual_expected=variant?0xAABBCC08:0xAABBCC04; event_return_pc=variant?0x103F54:0x102414;
        if(variant)sub_00103F20();else sub_001023E0();
        saved(0x9008); CHECK(events==1 && eax==0xCAFEBABE);
        CHECK(gates==(unsigned)(type==9)); CHECK(virtual_calls==(unsigned)(type==9 && (gate_result&0xFF)!=0));
        CHECK(!forwarded && !conversions);
    }
    const uint32_t vector_keys[]={0x0720E37A,0x8A40881A,0xF746A230,0,0xC2888755,0xFFFFFFFF};
    for(unsigned k=0;k<sizeof(vector_keys)/sizeof(vector_keys[0]);++k)
    for(unsigned v=0;v<sizeof(values)/sizeof(values[0]);++v)
    for(unsigned top=0;top<8;++top) {
        reset(); hash=vector_keys[k]; number=values[v]; g_fp_top=top;
        MEM32(esp+4)=hash; MEM32(esp+8)=0x5000;
        sub_00101220(); saved(0x900C); CHECK(g_fp_top==top);
        if(k<3) {
            float expected=(float)number;
            CHECK(conversions==1 && !forwarded && !virtual_calls && eax==0);
            CHECK(isnan(expected)?isnan(MEMF(0x3004+k*4)):memcmp(&expected,&MEMF(0x3004+k*4),4)==0);
            CHECK(MEM32(0x3010)==0xCDCDCD01);
            for(unsigned j=0;j<3;++j)if(j!=k)CHECK(MEM32(0x3004+j*4)==0xCDCDCDCD);
        }else CHECK(forwarded==1 && !conversions && !virtual_calls && eax==0xCAFEBABE);
    }
    const uint32_t delete_flags[]={0,1,2,3,0x100,0x101,0xFFFFFFFF};
    for(unsigned child=0;child<2;++child)
    for(unsigned f=0;f<sizeof(delete_flags)/sizeof(delete_flags[0]);++f) {
        reset(); MEM32(esp+4)=delete_flags[f]; if(!child)MEM32(0x20B0)=0;
        sub_00104510(); saved(0x9008); CHECK(eax==0x2000 && destroyed==1);
        CHECK(virtual_calls==child && released==(delete_flags[f]&1u));
    }
    printf("PASS: %u frontend callback cases, %u assertions; property/x87, virtual slots, base forwarding, destructor, and ret/nonvolatile ABI\n",cases,checks);
    return 0;
}
