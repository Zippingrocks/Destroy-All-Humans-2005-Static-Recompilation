/* Retail callback 0x0002C6E0 observed from 0x0001E9E6 during the
 * Capitol/Silhouette cinematic. Byte-checked against the retail XBE; see
 * tools/lift_callback_0002C6E0.py. */
#define RECOMP_GENERATED_CODE
#include "recomp_funcs.h"

/**
 * sub_0002C6E0
 * Original: 0x0002C6E0 - 0x0002C851 (369 bytes, 121 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0002C6E0(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
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
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_0002C6E0: ;
    esp = esp - 8;
    PUSH32(esp, ebx);
    ebx = MEM32(esp + 0x10);
    PUSH32(esp, esi);
    PUSH32(esp, ebx);
    esi = ecx;
    PUSH32(esp, 0x0002C6F1u); sub_0001B670(); /* call 0x0001B670 */

loc_0002C6F1: ;
    fp_push(MEMF(esi + 0x88)); /* fld float */
    fp_top() = fp_top() - MEMF(esp + 0x14); /* fsub dword ptr [esp + 0x14] */
    ecx = esi + 0x70;
    MEMF(esi + 0x88) = (float)fp_top(); fp_pop(); /* fstp */
    fp_push(MEMF(esi + 0x94)); /* fld float */
    fp_top() = fp_top() - MEMF(esp + 0x14); /* fsub dword ptr [esp + 0x14] */
    MEMF(esi + 0x94) = (float)fp_top(); fp_pop(); /* fstp */
    fp_push(MEMF(esi + 0xA8)); /* fld float */
    fp_top() = fp_top() - MEMF(esp + 0x14); /* fsub dword ptr [esp + 0x14] */
    MEMF(esi + 0xA8) = (float)fp_top(); fp_pop(); /* fstp */
    PUSH32(esp, 0x0002C729u); sub_0010BC40(); /* call 0x0010BC40 */

loc_0002C729: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    MEM32(esi + 0x6C) = eax;
    if (TEST_Z(_fa, _fb)) goto loc_0002C73B; /* je: equal / zero */

loc_0002C730: ;
    edx = MEM32(eax);
    ecx = eax;
    { uint32_t _icall_esp = g_esp;
    { uint32_t _icall_target = MEM32(edx + 0x40); PUSH32(esp, 0x0002C737u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_0002C737: ;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_0002C772; /* jne: not equal / not zero */

loc_0002C73B: ;
    eax = MEM32(esi);
    ecx = esi;
    { uint32_t _icall_esp = g_esp;
    { uint32_t _icall_target = MEM32(eax + 0x3C); PUSH32(esp, 0x0002C742u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_0002C742: ;
    SET_LO8(ecx, MEM8(eax + 0x599));
    _fa = (uint32_t)(LO8(ecx)) & 0xFFu; _fb = (uint32_t)(LO8(ecx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(ecx), LO8(ecx) (8-bit) */
    ecx = esi;
    if (TEST_Z(_fa, _fb)) goto loc_0002C760; /* je: equal / zero */

loc_0002C74E: ;
    PUSH32(esp, 0x33952CF);
    PUSH32(esp, 0x0002C758u); sub_0001B300(); /* call 0x0001B300 */

loc_0002C758: ;
    POP32(esp, esi);
    POP32(esp, ebx);
    esp = esp + 8;
    esp += 8; return; /* ret 4 */

loc_0002C760: ;
    PUSH32(esp, 0x5513A823);
    PUSH32(esp, 0x0002C76Au); sub_0001B300(); /* call 0x0001B300 */

loc_0002C76A: ;
    POP32(esp, esi);
    POP32(esp, ebx);
    esp = esp + 8;
    esp += 8; return; /* ret 4 */

loc_0002C772: ;
    edx = MEM32(esi);
    ecx = esi;
    { uint32_t _icall_esp = g_esp;
    { uint32_t _icall_target = MEM32(edx + 0x3C); PUSH32(esp, 0x0002C779u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_0002C779: ;
    fp_push(MEMF(esi + 0x84)); /* fld float */
    g_fp_cmp = RECOMP_FCMP(fp_top(), MEMF(eax + 0x1F0)); fp_pop(); /* fcomp dword ptr [eax + 0x1f0] */
    ecx = esi;
    eax = (eax & 0xFFFF0000u) | (uint32_t)(uint16_t)(((g_fp_top & 7u) << 11) | (g_fp_cmp == 2 ? 0x4500u : g_fp_cmp < 0 ? 0x0100u : g_fp_cmp > 0 ? 0x0000u : 0x4000u)); /* fnstsw ax <- fpu status */
    _fa = (uint32_t)(HI8(eax)) & 0xFFu; _fb = (uint32_t)(0x41) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test HI8(eax), 0x41 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0002C7E8; /* je: equal / zero */

loc_0002C78E: ;
    eax = MEM32(esi);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, ebp);
    PUSH32(esp, edi);
    { uint32_t _icall_target = MEM32(eax + 0x3C); PUSH32(esp, 0x0002C795u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_0002C795: ;
    edx = MEM32(esi);
    ecx = esi;
    edi = eax + 0x18;
    { uint32_t _icall_esp = g_esp;
    { uint32_t _icall_target = MEM32(edx + 0x3C); PUSH32(esp, 0x0002C79Fu); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_0002C79F: ;
    eax = MEM32(eax + 0x1EC);
    edx = MEM32(esi);
    ecx = esi;
    MEM32(esp + 0x14) = eax;
    { uint32_t _icall_esp = g_esp;
    { uint32_t _icall_target = MEM32(edx + 0x3C); PUSH32(esp, 0x0002C7B0u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_0002C7B0: ;
    ecx = MEM32(esi + 0x6C);
    eax = MEM32(eax + 0x1EC);
    edx = MEM32(ecx);
    MEM32(esp + 0x10) = eax;
    { uint32_t _icall_esp = g_esp;
    { uint32_t _icall_target = MEM32(edx + 0x1C); PUSH32(esp, 0x0002C7C2u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_0002C7C2: ;
    ebp = eax;
    eax = MEM32(edi);
    ecx = edi;
    { uint32_t _icall_esp = g_esp;
    { uint32_t _icall_target = MEM32(eax); PUSH32(esp, 0x0002C7CAu); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_0002C7CA: ;
    edx = ebp;
    ecx = eax;
    PUSH32(esp, 0x0002C7D3u); sub_000D4F40(); /* call 0x000D4F40 */

loc_0002C7D3: ;
    fp_push(MEMF(esp + 0x10)); /* fld float */
    fp_top() = fp_top() * MEMF(esp + 0x14); /* fmul dword ptr [esp + 0x14] */
    POP32(esp, edi);
    POP32(esp, ebp);
    ecx = esi;
    g_fp_cmp = RECOMP_FCMP(fp_top(), fp_st1()); fp_pop(); fp_pop(); /* fcompp  */
    eax = (eax & 0xFFFF0000u) | (uint32_t)(uint16_t)(((g_fp_top & 7u) << 11) | (g_fp_cmp == 2 ? 0x4500u : g_fp_cmp < 0 ? 0x0100u : g_fp_cmp > 0 ? 0x0000u : 0x4000u)); /* fnstsw ax <- fpu status */
    _fa = (uint32_t)(HI8(eax)) & 0xFFu; _fb = (uint32_t)(5) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test HI8(eax), 5 (8-bit) */
    if (RECOMP_PARITY8((_fa) & (_fb))) goto loc_0002C7FA; /* jp: parity */

loc_0002C7E8: ;
    PUSH32(esp, 0x8F651465u);
    PUSH32(esp, 0x0002C7F2u); sub_0001B300(); /* call 0x0001B300 */

loc_0002C7F2: ;
    POP32(esp, esi);
    POP32(esp, ebx);
    esp = esp + 8;
    esp += 8; return; /* ret 4 */

loc_0002C7FA: ;
    fp_push(MEMF(esp + 0x14)); /* fld float */
    fp_top() = fp_top() + MEMF(esi + 0x84); /* fadd dword ptr [esi + 0x84] */
    MEMF(esi + 0x84) = (float)fp_top(); fp_pop(); /* fstp */
    fp_push(MEMF(esp + 0x14)); /* fld float */
    fp_top() = fp_top() + MEMF(esi + 0x80); /* fadd dword ptr [esi + 0x80] */
    MEMF(esi + 0x80) = (float)fp_top(); fp_pop(); /* fstp */
    PUSH32(esp, 0x0002C81Fu); sub_0002C330(); /* call 0x0002C330 */

loc_0002C81F: ;
    PUSH32(esp, ebx);
    ecx = esi + 0x48;
    PUSH32(esp, 0x0002C828u); sub_0003A3C0(); /* call 0x0003A3C0 */

loc_0002C828: ;
    _fa = (uint32_t)(MEM32(esi + 0x50)) & 0xFFFFFFFFu; _fb = (uint32_t)(5) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(esi + 0x50), 5 (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_0002C849; /* je: equal / zero */

loc_0002C82E: ;
    ecx = MEM32(esi + 0x6C);
    edx = MEM32(ecx);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 1);
    PUSH32(esp, 0);
    { uint32_t _icall_target = MEM32(edx + 0x1C); PUSH32(esp, 0x0002C83Au); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_0002C83A: ;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, eax);
    eax = MEM32(esi);
    ecx = esi;
    { uint32_t _icall_target = MEM32(eax + 0x3C); PUSH32(esp, 0x0002C842u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_0002C842: ;
    ecx = eax;
    PUSH32(esp, 0x0002C849u); sub_00022E10(); /* call 0x00022E10 */

loc_0002C849: ;
    POP32(esp, esi);
    POP32(esp, ebx);
    esp = esp + 8;
    esp += 8; return; /* ret 4 */

    #undef fp_push
    #undef fp_pop
    #undef fp_top
    #undef fp_st
    #undef fp_st1
}

