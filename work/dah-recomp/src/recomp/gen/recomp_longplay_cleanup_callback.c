#define RECOMP_GENERATED_CODE
#include "recomp_funcs.h"

/**
 * sub_0002A1A0
 * Original: 0x0002A1A0 - 0x0002A1EA (74 bytes, 19 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0002A1A0(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_0002A1A0: ;
    PUSH32(esp, esi);
    esi = ecx;
    ecx = esi + 0x13C;
    MEM32(esi) = 0x2280A0;
    MEM32(esi + 0x48) = 0x228098;
    PUSH32(esp, 0x0002A1BBu); sub_00131990(); /* call 0x00131990 */

loc_0002A1BB: ;
    ecx = esi + 0xB0;
    PUSH32(esp, 0x0002A1C6u); sub_00131990(); /* call 0x00131990 */

loc_0002A1C6: ;
    ecx = esi;
    MEM32(esi + 0x48) = 0x226F44;
    PUSH32(esp, 0x0002A1D4u); sub_0001AF40(); /* call 0x0001AF40 */

loc_0002A1D4: ;
    _fa = (uint32_t)(MEM8(esp + 8)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(esp + 8), 1 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0002A1E4; /* je: equal / zero */

loc_0002A1DB: ;
    PUSH32(esp, esi);
    PUSH32(esp, 0x0002A1E1u); sub_0006B710(); /* call 0x0006B710 */

loc_0002A1E1: ;
    esp = esp + 4;

loc_0002A1E4: ;
    eax = esi;
    POP32(esp, esi);
    esp += 8; return; /* ret 4 */

}
