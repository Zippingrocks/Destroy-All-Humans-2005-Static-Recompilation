/* Retail-only recovery entries omitted at internal CRT control-flow boundaries.
 * Regenerate and verify the byte ranges with
 * tools/lift_retail_final_crt_entries_20261013.py.
 */
#define RECOMP_GENERATED_CODE
#include "recomp_funcs.h"
#include <math.h>

/* 0x0013FBDC is a nonlocal x87 tail. It deliberately discards the immediate
 * guest return address before returning through its caller's caller. */
void sub_0013FBDC(void)
{
    uint32_t ebp = g_seh_ebp;
    #define fp_push(v) do { double _fp_value = (v); \
        g_fp_top = (g_fp_top + 7u) & 7u; \
        g_fp_stack[g_fp_top] = _fp_value; } while (0)
    #define fp_pop() (g_fp_top = (g_fp_top + 1u) & 7u)
    #define fp_top() g_fp_stack[g_fp_top]

    POP32(esp, eax);
    g_fp_cmp = RECOMP_FCMP(fp_top(), 0.0);
    MEM16(ebp - 160u) = (uint16_t)(((g_fp_top & 7u) << 11) |
        (g_fp_cmp == 2 ? 0x4500u : g_fp_cmp < 0 ? 0x0100u :
         g_fp_cmp > 0 ? 0x0000u : 0x4000u));
    if (g_fp_cmp < 0 || g_fp_cmp == 2) {
        MEM8(ebp - 144u) = 4u;
        fp_pop();
        fp_pop();
        fp_push(0.0);
    } else {
        fp_pop();
        fp_push(INFINITY); /* retail 80-bit +infinity at 0x00259BFC */
        if ((ecx & 0x0000FF00u) != 0u) fp_top() = -fp_top();
    }
    esp += 4u;

    #undef fp_push
    #undef fp_pop
    #undef fp_top
}

enum descriptor_entry {
    DESCRIPTOR_FROM_142434,
    DESCRIPTOR_FROM_142450,
    DESCRIPTOR_FROM_14245C,
    DESCRIPTOR_FROM_1424B3,
};

/* These four retail addresses are entries into one descriptor-allocation CFG.
 * Keep the backward edges inside one helper: calling the parent function again
 * would repeat its SEH prolog and lock acquisition and would be incorrect. */
static void continue_descriptor_allocation(enum descriptor_entry entry)
{
    uint32_t ebp = g_seh_ebp;
    uint32_t quotient;
    int64_t dividend;

    switch (entry) {
    case DESCRIPTOR_FROM_142434: goto loc_00142434;
    case DESCRIPTOR_FROM_142450: goto loc_00142450;
    case DESCRIPTOR_FROM_14245C: goto loc_0014245C;
    case DESCRIPTOR_FROM_1424B3: goto loc_001424B3;
    }

loc_0014237F:
    MEM32(ebp - 36u) = edi;
    if ((int32_t)edi >= 0x40) goto loc_001424B3;
    esi = MEM32(0x00287C20u + edi * 4u);
    if (esi == 0u) goto loc_0014245C;

loc_0014239A:
    MEM32(ebp - 32u) = esi;
    eax = MEM32(0x00287C20u + edi * 4u) + 0x500u;
    if (esi >= eax) goto loc_00142450;
    if ((MEM8(esi + 4u) & 1u) != 0u) goto loc_0014241D;
    ebx = 0u;
    if (MEM32(esi + 8u) != ebx) goto loc_00142406;
    PUSH32(esp, 0xAu);
    PUSH32(esp, 0x001423C5u); sub_00140C99();
    POP32(esp, ecx);
    MEM32(ebp - 4u) = 1u;
    if (MEM32(esi + 8u) != ebx) goto loc_001423FE;
    PUSH32(esp, 0xFA0u);
    PUSH32(esp, esi + 0xCu);
    PUSH32(esp, 0x001423E0u); sub_0014215F();
    POP32(esp, ecx);
    POP32(esp, ecx);
    if (eax != 0u) goto loc_001423FB;
    PUSH32(esp, 0xFFFFFFFFu);
    PUSH32(esp, ebp - 16u);
    PUSH32(esp, 0x001423F1u); sub_0013A2A6();
    POP32(esp, ecx);
    POP32(esp, ecx);
    eax = 0xFFFFFFFFu;
    g_seh_ebp = ebp;
    sub_001424BF();
    return;

loc_001423FB:
    MEM32(esi + 8u) += 1u;

loc_001423FE:
    MEM32(ebp - 4u) = ebx;
    PUSH32(esp, 0x00142406u); sub_0014242B();

loc_00142406:
    ebx = esi + 0xCu;
    {
        uint32_t _icall_esp = esp;
        uint32_t _icall_target;
        PUSH32(esp, ebx);
        _icall_target = MEM32(0x00225AC4u);
        PUSH32(esp, 0x00142410u);
        RECOMP_ICALL_SAFE(_icall_target, _icall_esp);
    }
    if ((MEM8(esi + 4u) & 1u) == 0u) goto loc_00142434;
    {
        uint32_t _icall_esp = esp;
        uint32_t _icall_target;
        PUSH32(esp, ebx);
        _icall_target = MEM32(0x00225AC0u);
        PUSH32(esp, 0x0014241Du);
        RECOMP_ICALL_SAFE(_icall_target, _icall_esp);
    }

loc_0014241D:
    esi += 0x28u;
    goto loc_0014239A;

loc_00142434:
    MEM32(esi) = 0xFFFFFFFFu;
    eax = esi - MEM32(0x00287C20u + edi * 4u);
    dividend = (int32_t)eax;
    quotient = (uint32_t)(dividend / 0x28);
    edx = (uint32_t)(dividend % 0x28);
    eax = quotient + (edi << 5);
    MEM32(ebp - 28u) = eax;

loc_00142450:
    if (MEM32(ebp - 28u) != 0xFFFFFFFFu) goto loc_001424B3;
    edi += 1u;
    goto loc_0014237F;

loc_0014245C:
    esi = 0x500u;
    PUSH32(esp, esi);
    PUSH32(esp, 0x00142467u); sub_0013CBF3();
    POP32(esp, ecx);
    MEM32(ebp - 32u) = eax;
    if (eax == 0u) goto loc_001424B3;
    ecx = 0x00287C20u + edi * 4u;
    MEM32(ecx) = eax;
    MEM32(0x00287C08u) += 0x20u;
    edx = MEM32(ecx) + esi;
    while (eax < edx) {
        MEM8(eax + 4u) = 0u;
        MEM32(eax) = 0xFFFFFFFFu;
        MEM8(eax + 5u) = 0xAu;
        MEM32(eax + 8u) = 0u;
        eax += 0x28u;
        MEM32(ebp - 32u) = eax;
    }
    edi <<= 5;
    MEM32(ebp - 28u) = edi;
    PUSH32(esp, edi);
    PUSH32(esp, 0x001424AAu); sub_00142290();
    POP32(esp, ecx);
    if (eax == 0u) MEM32(ebp - 28u) = 0xFFFFFFFFu;

loc_001424B3:
    MEM32(ebp - 4u) = 0xFFFFFFFFu;
    PUSH32(esp, 0x001424BCu); sub_001424C5();
    eax = MEM32(ebp - 28u);
    g_seh_ebp = ebp;
    sub_001424BF();
}

void sub_00142434(void) { continue_descriptor_allocation(DESCRIPTOR_FROM_142434); }
void sub_00142450(void) { continue_descriptor_allocation(DESCRIPTOR_FROM_142450); }
void sub_0014245C(void) { continue_descriptor_allocation(DESCRIPTOR_FROM_14245C); }
void sub_001424B3(void) { continue_descriptor_allocation(DESCRIPTOR_FROM_1424B3); }
