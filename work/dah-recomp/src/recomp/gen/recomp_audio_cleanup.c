/* Retail DSOUND release/action callbacks observed after logo playback.
 * Byte-checked lifts; see tools/lift_audio_cleanup.py. */
#define RECOMP_GENERATED_CODE
#include "recomp_funcs.h"

/**
 * sub_001ECE7E
 * Original: 0x001ECE7E - 0x001ECEC8 (74 bytes, 23 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_001ECE7E(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_001ECE7E: ;
    PUSH32(esp, esi);
    PUSH32(esp, 0x001ECE84u); sub_001EC935(); /* call 0x001EC935 */

loc_001ECE84: ;
    _fa = (uint32_t)(MEM32(0x20A1B4)) & 0xFFFFFFFFu; _fb = (uint32_t)(0) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(0x20A1B4), 0 (32-bit) */
    esi = ZX8(LO8(eax));
    if (CMP_EQ(_fa, _fb)) goto loc_001ECEA6; /* je: equal / zero */

loc_001ECE90: ;
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(esi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test esi, esi (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_001ECE9F; /* je: equal / zero */

loc_001ECE94: ;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 0x20A1C0);
    { uint32_t _icall_target = MEM32(0x225AC0); PUSH32(esp, 0x001ECE9Fu); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_001ECE9F: ;
    eax = 0x80004005u;
    goto loc_001ECEC4;

loc_001ECEA6: ;
    PUSH32(esp, edi);
    PUSH32(esp, MEM32(esp + 0xC));
    PUSH32(esp, 0x001ECEB0u); sub_001EC7CA(); /* call 0x001EC7CA */

loc_001ECEB0: ;
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(esi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test esi, esi (32-bit) */
    edi = eax;
    if (TEST_Z(_fa, _fb)) goto loc_001ECEC1; /* je: equal / zero */

loc_001ECEB6: ;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 0x20A1C0);
    { uint32_t _icall_target = MEM32(0x225AC0); PUSH32(esp, 0x001ECEC1u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_001ECEC1: ;
    eax = edi;
    POP32(esp, edi);

loc_001ECEC4: ;
    POP32(esp, esi);
    esp += 8; return; /* ret 4 */

}


/**
 * sub_001F50FF
 * Original: 0x001F50FF - 0x001F514E (79 bytes, 28 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_001F50FF(void)
{
    int _flags = 0; /* fallback flag var */

loc_001F50FF: ;
    eax = MEM32(esp + 4);
    eax = eax - 0;
    if ((eax == 0)) goto loc_001F5146; /* je: equal / zero */

loc_001F5108: ;
    eax--;
    if ((eax == 0)) goto loc_001F513F; /* je: equal / zero */

loc_001F510B: ;
    eax--;
    if ((eax == 0)) goto loc_001F5138; /* je: equal / zero */

loc_001F510E: ;
    eax--;
    if ((eax == 0)) goto loc_001F512D; /* je: equal / zero */

loc_001F5111: ;
    eax--;
    if ((eax == 0)) goto loc_001F5122; /* je: equal / zero */

loc_001F5114: ;
    eax--;
    if ((eax != 0)) goto loc_001F514B; /* jne: not equal / not zero */

loc_001F5117: ;
    PUSH32(esp, MEM32(esp + 8));
    PUSH32(esp, 0x001F5120u); sub_001F4865(); /* call 0x001F4865 */

loc_001F5120: ;
    goto loc_001F514B;

loc_001F5122: ;
    PUSH32(esp, MEM32(esp + 8));
    PUSH32(esp, 0x001F512Bu); sub_001F4DD4(); /* call 0x001F4DD4 */

loc_001F512B: ;
    goto loc_001F514B;

loc_001F512D: ;
    PUSH32(esp, MEM32(esp + 8));
    PUSH32(esp, 0x001F5136u); sub_001F4D24(); /* call 0x001F4D24 */

loc_001F5136: ;
    goto loc_001F514B;

loc_001F5138: ;
    PUSH32(esp, 0x001F513Du); sub_001F4C37(); /* call 0x001F4C37 */

loc_001F513D: ;
    goto loc_001F514B;

loc_001F513F: ;
    PUSH32(esp, 0x001F5144u); sub_001F5076(); /* call 0x001F5076 */

loc_001F5144: ;
    goto loc_001F514B;

loc_001F5146: ;
    PUSH32(esp, 0x001F514Bu); sub_001F355A(); /* call 0x001F355A */

loc_001F514B: ;
    esp += 12; return; /* ret 8 */

}


/**
 * sub_001EC7B9
 * Original: 0x001EC7B9 - 0x001EC7CA (17 bytes, 6 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_001EC7B9(void)
{

loc_001EC7B9: ;
    ecx = MEM32(esp + 4);
    MEM32(ecx + 4) = MEM32(ecx + 4) & 0;
    eax = MEM32(ecx);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 1);
    { uint32_t _icall_target = MEM32(eax); PUSH32(esp, 0x001EC7C7u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_001EC7C7: ;
    esp += 8; return; /* ret 4 */

}


/**
 * sub_001F49F9
 * Original: 0x001F49F9 - 0x001F4A40 (71 bytes, 31 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_001F49F9(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_001F49F9: ;
    PUSH32(esp, ebx);
    PUSH32(esp, esi);
    esi = ecx;
    PUSH32(esp, edi);
    edi = esi + 0x68;
    PUSH32(esp, 3);
    ecx = edi;
    PUSH32(esp, 0x001F4A0Au); sub_001F17AD(); /* call 0x001F17AD */

loc_001F4A0A: ;
    ebx = eax;
    _fa = (uint32_t)(ebx) & 0xFFFFFFFFu; _fb = (uint32_t)(ebx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ebx, ebx (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_001F4A3A; /* je: equal / zero */

loc_001F4A10: ;
    eax = MEM32(edi);
    PUSH32(esp, 0);
    ecx = esi;
    MEM8(eax + 0x3F) = 0x80;
    PUSH32(esp, 0x001F4A1Fu); sub_001F4003(); /* call 0x001F4003 */

loc_001F4A1F: ;
    eax = MEM32(esi + 0x80);
    _fa = (uint32_t)(MEM8(eax + 0xA)) & 0xFFu; _fb = (uint32_t)(4) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(eax + 0xA), 4 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_001F4A3A; /* je: equal / zero */

loc_001F4A2B: ;
    eax = MEM32(esi);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 0);
    PUSH32(esp, 0);
    PUSH32(esp, 0);
    PUSH32(esp, 1);
    ecx = esi;
    { uint32_t _icall_target = MEM32(eax + 0x1C); PUSH32(esp, 0x001F4A3Au); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_001F4A3A: ;
    POP32(esp, edi);
    POP32(esp, esi);
    eax = ebx;
    POP32(esp, ebx);
    esp += 4; return; /* ret */

}


/**
 * sub_001EE1DE
 * Original: 0x001EE1DE - 0x001EE1F9 (27 bytes, 10 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_001EE1DE(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_001EE1DE: ;
    PUSH32(esp, esi);
    esi = ecx;
    PUSH32(esp, 0x001EE1E6u); sub_001ECE04(); /* call 0x001ECE04 */

loc_001EE1E6: ;
    _fa = (uint32_t)(MEM8(esp + 8)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(esp + 8), 1 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_001EE1F3; /* je: equal / zero */

loc_001EE1ED: ;
    PUSH32(esp, esi);
    PUSH32(esp, 0x001EE1F3u); sub_001EFB85(); /* call 0x001EFB85 */

loc_001EE1F3: ;
    eax = esi;
    POP32(esp, esi);
    esp += 8; return; /* ret 4 */

}


/**
 * sub_001EF685
 * Original: 0x001EF685 - 0x001EF6A0 (27 bytes, 10 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_001EF685(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_001EF685: ;
    PUSH32(esp, esi);
    esi = ecx;
    PUSH32(esp, 0x001EF68Du); sub_001EEFF1(); /* call 0x001EEFF1 */

loc_001EF68D: ;
    _fa = (uint32_t)(MEM8(esp + 8)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(esp + 8), 1 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_001EF69A; /* je: equal / zero */

loc_001EF694: ;
    PUSH32(esp, esi);
    PUSH32(esp, 0x001EF69Au); sub_001EFB85(); /* call 0x001EFB85 */

loc_001EF69A: ;
    eax = esi;
    POP32(esp, esi);
    esp += 8; return; /* ret 4 */

}


/**
 * sub_001F514E
 * Original: 0x001F514E - 0x001F5169 (27 bytes, 10 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_001F514E(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_001F514E: ;
    PUSH32(esp, esi);
    esi = ecx;
    PUSH32(esp, 0x001F5156u); sub_001F5091(); /* call 0x001F5091 */

loc_001F5156: ;
    _fa = (uint32_t)(MEM8(esp + 8)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(esp + 8), 1 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_001F5163; /* je: equal / zero */

loc_001F515D: ;
    PUSH32(esp, esi);
    PUSH32(esp, 0x001F5163u); sub_001EFB85(); /* call 0x001EFB85 */

loc_001F5163: ;
    eax = esi;
    POP32(esp, esi);
    esp += 8; return; /* ret 4 */

}


/**
 * sub_001F225D
 * Original: 0x001F225D - 0x001F234C (239 bytes, 74 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_001F225D(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_001F225D: ;
    PUSH32(esp, esi);
    esi = ecx;
    eax = 0; /* xor self */
    SET_LO8(eax, MEM8(esi + 0x12));
    PUSH32(esp, edi);
    eax = eax & 1;
    edi = eax;
    if ((eax == 0)) goto loc_001F228F; /* je: equal / zero */

loc_001F226D: ;
    PUSH32(esp, 0);
    PUSH32(esp, 0x001F2274u); sub_001F1FA4(); /* call 0x001F1FA4 */

loc_001F2274: ;
    eax = MEM32(esi + 0x80);
    eax = ZX8(MEM8(eax + 0xE));
    eax--;
    eax = (uint32_t)((int32_t)eax >> 1);
    SET_LO8(eax, LO8(eax) + 1);
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(MEM8(esi + 0x64)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp LO8(eax), MEM8(esi + 0x64) (8-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_001F228F; /* je: equal / zero */

loc_001F2288: ;
    ecx = esi;
    PUSH32(esp, 0x001F228Fu); sub_001F1C42(); /* call 0x001F1C42 */

loc_001F228F: ;
    ecx = esi;
    PUSH32(esp, 0x001F2296u); sub_001F2CFF(); /* call 0x001F2CFF */

loc_001F2296: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_S(_fas, _fbs)) goto loc_001F2349; /* jl: less (signed <) */

loc_001F229E: ;
    edx = MEM32(esi + 0x80);
    ecx = ZX16(MEM16(edx + 0xC));
    ecx--;
    PUSH32(esp, ebx);
    if ((ecx == 0)) goto loc_001F22C9; /* je: equal / zero */

loc_001F22AC: ;
    ecx = ecx - 0x68;
    if ((ecx != 0)) goto loc_001F2301; /* jne: not equal / not zero */

loc_001F22B1: ;
    ecx = esi + 0x84;
    ebx = MEM32(ecx);
    ebx = ebx & 0xFFFEFFFFu;
    ebx = ebx | 0x20000;

loc_001F22C5: ;
    MEM32(ecx) = ebx;
    goto loc_001F2301;

loc_001F22C9: ;
    SET_LO8(ecx, MEM8(edx + 0xF));
    _fa = (uint32_t)(LO8(ecx)) & 0xFFu; _fb = (uint32_t)(8) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp LO8(ecx), 8 (8-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_001F22FA; /* je: equal / zero */

loc_001F22D1: ;
    _fa = (uint32_t)(LO8(ecx)) & 0xFFu; _fb = (uint32_t)(0x10) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp LO8(ecx), 0x10 (8-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_001F22E4; /* je: equal / zero */

loc_001F22D6: ;
    _fa = (uint32_t)(LO8(ecx)) & 0xFFu; _fb = (uint32_t)(0x20) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp LO8(ecx), 0x20 (8-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_001F2301; /* jne: not equal / not zero */

loc_001F22DB: ;
    MEM8(esi + 0x86) = MEM8(esi + 0x86) | 3;
    goto loc_001F2301;

loc_001F22E4: ;
    ecx = esi + 0x84;
    ebx = MEM32(ecx);
    ebx = ebx & 0xFFFDFFFFu;
    ebx = ebx | 0x10000;
    goto loc_001F22C5;

loc_001F22FA: ;
    MEM8(esi + 0x86) = MEM8(esi + 0x86) & 0xFC;

loc_001F2301: ;
    ecx = ZX8(MEM8(edx + 0xE));
    ecx--;
    ecx = ecx << 0x12;
    ecx = ecx ^ MEM32(esi + 0x84);
    POP32(esp, ebx);
    ecx = ecx & 0x7C0000;
    MEM32(esi + 0x84) = MEM32(esi + 0x84) ^ ecx;
    _fa = (uint32_t)(MEM8(edx + 0xE)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(edx + 0xE), 1 (8-bit) */
    ecx = MEM32(esi + 0x84);
    if (CMP_BE(_fa, _fb)) goto loc_001F2330; /* jbe: below or equal (unsigned <=) */

loc_001F2328: ;
    ecx = ecx | 0x800000;
    goto loc_001F2336;

loc_001F2330: ;
    ecx = ecx & 0xFF7FFFFFu;

loc_001F2336: ;
    _fa = (uint32_t)(edi) & 0xFFFFFFFFu; _fb = (uint32_t)(edi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test edi, edi (32-bit) */
    MEM32(esi + 0x84) = ecx;
    if (TEST_Z(_fa, _fb)) goto loc_001F2349; /* je: equal / zero */

loc_001F2340: ;
    POP32(esp, edi);
    ecx = esi;
    POP32(esp, esi);
    g_seh_ebp = ebp; sub_001F3BB4(); return; /* tail jmp 0x001F3BB4 */

loc_001F2349: ;
    POP32(esp, edi);
    POP32(esp, esi);
    esp += 4; return; /* ret */

}


/**
 * sub_001F1C82
 * Original: 0x001F1C82 - 0x001F1CB1 (47 bytes, 13 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_001F1C82(void)
{

loc_001F1C82: ;
    eax = MEM32(esp + 4);
    edx = MEM32(esp + 8);
    eax = eax << 5;
    eax = eax + ecx + 0xD0;
    MEM32(eax + 0x18) = edx;
    edx = MEM32(esp + 0xC);
    MEM32(eax + 0x1C) = edx;
    edx = MEM32(esp + 0x10);
    MEM32(eax + 0x14) = edx;
    ecx = MEM32(ecx + 8);
    PUSH32(esp, eax);
    PUSH32(esp, 0x001F1CAEu); sub_001F15EB(); /* call 0x001F15EB */

loc_001F1CAE: ;
    esp += 20; return; /* ret 16 */

}


/**
 * sub_001F24F3
 * Original: 0x001F24F3 - 0x001F250E (27 bytes, 10 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_001F24F3(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_001F24F3: ;
    PUSH32(esp, esi);
    esi = ecx;
    PUSH32(esp, 0x001F24FBu); sub_001F2200(); /* call 0x001F2200 */

loc_001F24FB: ;
    _fa = (uint32_t)(MEM8(esp + 8)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(esp + 8), 1 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_001F2508; /* je: equal / zero */

loc_001F2502: ;
    PUSH32(esp, esi);
    PUSH32(esp, 0x001F2508u); sub_001EFB85(); /* call 0x001EFB85 */

loc_001F2508: ;
    eax = esi;
    POP32(esp, esi);
    esp += 8; return; /* ret 4 */

}


/**
 * sub_001F24A8
 * Original: 0x001F24A8 - 0x001F24F3 (75 bytes, 27 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_001F24A8(void)
{
    int _flags = 0; /* fallback flag var */

loc_001F24A8: ;
    eax = MEM32(esp + 4);
    eax = eax - 0;
    if ((eax == 0)) goto loc_001F24EB; /* je: equal / zero */

loc_001F24B1: ;
    eax--;
    if ((eax == 0)) goto loc_001F24E4; /* je: equal / zero */

loc_001F24B4: ;
    eax--;
    if ((eax == 0)) goto loc_001F24DD; /* je: equal / zero */

loc_001F24B7: ;
    eax--;
    if ((eax == 0)) goto loc_001F24D6; /* je: equal / zero */

loc_001F24BA: ;
    eax--;
    if ((eax == 0)) goto loc_001F24CB; /* je: equal / zero */

loc_001F24BD: ;
    eax--;
    if ((eax != 0)) goto loc_001F24F0; /* jne: not equal / not zero */

loc_001F24C0: ;
    PUSH32(esp, MEM32(esp + 8));
    PUSH32(esp, 0x001F24C9u); sub_001F241A(); /* call 0x001F241A */

loc_001F24C9: ;
    goto loc_001F24F0;

loc_001F24CB: ;
    PUSH32(esp, MEM32(esp + 8));
    PUSH32(esp, 0x001F24D4u); sub_001F18C5(); /* call 0x001F18C5 */

loc_001F24D4: ;
    goto loc_001F24F0;

loc_001F24D6: ;
    PUSH32(esp, 0x001F24DBu); sub_001F2084(); /* call 0x001F2084 */

loc_001F24DB: ;
    goto loc_001F24F0;

loc_001F24DD: ;
    PUSH32(esp, 0x001F24E2u); sub_001F1E8C(); /* call 0x001F1E8C */

loc_001F24E2: ;
    goto loc_001F24F0;

loc_001F24E4: ;
    PUSH32(esp, 0x001F24E9u); sub_001F1C42(); /* call 0x001F1C42 */

loc_001F24E9: ;
    goto loc_001F24F0;

loc_001F24EB: ;
    PUSH32(esp, 0x001F24F0u); sub_001F355A(); /* call 0x001F355A */

loc_001F24F0: ;
    esp += 12; return; /* ret 8 */

}


/**
 * sub_001ED372
 * Original: 0x001ED372 - 0x001ED3BD (75 bytes, 22 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_001ED372(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_001ED372: ;
    PUSH32(esp, esi);
    PUSH32(esp, 0x001ED378u); sub_001EC935(); /* call 0x001EC935 */

loc_001ED378: ;
    _fa = (uint32_t)(MEM32(0x20A1B4)) & 0xFFFFFFFFu; _fb = (uint32_t)(0) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(0x20A1B4), 0 (32-bit) */
    esi = ZX8(LO8(eax));
    if (CMP_EQ(_fa, _fb)) goto loc_001ED39A; /* je: equal / zero */

loc_001ED384: ;
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(esi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test esi, esi (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_001ED393; /* je: equal / zero */

loc_001ED388: ;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 0x20A1C0);
    { uint32_t _icall_target = MEM32(0x225AC0); PUSH32(esp, 0x001ED393u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_001ED393: ;
    eax = 0x80004005u;
    goto loc_001ED3B9;

loc_001ED39A: ;
    eax = MEM32(esp + 8);
    ecx = MEM32(eax + 0x24);
    PUSH32(esp, 0);
    PUSH32(esp, 0x001ED3A8u); sub_001F1FA4(); /* call 0x001F1FA4 */

loc_001ED3A8: ;
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(esi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test esi, esi (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_001ED3B7; /* je: equal / zero */

loc_001ED3AC: ;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 0x20A1C0);
    { uint32_t _icall_target = MEM32(0x225AC0); PUSH32(esp, 0x001ED3B7u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_001ED3B7: ;
    eax = 0; /* xor self */

loc_001ED3B9: ;
    POP32(esp, esi);
    esp += 8; return; /* ret 4 */

}


/**
 * sub_001ED270
 * Original: 0x001ED270 - 0x001ED2BE (78 bytes, 25 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_001ED270(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_001ED270: ;
    PUSH32(esp, esi);
    PUSH32(esp, 0x001ED276u); sub_001EC935(); /* call 0x001EC935 */

loc_001ED276: ;
    _fa = (uint32_t)(MEM32(0x20A1B4)) & 0xFFFFFFFFu; _fb = (uint32_t)(0) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(0x20A1B4), 0 (32-bit) */
    esi = ZX8(LO8(eax));
    if (CMP_EQ(_fa, _fb)) goto loc_001ED298; /* je: equal / zero */

loc_001ED282: ;
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(esi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test esi, esi (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_001ED291; /* je: equal / zero */

loc_001ED286: ;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 0x20A1C0);
    { uint32_t _icall_target = MEM32(0x225AC0); PUSH32(esp, 0x001ED291u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_001ED291: ;
    eax = 0x80004005u;
    goto loc_001ED2BA;

loc_001ED298: ;
    eax = MEM32(esp + 8);
    PUSH32(esp, edi);
    eax = eax + 4;
    PUSH32(esp, eax);
    PUSH32(esp, 0x001ED2A6u); sub_001EC7CA(); /* call 0x001EC7CA */

loc_001ED2A6: ;
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(esi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test esi, esi (32-bit) */
    edi = eax;
    if (TEST_Z(_fa, _fb)) goto loc_001ED2B7; /* je: equal / zero */

loc_001ED2AC: ;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 0x20A1C0);
    { uint32_t _icall_target = MEM32(0x225AC0); PUSH32(esp, 0x001ED2B7u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_001ED2B7: ;
    eax = edi;
    POP32(esp, edi);

loc_001ED2BA: ;
    POP32(esp, esi);
    esp += 8; return; /* ret 4 */

}


/**
 * sub_001ED3BD
 * Original: 0x001ED3BD - 0x001ED40E (81 bytes, 25 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_001ED3BD(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_001ED3BD: ;
    PUSH32(esp, esi);
    PUSH32(esp, 0x001ED3C3u); sub_001EC935(); /* call 0x001EC935 */

loc_001ED3C3: ;
    _fa = (uint32_t)(MEM32(0x20A1B4)) & 0xFFFFFFFFu; _fb = (uint32_t)(0) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(0x20A1B4), 0 (32-bit) */
    esi = ZX8(LO8(eax));
    if (CMP_EQ(_fa, _fb)) goto loc_001ED3E5; /* je: equal / zero */

loc_001ED3CF: ;
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(esi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test esi, esi (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_001ED3DE; /* je: equal / zero */

loc_001ED3D3: ;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 0x20A1C0);
    { uint32_t _icall_target = MEM32(0x225AC0); PUSH32(esp, 0x001ED3DEu); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_001ED3DE: ;
    eax = 0x80004005u;
    goto loc_001ED40A;

loc_001ED3E5: ;
    eax = MEM32(esp + 8);
    ecx = MEM32(eax + 0x24);
    PUSH32(esp, edi);
    PUSH32(esp, MEM32(esp + 0x10));
    PUSH32(esp, 0x001ED3F6u); sub_001F1937(); /* call 0x001F1937 */

loc_001ED3F6: ;
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(esi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test esi, esi (32-bit) */
    edi = eax;
    if (TEST_Z(_fa, _fb)) goto loc_001ED407; /* je: equal / zero */

loc_001ED3FC: ;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 0x20A1C0);
    { uint32_t _icall_target = MEM32(0x225AC0); PUSH32(esp, 0x001ED407u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_001ED407: ;
    eax = edi;
    POP32(esp, edi);

loc_001ED40A: ;
    POP32(esp, esi);
    esp += 12; return; /* ret 8 */

}
