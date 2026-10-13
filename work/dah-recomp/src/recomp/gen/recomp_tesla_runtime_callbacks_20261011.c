/* Generated only from the retail XBE for recurring crash CE45648D31F5AFCD. */
#define RECOMP_GENERATED_CODE
#include "recomp_funcs.h"

/**
 * sub_00079450
 * Original: 0x00079450 - 0x000795FE (430 bytes, 131 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00079450(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    #define fp_push(v) do { double _fp_value = (v); \
        g_fp_top = (g_fp_top + 7u) & 7u; \
        g_fp_stack[g_fp_top] = _fp_value; } while (0)
    #define fp_pop() (g_fp_top = (g_fp_top + 1u) & 7u)
    #define fp_top() g_fp_stack[g_fp_top]
    #define fp_st(i) g_fp_stack[(g_fp_top + (i)) & 7u]
    #define fp_st1() fp_st(1)

loc_00079450: ;
    esp = esp - 0x10;
    PUSH32(esp, esi);
    esi = ecx;
    fp_push(MEMF(esi + 0x120)); /* fld float */
    fp_top() = fp_top() - MEMF(esp + 0x18); /* fsub dword ptr [esp + 0x18] */
    MEMF(esi + 0x120) = (float)fp_top(); /* fst */
    g_fp_cmp = RECOMP_FCMP(fp_top(), MEMF(0x225C20)); fp_pop(); /* fcomp dword ptr [0x225c20] */
    eax = (eax & 0xFFFF0000u) | (uint32_t)(uint16_t)(((g_fp_top & 7u) << 11) | (g_fp_cmp == 2 ? 0x4500u : g_fp_cmp < 0 ? 0x0100u : g_fp_cmp > 0 ? 0x0000u : 0x4000u)); /* fnstsw ax <- fpu status */
    _fa = (uint32_t)(HI8(eax)) & 0xFFu; _fb = (uint32_t)(0x41) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test HI8(eax), 0x41 (8-bit) */
    if (RECOMP_PARITY8((_fa) & (_fb))) goto loc_0007947A; /* jp: parity */

loc_00079473: ;
    PUSH32(esp, 1);
    PUSH32(esp, 0x0007947Au); sub_00079320(); /* call 0x00079320 */

loc_0007947A: ;
    eax = MEM32(esi + 0x10);
    eax = eax - 0;
    if ((eax == 0)) goto loc_00079535; /* je: equal / zero */

loc_00079486: ;
    eax = eax - 1;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fas = (int32_t)(int32_t)_fa; /* dec flags snapshot */
    if ((_fa == 0)) goto loc_000794C0; /* je: equal / zero */

loc_00079489: ;
    eax = eax - 1;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fas = (int32_t)(int32_t)_fa; /* dec flags snapshot */
    if ((_fa != 0)) goto loc_000795F7; /* jne: not equal / not zero */

loc_00079490: ;
    ecx = esi + 0x128;
    PUSH32(esp, 0x0007949Bu); sub_001046E0(); /* call 0x001046E0 */

loc_0007949B: ;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp LO8(eax), 1 (8-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_000795F7; /* jne: not equal / not zero */

loc_000794A3: ;
    _fa = (uint32_t)(MEM32(esi + 0x10)) & 0xFFFFFFFFu; _fb = (uint32_t)(2) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(esi + 0x10), 2 (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_000795F7; /* jne: not equal / not zero */

loc_000794AD: ;
    ecx = MEM32(0x286768);
    PUSH32(esp, esi);
    PUSH32(esp, 0x000794B9u); sub_00104E90(); /* call 0x00104E90 */

loc_000794B9: ;
    POP32(esp, esi);
    esp = esp + 0x10;
    esp += 8; return; /* ret 4 */

loc_000794C0: ;
    eax = MEM32(esi + 0x110);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0xFFFFFFFFu) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0xFFFFFFFFu (32-bit) */
    ecx = esi + 0x110;
    if (CMP_EQ(_fa, _fb)) goto loc_000795F7; /* je: equal / zero */

loc_000794D5: ;
    PUSH32(esp, 0x000794DAu); sub_00109F70(); /* call 0x00109F70 */

loc_000794DA: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00079525; /* je: equal / zero */

loc_000794DE: ;
    ecx = MEM32(esi + 0x114);
    eax = MEM32(eax + 0x28);
    edx = esi + 0x114;
    MEM32(esp + 8) = ecx;
    ecx = MEM32(edx + 4);
    MEM32(esp + 0xC) = ecx;
    ecx = MEM32(edx + 8);
    MEM32(esp + 0x10) = ecx;
    ecx = MEM32(eax);
    ecx = ecx + 0x50;
    PUSH32(esp, ecx);
    ecx = esp + 0xC;
    PUSH32(esp, 0x0007950Eu); sub_000D68C0(); /* call 0x000D68C0 */

loc_0007950E: ;
    edx = MEM32(esi + 4);
    ecx = esi + 4;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 1);
    eax = esp + 0xC;
    PUSH32(esp, eax);
    { uint32_t _icall_target = MEM32(edx + 8); PUSH32(esp, 0x0007951Eu); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_0007951E: ;
    POP32(esp, esi);
    esp = esp + 0x10;
    esp += 8; return; /* ret 4 */

loc_00079525: ;
    PUSH32(esp, 1);
    ecx = esi;
    PUSH32(esp, 0x0007952Eu); sub_00079320(); /* call 0x00079320 */

loc_0007952E: ;
    POP32(esp, esi);
    esp = esp + 0x10;
    esp += 8; return; /* ret 4 */

loc_00079535: ;
    fp_push(MEMF(esi + 0x10C)); /* fld float */
    PUSH32(esp, edi);
    fp_top() = fp_top() - MEMF(esp + 0x1C); /* fsub dword ptr [esp + 0x1c] */
    edi = esi + 0x104;
    ecx = edi;
    MEMF(esi + 0x10C) = (float)fp_top(); fp_pop(); /* fstp */
    PUSH32(esp, 0x00079553u); sub_000D4E40(); /* call 0x000D4E40 */

loc_00079553: ;
    ecx = MEM32(esi + 0xC);
    MEMF(esp + 8) = (float)fp_top(); fp_pop(); /* fstp */
    fp_push(MEMF(0x225C20)); /* fld float */
    fp_push(MEMF(ecx + 0x28)); /* fld float */
    g_fp_cmp = RECOMP_FCMP(fp_top(), fp_st1()); fp_pop(); fp_pop(); /* fucompp  */
    eax = (eax & 0xFFFF0000u) | (uint32_t)(uint16_t)(((g_fp_top & 7u) << 11) | (g_fp_cmp == 2 ? 0x4500u : g_fp_cmp < 0 ? 0x0100u : g_fp_cmp > 0 ? 0x0000u : 0x4000u)); /* fnstsw ax <- fpu status */
    _fa = (uint32_t)(HI8(eax)) & 0xFFu; _fb = (uint32_t)(0x44) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test HI8(eax), 0x44 (8-bit) */
    if ((!RECOMP_PARITY8((_fa) & (_fb)))) goto loc_00079599; /* jnp: not parity */

loc_0007956C: ;
    fp_push(MEMF(ecx + 0x24)); /* fld float */
    edx = MEM32(ecx + 0x24);
    fp_top() = fp_top() - MEMF(esp + 8); /* fsub dword ptr [esp + 8] */
    eax = MEM32(ecx + 0x20);
    PUSH32(esp, edx);
    PUSH32(esp, ecx);
    fp_top() = fp_top() * MEMF(0x225C3C); /* fmul dword ptr [0x225c3c] */
    fp_top() = fp_top() / MEMF(ecx + 0x28); /* fdiv dword ptr [ecx + 0x28] */
    fp_top() = fp_top() * MEMF(esp + 0x24); /* fmul dword ptr [esp + 0x24] */
    fp_top() = fp_top() + MEMF(esp + 0x10); /* fadd dword ptr [esp + 0x10] */
    MEMF(esp) = (float)fp_top(); fp_pop(); /* fstp */
    PUSH32(esp, eax);
    PUSH32(esp, 0x00079595u); sub_00017EA0(); /* call 0x00017EA0 */

loc_00079595: ;
    MEMF(esp + 8) = (float)fp_top(); fp_pop(); /* fstp */

loc_00079599: ;
    ecx = edi;
    PUSH32(esp, 0x000795A0u); sub_000D5010(); /* call 0x000D5010 */

loc_000795A0: ;
    ecx = MEM32(esp + 8);
    PUSH32(esp, ecx);
    edx = edi;
    ecx = edi;
    PUSH32(esp, 0x000795AEu); sub_000D4A10(); /* call 0x000D4A10 */

loc_000795AE: ;
    edx = MEM32(edi);
    ecx = MEM32(edi + 8);
    eax = MEM32(edi + 4);
    MEM32(esp + 0xC) = edx;
    edx = MEM32(esp + 0x1C);
    PUSH32(esp, edx);
    edx = esp + 0x10;
    MEM32(esp + 0x18) = ecx;
    ecx = edx;
    MEM32(esp + 0x14) = eax;
    PUSH32(esp, 0x000795D2u); sub_000D4A10(); /* call 0x000D4A10 */

loc_000795D2: ;
    eax = MEM32(esi + 4);
    esi = esi + 4;
    ecx = esi;
    { uint32_t _icall_esp = g_esp;
    { uint32_t _icall_target = MEM32(eax); PUSH32(esp, 0x000795DCu); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_000795DC: ;
    edx = esp + 0xC;
    PUSH32(esp, eax);
    ecx = edx;
    PUSH32(esp, 0x000795E8u); sub_000D4770(); /* call 0x000D4770 */

loc_000795E8: ;
    edx = MEM32(esi);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 1);
    eax = esp + 0x10;
    PUSH32(esp, eax);
    ecx = esi;
    { uint32_t _icall_target = MEM32(edx + 8); PUSH32(esp, 0x000795F6u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_000795F6: ;
    POP32(esp, edi);

loc_000795F7: ;
    POP32(esp, esi);
    esp = esp + 0x10;
    esp += 8; return; /* ret 4 */

    #undef fp_push
    #undef fp_pop
    #undef fp_top
    #undef fp_st
    #undef fp_st1
}

/**
 * sub_000797E0
 * Original: 0x000797E0 - 0x000797E8 (8 bytes, 3 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_000797E0(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_000797E0: ;
    ecx = ecx + 0x10;
    eax = MEM32(ecx);
    g_seh_ebp = ebp; RECOMP_ITAIL(MEM32(eax + 0x34)); return; /* indirect tail jmp */

}
