#define RECOMP_GENERATED_CODE
#include "recomp_funcs.h"

/**
 * sub_00034C70
 * Original: 0x00034C70 - 0x00034C8B (27 bytes, 8 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00034C70(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00034C70: ;
    eax = MEM32(esp + 4);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0x5355F7F9) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0x5355F7F9 (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_00034C80; /* jne: not equal / not zero */

loc_00034C7B: ;
    SET_LO8(eax, 1);
    esp += 8; return; /* ret 4 */

loc_00034C80: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0x455D1F89) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0x455D1F89 (32-bit) */
    SET_LO8(eax, (CMP_EQ(_fa, _fb)) ? 1 : 0); /* sete */
    esp += 8; return; /* ret 4 */

}

/**
 * sub_00035000
 * Original: 0x00035000 - 0x0003500E (14 bytes, 6 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00035000(void)
{

loc_00035000: ;
    PUSH32(esp, esi);
    esi = ecx;
    PUSH32(esp, 0x00035008u); sub_00032900(); /* call 0x00032900 */

loc_00035008: ;
    MEM8(esi + 0x7C) = 1;
    POP32(esp, esi);
    esp += 4; return; /* ret */

}
