#define RECOMP_GENERATED_CODE
#include "recomp_funcs.h"

/**
 * sub_00016A90
 * Original: 0x00016A90 - 0x00016B47 (183 bytes, 63 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00016A90(void)
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

loc_00016A90: ;
    esp = esp - 0xC;
    PUSH32(esp, esi);
    esi = ecx;
    PUSH32(esp, edi);
    edi = MEM32(esi + 0x1C);
    fp_push(MEMF(edi + 0x130)); /* fld float */
    g_fp_cmp = RECOMP_FCMP(fp_top(), MEMF(0x225C20)); fp_pop(); /* fcomp dword ptr [0x225c20] */
    eax = (eax & 0xFFFF0000u) | (uint32_t)(uint16_t)(((g_fp_top & 7u) << 11) | (g_fp_cmp == 2 ? 0x4500u : g_fp_cmp < 0 ? 0x0100u : g_fp_cmp > 0 ? 0x0000u : 0x4000u)); /* fnstsw ax <- fpu status */
    _fa = (uint32_t)(HI8(eax)) & 0xFFu; _fb = (uint32_t)(0x41) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test HI8(eax), 0x41 (8-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_00016AEC; /* jne: not equal / not zero */

loc_00016AAD: ;
    eax = MEM32(esi + 0x18);
    ecx = esi + 0x18;
    { uint32_t _icall_esp = g_esp;
    { uint32_t _icall_target = MEM32(eax); PUSH32(esp, 0x00016AB5u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00016AB5: ;
    edx = MEM32(edi + 0x130);
    ecx = esp + 8;
    PUSH32(esp, ecx);
    PUSH32(esp, 0);
    PUSH32(esp, eax);
    PUSH32(esp, edx);
    edi = edi + 0x11C;
    PUSH32(esp, edi);
    edx = 0; /* xor self */
    ecx = eax;
    MEM32(esp + 0x1C) = 0;
    MEM32(esp + 0x20) = 0;
    MEM32(esp + 0x24) = 0;
    PUSH32(esp, 0x00016AECu); sub_0007A130(); /* call 0x0007A130 */

loc_00016AEC: ;
    edi = MEM32(esp + 0x18);
    eax = MEM32(edi + 4);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00016AFC; /* je: equal / zero */

loc_00016AF7: ;
    edx = MEM32(eax + 0x1C);
    goto loc_00016B01;

loc_00016AFC: ;
    edx = 0x1FDDA155;

loc_00016B01: ;
    ecx = 0x225FB0;
    PUSH32(esp, 0x00016B0Bu); sub_000D54A0(); /* call 0x000D54A0 */

loc_00016B0B: ;
    edx = MEM32(esi);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 0);
    PUSH32(esp, 1);
    PUSH32(esp, 0);
    PUSH32(esp, 0);
    PUSH32(esp, 0);
    PUSH32(esp, eax);
    ecx = esi;
    { uint32_t _icall_target = MEM32(edx + 0x6C); PUSH32(esp, 0x00016B1Du); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00016B1D: ;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_00016B37; /* jne: not equal / not zero */

loc_00016B21: ;
    eax = MEM32(esi);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 0);
    PUSH32(esp, 1);
    PUSH32(esp, 0);
    PUSH32(esp, 0);
    PUSH32(esp, 0);
    PUSH32(esp, 0xE4A4EAC2u);
    ecx = esi;
    { uint32_t _icall_target = MEM32(eax + 0x6C); PUSH32(esp, 0x00016B37u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00016B37: ;
    PUSH32(esp, edi);
    ecx = esi;
    PUSH32(esp, 0x00016B3Fu); sub_000113D0(); /* call 0x000113D0 */

loc_00016B3F: ;
    POP32(esp, edi);
    POP32(esp, esi);
    esp = esp + 0xC;
    esp += 8; return; /* ret 4 */

    #undef fp_push
    #undef fp_pop
    #undef fp_top
    #undef fp_st
    #undef fp_st1
}

/**
 * sub_0009A210
 * Original: 0x0009A210 - 0x0009A22E (30 bytes, 11 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0009A210(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_0009A210: ;
    PUSH32(esp, esi);
    esi = ecx;
    PUSH32(esp, 0x0009A218u); sub_0009A090(); /* call 0x0009A090 */

loc_0009A218: ;
    _fa = (uint32_t)(MEM8(esp + 8)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(esp + 8), 1 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0009A228; /* je: equal / zero */

loc_0009A21F: ;
    PUSH32(esp, esi);
    PUSH32(esp, 0x0009A225u); sub_0006B710(); /* call 0x0006B710 */

loc_0009A225: ;
    esp = esp + 4;

loc_0009A228: ;
    eax = esi;
    POP32(esp, esi);
    esp += 8; return; /* ret 4 */

}
