#define RECOMP_GENERATED_CODE
#include "recomp_funcs.h"

/**
 * sub_000A21A0
 * Original: 0x000A21A0 - 0x000A21B2 (18 bytes, 8 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_000A21A0(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_000A21A0: ;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, esi);
    esi = ecx;
    eax = MEM32(esi);
    PUSH32(esp, 0);
    { uint32_t _icall_target = MEM32(eax + 0x60); PUSH32(esp, 0x000A21AAu); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_000A21AA: ;
    ecx = esi;
    POP32(esp, esi);
    g_seh_ebp = ebp; sub_00097C00(); return; /* tail jmp 0x00097C00 */

}
