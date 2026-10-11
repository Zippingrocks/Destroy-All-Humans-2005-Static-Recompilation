#define RECOMP_GENERATED_CODE
#include "recomp_types.h"
#include "recomp_funcs.h"

/**
 * sub_000A8130
 * Original: 0x000A8130 - 0x000A825B (299 bytes, 90 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_000A8130(void)
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

loc_000A8130: ;
    PUSH32(esp, ecx);
    PUSH32(esp, esi);
    PUSH32(esp, 0xFFFFFFFFu);
    esi = ecx;
    PUSH32(esp, 0x000A813Bu); sub_00097E60(); /* call 0x00097E60 */

loc_000A813B: ;
    fp_push(MEMF(esi + 0x18)); /* fld float */
    eax = MEM32(0x286768);
    ecx = MEM32(eax + 0xC);
    edx = MEM32(esi + 0x10);
    MEM32(esi + 0x188) = ecx;
    MEM32(esi + 0x18C) = 0;
    MEM8(esi + 0x190) = 0;
    g_fp_cmp = RECOMP_FCMP(fp_top(), MEMF(edx + 0x48)); fp_pop(); /* fcomp dword ptr [edx + 0x48] */
    eax = (eax & 0xFFFF0000u) | (uint32_t)(uint16_t)(((g_fp_top & 7u) << 11) | (g_fp_cmp == 2 ? 0x4500u : g_fp_cmp < 0 ? 0x0100u : g_fp_cmp > 0 ? 0x0000u : 0x4000u)); /* fnstsw ax <- fpu status */
    _fa = (uint32_t)(HI8(eax)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test HI8(eax), 1 (8-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_000A8220; /* jne: not equal / not zero */

loc_000A816E: ;
    ecx = esi;
    PUSH32(esp, 0x000A8175u); sub_00097C90(); /* call 0x00097C90 */

loc_000A8175: ;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_000A8220; /* je: equal / zero */

loc_000A817D: ;
    ecx = esi;
    PUSH32(esp, 0x000A8184u); sub_00098110(); /* call 0x00098110 */

loc_000A8184: ;
    ecx = MEM32(esi + 0x2C);
    PUSH32(esp, 0);
    PUSH32(esp, 0x278BEC);
    PUSH32(esp, 0x000A8193u); sub_000A2B30(); /* call 0x000A2B30 */

loc_000A8193: ;
    ecx = esi + 0x44;
    PUSH32(esp, 0x000A819Bu); sub_0009BD40(); /* call 0x0009BD40 */

loc_000A819B: ;
    eax = MEM32(esi + 0x10);
    ecx = MEM32(eax + 0x38);
    eax = MEM32(esi + 0x20);
    PUSH32(esp, 0);
    PUSH32(esp, ecx);
    ecx = MEM32(eax + 0x28);
    edx = esi + 0x194;
    PUSH32(esp, edx);
    PUSH32(esp, 0x000A81B6u); sub_00107CC0(); /* call 0x00107CC0 */

loc_000A81B6: ;
    ecx = MEM32(esi + 0x10);
    MEM32(esi + 0x1C0) = 1;
    fp_push(MEMF(ecx + 0x40)); /* fld float */
    edx = MEM32(0x286768);
    fp_top() = fp_top() * MEMF(edx + 0x10); /* fmul dword ptr [edx + 0x10] */
    fp_top() = fp_top() * MEMF(0x225C38); /* fmul dword ptr [0x225c38] */
    fp_top() = MEMF(esi + 0x18) - fp_top(); /* fsubr dword ptr [esi + 0x18] */
    MEMF(esp + 4) = (float)fp_top(); fp_pop(); /* fstp */
    fp_push(MEMF(0x225C20)); /* fld float */
    g_fp_cmp = RECOMP_FCMP(fp_top(), MEMF(esp + 4)); fp_pop(); /* fcomp dword ptr [esp + 4] */
    eax = (eax & 0xFFFF0000u) | (uint32_t)(uint16_t)(((g_fp_top & 7u) << 11) | (g_fp_cmp == 2 ? 0x4500u : g_fp_cmp < 0 ? 0x0100u : g_fp_cmp > 0 ? 0x0000u : 0x4000u)); /* fnstsw ax <- fpu status */
    _fa = (uint32_t)(HI8(eax)) & 0xFFu; _fb = (uint32_t)(5) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test HI8(eax), 5 (8-bit) */
    if (RECOMP_PARITY8((_fa) & (_fb))) goto loc_000A8212; /* jp: parity */

loc_000A81ED: ;
    fp_push(MEMF(esp + 4)); /* fld float */
    fp_push(MEMF(esp + 4)); /* fld float */
    g_fp_cmp = RECOMP_FCMP(fp_top(), MEMF(0x225C28)); fp_pop(); /* fcomp dword ptr [0x225c28] */
    eax = (eax & 0xFFFF0000u) | (uint32_t)(uint16_t)(((g_fp_top & 7u) << 11) | (g_fp_cmp == 2 ? 0x4500u : g_fp_cmp < 0 ? 0x0100u : g_fp_cmp > 0 ? 0x0000u : 0x4000u)); /* fnstsw ax <- fpu status */
    _fa = (uint32_t)(HI8(eax)) & 0xFFu; _fb = (uint32_t)(0x41) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test HI8(eax), 0x41 (8-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_000A820A; /* jne: not equal / not zero */

loc_000A8202: ;
    fp_pop(); /* fstp st(0) */
    fp_push(MEMF(0x225C28)); /* fld float */

loc_000A820A: ;
    MEMF(esi + 0x18) = (float)fp_top(); fp_pop(); /* fstp */
    SET_LO8(eax, 1);
    POP32(esp, esi);
    POP32(esp, ecx);
    esp += 4; return; /* ret */

loc_000A8212: ;
    fp_push(MEMF(0x225C20)); /* fld float */
    SET_LO8(eax, 1);
    MEMF(esi + 0x18) = (float)fp_top(); fp_pop(); /* fstp */
    POP32(esp, esi);
    POP32(esp, ecx);
    esp += 4; return; /* ret */

loc_000A8220: ;
    eax = MEM32(esi + 0x10);
    edx = MEM32(eax + 0x1D0);
    ecx = 0x22F5A0;
    PUSH32(esp, 0x000A8233u); sub_000D54A0(); /* call 0x000D54A0 */

loc_000A8233: ;
    ecx = MEM32(esi + 0x2C);
    edx = MEM32(ecx);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 0);
    PUSH32(esp, 1);
    PUSH32(esp, 0);
    PUSH32(esp, 0);
    PUSH32(esp, 0);
    PUSH32(esp, eax);
    { uint32_t _icall_target = MEM32(edx + 0x6C); PUSH32(esp, 0x000A8246u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_000A8246: ;
    eax = MEM32(esi + 0x24);
    ecx = MEM32(eax + 0x6C);
    PUSH32(esp, 0xFF490DE);
    PUSH32(esp, 0x000A8256u); sub_000885C0(); /* call 0x000885C0 */

loc_000A8256: ;
    SET_LO8(eax, 0); /* xor self */
    POP32(esp, esi);
    POP32(esp, ecx);
    esp += 4; return; /* ret */

    #undef fp_push
    #undef fp_pop
    #undef fp_top
    #undef fp_st
    #undef fp_st1
}
