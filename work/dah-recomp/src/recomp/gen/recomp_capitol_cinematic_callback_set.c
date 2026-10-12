/* Generated only from the retail XBE for the Capitol cinematic callback set. */
#define RECOMP_GENERATED_CODE
#include "recomp_funcs.h"

/**
 * sub_00021FB0
 * Original: 0x00021FB0 - 0x00021FF8 (72 bytes, 24 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00021FB0(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00021FB0: ;
    eax = MEM32(esp + 4);
    PUSH32(esp, esi);
    PUSH32(esp, eax);
    esi = ecx;
    PUSH32(esp, 0x00021FBDu); sub_0001B580(); /* call 0x0001B580 */

loc_00021FBD: ;
    ecx = MEM32(esi + 4);
    PUSH32(esp, 0x00021FC5u); sub_000112F0(); /* call 0x000112F0 */

loc_00021FC5: ;
    ecx = eax;
    PUSH32(esp, 0x00021FCCu); sub_000417C0(); /* call 0x000417C0 */

loc_00021FCC: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0xFFFFFFFFu) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0xFFFFFFFFu (32-bit) */
    MEM32(esi + 0x60) = eax;
    if (CMP_NE(_fa, _fb)) goto loc_00021FEA; /* jne: not equal / not zero */

loc_00021FD4: ;
    ecx = MEM32(0x25FCEC);
    eax = MEM32(ecx + 0x38);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00021FEA; /* je: equal / zero */

loc_00021FE1: ;
    edx = MEM32(eax + 0x30);
    eax = MEM32(edx + 0x24);
    MEM32(esi + 0x60) = eax;

loc_00021FEA: ;
    PUSH32(esp, 1);
    ecx = esi + 0x48;
    PUSH32(esp, 0x00021FF4u); sub_0003A3A0(); /* call 0x0003A3A0 */

loc_00021FF4: ;
    POP32(esp, esi);
    esp += 8; return; /* ret 4 */

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
 * sub_0003E190
 * Original: 0x0003E190 - 0x0003E1AB (27 bytes, 8 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0003E190(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_0003E190: ;
    eax = MEM32(esp + 4);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0x4A0548A5) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0x4A0548A5 (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_0003E1A0; /* jne: not equal / not zero */

loc_0003E19B: ;
    SET_LO8(eax, 1);
    esp += 8; return; /* ret 4 */

loc_0003E1A0: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0x1DE7E3DA) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0x1DE7E3DA (32-bit) */
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
