/* Retail HypnoRay cleanup callback at 0x0009A950. The original disassembler
 * missed the function boundary because it is a short vtable thunk between
 * two runs of INT3 padding. Byte-checked against default.xbe. */
#define RECOMP_GENERATED_CODE
#include "recomp_funcs.h"

void sub_0009A950(void)
{
    uint32_t ebp;
    ebp = g_ebp;
    ebp = g_seh_ebp;

    {
        uint32_t _icall_esp = g_esp;
        PUSH32(esp, esi);
        esi = ecx;
        eax = MEM32(esi);
        PUSH32(esp, 1);
        {
            uint32_t _icall_target = MEM32(eax + 0x60);
            PUSH32(esp, 0x0009A95Au);
            RECOMP_ICALL_SAFE(_icall_target, _icall_esp);
        }
    }

    ecx = esi;
    POP32(esp, esi);
    g_seh_ebp = ebp;
    sub_00097C00();
}
