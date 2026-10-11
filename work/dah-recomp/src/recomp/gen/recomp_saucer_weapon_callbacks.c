#define RECOMP_GENERATED_CODE
#include "recomp_types.h"
#include "recomp_funcs.h"

/**
 * sub_0011A280
 * Original: 0x0011A280 - 0x0011A2D4 (84 bytes, 22 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0011A280(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_0011A280: ;
    edx = MEM32(esp + 8);
    _fa = (uint32_t)(LO8(edx)) & 0xFFu; _fb = (uint32_t)(LO8(edx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(edx), LO8(edx) (8-bit) */
    eax = MEM32(esp + 4);
    if (TEST_Z(_fa, _fb)) goto loc_0011A2C7; /* je: equal / zero */

loc_0011A28C: ;
    PUSH32(esp, esi);
    esi = MEM32(ecx + 8);
    _fa = (uint32_t)(MEM32(esi + 0xC)) & 0xFFFFFFFFu; _fb = (uint32_t)(0x40000) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test MEM32(esi + 0xC), 0x40000 (32-bit) */
    POP32(esp, esi);
    if (TEST_Z(_fa, _fb)) goto loc_0011A2C7; /* je: equal / zero */

loc_0011A29A: ;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(7) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), 7 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0011A2C7; /* je: equal / zero */

loc_0011A29E: ;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), 1 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0011A2B6; /* je: equal / zero */

loc_0011A2A2: ;
    MEM8(ecx + 0x1FC) = 0;
    MEM32(esp + 8) = edx;
    MEM32(esp + 4) = eax;
    g_seh_ebp = ebp; sub_0011D0C0(); return; /* tail jmp 0x0011D0C0 */

loc_0011A2B6: ;
    MEM32(ecx + 0x1F8) = 0;
    MEM8(ecx + 0x1FC) = 1;

loc_0011A2C7: ;
    MEM32(esp + 8) = edx;
    MEM32(esp + 4) = eax;
    g_seh_ebp = ebp; sub_0011D0C0(); return; /* tail jmp 0x0011D0C0 */

}
/**
 * sub_0011A2E0
 * Original: 0x0011A2E0 - 0x0011A2F3 (19 bytes, 4 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0011A2E0(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_0011A2E0: ;
    eax = 0; /* xor self */
    MEM32(ecx + 0x1F8) = eax;
    MEM8(ecx + 0x1FC) = LO8(eax);
    g_seh_ebp = ebp; sub_0011CCD0(); return; /* tail jmp 0x0011CCD0 */

}
/**
 * sub_0011A300
 * Original: 0x0011A300 - 0x0011A383 (131 bytes, 41 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0011A300(void)
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

loc_0011A300: ;
    PUSH32(esp, esi);
    esi = ecx;
    SET_LO8(eax, MEM8(esi + 0x1FC));
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0011A373; /* je: equal / zero */

loc_0011A30D: ;
    fp_push(MEMF(esi + 0x1F8)); /* fld float */
    g_fp_cmp = RECOMP_FCMP(fp_top(), MEMF(0x225C28)); fp_pop(); /* fcomp dword ptr [0x225c28] */
    eax = (eax & 0xFFFF0000u) | (uint32_t)(uint16_t)(((g_fp_top & 7u) << 11) | (g_fp_cmp == 2 ? 0x4500u : g_fp_cmp < 0 ? 0x0100u : g_fp_cmp > 0 ? 0x0000u : 0x4000u)); /* fnstsw ax <- fpu status */
    _fa = (uint32_t)(HI8(eax)) & 0xFFu; _fb = (uint32_t)(5) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test HI8(eax), 5 (8-bit) */
    if (RECOMP_PARITY8((_fa) & (_fb))) goto loc_0011A373; /* jp: parity */

loc_0011A320: ;
    eax = MEM32(esi + 8);
    fp_push(MEMF(esp + 8)); /* fld float */
    fp_top() = fp_top() * MEMF(eax + 0x34); /* fmul dword ptr [eax + 0x34] */
    fp_top() = fp_top() + MEMF(esi + 0x1F8); /* fadd dword ptr [esi + 0x1f8] */
    MEMF(esi + 0x1F8) = (float)fp_top(); /* fst */
    g_fp_cmp = RECOMP_FCMP(fp_top(), MEMF(0x225C28)); fp_pop(); /* fcomp dword ptr [0x225c28] */
    eax = (eax & 0xFFFF0000u) | (uint32_t)(uint16_t)(((g_fp_top & 7u) << 11) | (g_fp_cmp == 2 ? 0x4500u : g_fp_cmp < 0 ? 0x0100u : g_fp_cmp > 0 ? 0x0000u : 0x4000u)); /* fnstsw ax <- fpu status */
    _fa = (uint32_t)(HI8(eax)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test HI8(eax), 1 (8-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_0011A373; /* jne: not equal / not zero */

loc_0011A343: ;
    MEM32(esi + 0x1F8) = 0x3F800000;
    eax = MEM32(esi + 0x1C);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    MEM32(esi + 0x20) = eax;
    if (TEST_Z(_fa, _fb)) goto loc_0011A373; /* je: equal / zero */

loc_0011A357: ;
    ecx = MEM32(eax);
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, ecx (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0011A366; /* je: equal / zero */

loc_0011A35D: ;
    PUSH32(esp, 1);
    PUSH32(esp, 1);
    PUSH32(esp, 0x0011A366u); sub_0011F3F0(); /* call 0x0011F3F0 */

loc_0011A366: ;
    ecx = MEM32(esi + 0x20);
    eax = MEM32(ecx + 4);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    MEM32(esi + 0x20) = eax;
    if (TEST_NZ(_fa, _fb)) goto loc_0011A357; /* jne: not equal / not zero */

loc_0011A373: ;
    edx = MEM32(esp + 8);
    PUSH32(esp, edx);
    ecx = esi;
    PUSH32(esp, 0x0011A37Fu); sub_0011CF30(); /* call 0x0011CF30 */

loc_0011A37F: ;
    POP32(esp, esi);
    esp += 8; return; /* ret 4 */

    #undef fp_push
    #undef fp_pop
    #undef fp_top
    #undef fp_st
    #undef fp_st1
}
/**
 * sub_0008F680
 * Original: 0x0008F680 - 0x0008F6B0 (48 bytes, 14 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0008F680(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_0008F680: ;
    eax = MEM32(edx + 4);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0x9E7EDF34u) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0x9E7EDF34u (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_0008F6AD; /* je: equal / zero */

loc_0008F68A: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0x2C4F6A80) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0x2C4F6A80 (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_0008F6A6; /* je: equal / zero */

loc_0008F691: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0x768FCBA6) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0x768FCBA6 (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_0008F6AD; /* jne: not equal / not zero */

loc_0008F698: ;
    eax = MEM32(esp + 4);
    MEM8(eax + 1) = 1;
    MEM8(eax) = 1;
    esp += 8; return; /* ret 4 */

loc_0008F6A6: ;
    eax = MEM32(esp + 4);
    MEM8(eax) = 1;

loc_0008F6AD: ;
    esp += 8; return; /* ret 4 */

}
/**
 * sub_00084FB0
 * Original: 0x00084FB0 - 0x00084FFD (77 bytes, 21 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00084FB0(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00084FB0: ;
    eax = MEM32(esp + 4);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0x9E7EDF34u) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0x9E7EDF34u (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_00084FCB; /* jne: not equal / not zero */

loc_00084FBB: ;
    ecx = MEM32(ecx + 0x3C);
    PUSH32(esp, 0x930E920Bu);
    PUSH32(esp, 0x00084FC8u); sub_0007C2E0(); /* call 0x0007C2E0 */

loc_00084FC8: ;
    esp += 12; return; /* ret 8 */

loc_00084FCB: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0x37EC8C25) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0x37EC8C25 (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_00084FFA; /* je: equal / zero */

loc_00084FD2: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0xBDF7C019u) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0xBDF7C019u (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_00084FFA; /* jne: not equal / not zero */

loc_00084FD9: ;
    SET_LO8(eax, MEM8(0x258B48));
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00084FF0; /* je: equal / zero */

loc_00084FE2: ;
    eax = MEM32(ecx + 0x3C);
    edx = MEM32(eax + 0x48);
    _fa = (uint32_t)(MEM32(edx)) & 0xFFFFFFFFu; _fb = (uint32_t)(0xD3C8230Eu) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(edx), 0xD3C8230Eu (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_00084FFA; /* jne: not equal / not zero */

loc_00084FF0: ;
    PUSH32(esp, 0xFB009F42u);
    PUSH32(esp, 0x00084FFAu); sub_00084CB0(); /* call 0x00084CB0 */

loc_00084FFA: ;
    esp += 12; return; /* ret 8 */

}

/**
 * sub_00098210
 * Original: 0x00098210 - 0x00098225 (21 bytes, 8 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00098210(void)
{

loc_00098210: ;
    PUSH32(esp, esi);
    esi = ecx;
    PUSH32(esp, 0x00098218u); sub_00097C10(); /* call 0x00097C10 */

loc_00098218: ;
    eax = MEM32(0x286768);
    ecx = MEM32(eax + 0xC);
    MEM32(esi + 0x50) = ecx;
    POP32(esp, esi);
    esp += 4; return; /* ret */

}

/**
 * sub_00025A00
 * Original: 0x00025A00 - 0x00025A77 (119 bytes, 46 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00025A00(void)
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

loc_00025A00: ;
    eax = MEM32(esp + 4);
    PUSH32(esp, ebx);
    PUSH32(esp, eax);
    ebx = ecx;
    PUSH32(esp, 0x00025A0Du); sub_00022970(); /* call 0x00022970 */

loc_00025A0D: ;
    ecx = MEM32(ebx + 8);
    fp_push(MEMF(ecx + 0x10C)); /* fld float */
    eax = MEM32(ebx + 4);
    fp_top() = fp_top() * MEMF(eax + 0x1EC); /* fmul dword ptr [eax + 0x1ec] */
    ecx = MEM32(ebx + 0x60);
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, ecx (32-bit) */
    MEMF(esp + 8) = (float)fp_top(); fp_pop(); /* fstp */
    if (TEST_Z(_fa, _fb)) goto loc_00025A73; /* je: equal / zero */

loc_00025A2A: ;
    edx = MEM32(ecx);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    esi = eax + 0x18;
    { uint32_t _icall_target = MEM32(edx + 0x1C); PUSH32(esp, 0x00025A34u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00025A34: ;
    edi = eax;
    eax = MEM32(esi);
    ecx = esi;
    { uint32_t _icall_esp = g_esp;
    { uint32_t _icall_target = MEM32(eax); PUSH32(esp, 0x00025A3Cu); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00025A3C: ;
    fp_push(MEMF(eax)); /* fld float */
    fp_top() = fp_top() - MEMF(edi); /* fsub dword ptr [edi] */
    fp_push(MEMF(eax + 4)); /* fld float */
    fp_top() = fp_top() - MEMF(edi + 4); /* fsub dword ptr [edi + 4] */
    POP32(esp, edi);
    POP32(esp, esi);
    { double _t = fp_top(); fp_push(_t); } /* fld st(0) */
    fp_top() = fp_top() * fp_st1(); /* fmul st(1) */
    { double _t = g_fp_stack[(g_fp_top + 2) & 7]; fp_push(_t); } /* fld st(2) */
    fp_top() = fp_top() * g_fp_stack[(g_fp_top + 3) & 7]; /* fmul st(3) */
    fp_st1() = fp_st1() + fp_top(); fp_pop(); /* faddp st(1) */
    fp_push(MEMF(esp + 8)); /* fld float */
    fp_top() = fp_top() * MEMF(esp + 8); /* fmul dword ptr [esp + 8] */
    g_fp_cmp = RECOMP_FCMP(fp_top(), fp_st1()); fp_pop(); fp_pop(); /* fcompp  */
    eax = (eax & 0xFFFF0000u) | (uint32_t)(uint16_t)(((g_fp_top & 7u) << 11) | (g_fp_cmp == 2 ? 0x4500u : g_fp_cmp < 0 ? 0x0100u : g_fp_cmp > 0 ? 0x0000u : 0x4000u)); /* fnstsw ax <- fpu status */
    fp_pop(); /* fstp st(0) */
    _fa = (uint32_t)(HI8(eax)) & 0xFFu; _fb = (uint32_t)(5) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test HI8(eax), 5 (8-bit) */
    fp_pop(); /* fstp st(0) */
    if (RECOMP_PARITY8((_fa) & (_fb))) goto loc_00025A73; /* jp: parity */

loc_00025A67: ;
    PUSH32(esp, 0x8F651465u);
    ecx = ebx;
    PUSH32(esp, 0x00025A73u); sub_0001B300(); /* call 0x0001B300 */

loc_00025A73: ;
    POP32(esp, ebx);
    esp += 8; return; /* ret 4 */

    #undef fp_push
    #undef fp_pop
    #undef fp_top
    #undef fp_st
    #undef fp_st1
}

/**
 * sub_00098270
 * Original: 0x00098270 - 0x000982F0 (128 bytes, 46 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00098270(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00098270: ;
    PUSH32(esp, esi);
    esi = ecx;
    PUSH32(esp, 0x00098278u); sub_00097C90(); /* call 0x00097C90 */

loc_00098278: ;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_000982D5; /* je: equal / zero */

loc_0009827C: ;
    PUSH32(esp, 1);
    PUSH32(esp, 2);
    ecx = esi + 0x5C;
    PUSH32(esp, 0x00098288u); sub_00104710(); /* call 0x00104710 */

loc_00098288: ;
    PUSH32(esp, 1);
    PUSH32(esp, 2);
    ecx = esi + 0x64;
    PUSH32(esp, 0x00098294u); sub_00104710(); /* call 0x00104710 */

loc_00098294: ;
    ecx = esi;
    PUSH32(esp, 0x0009829Bu); sub_00098110(); /* call 0x00098110 */

loc_0009829B: ;
    eax = MEM32(esi + 0x10);
    ecx = MEM32(eax + 0x38);
    eax = MEM32(esi + 0x20);
    PUSH32(esp, 0);
    PUSH32(esp, ecx);
    ecx = MEM32(eax + 0x28);
    edx = esi + 0x6C;
    PUSH32(esp, edx);
    PUSH32(esp, 0x000982B3u); sub_00107CC0(); /* call 0x00107CC0 */

loc_000982B3: ;
    ecx = MEM32(esi + 0x20);
    edx = MEM32(ecx);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 1);
    { uint32_t _icall_target = MEM32(edx + 0x130); PUSH32(esp, 0x000982C0u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_000982C0: ;
    ecx = MEM32(esi + 0x30);
    PUSH32(esp, 0);
    PUSH32(esp, 0);
    PUSH32(esp, 0x278BEC);
    PUSH32(esp, 0x000982D1u); sub_0009F370(); /* call 0x0009F370 */

loc_000982D1: ;
    SET_LO8(eax, 1);
    POP32(esp, esi);
    esp += 4; return; /* ret */

loc_000982D5: ;
    eax = MEM32(esi + 0x10);
    ecx = MEM32(eax + 0x3C);
    edx = MEM32(esi + 0x20);
    PUSH32(esp, 0x3F800000);
    PUSH32(esp, ecx);
    ecx = MEM32(edx + 0x28);
    PUSH32(esp, 0x000982ECu); sub_00107C00(); /* call 0x00107C00 */

loc_000982EC: ;
    SET_LO8(eax, 0); /* xor self */
    POP32(esp, esi);
    esp += 4; return; /* ret */

}

/**
 * sub_0007A2C0
 * Original: 0x0007A2C0 - 0x0007A2E4 (36 bytes, 12 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0007A2C0(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_0007A2C0: ;
    PUSH32(esp, esi);
    esi = ecx;
    MEM32(esi) = 0x22C57C;
    PUSH32(esp, 0x0007A2CEu); sub_0010D710(); /* call 0x0010D710 */

loc_0007A2CE: ;
    _fa = (uint32_t)(MEM8(esp + 8)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(esp + 8), 1 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0007A2DE; /* je: equal / zero */

loc_0007A2D5: ;
    PUSH32(esp, esi);
    PUSH32(esp, 0x0007A2DBu); sub_0006B710(); /* call 0x0006B710 */

loc_0007A2DB: ;
    esp = esp + 4;

loc_0007A2DE: ;
    eax = esi;
    POP32(esp, esi);
    esp += 8; return; /* ret 4 */

}
