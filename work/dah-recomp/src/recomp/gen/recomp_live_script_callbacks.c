/* Retail Lua native callback reached through the script VM's indirect call
 * bridge. Byte-checked lift; see tools/lift_live_script_callback.py. */
#define RECOMP_GENERATED_CODE
#include "recomp_funcs.h"

/**
 * sub_001932F0
 * Original: 0x001932F0 - 0x0019332C (60 bytes, 20 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_001932F0(void)
{
    int _flags = 0;
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    #define fp_push(v) do { double _fp_value = (v); \
        g_fp_top = (g_fp_top + 7u) & 7u; \
        g_fp_stack[g_fp_top] = _fp_value; } while (0)
    #define fp_pop() (g_fp_top = (g_fp_top + 1u) & 7u)
    #define fp_top() g_fp_stack[g_fp_top]
    #define fp_st(i) g_fp_stack[(g_fp_top + (i)) & 7u]
    #define fp_st1() fp_st(1)

    esp = esp - 8;
    PUSH32(esp, esi);
    eax = esp + 4;
    PUSH32(esp, eax);
    edx = 1;
    esi = ecx;
    PUSH32(esp, 0x00193305u); sub_00191960();

loc_00193305: ;
    fp_push((double)SMEM32(esp + 4));
    ecx = MEM32(esp + 4);
    _fa = (uint32_t)(ecx); _fb = (uint32_t)(ecx);
    _fas = (int32_t)(_fa); _fbs = (int32_t)(_fb);
    if (CMP_GE(_fas & _fbs, 0)) goto loc_00193317;
    fp_top() = fp_top() + MEMF(0x22A3D8);

loc_00193317: ;
    PUSH32(esp, ecx);
    ecx = esi;
    MEMF(esp) = (float)fp_top(); fp_pop();
    PUSH32(esp, 0x00193322u); sub_00190ED0();

loc_00193322: ;
    eax = 1;
    POP32(esp, esi);
    esp = esp + 8;
    esp += 4; return;

    #undef fp_push
    #undef fp_pop
    #undef fp_top
    #undef fp_st
    #undef fp_st1
}
