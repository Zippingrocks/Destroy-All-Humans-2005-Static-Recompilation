#define RECOMP_GENERATED_CODE
#include "recomp_funcs.h"

/**
 * sub_0003CD20
 * Original: 0x0003CD20 - 0x0003CDF6 (214 bytes, 66 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0003CD20(void)
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

loc_0003CD20: ;
    esp = esp - 0xC;
    PUSH32(esp, esi);
    esi = ecx;
    fp_push(MEMF(esi + 0x24)); /* fld float */
    PUSH32(esp, edi);
    g_fp_cmp = RECOMP_FCMP(fp_top(), MEMF(0x225C20)); fp_pop(); /* fcomp dword ptr [0x225c20] */
    eax = (eax & 0xFFFF0000u) | (uint32_t)(uint16_t)(((g_fp_top & 7u) << 11) | (g_fp_cmp == 2 ? 0x4500u : g_fp_cmp < 0 ? 0x0100u : g_fp_cmp > 0 ? 0x0000u : 0x4000u)); /* fnstsw ax <- fpu status */
    _fa = (uint32_t)(HI8(eax)) & 0xFFu; _fb = (uint32_t)(0x41) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test HI8(eax), 0x41 (8-bit) */
    if (RECOMP_PARITY8((_fa) & (_fb))) goto loc_0003CDF0; /* jp: parity */

loc_0003CD3B: ;
    fp_push(MEMF(esi + 0x20)); /* fld float */
    g_fp_cmp = RECOMP_FCMP(fp_top(), MEMF(0x225C20)); fp_pop(); /* fcomp dword ptr [0x225c20] */
    eax = (eax & 0xFFFF0000u) | (uint32_t)(uint16_t)(((g_fp_top & 7u) << 11) | (g_fp_cmp == 2 ? 0x4500u : g_fp_cmp < 0 ? 0x0100u : g_fp_cmp > 0 ? 0x0000u : 0x4000u)); /* fnstsw ax <- fpu status */
    _fa = (uint32_t)(HI8(eax)) & 0xFFu; _fb = (uint32_t)(0x41) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test HI8(eax), 0x41 (8-bit) */
    if (RECOMP_PARITY8((_fa) & (_fb))) goto loc_0003CDF0; /* jp: parity */

loc_0003CD4F: ;
    fp_push(MEMF(esi + 0x28)); /* fld float */
    g_fp_cmp = RECOMP_FCMP(fp_top(), MEMF(0x225C20)); fp_pop(); /* fcomp dword ptr [0x225c20] */
    eax = (eax & 0xFFFF0000u) | (uint32_t)(uint16_t)(((g_fp_top & 7u) << 11) | (g_fp_cmp == 2 ? 0x4500u : g_fp_cmp < 0 ? 0x0100u : g_fp_cmp > 0 ? 0x0000u : 0x4000u)); /* fnstsw ax <- fpu status */
    _fa = (uint32_t)(HI8(eax)) & 0xFFu; _fb = (uint32_t)(0x41) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test HI8(eax), 0x41 (8-bit) */
    if (RECOMP_PARITY8((_fa) & (_fb))) goto loc_0003CDF0; /* jp: parity */

loc_0003CD63: ;
    PUSH32(esp, 0x0003CD68u); sub_00029B30(); /* call 0x00029B30 */

loc_0003CD68: ;
    ecx = MEM32(esi + 8);
    eax = MEM32(ecx);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 0);
    PUSH32(esp, 1);
    PUSH32(esp, 0);
    PUSH32(esp, 0);
    PUSH32(esp, 0);
    PUSH32(esp, 0xEBEB1BE9u);
    { uint32_t _icall_target = MEM32(eax + 0x6C); PUSH32(esp, 0x0003CD7Fu); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_0003CD7F: ;
    eax = MEM32(esi + 8);
    edx = MEM32(eax + 0x18);
    ecx = eax + 0x18;
    { uint32_t _icall_esp = g_esp;
    { uint32_t _icall_target = MEM32(edx); PUSH32(esp, 0x0003CD8Au); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_0003CD8A: ;
    edi = eax;
    eax = MEM32(esi + 4);
    ecx = esp + 8;
    PUSH32(esp, ecx);
    PUSH32(esp, 0);
    MEM32(esp + 0x10) = 0;
    MEM32(esp + 0x14) = 0;
    MEM32(esp + 0x18) = 0;
    edx = MEM32(eax + 0xD8);
    PUSH32(esp, edi);
    PUSH32(esp, edx);
    eax = eax + 0xC4;
    PUSH32(esp, eax);
    edx = 0; /* xor self */
    ecx = edi;
    PUSH32(esp, 0x0003CDC5u); sub_0007A130(); /* call 0x0007A130 */

loc_0003CDC5: ;
    eax = MEM32(esi);
    ecx = esi;
    { uint32_t _icall_esp = g_esp;
    { uint32_t _icall_target = MEM32(eax + 0x30); PUSH32(esp, 0x0003CDCCu); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_0003CDCC: ;
    edx = MEM32(eax + 0x120);
    esp = esp - 0xC;
    ecx = esp;
    PUSH32(esp, edx);
    PUSH32(esp, 0x0003CDDDu); sub_00012360(); /* call 0x00012360 */

loc_0003CDDD: ;
    ecx = edi;
    PUSH32(esp, 0x0003CDE4u); sub_00094300(); /* call 0x00094300 */

loc_0003CDE4: ;
    eax = MEM32(esi + 4);
    ecx = MEM32(eax + 0xBC);
    MEM32(esi + 0x24) = ecx;

loc_0003CDF0: ;
    POP32(esp, edi);
    POP32(esp, esi);
    esp = esp + 0xC;
    esp += 4; return; /* ret */

    #undef fp_push
    #undef fp_pop
    #undef fp_top
    #undef fp_st
    #undef fp_st1
}

/**
 * sub_0003E2E0
 * Original: 0x0003E2E0 - 0x0003E301 (33 bytes, 14 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0003E2E0(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_0003E2E0: ;
    PUSH32(esp, esi);
    esi = ecx;
    ecx = MEM32(esp + 8);
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, ecx (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0003E2F7; /* je: equal / zero */

loc_0003E2EB: ;
    eax = MEM32(ecx);
    { uint32_t _icall_esp = g_esp;
    { uint32_t _icall_target = MEM32(eax + 0x44); PUSH32(esp, 0x0003E2F0u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_0003E2F0: ;
    MEM32(esi + 0x20) = eax;
    POP32(esp, esi);
    esp += 8; return; /* ret 4 */

loc_0003E2F7: ;
    eax = eax | 0xFFFFFFFFu;
    MEM32(esi + 0x20) = eax;
    POP32(esp, esi);
    esp += 8; return; /* ret 4 */

}

/**
 * sub_0004ACC0
 * Original: 0x0004ACC0 - 0x0004ADB7 (247 bytes, 90 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0004ACC0(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_0004ACC0: ;
    esp = esp - 0x1C;
    PUSH32(esp, esi);
    esi = ecx;
    eax = MEM32(esi + 0xC);
    _fa = (uint32_t)(MEM32(eax + 0x40)) & 0xFFFFFFFFu; _fb = (uint32_t)(2) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(eax + 0x40), 2 (32-bit) */
    PUSH32(esp, edi);
    if (CMP_NE(_fa, _fb)) goto loc_0004AD0B; /* jne: not equal / not zero */

loc_0004ACD0: ;
    PUSH32(esp, 8);
    PUSH32(esp, 0x0004ACD7u); sub_0006B6F0(); /* call 0x0006B6F0 */

loc_0004ACD7: ;
    ecx = MEM32(esi + 4);
    edx = MEM32(ecx + 0x28);
    edi = eax;
    eax = MEM32(edx);
    MEM32(edi) = eax;
    ecx = MEM32(esi + 0x3C);
    MEM32(edi + 4) = ecx;
    edx = MEM32(esi + 0xC);
    eax = MEM32(edx + 0x44);
    esp = esp + 4;
    PUSH32(esp, eax);
    edx = edi;
    ecx = 2;
    PUSH32(esp, 0x0004ACFFu); sub_00130D80(); /* call 0x00130D80 */

loc_0004ACFF: ;
    PUSH32(esp, edi);
    MEM32(esi + 0x34) = eax;
    PUSH32(esp, 0x0004AD08u); sub_0006B710(); /* call 0x0006B710 */

loc_0004AD08: ;
    esp = esp + 4;

loc_0004AD0B: ;
    ecx = MEM32(esi + 0x34);
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, ecx (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0004ADB1; /* je: equal / zero */

loc_0004AD16: ;
    eax = MEM32(esi + 0x3C);
    edx = MEM32(eax + 0x20);
    MEM32(esp + 8) = edx;
    edx = MEM32(eax + 0x24);
    MEM32(esp + 0xC) = edx;
    edx = MEM32(eax + 0x28);
    MEM32(esp + 0x10) = edx;
    edx = MEM32(eax + 0x40);
    MEM32(esp + 0x14) = edx;
    edx = MEM32(eax + 0x44);
    MEM32(esp + 0x18) = edx;
    edx = MEM32(eax + 0x48);
    MEM32(esp + 0x1C) = edx;
    eax = MEM32(eax + 0x4C);
    MEM32(esp + 0x20) = eax;
    edx = MEM32(ecx);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 1);
    eax = esp + 0xC;
    PUSH32(esp, eax);
    { uint32_t _icall_target = MEM32(edx + 0x48); PUSH32(esp, 0x0004AD56u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_0004AD56: ;
    ecx = MEM32(esi + 0x34);
    edx = MEM32(ecx);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 1);
    eax = esp + 0x18;
    PUSH32(esp, eax);
    { uint32_t _icall_target = MEM32(edx + 0x50); PUSH32(esp, 0x0004AD65u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_0004AD65: ;
    ecx = MEM32(esi + 4);
    eax = MEM32(ecx + 0x1C);
    edi = MEM32(eax + 0x58);
    ecx = MEM32(esi + 0x34);
    eax = MEM32(eax + 0x54);
    edx = MEM32(ecx);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 0x3F800000);
    PUSH32(esp, edi);
    PUSH32(esp, eax);
    { uint32_t _icall_target = MEM32(edx + 0x10); PUSH32(esp, 0x0004AD80u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_0004AD80: ;
    eax = MEM32(esi + 4);
    edi = MEM32(eax + 0x1C);
    edi = MEM32(edi + 0x54);
    ecx = MEM32(esi + 0x34);
    edx = MEM32(ecx);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, edi);
    PUSH32(esp, eax);
    { uint32_t _icall_target = MEM32(edx + 0x18); PUSH32(esp, 0x0004AD93u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_0004AD93: ;
    ecx = MEM32(esi + 0x34);
    eax = MEM32(ecx);
    { uint32_t _icall_esp = g_esp;
    { uint32_t _icall_target = MEM32(eax + 0x58); PUSH32(esp, 0x0004AD9Bu); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_0004AD9B: ;
    ecx = MEM32(esi + 0x34);
    edx = MEM32(ecx);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 1);
    { uint32_t _icall_target = MEM32(edx + 0x68); PUSH32(esp, 0x0004ADA5u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_0004ADA5: ;
    ecx = MEM32(esi + 0x34);
    eax = MEM32(ecx);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 0);
    PUSH32(esp, 1);
    { uint32_t _icall_target = MEM32(eax + 0x40); PUSH32(esp, 0x0004ADB1u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_0004ADB1: ;
    POP32(esp, edi);
    POP32(esp, esi);
    esp = esp + 0x1C;
    esp += 4; return; /* ret */

}
