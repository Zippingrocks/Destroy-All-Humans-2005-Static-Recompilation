/* Retail Rockwell event callback observed from 0x000A3A44, 0x000A3D18,
 * and 0x000A4BD8. Byte-checked lift; see
 * tools/lift_rockwell_event_callback.py. */
#define RECOMP_GENERATED_CODE
#include "recomp_funcs.h"

void sub_000A3720(void)
{
    uint32_t ebp;
    ebp = g_ebp;
    int _flags = 0;
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_flags; (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    ebp = g_seh_ebp;

loc_000A3720: ;
    PUSH32(esp, esi);
    esi = ecx;
    ecx = MEM32(esi + 0x20);
    eax = MEM32(ecx + 0xD0);
    eax = eax >> 8;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu;
    _fb = 1;
    _fas = (int32_t)(int8_t)_fa;
    _fbs = 1;
    if (TEST_NZ(_fa, _fb)) goto loc_000A3748;

    edx = MEM32(ecx);
    {
        uint32_t _icall_esp = g_esp;
        PUSH32(esp, 1);
        PUSH32(esp, 0);
        PUSH32(esp, 0);
        PUSH32(esp, 0);
        PUSH32(esp, 0xD718C982u);
        {
            uint32_t _icall_target = MEM32(edx + 0x140);
            PUSH32(esp, 0x000A3748u);
            RECOMP_ICALL_SAFE(_icall_target, _icall_esp);
        }
    }

loc_000A3748: ;
    ecx = esi;
    POP32(esp, esi);
    g_seh_ebp = ebp;
    sub_00099A10();
}
