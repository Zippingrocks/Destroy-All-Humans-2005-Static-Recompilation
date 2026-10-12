/* Generated only from the retail XBE for crash 5CE241E1BBDBD156. */
#define RECOMP_GENERATED_CODE
#include "recomp_funcs.h"

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
 * sub_00075410
 * Original: 0x00075410 - 0x0007542E (30 bytes, 11 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00075410(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00075410: ;
    PUSH32(esp, esi);
    esi = ecx;
    PUSH32(esp, 0x00075418u); sub_00075340(); /* call 0x00075340 */

loc_00075418: ;
    _fa = (uint32_t)(MEM8(esp + 8)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(esp + 8), 1 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00075428; /* je: equal / zero */

loc_0007541F: ;
    PUSH32(esp, esi);
    PUSH32(esp, 0x00075425u); sub_0006B710(); /* call 0x0006B710 */

loc_00075425: ;
    esp = esp + 4;

loc_00075428: ;
    eax = esi;
    POP32(esp, esi);
    esp += 8; return; /* ret 4 */

}
