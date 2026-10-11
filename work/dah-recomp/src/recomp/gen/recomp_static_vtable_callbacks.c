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

/* BEGIN RETAIL VTABLE GAP BODIES */
/**
 * sub_000127D0
 * Original: 0x000127D0 - 0x000127D5 (5 bytes, 1 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_000127D0(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_000127D0: ;
    g_seh_ebp = ebp; sub_000117D0(); return; /* tail jmp 0x000117D0 */

}

/**
 * sub_000127E0
 * Original: 0x000127E0 - 0x000127FE (30 bytes, 11 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_000127E0(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_000127E0: ;
    PUSH32(esp, esi);
    esi = ecx;
    PUSH32(esp, 0x000127E8u); sub_00012750(); /* call 0x00012750 */

loc_000127E8: ;
    _fa = (uint32_t)(MEM8(esp + 8)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(esp + 8), 1 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_000127F8; /* je: equal / zero */

loc_000127EF: ;
    PUSH32(esp, esi);
    PUSH32(esp, 0x000127F5u); sub_0006B710(); /* call 0x0006B710 */

loc_000127F5: ;
    esp = esp + 4;

loc_000127F8: ;
    eax = esi;
    POP32(esp, esi);
    esp += 8; return; /* ret 4 */

}

/**
 * sub_00012900
 * Original: 0x00012900 - 0x0001298A (138 bytes, 43 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00012900(void)
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

loc_00012900: ;
    eax = MEM32(esp + 4);
    esp = esp - 0xC;
    PUSH32(esp, esi);
    PUSH32(esp, eax);
    esi = ecx;
    PUSH32(esp, 0x00012910u); sub_00015660(); /* call 0x00015660 */

loc_00012910: ;
    _fa = (uint32_t)(MEM8(esi + 0x12C)) & 0xFFu; _fb = (uint32_t)(8) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(esi + 0x12C), 8 (8-bit) */
    ecx = MEM32(esi + 0x324);
    if (TEST_Z(_fa, _fb)) goto loc_00012973; /* je: equal / zero */

loc_0001291F: ;
    edx = MEM32(ecx);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 1);
    PUSH32(esp, 1);
    { uint32_t _icall_target = MEM32(edx + 0x4C); PUSH32(esp, 0x00012928u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00012928: ;
    eax = MEM32(esi + 0x12C);
    edx = MEM32(esi + 0x18);
    eax = eax & 0xFFFFFFFBu;
    ecx = esi + 0x18;
    eax = eax | 3;
    MEM32(esi + 0x12C) = eax;
    { uint32_t _icall_esp = g_esp;
    { uint32_t _icall_target = MEM32(edx); PUSH32(esp, 0x00012942u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00012942: ;
    ecx = MEM32(eax);
    MEM32(esp + 4) = ecx;
    edx = MEM32(eax + 4);
    ecx = MEM32(esi + 0x324);
    MEM32(esp + 8) = edx;
    fp_push(MEMF(eax + 8)); /* fld float */
    fp_top() = fp_top() + MEMF(0x225C28); /* fadd dword ptr [0x225c28] */
    edx = esp + 4;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, edx);
    MEMF(esp + 0x10) = (float)fp_top(); fp_pop(); /* fstp */
    eax = MEM32(ecx);
    { uint32_t _icall_target = MEM32(eax + 0x18); PUSH32(esp, 0x0001296Cu); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_0001296C: ;
    POP32(esp, esi);
    esp = esp + 0xC;
    esp += 8; return; /* ret 4 */

loc_00012973: ;
    eax = MEM32(ecx);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 0);
    PUSH32(esp, 0);
    { uint32_t _icall_target = MEM32(eax + 0x4C); PUSH32(esp, 0x0001297Cu); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_0001297C: ;
    MEM32(esi + 0x12C) = MEM32(esi + 0x12C) & 0xFFFFFFFCu;
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
 * sub_00012A10
 * Original: 0x00012A10 - 0x00012A46 (54 bytes, 16 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00012A10(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00012A10: ;
    eax = MEM32(esp + 4);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0x1975BCED) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0x1975BCED (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_00012A20; /* jne: not equal / not zero */

loc_00012A1B: ;
    SET_LO8(eax, 1);
    esp += 8; return; /* ret 4 */

loc_00012A20: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0xB405C7B6u) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0xB405C7B6u (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_00012A1B; /* je: equal / zero */

loc_00012A27: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0x883240FCu) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0x883240FCu (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_00012A1B; /* je: equal / zero */

loc_00012A2E: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0x38082939) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0x38082939 (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_00012A1B; /* je: equal / zero */

loc_00012A35: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0xA75FFAEBu) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0xA75FFAEBu (32-bit) */
    SET_LO8(eax, (CMP_EQ(_fa, _fb)) ? 1 : 0); /* sete */
    esp += 8; return; /* ret 4 */

}

/**
 * sub_00016280
 * Original: 0x00016280 - 0x0001629E (30 bytes, 11 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00016280(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00016280: ;
    PUSH32(esp, esi);
    esi = ecx;
    PUSH32(esp, 0x00016288u); sub_000161F0(); /* call 0x000161F0 */

loc_00016288: ;
    _fa = (uint32_t)(MEM8(esp + 8)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(esp + 8), 1 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00016298; /* je: equal / zero */

loc_0001628F: ;
    PUSH32(esp, esi);
    PUSH32(esp, 0x00016295u); sub_0006B710(); /* call 0x0006B710 */

loc_00016295: ;
    esp = esp + 4;

loc_00016298: ;
    eax = esi;
    POP32(esp, esi);
    esp += 8; return; /* ret 4 */

}

/**
 * sub_0001ED00
 * Original: 0x0001ED00 - 0x0001ED24 (36 bytes, 12 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0001ED00(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_0001ED00: ;
    PUSH32(esp, esi);
    esi = ecx;
    MEM32(esi) = 0x227394;
    PUSH32(esp, 0x0001ED0Eu); sub_0001EBF0(); /* call 0x0001EBF0 */

loc_0001ED0E: ;
    _fa = (uint32_t)(MEM8(esp + 8)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(esp + 8), 1 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0001ED1E; /* je: equal / zero */

loc_0001ED15: ;
    PUSH32(esp, esi);
    PUSH32(esp, 0x0001ED1Bu); sub_0006B710(); /* call 0x0006B710 */

loc_0001ED1B: ;
    esp = esp + 4;

loc_0001ED1E: ;
    eax = esi;
    POP32(esp, esi);
    esp += 8; return; /* ret 4 */

}

/**
 * sub_0001F300
 * Original: 0x0001F300 - 0x0001F324 (36 bytes, 12 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0001F300(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_0001F300: ;
    PUSH32(esp, esi);
    esi = ecx;
    MEM32(esi) = 0x2273CC;
    PUSH32(esp, 0x0001F30Eu); sub_0001EBF0(); /* call 0x0001EBF0 */

loc_0001F30E: ;
    _fa = (uint32_t)(MEM8(esp + 8)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(esp + 8), 1 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0001F31E; /* je: equal / zero */

loc_0001F315: ;
    PUSH32(esp, esi);
    PUSH32(esp, 0x0001F31Bu); sub_0006B710(); /* call 0x0006B710 */

loc_0001F31B: ;
    esp = esp + 4;

loc_0001F31E: ;
    eax = esi;
    POP32(esp, esi);
    esp += 8; return; /* ret 4 */

}

/**
 * sub_0001F400
 * Original: 0x0001F400 - 0x0001F424 (36 bytes, 12 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0001F400(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_0001F400: ;
    PUSH32(esp, esi);
    esi = ecx;
    MEM32(esi) = 0x2273E8;
    PUSH32(esp, 0x0001F40Eu); sub_0001EBF0(); /* call 0x0001EBF0 */

loc_0001F40E: ;
    _fa = (uint32_t)(MEM8(esp + 8)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(esp + 8), 1 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0001F41E; /* je: equal / zero */

loc_0001F415: ;
    PUSH32(esp, esi);
    PUSH32(esp, 0x0001F41Bu); sub_0006B710(); /* call 0x0006B710 */

loc_0001F41B: ;
    esp = esp + 4;

loc_0001F41E: ;
    eax = esi;
    POP32(esp, esi);
    esp += 8; return; /* ret 4 */

}

/**
 * sub_0001F500
 * Original: 0x0001F500 - 0x0001F657 (343 bytes, 127 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0001F500(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_0001F500: ;
    esp = esp - 0x50;
    PUSH32(esp, esi);
    esi = MEM32(esp + 0x58);
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(esi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test esi, esi (32-bit) */
    PUSH32(esp, edi);
    edi = ecx;
    if (TEST_Z(_fa, _fb)) goto loc_0001F64D; /* je: equal / zero */

loc_0001F513: ;
    eax = MEM32(esi);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0x9C519AA2u) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0x9C519AA2u (32-bit) */
    PUSH32(esp, ebx);
    if (CMP_A(_fa, _fb)) goto loc_0001F606; /* ja: above (unsigned >) */

loc_0001F521: ;
    if (CMP_EQ(_fa, _fb)) goto loc_0001F59B; /* je: equal / zero */

loc_0001F523: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0x15118CEB) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0x15118CEB (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_0001F534; /* je: equal / zero */

loc_0001F52A: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0x4ED3433F) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0x4ED3433F (32-bit) */
    goto loc_0001F60B;

loc_0001F534: ;
    eax = MEM32(esp + 0x64);
    eax = MEM32(eax + 0x14);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0xFFFFFFFFu) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0xFFFFFFFFu (32-bit) */
    PUSH32(esp, 1);
    if (CMP_EQ(_fa, _fb)) goto loc_0001F573; /* je: equal / zero */

loc_0001F542: ;
    ecx = esp + 0x68;
    PUSH32(esp, ecx);
    ecx = esp + 0x14;
    MEM32(esp + 0x6C) = eax;
    PUSH32(esp, 0x0001F554u); sub_00041780(); /* call 0x00041780 */

loc_0001F554: ;
    PUSH32(esp, eax);
    PUSH32(esp, esi);
    ecx = edi;
    PUSH32(esp, 0x0001F55Du); sub_0001E9F0(); /* call 0x0001E9F0 */

loc_0001F55D: ;
    ecx = esp + 0xC;
    SET_LO8(ebx, LO8(eax));
    PUSH32(esp, 0x0001F568u); sub_00029B30(); /* call 0x00029B30 */

loc_0001F568: ;
    SET_LO8(eax, LO8(ebx));
    POP32(esp, ebx);
    POP32(esp, edi);
    POP32(esp, esi);
    esp = esp + 0x50;
    esp += 12; return; /* ret 8 */

loc_0001F573: ;
    ecx = esp + 0x20;
    PUSH32(esp, 0x0001F57Cu); sub_00041730(); /* call 0x00041730 */

loc_0001F57C: ;
    PUSH32(esp, eax);
    PUSH32(esp, esi);
    ecx = edi;
    PUSH32(esp, 0x0001F585u); sub_0001E9F0(); /* call 0x0001E9F0 */

loc_0001F585: ;
    ecx = esp + 0x1C;
    SET_LO8(ebx, LO8(eax));
    PUSH32(esp, 0x0001F590u); sub_00029B30(); /* call 0x00029B30 */

loc_0001F590: ;
    SET_LO8(eax, LO8(ebx));
    POP32(esp, ebx);
    POP32(esp, edi);
    POP32(esp, esi);
    esp = esp + 0x50;
    esp += 12; return; /* ret 8 */

loc_0001F59B: ;
    ecx = MEM32(esp + 0x64);
    eax = MEM32(ecx + 0x14);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0xFFFFFFFFu) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0xFFFFFFFFu (32-bit) */
    PUSH32(esp, 1);
    if (CMP_EQ(_fa, _fb)) goto loc_0001F5DA; /* je: equal / zero */

loc_0001F5A9: ;
    edx = esp + 0x64;
    PUSH32(esp, edx);
    ecx = esp + 0x34;
    MEM32(esp + 0x68) = eax;
    PUSH32(esp, 0x0001F5BBu); sub_00041780(); /* call 0x00041780 */

loc_0001F5BB: ;
    PUSH32(esp, eax);
    PUSH32(esp, esi);
    ecx = edi;
    PUSH32(esp, 0x0001F5C4u); sub_0001E9F0(); /* call 0x0001E9F0 */

loc_0001F5C4: ;
    ecx = esp + 0x2C;
    SET_LO8(ebx, LO8(eax));
    PUSH32(esp, 0x0001F5CFu); sub_00029B30(); /* call 0x00029B30 */

loc_0001F5CF: ;
    SET_LO8(eax, LO8(ebx));
    POP32(esp, ebx);
    POP32(esp, edi);
    POP32(esp, esi);
    esp = esp + 0x50;
    esp += 12; return; /* ret 8 */

loc_0001F5DA: ;
    ecx = ecx + 4;
    PUSH32(esp, ecx);
    ecx = esp + 0x44;
    PUSH32(esp, 0x0001F5E7u); sub_00041740(); /* call 0x00041740 */

loc_0001F5E7: ;
    PUSH32(esp, eax);
    PUSH32(esp, esi);
    ecx = edi;
    PUSH32(esp, 0x0001F5F0u); sub_0001E9F0(); /* call 0x0001E9F0 */

loc_0001F5F0: ;
    ecx = esp + 0x3C;
    SET_LO8(ebx, LO8(eax));
    PUSH32(esp, 0x0001F5FBu); sub_00029B30(); /* call 0x00029B30 */

loc_0001F5FB: ;
    SET_LO8(eax, LO8(ebx));
    POP32(esp, ebx);
    POP32(esp, edi);
    POP32(esp, esi);
    esp = esp + 0x50;
    esp += 12; return; /* ret 8 */

loc_0001F606: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0xD6E30158u) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0xD6E30158u (32-bit) */

loc_0001F60B: ;
    if (_flags /* je: equal / zero */) goto loc_0001F623;

loc_0001F60D: ;
    eax = MEM32(esp + 0x64);
    PUSH32(esp, eax);
    PUSH32(esp, esi);
    ecx = edi;
    PUSH32(esp, 0x0001F61Au); sub_0001E4D0(); /* call 0x0001E4D0 */

loc_0001F61A: ;
    POP32(esp, ebx);
    POP32(esp, edi);
    POP32(esp, esi);
    esp = esp + 0x50;
    esp += 12; return; /* ret 8 */

loc_0001F623: ;
    PUSH32(esp, 1);
    ecx = esp + 0x50;
    PUSH32(esp, 0x0001F62Eu); sub_00041730(); /* call 0x00041730 */

loc_0001F62E: ;
    PUSH32(esp, eax);
    PUSH32(esp, esi);
    ecx = edi;
    PUSH32(esp, 0x0001F637u); sub_0001E9F0(); /* call 0x0001E9F0 */

loc_0001F637: ;
    ecx = esp + 0x4C;
    SET_LO8(ebx, LO8(eax));
    PUSH32(esp, 0x0001F642u); sub_00029B30(); /* call 0x00029B30 */

loc_0001F642: ;
    SET_LO8(eax, LO8(ebx));
    POP32(esp, ebx);
    POP32(esp, edi);
    POP32(esp, esi);
    esp = esp + 0x50;
    esp += 12; return; /* ret 8 */

loc_0001F64D: ;
    POP32(esp, edi);
    SET_LO8(eax, 0); /* xor self */
    POP32(esp, esi);
    esp = esp + 0x50;
    esp += 12; return; /* ret 8 */

}

/**
 * sub_0001F800
 * Original: 0x0001F800 - 0x0001F824 (36 bytes, 12 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0001F800(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_0001F800: ;
    PUSH32(esp, esi);
    esi = ecx;
    MEM32(esi) = 0x227420;
    PUSH32(esp, 0x0001F80Eu); sub_0001EBF0(); /* call 0x0001EBF0 */

loc_0001F80E: ;
    _fa = (uint32_t)(MEM8(esp + 8)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(esp + 8), 1 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0001F81E; /* je: equal / zero */

loc_0001F815: ;
    PUSH32(esp, esi);
    PUSH32(esp, 0x0001F81Bu); sub_0006B710(); /* call 0x0006B710 */

loc_0001F81B: ;
    esp = esp + 4;

loc_0001F81E: ;
    eax = esi;
    POP32(esp, esi);
    esp += 8; return; /* ret 4 */

}

/**
 * sub_0001F900
 * Original: 0x0001F900 - 0x0001F924 (36 bytes, 12 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0001F900(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_0001F900: ;
    PUSH32(esp, esi);
    esi = ecx;
    MEM32(esi) = 0x22744C;
    PUSH32(esp, 0x0001F90Eu); sub_0001EBF0(); /* call 0x0001EBF0 */

loc_0001F90E: ;
    _fa = (uint32_t)(MEM8(esp + 8)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(esp + 8), 1 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0001F91E; /* je: equal / zero */

loc_0001F915: ;
    PUSH32(esp, esi);
    PUSH32(esp, 0x0001F91Bu); sub_0006B710(); /* call 0x0006B710 */

loc_0001F91B: ;
    esp = esp + 4;

loc_0001F91E: ;
    eax = esi;
    POP32(esp, esi);
    esp += 8; return; /* ret 4 */

}

/**
 * sub_00022580
 * Original: 0x00022580 - 0x000225CF (79 bytes, 22 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00022580(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00022580: ;
    PUSH32(esp, esi);
    esi = ecx;
    ecx = MEM32(esi + 0xA4);
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, ecx (32-bit) */
    MEM32(esi) = 0x22791C;
    MEM32(esi + 0x48) = 0x227914;
    if (TEST_Z(_fa, _fb)) goto loc_000225A1; /* je: equal / zero */

loc_0002259A: ;
    eax = MEM32(ecx);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 1);
    { uint32_t _icall_target = MEM32(eax + 8); PUSH32(esp, 0x000225A1u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_000225A1: ;
    MEM32(esi + 0xA4) = 0;
    ecx = esi;
    MEM32(esi + 0x48) = 0x226F44;
    PUSH32(esp, 0x000225B9u); sub_0001AF40(); /* call 0x0001AF40 */

loc_000225B9: ;
    _fa = (uint32_t)(MEM8(esp + 8)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(esp + 8), 1 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_000225C9; /* je: equal / zero */

loc_000225C0: ;
    PUSH32(esp, esi);
    PUSH32(esp, 0x000225C6u); sub_0006B710(); /* call 0x0006B710 */

loc_000225C6: ;
    esp = esp + 4;

loc_000225C9: ;
    eax = esi;
    POP32(esp, esi);
    esp += 8; return; /* ret 4 */

}

/**
 * sub_00024FF0
 * Original: 0x00024FF0 - 0x00025038 (72 bytes, 21 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00024FF0(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00024FF0: ;
    PUSH32(esp, esi);
    esi = ecx;
    ecx = MEM32(esi + 0xD0);
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, ecx (32-bit) */
    MEM32(esi) = 0x227A50;
    MEM32(esi + 0x48) = 0x227A48;
    if (TEST_Z(_fa, _fb)) goto loc_00025011; /* je: equal / zero */

loc_0002500A: ;
    eax = MEM32(ecx);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 1);
    { uint32_t _icall_target = MEM32(eax + 8); PUSH32(esp, 0x00025011u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00025011: ;
    ecx = esi;
    MEM32(esi + 0xD0) = 0;
    PUSH32(esp, 0x00025022u); sub_000221C0(); /* call 0x000221C0 */

loc_00025022: ;
    _fa = (uint32_t)(MEM8(esp + 8)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(esp + 8), 1 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00025032; /* je: equal / zero */

loc_00025029: ;
    PUSH32(esp, esi);
    PUSH32(esp, 0x0002502Fu); sub_0006B710(); /* call 0x0006B710 */

loc_0002502F: ;
    esp = esp + 4;

loc_00025032: ;
    eax = esi;
    POP32(esp, esi);
    esp += 8; return; /* ret 4 */

}

/**
 * sub_00026860
 * Original: 0x00026860 - 0x00026878 (24 bytes, 8 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00026860(void)
{

loc_00026860: ;
    eax = MEM32(esp + 4);
    PUSH32(esp, esi);
    PUSH32(esp, eax);
    esi = ecx;
    PUSH32(esp, 0x0002686Du); sub_00028290(); /* call 0x00028290 */

loc_0002686D: ;
    MEM32(esi + 0x60) = 0;
    POP32(esp, esi);
    esp += 8; return; /* ret 4 */

}

/**
 * sub_0002BFB0
 * Original: 0x0002BFB0 - 0x0002BFE2 (50 bytes, 14 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0002BFB0(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_0002BFB0: ;
    PUSH32(esp, esi);
    esi = ecx;
    MEM32(esi) = 0x2281D8;
    MEM32(esi + 0x48) = 0x2281CC;
    MEM32(esi + 0x48) = 0x226F44;
    PUSH32(esp, 0x0002BFCCu); sub_0001AF40(); /* call 0x0001AF40 */

loc_0002BFCC: ;
    _fa = (uint32_t)(MEM8(esp + 8)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(esp + 8), 1 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0002BFDC; /* je: equal / zero */

loc_0002BFD3: ;
    PUSH32(esp, esi);
    PUSH32(esp, 0x0002BFD9u); sub_0006B710(); /* call 0x0006B710 */

loc_0002BFD9: ;
    esp = esp + 4;

loc_0002BFDC: ;
    eax = esi;
    POP32(esp, esi);
    esp += 8; return; /* ret 4 */

}

/**
 * sub_0002C6E0
 * Original: 0x0002C6E0 - 0x0002C851 (369 bytes, 121 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0002C6E0(void)
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

loc_0002C6E0: ;
    esp = esp - 8;
    PUSH32(esp, ebx);
    ebx = MEM32(esp + 0x10);
    PUSH32(esp, esi);
    PUSH32(esp, ebx);
    esi = ecx;
    PUSH32(esp, 0x0002C6F1u); sub_0001B670(); /* call 0x0001B670 */

loc_0002C6F1: ;
    fp_push(MEMF(esi + 0x88)); /* fld float */
    fp_top() = fp_top() - MEMF(esp + 0x14); /* fsub dword ptr [esp + 0x14] */
    ecx = esi + 0x70;
    MEMF(esi + 0x88) = (float)fp_top(); fp_pop(); /* fstp */
    fp_push(MEMF(esi + 0x94)); /* fld float */
    fp_top() = fp_top() - MEMF(esp + 0x14); /* fsub dword ptr [esp + 0x14] */
    MEMF(esi + 0x94) = (float)fp_top(); fp_pop(); /* fstp */
    fp_push(MEMF(esi + 0xA8)); /* fld float */
    fp_top() = fp_top() - MEMF(esp + 0x14); /* fsub dword ptr [esp + 0x14] */
    MEMF(esi + 0xA8) = (float)fp_top(); fp_pop(); /* fstp */
    PUSH32(esp, 0x0002C729u); sub_0010BC40(); /* call 0x0010BC40 */

loc_0002C729: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    MEM32(esi + 0x6C) = eax;
    if (TEST_Z(_fa, _fb)) goto loc_0002C73B; /* je: equal / zero */

loc_0002C730: ;
    edx = MEM32(eax);
    ecx = eax;
    { uint32_t _icall_esp = g_esp;
    { uint32_t _icall_target = MEM32(edx + 0x40); PUSH32(esp, 0x0002C737u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_0002C737: ;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_0002C772; /* jne: not equal / not zero */

loc_0002C73B: ;
    eax = MEM32(esi);
    ecx = esi;
    { uint32_t _icall_esp = g_esp;
    { uint32_t _icall_target = MEM32(eax + 0x3C); PUSH32(esp, 0x0002C742u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_0002C742: ;
    SET_LO8(ecx, MEM8(eax + 0x599));
    _fa = (uint32_t)(LO8(ecx)) & 0xFFu; _fb = (uint32_t)(LO8(ecx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(ecx), LO8(ecx) (8-bit) */
    ecx = esi;
    if (TEST_Z(_fa, _fb)) goto loc_0002C760; /* je: equal / zero */

loc_0002C74E: ;
    PUSH32(esp, 0x33952CF);
    PUSH32(esp, 0x0002C758u); sub_0001B300(); /* call 0x0001B300 */

loc_0002C758: ;
    POP32(esp, esi);
    POP32(esp, ebx);
    esp = esp + 8;
    esp += 8; return; /* ret 4 */

loc_0002C760: ;
    PUSH32(esp, 0x5513A823);
    PUSH32(esp, 0x0002C76Au); sub_0001B300(); /* call 0x0001B300 */

loc_0002C76A: ;
    POP32(esp, esi);
    POP32(esp, ebx);
    esp = esp + 8;
    esp += 8; return; /* ret 4 */

loc_0002C772: ;
    edx = MEM32(esi);
    ecx = esi;
    { uint32_t _icall_esp = g_esp;
    { uint32_t _icall_target = MEM32(edx + 0x3C); PUSH32(esp, 0x0002C779u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_0002C779: ;
    fp_push(MEMF(esi + 0x84)); /* fld float */
    g_fp_cmp = RECOMP_FCMP(fp_top(), MEMF(eax + 0x1F0)); fp_pop(); /* fcomp dword ptr [eax + 0x1f0] */
    ecx = esi;
    eax = (eax & 0xFFFF0000u) | (uint32_t)(uint16_t)(((g_fp_top & 7u) << 11) | (g_fp_cmp == 2 ? 0x4500u : g_fp_cmp < 0 ? 0x0100u : g_fp_cmp > 0 ? 0x0000u : 0x4000u)); /* fnstsw ax <- fpu status */
    _fa = (uint32_t)(HI8(eax)) & 0xFFu; _fb = (uint32_t)(0x41) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test HI8(eax), 0x41 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0002C7E8; /* je: equal / zero */

loc_0002C78E: ;
    eax = MEM32(esi);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, ebp);
    PUSH32(esp, edi);
    { uint32_t _icall_target = MEM32(eax + 0x3C); PUSH32(esp, 0x0002C795u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_0002C795: ;
    edx = MEM32(esi);
    ecx = esi;
    edi = eax + 0x18;
    { uint32_t _icall_esp = g_esp;
    { uint32_t _icall_target = MEM32(edx + 0x3C); PUSH32(esp, 0x0002C79Fu); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_0002C79F: ;
    eax = MEM32(eax + 0x1EC);
    edx = MEM32(esi);
    ecx = esi;
    MEM32(esp + 0x14) = eax;
    { uint32_t _icall_esp = g_esp;
    { uint32_t _icall_target = MEM32(edx + 0x3C); PUSH32(esp, 0x0002C7B0u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_0002C7B0: ;
    ecx = MEM32(esi + 0x6C);
    eax = MEM32(eax + 0x1EC);
    edx = MEM32(ecx);
    MEM32(esp + 0x10) = eax;
    { uint32_t _icall_esp = g_esp;
    { uint32_t _icall_target = MEM32(edx + 0x1C); PUSH32(esp, 0x0002C7C2u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_0002C7C2: ;
    ebp = eax;
    eax = MEM32(edi);
    ecx = edi;
    { uint32_t _icall_esp = g_esp;
    { uint32_t _icall_target = MEM32(eax); PUSH32(esp, 0x0002C7CAu); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_0002C7CA: ;
    edx = ebp;
    ecx = eax;
    PUSH32(esp, 0x0002C7D3u); sub_000D4F40(); /* call 0x000D4F40 */

loc_0002C7D3: ;
    fp_push(MEMF(esp + 0x10)); /* fld float */
    fp_top() = fp_top() * MEMF(esp + 0x14); /* fmul dword ptr [esp + 0x14] */
    POP32(esp, edi);
    POP32(esp, ebp);
    ecx = esi;
    g_fp_cmp = RECOMP_FCMP(fp_top(), fp_st1()); fp_pop(); fp_pop(); /* fcompp  */
    eax = (eax & 0xFFFF0000u) | (uint32_t)(uint16_t)(((g_fp_top & 7u) << 11) | (g_fp_cmp == 2 ? 0x4500u : g_fp_cmp < 0 ? 0x0100u : g_fp_cmp > 0 ? 0x0000u : 0x4000u)); /* fnstsw ax <- fpu status */
    _fa = (uint32_t)(HI8(eax)) & 0xFFu; _fb = (uint32_t)(5) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test HI8(eax), 5 (8-bit) */
    if (RECOMP_PARITY8((_fa) & (_fb))) goto loc_0002C7FA; /* jp: parity */

loc_0002C7E8: ;
    PUSH32(esp, 0x8F651465u);
    PUSH32(esp, 0x0002C7F2u); sub_0001B300(); /* call 0x0001B300 */

loc_0002C7F2: ;
    POP32(esp, esi);
    POP32(esp, ebx);
    esp = esp + 8;
    esp += 8; return; /* ret 4 */

loc_0002C7FA: ;
    fp_push(MEMF(esp + 0x14)); /* fld float */
    fp_top() = fp_top() + MEMF(esi + 0x84); /* fadd dword ptr [esi + 0x84] */
    MEMF(esi + 0x84) = (float)fp_top(); fp_pop(); /* fstp */
    fp_push(MEMF(esp + 0x14)); /* fld float */
    fp_top() = fp_top() + MEMF(esi + 0x80); /* fadd dword ptr [esi + 0x80] */
    MEMF(esi + 0x80) = (float)fp_top(); fp_pop(); /* fstp */
    PUSH32(esp, 0x0002C81Fu); sub_0002C330(); /* call 0x0002C330 */

loc_0002C81F: ;
    PUSH32(esp, ebx);
    ecx = esi + 0x48;
    PUSH32(esp, 0x0002C828u); sub_0003A3C0(); /* call 0x0003A3C0 */

loc_0002C828: ;
    _fa = (uint32_t)(MEM32(esi + 0x50)) & 0xFFFFFFFFu; _fb = (uint32_t)(5) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(esi + 0x50), 5 (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_0002C849; /* je: equal / zero */

loc_0002C82E: ;
    ecx = MEM32(esi + 0x6C);
    edx = MEM32(ecx);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 1);
    PUSH32(esp, 0);
    { uint32_t _icall_target = MEM32(edx + 0x1C); PUSH32(esp, 0x0002C83Au); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_0002C83A: ;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, eax);
    eax = MEM32(esi);
    ecx = esi;
    { uint32_t _icall_target = MEM32(eax + 0x3C); PUSH32(esp, 0x0002C842u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_0002C842: ;
    ecx = eax;
    PUSH32(esp, 0x0002C849u); sub_00022E10(); /* call 0x00022E10 */

loc_0002C849: ;
    POP32(esp, esi);
    POP32(esp, ebx);
    esp = esp + 8;
    esp += 8; return; /* ret 4 */

    #undef fp_push
    #undef fp_pop
    #undef fp_top
    #undef fp_st
    #undef fp_st1
}

/**
 * sub_00033060
 * Original: 0x00033060 - 0x00033202 (418 bytes, 127 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00033060(void)
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

loc_00033060: ;
    esp = esp - 0x44;
    PUSH32(esp, ebx);
    PUSH32(esp, ebp);
    ebp = MEM32(esp + 0x50);
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    PUSH32(esp, ebp);
    esi = ecx;
    PUSH32(esp, 0x00033073u); sub_00032B90(); /* call 0x00032B90 */

loc_00033073: ;
    fp_push(MEMF(esp + 0x58)); /* fld float */
    fp_top() = fp_top() * MEMF(0x228850); /* fmul dword ptr [0x228850] */
    eax = MEM32(esi + 0x28);
    PUSH32(esp, 1);
    PUSH32(esp, ecx);
    MEMF(esp) = (float)fp_top(); fp_pop(); /* fstp */
    ebx = esi + 0x44;
    PUSH32(esp, eax);
    ecx = ebx;
    PUSH32(esp, 0x00033091u); sub_0005BC90(); /* call 0x0005BC90 */

loc_00033091: ;
    ecx = MEM32(esi + 0x70);
    edx = MEM32(ecx + 0x1C);
    ecx = MEM32(ebx);
    eax = MEM32(edx + 0x1AC);
    edi = ecx;
    PUSH32(esp, edi);
    MEM32(esi + 0x30) = eax;
    MEM32(esp + 0x5C) = ecx;
    PUSH32(esp, 0x000330AEu); sub_000D44D0(); /* call 0x000D44D0 */

loc_000330AE: ;
    MEMF(esp + 0x58) = (float)fp_top(); fp_pop(); /* fstp */
    PUSH32(esp, edi);
    PUSH32(esp, 0x000330B8u); sub_000D4420(); /* call 0x000D4420 */

loc_000330B8: ;
    MEMF(esi + 0x38) = (float)fp_top(); fp_pop(); /* fstp */
    edx = MEM32(esp + 0x58);
    edi = esi + 0x38;
    MEM32(edi + 4) = edx;
    MEM32(edi + 8) = 0;
    eax = MEM32(esi + 0x30);
    PUSH32(esp, eax);
    edx = edi;
    ecx = edi;
    PUSH32(esp, 0x000330D9u); sub_000D4A10(); /* call 0x000D4A10 */

loc_000330D9: ;
    eax = MEM32(esi + 0x70);
    edx = MEM32(eax + 0x18);
    ecx = eax + 0x18;
    { uint32_t _icall_esp = g_esp;
    { uint32_t _icall_target = MEM32(edx); PUSH32(esp, 0x000330E4u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_000330E4: ;
    ecx = MEM32(eax);
    MEM32(esp + 0x10) = ecx;
    edx = MEM32(eax + 4);
    ecx = MEM32(edi);
    MEM32(esp + 0x14) = edx;
    eax = MEM32(eax + 8);
    edx = MEM32(edi + 4);
    MEM32(esp + 0x20) = edx;
    MEM32(esp + 0x18) = eax;
    eax = MEM32(edi + 8);
    edx = esp + 0x1C;
    MEM32(esp + 0x1C) = ecx;
    PUSH32(esp, ebp);
    ecx = edx;
    MEM32(esp + 0x28) = eax;
    PUSH32(esp, 0x00033118u); sub_000D4A10(); /* call 0x000D4A10 */

loc_00033118: ;
    ecx = esp + 0x1C;
    edx = esp + 0x10;
    PUSH32(esp, ecx);
    ecx = edx;
    PUSH32(esp, 0x00033128u); sub_000D4770(); /* call 0x000D4770 */

loc_00033128: ;
    eax = MEM32(esi + 0x70);
    edx = MEM32(eax + 0x12C);
    edx = edx >> 2;
    _fa = (uint32_t)(LO8(edx)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(edx), 1 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0003315D; /* je: equal / zero */

loc_00033139: ;
    ecx = MEM32(eax + 0x1C);
    fp_push(MEMF(ecx + 0x48C)); /* fld float */
    PUSH32(esp, ebp);
    fp_top() = fp_top() + MEMF(eax + 0x328); /* fadd dword ptr [eax + 0x328] */
    PUSH32(esp, ecx);
    edi = esi + 0x74;
    ecx = edi;
    MEMF(esp) = (float)fp_top(); fp_pop(); /* fstp */
    PUSH32(esp, 0x00033157u); sub_0005BC30(); /* call 0x0005BC30 */

loc_00033157: ;
    edx = MEM32(edi);
    MEM32(esp + 0x18) = edx;

loc_0003315D: ;
    ecx = MEM32(esi + 0x70);
    eax = MEM32(ecx + 0x18);
    ecx = ecx + 0x18;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 1);
    edx = esp + 0x14;
    PUSH32(esp, edx);
    { uint32_t _icall_target = MEM32(eax + 8); PUSH32(esp, 0x00033170u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00033170: ;
    fp_push(MEMF(0x246B14)); /* fld float */
    fp_top() = fp_top() + MEMF(ebx); /* fadd dword ptr [ebx] */
    PUSH32(esp, ecx);
    edx = esp + 0x2C;
    ecx = esp + 0x38;
    MEMF(esp) = (float)fp_top(); fp_pop(); /* fstp */
    MEM32(esp + 0x2C) = 0;
    MEM32(esp + 0x30) = 0;
    MEM32(esp + 0x34) = 0x3F800000;
    PUSH32(esp, 0x000331A1u); sub_000D55D0(); /* call 0x000D55D0 */

loc_000331A1: ;
    eax = MEM32(esi + 0x70);
    eax = MEM32(eax + 0x1C);
    MEM32(esp + 0x28) = 0xBF800000u;
    MEM32(esp + 0x2C) = 0;
    MEM32(esp + 0x30) = 0;
    ecx = MEM32(eax + 0x490);
    PUSH32(esp, ecx);
    edx = esp + 0x2C;
    ecx = esp + 0x48;
    PUSH32(esp, 0x000331D3u); sub_000D55D0(); /* call 0x000D55D0 */

loc_000331D3: ;
    edx = esp + 0x34;
    PUSH32(esp, edx);
    edx = esp + 0x48;
    ecx = esp + 0x38;
    PUSH32(esp, 0x000331E5u); sub_000D5A00(); /* call 0x000D5A00 */

loc_000331E5: ;
    esi = MEM32(esi + 0x70);
    eax = MEM32(esi + 0x18);
    ecx = esi + 0x18;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 1);
    edx = esp + 0x38;
    PUSH32(esp, edx);
    { uint32_t _icall_target = MEM32(eax + 0xC); PUSH32(esp, 0x000331F8u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_000331F8: ;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebp);
    POP32(esp, ebx);
    esp = esp + 0x44;
    esp += 8; return; /* ret 4 */

    #undef fp_push
    #undef fp_pop
    #undef fp_top
    #undef fp_st
    #undef fp_st1
}

/**
 * sub_0003C880
 * Original: 0x0003C880 - 0x0003C892 (18 bytes, 5 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0003C880(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_0003C880: ;
    ecx = MEM32(esp + 4);
    eax = 0; /* xor self */
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(0x1DE7E3DA) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp ecx, 0x1DE7E3DA (32-bit) */
    SET_LO8(eax, (CMP_EQ(_fa, _fb)) ? 1 : 0); /* sete */
    esp += 8; return; /* ret 4 */

}

/**
 * sub_0003F9D0
 * Original: 0x0003F9D0 - 0x0003FA8F (191 bytes, 61 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0003F9D0(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_0003F9D0: ;
    PUSH32(esp, esi);
    esi = ecx;
    eax = MEM32(esi + 4);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_0003FA8D; /* jne: not equal / not zero */

loc_0003F9DE: ;
    eax = MEM32(esi + 0xC);
    MEM32(eax + 0xD0) = MEM32(eax + 0xD0) | 0x100;
    eax = MEM32(esi + 0x14);
    ecx = MEM32(eax + 0x2C);
    ecx = ecx >> 5;
    _fa = (uint32_t)(LO8(ecx)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(ecx), 1 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0003FA01; /* je: equal / zero */

loc_0003F9F9: ;
    MEM32(eax + 0x2C) = MEM32(eax + 0x2C) & 0xFFFFFFDFu;
    MEM32(esi + 0x60) = MEM32(esi + 0x60) | 8;

loc_0003FA01: ;
    ecx = MEM32(esi + 0x2C);
    eax = 0; /* xor self */
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, ecx (32-bit) */
    if (CMP_LE(_fas & _fbs, 0)) goto loc_0003FA21; /* jle: less or equal (signed <=) */

loc_0003FA0A: ;
    edx = 0x20;
    /* nop */

loc_0003FA10: ;
    ecx = MEM32(esi + 0x34);
    ecx = MEM32(ecx + eax * 4);
    MEM32(ecx + 0x2C) = MEM32(ecx + 0x2C) | edx;
    ecx = MEM32(esi + 0x2C);
    eax = eax + 1;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fas = (int32_t)(int32_t)_fa; /* inc flags snapshot */
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, ecx (32-bit) */
    if (CMP_L(_fas, _fbs)) goto loc_0003FA10; /* jl: less (signed <) */

loc_0003FA21: ;
    edx = MEM32(esi + 0x70);
    ecx = esi + 0x70;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 1);
    PUSH32(esp, 1);
    { uint32_t _icall_target = MEM32(edx + 0x40); PUSH32(esp, 0x0003FA2Eu); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_0003FA2E: ;
    ecx = MEM32(esi + 0xC);
    eax = MEM32(ecx);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 0);
    PUSH32(esp, 1);
    PUSH32(esp, 0);
    PUSH32(esp, 0);
    PUSH32(esp, 0);
    PUSH32(esp, 0xC35449A3u);
    { uint32_t _icall_target = MEM32(eax + 0x6C); PUSH32(esp, 0x0003FA45u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_0003FA45: ;
    ecx = MEM32(esi + 8);
    edx = MEM32(ecx + 0xD0);
    ecx = MEM32(esi + 0x10);
    PUSH32(esp, 0x3F800000);
    PUSH32(esp, edx);
    PUSH32(esp, 0x0003FA5Cu); sub_00107C00(); /* call 0x00107C00 */

loc_0003FA5C: ;
    eax = MEM32(esi + 8);
    ecx = MEM32(eax + 0xD4);
    PUSH32(esp, 0);
    PUSH32(esp, ecx);
    ecx = MEM32(esi + 0x10);
    edx = esi + 0xB8;
    PUSH32(esp, edx);
    PUSH32(esp, 0x0003FA77u); sub_00107C40(); /* call 0x00107C40 */

loc_0003FA77: ;
    eax = MEM32(esi + 8);
    ecx = MEM32(eax + 0xC4);
    MEM32(esi + 0xB0) = ecx;
    MEM32(esi + 4) = 1;

loc_0003FA8D: ;
    POP32(esp, esi);
    esp += 4; return; /* ret */

}

/**
 * sub_00043480
 * Original: 0x00043480 - 0x0004348B (11 bytes, 3 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00043480(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_00043480: ;
    ecx = MEM32(ecx + 0x48);
    eax = MEM32(ecx);
    g_seh_ebp = ebp; RECOMP_ITAIL(MEM32(eax + 0x84)); return; /* indirect tail jmp */

}

/**
 * sub_00043490
 * Original: 0x00043490 - 0x0004349B (11 bytes, 3 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00043490(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_00043490: ;
    ecx = MEM32(ecx + 0x48);
    eax = MEM32(ecx);
    g_seh_ebp = ebp; RECOMP_ITAIL(MEM32(eax + 0x88)); return; /* indirect tail jmp */

}

/**
 * sub_000434A0
 * Original: 0x000434A0 - 0x000434AB (11 bytes, 3 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_000434A0(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_000434A0: ;
    ecx = MEM32(ecx + 0x48);
    eax = MEM32(ecx);
    g_seh_ebp = ebp; RECOMP_ITAIL(MEM32(eax + 0x8C)); return; /* indirect tail jmp */

}

/**
 * sub_000434B0
 * Original: 0x000434B0 - 0x000434BB (11 bytes, 3 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_000434B0(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_000434B0: ;
    ecx = MEM32(ecx + 0x48);
    eax = MEM32(ecx);
    g_seh_ebp = ebp; RECOMP_ITAIL(MEM32(eax + 0x90)); return; /* indirect tail jmp */

}

/**
 * sub_000434C0
 * Original: 0x000434C0 - 0x000434CB (11 bytes, 3 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_000434C0(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_000434C0: ;
    ecx = MEM32(ecx + 0x48);
    eax = MEM32(ecx);
    g_seh_ebp = ebp; RECOMP_ITAIL(MEM32(eax + 0x94)); return; /* indirect tail jmp */

}

/**
 * sub_000434D0
 * Original: 0x000434D0 - 0x000434DB (11 bytes, 3 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_000434D0(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_000434D0: ;
    ecx = MEM32(ecx + 0x48);
    eax = MEM32(ecx);
    g_seh_ebp = ebp; RECOMP_ITAIL(MEM32(eax + 0x98)); return; /* indirect tail jmp */

}

/**
 * sub_000434E0
 * Original: 0x000434E0 - 0x000434E8 (8 bytes, 3 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_000434E0(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_000434E0: ;
    ecx = MEM32(ecx + 0x48);
    eax = MEM32(ecx);
    g_seh_ebp = ebp; RECOMP_ITAIL(MEM32(eax + 0x4C)); return; /* indirect tail jmp */

}

/**
 * sub_000434F0
 * Original: 0x000434F0 - 0x000434F8 (8 bytes, 3 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_000434F0(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_000434F0: ;
    ecx = MEM32(ecx + 0x48);
    eax = MEM32(ecx);
    g_seh_ebp = ebp; RECOMP_ITAIL(MEM32(eax + 0x54)); return; /* indirect tail jmp */

}

/**
 * sub_00043500
 * Original: 0x00043500 - 0x00043508 (8 bytes, 3 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00043500(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_00043500: ;
    ecx = MEM32(ecx + 0x48);
    eax = MEM32(ecx);
    g_seh_ebp = ebp; RECOMP_ITAIL(MEM32(eax + 0x48)); return; /* indirect tail jmp */

}

/**
 * sub_00043510
 * Original: 0x00043510 - 0x00043518 (8 bytes, 3 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00043510(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_00043510: ;
    ecx = MEM32(ecx + 0x48);
    eax = MEM32(ecx);
    g_seh_ebp = ebp; RECOMP_ITAIL(MEM32(eax + 0x50)); return; /* indirect tail jmp */

}

/**
 * sub_00043520
 * Original: 0x00043520 - 0x00043528 (8 bytes, 3 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00043520(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_00043520: ;
    ecx = MEM32(ecx + 0x48);
    eax = MEM32(ecx);
    g_seh_ebp = ebp; RECOMP_ITAIL(MEM32(eax + 0x40)); return; /* indirect tail jmp */

}

/**
 * sub_00043530
 * Original: 0x00043530 - 0x00043538 (8 bytes, 3 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00043530(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_00043530: ;
    ecx = MEM32(ecx + 0x48);
    eax = MEM32(ecx);
    g_seh_ebp = ebp; RECOMP_ITAIL(MEM32(eax + 0x38)); return; /* indirect tail jmp */

}

/**
 * sub_00043540
 * Original: 0x00043540 - 0x00043548 (8 bytes, 3 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00043540(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_00043540: ;
    ecx = MEM32(ecx + 0x48);
    eax = MEM32(ecx);
    g_seh_ebp = ebp; RECOMP_ITAIL(MEM32(eax + 0x34)); return; /* indirect tail jmp */

}

/**
 * sub_00043550
 * Original: 0x00043550 - 0x0004355B (11 bytes, 3 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00043550(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_00043550: ;
    ecx = MEM32(ecx + 0x48);
    eax = MEM32(ecx);
    g_seh_ebp = ebp; RECOMP_ITAIL(MEM32(eax + 0x9C)); return; /* indirect tail jmp */

}

/**
 * sub_00043560
 * Original: 0x00043560 - 0x0004356B (11 bytes, 3 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00043560(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_00043560: ;
    ecx = MEM32(ecx + 0x48);
    eax = MEM32(ecx);
    g_seh_ebp = ebp; RECOMP_ITAIL(MEM32(eax + 0xA0)); return; /* indirect tail jmp */

}

/**
 * sub_00043570
 * Original: 0x00043570 - 0x0004357B (11 bytes, 3 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00043570(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_00043570: ;
    ecx = MEM32(ecx + 0x48);
    eax = MEM32(ecx);
    g_seh_ebp = ebp; RECOMP_ITAIL(MEM32(eax + 0xA4)); return; /* indirect tail jmp */

}

/**
 * sub_00043580
 * Original: 0x00043580 - 0x0004358B (11 bytes, 3 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00043580(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_00043580: ;
    ecx = MEM32(ecx + 0x48);
    eax = MEM32(ecx);
    g_seh_ebp = ebp; RECOMP_ITAIL(MEM32(eax + 0xA8)); return; /* indirect tail jmp */

}

/**
 * sub_00043590
 * Original: 0x00043590 - 0x00043598 (8 bytes, 3 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00043590(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_00043590: ;
    ecx = MEM32(ecx + 0x48);
    eax = MEM32(ecx);
    g_seh_ebp = ebp; RECOMP_ITAIL(MEM32(eax + 0x68)); return; /* indirect tail jmp */

}

/**
 * sub_000435A0
 * Original: 0x000435A0 - 0x000435A8 (8 bytes, 3 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_000435A0(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_000435A0: ;
    ecx = MEM32(ecx + 0x48);
    eax = MEM32(ecx);
    g_seh_ebp = ebp; RECOMP_ITAIL(MEM32(eax + 0x6C)); return; /* indirect tail jmp */

}

/**
 * sub_000435B0
 * Original: 0x000435B0 - 0x000435BB (11 bytes, 3 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_000435B0(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_000435B0: ;
    ecx = MEM32(ecx + 0x48);
    eax = MEM32(ecx);
    g_seh_ebp = ebp; RECOMP_ITAIL(MEM32(eax + 0xAC)); return; /* indirect tail jmp */

}

/**
 * sub_000435C0
 * Original: 0x000435C0 - 0x000435C8 (8 bytes, 3 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_000435C0(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_000435C0: ;
    ecx = MEM32(ecx + 0x48);
    eax = MEM32(ecx);
    g_seh_ebp = ebp; RECOMP_ITAIL(MEM32(eax + 0x70)); return; /* indirect tail jmp */

}

/**
 * sub_000435F0
 * Original: 0x000435F0 - 0x000435F8 (8 bytes, 3 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_000435F0(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_000435F0: ;
    ecx = MEM32(ecx + 0x48);
    eax = MEM32(ecx);
    g_seh_ebp = ebp; RECOMP_ITAIL(MEM32(eax + 0x64)); return; /* indirect tail jmp */

}

/**
 * sub_0004BF40
 * Original: 0x0004BF40 - 0x0004BF5B (27 bytes, 8 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0004BF40(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_0004BF40: ;
    eax = MEM32(esp + 4);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0x7AE2FD86) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0x7AE2FD86 (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_0004BF50; /* jne: not equal / not zero */

loc_0004BF4B: ;
    SET_LO8(eax, 1);
    esp += 8; return; /* ret 4 */

loc_0004BF50: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0x1F7AADFF) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0x1F7AADFF (32-bit) */
    SET_LO8(eax, (CMP_EQ(_fa, _fb)) ? 1 : 0); /* sete */
    esp += 8; return; /* ret 4 */

}

/**
 * sub_0005A550
 * Original: 0x0005A550 - 0x0005A5EB (155 bytes, 54 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0005A550(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_0005A550: ;
    eax = MEM32(esp + 4);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0x589587CA) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0x589587CA (32-bit) */
    PUSH32(esp, esi);
    if (CMP_EQ(_fa, _fb)) goto loc_0005A590; /* je: equal / zero */

loc_0005A55C: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0x6AF4A6D7) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0x6AF4A6D7 (32-bit) */
    esi = MEM32(esp + 0xC);
    if (CMP_EQ(_fa, _fb)) goto loc_0005A579; /* je: equal / zero */

loc_0005A567: ;
    edx = MEM32(esp + 0x10);
    PUSH32(esp, edx);
    PUSH32(esp, esi);
    PUSH32(esp, eax);
    PUSH32(esp, 0x0005A573u); sub_000DAD50(); /* call 0x000DAD50 */

loc_0005A573: ;
    eax = esi;
    POP32(esp, esi);
    esp += 16; return; /* ret 12 */

loc_0005A579: ;
    eax = MEM32(esp + 0x10);
    PUSH32(esp, eax);
    edx = 0x22A3FC;
    ecx = esi;
    PUSH32(esp, 0x0005A58Au); sub_000D52A0(); /* call 0x000D52A0 */

loc_0005A58A: ;
    eax = esi;
    POP32(esp, esi);
    esp += 16; return; /* ret 12 */

loc_0005A590: ;
    edx = MEM32(ecx);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, edi);
    PUSH32(esp, 0x1ACCF75F);
    PUSH32(esp, 0x572EB5B2);
    esi = 0; /* xor self */
    edi = 0; /* xor self */
    { uint32_t _icall_target = MEM32(edx + 0x1C); PUSH32(esp, 0x0005A5A4u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_0005A5A4: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0005A5B4; /* je: equal / zero */

loc_0005A5A8: ;
    esi = MEM32(eax + 0xD0);
    edi = MEM32(eax + 0xD4);

loc_0005A5B4: ;
    PUSH32(esp, 0x22A3F4);
    PUSH32(esp, 0x0005A5BEu); sub_00097940(); /* call 0x00097940 */

loc_0005A5BE: ;
    PUSH32(esp, eax);
    PUSH32(esp, 0x0005A5C4u); sub_00097930(); /* call 0x00097930 */

loc_0005A5C4: ;
    PUSH32(esp, eax);
    PUSH32(esp, 0x0005A5CAu); sub_00097920(); /* call 0x00097920 */

loc_0005A5CA: ;
    PUSH32(esp, eax);
    eax = MEM32(esp + 0x24);
    PUSH32(esp, edi);
    PUSH32(esp, esi);
    esi = MEM32(esp + 0x28);
    PUSH32(esp, 0x22A3DC);
    PUSH32(esp, eax);
    PUSH32(esp, esi);
    PUSH32(esp, 0x0005A5E1u); sub_000D5410(); /* call 0x000D5410 */

loc_0005A5E1: ;
    esp = esp + 0x24;
    POP32(esp, edi);
    eax = esi;
    POP32(esp, esi);
    esp += 16; return; /* ret 12 */

}

/**
 * sub_0006BB00
 * Original: 0x0006BB00 - 0x0006BB22 (34 bytes, 10 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0006BB00(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_0006BB00: ;
    eax = MEM32(esp + 4);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0xB1A0801Bu) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0xB1A0801Bu (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_0006BB10; /* jne: not equal / not zero */

loc_0006BB0B: ;
    SET_LO8(eax, 1);
    esp += 8; return; /* ret 4 */

loc_0006BB10: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0x38082939) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0x38082939 (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_0006BB0B; /* je: equal / zero */

loc_0006BB17: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0xA75FFAEBu) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0xA75FFAEBu (32-bit) */
    SET_LO8(eax, (CMP_EQ(_fa, _fb)) ? 1 : 0); /* sete */
    esp += 8; return; /* ret 4 */

}

/**
 * sub_00070550
 * Original: 0x00070550 - 0x000705B3 (99 bytes, 40 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00070550(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00070550: ;
    eax = MEM32(esp + 4);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    PUSH32(esp, edi);
    edi = ecx;
    if (TEST_NZ(_fa, _fb)) goto loc_000705AF; /* jne: not equal / not zero */

loc_0007055B: ;
    PUSH32(esp, ebx);
    ebx = MEM32(esp + 0x14);
    _fa = (uint32_t)(ebx) & 0xFFFFFFFFu; _fb = (uint32_t)(0xFFFFFFFFu) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp ebx, 0xFFFFFFFFu (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_000705AE; /* je: equal / zero */

loc_00070565: ;
    eax = MEM32(edi + -8);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_000705AE; /* je: equal / zero */

loc_0007056C: ;
    ecx = MEM32(0x286774);
    PUSH32(esp, eax);
    PUSH32(esp, 0x00070578u); sub_0010E3F0(); /* call 0x0010E3F0 */

loc_00070578: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_000705AE; /* je: equal / zero */

loc_0007057C: ;
    edx = MEM32(eax);
    ecx = eax;
    { uint32_t _icall_esp = g_esp;
    { uint32_t _icall_target = MEM32(edx + 4); PUSH32(esp, 0x00070583u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00070583: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_000705AE; /* je: equal / zero */

loc_00070587: ;
    ecx = MEM32(eax);
    PUSH32(esp, esi);
    esi = eax + ecx * 4 + 4;
    edx = esp + 0x18;
    PUSH32(esp, edx);
    ecx = esp + 0x14;
    PUSH32(esp, ecx);
    ecx = eax;
    PUSH32(esp, 0x0007059Fu); sub_0006FDC0(); /* call 0x0006FDC0 */

loc_0007059F: ;
    _fa = (uint32_t)(MEM32(eax)) & 0xFFFFFFFFu; _fb = (uint32_t)(esi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(eax), esi (32-bit) */
    POP32(esp, esi);
    if (CMP_EQ(_fa, _fb)) goto loc_000705AE; /* je: equal / zero */

loc_000705A4: ;
    ecx = edi + 0xC;
    edx = ebx;
    PUSH32(esp, 0x000705AEu); sub_0006E9D0(); /* call 0x0006E9D0 */

loc_000705AE: ;
    POP32(esp, ebx);

loc_000705AF: ;
    POP32(esp, edi);
    esp += 20; return; /* ret 16 */

}

/**
 * sub_00074DD0
 * Original: 0x00074DD0 - 0x00074E0A (58 bytes, 13 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00074DD0(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_00074DD0: ;
    eax = MEM32(esp + 4);
    edx = MEM32(eax);
    MEM32(ecx + 0xE0) = edx;
    edx = MEM32(eax + 4);
    MEM32(ecx + 0xE4) = edx;
    edx = MEM32(eax + 8);
    MEM32(ecx + 0xE8) = edx;
    edx = MEM32(eax + 0xC);
    MEM32(ecx + 0xEC) = edx;
    MEM32(ecx + 0xF4) = MEM32(ecx + 0xF4) | 2;
    MEM32(esp + 4) = eax;
    ecx = ecx + 0x14;
    g_seh_ebp = ebp; sub_00133180(); return; /* tail jmp 0x00133180 */

}

/**
 * sub_00075330
 * Original: 0x00075330 - 0x00075338 (8 bytes, 3 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00075330(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_00075330: ;
    ecx = ecx + 0x14;
    eax = MEM32(ecx);
    g_seh_ebp = ebp; RECOMP_ITAIL(MEM32(eax + 0x34)); return; /* indirect tail jmp */

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

/**
 * sub_00079880
 * Original: 0x00079880 - 0x0007989E (30 bytes, 11 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00079880(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00079880: ;
    PUSH32(esp, esi);
    esi = ecx;
    PUSH32(esp, 0x00079888u); sub_000797F0(); /* call 0x000797F0 */

loc_00079888: ;
    _fa = (uint32_t)(MEM8(esp + 8)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(esp + 8), 1 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00079898; /* je: equal / zero */

loc_0007988F: ;
    PUSH32(esp, esi);
    PUSH32(esp, 0x00079895u); sub_0006B710(); /* call 0x0006B710 */

loc_00079895: ;
    esp = esp + 4;

loc_00079898: ;
    eax = esi;
    POP32(esp, esi);
    esp += 8; return; /* ret 4 */

}

/**
 * sub_00081A10
 * Original: 0x00081A10 - 0x00081A2E (30 bytes, 11 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00081A10(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00081A10: ;
    PUSH32(esp, esi);
    esi = ecx;
    PUSH32(esp, 0x00081A18u); sub_00081630(); /* call 0x00081630 */

loc_00081A18: ;
    _fa = (uint32_t)(MEM8(esp + 8)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(esp + 8), 1 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00081A28; /* je: equal / zero */

loc_00081A1F: ;
    PUSH32(esp, esi);
    PUSH32(esp, 0x00081A25u); sub_0006B710(); /* call 0x0006B710 */

loc_00081A25: ;
    esp = esp + 4;

loc_00081A28: ;
    eax = esi;
    POP32(esp, esi);
    esp += 8; return; /* ret 4 */

}

/**
 * sub_00085FF0
 * Original: 0x00085FF0 - 0x0008600F (31 bytes, 11 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00085FF0(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00085FF0: ;
    _fa = (uint32_t)(MEM8(esp + 4)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(esp + 4), 1 (8-bit) */
    PUSH32(esp, esi);
    esi = ecx;
    MEM32(esi) = 0x22DF90;
    if (TEST_Z(_fa, _fb)) goto loc_00086009; /* je: equal / zero */

loc_00086000: ;
    PUSH32(esp, esi);
    PUSH32(esp, 0x00086006u); sub_0006B710(); /* call 0x0006B710 */

loc_00086006: ;
    esp = esp + 4;

loc_00086009: ;
    eax = esi;
    POP32(esp, esi);
    esp += 8; return; /* ret 4 */

}

/**
 * sub_00097BA0
 * Original: 0x00097BA0 - 0x00097BC2 (34 bytes, 10 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00097BA0(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00097BA0: ;
    eax = MEM32(esp + 4);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0x1DE7E3DA) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0x1DE7E3DA (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_00097BB0; /* jne: not equal / not zero */

loc_00097BAB: ;
    SET_LO8(eax, 1);
    esp += 8; return; /* ret 4 */

loc_00097BB0: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0x3BE6820C) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0x3BE6820C (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_00097BAB; /* je: equal / zero */

loc_00097BB7: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0xA75FFAEBu) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0xA75FFAEBu (32-bit) */
    SET_LO8(eax, (CMP_EQ(_fa, _fb)) ? 1 : 0); /* sete */
    esp += 8; return; /* ret 4 */

}

/**
 * sub_0009C2D0
 * Original: 0x0009C2D0 - 0x0009C2D6 (6 bytes, 2 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0009C2D0(void)
{

loc_0009C2D0: ;
    eax = 0x8BFCF9A0u;
    esp += 4; return; /* ret */

}

/**
 * sub_000A1270
 * Original: 0x000A1270 - 0x000A1276 (6 bytes, 2 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_000A1270(void)
{

loc_000A1270: ;
    eax = 0x6460CAB8;
    esp += 4; return; /* ret */

}

/**
 * sub_000A4980
 * Original: 0x000A4980 - 0x000A4986 (6 bytes, 2 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_000A4980(void)
{

loc_000A4980: ;
    eax = 0x9BCE23F0u;
    esp += 4; return; /* ret */

}

/**
 * sub_000AECE0
 * Original: 0x000AECE0 - 0x000AED3F (95 bytes, 37 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_000AECE0(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_000AECE0: ;
    esp = esp - 0xC;
    PUSH32(esp, ebx);
    ebx = ecx;
    eax = MEM32(ebx + 0x80);
    PUSH32(esp, esi);
    esi = 0; /* xor self */
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (CMP_LE(_fas & _fbs, 0)) goto loc_000AED37; /* jle: less or equal (signed <=) */

loc_000AECF3: ;
    PUSH32(esp, ebp);
    ebp = MEM32(esp + 0x24);
    PUSH32(esp, edi);
    MEM32(esp + 0x10) = esi;
    MEM32(esp + 0x14) = esi;
    MEM32(esp + 0x18) = esi;
    edi = ebx + 0x30;
    goto loc_000AED10;

    /* nop */

loc_000AED10: ;
    ecx = MEM32(esp + 0x24);
    edx = MEM32(esp + 0x20);
    eax = esp + 0x10;
    PUSH32(esp, eax);
    PUSH32(esp, ecx);
    ecx = MEM32(edi);
    PUSH32(esp, ebp);
    PUSH32(esp, edx);
    PUSH32(esp, 0x000AED27u); sub_000AEA30(); /* call 0x000AEA30 */

loc_000AED27: ;
    eax = MEM32(ebx + 0x80);
    esi = esi + 1;
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fas = (int32_t)(int32_t)_fa; /* inc flags snapshot */
    edi = edi + 4;
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp esi, eax (32-bit) */
    if (CMP_L(_fas, _fbs)) goto loc_000AED10; /* jl: less (signed <) */

loc_000AED35: ;
    POP32(esp, edi);
    POP32(esp, ebp);

loc_000AED37: ;
    POP32(esp, esi);
    POP32(esp, ebx);
    esp = esp + 0xC;
    esp += 16; return; /* ret 12 */

}

/**
 * sub_000B8060
 * Original: 0x000B8060 - 0x000B8078 (24 bytes, 5 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_000B8060(void)
{

loc_000B8060: ;
    eax = MEM32(esp + 4);
    MEM32(eax) = 1;
    MEM32(eax + 8) = 0x10;
    MEM8(eax + 4) = 1;
    esp += 8; return; /* ret 4 */

}

/**
 * sub_000BBCD0
 * Original: 0x000BBCD0 - 0x000BBCD6 (6 bytes, 2 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_000BBCD0(void)
{

loc_000BBCD0: ;
    eax = ecx + 8;
    esp += 16; return; /* ret 12 */

}

/**
 * sub_000C7CC0
 * Original: 0x000C7CC0 - 0x000C7CE8 (40 bytes, 15 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_000C7CC0(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_000C7CC0: ;
    PUSH32(esp, esi);
    esi = ecx;
    PUSH32(esp, 0x000C7CC8u); sub_000C6B60(); /* call 0x000C6B60 */

loc_000C7CC8: ;
    _fa = (uint32_t)(MEM8(esp + 8)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(esp + 8), 1 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_000C7CE2; /* je: equal / zero */

loc_000C7CCF: ;
    edx = ZX16(MEM16(esi + 4));
    ecx = MEM32(0x270A80);
    eax = MEM32(ecx);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 0x27);
    PUSH32(esp, edx);
    PUSH32(esp, esi);
    { uint32_t _icall_target = MEM32(eax + 0x14); PUSH32(esp, 0x000C7CE2u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_000C7CE2: ;
    eax = esi;
    POP32(esp, esi);
    esp += 8; return; /* ret 4 */

}

/**
 * sub_000D2420
 * Original: 0x000D2420 - 0x000D242B (11 bytes, 5 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_000D2420(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_000D2420: ;
    edx = MEM32(ecx + 0x58);
    eax = 0; /* xor self */
    _fa = (uint32_t)(edx) & 0xFFFFFFFFu; _fb = (uint32_t)(edx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test edx, edx (32-bit) */
    SET_LO8(eax, (CMP_GE(_fas & _fbs, 0)) ? 1 : 0); /* setge */
    esp += 4; return; /* ret */

}

/**
 * sub_000DA990
 * Original: 0x000DA990 - 0x000DA99F (15 bytes, 6 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_000DA990(void)
{

loc_000DA990: ;
    edx = MEM32(esp + 4);
    eax = MEM32(ecx);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 0xA);
    PUSH32(esp, edx);
    { uint32_t _icall_target = MEM32(eax + 0x10); PUSH32(esp, 0x000DA99Cu); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_000DA99C: ;
    esp += 8; return; /* ret 4 */

}

/**
 * sub_000E7DB0
 * Original: 0x000E7DB0 - 0x000E7DB8 (8 bytes, 2 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_000E7DB0(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_000E7DB0: ;
    ecx = ecx - 0x1C;
    g_seh_ebp = ebp; sub_000E7DC0(); return; /* tail jmp 0x000E7DC0 */

}

/**
 * sub_000E7FB0
 * Original: 0x000E7FB0 - 0x000E800D (93 bytes, 29 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_000E7FB0(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_000E7FB0: ;
    PUSH32(esp, esi);
    esi = ecx;
    eax = MEM32(esi + 0x8E4);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    MEM32(esi) = 0x2349C4;
    MEM32(esi + 0x1C) = 0x2349BC;
    if (TEST_Z(_fa, _fb)) goto loc_000E7FD0; /* je: equal / zero */

loc_000E7FCA: ;
    PUSH32(esp, eax);
    PUSH32(esp, 0x000E7FD0u); sub_001DD3E0(); /* call 0x001DD3E0 */

loc_000E7FD0: ;
    eax = MEM32(esi + 0x8E8);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_000E7FE0; /* je: equal / zero */

loc_000E7FDA: ;
    PUSH32(esp, eax);
    PUSH32(esp, 0x000E7FE0u); sub_001DD3E0(); /* call 0x001DD3E0 */

loc_000E7FE0: ;
    eax = MEM32(esi + 0x8EC);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_000E7FF0; /* je: equal / zero */

loc_000E7FEA: ;
    PUSH32(esp, eax);
    PUSH32(esp, 0x000E7FF0u); sub_001DD3E0(); /* call 0x001DD3E0 */

loc_000E7FF0: ;
    ecx = esi;
    PUSH32(esp, 0x000E7FF7u); sub_000F5230(); /* call 0x000F5230 */

loc_000E7FF7: ;
    _fa = (uint32_t)(MEM8(esp + 8)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(esp + 8), 1 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_000E8007; /* je: equal / zero */

loc_000E7FFE: ;
    PUSH32(esp, esi);
    PUSH32(esp, 0x000E8004u); sub_0006B710(); /* call 0x0006B710 */

loc_000E8004: ;
    esp = esp + 4;

loc_000E8007: ;
    eax = esi;
    POP32(esp, esi);
    esp += 8; return; /* ret 4 */

}

/**
 * sub_000E8180
 * Original: 0x000E8180 - 0x000E81AB (43 bytes, 13 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_000E8180(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_000E8180: ;
    PUSH32(esp, esi);
    esi = ecx;
    MEM32(esi) = 0x234A40;
    MEM32(esi + 0x1C) = 0x234A38;
    PUSH32(esp, 0x000E8195u); sub_000F5370(); /* call 0x000F5370 */

loc_000E8195: ;
    _fa = (uint32_t)(MEM8(esp + 8)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(esp + 8), 1 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_000E81A5; /* je: equal / zero */

loc_000E819C: ;
    PUSH32(esp, esi);
    PUSH32(esp, 0x000E81A2u); sub_0006B710(); /* call 0x0006B710 */

loc_000E81A2: ;
    esp = esp + 4;

loc_000E81A5: ;
    eax = esi;
    POP32(esp, esi);
    esp += 8; return; /* ret 4 */

}

/**
 * sub_000E84C0
 * Original: 0x000E84C0 - 0x000E8512 (82 bytes, 25 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_000E84C0(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_000E84C0: ;
    PUSH32(esp, esi);
    esi = ecx;
    PUSH32(esp, edi);
    edi = esi + 0x1C;
    MEM32(esi) = 0x234ABC;
    MEM32(edi) = 0x234AB4;
    ecx = MEM32(0x258154);
    PUSH32(esp, edi);
    PUSH32(esp, 0x000E84DFu); sub_000F3570(); /* call 0x000F3570 */

loc_000E84DF: ;
    eax = MEM32(esi + 0x2C);
    ecx = MEM32(0x250EF8);
    PUSH32(esp, eax);
    PUSH32(esp, 0x000E84EEu); sub_000E35F0(); /* call 0x000E35F0 */

loc_000E84EE: ;
    ecx = esi;
    MEM32(edi) = 0x234938;
    PUSH32(esp, 0x000E84FBu); sub_000E7830(); /* call 0x000E7830 */

loc_000E84FB: ;
    _fa = (uint32_t)(MEM8(esp + 0xC)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(esp + 0xC), 1 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_000E850B; /* je: equal / zero */

loc_000E8502: ;
    PUSH32(esp, esi);
    PUSH32(esp, 0x000E8508u); sub_0006B710(); /* call 0x0006B710 */

loc_000E8508: ;
    esp = esp + 4;

loc_000E850B: ;
    POP32(esp, edi);
    eax = esi;
    POP32(esp, esi);
    esp += 8; return; /* ret 4 */

}

/**
 * sub_000EC010
 * Original: 0x000EC010 - 0x000EC02F (31 bytes, 11 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_000EC010(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_000EC010: ;
    _fa = (uint32_t)(MEM8(esp + 4)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(esp + 4), 1 (8-bit) */
    PUSH32(esp, esi);
    esi = ecx;
    MEM32(esi) = 0x234D10;
    if (TEST_Z(_fa, _fb)) goto loc_000EC029; /* je: equal / zero */

loc_000EC020: ;
    PUSH32(esp, esi);
    PUSH32(esp, 0x000EC026u); sub_0006B710(); /* call 0x0006B710 */

loc_000EC026: ;
    esp = esp + 4;

loc_000EC029: ;
    eax = esi;
    POP32(esp, esi);
    esp += 8; return; /* ret 4 */

}

/**
 * sub_001116F0
 * Original: 0x001116F0 - 0x00111702 (18 bytes, 5 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_001116F0(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_001116F0: ;
    ecx = MEM32(esp + 4);
    eax = 0; /* xor self */
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(0x1F7AADFF) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp ecx, 0x1F7AADFF (32-bit) */
    SET_LO8(eax, (CMP_EQ(_fa, _fb)) ? 1 : 0); /* sete */
    esp += 8; return; /* ret 4 */

}

/**
 * sub_00114B10
 * Original: 0x00114B10 - 0x00114B34 (36 bytes, 12 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00114B10(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00114B10: ;
    PUSH32(esp, esi);
    esi = ecx;
    MEM32(esi) = 0x2363D0;
    PUSH32(esp, 0x00114B1Eu); sub_00111590(); /* call 0x00111590 */

loc_00114B1E: ;
    _fa = (uint32_t)(MEM8(esp + 8)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(esp + 8), 1 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00114B2E; /* je: equal / zero */

loc_00114B25: ;
    PUSH32(esp, esi);
    PUSH32(esp, 0x00114B2Bu); sub_0006B710(); /* call 0x0006B710 */

loc_00114B2B: ;
    esp = esp + 4;

loc_00114B2E: ;
    eax = esi;
    POP32(esp, esi);
    esp += 8; return; /* ret 4 */

}

/**
 * sub_0011A830
 * Original: 0x0011A830 - 0x0011A84B (27 bytes, 8 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0011A830(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_0011A830: ;
    eax = MEM32(esp + 4);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0xB5FA0F27u) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0xB5FA0F27u (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_0011A840; /* jne: not equal / not zero */

loc_0011A83B: ;
    SET_LO8(eax, 1);
    esp += 8; return; /* ret 4 */

loc_0011A840: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0xFD21D593u) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0xFD21D593u (32-bit) */
    SET_LO8(eax, (CMP_EQ(_fa, _fb)) ? 1 : 0); /* sete */
    esp += 8; return; /* ret 4 */

}

/**
 * sub_0011D300
 * Original: 0x0011D300 - 0x0011D348 (72 bytes, 26 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0011D300(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_0011D300: ;
    PUSH32(esp, esi);
    esi = ecx;
    PUSH32(esp, edi);
    edi = esi + 0x1C;
    ecx = edi;
    MEM32(esi) = 0x236B94;
    PUSH32(esp, 0x0011D314u); sub_0011D100(); /* call 0x0011D100 */

loc_0011D314: ;
    ecx = MEM32(esi + 0x28);
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, ecx (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0011D322; /* je: equal / zero */

loc_0011D31B: ;
    eax = MEM32(ecx);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 1);
    { uint32_t _icall_target = MEM32(eax + 8); PUSH32(esp, 0x0011D322u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_0011D322: ;
    ecx = esi + 0x2C;
    PUSH32(esp, 0x0011D32Au); sub_0011A390(); /* call 0x0011A390 */

loc_0011D32A: ;
    ecx = edi;
    PUSH32(esp, 0x0011D331u); sub_0011D100(); /* call 0x0011D100 */

loc_0011D331: ;
    _fa = (uint32_t)(MEM8(esp + 0xC)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(esp + 0xC), 1 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0011D341; /* je: equal / zero */

loc_0011D338: ;
    PUSH32(esp, esi);
    PUSH32(esp, 0x0011D33Eu); sub_0006B710(); /* call 0x0006B710 */

loc_0011D33E: ;
    esp = esp + 4;

loc_0011D341: ;
    POP32(esp, edi);
    eax = esi;
    POP32(esp, esi);
    esp += 8; return; /* ret 4 */

}

/**
 * sub_00120190
 * Original: 0x00120190 - 0x001201B4 (36 bytes, 12 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00120190(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00120190: ;
    PUSH32(esp, esi);
    esi = ecx;
    MEM32(esi) = 0x236E58;
    PUSH32(esp, 0x0012019Eu); sub_0011D2C0(); /* call 0x0011D2C0 */

loc_0012019E: ;
    _fa = (uint32_t)(MEM8(esp + 8)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(esp + 8), 1 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_001201AE; /* je: equal / zero */

loc_001201A5: ;
    PUSH32(esp, esi);
    PUSH32(esp, 0x001201ABu); sub_0006B710(); /* call 0x0006B710 */

loc_001201AB: ;
    esp = esp + 4;

loc_001201AE: ;
    eax = esi;
    POP32(esp, esi);
    esp += 8; return; /* ret 4 */

}

/**
 * sub_00120530
 * Original: 0x00120530 - 0x00120554 (36 bytes, 12 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00120530(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00120530: ;
    PUSH32(esp, esi);
    esi = ecx;
    MEM32(esi) = 0x236E88;
    PUSH32(esp, 0x0012053Eu); sub_0011F3B0(); /* call 0x0011F3B0 */

loc_0012053E: ;
    _fa = (uint32_t)(MEM8(esp + 8)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(esp + 8), 1 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0012054E; /* je: equal / zero */

loc_00120545: ;
    PUSH32(esp, esi);
    PUSH32(esp, 0x0012054Bu); sub_0006B710(); /* call 0x0006B710 */

loc_0012054B: ;
    esp = esp + 4;

loc_0012054E: ;
    eax = esi;
    POP32(esp, esi);
    esp += 8; return; /* ret 4 */

}

/**
 * sub_00120FB0
 * Original: 0x00120FB0 - 0x00120FD4 (36 bytes, 12 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00120FB0(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00120FB0: ;
    PUSH32(esp, esi);
    esi = ecx;
    MEM32(esi) = 0x236EB0;
    PUSH32(esp, 0x00120FBEu); sub_00121CC0(); /* call 0x00121CC0 */

loc_00120FBE: ;
    _fa = (uint32_t)(MEM8(esp + 8)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(esp + 8), 1 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00120FCE; /* je: equal / zero */

loc_00120FC5: ;
    PUSH32(esp, esi);
    PUSH32(esp, 0x00120FCBu); sub_0006B710(); /* call 0x0006B710 */

loc_00120FCB: ;
    esp = esp + 4;

loc_00120FCE: ;
    eax = esi;
    POP32(esp, esi);
    esp += 8; return; /* ret 4 */

}

/**
 * sub_00121110
 * Original: 0x00121110 - 0x00121134 (36 bytes, 12 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00121110(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00121110: ;
    PUSH32(esp, esi);
    esi = ecx;
    MEM32(esi) = 0x236ECC;
    PUSH32(esp, 0x0012111Eu); sub_00121CC0(); /* call 0x00121CC0 */

loc_0012111E: ;
    _fa = (uint32_t)(MEM8(esp + 8)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(esp + 8), 1 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0012112E; /* je: equal / zero */

loc_00121125: ;
    PUSH32(esp, esi);
    PUSH32(esp, 0x0012112Bu); sub_0006B710(); /* call 0x0006B710 */

loc_0012112B: ;
    esp = esp + 4;

loc_0012112E: ;
    eax = esi;
    POP32(esp, esi);
    esp += 8; return; /* ret 4 */

}

/**
 * sub_001346E0
 * Original: 0x001346E0 - 0x001346E8 (8 bytes, 2 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_001346E0(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_001346E0: ;
    ecx = ecx - 8;
    g_seh_ebp = ebp; sub_001347A0(); return; /* tail jmp 0x001347A0 */

}

/**
 * sub_001350D0
 * Original: 0x001350D0 - 0x001350F2 (34 bytes, 10 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_001350D0(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_001350D0: ;
    eax = MEM32(esp + 4);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0x460B3751) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0x460B3751 (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_001350E0; /* jne: not equal / not zero */

loc_001350DB: ;
    SET_LO8(eax, 1);
    esp += 8; return; /* ret 4 */

loc_001350E0: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0xEF29B136u) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0xEF29B136u (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_001350DB; /* je: equal / zero */

loc_001350E7: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0xFFEE9E41u) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0xFFEE9E41u (32-bit) */
    SET_LO8(eax, (CMP_EQ(_fa, _fb)) ? 1 : 0); /* sete */
    esp += 8; return; /* ret 4 */

}

/**
 * sub_001360F0
 * Original: 0x001360F0 - 0x001360F8 (8 bytes, 2 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_001360F0(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_001360F0: ;
    ecx = ecx - 0x10;
    g_seh_ebp = ebp; sub_00136100(); return; /* tail jmp 0x00136100 */

}

/**
 * sub_001377F0
 * Original: 0x001377F0 - 0x00137808 (24 bytes, 9 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_001377F0(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_001377F0: ;
    ecx = MEM32(ecx + 0xC);
    edx = MEM32(esp + 4);
    eax = MEM32(ecx);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, edx);
    { uint32_t _icall_target = MEM32(eax + 0x18); PUSH32(esp, 0x001377FDu); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_001377FD: ;
    esp += 12; return; /* ret 8 */

}

/**
 * sub_00137830
 * Original: 0x00137830 - 0x0013783F (15 bytes, 6 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00137830(void)
{

loc_00137830: ;
    edx = MEM32(esp + 4);
    eax = MEM32(ecx);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 0);
    PUSH32(esp, edx);
    { uint32_t _icall_target = MEM32(eax + 0x40); PUSH32(esp, 0x0013783Cu); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_0013783C: ;
    esp += 8; return; /* ret 4 */

}

/**
 * sub_001532A0
 * Original: 0x001532A0 - 0x001532FA (90 bytes, 25 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_001532A0(void)
{

loc_001532A0: ;
    PUSH32(esp, 0xFFFFFFFFu);
    PUSH32(esp, 0x1AC278);
    eax = MEM32(0);
    PUSH32(esp, eax);
    MEM32(0) = esp;
    esp = esp - 0xC;
    edx = MEM32(esp + 0x28);
    eax = 0; /* xor self */
    MEM8(esp + 4) = LO8(eax);
    MEM32(esp) = 0x238348;
    MEM32(esp + 8) = edx;
    edx = MEM32(esp + 0x24);
    MEM32(esp + 0x14) = eax;
    eax = esp;
    PUSH32(esp, eax);
    eax = MEM32(esp + 0x20);
    PUSH32(esp, edx);
    edx = MEM32(esp + 0x28);
    PUSH32(esp, eax);
    PUSH32(esp, edx);
    PUSH32(esp, 0x001532E9u); sub_00151EE0(); /* call 0x00151EE0 */

loc_001532E9: ;
    ecx = MEM32(esp + 0xC);
    MEM32(0) = ecx;
    esp = esp + 0x18;
    esp += 20; return; /* ret 16 */

}

/**
 * sub_00166470
 * Original: 0x00166470 - 0x0016647F (15 bytes, 5 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00166470(void)
{

loc_00166470: ;
    eax = MEM32(esp + 8);
    ecx = MEM32(esp + 4);
    PUSH32(esp, eax);
    PUSH32(esp, 0x0016647Eu); sub_00164D30(); /* call 0x00164D30 */

loc_0016647E: ;
    esp += 4; return; /* ret */

}
/* END RETAIL VTABLE GAP BODIES */
