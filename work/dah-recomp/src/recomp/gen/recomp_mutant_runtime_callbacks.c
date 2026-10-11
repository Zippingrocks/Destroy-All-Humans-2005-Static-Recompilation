#define RECOMP_GENERATED_CODE
#include "recomp_funcs.h"

/**
 * sub_00130B20
 * Original: 0x00130B20 - 0x00130B3B (27 bytes, 8 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00130B20(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00130B20: ;
    eax = MEM32(esp + 4);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0x1CCAFDCC) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0x1CCAFDCC (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_00130B30; /* jne: not equal / not zero */

loc_00130B2B: ;
    SET_LO8(eax, 1);
    esp += 8; return; /* ret 4 */

loc_00130B30: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0x3F36394C) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0x3F36394C (32-bit) */
    SET_LO8(eax, (CMP_EQ(_fa, _fb)) ? 1 : 0); /* sete */
    esp += 8; return; /* ret 4 */

}

/**
 * sub_000242F0
 * Original: 0x000242F0 - 0x0002431B (43 bytes, 13 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_000242F0(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_000242F0: ;
    PUSH32(esp, esi);
    esi = ecx;
    MEM32(esi) = 0x2279F4;
    MEM32(esi + 0x48) = 0x2279EC;
    PUSH32(esp, 0x00024305u); sub_000221C0(); /* call 0x000221C0 */

loc_00024305: ;
    _fa = (uint32_t)(MEM8(esp + 8)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(esp + 8), 1 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00024315; /* je: equal / zero */

loc_0002430C: ;
    PUSH32(esp, esi);
    PUSH32(esp, 0x00024312u); sub_0006B710(); /* call 0x0006B710 */

loc_00024312: ;
    esp = esp + 4;

loc_00024315: ;
    eax = esi;
    POP32(esp, esi);
    esp += 8; return; /* ret 4 */

}

/**
 * sub_0011CB60
 * Original: 0x0011CB60 - 0x0011CB68 (8 bytes, 2 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0011CB60(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_0011CB60: ;
    ecx = ecx - 0x10;
    g_seh_ebp = ebp; sub_000C7CA0(); return; /* tail jmp 0x000C7CA0 */

}

/**
 * sub_0014A290
 * Original: 0x0014A290 - 0x0014A2DA (74 bytes, 30 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0014A290(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_0014A290: ;
    PUSH32(esp, esi);
    esi = MEM32(esp + 8);
    edx = MEM32(esi + 0xC);
    _fa = (uint32_t)(edx) & 0xFFFFFFFFu; _fb = (uint32_t)(edx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test edx, edx (32-bit) */
    eax = esi;
    if (TEST_Z(_fa, _fb)) goto loc_0014A2A9; /* je: equal / zero */

loc_0014A29E: ;
    edi = edi;

loc_0014A2A0: ;
    eax = edx;
    edx = MEM32(eax + 0xC);
    _fa = (uint32_t)(edx) & 0xFFFFFFFFu; _fb = (uint32_t)(edx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test edx, edx (32-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_0014A2A0; /* jne: not equal / not zero */

loc_0014A2A9: ;
    MEM32(ecx + 8) = eax;
    eax = MEM32(esi + 4);
    esi = MEM32(esp + 0xC);
    MEM32(ecx + 0xC) = eax;
    edx = MEM32(esi + 0xC);
    _fa = (uint32_t)(edx) & 0xFFFFFFFFu; _fb = (uint32_t)(edx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test edx, edx (32-bit) */
    eax = esi;
    if (TEST_Z(_fa, _fb)) goto loc_0014A2C9; /* je: equal / zero */

loc_0014A2BF: ;
    /* nop */

loc_0014A2C0: ;
    eax = edx;
    edx = MEM32(eax + 0xC);
    _fa = (uint32_t)(edx) & 0xFFFFFFFFu; _fb = (uint32_t)(edx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test edx, edx (32-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_0014A2C0; /* jne: not equal / not zero */

loc_0014A2C9: ;
    MEM32(ecx + 0x10) = eax;
    edx = MEM32(esi + 4);
    MEM32(ecx + 0x14) = edx;
    MEM8(ecx + 4) = 1;
    POP32(esp, esi);
    esp += 12; return; /* ret 8 */

}

/**
 * sub_00078040
 * Original: 0x00078040 - 0x0007805E (30 bytes, 11 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00078040(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00078040: ;
    PUSH32(esp, esi);
    esi = ecx;
    PUSH32(esp, 0x00078048u); sub_00077FB0(); /* call 0x00077FB0 */

loc_00078048: ;
    _fa = (uint32_t)(MEM8(esp + 8)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(esp + 8), 1 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00078058; /* je: equal / zero */

loc_0007804F: ;
    PUSH32(esp, esi);
    PUSH32(esp, 0x00078055u); sub_0006B710(); /* call 0x0006B710 */

loc_00078055: ;
    esp = esp + 4;

loc_00078058: ;
    eax = esi;
    POP32(esp, esi);
    esp += 8; return; /* ret 4 */

}
