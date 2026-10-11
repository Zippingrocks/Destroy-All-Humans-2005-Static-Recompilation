#define RECOMP_GENERATED_CODE
#include "recomp_funcs.h"

/**
 * sub_000A6AF0
 * Original: 0x000A6AF0 - 0x000A6B59 (105 bytes, 37 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_000A6AF0(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_000A6AF0: ;
    PUSH32(esp, esi);
    esi = ecx;
    eax = MEM32(esi + 0x48);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_000A6B14; /* jne: not equal / not zero */

loc_000A6AFA: ;
    eax = MEM32(esi + 0x24);
    ecx = MEM32(eax + 0x34);
    edx = MEM32(ecx);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 0);
    PUSH32(esp, 1);
    PUSH32(esp, 0);
    PUSH32(esp, 0);
    PUSH32(esp, 0);
    PUSH32(esp, 0x3D21A67C);
    { uint32_t _icall_target = MEM32(edx + 0x6C); PUSH32(esp, 0x000A6B14u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_000A6B14: ;
    _fa = (uint32_t)(MEM32(esi + 0x48)) & 0xFFFFFFFFu; _fb = (uint32_t)(1) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(esi + 0x48), 1 (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_000A6B37; /* jne: not equal / not zero */

loc_000A6B1A: ;
    ecx = esi;
    PUSH32(esp, 0x000A6B21u); sub_00097C90(); /* call 0x00097C90 */

loc_000A6B21: ;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_000A6B37; /* je: equal / zero */

loc_000A6B25: ;
    MEM32(esi + 0x48) = 2;
    MEM32(esi + 0x50) = 0;
    SET_LO8(eax, 1);
    POP32(esp, esi);
    esp += 4; return; /* ret */

loc_000A6B37: ;
    eax = MEM32(esi + 0x10);
    ecx = MEM32(eax + 0x3C);
    edx = MEM32(esi + 0x20);
    PUSH32(esp, 0x3F800000);
    PUSH32(esp, ecx);
    ecx = MEM32(edx + 0x28);
    PUSH32(esp, 0x000A6B4Eu); sub_00107C00(); /* call 0x00107C00 */

loc_000A6B4E: ;
    MEM32(esi + 0x48) = 0;
    SET_LO8(eax, 0); /* xor self */
    POP32(esp, esi);
    esp += 4; return; /* ret */

}
