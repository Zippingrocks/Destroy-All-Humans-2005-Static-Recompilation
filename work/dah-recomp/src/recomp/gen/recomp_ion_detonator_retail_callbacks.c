#define RECOMP_GENERATED_CODE
#include "recomp_funcs.h"

/**
 * sub_00075660
 * Original: 0x00075660 - 0x00075681 (33 bytes, 8 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00075660(void)
{

loc_00075660: ;
    eax = MEM32(esp + 4);
    edx = MEM32(eax);
    MEM32(ecx + 0xF4) = edx;
    edx = MEM32(eax + 4);
    MEM32(ecx + 0xF8) = edx;
    eax = MEM32(eax + 8);
    MEM32(ecx + 0xFC) = eax;
    esp += 8; return; /* ret 4 */

}

/**
 * sub_00075780
 * Original: 0x00075780 - 0x000757A1 (33 bytes, 12 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00075780(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_00075780: ;
    eax = MEM32(ecx + 0x108);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00075794; /* je: equal / zero */

loc_0007578A: ;
    ecx = eax;
    eax = MEM32(ecx + 0x18);
    ecx = ecx + 0x18;
    g_seh_ebp = ebp; RECOMP_ITAIL(MEM32(eax)); return; /* indirect tail jmp */

loc_00075794: ;
    edx = MEM32(ecx + -4);
    ecx = ecx + 0xFFFFFFFCu;
    { uint32_t _icall_esp = g_esp;
    { uint32_t _icall_target = MEM32(edx + 0x58); PUSH32(esp, 0x0007579Du); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_0007579D: ;
    eax = eax + 0x2C;
    esp += 4; return; /* ret */

}

/**
 * sub_00075800
 * Original: 0x00075800 - 0x00075815 (21 bytes, 7 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00075800(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00075800: ;
    eax = MEM32(ecx + 0x10C);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0007580E; /* je: equal / zero */

loc_0007580A: ;
    eax = MEM32(eax + 0x28);
    esp += 4; return; /* ret */

loc_0007580E: ;
    eax = ecx + 0x84;
    esp += 4; return; /* ret */

}

/**
 * sub_00075A10
 * Original: 0x00075A10 - 0x00075C52 (578 bytes, 183 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00075A10(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
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
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_00075A10: ;
    fp_push(MEMF(0x225C20)); /* fld float */
    esp = esp - 0x28;
    PUSH32(esp, ebx);
    PUSH32(esp, ebp);
    PUSH32(esp, esi);
    esi = ecx;
    fp_push(MEMF(esi + 0xDC)); /* fld float */
    ebp = MEM32(esi + 0xC);
    g_fp_cmp = RECOMP_FCMP(fp_top(), fp_st1()); fp_pop(); fp_pop(); /* fucompp  */
    PUSH32(esp, edi);
    eax = (eax & 0xFFFF0000u) | (uint32_t)(uint16_t)(((g_fp_top & 7u) << 11) | (g_fp_cmp == 2 ? 0x4500u : g_fp_cmp < 0 ? 0x0100u : g_fp_cmp > 0 ? 0x0000u : 0x4000u)); /* fnstsw ax <- fpu status */
    _fa = (uint32_t)(HI8(eax)) & 0xFFu; _fb = (uint32_t)(0x44) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test HI8(eax), 0x44 (8-bit) */
    if (RECOMP_PARITY8((_fa) & (_fb))) goto loc_00075A35; /* jp: parity */

loc_00075A31: ;
    SET_LO8(eax, 1);
    goto loc_00075A37;

loc_00075A35: ;
    SET_LO8(eax, 0); /* xor self */

loc_00075A37: ;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    fp_push(MEMF(esp + 0x3C)); /* fld float */
    fp_top() = fp_top() + MEMF(esi + 0xDC); /* fadd dword ptr [esi + 0xdc] */
    MEMF(esi + 0xDC) = (float)fp_top(); fp_pop(); /* fstp */
    if (TEST_Z(_fa, _fb)) goto loc_00075B01; /* je: equal / zero */

loc_00075A4F: ;
    eax = MEM32(esi + 0x108);
    edx = MEM32(esi + 4);
    ebx = MEM32(eax);
    edi = esi + 4;
    ecx = edi;
    { uint32_t _icall_esp = g_esp;
    { uint32_t _icall_target = MEM32(edx); PUSH32(esp, 0x00075A61u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00075A61: ;
    ecx = MEM32(esi + 0x108);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, eax);
    { uint32_t _icall_target = MEM32(ebx + 0x18); PUSH32(esp, 0x00075A6Bu); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00075A6B: ;
    eax = MEM32(esi + 0x108);
    edx = MEM32(edi);
    ebx = MEM32(eax);
    ecx = edi;
    { uint32_t _icall_esp = g_esp;
    { uint32_t _icall_target = MEM32(edx + 4); PUSH32(esp, 0x00075A7Au); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00075A7A: ;
    ecx = MEM32(esi + 0x108);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, eax);
    { uint32_t _icall_target = MEM32(ebx + 0x2C); PUSH32(esp, 0x00075A84u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00075A84: ;
    ecx = MEM32(esi + 0x108);
    eax = esi + 0x34;
    PUSH32(esp, eax);
    PUSH32(esp, 0x00075A93u); sub_00075880(); /* call 0x00075880 */

loc_00075A93: ;
    edi = MEM32(esi + 0x108);
    eax = MEM32(edi + 0x20);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    ebx = 0x3F83D70A;
    MEM32(edi + 0x4C) = ebx;
    if (TEST_Z(_fa, _fb)) goto loc_00075ACA; /* je: equal / zero */

loc_00075AA8: ;
    edx = MEM32(edi);
    ecx = edi;
    { uint32_t _icall_esp = g_esp;
    { uint32_t _icall_target = MEM32(edx + 0xC); PUSH32(esp, 0x00075AAFu); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00075AAF: ;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00075ABD; /* je: equal / zero */

loc_00075AB3: ;
    ecx = MEM32(edi + 0x20);
    PUSH32(esp, 0x00075ABBu); sub_000BA420(); /* call 0x000BA420 */

loc_00075ABB: ;
    goto loc_00075AC3;

loc_00075ABD: ;
    eax = MEM32(edi + 0x20);
    eax = MEM32(eax + 0x3C);

loc_00075AC3: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00075ACA; /* je: equal / zero */

loc_00075AC7: ;
    MEM32(eax + 0x14) = ebx;

loc_00075ACA: ;
    edi = MEM32(esi + 0x108);
    eax = MEM32(edi + 0x20);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    ebx = 0x4120CCCD;
    MEM32(edi + 0x50) = ebx;
    if (TEST_Z(_fa, _fb)) goto loc_00075B01; /* je: equal / zero */

loc_00075ADF: ;
    edx = MEM32(edi);
    ecx = edi;
    { uint32_t _icall_esp = g_esp;
    { uint32_t _icall_target = MEM32(edx + 0xC); PUSH32(esp, 0x00075AE6u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00075AE6: ;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00075AF4; /* je: equal / zero */

loc_00075AEA: ;
    ecx = MEM32(edi + 0x20);
    PUSH32(esp, 0x00075AF2u); sub_000BA420(); /* call 0x000BA420 */

loc_00075AF2: ;
    goto loc_00075AFA;

loc_00075AF4: ;
    eax = MEM32(edi + 0x20);
    eax = MEM32(eax + 0x3C);

loc_00075AFA: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00075B01; /* je: equal / zero */

loc_00075AFE: ;
    MEM32(eax + 0x18) = ebx;

loc_00075B01: ;
    eax = MEM32(esi + 0x78);
    eax = eax - 1;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fas = (int32_t)(int32_t)_fa; /* dec flags snapshot */
    ebx = MEM32(esp + 0x3C);
    if ((_fa == 0)) goto loc_00075B1E; /* je: equal / zero */

loc_00075B0B: ;
    eax = eax - 1;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fas = (int32_t)(int32_t)_fa; /* dec flags snapshot */
    if ((_fa != 0)) goto loc_00075C35; /* jne: not equal / not zero */

loc_00075B12: ;
    ecx = esi;
    PUSH32(esp, 0x00075B19u); sub_000780C0(); /* call 0x000780C0 */

loc_00075B19: ;
    goto loc_00075C35;

loc_00075B1E: ;
    ecx = MEM32(esi + 0x108);
    edx = MEM32(ecx);
    eax = esp + 0x10;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, eax);
    { uint32_t _icall_target = MEM32(edx + 0x1C); PUSH32(esp, 0x00075B2Eu); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00075B2E: ;
    edx = MEM32(esi + 4);
    edi = esi + 4;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 1);
    eax = esp + 0x14;
    PUSH32(esp, eax);
    ecx = edi;
    { uint32_t _icall_target = MEM32(edx + 8); PUSH32(esp, 0x00075B40u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00075B40: ;
    ecx = MEM32(esi + 0x108);
    edx = MEM32(ecx);
    eax = esp + 0x28;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, eax);
    { uint32_t _icall_target = MEM32(edx + 0x30); PUSH32(esp, 0x00075B50u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00075B50: ;
    edx = MEM32(edi);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 1);
    eax = esp + 0x2C;
    PUSH32(esp, eax);
    ecx = edi;
    { uint32_t _icall_target = MEM32(edx + 0xC); PUSH32(esp, 0x00075B5Eu); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00075B5E: ;
    SET_LO8(eax, MEM8(esi + 0x114));
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_00075BD0; /* jne: not equal / not zero */

loc_00075B68: ;
    ecx = esp + 0x1C;
    PUSH32(esp, ecx);
    ecx = MEM32(esi + 0x108);
    PUSH32(esp, 0x00075B78u); sub_000758E0(); /* call 0x000758E0 */

loc_00075B78: ;
    ecx = esp + 0x1C;
    PUSH32(esp, 0x00075B81u); sub_000D4EA0(); /* call 0x000D4EA0 */

loc_00075B81: ;
    g_fp_cmp = RECOMP_FCMP(fp_top(), MEMF(0x22684C)); fp_pop(); /* fcomp dword ptr [0x22684c] */
    eax = (eax & 0xFFFF0000u) | (uint32_t)(uint16_t)(((g_fp_top & 7u) << 11) | (g_fp_cmp == 2 ? 0x4500u : g_fp_cmp < 0 ? 0x0100u : g_fp_cmp > 0 ? 0x0000u : 0x4000u)); /* fnstsw ax <- fpu status */
    _fa = (uint32_t)(HI8(eax)) & 0xFFu; _fb = (uint32_t)(5) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test HI8(eax), 5 (8-bit) */
    if (RECOMP_PARITY8((_fa) & (_fb))) goto loc_00075C35; /* jp: parity */

loc_00075B92: ;
    edx = MEM32(esi + 0xDC);
    eax = MEM32(esi);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 0x1E5156C);
    ecx = esi;
    MEM8(esi + 0x114) = 1;
    MEM32(esi + 0x118) = edx;
    { uint32_t _icall_target = MEM32(eax + 0x5C); PUSH32(esp, 0x00075BB1u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00075BB1: ;
    ecx = eax;
    PUSH32(esp, 0x00075BB8u); sub_00107D50(); /* call 0x00107D50 */

loc_00075BB8: ;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00075C35; /* je: equal / zero */

loc_00075BBC: ;
    PUSH32(esp, 0);
    PUSH32(esp, 0);
    PUSH32(esp, 0);
    PUSH32(esp, 0x1E5156C);
    ecx = esi;
    PUSH32(esp, 0x00075BCEu); sub_00075820(); /* call 0x00075820 */

loc_00075BCE: ;
    goto loc_00075C35;

loc_00075BD0: ;
    ecx = esp + 0x10;
    edi = esi + 0x11C;
    PUSH32(esp, ecx);
    ecx = edi;
    PUSH32(esp, 0x00075BE2u); sub_00094A40(); /* call 0x00094A40 */

loc_00075BE2: ;
    PUSH32(esp, ebx);
    ecx = edi;
    PUSH32(esp, 0x00075BEAu); sub_00094A90(); /* call 0x00094A90 */

loc_00075BEA: ;
    fp_push(MEMF(esi + 0xDC)); /* fld float */
    fp_top() = fp_top() - MEMF(esi + 0x118); /* fsub dword ptr [esi + 0x118] */
    g_fp_cmp = RECOMP_FCMP(fp_top(), MEMF(ebp + 0xF8)); fp_pop(); /* fcomp dword ptr [ebp + 0xf8] */
    eax = (eax & 0xFFFF0000u) | (uint32_t)(uint16_t)(((g_fp_top & 7u) << 11) | (g_fp_cmp == 2 ? 0x4500u : g_fp_cmp < 0 ? 0x0100u : g_fp_cmp > 0 ? 0x0000u : 0x4000u)); /* fnstsw ax <- fpu status */
    _fa = (uint32_t)(HI8(eax)) & 0xFFu; _fb = (uint32_t)(0x41) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test HI8(eax), 0x41 (8-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_00075C35; /* jne: not equal / not zero */

loc_00075C03: ;
    ecx = MEM32(esi + 0x108);
    eax = esi + 0xE8;
    MEM32(esi + 0xE4) = 0xFFFFFFFFu;
    edx = MEM32(ecx);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, eax);
    { uint32_t _icall_target = MEM32(edx + 0x1C); PUSH32(esp, 0x00075C1Fu); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00075C1F: ;
    edx = MEM32(esi);
    ecx = esi;
    { uint32_t _icall_esp = g_esp;
    { uint32_t _icall_target = MEM32(edx + 0x54); PUSH32(esp, 0x00075C26u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00075C26: ;
    ecx = MEM32(esi + 0x108);
    eax = MEM32(ecx);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 0);
    PUSH32(esp, 0);
    { uint32_t _icall_target = MEM32(eax + 0x4C); PUSH32(esp, 0x00075C35u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00075C35: ;
    ecx = MEM32(esi + 0x10C);
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, ecx (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00075C48; /* je: equal / zero */

loc_00075C3F: ;
    edx = MEM32(ecx);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, ebx);
    { uint32_t _icall_target = MEM32(edx + 0x80); PUSH32(esp, 0x00075C48u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00075C48: ;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebp);
    POP32(esp, ebx);
    esp = esp + 0x28;
    esp += 8; return; /* ret 4 */

    #undef fp_push
    #undef fp_pop
    #undef fp_top
    #undef fp_st
    #undef fp_st1
}
