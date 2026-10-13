#define RECOMP_GENERATED_CODE
#include "recomp_funcs.h"

/**
 * sub_00012280
 * Original: 0x00012280 - 0x000122A9 (41 bytes, 12 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00012280(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00012280: ;
    eax = MEM32(esp + 4);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0xB405C7B6u) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0xB405C7B6u (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_00012290; /* jne: not equal / not zero */

loc_0001228B: ;
    SET_LO8(eax, 1);
    esp += 8; return; /* ret 4 */

loc_00012290: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0x883240FCu) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0x883240FCu (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_0001228B; /* je: equal / zero */

loc_00012297: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0x38082939) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0x38082939 (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_0001228B; /* je: equal / zero */

loc_0001229E: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0xA75FFAEBu) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0xA75FFAEBu (32-bit) */
    SET_LO8(eax, (CMP_EQ(_fa, _fb)) ? 1 : 0); /* sete */
    esp += 8; return; /* ret 4 */

}

/**
 * sub_0002C660
 * Original: 0x0002C660 - 0x0002C6DA (122 bytes, 41 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0002C660(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_0002C660: ;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, esi);
    esi = ecx;
    eax = MEM32(esi);
    PUSH32(esp, edi);
    { uint32_t _icall_target = MEM32(eax + 0x3C); PUSH32(esp, 0x0002C669u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_0002C669: ;
    edx = MEM32(esi);
    edi = MEM32(eax + 0x1B8);
    ecx = esi;
    { uint32_t _icall_esp = g_esp;
    { uint32_t _icall_target = MEM32(edx + 0x3C); PUSH32(esp, 0x0002C676u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_0002C676: ;
    ecx = MEM32(eax + 0x1B0);
    edx = MEM32(eax + 0x1B8);
    eax = eax + 0x1B0;
    eax = edx + ecx * 4;
    _fa = (uint32_t)(edi) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edi, eax (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_0002C6B9; /* je: equal / zero */

loc_0002C68E: ;
    edi = edi;

loc_0002C690: ;
    ecx = MEM32(edi);
    edx = MEM32(ecx);
    { uint32_t _icall_esp = g_esp;
    { uint32_t _icall_target = MEM32(edx + 0x20); PUSH32(esp, 0x0002C697u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_0002C697: ;
    eax = MEM32(esi);
    ecx = esi;
    edi = edi + 4;
    { uint32_t _icall_esp = g_esp;
    { uint32_t _icall_target = MEM32(eax + 0x3C); PUSH32(esp, 0x0002C6A1u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_0002C6A1: ;
    ecx = MEM32(eax + 0x1B0);
    edx = MEM32(eax + 0x1B8);
    eax = eax + 0x1B0;
    eax = edx + ecx * 4;
    _fa = (uint32_t)(edi) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edi, eax (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_0002C690; /* jne: not equal / not zero */

loc_0002C6B9: ;
    edx = MEM32(esi);
    ecx = esi;
    { uint32_t _icall_esp = g_esp;
    { uint32_t _icall_target = MEM32(edx + 0x3C); PUSH32(esp, 0x0002C6C0u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_0002C6C0: ;
    edx = MEM32(eax);
    ecx = eax;
    { uint32_t _icall_esp = g_esp;
    { uint32_t _icall_target = MEM32(edx + 0xF8); PUSH32(esp, 0x0002C6CAu); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_0002C6CA: ;
    ecx = eax;
    PUSH32(esp, 0x0002C6D1u); sub_00035050(); /* call 0x00035050 */

loc_0002C6D1: ;
    POP32(esp, edi);
    ecx = esi;
    POP32(esp, esi);
    g_seh_ebp = ebp; sub_0001B260(); return; /* tail jmp 0x0001B260 */

}

/**
 * sub_0003DF00
 * Original: 0x0003DF00 - 0x0003DF1F (31 bytes, 8 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0003DF00(void)
{

loc_0003DF00: ;
    PUSH32(esp, 0x42C80000);
    eax = ecx + 0x1B0;
    edx = ecx + 0x1A4;
    PUSH32(esp, eax);
    PUSH32(esp, edx);
    ecx = ecx + 0x1A0;
    PUSH32(esp, 0x0003DF1Eu); sub_001047C0(); /* call 0x001047C0 */

loc_0003DF1E: ;
    esp += 4; return; /* ret */

}

/**
 * sub_00077810
 * Original: 0x00077810 - 0x0007783B (43 bytes, 13 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00077810(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00077810: ;
    PUSH32(esp, esi);
    esi = ecx;
    MEM32(esi) = 0x22C388;
    MEM32(esi + 4) = 0x22C378;
    PUSH32(esp, 0x00077825u); sub_00076DC0(); /* call 0x00076DC0 */

loc_00077825: ;
    _fa = (uint32_t)(MEM8(esp + 8)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(esp + 8), 1 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00077835; /* je: equal / zero */

loc_0007782C: ;
    PUSH32(esp, esi);
    PUSH32(esp, 0x00077832u); sub_0006B710(); /* call 0x0006B710 */

loc_00077832: ;
    esp = esp + 4;

loc_00077835: ;
    eax = esi;
    POP32(esp, esi);
    esp += 8; return; /* ret 4 */

}
