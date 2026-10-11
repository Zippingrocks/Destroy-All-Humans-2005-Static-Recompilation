/* Retail startup cleanup callbacks reached after the logo movies.
 * Byte-checked lifts; see tools/lift_startup_cleanup.py. */
#define RECOMP_GENERATED_CODE
#include "recomp_funcs.h"

/**
 * sub_00063510
 * Original: 0x00063510 - 0x00063549 (57 bytes, 20 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00063510(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00063510: ;
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    edi = MEM32(esp + 0xC);
    _fa = (uint32_t)(MEM32(edi + 4)) & 0xFFFFFFFFu; _fb = (uint32_t)(0xF) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(edi + 4), 0xF (32-bit) */
    esi = ecx;
    if (CMP_NE(_fa, _fb)) goto loc_0006353C; /* jne: not equal / not zero */

loc_0006351E: ;
    SET_LO8(eax, MEM8(esi + 0x98));
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0006353C; /* je: equal / zero */

loc_00063528: ;
    PUSH32(esp, 0x0006352Du); sub_000D83E0(); /* call 0x000D83E0 */

loc_0006352D: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(MEM32(esi + 0x9C)) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, MEM32(esi + 0x9C) (32-bit) */
    if (CMP_B(_fa, _fb)) goto loc_0006353C; /* jb: below (unsigned <) */

loc_00063535: ;
    ecx = esi;
    PUSH32(esp, 0x0006353Cu); sub_00063320(); /* call 0x00063320 */

loc_0006353C: ;
    PUSH32(esp, edi);
    ecx = esi;
    PUSH32(esp, 0x00063544u); sub_000FDFD0(); /* call 0x000FDFD0 */

loc_00063544: ;
    POP32(esp, edi);
    POP32(esp, esi);
    esp += 8; return; /* ret 4 */

}


/**
 * sub_00068B50
 * Original: 0x00068B50 - 0x00068B6E (30 bytes, 11 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00068B50(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00068B50: ;
    PUSH32(esp, esi);
    esi = ecx;
    PUSH32(esp, 0x00068B58u); sub_00068220(); /* call 0x00068220 */

loc_00068B58: ;
    _fa = (uint32_t)(MEM8(esp + 8)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(esp + 8), 1 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00068B68; /* je: equal / zero */

loc_00068B5F: ;
    PUSH32(esp, esi);
    PUSH32(esp, 0x00068B65u); sub_0006B710(); /* call 0x0006B710 */

loc_00068B65: ;
    esp = esp + 4;

loc_00068B68: ;
    eax = esi;
    POP32(esp, esi);
    esp += 8; return; /* ret 4 */

}


/**
 * sub_000F7180
 * Original: 0x000F7180 - 0x000F71C3 (67 bytes, 21 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_000F7180(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_000F7180: ;
    PUSH32(esp, esi);
    esi = ecx;
    eax = MEM32(esi + 4);
    ecx = MEM32(0x250EC4);
    PUSH32(esp, eax);
    PUSH32(esp, 0x000F7192u); sub_000E3200(); /* call 0x000E3200 */

loc_000F7192: ;
    eax = MEM32(esi + 4);
    ecx = MEM32(0x2745B4);
    PUSH32(esp, eax);
    PUSH32(esp, 0x000F71A1u); sub_000CE640(); /* call 0x000CE640 */

loc_000F71A1: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0xFFFFFFFFu) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0xFFFFFFFFu (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_000F71C1; /* je: equal / zero */

loc_000F71A6: ;
    esi = MEM32(esi + 4);
    ecx = MEM32(0x2745B4);
    PUSH32(esp, esi);
    PUSH32(esp, 0x000F71B5u); sub_000CE640(); /* call 0x000CE640 */

loc_000F71B5: ;
    ecx = MEM32(0x2745B4);
    PUSH32(esp, eax);
    PUSH32(esp, 0x000F71C1u); sub_000CE6C0(); /* call 0x000CE6C0 */

loc_000F71C1: ;
    POP32(esp, esi);
    esp += 4; return; /* ret */

}


/**
 * sub_0013C5A6
 * Original: 0x0013C5A6 - 0x0013C5F1 (75 bytes, 38 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0013C5A6(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_0013C5A6: ;
    eax = MEM32(esp + 4);
    PUSH32(esp, ebx);
    SET_LO8(ebx, MEM8(0x259BF4));
    goto loc_0013C5B8;

loc_0013C5B3: ;
    _fa = (uint32_t)(LO8(ecx)) & 0xFFu; _fb = (uint32_t)(LO8(ebx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp LO8(ecx), LO8(ebx) (8-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_0013C5BE; /* je: equal / zero */

loc_0013C5B7: ;
    eax = eax + 1;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fas = (int32_t)(int32_t)_fa; /* inc flags snapshot */

loc_0013C5B8: ;
    SET_LO8(ecx, MEM8(eax));
    _fa = (uint32_t)(LO8(ecx)) & 0xFFu; _fb = (uint32_t)(LO8(ecx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(ecx), LO8(ecx) (8-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_0013C5B3; /* jne: not equal / not zero */

loc_0013C5BE: ;
    SET_LO8(ecx, MEM8(eax));
    eax = eax + 1;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fas = (int32_t)(int32_t)_fa; /* inc flags snapshot */
    _fa = (uint32_t)(LO8(ecx)) & 0xFFu; _fb = (uint32_t)(LO8(ecx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(ecx), LO8(ecx) (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0013C5EF; /* je: equal / zero */

loc_0013C5C5: ;
    goto loc_0013C5D2;

loc_0013C5C7: ;
    _fa = (uint32_t)(LO8(ecx)) & 0xFFu; _fb = (uint32_t)(0x65) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp LO8(ecx), 0x65 (8-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_0013C5D8; /* je: equal / zero */

loc_0013C5CC: ;
    _fa = (uint32_t)(LO8(ecx)) & 0xFFu; _fb = (uint32_t)(0x45) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp LO8(ecx), 0x45 (8-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_0013C5D8; /* je: equal / zero */

loc_0013C5D1: ;
    eax = eax + 1;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fas = (int32_t)(int32_t)_fa; /* inc flags snapshot */

loc_0013C5D2: ;
    SET_LO8(ecx, MEM8(eax));
    _fa = (uint32_t)(LO8(ecx)) & 0xFFu; _fb = (uint32_t)(LO8(ecx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(ecx), LO8(ecx) (8-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_0013C5C7; /* jne: not equal / not zero */

loc_0013C5D8: ;
    edx = eax;

loc_0013C5DA: ;
    eax = eax - 1;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fas = (int32_t)(int32_t)_fa; /* dec flags snapshot */
    _fa = (uint32_t)(MEM8(eax)) & 0xFFu; _fb = (uint32_t)(0x30) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(eax), 0x30 (8-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_0013C5DA; /* je: equal / zero */

loc_0013C5E0: ;
    _fa = (uint32_t)(MEM8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(ebx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(eax), LO8(ebx) (8-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_0013C5E5; /* jne: not equal / not zero */

loc_0013C5E4: ;
    eax = eax - 1;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fas = (int32_t)(int32_t)_fa; /* dec flags snapshot */

loc_0013C5E5: ;
    SET_LO8(ecx, MEM8(edx));
    eax = eax + 1;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fas = (int32_t)(int32_t)_fa; /* inc flags snapshot */
    edx = edx + 1;
    _fa = (uint32_t)(edx) & 0xFFFFFFFFu; _fas = (int32_t)(int32_t)_fa; /* inc flags snapshot */
    _fa = (uint32_t)(LO8(ecx)) & 0xFFu; _fb = (uint32_t)(LO8(ecx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(ecx), LO8(ecx) (8-bit) */
    MEM8(eax) = LO8(ecx);
    if (TEST_NZ(_fa, _fb)) goto loc_0013C5E5; /* jne: not equal / not zero */

loc_0013C5EF: ;
    POP32(esp, ebx);
    esp += 4; return; /* ret */

}


/**
 * sub_00188750
 * Original: 0x00188750 - 0x00188778 (40 bytes, 15 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00188750(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00188750: ;
    PUSH32(esp, esi);
    esi = ecx;
    PUSH32(esp, 0x00188758u); sub_0018DE10(); /* call 0x0018DE10 */

loc_00188758: ;
    _fa = (uint32_t)(MEM8(esp + 8)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(esp + 8), 1 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00188772; /* je: equal / zero */

loc_0018875F: ;
    edx = ZX16(MEM16(esi + 4));
    ecx = MEM32(0x270A80);
    eax = MEM32(ecx);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 6);
    PUSH32(esp, edx);
    PUSH32(esp, esi);
    { uint32_t _icall_target = MEM32(eax + 0x14); PUSH32(esp, 0x00188772u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00188772: ;
    eax = esi;
    POP32(esp, esi);
    esp += 8; return; /* ret 4 */

}


/**
 * sub_001F4ADB
 * Original: 0x001F4ADB - 0x001F4B0A (47 bytes, 13 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_001F4ADB(void)
{

loc_001F4ADB: ;
    eax = MEM32(esp + 4);
    edx = MEM32(esp + 8);
    eax = eax << 5;
    eax = eax + ecx + 0x88;
    MEM32(eax + 0x18) = edx;
    edx = MEM32(esp + 0xC);
    MEM32(eax + 0x1C) = edx;
    edx = MEM32(esp + 0x10);
    MEM32(eax + 0x14) = edx;
    ecx = MEM32(ecx + 8);
    PUSH32(esp, eax);
    PUSH32(esp, 0x001F4B07u); sub_001F15EB(); /* call 0x001F15EB */

loc_001F4B07: ;
    esp += 20; return; /* ret 16 */

}


/**
 * sub_0020B060
 * Original: 0x0020B060 - 0x0020B079 (25 bytes, 7 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0020B060(void)
{

loc_0020B060: ;
    eax = MEM32(esp + 4);
    ecx = MEM32(0x28EECC);
    eax = eax + 0xFC;
    PUSH32(esp, eax);
    PUSH32(esp, ecx);
    PUSH32(esp, 0x0020B076u); sub_0020E840(); /* call 0x0020E840 */

loc_0020B076: ;
    esp += 8; return; /* ret 4 */

}


/**
 * sub_0020E010
 * Original: 0x0020E010 - 0x0020E08D (125 bytes, 35 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0020E010(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_0020E010: ;
    PUSH32(esp, esi);
    esi = MEM32(esp + 8);
    eax = MEM32(esi + 0x7C);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0020E089; /* je: equal / zero */

loc_0020E01C: ;
    PUSH32(esp, eax);
    PUSH32(esp, 0x0020E022u); sub_001EDC45(); /* call 0x001EDC45 */

loc_0020E022: ;
    MEM32(esi + 0xA4) = 1;
    ecx = MEM32(esi + 0x7C);
    PUSH32(esp, ecx);
    PUSH32(esp, 0x0020E035u); sub_001EC9DC(); /* call 0x001EC9DC */

loc_0020E035: ;
    edx = MEM32(esi + 0x80);
    PUSH32(esp, edx);
    MEM32(esi + 0x7C) = 0;
    PUSH32(esp, 0x0020E048u); sub_0017BD40(); /* call 0x0017BD40 */

loc_0020E048: ;
    ecx = MEM32(0x292914);
    eax = MEM32(0x29292C);
    ecx--;
    eax--;
    MEM32(0x292914) = ecx;
    MEM32(0x29292C) = eax;
    if ((eax != 0)) goto loc_0020E089; /* jne: not equal / not zero */

loc_0020E062: ;
    eax = MEM32(0x292910);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0020E089; /* je: equal / zero */

loc_0020E06B: ;
    eax = MEM32(0x29290C);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0020E089; /* je: equal / zero */

loc_0020E074: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0xFFFFFFFFu) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0xFFFFFFFFu (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_0020E089; /* je: equal / zero */

loc_0020E079: ;
    PUSH32(esp, eax);
    PUSH32(esp, 0x0020E07Fu); sub_001EC9C1(); /* call 0x001EC9C1 */

loc_0020E07F: ;
    MEM32(0x29290C) = 0xFFFFFFFFu;

loc_0020E089: ;
    POP32(esp, esi);
    esp += 8; return; /* ret 4 */

}
