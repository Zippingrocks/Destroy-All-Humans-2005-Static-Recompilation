/**
 * Burnout 3 - Recompiled code chunk 21
 * Functions: 281 (0x00213BD0 - 0x0022597C)
 */

#define RECOMP_GENERATED_CODE
#include "recomp_funcs.h"
#include "dah_timing.h"
#include "recomp_mmx.h"
#include <math.h>

/**
 * sub_00213BD0
 * Original: 0x00213BD0 - 0x00213C8B (187 bytes, 61 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00213BD0(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_00213BD0: ;
    edx = MEM32(esp + 4);
    eax = MEM32(0x29BF7C);
    ecx = MEM32(0x29BF80);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, ebx);
    ebx = MEM32(0x299F10);
    PUSH32(esp, ebp);
    ebp = MEM32(0x299F14);
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    PUSH32(esp, edx);
    MEM32(0x299F10) = eax;
    MEM32(0x299F14) = ecx;
    { uint32_t _icall_target = MEM32(0x28722C); PUSH32(esp, 0x00213C01u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00213C01: ;
    eax = MEM32(0x299F10);
    esi = MEM32(0x29BF7C);
    eax = eax - esi;
    ecx = eax;
    edx = ecx;
    ecx = ecx >> 2;
    edi = ebx;
    memcpy((void*)XBOX_PTR(edi), (void*)XBOX_PTR(esi), ecx * 4);
    esi += ecx * 4; edi += ecx * 4; ecx = 0; /* rep movsd */
    ecx = edx;
    ecx = ecx & 3;
    memcpy((void*)XBOX_PTR(edi), (void*)XBOX_PTR(esi), ecx);
    esi += ecx; edi += ecx; ecx = 0; /* rep movsb */
    edx = MEM32(0x299F30);
    esi = MEM32(0x29BF7C);
    edi = edx + ebx;
    ecx = eax;
    edx = ecx;
    ecx = ecx >> 2;
    memcpy((void*)XBOX_PTR(edi), (void*)XBOX_PTR(esi), ecx * 4);
    esi += ecx * 4; edi += ecx * 4; ecx = 0; /* rep movsd */
    ecx = edx;
    ecx = ecx & 3;
    memcpy((void*)XBOX_PTR(edi), (void*)XBOX_PTR(esi), ecx);
    esi += ecx; edi += ecx; ecx = 0; /* rep movsb */
    esi = MEM32(0x29BF80);
    ecx = eax;
    ecx = ecx >> 2;
    edi = ebp;
    memcpy((void*)XBOX_PTR(edi), (void*)XBOX_PTR(esi), ecx * 4);
    esi += ecx * 4; edi += ecx * 4; ecx = 0; /* rep movsd */
    ecx = edx;
    ecx = ecx & 3;
    memcpy((void*)XBOX_PTR(edi), (void*)XBOX_PTR(esi), ecx);
    esi += ecx; edi += ecx; ecx = 0; /* rep movsb */
    edx = MEM32(0x299F30);
    esi = MEM32(0x29BF80);
    ecx = eax;
    edi = edx + ebp;
    edx = ecx;
    ecx = ecx >> 2;
    memcpy((void*)XBOX_PTR(edi), (void*)XBOX_PTR(esi), ecx * 4);
    esi += ecx * 4; edi += ecx * 4; ecx = 0; /* rep movsd */
    ecx = edx;
    ecx = ecx & 3;
    memcpy((void*)XBOX_PTR(edi), (void*)XBOX_PTR(esi), ecx);
    esi += ecx; edi += ecx; ecx = 0; /* rep movsb */
    POP32(esp, edi);
    ecx = eax + ebx;
    POP32(esp, esi);
    eax = eax + ebp;
    POP32(esp, ebp);
    MEM32(0x299F10) = ecx;
    MEM32(0x299F14) = eax;
    POP32(esp, ebx);
    esp += 8; return; /* ret 4 */

}

/**
 * sub_00213C90
 * Original: 0x00213C90 - 0x00213D6C (220 bytes, 52 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00213C90(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00213C90: ;
    PUSH32(esp, esi);
    esi = MEM32(0x28725C);
    eax = MEM32(esi);
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(2) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), 2 (8-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_00213D4A; /* jne: not equal / not zero */

loc_00213CA1: ;
    ecx = eax;
    ecx = ecx >> 2;
    eax = eax >> 8;
    ecx = ecx & 0x3F;
    _fa = (uint32_t)(edx) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edx, eax (32-bit) */
    if (CMP_AE(_fa, _fb)) goto loc_00213CF8; /* jae: above or equal (unsigned >=) */

loc_00213CB0: ;
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, ecx (32-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_00213CD6; /* jne: not equal / not zero */

loc_00213CB4: ;
    MEM32(esi) = 3;
    MEM32(0x287248) = ecx;
    MEM32(0x287250) = 0x213B10;
    MEM32(0x287228) = 0x213BD0;
    POP32(esp, esi);
    esp += 4; return; /* ret */

loc_00213CD6: ;
    ecx--;
    ecx = ecx & 0x3F;
    ecx = ecx << 2;
    ecx = ecx | 2;
    MEM32(esi) = ecx;
    MEM32(0x287234) = 0x213970;
    MEM32(0x287240) = 0x213A40;
    POP32(esp, esi);
    esp += 4; return; /* ret */

loc_00213CF8: ;
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(0x3F) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp ecx, 0x3F (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_00213D23; /* jne: not equal / not zero */

loc_00213CFD: ;
    MEM32(esi) = 1;
    MEM32(0x287248) = 0;
    MEM32(0x287250) = 0x213970;
    MEM32(0x287228) = 0x213A40;
    POP32(esp, esi);
    esp += 4; return; /* ret */

loc_00213D23: ;
    eax = ecx * 4 + 4;
    eax = eax & 0xFC;
    eax = eax | 2;
    MEM32(esi) = eax;
    MEM32(0x287234) = 0x213970;
    MEM32(0x287240) = 0x213A40;
    POP32(esp, esi);
    esp += 4; return; /* ret */

loc_00213D4A: ;
    eax = eax & 0xFD;
    edx = edx << 8;
    eax = eax | edx;
    MEM32(esi) = eax;
    MEM32(0x287234) = 0x213B10;
    MEM32(0x287240) = 0x213BD0;
    POP32(esp, esi);
    esp += 4; return; /* ret */

}

/**
 * sub_00213D70
 * Original: 0x00213D70 - 0x00213DAE (62 bytes, 20 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00213D70(void)
{

loc_00213D70: ;
    esp = esp - 8;
    eax = esp;
    MEM32(esp + 4) = eax;
    ecx = MEM32(esp + 4);
    { uint64_t _tsc = dah_read_tsc(); eax = (uint32_t)_tsc; edx = (uint32_t)(_tsc >> 32); } /* rdtsc */
    MEM32(ecx) = eax;
    ecx = MEM32(esp + 0xC);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, ecx);
    { uint32_t _icall_target = MEM32(0x287234); PUSH32(esp, 0x00213D8Du); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00213D8D: ;
    edx = esp;
    MEM32(esp + 0xC) = edx;
    { uint64_t _tsc = dah_read_tsc(); eax = (uint32_t)_tsc; edx = (uint32_t)(_tsc >> 32); } /* rdtsc */
    ecx = MEM32(esp + 0xC);
    edx = eax;
    eax = eax - MEM32(ecx);
    MEM32(ecx) = eax;
    edx = MEM32(esp);
    PUSH32(esp, 0x00213DA8u); sub_00213C90(); /* call 0x00213C90 */

loc_00213DA8: ;
    esp = esp + 8;
    esp += 8; return; /* ret 4 */

}

/**
 * sub_00213DB0
 * Original: 0x00213DB0 - 0x00213DEE (62 bytes, 20 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00213DB0(void)
{

loc_00213DB0: ;
    esp = esp - 8;
    eax = esp;
    MEM32(esp + 4) = eax;
    ecx = MEM32(esp + 4);
    { uint64_t _tsc = dah_read_tsc(); eax = (uint32_t)_tsc; edx = (uint32_t)(_tsc >> 32); } /* rdtsc */
    MEM32(ecx) = eax;
    ecx = MEM32(esp + 0xC);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, ecx);
    { uint32_t _icall_target = MEM32(0x287240); PUSH32(esp, 0x00213DCDu); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00213DCD: ;
    edx = esp;
    MEM32(esp + 0xC) = edx;
    { uint64_t _tsc = dah_read_tsc(); eax = (uint32_t)_tsc; edx = (uint32_t)(_tsc >> 32); } /* rdtsc */
    ecx = MEM32(esp + 0xC);
    edx = eax;
    eax = eax - MEM32(ecx);
    MEM32(ecx) = eax;
    edx = MEM32(esp);
    PUSH32(esp, 0x00213DE8u); sub_00213C90(); /* call 0x00213C90 */

loc_00213DE8: ;
    esp = esp + 8;
    esp += 8; return; /* ret 4 */

}

/**
 * sub_00213DF0
 * Original: 0x00213DF0 - 0x00213E7D (141 bytes, 28 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00213DF0(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00213DF0: ;
    eax = MEM32(0x29BF68);
    edx = 1;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(edx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, edx (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_00213E18; /* jne: not equal / not zero */

loc_00213DFE: ;
    eax = MEM32(ecx);
    _fa = (uint32_t)(LO8(edx)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(edx), LO8(eax) (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00213E42; /* je: equal / zero */

loc_00213E04: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0x2000) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0x2000 (32-bit) */
    if (CMP_A(_fa, _fb)) goto loc_00213E42; /* ja: above (unsigned >) */

loc_00213E0B: ;
    edx = MEM32(esp + 4);
    eax = eax + edx * 4;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(2) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), 2 (8-bit) */
    MEM32(ecx) = eax;
    if (TEST_Z(_fa, _fb)) goto loc_00213E2D; /* je: equal / zero */

loc_00213E18: ;
    MEM32(0x287250) = 0x213B10;
    MEM32(0x287228) = 0x213BD0;
    esp += 4; return; /* ret */

loc_00213E2D: ;
    MEM32(0x287250) = 0x213970;
    MEM32(0x287228) = 0x213A40;
    esp += 4; return; /* ret */

loc_00213E42: ;
    MEM32(0x287250) = 0x213D70;
    MEM32(0x287228) = 0x213DB0;
    MEM32(0x28725C) = ecx;
    MEM32(ecx) = 0x82;
    MEM32(0x287234) = 0x213970;
    MEM32(0x287240) = 0x213A40;
    MEM32(0x287248) = edx;
    esp += 4; return; /* ret */

}

/**
 * sub_00213E80
 * Original: 0x00213E80 - 0x00214275 (1013 bytes, 263 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00213E80(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_00213E80: ;
    ecx = MEM32(edi);
    PUSH32(esp, ebp);
    ebp = MEM32(esp + 8);
    PUSH32(esp, esi);
    esi = eax;
    eax = 0; /* xor self */
    _fa = (uint32_t)(ebx) & 0xFFFFFFFFu; _fb = (uint32_t)(0x10000) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ebx, 0x10000 (32-bit) */
    MEM32(0x299F30) = ecx;
    ecx = MEM32(0x29BF6C);
    MEM32(0x287248) = eax;
    if (TEST_Z(_fa, _fb)) goto loc_00213F3D; /* je: equal / zero */

loc_00213EA9: ;
    eax = 1;
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp ecx, eax (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_00213F90; /* je: equal / zero */

loc_00213EB6: ;
    MEM32(0x29BF6C) = eax;
    eax = 0x29AB38;
    edx = 0x100;

loc_00213EC5: ;
    ebp = MEM32(eax + -3072);
    ecx = MEM32(eax);
    MEM32(eax) = ebp;
    MEM32(eax + -3072) = ecx;
    eax = eax + 4;
    edx--;
    if ((edx != 0)) goto loc_00213EC5; /* jne: not equal / not zero */

loc_00213EDB: ;
    eax = 0x29A338;
    edx = 0x100;

loc_00213EE5: ;
    ebp = MEM32(eax + 0x400);
    ecx = MEM32(eax);
    MEM32(eax) = ebp;
    MEM32(eax + 0x400) = ecx;
    eax = eax + 4;
    edx--;
    if ((edx != 0)) goto loc_00213EE5; /* jne: not equal / not zero */

loc_00213EFB: ;
    eax = 0x29BB38;
    edx = 0x100;

loc_00213F05: ;
    ebp = MEM32(eax + -3072);
    ecx = MEM32(eax);
    MEM32(eax) = ebp;
    MEM32(eax + -3072) = ecx;
    eax = eax + 4;
    edx--;
    if ((edx != 0)) goto loc_00213F05; /* jne: not equal / not zero */

loc_00213F1B: ;
    eax = 0x29B338;
    edx = 0x100;

loc_00213F25: ;
    ebp = MEM32(eax + 0x400);
    ecx = MEM32(eax);
    MEM32(eax) = ebp;
    MEM32(eax + 0x400) = ecx;
    eax = eax + 4;
    edx--;
    if ((edx != 0)) goto loc_00213F25; /* jne: not equal / not zero */

loc_00213F3B: ;
    goto loc_00213F86;

loc_00213F3D: ;
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp ecx, eax (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_00213F90; /* je: equal / zero */

loc_00213F41: ;
    MEM32(0x29BF6C) = eax;
    eax = 0x29AB38;
    edx = 0x100;

loc_00213F50: ;
    ebp = MEM32(eax + -3072);
    ecx = MEM32(eax);
    MEM32(eax) = ebp;
    MEM32(eax + -3072) = ecx;
    eax = eax + 4;
    edx--;
    if ((edx != 0)) goto loc_00213F50; /* jne: not equal / not zero */

loc_00213F66: ;
    eax = 0x29A338;
    edx = 0x100;

loc_00213F70: ;
    ebp = MEM32(eax + 0x400);
    ecx = MEM32(eax);
    MEM32(eax) = ebp;
    MEM32(eax + 0x400) = ecx;
    eax = eax + 4;
    edx--;
    if ((edx != 0)) goto loc_00213F70; /* jne: not equal / not zero */

loc_00213F86: ;
    ebp = MEM32(esp + 0xC);
    /* nop */

loc_00213F90: ;
    PUSH32(esp, ebx);
    PUSH32(esp, 0x00213F96u); sub_00180950(); /* call 0x00180950 */

loc_00213F96: ;
    eax = MEM32(0x2879B0);
    esp = esp + 4;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0021425A; /* je: equal / zero */

loc_00213FA6: ;
    eax = ebx;
    eax = eax & 0x70000000;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0x10000000) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0x10000000 (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_0021406F; /* jne: not equal / not zero */

loc_00213FB8: ;
    eax = MEM32(esi);
    eax = (uint32_t)((int32_t)eax * (int32_t)ebp);
    PUSH32(esp, 0x00213FC2u); sub_002138F0(); /* call 0x002138F0 */

loc_00213FC2: ;
    eax = MEM32(edi);
    ecx = MEM32(esp + 0x14);
    eax = eax << 1;
    MEM32(edi) = eax;
    edx = MEM32(esi);
    edx = (uint32_t)((int32_t)edx * (int32_t)ebp);
    eax = eax - edx;
    _fa = (uint32_t)(ebx) & 0xFFFFFFFFu; _fb = (uint32_t)(0x20000) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ebx, 0x20000 (32-bit) */
    MEM32(ecx) = eax;
    if (TEST_Z(_fa, _fb)) goto loc_00214023; /* je: equal / zero */

loc_00213FDD: ;
    eax = MEM32(esp + 0x10);
    edx = esi + 0x60;
    PUSH32(esp, eax);
    ecx = esi + 0x40;
    MEM32(0x28724C) = edx;
    PUSH32(esp, 0x00213FF3u); sub_00213DF0(); /* call 0x00213DF0 */

loc_00213FF3: ;
    eax = MEM32(esi + 0x18);
    ecx = MEM32(esi + 0x9C);
    edx = MEM32(esi + 0xA0);
    MEM32(0x28723C) = eax;
    MEM32(0x28722C) = eax;
    eax = MEM32(esi + 0x14);
    esp = esp + 4;
    MEM32(0x287258) = ecx;
    MEM32(0x287238) = edx;
    goto loc_00214255;

loc_00214023: ;
    edx = MEM32(esp + 0x10);
    ecx = esi + 0x58;
    MEM32(0x28724C) = ecx;
    PUSH32(esp, edx);
    ecx = esi + 0x38;
    PUSH32(esp, 0x00214039u); sub_00213DF0(); /* call 0x00213DF0 */

loc_00214039: ;
    eax = MEM32(esi + 0x94);
    ecx = MEM32(esi + 0x98);
    edx = MEM32(esi + 8);
    MEM32(0x287258) = eax;
    eax = MEM32(esi + 0x10);
    MEM32(0x28722C) = eax;
    eax = MEM32(esi + 0xC);
    esi = MEM32(esi + 4);
    esp = esp + 4;
    MEM32(0x287238) = ecx;
    MEM32(0x28723C) = edx;
    goto loc_0021424B;

loc_0021406F: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0x30000000) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0x30000000 (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_002141C3; /* je: equal / zero */

loc_0021407A: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0x50000000) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0x50000000 (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_002141C3; /* je: equal / zero */

loc_00214085: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0x40000000) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0x40000000 (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_00214144; /* jne: not equal / not zero */

loc_00214090: ;
    eax = MEM32(esi);
    eax = (uint32_t)((int32_t)eax * (int32_t)ebp);
    eax = eax << 1;
    PUSH32(esp, 0x0021409Cu); sub_002138F0(); /* call 0x002138F0 */

loc_0021409C: ;
    eax = MEM32(edi);
    edx = MEM32(esp + 0x14);
    eax = eax << 1;
    MEM32(edi) = eax;
    ecx = MEM32(esi);
    ecx = (uint32_t)((int32_t)ecx * (int32_t)ebp);
    ecx = ecx << 1;
    eax = eax - ecx;
    _fa = (uint32_t)(ebx) & 0xFFFFFFFFu; _fb = (uint32_t)(0x20000) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ebx, 0x20000 (32-bit) */
    MEM32(edx) = eax;
    if (TEST_Z(_fa, _fb)) goto loc_00214103; /* je: equal / zero */

loc_002140B9: ;
    ecx = MEM32(esp + 0x10);
    eax = esi + 0x70;
    PUSH32(esp, ecx);
    ecx = esi + 0x50;
    MEM32(0x28724C) = eax;
    PUSH32(esp, 0x002140CEu); sub_00213DF0(); /* call 0x00213DF0 */

loc_002140CE: ;
    eax = MEM32(esi + 0xB0);
    edx = MEM32(esi + 0xAC);
    ecx = MEM32(esi + 0x2C);
    MEM32(0x287238) = eax;
    eax = MEM32(esi + 0x30);
    esp = esp + 4;
    MEM32(0x287258) = edx;
    MEM32(0x28723C) = eax;
    MEM32(0x28722C) = eax;
    MEM32(0x287224) = ecx;
    goto loc_0021425A;

loc_00214103: ;
    eax = MEM32(esp + 0x10);
    edx = esi + 0x68;
    PUSH32(esp, eax);
    ecx = esi + 0x48;
    MEM32(0x28724C) = edx;
    PUSH32(esp, 0x00214119u); sub_00213DF0(); /* call 0x00213DF0 */

loc_00214119: ;
    ecx = MEM32(esi + 0xA4);
    eax = MEM32(esi + 0x20);
    edx = MEM32(esi + 0xA8);
    MEM32(0x287258) = ecx;
    ecx = MEM32(esi + 0x28);
    esp = esp + 4;
    MEM32(0x28723C) = eax;
    MEM32(0x28722C) = ecx;
    goto loc_0021423F;

loc_00214144: ;
    edx = MEM32(esi);
    eax = MEM32(edi);
    edx = (uint32_t)((int32_t)edx * (int32_t)ebp);
    ecx = MEM32(esp + 0x14);
    eax = eax - edx;
    _fa = (uint32_t)(ebx) & 0xFFFFFFFFu; _fb = (uint32_t)(0x20000) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ebx, 0x20000 (32-bit) */
    MEM32(ecx) = eax;
    if (TEST_Z(_fa, _fb)) goto loc_00214193; /* je: equal / zero */

loc_0021415B: ;
    eax = MEM32(esi + 0x7C);
    ecx = MEM32(esi + 0x80);
    edx = esi + 0x60;
    MEM32(0x28724C) = edx;
    edx = MEM32(esi + 0x14);
    MEM32(0x287258) = eax;
    eax = MEM32(esi + 0x18);
    MEM32(0x287238) = ecx;
    MEM32(0x287250) = eax;
    MEM32(0x287228) = eax;
    MEM32(0x287224) = edx;
    goto loc_0021425A;

loc_00214193: ;
    ecx = MEM32(esi + 0x74);
    edx = MEM32(esi + 0x78);
    eax = esi + 0x58;
    MEM32(0x28724C) = eax;
    eax = MEM32(esi + 8);
    MEM32(0x287258) = ecx;
    ecx = MEM32(esi + 0x10);
    MEM32(0x287250) = eax;
    eax = MEM32(esi + 0xC);
    esi = MEM32(esi + 4);
    MEM32(0x287228) = ecx;
    goto loc_00214245;

loc_002141C3: ;
    edx = MEM32(esi);
    eax = MEM32(edi);
    edx = (uint32_t)((int32_t)edx * (int32_t)ebp);
    ecx = MEM32(esp + 0x14);
    edx = edx << 1;
    eax = eax - edx;
    _fa = (uint32_t)(ebx) & 0xFFFFFFFFu; _fb = (uint32_t)(0x20000) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ebx, 0x20000 (32-bit) */
    MEM32(ecx) = eax;
    if (TEST_Z(_fa, _fb)) goto loc_00214214; /* je: equal / zero */

loc_002141DC: ;
    eax = MEM32(esi + 0x8C);
    ecx = MEM32(esi + 0x90);
    edx = esi + 0x70;
    MEM32(0x28724C) = edx;
    edx = MEM32(esi + 0x2C);
    MEM32(0x287258) = eax;
    eax = MEM32(esi + 0x30);
    MEM32(0x287238) = ecx;
    MEM32(0x287250) = eax;
    MEM32(0x287228) = eax;
    MEM32(0x287224) = edx;
    goto loc_0021425A;

loc_00214214: ;
    ecx = MEM32(esi + 0x84);
    edx = MEM32(esi + 0x88);
    eax = esi + 0x68;
    MEM32(0x28724C) = eax;
    eax = MEM32(esi + 0x20);
    MEM32(0x287258) = ecx;
    ecx = MEM32(esi + 0x28);
    MEM32(0x287250) = eax;
    MEM32(0x287228) = ecx;

loc_0021423F: ;
    eax = MEM32(esi + 0x24);
    esi = MEM32(esi + 0x1C);

loc_00214245: ;
    MEM32(0x287238) = edx;

loc_0021424B: ;
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp esi, eax (32-bit) */
    MEM32(0x287224) = esi;
    if (CMP_A(_fa, _fb)) goto loc_0021425A; /* ja: above (unsigned >) */

loc_00214255: ;
    MEM32(0x287224) = eax;

loc_0021425A: ;
    ecx = MEM32(0x287224);
    eax = 1;
    eax = eax << LO8(ecx);
    POP32(esp, esi);
    POP32(esp, ebp);
    MEM32(0x287230) = eax;
    eax--;
    MEM32(0x287254) = eax;
    esp += 4; return; /* ret */

}

/**
 * sub_00214280
 * Original: 0x00214280 - 0x00214307 (135 bytes, 54 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00214280(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00214280: ;
    PUSH32(esp, ebx);
    PUSH32(esp, esi);
    esi = MEM32(0x28724C);
    ebx = MEM32(esi);
    _fa = (uint32_t)(LO8(ebx)) & 0xFFu; _fb = (uint32_t)(4) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(ebx), 4 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00214304; /* je: equal / zero */

loc_0021428F: ;
    { uint64_t _tsc = dah_read_tsc(); eax = (uint32_t)_tsc; edx = (uint32_t)(_tsc >> 32); } /* rdtsc */
    ecx = 0x287244;
    edx = eax;
    eax = eax - MEM32(ecx);
    MEM32(ecx) = eax;
    _fa = (uint32_t)(LO8(ebx)) & 0xFFu; _fb = (uint32_t)(2) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(ebx), 2 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_002142EE; /* je: equal / zero */

loc_002142A1: ;
    ecx = MEM32(0x287244);
    eax = ebx;
    eax = eax >> 3;
    ebx = ebx >> 8;
    eax = eax & 0x1F;
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ebx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp ecx, ebx (32-bit) */
    if (CMP_AE(_fa, _fb)) goto loc_002142CF; /* jae: above or equal (unsigned >=) */

loc_002142B6: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_002142C3; /* jne: not equal / not zero */

loc_002142BA: ;
    MEM32(esi) = 3;
    POP32(esp, esi);
    POP32(esp, ebx);
    esp += 4; return; /* ret */

loc_002142C3: ;
    eax--;
    eax = eax & 0x1F;
    eax = eax << 3;
    MEM32(esi) = eax;
    POP32(esp, esi);
    POP32(esp, ebx);
    esp += 4; return; /* ret */

loc_002142CF: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0x1F) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0x1F (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_002142DD; /* jne: not equal / not zero */

loc_002142D4: ;
    MEM32(esi) = 1;
    POP32(esp, esi);
    POP32(esp, ebx);
    esp += 4; return; /* ret */

loc_002142DD: ;
    eax = eax * 8 + 8;
    eax = eax & 0xF8;
    MEM32(esi) = eax;
    POP32(esp, esi);
    POP32(esp, ebx);
    esp += 4; return; /* ret */

loc_002142EE: ;
    ecx = MEM32(0x287244);
    ecx = ecx << 8;
    ebx = ebx & 0xFD;
    ecx = ecx | ebx;
    ecx = ecx | 2;
    MEM32(esi) = ecx;

loc_00214304: ;
    POP32(esp, esi);
    POP32(esp, ebx);
    esp += 4; return; /* ret */

}

/**
 * sub_00214310
 * Original: 0x00214310 - 0x00214781 (1137 bytes, 345 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00214310(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_00214310: ;
    ecx = MEM32(esp + 0x2C);
    PUSH32(esp, ebx);
    PUSH32(esp, ebp);
    ebp = MEM32(esp + 0x2C);
    PUSH32(esp, esi);
    esi = MEM32(esp + 0x34);
    ecx = ecx & 0x70000000;
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(0x60000000) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp ecx, 0x60000000 (32-bit) */
    PUSH32(esp, edi);
    edi = MEM32(esp + 0x1C);
    if (CMP_NE(_fa, _fb)) goto loc_00214351; /* jne: not equal / not zero */

loc_00214332: ;
    eax = MEM32(esp + 0x28);
    ebx = MEM32(esp + 0x30);
    eax = eax >> 1;
    MEM32(esp + 0x28) = eax;
    ebx = ebx >> 1;
    eax = edi + edi;
    esi = esi >> 1;
    MEM32(esp + 0x30) = ebx;
    MEM32(esp + 0x1C) = eax;
    ebp = ebp + ebp;

loc_00214351: ;
    eax = MEM32(esp + 0x44);
    MEM32(0x299F34) = edx;
    eax = MEM32(eax);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(2) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 2 (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_00214375; /* jne: not equal / not zero */

loc_00214362: ;
    ebx = edx;
    SET_LO8(ebx, LO8(ebx) & 3);
    _fa = (uint32_t)(LO8(ebx)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp LO8(ebx), LO8(eax) (8-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_002143B4; /* jne: not equal / not zero */

loc_0021436B: ;
    ebx = MEM32(esp + 0x14);
    ebx++;
    edx = edx & 0xFFFFFFFCu;
    goto loc_002143B0;

loc_00214375: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(3) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 3 (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_002143B4; /* jne: not equal / not zero */

loc_0021437A: ;
    ebx = edx + 1;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(ebx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(ebx) (8-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_0021438A; /* jne: not equal / not zero */

loc_00214381: ;
    ebx = MEM32(esp + 0x14);
    ebx++;
    edx = edx - eax;
    goto loc_002143B0;

loc_0021438A: ;
    ebx = edx + -2;
    _fa = (uint32_t)(LO8(ebx)) & 0xFFu; _fb = (uint32_t)(3) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(ebx), 3 (8-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_0021439E; /* jne: not equal / not zero */

loc_00214392: ;
    ebx = MEM32(esp + 0x14);
    ebx = ebx + 2;
    edx = edx - 6;
    goto loc_002143B0;

loc_0021439E: ;
    ebx = edx + -1;
    _fa = (uint32_t)(LO8(ebx)) & 0xFFu; _fb = (uint32_t)(3) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(ebx), 3 (8-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_002143B4; /* jne: not equal / not zero */

loc_002143A6: ;
    ebx = MEM32(esp + 0x14);
    ebx = ebx + 3;
    edx = edx - 9;

loc_002143B0: ;
    MEM32(esp + 0x14) = ebx;

loc_002143B4: ;
    eax = (uint32_t)((int32_t)eax * (int32_t)MEM32(esp + 0x14));
    edi = (uint32_t)((int32_t)edi * (int32_t)MEM32(esp + 0x18));
    eax = eax + edx;
    edi = edi + eax;
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(0x20000000) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp ecx, 0x20000000 (32-bit) */
    MEM32(0x299F10) = edi;
    if (CMP_EQ(_fa, _fb)) goto loc_002143D8; /* je: equal / zero */

loc_002143D0: ;
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(0x50000000) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp ecx, 0x50000000 (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_002143E3; /* jne: not equal / not zero */

loc_002143D8: ;
    ecx = MEM32(esp + 0x1C);
    edx = ecx + ecx;
    MEM32(esp + 0x1C) = edx;

loc_002143E3: ;
    ecx = MEM32(esp + 0x30);
    edx = MEM32(esp + 0x2C);
    ebx = MEM32(esp + 0x3C);
    eax = esp + 0x18;
    PUSH32(esp, eax);
    eax = MEM32(esp + 0x48);
    PUSH32(esp, ecx);
    PUSH32(esp, edx);
    edi = esp + 0x28;
    PUSH32(esp, 0x00214403u); sub_00213E80(); /* call 0x00213E80 */

loc_00214403: ;
    ecx = MEM32(esp + 0x28);
    eax = MEM32(0x299F10);
    edx = MEM32(esp + 0x2C);
    eax = eax + ecx;
    MEM32(0x299F14) = eax;
    eax = MEM32(esp + 0x34);
    eax = (uint32_t)((int32_t)eax * (int32_t)ebp);
    ecx = eax + edx;
    edx = MEM32(esp + 0x30);
    ecx = ecx + edx;
    edi = ecx + ebp;
    MEM32(0x299F1C) = edi;
    edi = eax + edx;
    eax = MEM32(esp + 0x4C);
    edx = MEM32(esp + 0x38);
    edi = edi + eax;
    eax = edi + ebp;
    MEM32(0x299F2C) = eax;
    eax = ebp;
    eax = eax - edx;
    MEM32(esp + 0x40) = eax;
    eax = ebp;
    ebx = edx;
    eax = eax >> 1;
    ebx = ebx >> 1;
    edx = eax;
    edx = edx - ebx;
    SET_LO8(ebx, 1);
    esp = esp + 0xC;
    _fa = (uint32_t)(MEM8(esp + 0x2C)) & 0xFFu; _fb = (uint32_t)(LO8(ebx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(esp + 0x2C), LO8(ebx) (8-bit) */
    MEM32(0x299F18) = ecx;
    MEM32(0x299F28) = edi;
    MEM32(esp + 0x44) = edx;
    if (TEST_Z(_fa, _fb)) goto loc_0021447F; /* je: equal / zero */

loc_00214474: ;
    _fa = (uint32_t)(MEM8(esp + 0x24)) & 0xFFu; _fb = (uint32_t)(LO8(ebx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(esp + 0x24), LO8(ebx) (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0021447F; /* je: equal / zero */

loc_0021447A: ;
    edx--;
    MEM32(esp + 0x44) = edx;

loc_0021447F: ;
    edx = MEM32(esp + 0x3C);
    ebx = MEM32(esp + 0x20);
    _fa = (uint32_t)(edx) & 0xFFFFFFFFu; _fb = (uint32_t)(0x10000) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test edx, 0x10000 (32-bit) */
    edx = ebp;
    if (TEST_Z(_fa, _fb)) goto loc_002144A5; /* je: equal / zero */

loc_00214491: ;
    edx = (uint32_t)((int32_t)edx * (int32_t)esi);
    esi = esi >> 1;
    esi = (uint32_t)((int32_t)esi * (int32_t)eax);
    edx = edx + ebx;
    esi = esi + edx;
    MEM32(0x299F24) = esi;
    goto loc_002144B9;

loc_002144A5: ;
    edx = (uint32_t)((int32_t)edx * (int32_t)esi);
    esi = esi >> 1;
    esi = (uint32_t)((int32_t)esi * (int32_t)eax);
    edx = edx + ebx;
    esi = esi + edx;
    MEM32(0x299F24) = edx;
    edx = esi;

loc_002144B9: ;
    ebx = MEM32(esp + 0x28);
    esi = MEM32(esp + 0x24);
    ebx = ebx >> 1;
    ebx = (uint32_t)((int32_t)ebx * (int32_t)eax);
    eax = esi;
    eax = eax >> 1;
    eax = eax + ebx;
    edx = edx + eax;
    MEM32(0x299F20) = edx;
    edx = MEM32(0x299F24);
    edx = edx + eax;
    eax = MEM32(esp + 0x3C);
    _fa = (uint32_t)(HI8(eax)) & 0xFFu; _fb = (uint32_t)(8) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test HI8(eax), 8 (8-bit) */
    MEM32(0x299F24) = edx;
    if (TEST_Z(_fa, _fb)) goto loc_0021450D; /* je: equal / zero */

loc_002144EB: ;
    eax = MEM32(0x299F1C);
    MEM32(0x299F28) = ecx;
    ecx = MEM32(0x299F2C);
    MEM32(0x299F18) = edi;
    MEM32(0x299F1C) = ecx;
    MEM32(0x299F2C) = eax;

loc_0021450D: ;
    ebx = MEM32(esp + 0x28);
    _fa = (uint32_t)(LO8(ebx)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(ebx), 1 (8-bit) */
    edx = MEM32(esp + 0x30);
    eax = ebx + edx + -1;
    MEM32(esp + 0x28) = ebx;
    MEM32(esp + 0x20) = eax;
    if (TEST_Z(_fa, _fb)) goto loc_002145AB; /* je: equal / zero */

loc_0021452A: ;
    _fa = (uint32_t)(ebx) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp ebx, eax (32-bit) */
    if (CMP_G(_fas, _fbs)) goto loc_002145AB; /* jg: greater (signed >) */

loc_0021452E: ;
    edi = MEM32(esp + 0x2C);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, edi);
    PUSH32(esp, esi);
    { uint32_t _icall_target = MEM32(0x287258); PUSH32(esp, 0x0021453Au); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_0021453A: ;
    ecx = MEM32(esp + 0x3C);
    eax = MEM32(0x299F18);
    edx = MEM32(0x299F24);
    eax = eax + ecx;
    MEM32(0x299F18) = eax;
    eax = eax + ebp;
    MEM32(0x299F1C) = eax;
    eax = MEM32(0x299F28);
    eax = eax + ecx;
    ecx = MEM32(0x299F20);
    MEM32(0x299F28) = eax;
    eax = eax + ebp;
    MEM32(0x299F2C) = eax;
    eax = MEM32(esp + 0x4C);
    ecx = ecx + eax;
    edx = edx + eax;
    eax = MEM32(0x299F10);
    MEM32(0x299F20) = ecx;
    eax = eax + MEM32(esp + 0x20);
    ecx = MEM32(esp + 0x24);
    MEM32(0x299F10) = eax;
    eax = eax + ecx;
    esp = esp + 8;
    ebx++;
    MEM32(0x299F14) = eax;
    eax = MEM32(esp + 0x20);
    MEM32(0x299F24) = edx;
    MEM32(esp + 0x28) = ebx;
    goto loc_002145AF;

loc_002145AB: ;
    edi = MEM32(esp + 0x2C);

loc_002145AF: ;
    ecx = MEM32(esp + 0x14);
    ecx = (uint32_t)(-(int32_t)ecx);
    ecx = ecx & 3;
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(edi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp ecx, edi (32-bit) */
    MEM32(esp + 0x3C) = ecx;
    if (CMP_BE(_fa, _fb)) goto loc_002145C4; /* jbe: below or equal (unsigned <=) */

loc_002145C0: ;
    MEM32(esp + 0x3C) = edi;

loc_002145C4: ;
    edx = esi;
    edx = edx & 1;
    _fa = (uint32_t)(edx) & 0xFFFFFFFFu; _fb = (uint32_t)(edi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edx, edi (32-bit) */
    MEM32(esp + 0x14) = edx;
    if (CMP_BE(_fa, _fb)) goto loc_002145D7; /* jbe: below or equal (unsigned <=) */

loc_002145D1: ;
    MEM32(esp + 0x14) = edi;
    edx = edi;

loc_002145D7: ;
    ecx = MEM32(0x28724C);
    ebx = MEM32(ecx);
    _fa = (uint32_t)(LO8(ebx)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(ebx), 1 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_002145FB; /* je: equal / zero */

loc_002145E4: ;
    _fa = (uint32_t)(ebx) & 0xFFFFFFFFu; _fb = (uint32_t)(0x2000) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp ebx, 0x2000 (32-bit) */
    if (CMP_A(_fa, _fb)) goto loc_002145FF; /* ja: above (unsigned >) */

loc_002145EC: ;
    eax = MEM32(esp + 0x30);
    eax = ebx + eax * 4;
    MEM32(ecx) = eax;
    eax = MEM32(esp + 0x20);
    goto loc_00214605;

loc_002145FB: ;
    _fa = (uint32_t)(ebx) & 0xFFFFFFFFu; _fb = (uint32_t)(ebx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ebx, ebx (32-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_00214605; /* jne: not equal / not zero */

loc_002145FF: ;
    MEM32(ecx) = 0x80;

loc_00214605: ;
    ebx = MEM32(esp + 0x28);
    _fa = (uint32_t)(ebx) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp ebx, eax (32-bit) */
    if (CMP_GE(_fas, _fbs)) goto loc_00214760; /* jge: greater or equal (signed >=) */

loc_00214611: ;
    eax = eax - ebx;
    eax--;
    eax = eax >> 1;
    eax++;
    MEM32(esp + 0x40) = eax;
    eax = ebx + eax * 2;
    MEM32(esp + 0x28) = eax;
    goto loc_00214630;

loc_00214624: ;
    ecx = MEM32(0x28724C);
    edx = MEM32(esp + 0x14);
    edi = edi;

loc_00214630: ;
    eax = MEM32(0x287248);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    ebx = MEM32(ecx);
    MEM32(esp + 0x30) = esi;
    if (TEST_NZ(_fa, _fb)) goto loc_00214669; /* jne: not equal / not zero */

loc_0021463F: ;
    esi = MEM32(esp + 0x3C);
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(edx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp esi, edx (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_00214669; /* je: equal / zero */

loc_00214647: ;
    _fa = (uint32_t)(MEM32(0x29BF68)) & 0xFFFFFFFFu; _fb = (uint32_t)(1) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(0x29BF68), 1 (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_00214674; /* jne: not equal / not zero */

loc_00214650: ;
    _fa = (uint32_t)(LO8(ebx)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(ebx), 1 (8-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_00214669; /* jne: not equal / not zero */

loc_00214655: ;
    edx = ebx;
    edx = edx | 4;
    MEM32(ecx) = edx;
    ecx = 0x287244;
    { uint64_t _tsc = dah_read_tsc(); eax = (uint32_t)_tsc; edx = (uint32_t)(_tsc >> 32); } /* rdtsc */
    MEM32(ecx) = eax;
    edx = MEM32(esp + 0x14);

loc_00214669: ;
    _fa = (uint32_t)(LO8(ebx)) & 0xFFu; _fb = (uint32_t)(2) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(ebx), 2 (8-bit) */
    esi = edx;
    if (TEST_NZ(_fa, _fb)) goto loc_00214674; /* jne: not equal / not zero */

loc_00214670: ;
    esi = MEM32(esp + 0x3C);

loc_00214674: ;
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(esi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test esi, esi (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00214691; /* je: equal / zero */

loc_00214678: ;
    eax = MEM32(esp + 0x24);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, eax);
    PUSH32(esp, esi);
    { uint32_t _icall_target = MEM32(0x287238); PUSH32(esp, 0x00214684u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00214684: ;
    edi = MEM32(esp + 0x34);
    esp = esp + 8;
    MEM32(esp + 0x30) = eax;
    edi = edi - esi;

loc_00214691: ;
    esi = MEM32(0x287254);
    esi = ~esi;
    ebx = edi;
    esi = esi >> 2;
    edi = edi >> 2;
    esi = esi & edi;
    ecx = esi * 4;
    ebx = ebx - ecx;
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(esi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test esi, esi (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_002146C6; /* je: equal / zero */

loc_002146B0: ;
    _fa = (uint32_t)(MEM8(esp + 0x30)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(esp + 0x30), 1 (8-bit) */
    PUSH32(esp, esi);
    if (TEST_Z(_fa, _fb)) goto loc_002146C0; /* je: equal / zero */

loc_002146B8: ;
    { uint32_t _icall_esp = g_esp;
    { uint32_t _icall_target = MEM32(0x287228); PUSH32(esp, 0x002146BEu); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_002146BE: ;
    goto loc_002146C6;

loc_002146C0: ;
    { uint32_t _icall_esp = g_esp;
    { uint32_t _icall_target = MEM32(0x287250); PUSH32(esp, 0x002146C6u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_002146C6: ;
    _fa = (uint32_t)(ebx) & 0xFFFFFFFFu; _fb = (uint32_t)(ebx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ebx, ebx (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_002146DC; /* je: equal / zero */

loc_002146CA: ;
    edx = MEM32(esp + 0x30);
    eax = edx + esi * 4;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, eax);
    PUSH32(esp, ebx);
    { uint32_t _icall_target = MEM32(0x287238); PUSH32(esp, 0x002146D9u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_002146D9: ;
    esp = esp + 8;

loc_002146DC: ;
    PUSH32(esp, 0x002146E1u); sub_00214280(); /* call 0x00214280 */

loc_002146E1: ;
    edx = MEM32(0x299F1C);
    ecx = MEM32(esp + 0x34);
    eax = edx + ecx;
    edx = MEM32(0x299F20);
    MEM32(0x299F18) = eax;
    eax = eax + ebp;
    MEM32(0x299F1C) = eax;
    eax = MEM32(0x299F2C);
    eax = eax + ecx;
    ecx = MEM32(0x299F24);
    edi = MEM32(esp + 0x2C);
    esi = MEM32(esp + 0x24);
    MEM32(0x299F28) = eax;
    eax = eax + ebp;
    MEM32(0x299F2C) = eax;
    eax = MEM32(esp + 0x44);
    ecx = ecx + eax;
    edx = edx + eax;
    MEM32(0x299F24) = ecx;
    ecx = MEM32(0x299F14);
    MEM32(0x299F20) = edx;
    edx = MEM32(esp + 0x18);
    eax = ecx + edx;
    ecx = MEM32(esp + 0x1C);
    MEM32(0x299F10) = eax;
    eax = eax + ecx;
    MEM32(0x299F14) = eax;
    MEM32(esp + 0x40) = MEM32(esp + 0x40) - 1;
    if ((MEM32(esp + 0x40) != 0)) goto loc_00214624; /* jne: not equal / not zero */

loc_0021475C: ;
    eax = MEM32(esp + 0x20);

loc_00214760: ;
    _fa = (uint32_t)(MEM32(esp + 0x28)) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(esp + 0x28), eax (32-bit) */
    if (CMP_G(_fas, _fbs)) goto loc_00214771; /* jg: greater (signed >) */

loc_00214766: ;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, edi);
    PUSH32(esp, esi);
    { uint32_t _icall_target = MEM32(0x287258); PUSH32(esp, 0x0021476Eu); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_0021476E: ;
    esp = esp + 8;

loc_00214771: ;
    eax = MEM32(0x2879B0);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebp);
    POP32(esp, ebx);
    if (TEST_Z(_fa, _fb)) goto loc_00214780; /* je: equal / zero */

loc_0021477E: ;
    /* emms - empty MMX state */

loc_00214780: ;
    esp += 4; return; /* ret */

}

/**
 * sub_00214790
 * Original: 0x00214790 - 0x00215144 (2484 bytes, 617 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00214790(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_00214790: ;
    esp = esp - 0x84;
    ecx = MEM32(esp + 0x94);
    edx = MEM32(esp + 0xB0);
    eax = MEM32(esp + 0xB8);
    PUSH32(esp, ebx);
    PUSH32(esp, ebp);
    ebp = MEM32(esp + 0xBC);
    PUSH32(esp, esi);
    esi = MEM32(esp + 0xC8);
    PUSH32(esp, edi);
    esi = esi & 0x70000000;
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(0x60000000) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp esi, 0x60000000 (32-bit) */
    edi = ecx;
    MEM32(esp + 0x30) = edx;
    MEM32(esp + 0x4C) = eax;
    MEM32(esp + 0x54) = ebp;
    MEM32(esp + 0x40) = edi;
    if (CMP_NE(_fa, _fb)) goto loc_00214815; /* jne: not equal / not zero */

loc_002147DD: ;
    MEM32(esp + 0xB8) = MEM32(esp + 0xB8) >> 1;
    MEM32(esp + 0xC8) = MEM32(esp + 0xC8) >> 1;
    eax = MEM32(esp + 0xAC);
    edx = edx >> 1;
    ecx = ecx + ecx;
    ebp = ebp + ebp;
    MEM32(esp + 0x18) = eax;
    eax = eax + eax;
    MEM32(esp + 0xC0) = edx;
    MEM32(esp + 0xA4) = ecx;
    MEM32(esp + 0xAC) = eax;
    goto loc_0021481D;

loc_00214815: ;
    MEM32(esp + 0x18) = 0;

loc_0021481D: ;
    eax = MEM32(esp + 0x98);
    edi = (uint32_t)((int32_t)edi * (int32_t)MEM32(esp + 0xA0));
    MEM32(0x299F34) = eax;
    eax = MEM32(esp + 0xD4);
    ebx = MEM32(eax);
    ebx = (uint32_t)((int32_t)ebx * (int32_t)MEM32(esp + 0x9C));
    ebx = ebx + MEM32(esp + 0x98);
    edi = edi + ebx;
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(0x20000000) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp esi, 0x20000000 (32-bit) */
    MEM32(0x299F10) = edi;
    if (CMP_EQ(_fa, _fb)) goto loc_00214861; /* je: equal / zero */

loc_00214859: ;
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(0x50000000) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp esi, 0x50000000 (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_0021486A; /* jne: not equal / not zero */

loc_00214861: ;
    ecx = ecx + ecx;
    MEM32(esp + 0xA4) = ecx;

loc_0021486A: ;
    ebx = MEM32(esp + 0xBC);
    edi = MEM32(esp + 0xAC);
    MEM32(esp + 0x1C) = ecx;
    ecx = esp + 0x2C;
    ebx = ebx >> 4;
    PUSH32(esp, ecx);
    edi = edi - ebx;
    ebx = MEM32(esp + 0xD0);
    PUSH32(esp, edx);
    MEM32(esp + 0x1C) = edi;
    PUSH32(esp, 0x10);
    edi = esp + 0x28;
    PUSH32(esp, 0x0021489Du); sub_00213E80(); /* call 0x00213E80 */

loc_0021489D: ;
    eax = MEM32(esp + 0xCC);
    edx = esp + 0x48;
    PUSH32(esp, edx);
    PUSH32(esp, eax);
    eax = MEM32(esp + 0xE8);
    PUSH32(esp, 0x20);
    edi = esp + 0xBC;
    PUSH32(esp, 0x002148BFu); sub_00213E80(); /* call 0x00213E80 */

loc_002148BF: ;
    esp = esp + 0x18;
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(0x30000000) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp esi, 0x30000000 (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_002148E2; /* je: equal / zero */

loc_002148CA: ;
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(0x50000000) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp esi, 0x50000000 (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_002148E2; /* je: equal / zero */

loc_002148D2: ;
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(0x40000000) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp esi, 0x40000000 (32-bit) */
    MEM32(esp + 0x24) = 1;
    if (CMP_NE(_fa, _fb)) goto loc_002148EA; /* jne: not equal / not zero */

loc_002148E2: ;
    MEM32(esp + 0x24) = 2;

loc_002148EA: ;
    ecx = MEM32(esp + 0xD4);
    edx = MEM32(ecx);
    ecx = MEM32(esp + 0xA4);
    edx = (uint32_t)((int32_t)edx * (int32_t)MEM32(esp + 0x24));
    eax = MEM32(0x299F10);
    eax = eax + ecx;
    esi = MEM32(esp + 0xB4);
    ecx = MEM32(esp + 0xB0);
    ebx = MEM32(esp + 0xD0);
    MEM32(0x299F14) = eax;
    eax = MEM32(esp + 0xB8);
    eax = (uint32_t)((int32_t)eax * (int32_t)ebp);
    ecx = ecx + eax;
    ecx = ecx + esi;
    eax = eax + esi;
    eax = eax + ebx;
    MEM32(0x299F18) = ecx;
    ecx = ecx + ebp;
    MEM32(0x299F28) = eax;
    eax = eax + ebp;
    MEM32(0x299F1C) = ecx;
    MEM32(0x299F2C) = eax;
    esi = ebp;
    esi = (uint32_t)((int32_t)esi * (int32_t)0xF);
    eax = ebp;
    eax = eax >> 1;
    ecx = eax + -16;
    MEM32(esp + 0x64) = ecx;
    ecx = MEM32(esp + 0xBC);
    edi = ecx;
    edi = edi & 0xF;
    esi = esi - ecx;
    esi = esi + edi;
    ecx = ecx >> 1;
    MEM32(esp + 0x1C) = edi;
    edi = ecx;
    edi = edi & 7;
    edx = edx << 4;
    edi = edi + eax * 8;
    edi = edi - ecx;
    ecx = MEM32(esp + 0x1C);
    MEM32(esp + 0x34) = edx;
    edx = edx >> 4;
    MEM32(esp + 0x44) = edi;
    ecx = ecx - MEM32(esp + 0xBC);
    ecx = (uint32_t)((int32_t)ecx * (int32_t)edx);
    edx = MEM32(esp + 0xA4);
    edx = (uint32_t)((int32_t)edx * (int32_t)0xF);
    ecx = ecx + edx;
    _fa = (uint32_t)(MEM32(esp + 0xCC)) & 0xFFFFFFFFu; _fb = (uint32_t)(0x10000) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test MEM32(esp + 0xCC), 0x10000 (32-bit) */
    edx = MEM32(esp + 0xC8);
    ebx = eax + -8;
    MEM32(esp + 0x58) = esi;
    MEM32(esp + 0x48) = ecx;
    edi = ebp;
    if (TEST_Z(_fa, _fb)) goto loc_002149E4; /* je: equal / zero */

loc_002149C5: ;
    edi = (uint32_t)((int32_t)edi * (int32_t)edx);
    edi = edi + MEM32(esp + 0xB0);
    edx = edx >> 1;
    edx = (uint32_t)((int32_t)edx * (int32_t)eax);
    edx = edx + edi;
    MEM32(0x299F20) = edi;
    MEM32(0x299F24) = edx;
    goto loc_00214A01;

loc_002149E4: ;
    edi = (uint32_t)((int32_t)edi * (int32_t)edx);
    edi = edi + MEM32(esp + 0xB0);
    edx = edx >> 1;
    edx = (uint32_t)((int32_t)edx * (int32_t)eax);
    edx = edx + edi;
    MEM32(0x299F24) = edi;
    MEM32(0x299F20) = edx;

loc_00214A01: ;
    edx = MEM32(esp + 0xB8);
    edi = edx;
    edi = edi >> 1;
    edi = (uint32_t)((int32_t)edi * (int32_t)eax);
    eax = MEM32(esp + 0xB4);
    eax = eax >> 1;
    eax = eax + edi;
    MEM32(0x299F20) = MEM32(0x299F20) + eax;
    edi = MEM32(0x299F24);
    edi = edi + eax;
    eax = MEM32(esp + 0xCC);
    _fa = (uint32_t)(HI8(eax)) & 0xFFu; _fb = (uint32_t)(8) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test HI8(eax), 8 (8-bit) */
    MEM32(0x299F24) = edi;
    if (TEST_Z(_fa, _fb)) goto loc_00214A66; /* je: equal / zero */

loc_00214A3A: ;
    eax = MEM32(0x299F18);
    edi = MEM32(0x299F28);
    MEM32(0x299F18) = edi;
    edi = MEM32(0x299F2C);
    MEM32(0x299F28) = eax;
    eax = MEM32(0x299F1C);
    MEM32(0x299F1C) = edi;
    MEM32(0x299F2C) = eax;

loc_00214A66: ;
    eax = MEM32(esp + 0xC0);
    edi = MEM32(esp + 0xBC);
    eax = edx + eax + -1;
    edx = edx >> 4;
    edx = (uint32_t)((int32_t)edx * (int32_t)MEM32(esp + 0xAC));
    MEM32(esp + 0x5C) = eax;
    eax = MEM32(esp + 0xB4);
    edi = eax + edi + -1;
    MEM32(esp + 0x20) = edx;
    edx = ((int32_t)eax < 0) ? 0xFFFFFFFF : 0; /* cdq */
    edx = edx & 0xF;
    eax = eax + edx;
    edx = MEM32(esp + 0xA8);
    MEM32(esp + 0x28) = edi;
    edi = eax;
    eax = MEM32(esp + 0x20);
    eax = eax + edx;
    edx = MEM32(esp + 0x5C);
    edi = (uint32_t)((int32_t)edi >> 4);
    edi = edi + eax;
    eax = MEM32(esp + 0xB8);
    eax = eax + 0xF;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(edx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, edx (32-bit) */
    MEM32(esp + 0x10) = edi;
    if (CMP_G(_fas, _fbs)) goto loc_00214FEB; /* jg: greater (signed >) */

loc_00214ACE: ;
    MEM32(esp + 0x20) = eax;
    goto loc_00214AE0;

    /* nop */
    goto loc_00214AE0;

    /* nop */

loc_00214AE0: ;
    eax = MEM32(esp + 0xB4);
    edx = MEM32(esp + 0x28);
    MEM32(esp + 0x38) = eax;
    eax = eax + 0x1F;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(edx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, edx (32-bit) */
    if (CMP_G(_fas, _fbs)) goto loc_00214E4D; /* jg: greater (signed >) */

loc_00214AFA: ;
    MEM32(esp + 0x60) = eax;
    eax = MEM32(esp + 0x18);
    esi = 1;
    ecx = edi + eax;
    esi = esi - eax;
    MEM32(esp + 0x50) = ecx;
    MEM32(esp + 0x68) = esi;
    goto loc_00214B20;

loc_00214B16: ;
    esi = MEM32(esp + 0x68);
    /* nop */

loc_00214B20: ;
    SET_LO8(eax, MEM8(esi + ecx));
    edx = 0; /* xor self */
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    SET_LO8(edx, (TEST_NZ(_fa, _fb)) ? 1 : 0); /* setne */
    eax = 0; /* xor self */
    _fa = (uint32_t)(MEM8(edi)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(edi), LO8(eax) (8-bit) */
    SET_LO8(eax, (CMP_NE(_fa, _fb)) ? 1 : 0); /* setne */
    esi = eax + edx * 2;
    eax = MEM32(esp + 0x18);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00214B51; /* je: equal / zero */

loc_00214B3C: ;
    edx = 0; /* xor self */
    _fa = (uint32_t)(MEM8(edi + eax + 1)) & 0xFFu; _fb = (uint32_t)(LO8(edx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(edi + eax + 1), LO8(edx) (8-bit) */
    SET_LO8(edx, (CMP_NE(_fa, _fb)) ? 1 : 0); /* setne */
    eax = 0; /* xor self */
    _fa = (uint32_t)(MEM8(ecx)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(ecx), LO8(eax) (8-bit) */
    SET_LO8(eax, (CMP_NE(_fa, _fb)) ? 1 : 0); /* setne */
    ecx = eax + edx * 2;
    esi = esi | ecx;

loc_00214B51: ;
    esi--;
    if ((esi == 0)) goto loc_00214CFE; /* je: equal / zero */

loc_00214B58: ;
    esi--;
    if ((esi == 0)) goto loc_00214BFB; /* je: equal / zero */

loc_00214B5F: ;
    esi--;
    if ((esi != 0)) goto loc_00214D99; /* jne: not equal / not zero */

loc_00214B66: ;
    ecx = 0xA;
    esi = 0x299F10;
    edi = esp + 0x6C;
    memcpy((void*)XBOX_PTR(edi), (void*)XBOX_PTR(esi), ecx * 4);
    esi += ecx * 4; edi += ecx * 4; ecx = 0; /* rep movsd */
    esi = 8;
    goto loc_00214B80;

    /* nop */

loc_00214B80: ;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 8);
    { uint32_t _icall_target = MEM32(0x287250); PUSH32(esp, 0x00214B88u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00214B88: ;
    edx = MEM32(0x299F1C);
    ecx = MEM32(0x299F24);
    eax = edx + ebp + -32;
    edx = MEM32(0x299F20);
    MEM32(0x299F18) = eax;
    eax = eax + ebp;
    MEM32(0x299F1C) = eax;
    eax = MEM32(0x299F2C);
    eax = eax + ebp + -32;
    MEM32(0x299F28) = eax;
    eax = eax + ebp;
    MEM32(0x299F2C) = eax;
    eax = MEM32(esp + 0x64);
    ecx = ecx + eax;
    edx = edx + eax;
    MEM32(0x299F24) = ecx;
    ecx = MEM32(0x299F14);
    MEM32(0x299F20) = edx;
    edx = MEM32(esp + 0x3C);
    eax = ecx + edx;
    ecx = MEM32(esp + 0xA4);
    MEM32(0x299F10) = eax;
    eax = eax + ecx;
    esi--;
    MEM32(0x299F14) = eax;
    if ((esi != 0)) goto loc_00214B80; /* jne: not equal / not zero */

loc_00214BF6: ;
    goto loc_00214D85;

loc_00214BFB: ;
    edx = MEM32(0x299F28);
    eax = 0x10;
    ecx = 0xA;
    esi = 0x299F10;
    edi = esp + 0x6C;
    memcpy((void*)XBOX_PTR(edi), (void*)XBOX_PTR(esi), ecx * 4);
    esi += ecx * 4; edi += ecx * 4; ecx = 0; /* rep movsd */
    esi = MEM32(0x299F1C);
    edi = MEM32(0x299F18);
    ecx = MEM32(0x299F2C);
    esi = esi + eax;
    edi = edi + eax;
    edx = edx + eax;
    ecx = ecx + eax;
    eax = MEM32(0x299F20);
    MEM32(0x299F1C) = esi;
    esi = 8;
    eax = eax + esi;
    MEM32(0x299F18) = edi;
    edi = MEM32(0x299F24);
    MEM32(0x299F28) = edx;
    edx = MEM32(0x299F10);
    MEM32(0x299F2C) = ecx;
    ecx = MEM32(0x299F14);
    MEM32(0x299F20) = eax;
    eax = MEM32(esp + 0x34);
    edi = edi + esi;
    edx = edx + eax;
    ecx = ecx + eax;
    MEM32(0x299F24) = edi;
    MEM32(0x299F10) = edx;
    MEM32(0x299F14) = ecx;

loc_00214C87: ;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 4);
    { uint32_t _icall_target = MEM32(0x287250); PUSH32(esp, 0x00214C8Fu); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00214C8F: ;
    edx = MEM32(0x299F1C);
    ecx = MEM32(0x299F24);
    eax = edx + ebp + -16;
    edx = MEM32(0x299F20);
    MEM32(0x299F18) = eax;
    eax = eax + ebp;
    MEM32(0x299F1C) = eax;
    eax = MEM32(0x299F2C);
    eax = eax + ebp + -16;
    ecx = ecx + ebx;
    edx = edx + ebx;
    MEM32(0x299F28) = eax;
    eax = eax + ebp;
    MEM32(0x299F24) = ecx;
    ecx = MEM32(0x299F14);
    MEM32(0x299F20) = edx;
    edx = MEM32(esp + 0x2C);
    MEM32(0x299F2C) = eax;
    eax = ecx + edx;
    ecx = MEM32(esp + 0xA4);
    MEM32(0x299F10) = eax;
    eax = eax + ecx;
    esi--;
    MEM32(0x299F14) = eax;
    if ((esi != 0)) goto loc_00214C87; /* jne: not equal / not zero */

loc_00214CF9: ;
    goto loc_00214D85;

loc_00214CFE: ;
    ecx = 0xA;
    esi = 0x299F10;
    edi = esp + 0x6C;
    memcpy((void*)XBOX_PTR(edi), (void*)XBOX_PTR(esi), ecx * 4);
    esi += ecx * 4; edi += ecx * 4; ecx = 0; /* rep movsd */
    esi = 8;

loc_00214D13: ;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 4);
    { uint32_t _icall_target = MEM32(0x287250); PUSH32(esp, 0x00214D1Bu); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00214D1B: ;
    edx = MEM32(0x299F1C);
    ecx = MEM32(0x299F24);
    eax = edx + ebp + -16;
    edx = MEM32(0x299F20);
    MEM32(0x299F18) = eax;
    eax = eax + ebp;
    MEM32(0x299F1C) = eax;
    eax = MEM32(0x299F2C);
    eax = eax + ebp + -16;
    ecx = ecx + ebx;
    edx = edx + ebx;
    MEM32(0x299F28) = eax;
    eax = eax + ebp;
    MEM32(0x299F24) = ecx;
    ecx = MEM32(0x299F14);
    MEM32(0x299F20) = edx;
    edx = MEM32(esp + 0x2C);
    MEM32(0x299F2C) = eax;
    eax = ecx + edx;
    ecx = MEM32(esp + 0xA4);
    MEM32(0x299F10) = eax;
    eax = eax + ecx;
    esi--;
    MEM32(0x299F14) = eax;
    if ((esi != 0)) goto loc_00214D13; /* jne: not equal / not zero */

loc_00214D85: ;
    esi = esp + 0x6C;
    edi = 0x299F10;
    ecx = 0xA;
    memcpy((void*)XBOX_PTR(edi), (void*)XBOX_PTR(esi), ecx * 4);
    esi += ecx * 4; edi += ecx * 4; ecx = 0; /* rep movsd */
    edi = MEM32(esp + 0x10);

loc_00214D99: ;
    eax = MEM32(0x299F18);
    ecx = MEM32(0x299F28);
    esi = MEM32(0x299F1C);
    edx = 0x20;
    eax = eax + edx;
    MEM32(0x299F18) = eax;
    eax = MEM32(0x299F2C);
    eax = eax + edx;
    ecx = ecx + edx;
    MEM32(0x299F2C) = eax;
    MEM32(0x299F28) = ecx;
    ecx = MEM32(0x299F24);
    esi = esi + edx;
    eax = 0x10;
    ecx = ecx + eax;
    MEM32(0x299F1C) = esi;
    esi = MEM32(0x299F20);
    esi = esi + eax;
    eax = MEM32(0x299F10);
    MEM32(0x299F24) = ecx;
    ecx = MEM32(esp + 0x34);
    ecx = ecx + ecx;
    eax = eax + ecx;
    MEM32(0x299F10) = eax;
    eax = MEM32(esp + 0x38);
    eax = eax + edx;
    MEM32(0x299F20) = esi;
    esi = MEM32(0x299F14);
    esi = esi + ecx;
    ecx = MEM32(esp + 0x50);
    MEM32(esp + 0x38) = eax;
    eax = MEM32(esp + 0x60);
    eax = eax + edx;
    edx = MEM32(esp + 0x28);
    edi = edi + 2;
    ecx = ecx + 2;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(edx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, edx (32-bit) */
    MEM32(0x299F14) = esi;
    MEM32(esp + 0x10) = edi;
    MEM32(esp + 0x50) = ecx;
    MEM32(esp + 0x60) = eax;
    if (CMP_LE(_fas, _fbs)) goto loc_00214B16; /* jle: less or equal (signed <=) */

loc_00214E45: ;
    ecx = MEM32(esp + 0x48);
    esi = MEM32(esp + 0x58);

loc_00214E4D: ;
    edx = MEM32(esp + 0x38);
    eax = MEM32(esp + 0x28);
    edx = edx + 0xF;
    _fa = (uint32_t)(edx) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edx, eax (32-bit) */
    if (CMP_G(_fas, _fbs)) goto loc_00214F6A; /* jg: greater (signed >) */

loc_00214E60: ;
    edx = MEM32(esp + 0x18);
    _fa = (uint32_t)(edx) & 0xFFFFFFFFu; _fb = (uint32_t)(edx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test edx, edx (32-bit) */
    eax = ZX8(MEM8(edi));
    if (TEST_Z(_fa, _fb)) goto loc_00214E71; /* je: equal / zero */

loc_00214E6B: ;
    edx = ZX8(MEM8(edi + edx));
    eax = eax | edx;

loc_00214E71: ;
    edi++;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    MEM32(esp + 0x10) = edi;
    if (TEST_Z(_fa, _fb)) goto loc_00214F20; /* je: equal / zero */

loc_00214E7E: ;
    ecx = 0xA;
    esi = 0x299F10;
    edi = esp + 0x6C;
    memcpy((void*)XBOX_PTR(edi), (void*)XBOX_PTR(esi), ecx * 4);
    esi += ecx * 4; edi += ecx * 4; ecx = 0; /* rep movsd */
    esi = 8;

loc_00214E93: ;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 4);
    { uint32_t _icall_target = MEM32(0x287250); PUSH32(esp, 0x00214E9Bu); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00214E9B: ;
    eax = MEM32(0x299F1C);
    ecx = MEM32(0x299F2C);
    edx = MEM32(0x299F20);
    eax = eax + ebp + -16;
    MEM32(0x299F18) = eax;
    eax = eax + ebp;
    MEM32(0x299F1C) = eax;
    eax = ecx + ebp + -16;
    ecx = MEM32(0x299F24);
    MEM32(0x299F28) = eax;
    eax = eax + ebp;
    edx = edx + ebx;
    MEM32(0x299F2C) = eax;
    eax = MEM32(esp + 0x2C);
    ecx = ecx + ebx;
    MEM32(0x299F20) = edx;
    edx = MEM32(0x299F14);
    eax = eax + edx;
    MEM32(0x299F24) = ecx;
    ecx = MEM32(esp + 0xA4);
    MEM32(0x299F10) = eax;
    eax = eax + ecx;
    esi--;
    MEM32(0x299F14) = eax;
    if ((esi != 0)) goto loc_00214E93; /* jne: not equal / not zero */

loc_00214F04: ;
    ecx = 0xA;
    esi = esp + 0x6C;
    edi = 0x299F10;
    memcpy((void*)XBOX_PTR(edi), (void*)XBOX_PTR(esi), ecx * 4);
    esi += ecx * 4; edi += ecx * 4; ecx = 0; /* rep movsd */
    edi = MEM32(esp + 0x10);
    ecx = MEM32(esp + 0x48);
    esi = MEM32(esp + 0x58);

loc_00214F20: ;
    edx = MEM32(0x299F1C);
    eax = 0x10;
    edx = edx + eax;
    MEM32(0x299F1C) = edx;
    MEM32(0x299F2C) = MEM32(0x299F2C) + eax;
    edx = MEM32(0x299F20);
    eax = 8;
    edx = edx + eax;
    MEM32(0x299F20) = edx;
    edx = MEM32(0x299F24);
    edx = edx + eax;
    eax = MEM32(0x299F14);
    MEM32(0x299F24) = edx;
    edx = MEM32(esp + 0x34);
    eax = eax + edx;
    MEM32(0x299F14) = eax;

loc_00214F6A: ;
    eax = MEM32(0x299F1C);
    edx = MEM32(0x299F2C);
    eax = eax + esi;
    MEM32(0x299F18) = eax;
    eax = eax + ebp;
    MEM32(0x299F1C) = eax;
    eax = esi + edx;
    edx = MEM32(0x299F20);
    MEM32(0x299F28) = eax;
    eax = eax + ebp;
    MEM32(0x299F2C) = eax;
    eax = MEM32(esp + 0x44);
    edx = edx + eax;
    MEM32(0x299F20) = edx;
    edx = MEM32(0x299F24);
    edx = edx + eax;
    eax = MEM32(0x299F14);
    eax = eax + ecx;
    MEM32(0x299F24) = edx;
    edx = MEM32(esp + 0xA4);
    MEM32(0x299F10) = eax;
    eax = eax + edx;
    edx = MEM32(esp + 0x5C);
    MEM32(0x299F14) = eax;
    edi = edi + MEM32(esp + 0x14);
    eax = MEM32(esp + 0x20);
    eax = eax + 0x10;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(edx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, edx (32-bit) */
    MEM32(esp + 0x10) = edi;
    MEM32(esp + 0x20) = eax;
    if (CMP_LE(_fas, _fbs)) goto loc_00214AE0; /* jle: less or equal (signed <=) */

loc_00214FEB: ;
    eax = MEM32(esp + 0x1C);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    edi = MEM32(esp + 0x30);
    ebx = MEM32(esp + 0x54);
    if (TEST_Z(_fa, _fb)) goto loc_0021506D; /* je: equal / zero */

loc_00214FFB: ;
    edx = MEM32(esp + 0xD4);
    ecx = MEM32(esp + 0xBC);
    PUSH32(esp, edx);
    edx = MEM32(esp + 0xD4);
    PUSH32(esp, edx);
    edx = MEM32(esp + 0xD4);
    PUSH32(esp, edx);
    edx = MEM32(esp + 0x58);
    PUSH32(esp, edx);
    edx = MEM32(esp + 0xC4);
    eax = ecx;
    PUSH32(esp, ebx);
    eax = eax & 0xFFFFFFF0u;
    PUSH32(esp, edi);
    ecx = ecx - eax;
    PUSH32(esp, ecx);
    ecx = MEM32(esp + 0xD4);
    PUSH32(esp, ecx);
    ecx = eax + edx;
    eax = (uint32_t)((int32_t)eax * (int32_t)MEM32(esp + 0x44));
    edx = MEM32(esp + 0xD0);
    PUSH32(esp, ecx);
    ecx = MEM32(esp + 0x64);
    PUSH32(esp, edx);
    edx = MEM32(esp + 0xC8);
    PUSH32(esp, ecx);
    PUSH32(esp, edx);
    eax = eax + MEM32(esp + 0xCC);
    edx = MEM32(esp + 0xC8);
    PUSH32(esp, eax);
    PUSH32(esp, 0x0021506Au); sub_00214310(); /* call 0x00214310 */

loc_0021506A: ;
    esp = esp + 0x34;

loc_0021506D: ;
    eax = MEM32(esp + 0xC0);
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(0xF) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), 0xF (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0021512E; /* je: equal / zero */

loc_0021507C: ;
    eax = eax & 0xFFFFFFF0u;
    MEM32(esp + 0x14) = eax;
    eax = MEM32(esp + 0x14);
    ecx = MEM32(esp + 0x30);
    { uint64_t _r = (uint64_t)eax * (uint64_t)ecx;
      eax = (uint32_t)_r; edx = (uint32_t)(_r >> 32); }
    ecx = MEM32(esp + 0xC0);
    { uint64_t _dividend = ((uint64_t)edx << 32) | eax;
      eax = (uint32_t)(_dividend / (uint32_t)ecx);
      edx = (uint32_t)(_dividend % (uint32_t)ecx); }
    esi = eax;
    eax = MEM32(esp + 0x40);
    ecx = ebx;
    eax = (uint32_t)((int32_t)eax * (int32_t)ebp);
    ecx = (uint32_t)((int32_t)ecx * (int32_t)MEM32(esp + 0xA4));
    MEM32(esp + 0x3C) = esi;
    MEM32(esp + 0x14) = eax;
    MEM32(esp + 0x44) = ecx;
    eax = MEM32(esp + 0x3C);
    ecx = MEM32(esp + 0x44);
    { uint64_t _r = (uint64_t)eax * (uint64_t)ecx;
      eax = (uint32_t)_r; edx = (uint32_t)(_r >> 32); }
    ecx = MEM32(esp + 0x14);
    { uint64_t _dividend = ((uint64_t)edx << 32) | eax;
      eax = (uint32_t)(_dividend / (uint32_t)ecx);
      edx = (uint32_t)(_dividend % (uint32_t)ecx); }
    edx = MEM32(esp + 0xD4);
    ecx = MEM32(esp + 0xD0);
    PUSH32(esp, edx);
    edx = MEM32(esp + 0xD0);
    PUSH32(esp, ecx);
    ecx = MEM32(esp + 0x54);
    PUSH32(esp, edx);
    edx = MEM32(esp + 0xC8);
    PUSH32(esp, ecx);
    ecx = MEM32(esp + 0xC8);
    PUSH32(esp, ebx);
    edi = edi - esi;
    PUSH32(esp, edi);
    PUSH32(esp, edx);
    edx = MEM32(esp + 0xD0);
    esi = esi + ecx;
    ecx = MEM32(esp + 0xCC);
    PUSH32(esp, esi);
    PUSH32(esp, edx);
    edx = MEM32(esp + 0x64);
    PUSH32(esp, ecx);
    ecx = MEM32(esp + 0xC8);
    PUSH32(esp, edx);
    edx = MEM32(esp + 0xC8);
    eax = eax + ecx;
    PUSH32(esp, eax);
    PUSH32(esp, edx);
    edx = MEM32(esp + 0xCC);
    PUSH32(esp, 0x0021512Bu); sub_00214310(); /* call 0x00214310 */

loc_0021512B: ;
    esp = esp + 0x34;

loc_0021512E: ;
    eax = MEM32(0x2879B0);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebp);
    POP32(esp, ebx);
    if (TEST_Z(_fa, _fb)) goto loc_0021513D; /* je: equal / zero */

loc_0021513B: ;
    /* emms - empty MMX state */

loc_0021513D: ;
    esp = esp + 0x84;
    esp += 4; return; /* ret */

}

/**
 * sub_00215150
 * Original: 0x00215150 - 0x002151A6 (86 bytes, 27 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00215150(void)
{
    uint32_t ebp;

loc_00215150: ;
    PUSH32(esp, ebp);
    ebp = esp;
    g_ebp = ebp; /* publish frame for frameless callees */
    PUSH32(esp, 0xFFFFFFFFu);
    PUSH32(esp, 0x23B130);
    PUSH32(esp, 0x13A174);
    eax = MEM32(0);
    PUSH32(esp, eax);
    MEM32(0) = esp;
    esp = esp - 8;
    PUSH32(esp, ebx);
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    MEM32(ebp + -24) = esp;
    ecx = ecx | 0xFFFFFFFFu;
    MEM32(0x29BF68) = ecx;
    MEM32(ebp + -4) = 0;
    { uint64_t _tsc = dah_read_tsc(); eax = (uint32_t)_tsc; edx = (uint32_t)(_tsc >> 32); } /* rdtsc */
    MEM32(0x29BF68) = 1;
    MEM32(ebp + -4) = ecx;
    ecx = MEM32(ebp + -16);
    MEM32(0) = ecx;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebx);
    esp = ebp;
    POP32(esp, ebp);
    esp += 4; return; /* ret */

}

/**
 * sub_002151D0
 * Original: 0x002151D0 - 0x00215A3E (2158 bytes, 505 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_002151D0(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_002151D0: ;
    eax = MEM32(0x29BF68);
    PUSH32(esp, ebx);
    PUSH32(esp, ebp);
    ebx = 0; /* xor self */
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(ebx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, ebx (32-bit) */
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    if (CMP_NE(_fa, _fb)) goto loc_002151E4; /* jne: not equal / not zero */

loc_002151DF: ;
    PUSH32(esp, 0x002151E4u); sub_00215150(); /* call 0x00215150 */

loc_002151E4: ;
    ecx = MEM32(esp + 0x14);
    eax = ecx + -7;
    edx = 5;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(edx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, edx (32-bit) */
    if (CMP_A(_fa, _fb)) goto loc_002156B9; /* ja: above (unsigned >) */

loc_002151F8: ;
    { uint32_t _jt = MEM32(eax * 4 + 0x215A40); /* switch: 6 entries, 5 targets */
    if (_jt == 0x002151FFu) goto loc_002151FF;
    if (_jt == 0x00215551u) goto loc_00215551;
    if (_jt == 0x002155A9u) goto loc_002155A9;
    if (_jt == 0x002155FEu) goto loc_002155FE;
    if (_jt == 0x0021565Bu) goto loc_0021565B;
    g_seh_ebp = ebp; RECOMP_ITAIL(_jt); return; }

loc_002151FF: ;
    eax = 3;
    ebp = eax;
    MEM32(0x29BF50) = eax;
    MEM32(0x29BF60) = eax;
    eax = 0x25422542;
    MEM32(0x25A7F8) = eax;
    MEM32(0x25A7FC) = eax;
    eax = 0x7FE07FE0;
    MEM32(0x25A800) = eax;
    MEM32(0x25A804) = eax;
    MEM32(0x29BF38) = ebx;
    MEM32(0x29BF58) = ebp;
    MEM32(0x29BF40) = edx;
    MEM32(0x29BF48) = 0xA;
    eax = 0x4210421;

loc_0021524F: ;
    MEM32(0x25A7F0) = eax;
    MEM32(0x25A7F4) = eax;
    eax = MEM32(0x29BF70);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, ecx (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_00215790; /* je: equal / zero */

loc_00215266: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0xFFFFFFFFu) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0xFFFFFFFFu (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_00215377; /* jne: not equal / not zero */

loc_0021526F: ;
    eax = 0; /* xor self */
    MEM32(0x292E60) = eax;
    MEM32(0x292E64) = eax;
    MEM32(0x292E68) = eax;
    MEM32(0x292E6C) = eax;
    MEM32(0x292E70) = eax;
    MEM32(0x292E74) = eax;
    MEM32(0x292E78) = eax;
    MEM32(0x292E7C) = eax;
    MEM32(0x292E80) = eax;
    MEM32(0x292E84) = eax;
    MEM32(0x292E88) = eax;
    MEM32(0x292E8C) = eax;
    MEM32(0x292E90) = eax;
    MEM32(0x292E94) = eax;
    MEM32(0x292E98) = eax;
    MEM32(0x292E9C) = eax;
    MEM32(0x292EA0) = eax;
    esi = 0x292EA4;
    ecx = 0x7DAD;

loc_002152D0: ;
    eax = ecx;
    edx = ((int32_t)eax < 0) ? 0xFFFFFFFF : 0; /* cdq */
    edx = edx & 0x7FFF;
    eax = eax + edx;
    eax = (uint32_t)((int32_t)eax >> 0xF);
    eax = eax << 2;
    MEM32(esi) = eax;
    ecx = ecx + 0x7DAD;
    esi = esi + 4;
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(0x6B0552) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp ecx, 0x6B0552 (32-bit) */
    if (CMP_LE(_fas, _fbs)) goto loc_002152D0; /* jle: less or equal (signed <=) */

loc_002152F4: ;
    ecx = 0x3FC;
    MEM32(0x29320C) = ecx;
    MEM32(0x293210) = ecx;
    MEM32(0x293214) = ecx;
    MEM32(0x293218) = ecx;
    MEM32(0x29321C) = ecx;
    MEM32(0x293220) = ecx;
    MEM32(0x293224) = ecx;
    MEM32(0x293228) = ecx;
    MEM32(0x29322C) = ecx;
    MEM32(0x293230) = ecx;
    MEM32(0x293234) = ecx;
    MEM32(0x293238) = ecx;
    MEM32(0x29323C) = ecx;
    MEM32(0x293240) = ecx;
    MEM32(0x293244) = ecx;
    MEM32(0x293248) = ecx;
    MEM32(0x29324C) = ecx;
    MEM32(0x293250) = ecx;
    MEM32(0x293254) = ecx;
    MEM32(0x293258) = ecx;
    MEM32(0x29325C) = ecx;

loc_00215377: ;
    edx = MEM32(0x29BF50);
    ecx = 0x100;
    eax = 0; /* xor self */
    edi = 0x293680;
    { uint32_t _i; for (_i = 0; _i < ecx; _i++) MEM32(edi + _i*4) = eax; }
    edi += ecx * 4; ecx = 0; /* rep stosd */
    goto loc_00215390;

    /* nop */

loc_00215390: ;
    esi = eax;
    ecx = edx;
    esi = (uint32_t)((int32_t)esi >> LO8(ecx));
    eax++;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0x100) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0x100 (32-bit) */
    MEM32(eax * 4 + 0x293A7C) = esi;
    if (CMP_L(_fas, _fbs)) goto loc_00215390; /* jl: less (signed <) */

loc_002153A5: ;
    ecx = 8;
    ecx = ecx - edx;
    ebx = 1;
    ebx = ebx << LO8(ecx);
    ecx = 0x100;
    edi = 0x293E80;
    ebx--;
    eax = ebx;
    { uint32_t _i; for (_i = 0; _i < ecx; _i++) MEM32(edi + _i*4) = eax; }
    edi += ecx * 4; ecx = 0; /* rep stosd */
    ecx = 0x100;
    eax = 0; /* xor self */
    edi = 0x294290;
    { uint32_t _i; for (_i = 0; _i < ecx; _i++) MEM32(edi + _i*4) = eax; }
    edi += ecx * 4; ecx = 0; /* rep stosd */

loc_002153D0: ;
    edx = eax;
    ecx = ebp;
    edx = (uint32_t)((int32_t)edx >> LO8(ecx));
    ecx = MEM32(0x29BF40);
    edx = edx << LO8(ecx);
    eax++;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0x100) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0x100 (32-bit) */
    MEM32(eax * 4 + 0x29468C) = edx;
    if (CMP_L(_fas, _fbs)) goto loc_002153D0; /* jl: less (signed <) */

loc_002153ED: ;
    ecx = 8;
    ecx = ecx - ebp;
    edx = 1;
    edx = edx << LO8(ecx);
    ecx = MEM32(0x29BF40);
    edi = 0x294A90;
    edx--;
    edx = edx << LO8(ecx);
    ecx = 0x100;
    eax = edx;
    { uint32_t _i; for (_i = 0; _i < ecx; _i++) MEM32(edi + _i*4) = eax; }
    edi += ecx * 4; ecx = 0; /* rep stosd */
    ecx = 0x100;
    eax = 0; /* xor self */
    edi = 0x294EA0;
    { uint32_t _i; for (_i = 0; _i < ecx; _i++) MEM32(edi + _i*4) = eax; }
    edi += ecx * 4; ecx = 0; /* rep stosd */

loc_00215420: ;
    ecx = MEM32(0x29BF60);
    esi = eax;
    esi = (uint32_t)((int32_t)esi >> LO8(ecx));
    ecx = MEM32(0x29BF48);
    esi = esi << LO8(ecx);
    eax++;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0x100) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0x100 (32-bit) */
    MEM32(eax * 4 + 0x29529C) = esi;
    if (CMP_L(_fas, _fbs)) goto loc_00215420; /* jl: less (signed <) */

loc_00215441: ;
    eax = MEM32(0x29BF60);
    ecx = 8;
    ecx = ecx - eax;
    esi = 1;
    esi = esi << LO8(ecx);
    ecx = MEM32(0x29BF48);
    edi = 0x2956A0;
    esi--;
    esi = esi << LO8(ecx);
    ecx = 0x100;
    eax = esi;
    { uint32_t _i; for (_i = 0; _i < ecx; _i++) MEM32(edi + _i*4) = eax; }
    edi += ecx * 4; ecx = 0; /* rep stosd */
    ecx = 0x100;
    eax = 0; /* xor self */
    edi = 0x296EE0;
    { uint32_t _i; for (_i = 0; _i < ecx; _i++) MEM32(edi + _i*4) = eax; }
    edi += ecx * 4; ecx = 0; /* rep stosd */
    /* nop */

loc_00215480: ;
    ecx = MEM32(0x29BF50);
    edi = eax;
    edi = (uint32_t)((int32_t)edi >> LO8(ecx));
    edi = (uint32_t)((int32_t)edi * (int32_t)0x10001);
    MEM32(eax * 4 + 0x2972E0) = edi;
    eax++;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0x100) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0x100 (32-bit) */
    if (CMP_L(_fas, _fbs)) goto loc_00215480; /* jl: less (signed <) */

loc_0021549F: ;
    ebx = (uint32_t)((int32_t)ebx * (int32_t)0x10001);
    eax = ebx;
    ecx = 0x100;
    edi = 0x2976E0;
    { uint32_t _i; for (_i = 0; _i < ecx; _i++) MEM32(edi + _i*4) = eax; }
    edi += ecx * 4; ecx = 0; /* rep stosd */
    ecx = 0x100;
    eax = 0; /* xor self */
    edi = 0x297AF0;
    { uint32_t _i; for (_i = 0; _i < ecx; _i++) MEM32(edi + _i*4) = eax; }
    edi += ecx * 4; ecx = 0; /* rep stosd */

loc_002154C1: ;
    edi = eax;
    ecx = ebp;
    edi = (uint32_t)((int32_t)edi >> LO8(ecx));
    ecx = MEM32(0x29BF40);
    edi = edi << LO8(ecx);
    edi = (uint32_t)((int32_t)edi * (int32_t)0x10001);
    MEM32(eax * 4 + 0x297EF0) = edi;
    eax++;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0x100) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0x100 (32-bit) */
    if (CMP_L(_fas, _fbs)) goto loc_002154C1; /* jl: less (signed <) */

loc_002154E4: ;
    edx = (uint32_t)((int32_t)edx * (int32_t)0x10001);
    eax = edx;
    ecx = 0x100;
    edi = 0x2982F0;
    { uint32_t _i; for (_i = 0; _i < ecx; _i++) MEM32(edi + _i*4) = eax; }
    edi += ecx * 4; ecx = 0; /* rep stosd */
    ecx = 0x100;
    eax = 0; /* xor self */
    edi = 0x298700;
    { uint32_t _i; for (_i = 0; _i < ecx; _i++) MEM32(edi + _i*4) = eax; }
    edi += ecx * 4; ecx = 0; /* rep stosd */

loc_00215506: ;
    ecx = MEM32(0x29BF60);
    edx = eax;
    edx = (uint32_t)((int32_t)edx >> LO8(ecx));
    ecx = MEM32(0x29BF48);
    edx = edx << LO8(ecx);
    edx = (uint32_t)((int32_t)edx * (int32_t)0x10001);
    MEM32(eax * 4 + 0x298B00) = edx;
    eax++;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0x100) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0x100 (32-bit) */
    if (CMP_L(_fas, _fbs)) goto loc_00215506; /* jl: less (signed <) */

loc_0021552D: ;
    esi = (uint32_t)((int32_t)esi * (int32_t)0x10001);
    eax = esi;
    ecx = 0x100;
    edi = 0x298F00;
    { uint32_t _i; for (_i = 0; _i < ecx; _i++) MEM32(edi + _i*4) = eax; }
    edi += ecx * 4; ecx = 0; /* rep stosd */
    eax = MEM32(esp + 0x14);
    MEM32(0x29BF70) = eax;
    ebx = 0; /* xor self */
    goto loc_00215790;

loc_00215551: ;
    eax = 3;
    MEM32(0x29BF50) = eax;
    MEM32(0x29BF60) = eax;
    eax = 0x25422542;
    MEM32(0x25A7F8) = eax;
    MEM32(0x25A7FC) = eax;
    eax = 0x7FE07FE0;
    ebp = 2;
    MEM32(0x25A800) = eax;
    MEM32(0x25A804) = eax;
    MEM32(0x29BF38) = ebx;
    MEM32(0x29BF58) = ebp;
    MEM32(0x29BF40) = edx;
    MEM32(0x29BF48) = 0xB;
    eax = 0x8410841;
    goto loc_0021524F;

loc_002155A9: ;
    eax = 0x12A112A1;
    ebp = 4;
    MEM32(0x25A7F8) = eax;
    MEM32(0x25A7FC) = eax;
    eax = 0x7FF07FF0;
    MEM32(0x25A800) = eax;
    MEM32(0x25A804) = eax;
    MEM32(0x29BF50) = ebp;
    MEM32(0x29BF38) = ebx;
    MEM32(0x29BF58) = ebp;
    MEM32(0x29BF40) = ebp;
    MEM32(0x29BF60) = ebp;
    MEM32(0x29BF48) = 8;
    eax = 0x1110111;
    goto loc_0021524F;

loc_002155FE: ;
    eax = 0x12A112A1;
    MEM32(0x25A7F8) = eax;
    MEM32(0x25A7FC) = eax;
    eax = 0x7FF07FF0;
    ebp = 2;
    MEM32(0x25A800) = eax;
    MEM32(0x25A804) = eax;
    MEM32(0x29BF50) = ebp;
    MEM32(0x29BF38) = ebx;
    MEM32(0x29BF58) = ebp;
    MEM32(0x29BF40) = 6;
    MEM32(0x29BF60) = 4;
    MEM32(0x29BF48) = 0xC;
    eax = 0x11041104;
    goto loc_0021524F;

loc_0021565B: ;
    eax = 3;
    ebp = eax;
    MEM32(0x29BF60) = eax;
    eax = 0x25422542;
    MEM32(0x25A7F8) = eax;
    MEM32(0x25A7FC) = eax;
    eax = 0x7FE07FE0;
    MEM32(0x25A800) = eax;
    MEM32(0x25A804) = eax;
    MEM32(0x29BF50) = 2;
    MEM32(0x29BF38) = ebx;
    MEM32(0x29BF58) = ebp;
    MEM32(0x29BF40) = 6;
    MEM32(0x29BF48) = 0xB;
    eax = 0x8420842;
    goto loc_0021524F;

loc_002156B9: ;
    eax = MEM32(0x29BF74);
    ebp = 0; /* xor self */
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(1) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 1 (32-bit) */
    MEM32(0x29BF50) = ebx;
    MEM32(0x29BF38) = ebx;
    MEM32(0x29BF58) = ebp;
    MEM32(0x29BF40) = ebx;
    MEM32(0x29BF60) = ebx;
    MEM32(0x29BF48) = ebx;
    if (CMP_EQ(_fa, _fb)) goto loc_00215790; /* je: equal / zero */

loc_002156ED: ;
    ecx = 0; /* xor self */
    esi = 0xFFF6A470u;
    edi = 0xFFF6EFDFu;
    /* nop */

loc_00215700: ;
    eax = edi;
    edx = ((int32_t)eax < 0) ? 0xFFFFFFFF : 0; /* cdq */
    edx = edx & 0x7FFF;
    eax = eax + edx;
    eax = (uint32_t)((int32_t)eax >> 0xF);
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(ebx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp esi, ebx (32-bit) */
    edx = eax * 4 + 0x2966D0;
    MEM32(ecx * 4 + 0x2962D0) = ebx;
    MEM32(ecx * 4 + 0x2966D0) = ecx;
    MEM32(ecx * 4 + 0x296AD0) = 0xFF;
    MEM32(ecx * 4 + 0x295EC0) = edx;
    if (CMP_G(_fas, _fbs)) goto loc_0021573D; /* jg: greater (signed >) */

loc_00215739: ;
    eax = 0; /* xor self */
    goto loc_0021575A;

loc_0021573D: ;
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(0x801543) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp esi, 0x801543 (32-bit) */
    if (CMP_L(_fas, _fbs)) goto loc_0021574C; /* jl: less (signed <) */

loc_00215745: ;
    eax = 0xFF;
    goto loc_0021575A;

loc_0021574C: ;
    eax = esi;
    edx = ((int32_t)eax < 0) ? 0xFFFFFFFF : 0; /* cdq */
    edx = edx & 0x7FFF;
    eax = eax + edx;
    eax = (uint32_t)((int32_t)eax >> 0xF);

loc_0021575A: ;
    edx = eax;
    edx = edx << 8;
    edx = edx | eax;
    edx = edx << 8;
    edx = edx | eax;
    MEM32(ecx * 4 + 0x299B10) = edx;
    esi = esi + 0x95B9;
    ecx++;
    edi = edi + 0x9502;
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(0x8C5D70) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp esi, 0x8C5D70 (32-bit) */
    if (CMP_L(_fas, _fbs)) goto loc_00215700; /* jl: less (signed <) */

loc_00215786: ;
    MEM32(0x29BF74) = 1;

loc_00215790: ;
    _fa = (uint32_t)(MEM32(0x29BF84)) & 0xFFFFFFFFu; _fb = (uint32_t)(ebx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(0x29BF84), ebx (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_00215A37; /* jne: not equal / not zero */

loc_0021579C: ;
    esi = 0x29A338;
    ecx = 0x341000;

loc_002157A6: ;
    eax = ecx;
    edx = ((int32_t)eax < 0) ? 0xFFFFFFFF : 0; /* cdq */
    edx = edx & 0x7FFF;
    eax = eax + edx;
    eax = (uint32_t)((int32_t)eax >> 0xF);
    MEM32(esi) = eax;
    ecx = ecx - 0x6820;
    esi = esi + 4;
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(0xFFCBF000u) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp ecx, 0xFFCBF000u (32-bit) */
    if (CMP_G(_fas, _fbs)) goto loc_002157A6; /* jg: greater (signed >) */

loc_002157C7: ;
    esi = 0x29A738;
    ecx = 0x190D80;

loc_002157D1: ;
    eax = ecx;
    edx = ((int32_t)eax < 0) ? 0xFFFFFFFF : 0; /* cdq */
    edx = edx & 0x7FFF;
    eax = eax + edx;
    eax = (uint32_t)((int32_t)eax >> 0xF);
    MEM32(esi) = eax;
    ecx = ecx - 0x321B;
    esi = esi + 4;
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(0xFFE6F280u) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp ecx, 0xFFE6F280u (32-bit) */
    if (CMP_G(_fas, _fbs)) goto loc_002157D1; /* jg: greater (signed >) */

loc_002157F2: ;
    esi = 0x29AB38;
    ecx = 0xFF99DE80u;
    /* nop */

loc_00215800: ;
    eax = ecx;
    edx = ((int32_t)eax < 0) ? 0xFFFFFFFF : 0; /* cdq */
    edx = edx & 0x7FFF;
    eax = eax + edx;
    eax = (uint32_t)((int32_t)eax >> 0xF);
    MEM32(esi) = eax;
    ecx = ecx + 0xCC43;
    esi = esi + 4;
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(0x662180) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp ecx, 0x662180 (32-bit) */
    if (CMP_L(_fas, _fbs)) goto loc_00215800; /* jl: less (signed <) */

loc_00215821: ;
    esi = 0x299F38;
    ecx = 0xFF7EDC00u;
    goto loc_00215830;

    /* nop */

loc_00215830: ;
    eax = ecx;
    edx = ((int32_t)eax < 0) ? 0xFFFFFFFF : 0; /* cdq */
    edx = edx & 0x7FFF;
    eax = eax + edx;
    eax = (uint32_t)((int32_t)eax >> 0xF);
    MEM32(esi) = eax;
    ecx = ecx + 0x10248;
    esi = esi + 4;
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(0x812400) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp ecx, 0x812400 (32-bit) */
    if (CMP_L(_fas, _fbs)) goto loc_00215830; /* jl: less (signed <) */

loc_00215851: ;
    eax = 0x29B338;
    goto loc_00215860;

    /* nop */
    /* nop */

loc_00215860: ;
    ecx = MEM32(eax + -4096);
    ecx = ecx & 0xFFFF;
    ecx = (uint32_t)((int32_t)ecx * (int32_t)0x10001);
    MEM32(eax) = ecx;
    eax = eax + 4;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0x29B738) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0x29B738 (32-bit) */
    if (CMP_L(_fas, _fbs)) goto loc_00215860; /* jl: less (signed <) */

loc_0021587E: ;
    eax = 0x29B738;

loc_00215883: ;
    edx = MEM32(eax + -4096);
    edx = edx & 0xFFFF;
    edx = (uint32_t)((int32_t)edx * (int32_t)0x10001);
    MEM32(eax) = edx;
    eax = eax + 4;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0x29BB38) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0x29BB38 (32-bit) */
    if (CMP_L(_fas, _fbs)) goto loc_00215883; /* jl: less (signed <) */

loc_002158A1: ;
    eax = 0x29BB38;
    goto loc_002158B0;

    /* nop */
    /* nop */

loc_002158B0: ;
    ecx = MEM32(eax + -4096);
    ecx = ecx & 0xFFFF;
    ecx = (uint32_t)((int32_t)ecx * (int32_t)0x10001);
    MEM32(eax) = ecx;
    eax = eax + 4;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0x29BF38) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0x29BF38 (32-bit) */
    if (CMP_L(_fas, _fbs)) goto loc_002158B0; /* jl: less (signed <) */

loc_002158CE: ;
    eax = 0x29AF38;

loc_002158D3: ;
    edx = MEM32(eax + -4096);
    edx = edx & 0xFFFF;
    edx = (uint32_t)((int32_t)edx * (int32_t)0x10001);
    MEM32(eax) = edx;
    eax = eax + 4;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0x29B338) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0x29B338 (32-bit) */
    if (CMP_L(_fas, _fbs)) goto loc_002158D3; /* jl: less (signed <) */

loc_002158F1: ;
    eax = 0; /* xor self */
    MEM32(0x299310) = eax;
    MEM32(0x299314) = eax;
    MEM32(0x299318) = eax;
    MEM32(0x29931C) = eax;
    MEM32(0x299320) = eax;
    MEM32(0x299324) = eax;
    MEM32(0x299328) = eax;
    MEM32(0x29932C) = eax;
    MEM32(0x299330) = eax;
    MEM32(0x299334) = eax;
    MEM32(0x299338) = eax;
    MEM32(0x29933C) = eax;
    MEM32(0x299340) = eax;
    MEM32(0x299344) = eax;
    MEM32(0x299348) = eax;
    MEM32(0x29934C) = eax;
    MEM32(0x299350) = eax;
    edi = 0x299354;
    esi = 0x95B9;

loc_00215952: ;
    ecx = MEM32(0x29BF60);
    eax = esi;
    edx = ((int32_t)eax < 0) ? 0xFFFFFFFF : 0; /* cdq */
    edx = edx & 0x7FFF;
    eax = eax + edx;
    eax = (uint32_t)((int32_t)eax >> 0xF);
    edx = eax;
    edx = (uint32_t)((int32_t)edx >> LO8(ecx));
    ecx = MEM32(0x29BF48);
    ebx = eax;
    esi = esi + 0x95B9;
    edx = edx << LO8(ecx);
    ecx = ebp;
    ebx = (uint32_t)((int32_t)ebx >> LO8(ecx));
    ecx = MEM32(0x29BF40);
    edi = edi + 4;
    ebx = ebx << LO8(ecx);
    ecx = MEM32(0x29BF50);
    eax = (uint32_t)((int32_t)eax >> LO8(ecx));
    edx = edx | ebx;
    edx = edx | eax;
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(0x7F7F8A) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp esi, 0x7F7F8A (32-bit) */
    MEM32(edi + -4) = edx;
    if (CMP_LE(_fas, _fbs)) goto loc_00215952; /* jle: less or equal (signed <=) */

loc_002159A0: ;
    eax = 0xFF;
    MEM32(0x2996BC) = eax;
    MEM32(0x2996C0) = eax;
    MEM32(0x2996C4) = eax;
    MEM32(0x2996C8) = eax;
    MEM32(0x2996CC) = eax;
    MEM32(0x2996D0) = eax;
    MEM32(0x2996D4) = eax;
    MEM32(0x2996D8) = eax;
    MEM32(0x2996DC) = eax;
    MEM32(0x2996E0) = eax;
    MEM32(0x2996E4) = eax;
    MEM32(0x2996E8) = eax;
    MEM32(0x2996EC) = eax;
    MEM32(0x2996F0) = eax;
    MEM32(0x2996F4) = eax;
    MEM32(0x2996F8) = eax;
    MEM32(0x2996FC) = eax;
    MEM32(0x299700) = eax;
    MEM32(0x299704) = eax;
    MEM32(0x299708) = eax;
    MEM32(0x29970C) = eax;
    eax = 0; /* xor self */

loc_00215A10: ;
    ecx = MEM32(eax + 0x299310);
    edx = ecx;
    edx = edx << 0x10;
    edx = edx | ecx;
    MEM32(eax + 0x299710) = edx;
    eax = eax + 4;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0x400) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0x400 (32-bit) */
    if (CMP_L(_fas, _fbs)) goto loc_00215A10; /* jl: less (signed <) */

loc_00215A2D: ;
    MEM32(0x29BF84) = 1;

loc_00215A37: ;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebp);
    POP32(esp, ebx);
    esp += 8; return; /* ret 4 */

}

/**
 * sub_00215A60
 * Original: 0x00215A60 - 0x00215D8B (811 bytes, 240 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00215A60(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_00215A60: ;
    esp = esp - 0x120;
    PUSH32(esp, ebx);
    PUSH32(esp, ebp);
    PUSH32(esp, esi);
    ebx = eax;
    PUSH32(esp, edi);
    MEM32(esp + 0x14) = ebx;
    ecx = esp + 0x30;
    MEM32(esp + 0x18) = 8;
    /* nop */

loc_00215A80: ;
    SET_LO16(edi, MEM16(ebx + 0x40));
    eax = 0; /* xor self */
    SET_LO16(eax, MEM16(ebx + 0x20));
    esi = 0; /* xor self */
    SET_LO16(esi, MEM16(ebx + 0x10));
    SET_LO16(ebp, MEM16(ebx + 0x60));
    MEM32(esp + 0x1C) = eax;
    esi = esi | eax;
    eax = 0; /* xor self */
    SET_LO16(eax, MEM16(ebx + 0x30));
    esi = esi | eax;
    eax = 0; /* xor self */
    SET_LO16(eax, MEM16(ebx + 0x50));
    esi = esi | edi;
    esi = esi | eax;
    eax = 0; /* xor self */
    SET_LO16(eax, MEM16(ebx + 0x70));
    esi = esi | ebp;
    esi = esi | eax;
    _fa = (uint32_t)(LO16(esi)) & 0xFFFFu; _fb = (uint32_t)(LO16(esi)) & 0xFFFFu;
    _fas = (int32_t)(int16_t)(_fa); _fbs = (int32_t)(int16_t)(_fb); /* test LO16(esi), LO16(esi) (16-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_00215AE9; /* jne: not equal / not zero */

loc_00215ABB: ;
    eax = (uint32_t)(int32_t)SMEM16(ebx);
    eax = (uint32_t)((int32_t)eax * (int32_t)MEM32(edx));
    eax = (uint32_t)((int32_t)eax >> 0xB);
    MEM32(ecx) = eax;
    MEM32(ecx + 0x20) = eax;
    MEM32(ecx + 0x40) = eax;
    MEM32(ecx + 0x80) = eax;
    MEM32(ecx + 0xA0) = eax;
    MEM32(ecx + 0xC0) = eax;
    MEM32(ecx + 0xE0) = eax;
    goto loc_00215C2F;

loc_00215AE9: ;
    esi = (uint32_t)(int32_t)SMEM16(ebx);
    esi = (uint32_t)((int32_t)esi * (int32_t)MEM32(edx));
    eax = (uint32_t)(int32_t)SMEM16(esp + 0x1C);
    eax = (uint32_t)((int32_t)eax * (int32_t)MEM32(edx + 0x40));
    ebx = SX16(LO16(ebp)); /* MOVSX 0x00215AF8: movsx ebx, bp */
    ebx = (uint32_t)((int32_t)ebx * (int32_t)MEM32(edx + 0xC0));
    edi = SX16(LO16(edi));
    edi = (uint32_t)((int32_t)edi * (int32_t)MEM32(edx + 0x80));
    eax = (uint32_t)((int32_t)eax >> 0xB);
    edi = (uint32_t)((int32_t)edi >> 0xB);
    esi = (uint32_t)((int32_t)esi >> 0xB);
    ebp = edi + esi;
    esi = esi - edi;
    ebx = (uint32_t)((int32_t)ebx >> 0xB);
    edi = ebx + eax;
    eax = eax - ebx;
    ebx = edi + ebp;
    eax = (uint32_t)((int32_t)eax * (int32_t)0xB50);
    ebp = ebp - edi;
    eax = (uint32_t)((int32_t)eax >> 0xB);
    eax = eax - edi;
    edi = eax + esi;
    esi = esi - eax;
    MEM32(esp + 0x1C) = ebp;
    MEM32(esp + 0x2C) = edi;
    MEM32(esp + 0x20) = esi;
    MEM32(esp + 0x24) = ebx;
    ebx = MEM32(esp + 0x14);
    ebp = (uint32_t)(int32_t)SMEM16(ebx + 0x70);
    ebp = (uint32_t)((int32_t)ebp * (int32_t)MEM32(edx + 0xE0));
    edi = (uint32_t)(int32_t)SMEM16(ebx + 0x30);
    edi = (uint32_t)((int32_t)edi * (int32_t)MEM32(edx + 0x60));
    esi = (uint32_t)(int32_t)SMEM16(ebx + 0x50);
    esi = (uint32_t)((int32_t)esi * (int32_t)MEM32(edx + 0xA0));
    eax = (uint32_t)(int32_t)SMEM16(ebx + 0x10);
    eax = (uint32_t)((int32_t)eax * (int32_t)MEM32(edx + 0x20));
    ebp = (uint32_t)((int32_t)ebp >> 0xB);
    MEM32(esp + 0x10) = ebp;
    edi = (uint32_t)((int32_t)edi >> 0xB);
    esi = (uint32_t)((int32_t)esi >> 0xB);
    ebp = esi + edi;
    MEM32(esp + 0x14) = ebp;
    ebp = MEM32(esp + 0x10);
    eax = (uint32_t)((int32_t)eax >> 0xB);
    esi = esi - edi;
    edi = eax + ebp;
    eax = eax - ebp;
    ebp = MEM32(esp + 0x14);
    ebp = ebp + edi;
    edi = edi - MEM32(esp + 0x14);
    MEM32(esp + 0x10) = ebp;
    ebp = eax + esi;
    esi = (uint32_t)((int32_t)esi * (int32_t)0xFFFFEB18u);
    eax = (uint32_t)((int32_t)eax * (int32_t)0x8A9);
    ebp = (uint32_t)((int32_t)ebp * (int32_t)0xEC8);
    edi = (uint32_t)((int32_t)edi * (int32_t)0xB50);
    ebp = (uint32_t)((int32_t)ebp >> 0xB);
    MEM32(esp + 0x28) = ebp;
    ebp = MEM32(esp + 0x10);
    esi = (uint32_t)((int32_t)esi >> 0xB);
    esi = esi - ebp;
    ebp = MEM32(esp + 0x28);
    esi = esi + ebp;
    eax = (uint32_t)((int32_t)eax >> 0xB);
    eax = eax - ebp;
    ebp = MEM32(esp + 0x10);
    edi = (uint32_t)((int32_t)edi >> 0xB);
    edi = edi - esi;
    eax = eax + edi;
    MEM32(esp + 0x28) = eax;
    eax = MEM32(esp + 0x24);
    ebp = ebp + eax;
    MEM32(ecx) = ebp;
    eax = eax - MEM32(esp + 0x10);
    MEM32(ecx + 0xE0) = eax;
    eax = MEM32(esp + 0x2C);
    ebp = esi + eax;
    eax = eax - esi;
    MEM32(ecx + 0x20) = ebp;
    MEM32(ecx + 0xC0) = eax;
    eax = MEM32(esp + 0x20);
    esi = edi + eax;
    eax = eax - edi;
    MEM32(ecx + 0xA0) = eax;
    eax = MEM32(esp + 0x1C);
    MEM32(ecx + 0x40) = esi;
    esi = MEM32(esp + 0x28);
    edi = esi + eax;
    MEM32(ecx + 0x80) = edi;
    eax = eax - esi;

loc_00215C2F: ;
    MEM32(ecx + 0x60) = eax;
    eax = MEM32(esp + 0x18);
    ebx = ebx + 2;
    edx = edx + 4;
    ecx = ecx + 4;
    eax--;
    MEM32(esp + 0x14) = ebx;
    MEM32(esp + 0x18) = eax;
    if ((eax != 0)) goto loc_00215A80; /* jne: not equal / not zero */

loc_00215C4E: ;
    ecx = MEM32(esp + 0x134);
    ecx++;
    eax = esp + 0x48;
    MEM32(esp + 0x18) = 8;

loc_00215C62: ;
    edi = MEM32(eax + -8);
    edx = MEM32(eax + -24);
    esi = edx + edi;
    edx = edx - edi;
    ebp = MEM32(eax);
    edi = edx;
    edx = MEM32(eax + -16);
    ebx = edx + ebp;
    edx = edx - ebp;
    edx = (uint32_t)((int32_t)edx * (int32_t)0xB50);
    edx = (uint32_t)((int32_t)edx >> 0xB);
    edx = edx - ebx;
    ebp = ebx + esi;
    esi = esi - ebx;
    ebx = MEM32(eax + 4);
    MEM32(esp + 0x1C) = esi;
    esi = edx + edi;
    edi = edi - edx;
    edx = MEM32(eax + -12);
    MEM32(esp + 0x2C) = esi;
    esi = MEM32(eax + -4);
    MEM32(esp + 0x20) = edi;
    edi = MEM32(eax + -20);
    MEM32(esp + 0x24) = ebp;
    ebp = edx + esi;
    esi = esi - edx;
    edx = edi + ebx;
    edi = edi - ebx;
    ebx = edx + ebp;
    MEM32(esp + 0x10) = ebx;
    ebx = edi + esi;
    esi = (uint32_t)((int32_t)esi * (int32_t)0xFFFFEB18u);
    edi = (uint32_t)((int32_t)edi * (int32_t)0x8A9);
    esi = (uint32_t)((int32_t)esi >> 0xB);
    ebx = (uint32_t)((int32_t)ebx * (int32_t)0xEC8);
    MEM32(esp + 0x14) = ebp;
    esi = esi - MEM32(esp + 0x10);
    edx = edx - MEM32(esp + 0x14);
    edx = (uint32_t)((int32_t)edx * (int32_t)0xB50);
    edx = (uint32_t)((int32_t)edx >> 0xB);
    ebx = (uint32_t)((int32_t)ebx >> 0xB);
    esi = esi + ebx;
    edx = edx - esi;
    ebp = edx;
    edx = MEM32(esp + 0x24);
    edi = (uint32_t)((int32_t)edi >> 0xB);
    edi = edi - ebx;
    ebx = MEM32(esp + 0x10);
    ebx = ebx + edx + 0x7F;
    ebx = (uint32_t)((int32_t)ebx >> 8);
    MEM8(ecx + -1) = LO8(ebx);
    edx = edx - MEM32(esp + 0x10);
    edx = edx + 0x7F;
    edx = (uint32_t)((int32_t)edx >> 8);
    MEM8(ecx + 6) = LO8(edx);
    edx = MEM32(esp + 0x2C);
    ebx = esi + edx + 0x7F;
    edx = edx - esi;
    esi = MEM32(esp + 0x20);
    edx = edx + 0x7F;
    edx = (uint32_t)((int32_t)edx >> 8);
    MEM8(ecx + 5) = LO8(edx);
    edx = esi + ebp + 0x7F;
    edx = (uint32_t)((int32_t)edx >> 8);
    MEM8(ecx + 1) = LO8(edx);
    edx = esi;
    esi = MEM32(esp + 0x1C);
    edx = edx - ebp;
    edx = edx + 0x7F;
    edx = (uint32_t)((int32_t)edx >> 8);
    edi = edi + ebp;
    MEM8(ecx + 4) = LO8(edx);
    ebx = (uint32_t)((int32_t)ebx >> 8);
    edx = edi + esi + 0x7F;
    edx = (uint32_t)((int32_t)edx >> 8);
    MEM8(ecx + 3) = LO8(edx);
    MEM8(ecx) = LO8(ebx);
    edx = esi;
    esi = MEM32(esp + 0x138);
    edx = edx - edi;
    edx = edx + 0x7F;
    edx = (uint32_t)((int32_t)edx >> 8);
    MEM8(ecx + 2) = LO8(edx);
    edx = MEM32(esp + 0x18);
    eax = eax + 0x20;
    ecx = ecx + esi;
    edx--;
    MEM32(esp + 0x18) = edx;
    if ((edx != 0)) goto loc_00215C62; /* jne: not equal / not zero */

loc_00215D80: ;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebp);
    POP32(esp, ebx);
    esp = esp + 0x120;
    esp += 4; return; /* ret */

}

/**
 * sub_00215D90
 * Original: 0x00215D90 - 0x0021612C (924 bytes, 281 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00215D90(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_00215D90: ;
    esp = esp - 0x128;
    PUSH32(esp, ebx);
    ebx = ecx;
    ecx = MEM32(esp + 0x130);
    PUSH32(esp, ebp);
    ecx = ecx + eax;
    PUSH32(esp, esi);
    eax = eax + eax;
    MEM32(esp + 0x28) = ecx;
    PUSH32(esp, edi);
    MEM32(esp + 0x10) = ebx;
    MEM32(esp + 0x30) = eax;
    ecx = esp + 0x38;
    MEM32(esp + 0x1C) = 8;
    /* nop */

loc_00215DC0: ;
    SET_LO16(edi, MEM16(ebx + 0x40));
    eax = 0; /* xor self */
    SET_LO16(eax, MEM16(ebx + 0x20));
    esi = 0; /* xor self */
    SET_LO16(esi, MEM16(ebx + 0x10));
    SET_LO16(ebp, MEM16(ebx + 0x60));
    MEM32(esp + 0x18) = eax;
    esi = esi | eax;
    eax = 0; /* xor self */
    SET_LO16(eax, MEM16(ebx + 0x30));
    esi = esi | eax;
    eax = 0; /* xor self */
    SET_LO16(eax, MEM16(ebx + 0x50));
    esi = esi | edi;
    esi = esi | eax;
    eax = 0; /* xor self */
    SET_LO16(eax, MEM16(ebx + 0x70));
    esi = esi | ebp;
    esi = esi | eax;
    _fa = (uint32_t)(LO16(esi)) & 0xFFFFu; _fb = (uint32_t)(LO16(esi)) & 0xFFFFu;
    _fas = (int32_t)(int16_t)(_fa); _fbs = (int32_t)(int16_t)(_fb); /* test LO16(esi), LO16(esi) (16-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_00215E29; /* jne: not equal / not zero */

loc_00215DFB: ;
    eax = (uint32_t)(int32_t)SMEM16(ebx);
    eax = (uint32_t)((int32_t)eax * (int32_t)MEM32(edx));
    eax = (uint32_t)((int32_t)eax >> 0xB);
    MEM32(ecx) = eax;
    MEM32(ecx + 0x20) = eax;
    MEM32(ecx + 0x40) = eax;
    MEM32(ecx + 0x80) = eax;
    MEM32(ecx + 0xA0) = eax;
    MEM32(ecx + 0xC0) = eax;
    MEM32(ecx + 0xE0) = eax;
    goto loc_00215F6F;

loc_00215E29: ;
    esi = (uint32_t)(int32_t)SMEM16(ebx);
    esi = (uint32_t)((int32_t)esi * (int32_t)MEM32(edx));
    eax = (uint32_t)(int32_t)SMEM16(esp + 0x18);
    eax = (uint32_t)((int32_t)eax * (int32_t)MEM32(edx + 0x40));
    ebx = SX16(LO16(ebp)); /* MOVSX 0x00215E38: movsx ebx, bp */
    ebx = (uint32_t)((int32_t)ebx * (int32_t)MEM32(edx + 0xC0));
    edi = SX16(LO16(edi));
    edi = (uint32_t)((int32_t)edi * (int32_t)MEM32(edx + 0x80));
    eax = (uint32_t)((int32_t)eax >> 0xB);
    edi = (uint32_t)((int32_t)edi >> 0xB);
    esi = (uint32_t)((int32_t)esi >> 0xB);
    ebp = edi + esi;
    esi = esi - edi;
    ebx = (uint32_t)((int32_t)ebx >> 0xB);
    edi = ebx + eax;
    eax = eax - ebx;
    ebx = edi + ebp;
    eax = (uint32_t)((int32_t)eax * (int32_t)0xB50);
    ebp = ebp - edi;
    eax = (uint32_t)((int32_t)eax >> 0xB);
    eax = eax - edi;
    edi = eax + esi;
    esi = esi - eax;
    MEM32(esp + 0x28) = ebp;
    MEM32(esp + 0x20) = edi;
    MEM32(esp + 0x24) = esi;
    MEM32(esp + 0x18) = ebx;
    ebx = MEM32(esp + 0x10);
    ebp = (uint32_t)(int32_t)SMEM16(ebx + 0x70);
    ebp = (uint32_t)((int32_t)ebp * (int32_t)MEM32(edx + 0xE0));
    edi = (uint32_t)(int32_t)SMEM16(ebx + 0x30);
    edi = (uint32_t)((int32_t)edi * (int32_t)MEM32(edx + 0x60));
    esi = (uint32_t)(int32_t)SMEM16(ebx + 0x50);
    esi = (uint32_t)((int32_t)esi * (int32_t)MEM32(edx + 0xA0));
    eax = (uint32_t)(int32_t)SMEM16(ebx + 0x10);
    eax = (uint32_t)((int32_t)eax * (int32_t)MEM32(edx + 0x20));
    ebp = (uint32_t)((int32_t)ebp >> 0xB);
    MEM32(esp + 0x14) = ebp;
    edi = (uint32_t)((int32_t)edi >> 0xB);
    esi = (uint32_t)((int32_t)esi >> 0xB);
    ebp = esi + edi;
    MEM32(esp + 0x10) = ebp;
    ebp = MEM32(esp + 0x14);
    eax = (uint32_t)((int32_t)eax >> 0xB);
    esi = esi - edi;
    edi = eax + ebp;
    eax = eax - ebp;
    ebp = MEM32(esp + 0x10);
    ebp = ebp + edi;
    edi = edi - MEM32(esp + 0x10);
    MEM32(esp + 0x14) = ebp;
    ebp = eax + esi;
    esi = (uint32_t)((int32_t)esi * (int32_t)0xFFFFEB18u);
    eax = (uint32_t)((int32_t)eax * (int32_t)0x8A9);
    ebp = (uint32_t)((int32_t)ebp * (int32_t)0xEC8);
    edi = (uint32_t)((int32_t)edi * (int32_t)0xB50);
    ebp = (uint32_t)((int32_t)ebp >> 0xB);
    MEM32(esp + 0x34) = ebp;
    ebp = MEM32(esp + 0x14);
    esi = (uint32_t)((int32_t)esi >> 0xB);
    esi = esi - ebp;
    ebp = MEM32(esp + 0x34);
    esi = esi + ebp;
    eax = (uint32_t)((int32_t)eax >> 0xB);
    eax = eax - ebp;
    ebp = MEM32(esp + 0x14);
    edi = (uint32_t)((int32_t)edi >> 0xB);
    edi = edi - esi;
    eax = eax + edi;
    MEM32(esp + 0x10) = eax;
    eax = MEM32(esp + 0x18);
    ebp = ebp + eax;
    MEM32(ecx) = ebp;
    eax = eax - MEM32(esp + 0x14);
    MEM32(ecx + 0xE0) = eax;
    eax = MEM32(esp + 0x20);
    ebp = esi + eax;
    eax = eax - esi;
    MEM32(ecx + 0x20) = ebp;
    MEM32(ecx + 0xC0) = eax;
    eax = MEM32(esp + 0x24);
    esi = edi + eax;
    eax = eax - edi;
    MEM32(ecx + 0xA0) = eax;
    eax = MEM32(esp + 0x28);
    MEM32(ecx + 0x40) = esi;
    esi = MEM32(esp + 0x10);
    edi = esi + eax;
    MEM32(ecx + 0x80) = edi;
    eax = eax - esi;

loc_00215F6F: ;
    MEM32(ecx + 0x60) = eax;
    eax = MEM32(esp + 0x1C);
    ebx = ebx + 2;
    edx = edx + 4;
    ecx = ecx + 4;
    eax--;
    MEM32(esp + 0x10) = ebx;
    MEM32(esp + 0x1C) = eax;
    if ((eax != 0)) goto loc_00215DC0; /* jne: not equal / not zero */

loc_00215F8E: ;
    ecx = MEM32(esp + 0x13C);
    ecx = ecx + 8;
    eax = esp + 0x50;
    MEM32(esp + 0x1C) = ecx;
    MEM32(esp + 0x14) = 8;

loc_00215FA8: ;
    esi = MEM32(eax + -8);
    ecx = MEM32(eax + -24);
    ebx = MEM32(eax);
    edx = ecx + esi;
    ecx = ecx - esi;
    esi = ecx;
    ecx = MEM32(eax + -16);
    edi = ecx + ebx;
    ecx = ecx - ebx;
    ebx = edi + edx;
    ecx = (uint32_t)((int32_t)ecx * (int32_t)0xB50);
    edx = edx - edi;
    MEM32(esp + 0x28) = edx;
    ecx = (uint32_t)((int32_t)ecx >> 0xB);
    ecx = ecx - edi;
    edi = MEM32(eax + 4);
    edx = ecx + esi;
    MEM32(esp + 0x20) = edx;
    edx = MEM32(eax + -4);
    esi = esi - ecx;
    ecx = MEM32(eax + -12);
    MEM32(esp + 0x24) = esi;
    esi = MEM32(eax + -20);
    MEM32(esp + 0x18) = ebx;
    ebx = ecx + edx;
    edx = edx - ecx;
    ecx = esi + edi;
    esi = esi - edi;
    edi = esi + edx;
    edx = (uint32_t)((int32_t)edx * (int32_t)0xFFFFEB18u);
    esi = (uint32_t)((int32_t)esi * (int32_t)0x8A9);
    edx = (uint32_t)((int32_t)edx >> 0xB);
    edi = (uint32_t)((int32_t)edi * (int32_t)0xEC8);
    MEM32(esp + 0x10) = ebx;
    ebx = ebx + ecx;
    edx = edx - ebx;
    edi = (uint32_t)((int32_t)edi >> 0xB);
    edx = edx + edi;
    ebp = edx;
    ecx = ecx - MEM32(esp + 0x10);
    edx = MEM32(esp + 0x20);
    ecx = (uint32_t)((int32_t)ecx * (int32_t)0xB50);
    edx = edx + ebp + 0x7F;
    edx = (uint32_t)((int32_t)edx >> 8);
    esi = (uint32_t)((int32_t)esi >> 0xB);
    esi = esi - edi;
    edi = ZX8(LO8(edx));
    ecx = (uint32_t)((int32_t)ecx >> 0xB);
    ecx = ecx - ebp;
    esi = esi + ecx;
    MEM32(esp + 0x10) = esi;
    esi = MEM32(esp + 0x18);
    edx = ebx + esi + 0x7F;
    edx = (uint32_t)((int32_t)edx >> 8);
    edx = ZX8(LO8(edx));
    edi = edi << 0x10;
    edi = edi | edx;
    edx = esi;
    edx = edx - ebx;
    edx = edx + 0x7F;
    edx = (uint32_t)((int32_t)edx >> 8);
    ebx = ZX8(LO8(edx));
    edx = MEM32(esp + 0x20);
    edx = edx - ebp;
    ebp = MEM32(esp + 0x28);
    edx = edx + 0x7F;
    edx = (uint32_t)((int32_t)edx >> 8);
    edx = ZX8(LO8(edx));
    ebx = ebx << 0x10;
    ebx = ebx | edx;
    edx = MEM32(esp + 0x24);
    edx = edx - ecx;
    edx = edx + 0x7F;
    edx = (uint32_t)((int32_t)edx >> 8);
    esi = ZX8(LO8(edx));
    edx = MEM32(esp + 0x10);
    edx = edx + ebp + 0x7F;
    esi = esi << 0x10;
    edx = (uint32_t)((int32_t)edx >> 8);
    edx = ZX8(LO8(edx));
    esi = esi | edx;
    edx = ebp;
    edx = edx - MEM32(esp + 0x10);
    edx = edx + 0x7F;
    edx = (uint32_t)((int32_t)edx >> 8);
    ebp = ZX8(LO8(edx));
    edx = MEM32(esp + 0x24);
    ecx = ecx + edx + 0x7F;
    ecx = (uint32_t)((int32_t)ecx >> 8);
    edx = ZX8(LO8(ecx));
    ebp = ebp << 0x10;
    ebp = ebp | edx;
    ecx = edi;
    ecx = ecx << 8;
    edi = edi | ecx;
    edx = ebx;
    edx = edx << 8;
    ebx = ebx | edx;
    ecx = esi;
    ecx = ecx << 8;
    esi = esi | ecx;
    ecx = MEM32(esp + 0x1C);
    edx = ebp;
    edx = edx << 8;
    MEM32(ecx) = esi;
    ebp = ebp | edx;
    edx = MEM32(esp + 0x2C);
    MEM32(ecx + -8) = edi;
    MEM32(ecx + -4) = ebp;
    MEM32(ecx + 4) = ebx;
    MEM32(edx + 8) = esi;
    esi = MEM32(esp + 0x30);
    ecx = ecx + esi;
    MEM32(esp + 0x1C) = ecx;
    ecx = MEM32(esp + 0x14);
    MEM32(edx) = edi;
    MEM32(edx + 4) = ebp;
    MEM32(edx + 0xC) = ebx;
    edx = edx + esi;
    eax = eax + 0x20;
    ecx--;
    MEM32(esp + 0x2C) = edx;
    MEM32(esp + 0x14) = ecx;
    if ((ecx != 0)) goto loc_00215FA8; /* jne: not equal / not zero */

loc_00216121: ;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebp);
    POP32(esp, ebx);
    esp = esp + 0x128;
    esp += 4; return; /* ret */

}

/**
 * sub_00216130
 * Original: 0x00216130 - 0x00216156 (38 bytes, 11 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00216130(void)
{

loc_00216130: ;
    eax = MEM32(esp + 8);
    edx = MEM32(esp + 0x10);
    ecx = MEM32(esp + 4);
    PUSH32(esp, eax);
    eax = MEM32(esp + 0x10);
    edx = edx << 8;
    edx = edx + 0x23B280;
    PUSH32(esp, ecx);
    PUSH32(esp, 0x00216150u); sub_00215A60(); /* call 0x00215A60 */

loc_00216150: ;
    esp = esp + 8;
    esp += 20; return; /* ret 16 */

}

/**
 * sub_00216160
 * Original: 0x00216160 - 0x00216183 (35 bytes, 10 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00216160(void)
{

loc_00216160: ;
    edx = MEM32(esp + 0x10);
    eax = MEM32(esp + 4);
    ecx = MEM32(esp + 0xC);
    edx = edx << 8;
    PUSH32(esp, eax);
    eax = MEM32(esp + 0xC);
    edx = edx + 0x23B280;
    PUSH32(esp, 0x0021617Fu); sub_00215D90(); /* call 0x00215D90 */

loc_0021617F: ;
    POP32(esp, ecx);
    esp += 20; return; /* ret 16 */

}

/**
 * sub_00216190
 * Original: 0x00216190 - 0x00216520 (912 bytes, 269 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00216190(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_00216190: ;
    esp = esp - 0x124;
    edx = MEM32(esp + 0x134);
    PUSH32(esp, ebx);
    ebx = MEM32(esp + 0x134);
    PUSH32(esp, ebp);
    PUSH32(esp, esi);
    edx = edx << 8;
    PUSH32(esp, edi);
    edx = edx + 0x23C2A0;
    MEM32(esp + 0x10) = ebx;
    ecx = esp + 0x34;
    MEM32(esp + 0x1C) = 8;

loc_002161C1: ;
    SET_LO16(edi, MEM16(ebx + 0x40));
    eax = 0; /* xor self */
    SET_LO16(eax, MEM16(ebx + 0x20));
    esi = 0; /* xor self */
    SET_LO16(esi, MEM16(ebx + 0x10));
    SET_LO16(ebp, MEM16(ebx + 0x60));
    MEM32(esp + 0x24) = eax;
    esi = esi | eax;
    eax = 0; /* xor self */
    SET_LO16(eax, MEM16(ebx + 0x30));
    esi = esi | eax;
    eax = 0; /* xor self */
    SET_LO16(eax, MEM16(ebx + 0x50));
    esi = esi | edi;
    esi = esi | eax;
    eax = 0; /* xor self */
    SET_LO16(eax, MEM16(ebx + 0x70));
    esi = esi | ebp;
    esi = esi | eax;
    _fa = (uint32_t)(LO16(esi)) & 0xFFFFu; _fb = (uint32_t)(LO16(esi)) & 0xFFFFu;
    _fas = (int32_t)(int16_t)(_fa); _fbs = (int32_t)(int16_t)(_fb); /* test LO16(esi), LO16(esi) (16-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_0021622A; /* jne: not equal / not zero */

loc_002161FC: ;
    eax = (uint32_t)(int32_t)SMEM16(ebx);
    eax = (uint32_t)((int32_t)eax * (int32_t)MEM32(edx));
    eax = (uint32_t)((int32_t)eax >> 0xB);
    MEM32(ecx) = eax;
    MEM32(ecx + 0x20) = eax;
    MEM32(ecx + 0x40) = eax;
    MEM32(ecx + 0x80) = eax;
    MEM32(ecx + 0xA0) = eax;
    MEM32(ecx + 0xC0) = eax;
    MEM32(ecx + 0xE0) = eax;
    goto loc_00216370;

loc_0021622A: ;
    esi = (uint32_t)(int32_t)SMEM16(ebx);
    esi = (uint32_t)((int32_t)esi * (int32_t)MEM32(edx));
    eax = (uint32_t)(int32_t)SMEM16(esp + 0x24);
    eax = (uint32_t)((int32_t)eax * (int32_t)MEM32(edx + 0x40));
    ebx = SX16(LO16(ebp)); /* MOVSX 0x00216239: movsx ebx, bp */
    ebx = (uint32_t)((int32_t)ebx * (int32_t)MEM32(edx + 0xC0));
    edi = SX16(LO16(edi));
    edi = (uint32_t)((int32_t)edi * (int32_t)MEM32(edx + 0x80));
    eax = (uint32_t)((int32_t)eax >> 0xB);
    edi = (uint32_t)((int32_t)edi >> 0xB);
    esi = (uint32_t)((int32_t)esi >> 0xB);
    ebp = edi + esi;
    esi = esi - edi;
    ebx = (uint32_t)((int32_t)ebx >> 0xB);
    edi = ebx + eax;
    eax = eax - ebx;
    ebx = edi + ebp;
    eax = (uint32_t)((int32_t)eax * (int32_t)0xB50);
    ebp = ebp - edi;
    eax = (uint32_t)((int32_t)eax >> 0xB);
    eax = eax - edi;
    edi = eax + esi;
    esi = esi - eax;
    MEM32(esp + 0x2C) = ebp;
    MEM32(esp + 0x28) = edi;
    MEM32(esp + 0x30) = esi;
    MEM32(esp + 0x20) = ebx;
    ebx = MEM32(esp + 0x10);
    ebp = (uint32_t)(int32_t)SMEM16(ebx + 0x70);
    ebp = (uint32_t)((int32_t)ebp * (int32_t)MEM32(edx + 0xE0));
    edi = (uint32_t)(int32_t)SMEM16(ebx + 0x30);
    edi = (uint32_t)((int32_t)edi * (int32_t)MEM32(edx + 0x60));
    esi = (uint32_t)(int32_t)SMEM16(ebx + 0x50);
    esi = (uint32_t)((int32_t)esi * (int32_t)MEM32(edx + 0xA0));
    eax = (uint32_t)(int32_t)SMEM16(ebx + 0x10);
    eax = (uint32_t)((int32_t)eax * (int32_t)MEM32(edx + 0x20));
    ebp = (uint32_t)((int32_t)ebp >> 0xB);
    MEM32(esp + 0x14) = ebp;
    edi = (uint32_t)((int32_t)edi >> 0xB);
    esi = (uint32_t)((int32_t)esi >> 0xB);
    ebp = esi + edi;
    MEM32(esp + 0x18) = ebp;
    ebp = MEM32(esp + 0x14);
    eax = (uint32_t)((int32_t)eax >> 0xB);
    esi = esi - edi;
    edi = eax + ebp;
    eax = eax - ebp;
    ebp = MEM32(esp + 0x18);
    ebp = ebp + edi;
    edi = edi - MEM32(esp + 0x18);
    MEM32(esp + 0x14) = ebp;
    ebp = eax + esi;
    esi = (uint32_t)((int32_t)esi * (int32_t)0xFFFFEB18u);
    eax = (uint32_t)((int32_t)eax * (int32_t)0x8A9);
    ebp = (uint32_t)((int32_t)ebp * (int32_t)0xEC8);
    edi = (uint32_t)((int32_t)edi * (int32_t)0xB50);
    ebp = (uint32_t)((int32_t)ebp >> 0xB);
    MEM32(esp + 0x10) = ebp;
    ebp = MEM32(esp + 0x14);
    esi = (uint32_t)((int32_t)esi >> 0xB);
    esi = esi - ebp;
    ebp = MEM32(esp + 0x10);
    esi = esi + ebp;
    eax = (uint32_t)((int32_t)eax >> 0xB);
    eax = eax - ebp;
    ebp = MEM32(esp + 0x14);
    edi = (uint32_t)((int32_t)edi >> 0xB);
    edi = edi - esi;
    eax = eax + edi;
    MEM32(esp + 0x10) = eax;
    eax = MEM32(esp + 0x20);
    ebp = ebp + eax;
    MEM32(ecx) = ebp;
    eax = eax - MEM32(esp + 0x14);
    MEM32(ecx + 0xE0) = eax;
    eax = MEM32(esp + 0x28);
    ebp = esi + eax;
    eax = eax - esi;
    MEM32(ecx + 0x20) = ebp;
    MEM32(ecx + 0xC0) = eax;
    eax = MEM32(esp + 0x30);
    esi = edi + eax;
    eax = eax - edi;
    MEM32(ecx + 0xA0) = eax;
    eax = MEM32(esp + 0x2C);
    MEM32(ecx + 0x40) = esi;
    esi = MEM32(esp + 0x10);
    edi = esi + eax;
    MEM32(ecx + 0x80) = edi;
    eax = eax - esi;

loc_00216370: ;
    MEM32(ecx + 0x60) = eax;
    eax = MEM32(esp + 0x1C);
    ebx = ebx + 2;
    edx = edx + 4;
    ecx = ecx + 4;
    eax--;
    MEM32(esp + 0x10) = ebx;
    MEM32(esp + 0x1C) = eax;
    if ((eax != 0)) goto loc_002161C1; /* jne: not equal / not zero */

loc_0021638F: ;
    ecx = MEM32(esp + 0x138);
    esi = MEM32(esp + 0x148);
    ecx++;
    esi++;
    eax = esp + 0x4C;
    MEM32(esp + 0x24) = 8;
    goto loc_002163B0;

    /* nop */

loc_002163B0: ;
    ebx = MEM32(eax + -8);
    edx = MEM32(eax + -24);
    edi = edx + ebx;
    edx = edx - ebx;
    ebp = MEM32(eax);
    ebx = edx;
    edx = MEM32(eax + -16);
    ebp = ebp + edx;
    MEM32(esp + 0x1C) = ebp;
    edx = edx - MEM32(eax);
    ebp = MEM32(esp + 0x1C);
    edx = (uint32_t)((int32_t)edx * (int32_t)0xB50);
    edx = (uint32_t)((int32_t)edx >> 0xB);
    edx = edx - ebp;
    ebp = ebp + edi;
    MEM32(esp + 0x20) = ebp;
    edi = edi - MEM32(esp + 0x1C);
    ebp = MEM32(eax + 4);
    MEM32(esp + 0x2C) = edi;
    edi = edx + ebx;
    ebx = ebx - edx;
    edx = MEM32(eax + -12);
    MEM32(esp + 0x30) = ebx;
    MEM32(esp + 0x28) = edi;
    edi = MEM32(eax + -4);
    ebx = edx + edi;
    MEM32(esp + 0x18) = ebx;
    ebx = MEM32(eax + -20);
    edi = edi - edx;
    edx = ebx + ebp;
    ebx = ebx - ebp;
    ebp = MEM32(esp + 0x18);
    ebp = ebp + edx;
    MEM32(esp + 0x14) = ebp;
    ebp = ebx + edi;
    edi = (uint32_t)((int32_t)edi * (int32_t)0xFFFFEB18u);
    ebx = (uint32_t)((int32_t)ebx * (int32_t)0x8A9);
    ebp = (uint32_t)((int32_t)ebp * (int32_t)0xEC8);
    ebp = (uint32_t)((int32_t)ebp >> 0xB);
    MEM32(esp + 0x10) = ebp;
    ebp = MEM32(esp + 0x14);
    edi = (uint32_t)((int32_t)edi >> 0xB);
    edi = edi - ebp;
    edi = edi + MEM32(esp + 0x10);
    edx = edx - MEM32(esp + 0x18);
    edx = (uint32_t)((int32_t)edx * (int32_t)0xB50);
    ebx = (uint32_t)((int32_t)ebx >> 0xB);
    edx = (uint32_t)((int32_t)edx >> 0xB);
    edx = edx - edi;
    ebp = edx;
    ebx = ebx - MEM32(esp + 0x10);
    edx = MEM32(esp + 0x14);
    ebx = ebx + ebp;
    MEM32(esp + 0x10) = ebx;
    ebx = MEM32(esp + 0x20);
    ebx = edx + ebx + 0x7F;
    ebx = (uint32_t)((int32_t)ebx >> 8);
    SET_LO8(ebx, LO8(ebx) + MEM8(esi + -1));
    MEM8(ecx + -1) = LO8(ebx);
    ebx = MEM32(esp + 0x20);
    ebx = ebx - edx;
    SET_LO8(edx, MEM8(esi + 6));
    ebx = ebx + 0x7F;
    ebx = (uint32_t)((int32_t)ebx >> 8);
    SET_LO8(ebx, LO8(ebx) + LO8(edx));
    edx = MEM32(esp + 0x28);
    MEM8(ecx + 6) = LO8(ebx);
    ebx = edi + edx + 0x7F;
    ebx = (uint32_t)((int32_t)ebx >> 8);
    SET_LO8(ebx, LO8(ebx) + MEM8(esi));
    edx = edx - edi;
    edx = edx + 0x7F;
    MEM8(ecx) = LO8(ebx);
    SET_LO8(ebx, MEM8(esi + 5));
    edx = (uint32_t)((int32_t)edx >> 8);
    SET_LO8(edx, LO8(edx) + LO8(ebx));
    edi = MEM32(esp + 0x30);
    MEM8(ecx + 5) = LO8(edx);
    SET_LO8(ebx, MEM8(esi + 1));
    edx = edi + ebp + 0x7F;
    edx = (uint32_t)((int32_t)edx >> 8);
    SET_LO8(edx, LO8(edx) + LO8(ebx));
    MEM8(ecx + 1) = LO8(edx);
    SET_LO8(ebx, MEM8(esi + 4));
    edx = edi;
    edi = MEM32(esp + 0x2C);
    edx = edx - ebp;
    ebp = MEM32(esp + 0x10);
    edx = edx + 0x7F;
    edx = (uint32_t)((int32_t)edx >> 8);
    SET_LO8(edx, LO8(edx) + LO8(ebx));
    MEM8(ecx + 4) = LO8(edx);
    SET_LO8(ebx, MEM8(esi + 3));
    edx = edi + ebp + 0x7F;
    edx = (uint32_t)((int32_t)edx >> 8);
    SET_LO8(edx, LO8(edx) + LO8(ebx));
    MEM8(ecx + 3) = LO8(edx);
    SET_LO8(ebx, MEM8(esi + 2));
    edx = edi;
    edx = edx - ebp;
    edx = edx + 0x7F;
    edx = (uint32_t)((int32_t)edx >> 8);
    SET_LO8(edx, LO8(edx) + LO8(ebx));
    ebx = MEM32(esp + 0x13C);
    MEM8(ecx + 2) = LO8(edx);
    edx = MEM32(esp + 0x24);
    eax = eax + 0x20;
    ecx = ecx + ebx;
    esi = esi + 8;
    edx--;
    MEM32(esp + 0x24) = edx;
    if ((edx != 0)) goto loc_002163B0; /* jne: not equal / not zero */

loc_00216513: ;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebp);
    POP32(esp, ebx);
    esp = esp + 0x124;
    esp += 24; return; /* ret 20 */

}

/**
 * sub_00216520
 * Original: 0x00216520 - 0x00216E03 (2275 bytes, 793 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00216520(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    int _cf = 0; /* carry flag */
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_00216520: ;
    _cf = (int)((uint32_t)(esp) < (uint32_t)(0x124));
    esp = esp - 0x124;
    PUSH32(esp, ebx);
    PUSH32(esp, ebp);
    eax = 0; /* xor self */
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    MEM32(esp + 0x30) = eax;
    MEM32(esp + 0x34) = eax;
    ecx = 0x1E;
    edi = esp + 0x38;
    { uint32_t _i; for (_i = 0; _i < ecx; _i++) MEM32(edi + _i*4) = eax; }
    edi += ecx * 4; ecx = 0; /* rep stosd */
    ecx = MEM32(esp + 0x13C);
    esi = MEM32(ecx + 8);
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(4) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp esi, 4 (32-bit) */
    edi = MEM32(ecx + 4);
    eax = MEM32(ecx);
    if (CMP_B(_fa, _fb)) goto loc_00216564; /* jb: below (unsigned <) */

loc_00216553: ;
    SET_LO8(ebx, LO8(eax));
    _cf = 0; /* logical op clears CF */
    SET_LO8(ebx, LO8(ebx) & 0xF);
    if (4) _cf = (int)(((eax) >> ((4) - 1)) & 1);
    eax = eax >> 4;
    MEM8(esp + 0x17) = LO8(ebx);
    _cf = (int)((uint32_t)(esi) < (uint32_t)(4));
    esi = esi - 4;
    goto loc_00216586;

loc_00216564: ;
    edx = MEM32(edi);
    ecx = esi;
    SET_LO8(ebx, LO8(edx));
    if (LO8(ecx)) _cf = (int)(((LO8(ebx)) >> (8 - (LO8(ecx)))) & 1);
    SET_LO8(ebx, LO8(ebx) << LO8(ecx));
    ecx = 4;
    _cf = (int)((uint32_t)(ecx) < (uint32_t)(esi));
    ecx = ecx - esi;
    if (LO8(ecx)) _cf = (int)(((edx) >> ((LO8(ecx)) - 1)) & 1);
    edx = edx >> LO8(ecx);
    _cf = 0; /* logical op clears CF */
    SET_LO8(ebx, LO8(ebx) | LO8(eax));
    _cf = 0; /* logical op clears CF */
    SET_LO8(ebx, LO8(ebx) & 0xF);
    _cf = (int)((((uint64_t)(esi) + (uint64_t)(0x1C)) >> 32) & 1);
    esi = esi + 0x1C;
    MEM8(esp + 0x17) = LO8(ebx);
    eax = edx;
    _cf = (int)((((uint64_t)(edi) + (uint64_t)(4)) >> 32) & 1);
    edi = edi + 4;

loc_00216586: ;
    ecx = esp + 0xF4;
    MEM32(esp + 0x10) = ecx;
    ecx = 0; /* xor self */
    SET_LO8(ecx, LO8(ebx));
    edx = esp + 0xFA;
    MEM32(esp + 0x20) = edx;
    edx = 1;
    MEM8(esp + 0xF4) = 0x10;
    MEM8(esp + 0xF5) = 0x60;
    MEM8(esp + 0xF6) = 0xB0;
    ecx--;
    if (LO8(ecx)) _cf = (int)(((edx) >> (32 - (LO8(ecx)))) & 1);
    edx = edx << LO8(ecx);
    _fa = (uint32_t)(LO8(ebx)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp LO8(ebx), 1 (8-bit) */
    MEM8(esp + 0xF7) = 7;
    MEM8(esp + 0xF8) = 0xB;
    MEM8(esp + 0xF9) = 0xF;
    MEM32(esp + 0x24) = edx;
    if (CMP_BE(_fa, _fb)) goto loc_00216A31; /* jbe: below or equal (unsigned <=) */

loc_002165E5: ;
    SET_LO8(ecx, LO8(ebx));
    SET_LO8(ecx, LO8(ecx) - 1);
    ecx = ZX8(LO8(ecx));
    edx = ZX8(LO8(ebx));
    MEM32(esp + 0x2C) = ecx;

loc_002165F3: ;
    ecx = MEM32(esp + 0x10);
    edx--;
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(MEM32(esp + 0x20)) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp ecx, MEM32(esp + 0x20) (32-bit) */
    ebp = ecx;
    MEM32(esp + 0x28) = ebp;
    if (CMP_AE(_fa, _fb)) goto loc_00216A1D; /* jae: above or equal (unsigned >=) */

loc_00216608: ;
    goto loc_00216610;

    /* nop */

loc_00216610: ;
    SET_LO8(ebx, MEM8(ebp));
    _fa = (uint32_t)(LO8(ebx)) & 0xFFu; _fb = (uint32_t)(LO8(ebx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(ebx), LO8(ebx) (8-bit) */
    MEM8(esp + 0x18) = LO8(ebx);
    if (TEST_Z(_fa, _fb)) goto loc_00216A07; /* je: equal / zero */

loc_0021661F: ;
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(esi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test esi, esi (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0021662D; /* je: equal / zero */

loc_00216623: ;
    ecx = eax;
    _cf = 0; /* logical op clears CF */
    ecx = ecx & 1;
    if (1) _cf = (int)(((eax) >> ((1) - 1)) & 1);
    eax = eax >> 1;
    esi--;
    goto loc_0021663E;

loc_0021662D: ;
    ecx = MEM32(edi);
    eax = ecx;
    _cf = (int)((((uint64_t)(edi) + (uint64_t)(4)) >> 32) & 1);
    edi = edi + 4;
    if (1) _cf = (int)(((eax) >> ((1) - 1)) & 1);
    eax = eax >> 1;
    esi = 0x1F;
    _cf = 0; /* logical op clears CF */
    ecx = ecx & 1;

loc_0021663E: ;
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, ecx (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00216A07; /* je: equal / zero */

loc_00216646: ;
    ecx = MEM32(esp + 0x18);
    _cf = 0; /* logical op clears CF */
    ecx = ecx & 3;
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(3) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp ecx, 3 (32-bit) */
    if (CMP_A(_fa, _fb)) goto loc_00216A07; /* ja: above (unsigned >) */

loc_00216656: ;
    { uint32_t _jt = MEM32(ecx * 4 + 0x216E04); /* switch: 8 entries, 8 targets */
    if (_jt == 0x0021665Du) goto loc_0021665D;
    if (_jt == 0x0021666Du) goto loc_0021666D;
    if (_jt == 0x002166A3u) goto loc_002166A3;
    if (_jt == 0x00216983u) goto loc_00216983;
    if (_jt == 0x00216A9Du) goto loc_00216A9D;
    if (_jt == 0x00216AADu) goto loc_00216AAD;
    if (_jt == 0x00216ADAu) goto loc_00216ADA;
    if (_jt == 0x00216C98u) goto loc_00216C98;
    g_seh_ebp = ebp; RECOMP_ITAIL(_jt); return; }

loc_0021665D: ;
    if (2) _cf = (int)(((LO8(ebx)) >> ((2) - 1)) & 1);
    SET_LO8(ebx, LO8(ebx) >> 2);
    SET_LO8(ecx, LO8(ebx));
    if (2) _cf = (int)(((LO8(ecx)) >> (8 - (2))) & 1);
    SET_LO8(ecx, LO8(ecx) << 2);
    _cf = (int)((((uint64_t)(LO8(ecx)) + (uint64_t)(0x11)) >> 8) & 1);
    SET_LO8(ecx, LO8(ecx) + 0x11);
    MEM8(ebp) = LO8(ecx);
    goto loc_002166AF;

loc_0021666D: ;
    if (2) _cf = (int)(((LO8(ebx)) >> ((2) - 1)) & 1);
    SET_LO8(ebx, LO8(ebx) >> 2);
    SET_LO8(ecx, LO8(ebx));
    if (2) _cf = (int)(((LO8(ecx)) >> (8 - (2))) & 1);
    SET_LO8(ecx, LO8(ecx) << 2);
    SET_LO8(ebx, LO8(ecx));
    _cf = (int)((((uint64_t)(LO8(ebx)) + (uint64_t)(2)) >> 8) & 1);
    SET_LO8(ebx, LO8(ebx) + 2);
    MEM8(ebp) = LO8(ebx);
    ebp = MEM32(esp + 0x20);
    SET_LO8(ebx, LO8(ecx));
    _cf = (int)((((uint64_t)(LO8(ebx)) + (uint64_t)(0x12)) >> 8) & 1);
    SET_LO8(ebx, LO8(ebx) + 0x12);
    MEM8(ebp) = LO8(ebx);
    SET_LO8(ebx, LO8(ecx));
    ebp++;
    _cf = (int)((((uint64_t)(LO8(ebx)) + (uint64_t)(0x22)) >> 8) & 1);
    SET_LO8(ebx, LO8(ebx) + 0x22);
    MEM8(ebp) = LO8(ebx);
    ebp++;
    _cf = (int)((((uint64_t)(LO8(ecx)) + (uint64_t)(0x32)) >> 8) & 1);
    SET_LO8(ecx, LO8(ecx) + 0x32);
    MEM8(ebp) = LO8(ecx);
    ebp++;
    MEM32(esp + 0x20) = ebp;
    goto loc_00216A0B;

loc_002166A3: ;
    if (2) _cf = (int)(((LO8(ebx)) >> ((2) - 1)) & 1);
    SET_LO8(ebx, LO8(ebx) >> 2);
    MEM8(ebp) = 0;
    ebp++;
    MEM32(esp + 0x28) = ebp;

loc_002166AF: ;
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(esi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test esi, esi (32-bit) */
    MEM8(esp + 0x18) = LO8(ebx);
    if (TEST_Z(_fa, _fb)) goto loc_002166C1; /* je: equal / zero */

loc_002166B7: ;
    ecx = eax;
    _cf = 0; /* logical op clears CF */
    ecx = ecx & 1;
    if (1) _cf = (int)(((eax) >> ((1) - 1)) & 1);
    eax = eax >> 1;
    esi--;
    goto loc_002166D2;

loc_002166C1: ;
    ecx = MEM32(edi);
    eax = ecx;
    _cf = (int)((((uint64_t)(edi) + (uint64_t)(4)) >> 32) & 1);
    edi = edi + 4;
    if (1) _cf = (int)(((eax) >> ((1) - 1)) & 1);
    eax = eax >> 1;
    esi = 0x1F;
    _cf = 0; /* logical op clears CF */
    ecx = ecx & 1;

loc_002166D2: ;
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, ecx (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_002166EB; /* je: equal / zero */

loc_002166D6: ;
    MEM32(esp + 0x10) = MEM32(esp + 0x10) - 1;
    ebp = MEM32(esp + 0x10);
    SET_LO8(ecx, LO8(ebx));
    if (2) _cf = (int)(((LO8(ecx)) >> (8 - (2))) & 1);
    SET_LO8(ecx, LO8(ecx) << 2);
    _cf = (int)((((uint64_t)(LO8(ecx)) + (uint64_t)(3)) >> 8) & 1);
    SET_LO8(ecx, LO8(ecx) + 3);
    MEM8(ebp) = LO8(ecx);
    goto loc_00216761;

loc_002166EB: ;
    ecx = 0x20;
    _cf = 0; /* logical op clears CF */
    ebp = ebp | 0xFFFFFFFFu;
    _cf = (int)((uint32_t)(ecx) < (uint32_t)(edx));
    ecx = ecx - edx;
    if (LO8(ecx)) _cf = (int)(((ebp) >> ((LO8(ecx)) - 1)) & 1);
    ebp = ebp >> LO8(ecx);
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(edx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp esi, edx (32-bit) */
    if (CMP_B(_fa, _fb)) goto loc_00216705; /* jb: below (unsigned <) */

loc_002166FB: ;
    _cf = 0; /* logical op clears CF */
    ebp = ebp & eax;
    ecx = edx;
    if (LO8(ecx)) _cf = (int)(((eax) >> ((LO8(ecx)) - 1)) & 1);
    eax = eax >> LO8(ecx);
    _cf = (int)((uint32_t)(esi) < (uint32_t)(edx));
    esi = esi - edx;
    goto loc_0021672D;

loc_00216705: ;
    ebx = MEM32(edi);
    MEM32(esp + 0x1C) = ebx;
    ecx = esi;
    if (LO8(ecx)) _cf = (int)(((ebx) >> (32 - (LO8(ecx)))) & 1);
    ebx = ebx << LO8(ecx);
    ecx = edx;
    _cf = (int)((uint32_t)(ecx) < (uint32_t)(esi));
    ecx = ecx - esi;
    _cf = 0; /* logical op clears CF */
    ebx = ebx | eax;
    eax = MEM32(esp + 0x1C);
    if (LO8(ecx)) _cf = (int)(((eax) >> ((LO8(ecx)) - 1)) & 1);
    eax = eax >> LO8(ecx);
    ecx = 0x20;
    _cf = (int)((uint32_t)(ecx) < (uint32_t)(edx));
    ecx = ecx - edx;
    _cf = 0; /* logical op clears CF */
    ebp = ebp & ebx;
    SET_LO8(ebx, MEM8(esp + 0x18));
    _cf = (int)((((uint64_t)(esi) + (uint64_t)(ecx)) >> 32) & 1);
    esi = esi + ecx;
    _cf = (int)((((uint64_t)(edi) + (uint64_t)(4)) >> 32) & 1);
    edi = edi + 4;

loc_0021672D: ;
    _cf = 0; /* logical op clears CF */
    ebp = ebp | MEM32(esp + 0x24);
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(esi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test esi, esi (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0021673F; /* je: equal / zero */

loc_00216735: ;
    ecx = eax;
    _cf = 0; /* logical op clears CF */
    ecx = ecx & 1;
    if (1) _cf = (int)(((eax) >> ((1) - 1)) & 1);
    eax = eax >> 1;
    esi--;
    goto loc_00216750;

loc_0021673F: ;
    ecx = MEM32(edi);
    eax = ecx;
    _cf = (int)((((uint64_t)(edi) + (uint64_t)(4)) >> 32) & 1);
    edi = edi + 4;
    if (1) _cf = (int)(((eax) >> ((1) - 1)) & 1);
    eax = eax >> 1;
    esi = 0x1F;
    _cf = 0; /* logical op clears CF */
    ecx = ecx & 1;

loc_00216750: ;
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, ecx (32-bit) */
    ebp = SX16(LO16(ebp)); /* MOVSX 0x00216752: movsx ebp, bp */
    if (TEST_Z(_fa, _fb)) goto loc_00216759; /* je: equal / zero */

loc_00216757: ;
    _cf = (int)((ebp) != 0);
    ebp = (uint32_t)(-(int32_t)ebp);

loc_00216759: ;
    ecx = ZX8(LO8(ebx));
    MEM16(esp + ecx * 2 + 0x30) = LO16(ebp);

loc_00216761: ;
    SET_LO8(ebx, LO8(ebx) + 1);
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(esi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test esi, esi (32-bit) */
    MEM8(esp + 0x18) = LO8(ebx);
    if (TEST_Z(_fa, _fb)) goto loc_00216775; /* je: equal / zero */

loc_0021676B: ;
    ecx = eax;
    _cf = 0; /* logical op clears CF */
    ecx = ecx & 1;
    if (1) _cf = (int)(((eax) >> ((1) - 1)) & 1);
    eax = eax >> 1;
    esi--;
    goto loc_00216786;

loc_00216775: ;
    ecx = MEM32(edi);
    eax = ecx;
    _cf = (int)((((uint64_t)(edi) + (uint64_t)(4)) >> 32) & 1);
    edi = edi + 4;
    if (1) _cf = (int)(((eax) >> ((1) - 1)) & 1);
    eax = eax >> 1;
    esi = 0x1F;
    _cf = 0; /* logical op clears CF */
    ecx = ecx & 1;

loc_00216786: ;
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, ecx (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0021679F; /* je: equal / zero */

loc_0021678A: ;
    MEM32(esp + 0x10) = MEM32(esp + 0x10) - 1;
    ebp = MEM32(esp + 0x10);
    SET_LO8(ecx, LO8(ebx));
    if (2) _cf = (int)(((LO8(ecx)) >> (8 - (2))) & 1);
    SET_LO8(ecx, LO8(ecx) << 2);
    _cf = (int)((((uint64_t)(LO8(ecx)) + (uint64_t)(3)) >> 8) & 1);
    SET_LO8(ecx, LO8(ecx) + 3);
    MEM8(ebp) = LO8(ecx);
    goto loc_00216815;

loc_0021679F: ;
    ecx = 0x20;
    _cf = 0; /* logical op clears CF */
    ebp = ebp | 0xFFFFFFFFu;
    _cf = (int)((uint32_t)(ecx) < (uint32_t)(edx));
    ecx = ecx - edx;
    if (LO8(ecx)) _cf = (int)(((ebp) >> ((LO8(ecx)) - 1)) & 1);
    ebp = ebp >> LO8(ecx);
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(edx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp esi, edx (32-bit) */
    if (CMP_B(_fa, _fb)) goto loc_002167B9; /* jb: below (unsigned <) */

loc_002167AF: ;
    _cf = 0; /* logical op clears CF */
    ebp = ebp & eax;
    ecx = edx;
    if (LO8(ecx)) _cf = (int)(((eax) >> ((LO8(ecx)) - 1)) & 1);
    eax = eax >> LO8(ecx);
    _cf = (int)((uint32_t)(esi) < (uint32_t)(edx));
    esi = esi - edx;
    goto loc_002167E1;

loc_002167B9: ;
    ebx = MEM32(edi);
    MEM32(esp + 0x1C) = ebx;
    ecx = esi;
    if (LO8(ecx)) _cf = (int)(((ebx) >> (32 - (LO8(ecx)))) & 1);
    ebx = ebx << LO8(ecx);
    ecx = edx;
    _cf = (int)((uint32_t)(ecx) < (uint32_t)(esi));
    ecx = ecx - esi;
    _cf = 0; /* logical op clears CF */
    ebx = ebx | eax;
    eax = MEM32(esp + 0x1C);
    if (LO8(ecx)) _cf = (int)(((eax) >> ((LO8(ecx)) - 1)) & 1);
    eax = eax >> LO8(ecx);
    ecx = 0x20;
    _cf = (int)((uint32_t)(ecx) < (uint32_t)(edx));
    ecx = ecx - edx;
    _cf = 0; /* logical op clears CF */
    ebp = ebp & ebx;
    SET_LO8(ebx, MEM8(esp + 0x18));
    _cf = (int)((((uint64_t)(esi) + (uint64_t)(ecx)) >> 32) & 1);
    esi = esi + ecx;
    _cf = (int)((((uint64_t)(edi) + (uint64_t)(4)) >> 32) & 1);
    edi = edi + 4;

loc_002167E1: ;
    _cf = 0; /* logical op clears CF */
    ebp = ebp | MEM32(esp + 0x24);
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(esi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test esi, esi (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_002167F3; /* je: equal / zero */

loc_002167E9: ;
    ecx = eax;
    _cf = 0; /* logical op clears CF */
    ecx = ecx & 1;
    if (1) _cf = (int)(((eax) >> ((1) - 1)) & 1);
    eax = eax >> 1;
    esi--;
    goto loc_00216804;

loc_002167F3: ;
    ecx = MEM32(edi);
    eax = ecx;
    _cf = (int)((((uint64_t)(edi) + (uint64_t)(4)) >> 32) & 1);
    edi = edi + 4;
    if (1) _cf = (int)(((eax) >> ((1) - 1)) & 1);
    eax = eax >> 1;
    esi = 0x1F;
    _cf = 0; /* logical op clears CF */
    ecx = ecx & 1;

loc_00216804: ;
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, ecx (32-bit) */
    ebp = SX16(LO16(ebp)); /* MOVSX 0x00216806: movsx ebp, bp */
    if (TEST_Z(_fa, _fb)) goto loc_0021680D; /* je: equal / zero */

loc_0021680B: ;
    _cf = (int)((ebp) != 0);
    ebp = (uint32_t)(-(int32_t)ebp);

loc_0021680D: ;
    ecx = ZX8(LO8(ebx));
    MEM16(esp + ecx * 2 + 0x30) = LO16(ebp);

loc_00216815: ;
    SET_LO8(ebx, LO8(ebx) + 1);
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(esi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test esi, esi (32-bit) */
    MEM8(esp + 0x18) = LO8(ebx);
    if (TEST_Z(_fa, _fb)) goto loc_00216829; /* je: equal / zero */

loc_0021681F: ;
    ecx = eax;
    _cf = 0; /* logical op clears CF */
    ecx = ecx & 1;
    if (1) _cf = (int)(((eax) >> ((1) - 1)) & 1);
    eax = eax >> 1;
    esi--;
    goto loc_0021683A;

loc_00216829: ;
    ecx = MEM32(edi);
    eax = ecx;
    _cf = (int)((((uint64_t)(edi) + (uint64_t)(4)) >> 32) & 1);
    edi = edi + 4;
    if (1) _cf = (int)(((eax) >> ((1) - 1)) & 1);
    eax = eax >> 1;
    esi = 0x1F;
    _cf = 0; /* logical op clears CF */
    ecx = ecx & 1;

loc_0021683A: ;
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, ecx (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00216853; /* je: equal / zero */

loc_0021683E: ;
    MEM32(esp + 0x10) = MEM32(esp + 0x10) - 1;
    ebp = MEM32(esp + 0x10);
    SET_LO8(ecx, LO8(ebx));
    if (2) _cf = (int)(((LO8(ecx)) >> (8 - (2))) & 1);
    SET_LO8(ecx, LO8(ecx) << 2);
    _cf = (int)((((uint64_t)(LO8(ecx)) + (uint64_t)(3)) >> 8) & 1);
    SET_LO8(ecx, LO8(ecx) + 3);
    MEM8(ebp) = LO8(ecx);
    goto loc_002168C9;

loc_00216853: ;
    ecx = 0x20;
    _cf = 0; /* logical op clears CF */
    ebp = ebp | 0xFFFFFFFFu;
    _cf = (int)((uint32_t)(ecx) < (uint32_t)(edx));
    ecx = ecx - edx;
    if (LO8(ecx)) _cf = (int)(((ebp) >> ((LO8(ecx)) - 1)) & 1);
    ebp = ebp >> LO8(ecx);
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(edx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp esi, edx (32-bit) */
    if (CMP_B(_fa, _fb)) goto loc_0021686D; /* jb: below (unsigned <) */

loc_00216863: ;
    _cf = 0; /* logical op clears CF */
    ebp = ebp & eax;
    ecx = edx;
    if (LO8(ecx)) _cf = (int)(((eax) >> ((LO8(ecx)) - 1)) & 1);
    eax = eax >> LO8(ecx);
    _cf = (int)((uint32_t)(esi) < (uint32_t)(edx));
    esi = esi - edx;
    goto loc_00216895;

loc_0021686D: ;
    ebx = MEM32(edi);
    MEM32(esp + 0x1C) = ebx;
    ecx = esi;
    if (LO8(ecx)) _cf = (int)(((ebx) >> (32 - (LO8(ecx)))) & 1);
    ebx = ebx << LO8(ecx);
    ecx = edx;
    _cf = (int)((uint32_t)(ecx) < (uint32_t)(esi));
    ecx = ecx - esi;
    _cf = 0; /* logical op clears CF */
    ebx = ebx | eax;
    eax = MEM32(esp + 0x1C);
    if (LO8(ecx)) _cf = (int)(((eax) >> ((LO8(ecx)) - 1)) & 1);
    eax = eax >> LO8(ecx);
    ecx = 0x20;
    _cf = (int)((uint32_t)(ecx) < (uint32_t)(edx));
    ecx = ecx - edx;
    _cf = 0; /* logical op clears CF */
    ebp = ebp & ebx;
    SET_LO8(ebx, MEM8(esp + 0x18));
    _cf = (int)((((uint64_t)(esi) + (uint64_t)(ecx)) >> 32) & 1);
    esi = esi + ecx;
    _cf = (int)((((uint64_t)(edi) + (uint64_t)(4)) >> 32) & 1);
    edi = edi + 4;

loc_00216895: ;
    _cf = 0; /* logical op clears CF */
    ebp = ebp | MEM32(esp + 0x24);
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(esi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test esi, esi (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_002168A7; /* je: equal / zero */

loc_0021689D: ;
    ecx = eax;
    _cf = 0; /* logical op clears CF */
    ecx = ecx & 1;
    if (1) _cf = (int)(((eax) >> ((1) - 1)) & 1);
    eax = eax >> 1;
    esi--;
    goto loc_002168B8;

loc_002168A7: ;
    ecx = MEM32(edi);
    eax = ecx;
    _cf = (int)((((uint64_t)(edi) + (uint64_t)(4)) >> 32) & 1);
    edi = edi + 4;
    if (1) _cf = (int)(((eax) >> ((1) - 1)) & 1);
    eax = eax >> 1;
    esi = 0x1F;
    _cf = 0; /* logical op clears CF */
    ecx = ecx & 1;

loc_002168B8: ;
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, ecx (32-bit) */
    ebp = SX16(LO16(ebp)); /* MOVSX 0x002168BA: movsx ebp, bp */
    if (TEST_Z(_fa, _fb)) goto loc_002168C1; /* je: equal / zero */

loc_002168BF: ;
    _cf = (int)((ebp) != 0);
    ebp = (uint32_t)(-(int32_t)ebp);

loc_002168C1: ;
    ecx = ZX8(LO8(ebx));
    MEM16(esp + ecx * 2 + 0x30) = LO16(ebp);

loc_002168C9: ;
    SET_LO8(ebx, LO8(ebx) + 1);
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(esi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test esi, esi (32-bit) */
    MEM8(esp + 0x18) = LO8(ebx);
    if (TEST_Z(_fa, _fb)) goto loc_002168DD; /* je: equal / zero */

loc_002168D3: ;
    ecx = eax;
    _cf = 0; /* logical op clears CF */
    ecx = ecx & 1;
    if (1) _cf = (int)(((eax) >> ((1) - 1)) & 1);
    eax = eax >> 1;
    esi--;
    goto loc_002168EE;

loc_002168DD: ;
    ecx = MEM32(edi);
    eax = ecx;
    _cf = (int)((((uint64_t)(edi) + (uint64_t)(4)) >> 32) & 1);
    edi = edi + 4;
    if (1) _cf = (int)(((eax) >> ((1) - 1)) & 1);
    eax = eax >> 1;
    esi = 0x1F;
    _cf = 0; /* logical op clears CF */
    ecx = ecx & 1;

loc_002168EE: ;
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, ecx (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00216908; /* je: equal / zero */

loc_002168F2: ;
    ecx = MEM32(esp + 0x10);
    ecx--;
    if (2) _cf = (int)(((LO8(ebx)) >> (8 - (2))) & 1);
    SET_LO8(ebx, LO8(ebx) << 2);
    _cf = (int)((((uint64_t)(LO8(ebx)) + (uint64_t)(3)) >> 8) & 1);
    SET_LO8(ebx, LO8(ebx) + 3);
    MEM32(esp + 0x10) = ecx;
    MEM8(ecx) = LO8(ebx);
    goto loc_00216A0B;

loc_00216908: ;
    ecx = 0x20;
    _cf = 0; /* logical op clears CF */
    ebp = ebp | 0xFFFFFFFFu;
    _cf = (int)((uint32_t)(ecx) < (uint32_t)(edx));
    ecx = ecx - edx;
    if (LO8(ecx)) _cf = (int)(((ebp) >> ((LO8(ecx)) - 1)) & 1);
    ebp = ebp >> LO8(ecx);
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(edx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp esi, edx (32-bit) */
    if (CMP_B(_fa, _fb)) goto loc_00216922; /* jb: below (unsigned <) */

loc_00216918: ;
    _cf = 0; /* logical op clears CF */
    ebp = ebp & eax;
    ecx = edx;
    if (LO8(ecx)) _cf = (int)(((eax) >> ((LO8(ecx)) - 1)) & 1);
    eax = eax >> LO8(ecx);
    _cf = (int)((uint32_t)(esi) < (uint32_t)(edx));
    esi = esi - edx;
    goto loc_0021694A;

loc_00216922: ;
    ebx = MEM32(edi);
    MEM32(esp + 0x1C) = ebx;
    ecx = esi;
    if (LO8(ecx)) _cf = (int)(((ebx) >> (32 - (LO8(ecx)))) & 1);
    ebx = ebx << LO8(ecx);
    ecx = edx;
    _cf = (int)((uint32_t)(ecx) < (uint32_t)(esi));
    ecx = ecx - esi;
    _cf = 0; /* logical op clears CF */
    ebx = ebx | eax;
    eax = MEM32(esp + 0x1C);
    if (LO8(ecx)) _cf = (int)(((eax) >> ((LO8(ecx)) - 1)) & 1);
    eax = eax >> LO8(ecx);
    ecx = 0x20;
    _cf = (int)((uint32_t)(ecx) < (uint32_t)(edx));
    ecx = ecx - edx;
    _cf = 0; /* logical op clears CF */
    ebp = ebp & ebx;
    SET_LO8(ebx, MEM8(esp + 0x18));
    _cf = (int)((((uint64_t)(esi) + (uint64_t)(ecx)) >> 32) & 1);
    esi = esi + ecx;
    _cf = (int)((((uint64_t)(edi) + (uint64_t)(4)) >> 32) & 1);
    edi = edi + 4;

loc_0021694A: ;
    _cf = 0; /* logical op clears CF */
    ebp = ebp | MEM32(esp + 0x24);
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(esi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test esi, esi (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0021695C; /* je: equal / zero */

loc_00216952: ;
    ecx = eax;
    _cf = 0; /* logical op clears CF */
    ecx = ecx & 1;
    if (1) _cf = (int)(((eax) >> ((1) - 1)) & 1);
    eax = eax >> 1;
    esi--;
    goto loc_0021696D;

loc_0021695C: ;
    ecx = MEM32(edi);
    eax = ecx;
    _cf = (int)((((uint64_t)(edi) + (uint64_t)(4)) >> 32) & 1);
    edi = edi + 4;
    if (1) _cf = (int)(((eax) >> ((1) - 1)) & 1);
    eax = eax >> 1;
    esi = 0x1F;
    _cf = 0; /* logical op clears CF */
    ecx = ecx & 1;

loc_0021696D: ;
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, ecx (32-bit) */
    ebp = SX16(LO16(ebp)); /* MOVSX 0x0021696F: movsx ebp, bp */
    if (TEST_Z(_fa, _fb)) goto loc_00216976; /* je: equal / zero */

loc_00216974: ;
    _cf = (int)((ebp) != 0);
    ebp = (uint32_t)(-(int32_t)ebp);

loc_00216976: ;
    ecx = ZX8(LO8(ebx));
    MEM16(esp + ecx * 2 + 0x30) = LO16(ebp);
    goto loc_00216A0B;

loc_00216983: ;
    ecx = 0x20;
    _cf = 0; /* logical op clears CF */
    ebp = ebp | 0xFFFFFFFFu;
    _cf = (int)((uint32_t)(ecx) < (uint32_t)(edx));
    ecx = ecx - edx;
    if (2) _cf = (int)(((LO8(ebx)) >> ((2) - 1)) & 1);
    SET_LO8(ebx, LO8(ebx) >> 2);
    if (LO8(ecx)) _cf = (int)(((ebp) >> ((LO8(ecx)) - 1)) & 1);
    ebp = ebp >> LO8(ecx);
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(edx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp esi, edx (32-bit) */
    MEM8(esp + 0x18) = LO8(ebx);
    if (CMP_B(_fa, _fb)) goto loc_002169A4; /* jb: below (unsigned <) */

loc_0021699A: ;
    _cf = 0; /* logical op clears CF */
    ebp = ebp & eax;
    ecx = edx;
    if (LO8(ecx)) _cf = (int)(((eax) >> ((LO8(ecx)) - 1)) & 1);
    eax = eax >> LO8(ecx);
    _cf = (int)((uint32_t)(esi) < (uint32_t)(edx));
    esi = esi - edx;
    goto loc_002169CC;

loc_002169A4: ;
    ebx = MEM32(edi);
    MEM32(esp + 0x1C) = ebx;
    ecx = esi;
    if (LO8(ecx)) _cf = (int)(((ebx) >> (32 - (LO8(ecx)))) & 1);
    ebx = ebx << LO8(ecx);
    ecx = edx;
    _cf = (int)((uint32_t)(ecx) < (uint32_t)(esi));
    ecx = ecx - esi;
    _cf = 0; /* logical op clears CF */
    ebx = ebx | eax;
    eax = MEM32(esp + 0x1C);
    if (LO8(ecx)) _cf = (int)(((eax) >> ((LO8(ecx)) - 1)) & 1);
    eax = eax >> LO8(ecx);
    ecx = 0x20;
    _cf = (int)((uint32_t)(ecx) < (uint32_t)(edx));
    ecx = ecx - edx;
    _cf = 0; /* logical op clears CF */
    ebp = ebp & ebx;
    SET_LO8(ebx, MEM8(esp + 0x18));
    _cf = (int)((((uint64_t)(esi) + (uint64_t)(ecx)) >> 32) & 1);
    esi = esi + ecx;
    _cf = (int)((((uint64_t)(edi) + (uint64_t)(4)) >> 32) & 1);
    edi = edi + 4;

loc_002169CC: ;
    _cf = 0; /* logical op clears CF */
    ebp = ebp | MEM32(esp + 0x24);
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(esi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test esi, esi (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_002169DE; /* je: equal / zero */

loc_002169D4: ;
    ecx = eax;
    _cf = 0; /* logical op clears CF */
    ecx = ecx & 1;
    if (1) _cf = (int)(((eax) >> ((1) - 1)) & 1);
    eax = eax >> 1;
    esi--;
    goto loc_002169EF;

loc_002169DE: ;
    ecx = MEM32(edi);
    eax = ecx;
    _cf = (int)((((uint64_t)(edi) + (uint64_t)(4)) >> 32) & 1);
    edi = edi + 4;
    if (1) _cf = (int)(((eax) >> ((1) - 1)) & 1);
    eax = eax >> 1;
    esi = 0x1F;
    _cf = 0; /* logical op clears CF */
    ecx = ecx & 1;

loc_002169EF: ;
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, ecx (32-bit) */
    ebp = SX16(LO16(ebp)); /* MOVSX 0x002169F1: movsx ebp, bp */
    if (TEST_Z(_fa, _fb)) goto loc_002169F8; /* je: equal / zero */

loc_002169F6: ;
    _cf = (int)((ebp) != 0);
    ebp = (uint32_t)(-(int32_t)ebp);

loc_002169F8: ;
    ecx = ZX8(LO8(ebx));
    MEM16(esp + ecx * 2 + 0x30) = LO16(ebp);
    ecx = MEM32(esp + 0x28);
    MEM8(ecx) = 0;

loc_00216A07: ;
    MEM32(esp + 0x28) = MEM32(esp + 0x28) + 1;

loc_00216A0B: ;
    ebp = MEM32(esp + 0x28);
    _fa = (uint32_t)(ebp) & 0xFFFFFFFFu; _fb = (uint32_t)(MEM32(esp + 0x20)) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp ebp, MEM32(esp + 0x20) (32-bit) */
    if (CMP_B(_fa, _fb)) goto loc_00216610; /* jb: below (unsigned <) */

loc_00216A19: ;
    SET_LO8(ebx, MEM8(esp + 0x17));

loc_00216A1D: ;
    ecx = MEM32(esp + 0x2C);
    if (1) _cf = (int)(((MEM16(esp + 0x24)) >> ((1) - 1)) & 1);
    MEM16(esp + 0x24) = (uint32_t)((int32_t)MEM16(esp + 0x24) >> 1);
    ecx--;
    MEM32(esp + 0x2C) = ecx;
    if ((ecx != 0)) goto loc_002165F3; /* jne: not equal / not zero */

loc_00216A31: ;
    _fa = (uint32_t)(LO8(ebx)) & 0xFFu; _fb = (uint32_t)(LO8(ebx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(ebx), LO8(ebx) (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00216CDA; /* je: equal / zero */

loc_00216A39: ;
    ecx = MEM32(esp + 0x10);
    edx = MEM32(esp + 0x20);
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(edx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp ecx, edx (32-bit) */
    ebp = ecx;
    if (CMP_AE(_fa, _fb)) goto loc_00216CDA; /* jae: above or equal (unsigned >=) */

loc_00216A4B: ;
    ebx = edx;
    /* nop */

loc_00216A50: ;
    SET_LO8(ecx, MEM8(ebp));
    _fa = (uint32_t)(LO8(ecx)) & 0xFFu; _fb = (uint32_t)(LO8(ecx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(ecx), LO8(ecx) (8-bit) */
    MEM8(esp + 0x1C) = LO8(ecx);
    if (TEST_Z(_fa, _fb)) goto loc_00216CD1; /* je: equal / zero */

loc_00216A5F: ;
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(esi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test esi, esi (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00216A6D; /* je: equal / zero */

loc_00216A63: ;
    edx = eax;
    _cf = 0; /* logical op clears CF */
    edx = edx & 1;
    if (1) _cf = (int)(((eax) >> ((1) - 1)) & 1);
    eax = eax >> 1;
    esi--;
    goto loc_00216A7E;

loc_00216A6D: ;
    edx = MEM32(edi);
    eax = edx;
    _cf = (int)((((uint64_t)(edi) + (uint64_t)(4)) >> 32) & 1);
    edi = edi + 4;
    if (1) _cf = (int)(((eax) >> ((1) - 1)) & 1);
    eax = eax >> 1;
    esi = 0x1F;
    _cf = 0; /* logical op clears CF */
    edx = edx & 1;

loc_00216A7E: ;
    _fa = (uint32_t)(edx) & 0xFFFFFFFFu; _fb = (uint32_t)(edx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test edx, edx (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00216CD1; /* je: equal / zero */

loc_00216A86: ;
    edx = MEM32(esp + 0x1C);
    _cf = 0; /* logical op clears CF */
    edx = edx & 3;
    _fa = (uint32_t)(edx) & 0xFFFFFFFFu; _fb = (uint32_t)(3) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edx, 3 (32-bit) */
    if (CMP_A(_fa, _fb)) goto loc_00216CD1; /* ja: above (unsigned >) */

loc_00216A96: ;
    { uint32_t _jt = MEM32(edx * 4 + 0x216E14); /* switch: 4 entries, 4 targets */
    if (_jt == 0x00216A9Du) goto loc_00216A9D;
    if (_jt == 0x00216AADu) goto loc_00216AAD;
    if (_jt == 0x00216ADAu) goto loc_00216ADA;
    if (_jt == 0x00216C98u) goto loc_00216C98;
    g_seh_ebp = ebp; RECOMP_ITAIL(_jt); return; }

loc_00216A9D: ;
    if (2) _cf = (int)(((LO8(ecx)) >> ((2) - 1)) & 1);
    SET_LO8(ecx, LO8(ecx) >> 2);
    SET_LO8(edx, LO8(ecx));
    if (2) _cf = (int)(((LO8(edx)) >> (8 - (2))) & 1);
    SET_LO8(edx, LO8(edx) << 2);
    _cf = (int)((((uint64_t)(LO8(edx)) + (uint64_t)(0x11)) >> 8) & 1);
    SET_LO8(edx, LO8(edx) + 0x11);
    MEM8(ebp) = LO8(edx);
    goto loc_00216AE2;

loc_00216AAD: ;
    if (2) _cf = (int)(((LO8(ecx)) >> ((2) - 1)) & 1);
    SET_LO8(ecx, LO8(ecx) >> 2);
    if (2) _cf = (int)(((LO8(ecx)) >> (8 - (2))) & 1);
    SET_LO8(ecx, LO8(ecx) << 2);
    SET_LO8(edx, LO8(ecx));
    _cf = (int)((((uint64_t)(LO8(edx)) + (uint64_t)(2)) >> 8) & 1);
    SET_LO8(edx, LO8(edx) + 2);
    MEM8(ebp) = LO8(edx);
    SET_LO8(edx, LO8(ecx));
    _cf = (int)((((uint64_t)(LO8(edx)) + (uint64_t)(0x12)) >> 8) & 1);
    SET_LO8(edx, LO8(edx) + 0x12);
    MEM8(ebx) = LO8(edx);
    SET_LO8(edx, LO8(ecx));
    ebx++;
    _cf = (int)((((uint64_t)(LO8(edx)) + (uint64_t)(0x22)) >> 8) & 1);
    SET_LO8(edx, LO8(edx) + 0x22);
    MEM8(ebx) = LO8(edx);
    ebx++;
    _cf = (int)((((uint64_t)(LO8(ecx)) + (uint64_t)(0x32)) >> 8) & 1);
    SET_LO8(ecx, LO8(ecx) + 0x32);
    MEM8(ebx) = LO8(ecx);
    ebx++;
    MEM32(esp + 0x20) = ebx;
    goto loc_00216CD2;

loc_00216ADA: ;
    if (2) _cf = (int)(((LO8(ecx)) >> ((2) - 1)) & 1);
    SET_LO8(ecx, LO8(ecx) >> 2);
    MEM8(ebp) = 0;
    ebp++;

loc_00216AE2: ;
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(esi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test esi, esi (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00216AF0; /* je: equal / zero */

loc_00216AE6: ;
    edx = eax;
    _cf = 0; /* logical op clears CF */
    edx = edx & 1;
    if (1) _cf = (int)(((eax) >> ((1) - 1)) & 1);
    eax = eax >> 1;
    esi--;
    goto loc_00216B01;

loc_00216AF0: ;
    edx = MEM32(edi);
    eax = edx;
    _cf = (int)((((uint64_t)(edi) + (uint64_t)(4)) >> 32) & 1);
    edi = edi + 4;
    if (1) _cf = (int)(((eax) >> ((1) - 1)) & 1);
    eax = eax >> 1;
    esi = 0x1F;
    _cf = 0; /* logical op clears CF */
    edx = edx & 1;

loc_00216B01: ;
    _fa = (uint32_t)(edx) & 0xFFFFFFFFu; _fb = (uint32_t)(edx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test edx, edx (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00216B1A; /* je: equal / zero */

loc_00216B05: ;
    edx = MEM32(esp + 0x10);
    SET_LO8(ebx, LO8(ecx));
    edx--;
    if (2) _cf = (int)(((LO8(ebx)) >> (8 - (2))) & 1);
    SET_LO8(ebx, LO8(ebx) << 2);
    _cf = (int)((((uint64_t)(LO8(ebx)) + (uint64_t)(3)) >> 8) & 1);
    SET_LO8(ebx, LO8(ebx) + 3);
    MEM32(esp + 0x10) = edx;
    MEM8(edx) = LO8(ebx);
    goto loc_00216B4C;

loc_00216B1A: ;
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(esi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test esi, esi (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00216B28; /* je: equal / zero */

loc_00216B1E: ;
    edx = eax;
    _cf = 0; /* logical op clears CF */
    edx = edx & 1;
    if (1) _cf = (int)(((eax) >> ((1) - 1)) & 1);
    eax = eax >> 1;
    esi--;
    goto loc_00216B39;

loc_00216B28: ;
    edx = MEM32(edi);
    eax = edx;
    _cf = (int)((((uint64_t)(edi) + (uint64_t)(4)) >> 32) & 1);
    edi = edi + 4;
    if (1) _cf = (int)(((eax) >> ((1) - 1)) & 1);
    eax = eax >> 1;
    esi = 0x1F;
    _cf = 0; /* logical op clears CF */
    edx = edx & 1;

loc_00216B39: ;
    _cf = (int)((edx) != 0);
    edx = (uint32_t)(-(int32_t)edx);
    edx = _cf ? 0xFFFFFFFF : 0; /* sbb self (CF extend) */
    _cf = 0; /* logical op clears CF */
    edx = edx & 0xFFFE;
    ebx = ZX8(LO8(ecx));
    edx++;
    MEM16(esp + ebx * 2 + 0x30) = LO16(edx);

loc_00216B4C: ;
    SET_LO8(ecx, LO8(ecx) + 1);
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(esi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test esi, esi (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00216B5C; /* je: equal / zero */

loc_00216B52: ;
    edx = eax;
    _cf = 0; /* logical op clears CF */
    edx = edx & 1;
    if (1) _cf = (int)(((eax) >> ((1) - 1)) & 1);
    eax = eax >> 1;
    esi--;
    goto loc_00216B6D;

loc_00216B5C: ;
    edx = MEM32(edi);
    eax = edx;
    _cf = (int)((((uint64_t)(edi) + (uint64_t)(4)) >> 32) & 1);
    edi = edi + 4;
    if (1) _cf = (int)(((eax) >> ((1) - 1)) & 1);
    eax = eax >> 1;
    esi = 0x1F;
    _cf = 0; /* logical op clears CF */
    edx = edx & 1;

loc_00216B6D: ;
    _fa = (uint32_t)(edx) & 0xFFFFFFFFu; _fb = (uint32_t)(edx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test edx, edx (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00216B86; /* je: equal / zero */

loc_00216B71: ;
    edx = MEM32(esp + 0x10);
    SET_LO8(ebx, LO8(ecx));
    edx--;
    if (2) _cf = (int)(((LO8(ebx)) >> (8 - (2))) & 1);
    SET_LO8(ebx, LO8(ebx) << 2);
    _cf = (int)((((uint64_t)(LO8(ebx)) + (uint64_t)(3)) >> 8) & 1);
    SET_LO8(ebx, LO8(ebx) + 3);
    MEM32(esp + 0x10) = edx;
    MEM8(edx) = LO8(ebx);
    goto loc_00216BB8;

loc_00216B86: ;
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(esi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test esi, esi (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00216B94; /* je: equal / zero */

loc_00216B8A: ;
    edx = eax;
    _cf = 0; /* logical op clears CF */
    edx = edx & 1;
    if (1) _cf = (int)(((eax) >> ((1) - 1)) & 1);
    eax = eax >> 1;
    esi--;
    goto loc_00216BA5;

loc_00216B94: ;
    edx = MEM32(edi);
    eax = edx;
    _cf = (int)((((uint64_t)(edi) + (uint64_t)(4)) >> 32) & 1);
    edi = edi + 4;
    if (1) _cf = (int)(((eax) >> ((1) - 1)) & 1);
    eax = eax >> 1;
    esi = 0x1F;
    _cf = 0; /* logical op clears CF */
    edx = edx & 1;

loc_00216BA5: ;
    _cf = (int)((edx) != 0);
    edx = (uint32_t)(-(int32_t)edx);
    edx = _cf ? 0xFFFFFFFF : 0; /* sbb self (CF extend) */
    _cf = 0; /* logical op clears CF */
    edx = edx & 0xFFFE;
    ebx = ZX8(LO8(ecx));
    edx++;
    MEM16(esp + ebx * 2 + 0x30) = LO16(edx);

loc_00216BB8: ;
    SET_LO8(ecx, LO8(ecx) + 1);
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(esi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test esi, esi (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00216BC8; /* je: equal / zero */

loc_00216BBE: ;
    edx = eax;
    _cf = 0; /* logical op clears CF */
    edx = edx & 1;
    if (1) _cf = (int)(((eax) >> ((1) - 1)) & 1);
    eax = eax >> 1;
    esi--;
    goto loc_00216BD9;

loc_00216BC8: ;
    edx = MEM32(edi);
    eax = edx;
    _cf = (int)((((uint64_t)(edi) + (uint64_t)(4)) >> 32) & 1);
    edi = edi + 4;
    if (1) _cf = (int)(((eax) >> ((1) - 1)) & 1);
    eax = eax >> 1;
    esi = 0x1F;
    _cf = 0; /* logical op clears CF */
    edx = edx & 1;

loc_00216BD9: ;
    _fa = (uint32_t)(edx) & 0xFFFFFFFFu; _fb = (uint32_t)(edx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test edx, edx (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00216BF2; /* je: equal / zero */

loc_00216BDD: ;
    edx = MEM32(esp + 0x10);
    SET_LO8(ebx, LO8(ecx));
    edx--;
    if (2) _cf = (int)(((LO8(ebx)) >> (8 - (2))) & 1);
    SET_LO8(ebx, LO8(ebx) << 2);
    _cf = (int)((((uint64_t)(LO8(ebx)) + (uint64_t)(3)) >> 8) & 1);
    SET_LO8(ebx, LO8(ebx) + 3);
    MEM32(esp + 0x10) = edx;
    MEM8(edx) = LO8(ebx);
    goto loc_00216C24;

loc_00216BF2: ;
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(esi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test esi, esi (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00216C00; /* je: equal / zero */

loc_00216BF6: ;
    edx = eax;
    _cf = 0; /* logical op clears CF */
    edx = edx & 1;
    if (1) _cf = (int)(((eax) >> ((1) - 1)) & 1);
    eax = eax >> 1;
    esi--;
    goto loc_00216C11;

loc_00216C00: ;
    edx = MEM32(edi);
    eax = edx;
    _cf = (int)((((uint64_t)(edi) + (uint64_t)(4)) >> 32) & 1);
    edi = edi + 4;
    if (1) _cf = (int)(((eax) >> ((1) - 1)) & 1);
    eax = eax >> 1;
    esi = 0x1F;
    _cf = 0; /* logical op clears CF */
    edx = edx & 1;

loc_00216C11: ;
    _cf = (int)((edx) != 0);
    edx = (uint32_t)(-(int32_t)edx);
    edx = _cf ? 0xFFFFFFFF : 0; /* sbb self (CF extend) */
    _cf = 0; /* logical op clears CF */
    edx = edx & 0xFFFE;
    ebx = ZX8(LO8(ecx));
    edx++;
    MEM16(esp + ebx * 2 + 0x30) = LO16(edx);

loc_00216C24: ;
    SET_LO8(ecx, LO8(ecx) + 1);
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(esi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test esi, esi (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00216C34; /* je: equal / zero */

loc_00216C2A: ;
    edx = eax;
    _cf = 0; /* logical op clears CF */
    edx = edx & 1;
    if (1) _cf = (int)(((eax) >> ((1) - 1)) & 1);
    eax = eax >> 1;
    esi--;
    goto loc_00216C45;

loc_00216C34: ;
    edx = MEM32(edi);
    eax = edx;
    _cf = (int)((((uint64_t)(edi) + (uint64_t)(4)) >> 32) & 1);
    edi = edi + 4;
    if (1) _cf = (int)(((eax) >> ((1) - 1)) & 1);
    eax = eax >> 1;
    esi = 0x1F;
    _cf = 0; /* logical op clears CF */
    edx = edx & 1;

loc_00216C45: ;
    _fa = (uint32_t)(edx) & 0xFFFFFFFFu; _fb = (uint32_t)(edx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test edx, edx (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00216C60; /* je: equal / zero */

loc_00216C49: ;
    edx = MEM32(esp + 0x10);
    ebx = MEM32(esp + 0x20);
    edx--;
    if (2) _cf = (int)(((LO8(ecx)) >> (8 - (2))) & 1);
    SET_LO8(ecx, LO8(ecx) << 2);
    _cf = (int)((((uint64_t)(LO8(ecx)) + (uint64_t)(3)) >> 8) & 1);
    SET_LO8(ecx, LO8(ecx) + 3);
    MEM32(esp + 0x10) = edx;
    MEM8(edx) = LO8(ecx);
    goto loc_00216CD2;

loc_00216C60: ;
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(esi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test esi, esi (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00216C6E; /* je: equal / zero */

loc_00216C64: ;
    edx = eax;
    _cf = 0; /* logical op clears CF */
    edx = edx & 1;
    if (1) _cf = (int)(((eax) >> ((1) - 1)) & 1);
    eax = eax >> 1;
    esi--;
    goto loc_00216C7F;

loc_00216C6E: ;
    edx = MEM32(edi);
    eax = edx;
    _cf = (int)((((uint64_t)(edi) + (uint64_t)(4)) >> 32) & 1);
    edi = edi + 4;
    if (1) _cf = (int)(((eax) >> ((1) - 1)) & 1);
    eax = eax >> 1;
    esi = 0x1F;
    _cf = 0; /* logical op clears CF */
    edx = edx & 1;

loc_00216C7F: ;
    ebx = MEM32(esp + 0x20);
    _cf = (int)((edx) != 0);
    edx = (uint32_t)(-(int32_t)edx);
    edx = _cf ? 0xFFFFFFFF : 0; /* sbb self (CF extend) */
    _cf = 0; /* logical op clears CF */
    edx = edx & 0xFFFE;
    ecx = ZX8(LO8(ecx));
    edx++;
    MEM16(esp + ecx * 2 + 0x30) = LO16(edx);
    goto loc_00216CD2;

loc_00216C98: ;
    if (2) _cf = (int)(((LO8(ecx)) >> ((2) - 1)) & 1);
    SET_LO8(ecx, LO8(ecx) >> 2);
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(esi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test esi, esi (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00216CA9; /* je: equal / zero */

loc_00216C9F: ;
    edx = eax;
    _cf = 0; /* logical op clears CF */
    edx = edx & 1;
    if (1) _cf = (int)(((eax) >> ((1) - 1)) & 1);
    eax = eax >> 1;
    esi--;
    goto loc_00216CBA;

loc_00216CA9: ;
    edx = MEM32(edi);
    eax = edx;
    _cf = (int)((((uint64_t)(edi) + (uint64_t)(4)) >> 32) & 1);
    edi = edi + 4;
    if (1) _cf = (int)(((eax) >> ((1) - 1)) & 1);
    eax = eax >> 1;
    esi = 0x1F;
    _cf = 0; /* logical op clears CF */
    edx = edx & 1;

loc_00216CBA: ;
    _cf = (int)((edx) != 0);
    edx = (uint32_t)(-(int32_t)edx);
    edx = _cf ? 0xFFFFFFFF : 0; /* sbb self (CF extend) */
    _cf = 0; /* logical op clears CF */
    edx = edx & 0xFFFE;
    ecx = ZX8(LO8(ecx));
    edx++;
    MEM16(esp + ecx * 2 + 0x30) = LO16(edx);
    MEM8(ebp) = 0;

loc_00216CD1: ;
    ebp++;

loc_00216CD2: ;
    _fa = (uint32_t)(ebp) & 0xFFFFFFFFu; _fb = (uint32_t)(ebx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp ebp, ebx (32-bit) */
    if (CMP_B(_fa, _fb)) goto loc_00216A50; /* jb: below (unsigned <) */

loc_00216CDA: ;
    ecx = MEM32(esp + 0x13C);
    MEM32(ecx + 4) = edi;
    MEM32(ecx) = eax;
    eax = MEM32(esp + 0x138);
    MEM32(ecx + 8) = esi;
    SET_LO16(edx, MEM16(esp + 0x32));
    ecx = MEM32(esp + 0x38);
    MEM16(eax + 2) = LO16(edx);
    edx = MEM32(esp + 0x40);
    MEM32(eax + 4) = ecx;
    ecx = MEM32(esp + 0x48);
    MEM32(eax + 8) = edx;
    edx = MEM32(esp + 0x34);
    MEM32(eax + 0xC) = ecx;
    ecx = MEM32(esp + 0x3C);
    MEM32(eax + 0x10) = edx;
    edx = MEM32(esp + 0x44);
    MEM32(eax + 0x14) = ecx;
    ecx = MEM32(esp + 0x4C);
    MEM32(eax + 0x18) = edx;
    edx = MEM32(esp + 0x60);
    MEM32(eax + 0x1C) = ecx;
    ecx = MEM32(esp + 0x88);
    MEM32(eax + 0x20) = edx;
    edx = MEM32(esp + 0x50);
    MEM32(eax + 0x24) = ecx;
    ecx = MEM32(esp + 0x58);
    MEM32(eax + 0x28) = edx;
    edx = MEM32(esp + 0x64);
    MEM32(eax + 0x2C) = ecx;
    ecx = MEM32(esp + 0x8C);
    MEM32(eax + 0x30) = edx;
    edx = MEM32(esp + 0x54);
    MEM32(eax + 0x34) = ecx;
    ecx = MEM32(esp + 0x5C);
    MEM32(eax + 0x38) = edx;
    edx = MEM32(esp + 0x68);
    MEM32(eax + 0x3C) = ecx;
    ecx = MEM32(esp + 0x70);
    MEM32(eax + 0x40) = edx;
    edx = MEM32(esp + 0x90);
    MEM32(eax + 0x44) = ecx;
    ecx = MEM32(esp + 0x98);
    MEM32(eax + 0x48) = edx;
    edx = MEM32(esp + 0x6C);
    MEM32(eax + 0x4C) = ecx;
    ecx = MEM32(esp + 0x74);
    MEM32(eax + 0x50) = edx;
    edx = MEM32(esp + 0x94);
    MEM32(eax + 0x54) = ecx;
    ecx = MEM32(esp + 0x9C);
    MEM32(eax + 0x58) = edx;
    edx = MEM32(esp + 0x78);
    MEM32(eax + 0x5C) = ecx;
    ecx = MEM32(esp + 0x80);
    MEM32(eax + 0x60) = edx;
    edx = MEM32(esp + 0xA0);
    MEM32(eax + 0x64) = ecx;
    ecx = MEM32(esp + 0xA8);
    POP32(esp, edi);
    MEM32(eax + 0x68) = edx;
    edx = MEM32(esp + 0x78);
    MEM32(eax + 0x6C) = ecx;
    ecx = MEM32(esp + 0x80);
    POP32(esp, esi);
    MEM32(eax + 0x70) = edx;
    edx = MEM32(esp + 0x9C);
    MEM32(eax + 0x74) = ecx;
    ecx = MEM32(esp + 0xA4);
    POP32(esp, ebp);
    MEM32(eax + 0x78) = edx;
    MEM32(eax + 0x7C) = ecx;
    POP32(esp, ebx);
    _cf = (int)((((uint64_t)(esp) + (uint64_t)(0x124)) >> 32) & 1);
    esp = esp + 0x124;
    esp += 12; return; /* ret 8 */

}

/**
 * sub_00216E30
 * Original: 0x00216E30 - 0x002172F7 (1223 bytes, 417 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00216E30(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_00216E30: ;
    esp = esp - 0xE4;
    PUSH32(esp, ebx);
    PUSH32(esp, ebp);
    ebp = MEM32(esp + 0xF4);
    eax = MEM32(ebp);
    PUSH32(esp, esi);
    esi = MEM32(ebp + 8);
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(3) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp esi, 3 (32-bit) */
    PUSH32(esp, edi);
    edi = MEM32(ebp + 4);
    MEM32(esp + 0x14) = 0;
    if (CMP_B(_fa, _fb)) goto loc_00216E64; /* jb: below (unsigned <) */

loc_00216E57: ;
    SET_LO8(edx, LO8(eax));
    SET_LO8(edx, LO8(edx) & 7);
    eax = eax >> 3;
    esi = esi - 3;
    goto loc_00216E82;

loc_00216E64: ;
    ebx = MEM32(edi);
    ecx = esi;
    SET_LO8(edx, LO8(ebx));
    SET_LO8(edx, LO8(edx) << LO8(ecx));
    ecx = 3;
    ecx = ecx - esi;
    ebx = ebx >> LO8(ecx);
    SET_LO8(edx, LO8(edx) | LO8(eax));
    SET_LO8(edx, LO8(edx) & 7);
    esi = esi + 0x1D;
    eax = ebx;
    edi = edi + 4;

loc_00216E82: ;
    ecx = esp + 0xB4;
    MEM32(esp + 0x20) = ecx;
    SET_LO8(edx, LO8(edx) + 1);
    ecx = esp + 0xB8;
    MEM32(esp + 0x28) = ecx;
    ecx = 0; /* xor self */
    SET_LO8(ecx, LO8(edx));
    SET_LO8(ebx, 1);
    MEM8(esp + 0xB4) = 0x10;
    MEM8(esp + 0xB5) = 0x60;
    MEM8(esp + 0xB6) = 0xB0;
    MEM8(esp + 0xB7) = 2;
    MEM32(esp + 0x18) = 0;
    ecx--;
    SET_LO8(ebx, LO8(ebx) << LO8(ecx));
    _fa = (uint32_t)(LO8(edx)) & 0xFFu; _fb = (uint32_t)(LO8(edx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(edx), LO8(edx) (8-bit) */
    MEM8(esp + 0x1F) = LO8(edx);
    MEM8(esp + 0x13) = LO8(ebx);
    if (CMP_BE(_fa & _fb, 0)) goto loc_002172E3; /* jbe: below or equal (unsigned <=) */

loc_00216EDB: ;
    goto loc_00216EE1;

loc_00216EDD: ;
    SET_LO8(ebx, MEM8(esp + 0x13));

loc_00216EE1: ;
    ecx = MEM32(esp + 0x18);
    ebp = 0; /* xor self */
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, ecx (32-bit) */
    if (CMP_LE(_fas & _fbs, 0)) goto loc_00216F4E; /* jle: less or equal (signed <=) */

loc_00216EEB: ;
    goto loc_00216EF0;

    /* nop */

loc_00216EF0: ;
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(esi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test esi, esi (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00216EFE; /* je: equal / zero */

loc_00216EF4: ;
    ecx = eax;
    ecx = ecx & 1;
    eax = eax >> 1;
    esi--;
    goto loc_00216F0F;

loc_00216EFE: ;
    ecx = MEM32(edi);
    eax = ecx;
    edi = edi + 4;
    eax = eax >> 1;
    esi = 0x1F;
    ecx = ecx & 1;

loc_00216F0F: ;
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, ecx (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00216F45; /* je: equal / zero */

loc_00216F13: ;
    edx = ZX8(MEM8(esp + ebp + 0x30));
    ecx = MEM32(esp + 0xF8);
    ecx = ecx + edx;
    _fa = (uint32_t)(MEM8(ecx)) & 0xFFu; _fb = (uint32_t)(0) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(ecx), 0 (8-bit) */
    edx = SX8(LO8(ebx));
    if (CMP_GE(_fas, _fbs)) goto loc_00216F2B; /* jge: greater or equal (signed >=) */

loc_00216F29: ;
    edx = (uint32_t)(-(int32_t)edx);

loc_00216F2B: ;
    MEM8(ecx) = MEM8(ecx) + LO8(edx);
    ecx = MEM32(esp + 0x14);
    edx = ecx;
    ecx++;
    MEM32(esp + 0x14) = ecx;
    _fa = (uint32_t)(edx) & 0xFFFFFFFFu; _fb = (uint32_t)(MEM32(esp + 0x100)) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edx, MEM32(esp + 0x100) (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_002172DC; /* je: equal / zero */

loc_00216F45: ;
    ecx = MEM32(esp + 0x18);
    ebp++;
    _fa = (uint32_t)(ebp) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp ebp, ecx (32-bit) */
    if (CMP_L(_fas, _fbs)) goto loc_00216EF0; /* jl: less (signed <) */

loc_00216F4E: ;
    ebp = MEM32(esp + 0x20);
    _fa = (uint32_t)(ebp) & 0xFFFFFFFFu; _fb = (uint32_t)(MEM32(esp + 0x28)) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp ebp, MEM32(esp + 0x28) (32-bit) */
    ebx = ebp;
    MEM32(esp + 0x24) = ebx;
    if (CMP_AE(_fa, _fb)) goto loc_002172C2; /* jae: above or equal (unsigned >=) */

loc_00216F62: ;
    SET_LO8(ecx, MEM8(ebx));
    _fa = (uint32_t)(LO8(ecx)) & 0xFFu; _fb = (uint32_t)(LO8(ecx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(ecx), LO8(ecx) (8-bit) */
    MEM8(esp + 0x2C) = LO8(ecx);
    if (TEST_Z(_fa, _fb)) goto loc_002172B3; /* je: equal / zero */

loc_00216F70: ;
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(esi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test esi, esi (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00216F7E; /* je: equal / zero */

loc_00216F74: ;
    edx = eax;
    edx = edx & 1;
    eax = eax >> 1;
    esi--;
    goto loc_00216F8F;

loc_00216F7E: ;
    edx = MEM32(edi);
    eax = edx;
    edi = edi + 4;
    eax = eax >> 1;
    esi = 0x1F;
    edx = edx & 1;

loc_00216F8F: ;
    _fa = (uint32_t)(edx) & 0xFFFFFFFFu; _fb = (uint32_t)(edx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test edx, edx (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_002172B3; /* je: equal / zero */

loc_00216F97: ;
    edx = MEM32(esp + 0x2C);
    edx = edx & 3;
    _fa = (uint32_t)(edx) & 0xFFFFFFFFu; _fb = (uint32_t)(3) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edx, 3 (32-bit) */
    if (CMP_A(_fa, _fb)) goto loc_002172B3; /* ja: above (unsigned >) */

loc_00216FA7: ;
    { uint32_t _jt = MEM32(edx * 4 + 0x2172F8); /* switch: 4 entries, 4 targets */
    if (_jt == 0x00216FAEu) goto loc_00216FAE;
    if (_jt == 0x00216FBDu) goto loc_00216FBD;
    if (_jt == 0x00216FF1u) goto loc_00216FF1;
    if (_jt == 0x0021724Fu) goto loc_0021724F;
    g_seh_ebp = ebp; RECOMP_ITAIL(_jt); return; }

loc_00216FAE: ;
    SET_LO8(ecx, LO8(ecx) >> 2);
    SET_LO8(edx, LO8(ecx));
    SET_LO8(edx, LO8(edx) << 2);
    SET_LO8(edx, LO8(edx) + 0x11);
    MEM8(ebx) = LO8(edx);
    goto loc_00216FFC;

loc_00216FBD: ;
    SET_LO8(ecx, LO8(ecx) >> 2);
    SET_LO8(ecx, LO8(ecx) << 2);
    SET_LO8(edx, LO8(ecx));
    SET_LO8(edx, LO8(edx) + 2);
    MEM8(ebx) = LO8(edx);
    edx = MEM32(esp + 0x28);
    SET_LO8(ebx, LO8(ecx));
    SET_LO8(ebx, LO8(ebx) + 0x12);
    MEM8(edx) = LO8(ebx);
    SET_LO8(ebx, LO8(ecx));
    SET_LO8(ebx, LO8(ebx) + 0x22);
    edx++;
    MEM8(edx) = LO8(ebx);
    ebx = MEM32(esp + 0x24);
    edx++;
    SET_LO8(ecx, LO8(ecx) + 0x32);
    MEM8(edx) = LO8(ecx);
    edx++;
    MEM32(esp + 0x28) = edx;
    goto loc_002172B8;

loc_00216FF1: ;
    SET_LO8(ecx, LO8(ecx) >> 2);
    MEM8(ebx) = 0;
    ebx++;
    MEM32(esp + 0x24) = ebx;

loc_00216FFC: ;
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(esi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test esi, esi (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0021700A; /* je: equal / zero */

loc_00217000: ;
    edx = eax;
    edx = edx & 1;
    eax = eax >> 1;
    esi--;
    goto loc_0021701B;

loc_0021700A: ;
    edx = MEM32(edi);
    eax = edx;
    edi = edi + 4;
    eax = eax >> 1;
    esi = 0x1F;
    edx = edx & 1;

loc_0021701B: ;
    _fa = (uint32_t)(edx) & 0xFFFFFFFFu; _fb = (uint32_t)(edx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test edx, edx (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00217038; /* je: equal / zero */

loc_0021701F: ;
    ebx = MEM32(esp + 0xF8);
    SET_LO8(edx, LO8(ecx));
    ebp--;
    SET_LO8(edx, LO8(edx) << 2);
    SET_LO8(edx, LO8(edx) + 3);
    MEM32(esp + 0x20) = ebp;
    MEM8(ebp) = LO8(edx);
    goto loc_00217098;

loc_00217038: ;
    edx = MEM32(esp + 0x18);
    MEM8(esp + edx + 0x30) = LO8(ecx);
    edx++;
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(esi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test esi, esi (32-bit) */
    MEM32(esp + 0x18) = edx;
    if (TEST_Z(_fa, _fb)) goto loc_00217053; /* je: equal / zero */

loc_00217049: ;
    edx = eax;
    edx = edx & 1;
    eax = eax >> 1;
    esi--;
    goto loc_00217064;

loc_00217053: ;
    edx = MEM32(edi);
    eax = edx;
    edi = edi + 4;
    eax = eax >> 1;
    esi = 0x1F;
    edx = edx & 1;

loc_00217064: ;
    _fa = (uint32_t)(edx) & 0xFFFFFFFFu; _fb = (uint32_t)(edx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test edx, edx (32-bit) */
    edx = (uint32_t)(int32_t)SMEM8(esp + 0x13);
    if (TEST_Z(_fa, _fb)) goto loc_0021706F; /* je: equal / zero */

loc_0021706D: ;
    edx = (uint32_t)(-(int32_t)edx);

loc_0021706F: ;
    ebx = MEM32(esp + 0xF8);
    ebp = ZX8(LO8(ecx));
    MEM8(ebx + ebp) = LO8(edx);
    edx = MEM32(esp + 0x14);
    ebp = edx;
    edx++;
    MEM32(esp + 0x14) = edx;
    _fa = (uint32_t)(ebp) & 0xFFFFFFFFu; _fb = (uint32_t)(MEM32(esp + 0x100)) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp ebp, MEM32(esp + 0x100) (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_002172DC; /* je: equal / zero */

loc_00217094: ;
    ebp = MEM32(esp + 0x20);

loc_00217098: ;
    SET_LO8(ecx, LO8(ecx) + 1);
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(esi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test esi, esi (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_002170A8; /* je: equal / zero */

loc_0021709E: ;
    edx = eax;
    edx = edx & 1;
    eax = eax >> 1;
    esi--;
    goto loc_002170B9;

loc_002170A8: ;
    edx = MEM32(edi);
    eax = edx;
    edi = edi + 4;
    eax = eax >> 1;
    esi = 0x1F;
    edx = edx & 1;

loc_002170B9: ;
    _fa = (uint32_t)(edx) & 0xFFFFFFFFu; _fb = (uint32_t)(edx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test edx, edx (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_002170CF; /* je: equal / zero */

loc_002170BD: ;
    SET_LO8(edx, LO8(ecx));
    ebp--;
    SET_LO8(edx, LO8(edx) << 2);
    SET_LO8(edx, LO8(edx) + 3);
    MEM32(esp + 0x20) = ebp;
    MEM8(ebp) = LO8(edx);
    goto loc_00217128;

loc_002170CF: ;
    edx = MEM32(esp + 0x18);
    MEM8(esp + edx + 0x30) = LO8(ecx);
    edx++;
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(esi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test esi, esi (32-bit) */
    MEM32(esp + 0x18) = edx;
    if (TEST_Z(_fa, _fb)) goto loc_002170EA; /* je: equal / zero */

loc_002170E0: ;
    edx = eax;
    edx = edx & 1;
    eax = eax >> 1;
    esi--;
    goto loc_002170FB;

loc_002170EA: ;
    edx = MEM32(edi);
    eax = edx;
    edi = edi + 4;
    eax = eax >> 1;
    esi = 0x1F;
    edx = edx & 1;

loc_002170FB: ;
    _fa = (uint32_t)(edx) & 0xFFFFFFFFu; _fb = (uint32_t)(edx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test edx, edx (32-bit) */
    edx = (uint32_t)(int32_t)SMEM8(esp + 0x13);
    if (TEST_Z(_fa, _fb)) goto loc_00217106; /* je: equal / zero */

loc_00217104: ;
    edx = (uint32_t)(-(int32_t)edx);

loc_00217106: ;
    ebp = ZX8(LO8(ecx));
    MEM8(ebx + ebp) = LO8(edx);
    edx = MEM32(esp + 0x14);
    ebp = edx;
    edx++;
    MEM32(esp + 0x14) = edx;
    _fa = (uint32_t)(ebp) & 0xFFFFFFFFu; _fb = (uint32_t)(MEM32(esp + 0x100)) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp ebp, MEM32(esp + 0x100) (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_002172DC; /* je: equal / zero */

loc_00217124: ;
    ebp = MEM32(esp + 0x20);

loc_00217128: ;
    SET_LO8(ecx, LO8(ecx) + 1);
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(esi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test esi, esi (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00217138; /* je: equal / zero */

loc_0021712E: ;
    edx = eax;
    edx = edx & 1;
    eax = eax >> 1;
    esi--;
    goto loc_00217149;

loc_00217138: ;
    edx = MEM32(edi);
    eax = edx;
    edi = edi + 4;
    eax = eax >> 1;
    esi = 0x1F;
    edx = edx & 1;

loc_00217149: ;
    _fa = (uint32_t)(edx) & 0xFFFFFFFFu; _fb = (uint32_t)(edx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test edx, edx (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0021715F; /* je: equal / zero */

loc_0021714D: ;
    SET_LO8(edx, LO8(ecx));
    ebp--;
    SET_LO8(edx, LO8(edx) << 2);
    SET_LO8(edx, LO8(edx) + 3);
    MEM32(esp + 0x20) = ebp;
    MEM8(ebp) = LO8(edx);
    goto loc_002171B8;

loc_0021715F: ;
    edx = MEM32(esp + 0x18);
    MEM8(esp + edx + 0x30) = LO8(ecx);
    edx++;
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(esi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test esi, esi (32-bit) */
    MEM32(esp + 0x18) = edx;
    if (TEST_Z(_fa, _fb)) goto loc_0021717A; /* je: equal / zero */

loc_00217170: ;
    edx = eax;
    edx = edx & 1;
    eax = eax >> 1;
    esi--;
    goto loc_0021718B;

loc_0021717A: ;
    edx = MEM32(edi);
    eax = edx;
    edi = edi + 4;
    eax = eax >> 1;
    esi = 0x1F;
    edx = edx & 1;

loc_0021718B: ;
    _fa = (uint32_t)(edx) & 0xFFFFFFFFu; _fb = (uint32_t)(edx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test edx, edx (32-bit) */
    edx = (uint32_t)(int32_t)SMEM8(esp + 0x13);
    if (TEST_Z(_fa, _fb)) goto loc_00217196; /* je: equal / zero */

loc_00217194: ;
    edx = (uint32_t)(-(int32_t)edx);

loc_00217196: ;
    ebp = ZX8(LO8(ecx));
    MEM8(ebx + ebp) = LO8(edx);
    edx = MEM32(esp + 0x14);
    ebp = edx;
    edx++;
    MEM32(esp + 0x14) = edx;
    _fa = (uint32_t)(ebp) & 0xFFFFFFFFu; _fb = (uint32_t)(MEM32(esp + 0x100)) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp ebp, MEM32(esp + 0x100) (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_002172DC; /* je: equal / zero */

loc_002171B4: ;
    ebp = MEM32(esp + 0x20);

loc_002171B8: ;
    SET_LO8(ecx, LO8(ecx) + 1);
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(esi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test esi, esi (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_002171C8; /* je: equal / zero */

loc_002171BE: ;
    edx = eax;
    edx = edx & 1;
    eax = eax >> 1;
    esi--;
    goto loc_002171D9;

loc_002171C8: ;
    edx = MEM32(edi);
    eax = edx;
    edi = edi + 4;
    eax = eax >> 1;
    esi = 0x1F;
    edx = edx & 1;

loc_002171D9: ;
    _fa = (uint32_t)(edx) & 0xFFFFFFFFu; _fb = (uint32_t)(edx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test edx, edx (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_002171F4; /* je: equal / zero */

loc_002171DD: ;
    ebx = MEM32(esp + 0x24);
    ebp--;
    SET_LO8(ecx, LO8(ecx) << 2);
    SET_LO8(ecx, LO8(ecx) + 3);
    MEM32(esp + 0x20) = ebp;
    MEM8(ebp) = LO8(ecx);
    goto loc_002172B8;

loc_002171F4: ;
    edx = MEM32(esp + 0x18);
    MEM8(esp + edx + 0x30) = LO8(ecx);
    edx++;
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(esi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test esi, esi (32-bit) */
    MEM32(esp + 0x18) = edx;
    if (TEST_Z(_fa, _fb)) goto loc_0021720F; /* je: equal / zero */

loc_00217205: ;
    edx = eax;
    edx = edx & 1;
    eax = eax >> 1;
    esi--;
    goto loc_00217220;

loc_0021720F: ;
    edx = MEM32(edi);
    eax = edx;
    edi = edi + 4;
    eax = eax >> 1;
    esi = 0x1F;
    edx = edx & 1;

loc_00217220: ;
    _fa = (uint32_t)(edx) & 0xFFFFFFFFu; _fb = (uint32_t)(edx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test edx, edx (32-bit) */
    edx = (uint32_t)(int32_t)SMEM8(esp + 0x13);
    if (TEST_Z(_fa, _fb)) goto loc_0021722B; /* je: equal / zero */

loc_00217229: ;
    edx = (uint32_t)(-(int32_t)edx);

loc_0021722B: ;
    ecx = ZX8(LO8(ecx));
    MEM8(ecx + ebx) = LO8(edx);
    ecx = MEM32(esp + 0x14);
    edx = ecx;
    ecx++;
    MEM32(esp + 0x14) = ecx;
    _fa = (uint32_t)(edx) & 0xFFFFFFFFu; _fb = (uint32_t)(MEM32(esp + 0x100)) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edx, MEM32(esp + 0x100) (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_002172DC; /* je: equal / zero */

loc_00217249: ;
    ebx = MEM32(esp + 0x24);
    goto loc_002172B8;

loc_0021724F: ;
    edx = MEM32(esp + 0x18);
    SET_LO8(ecx, LO8(ecx) >> 2);
    MEM8(esp + edx + 0x30) = LO8(ecx);
    edx++;
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(esi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test esi, esi (32-bit) */
    MEM32(esp + 0x18) = edx;
    if (TEST_Z(_fa, _fb)) goto loc_0021726D; /* je: equal / zero */

loc_00217263: ;
    edx = eax;
    edx = edx & 1;
    eax = eax >> 1;
    esi--;
    goto loc_0021727E;

loc_0021726D: ;
    edx = MEM32(edi);
    eax = edx;
    edi = edi + 4;
    eax = eax >> 1;
    esi = 0x1F;
    edx = edx & 1;

loc_0021727E: ;
    _fa = (uint32_t)(edx) & 0xFFFFFFFFu; _fb = (uint32_t)(edx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test edx, edx (32-bit) */
    edx = (uint32_t)(int32_t)SMEM8(esp + 0x13);
    if (TEST_Z(_fa, _fb)) goto loc_00217289; /* je: equal / zero */

loc_00217287: ;
    edx = (uint32_t)(-(int32_t)edx);

loc_00217289: ;
    ebx = MEM32(esp + 0xF8);
    ecx = ZX8(LO8(ecx));
    MEM8(ecx + ebx) = LO8(edx);
    ecx = MEM32(esp + 0x14);
    edx = ecx;
    ecx++;
    MEM32(esp + 0x14) = ecx;
    _fa = (uint32_t)(edx) & 0xFFFFFFFFu; _fb = (uint32_t)(MEM32(esp + 0x100)) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edx, MEM32(esp + 0x100) (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_002172DC; /* je: equal / zero */

loc_002172AA: ;
    ecx = MEM32(esp + 0x24);
    MEM8(ecx) = 0;
    ebx = ecx;

loc_002172B3: ;
    ebx++;
    MEM32(esp + 0x24) = ebx;

loc_002172B8: ;
    _fa = (uint32_t)(ebx) & 0xFFFFFFFFu; _fb = (uint32_t)(MEM32(esp + 0x28)) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp ebx, MEM32(esp + 0x28) (32-bit) */
    if (CMP_B(_fa, _fb)) goto loc_00216F62; /* jb: below (unsigned <) */

loc_002172C2: ;
    SET_LO8(edx, MEM8(esp + 0x13));
    SET_LO8(ecx, MEM8(esp + 0x1F));
    SET_LO8(edx, (uint32_t)((int32_t)LO8(edx) >> 1));
    SET_LO8(ecx, LO8(ecx) - 1);
    MEM8(esp + 0x13) = LO8(edx);
    MEM8(esp + 0x1F) = LO8(ecx);
    if ((LO8(ecx) != 0)) goto loc_00216EDD; /* jne: not equal / not zero */

loc_002172DC: ;
    ebp = MEM32(esp + 0xFC);

loc_002172E3: ;
    MEM32(ebp + 4) = edi;
    POP32(esp, edi);
    MEM32(ebp + 8) = esi;
    POP32(esp, esi);
    MEM32(ebp) = eax;
    POP32(esp, ebp);
    POP32(esp, ebx);
    esp = esp + 0xE4;
    esp += 4; return; /* ret */

}

/**
 * sub_00217310
 * Original: 0x00217310 - 0x0021763D (813 bytes, 268 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00217310(void)
{

loc_00217310: ;
    esp = esp - 0x40;
    PUSH32(esp, ebx);
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    eax = 0; /* xor self */
    MEM32(esp + 0xC) = eax;
    MEM32(esp + 0x10) = eax;
    ecx = 0xE;
    edi = esp + 0x14;
    { uint32_t _i; for (_i = 0; _i < ecx; _i++) MEM32(edi + _i*4) = eax; }
    edi += ecx * 4; ecx = 0; /* rep stosd */
    eax = MEM32(esp + 0x5C);
    ecx = MEM32(esp + 0x58);
    PUSH32(esp, eax);
    PUSH32(esp, ecx);
    edx = esp + 0x14;
    PUSH32(esp, edx);
    PUSH32(esp, 0x0021733Fu); sub_00216E30(); /* call 0x00216E30 */

loc_0021733F: ;
    eax = MEM32(esp + 0x6C);
    SET_LO8(edx, MEM8(eax));
    esi = MEM32(esp + 0x5C);
    ecx = MEM32(esp + 0x18);
    SET_LO8(edx, LO8(edx) + LO8(ecx));
    MEM8(esi) = LO8(edx);
    SET_LO8(edx, MEM8(eax + 1));
    SET_LO8(edx, LO8(edx) + HI8(ecx));
    ecx = MEM32(esp + 0x1C);
    MEM8(esi + 1) = LO8(edx);
    SET_LO8(edx, MEM8(eax + 2));
    SET_LO8(edx, LO8(edx) + LO8(ecx));
    MEM8(esi + 2) = LO8(edx);
    SET_LO8(edx, MEM8(eax + 3));
    SET_LO8(ebx, MEM8(esp + 0x21));
    SET_LO8(edx, LO8(edx) + HI8(ecx));
    MEM8(esi + 3) = LO8(edx);
    SET_LO8(ecx, MEM8(eax + 4));
    SET_LO8(ecx, LO8(ecx) + MEM8(esp + 0x20));
    MEM8(esi + 4) = LO8(ecx);
    SET_LO8(edx, MEM8(eax + 5));
    SET_LO8(edx, LO8(edx) + LO8(ebx));
    MEM8(esi + 5) = LO8(edx);
    SET_LO8(ecx, MEM8(eax + 6));
    SET_LO8(edx, MEM8(esp + 0x24));
    SET_LO8(ebx, MEM8(esp + 0x1A));
    edi = MEM32(esp + 0x60);
    SET_LO8(ecx, LO8(ecx) + LO8(edx));
    MEM8(esi + 6) = LO8(ecx);
    SET_LO8(edx, MEM8(eax + 7));
    SET_LO8(edx, LO8(edx) + MEM8(esp + 0x25));
    MEM8(esi + 7) = LO8(edx);
    SET_LO8(edx, MEM8(eax + 8));
    SET_LO8(edx, LO8(edx) + LO8(ebx));
    SET_LO8(ebx, MEM8(esp + 0x1B));
    MEM8(esi + edi) = LO8(edx);
    SET_LO8(edx, MEM8(eax + 9));
    SET_LO8(edx, LO8(edx) + LO8(ebx));
    SET_LO8(ebx, MEM8(esp + 0x1E));
    ecx = esi + edi;
    MEM8(ecx + 1) = LO8(edx);
    SET_LO8(edx, MEM8(eax + 0xA));
    SET_LO8(edx, LO8(edx) + LO8(ebx));
    SET_LO8(ebx, MEM8(esp + 0x1F));
    MEM8(ecx + 2) = LO8(edx);
    SET_LO8(edx, MEM8(eax + 0xB));
    SET_LO8(edx, LO8(edx) + LO8(ebx));
    SET_LO8(ebx, MEM8(esp + 0x22));
    MEM8(ecx + 3) = LO8(edx);
    SET_LO8(edx, MEM8(eax + 0xC));
    SET_LO8(edx, LO8(edx) + LO8(ebx));
    SET_LO8(ebx, MEM8(esp + 0x23));
    MEM8(ecx + 4) = LO8(edx);
    SET_LO8(edx, MEM8(eax + 0xD));
    SET_LO8(edx, LO8(edx) + LO8(ebx));
    SET_LO8(ebx, MEM8(esp + 0x26));
    MEM8(ecx + 5) = LO8(edx);
    SET_LO8(edx, MEM8(eax + 0xE));
    esp = esp + 0xC;
    SET_LO8(edx, LO8(edx) + LO8(ebx));
    SET_LO8(ebx, MEM8(esp + 0x1B));
    MEM8(ecx + 6) = LO8(edx);
    SET_LO8(edx, MEM8(eax + 0xF));
    SET_LO8(edx, LO8(edx) + LO8(ebx));
    MEM8(ecx + 7) = LO8(edx);
    SET_LO8(edx, MEM8(eax + 0x10));
    SET_LO8(edx, LO8(edx) + MEM8(esp + 0x24));
    MEM8(ecx + edi) = LO8(edx);
    SET_LO8(edx, MEM8(eax + 0x11));
    SET_LO8(edx, LO8(edx) + MEM8(esp + 0x25));
    MEM8(ecx + edi + 1) = LO8(edx);
    SET_LO8(edx, MEM8(eax + 0x12));
    SET_LO8(edx, LO8(edx) + MEM8(esp + 0x38));
    MEM8(ecx + edi + 2) = LO8(edx);
    SET_LO8(edx, MEM8(eax + 0x13));
    SET_LO8(edx, LO8(edx) + MEM8(esp + 0x39));
    MEM8(ecx + edi + 3) = LO8(edx);
    SET_LO8(edx, MEM8(eax + 0x14));
    SET_LO8(edx, LO8(edx) + MEM8(esp + 0x1C));
    MEM8(ecx + edi + 4) = LO8(edx);
    SET_LO8(edx, MEM8(eax + 0x15));
    ecx = ecx + edi;
    SET_LO8(edx, LO8(edx) + MEM8(esp + 0x1D));
    MEM8(ecx + 5) = LO8(edx);
    SET_LO8(edx, MEM8(eax + 0x16));
    SET_LO8(edx, LO8(edx) + MEM8(esp + 0x20));
    MEM8(ecx + 6) = LO8(edx);
    SET_LO8(edx, MEM8(eax + 0x17));
    SET_LO8(edx, LO8(edx) + MEM8(esp + 0x21));
    MEM8(ecx + 7) = LO8(edx);
    SET_LO8(edx, MEM8(eax + 0x18));
    SET_LO8(edx, LO8(edx) + MEM8(esp + 0x26));
    SET_LO8(ebx, MEM8(esp + 0x27));
    MEM8(ecx + edi) = LO8(edx);
    SET_LO8(edx, MEM8(eax + 0x19));
    SET_LO8(edx, LO8(edx) + LO8(ebx));
    SET_LO8(ebx, MEM8(esp + 0x3A));
    MEM8(ecx + edi + 1) = LO8(edx);
    SET_LO8(edx, MEM8(eax + 0x1A));
    SET_LO8(edx, LO8(edx) + LO8(ebx));
    SET_LO8(ebx, MEM8(esp + 0x3B));
    ecx = ecx + edi;
    MEM8(ecx + 2) = LO8(edx);
    SET_LO8(edx, MEM8(eax + 0x1B));
    SET_LO8(edx, LO8(edx) + LO8(ebx));
    SET_LO8(ebx, MEM8(esp + 0x1E));
    MEM8(ecx + 3) = LO8(edx);
    SET_LO8(edx, MEM8(eax + 0x1C));
    SET_LO8(edx, LO8(edx) + LO8(ebx));
    SET_LO8(ebx, MEM8(esp + 0x1F));
    MEM8(ecx + 4) = LO8(edx);
    SET_LO8(edx, MEM8(eax + 0x1D));
    SET_LO8(edx, LO8(edx) + LO8(ebx));
    SET_LO8(ebx, MEM8(esp + 0x22));
    MEM8(ecx + 5) = LO8(edx);
    SET_LO8(edx, MEM8(eax + 0x1E));
    SET_LO8(edx, LO8(edx) + LO8(ebx));
    SET_LO8(ebx, MEM8(esp + 0x23));
    MEM8(ecx + 6) = LO8(edx);
    SET_LO8(edx, MEM8(eax + 0x1F));
    SET_LO8(edx, LO8(edx) + LO8(ebx));
    SET_LO8(ebx, MEM8(esp + 0x28));
    MEM8(ecx + 7) = LO8(edx);
    SET_LO8(edx, MEM8(eax + 0x20));
    SET_LO8(edx, LO8(edx) + LO8(ebx));
    SET_LO8(ebx, MEM8(esp + 0x29));
    ecx = ecx + edi;
    MEM8(ecx) = LO8(edx);
    SET_LO8(edx, MEM8(eax + 0x21));
    SET_LO8(edx, LO8(edx) + LO8(ebx));
    SET_LO8(ebx, MEM8(esp + 0x2C));
    MEM8(ecx + 1) = LO8(edx);
    SET_LO8(edx, MEM8(eax + 0x22));
    SET_LO8(edx, LO8(edx) + LO8(ebx));
    MEM8(ecx + 2) = LO8(edx);
    SET_LO8(edx, MEM8(eax + 0x23));
    SET_LO8(edx, LO8(edx) + MEM8(esp + 0x2D));
    MEM8(ecx + 3) = LO8(edx);
    SET_LO8(edx, MEM8(eax + 0x24));
    SET_LO8(edx, LO8(edx) + MEM8(esp + 0x3C));
    MEM8(ecx + 4) = LO8(edx);
    SET_LO8(edx, MEM8(eax + 0x25));
    SET_LO8(edx, LO8(edx) + MEM8(esp + 0x3D));
    MEM8(ecx + 5) = LO8(edx);
    SET_LO8(edx, MEM8(eax + 0x26));
    SET_LO8(edx, LO8(edx) + MEM8(esp + 0x40));
    MEM8(ecx + 6) = LO8(edx);
    SET_LO8(edx, MEM8(eax + 0x27));
    SET_LO8(edx, LO8(edx) + MEM8(esp + 0x41));
    MEM8(ecx + 7) = LO8(edx);
    SET_LO8(edx, MEM8(eax + 0x28));
    SET_LO8(edx, LO8(edx) + MEM8(esp + 0x2A));
    MEM8(ecx + edi) = LO8(edx);
    SET_LO8(edx, MEM8(eax + 0x29));
    SET_LO8(edx, LO8(edx) + MEM8(esp + 0x2B));
    MEM8(ecx + edi + 1) = LO8(edx);
    SET_LO8(edx, MEM8(eax + 0x2A));
    SET_LO8(edx, LO8(edx) + MEM8(esp + 0x2E));
    SET_LO8(ebx, MEM8(esp + 0x2F));
    MEM8(ecx + edi + 2) = LO8(edx);
    SET_LO8(edx, MEM8(eax + 0x2B));
    SET_LO8(edx, LO8(edx) + LO8(ebx));
    SET_LO8(ebx, MEM8(esp + 0x3E));
    MEM8(ecx + edi + 3) = LO8(edx);
    SET_LO8(edx, MEM8(eax + 0x2C));
    SET_LO8(edx, LO8(edx) + LO8(ebx));
    SET_LO8(ebx, MEM8(esp + 0x3F));
    ecx = ecx + edi;
    MEM8(ecx + 4) = LO8(edx);
    SET_LO8(edx, MEM8(eax + 0x2D));
    SET_LO8(edx, LO8(edx) + LO8(ebx));
    SET_LO8(ebx, MEM8(esp + 0x42));
    MEM8(ecx + 5) = LO8(edx);
    SET_LO8(edx, MEM8(eax + 0x2E));
    SET_LO8(edx, LO8(edx) + LO8(ebx));
    SET_LO8(ebx, MEM8(esp + 0x43));
    MEM8(ecx + 6) = LO8(edx);
    SET_LO8(edx, MEM8(eax + 0x2F));
    SET_LO8(edx, LO8(edx) + LO8(ebx));
    SET_LO8(ebx, MEM8(esp + 0x30));
    MEM8(ecx + 7) = LO8(edx);
    SET_LO8(edx, MEM8(eax + 0x30));
    SET_LO8(edx, LO8(edx) + LO8(ebx));
    SET_LO8(ebx, MEM8(esp + 0x31));
    MEM8(ecx + edi) = LO8(edx);
    SET_LO8(edx, MEM8(eax + 0x31));
    SET_LO8(edx, LO8(edx) + LO8(ebx));
    SET_LO8(ebx, MEM8(esp + 0x34));
    ecx = ecx + edi;
    MEM8(ecx + 1) = LO8(edx);
    SET_LO8(edx, MEM8(eax + 0x32));
    SET_LO8(edx, LO8(edx) + LO8(ebx));
    SET_LO8(ebx, MEM8(esp + 0x35));
    MEM8(ecx + 2) = LO8(edx);
    SET_LO8(edx, MEM8(eax + 0x33));
    SET_LO8(edx, LO8(edx) + LO8(ebx));
    SET_LO8(ebx, MEM8(esp + 0x44));
    MEM8(ecx + 3) = LO8(edx);
    SET_LO8(edx, MEM8(eax + 0x34));
    SET_LO8(edx, LO8(edx) + LO8(ebx));
    SET_LO8(ebx, MEM8(esp + 0x45));
    MEM8(ecx + 4) = LO8(edx);
    SET_LO8(edx, MEM8(eax + 0x35));
    SET_LO8(edx, LO8(edx) + LO8(ebx));
    SET_LO8(ebx, MEM8(esp + 0x48));
    MEM8(ecx + 5) = LO8(edx);
    SET_LO8(edx, MEM8(eax + 0x36));
    SET_LO8(edx, LO8(edx) + LO8(ebx));
    SET_LO8(ebx, MEM8(esp + 0x49));
    MEM8(ecx + 6) = LO8(edx);
    SET_LO8(edx, MEM8(eax + 0x37));
    SET_LO8(edx, LO8(edx) + LO8(ebx));
    SET_LO8(ebx, MEM8(esp + 0x32));
    MEM8(ecx + 7) = LO8(edx);
    SET_LO8(edx, MEM8(eax + 0x38));
    SET_LO8(edx, LO8(edx) + LO8(ebx));
    SET_LO8(ebx, MEM8(esp + 0x33));
    MEM8(ecx + edi) = LO8(edx);
    SET_LO8(edx, MEM8(eax + 0x39));
    SET_LO8(edx, LO8(edx) + LO8(ebx));
    SET_LO8(ebx, MEM8(esp + 0x36));
    ecx = ecx + edi;
    MEM8(ecx + 1) = LO8(edx);
    SET_LO8(edx, MEM8(eax + 0x3A));
    SET_LO8(edx, LO8(edx) + LO8(ebx));
    SET_LO8(ebx, MEM8(esp + 0x37));
    MEM8(ecx + 2) = LO8(edx);
    SET_LO8(edx, MEM8(eax + 0x3B));
    SET_LO8(edx, LO8(edx) + LO8(ebx));
    SET_LO8(ebx, MEM8(esp + 0x46));
    MEM8(ecx + 3) = LO8(edx);
    SET_LO8(edx, MEM8(eax + 0x3C));
    SET_LO8(edx, LO8(edx) + LO8(ebx));
    SET_LO8(ebx, MEM8(esp + 0x47));
    MEM8(ecx + 4) = LO8(edx);
    SET_LO8(edx, MEM8(eax + 0x3D));
    SET_LO8(edx, LO8(edx) + LO8(ebx));
    SET_LO8(ebx, MEM8(esp + 0x4A));
    MEM8(ecx + 5) = LO8(edx);
    SET_LO8(edx, MEM8(eax + 0x3E));
    SET_LO8(edx, LO8(edx) + LO8(ebx));
    MEM8(ecx + 6) = LO8(edx);
    SET_LO8(eax, MEM8(eax + 0x3F));
    SET_LO8(edx, MEM8(esp + 0x4B));
    POP32(esp, edi);
    SET_LO8(eax, LO8(eax) + LO8(edx));
    POP32(esp, esi);
    MEM8(ecx + 7) = LO8(eax);
    POP32(esp, ebx);
    esp = esp + 0x40;
    esp += 24; return; /* ret 20 */

}

/**
 * sub_00217640
 * Original: 0x00217640 - 0x0021767B (59 bytes, 18 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00217640(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_00217640: ;
    eax = eax | 0x420A0D0A;
    ebp = (uint32_t)((int32_t)MEM32(esi + 0x6B) * (int32_t)0x6F430A0D);
    if (_flags /* jo: overflow */) { g_seh_ebp = ebp; sub_002176C7(); return; }

loc_0021764E: ;
    if (_flags /* jb: below (unsigned <) */) { g_seh_ebp = ebp; sub_002176B9(); return; }

loc_00217650: ;
    PUSH32(esp, 0x43282074);
    MEM32(eax) = MEM32(eax) - esp;
    MEM32(ecx) = MEM32(ecx) ^ edi;
    _fa = (uint32_t)(MEM32(ebp + 0x32303032)) & 0xFFFFFFFFu; _fb = (uint32_t)(esi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(ebp + 0x32303032), esi (32-bit) */
    MEM8(edx + 0x41) = MEM8(edx + 0x41) & LO8(edx);
    esp++;
    MEM8(edi + 0x61) = MEM8(edi + 0x61) & LO8(eax);
    /* TODO: insd dword ptr es:[edi], dx */
    MEM8(edi + ebp * 2 + 0x6F) = MEM8(edi + ebp * 2 + 0x6F) & LO8(edx);
    /* TODO: insb byte ptr es:[edi], dx */
    if (_flags /* jae: above or equal (unsigned >=) */) { g_seh_ebp = ebp; sub_0021769D(); return; }

loc_00217671: ;
    MEM8(ecx + 0x6E) = MEM8(ecx + 0x6E) & LO8(ecx);
    /* TODO: arpl word ptr [esi], bp */
    eax = eax | 0xA0D0A;

}

/**
 * sub_002176D0
 * Original: 0x002176D0 - 0x00217757 (135 bytes, 37 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_002176D0(void)
{
    int _flags = 0; /* fallback flag var */

loc_002176D0: ;
    PUSH32(esp, esi);
    esi = MEM32(esp + 8);
    PUSH32(esp, edi);
    edx = esi;
    edi = 8;
    /* nop */

loc_002176E0: ;
    ecx = MEM32(0x299F18);
    eax = ZX8(MEM8(ecx));
    eax = MEM32(eax * 4 + 0x299B10);
    ecx++;
    MEM32(0x299F18) = ecx;
    ecx = MEM32(0x299F10);
    MEM32(ecx) = eax;
    ecx = MEM32(0x299F10);
    MEM32(ecx + 4) = eax;
    ecx = MEM32(0x299F1C);
    eax = ZX8(MEM8(ecx));
    eax = MEM32(eax * 4 + 0x299B10);
    ecx++;
    MEM32(0x299F1C) = ecx;
    ecx = MEM32(0x299F14);
    MEM32(ecx) = eax;
    ecx = MEM32(0x299F14);
    MEM32(ecx + 4) = eax;
    eax = MEM32(0x299F10);
    ecx = MEM32(0x299F14);
    eax = eax + edi;
    ecx = ecx + edi;
    edx--;
    MEM32(0x299F10) = eax;
    MEM32(0x299F14) = ecx;
    if ((edx != 0)) goto loc_002176E0; /* jne: not equal / not zero */

loc_0021774D: ;
    edx = MEM32(esp + 0x10);
    POP32(esp, edi);
    eax = esi + edx;
    POP32(esp, esi);
    esp += 4; return; /* ret */

}

/**
 * sub_00217760
 * Original: 0x00217760 - 0x002177B2 (82 bytes, 22 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00217760(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00217760: ;
    edx = MEM32(esp + 8);
    _fa = (uint32_t)(edx) & 0xFFFFFFFFu; _fb = (uint32_t)(edx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test edx, edx (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_002177B1; /* je: equal / zero */

loc_00217768: ;
    PUSH32(esp, esi);
    /* nop */

loc_00217770: ;
    ecx = MEM32(0x299F18);
    eax = ZX8(MEM8(ecx));
    eax = MEM32(eax * 4 + 0x299B10);
    ecx++;
    MEM32(0x299F18) = ecx;
    ecx = MEM32(0x299F10);
    MEM32(ecx) = eax;
    ecx = MEM32(0x299F10);
    esi = MEM32(0x299F30);
    MEM32(esi + ecx) = eax;
    ecx = MEM32(0x299F10);
    ecx = ecx + 4;
    edx--;
    MEM32(0x299F10) = ecx;
    if ((edx != 0)) goto loc_00217770; /* jne: not equal / not zero */

loc_002177B0: ;
    POP32(esp, esi);

loc_002177B1: ;
    esp += 4; return; /* ret */

}

/**
 * sub_002177C0
 * Original: 0x002177C0 - 0x00217856 (150 bytes, 41 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_002177C0(void)
{
    int _flags = 0; /* fallback flag var */

loc_002177C0: ;
    PUSH32(esp, ebx);
    PUSH32(esp, esi);
    esi = MEM32(esp + 0xC);
    PUSH32(esp, edi);
    edx = esi;
    edi = 4;
    edi = edi;

loc_002177D0: ;
    ecx = MEM32(0x299F18);
    eax = ZX8(MEM8(ecx));
    eax = MEM32(eax * 4 + 0x299B10);
    ecx++;
    MEM32(0x299F18) = ecx;
    ecx = MEM32(0x299F10);
    MEM32(ecx) = eax;
    ebx = MEM32(0x299F10);
    ecx = MEM32(0x299F30);
    MEM32(ecx + ebx) = eax;
    ecx = MEM32(0x299F1C);
    eax = ZX8(MEM8(ecx));
    eax = MEM32(eax * 4 + 0x299B10);
    ecx++;
    MEM32(0x299F1C) = ecx;
    ecx = MEM32(0x299F14);
    MEM32(ecx) = eax;
    ecx = MEM32(0x299F14);
    ebx = MEM32(0x299F30);
    MEM32(ecx + ebx) = eax;
    ebx = MEM32(0x299F10);
    ecx = MEM32(0x299F14);
    ebx = ebx + edi;
    ecx = ecx + edi;
    edx--;
    MEM32(0x299F10) = ebx;
    MEM32(0x299F14) = ecx;
    if ((edx != 0)) goto loc_002177D0; /* jne: not equal / not zero */

loc_0021784B: ;
    edx = MEM32(esp + 0x14);
    POP32(esp, edi);
    eax = esi + edx;
    POP32(esp, esi);
    POP32(esp, ebx);
    esp += 4; return; /* ret */

}

/**
 * sub_00217860
 * Original: 0x00217860 - 0x002178CB (107 bytes, 27 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00217860(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00217860: ;
    edx = MEM32(esp + 8);
    _fa = (uint32_t)(edx) & 0xFFFFFFFFu; _fb = (uint32_t)(edx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test edx, edx (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_002178CA; /* je: equal / zero */

loc_00217868: ;
    PUSH32(esp, esi);
    /* nop */

loc_00217870: ;
    ecx = MEM32(0x299F18);
    eax = ZX8(MEM8(ecx));
    eax = MEM32(eax * 4 + 0x299B10);
    ecx++;
    MEM32(0x299F18) = ecx;
    ecx = MEM32(0x299F10);
    MEM32(ecx) = eax;
    ecx = MEM32(0x299F10);
    MEM32(ecx + 4) = eax;
    esi = MEM32(0x299F10);
    ecx = MEM32(0x299F30);
    MEM32(ecx + esi) = eax;
    ecx = MEM32(0x299F10);
    esi = MEM32(0x299F30);
    MEM32(esi + ecx + 4) = eax;
    ecx = MEM32(0x299F10);
    ecx = ecx + 8;
    edx--;
    MEM32(0x299F10) = ecx;
    if ((edx != 0)) goto loc_00217870; /* jne: not equal / not zero */

loc_002178C9: ;
    POP32(esp, esi);

loc_002178CA: ;
    esp += 4; return; /* ret */

}

/**
 * sub_002178D0
 * Original: 0x002178D0 - 0x0021799C (204 bytes, 51 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_002178D0(void)
{
    int _flags = 0; /* fallback flag var */

loc_002178D0: ;
    PUSH32(esp, ebx);
    PUSH32(esp, esi);
    esi = MEM32(esp + 0xC);
    PUSH32(esp, edi);
    edx = esi;
    edi = 8;
    edi = edi;

loc_002178E0: ;
    ecx = MEM32(0x299F18);
    eax = ZX8(MEM8(ecx));
    eax = MEM32(eax * 4 + 0x299B10);
    ecx++;
    MEM32(0x299F18) = ecx;
    ecx = MEM32(0x299F10);
    MEM32(ecx) = eax;
    ecx = MEM32(0x299F10);
    MEM32(ecx + 4) = eax;
    ebx = MEM32(0x299F10);
    ecx = MEM32(0x299F30);
    MEM32(ecx + ebx) = eax;
    ebx = MEM32(0x299F10);
    ecx = MEM32(0x299F30);
    MEM32(ecx + ebx + 4) = eax;
    ecx = MEM32(0x299F1C);
    eax = ZX8(MEM8(ecx));
    eax = MEM32(eax * 4 + 0x299B10);
    ecx++;
    MEM32(0x299F1C) = ecx;
    ecx = MEM32(0x299F14);
    MEM32(ecx) = eax;
    ecx = MEM32(0x299F14);
    MEM32(ecx + 4) = eax;
    ecx = MEM32(0x299F14);
    ebx = MEM32(0x299F30);
    MEM32(ecx + ebx) = eax;
    ecx = MEM32(0x299F14);
    ebx = MEM32(0x299F30);
    MEM32(ecx + ebx + 4) = eax;
    ebx = MEM32(0x299F10);
    ecx = MEM32(0x299F14);
    ebx = ebx + edi;
    ecx = ecx + edi;
    edx--;
    MEM32(0x299F10) = ebx;
    MEM32(0x299F14) = ecx;
    if ((edx != 0)) goto loc_002178E0; /* jne: not equal / not zero */

loc_00217991: ;
    edx = MEM32(esp + 0x14);
    POP32(esp, edi);
    eax = esi + edx;
    POP32(esp, esi);
    POP32(esp, ebx);
    esp += 4; return; /* ret */

}

/**
 * sub_002179A0
 * Original: 0x002179A0 - 0x00217A63 (195 bytes, 58 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_002179A0(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_002179A0: ;
    eax = MEM32(esp + 8);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    PUSH32(esp, ebx);
    ebx = MEM32(esp + 8);
    if (TEST_Z(_fa, _fb)) goto loc_00217A61; /* je: equal / zero */

loc_002179B1: ;
    PUSH32(esp, ebp);
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    ebp = eax;
    goto loc_002179C0;

    /* nop */
    /* nop */

loc_002179C0: ;
    eax = MEM32(0x299F20);
    eax = ZX8(MEM8(eax));
    ecx = MEM32(0x299F24);
    ecx = ZX8(MEM8(ecx));
    eax = eax << 2;
    esi = MEM32(eax + 0x29A738);
    edi = MEM32(eax + 0x299F38);
    eax = MEM32(0x299F18);
    ecx = ecx << 2;
    edx = MEM32(ecx + 0x29A338);
    ecx = MEM32(ecx + 0x29AB38);
    edx = edx + esi;
    esi = ZX8(MEM8(eax));
    esi = MEM32(esi * 4 + 0x295EC0);
    eax++;
    MEM32(0x299F18) = eax;
    eax = MEM32(esi + ecx * 4);
    ecx = MEM32(esi + edx * 4);
    edx = MEM32(0x299F10);
    eax = eax << 8;
    eax = eax | ecx;
    ecx = MEM32(esi + edi * 4);
    eax = eax << 8;
    eax = eax | ecx;
    MEM32(edx) = eax;
    ecx = MEM32(0x299F10);
    MEM32(ecx + 4) = eax;
    edx = MEM32(0x299F10);
    edx = edx + 8;
    ebx++;
    _fa = (uint32_t)(LO8(ebx)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(ebx), 1 (8-bit) */
    MEM32(0x299F10) = edx;
    if (TEST_NZ(_fa, _fb)) goto loc_00217A57; /* jne: not equal / not zero */

loc_00217A3F: ;
    ecx = MEM32(0x299F20);
    eax = MEM32(0x299F24);
    ecx++;
    eax++;
    MEM32(0x299F20) = ecx;
    MEM32(0x299F24) = eax;

loc_00217A57: ;
    ebp--;
    if ((ebp != 0)) goto loc_002179C0; /* jne: not equal / not zero */

loc_00217A5E: ;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebp);

loc_00217A61: ;
    POP32(esp, ebx);
    esp += 4; return; /* ret */

}

/**
 * sub_00217A70
 * Original: 0x00217A70 - 0x00217B70 (256 bytes, 71 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00217A70(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_00217A70: ;
    eax = MEM32(esp + 8);
    PUSH32(esp, ebx);
    PUSH32(esp, ebp);
    ebp = MEM32(esp + 0xC);
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    /* nop */

loc_00217A80: ;
    ecx = MEM32(0x299F20);
    ecx = ZX8(MEM8(ecx));
    edx = MEM32(0x299F24);
    edx = ZX8(MEM8(edx));
    ecx = ecx << 2;
    edi = MEM32(ecx + 0x29A738);
    ebx = MEM32(ecx + 0x299F38);
    ecx = MEM32(0x299F18);
    edx = edx << 2;
    esi = MEM32(edx + 0x29A338);
    edx = MEM32(edx + 0x29AB38);
    esi = esi + edi;
    edi = ZX8(MEM8(ecx));
    edi = MEM32(edi * 4 + 0x295EC0);
    ecx++;
    MEM32(0x299F18) = ecx;
    ecx = MEM32(edi + edx * 4);
    ecx = ecx << 8;
    ecx = ecx | MEM32(edi + esi * 4);
    ecx = ecx << 8;
    ecx = ecx | MEM32(edi + ebx * 4);
    edi = MEM32(0x299F10);
    MEM32(edi) = ecx;
    edi = MEM32(0x299F10);
    MEM32(edi + 4) = ecx;
    ecx = MEM32(0x299F1C);
    edi = ZX8(MEM8(ecx));
    edi = MEM32(edi * 4 + 0x295EC0);
    ecx++;
    MEM32(0x299F1C) = ecx;
    ecx = MEM32(edi + edx * 4);
    edx = MEM32(edi + esi * 4);
    ecx = ecx << 8;
    ecx = ecx | edx;
    edx = MEM32(edi + ebx * 4);
    ecx = ecx << 8;
    ecx = ecx | edx;
    edx = MEM32(0x299F14);
    MEM32(edx) = ecx;
    edx = MEM32(0x299F14);
    MEM32(edx + 4) = ecx;
    edi = MEM32(0x299F10);
    esi = MEM32(0x299F14);
    ecx = 8;
    edi = edi + ecx;
    esi = esi + ecx;
    eax++;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), 1 (8-bit) */
    MEM32(0x299F10) = edi;
    MEM32(0x299F14) = esi;
    if (TEST_NZ(_fa, _fb)) goto loc_00217B64; /* jne: not equal / not zero */

loc_00217B4A: ;
    edx = MEM32(0x299F20);
    ecx = MEM32(0x299F24);
    edx++;
    ecx++;
    MEM32(0x299F20) = edx;
    MEM32(0x299F24) = ecx;

loc_00217B64: ;
    ebp--;
    if ((ebp != 0)) goto loc_00217A80; /* jne: not equal / not zero */

loc_00217B6B: ;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebp);
    POP32(esp, ebx);
    esp += 4; return; /* ret */

}

/**
 * sub_00217C40
 * Original: 0x00217C40 - 0x00217D53 (275 bytes, 75 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00217C40(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_00217C40: ;
    ecx = MEM32(esp + 4);
    eax = MEM32(esp + 8);
    PUSH32(esp, ebx);
    PUSH32(esp, ebp);
    PUSH32(esp, esi);
    MEM32(esp + 0x14) = ecx;
    PUSH32(esp, edi);

loc_00217C50: ;
    edx = MEM32(0x299F20);
    ecx = ZX8(MEM8(edx));
    edx = MEM32(0x299F24);
    edx = ZX8(MEM8(edx));
    ecx = ecx << 2;
    ebx = MEM32(ecx + 0x299F38);
    edi = MEM32(ecx + 0x29A738);
    ecx = MEM32(0x299F18);
    edx = edx << 2;
    esi = MEM32(edx + 0x29A338);
    edx = MEM32(edx + 0x29AB38);
    esi = esi + edi;
    edi = ZX8(MEM8(ecx));
    edi = MEM32(edi * 4 + 0x295EC0);
    ecx++;
    MEM32(0x299F18) = ecx;
    ecx = MEM32(edi + edx * 4);
    ebp = MEM32(edi + esi * 4);
    ecx = ecx << 8;
    ecx = ecx | ebp;
    ebp = MEM32(edi + ebx * 4);
    edi = MEM32(0x299F10);
    ecx = ecx << 8;
    ecx = ecx | ebp;
    MEM32(edi) = ecx;
    ebp = MEM32(0x299F10);
    edi = MEM32(0x299F30);
    MEM32(edi + ebp) = ecx;
    ecx = MEM32(0x299F1C);
    edi = ZX8(MEM8(ecx));
    edi = MEM32(edi * 4 + 0x295EC0);
    ecx++;
    MEM32(0x299F1C) = ecx;
    ecx = MEM32(edi + edx * 4);
    ebp = MEM32(edi + esi * 4);
    edx = MEM32(0x299F14);
    ecx = ecx << 8;
    ecx = ecx | ebp;
    ebp = MEM32(edi + ebx * 4);
    ecx = ecx << 8;
    ecx = ecx | ebp;
    MEM32(edx) = ecx;
    edx = MEM32(0x299F14);
    esi = MEM32(0x299F30);
    MEM32(edx + esi) = ecx;
    edi = MEM32(0x299F10);
    esi = MEM32(0x299F14);
    ecx = 4;
    edi = edi + ecx;
    esi = esi + ecx;
    eax++;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), 1 (8-bit) */
    MEM32(0x299F10) = edi;
    MEM32(0x299F14) = esi;
    if (TEST_NZ(_fa, _fb)) goto loc_00217D44; /* jne: not equal / not zero */

loc_00217D2A: ;
    edx = MEM32(0x299F20);
    ecx = MEM32(0x299F24);
    edx++;
    ecx++;
    MEM32(0x299F20) = edx;
    MEM32(0x299F24) = ecx;

loc_00217D44: ;
    MEM32(esp + 0x18) = MEM32(esp + 0x18) - 1;
    if ((MEM32(esp + 0x18) != 0)) goto loc_00217C50; /* jne: not equal / not zero */

loc_00217D4E: ;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebp);
    POP32(esp, ebx);
    esp += 4; return; /* ret */

}

/**
 * sub_00217D60
 * Original: 0x00217D60 - 0x00217E42 (226 bytes, 64 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00217D60(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_00217D60: ;
    eax = MEM32(esp + 8);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    PUSH32(esp, ebx);
    ebx = MEM32(esp + 8);
    if (TEST_Z(_fa, _fb)) goto loc_00217E40; /* je: equal / zero */

loc_00217D71: ;
    PUSH32(esp, ebp);
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    ebp = eax;
    goto loc_00217D80;

    /* nop */
    /* nop */

loc_00217D80: ;
    eax = MEM32(0x299F20);
    eax = ZX8(MEM8(eax));
    ecx = MEM32(0x299F24);
    ecx = ZX8(MEM8(ecx));
    eax = eax << 2;
    esi = MEM32(eax + 0x29A738);
    edi = MEM32(eax + 0x299F38);
    eax = MEM32(0x299F18);
    ecx = ecx << 2;
    edx = MEM32(ecx + 0x29A338);
    ecx = MEM32(ecx + 0x29AB38);
    edx = edx + esi;
    esi = ZX8(MEM8(eax));
    esi = MEM32(esi * 4 + 0x295EC0);
    eax++;
    MEM32(0x299F18) = eax;
    eax = MEM32(esi + ecx * 4);
    ecx = MEM32(esi + edx * 4);
    edx = MEM32(0x299F10);
    eax = eax << 8;
    eax = eax | ecx;
    ecx = MEM32(esi + edi * 4);
    eax = eax << 8;
    eax = eax | ecx;
    MEM32(edx) = eax;
    ecx = MEM32(0x299F10);
    MEM32(ecx + 4) = eax;
    ecx = MEM32(0x299F10);
    edx = MEM32(0x299F30);
    MEM32(edx + ecx) = eax;
    edx = MEM32(0x299F10);
    ecx = MEM32(0x299F30);
    MEM32(ecx + edx + 4) = eax;
    edx = MEM32(0x299F10);
    edx = edx + 8;
    ebx++;
    _fa = (uint32_t)(LO8(ebx)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(ebx), 1 (8-bit) */
    MEM32(0x299F10) = edx;
    if (TEST_NZ(_fa, _fb)) goto loc_00217E36; /* jne: not equal / not zero */

loc_00217E1E: ;
    ecx = MEM32(0x299F20);
    eax = MEM32(0x299F24);
    ecx++;
    eax++;
    MEM32(0x299F20) = ecx;
    MEM32(0x299F24) = eax;

loc_00217E36: ;
    ebp--;
    if ((ebp != 0)) goto loc_00217D80; /* jne: not equal / not zero */

loc_00217E3D: ;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebp);

loc_00217E40: ;
    POP32(esp, ebx);
    esp += 4; return; /* ret */

}

/**
 * sub_00217E50
 * Original: 0x00217E50 - 0x00217F95 (325 bytes, 85 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00217E50(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_00217E50: ;
    ecx = MEM32(esp + 4);
    eax = MEM32(esp + 8);
    PUSH32(esp, ebx);
    PUSH32(esp, ebp);
    PUSH32(esp, esi);
    MEM32(esp + 0x14) = ecx;
    PUSH32(esp, edi);

loc_00217E60: ;
    edx = MEM32(0x299F20);
    ecx = ZX8(MEM8(edx));
    edx = MEM32(0x299F24);
    edx = ZX8(MEM8(edx));
    ecx = ecx << 2;
    ebx = MEM32(ecx + 0x299F38);
    edi = MEM32(ecx + 0x29A738);
    ecx = MEM32(0x299F18);
    edx = edx << 2;
    esi = MEM32(edx + 0x29A338);
    edx = MEM32(edx + 0x29AB38);
    esi = esi + edi;
    edi = ZX8(MEM8(ecx));
    edi = MEM32(edi * 4 + 0x295EC0);
    ecx++;
    MEM32(0x299F18) = ecx;
    ecx = MEM32(edi + edx * 4);
    ebp = MEM32(edi + esi * 4);
    ecx = ecx << 8;
    ecx = ecx | ebp;
    ebp = MEM32(edi + ebx * 4);
    edi = MEM32(0x299F10);
    ecx = ecx << 8;
    ecx = ecx | ebp;
    MEM32(edi) = ecx;
    edi = MEM32(0x299F10);
    MEM32(edi + 4) = ecx;
    ebp = MEM32(0x299F10);
    edi = MEM32(0x299F30);
    MEM32(edi + ebp) = ecx;
    ebp = MEM32(0x299F10);
    edi = MEM32(0x299F30);
    MEM32(edi + ebp + 4) = ecx;
    ecx = MEM32(0x299F1C);
    edi = ZX8(MEM8(ecx));
    edi = MEM32(edi * 4 + 0x295EC0);
    ecx++;
    MEM32(0x299F1C) = ecx;
    ecx = MEM32(edi + edx * 4);
    ebp = MEM32(edi + esi * 4);
    edx = MEM32(0x299F14);
    ecx = ecx << 8;
    ecx = ecx | ebp;
    ebp = MEM32(edi + ebx * 4);
    ecx = ecx << 8;
    ecx = ecx | ebp;
    MEM32(edx) = ecx;
    edx = MEM32(0x299F14);
    MEM32(edx + 4) = ecx;
    edx = MEM32(0x299F14);
    esi = MEM32(0x299F30);
    MEM32(edx + esi) = ecx;
    edx = MEM32(0x299F14);
    esi = MEM32(0x299F30);
    MEM32(edx + esi + 4) = ecx;
    edi = MEM32(0x299F10);
    esi = MEM32(0x299F14);
    ecx = 8;
    edi = edi + ecx;
    esi = esi + ecx;
    eax++;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), 1 (8-bit) */
    MEM32(0x299F10) = edi;
    MEM32(0x299F14) = esi;
    if (TEST_NZ(_fa, _fb)) goto loc_00217F86; /* jne: not equal / not zero */

loc_00217F6C: ;
    edx = MEM32(0x299F20);
    ecx = MEM32(0x299F24);
    edx++;
    ecx++;
    MEM32(0x299F20) = edx;
    MEM32(0x299F24) = ecx;

loc_00217F86: ;
    MEM32(esp + 0x18) = MEM32(esp + 0x18) - 1;
    if ((MEM32(esp + 0x18) != 0)) goto loc_00217E60; /* jne: not equal / not zero */

loc_00217F90: ;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebp);
    POP32(esp, ebx);
    esp += 4; return; /* ret */

}

/**
 * sub_00217FA0
 * Original: 0x00217FA0 - 0x00217FE8 (72 bytes, 19 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00217FA0(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00217FA0: ;
    eax = MEM32(esp + 8);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00217FE7; /* je: equal / zero */

loc_00217FA8: ;
    goto loc_00217FB0;

    /* nop */

loc_00217FB0: ;
    ecx = MEM32(0x299F18);
    edx = ZX8(MEM8(ecx));
    ecx = MEM32(edx * 4 + 0x299B10);
    edx = MEM32(0x299F10);
    MEM32(edx) = ecx;
    ecx = MEM32(0x299F18);
    edx = MEM32(0x299F10);
    ecx++;
    edx = edx + 4;
    eax--;
    MEM32(0x299F18) = ecx;
    MEM32(0x299F10) = edx;
    if ((eax != 0)) goto loc_00217FB0; /* jne: not equal / not zero */

loc_00217FE7: ;
    esp += 4; return; /* ret */

}

/**
 * sub_00217FF0
 * Original: 0x00217FF0 - 0x00218072 (130 bytes, 35 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00217FF0(void)
{
    int _flags = 0; /* fallback flag var */

loc_00217FF0: ;
    ecx = MEM32(esp + 4);
    PUSH32(esp, esi);
    eax = ecx;
    edx = 4;
    PUSH32(esp, edi);
    /* nop */

loc_00218000: ;
    esi = MEM32(0x299F18);
    esi = ZX8(MEM8(esi));
    esi = MEM32(esi * 4 + 0x299B10);
    edi = MEM32(0x299F10);
    MEM32(edi) = esi;
    esi = MEM32(0x299F18);
    edi = MEM32(0x299F14);
    esi++;
    MEM32(0x299F18) = esi;
    esi = MEM32(0x299F1C);
    esi = ZX8(MEM8(esi));
    esi = MEM32(esi * 4 + 0x299B10);
    MEM32(edi) = esi;
    edi = MEM32(0x299F1C);
    esi = MEM32(0x299F10);
    edi++;
    MEM32(0x299F1C) = edi;
    edi = MEM32(0x299F14);
    esi = esi + edx;
    edi = edi + edx;
    eax--;
    MEM32(0x299F10) = esi;
    MEM32(0x299F14) = edi;
    if ((eax != 0)) goto loc_00218000; /* jne: not equal / not zero */

loc_00218069: ;
    eax = MEM32(esp + 0x10);
    POP32(esp, edi);
    eax = eax + ecx;
    POP32(esp, esi);
    esp += 4; return; /* ret */

}

/**
 * sub_00218080
 * Original: 0x00218080 - 0x0021813C (188 bytes, 56 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00218080(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_00218080: ;
    eax = MEM32(esp + 8);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    PUSH32(esp, ebx);
    ebx = MEM32(esp + 8);
    if (TEST_Z(_fa, _fb)) goto loc_0021813A; /* je: equal / zero */

loc_00218091: ;
    PUSH32(esp, ebp);
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    ebp = eax;
    goto loc_002180A0;

    /* nop */
    /* nop */

loc_002180A0: ;
    eax = MEM32(0x299F20);
    eax = ZX8(MEM8(eax));
    ecx = MEM32(0x299F24);
    ecx = ZX8(MEM8(ecx));
    ecx = ecx << 2;
    edx = MEM32(ecx + 0x29A338);
    ecx = MEM32(ecx + 0x29AB38);
    eax = eax << 2;
    edi = MEM32(eax + 0x29A738);
    esi = MEM32(eax + 0x299F38);
    edx = edx + edi;
    edi = MEM32(0x299F18);
    eax = ZX8(MEM8(edi));
    eax = MEM32(eax * 4 + 0x295EC0);
    edi++;
    MEM32(0x299F18) = edi;
    ecx = MEM32(eax + ecx * 4);
    edi = MEM32(eax + edx * 4);
    edx = MEM32(0x299F10);
    ecx = ecx << 8;
    ecx = ecx | edi;
    edi = MEM32(eax + esi * 4);
    ecx = ecx << 8;
    ecx = ecx | edi;
    MEM32(edx) = ecx;
    edx = MEM32(0x299F10);
    edx = edx + 4;
    ebx++;
    _fa = (uint32_t)(LO8(ebx)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(ebx), 1 (8-bit) */
    MEM32(0x299F10) = edx;
    if (TEST_NZ(_fa, _fb)) goto loc_00218130; /* jne: not equal / not zero */

loc_00218118: ;
    ecx = MEM32(0x299F20);
    eax = MEM32(0x299F24);
    ecx++;
    eax++;
    MEM32(0x299F20) = ecx;
    MEM32(0x299F24) = eax;

loc_00218130: ;
    ebp--;
    if ((ebp != 0)) goto loc_002180A0; /* jne: not equal / not zero */

loc_00218137: ;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebp);

loc_0021813A: ;
    POP32(esp, ebx);
    esp += 4; return; /* ret */

}

/**
 * sub_00218140
 * Original: 0x00218140 - 0x0021822E (238 bytes, 67 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00218140(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_00218140: ;
    eax = MEM32(esp + 8);
    PUSH32(esp, ebx);
    PUSH32(esp, ebp);
    ebp = MEM32(esp + 0xC);
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    /* nop */

loc_00218150: ;
    ecx = MEM32(0x299F20);
    ecx = ZX8(MEM8(ecx));
    edx = MEM32(0x299F24);
    edx = ZX8(MEM8(edx));
    ecx = ecx << 2;
    ebx = MEM32(ecx + 0x29A738);
    edi = MEM32(ecx + 0x299F38);
    edx = edx << 2;
    esi = MEM32(edx + 0x29A338);
    edx = MEM32(edx + 0x29AB38);
    esi = esi + ebx;
    ebx = MEM32(0x299F18);
    ecx = ZX8(MEM8(ebx));
    ecx = MEM32(ecx * 4 + 0x295EC0);
    ebx++;
    MEM32(0x299F18) = ebx;
    ebx = MEM32(ecx + edx * 4);
    ebx = ebx << 8;
    ebx = ebx | MEM32(ecx + esi * 4);
    ebx = ebx << 8;
    ebx = ebx | MEM32(ecx + edi * 4);
    ecx = MEM32(0x299F10);
    MEM32(ecx) = ebx;
    ebx = MEM32(0x299F1C);
    ecx = ZX8(MEM8(ebx));
    ecx = MEM32(ecx * 4 + 0x295EC0);
    ebx++;
    MEM32(0x299F1C) = ebx;
    edx = MEM32(ecx + edx * 4);
    ebx = MEM32(ecx + esi * 4);
    edx = edx << 8;
    edx = edx | ebx;
    ebx = MEM32(ecx + edi * 4);
    ecx = MEM32(0x299F14);
    edx = edx << 8;
    edx = edx | ebx;
    MEM32(ecx) = edx;
    edi = MEM32(0x299F10);
    esi = MEM32(0x299F14);
    ecx = 4;
    edi = edi + ecx;
    esi = esi + ecx;
    eax++;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), 1 (8-bit) */
    MEM32(0x299F10) = edi;
    MEM32(0x299F14) = esi;
    if (TEST_NZ(_fa, _fb)) goto loc_00218222; /* jne: not equal / not zero */

loc_00218208: ;
    edx = MEM32(0x299F20);
    ecx = MEM32(0x299F24);
    edx++;
    ecx++;
    MEM32(0x299F20) = edx;
    MEM32(0x299F24) = ecx;

loc_00218222: ;
    ebp--;
    if ((ebp != 0)) goto loc_00218150; /* jne: not equal / not zero */

loc_00218229: ;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebp);
    POP32(esp, ebx);
    esp += 4; return; /* ret */

}

/**
 * sub_00218230
 * Original: 0x00218230 - 0x00218280 (80 bytes, 29 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00218230(void)
{

loc_00218230: ;
    eax = MEM32(esp + 0x30);
    ecx = MEM32(esp + 0x34);
    edx = MEM32(esp + 0x2C);
    PUSH32(esp, 0x29BFA0);
    PUSH32(esp, eax);
    eax = MEM32(esp + 0x30);
    PUSH32(esp, ecx);
    ecx = MEM32(esp + 0x30);
    PUSH32(esp, edx);
    edx = MEM32(esp + 0x30);
    PUSH32(esp, eax);
    eax = MEM32(esp + 0x30);
    PUSH32(esp, ecx);
    ecx = MEM32(esp + 0x30);
    PUSH32(esp, edx);
    edx = MEM32(esp + 0x30);
    PUSH32(esp, eax);
    eax = MEM32(esp + 0x30);
    PUSH32(esp, ecx);
    ecx = MEM32(esp + 0x30);
    PUSH32(esp, edx);
    edx = MEM32(esp + 0x30);
    PUSH32(esp, eax);
    PUSH32(esp, ecx);
    PUSH32(esp, edx);
    edx = MEM32(esp + 0x38);
    PUSH32(esp, 0x0021827Au); sub_00214310(); /* call 0x00214310 */

loc_0021827A: ;
    esp = esp + 0x34;
    esp += 56; return; /* ret 52 */

}

/**
 * sub_00218280
 * Original: 0x00218280 - 0x002182DB (91 bytes, 34 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00218280(void)
{

loc_00218280: ;
    eax = MEM32(esp + 0x38);
    ecx = MEM32(esp + 0x3C);
    edx = MEM32(esp + 0x34);
    PUSH32(esp, 0x29BFA0);
    PUSH32(esp, eax);
    eax = MEM32(esp + 0x38);
    PUSH32(esp, ecx);
    ecx = MEM32(esp + 0x38);
    PUSH32(esp, edx);
    edx = MEM32(esp + 0x38);
    PUSH32(esp, eax);
    eax = MEM32(esp + 0x38);
    PUSH32(esp, ecx);
    ecx = MEM32(esp + 0x38);
    PUSH32(esp, edx);
    edx = MEM32(esp + 0x38);
    PUSH32(esp, eax);
    eax = MEM32(esp + 0x38);
    PUSH32(esp, ecx);
    ecx = MEM32(esp + 0x38);
    PUSH32(esp, edx);
    edx = MEM32(esp + 0x38);
    PUSH32(esp, eax);
    eax = MEM32(esp + 0x38);
    PUSH32(esp, ecx);
    ecx = MEM32(esp + 0x38);
    PUSH32(esp, edx);
    edx = MEM32(esp + 0x38);
    PUSH32(esp, eax);
    PUSH32(esp, ecx);
    PUSH32(esp, edx);
    PUSH32(esp, 0x002182D5u); sub_00214790(); /* call 0x00214790 */

loc_002182D5: ;
    esp = esp + 0x40;
    esp += 64; return; /* ret 60 */

}

/**
 * sub_002182E0
 * Original: 0x002182E0 - 0x00218523 (579 bytes, 145 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_002182E0(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    uint64_t mm0, mm1, mm2, mm3, mm4, mm5, mm6, mm7;
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_002182E0: ;
    PUSH32(esp, ebx);
    PUSH32(esp, ebp);
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    edi = MEM32(0x299F10);
    edx = MEM32(0x299F18);
    ebp = MEM32(0x299F20);
    ebx = MEM32(0x299F24);
    eax = MEM32(esp + 0x14);
    eax = eax << 4;
    eax = eax + edi;
    MEM32(0x299F10) = eax;
    mm7 = ((uint64_t)MEM32((uint32_t)(0x25a7e8)) | ((uint64_t)MEM32((uint32_t)(0x25a7e8) + 4u) << 32)); /* MMX 0x0021830A: movq mm7, qword ptr [0x25a7e8] */

loc_00218311: ;
    mm4 = (uint64_t)(uint32_t)(MEM32((uint32_t)(edx))); /* MMX 0x00218311: movd mm4, dword ptr [edx] */
    mm0 = MMX_PXOR(mm0, mm0); /* MMX 0x00218314: pxor mm0, mm0 */
    eax = 0; /* xor self */
    edx = edx + 4;
    SET_LO8(eax, MEM8(ebp));
    mm4 = MMX_PUNPCKLBW(mm4, mm0); /* MMX 0x0021831F: punpcklbw mm4, mm0 */
    mm2 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29b738))); /* MMX 0x00218322: movd mm2, dword ptr [eax*4 + 0x29b738] */
    mm1 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29af38))); /* MMX 0x0021832A: movd mm1, dword ptr [eax*4 + 0x29af38] */
    SET_LO8(eax, MEM8(ebp + 1));
    ebp = ebp + 2;
    mm4 = MMX_PSUBUSW(mm4, ((uint64_t)MEM32((uint32_t)(0x25a7d8)) | ((uint64_t)MEM32((uint32_t)(0x25a7d8) + 4u) << 32))); /* MMX 0x00218338: psubusw mm4, qword ptr [0x25a7d8] */
    mm6 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29b738))); /* MMX 0x0021833F: movd mm6, dword ptr [eax*4 + 0x29b738] */
    mm1 = MMX_PUNPCKLDQ(mm1, (uint64_t)MEM32((uint32_t)(eax*4 + 0x29af38))); /* MMX 0x00218347: punpckldq mm1, dword ptr [eax*4 + 0x29af38] */
    SET_LO8(eax, MEM8(ebx));
    mm4 = MMX_PSLLW(mm4, 2u); /* MMX 0x00218351: psllw mm4, 2 */
    mm4 = MMX_PMULHW(mm4, ((uint64_t)MEM32((uint32_t)(0x25a7e0)) | ((uint64_t)MEM32((uint32_t)(0x25a7e0) + 4u) << 32))); /* MMX 0x00218355: pmulhw mm4, qword ptr [0x25a7e0] */
    mm5 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29b338))); /* MMX 0x0021835C: movd mm5, dword ptr [eax*4 + 0x29b338] */
    mm3 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29bb38))); /* MMX 0x00218364: movd mm3, dword ptr [eax*4 + 0x29bb38] */
    mm2 = MMX_PADDW(mm2, mm5); /* MMX 0x0021836C: paddw mm2, mm5 */
    SET_LO8(eax, MEM8(ebx + 1));
    ebx = ebx + 2;
    mm5 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29b338))); /* MMX 0x00218375: movd mm5, dword ptr [eax*4 + 0x29b338] */
    mm3 = MMX_PUNPCKLDQ(mm3, (uint64_t)MEM32((uint32_t)(eax*4 + 0x29bb38))); /* MMX 0x0021837D: punpckldq mm3, dword ptr [eax*4 + 0x29bb38] */
    mm6 = MMX_PADDW(mm6, mm5); /* MMX 0x00218385: paddw mm6, mm5 */
    mm2 = MMX_PUNPCKLDQ(mm2, mm6); /* MMX 0x00218388: punpckldq mm2, mm6 */
    mm1 = MMX_PADDW(mm1, mm4); /* MMX 0x0021838B: paddw mm1, mm4 */
    mm2 = MMX_PADDW(mm2, mm4); /* MMX 0x0021838E: paddw mm2, mm4 */
    mm1 = MMX_PADDSW(mm1, mm7); /* MMX 0x00218391: paddsw mm1, mm7 */
    mm3 = MMX_PADDW(mm3, mm4); /* MMX 0x00218394: paddw mm3, mm4 */
    mm1 = MMX_PSUBUSW(mm1, mm7); /* MMX 0x00218397: psubusw mm1, mm7 */
    mm2 = MMX_PADDSW(mm2, mm7); /* MMX 0x0021839A: paddsw mm2, mm7 */
    mm4 = mm1; /* MMX 0x0021839D: movq mm4, mm1 */
    mm2 = MMX_PSUBUSW(mm2, mm7); /* MMX 0x002183A0: psubusw mm2, mm7 */
    mm1 = MMX_PUNPCKLWD(mm1, mm0); /* MMX 0x002183A3: punpcklwd mm1, mm0 */
    mm5 = mm2; /* MMX 0x002183A6: movq mm5, mm2 */
    mm2 = MMX_PUNPCKLWD(mm2, mm0); /* MMX 0x002183A9: punpcklwd mm2, mm0 */
    mm3 = MMX_PADDSW(mm3, mm7); /* MMX 0x002183AC: paddsw mm3, mm7 */
    mm2 = MMX_PSLLD(mm2, 8u); /* MMX 0x002183AF: pslld mm2, 8 */
    mm3 = MMX_PSUBUSW(mm3, mm7); /* MMX 0x002183B3: psubusw mm3, mm7 */
    mm4 = MMX_PUNPCKHWD(mm4, mm0); /* MMX 0x002183B6: punpckhwd mm4, mm0 */
    mm6 = mm3; /* MMX 0x002183B9: movq mm6, mm3 */
    mm3 = MMX_PUNPCKLWD(mm3, mm0); /* MMX 0x002183BC: punpcklwd mm3, mm0 */
    mm3 = MMX_PSLLD(mm3, 0x10u); /* MMX 0x002183BF: pslld mm3, 0x10 */
    mm1 = MMX_POR(mm1, mm2); /* MMX 0x002183C3: por mm1, mm2 */
    mm1 = MMX_POR(mm1, mm3); /* MMX 0x002183C6: por mm1, mm3 */
    mm5 = MMX_PUNPCKHWD(mm5, mm0); /* MMX 0x002183C9: punpckhwd mm5, mm0 */
    mm6 = MMX_PUNPCKHWD(mm6, mm0); /* MMX 0x002183CC: punpckhwd mm6, mm0 */
    mm5 = MMX_PSLLD(mm5, 8u); /* MMX 0x002183CF: pslld mm5, 8 */
    MEM32((uint32_t)(edi)) = (uint32_t)mm1; MEM32((uint32_t)(edi) + 4u) = (uint32_t)(mm1 >> 32); /* MMX 0x002183D3: movq qword ptr [edi], mm1 */
    mm6 = MMX_PSLLD(mm6, 0x10u); /* MMX 0x002183D6: pslld mm6, 0x10 */
    mm4 = MMX_POR(mm4, mm5); /* MMX 0x002183DA: por mm4, mm5 */
    edi = edi + 0x10;
    mm4 = MMX_POR(mm4, mm6); /* MMX 0x002183E0: por mm4, mm6 */
    eax = MEM32(0x299F10);
    MEM32((uint32_t)(edi - 8)) = (uint32_t)mm4; MEM32((uint32_t)(edi - 8) + 4u) = (uint32_t)(mm4 >> 32); /* MMX 0x002183E8: movq qword ptr [edi - 8], mm4 */
    _fa = (uint32_t)(edi) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edi, eax (32-bit) */
    if (CMP_B(_fa, _fb)) goto loc_00218311; /* jb: below (unsigned <) */

loc_002183F4: ;
    MEM32(0x299F18) = edx;
    edi = MEM32(0x299F14);
    edx = MEM32(0x299F1C);
    ebp = MEM32(0x299F20);
    ebx = MEM32(0x299F24);
    eax = MEM32(esp + 0x14);
    eax = eax << 4;
    eax = eax + edi;
    MEM32(0x299F14) = eax;
    mm7 = ((uint64_t)MEM32((uint32_t)(0x25a7e8)) | ((uint64_t)MEM32((uint32_t)(0x25a7e8) + 4u) << 32)); /* MMX 0x00218420: movq mm7, qword ptr [0x25a7e8] */

loc_00218427: ;
    mm4 = (uint64_t)(uint32_t)(MEM32((uint32_t)(edx))); /* MMX 0x00218427: movd mm4, dword ptr [edx] */
    mm0 = MMX_PXOR(mm0, mm0); /* MMX 0x0021842A: pxor mm0, mm0 */
    eax = 0; /* xor self */
    edx = edx + 4;
    SET_LO8(eax, MEM8(ebp));
    mm4 = MMX_PUNPCKLBW(mm4, mm0); /* MMX 0x00218435: punpcklbw mm4, mm0 */
    mm2 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29b738))); /* MMX 0x00218438: movd mm2, dword ptr [eax*4 + 0x29b738] */
    mm1 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29af38))); /* MMX 0x00218440: movd mm1, dword ptr [eax*4 + 0x29af38] */
    SET_LO8(eax, MEM8(ebp + 1));
    ebp = ebp + 2;
    mm4 = MMX_PSUBUSW(mm4, ((uint64_t)MEM32((uint32_t)(0x25a7d8)) | ((uint64_t)MEM32((uint32_t)(0x25a7d8) + 4u) << 32))); /* MMX 0x0021844E: psubusw mm4, qword ptr [0x25a7d8] */
    mm6 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29b738))); /* MMX 0x00218455: movd mm6, dword ptr [eax*4 + 0x29b738] */
    mm1 = MMX_PUNPCKLDQ(mm1, (uint64_t)MEM32((uint32_t)(eax*4 + 0x29af38))); /* MMX 0x0021845D: punpckldq mm1, dword ptr [eax*4 + 0x29af38] */
    SET_LO8(eax, MEM8(ebx));
    mm4 = MMX_PSLLW(mm4, 2u); /* MMX 0x00218467: psllw mm4, 2 */
    mm4 = MMX_PMULHW(mm4, ((uint64_t)MEM32((uint32_t)(0x25a7e0)) | ((uint64_t)MEM32((uint32_t)(0x25a7e0) + 4u) << 32))); /* MMX 0x0021846B: pmulhw mm4, qword ptr [0x25a7e0] */
    mm5 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29b338))); /* MMX 0x00218472: movd mm5, dword ptr [eax*4 + 0x29b338] */
    mm3 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29bb38))); /* MMX 0x0021847A: movd mm3, dword ptr [eax*4 + 0x29bb38] */
    mm2 = MMX_PADDW(mm2, mm5); /* MMX 0x00218482: paddw mm2, mm5 */
    SET_LO8(eax, MEM8(ebx + 1));
    ebx = ebx + 2;
    mm5 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29b338))); /* MMX 0x0021848B: movd mm5, dword ptr [eax*4 + 0x29b338] */
    mm3 = MMX_PUNPCKLDQ(mm3, (uint64_t)MEM32((uint32_t)(eax*4 + 0x29bb38))); /* MMX 0x00218493: punpckldq mm3, dword ptr [eax*4 + 0x29bb38] */
    mm6 = MMX_PADDW(mm6, mm5); /* MMX 0x0021849B: paddw mm6, mm5 */
    mm2 = MMX_PUNPCKLDQ(mm2, mm6); /* MMX 0x0021849E: punpckldq mm2, mm6 */
    mm1 = MMX_PADDW(mm1, mm4); /* MMX 0x002184A1: paddw mm1, mm4 */
    mm2 = MMX_PADDW(mm2, mm4); /* MMX 0x002184A4: paddw mm2, mm4 */
    mm1 = MMX_PADDSW(mm1, mm7); /* MMX 0x002184A7: paddsw mm1, mm7 */
    mm3 = MMX_PADDW(mm3, mm4); /* MMX 0x002184AA: paddw mm3, mm4 */
    mm1 = MMX_PSUBUSW(mm1, mm7); /* MMX 0x002184AD: psubusw mm1, mm7 */
    mm2 = MMX_PADDSW(mm2, mm7); /* MMX 0x002184B0: paddsw mm2, mm7 */
    mm4 = mm1; /* MMX 0x002184B3: movq mm4, mm1 */
    mm2 = MMX_PSUBUSW(mm2, mm7); /* MMX 0x002184B6: psubusw mm2, mm7 */
    mm1 = MMX_PUNPCKLWD(mm1, mm0); /* MMX 0x002184B9: punpcklwd mm1, mm0 */
    mm5 = mm2; /* MMX 0x002184BC: movq mm5, mm2 */
    mm2 = MMX_PUNPCKLWD(mm2, mm0); /* MMX 0x002184BF: punpcklwd mm2, mm0 */
    mm3 = MMX_PADDSW(mm3, mm7); /* MMX 0x002184C2: paddsw mm3, mm7 */
    mm2 = MMX_PSLLD(mm2, 8u); /* MMX 0x002184C5: pslld mm2, 8 */
    mm3 = MMX_PSUBUSW(mm3, mm7); /* MMX 0x002184C9: psubusw mm3, mm7 */
    mm4 = MMX_PUNPCKHWD(mm4, mm0); /* MMX 0x002184CC: punpckhwd mm4, mm0 */
    mm6 = mm3; /* MMX 0x002184CF: movq mm6, mm3 */
    mm3 = MMX_PUNPCKLWD(mm3, mm0); /* MMX 0x002184D2: punpcklwd mm3, mm0 */
    mm3 = MMX_PSLLD(mm3, 0x10u); /* MMX 0x002184D5: pslld mm3, 0x10 */
    mm1 = MMX_POR(mm1, mm2); /* MMX 0x002184D9: por mm1, mm2 */
    mm1 = MMX_POR(mm1, mm3); /* MMX 0x002184DC: por mm1, mm3 */
    mm5 = MMX_PUNPCKHWD(mm5, mm0); /* MMX 0x002184DF: punpckhwd mm5, mm0 */
    mm6 = MMX_PUNPCKHWD(mm6, mm0); /* MMX 0x002184E2: punpckhwd mm6, mm0 */
    mm5 = MMX_PSLLD(mm5, 8u); /* MMX 0x002184E5: pslld mm5, 8 */
    MEM32((uint32_t)(edi)) = (uint32_t)mm1; MEM32((uint32_t)(edi) + 4u) = (uint32_t)(mm1 >> 32); /* MMX 0x002184E9: movq qword ptr [edi], mm1 */
    mm6 = MMX_PSLLD(mm6, 0x10u); /* MMX 0x002184EC: pslld mm6, 0x10 */
    mm4 = MMX_POR(mm4, mm5); /* MMX 0x002184F0: por mm4, mm5 */
    edi = edi + 0x10;
    mm4 = MMX_POR(mm4, mm6); /* MMX 0x002184F6: por mm4, mm6 */
    eax = MEM32(0x299F14);
    MEM32((uint32_t)(edi - 8)) = (uint32_t)mm4; MEM32((uint32_t)(edi - 8) + 4u) = (uint32_t)(mm4 >> 32); /* MMX 0x002184FE: movq qword ptr [edi - 8], mm4 */
    _fa = (uint32_t)(edi) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edi, eax (32-bit) */
    if (CMP_B(_fa, _fb)) goto loc_00218427; /* jb: below (unsigned <) */

loc_0021850A: ;
    MEM32(0x299F1C) = edx;
    MEM32(0x299F20) = ebp;
    MEM32(0x299F24) = ebx;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebp);
    POP32(esp, ebx);
    esp += 8; return; /* ret 4 */

}

/**
 * sub_00218890
 * Original: 0x00218890 - 0x00218944 (180 bytes, 51 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00218890(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_00218890: ;
    PUSH32(esp, ebx);
    PUSH32(esp, ebp);
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    edi = MEM32(esp + 0x14);
    esi = edi;
    ebx = 8;
    /* nop */

loc_002188A0: ;
    edx = MEM32(0x299F28);
    eax = ZX8(MEM8(edx));
    ecx = MEM32(0x299F18);
    ebp = ZX8(MEM8(ecx));
    eax = eax << 0x18;
    eax = eax | MEM32(ebp * 4 + 0x299B10);
    edx++;
    ecx++;
    MEM32(0x299F18) = ecx;
    ecx = MEM32(0x299F10);
    MEM32(0x299F28) = edx;
    MEM32(ecx) = eax;
    edx = MEM32(0x299F10);
    MEM32(edx + 4) = eax;
    edx = MEM32(0x299F2C);
    eax = ZX8(MEM8(edx));
    ecx = MEM32(0x299F1C);
    ebp = ZX8(MEM8(ecx));
    eax = eax << 0x18;
    eax = eax | MEM32(ebp * 4 + 0x299B10);
    edx++;
    ecx++;
    MEM32(0x299F1C) = ecx;
    ecx = MEM32(0x299F14);
    MEM32(0x299F2C) = edx;
    MEM32(ecx) = eax;
    edx = MEM32(0x299F14);
    MEM32(edx + 4) = eax;
    edx = MEM32(0x299F10);
    ecx = MEM32(0x299F14);
    edx = edx + ebx;
    ecx = ecx + ebx;
    esi--;
    MEM32(0x299F10) = edx;
    MEM32(0x299F14) = ecx;
    if ((esi != 0)) goto loc_002188A0; /* jne: not equal / not zero */

loc_00218939: ;
    eax = MEM32(esp + 0x18);
    eax = eax + edi;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebp);
    POP32(esp, ebx);
    esp += 4; return; /* ret */

}

/**
 * sub_00218950
 * Original: 0x00218950 - 0x002189B9 (105 bytes, 33 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00218950(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00218950: ;
    PUSH32(esp, esi);
    esi = MEM32(esp + 0xC);
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(esi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test esi, esi (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_002189B7; /* je: equal / zero */

loc_00218959: ;
    PUSH32(esp, ebx);
    PUSH32(esp, edi);
    goto loc_00218960;

    /* nop */

loc_00218960: ;
    ecx = MEM32(0x299F18);
    edi = ZX8(MEM8(ecx));
    edx = MEM32(0x299F28);
    eax = ZX8(MEM8(edx));
    ebx = MEM32(edi * 4 + 0x299B10);
    eax = eax << 0x18;
    eax = eax | ebx;
    edx++;
    ecx++;
    MEM32(0x299F18) = ecx;
    ecx = MEM32(0x299F10);
    MEM32(0x299F28) = edx;
    MEM32(ecx) = eax;
    edx = MEM32(0x299F10);
    ecx = MEM32(0x299F30);
    MEM32(ecx + edx) = eax;
    ecx = MEM32(0x299F10);
    ecx = ecx + 4;
    esi--;
    MEM32(0x299F10) = ecx;
    if ((esi != 0)) goto loc_00218960; /* jne: not equal / not zero */

loc_002189B5: ;
    POP32(esp, edi);
    POP32(esp, ebx);

loc_002189B7: ;
    POP32(esp, esi);
    esp += 4; return; /* ret */

}

/**
 * sub_002189C0
 * Original: 0x002189C0 - 0x00218A80 (192 bytes, 53 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_002189C0(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_002189C0: ;
    PUSH32(esp, ebx);
    PUSH32(esp, ebp);
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    edi = MEM32(esp + 0x14);
    esi = edi;
    ebx = 4;
    /* nop */

loc_002189D0: ;
    edx = MEM32(0x299F28);
    eax = ZX8(MEM8(edx));
    ecx = MEM32(0x299F18);
    ebp = ZX8(MEM8(ecx));
    eax = eax << 0x18;
    eax = eax | MEM32(ebp * 4 + 0x299B10);
    edx++;
    ecx++;
    MEM32(0x299F18) = ecx;
    ecx = MEM32(0x299F10);
    MEM32(0x299F28) = edx;
    MEM32(ecx) = eax;
    ecx = MEM32(0x299F10);
    edx = MEM32(0x299F30);
    MEM32(edx + ecx) = eax;
    edx = MEM32(0x299F2C);
    eax = ZX8(MEM8(edx));
    ecx = MEM32(0x299F1C);
    ebp = ZX8(MEM8(ecx));
    eax = eax << 0x18;
    eax = eax | MEM32(ebp * 4 + 0x299B10);
    edx++;
    MEM32(0x299F2C) = edx;
    edx = MEM32(0x299F14);
    ecx++;
    MEM32(0x299F1C) = ecx;
    MEM32(edx) = eax;
    ecx = MEM32(0x299F14);
    edx = MEM32(0x299F30);
    MEM32(ecx + edx) = eax;
    edx = MEM32(0x299F10);
    ecx = MEM32(0x299F14);
    edx = edx + ebx;
    ecx = ecx + ebx;
    esi--;
    MEM32(0x299F10) = edx;
    MEM32(0x299F14) = ecx;
    if ((esi != 0)) goto loc_002189D0; /* jne: not equal / not zero */

loc_00218A75: ;
    eax = MEM32(esp + 0x18);
    eax = eax + edi;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebp);
    POP32(esp, ebx);
    esp += 4; return; /* ret */

}

/**
 * sub_00218B10
 * Original: 0x00218B10 - 0x00218C02 (242 bytes, 63 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00218B10(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_00218B10: ;
    PUSH32(esp, ebx);
    PUSH32(esp, ebp);
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    edi = MEM32(esp + 0x14);
    esi = edi;
    ebx = 8;
    /* nop */

loc_00218B20: ;
    edx = MEM32(0x299F28);
    eax = ZX8(MEM8(edx));
    ecx = MEM32(0x299F18);
    ebp = ZX8(MEM8(ecx));
    eax = eax << 0x18;
    eax = eax | MEM32(ebp * 4 + 0x299B10);
    edx++;
    MEM32(0x299F28) = edx;
    ecx++;
    MEM32(0x299F18) = ecx;
    ecx = MEM32(0x299F10);
    MEM32(ecx) = eax;
    edx = MEM32(0x299F10);
    MEM32(edx + 4) = eax;
    edx = MEM32(0x299F10);
    ecx = MEM32(0x299F30);
    MEM32(ecx + edx) = eax;
    edx = MEM32(0x299F10);
    ecx = MEM32(0x299F30);
    MEM32(ecx + edx + 4) = eax;
    edx = MEM32(0x299F2C);
    eax = ZX8(MEM8(edx));
    ecx = MEM32(0x299F1C);
    ebp = ZX8(MEM8(ecx));
    eax = eax << 0x18;
    eax = eax | MEM32(ebp * 4 + 0x299B10);
    edx++;
    ecx++;
    MEM32(0x299F1C) = ecx;
    ecx = MEM32(0x299F14);
    MEM32(0x299F2C) = edx;
    MEM32(ecx) = eax;
    edx = MEM32(0x299F14);
    MEM32(edx + 4) = eax;
    ecx = MEM32(0x299F14);
    edx = MEM32(0x299F30);
    MEM32(ecx + edx) = eax;
    ecx = MEM32(0x299F14);
    edx = MEM32(0x299F30);
    MEM32(ecx + edx + 4) = eax;
    edx = MEM32(0x299F10);
    ecx = MEM32(0x299F14);
    edx = edx + ebx;
    ecx = ecx + ebx;
    esi--;
    MEM32(0x299F10) = edx;
    MEM32(0x299F14) = ecx;
    if ((esi != 0)) goto loc_00218B20; /* jne: not equal / not zero */

loc_00218BF7: ;
    eax = MEM32(esp + 0x18);
    eax = eax + edi;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebp);
    POP32(esp, ebx);
    esp += 4; return; /* ret */

}

/**
 * sub_00218C10
 * Original: 0x00218C10 - 0x00218CEC (220 bytes, 63 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00218C10(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_00218C10: ;
    eax = MEM32(esp + 8);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    PUSH32(esp, ebx);
    ebx = MEM32(esp + 8);
    if (TEST_Z(_fa, _fb)) goto loc_00218CEA; /* je: equal / zero */

loc_00218C21: ;
    PUSH32(esp, ebp);
    PUSH32(esp, esi);
    MEM32(esp + 0x10) = eax;
    PUSH32(esp, edi);
    goto loc_00218C30;

    /* nop */

loc_00218C30: ;
    eax = MEM32(0x299F20);
    eax = ZX8(MEM8(eax));
    ecx = MEM32(0x299F24);
    ecx = ZX8(MEM8(ecx));
    ebp = MEM32(0x299F28);
    ecx = ecx << 2;
    edx = MEM32(ecx + 0x29A338);
    eax = eax << 2;
    edi = MEM32(eax + 0x29A738);
    esi = MEM32(eax + 0x299F38);
    edx = edx + edi;
    edi = MEM32(ecx + 0x29AB38);
    ecx = MEM32(0x299F18);
    eax = ZX8(MEM8(ecx));
    eax = MEM32(eax * 4 + 0x295EC0);
    ecx++;
    MEM32(0x299F18) = ecx;
    ecx = 0; /* xor self */
    SET_HI8(ecx, MEM8(ebp));
    ecx = ecx | MEM32(eax + edi * 4);
    edi = MEM32(eax + edx * 4);
    edx = MEM32(0x299F10);
    ecx = ecx << 8;
    ecx = ecx | edi;
    edi = MEM32(eax + esi * 4);
    ecx = ecx << 8;
    ecx = ecx | edi;
    ebp++;
    eax = ecx;
    MEM32(0x299F28) = ebp;
    MEM32(edx) = eax;
    ecx = MEM32(0x299F10);
    MEM32(ecx + 4) = eax;
    edx = MEM32(0x299F10);
    edx = edx + 8;
    ebx++;
    _fa = (uint32_t)(LO8(ebx)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(ebx), 1 (8-bit) */
    MEM32(0x299F10) = edx;
    if (TEST_NZ(_fa, _fb)) goto loc_00218CDD; /* jne: not equal / not zero */

loc_00218CC5: ;
    ecx = MEM32(0x299F20);
    eax = MEM32(0x299F24);
    ecx++;
    eax++;
    MEM32(0x299F20) = ecx;
    MEM32(0x299F24) = eax;

loc_00218CDD: ;
    MEM32(esp + 0x14) = MEM32(esp + 0x14) - 1;
    if ((MEM32(esp + 0x14) != 0)) goto loc_00218C30; /* jne: not equal / not zero */

loc_00218CE7: ;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebp);

loc_00218CEA: ;
    POP32(esp, ebx);
    esp += 4; return; /* ret */

}

/**
 * sub_00218CF0
 * Original: 0x00218CF0 - 0x00218E1B (299 bytes, 83 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00218CF0(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_00218CF0: ;
    ecx = MEM32(esp + 4);
    eax = MEM32(esp + 8);
    PUSH32(esp, ebx);
    PUSH32(esp, ebp);
    PUSH32(esp, esi);
    MEM32(esp + 0x14) = ecx;
    PUSH32(esp, edi);

loc_00218D00: ;
    edx = MEM32(0x299F20);
    ecx = ZX8(MEM8(edx));
    edx = MEM32(0x299F24);
    edx = ZX8(MEM8(edx));
    ebp = MEM32(0x299F28);
    ecx = ecx << 2;
    ebx = MEM32(ecx + 0x29A738);
    edi = MEM32(ecx + 0x299F38);
    edx = edx << 2;
    esi = MEM32(edx + 0x29A338);
    esi = esi + ebx;
    ebx = MEM32(0x299F18);
    ecx = ZX8(MEM8(ebx));
    ecx = MEM32(ecx * 4 + 0x295EC0);
    edx = MEM32(edx + 0x29AB38);
    ebx++;
    MEM32(0x299F18) = ebx;
    ebx = 0; /* xor self */
    SET_HI8(ebx, MEM8(ebp));
    ebx = ebx | MEM32(ecx + edx * 4);
    ebx = ebx << 8;
    ebx = ebx | MEM32(ecx + esi * 4);
    ebx = ebx << 8;
    ebx = ebx | MEM32(ecx + edi * 4);
    ebp++;
    ecx = ebx;
    ebx = MEM32(0x299F10);
    MEM32(0x299F28) = ebp;
    MEM32(ebx) = ecx;
    ebx = MEM32(0x299F10);
    MEM32(ebx + 4) = ecx;
    ebx = MEM32(0x299F1C);
    ecx = ZX8(MEM8(ebx));
    ebp = MEM32(0x299F2C);
    ecx = MEM32(ecx * 4 + 0x295EC0);
    ebx++;
    MEM32(0x299F1C) = ebx;
    ebx = 0; /* xor self */
    SET_HI8(ebx, MEM8(ebp));
    ebx = ebx | MEM32(ecx + edx * 4);
    edx = MEM32(ecx + esi * 4);
    ebx = ebx << 8;
    ebx = ebx | edx;
    edx = MEM32(ecx + edi * 4);
    ebx = ebx << 8;
    ebx = ebx | edx;
    edx = MEM32(0x299F14);
    ebp++;
    ecx = ebx;
    MEM32(0x299F2C) = ebp;
    MEM32(edx) = ecx;
    edx = MEM32(0x299F14);
    MEM32(edx + 4) = ecx;
    edi = MEM32(0x299F10);
    esi = MEM32(0x299F14);
    ecx = 8;
    edi = edi + ecx;
    esi = esi + ecx;
    eax++;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), 1 (8-bit) */
    MEM32(0x299F10) = edi;
    MEM32(0x299F14) = esi;
    if (TEST_NZ(_fa, _fb)) goto loc_00218E0C; /* jne: not equal / not zero */

loc_00218DF2: ;
    edx = MEM32(0x299F20);
    ecx = MEM32(0x299F24);
    edx++;
    ecx++;
    MEM32(0x299F20) = edx;
    MEM32(0x299F24) = ecx;

loc_00218E0C: ;
    MEM32(esp + 0x18) = MEM32(esp + 0x18) - 1;
    if ((MEM32(esp + 0x18) != 0)) goto loc_00218D00; /* jne: not equal / not zero */

loc_00218E16: ;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebp);
    POP32(esp, ebx);
    esp += 4; return; /* ret */

}

/**
 * sub_00218E20
 * Original: 0x00218E20 - 0x00218F02 (226 bytes, 64 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00218E20(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_00218E20: ;
    eax = MEM32(esp + 8);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    PUSH32(esp, ebx);
    ebx = MEM32(esp + 8);
    if (TEST_Z(_fa, _fb)) goto loc_00218F00; /* je: equal / zero */

loc_00218E31: ;
    PUSH32(esp, ebp);
    PUSH32(esp, esi);
    MEM32(esp + 0x10) = eax;
    PUSH32(esp, edi);
    goto loc_00218E40;

    /* nop */

loc_00218E40: ;
    eax = MEM32(0x299F20);
    eax = ZX8(MEM8(eax));
    ecx = MEM32(0x299F24);
    ecx = ZX8(MEM8(ecx));
    ebp = MEM32(0x299F28);
    ecx = ecx << 2;
    edx = MEM32(ecx + 0x29A338);
    eax = eax << 2;
    edi = MEM32(eax + 0x29A738);
    esi = MEM32(eax + 0x299F38);
    edx = edx + edi;
    edi = MEM32(ecx + 0x29AB38);
    ecx = MEM32(0x299F18);
    eax = ZX8(MEM8(ecx));
    eax = MEM32(eax * 4 + 0x295EC0);
    ecx++;
    MEM32(0x299F18) = ecx;
    ecx = 0; /* xor self */
    SET_HI8(ecx, MEM8(ebp));
    ecx = ecx | MEM32(eax + edi * 4);
    edi = MEM32(eax + edx * 4);
    edx = MEM32(0x299F10);
    ecx = ecx << 8;
    ecx = ecx | edi;
    edi = MEM32(eax + esi * 4);
    ecx = ecx << 8;
    ecx = ecx | edi;
    ebp++;
    eax = ecx;
    MEM32(0x299F28) = ebp;
    MEM32(edx) = eax;
    ecx = MEM32(0x299F10);
    edx = MEM32(0x299F30);
    MEM32(edx + ecx) = eax;
    edx = MEM32(0x299F10);
    edx = edx + 4;
    ebx++;
    _fa = (uint32_t)(LO8(ebx)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(ebx), 1 (8-bit) */
    MEM32(0x299F10) = edx;
    if (TEST_NZ(_fa, _fb)) goto loc_00218EF3; /* jne: not equal / not zero */

loc_00218EDB: ;
    ecx = MEM32(0x299F20);
    eax = MEM32(0x299F24);
    ecx++;
    eax++;
    MEM32(0x299F20) = ecx;
    MEM32(0x299F24) = eax;

loc_00218EF3: ;
    MEM32(esp + 0x14) = MEM32(esp + 0x14) - 1;
    if ((MEM32(esp + 0x14) != 0)) goto loc_00218E40; /* jne: not equal / not zero */

loc_00218EFD: ;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebp);

loc_00218F00: ;
    POP32(esp, ebx);
    esp += 4; return; /* ret */

}

/**
 * sub_00218F10
 * Original: 0x00218F10 - 0x00219047 (311 bytes, 85 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00218F10(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_00218F10: ;
    ecx = MEM32(esp + 4);
    eax = MEM32(esp + 8);
    PUSH32(esp, ebx);
    PUSH32(esp, ebp);
    PUSH32(esp, esi);
    MEM32(esp + 0x14) = ecx;
    PUSH32(esp, edi);

loc_00218F20: ;
    edx = MEM32(0x299F20);
    ecx = ZX8(MEM8(edx));
    edx = MEM32(0x299F24);
    edx = ZX8(MEM8(edx));
    ebp = MEM32(0x299F28);
    ecx = ecx << 2;
    ebx = MEM32(ecx + 0x29A738);
    edi = MEM32(ecx + 0x299F38);
    edx = edx << 2;
    esi = MEM32(edx + 0x29A338);
    esi = esi + ebx;
    ebx = MEM32(0x299F18);
    ecx = ZX8(MEM8(ebx));
    ecx = MEM32(ecx * 4 + 0x295EC0);
    edx = MEM32(edx + 0x29AB38);
    ebx++;
    MEM32(0x299F18) = ebx;
    ebx = 0; /* xor self */
    SET_HI8(ebx, MEM8(ebp));
    ebx = ebx | MEM32(ecx + edx * 4);
    ebx = ebx << 8;
    ebx = ebx | MEM32(ecx + esi * 4);
    ebx = ebx << 8;
    ebx = ebx | MEM32(ecx + edi * 4);
    ebp++;
    ecx = ebx;
    ebx = MEM32(0x299F10);
    MEM32(0x299F28) = ebp;
    MEM32(ebx) = ecx;
    ebp = MEM32(0x299F10);
    ebx = MEM32(0x299F30);
    MEM32(ebx + ebp) = ecx;
    ebx = MEM32(0x299F1C);
    ecx = ZX8(MEM8(ebx));
    ebp = MEM32(0x299F2C);
    ecx = MEM32(ecx * 4 + 0x295EC0);
    ebx++;
    MEM32(0x299F1C) = ebx;
    ebx = 0; /* xor self */
    SET_HI8(ebx, MEM8(ebp));
    ebx = ebx | MEM32(ecx + edx * 4);
    edx = MEM32(ecx + esi * 4);
    ebx = ebx << 8;
    ebx = ebx | edx;
    edx = MEM32(ecx + edi * 4);
    ebx = ebx << 8;
    ebx = ebx | edx;
    edx = MEM32(0x299F14);
    ebp++;
    ecx = ebx;
    MEM32(0x299F2C) = ebp;
    MEM32(edx) = ecx;
    edx = MEM32(0x299F14);
    esi = MEM32(0x299F30);
    MEM32(edx + esi) = ecx;
    edi = MEM32(0x299F10);
    esi = MEM32(0x299F14);
    ecx = 4;
    edi = edi + ecx;
    esi = esi + ecx;
    eax++;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), 1 (8-bit) */
    MEM32(0x299F10) = edi;
    MEM32(0x299F14) = esi;
    if (TEST_NZ(_fa, _fb)) goto loc_00219038; /* jne: not equal / not zero */

loc_0021901E: ;
    edx = MEM32(0x299F20);
    ecx = MEM32(0x299F24);
    edx++;
    ecx++;
    MEM32(0x299F20) = edx;
    MEM32(0x299F24) = ecx;

loc_00219038: ;
    MEM32(esp + 0x18) = MEM32(esp + 0x18) - 1;
    if ((MEM32(esp + 0x18) != 0)) goto loc_00218F20; /* jne: not equal / not zero */

loc_00219042: ;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebp);
    POP32(esp, ebx);
    esp += 4; return; /* ret */

}

/**
 * sub_00219050
 * Original: 0x00219050 - 0x0021914B (251 bytes, 69 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00219050(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_00219050: ;
    eax = MEM32(esp + 8);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    PUSH32(esp, ebx);
    ebx = MEM32(esp + 8);
    if (TEST_Z(_fa, _fb)) goto loc_00219149; /* je: equal / zero */

loc_00219061: ;
    PUSH32(esp, ebp);
    PUSH32(esp, esi);
    MEM32(esp + 0x10) = eax;
    PUSH32(esp, edi);
    goto loc_00219070;

    /* nop */

loc_00219070: ;
    eax = MEM32(0x299F20);
    eax = ZX8(MEM8(eax));
    ecx = MEM32(0x299F24);
    ecx = ZX8(MEM8(ecx));
    ebp = MEM32(0x299F28);
    ecx = ecx << 2;
    edx = MEM32(ecx + 0x29A338);
    eax = eax << 2;
    edi = MEM32(eax + 0x29A738);
    esi = MEM32(eax + 0x299F38);
    edx = edx + edi;
    edi = MEM32(ecx + 0x29AB38);
    ecx = MEM32(0x299F18);
    eax = ZX8(MEM8(ecx));
    eax = MEM32(eax * 4 + 0x295EC0);
    ecx++;
    MEM32(0x299F18) = ecx;
    ecx = 0; /* xor self */
    SET_HI8(ecx, MEM8(ebp));
    ecx = ecx | MEM32(eax + edi * 4);
    edi = MEM32(eax + edx * 4);
    edx = MEM32(0x299F10);
    ecx = ecx << 8;
    ecx = ecx | edi;
    edi = MEM32(eax + esi * 4);
    ecx = ecx << 8;
    ecx = ecx | edi;
    eax = ecx;
    ebp++;
    MEM32(0x299F28) = ebp;
    MEM32(edx) = eax;
    ecx = MEM32(0x299F10);
    MEM32(ecx + 4) = eax;
    ecx = MEM32(0x299F10);
    edx = MEM32(0x299F30);
    MEM32(edx + ecx) = eax;
    edx = MEM32(0x299F10);
    ecx = MEM32(0x299F30);
    MEM32(ecx + edx + 4) = eax;
    edx = MEM32(0x299F10);
    edx = edx + 8;
    ebx++;
    _fa = (uint32_t)(LO8(ebx)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(ebx), 1 (8-bit) */
    MEM32(0x299F10) = edx;
    if (TEST_NZ(_fa, _fb)) goto loc_0021913C; /* jne: not equal / not zero */

loc_00219124: ;
    ecx = MEM32(0x299F20);
    eax = MEM32(0x299F24);
    ecx++;
    eax++;
    MEM32(0x299F20) = ecx;
    MEM32(0x299F24) = eax;

loc_0021913C: ;
    MEM32(esp + 0x14) = MEM32(esp + 0x14) - 1;
    if ((MEM32(esp + 0x14) != 0)) goto loc_00219070; /* jne: not equal / not zero */

loc_00219146: ;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebp);

loc_00219149: ;
    POP32(esp, ebx);
    esp += 4; return; /* ret */

}

/**
 * sub_00219150
 * Original: 0x00219150 - 0x002192B9 (361 bytes, 95 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00219150(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_00219150: ;
    ecx = MEM32(esp + 4);
    eax = MEM32(esp + 8);
    PUSH32(esp, ebx);
    PUSH32(esp, ebp);
    PUSH32(esp, esi);
    MEM32(esp + 0x14) = ecx;
    PUSH32(esp, edi);

loc_00219160: ;
    edx = MEM32(0x299F20);
    ecx = ZX8(MEM8(edx));
    edx = MEM32(0x299F24);
    edx = ZX8(MEM8(edx));
    ebp = MEM32(0x299F28);
    ecx = ecx << 2;
    ebx = MEM32(ecx + 0x29A738);
    edi = MEM32(ecx + 0x299F38);
    edx = edx << 2;
    esi = MEM32(edx + 0x29A338);
    edx = MEM32(edx + 0x29AB38);
    esi = esi + ebx;
    ebx = MEM32(0x299F18);
    ecx = ZX8(MEM8(ebx));
    ecx = MEM32(ecx * 4 + 0x295EC0);
    ebx++;
    MEM32(0x299F18) = ebx;
    ebx = 0; /* xor self */
    SET_HI8(ebx, MEM8(ebp));
    ebx = ebx | MEM32(ecx + edx * 4);
    ebx = ebx << 8;
    ebx = ebx | MEM32(ecx + esi * 4);
    ebx = ebx << 8;
    ebx = ebx | MEM32(ecx + edi * 4);
    ebp++;
    ecx = ebx;
    ebx = MEM32(0x299F10);
    MEM32(0x299F28) = ebp;
    MEM32(ebx) = ecx;
    ebx = MEM32(0x299F10);
    MEM32(ebx + 4) = ecx;
    ebp = MEM32(0x299F10);
    ebx = MEM32(0x299F30);
    MEM32(ebx + ebp) = ecx;
    ebp = MEM32(0x299F10);
    ebx = MEM32(0x299F30);
    MEM32(ebx + ebp + 4) = ecx;
    ebx = MEM32(0x299F1C);
    ecx = ZX8(MEM8(ebx));
    ebp = MEM32(0x299F2C);
    ecx = MEM32(ecx * 4 + 0x295EC0);
    ebx++;
    MEM32(0x299F1C) = ebx;
    ebx = 0; /* xor self */
    SET_HI8(ebx, MEM8(ebp));
    ebx = ebx | MEM32(ecx + edx * 4);
    edx = MEM32(ecx + esi * 4);
    ebx = ebx << 8;
    ebx = ebx | edx;
    edx = MEM32(ecx + edi * 4);
    ebx = ebx << 8;
    ebx = ebx | edx;
    edx = MEM32(0x299F14);
    ecx = ebx;
    ebp++;
    MEM32(0x299F2C) = ebp;
    MEM32(edx) = ecx;
    edx = MEM32(0x299F14);
    MEM32(edx + 4) = ecx;
    edx = MEM32(0x299F14);
    esi = MEM32(0x299F30);
    MEM32(edx + esi) = ecx;
    edx = MEM32(0x299F14);
    esi = MEM32(0x299F30);
    MEM32(edx + esi + 4) = ecx;
    edi = MEM32(0x299F10);
    esi = MEM32(0x299F14);
    ecx = 8;
    edi = edi + ecx;
    esi = esi + ecx;
    eax++;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), 1 (8-bit) */
    MEM32(0x299F10) = edi;
    MEM32(0x299F14) = esi;
    if (TEST_NZ(_fa, _fb)) goto loc_002192AA; /* jne: not equal / not zero */

loc_00219290: ;
    edx = MEM32(0x299F20);
    ecx = MEM32(0x299F24);
    edx++;
    ecx++;
    MEM32(0x299F20) = edx;
    MEM32(0x299F24) = ecx;

loc_002192AA: ;
    MEM32(esp + 0x18) = MEM32(esp + 0x18) - 1;
    if ((MEM32(esp + 0x18) != 0)) goto loc_00219160; /* jne: not equal / not zero */

loc_002192B4: ;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebp);
    POP32(esp, ebx);
    esp += 4; return; /* ret */

}

/**
 * sub_002192C0
 * Original: 0x002192C0 - 0x00219324 (100 bytes, 27 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_002192C0(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_002192C0: ;
    eax = MEM32(esp + 8);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00219323; /* je: equal / zero */

loc_002192C8: ;
    PUSH32(esp, esi);
    /* nop */

loc_002192D0: ;
    ecx = MEM32(0x299F18);
    edx = ZX8(MEM8(ecx));
    ecx = MEM32(0x299F28);
    ecx = ZX8(MEM8(ecx));
    esi = MEM32(edx * 4 + 0x299B10);
    edx = MEM32(0x299F10);
    ecx = ecx << 0x18;
    ecx = ecx | esi;
    MEM32(edx) = ecx;
    edx = MEM32(0x299F28);
    ecx = MEM32(0x299F18);
    edx++;
    MEM32(0x299F28) = edx;
    edx = MEM32(0x299F10);
    ecx++;
    edx = edx + 4;
    eax--;
    MEM32(0x299F18) = ecx;
    MEM32(0x299F10) = edx;
    if ((eax != 0)) goto loc_002192D0; /* jne: not equal / not zero */

loc_00219322: ;
    POP32(esp, esi);

loc_00219323: ;
    esp += 4; return; /* ret */

}

/**
 * sub_00219330
 * Original: 0x00219330 - 0x002193ED (189 bytes, 51 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00219330(void)
{
    int _flags = 0; /* fallback flag var */

loc_00219330: ;
    ecx = MEM32(esp + 4);
    PUSH32(esp, ebx);
    PUSH32(esp, esi);
    eax = ecx;
    edx = 4;
    PUSH32(esp, edi);
    edi = edi;

loc_00219340: ;
    esi = MEM32(0x299F18);
    esi = ZX8(MEM8(esi));
    ebx = MEM32(esi * 4 + 0x299B10);
    edi = MEM32(0x299F28);
    edi = ZX8(MEM8(edi));
    esi = MEM32(0x299F10);
    edi = edi << 0x18;
    edi = edi | ebx;
    MEM32(esi) = edi;
    edi = MEM32(0x299F28);
    esi = MEM32(0x299F18);
    edi++;
    esi++;
    MEM32(0x299F28) = edi;
    edi = MEM32(0x299F2C);
    MEM32(0x299F18) = esi;
    edi = ZX8(MEM8(edi));
    esi = MEM32(0x299F1C);
    esi = ZX8(MEM8(esi));
    ebx = MEM32(esi * 4 + 0x299B10);
    esi = MEM32(0x299F14);
    edi = edi << 0x18;
    edi = edi | ebx;
    MEM32(esi) = edi;
    esi = MEM32(0x299F2C);
    edi = MEM32(0x299F1C);
    esi++;
    edi++;
    MEM32(0x299F2C) = esi;
    esi = MEM32(0x299F10);
    MEM32(0x299F1C) = edi;
    edi = MEM32(0x299F14);
    esi = esi + edx;
    edi = edi + edx;
    eax--;
    MEM32(0x299F10) = esi;
    MEM32(0x299F14) = edi;
    if ((eax != 0)) goto loc_00219340; /* jne: not equal / not zero */

loc_002193E3: ;
    eax = MEM32(esp + 0x14);
    POP32(esp, edi);
    POP32(esp, esi);
    eax = eax + ecx;
    POP32(esp, ebx);
    esp += 4; return; /* ret */

}

/**
 * sub_002193F0
 * Original: 0x002193F0 - 0x002194C9 (217 bytes, 62 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_002193F0(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_002193F0: ;
    eax = MEM32(esp + 8);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    PUSH32(esp, ebx);
    ebx = MEM32(esp + 8);
    if (TEST_Z(_fa, _fb)) goto loc_002194C7; /* je: equal / zero */

loc_00219401: ;
    PUSH32(esp, ebp);
    PUSH32(esp, esi);
    MEM32(esp + 0x10) = eax;
    PUSH32(esp, edi);
    goto loc_00219410;

    /* nop */

loc_00219410: ;
    eax = MEM32(0x299F20);
    eax = ZX8(MEM8(eax));
    ecx = MEM32(0x299F24);
    ecx = ZX8(MEM8(ecx));
    ebp = MEM32(0x299F28);
    ecx = ecx << 2;
    edx = MEM32(ecx + 0x29A338);
    eax = eax << 2;
    edi = MEM32(eax + 0x29A738);
    esi = MEM32(eax + 0x299F38);
    edx = edx + edi;
    edi = MEM32(ecx + 0x29AB38);
    ecx = MEM32(0x299F18);
    eax = ZX8(MEM8(ecx));
    eax = MEM32(eax * 4 + 0x295EC0);
    ecx++;
    MEM32(0x299F18) = ecx;
    ecx = 0; /* xor self */
    SET_HI8(ecx, MEM8(ebp));
    ebp = MEM32(eax + edi * 4);
    edi = MEM32(eax + edx * 4);
    edx = MEM32(0x299F10);
    ecx = ecx | ebp;
    ecx = ecx << 8;
    ecx = ecx | edi;
    edi = MEM32(eax + esi * 4);
    ecx = ecx << 8;
    ecx = ecx | edi;
    MEM32(edx) = ecx;
    esi = MEM32(0x299F28);
    edx = MEM32(0x299F10);
    esi++;
    edx = edx + 4;
    ebx++;
    _fa = (uint32_t)(LO8(ebx)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(ebx), 1 (8-bit) */
    MEM32(0x299F28) = esi;
    MEM32(0x299F10) = edx;
    if (TEST_NZ(_fa, _fb)) goto loc_002194BA; /* jne: not equal / not zero */

loc_002194A2: ;
    ecx = MEM32(0x299F20);
    eax = MEM32(0x299F24);
    ecx++;
    eax++;
    MEM32(0x299F20) = ecx;
    MEM32(0x299F24) = eax;

loc_002194BA: ;
    MEM32(esp + 0x14) = MEM32(esp + 0x14) - 1;
    if ((MEM32(esp + 0x14) != 0)) goto loc_00219410; /* jne: not equal / not zero */

loc_002194C4: ;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebp);

loc_002194C7: ;
    POP32(esp, ebx);
    esp += 4; return; /* ret */

}

/**
 * sub_002194D0
 * Original: 0x002194D0 - 0x002195F8 (296 bytes, 82 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_002194D0(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_002194D0: ;
    ecx = MEM32(esp + 4);
    eax = MEM32(esp + 8);
    PUSH32(esp, ebx);
    PUSH32(esp, ebp);
    PUSH32(esp, esi);
    MEM32(esp + 0x14) = ecx;
    PUSH32(esp, edi);

loc_002194E0: ;
    edx = MEM32(0x299F20);
    ecx = ZX8(MEM8(edx));
    edx = MEM32(0x299F24);
    edx = ZX8(MEM8(edx));
    ebp = MEM32(0x299F28);
    ecx = ecx << 2;
    ebx = MEM32(ecx + 0x29A738);
    edi = MEM32(ecx + 0x299F38);
    edx = edx << 2;
    esi = MEM32(edx + 0x29A338);
    esi = esi + ebx;
    ebx = MEM32(0x299F18);
    ecx = ZX8(MEM8(ebx));
    ecx = MEM32(ecx * 4 + 0x295EC0);
    edx = MEM32(edx + 0x29AB38);
    ebx++;
    MEM32(0x299F18) = ebx;
    ebx = 0; /* xor self */
    SET_HI8(ebx, MEM8(ebp));
    ebx = ebx | MEM32(ecx + edx * 4);
    ebp = MEM32(ecx + esi * 4);
    ebx = ebx << 8;
    ebx = ebx | ebp;
    ebp = MEM32(ecx + edi * 4);
    ecx = MEM32(0x299F10);
    ebx = ebx << 8;
    ebx = ebx | ebp;
    MEM32(ecx) = ebx;
    ecx = MEM32(0x299F28);
    ebx = MEM32(0x299F1C);
    ebp = MEM32(0x299F2C);
    ecx++;
    ebx++;
    MEM32(0x299F28) = ecx;
    ecx = ZX8(MEM8(ebx + -1));
    ecx = MEM32(ecx * 4 + 0x295EC0);
    MEM32(0x299F1C) = ebx;
    ebx = 0; /* xor self */
    SET_HI8(ebx, MEM8(ebp));
    ebp = MEM32(ecx + edx * 4);
    edx = MEM32(0x299F14);
    ebx = ebx | ebp;
    ebp = MEM32(ecx + esi * 4);
    ebx = ebx << 8;
    ebx = ebx | ebp;
    ebp = MEM32(ecx + edi * 4);
    ebx = ebx << 8;
    ebx = ebx | ebp;
    MEM32(edx) = ebx;
    ebx = MEM32(0x299F2C);
    edi = MEM32(0x299F10);
    esi = MEM32(0x299F14);
    ecx = 4;
    ebx++;
    edi = edi + ecx;
    esi = esi + ecx;
    eax++;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), 1 (8-bit) */
    MEM32(0x299F2C) = ebx;
    MEM32(0x299F10) = edi;
    MEM32(0x299F14) = esi;
    if (TEST_NZ(_fa, _fb)) goto loc_002195E9; /* jne: not equal / not zero */

loc_002195CF: ;
    edx = MEM32(0x299F20);
    ecx = MEM32(0x299F24);
    edx++;
    ecx++;
    MEM32(0x299F20) = edx;
    MEM32(0x299F24) = ecx;

loc_002195E9: ;
    MEM32(esp + 0x18) = MEM32(esp + 0x18) - 1;
    if ((MEM32(esp + 0x18) != 0)) goto loc_002194E0; /* jne: not equal / not zero */

loc_002195F3: ;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebp);
    POP32(esp, ebx);
    esp += 4; return; /* ret */

}

/**
 * sub_00219600
 * Original: 0x00219600 - 0x00219650 (80 bytes, 29 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00219600(void)
{

loc_00219600: ;
    eax = MEM32(esp + 0x30);
    ecx = MEM32(esp + 0x34);
    edx = MEM32(esp + 0x2C);
    PUSH32(esp, 0x29C060);
    PUSH32(esp, eax);
    eax = MEM32(esp + 0x30);
    PUSH32(esp, ecx);
    ecx = MEM32(esp + 0x30);
    PUSH32(esp, edx);
    edx = MEM32(esp + 0x30);
    PUSH32(esp, eax);
    eax = MEM32(esp + 0x30);
    PUSH32(esp, ecx);
    ecx = MEM32(esp + 0x30);
    PUSH32(esp, edx);
    edx = MEM32(esp + 0x30);
    PUSH32(esp, eax);
    eax = MEM32(esp + 0x30);
    PUSH32(esp, ecx);
    ecx = MEM32(esp + 0x30);
    PUSH32(esp, edx);
    edx = MEM32(esp + 0x30);
    PUSH32(esp, eax);
    PUSH32(esp, ecx);
    PUSH32(esp, edx);
    edx = MEM32(esp + 0x38);
    PUSH32(esp, 0x0021964Au); sub_00214310(); /* call 0x00214310 */

loc_0021964A: ;
    esp = esp + 0x34;
    esp += 56; return; /* ret 52 */

}

/**
 * sub_00219650
 * Original: 0x00219650 - 0x002196AB (91 bytes, 34 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00219650(void)
{

loc_00219650: ;
    eax = MEM32(esp + 0x38);
    ecx = MEM32(esp + 0x3C);
    edx = MEM32(esp + 0x34);
    PUSH32(esp, 0x29C060);
    PUSH32(esp, eax);
    eax = MEM32(esp + 0x38);
    PUSH32(esp, ecx);
    ecx = MEM32(esp + 0x38);
    PUSH32(esp, edx);
    edx = MEM32(esp + 0x38);
    PUSH32(esp, eax);
    eax = MEM32(esp + 0x38);
    PUSH32(esp, ecx);
    ecx = MEM32(esp + 0x38);
    PUSH32(esp, edx);
    edx = MEM32(esp + 0x38);
    PUSH32(esp, eax);
    eax = MEM32(esp + 0x38);
    PUSH32(esp, ecx);
    ecx = MEM32(esp + 0x38);
    PUSH32(esp, edx);
    edx = MEM32(esp + 0x38);
    PUSH32(esp, eax);
    eax = MEM32(esp + 0x38);
    PUSH32(esp, ecx);
    ecx = MEM32(esp + 0x38);
    PUSH32(esp, edx);
    edx = MEM32(esp + 0x38);
    PUSH32(esp, eax);
    PUSH32(esp, ecx);
    PUSH32(esp, edx);
    PUSH32(esp, 0x002196A5u); sub_00214790(); /* call 0x00214790 */

loc_002196A5: ;
    esp = esp + 0x40;
    esp += 64; return; /* ret 60 */

}

/**
 * sub_002196B0
 * Original: 0x002196B0 - 0x00219947 (663 bytes, 169 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_002196B0(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    uint64_t mm0, mm1, mm2, mm3, mm4, mm5, mm6, mm7;
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_002196B0: ;
    PUSH32(esp, ebx);
    PUSH32(esp, ebp);
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    edi = MEM32(0x299F10);
    edx = MEM32(0x299F18);
    ebp = MEM32(0x299F20);
    ebx = MEM32(0x299F24);
    ecx = MEM32(0x299F28);
    eax = MEM32(esp + 0x14);
    eax = eax << 4;
    eax = eax + edi;
    MEM32(0x299F10) = eax;
    mm7 = ((uint64_t)MEM32((uint32_t)(0x25a7e8)) | ((uint64_t)MEM32((uint32_t)(0x25a7e8) + 4u) << 32)); /* MMX 0x002196E0: movq mm7, qword ptr [0x25a7e8] */

loc_002196E7: ;
    mm4 = (uint64_t)(uint32_t)(MEM32((uint32_t)(edx))); /* MMX 0x002196E7: movd mm4, dword ptr [edx] */
    mm0 = MMX_PXOR(mm0, mm0); /* MMX 0x002196EA: pxor mm0, mm0 */
    eax = 0; /* xor self */
    edx = edx + 4;
    SET_LO8(eax, MEM8(ebp));
    mm4 = MMX_PUNPCKLBW(mm4, mm0); /* MMX 0x002196F5: punpcklbw mm4, mm0 */
    mm2 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29b738))); /* MMX 0x002196F8: movd mm2, dword ptr [eax*4 + 0x29b738] */
    mm1 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29af38))); /* MMX 0x00219700: movd mm1, dword ptr [eax*4 + 0x29af38] */
    SET_LO8(eax, MEM8(ebp + 1));
    ebp = ebp + 2;
    mm4 = MMX_PSUBUSW(mm4, ((uint64_t)MEM32((uint32_t)(0x25a7d8)) | ((uint64_t)MEM32((uint32_t)(0x25a7d8) + 4u) << 32))); /* MMX 0x0021970E: psubusw mm4, qword ptr [0x25a7d8] */
    mm6 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29b738))); /* MMX 0x00219715: movd mm6, dword ptr [eax*4 + 0x29b738] */
    mm1 = MMX_PUNPCKLDQ(mm1, (uint64_t)MEM32((uint32_t)(eax*4 + 0x29af38))); /* MMX 0x0021971D: punpckldq mm1, dword ptr [eax*4 + 0x29af38] */
    SET_LO8(eax, MEM8(ebx));
    mm4 = MMX_PSLLW(mm4, 2u); /* MMX 0x00219727: psllw mm4, 2 */
    mm4 = MMX_PMULHW(mm4, ((uint64_t)MEM32((uint32_t)(0x25a7e0)) | ((uint64_t)MEM32((uint32_t)(0x25a7e0) + 4u) << 32))); /* MMX 0x0021972B: pmulhw mm4, qword ptr [0x25a7e0] */
    mm5 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29b338))); /* MMX 0x00219732: movd mm5, dword ptr [eax*4 + 0x29b338] */
    mm3 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29bb38))); /* MMX 0x0021973A: movd mm3, dword ptr [eax*4 + 0x29bb38] */
    mm2 = MMX_PADDW(mm2, mm5); /* MMX 0x00219742: paddw mm2, mm5 */
    SET_LO8(eax, MEM8(ebx + 1));
    ebx = ebx + 2;
    mm5 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29b338))); /* MMX 0x0021974B: movd mm5, dword ptr [eax*4 + 0x29b338] */
    mm3 = MMX_PUNPCKLDQ(mm3, (uint64_t)MEM32((uint32_t)(eax*4 + 0x29bb38))); /* MMX 0x00219753: punpckldq mm3, dword ptr [eax*4 + 0x29bb38] */
    mm6 = MMX_PADDW(mm6, mm5); /* MMX 0x0021975B: paddw mm6, mm5 */
    mm2 = MMX_PUNPCKLDQ(mm2, mm6); /* MMX 0x0021975E: punpckldq mm2, mm6 */
    mm1 = MMX_PADDW(mm1, mm4); /* MMX 0x00219761: paddw mm1, mm4 */
    mm2 = MMX_PADDW(mm2, mm4); /* MMX 0x00219764: paddw mm2, mm4 */
    mm1 = MMX_PADDSW(mm1, mm7); /* MMX 0x00219767: paddsw mm1, mm7 */
    mm3 = MMX_PADDW(mm3, mm4); /* MMX 0x0021976A: paddw mm3, mm4 */
    mm1 = MMX_PSUBUSW(mm1, mm7); /* MMX 0x0021976D: psubusw mm1, mm7 */
    mm2 = MMX_PADDSW(mm2, mm7); /* MMX 0x00219770: paddsw mm2, mm7 */
    mm4 = mm1; /* MMX 0x00219773: movq mm4, mm1 */
    mm2 = MMX_PSUBUSW(mm2, mm7); /* MMX 0x00219776: psubusw mm2, mm7 */
    mm1 = MMX_PUNPCKLWD(mm1, mm0); /* MMX 0x00219779: punpcklwd mm1, mm0 */
    mm5 = mm2; /* MMX 0x0021977C: movq mm5, mm2 */
    mm2 = MMX_PUNPCKLWD(mm2, mm0); /* MMX 0x0021977F: punpcklwd mm2, mm0 */
    mm3 = MMX_PADDSW(mm3, mm7); /* MMX 0x00219782: paddsw mm3, mm7 */
    mm2 = MMX_PSLLD(mm2, 8u); /* MMX 0x00219785: pslld mm2, 8 */
    mm3 = MMX_PSUBUSW(mm3, mm7); /* MMX 0x00219789: psubusw mm3, mm7 */
    mm4 = MMX_PUNPCKHWD(mm4, mm0); /* MMX 0x0021978C: punpckhwd mm4, mm0 */
    mm6 = mm3; /* MMX 0x0021978F: movq mm6, mm3 */
    mm3 = MMX_PUNPCKLWD(mm3, mm0); /* MMX 0x00219792: punpcklwd mm3, mm0 */
    mm3 = MMX_PSLLD(mm3, 0x10u); /* MMX 0x00219795: pslld mm3, 0x10 */
    mm1 = MMX_POR(mm1, mm2); /* MMX 0x00219799: por mm1, mm2 */
    mm2 = (uint64_t)(uint32_t)(MEM32((uint32_t)(ecx))); /* MMX 0x0021979C: movd mm2, dword ptr [ecx] */
    mm1 = MMX_POR(mm1, mm3); /* MMX 0x0021979F: por mm1, mm3 */
    mm3 = MMX_PXOR(mm3, mm3); /* MMX 0x002197A2: pxor mm3, mm3 */
    mm5 = MMX_PUNPCKHWD(mm5, mm0); /* MMX 0x002197A5: punpckhwd mm5, mm0 */
    mm3 = MMX_PUNPCKLBW(mm3, mm2); /* MMX 0x002197A8: punpcklbw mm3, mm2 */
    mm2 = MMX_PXOR(mm2, mm2); /* MMX 0x002197AB: pxor mm2, mm2 */
    mm2 = MMX_PUNPCKLWD(mm2, mm3); /* MMX 0x002197AE: punpcklwd mm2, mm3 */
    mm6 = MMX_PUNPCKHWD(mm6, mm0); /* MMX 0x002197B1: punpckhwd mm6, mm0 */
    mm1 = MMX_POR(mm1, mm2); /* MMX 0x002197B4: por mm1, mm2 */
    mm5 = MMX_PSLLD(mm5, 8u); /* MMX 0x002197B7: pslld mm5, 8 */
    mm2 = MMX_PXOR(mm2, mm2); /* MMX 0x002197BB: pxor mm2, mm2 */
    MEM32((uint32_t)(edi)) = (uint32_t)mm1; MEM32((uint32_t)(edi) + 4u) = (uint32_t)(mm1 >> 32); /* MMX 0x002197BE: movq qword ptr [edi], mm1 */
    mm2 = MMX_PUNPCKHWD(mm2, mm3); /* MMX 0x002197C1: punpckhwd mm2, mm3 */
    mm6 = MMX_PSLLD(mm6, 0x10u); /* MMX 0x002197C4: pslld mm6, 0x10 */
    mm4 = MMX_POR(mm4, mm2); /* MMX 0x002197C8: por mm4, mm2 */
    mm4 = MMX_POR(mm4, mm5); /* MMX 0x002197CB: por mm4, mm5 */
    ecx = ecx + 4;
    edi = edi + 0x10;
    mm4 = MMX_POR(mm4, mm6); /* MMX 0x002197D4: por mm4, mm6 */
    eax = MEM32(0x299F10);
    MEM32((uint32_t)(edi - 8)) = (uint32_t)mm4; MEM32((uint32_t)(edi - 8) + 4u) = (uint32_t)(mm4 >> 32); /* MMX 0x002197DC: movq qword ptr [edi - 8], mm4 */
    _fa = (uint32_t)(edi) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edi, eax (32-bit) */
    if (CMP_B(_fa, _fb)) goto loc_002196E7; /* jb: below (unsigned <) */

loc_002197E8: ;
    MEM32(0x299F18) = edx;
    MEM32(0x299F28) = ecx;
    edi = MEM32(0x299F14);
    edx = MEM32(0x299F1C);
    ebp = MEM32(0x299F20);
    ebx = MEM32(0x299F24);
    ecx = MEM32(0x299F2C);
    eax = MEM32(esp + 0x14);
    eax = eax << 4;
    eax = eax + edi;
    MEM32(0x299F14) = eax;
    mm7 = ((uint64_t)MEM32((uint32_t)(0x25a7e8)) | ((uint64_t)MEM32((uint32_t)(0x25a7e8) + 4u) << 32)); /* MMX 0x00219820: movq mm7, qword ptr [0x25a7e8] */

loc_00219827: ;
    mm4 = (uint64_t)(uint32_t)(MEM32((uint32_t)(edx))); /* MMX 0x00219827: movd mm4, dword ptr [edx] */
    mm0 = MMX_PXOR(mm0, mm0); /* MMX 0x0021982A: pxor mm0, mm0 */
    eax = 0; /* xor self */
    edx = edx + 4;
    SET_LO8(eax, MEM8(ebp));
    mm4 = MMX_PUNPCKLBW(mm4, mm0); /* MMX 0x00219835: punpcklbw mm4, mm0 */
    mm2 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29b738))); /* MMX 0x00219838: movd mm2, dword ptr [eax*4 + 0x29b738] */
    mm1 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29af38))); /* MMX 0x00219840: movd mm1, dword ptr [eax*4 + 0x29af38] */
    SET_LO8(eax, MEM8(ebp + 1));
    ebp = ebp + 2;
    mm4 = MMX_PSUBUSW(mm4, ((uint64_t)MEM32((uint32_t)(0x25a7d8)) | ((uint64_t)MEM32((uint32_t)(0x25a7d8) + 4u) << 32))); /* MMX 0x0021984E: psubusw mm4, qword ptr [0x25a7d8] */
    mm6 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29b738))); /* MMX 0x00219855: movd mm6, dword ptr [eax*4 + 0x29b738] */
    mm1 = MMX_PUNPCKLDQ(mm1, (uint64_t)MEM32((uint32_t)(eax*4 + 0x29af38))); /* MMX 0x0021985D: punpckldq mm1, dword ptr [eax*4 + 0x29af38] */
    SET_LO8(eax, MEM8(ebx));
    mm4 = MMX_PSLLW(mm4, 2u); /* MMX 0x00219867: psllw mm4, 2 */
    mm4 = MMX_PMULHW(mm4, ((uint64_t)MEM32((uint32_t)(0x25a7e0)) | ((uint64_t)MEM32((uint32_t)(0x25a7e0) + 4u) << 32))); /* MMX 0x0021986B: pmulhw mm4, qword ptr [0x25a7e0] */
    mm5 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29b338))); /* MMX 0x00219872: movd mm5, dword ptr [eax*4 + 0x29b338] */
    mm3 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29bb38))); /* MMX 0x0021987A: movd mm3, dword ptr [eax*4 + 0x29bb38] */
    mm2 = MMX_PADDW(mm2, mm5); /* MMX 0x00219882: paddw mm2, mm5 */
    SET_LO8(eax, MEM8(ebx + 1));
    ebx = ebx + 2;
    mm5 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29b338))); /* MMX 0x0021988B: movd mm5, dword ptr [eax*4 + 0x29b338] */
    mm3 = MMX_PUNPCKLDQ(mm3, (uint64_t)MEM32((uint32_t)(eax*4 + 0x29bb38))); /* MMX 0x00219893: punpckldq mm3, dword ptr [eax*4 + 0x29bb38] */
    mm6 = MMX_PADDW(mm6, mm5); /* MMX 0x0021989B: paddw mm6, mm5 */
    mm2 = MMX_PUNPCKLDQ(mm2, mm6); /* MMX 0x0021989E: punpckldq mm2, mm6 */
    mm1 = MMX_PADDW(mm1, mm4); /* MMX 0x002198A1: paddw mm1, mm4 */
    mm2 = MMX_PADDW(mm2, mm4); /* MMX 0x002198A4: paddw mm2, mm4 */
    mm1 = MMX_PADDSW(mm1, mm7); /* MMX 0x002198A7: paddsw mm1, mm7 */
    mm3 = MMX_PADDW(mm3, mm4); /* MMX 0x002198AA: paddw mm3, mm4 */
    mm1 = MMX_PSUBUSW(mm1, mm7); /* MMX 0x002198AD: psubusw mm1, mm7 */
    mm2 = MMX_PADDSW(mm2, mm7); /* MMX 0x002198B0: paddsw mm2, mm7 */
    mm4 = mm1; /* MMX 0x002198B3: movq mm4, mm1 */
    mm2 = MMX_PSUBUSW(mm2, mm7); /* MMX 0x002198B6: psubusw mm2, mm7 */
    mm1 = MMX_PUNPCKLWD(mm1, mm0); /* MMX 0x002198B9: punpcklwd mm1, mm0 */
    mm5 = mm2; /* MMX 0x002198BC: movq mm5, mm2 */
    mm2 = MMX_PUNPCKLWD(mm2, mm0); /* MMX 0x002198BF: punpcklwd mm2, mm0 */
    mm3 = MMX_PADDSW(mm3, mm7); /* MMX 0x002198C2: paddsw mm3, mm7 */
    mm2 = MMX_PSLLD(mm2, 8u); /* MMX 0x002198C5: pslld mm2, 8 */
    mm3 = MMX_PSUBUSW(mm3, mm7); /* MMX 0x002198C9: psubusw mm3, mm7 */
    mm4 = MMX_PUNPCKHWD(mm4, mm0); /* MMX 0x002198CC: punpckhwd mm4, mm0 */
    mm6 = mm3; /* MMX 0x002198CF: movq mm6, mm3 */
    mm3 = MMX_PUNPCKLWD(mm3, mm0); /* MMX 0x002198D2: punpcklwd mm3, mm0 */
    mm3 = MMX_PSLLD(mm3, 0x10u); /* MMX 0x002198D5: pslld mm3, 0x10 */
    mm1 = MMX_POR(mm1, mm2); /* MMX 0x002198D9: por mm1, mm2 */
    mm2 = (uint64_t)(uint32_t)(MEM32((uint32_t)(ecx))); /* MMX 0x002198DC: movd mm2, dword ptr [ecx] */
    mm1 = MMX_POR(mm1, mm3); /* MMX 0x002198DF: por mm1, mm3 */
    mm3 = MMX_PXOR(mm3, mm3); /* MMX 0x002198E2: pxor mm3, mm3 */
    mm5 = MMX_PUNPCKHWD(mm5, mm0); /* MMX 0x002198E5: punpckhwd mm5, mm0 */
    mm3 = MMX_PUNPCKLBW(mm3, mm2); /* MMX 0x002198E8: punpcklbw mm3, mm2 */
    mm2 = MMX_PXOR(mm2, mm2); /* MMX 0x002198EB: pxor mm2, mm2 */
    mm2 = MMX_PUNPCKLWD(mm2, mm3); /* MMX 0x002198EE: punpcklwd mm2, mm3 */
    mm6 = MMX_PUNPCKHWD(mm6, mm0); /* MMX 0x002198F1: punpckhwd mm6, mm0 */
    mm1 = MMX_POR(mm1, mm2); /* MMX 0x002198F4: por mm1, mm2 */
    mm5 = MMX_PSLLD(mm5, 8u); /* MMX 0x002198F7: pslld mm5, 8 */
    mm2 = MMX_PXOR(mm2, mm2); /* MMX 0x002198FB: pxor mm2, mm2 */
    MEM32((uint32_t)(edi)) = (uint32_t)mm1; MEM32((uint32_t)(edi) + 4u) = (uint32_t)(mm1 >> 32); /* MMX 0x002198FE: movq qword ptr [edi], mm1 */
    mm2 = MMX_PUNPCKHWD(mm2, mm3); /* MMX 0x00219901: punpckhwd mm2, mm3 */
    mm6 = MMX_PSLLD(mm6, 0x10u); /* MMX 0x00219904: pslld mm6, 0x10 */
    mm4 = MMX_POR(mm4, mm2); /* MMX 0x00219908: por mm4, mm2 */
    mm4 = MMX_POR(mm4, mm5); /* MMX 0x0021990B: por mm4, mm5 */
    ecx = ecx + 4;
    edi = edi + 0x10;
    mm4 = MMX_POR(mm4, mm6); /* MMX 0x00219914: por mm4, mm6 */
    eax = MEM32(0x299F14);
    MEM32((uint32_t)(edi - 8)) = (uint32_t)mm4; MEM32((uint32_t)(edi - 8) + 4u) = (uint32_t)(mm4 >> 32); /* MMX 0x0021991C: movq qword ptr [edi - 8], mm4 */
    _fa = (uint32_t)(edi) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edi, eax (32-bit) */
    if (CMP_B(_fa, _fb)) goto loc_00219827; /* jb: below (unsigned <) */

loc_00219928: ;
    MEM32(0x299F1C) = edx;
    MEM32(0x299F2C) = ecx;
    MEM32(0x299F20) = ebp;
    MEM32(0x299F24) = ebx;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebp);
    POP32(esp, ebx);
    esp += 8; return; /* ret 4 */

}

/**
 * sub_00219CE0
 * Original: 0x00219CE0 - 0x00219D80 (160 bytes, 41 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00219CE0(void)
{
    int _flags = 0; /* fallback flag var */

loc_00219CE0: ;
    PUSH32(esp, ebx);
    PUSH32(esp, esi);
    esi = MEM32(esp + 0xC);
    PUSH32(esp, edi);
    edx = esi;
    edi = 2;
    edi = edi;

loc_00219CF0: ;
    ecx = MEM32(0x299F18);
    eax = ZX8(MEM8(ecx));
    SET_LO16(eax, MEM16(eax * 4 + 0x299310));
    ecx++;
    MEM32(0x299F18) = ecx;
    ecx = MEM32(0x299F10);
    MEM16(ecx) = LO16(eax);
    ebx = MEM32(0x299F10);
    ecx = MEM32(0x299F30);
    MEM16(ecx + ebx) = LO16(eax);
    ecx = MEM32(0x299F1C);
    eax = ZX8(MEM8(ecx));
    SET_LO16(eax, MEM16(eax * 4 + 0x299310));
    ecx++;
    MEM32(0x299F1C) = ecx;
    ecx = MEM32(0x299F14);
    MEM16(ecx) = LO16(eax);
    ecx = MEM32(0x299F14);
    ebx = MEM32(0x299F30);
    MEM16(ecx + ebx) = LO16(eax);
    ebx = MEM32(0x299F10);
    ecx = MEM32(0x299F14);
    ebx = ebx + edi;
    ecx = ecx + edi;
    edx--;
    MEM32(0x299F10) = ebx;
    MEM32(0x299F14) = ecx;
    if ((edx != 0)) goto loc_00219CF0; /* jne: not equal / not zero */

loc_00219D75: ;
    edx = MEM32(esp + 0x14);
    POP32(esp, edi);
    eax = esi + edx;
    POP32(esp, esi);
    POP32(esp, ebx);
    esp += 4; return; /* ret */

}

/**
 * sub_00219DD0
 * Original: 0x00219DD0 - 0x00219E5D (141 bytes, 37 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00219DD0(void)
{
    int _flags = 0; /* fallback flag var */

loc_00219DD0: ;
    PUSH32(esp, esi);
    esi = MEM32(esp + 8);
    PUSH32(esp, edi);
    edx = esi;
    edi = 4;
    /* nop */

loc_00219DE0: ;
    ecx = MEM32(0x299F18);
    eax = ZX8(MEM8(ecx));
    SET_LO16(eax, MEM16(eax * 4 + 0x299310));
    ecx++;
    MEM32(0x299F18) = ecx;
    ecx = MEM32(0x299F10);
    MEM16(ecx) = LO16(eax);
    ecx = MEM32(0x299F10);
    MEM16(ecx + 2) = LO16(eax);
    ecx = MEM32(0x299F1C);
    eax = ZX8(MEM8(ecx));
    SET_LO16(eax, MEM16(eax * 4 + 0x299310));
    ecx++;
    MEM32(0x299F1C) = ecx;
    ecx = MEM32(0x299F14);
    MEM16(ecx) = LO16(eax);
    ecx = MEM32(0x299F14);
    MEM16(ecx + 2) = LO16(eax);
    eax = MEM32(0x299F10);
    ecx = MEM32(0x299F14);
    eax = eax + edi;
    ecx = ecx + edi;
    edx--;
    MEM32(0x299F10) = eax;
    MEM32(0x299F14) = ecx;
    if ((edx != 0)) goto loc_00219DE0; /* jne: not equal / not zero */

loc_00219E53: ;
    edx = MEM32(esp + 0x10);
    POP32(esp, edi);
    eax = esi + edx;
    POP32(esp, esi);
    esp += 4; return; /* ret */

}

/**
 * sub_00219E60
 * Original: 0x00219E60 - 0x00219ED0 (112 bytes, 27 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00219E60(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00219E60: ;
    edx = MEM32(esp + 8);
    _fa = (uint32_t)(edx) & 0xFFFFFFFFu; _fb = (uint32_t)(edx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test edx, edx (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00219ECF; /* je: equal / zero */

loc_00219E68: ;
    PUSH32(esp, esi);
    /* nop */

loc_00219E70: ;
    ecx = MEM32(0x299F18);
    eax = ZX8(MEM8(ecx));
    SET_LO16(eax, MEM16(eax * 4 + 0x299310));
    ecx++;
    MEM32(0x299F18) = ecx;
    ecx = MEM32(0x299F10);
    MEM16(ecx) = LO16(eax);
    ecx = MEM32(0x299F10);
    MEM16(ecx + 2) = LO16(eax);
    esi = MEM32(0x299F10);
    ecx = MEM32(0x299F30);
    MEM16(ecx + esi) = LO16(eax);
    ecx = MEM32(0x299F10);
    esi = MEM32(0x299F30);
    MEM16(esi + ecx + 2) = LO16(eax);
    ecx = MEM32(0x299F10);
    ecx = ecx + 4;
    edx--;
    MEM32(0x299F10) = ecx;
    if ((edx != 0)) goto loc_00219E70; /* jne: not equal / not zero */

loc_00219ECE: ;
    POP32(esp, esi);

loc_00219ECF: ;
    esp += 4; return; /* ret */

}

/**
 * sub_00219FB0
 * Original: 0x00219FB0 - 0x0021A088 (216 bytes, 58 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00219FB0(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_00219FB0: ;
    eax = MEM32(esp + 8);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    PUSH32(esp, ebx);
    ebx = MEM32(esp + 8);
    if (TEST_Z(_fa, _fb)) goto loc_0021A086; /* je: equal / zero */

loc_00219FC1: ;
    PUSH32(esp, ebp);
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    ebp = eax;
    goto loc_00219FD0;

    /* nop */
    /* nop */

loc_00219FD0: ;
    eax = MEM32(0x299F20);
    eax = ZX8(MEM8(eax));
    ecx = MEM32(0x299F24);
    ecx = ZX8(MEM8(ecx));
    eax = eax << 2;
    esi = MEM32(eax + 0x29A738);
    edi = MEM32(eax + 0x299F38);
    eax = MEM32(0x299F18);
    ecx = ecx << 2;
    edx = MEM32(ecx + 0x29A338);
    ecx = MEM32(ecx + 0x29AB38);
    edx = edx + esi;
    esi = ZX8(MEM8(eax));
    esi = MEM32(esi * 4 + 0x293270);
    eax++;
    MEM32(0x299F18) = eax;
    eax = esi + ecx;
    SET_LO16(eax, MEM16(eax * 4 + 0x2952A0));
    ecx = esi + edx;
    SET_LO16(eax, LO16(eax) | MEM16(ecx * 4 + 0x294690));
    edx = MEM32(0x299F10);
    esi = esi + edi;
    SET_LO16(eax, LO16(eax) | MEM16(esi * 4 + 0x293A80));
    MEM16(edx) = LO16(eax);
    ecx = MEM32(0x299F10);
    edx = MEM32(0x299F30);
    MEM16(edx + ecx) = LO16(eax);
    edx = MEM32(0x299F10);
    edx = edx + 2;
    ebx++;
    _fa = (uint32_t)(LO8(ebx)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(ebx), 1 (8-bit) */
    MEM32(0x299F10) = edx;
    if (TEST_NZ(_fa, _fb)) goto loc_0021A07C; /* jne: not equal / not zero */

loc_0021A064: ;
    ecx = MEM32(0x299F20);
    eax = MEM32(0x299F24);
    ecx++;
    eax++;
    MEM32(0x299F20) = ecx;
    MEM32(0x299F24) = eax;

loc_0021A07C: ;
    ebp--;
    if ((ebp != 0)) goto loc_00219FD0; /* jne: not equal / not zero */

loc_0021A083: ;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebp);

loc_0021A086: ;
    POP32(esp, ebx);
    esp += 4; return; /* ret */

}

/**
 * sub_0021A090
 * Original: 0x0021A090 - 0x0021A1BF (303 bytes, 73 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0021A090(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_0021A090: ;
    ecx = MEM32(esp + 4);
    eax = MEM32(esp + 8);
    PUSH32(esp, ebx);
    PUSH32(esp, ebp);
    PUSH32(esp, esi);
    MEM32(esp + 0x14) = ecx;
    PUSH32(esp, edi);

loc_0021A0A0: ;
    edx = MEM32(0x299F20);
    ecx = ZX8(MEM8(edx));
    edx = MEM32(0x299F24);
    edx = ZX8(MEM8(edx));
    ecx = ecx << 2;
    ebx = MEM32(ecx + 0x299F38);
    edi = MEM32(ecx + 0x29A738);
    ecx = MEM32(0x299F18);
    edx = edx << 2;
    esi = MEM32(edx + 0x29A338);
    edx = MEM32(edx + 0x29AB38);
    esi = esi + edi;
    edi = ZX8(MEM8(ecx));
    edi = MEM32(edi * 4 + 0x293270);
    ecx++;
    MEM32(0x299F18) = ecx;
    ecx = edi + edx;
    SET_LO16(ecx, MEM16(ecx * 4 + 0x2952A0));
    ebp = edi + esi;
    SET_LO16(ecx, LO16(ecx) | MEM16(ebp * 4 + 0x294690));
    edi = edi + ebx;
    SET_LO16(ecx, LO16(ecx) | MEM16(edi * 4 + 0x293A80));
    edi = MEM32(0x299F10);
    MEM16(edi) = LO16(ecx);
    edi = MEM32(0x299F30);
    ebp = MEM32(0x299F10);
    MEM16(edi + ebp) = LO16(ecx);
    ecx = MEM32(0x299F1C);
    edi = ZX8(MEM8(ecx));
    edi = MEM32(edi * 4 + 0x293270);
    ecx++;
    edx = edx + edi;
    esi = esi + edi;
    MEM32(0x299F1C) = ecx;
    SET_LO16(ecx, MEM16(edx * 4 + 0x2952A0));
    SET_LO16(ecx, LO16(ecx) | MEM16(esi * 4 + 0x294690));
    edx = MEM32(0x299F14);
    edi = edi + ebx;
    SET_LO16(ecx, LO16(ecx) | MEM16(edi * 4 + 0x293A80));
    MEM16(edx) = LO16(ecx);
    edx = MEM32(0x299F14);
    esi = MEM32(0x299F30);
    MEM16(edx + esi) = LO16(ecx);
    edi = MEM32(0x299F10);
    esi = MEM32(0x299F14);
    ecx = 2;
    edi = edi + ecx;
    esi = esi + ecx;
    eax++;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), 1 (8-bit) */
    MEM32(0x299F10) = edi;
    MEM32(0x299F14) = esi;
    if (TEST_NZ(_fa, _fb)) goto loc_0021A1B0; /* jne: not equal / not zero */

loc_0021A196: ;
    edx = MEM32(0x299F20);
    ecx = MEM32(0x299F24);
    edx++;
    ecx++;
    MEM32(0x299F20) = edx;
    MEM32(0x299F24) = ecx;

loc_0021A1B0: ;
    MEM32(esp + 0x18) = MEM32(esp + 0x18) - 1;
    if ((MEM32(esp + 0x18) != 0)) goto loc_0021A0A0; /* jne: not equal / not zero */

loc_0021A1BA: ;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebp);
    POP32(esp, ebx);
    esp += 4; return; /* ret */

}

/**
 * sub_0021A1C0
 * Original: 0x0021A1C0 - 0x0021A292 (210 bytes, 57 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0021A1C0(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_0021A1C0: ;
    eax = MEM32(esp + 8);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    PUSH32(esp, ebx);
    ebx = MEM32(esp + 8);
    if (TEST_Z(_fa, _fb)) goto loc_0021A290; /* je: equal / zero */

loc_0021A1D1: ;
    PUSH32(esp, ebp);
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    ebp = eax;
    goto loc_0021A1E0;

    /* nop */
    /* nop */

loc_0021A1E0: ;
    eax = MEM32(0x299F20);
    eax = ZX8(MEM8(eax));
    ecx = MEM32(0x299F24);
    ecx = ZX8(MEM8(ecx));
    eax = eax << 2;
    esi = MEM32(eax + 0x29A738);
    edi = MEM32(eax + 0x299F38);
    eax = MEM32(0x299F18);
    ecx = ecx << 2;
    edx = MEM32(ecx + 0x29A338);
    ecx = MEM32(ecx + 0x29AB38);
    edx = edx + esi;
    esi = ZX8(MEM8(eax));
    esi = MEM32(esi * 4 + 0x293270);
    eax++;
    MEM32(0x299F18) = eax;
    eax = esi + ecx;
    SET_LO16(eax, MEM16(eax * 4 + 0x2952A0));
    ecx = esi + edx;
    SET_LO16(eax, LO16(eax) | MEM16(ecx * 4 + 0x294690));
    edx = MEM32(0x299F10);
    esi = esi + edi;
    SET_LO16(eax, LO16(eax) | MEM16(esi * 4 + 0x293A80));
    MEM16(edx) = LO16(eax);
    ecx = MEM32(0x299F10);
    MEM16(ecx + 2) = LO16(eax);
    edx = MEM32(0x299F10);
    edx = edx + 4;
    ebx++;
    _fa = (uint32_t)(LO8(ebx)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(ebx), 1 (8-bit) */
    MEM32(0x299F10) = edx;
    if (TEST_NZ(_fa, _fb)) goto loc_0021A286; /* jne: not equal / not zero */

loc_0021A26E: ;
    ecx = MEM32(0x299F20);
    eax = MEM32(0x299F24);
    ecx++;
    eax++;
    MEM32(0x299F20) = ecx;
    MEM32(0x299F24) = eax;

loc_0021A286: ;
    ebp--;
    if ((ebp != 0)) goto loc_0021A1E0; /* jne: not equal / not zero */

loc_0021A28D: ;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebp);

loc_0021A290: ;
    POP32(esp, ebx);
    esp += 4; return; /* ret */

}

/**
 * sub_0021A2A0
 * Original: 0x0021A2A0 - 0x0021A3C3 (291 bytes, 71 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0021A2A0(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_0021A2A0: ;
    ecx = MEM32(esp + 4);
    eax = MEM32(esp + 8);
    PUSH32(esp, ebx);
    PUSH32(esp, ebp);
    PUSH32(esp, esi);
    MEM32(esp + 0x14) = ecx;
    PUSH32(esp, edi);

loc_0021A2B0: ;
    edx = MEM32(0x299F20);
    ecx = ZX8(MEM8(edx));
    edx = MEM32(0x299F24);
    edx = ZX8(MEM8(edx));
    ecx = ecx << 2;
    ebx = MEM32(ecx + 0x299F38);
    edi = MEM32(ecx + 0x29A738);
    ecx = MEM32(0x299F18);
    edx = edx << 2;
    esi = MEM32(edx + 0x29A338);
    edx = MEM32(edx + 0x29AB38);
    esi = esi + edi;
    edi = ZX8(MEM8(ecx));
    edi = MEM32(edi * 4 + 0x293270);
    ecx++;
    MEM32(0x299F18) = ecx;
    ecx = edi + edx;
    SET_LO16(ecx, MEM16(ecx * 4 + 0x2952A0));
    ebp = edi + esi;
    SET_LO16(ecx, LO16(ecx) | MEM16(ebp * 4 + 0x294690));
    edi = edi + ebx;
    SET_LO16(ecx, LO16(ecx) | MEM16(edi * 4 + 0x293A80));
    edi = MEM32(0x299F10);
    MEM16(edi) = LO16(ecx);
    edi = MEM32(0x299F10);
    MEM16(edi + 2) = LO16(ecx);
    ecx = MEM32(0x299F1C);
    edi = ZX8(MEM8(ecx));
    edi = MEM32(edi * 4 + 0x293270);
    ecx++;
    edx = edx + edi;
    esi = esi + edi;
    MEM32(0x299F1C) = ecx;
    SET_LO16(ecx, MEM16(edx * 4 + 0x2952A0));
    SET_LO16(ecx, LO16(ecx) | MEM16(esi * 4 + 0x294690));
    edx = MEM32(0x299F14);
    edi = edi + ebx;
    SET_LO16(ecx, LO16(ecx) | MEM16(edi * 4 + 0x293A80));
    MEM16(edx) = LO16(ecx);
    edx = MEM32(0x299F14);
    MEM16(edx + 2) = LO16(ecx);
    edi = MEM32(0x299F10);
    esi = MEM32(0x299F14);
    ecx = 4;
    edi = edi + ecx;
    esi = esi + ecx;
    eax++;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), 1 (8-bit) */
    MEM32(0x299F10) = edi;
    MEM32(0x299F14) = esi;
    if (TEST_NZ(_fa, _fb)) goto loc_0021A3B4; /* jne: not equal / not zero */

loc_0021A39A: ;
    edx = MEM32(0x299F20);
    ecx = MEM32(0x299F24);
    edx++;
    ecx++;
    MEM32(0x299F20) = edx;
    MEM32(0x299F24) = ecx;

loc_0021A3B4: ;
    MEM32(esp + 0x18) = MEM32(esp + 0x18) - 1;
    if ((MEM32(esp + 0x18) != 0)) goto loc_0021A2B0; /* jne: not equal / not zero */

loc_0021A3BE: ;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebp);
    POP32(esp, ebx);
    esp += 4; return; /* ret */

}

/**
 * sub_0021A3D0
 * Original: 0x0021A3D0 - 0x0021A4C3 (243 bytes, 63 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0021A3D0(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_0021A3D0: ;
    eax = MEM32(esp + 8);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    PUSH32(esp, ebx);
    ebx = MEM32(esp + 8);
    if (TEST_Z(_fa, _fb)) goto loc_0021A4C1; /* je: equal / zero */

loc_0021A3E1: ;
    PUSH32(esp, ebp);
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    ebp = eax;
    goto loc_0021A3F0;

    /* nop */
    /* nop */

loc_0021A3F0: ;
    eax = MEM32(0x299F20);
    eax = ZX8(MEM8(eax));
    ecx = MEM32(0x299F24);
    ecx = ZX8(MEM8(ecx));
    eax = eax << 2;
    esi = MEM32(eax + 0x29A738);
    edi = MEM32(eax + 0x299F38);
    eax = MEM32(0x299F18);
    ecx = ecx << 2;
    edx = MEM32(ecx + 0x29A338);
    ecx = MEM32(ecx + 0x29AB38);
    edx = edx + esi;
    esi = ZX8(MEM8(eax));
    esi = MEM32(esi * 4 + 0x293270);
    eax++;
    MEM32(0x299F18) = eax;
    eax = esi + ecx;
    SET_LO16(eax, MEM16(eax * 4 + 0x2952A0));
    ecx = esi + edx;
    SET_LO16(eax, LO16(eax) | MEM16(ecx * 4 + 0x294690));
    edx = MEM32(0x299F10);
    esi = esi + edi;
    SET_LO16(eax, LO16(eax) | MEM16(esi * 4 + 0x293A80));
    MEM16(edx) = LO16(eax);
    ecx = MEM32(0x299F10);
    MEM16(ecx + 2) = LO16(eax);
    ecx = MEM32(0x299F10);
    edx = MEM32(0x299F30);
    MEM16(edx + ecx) = LO16(eax);
    edx = MEM32(0x299F10);
    ecx = MEM32(0x299F30);
    MEM16(ecx + edx + 2) = LO16(eax);
    edx = MEM32(0x299F10);
    edx = edx + 4;
    ebx++;
    _fa = (uint32_t)(LO8(ebx)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(ebx), 1 (8-bit) */
    MEM32(0x299F10) = edx;
    if (TEST_NZ(_fa, _fb)) goto loc_0021A4B7; /* jne: not equal / not zero */

loc_0021A49F: ;
    ecx = MEM32(0x299F20);
    eax = MEM32(0x299F24);
    ecx++;
    eax++;
    MEM32(0x299F20) = ecx;
    MEM32(0x299F24) = eax;

loc_0021A4B7: ;
    ebp--;
    if ((ebp != 0)) goto loc_0021A3F0; /* jne: not equal / not zero */

loc_0021A4BE: ;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebp);

loc_0021A4C1: ;
    POP32(esp, ebx);
    esp += 4; return; /* ret */

}

/**
 * sub_0021A4D0
 * Original: 0x0021A4D0 - 0x0021A635 (357 bytes, 83 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0021A4D0(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_0021A4D0: ;
    ecx = MEM32(esp + 4);
    eax = MEM32(esp + 8);
    PUSH32(esp, ebx);
    PUSH32(esp, ebp);
    PUSH32(esp, esi);
    MEM32(esp + 0x14) = ecx;
    PUSH32(esp, edi);

loc_0021A4E0: ;
    edx = MEM32(0x299F20);
    ecx = ZX8(MEM8(edx));
    edx = MEM32(0x299F24);
    edx = ZX8(MEM8(edx));
    ecx = ecx << 2;
    ebx = MEM32(ecx + 0x299F38);
    edi = MEM32(ecx + 0x29A738);
    ecx = MEM32(0x299F18);
    edx = edx << 2;
    esi = MEM32(edx + 0x29A338);
    edx = MEM32(edx + 0x29AB38);
    esi = esi + edi;
    edi = ZX8(MEM8(ecx));
    edi = MEM32(edi * 4 + 0x293270);
    ecx++;
    MEM32(0x299F18) = ecx;
    ecx = edi + edx;
    SET_LO16(ecx, MEM16(ecx * 4 + 0x2952A0));
    ebp = edi + esi;
    SET_LO16(ecx, LO16(ecx) | MEM16(ebp * 4 + 0x294690));
    edi = edi + ebx;
    SET_LO16(ecx, LO16(ecx) | MEM16(edi * 4 + 0x293A80));
    edi = MEM32(0x299F10);
    MEM16(edi) = LO16(ecx);
    edi = MEM32(0x299F10);
    MEM16(edi + 2) = LO16(ecx);
    ebp = MEM32(0x299F10);
    edi = MEM32(0x299F30);
    MEM16(edi + ebp) = LO16(ecx);
    edi = MEM32(0x299F30);
    ebp = MEM32(0x299F10);
    MEM16(edi + ebp + 2) = LO16(ecx);
    ecx = MEM32(0x299F1C);
    edi = ZX8(MEM8(ecx));
    edi = MEM32(edi * 4 + 0x293270);
    edx = edx + edi;
    ecx++;
    esi = esi + edi;
    MEM32(0x299F1C) = ecx;
    SET_LO16(ecx, MEM16(edx * 4 + 0x2952A0));
    SET_LO16(ecx, LO16(ecx) | MEM16(esi * 4 + 0x294690));
    edx = MEM32(0x299F14);
    edi = edi + ebx;
    SET_LO16(ecx, LO16(ecx) | MEM16(edi * 4 + 0x293A80));
    MEM16(edx) = LO16(ecx);
    edx = MEM32(0x299F14);
    MEM16(edx + 2) = LO16(ecx);
    edx = MEM32(0x299F14);
    esi = MEM32(0x299F30);
    MEM16(edx + esi) = LO16(ecx);
    edx = MEM32(0x299F14);
    esi = MEM32(0x299F30);
    MEM16(edx + esi + 2) = LO16(ecx);
    edi = MEM32(0x299F10);
    esi = MEM32(0x299F14);
    ecx = 4;
    edi = edi + ecx;
    esi = esi + ecx;
    eax++;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), 1 (8-bit) */
    MEM32(0x299F10) = edi;
    MEM32(0x299F14) = esi;
    if (TEST_NZ(_fa, _fb)) goto loc_0021A626; /* jne: not equal / not zero */

loc_0021A60C: ;
    edx = MEM32(0x299F20);
    ecx = MEM32(0x299F24);
    edx++;
    ecx++;
    MEM32(0x299F20) = edx;
    MEM32(0x299F24) = ecx;

loc_0021A626: ;
    MEM32(esp + 0x18) = MEM32(esp + 0x18) - 1;
    if ((MEM32(esp + 0x18) != 0)) goto loc_0021A4E0; /* jne: not equal / not zero */

loc_0021A630: ;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebp);
    POP32(esp, ebx);
    esp += 4; return; /* ret */

}

/**
 * sub_0021A640
 * Original: 0x0021A640 - 0x0021A681 (65 bytes, 18 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0021A640(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_0021A640: ;
    edx = MEM32(esp + 8);
    _fa = (uint32_t)(edx) & 0xFFFFFFFFu; _fb = (uint32_t)(edx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test edx, edx (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0021A680; /* je: equal / zero */

loc_0021A648: ;
    goto loc_0021A650;

    /* nop */

loc_0021A650: ;
    eax = MEM32(0x299F18);
    ecx = ZX8(MEM8(eax));
    SET_LO16(ecx, MEM16(ecx * 4 + 0x299310));
    eax++;
    MEM32(0x299F18) = eax;
    eax = MEM32(0x299F10);
    MEM16(eax) = LO16(ecx);
    ecx = MEM32(0x299F10);
    ecx = ecx + 2;
    edx--;
    MEM32(0x299F10) = ecx;
    if ((edx != 0)) goto loc_0021A650; /* jne: not equal / not zero */

loc_0021A680: ;
    esp += 4; return; /* ret */

}

/**
 * sub_0021A690
 * Original: 0x0021A690 - 0x0021A703 (115 bytes, 33 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0021A690(void)
{
    int _flags = 0; /* fallback flag var */

loc_0021A690: ;
    PUSH32(esp, esi);
    esi = MEM32(esp + 8);
    PUSH32(esp, edi);
    edx = esi;
    edi = 2;
    /* nop */

loc_0021A6A0: ;
    eax = MEM32(0x299F18);
    ecx = ZX8(MEM8(eax));
    SET_LO16(ecx, MEM16(ecx * 4 + 0x299310));
    eax++;
    MEM32(0x299F18) = eax;
    eax = MEM32(0x299F10);
    MEM16(eax) = LO16(ecx);
    eax = MEM32(0x299F1C);
    ecx = ZX8(MEM8(eax));
    SET_LO16(ecx, MEM16(ecx * 4 + 0x299310));
    eax++;
    MEM32(0x299F1C) = eax;
    eax = MEM32(0x299F14);
    MEM16(eax) = LO16(ecx);
    eax = MEM32(0x299F10);
    ecx = MEM32(0x299F14);
    eax = eax + edi;
    ecx = ecx + edi;
    edx--;
    MEM32(0x299F10) = eax;
    MEM32(0x299F14) = ecx;
    if ((edx != 0)) goto loc_0021A6A0; /* jne: not equal / not zero */

loc_0021A6F9: ;
    ecx = MEM32(esp + 0x10);
    POP32(esp, edi);
    eax = esi + ecx;
    POP32(esp, esi);
    esp += 4; return; /* ret */

}

/**
 * sub_0021A710
 * Original: 0x0021A710 - 0x0021A7D8 (200 bytes, 55 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0021A710(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_0021A710: ;
    eax = MEM32(esp + 8);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    PUSH32(esp, ebx);
    ebx = MEM32(esp + 8);
    if (TEST_Z(_fa, _fb)) goto loc_0021A7D6; /* je: equal / zero */

loc_0021A721: ;
    PUSH32(esp, ebp);
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    ebp = eax;
    goto loc_0021A730;

    /* nop */
    /* nop */

loc_0021A730: ;
    eax = MEM32(0x299F20);
    eax = ZX8(MEM8(eax));
    ecx = MEM32(0x299F24);
    ecx = ZX8(MEM8(ecx));
    ecx = ecx << 2;
    edx = MEM32(ecx + 0x29A338);
    ecx = MEM32(ecx + 0x29AB38);
    eax = eax << 2;
    edi = MEM32(eax + 0x29A738);
    esi = MEM32(eax + 0x299F38);
    edx = edx + edi;
    edi = MEM32(0x299F18);
    eax = ZX8(MEM8(edi));
    eax = MEM32(eax * 4 + 0x293270);
    ecx = ecx + eax;
    SET_LO16(ecx, MEM16(ecx * 4 + 0x2952A0));
    edx = edx + eax;
    SET_LO16(ecx, LO16(ecx) | MEM16(edx * 4 + 0x294690));
    edx = MEM32(0x299F10);
    eax = eax + esi;
    SET_LO16(ecx, LO16(ecx) | MEM16(eax * 4 + 0x293A80));
    edi++;
    MEM32(0x299F18) = edi;
    MEM16(edx) = LO16(ecx);
    edx = MEM32(0x299F10);
    edx = edx + 2;
    ebx++;
    _fa = (uint32_t)(LO8(ebx)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(ebx), 1 (8-bit) */
    MEM32(0x299F10) = edx;
    if (TEST_NZ(_fa, _fb)) goto loc_0021A7CC; /* jne: not equal / not zero */

loc_0021A7B4: ;
    ecx = MEM32(0x299F20);
    eax = MEM32(0x299F24);
    ecx++;
    eax++;
    MEM32(0x299F20) = ecx;
    MEM32(0x299F24) = eax;

loc_0021A7CC: ;
    ebp--;
    if ((ebp != 0)) goto loc_0021A730; /* jne: not equal / not zero */

loc_0021A7D3: ;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebp);

loc_0021A7D6: ;
    POP32(esp, ebx);
    esp += 4; return; /* ret */

}

/**
 * sub_0021A7E0
 * Original: 0x0021A7E0 - 0x0021A8EF (271 bytes, 67 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0021A7E0(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_0021A7E0: ;
    ecx = MEM32(esp + 4);
    eax = MEM32(esp + 8);
    PUSH32(esp, ebx);
    PUSH32(esp, ebp);
    PUSH32(esp, esi);
    MEM32(esp + 0x14) = ecx;
    PUSH32(esp, edi);

loc_0021A7F0: ;
    edx = MEM32(0x299F20);
    ecx = ZX8(MEM8(edx));
    edx = MEM32(0x299F24);
    edx = ZX8(MEM8(edx));
    ecx = ecx << 2;
    ebx = MEM32(ecx + 0x29A738);
    edi = MEM32(ecx + 0x299F38);
    edx = edx << 2;
    esi = MEM32(edx + 0x29A338);
    edx = MEM32(edx + 0x29AB38);
    esi = esi + ebx;
    ebx = MEM32(0x299F18);
    ecx = ZX8(MEM8(ebx));
    ecx = MEM32(ecx * 4 + 0x293270);
    ebx++;
    MEM32(0x299F18) = ebx;
    ebx = ecx + edx;
    SET_LO16(ebx, MEM16(ebx * 4 + 0x2952A0));
    ebp = ecx + esi;
    SET_LO16(ebx, LO16(ebx) | MEM16(ebp * 4 + 0x294690));
    ecx = ecx + edi;
    SET_LO16(ebx, LO16(ebx) | MEM16(ecx * 4 + 0x293A80));
    ecx = MEM32(0x299F10);
    MEM16(ecx) = LO16(ebx);
    ebx = MEM32(0x299F1C);
    ecx = ZX8(MEM8(ebx));
    ecx = MEM32(ecx * 4 + 0x293270);
    edx = edx + ecx;
    SET_LO16(edx, MEM16(edx * 4 + 0x2952A0));
    esi = esi + ecx;
    SET_LO16(edx, LO16(edx) | MEM16(esi * 4 + 0x294690));
    ecx = ecx + edi;
    SET_LO16(edx, LO16(edx) | MEM16(ecx * 4 + 0x293A80));
    ecx = MEM32(0x299F14);
    ebx++;
    MEM32(0x299F1C) = ebx;
    MEM16(ecx) = LO16(edx);
    edi = MEM32(0x299F10);
    esi = MEM32(0x299F14);
    ecx = 2;
    edi = edi + ecx;
    esi = esi + ecx;
    eax++;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), 1 (8-bit) */
    MEM32(0x299F10) = edi;
    MEM32(0x299F14) = esi;
    if (TEST_NZ(_fa, _fb)) goto loc_0021A8E0; /* jne: not equal / not zero */

loc_0021A8C6: ;
    edx = MEM32(0x299F20);
    ecx = MEM32(0x299F24);
    edx++;
    ecx++;
    MEM32(0x299F20) = edx;
    MEM32(0x299F24) = ecx;

loc_0021A8E0: ;
    MEM32(esp + 0x18) = MEM32(esp + 0x18) - 1;
    if ((MEM32(esp + 0x18) != 0)) goto loc_0021A7F0; /* jne: not equal / not zero */

loc_0021A8EA: ;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebp);
    POP32(esp, ebx);
    esp += 4; return; /* ret */

}

/**
 * sub_0021A8F0
 * Original: 0x0021A8F0 - 0x0021A940 (80 bytes, 29 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0021A8F0(void)
{

loc_0021A8F0: ;
    eax = MEM32(esp + 0x30);
    ecx = MEM32(esp + 0x34);
    edx = MEM32(esp + 0x2C);
    PUSH32(esp, 0x29C120);
    PUSH32(esp, eax);
    eax = MEM32(esp + 0x30);
    PUSH32(esp, ecx);
    ecx = MEM32(esp + 0x30);
    PUSH32(esp, edx);
    edx = MEM32(esp + 0x30);
    PUSH32(esp, eax);
    eax = MEM32(esp + 0x30);
    PUSH32(esp, ecx);
    ecx = MEM32(esp + 0x30);
    PUSH32(esp, edx);
    edx = MEM32(esp + 0x30);
    PUSH32(esp, eax);
    eax = MEM32(esp + 0x30);
    PUSH32(esp, ecx);
    ecx = MEM32(esp + 0x30);
    PUSH32(esp, edx);
    edx = MEM32(esp + 0x30);
    PUSH32(esp, eax);
    PUSH32(esp, ecx);
    PUSH32(esp, edx);
    edx = MEM32(esp + 0x38);
    PUSH32(esp, 0x0021A93Au); sub_00214310(); /* call 0x00214310 */

loc_0021A93A: ;
    esp = esp + 0x34;
    esp += 56; return; /* ret 52 */

}

/**
 * sub_0021A940
 * Original: 0x0021A940 - 0x0021A99B (91 bytes, 34 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0021A940(void)
{

loc_0021A940: ;
    eax = MEM32(esp + 0x38);
    ecx = MEM32(esp + 0x3C);
    edx = MEM32(esp + 0x34);
    PUSH32(esp, 0x29C120);
    PUSH32(esp, eax);
    eax = MEM32(esp + 0x38);
    PUSH32(esp, ecx);
    ecx = MEM32(esp + 0x38);
    PUSH32(esp, edx);
    edx = MEM32(esp + 0x38);
    PUSH32(esp, eax);
    eax = MEM32(esp + 0x38);
    PUSH32(esp, ecx);
    ecx = MEM32(esp + 0x38);
    PUSH32(esp, edx);
    edx = MEM32(esp + 0x38);
    PUSH32(esp, eax);
    eax = MEM32(esp + 0x38);
    PUSH32(esp, ecx);
    ecx = MEM32(esp + 0x38);
    PUSH32(esp, edx);
    edx = MEM32(esp + 0x38);
    PUSH32(esp, eax);
    eax = MEM32(esp + 0x38);
    PUSH32(esp, ecx);
    ecx = MEM32(esp + 0x38);
    PUSH32(esp, edx);
    edx = MEM32(esp + 0x38);
    PUSH32(esp, eax);
    PUSH32(esp, ecx);
    PUSH32(esp, edx);
    PUSH32(esp, 0x0021A995u); sub_00214790(); /* call 0x00214790 */

loc_0021A995: ;
    esp = esp + 0x40;
    esp += 64; return; /* ret 60 */

}

/**
 * sub_0021A9A0
 * Original: 0x0021A9A0 - 0x0021ABE2 (578 bytes, 129 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0021A9A0(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    uint64_t mm0, mm1, mm2, mm3, mm4, mm5, mm6, mm7;
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_0021A9A0: ;
    PUSH32(esp, ebx);
    PUSH32(esp, ebp);
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    edi = MEM32(0x299F10);
    ebp = MEM32(0x299F20);
    ebx = MEM32(0x299F24);
    edx = MEM32(0x299F18);
    eax = MEM32(esp + 0x14);
    eax = eax << 3;
    eax = eax + edi;
    MEM32(0x299F10) = eax;
    mm7 = ((uint64_t)MEM32((uint32_t)(0x25a7e8)) | ((uint64_t)MEM32((uint32_t)(0x25a7e8) + 4u) << 32)); /* MMX 0x0021A9CA: movq mm7, qword ptr [0x25a7e8] */
    /* nop */
    /* nop */
    /* nop */

loc_0021A9E0: ;
    mm4 = (uint64_t)(uint32_t)(MEM32((uint32_t)(edx))); /* MMX 0x0021A9E0: movd mm4, dword ptr [edx] */
    mm0 = MMX_PXOR(mm0, mm0); /* MMX 0x0021A9E3: pxor mm0, mm0 */
    eax = 0; /* xor self */
    edx = edx + 4;
    SET_LO8(eax, MEM8(ebp));
    mm4 = MMX_PUNPCKLBW(mm4, mm0); /* MMX 0x0021A9EE: punpcklbw mm4, mm0 */
    mm2 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29b738))); /* MMX 0x0021A9F1: movd mm2, dword ptr [eax*4 + 0x29b738] */
    mm1 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29af38))); /* MMX 0x0021A9F9: movd mm1, dword ptr [eax*4 + 0x29af38] */
    SET_LO8(eax, MEM8(ebp + 1));
    ebp = ebp + 2;
    mm4 = MMX_PSUBUSW(mm4, ((uint64_t)MEM32((uint32_t)(0x25a7d8)) | ((uint64_t)MEM32((uint32_t)(0x25a7d8) + 4u) << 32))); /* MMX 0x0021AA07: psubusw mm4, qword ptr [0x25a7d8] */
    mm6 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29b738))); /* MMX 0x0021AA0E: movd mm6, dword ptr [eax*4 + 0x29b738] */
    mm1 = MMX_PUNPCKLDQ(mm1, (uint64_t)MEM32((uint32_t)(eax*4 + 0x29af38))); /* MMX 0x0021AA16: punpckldq mm1, dword ptr [eax*4 + 0x29af38] */
    SET_LO8(eax, MEM8(ebx));
    mm4 = MMX_PSLLW(mm4, 2u); /* MMX 0x0021AA20: psllw mm4, 2 */
    mm4 = MMX_PMULHW(mm4, ((uint64_t)MEM32((uint32_t)(0x25a7e0)) | ((uint64_t)MEM32((uint32_t)(0x25a7e0) + 4u) << 32))); /* MMX 0x0021AA24: pmulhw mm4, qword ptr [0x25a7e0] */
    mm5 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29b338))); /* MMX 0x0021AA2B: movd mm5, dword ptr [eax*4 + 0x29b338] */
    mm3 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29bb38))); /* MMX 0x0021AA33: movd mm3, dword ptr [eax*4 + 0x29bb38] */
    mm2 = MMX_PADDW(mm2, mm5); /* MMX 0x0021AA3B: paddw mm2, mm5 */
    SET_LO8(eax, MEM8(ebx + 1));
    ebx = ebx + 2;
    mm5 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29b338))); /* MMX 0x0021AA44: movd mm5, dword ptr [eax*4 + 0x29b338] */
    mm3 = MMX_PUNPCKLDQ(mm3, (uint64_t)MEM32((uint32_t)(eax*4 + 0x29bb38))); /* MMX 0x0021AA4C: punpckldq mm3, dword ptr [eax*4 + 0x29bb38] */
    mm6 = MMX_PADDW(mm6, mm5); /* MMX 0x0021AA54: paddw mm6, mm5 */
    mm2 = MMX_PUNPCKLDQ(mm2, mm6); /* MMX 0x0021AA57: punpckldq mm2, mm6 */
    mm1 = MMX_PADDW(mm1, mm4); /* MMX 0x0021AA5A: paddw mm1, mm4 */
    mm2 = MMX_PADDW(mm2, mm4); /* MMX 0x0021AA5D: paddw mm2, mm4 */
    mm1 = MMX_PADDSW(mm1, mm7); /* MMX 0x0021AA60: paddsw mm1, mm7 */
    mm3 = MMX_PADDW(mm3, mm4); /* MMX 0x0021AA63: paddw mm3, mm4 */
    mm1 = MMX_PSUBUSW(mm1, mm7); /* MMX 0x0021AA66: psubusw mm1, mm7 */
    mm1 = MMX_PSRLW(mm1, ((uint64_t)MEM32((uint32_t)(0x29bf50)) | ((uint64_t)MEM32((uint32_t)(0x29bf50) + 4u) << 32))); /* MMX 0x0021AA69: psrlw mm1, qword ptr [0x29bf50] */
    mm2 = MMX_PADDSW(mm2, mm7); /* MMX 0x0021AA70: paddsw mm2, mm7 */
    mm1 = MMX_PSLLW(mm1, ((uint64_t)MEM32((uint32_t)(0x29bf38)) | ((uint64_t)MEM32((uint32_t)(0x29bf38) + 4u) << 32))); /* MMX 0x0021AA73: psllw mm1, qword ptr [0x29bf38] */
    mm2 = MMX_PSUBUSW(mm2, mm7); /* MMX 0x0021AA7A: psubusw mm2, mm7 */
    mm2 = MMX_PSRLW(mm2, ((uint64_t)MEM32((uint32_t)(0x29bf58)) | ((uint64_t)MEM32((uint32_t)(0x29bf58) + 4u) << 32))); /* MMX 0x0021AA7D: psrlw mm2, qword ptr [0x29bf58] */
    mm3 = MMX_PADDSW(mm3, mm7); /* MMX 0x0021AA84: paddsw mm3, mm7 */
    mm2 = MMX_PSLLW(mm2, ((uint64_t)MEM32((uint32_t)(0x29bf40)) | ((uint64_t)MEM32((uint32_t)(0x29bf40) + 4u) << 32))); /* MMX 0x0021AA87: psllw mm2, qword ptr [0x29bf40] */
    mm3 = MMX_PSUBUSW(mm3, mm7); /* MMX 0x0021AA8E: psubusw mm3, mm7 */
    mm3 = MMX_PSRLW(mm3, ((uint64_t)MEM32((uint32_t)(0x29bf60)) | ((uint64_t)MEM32((uint32_t)(0x29bf60) + 4u) << 32))); /* MMX 0x0021AA91: psrlw mm3, qword ptr [0x29bf60] */
    mm1 = MMX_POR(mm1, mm2); /* MMX 0x0021AA98: por mm1, mm2 */
    mm3 = MMX_PSLLW(mm3, ((uint64_t)MEM32((uint32_t)(0x29bf48)) | ((uint64_t)MEM32((uint32_t)(0x29bf48) + 4u) << 32))); /* MMX 0x0021AA9B: psllw mm3, qword ptr [0x29bf48] */
    mm1 = MMX_POR(mm1, mm3); /* MMX 0x0021AAA2: por mm1, mm3 */
    edi = edi + 8;
    eax = MEM32(0x299F10);
    MEM32((uint32_t)(edi - 8)) = (uint32_t)mm1; MEM32((uint32_t)(edi - 8) + 4u) = (uint32_t)(mm1 >> 32); /* MMX 0x0021AAAD: movq qword ptr [edi - 8], mm1 */
    _fa = (uint32_t)(edi) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edi, eax (32-bit) */
    if (CMP_B(_fa, _fb)) goto loc_0021A9E0; /* jb: below (unsigned <) */

loc_0021AAB9: ;
    MEM32(0x299F18) = edx;
    edi = MEM32(0x299F14);
    ebp = MEM32(0x299F20);
    ebx = MEM32(0x299F24);
    edx = MEM32(0x299F1C);
    eax = MEM32(esp + 0x14);
    eax = eax << 3;
    eax = eax + edi;
    MEM32(0x299F14) = eax;
    mm7 = ((uint64_t)MEM32((uint32_t)(0x25a7e8)) | ((uint64_t)MEM32((uint32_t)(0x25a7e8) + 4u) << 32)); /* MMX 0x0021AAE5: movq mm7, qword ptr [0x25a7e8] */
    /* nop */

loc_0021AAF0: ;
    mm4 = (uint64_t)(uint32_t)(MEM32((uint32_t)(edx))); /* MMX 0x0021AAF0: movd mm4, dword ptr [edx] */
    mm0 = MMX_PXOR(mm0, mm0); /* MMX 0x0021AAF3: pxor mm0, mm0 */
    eax = 0; /* xor self */
    edx = edx + 4;
    SET_LO8(eax, MEM8(ebp));
    mm4 = MMX_PUNPCKLBW(mm4, mm0); /* MMX 0x0021AAFE: punpcklbw mm4, mm0 */
    mm2 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29b738))); /* MMX 0x0021AB01: movd mm2, dword ptr [eax*4 + 0x29b738] */
    mm1 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29af38))); /* MMX 0x0021AB09: movd mm1, dword ptr [eax*4 + 0x29af38] */
    SET_LO8(eax, MEM8(ebp + 1));
    ebp = ebp + 2;
    mm4 = MMX_PSUBUSW(mm4, ((uint64_t)MEM32((uint32_t)(0x25a7d8)) | ((uint64_t)MEM32((uint32_t)(0x25a7d8) + 4u) << 32))); /* MMX 0x0021AB17: psubusw mm4, qword ptr [0x25a7d8] */
    mm6 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29b738))); /* MMX 0x0021AB1E: movd mm6, dword ptr [eax*4 + 0x29b738] */
    mm1 = MMX_PUNPCKLDQ(mm1, (uint64_t)MEM32((uint32_t)(eax*4 + 0x29af38))); /* MMX 0x0021AB26: punpckldq mm1, dword ptr [eax*4 + 0x29af38] */
    SET_LO8(eax, MEM8(ebx));
    mm4 = MMX_PSLLW(mm4, 2u); /* MMX 0x0021AB30: psllw mm4, 2 */
    mm4 = MMX_PMULHW(mm4, ((uint64_t)MEM32((uint32_t)(0x25a7e0)) | ((uint64_t)MEM32((uint32_t)(0x25a7e0) + 4u) << 32))); /* MMX 0x0021AB34: pmulhw mm4, qword ptr [0x25a7e0] */
    mm5 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29b338))); /* MMX 0x0021AB3B: movd mm5, dword ptr [eax*4 + 0x29b338] */
    mm3 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29bb38))); /* MMX 0x0021AB43: movd mm3, dword ptr [eax*4 + 0x29bb38] */
    mm2 = MMX_PADDW(mm2, mm5); /* MMX 0x0021AB4B: paddw mm2, mm5 */
    SET_LO8(eax, MEM8(ebx + 1));
    ebx = ebx + 2;
    mm5 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29b338))); /* MMX 0x0021AB54: movd mm5, dword ptr [eax*4 + 0x29b338] */
    mm3 = MMX_PUNPCKLDQ(mm3, (uint64_t)MEM32((uint32_t)(eax*4 + 0x29bb38))); /* MMX 0x0021AB5C: punpckldq mm3, dword ptr [eax*4 + 0x29bb38] */
    mm6 = MMX_PADDW(mm6, mm5); /* MMX 0x0021AB64: paddw mm6, mm5 */
    mm2 = MMX_PUNPCKLDQ(mm2, mm6); /* MMX 0x0021AB67: punpckldq mm2, mm6 */
    mm1 = MMX_PADDW(mm1, mm4); /* MMX 0x0021AB6A: paddw mm1, mm4 */
    mm2 = MMX_PADDW(mm2, mm4); /* MMX 0x0021AB6D: paddw mm2, mm4 */
    mm1 = MMX_PADDSW(mm1, mm7); /* MMX 0x0021AB70: paddsw mm1, mm7 */
    mm3 = MMX_PADDW(mm3, mm4); /* MMX 0x0021AB73: paddw mm3, mm4 */
    mm1 = MMX_PSUBUSW(mm1, mm7); /* MMX 0x0021AB76: psubusw mm1, mm7 */
    mm1 = MMX_PSRLW(mm1, ((uint64_t)MEM32((uint32_t)(0x29bf50)) | ((uint64_t)MEM32((uint32_t)(0x29bf50) + 4u) << 32))); /* MMX 0x0021AB79: psrlw mm1, qword ptr [0x29bf50] */
    mm2 = MMX_PADDSW(mm2, mm7); /* MMX 0x0021AB80: paddsw mm2, mm7 */
    mm1 = MMX_PSLLW(mm1, ((uint64_t)MEM32((uint32_t)(0x29bf38)) | ((uint64_t)MEM32((uint32_t)(0x29bf38) + 4u) << 32))); /* MMX 0x0021AB83: psllw mm1, qword ptr [0x29bf38] */
    mm2 = MMX_PSUBUSW(mm2, mm7); /* MMX 0x0021AB8A: psubusw mm2, mm7 */
    mm2 = MMX_PSRLW(mm2, ((uint64_t)MEM32((uint32_t)(0x29bf58)) | ((uint64_t)MEM32((uint32_t)(0x29bf58) + 4u) << 32))); /* MMX 0x0021AB8D: psrlw mm2, qword ptr [0x29bf58] */
    mm3 = MMX_PADDSW(mm3, mm7); /* MMX 0x0021AB94: paddsw mm3, mm7 */
    mm2 = MMX_PSLLW(mm2, ((uint64_t)MEM32((uint32_t)(0x29bf40)) | ((uint64_t)MEM32((uint32_t)(0x29bf40) + 4u) << 32))); /* MMX 0x0021AB97: psllw mm2, qword ptr [0x29bf40] */
    mm3 = MMX_PSUBUSW(mm3, mm7); /* MMX 0x0021AB9E: psubusw mm3, mm7 */
    mm3 = MMX_PSRLW(mm3, ((uint64_t)MEM32((uint32_t)(0x29bf60)) | ((uint64_t)MEM32((uint32_t)(0x29bf60) + 4u) << 32))); /* MMX 0x0021ABA1: psrlw mm3, qword ptr [0x29bf60] */
    mm1 = MMX_POR(mm1, mm2); /* MMX 0x0021ABA8: por mm1, mm2 */
    mm3 = MMX_PSLLW(mm3, ((uint64_t)MEM32((uint32_t)(0x29bf48)) | ((uint64_t)MEM32((uint32_t)(0x29bf48) + 4u) << 32))); /* MMX 0x0021ABAB: psllw mm3, qword ptr [0x29bf48] */
    mm1 = MMX_POR(mm1, mm3); /* MMX 0x0021ABB2: por mm1, mm3 */
    edi = edi + 8;
    eax = MEM32(0x299F14);
    MEM32((uint32_t)(edi - 8)) = (uint32_t)mm1; MEM32((uint32_t)(edi - 8) + 4u) = (uint32_t)(mm1 >> 32); /* MMX 0x0021ABBD: movq qword ptr [edi - 8], mm1 */
    _fa = (uint32_t)(edi) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edi, eax (32-bit) */
    if (CMP_B(_fa, _fb)) goto loc_0021AAF0; /* jb: below (unsigned <) */

loc_0021ABC9: ;
    MEM32(0x299F20) = ebp;
    MEM32(0x299F24) = ebx;
    MEM32(0x299F1C) = edx;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebp);
    POP32(esp, ebx);
    esp += 8; return; /* ret 4 */

}

/**
 * sub_0021AF50
 * Original: 0x0021AF50 - 0x0021B021 (209 bytes, 53 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0021AF50(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_0021AF50: ;
    PUSH32(esp, ebx);
    PUSH32(esp, ebp);
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    edi = MEM32(esp + 0x14);
    esi = edi;
    ebx = 2;
    /* nop */

loc_0021AF60: ;
    ecx = MEM32(0x299F28);
    eax = ZX8(MEM8(ecx));
    edx = MEM32(0x299F18);
    ebp = ZX8(MEM8(edx));
    SET_LO16(eax, MEM16(eax * 4 + 0x295AB0));
    SET_LO16(eax, LO16(eax) | MEM16(ebp * 4 + 0x299310));
    ecx++;
    MEM32(0x299F28) = ecx;
    ecx = MEM32(0x299F10);
    edx++;
    MEM32(0x299F18) = edx;
    MEM16(ecx) = LO16(eax);
    ecx = MEM32(0x299F10);
    edx = MEM32(0x299F30);
    MEM16(edx + ecx) = LO16(eax);
    ecx = MEM32(0x299F2C);
    eax = ZX8(MEM8(ecx));
    edx = MEM32(0x299F1C);
    ebp = ZX8(MEM8(edx));
    SET_LO16(eax, MEM16(eax * 4 + 0x295AB0));
    SET_LO16(eax, LO16(eax) | MEM16(ebp * 4 + 0x299310));
    ecx++;
    MEM32(0x299F2C) = ecx;
    ecx = MEM32(0x299F14);
    edx++;
    MEM32(0x299F1C) = edx;
    MEM16(ecx) = LO16(eax);
    edx = MEM32(0x299F14);
    ecx = MEM32(0x299F30);
    MEM16(edx + ecx) = LO16(eax);
    edx = MEM32(0x299F10);
    ecx = MEM32(0x299F14);
    edx = edx + ebx;
    ecx = ecx + ebx;
    esi--;
    MEM32(0x299F10) = edx;
    MEM32(0x299F14) = ecx;
    if ((esi != 0)) goto loc_0021AF60; /* jne: not equal / not zero */

loc_0021B015: ;
    edx = MEM32(esp + 0x18);
    eax = edi + edx;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebp);
    POP32(esp, ebx);
    esp += 4; return; /* ret */

}

/**
 * sub_0021B030
 * Original: 0x0021B030 - 0x0021B098 (104 bytes, 28 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0021B030(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_0021B030: ;
    PUSH32(esp, esi);
    esi = MEM32(esp + 0xC);
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(esi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test esi, esi (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0021B096; /* je: equal / zero */

loc_0021B039: ;
    PUSH32(esp, edi);
    /* nop */

loc_0021B040: ;
    ecx = MEM32(0x299F28);
    eax = ZX8(MEM8(ecx));
    edx = MEM32(0x299F18);
    edi = ZX8(MEM8(edx));
    SET_LO16(eax, MEM16(eax * 4 + 0x295AB0));
    SET_LO16(eax, LO16(eax) | MEM16(edi * 4 + 0x299310));
    ecx++;
    MEM32(0x299F28) = ecx;
    ecx = MEM32(0x299F10);
    edx++;
    MEM32(0x299F18) = edx;
    MEM16(ecx) = LO16(eax);
    edx = MEM32(0x299F10);
    MEM16(edx + 2) = LO16(eax);
    ecx = MEM32(0x299F10);
    ecx = ecx + 4;
    esi--;
    MEM32(0x299F10) = ecx;
    if ((esi != 0)) goto loc_0021B040; /* jne: not equal / not zero */

loc_0021B095: ;
    POP32(esp, edi);

loc_0021B096: ;
    POP32(esp, esi);
    esp += 4; return; /* ret */

}

/**
 * sub_0021B0A0
 * Original: 0x0021B0A0 - 0x0021B164 (196 bytes, 51 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0021B0A0(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_0021B0A0: ;
    PUSH32(esp, ebx);
    PUSH32(esp, ebp);
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    edi = MEM32(esp + 0x14);
    esi = edi;
    ebx = 4;
    /* nop */

loc_0021B0B0: ;
    ecx = MEM32(0x299F28);
    eax = ZX8(MEM8(ecx));
    edx = MEM32(0x299F18);
    ebp = ZX8(MEM8(edx));
    SET_LO16(eax, MEM16(eax * 4 + 0x295AB0));
    SET_LO16(eax, LO16(eax) | MEM16(ebp * 4 + 0x299310));
    ecx++;
    MEM32(0x299F28) = ecx;
    ecx = MEM32(0x299F10);
    edx++;
    MEM32(0x299F18) = edx;
    MEM16(ecx) = LO16(eax);
    edx = MEM32(0x299F10);
    MEM16(edx + 2) = LO16(eax);
    ecx = MEM32(0x299F2C);
    eax = ZX8(MEM8(ecx));
    edx = MEM32(0x299F1C);
    ebp = ZX8(MEM8(edx));
    SET_LO16(eax, MEM16(eax * 4 + 0x295AB0));
    SET_LO16(eax, LO16(eax) | MEM16(ebp * 4 + 0x299310));
    ecx++;
    MEM32(0x299F2C) = ecx;
    ecx = MEM32(0x299F14);
    edx++;
    MEM32(0x299F1C) = edx;
    MEM16(ecx) = LO16(eax);
    edx = MEM32(0x299F14);
    MEM16(edx + 2) = LO16(eax);
    edx = MEM32(0x299F10);
    ecx = MEM32(0x299F14);
    edx = edx + ebx;
    ecx = ecx + ebx;
    esi--;
    MEM32(0x299F10) = edx;
    MEM32(0x299F14) = ecx;
    if ((esi != 0)) goto loc_0021B0B0; /* jne: not equal / not zero */

loc_0021B159: ;
    eax = MEM32(esp + 0x18);
    eax = eax + edi;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebp);
    POP32(esp, ebx);
    esp += 4; return; /* ret */

}

/**
 * sub_0021B170
 * Original: 0x0021B170 - 0x0021B1F9 (137 bytes, 34 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0021B170(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_0021B170: ;
    PUSH32(esp, esi);
    esi = MEM32(esp + 0xC);
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(esi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test esi, esi (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0021B1F7; /* je: equal / zero */

loc_0021B179: ;
    PUSH32(esp, edi);
    /* nop */

loc_0021B180: ;
    ecx = MEM32(0x299F28);
    eax = ZX8(MEM8(ecx));
    edx = MEM32(0x299F18);
    edi = ZX8(MEM8(edx));
    SET_LO16(eax, MEM16(eax * 4 + 0x295AB0));
    SET_LO16(eax, LO16(eax) | MEM16(edi * 4 + 0x299310));
    ecx++;
    MEM32(0x299F28) = ecx;
    ecx = MEM32(0x299F10);
    edx++;
    MEM32(0x299F18) = edx;
    MEM16(ecx) = LO16(eax);
    edx = MEM32(0x299F10);
    MEM16(edx + 2) = LO16(eax);
    edx = MEM32(0x299F10);
    ecx = MEM32(0x299F30);
    MEM16(ecx + edx) = LO16(eax);
    ecx = MEM32(0x299F10);
    edx = MEM32(0x299F30);
    MEM16(edx + ecx + 2) = LO16(eax);
    ecx = MEM32(0x299F10);
    ecx = ecx + 4;
    esi--;
    MEM32(0x299F10) = ecx;
    if ((esi != 0)) goto loc_0021B180; /* jne: not equal / not zero */

loc_0021B1F6: ;
    POP32(esp, edi);

loc_0021B1F7: ;
    POP32(esp, esi);
    esp += 4; return; /* ret */

}

/**
 * sub_0021B200
 * Original: 0x0021B200 - 0x0021B306 (262 bytes, 63 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0021B200(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_0021B200: ;
    PUSH32(esp, ebx);
    PUSH32(esp, ebp);
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    edi = MEM32(esp + 0x14);
    esi = edi;
    ebx = 4;
    /* nop */

loc_0021B210: ;
    ecx = MEM32(0x299F28);
    eax = ZX8(MEM8(ecx));
    edx = MEM32(0x299F18);
    ebp = ZX8(MEM8(edx));
    SET_LO16(eax, MEM16(eax * 4 + 0x295AB0));
    SET_LO16(eax, LO16(eax) | MEM16(ebp * 4 + 0x299310));
    ecx++;
    MEM32(0x299F28) = ecx;
    ecx = MEM32(0x299F10);
    edx++;
    MEM32(0x299F18) = edx;
    MEM16(ecx) = LO16(eax);
    edx = MEM32(0x299F10);
    MEM16(edx + 2) = LO16(eax);
    edx = MEM32(0x299F10);
    ecx = MEM32(0x299F30);
    MEM16(ecx + edx) = LO16(eax);
    edx = MEM32(0x299F10);
    ecx = MEM32(0x299F30);
    MEM16(ecx + edx + 2) = LO16(eax);
    ecx = MEM32(0x299F2C);
    eax = ZX8(MEM8(ecx));
    edx = MEM32(0x299F1C);
    ebp = ZX8(MEM8(edx));
    SET_LO16(eax, MEM16(eax * 4 + 0x295AB0));
    SET_LO16(eax, LO16(eax) | MEM16(ebp * 4 + 0x299310));
    ecx++;
    MEM32(0x299F2C) = ecx;
    ecx = MEM32(0x299F14);
    edx++;
    MEM32(0x299F1C) = edx;
    MEM16(ecx) = LO16(eax);
    edx = MEM32(0x299F14);
    MEM16(edx + 2) = LO16(eax);
    ecx = MEM32(0x299F14);
    edx = MEM32(0x299F30);
    MEM16(ecx + edx) = LO16(eax);
    ecx = MEM32(0x299F14);
    edx = MEM32(0x299F30);
    MEM16(ecx + edx + 2) = LO16(eax);
    edx = MEM32(0x299F10);
    ecx = MEM32(0x299F14);
    edx = edx + ebx;
    ecx = ecx + ebx;
    esi--;
    MEM32(0x299F10) = edx;
    MEM32(0x299F14) = ecx;
    if ((esi != 0)) goto loc_0021B210; /* jne: not equal / not zero */

loc_0021B2FB: ;
    eax = MEM32(esp + 0x18);
    eax = eax + edi;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebp);
    POP32(esp, ebx);
    esp += 4; return; /* ret */

}

/**
 * sub_0021B310
 * Original: 0x0021B310 - 0x0021B400 (240 bytes, 63 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0021B310(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_0021B310: ;
    eax = MEM32(esp + 8);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    PUSH32(esp, ebx);
    ebx = MEM32(esp + 8);
    if (TEST_Z(_fa, _fb)) goto loc_0021B3FE; /* je: equal / zero */

loc_0021B321: ;
    PUSH32(esp, ebp);
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    ebp = eax;
    goto loc_0021B330;

    /* nop */
    /* nop */

loc_0021B330: ;
    eax = MEM32(0x299F20);
    eax = ZX8(MEM8(eax));
    ecx = MEM32(0x299F24);
    ecx = ZX8(MEM8(ecx));
    eax = eax << 2;
    esi = MEM32(eax + 0x29A738);
    edi = MEM32(eax + 0x299F38);
    eax = MEM32(0x299F18);
    ecx = ecx << 2;
    edx = MEM32(ecx + 0x29A338);
    ecx = MEM32(ecx + 0x29AB38);
    edx = edx + esi;
    esi = ZX8(MEM8(eax));
    esi = MEM32(esi * 4 + 0x293270);
    eax++;
    MEM32(0x299F18) = eax;
    eax = esi + ecx;
    SET_LO16(eax, MEM16(eax * 4 + 0x2952A0));
    ecx = esi + edx;
    SET_LO16(eax, LO16(eax) | MEM16(ecx * 4 + 0x294690));
    ecx = MEM32(0x299F28);
    edx = ZX8(MEM8(ecx));
    esi = esi + edi;
    SET_LO16(eax, LO16(eax) | MEM16(esi * 4 + 0x293A80));
    SET_LO16(eax, LO16(eax) | MEM16(edx * 4 + 0x295AB0));
    ecx++;
    MEM32(0x299F28) = ecx;
    ecx = MEM32(0x299F10);
    MEM16(ecx) = LO16(eax);
    edx = MEM32(0x299F10);
    ecx = MEM32(0x299F30);
    MEM16(ecx + edx) = LO16(eax);
    edx = MEM32(0x299F10);
    edx = edx + 2;
    ebx++;
    _fa = (uint32_t)(LO8(ebx)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(ebx), 1 (8-bit) */
    MEM32(0x299F10) = edx;
    if (TEST_NZ(_fa, _fb)) goto loc_0021B3F4; /* jne: not equal / not zero */

loc_0021B3DC: ;
    ecx = MEM32(0x299F20);
    eax = MEM32(0x299F24);
    ecx++;
    eax++;
    MEM32(0x299F20) = ecx;
    MEM32(0x299F24) = eax;

loc_0021B3F4: ;
    ebp--;
    if ((ebp != 0)) goto loc_0021B330; /* jne: not equal / not zero */

loc_0021B3FB: ;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebp);

loc_0021B3FE: ;
    POP32(esp, ebx);
    esp += 4; return; /* ret */

}

/**
 * sub_0021B560
 * Original: 0x0021B560 - 0x0021B64A (234 bytes, 62 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0021B560(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_0021B560: ;
    eax = MEM32(esp + 8);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    PUSH32(esp, ebx);
    ebx = MEM32(esp + 8);
    if (TEST_Z(_fa, _fb)) goto loc_0021B648; /* je: equal / zero */

loc_0021B571: ;
    PUSH32(esp, ebp);
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    ebp = eax;
    goto loc_0021B580;

    /* nop */
    /* nop */

loc_0021B580: ;
    eax = MEM32(0x299F20);
    eax = ZX8(MEM8(eax));
    ecx = MEM32(0x299F24);
    ecx = ZX8(MEM8(ecx));
    eax = eax << 2;
    esi = MEM32(eax + 0x29A738);
    edi = MEM32(eax + 0x299F38);
    eax = MEM32(0x299F18);
    ecx = ecx << 2;
    edx = MEM32(ecx + 0x29A338);
    ecx = MEM32(ecx + 0x29AB38);
    edx = edx + esi;
    esi = ZX8(MEM8(eax));
    esi = MEM32(esi * 4 + 0x293270);
    eax++;
    MEM32(0x299F18) = eax;
    eax = esi + ecx;
    SET_LO16(eax, MEM16(eax * 4 + 0x2952A0));
    ecx = esi + edx;
    SET_LO16(eax, LO16(eax) | MEM16(ecx * 4 + 0x294690));
    ecx = MEM32(0x299F28);
    edx = ZX8(MEM8(ecx));
    esi = esi + edi;
    SET_LO16(eax, LO16(eax) | MEM16(esi * 4 + 0x293A80));
    SET_LO16(eax, LO16(eax) | MEM16(edx * 4 + 0x295AB0));
    ecx++;
    MEM32(0x299F28) = ecx;
    ecx = MEM32(0x299F10);
    MEM16(ecx) = LO16(eax);
    edx = MEM32(0x299F10);
    MEM16(edx + 2) = LO16(eax);
    edx = MEM32(0x299F10);
    edx = edx + 4;
    ebx++;
    _fa = (uint32_t)(LO8(ebx)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(ebx), 1 (8-bit) */
    MEM32(0x299F10) = edx;
    if (TEST_NZ(_fa, _fb)) goto loc_0021B63E; /* jne: not equal / not zero */

loc_0021B626: ;
    ecx = MEM32(0x299F20);
    eax = MEM32(0x299F24);
    ecx++;
    eax++;
    MEM32(0x299F20) = ecx;
    MEM32(0x299F24) = eax;

loc_0021B63E: ;
    ebp--;
    if ((ebp != 0)) goto loc_0021B580; /* jne: not equal / not zero */

loc_0021B645: ;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebp);

loc_0021B648: ;
    POP32(esp, ebx);
    esp += 4; return; /* ret */

}

/**
 * sub_0021B650
 * Original: 0x0021B650 - 0x0021B7A3 (339 bytes, 81 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0021B650(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_0021B650: ;
    ecx = MEM32(esp + 4);
    eax = MEM32(esp + 8);
    PUSH32(esp, ebx);
    PUSH32(esp, ebp);
    PUSH32(esp, esi);
    MEM32(esp + 0x14) = ecx;
    PUSH32(esp, edi);

loc_0021B660: ;
    edx = MEM32(0x299F20);
    ecx = ZX8(MEM8(edx));
    edx = MEM32(0x299F24);
    edx = ZX8(MEM8(edx));
    ecx = ecx << 2;
    ebx = MEM32(ecx + 0x299F38);
    edi = MEM32(ecx + 0x29A738);
    ecx = MEM32(0x299F18);
    edx = edx << 2;
    esi = MEM32(edx + 0x29A338);
    edx = MEM32(edx + 0x29AB38);
    esi = esi + edi;
    edi = ZX8(MEM8(ecx));
    edi = MEM32(edi * 4 + 0x293270);
    ecx++;
    MEM32(0x299F18) = ecx;
    ecx = edi + edx;
    SET_LO16(ecx, MEM16(ecx * 4 + 0x2952A0));
    ebp = edi + esi;
    SET_LO16(ecx, LO16(ecx) | MEM16(ebp * 4 + 0x294690));
    edi = edi + ebx;
    SET_LO16(ecx, LO16(ecx) | MEM16(edi * 4 + 0x293A80));
    edi = MEM32(0x299F28);
    ebp = ZX8(MEM8(edi));
    SET_LO16(ecx, LO16(ecx) | MEM16(ebp * 4 + 0x295AB0));
    edi++;
    MEM32(0x299F28) = edi;
    edi = MEM32(0x299F10);
    MEM16(edi) = LO16(ecx);
    edi = MEM32(0x299F10);
    MEM16(edi + 2) = LO16(ecx);
    ecx = MEM32(0x299F1C);
    edi = ZX8(MEM8(ecx));
    edi = MEM32(edi * 4 + 0x293270);
    ecx++;
    edx = edx + edi;
    esi = esi + edi;
    MEM32(0x299F1C) = ecx;
    SET_LO16(ecx, MEM16(edx * 4 + 0x2952A0));
    SET_LO16(ecx, LO16(ecx) | MEM16(esi * 4 + 0x294690));
    edx = MEM32(0x299F2C);
    esi = ZX8(MEM8(edx));
    edi = edi + ebx;
    SET_LO16(ecx, LO16(ecx) | MEM16(edi * 4 + 0x293A80));
    SET_LO16(ecx, LO16(ecx) | MEM16(esi * 4 + 0x295AB0));
    edx++;
    MEM32(0x299F2C) = edx;
    edx = MEM32(0x299F14);
    MEM16(edx) = LO16(ecx);
    edx = MEM32(0x299F14);
    MEM16(edx + 2) = LO16(ecx);
    edi = MEM32(0x299F10);
    esi = MEM32(0x299F14);
    ecx = 4;
    edi = edi + ecx;
    esi = esi + ecx;
    eax++;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), 1 (8-bit) */
    MEM32(0x299F10) = edi;
    MEM32(0x299F14) = esi;
    if (TEST_NZ(_fa, _fb)) goto loc_0021B794; /* jne: not equal / not zero */

loc_0021B77A: ;
    edx = MEM32(0x299F20);
    ecx = MEM32(0x299F24);
    edx++;
    ecx++;
    MEM32(0x299F20) = edx;
    MEM32(0x299F24) = ecx;

loc_0021B794: ;
    MEM32(esp + 0x18) = MEM32(esp + 0x18) - 1;
    if ((MEM32(esp + 0x18) != 0)) goto loc_0021B660; /* jne: not equal / not zero */

loc_0021B79E: ;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebp);
    POP32(esp, ebx);
    esp += 4; return; /* ret */

}

/**
 * sub_0021B7B0
 * Original: 0x0021B7B0 - 0x0021B8BB (267 bytes, 68 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0021B7B0(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_0021B7B0: ;
    eax = MEM32(esp + 8);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    PUSH32(esp, ebx);
    ebx = MEM32(esp + 8);
    if (TEST_Z(_fa, _fb)) goto loc_0021B8B9; /* je: equal / zero */

loc_0021B7C1: ;
    PUSH32(esp, ebp);
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    ebp = eax;
    goto loc_0021B7D0;

    /* nop */
    /* nop */

loc_0021B7D0: ;
    eax = MEM32(0x299F20);
    eax = ZX8(MEM8(eax));
    ecx = MEM32(0x299F24);
    ecx = ZX8(MEM8(ecx));
    eax = eax << 2;
    esi = MEM32(eax + 0x29A738);
    edi = MEM32(eax + 0x299F38);
    eax = MEM32(0x299F18);
    ecx = ecx << 2;
    edx = MEM32(ecx + 0x29A338);
    ecx = MEM32(ecx + 0x29AB38);
    edx = edx + esi;
    esi = ZX8(MEM8(eax));
    esi = MEM32(esi * 4 + 0x293270);
    eax++;
    MEM32(0x299F18) = eax;
    eax = esi + ecx;
    SET_LO16(eax, MEM16(eax * 4 + 0x2952A0));
    ecx = esi + edx;
    SET_LO16(eax, LO16(eax) | MEM16(ecx * 4 + 0x294690));
    ecx = MEM32(0x299F28);
    edx = ZX8(MEM8(ecx));
    esi = esi + edi;
    SET_LO16(eax, LO16(eax) | MEM16(esi * 4 + 0x293A80));
    SET_LO16(eax, LO16(eax) | MEM16(edx * 4 + 0x295AB0));
    ecx++;
    MEM32(0x299F28) = ecx;
    ecx = MEM32(0x299F10);
    MEM16(ecx) = LO16(eax);
    edx = MEM32(0x299F10);
    MEM16(edx + 2) = LO16(eax);
    edx = MEM32(0x299F10);
    ecx = MEM32(0x299F30);
    MEM16(ecx + edx) = LO16(eax);
    ecx = MEM32(0x299F10);
    edx = MEM32(0x299F30);
    MEM16(edx + ecx + 2) = LO16(eax);
    edx = MEM32(0x299F10);
    edx = edx + 4;
    ebx++;
    _fa = (uint32_t)(LO8(ebx)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(ebx), 1 (8-bit) */
    MEM32(0x299F10) = edx;
    if (TEST_NZ(_fa, _fb)) goto loc_0021B8AF; /* jne: not equal / not zero */

loc_0021B897: ;
    ecx = MEM32(0x299F20);
    eax = MEM32(0x299F24);
    ecx++;
    eax++;
    MEM32(0x299F20) = ecx;
    MEM32(0x299F24) = eax;

loc_0021B8AF: ;
    ebp--;
    if ((ebp != 0)) goto loc_0021B7D0; /* jne: not equal / not zero */

loc_0021B8B6: ;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebp);

loc_0021B8B9: ;
    POP32(esp, ebx);
    esp += 4; return; /* ret */

}

/**
 * sub_0021B8C0
 * Original: 0x0021B8C0 - 0x0021BA55 (405 bytes, 93 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0021B8C0(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_0021B8C0: ;
    ecx = MEM32(esp + 4);
    eax = MEM32(esp + 8);
    PUSH32(esp, ebx);
    PUSH32(esp, ebp);
    PUSH32(esp, esi);
    MEM32(esp + 0x14) = ecx;
    PUSH32(esp, edi);

loc_0021B8D0: ;
    edx = MEM32(0x299F20);
    ecx = ZX8(MEM8(edx));
    edx = MEM32(0x299F24);
    edx = ZX8(MEM8(edx));
    ecx = ecx << 2;
    ebx = MEM32(ecx + 0x299F38);
    edi = MEM32(ecx + 0x29A738);
    ecx = MEM32(0x299F18);
    edx = edx << 2;
    esi = MEM32(edx + 0x29A338);
    edx = MEM32(edx + 0x29AB38);
    esi = esi + edi;
    edi = ZX8(MEM8(ecx));
    edi = MEM32(edi * 4 + 0x293270);
    ecx++;
    MEM32(0x299F18) = ecx;
    ecx = edi + edx;
    SET_LO16(ecx, MEM16(ecx * 4 + 0x2952A0));
    ebp = edi + esi;
    SET_LO16(ecx, LO16(ecx) | MEM16(ebp * 4 + 0x294690));
    edi = edi + ebx;
    SET_LO16(ecx, LO16(ecx) | MEM16(edi * 4 + 0x293A80));
    edi = MEM32(0x299F28);
    ebp = ZX8(MEM8(edi));
    SET_LO16(ecx, LO16(ecx) | MEM16(ebp * 4 + 0x295AB0));
    edi++;
    MEM32(0x299F28) = edi;
    edi = MEM32(0x299F10);
    MEM16(edi) = LO16(ecx);
    edi = MEM32(0x299F10);
    MEM16(edi + 2) = LO16(ecx);
    ebp = MEM32(0x299F10);
    edi = MEM32(0x299F30);
    MEM16(edi + ebp) = LO16(ecx);
    edi = MEM32(0x299F30);
    ebp = MEM32(0x299F10);
    MEM16(edi + ebp + 2) = LO16(ecx);
    ecx = MEM32(0x299F1C);
    edi = ZX8(MEM8(ecx));
    edi = MEM32(edi * 4 + 0x293270);
    edx = edx + edi;
    ecx++;
    esi = esi + edi;
    MEM32(0x299F1C) = ecx;
    SET_LO16(ecx, MEM16(edx * 4 + 0x2952A0));
    SET_LO16(ecx, LO16(ecx) | MEM16(esi * 4 + 0x294690));
    edx = MEM32(0x299F2C);
    esi = ZX8(MEM8(edx));
    edi = edi + ebx;
    SET_LO16(ecx, LO16(ecx) | MEM16(edi * 4 + 0x293A80));
    SET_LO16(ecx, LO16(ecx) | MEM16(esi * 4 + 0x295AB0));
    edx++;
    MEM32(0x299F2C) = edx;
    edx = MEM32(0x299F14);
    MEM16(edx) = LO16(ecx);
    edx = MEM32(0x299F14);
    MEM16(edx + 2) = LO16(ecx);
    edx = MEM32(0x299F14);
    esi = MEM32(0x299F30);
    MEM16(edx + esi) = LO16(ecx);
    edx = MEM32(0x299F14);
    esi = MEM32(0x299F30);
    MEM16(edx + esi + 2) = LO16(ecx);
    edi = MEM32(0x299F10);
    esi = MEM32(0x299F14);
    ecx = 4;
    edi = edi + ecx;
    esi = esi + ecx;
    eax++;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), 1 (8-bit) */
    MEM32(0x299F10) = edi;
    MEM32(0x299F14) = esi;
    if (TEST_NZ(_fa, _fb)) goto loc_0021BA46; /* jne: not equal / not zero */

loc_0021BA2C: ;
    edx = MEM32(0x299F20);
    ecx = MEM32(0x299F24);
    edx++;
    ecx++;
    MEM32(0x299F20) = edx;
    MEM32(0x299F24) = ecx;

loc_0021BA46: ;
    MEM32(esp + 0x18) = MEM32(esp + 0x18) - 1;
    if ((MEM32(esp + 0x18) != 0)) goto loc_0021B8D0; /* jne: not equal / not zero */

loc_0021BA50: ;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebp);
    POP32(esp, ebx);
    esp += 4; return; /* ret */

}

/**
 * sub_0021BA60
 * Original: 0x0021BA60 - 0x0021BABE (94 bytes, 26 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0021BA60(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_0021BA60: ;
    PUSH32(esp, esi);
    esi = MEM32(esp + 0xC);
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(esi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test esi, esi (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0021BABC; /* je: equal / zero */

loc_0021BA69: ;
    PUSH32(esp, edi);
    /* nop */

loc_0021BA70: ;
    ecx = MEM32(0x299F28);
    eax = ZX8(MEM8(ecx));
    edx = MEM32(0x299F18);
    edi = ZX8(MEM8(edx));
    SET_LO16(eax, MEM16(eax * 4 + 0x295AB0));
    SET_LO16(eax, LO16(eax) | MEM16(edi * 4 + 0x299310));
    ecx++;
    MEM32(0x299F28) = ecx;
    ecx = MEM32(0x299F10);
    edx++;
    MEM32(0x299F18) = edx;
    MEM16(ecx) = LO16(eax);
    ecx = MEM32(0x299F10);
    ecx = ecx + 2;
    esi--;
    MEM32(0x299F10) = ecx;
    if ((esi != 0)) goto loc_0021BA70; /* jne: not equal / not zero */

loc_0021BABB: ;
    POP32(esp, edi);

loc_0021BABC: ;
    POP32(esp, esi);
    esp += 4; return; /* ret */

}

/**
 * sub_0021BAC0
 * Original: 0x0021BAC0 - 0x0021BB71 (177 bytes, 47 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0021BAC0(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_0021BAC0: ;
    PUSH32(esp, ebx);
    PUSH32(esp, ebp);
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    edi = MEM32(esp + 0x14);
    esi = edi;
    ebx = 2;
    /* nop */

loc_0021BAD0: ;
    ecx = MEM32(0x299F28);
    eax = ZX8(MEM8(ecx));
    edx = MEM32(0x299F18);
    ebp = ZX8(MEM8(edx));
    SET_LO16(eax, MEM16(eax * 4 + 0x295AB0));
    SET_LO16(eax, LO16(eax) | MEM16(ebp * 4 + 0x299310));
    ecx++;
    MEM32(0x299F28) = ecx;
    ecx = MEM32(0x299F10);
    edx++;
    MEM32(0x299F18) = edx;
    MEM16(ecx) = LO16(eax);
    ecx = MEM32(0x299F2C);
    eax = ZX8(MEM8(ecx));
    edx = MEM32(0x299F1C);
    ebp = ZX8(MEM8(edx));
    SET_LO16(eax, MEM16(eax * 4 + 0x295AB0));
    SET_LO16(eax, LO16(eax) | MEM16(ebp * 4 + 0x299310));
    ecx++;
    MEM32(0x299F2C) = ecx;
    ecx = MEM32(0x299F14);
    edx++;
    MEM32(0x299F1C) = edx;
    MEM16(ecx) = LO16(eax);
    edx = MEM32(0x299F10);
    ecx = MEM32(0x299F14);
    edx = edx + ebx;
    ecx = ecx + ebx;
    esi--;
    MEM32(0x299F10) = edx;
    MEM32(0x299F14) = ecx;
    if ((esi != 0)) goto loc_0021BAD0; /* jne: not equal / not zero */

loc_0021BB65: ;
    edx = MEM32(esp + 0x18);
    eax = edi + edx;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebp);
    POP32(esp, ebx);
    esp += 4; return; /* ret */

}

/**
 * sub_0021BB80
 * Original: 0x0021BB80 - 0x0021BC66 (230 bytes, 61 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0021BB80(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_0021BB80: ;
    eax = MEM32(esp + 8);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    PUSH32(esp, ebx);
    ebx = MEM32(esp + 8);
    if (TEST_Z(_fa, _fb)) goto loc_0021BC64; /* je: equal / zero */

loc_0021BB91: ;
    PUSH32(esp, ebp);
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    ebp = eax;
    goto loc_0021BBA0;

    /* nop */
    /* nop */

loc_0021BBA0: ;
    eax = MEM32(0x299F20);
    eax = ZX8(MEM8(eax));
    ecx = MEM32(0x299F24);
    ecx = ZX8(MEM8(ecx));
    ecx = ecx << 2;
    edx = MEM32(ecx + 0x29A338);
    ecx = MEM32(ecx + 0x29AB38);
    eax = eax << 2;
    edi = MEM32(eax + 0x29A738);
    esi = MEM32(eax + 0x299F38);
    edx = edx + edi;
    edi = MEM32(0x299F18);
    eax = ZX8(MEM8(edi));
    eax = MEM32(eax * 4 + 0x293270);
    ecx = ecx + eax;
    SET_LO16(ecx, MEM16(ecx * 4 + 0x2952A0));
    edx = edx + eax;
    SET_LO16(ecx, LO16(ecx) | MEM16(edx * 4 + 0x294690));
    edx = MEM32(0x299F28);
    eax = eax + esi;
    SET_LO16(ecx, LO16(ecx) | MEM16(eax * 4 + 0x293A80));
    edi++;
    MEM32(0x299F18) = edi;
    eax = ZX8(MEM8(edx));
    SET_LO16(ecx, LO16(ecx) | MEM16(eax * 4 + 0x295AB0));
    edx = MEM32(0x299F10);
    MEM16(edx) = LO16(ecx);
    esi = MEM32(0x299F28);
    edx = MEM32(0x299F10);
    esi++;
    edx = edx + 2;
    ebx++;
    _fa = (uint32_t)(LO8(ebx)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(ebx), 1 (8-bit) */
    MEM32(0x299F28) = esi;
    MEM32(0x299F10) = edx;
    if (TEST_NZ(_fa, _fb)) goto loc_0021BC5A; /* jne: not equal / not zero */

loc_0021BC42: ;
    ecx = MEM32(0x299F20);
    eax = MEM32(0x299F24);
    ecx++;
    eax++;
    MEM32(0x299F20) = ecx;
    MEM32(0x299F24) = eax;

loc_0021BC5A: ;
    ebp--;
    if ((ebp != 0)) goto loc_0021BBA0; /* jne: not equal / not zero */

loc_0021BC61: ;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebp);

loc_0021BC64: ;
    POP32(esp, ebx);
    esp += 4; return; /* ret */

}

/**
 * sub_0021BC70
 * Original: 0x0021BC70 - 0x0021BDBB (331 bytes, 79 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0021BC70(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_0021BC70: ;
    ecx = MEM32(esp + 4);
    eax = MEM32(esp + 8);
    PUSH32(esp, ebx);
    PUSH32(esp, ebp);
    PUSH32(esp, esi);
    MEM32(esp + 0x14) = ecx;
    PUSH32(esp, edi);

loc_0021BC80: ;
    edx = MEM32(0x299F20);
    ecx = ZX8(MEM8(edx));
    edx = MEM32(0x299F24);
    edx = ZX8(MEM8(edx));
    ecx = ecx << 2;
    ebx = MEM32(ecx + 0x29A738);
    edi = MEM32(ecx + 0x299F38);
    edx = edx << 2;
    esi = MEM32(edx + 0x29A338);
    edx = MEM32(edx + 0x29AB38);
    esi = esi + ebx;
    ebx = MEM32(0x299F18);
    ecx = ZX8(MEM8(ebx));
    ecx = MEM32(ecx * 4 + 0x293270);
    ebx++;
    MEM32(0x299F18) = ebx;
    ebx = ecx + edx;
    SET_LO16(ebx, MEM16(ebx * 4 + 0x2952A0));
    ebp = ecx + esi;
    SET_LO16(ebx, LO16(ebx) | MEM16(ebp * 4 + 0x294690));
    ecx = ecx + edi;
    SET_LO16(ebx, LO16(ebx) | MEM16(ecx * 4 + 0x293A80));
    ecx = MEM32(0x299F28);
    ecx = ZX8(MEM8(ecx));
    SET_LO16(ebx, LO16(ebx) | MEM16(ecx * 4 + 0x295AB0));
    ecx = MEM32(0x299F10);
    MEM16(ecx) = LO16(ebx);
    ecx = MEM32(0x299F28);
    ebx = MEM32(0x299F1C);
    ecx++;
    MEM32(0x299F28) = ecx;
    ecx = ZX8(MEM8(ebx));
    ecx = MEM32(ecx * 4 + 0x293270);
    edx = edx + ecx;
    SET_LO16(edx, MEM16(edx * 4 + 0x2952A0));
    esi = esi + ecx;
    SET_LO16(edx, LO16(edx) | MEM16(esi * 4 + 0x294690));
    ecx = ecx + edi;
    SET_LO16(edx, LO16(edx) | MEM16(ecx * 4 + 0x293A80));
    ecx = MEM32(0x299F2C);
    ebx++;
    MEM32(0x299F1C) = ebx;
    ecx = ZX8(MEM8(ecx));
    SET_LO16(edx, LO16(edx) | MEM16(ecx * 4 + 0x295AB0));
    ecx = MEM32(0x299F14);
    MEM16(ecx) = LO16(edx);
    ebx = MEM32(0x299F2C);
    edi = MEM32(0x299F10);
    esi = MEM32(0x299F14);
    ecx = 2;
    ebx++;
    edi = edi + ecx;
    esi = esi + ecx;
    eax++;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), 1 (8-bit) */
    MEM32(0x299F2C) = ebx;
    MEM32(0x299F10) = edi;
    MEM32(0x299F14) = esi;
    if (TEST_NZ(_fa, _fb)) goto loc_0021BDAC; /* jne: not equal / not zero */

loc_0021BD92: ;
    edx = MEM32(0x299F20);
    ecx = MEM32(0x299F24);
    edx++;
    ecx++;
    MEM32(0x299F20) = edx;
    MEM32(0x299F24) = ecx;

loc_0021BDAC: ;
    MEM32(esp + 0x18) = MEM32(esp + 0x18) - 1;
    if ((MEM32(esp + 0x18) != 0)) goto loc_0021BC80; /* jne: not equal / not zero */

loc_0021BDB6: ;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebp);
    POP32(esp, ebx);
    esp += 4; return; /* ret */

}

/**
 * sub_0021BDC0
 * Original: 0x0021BDC0 - 0x0021BE10 (80 bytes, 29 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0021BDC0(void)
{

loc_0021BDC0: ;
    eax = MEM32(esp + 0x30);
    ecx = MEM32(esp + 0x34);
    edx = MEM32(esp + 0x2C);
    PUSH32(esp, 0x29C1E0);
    PUSH32(esp, eax);
    eax = MEM32(esp + 0x30);
    PUSH32(esp, ecx);
    ecx = MEM32(esp + 0x30);
    PUSH32(esp, edx);
    edx = MEM32(esp + 0x30);
    PUSH32(esp, eax);
    eax = MEM32(esp + 0x30);
    PUSH32(esp, ecx);
    ecx = MEM32(esp + 0x30);
    PUSH32(esp, edx);
    edx = MEM32(esp + 0x30);
    PUSH32(esp, eax);
    eax = MEM32(esp + 0x30);
    PUSH32(esp, ecx);
    ecx = MEM32(esp + 0x30);
    PUSH32(esp, edx);
    edx = MEM32(esp + 0x30);
    PUSH32(esp, eax);
    PUSH32(esp, ecx);
    PUSH32(esp, edx);
    edx = MEM32(esp + 0x38);
    PUSH32(esp, 0x0021BE0Au); sub_00214310(); /* call 0x00214310 */

loc_0021BE0A: ;
    esp = esp + 0x34;
    esp += 56; return; /* ret 52 */

}

/**
 * sub_0021BE10
 * Original: 0x0021BE10 - 0x0021BE6B (91 bytes, 34 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0021BE10(void)
{

loc_0021BE10: ;
    eax = MEM32(esp + 0x38);
    ecx = MEM32(esp + 0x3C);
    edx = MEM32(esp + 0x34);
    PUSH32(esp, 0x29C1E0);
    PUSH32(esp, eax);
    eax = MEM32(esp + 0x38);
    PUSH32(esp, ecx);
    ecx = MEM32(esp + 0x38);
    PUSH32(esp, edx);
    edx = MEM32(esp + 0x38);
    PUSH32(esp, eax);
    eax = MEM32(esp + 0x38);
    PUSH32(esp, ecx);
    ecx = MEM32(esp + 0x38);
    PUSH32(esp, edx);
    edx = MEM32(esp + 0x38);
    PUSH32(esp, eax);
    eax = MEM32(esp + 0x38);
    PUSH32(esp, ecx);
    ecx = MEM32(esp + 0x38);
    PUSH32(esp, edx);
    edx = MEM32(esp + 0x38);
    PUSH32(esp, eax);
    eax = MEM32(esp + 0x38);
    PUSH32(esp, ecx);
    ecx = MEM32(esp + 0x38);
    PUSH32(esp, edx);
    edx = MEM32(esp + 0x38);
    PUSH32(esp, eax);
    PUSH32(esp, ecx);
    PUSH32(esp, edx);
    PUSH32(esp, 0x0021BE65u); sub_00214790(); /* call 0x00214790 */

loc_0021BE65: ;
    esp = esp + 0x40;
    esp += 64; return; /* ret 60 */

}

/**
 * sub_0021BE70
 * Original: 0x0021BE70 - 0x0021C0C6 (598 bytes, 143 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0021BE70(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    uint64_t mm0, mm1, mm2, mm3, mm4, mm5, mm6, mm7;
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_0021BE70: ;
    PUSH32(esp, ebx);
    PUSH32(esp, ebp);
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    edi = MEM32(0x299F10);
    ebp = MEM32(0x299F20);
    ebx = MEM32(0x299F24);
    edx = MEM32(0x299F18);
    ecx = MEM32(0x299F28);
    eax = MEM32(esp + 0x14);
    eax = eax << 3;
    eax = eax + edi;
    MEM32(0x299F10) = eax;
    mm7 = ((uint64_t)MEM32((uint32_t)(0x25a7e8)) | ((uint64_t)MEM32((uint32_t)(0x25a7e8) + 4u) << 32)); /* MMX 0x0021BEA0: movq mm7, qword ptr [0x25a7e8] */
    /* nop */
    edi = edi;

loc_0021BEB0: ;
    mm4 = (uint64_t)(uint32_t)(MEM32((uint32_t)(edx))); /* MMX 0x0021BEB0: movd mm4, dword ptr [edx] */
    mm0 = MMX_PXOR(mm0, mm0); /* MMX 0x0021BEB3: pxor mm0, mm0 */
    eax = 0; /* xor self */
    edx = edx + 4;
    SET_LO8(eax, MEM8(ebp));
    mm4 = MMX_PUNPCKLBW(mm4, mm0); /* MMX 0x0021BEBE: punpcklbw mm4, mm0 */
    mm2 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29b738))); /* MMX 0x0021BEC1: movd mm2, dword ptr [eax*4 + 0x29b738] */
    mm1 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29af38))); /* MMX 0x0021BEC9: movd mm1, dword ptr [eax*4 + 0x29af38] */
    SET_LO8(eax, MEM8(ebp + 1));
    ebp = ebp + 2;
    mm4 = MMX_PSUBUSW(mm4, ((uint64_t)MEM32((uint32_t)(0x25a7d8)) | ((uint64_t)MEM32((uint32_t)(0x25a7d8) + 4u) << 32))); /* MMX 0x0021BED7: psubusw mm4, qword ptr [0x25a7d8] */
    mm6 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29b738))); /* MMX 0x0021BEDE: movd mm6, dword ptr [eax*4 + 0x29b738] */
    mm1 = MMX_PUNPCKLDQ(mm1, (uint64_t)MEM32((uint32_t)(eax*4 + 0x29af38))); /* MMX 0x0021BEE6: punpckldq mm1, dword ptr [eax*4 + 0x29af38] */
    SET_LO8(eax, MEM8(ebx));
    mm4 = MMX_PSLLW(mm4, 2u); /* MMX 0x0021BEF0: psllw mm4, 2 */
    mm4 = MMX_PMULHW(mm4, ((uint64_t)MEM32((uint32_t)(0x25a7e0)) | ((uint64_t)MEM32((uint32_t)(0x25a7e0) + 4u) << 32))); /* MMX 0x0021BEF4: pmulhw mm4, qword ptr [0x25a7e0] */
    mm5 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29b338))); /* MMX 0x0021BEFB: movd mm5, dword ptr [eax*4 + 0x29b338] */
    mm3 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29bb38))); /* MMX 0x0021BF03: movd mm3, dword ptr [eax*4 + 0x29bb38] */
    mm2 = MMX_PADDW(mm2, mm5); /* MMX 0x0021BF0B: paddw mm2, mm5 */
    SET_LO8(eax, MEM8(ebx + 1));
    ebx = ebx + 2;
    mm5 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29b338))); /* MMX 0x0021BF14: movd mm5, dword ptr [eax*4 + 0x29b338] */
    mm3 = MMX_PUNPCKLDQ(mm3, (uint64_t)MEM32((uint32_t)(eax*4 + 0x29bb38))); /* MMX 0x0021BF1C: punpckldq mm3, dword ptr [eax*4 + 0x29bb38] */
    mm6 = MMX_PADDW(mm6, mm5); /* MMX 0x0021BF24: paddw mm6, mm5 */
    mm2 = MMX_PUNPCKLDQ(mm2, mm6); /* MMX 0x0021BF27: punpckldq mm2, mm6 */
    mm1 = MMX_PADDW(mm1, mm4); /* MMX 0x0021BF2A: paddw mm1, mm4 */
    mm2 = MMX_PADDW(mm2, mm4); /* MMX 0x0021BF2D: paddw mm2, mm4 */
    mm1 = MMX_PADDSW(mm1, mm7); /* MMX 0x0021BF30: paddsw mm1, mm7 */
    mm3 = MMX_PADDW(mm3, mm4); /* MMX 0x0021BF33: paddw mm3, mm4 */
    mm1 = MMX_PSUBUSW(mm1, mm7); /* MMX 0x0021BF36: psubusw mm1, mm7 */
    mm1 = MMX_PSRLW(mm1, 4u); /* MMX 0x0021BF39: psrlw mm1, 4 */
    mm2 = MMX_PADDSW(mm2, mm7); /* MMX 0x0021BF3D: paddsw mm2, mm7 */
    mm6 = (uint64_t)(uint32_t)(MEM32((uint32_t)(ecx))); /* MMX 0x0021BF40: movd mm6, dword ptr [ecx] */
    mm2 = MMX_PSUBUSW(mm2, mm7); /* MMX 0x0021BF43: psubusw mm2, mm7 */
    mm2 = MMX_PSRLW(mm2, 4u); /* MMX 0x0021BF46: psrlw mm2, 4 */
    mm3 = MMX_PADDSW(mm3, mm7); /* MMX 0x0021BF4A: paddsw mm3, mm7 */
    mm2 = MMX_PSLLW(mm2, 4u); /* MMX 0x0021BF4D: psllw mm2, 4 */
    mm3 = MMX_PSUBUSW(mm3, mm7); /* MMX 0x0021BF51: psubusw mm3, mm7 */
    mm3 = MMX_PSRLW(mm3, 4u); /* MMX 0x0021BF54: psrlw mm3, 4 */
    mm1 = MMX_POR(mm1, mm2); /* MMX 0x0021BF58: por mm1, mm2 */
    mm3 = MMX_PSLLW(mm3, 8u); /* MMX 0x0021BF5B: psllw mm3, 8 */
    mm6 = MMX_PUNPCKLBW(mm6, mm0); /* MMX 0x0021BF5F: punpcklbw mm6, mm0 */
    mm1 = MMX_POR(mm1, mm3); /* MMX 0x0021BF62: por mm1, mm3 */
    mm6 = MMX_PSRLW(mm6, 4u); /* MMX 0x0021BF65: psrlw mm6, 4 */
    mm6 = MMX_PSLLW(mm6, 0xcu); /* MMX 0x0021BF69: psllw mm6, 0xc */
    edi = edi + 8;
    mm1 = MMX_POR(mm1, mm6); /* MMX 0x0021BF70: por mm1, mm6 */
    eax = MEM32(0x299F10);
    ecx = ecx + 4;
    MEM32((uint32_t)(edi - 8)) = (uint32_t)mm1; MEM32((uint32_t)(edi - 8) + 4u) = (uint32_t)(mm1 >> 32); /* MMX 0x0021BF7B: movq qword ptr [edi - 8], mm1 */
    _fa = (uint32_t)(edi) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edi, eax (32-bit) */
    if (CMP_B(_fa, _fb)) goto loc_0021BEB0; /* jb: below (unsigned <) */

loc_0021BF87: ;
    MEM32(0x299F18) = edx;
    MEM32(0x299F28) = ecx;
    edi = MEM32(0x299F14);
    ebp = MEM32(0x299F20);
    ebx = MEM32(0x299F24);
    edx = MEM32(0x299F1C);
    ecx = MEM32(0x299F2C);
    eax = MEM32(esp + 0x14);
    eax = eax << 3;
    eax = eax + edi;
    MEM32(0x299F14) = eax;
    mm7 = ((uint64_t)MEM32((uint32_t)(0x25a7e8)) | ((uint64_t)MEM32((uint32_t)(0x25a7e8) + 4u) << 32)); /* MMX 0x0021BFBF: movq mm7, qword ptr [0x25a7e8] */
    /* nop */
    /* nop */

loc_0021BFD0: ;
    mm4 = (uint64_t)(uint32_t)(MEM32((uint32_t)(edx))); /* MMX 0x0021BFD0: movd mm4, dword ptr [edx] */
    mm0 = MMX_PXOR(mm0, mm0); /* MMX 0x0021BFD3: pxor mm0, mm0 */
    eax = 0; /* xor self */
    edx = edx + 4;
    SET_LO8(eax, MEM8(ebp));
    mm4 = MMX_PUNPCKLBW(mm4, mm0); /* MMX 0x0021BFDE: punpcklbw mm4, mm0 */
    mm2 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29b738))); /* MMX 0x0021BFE1: movd mm2, dword ptr [eax*4 + 0x29b738] */
    mm1 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29af38))); /* MMX 0x0021BFE9: movd mm1, dword ptr [eax*4 + 0x29af38] */
    SET_LO8(eax, MEM8(ebp + 1));
    ebp = ebp + 2;
    mm4 = MMX_PSUBUSW(mm4, ((uint64_t)MEM32((uint32_t)(0x25a7d8)) | ((uint64_t)MEM32((uint32_t)(0x25a7d8) + 4u) << 32))); /* MMX 0x0021BFF7: psubusw mm4, qword ptr [0x25a7d8] */
    mm6 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29b738))); /* MMX 0x0021BFFE: movd mm6, dword ptr [eax*4 + 0x29b738] */
    mm1 = MMX_PUNPCKLDQ(mm1, (uint64_t)MEM32((uint32_t)(eax*4 + 0x29af38))); /* MMX 0x0021C006: punpckldq mm1, dword ptr [eax*4 + 0x29af38] */
    SET_LO8(eax, MEM8(ebx));
    mm4 = MMX_PSLLW(mm4, 2u); /* MMX 0x0021C010: psllw mm4, 2 */
    mm4 = MMX_PMULHW(mm4, ((uint64_t)MEM32((uint32_t)(0x25a7e0)) | ((uint64_t)MEM32((uint32_t)(0x25a7e0) + 4u) << 32))); /* MMX 0x0021C014: pmulhw mm4, qword ptr [0x25a7e0] */
    mm5 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29b338))); /* MMX 0x0021C01B: movd mm5, dword ptr [eax*4 + 0x29b338] */
    mm3 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29bb38))); /* MMX 0x0021C023: movd mm3, dword ptr [eax*4 + 0x29bb38] */
    mm2 = MMX_PADDW(mm2, mm5); /* MMX 0x0021C02B: paddw mm2, mm5 */
    SET_LO8(eax, MEM8(ebx + 1));
    ebx = ebx + 2;
    mm5 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29b338))); /* MMX 0x0021C034: movd mm5, dword ptr [eax*4 + 0x29b338] */
    mm3 = MMX_PUNPCKLDQ(mm3, (uint64_t)MEM32((uint32_t)(eax*4 + 0x29bb38))); /* MMX 0x0021C03C: punpckldq mm3, dword ptr [eax*4 + 0x29bb38] */
    mm6 = MMX_PADDW(mm6, mm5); /* MMX 0x0021C044: paddw mm6, mm5 */
    mm2 = MMX_PUNPCKLDQ(mm2, mm6); /* MMX 0x0021C047: punpckldq mm2, mm6 */
    mm1 = MMX_PADDW(mm1, mm4); /* MMX 0x0021C04A: paddw mm1, mm4 */
    mm2 = MMX_PADDW(mm2, mm4); /* MMX 0x0021C04D: paddw mm2, mm4 */
    mm1 = MMX_PADDSW(mm1, mm7); /* MMX 0x0021C050: paddsw mm1, mm7 */
    mm3 = MMX_PADDW(mm3, mm4); /* MMX 0x0021C053: paddw mm3, mm4 */
    mm1 = MMX_PSUBUSW(mm1, mm7); /* MMX 0x0021C056: psubusw mm1, mm7 */
    mm1 = MMX_PSRLW(mm1, 4u); /* MMX 0x0021C059: psrlw mm1, 4 */
    mm2 = MMX_PADDSW(mm2, mm7); /* MMX 0x0021C05D: paddsw mm2, mm7 */
    mm6 = (uint64_t)(uint32_t)(MEM32((uint32_t)(ecx))); /* MMX 0x0021C060: movd mm6, dword ptr [ecx] */
    mm2 = MMX_PSUBUSW(mm2, mm7); /* MMX 0x0021C063: psubusw mm2, mm7 */
    mm2 = MMX_PSRLW(mm2, 4u); /* MMX 0x0021C066: psrlw mm2, 4 */
    mm3 = MMX_PADDSW(mm3, mm7); /* MMX 0x0021C06A: paddsw mm3, mm7 */
    mm2 = MMX_PSLLW(mm2, 4u); /* MMX 0x0021C06D: psllw mm2, 4 */
    mm3 = MMX_PSUBUSW(mm3, mm7); /* MMX 0x0021C071: psubusw mm3, mm7 */
    mm3 = MMX_PSRLW(mm3, 4u); /* MMX 0x0021C074: psrlw mm3, 4 */
    mm1 = MMX_POR(mm1, mm2); /* MMX 0x0021C078: por mm1, mm2 */
    mm3 = MMX_PSLLW(mm3, 8u); /* MMX 0x0021C07B: psllw mm3, 8 */
    mm6 = MMX_PUNPCKLBW(mm6, mm0); /* MMX 0x0021C07F: punpcklbw mm6, mm0 */
    mm1 = MMX_POR(mm1, mm3); /* MMX 0x0021C082: por mm1, mm3 */
    mm6 = MMX_PSRLW(mm6, 4u); /* MMX 0x0021C085: psrlw mm6, 4 */
    mm6 = MMX_PSLLW(mm6, 0xcu); /* MMX 0x0021C089: psllw mm6, 0xc */
    edi = edi + 8;
    mm1 = MMX_POR(mm1, mm6); /* MMX 0x0021C090: por mm1, mm6 */
    eax = MEM32(0x299F14);
    ecx = ecx + 4;
    MEM32((uint32_t)(edi - 8)) = (uint32_t)mm1; MEM32((uint32_t)(edi - 8) + 4u) = (uint32_t)(mm1 >> 32); /* MMX 0x0021C09B: movq qword ptr [edi - 8], mm1 */
    _fa = (uint32_t)(edi) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edi, eax (32-bit) */
    if (CMP_B(_fa, _fb)) goto loc_0021BFD0; /* jb: below (unsigned <) */

loc_0021C0A7: ;
    MEM32(0x299F20) = ebp;
    MEM32(0x299F24) = ebx;
    MEM32(0x299F1C) = edx;
    MEM32(0x299F2C) = ecx;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebp);
    POP32(esp, ebx);
    esp += 8; return; /* ret 4 */

}

/**
 * sub_0021C430
 * Original: 0x0021C430 - 0x0021C505 (213 bytes, 59 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0021C430(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_0021C430: ;
    PUSH32(esp, ebx);
    PUSH32(esp, ebp);
    ebp = MEM32(esp + 0xC);
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    edi = ebp;
    /* nop */

loc_0021C440: ;
    esi = MEM32(0x299F28);
    SET_LO8(edx, MEM8(esi));
    ecx = MEM32(0x299F18);
    eax = ZX8(MEM8(ecx));
    SET_LO8(edx, LO8(edx) & 0x80);
    ebx = 0; /* xor self */
    SET_HI8(ebx, LO8(edx));
    SET_LO16(ebx, LO16(ebx) | MEM16(eax * 4 + 0x299310));
    esi++;
    ecx++;
    MEM32(0x299F18) = ecx;
    ecx = MEM32(0x299F10);
    MEM32(0x299F28) = esi;
    eax = ebx;
    MEM16(ecx) = LO16(eax);
    ecx = MEM32(0x299F10);
    edx = MEM32(0x299F30);
    MEM16(edx + ecx) = LO16(eax);
    esi = MEM32(0x299F2C);
    SET_LO8(eax, MEM8(esi));
    ecx = MEM32(0x299F1C);
    edx = ZX8(MEM8(ecx));
    SET_LO8(eax, LO8(eax) & 0x80);
    ebx = 0; /* xor self */
    SET_HI8(ebx, LO8(eax));
    SET_LO16(ebx, LO16(ebx) | MEM16(edx * 4 + 0x299310));
    esi++;
    ecx++;
    MEM32(0x299F1C) = ecx;
    ecx = MEM32(0x299F14);
    MEM32(0x299F2C) = esi;
    eax = ebx;
    MEM16(ecx) = LO16(eax);
    edx = MEM32(0x299F14);
    ecx = MEM32(0x299F30);
    MEM16(edx + ecx) = LO16(eax);
    edx = MEM32(0x299F10);
    ecx = MEM32(0x299F14);
    eax = 2;
    edx = edx + eax;
    ecx = ecx + eax;
    edi--;
    MEM32(0x299F10) = edx;
    MEM32(0x299F14) = ecx;
    if ((edi != 0)) goto loc_0021C440; /* jne: not equal / not zero */

loc_0021C4F9: ;
    edx = MEM32(esp + 0x18);
    POP32(esp, edi);
    POP32(esp, esi);
    eax = edx + ebp;
    POP32(esp, ebp);
    POP32(esp, ebx);
    esp += 4; return; /* ret */

}

/**
 * sub_0021C510
 * Original: 0x0021C510 - 0x0021C579 (105 bytes, 34 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0021C510(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_0021C510: ;
    PUSH32(esp, edi);
    edi = MEM32(esp + 0xC);
    _fa = (uint32_t)(edi) & 0xFFFFFFFFu; _fb = (uint32_t)(edi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test edi, edi (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0021C577; /* je: equal / zero */

loc_0021C519: ;
    PUSH32(esp, ebx);
    PUSH32(esp, esi);
    goto loc_0021C520;

    /* nop */

loc_0021C520: ;
    esi = MEM32(0x299F28);
    SET_LO8(edx, MEM8(esi));
    ecx = MEM32(0x299F18);
    eax = ZX8(MEM8(ecx));
    ebx = 0; /* xor self */
    SET_LO8(edx, LO8(edx) & 0x80);
    SET_HI8(ebx, LO8(edx));
    SET_LO16(ebx, LO16(ebx) | MEM16(eax * 4 + 0x299310));
    esi++;
    ecx++;
    MEM32(0x299F18) = ecx;
    ecx = MEM32(0x299F10);
    MEM32(0x299F28) = esi;
    eax = ebx;
    MEM16(ecx) = LO16(eax);
    edx = MEM32(0x299F10);
    MEM16(edx + 2) = LO16(eax);
    ecx = MEM32(0x299F10);
    ecx = ecx + 4;
    edi--;
    MEM32(0x299F10) = ecx;
    if ((edi != 0)) goto loc_0021C520; /* jne: not equal / not zero */

loc_0021C575: ;
    POP32(esp, esi);
    POP32(esp, ebx);

loc_0021C577: ;
    POP32(esp, edi);
    esp += 4; return; /* ret */

}

/**
 * sub_0021C580
 * Original: 0x0021C580 - 0x0021C649 (201 bytes, 57 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0021C580(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_0021C580: ;
    PUSH32(esp, ebx);
    PUSH32(esp, ebp);
    ebp = MEM32(esp + 0xC);
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    edi = ebp;
    /* nop */

loc_0021C590: ;
    esi = MEM32(0x299F28);
    SET_LO8(edx, MEM8(esi));
    ecx = MEM32(0x299F18);
    eax = ZX8(MEM8(ecx));
    SET_LO8(edx, LO8(edx) & 0x80);
    ebx = 0; /* xor self */
    SET_HI8(ebx, LO8(edx));
    SET_LO16(ebx, LO16(ebx) | MEM16(eax * 4 + 0x299310));
    esi++;
    ecx++;
    MEM32(0x299F18) = ecx;
    ecx = MEM32(0x299F10);
    MEM32(0x299F28) = esi;
    eax = ebx;
    MEM16(ecx) = LO16(eax);
    edx = MEM32(0x299F10);
    MEM16(edx + 2) = LO16(eax);
    esi = MEM32(0x299F2C);
    SET_LO8(edx, MEM8(esi));
    ecx = MEM32(0x299F1C);
    eax = ZX8(MEM8(ecx));
    SET_LO8(edx, LO8(edx) & 0x80);
    ebx = 0; /* xor self */
    SET_HI8(ebx, LO8(edx));
    SET_LO16(ebx, LO16(ebx) | MEM16(eax * 4 + 0x299310));
    esi++;
    ecx++;
    MEM32(0x299F1C) = ecx;
    ecx = MEM32(0x299F14);
    MEM32(0x299F2C) = esi;
    eax = ebx;
    MEM16(ecx) = LO16(eax);
    edx = MEM32(0x299F14);
    MEM16(edx + 2) = LO16(eax);
    edx = MEM32(0x299F10);
    ecx = MEM32(0x299F14);
    eax = 4;
    edx = edx + eax;
    ecx = ecx + eax;
    edi--;
    MEM32(0x299F10) = edx;
    MEM32(0x299F14) = ecx;
    if ((edi != 0)) goto loc_0021C590; /* jne: not equal / not zero */

loc_0021C63E: ;
    eax = MEM32(esp + 0x18);
    POP32(esp, edi);
    POP32(esp, esi);
    eax = eax + ebp;
    POP32(esp, ebp);
    POP32(esp, ebx);
    esp += 4; return; /* ret */

}

/**
 * sub_0021C650
 * Original: 0x0021C650 - 0x0021C6DA (138 bytes, 40 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0021C650(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_0021C650: ;
    PUSH32(esp, edi);
    edi = MEM32(esp + 0xC);
    _fa = (uint32_t)(edi) & 0xFFFFFFFFu; _fb = (uint32_t)(edi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test edi, edi (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0021C6D8; /* je: equal / zero */

loc_0021C659: ;
    PUSH32(esp, ebx);
    PUSH32(esp, esi);
    goto loc_0021C660;

    /* nop */

loc_0021C660: ;
    esi = MEM32(0x299F28);
    SET_LO8(edx, MEM8(esi));
    ecx = MEM32(0x299F18);
    eax = ZX8(MEM8(ecx));
    SET_LO8(edx, LO8(edx) & 0x80);
    ebx = 0; /* xor self */
    SET_HI8(ebx, LO8(edx));
    SET_LO16(ebx, LO16(ebx) | MEM16(eax * 4 + 0x299310));
    esi++;
    ecx++;
    MEM32(0x299F18) = ecx;
    ecx = MEM32(0x299F10);
    MEM32(0x299F28) = esi;
    eax = ebx;
    MEM16(ecx) = LO16(eax);
    edx = MEM32(0x299F10);
    MEM16(edx + 2) = LO16(eax);
    edx = MEM32(0x299F10);
    ecx = MEM32(0x299F30);
    MEM16(ecx + edx) = LO16(eax);
    ecx = MEM32(0x299F10);
    edx = MEM32(0x299F30);
    MEM16(edx + ecx + 2) = LO16(eax);
    ecx = MEM32(0x299F10);
    ecx = ecx + 4;
    edi--;
    MEM32(0x299F10) = ecx;
    if ((edi != 0)) goto loc_0021C660; /* jne: not equal / not zero */

loc_0021C6D6: ;
    POP32(esp, esi);
    POP32(esp, ebx);

loc_0021C6D8: ;
    POP32(esp, edi);
    esp += 4; return; /* ret */

}

/**
 * sub_0021C6E0
 * Original: 0x0021C6E0 - 0x0021C7EB (267 bytes, 69 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0021C6E0(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_0021C6E0: ;
    PUSH32(esp, ebx);
    PUSH32(esp, ebp);
    ebp = MEM32(esp + 0xC);
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    edi = ebp;
    /* nop */

loc_0021C6F0: ;
    esi = MEM32(0x299F28);
    SET_LO8(edx, MEM8(esi));
    ecx = MEM32(0x299F18);
    eax = ZX8(MEM8(ecx));
    SET_LO8(edx, LO8(edx) & 0x80);
    ebx = 0; /* xor self */
    SET_HI8(ebx, LO8(edx));
    SET_LO16(ebx, LO16(ebx) | MEM16(eax * 4 + 0x299310));
    esi++;
    ecx++;
    MEM32(0x299F18) = ecx;
    ecx = MEM32(0x299F10);
    MEM32(0x299F28) = esi;
    eax = ebx;
    MEM16(ecx) = LO16(eax);
    edx = MEM32(0x299F10);
    MEM16(edx + 2) = LO16(eax);
    edx = MEM32(0x299F10);
    ecx = MEM32(0x299F30);
    MEM16(ecx + edx) = LO16(eax);
    edx = MEM32(0x299F10);
    ecx = MEM32(0x299F30);
    MEM16(ecx + edx + 2) = LO16(eax);
    esi = MEM32(0x299F2C);
    SET_LO8(edx, MEM8(esi));
    ecx = MEM32(0x299F1C);
    eax = ZX8(MEM8(ecx));
    SET_LO8(edx, LO8(edx) & 0x80);
    ebx = 0; /* xor self */
    SET_HI8(ebx, LO8(edx));
    SET_LO16(ebx, LO16(ebx) | MEM16(eax * 4 + 0x299310));
    esi++;
    ecx++;
    MEM32(0x299F1C) = ecx;
    ecx = MEM32(0x299F14);
    MEM32(0x299F2C) = esi;
    eax = ebx;
    MEM16(ecx) = LO16(eax);
    edx = MEM32(0x299F14);
    MEM16(edx + 2) = LO16(eax);
    ecx = MEM32(0x299F14);
    edx = MEM32(0x299F30);
    MEM16(ecx + edx) = LO16(eax);
    ecx = MEM32(0x299F14);
    edx = MEM32(0x299F30);
    MEM16(ecx + edx + 2) = LO16(eax);
    edx = MEM32(0x299F10);
    ecx = MEM32(0x299F14);
    eax = 4;
    edx = edx + eax;
    ecx = ecx + eax;
    edi--;
    MEM32(0x299F10) = edx;
    MEM32(0x299F14) = ecx;
    if ((edi != 0)) goto loc_0021C6F0; /* jne: not equal / not zero */

loc_0021C7E0: ;
    eax = MEM32(esp + 0x18);
    POP32(esp, edi);
    POP32(esp, esi);
    eax = eax + ebp;
    POP32(esp, ebp);
    POP32(esp, ebx);
    esp += 4; return; /* ret */

}

/**
 * sub_0021C7F0
 * Original: 0x0021C7F0 - 0x0021C8E0 (240 bytes, 66 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0021C7F0(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_0021C7F0: ;
    eax = MEM32(esp + 8);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    PUSH32(esp, ebx);
    ebx = MEM32(esp + 8);
    if (TEST_Z(_fa, _fb)) goto loc_0021C8DE; /* je: equal / zero */

loc_0021C801: ;
    PUSH32(esp, ebp);
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    ebp = eax;
    goto loc_0021C810;

    /* nop */
    /* nop */

loc_0021C810: ;
    eax = MEM32(0x299F20);
    eax = ZX8(MEM8(eax));
    ecx = MEM32(0x299F24);
    ecx = ZX8(MEM8(ecx));
    eax = eax << 2;
    esi = MEM32(eax + 0x29A738);
    edi = MEM32(eax + 0x299F38);
    eax = MEM32(0x299F18);
    ecx = ecx << 2;
    edx = MEM32(ecx + 0x29A338);
    ecx = MEM32(ecx + 0x29AB38);
    edx = edx + esi;
    esi = ZX8(MEM8(eax));
    esi = MEM32(esi * 4 + 0x293270);
    eax++;
    MEM32(0x299F18) = eax;
    eax = esi + ecx;
    eax = ZX16(MEM16(eax * 4 + 0x2952A0));
    ecx = esi + edx;
    SET_LO16(eax, LO16(eax) | MEM16(ecx * 4 + 0x294690));
    esi = esi + edi;
    SET_LO16(eax, LO16(eax) | MEM16(esi * 4 + 0x293A80));
    esi = MEM32(0x299F28);
    SET_LO8(edx, MEM8(esi));
    SET_LO8(edx, LO8(edx) & 0x80);
    ecx = 0; /* xor self */
    SET_HI8(ecx, LO8(edx));
    edx = MEM32(0x299F10);
    eax = eax | ecx;
    esi++;
    MEM32(0x299F28) = esi;
    MEM16(edx) = LO16(eax);
    ecx = MEM32(0x299F10);
    edx = MEM32(0x299F30);
    MEM16(edx + ecx) = LO16(eax);
    edx = MEM32(0x299F10);
    edx = edx + 2;
    ebx++;
    _fa = (uint32_t)(LO8(ebx)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(ebx), 1 (8-bit) */
    MEM32(0x299F10) = edx;
    if (TEST_NZ(_fa, _fb)) goto loc_0021C8D4; /* jne: not equal / not zero */

loc_0021C8BC: ;
    ecx = MEM32(0x299F20);
    eax = MEM32(0x299F24);
    ecx++;
    eax++;
    MEM32(0x299F20) = ecx;
    MEM32(0x299F24) = eax;

loc_0021C8D4: ;
    ebp--;
    if ((ebp != 0)) goto loc_0021C810; /* jne: not equal / not zero */

loc_0021C8DB: ;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebp);

loc_0021C8DE: ;
    POP32(esp, ebx);
    esp += 4; return; /* ret */

}

/**
 * sub_0021CA60
 * Original: 0x0021CA60 - 0x0021CB4A (234 bytes, 65 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0021CA60(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_0021CA60: ;
    eax = MEM32(esp + 8);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    PUSH32(esp, ebx);
    ebx = MEM32(esp + 8);
    if (TEST_Z(_fa, _fb)) goto loc_0021CB48; /* je: equal / zero */

loc_0021CA71: ;
    PUSH32(esp, ebp);
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    ebp = eax;
    goto loc_0021CA80;

    /* nop */
    /* nop */

loc_0021CA80: ;
    eax = MEM32(0x299F20);
    eax = ZX8(MEM8(eax));
    ecx = MEM32(0x299F24);
    ecx = ZX8(MEM8(ecx));
    eax = eax << 2;
    esi = MEM32(eax + 0x29A738);
    edi = MEM32(eax + 0x299F38);
    eax = MEM32(0x299F18);
    ecx = ecx << 2;
    edx = MEM32(ecx + 0x29A338);
    ecx = MEM32(ecx + 0x29AB38);
    edx = edx + esi;
    esi = ZX8(MEM8(eax));
    esi = MEM32(esi * 4 + 0x293270);
    eax++;
    MEM32(0x299F18) = eax;
    eax = esi + ecx;
    eax = ZX16(MEM16(eax * 4 + 0x2952A0));
    ecx = esi + edx;
    SET_LO16(eax, LO16(eax) | MEM16(ecx * 4 + 0x294690));
    esi = esi + edi;
    SET_LO16(eax, LO16(eax) | MEM16(esi * 4 + 0x293A80));
    esi = MEM32(0x299F28);
    SET_LO8(edx, MEM8(esi));
    SET_LO8(edx, LO8(edx) & 0x80);
    ecx = 0; /* xor self */
    SET_HI8(ecx, LO8(edx));
    edx = MEM32(0x299F10);
    eax = eax | ecx;
    esi++;
    MEM32(0x299F28) = esi;
    MEM16(edx) = LO16(eax);
    ecx = MEM32(0x299F10);
    MEM16(ecx + 2) = LO16(eax);
    edx = MEM32(0x299F10);
    edx = edx + 4;
    ebx++;
    _fa = (uint32_t)(LO8(ebx)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(ebx), 1 (8-bit) */
    MEM32(0x299F10) = edx;
    if (TEST_NZ(_fa, _fb)) goto loc_0021CB3E; /* jne: not equal / not zero */

loc_0021CB26: ;
    ecx = MEM32(0x299F20);
    eax = MEM32(0x299F24);
    ecx++;
    eax++;
    MEM32(0x299F20) = ecx;
    MEM32(0x299F24) = eax;

loc_0021CB3E: ;
    ebp--;
    if ((ebp != 0)) goto loc_0021CA80; /* jne: not equal / not zero */

loc_0021CB45: ;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebp);

loc_0021CB48: ;
    POP32(esp, ebx);
    esp += 4; return; /* ret */

}

/**
 * sub_0021CB50
 * Original: 0x0021CB50 - 0x0021CCB7 (359 bytes, 95 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0021CB50(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_0021CB50: ;
    eax = MEM32(esp + 8);
    ecx = MEM32(esp + 4);
    PUSH32(esp, ebx);
    PUSH32(esp, ebp);
    PUSH32(esp, esi);
    MEM32(esp + 0x14) = eax;
    MEM32(esp + 0x10) = ecx;
    PUSH32(esp, edi);
    goto loc_0021CB70;

    /* nop */
    /* nop */

loc_0021CB70: ;
    edx = MEM32(0x299F20);
    ecx = ZX8(MEM8(edx));
    eax = MEM32(0x299F24);
    edx = ZX8(MEM8(eax));
    eax = MEM32(0x299F18);
    ecx = ecx << 2;
    ebp = MEM32(ecx + 0x299F38);
    edi = MEM32(ecx + 0x29A738);
    ecx = ZX8(MEM8(eax));
    edx = edx << 2;
    esi = MEM32(edx + 0x29A338);
    edx = MEM32(edx + 0x29AB38);
    esi = esi + edi;
    edi = MEM32(ecx * 4 + 0x293270);
    eax++;
    MEM32(0x299F18) = eax;
    eax = edi + edx;
    ecx = 0; /* xor self */
    SET_LO16(ecx, MEM16(eax * 4 + 0x2952A0));
    ebx = edi + esi;
    SET_LO16(ecx, LO16(ecx) | MEM16(ebx * 4 + 0x294690));
    edi = edi + ebp;
    SET_LO16(ecx, LO16(ecx) | MEM16(edi * 4 + 0x293A80));
    edi = MEM32(0x299F28);
    SET_LO8(eax, MEM8(edi));
    SET_LO8(eax, LO8(eax) & 0x80);
    ebx = 0; /* xor self */
    SET_HI8(ebx, LO8(eax));
    eax = MEM32(0x299F10);
    ecx = ecx | ebx;
    edi++;
    MEM32(0x299F28) = edi;
    MEM16(eax) = LO16(ecx);
    eax = MEM32(0x299F10);
    MEM16(eax + 2) = LO16(ecx);
    eax = MEM32(0x299F1C);
    ecx = ZX8(MEM8(eax));
    edi = MEM32(ecx * 4 + 0x293270);
    eax++;
    MEM32(0x299F1C) = eax;
    edx = edx + edi;
    eax = edi + esi;
    esi = MEM32(0x299F2C);
    ecx = 0; /* xor self */
    SET_LO16(ecx, MEM16(edx * 4 + 0x2952A0));
    SET_LO16(ecx, LO16(ecx) | MEM16(eax * 4 + 0x294690));
    SET_LO8(edx, MEM8(esi));
    eax = 0; /* xor self */
    edi = edi + ebp;
    SET_LO16(ecx, LO16(ecx) | MEM16(edi * 4 + 0x293A80));
    SET_LO8(edx, LO8(edx) & 0x80);
    SET_HI8(eax, LO8(edx));
    edx = MEM32(0x299F14);
    ecx = ecx | eax;
    esi++;
    MEM32(0x299F2C) = esi;
    MEM16(edx) = LO16(ecx);
    eax = MEM32(0x299F14);
    MEM16(eax + 2) = LO16(ecx);
    edi = MEM32(0x299F10);
    esi = MEM32(0x299F14);
    eax = 4;
    edi = edi + eax;
    esi = esi + eax;
    eax = MEM32(esp + 0x18);
    eax++;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), 1 (8-bit) */
    MEM32(0x299F10) = edi;
    MEM32(0x299F14) = esi;
    MEM32(esp + 0x18) = eax;
    if (TEST_NZ(_fa, _fb)) goto loc_0021CCA8; /* jne: not equal / not zero */

loc_0021CC8E: ;
    edx = MEM32(0x299F20);
    ecx = MEM32(0x299F24);
    edx++;
    ecx++;
    MEM32(0x299F20) = edx;
    MEM32(0x299F24) = ecx;

loc_0021CCA8: ;
    MEM32(esp + 0x14) = MEM32(esp + 0x14) - 1;
    if ((MEM32(esp + 0x14) != 0)) goto loc_0021CB70; /* jne: not equal / not zero */

loc_0021CCB2: ;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebp);
    POP32(esp, ebx);
    esp += 4; return; /* ret */

}

/**
 * sub_0021CCC0
 * Original: 0x0021CCC0 - 0x0021CDCB (267 bytes, 71 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0021CCC0(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_0021CCC0: ;
    eax = MEM32(esp + 8);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    PUSH32(esp, ebx);
    ebx = MEM32(esp + 8);
    if (TEST_Z(_fa, _fb)) goto loc_0021CDC9; /* je: equal / zero */

loc_0021CCD1: ;
    PUSH32(esp, ebp);
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    ebp = eax;
    goto loc_0021CCE0;

    /* nop */
    /* nop */

loc_0021CCE0: ;
    eax = MEM32(0x299F20);
    eax = ZX8(MEM8(eax));
    ecx = MEM32(0x299F24);
    ecx = ZX8(MEM8(ecx));
    eax = eax << 2;
    esi = MEM32(eax + 0x29A738);
    edi = MEM32(eax + 0x299F38);
    eax = MEM32(0x299F18);
    ecx = ecx << 2;
    edx = MEM32(ecx + 0x29A338);
    ecx = MEM32(ecx + 0x29AB38);
    edx = edx + esi;
    esi = ZX8(MEM8(eax));
    esi = MEM32(esi * 4 + 0x293270);
    eax++;
    MEM32(0x299F18) = eax;
    eax = esi + ecx;
    eax = ZX16(MEM16(eax * 4 + 0x2952A0));
    ecx = esi + edx;
    SET_LO16(eax, LO16(eax) | MEM16(ecx * 4 + 0x294690));
    esi = esi + edi;
    SET_LO16(eax, LO16(eax) | MEM16(esi * 4 + 0x293A80));
    esi = MEM32(0x299F28);
    SET_LO8(edx, MEM8(esi));
    SET_LO8(edx, LO8(edx) & 0x80);
    ecx = 0; /* xor self */
    SET_HI8(ecx, LO8(edx));
    edx = MEM32(0x299F10);
    eax = eax | ecx;
    esi++;
    MEM32(0x299F28) = esi;
    MEM16(edx) = LO16(eax);
    ecx = MEM32(0x299F10);
    MEM16(ecx + 2) = LO16(eax);
    ecx = MEM32(0x299F10);
    edx = MEM32(0x299F30);
    MEM16(edx + ecx) = LO16(eax);
    edx = MEM32(0x299F10);
    ecx = MEM32(0x299F30);
    MEM16(ecx + edx + 2) = LO16(eax);
    edx = MEM32(0x299F10);
    edx = edx + 4;
    ebx++;
    _fa = (uint32_t)(LO8(ebx)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(ebx), 1 (8-bit) */
    MEM32(0x299F10) = edx;
    if (TEST_NZ(_fa, _fb)) goto loc_0021CDBF; /* jne: not equal / not zero */

loc_0021CDA7: ;
    ecx = MEM32(0x299F20);
    eax = MEM32(0x299F24);
    ecx++;
    eax++;
    MEM32(0x299F20) = ecx;
    MEM32(0x299F24) = eax;

loc_0021CDBF: ;
    ebp--;
    if ((ebp != 0)) goto loc_0021CCE0; /* jne: not equal / not zero */

loc_0021CDC6: ;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebp);

loc_0021CDC9: ;
    POP32(esp, ebx);
    esp += 4; return; /* ret */

}

/**
 * sub_0021CDD0
 * Original: 0x0021CDD0 - 0x0021CF75 (421 bytes, 107 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0021CDD0(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_0021CDD0: ;
    eax = MEM32(esp + 8);
    ecx = MEM32(esp + 4);
    PUSH32(esp, ebx);
    PUSH32(esp, ebp);
    PUSH32(esp, esi);
    MEM32(esp + 0x14) = eax;
    MEM32(esp + 0x10) = ecx;
    PUSH32(esp, edi);
    goto loc_0021CDF0;

    /* nop */
    /* nop */

loc_0021CDF0: ;
    edx = MEM32(0x299F20);
    ecx = ZX8(MEM8(edx));
    eax = MEM32(0x299F24);
    edx = ZX8(MEM8(eax));
    eax = MEM32(0x299F18);
    ecx = ecx << 2;
    ebp = MEM32(ecx + 0x299F38);
    edi = MEM32(ecx + 0x29A738);
    ecx = ZX8(MEM8(eax));
    edx = edx << 2;
    esi = MEM32(edx + 0x29A338);
    edx = MEM32(edx + 0x29AB38);
    esi = esi + edi;
    edi = MEM32(ecx * 4 + 0x293270);
    eax++;
    MEM32(0x299F18) = eax;
    eax = edi + edx;
    ebx = edi + esi;
    ecx = 0; /* xor self */
    SET_LO16(ecx, MEM16(eax * 4 + 0x2952A0));
    SET_LO16(ecx, LO16(ecx) | MEM16(ebx * 4 + 0x294690));
    edi = edi + ebp;
    SET_LO16(ecx, LO16(ecx) | MEM16(edi * 4 + 0x293A80));
    edi = MEM32(0x299F28);
    SET_LO8(eax, MEM8(edi));
    SET_LO8(eax, LO8(eax) & 0x80);
    ebx = 0; /* xor self */
    SET_HI8(ebx, LO8(eax));
    eax = MEM32(0x299F10);
    ecx = ecx | ebx;
    edi++;
    MEM32(0x299F28) = edi;
    MEM16(eax) = LO16(ecx);
    eax = MEM32(0x299F10);
    MEM16(eax + 2) = LO16(ecx);
    edi = MEM32(0x299F10);
    eax = MEM32(0x299F30);
    MEM16(eax + edi) = LO16(ecx);
    edi = MEM32(0x299F10);
    eax = MEM32(0x299F30);
    MEM16(eax + edi + 2) = LO16(ecx);
    eax = MEM32(0x299F1C);
    ecx = ZX8(MEM8(eax));
    edi = MEM32(ecx * 4 + 0x293270);
    eax++;
    MEM32(0x299F1C) = eax;
    edx = edx + edi;
    eax = edi + esi;
    esi = MEM32(0x299F2C);
    ecx = 0; /* xor self */
    SET_LO16(ecx, MEM16(edx * 4 + 0x2952A0));
    SET_LO16(ecx, LO16(ecx) | MEM16(eax * 4 + 0x294690));
    SET_LO8(edx, MEM8(esi));
    eax = 0; /* xor self */
    edi = edi + ebp;
    SET_LO16(ecx, LO16(ecx) | MEM16(edi * 4 + 0x293A80));
    SET_LO8(edx, LO8(edx) & 0x80);
    SET_HI8(eax, LO8(edx));
    edx = MEM32(0x299F14);
    ecx = ecx | eax;
    esi++;
    MEM32(0x299F2C) = esi;
    MEM16(edx) = LO16(ecx);
    eax = MEM32(0x299F14);
    MEM16(eax + 2) = LO16(ecx);
    edx = MEM32(0x299F14);
    eax = MEM32(0x299F30);
    MEM16(edx + eax) = LO16(ecx);
    edx = MEM32(0x299F14);
    eax = MEM32(0x299F30);
    MEM16(edx + eax + 2) = LO16(ecx);
    edi = MEM32(0x299F10);
    esi = MEM32(0x299F14);
    eax = 4;
    edi = edi + eax;
    esi = esi + eax;
    eax = MEM32(esp + 0x18);
    eax++;
    MEM32(0x299F10) = edi;
    MEM32(0x299F14) = esi;
    MEM32(esp + 0x18) = eax;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), 1 (8-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_0021CF66; /* jne: not equal / not zero */

loc_0021CF4C: ;
    edx = MEM32(0x299F20);
    ecx = MEM32(0x299F24);
    edx++;
    ecx++;
    MEM32(0x299F20) = edx;
    MEM32(0x299F24) = ecx;

loc_0021CF66: ;
    MEM32(esp + 0x14) = MEM32(esp + 0x14) - 1;
    if ((MEM32(esp + 0x14) != 0)) goto loc_0021CDF0; /* jne: not equal / not zero */

loc_0021CF70: ;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebp);
    POP32(esp, ebx);
    esp += 4; return; /* ret */

}

/**
 * sub_0021CF80
 * Original: 0x0021CF80 - 0x0021CFDC (92 bytes, 32 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0021CF80(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_0021CF80: ;
    PUSH32(esp, edi);
    edi = MEM32(esp + 0xC);
    _fa = (uint32_t)(edi) & 0xFFFFFFFFu; _fb = (uint32_t)(edi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test edi, edi (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0021CFDA; /* je: equal / zero */

loc_0021CF89: ;
    PUSH32(esp, ebx);
    PUSH32(esp, esi);
    goto loc_0021CF90;

    /* nop */

loc_0021CF90: ;
    esi = MEM32(0x299F28);
    SET_LO8(edx, MEM8(esi));
    eax = MEM32(0x299F18);
    ecx = ZX8(MEM8(eax));
    ebx = 0; /* xor self */
    SET_LO8(edx, LO8(edx) & 0x80);
    SET_HI8(ebx, LO8(edx));
    SET_LO16(ebx, LO16(ebx) | MEM16(ecx * 4 + 0x299310));
    esi++;
    eax++;
    MEM32(0x299F18) = eax;
    eax = MEM32(0x299F10);
    MEM32(0x299F28) = esi;
    ecx = ebx;
    MEM16(eax) = LO16(ecx);
    ecx = MEM32(0x299F10);
    ecx = ecx + 2;
    edi--;
    MEM32(0x299F10) = ecx;
    if ((edi != 0)) goto loc_0021CF90; /* jne: not equal / not zero */

loc_0021CFD8: ;
    POP32(esp, esi);
    POP32(esp, ebx);

loc_0021CFDA: ;
    POP32(esp, edi);
    esp += 4; return; /* ret */

}

/**
 * sub_0021CFE0
 * Original: 0x0021CFE0 - 0x0021D090 (176 bytes, 53 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0021CFE0(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_0021CFE0: ;
    PUSH32(esp, ebx);
    PUSH32(esp, ebp);
    ebp = MEM32(esp + 0xC);
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    edi = ebp;
    /* nop */

loc_0021CFF0: ;
    esi = MEM32(0x299F28);
    SET_LO8(edx, MEM8(esi));
    eax = MEM32(0x299F18);
    ecx = ZX8(MEM8(eax));
    ebx = 0; /* xor self */
    SET_LO8(edx, LO8(edx) & 0x80);
    SET_HI8(ebx, LO8(edx));
    SET_LO16(ebx, LO16(ebx) | MEM16(ecx * 4 + 0x299310));
    esi++;
    eax++;
    MEM32(0x299F18) = eax;
    eax = MEM32(0x299F10);
    MEM32(0x299F28) = esi;
    ecx = ebx;
    MEM16(eax) = LO16(ecx);
    esi = MEM32(0x299F2C);
    SET_LO8(edx, MEM8(esi));
    eax = MEM32(0x299F1C);
    ecx = ZX8(MEM8(eax));
    SET_LO8(edx, LO8(edx) & 0x80);
    ebx = 0; /* xor self */
    SET_HI8(ebx, LO8(edx));
    SET_LO16(ebx, LO16(ebx) | MEM16(ecx * 4 + 0x299310));
    esi++;
    eax++;
    MEM32(0x299F1C) = eax;
    eax = MEM32(0x299F14);
    MEM32(0x299F2C) = esi;
    ecx = ebx;
    MEM16(eax) = LO16(ecx);
    edx = MEM32(0x299F10);
    ecx = MEM32(0x299F14);
    eax = 2;
    edx = edx + eax;
    ecx = ecx + eax;
    edi--;
    MEM32(0x299F10) = edx;
    MEM32(0x299F14) = ecx;
    if ((edi != 0)) goto loc_0021CFF0; /* jne: not equal / not zero */

loc_0021D084: ;
    ecx = MEM32(esp + 0x18);
    POP32(esp, edi);
    POP32(esp, esi);
    eax = ecx + ebp;
    POP32(esp, ebp);
    POP32(esp, ebx);
    esp += 4; return; /* ret */

}

/**
 * sub_0021D180
 * Original: 0x0021D180 - 0x0021D2D1 (337 bytes, 87 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0021D180(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_0021D180: ;
    ecx = MEM32(esp + 4);
    eax = MEM32(esp + 8);
    PUSH32(esp, ebx);
    PUSH32(esp, ebp);
    PUSH32(esp, esi);
    MEM32(esp + 0x14) = ecx;
    PUSH32(esp, edi);

loc_0021D190: ;
    edx = MEM32(0x299F20);
    ecx = ZX8(MEM8(edx));
    edx = MEM32(0x299F24);
    edx = ZX8(MEM8(edx));
    ecx = ecx << 2;
    ebx = MEM32(ecx + 0x29A738);
    edi = MEM32(ecx + 0x299F38);
    edx = edx << 2;
    esi = MEM32(edx + 0x29A338);
    edx = MEM32(edx + 0x29AB38);
    esi = esi + ebx;
    ebx = MEM32(0x299F18);
    ecx = ZX8(MEM8(ebx));
    ecx = MEM32(ecx * 4 + 0x293270);
    ebx++;
    MEM32(0x299F18) = ebx;
    ebx = ecx + edx;
    ebx = ZX16(MEM16(ebx * 4 + 0x2952A0));
    ebp = ecx + esi;
    SET_LO16(ebx, LO16(ebx) | MEM16(ebp * 4 + 0x294690));
    ecx = ecx + edi;
    SET_LO16(ebx, LO16(ebx) | MEM16(ecx * 4 + 0x293A80));
    ecx = MEM32(0x299F28);
    SET_LO8(ecx, MEM8(ecx));
    SET_LO8(ecx, LO8(ecx) & 0x80);
    MEM32(esp + 0x14) = eax;
    eax = 0; /* xor self */
    SET_HI8(eax, LO8(ecx));
    ecx = MEM32(0x299F10);
    ebx = ebx | eax;
    MEM16(ecx) = LO16(ebx);
    eax = MEM32(0x299F28);
    ebx = MEM32(0x299F1C);
    eax++;
    MEM32(0x299F28) = eax;
    ecx = ZX8(MEM8(ebx));
    ecx = MEM32(ecx * 4 + 0x293270);
    edx = edx + ecx;
    edx = ZX16(MEM16(edx * 4 + 0x2952A0));
    esi = esi + ecx;
    SET_LO16(edx, LO16(edx) | MEM16(esi * 4 + 0x294690));
    eax = MEM32(esp + 0x14);
    ecx = ecx + edi;
    SET_LO16(edx, LO16(edx) | MEM16(ecx * 4 + 0x293A80));
    ecx = MEM32(0x299F2C);
    ebx++;
    MEM32(0x299F1C) = ebx;
    SET_LO8(ecx, MEM8(ecx));
    SET_LO8(ecx, LO8(ecx) & 0x80);
    ebx = 0; /* xor self */
    SET_HI8(ebx, LO8(ecx));
    ecx = MEM32(0x299F14);
    edx = edx | ebx;
    MEM16(ecx) = LO16(edx);
    ebx = MEM32(0x299F2C);
    edi = MEM32(0x299F10);
    esi = MEM32(0x299F14);
    ecx = 2;
    ebx++;
    edi = edi + ecx;
    esi = esi + ecx;
    eax++;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), 1 (8-bit) */
    MEM32(0x299F2C) = ebx;
    MEM32(0x299F10) = edi;
    MEM32(0x299F14) = esi;
    if (TEST_NZ(_fa, _fb)) goto loc_0021D2C2; /* jne: not equal / not zero */

loc_0021D2A8: ;
    edx = MEM32(0x299F20);
    ecx = MEM32(0x299F24);
    edx++;
    ecx++;
    MEM32(0x299F20) = edx;
    MEM32(0x299F24) = ecx;

loc_0021D2C2: ;
    MEM32(esp + 0x18) = MEM32(esp + 0x18) - 1;
    if ((MEM32(esp + 0x18) != 0)) goto loc_0021D190; /* jne: not equal / not zero */

loc_0021D2CC: ;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebp);
    POP32(esp, ebx);
    esp += 4; return; /* ret */

}

/**
 * sub_0021D2E0
 * Original: 0x0021D2E0 - 0x0021D330 (80 bytes, 29 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0021D2E0(void)
{

loc_0021D2E0: ;
    eax = MEM32(esp + 0x30);
    ecx = MEM32(esp + 0x34);
    edx = MEM32(esp + 0x2C);
    PUSH32(esp, 0x29C2A0);
    PUSH32(esp, eax);
    eax = MEM32(esp + 0x30);
    PUSH32(esp, ecx);
    ecx = MEM32(esp + 0x30);
    PUSH32(esp, edx);
    edx = MEM32(esp + 0x30);
    PUSH32(esp, eax);
    eax = MEM32(esp + 0x30);
    PUSH32(esp, ecx);
    ecx = MEM32(esp + 0x30);
    PUSH32(esp, edx);
    edx = MEM32(esp + 0x30);
    PUSH32(esp, eax);
    eax = MEM32(esp + 0x30);
    PUSH32(esp, ecx);
    ecx = MEM32(esp + 0x30);
    PUSH32(esp, edx);
    edx = MEM32(esp + 0x30);
    PUSH32(esp, eax);
    PUSH32(esp, ecx);
    PUSH32(esp, edx);
    edx = MEM32(esp + 0x38);
    PUSH32(esp, 0x0021D32Au); sub_00214310(); /* call 0x00214310 */

loc_0021D32A: ;
    esp = esp + 0x34;
    esp += 56; return; /* ret 52 */

}

/**
 * sub_0021D330
 * Original: 0x0021D330 - 0x0021D38B (91 bytes, 34 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0021D330(void)
{

loc_0021D330: ;
    eax = MEM32(esp + 0x38);
    ecx = MEM32(esp + 0x3C);
    edx = MEM32(esp + 0x34);
    PUSH32(esp, 0x29C2A0);
    PUSH32(esp, eax);
    eax = MEM32(esp + 0x38);
    PUSH32(esp, ecx);
    ecx = MEM32(esp + 0x38);
    PUSH32(esp, edx);
    edx = MEM32(esp + 0x38);
    PUSH32(esp, eax);
    eax = MEM32(esp + 0x38);
    PUSH32(esp, ecx);
    ecx = MEM32(esp + 0x38);
    PUSH32(esp, edx);
    edx = MEM32(esp + 0x38);
    PUSH32(esp, eax);
    eax = MEM32(esp + 0x38);
    PUSH32(esp, ecx);
    ecx = MEM32(esp + 0x38);
    PUSH32(esp, edx);
    edx = MEM32(esp + 0x38);
    PUSH32(esp, eax);
    eax = MEM32(esp + 0x38);
    PUSH32(esp, ecx);
    ecx = MEM32(esp + 0x38);
    PUSH32(esp, edx);
    edx = MEM32(esp + 0x38);
    PUSH32(esp, eax);
    PUSH32(esp, ecx);
    PUSH32(esp, edx);
    PUSH32(esp, 0x0021D385u); sub_00214790(); /* call 0x00214790 */

loc_0021D385: ;
    esp = esp + 0x40;
    esp += 64; return; /* ret 60 */

}

/**
 * sub_0021D390
 * Original: 0x0021D390 - 0x0021D5E5 (597 bytes, 143 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0021D390(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    uint64_t mm0, mm1, mm2, mm3, mm4, mm5, mm6, mm7;
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_0021D390: ;
    PUSH32(esp, ebx);
    PUSH32(esp, ebp);
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    edi = MEM32(0x299F10);
    ebp = MEM32(0x299F20);
    ebx = MEM32(0x299F24);
    edx = MEM32(0x299F18);
    ecx = MEM32(0x299F28);
    eax = MEM32(esp + 0x14);
    eax = eax << 3;
    eax = eax + edi;
    MEM32(0x299F10) = eax;
    mm7 = ((uint64_t)MEM32((uint32_t)(0x25a7e8)) | ((uint64_t)MEM32((uint32_t)(0x25a7e8) + 4u) << 32)); /* MMX 0x0021D3C0: movq mm7, qword ptr [0x25a7e8] */
    /* nop */
    edi = edi;

loc_0021D3D0: ;
    mm4 = (uint64_t)(uint32_t)(MEM32((uint32_t)(edx))); /* MMX 0x0021D3D0: movd mm4, dword ptr [edx] */
    mm0 = MMX_PXOR(mm0, mm0); /* MMX 0x0021D3D3: pxor mm0, mm0 */
    eax = 0; /* xor self */
    edx = edx + 4;
    SET_LO8(eax, MEM8(ebp));
    mm4 = MMX_PUNPCKLBW(mm4, mm0); /* MMX 0x0021D3DE: punpcklbw mm4, mm0 */
    mm2 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29b738))); /* MMX 0x0021D3E1: movd mm2, dword ptr [eax*4 + 0x29b738] */
    mm1 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29af38))); /* MMX 0x0021D3E9: movd mm1, dword ptr [eax*4 + 0x29af38] */
    SET_LO8(eax, MEM8(ebp + 1));
    ebp = ebp + 2;
    mm4 = MMX_PSUBUSW(mm4, ((uint64_t)MEM32((uint32_t)(0x25a7d8)) | ((uint64_t)MEM32((uint32_t)(0x25a7d8) + 4u) << 32))); /* MMX 0x0021D3F7: psubusw mm4, qword ptr [0x25a7d8] */
    mm6 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29b738))); /* MMX 0x0021D3FE: movd mm6, dword ptr [eax*4 + 0x29b738] */
    mm1 = MMX_PUNPCKLDQ(mm1, (uint64_t)MEM32((uint32_t)(eax*4 + 0x29af38))); /* MMX 0x0021D406: punpckldq mm1, dword ptr [eax*4 + 0x29af38] */
    SET_LO8(eax, MEM8(ebx));
    mm4 = MMX_PSLLW(mm4, 2u); /* MMX 0x0021D410: psllw mm4, 2 */
    mm4 = MMX_PMULHW(mm4, ((uint64_t)MEM32((uint32_t)(0x25a7e0)) | ((uint64_t)MEM32((uint32_t)(0x25a7e0) + 4u) << 32))); /* MMX 0x0021D414: pmulhw mm4, qword ptr [0x25a7e0] */
    mm5 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29b338))); /* MMX 0x0021D41B: movd mm5, dword ptr [eax*4 + 0x29b338] */
    mm3 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29bb38))); /* MMX 0x0021D423: movd mm3, dword ptr [eax*4 + 0x29bb38] */
    mm2 = MMX_PADDW(mm2, mm5); /* MMX 0x0021D42B: paddw mm2, mm5 */
    SET_LO8(eax, MEM8(ebx + 1));
    ebx = ebx + 2;
    mm5 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29b338))); /* MMX 0x0021D434: movd mm5, dword ptr [eax*4 + 0x29b338] */
    mm3 = MMX_PUNPCKLDQ(mm3, (uint64_t)MEM32((uint32_t)(eax*4 + 0x29bb38))); /* MMX 0x0021D43C: punpckldq mm3, dword ptr [eax*4 + 0x29bb38] */
    mm6 = MMX_PADDW(mm6, mm5); /* MMX 0x0021D444: paddw mm6, mm5 */
    mm2 = MMX_PUNPCKLDQ(mm2, mm6); /* MMX 0x0021D447: punpckldq mm2, mm6 */
    mm1 = MMX_PADDW(mm1, mm4); /* MMX 0x0021D44A: paddw mm1, mm4 */
    eax = MEM32(ecx);
    mm2 = MMX_PADDW(mm2, mm4); /* MMX 0x0021D44F: paddw mm2, mm4 */
    eax = eax & 0x80808080u;
    mm1 = MMX_PADDSW(mm1, mm7); /* MMX 0x0021D457: paddsw mm1, mm7 */
    mm6 = (uint64_t)(uint32_t)(eax); /* MMX 0x0021D45A: movd mm6, eax */
    mm3 = MMX_PADDW(mm3, mm4); /* MMX 0x0021D45D: paddw mm3, mm4 */
    mm0 = MMX_PUNPCKLBW(mm0, mm6); /* MMX 0x0021D460: punpcklbw mm0, mm6 */
    mm1 = MMX_PSUBUSW(mm1, mm7); /* MMX 0x0021D463: psubusw mm1, mm7 */
    mm1 = MMX_PSRLW(mm1, 3u); /* MMX 0x0021D466: psrlw mm1, 3 */
    mm2 = MMX_PADDSW(mm2, mm7); /* MMX 0x0021D46A: paddsw mm2, mm7 */
    mm2 = MMX_PSUBUSW(mm2, mm7); /* MMX 0x0021D46D: psubusw mm2, mm7 */
    mm2 = MMX_PSRLW(mm2, 3u); /* MMX 0x0021D470: psrlw mm2, 3 */
    mm3 = MMX_PADDSW(mm3, mm7); /* MMX 0x0021D474: paddsw mm3, mm7 */
    mm2 = MMX_PSLLW(mm2, 5u); /* MMX 0x0021D477: psllw mm2, 5 */
    mm3 = MMX_PSUBUSW(mm3, mm7); /* MMX 0x0021D47B: psubusw mm3, mm7 */
    mm3 = MMX_PSRLW(mm3, 3u); /* MMX 0x0021D47E: psrlw mm3, 3 */
    mm1 = MMX_POR(mm1, mm2); /* MMX 0x0021D482: por mm1, mm2 */
    mm3 = MMX_PSLLW(mm3, 0xau); /* MMX 0x0021D485: psllw mm3, 0xa */
    mm1 = MMX_POR(mm1, mm0); /* MMX 0x0021D489: por mm1, mm0 */
    mm1 = MMX_POR(mm1, mm3); /* MMX 0x0021D48C: por mm1, mm3 */
    edi = edi + 8;
    eax = MEM32(0x299F10);
    ecx = ecx + 4;
    MEM32((uint32_t)(edi - 8)) = (uint32_t)mm1; MEM32((uint32_t)(edi - 8) + 4u) = (uint32_t)(mm1 >> 32); /* MMX 0x0021D49A: movq qword ptr [edi - 8], mm1 */
    _fa = (uint32_t)(edi) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edi, eax (32-bit) */
    if (CMP_B(_fa, _fb)) goto loc_0021D3D0; /* jb: below (unsigned <) */

loc_0021D4A6: ;
    MEM32(0x299F18) = edx;
    MEM32(0x299F28) = ecx;
    edi = MEM32(0x299F14);
    ebp = MEM32(0x299F20);
    ebx = MEM32(0x299F24);
    edx = MEM32(0x299F1C);
    ecx = MEM32(0x299F2C);
    eax = MEM32(esp + 0x14);
    eax = eax << 3;
    eax = eax + edi;
    MEM32(0x299F14) = eax;
    mm7 = ((uint64_t)MEM32((uint32_t)(0x25a7e8)) | ((uint64_t)MEM32((uint32_t)(0x25a7e8) + 4u) << 32)); /* MMX 0x0021D4DE: movq mm7, qword ptr [0x25a7e8] */
    /* nop */
    /* nop */

loc_0021D4F0: ;
    mm4 = (uint64_t)(uint32_t)(MEM32((uint32_t)(edx))); /* MMX 0x0021D4F0: movd mm4, dword ptr [edx] */
    mm0 = MMX_PXOR(mm0, mm0); /* MMX 0x0021D4F3: pxor mm0, mm0 */
    eax = 0; /* xor self */
    edx = edx + 4;
    SET_LO8(eax, MEM8(ebp));
    mm4 = MMX_PUNPCKLBW(mm4, mm0); /* MMX 0x0021D4FE: punpcklbw mm4, mm0 */
    mm2 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29b738))); /* MMX 0x0021D501: movd mm2, dword ptr [eax*4 + 0x29b738] */
    mm1 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29af38))); /* MMX 0x0021D509: movd mm1, dword ptr [eax*4 + 0x29af38] */
    SET_LO8(eax, MEM8(ebp + 1));
    ebp = ebp + 2;
    mm4 = MMX_PSUBUSW(mm4, ((uint64_t)MEM32((uint32_t)(0x25a7d8)) | ((uint64_t)MEM32((uint32_t)(0x25a7d8) + 4u) << 32))); /* MMX 0x0021D517: psubusw mm4, qword ptr [0x25a7d8] */
    mm6 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29b738))); /* MMX 0x0021D51E: movd mm6, dword ptr [eax*4 + 0x29b738] */
    mm1 = MMX_PUNPCKLDQ(mm1, (uint64_t)MEM32((uint32_t)(eax*4 + 0x29af38))); /* MMX 0x0021D526: punpckldq mm1, dword ptr [eax*4 + 0x29af38] */
    SET_LO8(eax, MEM8(ebx));
    mm4 = MMX_PSLLW(mm4, 2u); /* MMX 0x0021D530: psllw mm4, 2 */
    mm4 = MMX_PMULHW(mm4, ((uint64_t)MEM32((uint32_t)(0x25a7e0)) | ((uint64_t)MEM32((uint32_t)(0x25a7e0) + 4u) << 32))); /* MMX 0x0021D534: pmulhw mm4, qword ptr [0x25a7e0] */
    mm5 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29b338))); /* MMX 0x0021D53B: movd mm5, dword ptr [eax*4 + 0x29b338] */
    mm3 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29bb38))); /* MMX 0x0021D543: movd mm3, dword ptr [eax*4 + 0x29bb38] */
    mm2 = MMX_PADDW(mm2, mm5); /* MMX 0x0021D54B: paddw mm2, mm5 */
    SET_LO8(eax, MEM8(ebx + 1));
    ebx = ebx + 2;
    mm5 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29b338))); /* MMX 0x0021D554: movd mm5, dword ptr [eax*4 + 0x29b338] */
    mm3 = MMX_PUNPCKLDQ(mm3, (uint64_t)MEM32((uint32_t)(eax*4 + 0x29bb38))); /* MMX 0x0021D55C: punpckldq mm3, dword ptr [eax*4 + 0x29bb38] */
    mm6 = MMX_PADDW(mm6, mm5); /* MMX 0x0021D564: paddw mm6, mm5 */
    mm2 = MMX_PUNPCKLDQ(mm2, mm6); /* MMX 0x0021D567: punpckldq mm2, mm6 */
    mm1 = MMX_PADDW(mm1, mm4); /* MMX 0x0021D56A: paddw mm1, mm4 */
    eax = MEM32(ecx);
    mm2 = MMX_PADDW(mm2, mm4); /* MMX 0x0021D56F: paddw mm2, mm4 */
    eax = eax & 0x80808080u;
    mm1 = MMX_PADDSW(mm1, mm7); /* MMX 0x0021D577: paddsw mm1, mm7 */
    mm6 = (uint64_t)(uint32_t)(eax); /* MMX 0x0021D57A: movd mm6, eax */
    mm3 = MMX_PADDW(mm3, mm4); /* MMX 0x0021D57D: paddw mm3, mm4 */
    mm0 = MMX_PUNPCKLBW(mm0, mm6); /* MMX 0x0021D580: punpcklbw mm0, mm6 */
    mm1 = MMX_PSUBUSW(mm1, mm7); /* MMX 0x0021D583: psubusw mm1, mm7 */
    mm1 = MMX_PSRLW(mm1, 3u); /* MMX 0x0021D586: psrlw mm1, 3 */
    mm2 = MMX_PADDSW(mm2, mm7); /* MMX 0x0021D58A: paddsw mm2, mm7 */
    mm2 = MMX_PSUBUSW(mm2, mm7); /* MMX 0x0021D58D: psubusw mm2, mm7 */
    mm2 = MMX_PSRLW(mm2, 3u); /* MMX 0x0021D590: psrlw mm2, 3 */
    mm3 = MMX_PADDSW(mm3, mm7); /* MMX 0x0021D594: paddsw mm3, mm7 */
    mm2 = MMX_PSLLW(mm2, 5u); /* MMX 0x0021D597: psllw mm2, 5 */
    mm3 = MMX_PSUBUSW(mm3, mm7); /* MMX 0x0021D59B: psubusw mm3, mm7 */
    mm3 = MMX_PSRLW(mm3, 3u); /* MMX 0x0021D59E: psrlw mm3, 3 */
    mm1 = MMX_POR(mm1, mm2); /* MMX 0x0021D5A2: por mm1, mm2 */
    mm3 = MMX_PSLLW(mm3, 0xau); /* MMX 0x0021D5A5: psllw mm3, 0xa */
    mm1 = MMX_POR(mm1, mm0); /* MMX 0x0021D5A9: por mm1, mm0 */
    mm1 = MMX_POR(mm1, mm3); /* MMX 0x0021D5AC: por mm1, mm3 */
    edi = edi + 8;
    eax = MEM32(0x299F14);
    ecx = ecx + 4;
    MEM32((uint32_t)(edi - 8)) = (uint32_t)mm1; MEM32((uint32_t)(edi - 8) + 4u) = (uint32_t)(mm1 >> 32); /* MMX 0x0021D5BA: movq qword ptr [edi - 8], mm1 */
    _fa = (uint32_t)(edi) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edi, eax (32-bit) */
    if (CMP_B(_fa, _fb)) goto loc_0021D4F0; /* jb: below (unsigned <) */

loc_0021D5C6: ;
    MEM32(0x299F20) = ebp;
    MEM32(0x299F24) = ebx;
    MEM32(0x299F1C) = edx;
    MEM32(0x299F2C) = ecx;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebp);
    POP32(esp, ebx);
    esp += 8; return; /* ret 4 */

}

/**
 * sub_0021D970
 * Original: 0x0021D970 - 0x0021DA77 (263 bytes, 71 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0021D970(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_0021D970: ;
    edx = MEM32(0x299F18);
    PUSH32(esp, ebx);
    PUSH32(esp, ebp);
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    edi = MEM32(esp + 0x14);
    esi = edi;
    ebx = 8;

loc_0021D985: ;
    ecx = ZX8(MEM8(edx));
    edx = ZX8(MEM8(edx + 1));
    eax = ecx;
    eax = eax << 0x10;
    eax = eax | ecx;
    ecx = edx;
    ecx = ecx << 0x10;
    ecx = ecx | edx;
    edx = MEM32(0x299F10);
    eax = eax | 0x80008000u;
    MEM32(edx) = eax;
    edx = MEM32(0x299F10);
    ecx = ecx | 0x80008000u;
    MEM32(edx + 4) = ecx;
    ebp = MEM32(0x299F10);
    edx = MEM32(0x299F30);
    MEM32(edx + ebp) = eax;
    edx = MEM32(0x299F10);
    eax = MEM32(0x299F30);
    MEM32(eax + edx + 4) = ecx;
    edx = MEM32(0x299F1C);
    ecx = ZX8(MEM8(edx));
    edx = ZX8(MEM8(edx + 1));
    eax = ecx;
    eax = eax << 0x10;
    eax = eax | ecx;
    ecx = edx;
    ecx = ecx << 0x10;
    ecx = ecx | edx;
    edx = MEM32(0x299F14);
    eax = eax | 0x80008000u;
    MEM32(edx) = eax;
    edx = MEM32(0x299F14);
    ecx = ecx | 0x80008000u;
    MEM32(edx + 4) = ecx;
    edx = MEM32(0x299F14);
    ebp = MEM32(0x299F30);
    MEM32(edx + ebp) = eax;
    eax = MEM32(0x299F14);
    edx = MEM32(0x299F30);
    MEM32(eax + edx + 4) = ecx;
    edx = MEM32(0x299F18);
    ecx = MEM32(0x299F1C);
    eax = MEM32(0x299F10);
    ebp = MEM32(0x299F14);
    edx = edx + 2;
    ecx = ecx + 2;
    eax = eax + ebx;
    ebp = ebp + ebx;
    esi = esi - 2;
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(esi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test esi, esi (32-bit) */
    MEM32(0x299F18) = edx;
    MEM32(0x299F1C) = ecx;
    MEM32(0x299F10) = eax;
    MEM32(0x299F14) = ebp;
    if (CMP_G(_fas & _fbs, 0)) goto loc_0021D985; /* jg: greater (signed >) */

loc_0021DA6C: ;
    eax = MEM32(esp + 0x18);
    eax = eax + edi;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebp);
    POP32(esp, ebx);
    esp += 4; return; /* ret */

}

/**
 * sub_0021DA80
 * Original: 0x0021DA80 - 0x0021DAE9 (105 bytes, 32 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0021DA80(void)
{
    int _flags = 0; /* fallback flag var */

loc_0021DA80: ;
    eax = MEM32(esp + 8);
    eax = eax + 0xFFFFFFFEu;
    if (((int32_t)eax < 0)) goto loc_0021DAE8; /* js: sign (negative) */

loc_0021DA89: ;
    PUSH32(esp, esi);
    esi = eax + 2;
    esi = esi >> 1;
    /* nop */

loc_0021DA90: ;
    eax = MEM32(0x299F18);
    eax = ZX8(MEM8(eax));
    edx = MEM32(0x299F10);
    ecx = eax;
    ecx = ecx << 0x10;
    ecx = ecx | eax;
    ecx = ecx | 0x80008000u;
    MEM32(edx) = ecx;
    edx = MEM32(0x299F18);
    ecx = ZX8(MEM8(edx + 1));
    eax = ecx;
    eax = eax << 0x10;
    eax = eax | ecx;
    ecx = MEM32(0x299F10);
    edx = edx + 2;
    eax = eax | 0x80008000u;
    MEM32(0x299F18) = edx;
    MEM32(ecx + 4) = eax;
    ecx = MEM32(0x299F10);
    ecx = ecx + 8;
    esi--;
    MEM32(0x299F10) = ecx;
    if ((esi != 0)) goto loc_0021DA90; /* jne: not equal / not zero */

loc_0021DAE7: ;
    POP32(esp, esi);

loc_0021DAE8: ;
    esp += 4; return; /* ret */

}

/**
 * sub_0021DAF0
 * Original: 0x0021DAF0 - 0x0021DBBB (203 bytes, 58 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0021DAF0(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_0021DAF0: ;
    PUSH32(esp, ebx);
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    edi = MEM32(esp + 0x10);
    esi = edi;
    ebx = 8;
    edi = edi;

loc_0021DB00: ;
    eax = MEM32(0x299F18);
    eax = ZX8(MEM8(eax));
    edx = MEM32(0x299F10);
    ecx = eax;
    ecx = ecx << 0x10;
    ecx = ecx | eax;
    ecx = ecx | 0x80008000u;
    MEM32(edx) = ecx;
    edx = MEM32(0x299F18);
    ecx = ZX8(MEM8(edx + 1));
    eax = ecx;
    eax = eax << 0x10;
    eax = eax | ecx;
    ecx = MEM32(0x299F10);
    eax = eax | 0x80008000u;
    edx = edx + 2;
    MEM32(0x299F18) = edx;
    MEM32(ecx + 4) = eax;
    edx = MEM32(0x299F1C);
    eax = ZX8(MEM8(edx));
    edx = MEM32(0x299F14);
    ecx = eax;
    ecx = ecx << 0x10;
    ecx = ecx | eax;
    ecx = ecx | 0x80008000u;
    MEM32(edx) = ecx;
    edx = MEM32(0x299F1C);
    ecx = ZX8(MEM8(edx + 1));
    eax = ecx;
    eax = eax << 0x10;
    eax = eax | ecx;
    ecx = MEM32(0x299F14);
    edx = edx + 2;
    eax = eax | 0x80008000u;
    MEM32(0x299F1C) = edx;
    MEM32(ecx + 4) = eax;
    eax = MEM32(0x299F10);
    edx = MEM32(0x299F14);
    eax = eax + ebx;
    edx = edx + ebx;
    esi = esi - 2;
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(esi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test esi, esi (32-bit) */
    MEM32(0x299F10) = eax;
    MEM32(0x299F14) = edx;
    if (CMP_G(_fas & _fbs, 0)) goto loc_0021DB00; /* jg: greater (signed >) */

loc_0021DBB0: ;
    edx = MEM32(esp + 0x14);
    eax = edi + edx;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebx);
    esp += 4; return; /* ret */

}

/**
 * sub_0021DBC0
 * Original: 0x0021DBC0 - 0x0021DC1B (91 bytes, 27 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0021DBC0(void)
{
    int _flags = 0; /* fallback flag var */

loc_0021DBC0: ;
    eax = MEM32(esp + 8);
    eax = eax + 0xFFFFFFFEu;
    if (((int32_t)eax < 0)) goto loc_0021DC1A; /* js: sign (negative) */

loc_0021DBC9: ;
    edx = eax + 2;
    edx = edx >> 1;
    PUSH32(esp, esi);
    /* nop */

loc_0021DBD0: ;
    ecx = MEM32(0x299F18);
    eax = ZX8(MEM8(ecx + 1));
    esi = ZX8(MEM8(ecx));
    ecx = ecx + 2;
    eax = eax << 0x10;
    MEM32(0x299F18) = ecx;
    ecx = MEM32(0x299F10);
    eax = eax | esi;
    eax = eax | 0x80008000u;
    MEM32(ecx) = eax;
    ecx = MEM32(0x299F10);
    esi = MEM32(0x299F30);
    MEM32(esi + ecx) = eax;
    ecx = MEM32(0x299F10);
    ecx = ecx + 4;
    edx--;
    MEM32(0x299F10) = ecx;
    if ((edx != 0)) goto loc_0021DBD0; /* jne: not equal / not zero */

loc_0021DC19: ;
    POP32(esp, esi);

loc_0021DC1A: ;
    esp += 4; return; /* ret */

}

/**
 * sub_0021DC20
 * Original: 0x0021DC20 - 0x0021DCCE (174 bytes, 48 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0021DC20(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_0021DC20: ;
    PUSH32(esp, ebx);
    PUSH32(esp, esi);
    esi = MEM32(esp + 0xC);
    PUSH32(esp, edi);
    edx = esi;
    edi = 4;
    edi = edi;

loc_0021DC30: ;
    ecx = MEM32(0x299F18);
    eax = ZX8(MEM8(ecx + 1));
    ebx = ZX8(MEM8(ecx));
    eax = eax << 0x10;
    eax = eax | ebx;
    ecx = ecx + 2;
    MEM32(0x299F18) = ecx;
    ecx = MEM32(0x299F10);
    eax = eax | 0x80008000u;
    MEM32(ecx) = eax;
    ebx = MEM32(0x299F10);
    ecx = MEM32(0x299F30);
    MEM32(ecx + ebx) = eax;
    ecx = MEM32(0x299F1C);
    eax = ZX8(MEM8(ecx + 1));
    ebx = ZX8(MEM8(ecx));
    eax = eax << 0x10;
    eax = eax | ebx;
    ecx = ecx + 2;
    eax = eax | 0x80008000u;
    MEM32(0x299F1C) = ecx;
    ecx = MEM32(0x299F14);
    MEM32(ecx) = eax;
    ecx = MEM32(0x299F14);
    ebx = MEM32(0x299F30);
    MEM32(ecx + ebx) = eax;
    eax = MEM32(0x299F10);
    ebx = MEM32(0x299F14);
    eax = eax + edi;
    ebx = ebx + edi;
    edx = edx - 2;
    _fa = (uint32_t)(edx) & 0xFFFFFFFFu; _fb = (uint32_t)(edx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test edx, edx (32-bit) */
    MEM32(0x299F10) = eax;
    MEM32(0x299F14) = ebx;
    if (CMP_G(_fas & _fbs, 0)) goto loc_0021DC30; /* jg: greater (signed >) */

loc_0021DCC3: ;
    edx = MEM32(esp + 0x14);
    POP32(esp, edi);
    eax = esi + edx;
    POP32(esp, esi);
    POP32(esp, ebx);
    esp += 4; return; /* ret */

}

/**
 * sub_0021DCD0
 * Original: 0x0021DCD0 - 0x0021DD8F (191 bytes, 56 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0021DCD0(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_0021DCD0: ;
    eax = MEM32(esp + 8);
    eax = eax + 0xFFFFFFFEu;
    if (((int32_t)eax < 0)) goto loc_0021DD8E; /* js: sign (negative) */

loc_0021DCDD: ;
    edx = MEM32(0x299F18);
    PUSH32(esp, ebx);
    PUSH32(esp, ebp);
    PUSH32(esp, esi);
    ebp = eax + 2;
    PUSH32(esp, edi);
    ebp = ebp >> 1;
    /* nop */

loc_0021DCF0: ;
    eax = ZX8(MEM8(edx));
    esi = MEM32(0x299F24);
    edi = MEM32(0x299F20);
    ebx = ZX8(MEM8(edi));
    ecx = 0; /* xor self */
    SET_HI8(ecx, MEM8(esi));
    ecx = ecx | eax;
    ecx = ecx << 8;
    ecx = ecx | ebx;
    ecx = ecx << 8;
    ecx = ecx | eax;
    esi++;
    MEM32(0x299F24) = esi;
    edi++;
    MEM32(0x299F20) = edi;
    edx = ZX8(MEM8(edx + 1));
    eax = edx;
    esi = ecx;
    eax = eax << 0x10;
    esi = esi & 0xFF00FF00u;
    eax = eax | esi;
    eax = eax | edx;
    edx = MEM32(0x299F10);
    MEM32(edx) = ecx;
    edx = MEM32(0x299F10);
    MEM32(edx + 4) = eax;
    edx = MEM32(0x299F30);
    esi = MEM32(0x299F10);
    MEM32(edx + esi) = ecx;
    ecx = MEM32(0x299F10);
    edx = MEM32(0x299F30);
    MEM32(edx + ecx + 4) = eax;
    edx = MEM32(0x299F18);
    ecx = MEM32(0x299F10);
    edx = edx + 2;
    ecx = ecx + 8;
    ebp--;
    MEM32(0x299F18) = edx;
    MEM32(0x299F10) = ecx;
    if ((ebp != 0)) goto loc_0021DCF0; /* jne: not equal / not zero */

loc_0021DD8A: ;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebp);
    POP32(esp, ebx);

loc_0021DD8E: ;
    esp += 4; return; /* ret */

}

/**
 * sub_0021DD90
 * Original: 0x0021DD90 - 0x0021DEBF (303 bytes, 85 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0021DD90(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_0021DD90: ;
    edx = MEM32(0x299F18);
    PUSH32(esp, ebx);
    PUSH32(esp, ebp);
    ebp = MEM32(esp + 0xC);
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    edi = edi;

loc_0021DDA0: ;
    eax = ZX8(MEM8(edx));
    esi = MEM32(0x299F24);
    edi = MEM32(0x299F20);
    ebx = ZX8(MEM8(edi));
    ecx = 0; /* xor self */
    SET_HI8(ecx, MEM8(esi));
    ebp = ebp - 2;
    ecx = ecx | eax;
    ecx = ecx << 8;
    ecx = ecx | ebx;
    ecx = ecx << 8;
    ecx = ecx | eax;
    esi++;
    MEM32(0x299F24) = esi;
    edi++;
    MEM32(0x299F20) = edi;
    esi = ZX8(MEM8(edx + 1));
    eax = esi;
    edx = ecx;
    edx = edx & 0xFF00FF00u;
    eax = eax << 0x10;
    eax = eax | edx;
    eax = eax | esi;
    esi = MEM32(0x299F10);
    MEM32(esi) = ecx;
    esi = MEM32(0x299F10);
    MEM32(esi + 4) = eax;
    edi = MEM32(0x299F10);
    esi = MEM32(0x299F30);
    MEM32(esi + edi) = ecx;
    esi = MEM32(0x299F10);
    ecx = MEM32(0x299F30);
    MEM32(ecx + esi + 4) = eax;
    edi = MEM32(0x299F1C);
    esi = ZX8(MEM8(edi));
    ecx = esi;
    ecx = ecx << 0x10;
    ecx = ecx | esi;
    esi = ZX8(MEM8(edi + 1));
    ecx = ecx | edx;
    eax = eax & 0xFF00FF00u;
    edx = esi;
    edx = edx << 0x10;
    edx = edx | eax;
    eax = MEM32(0x299F14);
    MEM32(eax) = ecx;
    eax = MEM32(0x299F14);
    edx = edx | esi;
    MEM32(eax + 4) = edx;
    eax = MEM32(0x299F14);
    esi = MEM32(0x299F30);
    MEM32(eax + esi) = ecx;
    ecx = MEM32(0x299F14);
    eax = MEM32(0x299F30);
    MEM32(ecx + eax + 4) = edx;
    edx = MEM32(0x299F18);
    ebx = MEM32(0x299F1C);
    edi = MEM32(0x299F10);
    esi = MEM32(0x299F14);
    eax = 8;
    edx = edx + 2;
    ebx = ebx + 2;
    edi = edi + eax;
    esi = esi + eax;
    _fa = (uint32_t)(ebp) & 0xFFFFFFFFu; _fb = (uint32_t)(ebp) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ebp, ebp (32-bit) */
    MEM32(0x299F18) = edx;
    MEM32(0x299F1C) = ebx;
    MEM32(0x299F10) = edi;
    MEM32(0x299F14) = esi;
    if (CMP_G(_fas & _fbs, 0)) goto loc_0021DDA0; /* jg: greater (signed >) */

loc_0021DEAF: ;
    ecx = MEM32(esp + 0x18);
    edx = MEM32(esp + 0x14);
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebp);
    eax = edx + ecx;
    POP32(esp, ebx);
    esp += 4; return; /* ret */

}

/**
 * sub_0021DEC0
 * Original: 0x0021DEC0 - 0x0021DF5E (158 bytes, 49 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0021DEC0(void)
{
    int _flags = 0; /* fallback flag var */

loc_0021DEC0: ;
    eax = MEM32(esp + 8);
    eax = eax + 0xFFFFFFFEu;
    if (((int32_t)eax < 0)) goto loc_0021DF5D; /* js: sign (negative) */

loc_0021DECD: ;
    PUSH32(esp, ebx);
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    edi = eax + 2;
    edi = edi >> 1;
    goto loc_0021DEE0;

    /* nop */
    edi = edi;

loc_0021DEE0: ;
    edx = MEM32(0x299F24);
    eax = MEM32(0x299F18);
    eax = ZX8(MEM8(eax));
    esi = MEM32(0x299F20);
    ebx = ZX8(MEM8(esi));
    ecx = 0; /* xor self */
    SET_HI8(ecx, MEM8(edx));
    ecx = ecx | eax;
    ecx = ecx << 8;
    ecx = ecx | ebx;
    ecx = ecx << 8;
    ecx = ecx | eax;
    edx++;
    MEM32(0x299F24) = edx;
    edx = MEM32(0x299F10);
    esi++;
    MEM32(0x299F20) = esi;
    MEM32(edx) = ecx;
    esi = MEM32(0x299F18);
    edx = ZX8(MEM8(esi + 1));
    ecx = ecx & 0xFF00FF00u;
    eax = edx;
    eax = eax << 0x10;
    eax = eax | ecx;
    ecx = MEM32(0x299F10);
    esi = esi + 2;
    eax = eax | edx;
    MEM32(0x299F18) = esi;
    MEM32(ecx + 4) = eax;
    ecx = MEM32(0x299F10);
    ecx = ecx + 8;
    edi--;
    MEM32(0x299F10) = ecx;
    if ((edi != 0)) goto loc_0021DEE0; /* jne: not equal / not zero */

loc_0021DF5A: ;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebx);

loc_0021DF5D: ;
    esp += 4; return; /* ret */

}

/**
 * sub_0021DF60
 * Original: 0x0021DF60 - 0x0021E059 (249 bytes, 73 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0021DF60(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_0021DF60: ;
    PUSH32(esp, ebx);
    PUSH32(esp, ebp);
    ebp = MEM32(esp + 0xC);
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    edi = ebp;
    /* nop */

loc_0021DF70: ;
    edx = MEM32(0x299F24);
    eax = MEM32(0x299F18);
    eax = ZX8(MEM8(eax));
    esi = MEM32(0x299F20);
    ebx = ZX8(MEM8(esi));
    ecx = 0; /* xor self */
    SET_HI8(ecx, MEM8(edx));
    edi = edi - 2;
    ecx = ecx | eax;
    ecx = ecx << 8;
    ecx = ecx | ebx;
    ecx = ecx << 8;
    ecx = ecx | eax;
    edx++;
    MEM32(0x299F24) = edx;
    edx = MEM32(0x299F10);
    esi++;
    MEM32(0x299F20) = esi;
    MEM32(edx) = ecx;
    esi = MEM32(0x299F18);
    edx = ZX8(MEM8(esi + 1));
    ecx = ecx & 0xFF00FF00u;
    eax = edx;
    eax = eax << 0x10;
    eax = eax | ecx;
    ecx = MEM32(0x299F10);
    eax = eax | edx;
    esi = esi + 2;
    MEM32(0x299F18) = esi;
    MEM32(ecx + 4) = eax;
    edx = MEM32(0x299F1C);
    edx = ZX8(MEM8(edx));
    eax = eax & 0xFF00FF00u;
    ecx = edx;
    ecx = ecx << 0x10;
    ecx = ecx | eax;
    eax = MEM32(0x299F14);
    ecx = ecx | edx;
    MEM32(eax) = ecx;
    esi = MEM32(0x299F1C);
    edx = ZX8(MEM8(esi + 1));
    eax = edx;
    eax = eax << 0x10;
    ecx = ecx & 0xFF00FF00u;
    eax = eax | ecx;
    ecx = MEM32(0x299F14);
    eax = eax | edx;
    esi = esi + 2;
    MEM32(0x299F1C) = esi;
    MEM32(ecx + 4) = eax;
    esi = MEM32(0x299F10);
    edx = MEM32(0x299F14);
    eax = 8;
    esi = esi + eax;
    edx = edx + eax;
    _fa = (uint32_t)(edi) & 0xFFFFFFFFu; _fb = (uint32_t)(edi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test edi, edi (32-bit) */
    MEM32(0x299F10) = esi;
    MEM32(0x299F14) = edx;
    if (CMP_G(_fas & _fbs, 0)) goto loc_0021DF70; /* jg: greater (signed >) */

loc_0021E04D: ;
    edx = MEM32(esp + 0x18);
    POP32(esp, edi);
    POP32(esp, esi);
    eax = edx + ebp;
    POP32(esp, ebp);
    POP32(esp, ebx);
    esp += 4; return; /* ret */

}

/**
 * sub_0021E060
 * Original: 0x0021E060 - 0x0021E0DB (123 bytes, 40 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0021E060(void)
{
    int _flags = 0; /* fallback flag var */

loc_0021E060: ;
    eax = MEM32(esp + 8);
    eax = eax + 0xFFFFFFFEu;
    if (((int32_t)eax < 0)) goto loc_0021E0DA; /* js: sign (negative) */

loc_0021E069: ;
    PUSH32(esp, ebx);
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    edi = eax + 2;
    edi = edi >> 1;

loc_0021E071: ;
    edx = MEM32(0x299F24);
    eax = MEM32(0x299F18);
    esi = MEM32(0x299F20);
    ebx = ZX8(MEM8(esi));
    ecx = 0; /* xor self */
    SET_HI8(ecx, MEM8(edx));
    eax = eax + 2;
    SET_LO8(ecx, MEM8(eax + -1));
    ecx = ecx << 8;
    ecx = ecx | ebx;
    ebx = ZX8(MEM8(eax + -2));
    ecx = ecx << 8;
    ecx = ecx | ebx;
    edx++;
    MEM32(0x299F18) = eax;
    eax = MEM32(0x299F10);
    esi++;
    MEM32(0x299F24) = edx;
    MEM32(0x299F20) = esi;
    MEM32(eax) = ecx;
    edx = MEM32(0x299F10);
    eax = MEM32(0x299F30);
    MEM32(eax + edx) = ecx;
    ecx = MEM32(0x299F10);
    ecx = ecx + 4;
    edi--;
    MEM32(0x299F10) = ecx;
    if ((edi != 0)) goto loc_0021E071; /* jne: not equal / not zero */

loc_0021E0D7: ;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebx);

loc_0021E0DA: ;
    esp += 4; return; /* ret */

}

/**
 * sub_0021E0E0
 * Original: 0x0021E0E0 - 0x0021E1B5 (213 bytes, 61 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0021E0E0(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_0021E0E0: ;
    PUSH32(esp, ebx);
    PUSH32(esp, ebp);
    ebp = MEM32(esp + 0xC);
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    edi = ebp;
    /* nop */

loc_0021E0F0: ;
    edx = MEM32(0x299F24);
    eax = MEM32(0x299F18);
    esi = MEM32(0x299F20);
    ebx = ZX8(MEM8(esi));
    ecx = 0; /* xor self */
    SET_HI8(ecx, MEM8(edx));
    eax = eax + 2;
    edi = edi - 2;
    SET_LO8(ecx, MEM8(eax + -1));
    ecx = ecx << 8;
    ecx = ecx | ebx;
    ebx = ZX8(MEM8(eax + -2));
    MEM32(0x299F18) = eax;
    eax = MEM32(0x299F10);
    ecx = ecx << 8;
    ecx = ecx | ebx;
    edx++;
    MEM32(0x299F24) = edx;
    esi++;
    MEM32(0x299F20) = esi;
    MEM32(eax) = ecx;
    eax = MEM32(0x299F10);
    edx = MEM32(0x299F30);
    MEM32(edx + eax) = ecx;
    edx = MEM32(0x299F1C);
    eax = ZX8(MEM8(edx + 1));
    eax = eax << 0x10;
    ecx = ecx & 0xFF00FF00u;
    eax = eax | ecx;
    ecx = ZX8(MEM8(edx));
    edx = edx + 2;
    MEM32(0x299F1C) = edx;
    edx = MEM32(0x299F14);
    eax = eax | ecx;
    MEM32(edx) = eax;
    ecx = MEM32(0x299F14);
    edx = MEM32(0x299F30);
    MEM32(ecx + edx) = eax;
    esi = MEM32(0x299F10);
    edx = MEM32(0x299F14);
    eax = 4;
    esi = esi + eax;
    edx = edx + eax;
    _fa = (uint32_t)(edi) & 0xFFFFFFFFu; _fb = (uint32_t)(edi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test edi, edi (32-bit) */
    MEM32(0x299F10) = esi;
    MEM32(0x299F14) = edx;
    if (CMP_G(_fas & _fbs, 0)) goto loc_0021E0F0; /* jg: greater (signed >) */

loc_0021E1AA: ;
    eax = MEM32(esp + 0x18);
    POP32(esp, edi);
    POP32(esp, esi);
    eax = eax + ebp;
    POP32(esp, ebp);
    POP32(esp, ebx);
    esp += 4; return; /* ret */

}

/**
 * sub_0021E1C0
 * Original: 0x0021E1C0 - 0x0021E20C (76 bytes, 24 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0021E1C0(void)
{
    int _flags = 0; /* fallback flag var */

loc_0021E1C0: ;
    eax = MEM32(esp + 8);
    eax = eax + 0xFFFFFFFEu;
    if (((int32_t)eax < 0)) goto loc_0021E20B; /* js: sign (negative) */

loc_0021E1C9: ;
    edx = eax + 2;
    edx = edx >> 1;
    PUSH32(esp, esi);
    /* nop */

loc_0021E1D0: ;
    ecx = MEM32(0x299F18);
    eax = ZX8(MEM8(ecx + 1));
    esi = ZX8(MEM8(ecx));
    ecx = ecx + 2;
    eax = eax << 0x10;
    MEM32(0x299F18) = ecx;
    ecx = MEM32(0x299F10);
    eax = eax | esi;
    eax = eax | 0x80008000u;
    MEM32(ecx) = eax;
    ecx = MEM32(0x299F10);
    ecx = ecx + 4;
    edx--;
    MEM32(0x299F10) = ecx;
    if ((edx != 0)) goto loc_0021E1D0; /* jne: not equal / not zero */

loc_0021E20A: ;
    POP32(esp, esi);

loc_0021E20B: ;
    esp += 4; return; /* ret */

}

/**
 * sub_0021E210
 * Original: 0x0021E210 - 0x0021E29C (140 bytes, 42 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0021E210(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_0021E210: ;
    PUSH32(esp, ebx);
    PUSH32(esp, esi);
    esi = MEM32(esp + 0xC);
    PUSH32(esp, edi);
    edx = esi;
    edi = 4;
    edi = edi;

loc_0021E220: ;
    ecx = MEM32(0x299F18);
    eax = ZX8(MEM8(ecx + 1));
    ebx = ZX8(MEM8(ecx));
    eax = eax << 0x10;
    eax = eax | ebx;
    ecx = ecx + 2;
    MEM32(0x299F18) = ecx;
    ecx = MEM32(0x299F10);
    eax = eax | 0x80008000u;
    MEM32(ecx) = eax;
    ecx = MEM32(0x299F1C);
    eax = ZX8(MEM8(ecx + 1));
    ebx = ZX8(MEM8(ecx));
    eax = eax << 0x10;
    eax = eax | ebx;
    ecx = ecx + 2;
    eax = eax | 0x80008000u;
    MEM32(0x299F1C) = ecx;
    ecx = MEM32(0x299F14);
    MEM32(ecx) = eax;
    eax = MEM32(0x299F10);
    ebx = MEM32(0x299F14);
    eax = eax + edi;
    ebx = ebx + edi;
    edx = edx - 2;
    _fa = (uint32_t)(edx) & 0xFFFFFFFFu; _fb = (uint32_t)(edx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test edx, edx (32-bit) */
    MEM32(0x299F10) = eax;
    MEM32(0x299F14) = ebx;
    if (CMP_G(_fas & _fbs, 0)) goto loc_0021E220; /* jg: greater (signed >) */

loc_0021E291: ;
    edx = MEM32(esp + 0x14);
    POP32(esp, edi);
    eax = esi + edx;
    POP32(esp, esi);
    POP32(esp, ebx);
    esp += 4; return; /* ret */

}

/**
 * sub_0021E2A0
 * Original: 0x0021E2A0 - 0x0021E30D (109 bytes, 37 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0021E2A0(void)
{
    int _flags = 0; /* fallback flag var */

loc_0021E2A0: ;
    eax = MEM32(esp + 8);
    eax = eax + 0xFFFFFFFEu;
    if (((int32_t)eax < 0)) goto loc_0021E30C; /* js: sign (negative) */

loc_0021E2A9: ;
    PUSH32(esp, ebx);
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    edi = eax + 2;
    edi = edi >> 1;

loc_0021E2B1: ;
    ecx = MEM32(0x299F24);
    eax = MEM32(0x299F18);
    esi = MEM32(0x299F20);
    ebx = ZX8(MEM8(esi));
    edx = 0; /* xor self */
    SET_HI8(edx, MEM8(ecx));
    eax = eax + 2;
    SET_LO8(edx, MEM8(eax + -1));
    edx = edx << 8;
    edx = edx | ebx;
    ebx = ZX8(MEM8(eax + -2));
    edx = edx << 8;
    edx = edx | ebx;
    ecx++;
    esi++;
    MEM32(0x299F18) = eax;
    eax = MEM32(0x299F10);
    MEM32(0x299F24) = ecx;
    MEM32(0x299F20) = esi;
    MEM32(eax) = edx;
    ecx = MEM32(0x299F10);
    ecx = ecx + 4;
    edi--;
    MEM32(0x299F10) = ecx;
    if ((edi != 0)) goto loc_0021E2B1; /* jne: not equal / not zero */

loc_0021E309: ;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebx);

loc_0021E30C: ;
    esp += 4; return; /* ret */

}

/**
 * sub_0021E310
 * Original: 0x0021E310 - 0x0021E3C8 (184 bytes, 55 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0021E310(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_0021E310: ;
    PUSH32(esp, ebx);
    PUSH32(esp, ebp);
    ebp = MEM32(esp + 0xC);
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    edi = ebp;
    /* nop */

loc_0021E320: ;
    edx = MEM32(0x299F24);
    eax = MEM32(0x299F18);
    esi = MEM32(0x299F20);
    ebx = ZX8(MEM8(esi));
    ecx = 0; /* xor self */
    SET_HI8(ecx, MEM8(edx));
    eax = eax + 2;
    edi = edi - 2;
    SET_LO8(ecx, MEM8(eax + -1));
    ecx = ecx << 8;
    ecx = ecx | ebx;
    ebx = ZX8(MEM8(eax + -2));
    ecx = ecx << 8;
    MEM32(0x299F18) = eax;
    eax = MEM32(0x299F10);
    ecx = ecx | ebx;
    edx++;
    MEM32(0x299F24) = edx;
    esi++;
    MEM32(0x299F20) = esi;
    MEM32(eax) = ecx;
    edx = MEM32(0x299F1C);
    eax = ZX8(MEM8(edx + 1));
    eax = eax << 0x10;
    ecx = ecx & 0xFF00FF00u;
    eax = eax | ecx;
    ecx = ZX8(MEM8(edx));
    edx = edx + 2;
    MEM32(0x299F1C) = edx;
    edx = MEM32(0x299F14);
    eax = eax | ecx;
    MEM32(edx) = eax;
    esi = MEM32(0x299F10);
    edx = MEM32(0x299F14);
    eax = 4;
    esi = esi + eax;
    edx = edx + eax;
    _fa = (uint32_t)(edi) & 0xFFFFFFFFu; _fb = (uint32_t)(edi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test edi, edi (32-bit) */
    MEM32(0x299F10) = esi;
    MEM32(0x299F14) = edx;
    if (CMP_G(_fas & _fbs, 0)) goto loc_0021E320; /* jg: greater (signed >) */

loc_0021E3BD: ;
    eax = MEM32(esp + 0x18);
    POP32(esp, edi);
    POP32(esp, esi);
    eax = eax + ebp;
    POP32(esp, ebp);
    POP32(esp, ebx);
    esp += 4; return; /* ret */

}

/**
 * sub_0021E3D0
 * Original: 0x0021E3D0 - 0x0021E44E (126 bytes, 54 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0021E3D0(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_0021E3D0: ;
    edx = MEM32(esp + 4);
    eax = edx;
    PUSH32(esp, ebx);
    ebx = MEM32(esp + 0xC);
    SET_LO8(eax, LO8(eax) & 3);
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(2) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp LO8(eax), 2 (8-bit) */
    PUSH32(esp, esi);
    if (CMP_NE(_fa, _fb)) goto loc_0021E3E6; /* jne: not equal / not zero */

loc_0021E3E2: ;
    ebx++;
    edx = edx & 0xFFFFFFFCu;

loc_0021E3E6: ;
    _fa = (uint32_t)(LO8(ebx)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(ebx), 1 (8-bit) */
    ecx = MEM32(esp + 0x20);
    if (TEST_Z(_fa, _fb)) goto loc_0021E3FC; /* je: equal / zero */

loc_0021E3EF: ;
    _fa = (uint32_t)(LO8(ecx)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(ecx), 1 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0021E3F5; /* je: equal / zero */

loc_0021E3F4: ;
    ecx++;

loc_0021E3F5: ;
    eax = MEM32(esp + 0x28);
    ebx++;
    goto loc_0021E406;

loc_0021E3FC: ;
    _fa = (uint32_t)(LO8(ecx)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(ecx), 1 (8-bit) */
    eax = MEM32(esp + 0x28);
    if (TEST_Z(_fa, _fb)) goto loc_0021E407; /* je: equal / zero */

loc_0021E405: ;
    ecx++;

loc_0021E406: ;
    eax--;

loc_0021E407: ;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), 1 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0021E40C; /* je: equal / zero */

loc_0021E40B: ;
    eax--;

loc_0021E40C: ;
    esi = MEM32(esp + 0x38);
    PUSH32(esp, 0x29C360);
    PUSH32(esp, esi);
    esi = MEM32(esp + 0x44);
    PUSH32(esp, esi);
    esi = MEM32(esp + 0x40);
    PUSH32(esp, esi);
    esi = MEM32(esp + 0x40);
    PUSH32(esp, esi);
    esi = MEM32(esp + 0x40);
    PUSH32(esp, esi);
    PUSH32(esp, eax);
    eax = MEM32(esp + 0x40);
    PUSH32(esp, eax);
    eax = MEM32(esp + 0x38);
    PUSH32(esp, ecx);
    ecx = MEM32(esp + 0x40);
    PUSH32(esp, ecx);
    ecx = MEM32(esp + 0x3C);
    PUSH32(esp, eax);
    PUSH32(esp, ecx);
    PUSH32(esp, ebx);
    PUSH32(esp, 0x0021E446u); sub_00214310(); /* call 0x00214310 */

loc_0021E446: ;
    esp = esp + 0x34;
    POP32(esp, esi);
    POP32(esp, ebx);
    esp += 56; return; /* ret 52 */

}

/**
 * sub_0021E450
 * Original: 0x0021E450 - 0x0021E4AB (91 bytes, 34 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0021E450(void)
{

loc_0021E450: ;
    eax = MEM32(esp + 0x38);
    ecx = MEM32(esp + 0x3C);
    edx = MEM32(esp + 0x34);
    PUSH32(esp, 0x29C360);
    PUSH32(esp, eax);
    eax = MEM32(esp + 0x38);
    PUSH32(esp, ecx);
    ecx = MEM32(esp + 0x38);
    PUSH32(esp, edx);
    edx = MEM32(esp + 0x38);
    PUSH32(esp, eax);
    eax = MEM32(esp + 0x38);
    PUSH32(esp, ecx);
    ecx = MEM32(esp + 0x38);
    PUSH32(esp, edx);
    edx = MEM32(esp + 0x38);
    PUSH32(esp, eax);
    eax = MEM32(esp + 0x38);
    PUSH32(esp, ecx);
    ecx = MEM32(esp + 0x38);
    PUSH32(esp, edx);
    edx = MEM32(esp + 0x38);
    PUSH32(esp, eax);
    eax = MEM32(esp + 0x38);
    PUSH32(esp, ecx);
    ecx = MEM32(esp + 0x38);
    PUSH32(esp, edx);
    edx = MEM32(esp + 0x38);
    PUSH32(esp, eax);
    PUSH32(esp, ecx);
    PUSH32(esp, edx);
    PUSH32(esp, 0x0021E4A5u); sub_00214790(); /* call 0x00214790 */

loc_0021E4A5: ;
    esp = esp + 0x40;
    esp += 64; return; /* ret 60 */

}

/**
 * sub_0021E4B0
 * Original: 0x0021E4B0 - 0x0021E58C (220 bytes, 60 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0021E4B0(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    uint64_t mm1, mm2, mm6, mm7;
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_0021E4B0: ;
    PUSH32(esp, ebx);
    PUSH32(esp, ebp);
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    edi = MEM32(0x299F10);
    ebp = MEM32(0x299F20);
    ebx = MEM32(0x299F24);
    edx = MEM32(0x299F18);
    ecx = MEM32(esp + 0x14);
    ecx = edi + ecx * 8 + -16;
    /* nop */
    eax = eax + 0;

loc_0021E4E0: ;
    mm1 = (uint64_t)(uint32_t)(MEM32((uint32_t)(ebp))); /* MMX 0x0021E4E0: movd mm1, dword ptr [ebp] */
    mm2 = (uint64_t)(uint32_t)(MEM32((uint32_t)(ebx))); /* MMX 0x0021E4E4: movd mm2, dword ptr [ebx] */
    mm6 = ((uint64_t)MEM32((uint32_t)(edx)) | ((uint64_t)MEM32((uint32_t)(edx) + 4u) << 32)); /* MMX 0x0021E4E7: movq mm6, qword ptr [edx] */
    mm1 = MMX_PUNPCKLBW(mm1, mm2); /* MMX 0x0021E4EA: punpcklbw mm1, mm2 */
    mm7 = mm6; /* MMX 0x0021E4ED: movq mm7, mm6 */
    mm6 = MMX_PUNPCKLBW(mm6, mm1); /* MMX 0x0021E4F0: punpcklbw mm6, mm1 */
    ebp = ebp + 4;
    ebx = ebx + 4;
    MEM32((uint32_t)(edi)) = (uint32_t)mm6; MEM32((uint32_t)(edi) + 4u) = (uint32_t)(mm6 >> 32); /* MMX 0x0021E4F9: movq qword ptr [edi], mm6 */
    mm7 = MMX_PUNPCKHBW(mm7, mm1); /* MMX 0x0021E4FC: punpckhbw mm7, mm1 */
    edx = edx + 8;
    _fa = (uint32_t)(edi) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edi, ecx (32-bit) */
    MEM32((uint32_t)(edi + 8)) = (uint32_t)mm7; MEM32((uint32_t)(edi + 8) + 4u) = (uint32_t)(mm7 >> 32); /* MMX 0x0021E504: movq qword ptr [edi + 8], mm7 */
    edi = edi + 0x10;
    if (CMP_B(_fa, _fb)) goto loc_0021E4E0; /* jb: below (unsigned <) */

loc_0021E50D: ;
    MEM32(0x299F10) = edi;
    MEM32(0x299F18) = edx;
    edi = MEM32(0x299F14);
    ebp = MEM32(0x299F20);
    ebx = MEM32(0x299F24);
    edx = MEM32(0x299F1C);
    ecx = MEM32(esp + 0x14);
    ecx = edi + ecx * 8 + -16;
    /* nop */

loc_0021E540: ;
    mm1 = (uint64_t)(uint32_t)(MEM32((uint32_t)(ebp))); /* MMX 0x0021E540: movd mm1, dword ptr [ebp] */
    mm2 = (uint64_t)(uint32_t)(MEM32((uint32_t)(ebx))); /* MMX 0x0021E544: movd mm2, dword ptr [ebx] */
    mm6 = ((uint64_t)MEM32((uint32_t)(edx)) | ((uint64_t)MEM32((uint32_t)(edx) + 4u) << 32)); /* MMX 0x0021E547: movq mm6, qword ptr [edx] */
    mm1 = MMX_PUNPCKLBW(mm1, mm2); /* MMX 0x0021E54A: punpcklbw mm1, mm2 */
    mm7 = mm6; /* MMX 0x0021E54D: movq mm7, mm6 */
    mm6 = MMX_PUNPCKLBW(mm6, mm1); /* MMX 0x0021E550: punpcklbw mm6, mm1 */
    ebp = ebp + 4;
    ebx = ebx + 4;
    MEM32((uint32_t)(edi)) = (uint32_t)mm6; MEM32((uint32_t)(edi) + 4u) = (uint32_t)(mm6 >> 32); /* MMX 0x0021E559: movq qword ptr [edi], mm6 */
    mm7 = MMX_PUNPCKHBW(mm7, mm1); /* MMX 0x0021E55C: punpckhbw mm7, mm1 */
    edx = edx + 8;
    _fa = (uint32_t)(edi) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edi, ecx (32-bit) */
    MEM32((uint32_t)(edi + 8)) = (uint32_t)mm7; MEM32((uint32_t)(edi + 8) + 4u) = (uint32_t)(mm7 >> 32); /* MMX 0x0021E564: movq qword ptr [edi + 8], mm7 */
    edi = edi + 0x10;
    if (CMP_B(_fa, _fb)) goto loc_0021E540; /* jb: below (unsigned <) */

loc_0021E56D: ;
    MEM32(0x299F14) = edi;
    MEM32(0x299F20) = ebp;
    MEM32(0x299F24) = ebx;
    MEM32(0x299F1C) = edx;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebp);
    POP32(esp, ebx);
    esp += 8; return; /* ret 4 */

}

/**
 * sub_0021FB47
 * Original: 0x0021FB47 - 0x0021FBF7 (176 bytes, 61 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0021FB47(void)
{
    uint32_t ebp;
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_0021FB47: ;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, ebp);
    ebp = esp;
    g_ebp = ebp; /* publish frame for frameless callees */
    PUSH32(esp, ecx);
    PUSH32(esp, ecx);
    PUSH32(esp, ebx);
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    esi = ecx;
    ebx = MEM32(esi);
    PUSH32(esp, 0);
    eax = esi + 0x478;
    PUSH32(esp, eax);
    { uint32_t _icall_target = MEM32(0x225B38); PUSH32(esp, 0x0021FB62u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_0021FB62: ;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, esi);
    PUSH32(esp, 0x222A72);
    eax = esi + 0x4A0;
    PUSH32(esp, eax);
    { uint32_t _icall_target = MEM32(0x225B3C); PUSH32(esp, 0x0021FB75u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_0021FB75: ;
    MEM8(esi + 0x460) = 4;
    eax = MEM32(ebx + 0x50);
    MEM32(ebp + -8) = eax;
    MEM16(ebp + -8) = MEM16(ebp + -8) & 0;
    eax = MEM32(ebp + -8);
    ecx = 0; /* xor self */
    MEM32(ebx + 0x50) = eax;
    eax = 0; /* xor self */
    edx = 0; /* xor self */
    edi = ebp + -4;
    ecx++;
    _fa = (uint32_t)(MEM8(esi + 0x460)) & 0xFFu; _fb = (uint32_t)(LO8(edx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(esi + 0x460), LO8(edx) (8-bit) */
    MEM32(edi) = eax; edi += 4; /* stosd */
    if (CMP_BE(_fa, _fb)) goto loc_0021FBD1; /* jbe: below or equal (unsigned <=) */

loc_0021FBA0: ;
    eax = ebx + 0x54;

loc_0021FBA3: ;
    edi = MEM32(eax);
    MEM32(ebp + -8) = edi;
    _fa = (uint32_t)(MEM8(ebp + -8)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(ebp + -8), 1 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0021FBB6; /* je: equal / zero */

loc_0021FBAE: ;
    MEM16(ebp + -2) = MEM16(ebp + -2) | LO16(ecx);
    MEM16(ebp + -4) = MEM16(ebp + -4) | LO16(ecx);

loc_0021FBB6: ;
    MEM16(ebp + -8) = MEM16(ebp + -8) & 0;
    edi = MEM32(ebp + -8);
    MEM32(eax) = edi;
    edi = ZX8(MEM8(esi + 0x460));
    edx++;
    eax = eax + 4;
    ecx = ecx << 1;
    _fa = (uint32_t)(edx) & 0xFFFFFFFFu; _fb = (uint32_t)(edi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edx, edi (32-bit) */
    if (CMP_B(_fa, _fb)) goto loc_0021FBA3; /* jb: below (unsigned <) */

loc_0021FBD1: ;
    MEM32(ebx + 0x10) = 0x40;
    { uint32_t _icall_esp = g_esp;
    { uint32_t _icall_target = MEM32(0x225B30); PUSH32(esp, 0x0021FBDEu); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_0021FBDE: ;
    edx = ebp + -4;
    ecx = esi;
    SET_LO8(ebx, LO8(eax));
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x0021FBEAu); sub_00222979(); /* call 0x00222979 */

loc_0021FBEA: ;
    SET_LO8(ecx, LO8(ebx));
    { uint32_t _icall_esp = g_esp;
    { uint32_t _icall_target = MEM32(0x225B2C); PUSH32(esp, 0x0021FBF2u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_0021FBF2: ;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebx);
    esp = ebp;
    POP32(esp, ebp); /* leave */
    esp += 4; return; /* ret */

}

/**
 * sub_0021FBF7
 * Original: 0x0021FBF7 - 0x0021FC03 (12 bytes, 3 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0021FBF7(void)
{

loc_0021FBF7: ;
    ecx = MEM32(esp + 4);
    PUSH32(esp, 0x0021FC00u); sub_0022044F(); /* call 0x0022044F */

loc_0021FC00: ;
    esp += 8; return; /* ret 4 */

}

/**
 * sub_0021FC03
 * Original: 0x0021FC03 - 0x0021FC45 (66 bytes, 20 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0021FC03(void)
{
    uint32_t ebp;
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_0021FC03: ;
    PUSH32(esp, ebp);
    ebp = esp;
    g_ebp = ebp; /* publish frame for frameless callees */
    esp = esp - 0x28;
    eax = MEM32(0x225AA8);
    _fa = (uint32_t)(MEM8(eax + 5)) & 0xFFu; _fb = (uint32_t)(0xA1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(eax + 5), 0xA1 (8-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_0021FC43; /* je: equal / zero */

loc_0021FC14: ;
    eax = ebp + -4;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, eax);
    PUSH32(esp, 1);
    MEM8(ebp + -24) = 3;
    MEM32(ebp + -16) = 0x1000;
    MEM32(ebp + -20) = 0xFED00000u;
    { uint32_t _icall_target = MEM32(0x225B74); PUSH32(esp, 0x0021FC32u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_0021FC32: ;
    MEM32(ebp + -12) = eax;
    PUSH32(esp, 0x4E0);
    eax = ebp + -40;
    PUSH32(esp, eax);
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x0021FC43u); sub_0021FE39(); /* call 0x0021FE39 */

loc_0021FC43: ;
    esp = ebp;
    POP32(esp, ebp); /* leave */
    esp += 4; return; /* ret */

}

/**
 * sub_0021FC45
 * Original: 0x0021FC45 - 0x0021FDC0 (379 bytes, 114 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0021FC45(void)
{
    uint32_t ebp;
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_0021FC45: ;
    PUSH32(esp, ebp);
    ebp = esp;
    g_ebp = ebp; /* publish frame for frameless callees */
    PUSH32(esp, ecx);
    MEM8(ebp + 0xC) = MEM8(ebp + 0xC) - 1;
    eax = MEM32(ebp + 0x10);
    PUSH32(esp, ebx);
    PUSH32(esp, esi);
    esi = MEM32(ebp + 8);
    PUSH32(esp, edi);
    edi = ZX8(MEM8(ebp + 0xC));
    MEM32(esi + 0x45C) = edi;
    ecx = MEM32(eax + 0x18);
    MEM32(esi + 4) = ecx;
    eax = MEM32(eax + 0x14);
    PUSH32(esp, esi);
    MEM32(ebp + -4) = edi;
    MEM32(esi) = eax;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x0021FC73u); sub_00220675(); /* call 0x00220675 */

loc_0021FC73: ;
    PUSH32(esp, esi);
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x0021FC79u); sub_00220680(); /* call 0x00220680 */

loc_0021FC79: ;
    ebx = MEM32(esi);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, esi);
    PUSH32(esp, 0x224CAA);
    eax = esi + 0x440;
    MEM32(ebx + 0x48) = 0x1200;
    MEM32(ebx + 0x4C) = 0;
    MEM32(ebx + 0x50) = 0x80000000u;
    PUSH32(esp, eax);
    { uint32_t _icall_target = MEM32(0x225B3C); PUSH32(esp, 0x0021FCA3u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_0021FCA3: ;
    eax = MEM32(edi * 4 + 0x287884);
    MEM32(esi + 8) = eax;
    eax = MEM32(ebx + 8);
    MEM32(ebp + 8) = eax;
    { uint32_t _icall_esp = g_esp;
    { uint32_t _icall_target = MEM32(0x225B30); PUSH32(esp, 0x0021FCB9u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_0021FCB9: ;
    MEM8(ebp + 0xF) = LO8(eax);
    eax = MEM32(ebp + 8);
    eax = eax | 1;
    MEM32(ebx + 8) = eax;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 0xA);
    { uint32_t _icall_target = MEM32(0x225B84); PUSH32(esp, 0x0021FCCDu); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_0021FCCD: ;
    ecx = esi;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x0021FCD4u); sub_00220614(); /* call 0x00220614 */

loc_0021FCD4: ;
    MEM32(ebx + 4) = 0xBE;
    eax = MEM32(ebx + 0x34);
    eax = eax & 0xA772EED8u;
    eax = eax | 0x27722ED8;
    ecx = eax;
    ecx = ~ecx;
    ecx = ecx ^ eax;
    ecx = ecx & 0x7FFFFFFF;
    eax = ~eax;
    ecx = ecx ^ eax;
    MEM32(ebx + 0x34) = ecx;
    eax = MEM32(0x225AA8);
    _fa = (uint32_t)(MEM8(eax)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(eax), 1 (8-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_0021FD48; /* jne: not equal / not zero */

loc_0021FD05: ;
    MEM32(ebp + 8) = 2;

loc_0021FD0C: ;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x0021FD11u); sub_00222B5C(); /* call 0x00222B5C */

loc_0021FD11: ;
    edx = eax;
    eax = 0; /* xor self */
    PUSH32(esp, 0xC);
    POP32(esp, ecx);
    edi = edx;
    { uint32_t _i; for (_i = 0; _i < ecx; _i++) MEM32(edi + _i*4) = eax; }
    edi += ecx * 4; ecx = 0; /* rep stosd */
    eax = edx;
    eax = eax - MEM32(0x287880);
    ecx = esi;
    MEM32(edx + 0x14) = eax;
    eax = MEM32(edx);
    eax = eax & 0xF808FFFFu;
    eax = eax | 0x80000;
    MEM8(edx + 0x11) = 0;
    MEM32(edx) = eax;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x0021FD40u); sub_00224167(); /* call 0x00224167 */

loc_0021FD40: ;
    MEM32(ebp + 8) = MEM32(ebp + 8) - 1;
    if ((MEM32(ebp + 8) != 0)) goto loc_0021FD0C; /* jne: not equal / not zero */

loc_0021FD45: ;
    edi = MEM32(ebp + -4);

loc_0021FD48: ;
    SET_LO8(ecx, MEM8(ebp + 0xF));
    { uint32_t _icall_esp = g_esp;
    { uint32_t _icall_target = MEM32(0x225B2C); PUSH32(esp, 0x0021FD51u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_0021FD51: ;
    edi = (uint32_t)((int32_t)edi * (int32_t)0x70);
    eax = MEM32(ebp + 0x10);
    ecx = 0; /* xor self */
    SET_LO8(ecx, MEM8(eax + 0x24));
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 0);
    PUSH32(esp, 0);
    edi = edi + 0x2878C0;
    PUSH32(esp, ecx);
    PUSH32(esp, MEM32(eax + 0x1C));
    PUSH32(esp, esi);
    PUSH32(esp, 0x2245D6);
    PUSH32(esp, edi);
    { uint32_t _icall_target = MEM32(0x225B80); PUSH32(esp, 0x0021FD77u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_0021FD77: ;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, edi);
    { uint32_t _icall_target = MEM32(0x225B7C); PUSH32(esp, 0x0021FD7Eu); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_0021FD7E: ;
    edx = 0; /* xor self */
    edx++;
    ecx = esi + 0x4C0;
    eax = esi + 0x4C8;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, edx);
    PUSH32(esp, ecx);
    MEM32(ecx) = 0x222E86;
    MEM32(esi + 0x4C4) = edx;
    MEM32(esi + 0x4CC) = eax;
    MEM32(eax) = eax;
    { uint32_t _icall_target = MEM32(0x225AAC); PUSH32(esp, 0x0021FDA9u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_0021FDA9: ;
    ecx = esi;
    MEM32(ebx + 0x10) = 0x80000033u;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x0021FDB7u); sub_0021FB47(); /* call 0x0021FB47 */

loc_0021FDB7: ;
    POP32(esp, edi);
    POP32(esp, esi);
    eax = 0; /* xor self */
    POP32(esp, ebx);
    esp = ebp;
    POP32(esp, ebp); /* leave */
    esp += 16; return; /* ret 12 */

}

/**
 * sub_0021FDC0
 * Original: 0x0021FDC0 - 0x0021FE39 (121 bytes, 41 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0021FDC0(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_0021FDC0: ;
    PUSH32(esp, ebp);
    ebp = esp + -112;
    esp = esp - 0xB4;
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    PUSH32(esp, MEM32(ebp + 0x7C));
    ecx = ebp + -68;
    PUSH32(esp, MEM32(ebp + 0x78));
    PUSH32(esp, 0x0021FDDBu); sub_0022314A(); /* call 0x0022314A */

loc_0021FDDB: ;
    eax = 0x21F914;
    esi = 0x21F920;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(esi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, esi (32-bit) */
    edi = eax;
    if (CMP_AE(_fa, _fb)) goto loc_0021FDFF; /* jae: above or equal (unsigned >=) */

loc_0021FDEB: ;
    eax = MEM32(edi);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0021FDF8; /* je: equal / zero */

loc_0021FDF1: ;
    ecx = ebp + -68;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, ecx);
    { uint32_t _icall_target = MEM32(eax + 4); PUSH32(esp, 0x0021FDF8u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_0021FDF8: ;
    edi = edi + 4;
    _fa = (uint32_t)(edi) & 0xFFFFFFFFu; _fb = (uint32_t)(esi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edi, esi (32-bit) */
    if (CMP_B(_fa, _fb)) goto loc_0021FDEB; /* jb: below (unsigned <) */

loc_0021FDFF: ;
    ecx = ebp + -68;
    PUSH32(esp, 0x0021FE07u); sub_00220306(); /* call 0x00220306 */

loc_0021FE07: ;
    eax = ebp + 0x60;
    PUSH32(esp, eax);
    PUSH32(esp, 0x0021FE10u); sub_0021FBF7(); /* call 0x0021FBF7 */

loc_0021FE10: ;
    eax = ZX8(MEM8(ebp + 0x5D));
    PUSH32(esp, eax);
    eax = ZX8(MEM8(ebp + 0x5C));
    PUSH32(esp, eax);
    ecx = 0x286B80;
    PUSH32(esp, 0x0021FE24u); sub_0021FA38(); /* call 0x0021FA38 */

loc_0021FE24: ;
    MEM8(0x286D2C) = 0;
    PUSH32(esp, 0x0021FE30u); sub_0021FC03(); /* call 0x0021FC03 */

loc_0021FE30: ;
    POP32(esp, edi);
    POP32(esp, esi);
    ebp = ebp + 0x70;
    esp = ebp;
    POP32(esp, ebp); /* leave */
    esp += 12; return; /* ret 8 */

}

/**
 * sub_0021FE39
 * Original: 0x0021FE39 - 0x0021FEB6 (125 bytes, 45 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0021FE39(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_0021FE39: ;
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    edi = MEM32(esp + 0x10);
    PUSH32(esp, 0x44425355);
    edi = edi + 0x18;
    PUSH32(esp, edi);
    PUSH32(esp, 0x0021FE4Du); sub_0022175B(); /* call 0x0022175B */

loc_0021FE4D: ;
    esi = eax;
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(esi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test esi, esi (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0021FEB1; /* je: equal / zero */

loc_0021FE53: ;
    ecx = edi;
    edx = ecx;
    ecx = ecx >> 2;
    eax = 0; /* xor self */
    edi = esi;
    { uint32_t _i; for (_i = 0; _i < ecx; _i++) MEM32(edi + _i*4) = eax; }
    edi += ecx * 4; ecx = 0; /* rep stosd */
    ecx = edx;
    ecx = ecx & 3;
    memset((void*)XBOX_PTR(edi), (uint8_t)eax, ecx);
    edi += ecx; ecx = 0; /* rep stosb */
    MEM8(0x286D2C) = MEM8(0x286D2C) + 1;
    eax = ZX8(MEM8(0x286D2C));
    ecx = 0x286B80;
    MEM32(esi) = eax;
    PUSH32(esp, 0x0021FE80u); sub_002206F4(); /* call 0x002206F4 */

loc_0021FE80: ;
    PUSH32(esp, MEM32(esp + 0xC));
    ecx = esi + 4;
    MEM32(ecx) = eax;
    MEM8(eax) = 0;
    eax = MEM32(ecx);
    MEM8(eax + 2) = 0x80;
    eax = MEM32(ecx);
    MEM8(eax + 1) = 0x80;
    eax = MEM32(ecx);
    MEM8(eax + 3) = 0x80;
    eax = MEM32(ecx);
    MEM32(eax + 0xC) = esi;
    eax = 0; /* xor self */
    SET_LO8(eax, MEM8(esi));
    esi = esi + 0x18;
    PUSH32(esp, eax);
    PUSH32(esp, esi);
    PUSH32(esp, 0x0021FEB1u); sub_0021FC45(); /* call 0x0021FC45 */

loc_0021FEB1: ;
    POP32(esp, edi);
    POP32(esp, esi);
    esp += 12; return; /* ret 8 */

}

/**
 * sub_0021FEB6
 * Original: 0x0021FEB6 - 0x002200C1 (523 bytes, 165 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0021FEB6(void)
{
    uint32_t ebp;
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_0021FEB6: ;
    PUSH32(esp, ebp);
    ebp = esp;
    g_ebp = ebp; /* publish frame for frameless callees */
    esp = esp - 0x60;
    PUSH32(esp, esi);
    esi = 0; /* xor self */
    _fa = (uint32_t)(MEM32(0x21FA34)) & 0xFFFFFFFFu; _fb = (uint32_t)(esi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(0x21FA34), esi (32-bit) */
    MEM32(ebp + -8) = esi;
    MEM32(ebp + -4) = esi;
    MEM32(ebp + -12) = esi;
    if (CMP_NE(_fa, _fb)) goto loc_002200BC; /* jne: not equal / not zero */

loc_0021FED4: ;
    ecx = MEM32(ebp + 8);
    PUSH32(esp, ebx);
    PUSH32(esp, edi);
    MEM32(0x21FA34) = 1;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x0021FEE8u); sub_002200F8(); /* call 0x002200F8 */

loc_0021FEE8: ;
    MEM32(ebp + -16) = eax;
    eax = 0x21F904;
    ebx = 0x21F90C;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(ebx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, ebx (32-bit) */
    edi = eax;
    if (CMP_AE(_fa, _fb)) goto loc_0021FF6F; /* jae: above or equal (unsigned >=) */

loc_0021FEFB: ;
    eax = MEM32(edi);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0021FF48; /* je: equal / zero */

loc_0021FF01: ;
    eax = MEM32(eax + 4);
    MEM32(ebp + esi * 4 + -96) = eax;
    esi++;
    _fa = (uint32_t)(MEM32(ebp + -16)) & 0xFFFFFFFFu; _fb = (uint32_t)(0) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(ebp + -16), 0 (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_0021FF1D; /* jne: not equal / not zero */

loc_0021FF0F: ;
    ecx = MEM32(ebp + 8);
    PUSH32(esp, eax);
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x0021FF18u); sub_002200C1(); /* call 0x002200C1 */

loc_0021FF18: ;
    ecx = MEM32(edi);
    MEM8(ecx + 1) = LO8(eax);

loc_0021FF1D: ;
    eax = MEM32(edi);
    eax = MEM32(eax + 0x14);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0021FF28; /* je: equal / zero */

loc_0021FF26: ;
    { uint32_t _icall_esp = g_esp;
    { uint32_t _icall_target = eax; PUSH32(esp, 0x0021FF28u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_0021FF28: ;
    eax = MEM32(edi);
    ecx = MEM32(eax + 0x28);
    _fa = (uint32_t)(LO8(ecx)) & 0xFFu; _fb = (uint32_t)(4) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(ecx), 4 (8-bit) */
    eax = ZX8(MEM8(eax + 1));
    if (TEST_Z(_fa, _fb)) goto loc_0021FF3B; /* je: equal / zero */

loc_0021FF36: ;
    MEM32(ebp + -4) = MEM32(ebp + -4) + eax;
    goto loc_0021FF48;

loc_0021FF3B: ;
    _fa = (uint32_t)(LO8(ecx)) & 0xFFu; _fb = (uint32_t)(8) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(ecx), 8 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0021FF45; /* je: equal / zero */

loc_0021FF40: ;
    MEM32(ebp + -12) = MEM32(ebp + -12) + eax;
    goto loc_0021FF48;

loc_0021FF45: ;
    MEM32(ebp + -8) = MEM32(ebp + -8) + eax;

loc_0021FF48: ;
    edi = edi + 4;
    _fa = (uint32_t)(edi) & 0xFFFFFFFFu; _fb = (uint32_t)(ebx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edi, ebx (32-bit) */
    if (CMP_B(_fa, _fb)) goto loc_0021FEFB; /* jb: below (unsigned <) */

loc_0021FF4F: ;
    _fa = (uint32_t)(MEM32(ebp + -12)) & 0xFFFFFFFFu; _fb = (uint32_t)(0) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(ebp + -12), 0 (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_0021FF60; /* je: equal / zero */

loc_0021FF55: ;
    MEM16(0x286D30) = 0xC;
    goto loc_0021FF78;

loc_0021FF60: ;
    _fa = (uint32_t)(MEM32(ebp + -4)) & 0xFFFFFFFFu; _fb = (uint32_t)(0) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(ebp + -4), 0 (32-bit) */
    MEM16(0x286D30) = 8;
    if (CMP_NE(_fa, _fb)) goto loc_0021FF78; /* jne: not equal / not zero */

loc_0021FF6F: ;
    MEM16(0x286D30) = 4;

loc_0021FF78: ;
    PUSH32(esp, 4);
    POP32(esp, eax);
    _fa = (uint32_t)(MEM32(ebp + -8)) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(ebp + -8), eax (32-bit) */
    if (CMP_BE(_fa, _fb)) goto loc_0021FF83; /* jbe: below or equal (unsigned <=) */

loc_0021FF80: ;
    MEM32(ebp + -8) = eax;

loc_0021FF83: ;
    _fa = (uint32_t)(MEM32(ebp + -4)) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(ebp + -4), eax (32-bit) */
    if (CMP_BE(_fa, _fb)) goto loc_0021FF8B; /* jbe: below or equal (unsigned <=) */

loc_0021FF88: ;
    MEM32(ebp + -4) = eax;

loc_0021FF8B: ;
    ecx = MEM32(ebp + -12);
    eax = MEM32(ebp + -4);
    eax = eax + ecx;
    PUSH32(esp, 8);
    POP32(esp, ecx);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, ecx (32-bit) */
    MEM32(ebp + -16) = eax;
    if (CMP_BE(_fa, _fb)) goto loc_0021FFA0; /* jbe: below or equal (unsigned <=) */

loc_0021FF9D: ;
    MEM32(ebp + -16) = ecx;

loc_0021FFA0: ;
    eax = MEM32(ebp + -16);
    eax = eax + MEM32(ebp + -8);
    ecx = ZX16(MEM16(0x286D30));
    MEM32(ebp + -16) = eax;
    ecx = (uint32_t)((int32_t)ecx * (int32_t)0x16);
    eax = (uint32_t)((int32_t)eax * (int32_t)0xAB);
    ebx = esi;
    ebx = ebx << 2;
    ecx = ecx + ebx;
    eax = eax + ecx;
    PUSH32(esp, 0x5F444958);
    PUSH32(esp, eax);
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x0021FFCDu); sub_0022175B(); /* call 0x0022175B */

loc_0021FFCD: ;
    ecx = ebx;
    edx = ecx;
    ecx = ecx >> 2;
    MEM32(0x21FA08) = esi;
    MEM32(0x21FA20) = esi;
    MEM32(0x21FA0C) = eax;
    MEM32(0x21FA24) = eax;
    edi = eax;
    esi = ebp + -96;
    memcpy((void*)XBOX_PTR(edi), (void*)XBOX_PTR(esi), ecx * 4);
    esi += ecx * 4; edi += ecx * 4; ecx = 0; /* rep movsd */
    ecx = edx;
    edx = MEM32(ebp + -16);
    ecx = ecx & 3;
    memcpy((void*)XBOX_PTR(edi), (void*)XBOX_PTR(esi), ecx);
    esi += ecx; edi += ecx; ecx = 0; /* rep movsb */
    edi = 0; /* xor self */
    ecx = 0; /* xor self */
    eax = eax + ebx;
    _fa = (uint32_t)(edx) & 0xFFFFFFFFu; _fb = (uint32_t)(edi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edx, edi (32-bit) */
    MEM32(0x286D38) = ecx;
    if (CMP_BE(_fa, _fb)) goto loc_00220021; /* jbe: below or equal (unsigned <=) */

loc_0022000B: ;
    MEM32(eax + 0xA7) = ecx;
    ecx = eax;
    eax = eax + 0xAB;
    edx--;
    if ((edx != 0)) goto loc_0022000B; /* jne: not equal / not zero */

loc_0022001B: ;
    MEM32(0x286D38) = ecx;

loc_00220021: ;
    edx = 0; /* xor self */
    _fa = (uint32_t)(MEM16(0x286D30)) & 0xFFFFu; _fb = (uint32_t)(LO16(edi)) & 0xFFFFu;
    _fas = (int32_t)(int16_t)(_fa); _fbs = (int32_t)(int16_t)(_fb); /* cmp MEM16(0x286D30), LO16(edi) (16-bit) */
    MEM32(0x286D34) = eax;
    MEM16(0x286D32) = LO16(edi);
    if (CMP_BE(_fa, _fb)) goto loc_00220055; /* jbe: below or equal (unsigned <=) */

loc_00220038: ;
    ecx = 0; /* xor self */

loc_0022003A: ;
    eax = MEM32(0x286D34);
    eax = ecx + eax + 4;
    MEM8(eax) = MEM8(eax) & 0xFE;
    eax = ZX16(MEM16(0x286D30));
    edx++;
    ecx = ecx + 0x16;
    _fa = (uint32_t)(edx) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edx, eax (32-bit) */
    if (CMP_B(_fa, _fb)) goto loc_0022003A; /* jb: below (unsigned <) */

loc_00220055: ;
    eax = MEM32(ebp + -8);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(edi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, edi (32-bit) */
    esi = 0x21FA28;
    if (CMP_EQ(_fa, _fb)) goto loc_00220076; /* je: equal / zero */

loc_00220061: ;
    ecx = MEM32(ebp + 8);
    PUSH32(esp, esi);
    MEM8(0x21FA28) = 0;
    MEM8(0x21FA29) = LO8(eax);
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00220076u); sub_00220104(); /* call 0x00220104 */

loc_00220076: ;
    eax = MEM32(ebp + -12);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(edi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, edi (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_00220092; /* je: equal / zero */

loc_0022007D: ;
    ecx = MEM32(ebp + 8);
    PUSH32(esp, esi);
    MEM8(0x21FA28) = 2;
    MEM8(0x21FA29) = LO8(eax);
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00220092u); sub_00220104(); /* call 0x00220104 */

loc_00220092: ;
    eax = MEM32(ebp + -4);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(edi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, edi (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_002200AE; /* je: equal / zero */

loc_00220099: ;
    ecx = MEM32(ebp + 8);
    PUSH32(esp, esi);
    MEM8(0x21FA28) = 1;
    MEM8(0x21FA29) = LO8(eax);
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x002200AEu); sub_00220104(); /* call 0x00220104 */

loc_002200AE: ;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, edi);
    PUSH32(esp, 0x286D88);
    { uint32_t _icall_target = MEM32(0x225B38); PUSH32(esp, 0x002200BAu); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_002200BA: ;
    POP32(esp, edi);
    POP32(esp, ebx);

loc_002200BC: ;
    POP32(esp, esi);
    esp = ebp;
    POP32(esp, ebp); /* leave */
    esp += 8; return; /* ret 4 */

}

/**
 * sub_002200C1
 * Original: 0x002200C1 - 0x002200F8 (55 bytes, 23 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_002200C1(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_002200C1: ;
    edx = MEM32(ecx + 0x9C);
    eax = 0; /* xor self */
    _fa = (uint32_t)(edx) & 0xFFFFFFFFu; _fb = (uint32_t)(edx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test edx, edx (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_002200EF; /* je: equal / zero */

loc_002200CD: ;
    ecx = MEM32(ecx + 0x98);
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, ecx (32-bit) */
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    if (CMP_BE(_fa & _fb, 0)) goto loc_002200EB; /* jbe: below or equal (unsigned <=) */

loc_002200D9: ;
    esi = edx;

loc_002200DB: ;
    edi = MEM32(esi);
    _fa = (uint32_t)(edi) & 0xFFFFFFFFu; _fb = (uint32_t)(MEM32(esp + 0xC)) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edi, MEM32(esp + 0xC) (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_002200F2; /* je: equal / zero */

loc_002200E3: ;
    eax++;
    esi = esi + 8;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, ecx (32-bit) */
    if (CMP_B(_fa, _fb)) goto loc_002200DB; /* jb: below (unsigned <) */

loc_002200EB: ;
    eax = 0; /* xor self */

loc_002200ED: ;
    POP32(esp, edi);
    POP32(esp, esi);

loc_002200EF: ;
    esp += 8; return; /* ret 4 */

loc_002200F2: ;
    eax = MEM32(edx + eax * 8 + 4);
    goto loc_002200ED;

}

/**
 * sub_002200F8
 * Original: 0x002200F8 - 0x00220104 (12 bytes, 4 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_002200F8(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_002200F8: ;
    eax = 0; /* xor self */
    _fa = (uint32_t)(MEM32(ecx + 0x9C)) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(ecx + 0x9C), eax (32-bit) */
    SET_LO8(eax, (CMP_EQ(_fa, _fb)) ? 1 : 0); /* sete */
    esp += 4; return; /* ret */

}

/**
 * sub_00220104
 * Original: 0x00220104 - 0x00220306 (514 bytes, 198 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00220104(void)
{
    uint32_t ebp;
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00220104: ;
    PUSH32(esp, ebp);
    ebp = esp;
    g_ebp = ebp; /* publish frame for frameless callees */
    esp = esp - 0xC;
    PUSH32(esp, ebx);
    PUSH32(esp, esi);
    esi = MEM32(ebp + 8);
    eax = ZX8(MEM8(esi + 1));
    MEM32(ebp + -8) = eax;
    eax = ZX8(MEM8(esi));
    eax = eax - 0;
    edx = ecx;
    PUSH32(esp, edi);
    MEM32(ebp + -12) = edx;
    if ((eax == 0)) goto loc_00220164; /* je: equal / zero */

loc_00220124: ;
    eax--;
    if ((eax == 0)) goto loc_0022015F; /* je: equal / zero */

loc_00220127: ;
    eax--;
    if ((eax != 0)) goto loc_00220168; /* jne: not equal / not zero */

loc_0022012A: ;
    SET_LO8(eax, MEM8(esi + 2));
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(MEM8(edx + 0x34)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp LO8(eax), MEM8(edx + 0x34) (8-bit) */
    ebx = edx + 0x64;
    if (CMP_BE(_fa, _fb)) goto loc_00220138; /* jbe: below or equal (unsigned <=) */

loc_00220135: ;
    MEM8(edx + 0x34) = LO8(eax);

loc_00220138: ;
    SET_LO8(eax, MEM8(esi + 1));
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(4) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp LO8(eax), 4 (8-bit) */
    if (CMP_BE(_fa, _fb)) goto loc_0022016B; /* jbe: below or equal (unsigned <=) */

loc_0022013F: ;
    SET_LO8(eax, LO8(eax) - 4);
    PUSH32(esp, esi);
    ecx = edx;
    MEM8(esi + 1) = LO8(eax);
    MEM8(esi) = 1;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x0022014Fu); sub_00220104(); /* call 0x00220104 */

loc_0022014F: ;
    MEM8(esi + 1) = MEM8(esi + 1) + 4;
    MEM32(ebp + -8) = MEM32(ebp + -8) - 4;
    edx = MEM32(ebp + -12);
    MEM8(esi) = 2;
    goto loc_0022016B;

loc_0022015F: ;
    ebx = edx + 0x32;
    goto loc_0022016B;

loc_00220164: ;
    ebx = edx;
    goto loc_0022016B;

loc_00220168: ;
    ebx = MEM32(ebp + 8);

loc_0022016B: ;
    SET_LO8(eax, MEM8(esi + 2));
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(MEM8(ebx + 2)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp LO8(eax), MEM8(ebx + 2) (8-bit) */
    if (CMP_BE(_fa, _fb)) goto loc_00220176; /* jbe: below or equal (unsigned <=) */

loc_00220173: ;
    MEM8(ebx + 2) = LO8(eax);

loc_00220176: ;
    eax = MEM32(ebp + -8);
    MEM32(ebp + 8) = MEM32(ebp + 8) & 0;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    MEM32(ebp + -4) = eax;
    if (TEST_Z(_fa, _fb)) goto loc_002201CD; /* je: equal / zero */

loc_00220184: ;
    edi = ebx + 3;

loc_00220187: ;
    _fa = (uint32_t)(MEM32(ebp + 8)) & 0xFFFFFFFFu; _fb = (uint32_t)(4) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(ebp + 8), 4 (32-bit) */
    if (CMP_AE(_fa, _fb)) goto loc_002201CD; /* jae: above or equal (unsigned >=) */

loc_0022018D: ;
    SET_LO8(eax, MEM8(edi));
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(MEM8(esi + 3)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp LO8(eax), MEM8(esi + 3) (8-bit) */
    if (CMP_BE(_fa, _fb)) goto loc_0022019C; /* jbe: below or equal (unsigned <=) */

loc_00220194: ;
    MEM32(ebp + 8) = MEM32(ebp + 8) + 1;
    edi = edi + 0xA;
    goto loc_002201C7;

loc_0022019C: ;
    _fa = (uint32_t)(MEM32(ebp + 8)) & 0xFFFFFFFFu; _fb = (uint32_t)(4) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(ebp + 8), 4 (32-bit) */
    if (CMP_AE(_fa, _fb)) goto loc_002201B9; /* jae: above or equal (unsigned >=) */

loc_002201A2: ;
    PUSH32(esp, 4);
    POP32(esp, eax);
    eax = eax - MEM32(ebp + 8);
    ecx = ebx + 0x2B;

loc_002201AB: ;
    SET_LO8(edx, MEM8(ecx + -10));
    MEM8(ecx) = LO8(edx);
    ecx = ecx - 0xA;
    eax--;
    if ((eax != 0)) goto loc_002201AB; /* jne: not equal / not zero */

loc_002201B6: ;
    edx = MEM32(ebp + -12);

loc_002201B9: ;
    SET_LO8(eax, MEM8(esi + 3));
    MEM32(ebp + 8) = MEM32(ebp + 8) + 1;
    MEM8(edi) = LO8(eax);
    edi = edi + 0xA;
    MEM32(ebp + -4) = MEM32(ebp + -4) - 1;

loc_002201C7: ;
    _fa = (uint32_t)(MEM32(ebp + -4)) & 0xFFFFFFFFu; _fb = (uint32_t)(0) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(ebp + -4), 0 (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_00220187; /* jne: not equal / not zero */

loc_002201CD: ;
    eax = MEM32(ebp + -8);
    MEM32(ebp + 8) = MEM32(ebp + 8) & 0;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    MEM32(ebp + -4) = eax;
    if (TEST_Z(_fa, _fb)) goto loc_00220224; /* je: equal / zero */

loc_002201DB: ;
    edi = ebx + 4;

loc_002201DE: ;
    _fa = (uint32_t)(MEM32(ebp + 8)) & 0xFFFFFFFFu; _fb = (uint32_t)(4) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(ebp + 8), 4 (32-bit) */
    if (CMP_AE(_fa, _fb)) goto loc_00220224; /* jae: above or equal (unsigned >=) */

loc_002201E4: ;
    SET_LO8(eax, MEM8(edi));
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(MEM8(esi + 4)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp LO8(eax), MEM8(esi + 4) (8-bit) */
    if (CMP_BE(_fa, _fb)) goto loc_002201F3; /* jbe: below or equal (unsigned <=) */

loc_002201EB: ;
    MEM32(ebp + 8) = MEM32(ebp + 8) + 1;
    edi = edi + 0xA;
    goto loc_0022021E;

loc_002201F3: ;
    _fa = (uint32_t)(MEM32(ebp + 8)) & 0xFFFFFFFFu; _fb = (uint32_t)(4) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(ebp + 8), 4 (32-bit) */
    if (CMP_AE(_fa, _fb)) goto loc_00220210; /* jae: above or equal (unsigned >=) */

loc_002201F9: ;
    PUSH32(esp, 4);
    POP32(esp, eax);
    eax = eax - MEM32(ebp + 8);
    ecx = ebx + 0x2C;

loc_00220202: ;
    SET_LO8(edx, MEM8(ecx + -10));
    MEM8(ecx) = LO8(edx);
    ecx = ecx - 0xA;
    eax--;
    if ((eax != 0)) goto loc_00220202; /* jne: not equal / not zero */

loc_0022020D: ;
    edx = MEM32(ebp + -12);

loc_00220210: ;
    SET_LO8(eax, MEM8(esi + 4));
    MEM32(ebp + 8) = MEM32(ebp + 8) + 1;
    MEM8(edi) = LO8(eax);
    edi = edi + 0xA;
    MEM32(ebp + -4) = MEM32(ebp + -4) - 1;

loc_0022021E: ;
    _fa = (uint32_t)(MEM32(ebp + -4)) & 0xFFFFFFFFu; _fb = (uint32_t)(0) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(ebp + -4), 0 (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_002201DE; /* jne: not equal / not zero */

loc_00220224: ;
    eax = MEM32(ebp + -8);
    MEM32(ebp + 8) = MEM32(ebp + 8) & 0;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    MEM32(ebp + -4) = eax;
    if (TEST_Z(_fa, _fb)) goto loc_0022027B; /* je: equal / zero */

loc_00220232: ;
    edi = ebx + 5;

loc_00220235: ;
    _fa = (uint32_t)(MEM32(ebp + 8)) & 0xFFFFFFFFu; _fb = (uint32_t)(4) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(ebp + 8), 4 (32-bit) */
    if (CMP_AE(_fa, _fb)) goto loc_0022027B; /* jae: above or equal (unsigned >=) */

loc_0022023B: ;
    SET_LO8(eax, MEM8(edi));
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(MEM8(esi + 5)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp LO8(eax), MEM8(esi + 5) (8-bit) */
    if (CMP_BE(_fa, _fb)) goto loc_0022024A; /* jbe: below or equal (unsigned <=) */

loc_00220242: ;
    MEM32(ebp + 8) = MEM32(ebp + 8) + 1;
    edi = edi + 0xA;
    goto loc_00220275;

loc_0022024A: ;
    _fa = (uint32_t)(MEM32(ebp + 8)) & 0xFFFFFFFFu; _fb = (uint32_t)(4) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(ebp + 8), 4 (32-bit) */
    if (CMP_AE(_fa, _fb)) goto loc_00220267; /* jae: above or equal (unsigned >=) */

loc_00220250: ;
    PUSH32(esp, 4);
    POP32(esp, eax);
    eax = eax - MEM32(ebp + 8);
    ecx = ebx + 0x2D;

loc_00220259: ;
    SET_LO8(edx, MEM8(ecx + -10));
    MEM8(ecx) = LO8(edx);
    ecx = ecx - 0xA;
    eax--;
    if ((eax != 0)) goto loc_00220259; /* jne: not equal / not zero */

loc_00220264: ;
    edx = MEM32(ebp + -12);

loc_00220267: ;
    SET_LO8(eax, MEM8(esi + 5));
    MEM32(ebp + 8) = MEM32(ebp + 8) + 1;
    MEM8(edi) = LO8(eax);
    edi = edi + 0xA;
    MEM32(ebp + -4) = MEM32(ebp + -4) - 1;

loc_00220275: ;
    _fa = (uint32_t)(MEM32(ebp + -4)) & 0xFFFFFFFFu; _fb = (uint32_t)(0) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(ebp + -4), 0 (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_00220235; /* jne: not equal / not zero */

loc_0022027B: ;
    eax = MEM32(ebp + -8);
    MEM32(ebp + 8) = MEM32(ebp + 8) & 0;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    MEM32(ebp + -4) = eax;
    if (TEST_Z(_fa, _fb)) goto loc_002202D2; /* je: equal / zero */

loc_00220289: ;
    edi = ebx + 8;

loc_0022028C: ;
    _fa = (uint32_t)(MEM32(ebp + 8)) & 0xFFFFFFFFu; _fb = (uint32_t)(4) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(ebp + 8), 4 (32-bit) */
    if (CMP_AE(_fa, _fb)) goto loc_002202D2; /* jae: above or equal (unsigned >=) */

loc_00220292: ;
    SET_LO8(eax, MEM8(edi));
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(MEM8(esi + 8)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp LO8(eax), MEM8(esi + 8) (8-bit) */
    if (CMP_BE(_fa, _fb)) goto loc_002202A1; /* jbe: below or equal (unsigned <=) */

loc_00220299: ;
    MEM32(ebp + 8) = MEM32(ebp + 8) + 1;
    edi = edi + 0xA;
    goto loc_002202CC;

loc_002202A1: ;
    _fa = (uint32_t)(MEM32(ebp + 8)) & 0xFFFFFFFFu; _fb = (uint32_t)(4) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(ebp + 8), 4 (32-bit) */
    if (CMP_AE(_fa, _fb)) goto loc_002202BE; /* jae: above or equal (unsigned >=) */

loc_002202A7: ;
    PUSH32(esp, 4);
    POP32(esp, eax);
    eax = eax - MEM32(ebp + 8);
    ecx = ebx + 0x30;

loc_002202B0: ;
    SET_LO8(edx, MEM8(ecx + -10));
    MEM8(ecx) = LO8(edx);
    ecx = ecx - 0xA;
    eax--;
    if ((eax != 0)) goto loc_002202B0; /* jne: not equal / not zero */

loc_002202BB: ;
    edx = MEM32(ebp + -12);

loc_002202BE: ;
    SET_LO8(eax, MEM8(esi + 8));
    MEM32(ebp + 8) = MEM32(ebp + 8) + 1;
    MEM8(edi) = LO8(eax);
    edi = edi + 0xA;
    MEM32(ebp + -4) = MEM32(ebp + -4) - 1;

loc_002202CC: ;
    _fa = (uint32_t)(MEM32(ebp + -4)) & 0xFFFFFFFFu; _fb = (uint32_t)(0) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(ebp + -4), 0 (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_0022028C; /* jne: not equal / not zero */

loc_002202D2: ;
    SET_LO8(eax, MEM8(esi + 6));
    ecx = edx + 0xB0;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(MEM8(ecx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp LO8(eax), MEM8(ecx) (8-bit) */
    if (CMP_BE(_fa, _fb)) goto loc_002202E1; /* jbe: below or equal (unsigned <=) */

loc_002202DF: ;
    MEM8(ecx) = LO8(eax);

loc_002202E1: ;
    SET_LO8(eax, MEM8(esi + 7));
    ecx = edx + 0xB1;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(MEM8(ecx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp LO8(eax), MEM8(ecx) (8-bit) */
    if (CMP_BE(_fa, _fb)) goto loc_002202F0; /* jbe: below or equal (unsigned <=) */

loc_002202EE: ;
    MEM8(ecx) = LO8(eax);

loc_002202F0: ;
    SET_LO8(eax, MEM8(esi + 9));
    POP32(esp, edi);
    ecx = edx + 0xB2;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(MEM8(ecx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp LO8(eax), MEM8(ecx) (8-bit) */
    POP32(esp, esi);
    POP32(esp, ebx);
    if (CMP_BE(_fa, _fb)) goto loc_00220302; /* jbe: below or equal (unsigned <=) */

loc_00220300: ;
    MEM8(ecx) = LO8(eax);

loc_00220302: ;
    esp = ebp;
    POP32(esp, ebp); /* leave */
    esp += 8; return; /* ret 4 */

}

/**
 * sub_00220306
 * Original: 0x00220306 - 0x0022044F (329 bytes, 96 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00220306(void)
{
    uint32_t ebp;
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00220306: ;
    PUSH32(esp, ebp);
    ebp = esp;
    g_ebp = ebp; /* publish frame for frameless callees */
    esp = esp - 0xC;
    PUSH32(esp, ebx);
    eax = 0; /* xor self */
    PUSH32(esp, esi);
    esi = 0; /* xor self */
    MEM8(ecx + 0xA0) = 0x10;
    _fa = (uint32_t)(MEM8(0x21F924)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(0x21F924), LO8(eax) (8-bit) */
    PUSH32(esp, edi);
    MEM32(ebp + -4) = eax;
    MEM32(ebp + -8) = eax;
    if (CMP_EQ(_fa, _fb)) goto loc_0022032F; /* je: equal / zero */

loc_00220328: ;
    MEM8(ecx + 0xA0) = 0x30;

loc_0022032F: ;
    SET_LO8(eax, MEM8(ecx + 2));
    SET_LO8(edx, MEM8(ecx + 0x34));
    SET_LO8(edx, LO8(edx) + LO8(eax));
    SET_LO8(edx, LO8(edx) + MEM8(ecx + 0x66));
    SET_LO8(edx, LO8(edx) << 2);
    SET_LO8(edx, LO8(edx) + 3);
    MEM8(ecx + 0xA0) = MEM8(ecx + 0xA0) + LO8(edx);
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(MEM8(ecx + 0xA1)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp LO8(eax), MEM8(ecx + 0xA1) (8-bit) */
    if (CMP_BE(_fa, _fb)) goto loc_00220354; /* jbe: below or equal (unsigned <=) */

loc_0022034E: ;
    MEM8(ecx + 0xA1) = LO8(eax);

loc_00220354: ;
    SET_LO8(eax, MEM8(ecx + 0x66));
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(MEM8(ecx + 0xA1)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp LO8(eax), MEM8(ecx + 0xA1) (8-bit) */
    if (CMP_BE(_fa, _fb)) goto loc_00220365; /* jbe: below or equal (unsigned <=) */

loc_0022035F: ;
    MEM8(ecx + 0xA1) = LO8(eax);

loc_00220365: ;
    SET_LO8(eax, MEM8(ecx + 0x34));
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(MEM8(ecx + 0xA1)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp LO8(eax), MEM8(ecx + 0xA1) (8-bit) */
    if (CMP_BE(_fa, _fb)) goto loc_00220376; /* jbe: below or equal (unsigned <=) */

loc_00220370: ;
    MEM8(ecx + 0xA1) = LO8(eax);

loc_00220376: ;
    SET_LO8(eax, MEM8(ecx + 0xA1));
    MEM8(ecx + 0xA0) = MEM8(ecx + 0xA0) + LO8(eax);
    eax = ecx + 0x37;
    MEM32(ebp + -12) = 4;

loc_0022038C: ;
    edi = ZX8(MEM8(eax + 0x32));
    edx = ZX8(MEM8(eax + -50));
    edx = edx + edi;
    edi = ZX8(MEM8(eax));
    edi = edi + esi;
    esi = edi + edx;
    edi = ZX8(MEM8(eax + 0x30));
    edx = ZX8(MEM8(eax + -52));
    edx = edx + edi;
    edi = ZX8(MEM8(eax + -2));
    edi = edi + MEM32(ebp + -4);
    eax = eax + 0xA;
    edi = edi + edx;
    edx = ZX8(MEM8(eax + -61));
    MEM32(ebp + -4) = edi;
    edi = ZX8(MEM8(eax + 0x27));
    edx = edx + edi;
    edi = ZX8(MEM8(eax + -11));
    edi = edi + MEM32(ebp + -8);
    edi = edi + edx;
    edx = ZX8(MEM8(eax + -57));
    MEM32(ecx + 0xA8) = MEM32(ecx + 0xA8) + edx;
    ebx = ZX8(MEM8(eax + 0x2B));
    edx = MEM32(ecx + 0xA8);
    edx = edx + ebx;
    MEM32(ecx + 0xA8) = edx;
    ebx = ZX8(MEM8(eax + -7));
    ebx = ebx + edx;
    MEM32(ebp + -12) = MEM32(ebp + -12) - 1;
    MEM32(ebp + -8) = edi;
    MEM32(ecx + 0xA8) = ebx;
    if ((MEM32(ebp + -12) != 0)) goto loc_0022038C; /* jne: not equal / not zero */

loc_002203FA: ;
    _fa = (uint32_t)(MEM8(0x21F924)) & 0xFFu; _fb = (uint32_t)(0) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(0x21F924), 0 (8-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_0022040C; /* je: equal / zero */

loc_00220403: ;
    esi = esi + 0xD;
    MEM32(ebp + -4) = MEM32(ebp + -4) + 0xD;
    goto loc_00220413;

loc_0022040C: ;
    esi = esi + 5;
    MEM32(ebp + -4) = MEM32(ebp + -4) + 5;

loc_00220413: ;
    MEM32(ebp + -4) = MEM32(ebp + -4) + 1;
    edx = ecx + 0xB0;
    _fa = (uint32_t)(MEM8(edx)) & 0xFFu; _fb = (uint32_t)(0xD) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(edx), 0xD (8-bit) */
    if (CMP_AE(_fa, _fb)) goto loc_00220424; /* jae: above or equal (unsigned >=) */

loc_00220421: ;
    MEM8(edx) = 0xD;

loc_00220424: ;
    eax = MEM32(ebp + -4);
    edx = ZX8(MEM8(edx));
    eax = eax + edi;
    edi = ZX8(MEM8(ecx + 0xB1));
    ebx = eax + esi * 2;
    ebx = ebx + esi;
    ebx = ebx + edi;
    edx = edx + ebx;
    POP32(esp, edi);
    eax = eax + esi;
    POP32(esp, esi);
    MEM32(ecx + 0xAC) = edx;
    MEM32(ecx + 0xA4) = eax;
    POP32(esp, ebx);
    esp = ebp;
    POP32(esp, ebp); /* leave */
    esp += 4; return; /* ret */

}

/**
 * sub_0022044F
 * Original: 0x0022044F - 0x00220614 (453 bytes, 142 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0022044F(void)
{
    uint32_t ebp;
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_0022044F: ;
    PUSH32(esp, ebp);
    ebp = esp;
    g_ebp = ebp; /* publish frame for frameless callees */
    esp = esp - 0xC;
    PUSH32(esp, ebx);
    ebx = ecx;
    ecx = ZX8(MEM8(ebx + 0xE));
    eax = MEM32(ebx + 4);
    ecx = ecx << 6;
    ecx = ecx + 0x30;
    _fa = (uint32_t)(MEM32(ebx)) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(ebx), eax (32-bit) */
    PUSH32(esp, esi);
    MEM32(ebp + -8) = ecx;
    if (CMP_AE(_fa, _fb)) goto loc_0022046F; /* jae: above or equal (unsigned >=) */

loc_0022046D: ;
    MEM32(ebx) = eax;

loc_0022046F: ;
    eax = (uint32_t)((int32_t)eax * (int32_t)ecx);
    ecx = MEM32(ebx + 8);
    ecx = ecx + 8;
    ecx = ecx << 5;
    eax = eax + ecx;
    ecx = MEM32(ebx);
    ecx = ecx + ecx * 2;
    ecx = ecx << 4;
    eax = eax + ecx;
    ecx = eax;
    eax = ecx + 0xFFF;
    eax = eax >> 0xC;
    edx = eax;
    edx = edx << 4;
    edx = edx + ecx;
    ecx = eax;
    ecx = ecx << 0xC;
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(edx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp ecx, edx (32-bit) */
    if (CMP_AE(_fa, _fb)) goto loc_002204A3; /* jae: above or equal (unsigned >=) */

loc_002204A2: ;
    eax++;

loc_002204A3: ;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, edi);
    eax = eax << 0xC;
    edi = eax;
    PUSH32(esp, edi);
    MEM32(ebp + -4) = edi;
    { uint32_t _icall_target = MEM32(0x225A8C); PUSH32(esp, 0x002204B3u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_002204B3: ;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 0);
    esi = eax;
    PUSH32(esp, edi);
    PUSH32(esp, esi);
    { uint32_t _icall_target = MEM32(0x225B8C); PUSH32(esp, 0x002204BFu); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_002204BF: ;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, esi);
    { uint32_t _icall_target = MEM32(0x225B88); PUSH32(esp, 0x002204C6u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_002204C6: ;
    ecx = esi;
    ecx = ecx - eax;
    MEM32(0x287880) = ecx;
    ecx = edi;
    edx = ecx;
    ecx = ecx >> 2;
    eax = 0; /* xor self */
    edi = esi;
    { uint32_t _i; for (_i = 0; _i < ecx; _i++) MEM32(edi + _i*4) = eax; }
    edi += ecx * 4; ecx = 0; /* rep stosd */
    ecx = edx;
    ecx = ecx & 3;
    memset((void*)XBOX_PTR(edi), (uint8_t)eax, ecx);
    edi += ecx; ecx = 0; /* rep stosb */
    eax = edx;
    edx = 0; /* xor self */
    MEM32(0x287884) = esi;
    MEM32(0x287888) = edx;
    edi = ZX8(MEM8(ebx + 0xE));
    ecx = esi + eax;
    esi = esi + 0x100;
    eax = 0; /* xor self */
    MEM32(0x2878AC) = edi;
    MEM32(0x2878A8) = edx;
    _fa = (uint32_t)(MEM32(ebx + 4)) & 0xFFFFFFFFu; _fb = (uint32_t)(edx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(ebx + 4), edx (32-bit) */
    MEM32(ebp + -12) = ecx;
    if (CMP_BE(_fa, _fb)) goto loc_00220555; /* jbe: below or equal (unsigned <=) */

loc_00220517: ;
    edi = MEM32(0x2878A8);
    MEM32(esi) = edi;
    edi = MEM32(0x287888);
    MEM32(0x2878A8) = esi;
    esi = esi + MEM32(ebp + -8);
    MEM32(esi + 0x18) = edi;
    MEM32(0x287888) = esi;
    esi = esi + 0x30;
    eax++;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(MEM32(ebx + 4)) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, MEM32(ebx + 4) (32-bit) */
    if (CMP_B(_fa, _fb)) goto loc_00220517; /* jb: below (unsigned <) */

loc_00220540: ;
    goto loc_00220555;

loc_00220542: ;
    edi = MEM32(0x287888);
    MEM32(esi + 0x18) = edi;
    MEM32(0x287888) = esi;
    esi = esi + 0x30;
    eax++;

loc_00220555: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(MEM32(ebx)) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, MEM32(ebx) (32-bit) */
    if (CMP_B(_fa, _fb)) goto loc_00220542; /* jb: below (unsigned <) */

loc_00220559: ;
    edi = esi + 0x20;
    _fa = (uint32_t)(edi) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edi, ecx (32-bit) */
    MEM32(ebp + -4) = edx;
    MEM32(0x28788C) = edx;
    MEM32(0x287890) = esi;
    if (CMP_A(_fa, _fb)) goto loc_00220593; /* ja: above (unsigned >) */

loc_0022056F: ;
    eax = esi;
    eax = eax - MEM32(0x287880);
    PUSH32(esp, esi);
    MEM32(ebp + -8) = esi;
    MEM32(edi + -16) = eax;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00220583u); sub_0022414A(); /* call 0x0022414A */

loc_00220583: ;
    esi = esi + 0x20;
    edi = edi + 0x20;
    MEM32(ebp + -4) = MEM32(ebp + -4) + 1;
    _fa = (uint32_t)(edi) & 0xFFFFFFFFu; _fb = (uint32_t)(MEM32(ebp + -12)) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edi, MEM32(ebp + -12) (32-bit) */
    if (CMP_BE(_fa, _fb)) goto loc_0022056F; /* jbe: below or equal (unsigned <=) */

loc_00220591: ;
    edx = 0; /* xor self */

loc_00220593: ;
    eax = MEM32(ebp + -8);
    ecx = MEM32(ebp + -4);
    MEM32(0x287894) = eax;
    MEM32(0x287898) = edx;
    MEM32(0x28789C) = 0x3E8;
    SET_LO16(eax, ZX8(MEM8(ebx + 0xC)));
    MEM16(0x2878A0) = LO16(eax);
    SET_LO16(eax, ZX8(MEM8(ebx + 0xD)));
    MEM16(0x2878A4) = LO16(eax);
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(MEM32(ebx + 8)) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp ecx, MEM32(ebx + 8) (32-bit) */
    POP32(esp, edi);
    if (CMP_BE(_fa, _fb)) goto loc_002205FC; /* jbe: below or equal (unsigned <=) */

loc_002205CA: ;
    SET_LO8(ecx, LO8(ecx) - MEM8(ebx + 8));
    _fa = (uint32_t)(LO16(eax)) & 0xFFFFu; _fb = (uint32_t)(LO16(edx)) & 0xFFFFu;
    _fas = (int32_t)(int16_t)(_fa); _fbs = (int32_t)(int16_t)(_fb); /* cmp LO16(eax), LO16(edx) (16-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_002205E5; /* je: equal / zero */

loc_002205D2: ;
    SET_LO8(edx, LO8(ecx));
    SET_LO8(edx, LO8(edx) >> 1);
    SET_LO16(esi, ZX8(LO8(edx)));
    SET_LO16(eax, LO16(eax) + LO16(esi));
    MEM16(0x2878A4) = LO16(eax);
    SET_LO8(ecx, LO8(ecx) - LO8(edx));

loc_002205E5: ;
    SET_LO16(eax, ZX8(LO8(ecx)));
    MEM16(0x2878A0) = MEM16(0x2878A0) + LO16(eax);
    eax = MEM32(ebp + -4);
    MEM32(ebx + 8) = eax;
    SET_LO16(eax, MEM16(0x2878A4));

loc_002205FC: ;
    SET_LO16(ecx, MEM16(0x2878A0));
    POP32(esp, esi);
    MEM16(0x2878A2) = LO16(ecx);
    MEM16(0x2878A6) = LO16(eax);
    POP32(esp, ebx);
    esp = ebp;
    POP32(esp, ebp); /* leave */
    esp += 4; return; /* ret */

}

/**
 * sub_00220614
 * Original: 0x00220614 - 0x00220675 (97 bytes, 32 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00220614(void)
{

loc_00220614: ;
    PUSH32(esp, esi);
    esi = ecx;
    eax = MEM32(esi + 8);
    eax = eax - MEM32(0x287880);
    ecx = MEM32(esi);
    MEM32(ecx + 0x18) = eax;
    ecx = MEM32(esi);
    eax = 0; /* xor self */
    MEM32(ecx + 0x1C) = eax;
    ecx = MEM32(esi);
    MEM32(ecx + 0x20) = eax;
    ecx = MEM32(esi);
    MEM32(ecx + 0x24) = eax;
    ecx = MEM32(esi);
    MEM32(ecx + 0x28) = eax;
    ecx = MEM32(esi);
    MEM32(ecx + 0x2C) = eax;
    ecx = MEM32(esi);
    MEM32(ecx + 0x30) = eax;
    PUSH32(esp, 1);
    MEM16(esi + 0x416) = 0x2772;
    eax = MEM32(esi);
    PUSH32(esp, 3);
    MEM32(eax + 0x40) = 0x2A29;
    PUSH32(esp, 8);
    MEM16(esi + 0x414) = 0x236F;
    PUSH32(esp, 0x0022066Bu); sub_002231B8(); /* call 0x002231B8 */

loc_0022066B: ;
    ecx = MEM32(esi);
    eax = ZX16(LO16(eax));
    MEM32(ecx + 0x44) = eax;
    POP32(esp, esi);
    esp += 4; return; /* ret */

}

/**
 * sub_00220675
 * Original: 0x00220675 - 0x00220680 (11 bytes, 4 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00220675(void)
{

loc_00220675: ;
    eax = MEM32(esp + 4);
    eax = MEM32(eax);
    eax = MEM32(eax);
    esp += 8; return; /* ret 4 */

}

/**
 * sub_00220680
 * Original: 0x00220680 - 0x002206E2 (98 bytes, 37 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00220680(void)
{
    uint32_t ebp;
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00220680: ;
    PUSH32(esp, ebp);
    ebp = esp;
    g_ebp = ebp; /* publish frame for frameless callees */
    PUSH32(esp, ecx);
    PUSH32(esp, ecx);
    edx = MEM32(ebp + 8);
    eax = MEM32(edx);
    ecx = MEM32(eax + 4);
    PUSH32(esp, esi);
    esi = 0x100;
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test esi, ecx (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_002206A9; /* je: equal / zero */

loc_00220697: ;
    ecx = MEM32(eax + 8);
    ecx = ecx | 8;
    MEM32(eax + 8) = ecx;
    edx = MEM32(edx);

loc_002206A2: ;
    _fa = (uint32_t)(MEM32(edx + 4)) & 0xFFFFFFFFu; _fb = (uint32_t)(esi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test MEM32(edx + 4), esi (32-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_002206A2; /* jne: not equal / not zero */

loc_002206A7: ;
    goto loc_002206DD;

loc_002206A9: ;
    edx = ecx;
    edx = edx >> 6;
    edx = edx & 3;
    if ((edx == 0)) goto loc_002206DD; /* je: equal / zero */

loc_002206B3: ;
    _fa = (uint32_t)(edx) & 0xFFFFFFFFu; _fb = (uint32_t)(2) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edx, 2 (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_002206DD; /* je: equal / zero */

loc_002206B8: ;
    ecx = ecx & 0xFFFFFF7Fu;
    ecx = ecx | 0x40;
    MEM32(eax + 4) = ecx;
    MEM32(ebp + -4) = MEM32(ebp + -4) | 0xFFFFFFFFu;
    eax = ebp + -8;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, eax);
    PUSH32(esp, 0);
    PUSH32(esp, 0);
    MEM32(ebp + -8) = 0xFFFCF2C0u;
    { uint32_t _icall_target = MEM32(0x225AFC); PUSH32(esp, 0x002206DDu); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_002206DD: ;
    POP32(esp, esi);
    esp = ebp;
    POP32(esp, ebp); /* leave */
    esp += 8; return; /* ret 4 */

}

/**
 * sub_002206F4
 * Original: 0x002206F4 - 0x00220744 (80 bytes, 20 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_002206F4(void)
{

loc_002206F4: ;
    edx = ZX8(MEM8(ecx + 0x79));
    eax = MEM32(ecx + 0xE0);
    edx = edx << 5;
    PUSH32(esp, esi);
    esi = eax + edx + 1;
    SET_LO8(eax, MEM8(esi));
    MEM8(ecx + 0x79) = LO8(eax);
    MEM8(esi) = 0x80;
    eax = MEM32(ecx + 0xE0);
    MEM8(eax + edx + 2) = 0x80;
    eax = MEM32(ecx + 0xE0);
    MEM8(eax + edx + 3) = 0x80;
    eax = MEM32(ecx + 0xE0);
    MEM32(eax + edx + 0x1C) = MEM32(eax + edx + 0x1C) & 0;
    eax = MEM32(ecx + 0xE0);
    MEM8(eax + edx + 7) = 0xFF;
    eax = MEM32(ecx + 0xE0);
    eax = eax + edx;
    POP32(esp, esi);
    esp += 4; return; /* ret */

}

/**
 * sub_00220744
 * Original: 0x00220744 - 0x00220776 (50 bytes, 17 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00220744(void)
{

loc_00220744: ;
    eax = MEM32(esp + 4);
    PUSH32(esp, ebx);
    PUSH32(esp, esi);
    esi = ecx;
    ecx = MEM32(esi + 0xE0);
    eax = eax - ecx;
    eax = (uint32_t)((int32_t)eax >> 5);
    edx = ZX8(LO8(eax));
    edx = edx << 5;
    MEM8(edx + ecx) = 0xFF;
    SET_LO8(ebx, MEM8(esi + 0x79));
    ecx = MEM32(esi + 0xE0);
    MEM8(edx + ecx + 1) = LO8(ebx);
    MEM8(esi + 0x79) = LO8(eax);
    POP32(esp, esi);
    POP32(esp, ebx);
    esp += 8; return; /* ret 4 */

}

/**
 * sub_00220776
 * Original: 0x00220776 - 0x0022078D (23 bytes, 9 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00220776(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00220776: ;
    SET_LO8(eax, MEM8(ecx + 1));
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(0x80) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp LO8(eax), 0x80 (8-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_0022078A; /* je: equal / zero */

loc_0022077D: ;
    eax = ZX8(LO8(eax));
    eax = eax << 5;
    eax = eax + MEM32(0x286C60);
    esp += 4; return; /* ret */

loc_0022078A: ;
    eax = 0; /* xor self */
    esp += 4; return; /* ret */

}

/**
 * sub_0022078D
 * Original: 0x0022078D - 0x002207A4 (23 bytes, 9 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0022078D(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_0022078D: ;
    SET_LO8(eax, MEM8(ecx + 2));
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(0x80) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp LO8(eax), 0x80 (8-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_002207A1; /* je: equal / zero */

loc_00220794: ;
    eax = ZX8(LO8(eax));
    eax = eax << 5;
    eax = eax + MEM32(0x286C60);
    esp += 4; return; /* ret */

loc_002207A1: ;
    eax = 0; /* xor self */
    esp += 4; return; /* ret */

}

/**
 * sub_002207A4
 * Original: 0x002207A4 - 0x002207BB (23 bytes, 9 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_002207A4(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_002207A4: ;
    SET_LO8(eax, MEM8(ecx + 3));
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(0x80) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp LO8(eax), 0x80 (8-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_002207B8; /* je: equal / zero */

loc_002207AB: ;
    eax = ZX8(LO8(eax));
    eax = eax << 5;
    eax = eax + MEM32(0x286C60);
    esp += 4; return; /* ret */

loc_002207B8: ;
    eax = 0; /* xor self */
    esp += 4; return; /* ret */

}

/**
 * sub_002207BB
 * Original: 0x002207BB - 0x0022087F (196 bytes, 58 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_002207BB(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    int _cf = 0; /* carry flag */

loc_002207BB: ;
    PUSH32(esp, ebx);
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    edi = ecx;
    ecx = 0x286B80;
    PUSH32(esp, 0x002207CAu); sub_002206F4(); /* call 0x002206F4 */

loc_002207CA: ;
    esi = eax;
    ebx = 0; /* xor self */
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(ebx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp esi, ebx (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_00220879; /* je: equal / zero */

loc_002207D6: ;
    SET_LO8(eax, MEM8(esp + 0x10));
    MEM8(esi) = 0xFE;
    MEM8(esi + 4) = LO8(eax);
    MEM32(esi + 0x10) = ebx;
    eax = MEM32(edi + 0xC);
    PUSH32(esp, esi);
    ecx = edi;
    MEM32(esi + 0xC) = eax;
    PUSH32(esp, 0x002207F1u); sub_00221A06(); /* call 0x00221A06 */

loc_002207F1: ;
    _fa = (uint32_t)(MEM8(0x286B80)) & 0xFFu; _fb = (uint32_t)(LO8(ebx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(0x286B80), LO8(ebx) (8-bit) */
    SET_LO8(eax, MEM8(esp + 0x14));
    if (CMP_EQ(_fa, _fb)) goto loc_00220834; /* je: equal / zero */

loc_002207FD: ;
    edi = esi + 0x18;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, edi);
    MEM8(esi + 5) = LO8(eax);
    { uint32_t _icall_target = MEM32(0x225AA0); PUSH32(esp, 0x0022080Au); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_0022080A: ;
    _cf = (int)((((uint64_t)(MEM32(edi)) + (uint64_t)(0xF4240)) >> 32) & 1);
    MEM32(edi) = MEM32(edi) + 0xF4240;
    MEM32(esi + 0x10) = ebx;
    { uint64_t _t = (uint64_t)(MEM32(edi + 4)) + (uint64_t)(ebx) + (uint64_t)_cf; _cf = (int)((_t >> 32) & 1); MEM32(edi + 4) = (uint32_t)_t; }  /* adc */
    eax = MEM32(0x286BFC);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(ebx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, ebx (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_0022082A; /* jne: not equal / not zero */

loc_0022081F: ;
    MEM32(0x286BFC) = esi;
    goto loc_00220879;

loc_00220827: ;
    eax = MEM32(eax + 0x10);

loc_0022082A: ;
    _fa = (uint32_t)(MEM32(eax + 0x10)) & 0xFFFFFFFFu; _fb = (uint32_t)(ebx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(eax + 0x10), ebx (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_00220827; /* jne: not equal / not zero */

loc_0022082F: ;
    MEM32(eax + 0x10) = esi;
    goto loc_00220879;

loc_00220834: ;
    MEM8(esi) = 0xFD;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 0x286BB4);
    MEM8(0x286B82) = LO8(eax);
    _cf = 0; /* logical op clears CF */
    ecx = ecx | 0xFFFFFFFFu;
    PUSH32(esp, ecx);
    eax = 0xFFF0BDC0u;
    PUSH32(esp, eax);
    MEM8(0x286B80) = 1;
    MEM8(0x286B81) = LO8(ebx);
    MEM32(0x286C00) = esi;
    MEM8(0x286B83) = 0x80;
    MEM8(esi + 5) = LO8(ebx);
    PUSH32(esp, 0x286BD0);
    MEM8(0x286BF8) = LO8(ebx);
    { uint32_t _icall_target = MEM32(0x225B28); PUSH32(esp, 0x00220879u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00220879: ;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebx);
    esp += 12; return; /* ret 8 */

}

/**
 * sub_0022087F
 * Original: 0x0022087F - 0x002208A1 (34 bytes, 9 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0022087F(void)
{

loc_0022087F: ;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 0x286BB4);
    ecx = ecx | 0xFFFFFFFFu;
    PUSH32(esp, ecx);
    eax = 0xFD050F80u;
    PUSH32(esp, eax);
    PUSH32(esp, 0x286BD0);
    MEM8(0x286BF8) = 1;
    { uint32_t _icall_target = MEM32(0x225B28); PUSH32(esp, 0x002208A0u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_002208A0: ;
    esp += 4; return; /* ret */

}

/**
 * sub_002208A1
 * Original: 0x002208A1 - 0x002208F2 (81 bytes, 20 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_002208A1(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_002208A1: ;
    _fa = (uint32_t)(MEM32(esp + 4)) & 0xFFFFFFFFu; _fb = (uint32_t)(0) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(esp + 4), 0 (32-bit) */
    MEM8(0x286B83) = 0x81;
    if (CMP_GE(_fas, _fbs)) goto loc_002208BC; /* jge: greater or equal (signed >=) */

loc_002208AF: ;
    PUSH32(esp, MEM32(esp + 8));
    PUSH32(esp, 0);
    PUSH32(esp, 0x002208BAu); sub_00220D2F(); /* call 0x00220D2F */

loc_002208BA: ;
    goto loc_002208EF;

loc_002208BC: ;
    _fa = (uint32_t)(MEM32(esp + 4)) & 0xFFFFFFFFu; _fb = (uint32_t)(0x1000000) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(esp + 4), 0x1000000 (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_002208CE; /* jne: not equal / not zero */

loc_002208C6: ;
    eax = MEM32(esp + 8);
    MEM8(eax + 4) = MEM8(eax + 4) | 0x80;

loc_002208CE: ;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 0x286BB4);
    ecx = ecx | 0xFFFFFFFFu;
    PUSH32(esp, ecx);
    eax = 0xFFFE7960u;
    PUSH32(esp, eax);
    PUSH32(esp, 0x286BD0);
    MEM8(0x286BF8) = 2;
    { uint32_t _icall_target = MEM32(0x225B28); PUSH32(esp, 0x002208EFu); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_002208EF: ;
    esp += 12; return; /* ret 8 */

}

/**
 * sub_0022091D
 * Original: 0x0022091D - 0x0022094E (49 bytes, 25 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0022091D(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_0022091D: ;
    PUSH32(esp, ebx);
    edx = 0; /* xor self */
    SET_LO8(ebx, 0); /* xor self */
    edx++;
    PUSH32(esp, esi);
    SET_LO8(eax, LO8(edx));

loc_00220926: ;
    esi = ZX8(LO8(ebx));
    _fa = (uint32_t)(MEM32(ecx + esi * 4 + 8)) & 0xFFFFFFFFu; _fb = (uint32_t)(edx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test MEM32(ecx + esi * 4 + 8), edx (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00220940; /* je: equal / zero */

loc_0022092F: ;
    edx = edx << 1;
    if ((edx != 0)) goto loc_00220938; /* jne: not equal / not zero */

loc_00220933: ;
    edx = 0; /* xor self */
    SET_LO8(ebx, LO8(ebx) + 1);
    edx++;

loc_00220938: ;
    SET_LO8(eax, LO8(eax) + 1);
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(0x80) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp LO8(eax), 0x80 (8-bit) */
    if (CMP_B(_fa, _fb)) goto loc_00220926; /* jb: below (unsigned <) */

loc_0022093E: ;
    goto loc_00220949;

loc_00220940: ;
    esi = ZX8(LO8(ebx));
    ecx = ecx + esi * 4 + 8;
    MEM32(ecx) = MEM32(ecx) | edx;

loc_00220949: ;
    POP32(esp, esi);
    SET_LO8(eax, LO8(eax) & 0x7F);
    POP32(esp, ebx);
    esp += 4; return; /* ret */

}

/**
 * sub_0022094E
 * Original: 0x0022094E - 0x00220982 (52 bytes, 26 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0022094E(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_0022094E: ;
    PUSH32(esp, ebx);
    SET_LO8(ebx, 0); /* xor self */
    SET_LO8(edx, LO8(edx) - 1);
    _fa = (uint32_t)(LO8(edx)) & 0xFFu; _fb = (uint32_t)(0x1F) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp LO8(edx), 0x1F (8-bit) */
    PUSH32(esp, esi);
    if (CMP_BE(_fa, _fb)) goto loc_0022096D; /* jbe: below or equal (unsigned <=) */

loc_00220959: ;
    SET_LO8(eax, LO8(edx));
    SET_LO8(eax, LO8(eax) - 0x20);
    SET_LO8(eax, LO8(eax) >> 5);
    SET_LO8(eax, LO8(eax) + 1);
    eax = ZX8(LO8(eax));
    SET_LO8(ebx, LO8(eax));

loc_00220967: ;
    SET_LO8(edx, LO8(edx) + 0xE0);
    eax--;
    if ((eax != 0)) goto loc_00220967; /* jne: not equal / not zero */

loc_0022096D: ;
    eax = ZX8(LO8(ebx));
    esi = 0; /* xor self */
    eax = ecx + eax * 4 + 8;
    esi++;
    SET_LO8(ecx, LO8(edx));
    esi = esi << LO8(ecx);
    esi = ~esi;
    MEM32(eax) = MEM32(eax) & esi;
    POP32(esp, esi);
    POP32(esp, ebx);
    esp += 4; return; /* ret */

}

/**
 * sub_00220982
 * Original: 0x00220982 - 0x00220989 (7 bytes, 2 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00220982(void)
{

loc_00220982: ;
    MEM32(0x286C64) = MEM32(0x286C64) + 1;
    esp += 4; return; /* ret */

}

/**
 * sub_00220989
 * Original: 0x00220989 - 0x00220990 (7 bytes, 2 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00220989(void)
{

loc_00220989: ;
    MEM32(0x286C64) = MEM32(0x286C64) - 1;
    esp += 4; return; /* ret */

}

/**
 * sub_00220990
 * Original: 0x00220990 - 0x002209B9 (41 bytes, 14 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00220990(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00220990: ;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, esi);
    esi = 0; /* xor self */
    { uint32_t _icall_target = MEM32(0x225B30); PUSH32(esp, 0x00220999u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00220999: ;
    _fa = (uint32_t)(MEM32(0x286C64)) & 0xFFFFFFFFu; _fb = (uint32_t)(esi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(0x286C64), esi (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_002209AA; /* jne: not equal / not zero */

loc_002209A1: ;
    _fa = (uint32_t)(MEM8(0x286B80)) & 0xFFu; _fb = (uint32_t)(0) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(0x286B80), 0 (8-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_002209AD; /* je: equal / zero */

loc_002209AA: ;
    esi = 0; /* xor self */
    esi++;

loc_002209AD: ;
    SET_LO8(ecx, LO8(eax));
    { uint32_t _icall_esp = g_esp;
    { uint32_t _icall_target = MEM32(0x225B2C); PUSH32(esp, 0x002209B5u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_002209B5: ;
    eax = esi;
    POP32(esp, esi);
    esp += 4; return; /* ret */

}

/**
 * sub_002209B9
 * Original: 0x002209B9 - 0x002209CE (21 bytes, 6 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_002209B9(void)
{

loc_002209B9: ;
    eax = MEM32(esp + 4);
    ecx = MEM32(eax + -20);
    PUSH32(esp, 5);
    PUSH32(esp, MEM32(esp + 0xC));
    PUSH32(esp, 0x002209CBu); sub_002207BB(); /* call 0x002207BB */

loc_002209CB: ;
    esp += 12; return; /* ret 8 */

}

/**
 * sub_002209CE
 * Original: 0x002209CE - 0x00220A30 (98 bytes, 39 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_002209CE(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_002209CE: ;
    PUSH32(esp, ebx);
    PUSH32(esp, esi);
    esi = MEM32(0x286C00);
    PUSH32(esp, edi);
    edi = MEM32(esi + 0xC);
    ebx = 0; /* xor self */
    edi = edi + 0x18;
    _fa = (uint32_t)(MEM8(0x286B81)) & 0xFFu; _fb = (uint32_t)(LO8(ebx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(0x286B81), LO8(ebx) (8-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_002209F0; /* je: equal / zero */

loc_002209E7: ;
    PUSH32(esp, esi);
    PUSH32(esp, ebx);
    PUSH32(esp, 0x002209EEu); sub_00220D2F(); /* call 0x00220D2F */

loc_002209EE: ;
    goto loc_00220A2C;

loc_002209F0: ;
    ecx = esi;
    MEM8(0x286B83) = LO8(ebx);
    PUSH32(esp, 0x002209FDu); sub_00220776(); /* call 0x00220776 */

loc_002209FD: ;
    _fa = (uint32_t)(MEM8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(ebx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(eax), LO8(ebx) (8-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_00220A18; /* jne: not equal / not zero */

loc_00220A01: ;
    eax = 0; /* xor self */
    SET_LO8(eax, MEM8(esi + 4));
    PUSH32(esp, esi);
    PUSH32(esp, 0x2208A1);
    eax = eax & 0x7F;
    PUSH32(esp, eax);
    PUSH32(esp, edi);
    PUSH32(esp, 0x00220A16u); sub_00222A08(); /* call 0x00222A08 */

loc_00220A16: ;
    goto loc_00220A2C;

loc_00220A18: ;
    ecx = 0; /* xor self */
    SET_LO8(ecx, MEM8(esi + 4));
    PUSH32(esp, ebx);
    PUSH32(esp, esi);
    ecx = ecx & 0xFFFFFF7Fu;
    PUSH32(esp, ecx);
    PUSH32(esp, eax);
    PUSH32(esp, 0x00220A2Cu); sub_00221FFE(); /* call 0x00221FFE */

loc_00220A2C: ;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebx);
    esp += 4; return; /* ret */

}

/**
 * sub_00220A30
 * Original: 0x00220A30 - 0x00220A35 (5 bytes, 1 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00220A30(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_00220A30: ;
    g_seh_ebp = ebp; sub_002208A1(); return; /* tail jmp 0x002208A1 */

}

/**
 * sub_00220A35
 * Original: 0x00220A35 - 0x00220AAB (118 bytes, 47 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00220A35(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00220A35: ;
    PUSH32(esp, ebx);
    PUSH32(esp, esi);
    esi = ecx;
    SET_LO8(eax, MEM8(esi + 7));
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(0xFF) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp LO8(eax), 0xFF (8-bit) */
    PUSH32(esp, edi);
    if (CMP_EQ(_fa, _fb)) goto loc_00220A5C; /* je: equal / zero */

loc_00220A41: ;
    ecx = MEM32(esi + 0x10);
    ecx = MEM32(ecx + 0x14);
    eax = ZX8(LO8(eax));
    eax = MEM32(ecx + eax * 4);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00220A5C; /* je: equal / zero */

loc_00220A51: ;
    PUSH32(esp, 0);
    PUSH32(esp, MEM32(esi + 0x14));
    PUSH32(esp, eax);
    PUSH32(esp, 0x00220A5Cu); sub_0022153B(); /* call 0x0022153B */

loc_00220A5C: ;
    _fa = (uint32_t)(MEM8(esi)) & 0xFFu; _fb = (uint32_t)(5) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(esi), 5 (8-bit) */
    ebx = 0x286B80;
    if (CMP_NE(_fa, _fb)) goto loc_00220A90; /* jne: not equal / not zero */

loc_00220A66: ;
    ecx = esi;
    PUSH32(esp, 0x00220A6Du); sub_00220776(); /* call 0x00220776 */

loc_00220A6D: ;
    edi = eax;
    PUSH32(esp, esi);
    ecx = edi;
    PUSH32(esp, 0x00220A77u); sub_00221A4E(); /* call 0x00221A4E */

loc_00220A77: ;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_00220A9F; /* jne: not equal / not zero */

loc_00220A7B: ;
    SET_LO8(edx, MEM8(edi + 5));
    ecx = MEM32(edi + 0xC);
    PUSH32(esp, 0x00220A86u); sub_0022094E(); /* call 0x0022094E */

loc_00220A86: ;
    PUSH32(esp, edi);
    ecx = ebx;
    PUSH32(esp, 0x00220A8Eu); sub_00220744(); /* call 0x00220744 */

loc_00220A8E: ;
    goto loc_00220A9F;

loc_00220A90: ;
    SET_LO8(edx, MEM8(esi + 5));
    _fa = (uint32_t)(LO8(edx)) & 0xFFu; _fb = (uint32_t)(LO8(edx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(edx), LO8(edx) (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00220A9F; /* je: equal / zero */

loc_00220A97: ;
    ecx = MEM32(esi + 0xC);
    PUSH32(esp, 0x00220A9Fu); sub_0022094E(); /* call 0x0022094E */

loc_00220A9F: ;
    PUSH32(esp, esi);
    ecx = ebx;
    PUSH32(esp, 0x00220AA7u); sub_00220744(); /* call 0x00220744 */

loc_00220AA7: ;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebx);
    esp += 4; return; /* ret */

}

/**
 * sub_00220AAB
 * Original: 0x00220AAB - 0x00220AFD (82 bytes, 34 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00220AAB(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00220AAB: ;
    ecx = MEM32(esp + 4);
    _fa = (uint32_t)(MEM8(ecx)) & 0xFFu; _fb = (uint32_t)(4) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(ecx), 4 (8-bit) */
    PUSH32(esp, esi);
    if (CMP_NE(_fa, _fb)) goto loc_00220AE7; /* jne: not equal / not zero */

loc_00220AB5: ;
    PUSH32(esp, 0x00220ABAu); sub_0022078D(); /* call 0x0022078D */

loc_00220ABA: ;
    esi = eax;
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(esi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test esi, esi (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00220AF9; /* je: equal / zero */

loc_00220AC0: ;
    PUSH32(esp, edi);

loc_00220AC1: ;
    ecx = esi;
    PUSH32(esp, 0x00220AC8u); sub_002207A4(); /* call 0x002207A4 */

loc_00220AC8: ;
    edi = eax;
    eax = MEM32(esi + 0x10);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00220AD7; /* je: equal / zero */

loc_00220AD1: ;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, esi);
    { uint32_t _icall_target = MEM32(eax + 0xC); PUSH32(esp, 0x00220AD5u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00220AD5: ;
    goto loc_00220ADE;

loc_00220AD7: ;
    ecx = esi;
    PUSH32(esp, 0x00220ADEu); sub_00220A35(); /* call 0x00220A35 */

loc_00220ADE: ;
    _fa = (uint32_t)(edi) & 0xFFFFFFFFu; _fb = (uint32_t)(edi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test edi, edi (32-bit) */
    esi = edi;
    if (TEST_NZ(_fa, _fb)) goto loc_00220AC1; /* jne: not equal / not zero */

loc_00220AE4: ;
    POP32(esp, edi);
    goto loc_00220AF9;

loc_00220AE7: ;
    eax = MEM32(ecx + 0x10);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00220AF4; /* je: equal / zero */

loc_00220AEE: ;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, ecx);
    { uint32_t _icall_target = MEM32(eax + 0xC); PUSH32(esp, 0x00220AF2u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00220AF2: ;
    goto loc_00220AF9;

loc_00220AF4: ;
    PUSH32(esp, 0x00220AF9u); sub_00220A35(); /* call 0x00220A35 */

loc_00220AF9: ;
    POP32(esp, esi);
    esp += 8; return; /* ret 4 */

}

/**
 * sub_00220AFD
 * Original: 0x00220AFD - 0x00220BAC (175 bytes, 50 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00220AFD(void)
{
    uint32_t ebp;
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00220AFD: ;
    PUSH32(esp, ebp);
    ebp = esp;
    g_ebp = ebp; /* publish frame for frameless callees */
    PUSH32(esp, ecx);
    PUSH32(esp, ecx);
    PUSH32(esp, ebx);
    ebx = 0; /* xor self */
    _fa = (uint32_t)(MEM8(0x286B81)) & 0xFFu; _fb = (uint32_t)(LO8(ebx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(0x286B81), LO8(ebx) (8-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_00220B15; /* je: equal / zero */

loc_00220B0D: ;
    PUSH32(esp, MEM32(ebp + 0xC));
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00220B15u); sub_00220AAB(); /* call 0x00220AAB */

loc_00220B15: ;
    eax = MEM32(0x286BFC);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(ebx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, ebx (32-bit) */
    MEM8(0x286B81) = LO8(ebx);
    if (CMP_NE(_fa, _fb)) goto loc_00220B32; /* jne: not equal / not zero */

loc_00220B24: ;
    MEM32(0x286C00) = ebx;
    MEM8(0x286B80) = LO8(ebx);
    goto loc_00220BA7;

loc_00220B32: ;
    MEM32(0x286C00) = eax;
    ecx = MEM32(eax + 0x10);
    MEM32(0x286BFC) = ecx;
    SET_LO8(ecx, MEM8(eax + 5));
    MEM8(0x286B82) = LO8(ecx);
    MEM8(0x286B83) = 0x80;
    MEM8(eax) = 0xFD;
    eax = MEM32(0x286C00);
    MEM32(eax + 0x10) = ebx;
    eax = MEM32(0x286C00);
    MEM8(eax + 5) = LO8(ebx);
    eax = ebp + -8;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, eax);
    { uint32_t _icall_target = MEM32(0x225AA0); PUSH32(esp, 0x00220B6Du); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00220B6D: ;
    eax = MEM32(0x286C00);
    ecx = MEM32(ebp + -4);
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(MEM32(eax + 0x1C)) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp ecx, MEM32(eax + 0x1C) (32-bit) */
    if (CMP_L(_fas, _fbs)) goto loc_00220B8B; /* jl: less (signed <) */

loc_00220B7A: ;
    if (CMP_G(_fas, _fbs)) goto loc_00220B84; /* jg: greater (signed >) */

loc_00220B7C: ;
    ecx = MEM32(ebp + -8);
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(MEM32(eax + 0x18)) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp ecx, MEM32(eax + 0x18) (32-bit) */
    if (CMP_BE(_fa, _fb)) goto loc_00220B8B; /* jbe: below or equal (unsigned <=) */

loc_00220B84: ;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00220B89u); sub_002209CE(); /* call 0x002209CE */

loc_00220B89: ;
    goto loc_00220BA7;

loc_00220B8B: ;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 0x286BB4);
    MEM8(0x286BF8) = LO8(ebx);
    PUSH32(esp, MEM32(eax + 0x1C));
    PUSH32(esp, MEM32(eax + 0x18));
    PUSH32(esp, 0x286BD0);
    { uint32_t _icall_target = MEM32(0x225B28); PUSH32(esp, 0x00220BA7u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00220BA7: ;
    POP32(esp, ebx);
    esp = ebp;
    POP32(esp, ebp); /* leave */
    esp += 12; return; /* ret 8 */

}

/**
 * sub_00220BAC
 * Original: 0x00220BAC - 0x00220C23 (119 bytes, 40 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00220BAC(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00220BAC: ;
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    PUSH32(esp, MEM32(esp + 0xC));
    edi = ecx;
    PUSH32(esp, 0x00220BB9u); sub_002219D5(); /* call 0x002219D5 */

loc_00220BB9: ;
    esi = eax;
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(esi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test esi, esi (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00220C1E; /* je: equal / zero */

loc_00220BBF: ;
    PUSH32(esp, esi);
    ecx = edi;
    PUSH32(esp, 0x00220BC7u); sub_00221A4E(); /* call 0x00221A4E */

loc_00220BC7: ;
    _fa = (uint32_t)(MEM8(esi)) & 0xFFu; _fb = (uint32_t)(0xFE) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(esi), 0xFE (8-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_00220BFE; /* jne: not equal / not zero */

loc_00220BCC: ;
    eax = MEM32(0x286BFC);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(esi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, esi (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_00220BE2; /* jne: not equal / not zero */

loc_00220BD5: ;
    eax = MEM32(esi + 0x10);
    MEM32(0x286BFC) = eax;
    goto loc_00220BED;

loc_00220BDF: ;
    eax = MEM32(eax + 0x10);

loc_00220BE2: ;
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(MEM32(eax + 0x10)) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp esi, MEM32(eax + 0x10) (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_00220BDF; /* jne: not equal / not zero */

loc_00220BE7: ;
    ecx = MEM32(esi + 0x10);
    MEM32(eax + 0x10) = ecx;

loc_00220BED: ;
    MEM32(esi + 0x10) = MEM32(esi + 0x10) & 0;
    PUSH32(esp, esi);
    ecx = 0x286B80;
    PUSH32(esp, 0x00220BFCu); sub_00220744(); /* call 0x00220744 */

loc_00220BFC: ;
    goto loc_00220C1E;

loc_00220BFE: ;
    _fa = (uint32_t)(MEM8(0x286B80)) & 0xFFu; _fb = (uint32_t)(0) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(0x286B80), 0 (8-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_00220C18; /* je: equal / zero */

loc_00220C07: ;
    _fa = (uint32_t)(MEM32(0x286C00)) & 0xFFFFFFFFu; _fb = (uint32_t)(esi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(0x286C00), esi (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_00220C18; /* jne: not equal / not zero */

loc_00220C0F: ;
    MEM8(0x286B81) = 1;
    goto loc_00220C1E;

loc_00220C18: ;
    PUSH32(esp, esi);
    PUSH32(esp, 0x00220C1Eu); sub_00220AAB(); /* call 0x00220AAB */

loc_00220C1E: ;
    POP32(esp, edi);
    POP32(esp, esi);
    esp += 8; return; /* ret 4 */

}

/**
 * sub_00220C23
 * Original: 0x00220C23 - 0x00220C68 (69 bytes, 30 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00220C23(void)
{
    uint32_t ebp;
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00220C23: ;
    PUSH32(esp, ebp);
    ebp = esp;
    g_ebp = ebp; /* publish frame for frameless callees */
    PUSH32(esp, ecx);
    _fa = (uint32_t)(MEM8(ecx)) & 0xFFu; _fb = (uint32_t)(5) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(ecx), 5 (8-bit) */
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    if (CMP_NE(_fa, _fb)) goto loc_00220C37; /* jne: not equal / not zero */

loc_00220C2E: ;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00220C33u); sub_00220776(); /* call 0x00220776 */

loc_00220C33: ;
    esi = eax;
    goto loc_00220C39;

loc_00220C37: ;
    esi = ecx;

loc_00220C39: ;
    ecx = esi;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00220C40u); sub_00220776(); /* call 0x00220776 */

loc_00220C40: ;
    edi = eax;
    _fa = (uint32_t)(edi) & 0xFFFFFFFFu; _fb = (uint32_t)(edi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test edi, edi (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00220C64; /* je: equal / zero */

loc_00220C46: ;
    SET_LO8(eax, MEM8(esi + 4));
    SET_LO8(eax, LO8(eax) & 0x7F);
    MEM8(ebp + -4) = LO8(eax);
    PUSH32(esp, MEM32(ebp + -4));
    ecx = edi;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00220C58u); sub_00220BAC(); /* call 0x00220BAC */

loc_00220C58: ;
    PUSH32(esp, 5);
    PUSH32(esp, MEM32(ebp + -4));
    ecx = edi;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00220C64u); sub_002207BB(); /* call 0x002207BB */

loc_00220C64: ;
    POP32(esp, edi);
    POP32(esp, esi);
    esp = ebp;
    POP32(esp, ebp); /* leave */
    esp += 4; return; /* ret */

}

/**
 * sub_00220C68
 * Original: 0x00220C68 - 0x00220CE9 (129 bytes, 49 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00220C68(void)
{
    uint32_t ebp;
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00220C68: ;
    PUSH32(esp, ebp);
    ebp = esp;
    g_ebp = ebp; /* publish frame for frameless callees */
    PUSH32(esp, ecx);
    PUSH32(esp, ebx);
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    SET_LO8(ebx, 0); /* xor self */
    edi = 0; /* xor self */
    _fa = (uint32_t)(MEM8(0x286B81)) & 0xFFu; _fb = (uint32_t)(0) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(0x286B81), 0 (8-bit) */
    esi = ecx;
    MEM8(ebp + -4) = LO8(ebx);
    MEM8(0x286B83) = 0xA;
    if (CMP_NE(_fa, _fb)) goto loc_00220CAA; /* jne: not equal / not zero */

loc_00220C88: ;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00220C8Du); sub_00220776(); /* call 0x00220776 */

loc_00220C8D: ;
    edi = eax;
    PUSH32(esp, esi);
    ecx = edi;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00220C97u); sub_00221A4E(); /* call 0x00221A4E */

loc_00220C97: ;
    SET_LO8(eax, MEM8(0x286B82));
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00220CAA; /* je: equal / zero */

loc_00220CA0: ;
    SET_LO8(ebx, LO8(eax));
    SET_LO8(eax, MEM8(esi + 4));
    SET_LO8(eax, LO8(eax) & 0x7F);
    MEM8(ebp + -4) = LO8(eax);

loc_00220CAA: ;
    SET_LO8(edx, MEM8(esi + 5));
    _fa = (uint32_t)(LO8(edx)) & 0xFFu; _fb = (uint32_t)(LO8(edx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(edx), LO8(edx) (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00220CB9; /* je: equal / zero */

loc_00220CB1: ;
    ecx = MEM32(esi + 0xC);
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00220CB9u); sub_0022094E(); /* call 0x0022094E */

loc_00220CB9: ;
    PUSH32(esp, esi);
    ecx = 0x286B80;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00220CC4u); sub_00220744(); /* call 0x00220744 */

loc_00220CC4: ;
    _fa = (uint32_t)(LO8(ebx)) & 0xFFu; _fb = (uint32_t)(LO8(ebx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(ebx), LO8(ebx) (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00220CD5; /* je: equal / zero */

loc_00220CC8: ;
    SET_LO8(ebx, LO8(ebx) - 1);
    ecx = edi;
    PUSH32(esp, ebx);
    PUSH32(esp, MEM32(ebp + -4));
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00220CD5u); sub_002207BB(); /* call 0x002207BB */

loc_00220CD5: ;
    PUSH32(esp, esi);
    PUSH32(esp, 0);
    MEM8(0x286B81) = 0;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00220CE4u); sub_00220AFD(); /* call 0x00220AFD */

loc_00220CE4: ;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebx);
    esp = ebp;
    POP32(esp, ebp); /* leave */
    esp += 4; return; /* ret */

}

/**
 * sub_00220CE9
 * Original: 0x00220CE9 - 0x00220CFC (19 bytes, 5 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00220CE9(void)
{

loc_00220CE9: ;
    eax = MEM32(esp + 4);
    PUSH32(esp, MEM32(esp + 8));
    ecx = MEM32(eax + -20);
    PUSH32(esp, 0x00220CF9u); sub_00220BAC(); /* call 0x00220BAC */

loc_00220CF9: ;
    esp += 12; return; /* ret 8 */

}

/**
 * sub_00220CFC
 * Original: 0x00220CFC - 0x00220D2F (51 bytes, 13 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00220CFC(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00220CFC: ;
    ecx = MEM32(esp + 8);
    eax = 0; /* xor self */
    _fa = (uint32_t)(MEM32(esp + 4)) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(esp + 4), eax (32-bit) */
    MEM8(0x286B83) = 9;
    if (CMP_GE(_fas, _fbs)) goto loc_00220D1A; /* jge: greater or equal (signed >=) */

loc_00220D0F: ;
    _fa = (uint32_t)(MEM8(0x286B81)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(0x286B81), LO8(eax) (8-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_00220D22; /* jne: not equal / not zero */

loc_00220D17: ;
    MEM8(ecx + 5) = LO8(eax);

loc_00220D1A: ;
    _fa = (uint32_t)(MEM8(0x286B81)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(0x286B81), LO8(eax) (8-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_00220D27; /* je: equal / zero */

loc_00220D22: ;
    MEM8(0x286B82) = LO8(eax);

loc_00220D27: ;
    PUSH32(esp, 0x00220D2Cu); sub_00220C68(); /* call 0x00220C68 */

loc_00220D2C: ;
    esp += 12; return; /* ret 8 */

}

/**
 * sub_00220D2F
 * Original: 0x00220D2F - 0x00220D9C (109 bytes, 36 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00220D2F(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00220D2F: ;
    _fa = (uint32_t)(MEM8(0x286B81)) & 0xFFu; _fb = (uint32_t)(0) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(0x286B81), 0 (8-bit) */
    PUSH32(esp, esi);
    MEM8(0x286B83) = 8;
    if (CMP_NE(_fa, _fb)) goto loc_00220D88; /* jne: not equal / not zero */

loc_00220D40: ;
    esi = MEM32(esp + 0xC);
    ecx = esi;
    PUSH32(esp, 0x00220D4Bu); sub_00220776(); /* call 0x00220776 */

loc_00220D4B: ;
    _fa = (uint32_t)(MEM8(eax)) & 0xFFu; _fb = (uint32_t)(0) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(eax), 0 (8-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_00220D71; /* jne: not equal / not zero */

loc_00220D50: ;
    eax = 0; /* xor self */
    SET_LO8(eax, MEM8(esi + 4));
    eax = eax & 0x7F;
    PUSH32(esp, eax);
    eax = MEM32(esi + 0xC);
    eax = eax + 0x18;
    PUSH32(esp, eax);
    PUSH32(esp, 0x00220D65u); sub_00222A55(); /* call 0x00222A55 */

loc_00220D65: ;
    PUSH32(esp, esi);
    PUSH32(esp, 0);
    ecx = esi;
    PUSH32(esp, 0x00220D6Fu); sub_00220CFC(); /* call 0x00220CFC */

loc_00220D6F: ;
    goto loc_00220D98;

loc_00220D71: ;
    ecx = 0; /* xor self */
    SET_LO8(ecx, MEM8(esi + 4));
    PUSH32(esp, 1);
    PUSH32(esp, esi);
    ecx = ecx & 0xFFFFFF7Fu;
    PUSH32(esp, ecx);
    PUSH32(esp, eax);
    PUSH32(esp, 0x00220D86u); sub_00221FFE(); /* call 0x00221FFE */

loc_00220D86: ;
    goto loc_00220D98;

loc_00220D88: ;
    ecx = MEM32(esp + 0xC);
    MEM8(0x286B82) = 0;
    PUSH32(esp, 0x00220D98u); sub_00220C68(); /* call 0x00220C68 */

loc_00220D98: ;
    POP32(esp, esi);
    esp += 12; return; /* ret 8 */

}

/**
 * sub_00220D9C
 * Original: 0x00220D9C - 0x00220E01 (101 bytes, 22 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00220D9C(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00220D9C: ;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 0x286BD0);
    { uint32_t _icall_target = MEM32(0x225B58); PUSH32(esp, 0x00220DA7u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00220DA7: ;
    eax = MEM32(esp + 4);
    MEM8(0x286B83) = 3;
    _fa = (uint32_t)(MEM32(eax + 4)) & 0xFFFFFFFFu; _fb = (uint32_t)(0) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(eax + 4), 0 (32-bit) */
    if (CMP_L(_fas, _fbs)) goto loc_00220DCB; /* jl: less (signed <) */

loc_00220DB8: ;
    _fa = (uint32_t)(MEM8(0x286B81)) & 0xFFu; _fb = (uint32_t)(0) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(0x286B81), 0 (8-bit) */
    MEM32(0x286B8C) = 0x2208F2;
    if (CMP_EQ(_fa, _fb)) goto loc_00220DD5; /* je: equal / zero */

loc_00220DCB: ;
    MEM32(0x286B8C) = 0x220D2F;

loc_00220DD5: ;
    PUSH32(esp, esi);
    esi = MEM32(esp + 0xC);
    MEM8(0x286B84) = 0x1C;
    MEM8(0x286B85) = 0x43;
    eax = MEM32(esi + 0xC);
    PUSH32(esp, 0x286B84);
    eax = eax + 0x18;
    PUSH32(esp, eax);
    PUSH32(esp, 0x00220DF9u); sub_00223032(); /* call 0x00223032 */

loc_00220DF9: ;
    MEM32(esi + 8) = MEM32(esi + 8) & 0;
    POP32(esp, esi);
    esp += 12; return; /* ret 8 */

}

/**
 * sub_00220E01
 * Original: 0x00220E01 - 0x00220F8D (396 bytes, 126 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00220E01(void)
{
    uint32_t ebp;
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00220E01: ;
    PUSH32(esp, ebp);
    ebp = esp;
    g_ebp = ebp; /* publish frame for frameless callees */
    esp = esp - 0xC;
    PUSH32(esp, ebx);
    PUSH32(esp, esi);
    esi = ecx;
    ecx = 0; /* xor self */
    ecx++;
    ebx = 0; /* xor self */
    _fa = (uint32_t)(MEM32(ebp + 8)) & 0xFFFFFFFFu; _fb = (uint32_t)(ebx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(ebp + 8), ebx (32-bit) */
    PUSH32(esp, edi);
    MEM32(ebp + -4) = ecx;
    MEM8(0x286B83) = 7;
    if (CMP_GE(_fas, _fbs)) goto loc_00220E31; /* jge: greater or equal (signed >=) */

loc_00220E20: ;
    _fa = (uint32_t)(MEM32(ebp + 8)) & 0xFFFFFFFFu; _fb = (uint32_t)(0x80000400u) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(ebp + 8), 0x80000400u (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_00220E2C; /* jne: not equal / not zero */

loc_00220E29: ;
    MEM32(ebp + -4) = ebx;

loc_00220E2C: ;
    MEM32(esi + 0x10) = ebx;
    goto loc_00220E52;

loc_00220E31: ;
    SET_LO8(eax, MEM8(esi + 7));
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(0xFF) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp LO8(eax), 0xFF (8-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_00220E52; /* je: equal / zero */

loc_00220E38: ;
    edx = MEM32(esi + 0x10);
    edx = MEM32(edx + 0x14);
    eax = ZX8(LO8(eax));
    eax = MEM32(edx + eax * 4);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(ebx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, ebx (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_00220E52; /* je: equal / zero */

loc_00220E48: ;
    PUSH32(esp, ecx);
    PUSH32(esp, MEM32(esi + 0x14));
    PUSH32(esp, eax);
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00220E52u); sub_0022153B(); /* call 0x0022153B */

loc_00220E52: ;
    SET_LO8(eax, MEM8(esi));
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(2) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp LO8(eax), 2 (8-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_00220F67; /* je: equal / zero */

loc_00220E5C: ;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp LO8(eax), 1 (8-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_00220F67; /* je: equal / zero */

loc_00220E64: ;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(5) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp LO8(eax), 5 (8-bit) */
    ecx = MEM32(esi + 8);
    edi = esi;
    MEM32(ebp + -12) = ecx;
    MEM32(esi + 8) = ebx;
    MEM32(ebp + -8) = 0x220AFD;
    if (CMP_NE(_fa, _fb)) goto loc_00220F18; /* jne: not equal / not zero */

loc_00220E7E: ;
    ecx = esi;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00220E85u); sub_002207A4(); /* call 0x002207A4 */

loc_00220E85: ;
    ecx = esi;
    ebx = eax;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00220E8Eu); sub_00220776(); /* call 0x00220776 */

loc_00220E8E: ;
    _fa = (uint32_t)(MEM8(0x286B81)) & 0xFFu; _fb = (uint32_t)(0) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(0x286B81), 0 (8-bit) */
    edi = eax;
    if (CMP_NE(_fa, _fb)) goto loc_00220F30; /* jne: not equal / not zero */

loc_00220E9D: ;
    _fa = (uint32_t)(MEM32(esi + 0x10)) & 0xFFFFFFFFu; _fb = (uint32_t)(0) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(esi + 0x10), 0 (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_00220ED2; /* jne: not equal / not zero */

loc_00220EA3: ;
    PUSH32(esp, esi);
    ecx = edi;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00220EABu); sub_00221A4E(); /* call 0x00221A4E */

loc_00220EAB: ;
    PUSH32(esp, esi);
    ecx = 0x286B80;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00220EB6u); sub_00220744(); /* call 0x00220744 */

loc_00220EB6: ;
    ecx = edi;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00220EBDu); sub_0022078D(); /* call 0x0022078D */

loc_00220EBD: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_00220ED2; /* jne: not equal / not zero */

loc_00220EC1: ;
    PUSH32(esp, edi);
    MEM8(0x286B82) = LO8(eax);
    PUSH32(esp, eax);

loc_00220EC8: ;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00220ECDu); sub_00220D2F(); /* call 0x00220D2F */

loc_00220ECD: ;
    goto loc_00220F86;

loc_00220ED2: ;
    _fa = (uint32_t)(ebx) & 0xFFFFFFFFu; _fb = (uint32_t)(ebx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ebx, ebx (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00220F30; /* je: equal / zero */

loc_00220ED6: ;
    eax = MEM32(0x286C5C);

loc_00220EDB: ;
    ecx = ZX8(MEM8(eax));
    eax = eax + ecx;
    _fa = (uint32_t)(MEM8(eax + 1)) & 0xFFu; _fb = (uint32_t)(4) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(eax + 1), 4 (8-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_00220EDB; /* jne: not equal / not zero */

loc_00220EE6: ;
    MEM32(0x286C5C) = eax;
    SET_LO8(eax, MEM8(eax + 2));
    MEM8(ebx + 2) = LO8(eax);
    eax = MEM32(0x286C5C);
    SET_LO8(ecx, MEM8(eax + 5));
    MEM8(ebp + 9) = LO8(ecx);
    SET_LO8(ecx, MEM8(eax + 6));
    SET_LO8(eax, MEM8(eax + 7));
    MEM8(ebp + 0xA) = LO8(ecx);
    MEM8(ebp + 0xB) = LO8(eax);
    MEM8(ebp + 8) = 0x82;
    PUSH32(esp, MEM32(ebp + 8));
    ecx = ebx;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00220F16u); sub_00220F8D(); /* call 0x00220F8D */

loc_00220F16: ;
    goto loc_00220F86;

loc_00220F18: ;
    _fa = (uint32_t)(MEM32(ebp + 8)) & 0xFFFFFFFFu; _fb = (uint32_t)(ebx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(ebp + 8), ebx (32-bit) */
    if (CMP_GE(_fas, _fbs)) goto loc_00220F30; /* jge: greater or equal (signed >=) */

loc_00220F1D: ;
    _fa = (uint32_t)(MEM32(ebp + -4)) & 0xFFFFFFFFu; _fb = (uint32_t)(ebx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(ebp + -4), ebx (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_00220F29; /* jne: not equal / not zero */

loc_00220F22: ;
    MEM8(0x286B82) = 0;

loc_00220F29: ;
    MEM32(ebp + -8) = 0x220D2F;

loc_00220F30: ;
    eax = MEM32(ebp + -8);
    MEM32(0x286B8C) = eax;
    eax = MEM32(ebp + -12);
    MEM32(0x286B94) = eax;
    MEM8(0x286B84) = 0x1C;
    MEM8(0x286B85) = 0x43;
    MEM32(0x286B90) = edi;
    eax = MEM32(edi + 0xC);
    PUSH32(esp, 0x286B84);
    eax = eax + 0x18;
    PUSH32(esp, eax);
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00220F65u); sub_00223032(); /* call 0x00223032 */

loc_00220F65: ;
    goto loc_00220F86;

loc_00220F67: ;
    _fa = (uint32_t)(MEM32(ebp + 8)) & 0xFFFFFFFFu; _fb = (uint32_t)(ebx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(ebp + 8), ebx (32-bit) */
    if (CMP_GE(_fas, _fbs)) goto loc_00220F7F; /* jge: greater or equal (signed >=) */

loc_00220F6C: ;
    _fa = (uint32_t)(MEM32(ebp + -4)) & 0xFFFFFFFFu; _fb = (uint32_t)(ebx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(ebp + -4), ebx (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_00220F78; /* jne: not equal / not zero */

loc_00220F71: ;
    MEM8(0x286B82) = 0;

loc_00220F78: ;
    PUSH32(esp, esi);
    PUSH32(esp, ebx);
    goto loc_00220EC8;

loc_00220F7F: ;
    PUSH32(esp, esi);
    PUSH32(esp, ebx);
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00220F86u); sub_00220AFD(); /* call 0x00220AFD */

loc_00220F86: ;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebx);
    esp = ebp;
    POP32(esp, ebp); /* leave */
    esp += 8; return; /* ret 4 */

}

/**
 * sub_00220F8D
 * Original: 0x00220F8D - 0x00220FC1 (52 bytes, 18 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00220F8D(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00220F8D: ;
    PUSH32(esp, esi);
    esi = ecx;
    PUSH32(esp, 0x00220F95u); sub_00221C4B(); /* call 0x00221C4B */

loc_00220F95: ;
    _fa = (uint32_t)(MEM32(esi + 0x14)) & 0xFFFFFFFFu; _fb = (uint32_t)(0x20) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(esi + 0x14), 0x20 (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_00220FB1; /* je: equal / zero */

loc_00220F9B: ;
    PUSH32(esp, MEM32(esp + 8));
    PUSH32(esp, 0x00220FA4u); sub_00223201(); /* call 0x00223201 */

loc_00220FA4: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    MEM32(esi + 0x10) = eax;
    if (TEST_Z(_fa, _fb)) goto loc_00220FB1; /* je: equal / zero */

loc_00220FAB: ;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, esi);
    { uint32_t _icall_target = MEM32(eax + 8); PUSH32(esp, 0x00220FAFu); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00220FAF: ;
    goto loc_00220FBD;

loc_00220FB1: ;
    ecx = esi;
    PUSH32(esp, 0x80000400u);
    PUSH32(esp, 0x00220FBDu); sub_00220E01(); /* call 0x00220E01 */

loc_00220FBD: ;
    POP32(esp, esi);
    esp += 8; return; /* ret 4 */

}

/**
 * sub_0022109C
 * Original: 0x0022109C - 0x002211E3 (327 bytes, 96 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0022109C(void)
{
    uint32_t ebp;
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_0022109C: ;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, ebp);
    ebp = esp;
    g_ebp = ebp; /* publish frame for frameless callees */
    PUSH32(esp, ebx);
    PUSH32(esp, esi);
    PUSH32(esp, 0x286BD0);
    { uint32_t _icall_target = MEM32(0x225B58); PUSH32(esp, 0x002210ACu); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_002210AC: ;
    ecx = MEM32(ebp + 8);
    ebx = 0; /* xor self */
    MEM8(0x286B83) = 6;
    _fa = (uint32_t)(MEM32(ecx + 4)) & 0xFFFFFFFFu; _fb = (uint32_t)(ebx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(ecx + 4), ebx (32-bit) */
    if (CMP_L(_fas, _fbs)) goto loc_002211D4; /* jl: less (signed <) */

loc_002210C1: ;
    _fa = (uint32_t)(MEM8(0x286B81)) & 0xFFu; _fb = (uint32_t)(LO8(ebx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(0x286B81), LO8(ebx) (8-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_002211D4; /* jne: not equal / not zero */

loc_002210CD: ;
    esi = MEM32(ebp + 0xC);
    MEM32(esi + 0x18) = ebx;
    eax = 0x286C0C;

loc_002210D8: ;
    edx = ZX8(MEM8(eax));
    eax = eax + edx;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0x286C5C) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0x286C5C (32-bit) */
    if (CMP_AE(_fa, _fb)) goto loc_002211C3; /* jae: above or equal (unsigned >=) */

loc_002210E8: ;
    _fa = (uint32_t)(MEM8(eax)) & 0xFFu; _fb = (uint32_t)(0) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(eax), 0 (8-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_002211C3; /* je: equal / zero */

loc_002210F1: ;
    _fa = (uint32_t)(MEM8(eax + 1)) & 0xFFu; _fb = (uint32_t)(4) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(eax + 1), 4 (8-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_002210D8; /* jne: not equal / not zero */

loc_002210F7: ;
    _fa = (uint32_t)(MEM8(0x286C10)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(0x286C10), 1 (8-bit) */
    MEM32(0x286C5C) = eax;
    if (CMP_EQ(_fa, _fb)) goto loc_0022118E; /* je: equal / zero */

loc_00221109: ;
    _fa = (uint32_t)(MEM8(0x286BFB)) & 0xFFu; _fb = (uint32_t)(0) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(0x286BFB), 0 (8-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_0022118E; /* je: equal / zero */

loc_00221112: ;
    MEM8(esi) = 4;
    MEM8(esi + 2) = 0x80;
    _fa = (uint32_t)(MEM8(0x286C10)) & 0xFFu; _fb = (uint32_t)(0) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(0x286C10), 0 (8-bit) */
    if (CMP_BE(_fa, _fb)) goto loc_0022117F; /* jbe: below or equal (unsigned <=) */

loc_00221122: ;
    eax = ZX8(MEM8(0x286BFB));
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(ebx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, ebx (32-bit) */
    if (CMP_BE(_fa, _fb)) goto loc_0022117F; /* jbe: below or equal (unsigned <=) */

loc_0022112D: ;
    ecx = 0x286B80;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00221137u); sub_002206F4(); /* call 0x002206F4 */

loc_00221137: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0022117F; /* je: equal / zero */

loc_0022113B: ;
    MEM8(eax) = 5;
    SET_LO8(ecx, MEM8(esi + 4));
    SET_LO8(ecx, LO8(ecx) & 0x80);
    SET_LO8(edx, LO8(ebx));
    SET_LO8(edx, LO8(edx) + 1);
    SET_LO8(ecx, LO8(ecx) | LO8(edx));
    MEM8(eax + 4) = LO8(ecx);
    SET_LO8(ecx, MEM8(esi + 5));
    MEM8(eax + 5) = LO8(ecx);
    ecx = MEM32(esi + 8);
    MEM32(eax + 8) = ecx;
    ecx = MEM32(esi + 0xC);
    MEM32(eax + 0xC) = ecx;
    SET_LO8(ecx, MEM8(esi + 6));
    MEM8(eax + 6) = LO8(ecx);
    ecx = MEM32(esi + 0x18);
    MEM32(eax + 0x18) = ecx;
    PUSH32(esp, eax);
    ecx = esi;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00221173u); sub_00221A06(); /* call 0x00221A06 */

loc_00221173: ;
    eax = ZX8(MEM8(0x286C10));
    ebx++;
    _fa = (uint32_t)(ebx) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp ebx, eax (32-bit) */
    if (CMP_B(_fa, _fb)) goto loc_00221122; /* jb: below (unsigned <) */

loc_0022117F: ;
    MEM32(esi + 8) = MEM32(esi + 8) & 0;
    ecx = esi;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x0022118Au); sub_0022078D(); /* call 0x0022078D */

loc_0022118A: ;
    esi = eax;
    goto loc_00221191;

loc_0022118E: ;
    MEM8(esi) = 3;

loc_00221191: ;
    eax = MEM32(0x286C5C);
    SET_LO8(eax, MEM8(eax + 2));
    MEM8(esi + 2) = LO8(eax);
    eax = MEM32(0x286C5C);
    SET_LO8(ecx, MEM8(eax + 5));
    MEM8(ebp + 0xD) = LO8(ecx);
    SET_LO8(ecx, MEM8(eax + 6));
    SET_LO8(eax, MEM8(eax + 7));
    MEM8(ebp + 0xE) = LO8(ecx);
    MEM8(ebp + 0xF) = LO8(eax);
    MEM8(ebp + 0xC) = 0x82;
    PUSH32(esp, MEM32(ebp + 0xC));
    ecx = esi;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x002211C1u); sub_00220F8D(); /* call 0x00220F8D */

loc_002211C1: ;
    goto loc_002211DD;

loc_002211C3: ;
    MEM8(0x286B82) = 0;
    MEM32(ecx + 4) = 0x80000400u;
    PUSH32(esp, esi);
    goto loc_002211D7;

loc_002211D4: ;
    PUSH32(esp, MEM32(ebp + 0xC));

loc_002211D7: ;
    PUSH32(esp, ecx);
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x002211DDu); sub_00220D9C(); /* call 0x00220D9C */

loc_002211DD: ;
    POP32(esp, esi);
    POP32(esp, ebx);
    POP32(esp, ebp);
    esp += 12; return; /* ret 8 */

}

/**
 * sub_002211E3
 * Original: 0x002211E3 - 0x002212E3 (256 bytes, 60 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_002211E3(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_002211E3: ;
    PUSH32(esp, ebx);
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    esi = ecx;
    edi = MEM32(esi + 0xC);
    ebx = 0; /* xor self */
    edi = edi + 0x18;
    _fa = (uint32_t)(MEM8(0x286B81)) & 0xFFu; _fb = (uint32_t)(LO8(ebx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(0x286B81), LO8(ebx) (8-bit) */
    MEM8(0x286B83) = 1;
    if (CMP_EQ(_fa, _fb)) goto loc_0022120B; /* je: equal / zero */

loc_002211FF: ;
    PUSH32(esp, esi);
    PUSH32(esp, ebx);
    PUSH32(esp, 0x00221206u); sub_00220D2F(); /* call 0x00220D2F */

loc_00221206: ;
    goto loc_002212DF;

loc_0022120B: ;
    MEM32(esi + 0x18) = ebx;
    PUSH32(esp, ebp);
    MEM8(0x286B84) = 0x20;
    MEM8(0x286B85) = 2;
    MEM32(0x286B8C) = ebx;
    MEM8(0x286B99) = LO8(ebx);
    MEM8(0x286B9A) = LO8(ebx);
    MEM8(0x286B9B) = LO8(ebx);
    MEM16(0x286BA0) = 8;
    SET_LO8(eax, MEM8(esi + 4));
    ebp = 0x286B84;
    PUSH32(esp, ebp);
    SET_LO8(eax, LO8(eax) >> 7);
    PUSH32(esp, edi);
    MEM8(0x286BA2) = LO8(eax);
    MEM8(0x286B98) = LO8(ebx);
    PUSH32(esp, 0x0022125Bu); sub_00223032(); /* call 0x00223032 */

loc_0022125B: ;
    eax = MEM32(0x286B94);
    MEM32(esi + 8) = eax;
    MEM8(0x286B84) = 0x30;
    MEM8(0x286B85) = 0x40;
    MEM32(0x286B8C) = 0x220FC1;
    MEM32(0x286B90) = esi;
    eax = MEM32(esi + 8);
    PUSH32(esp, 8);
    MEM32(0x286B94) = eax;
    POP32(esp, eax);
    MEM32(0x286B9C) = 0x286C04;
    MEM32(0x286B98) = eax;
    MEM8(0x286BA0) = 2;
    MEM8(0x286BA1) = LO8(ebx);
    MEM8(0x286BA2) = LO8(ebx);
    MEM8(0x286BAC) = 0x80;
    MEM8(0x286BAD) = 6;
    MEM16(0x286BAE) = 0x100;
    MEM16(0x286BB0) = LO16(ebx);
    MEM16(0x286BB2) = LO16(eax);
    PUSH32(esp, 0x002212D7u); sub_0022087F(); /* call 0x0022087F */

loc_002212D7: ;
    PUSH32(esp, ebp);
    PUSH32(esp, edi);
    PUSH32(esp, 0x002212DEu); sub_00223032(); /* call 0x00223032 */

loc_002212DE: ;
    POP32(esp, ebp);

loc_002212DF: ;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebx);
    esp += 4; return; /* ret */

}

/**
 * sub_002212E3
 * Original: 0x002212E3 - 0x0022139C (185 bytes, 43 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_002212E3(void)
{
    uint32_t ebp;
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_002212E3: ;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, ebp);
    ebp = esp;
    g_ebp = ebp; /* publish frame for frameless callees */
    PUSH32(esp, 0x286BD0);
    { uint32_t _icall_target = MEM32(0x225B58); PUSH32(esp, 0x002212F1u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_002212F1: ;
    eax = MEM32(ebp + 8);
    edx = 0; /* xor self */
    MEM8(0x286B83) = 5;
    _fa = (uint32_t)(MEM32(eax + 4)) & 0xFFFFFFFFu; _fb = (uint32_t)(edx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(eax + 4), edx (32-bit) */
    if (CMP_L(_fas, _fbs)) goto loc_00221324; /* jl: less (signed <) */

loc_00221302: ;
    _fa = (uint32_t)(MEM8(0x286B81)) & 0xFFu; _fb = (uint32_t)(LO8(edx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(0x286B81), LO8(edx) (8-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_00221324; /* jne: not equal / not zero */

loc_0022130A: ;
    SET_LO16(ecx, MEM16(0x286C0E));
    _fa = (uint32_t)(LO16(ecx)) & 0xFFFFu; _fb = (uint32_t)(0x50) & 0xFFFFu;
    _fas = (int32_t)(int16_t)(_fa); _fbs = (int32_t)(int16_t)(_fb); /* cmp LO16(ecx), 0x50 (16-bit) */
    if (CMP_BE(_fa, _fb)) goto loc_00221331; /* jbe: below or equal (unsigned <=) */

loc_00221317: ;
    MEM8(0x286B82) = LO8(edx);
    MEM32(eax + 4) = 0x80000400u;

loc_00221324: ;
    PUSH32(esp, MEM32(ebp + 0xC));
    PUSH32(esp, eax);
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x0022132Du); sub_00220D9C(); /* call 0x00220D9C */

loc_0022132D: ;
    POP32(esp, ebp);
    esp += 12; return; /* ret 8 */

loc_00221331: ;
    ecx = ZX16(LO16(ecx));
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(MEM32(eax + 0x14)) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp ecx, MEM32(eax + 0x14) (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_00221342; /* je: equal / zero */

loc_00221339: ;
    MEM32(eax + 4) = 0x80000000u;
    goto loc_00221324;

loc_00221342: ;
    SET_LO16(eax, ZX8(MEM8(0x286C11)));
    MEM32(0x286B8C) = 0x22109C;
    MEM32(0x286B9C) = edx;
    MEM32(0x286B98) = edx;
    MEM8(0x286BAC) = LO8(edx);
    MEM8(0x286BAD) = 9;
    MEM16(0x286BAE) = LO16(eax);
    MEM16(0x286BB0) = LO16(edx);
    MEM16(0x286BB2) = LO16(edx);
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00221386u); sub_0022087F(); /* call 0x0022087F */

loc_00221386: ;
    eax = MEM32(ebp + 0xC);
    eax = MEM32(eax + 0xC);
    PUSH32(esp, 0x286B84);
    eax = eax + 0x18;
    PUSH32(esp, eax);
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x0022139Au); sub_00223032(); /* call 0x00223032 */

loc_0022139A: ;
    goto loc_0022132D;

}

/**
 * sub_0022139C
 * Original: 0x0022139C - 0x002214E7 (331 bytes, 83 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0022139C(void)
{
    uint32_t ebp;
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_0022139C: ;
    PUSH32(esp, ebp);
    ebp = esp;
    g_ebp = ebp; /* publish frame for frameless callees */
    PUSH32(esp, ecx);
    PUSH32(esp, ebx);
    ebx = 0; /* xor self */
    _fa = (uint32_t)(MEM8(0x286B81)) & 0xFFu; _fb = (uint32_t)(LO8(ebx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(0x286B81), LO8(ebx) (8-bit) */
    PUSH32(esp, esi);
    esi = edx;
    MEM8(0x286B83) = 4;
    if (CMP_EQ(_fa, _fb)) goto loc_002213C1; /* je: equal / zero */

loc_002213B5: ;
    PUSH32(esp, esi);
    PUSH32(esp, ebx);
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x002213BCu); sub_00220D2F(); /* call 0x00220D2F */

loc_002213BC: ;
    goto loc_002214E3;

loc_002213C1: ;
    SET_LO8(eax, MEM8(0x286C08));
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(ebx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp LO8(eax), LO8(ebx) (8-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_002213FE; /* je: equal / zero */

loc_002213CA: ;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(9) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp LO8(eax), 9 (8-bit) */
    SET_LO8(eax, (CMP_NE(_fa, _fb)) ? 1 : 0); /* setne */
    SET_LO8(eax, LO8(eax) + 1);
    MEM8(esi) = LO8(eax);
    SET_LO8(eax, MEM8(0x286C08));
    MEM8(ebp + -3) = LO8(eax);
    SET_LO8(eax, MEM8(0x286C09));
    MEM8(ebp + -2) = LO8(eax);
    SET_LO8(eax, MEM8(0x286C0A));
    MEM8(ebp + -1) = LO8(eax);
    MEM8(ebp + -4) = 0x81;
    PUSH32(esp, MEM32(ebp + -4));
    ecx = esi;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x002213F9u); sub_00220F8D(); /* call 0x00220F8D */

loc_002213F9: ;
    goto loc_002214E3;

loc_002213FE: ;
    SET_LO16(eax, ZX8(MEM8(0x286C0B)));
    MEM16(0x286BA0) = LO16(eax);
    MEM8(0x286B84) = 0x20;
    MEM8(0x286B85) = 2;
    MEM32(0x286B8C) = ebx;
    MEM8(0x286B99) = LO8(ebx);
    MEM8(0x286B9A) = LO8(ebx);
    MEM8(0x286B9B) = LO8(ebx);
    SET_LO8(eax, MEM8(esi + 4));
    SET_LO8(eax, LO8(eax) >> 7);
    MEM8(0x286BA2) = LO8(eax);
    SET_LO8(eax, MEM8(esi + 5));
    PUSH32(esp, edi);
    MEM8(0x286B98) = LO8(eax);
    eax = MEM32(esi + 0xC);
    edi = 0x286B84;
    PUSH32(esp, edi);
    eax = eax + 0x18;
    PUSH32(esp, eax);
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00221458u); sub_00223032(); /* call 0x00223032 */

loc_00221458: ;
    eax = MEM32(0x286B94);
    MEM32(esi + 8) = eax;
    MEM8(0x286B84) = 0x30;
    MEM8(0x286B85) = 0x40;
    MEM32(0x286B8C) = 0x2212E3;
    MEM32(0x286B90) = esi;
    eax = MEM32(esi + 8);
    PUSH32(esp, 0x50);
    MEM32(0x286B94) = eax;
    POP32(esp, eax);
    MEM32(0x286B9C) = 0x286C0C;
    MEM32(0x286B98) = eax;
    MEM8(0x286BA0) = 2;
    MEM8(0x286BA1) = 1;
    MEM8(0x286BA2) = LO8(ebx);
    MEM8(0x286BAC) = 0x80;
    MEM8(0x286BAD) = 6;
    MEM16(0x286BAE) = 0x200;
    MEM16(0x286BB0) = LO16(ebx);
    MEM16(0x286BB2) = LO16(eax);
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x002214D5u); sub_0022087F(); /* call 0x0022087F */

loc_002214D5: ;
    eax = MEM32(esi + 0xC);
    PUSH32(esp, edi);
    eax = eax + 0x18;
    PUSH32(esp, eax);
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x002214E2u); sub_00223032(); /* call 0x00223032 */

loc_002214E2: ;
    POP32(esp, edi);

loc_002214E3: ;
    POP32(esp, esi);
    POP32(esp, ebx);
    esp = ebp;
    POP32(esp, ebp); /* leave */
    esp += 4; return; /* ret */

}

/**
 * sub_0022153B
 * Original: 0x0022153B - 0x0022155D (34 bytes, 13 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0022153B(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_0022153B: ;
    ecx = MEM32(esp + 8);
    eax = 0; /* xor self */
    eax++;
    eax = eax << LO8(ecx);
    ecx = MEM32(esp + 4);
    MEM32(ecx + 4) = MEM32(ecx + 4) | eax;
    _fa = (uint32_t)(MEM8(esp + 0xC)) & 0xFFu; _fb = (uint32_t)(0) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(esp + 0xC), 0 (8-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_00221556; /* je: equal / zero */

loc_00221552: ;
    MEM32(ecx) = MEM32(ecx) | eax;
    goto loc_0022155A;

loc_00221556: ;
    eax = ~eax;
    MEM32(ecx) = MEM32(ecx) & eax;

loc_0022155A: ;
    esp += 16; return; /* ret 12 */

}

/**
 * sub_0022155D
 * Original: 0x0022155D - 0x00221562 (5 bytes, 1 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0022155D(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_0022155D: ;
    g_seh_ebp = ebp; sub_0021FDC0(); return; /* tail jmp 0x0021FDC0 */

}

/**
 * sub_00221562
 * Original: 0x00221562 - 0x00221584 (34 bytes, 11 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00221562(void)
{
    extern void dah_xget_devices_bridge(void);
    dah_xget_devices_bridge();
}

/**
 * sub_00221584
 * Original: 0x00221584 - 0x002215F1 (109 bytes, 47 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00221584(void)
{
    extern void dah_xget_device_changes_bridge(void);
    dah_xget_device_changes_bridge();
    return;

    uint32_t ebp;
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    int _cf = 0; /* carry flag */

loc_00221584: ;
    PUSH32(esp, ebp);
    ebp = esp;
    g_ebp = ebp; /* publish frame for frameless callees */
    PUSH32(esp, esi);
    esi = MEM32(ebp + 8);
    eax = 0; /* xor self */
    _fa = (uint32_t)(MEM32(esi + 4)) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(esi + 4), eax (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_0022159E; /* jne: not equal / not zero */

loc_00221592: ;
    ecx = MEM32(ebp + 0xC);
    MEM32(ecx) = eax;
    ecx = MEM32(ebp + 0x10);
    MEM32(ecx) = eax;
    goto loc_002215EC;

loc_0022159E: ;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, ebx);
    PUSH32(esp, edi);
    { uint32_t _icall_target = MEM32(0x225B30); PUSH32(esp, 0x002215A6u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_002215A6: ;
    ecx = MEM32(esi + 8);
    ebx = MEM32(ebp + 0xC);
    ecx = ~ecx;
    _cf = 0; /* logical op clears CF */
    ecx = ecx & MEM32(esi);
    MEM32(ebx) = ecx;
    edx = MEM32(esi);
    ecx = MEM32(ebp + 0x10);
    edx = ~edx;
    _cf = 0; /* logical op clears CF */
    edx = edx & MEM32(esi + 8);
    MEM32(ecx) = edx;
    edi = MEM32(esi + 4);
    _cf = 0; /* logical op clears CF */
    edi = edi & MEM32(esi + 8);
    _cf = 0; /* logical op clears CF */
    edi = edi & MEM32(esi);
    _cf = 0; /* logical op clears CF */
    edx = edx | edi;
    MEM32(ecx) = edx;
    _cf = 0; /* logical op clears CF */
    MEM32(ebx) = MEM32(ebx) | edi;
    ecx = MEM32(esi);
    _cf = 0; /* logical op clears CF */
    MEM32(esi + 4) = MEM32(esi + 4) & 0;
    MEM32(esi + 8) = ecx;
    SET_LO8(ecx, LO8(eax));
    { uint32_t _icall_esp = g_esp;
    { uint32_t _icall_target = MEM32(0x225B2C); PUSH32(esp, 0x002215DDu); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_002215DD: ;
    eax = MEM32(ebx);
    ecx = MEM32(ebp + 0x10);
    _cf = 0; /* logical op clears CF */
    eax = eax | MEM32(ecx);
    POP32(esp, edi);
    _cf = (int)((eax) != 0);
    eax = (uint32_t)(-(int32_t)eax);
    eax = _cf ? 0xFFFFFFFF : 0; /* sbb self (CF extend) */
    _cf = (int)((eax) != 0);
    eax = (uint32_t)(-(int32_t)eax);
    POP32(esp, ebx);

loc_002215EC: ;
    POP32(esp, esi);
    POP32(esp, ebp);
    esp += 16; return; /* ret 12 */

}

/**
 * sub_002215F1
 * Original: 0x002215F1 - 0x00221628 (55 bytes, 27 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_002215F1(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_002215F1: ;
    PUSH32(esp, ebx);
    PUSH32(esp, esi);
    eax = 0x21F904;
    PUSH32(esp, edi);
    edi = eax;
    esi = 0x21F90C;
    SET_LO8(ebx, 0); /* xor self */
    _fa = (uint32_t)(edi) & 0xFFFFFFFFu; _fb = (uint32_t)(esi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edi, esi (32-bit) */
    MEM8(edx) = 0;
    if (CMP_AE(_fa, _fb)) goto loc_0022161C; /* jae: above or equal (unsigned >=) */

loc_00221609: ;
    edi = MEM32(eax);
    _fa = (uint32_t)(edi) & 0xFFFFFFFFu; _fb = (uint32_t)(edi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test edi, edi (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00221615; /* je: equal / zero */

loc_0022160F: ;
    _fa = (uint32_t)(MEM8(edi)) & 0xFFu; _fb = (uint32_t)(LO8(ecx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(edi), LO8(ecx) (8-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_00221622; /* je: equal / zero */

loc_00221613: ;
    SET_LO8(ebx, LO8(ebx) + 1);

loc_00221615: ;
    eax = eax + 4;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(esi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, esi (32-bit) */
    if (CMP_B(_fa, _fb)) goto loc_00221609; /* jb: below (unsigned <) */

loc_0022161C: ;
    eax = 0; /* xor self */

loc_0022161E: ;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebx);
    esp += 4; return; /* ret */

loc_00221622: ;
    MEM8(edx) = LO8(ebx);
    eax = MEM32(eax);
    goto loc_0022161E;

}

/**
 * sub_00221628
 * Original: 0x00221628 - 0x00221653 (43 bytes, 20 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00221628(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00221628: ;
    eax = 0x21F904;
    PUSH32(esp, esi);
    edx = eax;
    esi = 0x21F90C;
    _fa = (uint32_t)(edx) & 0xFFFFFFFFu; _fb = (uint32_t)(esi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edx, esi (32-bit) */
    if (CMP_AE(_fa, _fb)) goto loc_0022164B; /* jae: above or equal (unsigned >=) */

loc_00221639: ;
    edx = MEM32(eax);
    _fa = (uint32_t)(edx) & 0xFFFFFFFFu; _fb = (uint32_t)(edx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test edx, edx (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00221644; /* je: equal / zero */

loc_0022163F: ;
    _fa = (uint32_t)(MEM32(edx + 4)) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(edx + 4), ecx (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_0022164F; /* je: equal / zero */

loc_00221644: ;
    eax = eax + 4;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(esi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, esi (32-bit) */
    if (CMP_B(_fa, _fb)) goto loc_00221639; /* jb: below (unsigned <) */

loc_0022164B: ;
    eax = 0; /* xor self */
    POP32(esp, esi);
    esp += 4; return; /* ret */

loc_0022164F: ;
    eax = MEM32(eax);
    POP32(esp, esi);
    esp += 4; return; /* ret */

}

/**
 * sub_00221653
 * Original: 0x00221653 - 0x002216A9 (86 bytes, 34 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00221653(void)
{
    extern void dah_xinput_open_bridge(void);
    dah_xinput_open_bridge();
    return;

    uint32_t ebp;
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00221653: ;
    PUSH32(esp, ebp);
    ebp = esp;
    g_ebp = ebp; /* publish frame for frameless callees */
    PUSH32(esp, ecx);
    ecx = MEM32(ebp + 8);
    MEM32(ebp + -4) = MEM32(ebp + -4) & 0;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00221663u); sub_00221628(); /* call 0x00221628 */

loc_00221663: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_00221672; /* jne: not equal / not zero */

loc_00221667: ;
    PUSH32(esp, 0x57);
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x0022166Eu); sub_000B2855(); /* call 0x000B2855 */

loc_0022166E: ;
    eax = 0; /* xor self */
    goto loc_002216A5;

loc_00221672: ;
    PUSH32(esp, esi);
    esi = MEM32(ebp + 0x14);
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(esi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test esi, esi (32-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_0022167D; /* jne: not equal / not zero */

loc_0022167A: ;
    esi = MEM32(eax + 0x10);

loc_0022167D: ;
    _fa = (uint32_t)(MEM32(ebp + 0x10)) & 0xFFFFFFFFu; _fb = (uint32_t)(1) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(ebp + 0x10), 1 (32-bit) */
    edx = MEM32(ebp + 0xC);
    if (CMP_NE(_fa, _fb)) goto loc_00221689; /* jne: not equal / not zero */

loc_00221686: ;
    edx = edx + 0x10;

loc_00221689: ;
    PUSH32(esp, esi);
    ecx = ebp + -4;
    PUSH32(esp, ecx);
    ecx = eax;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00221695u); sub_00223DA6(); /* call 0x00223DA6 */

loc_00221695: ;
    _fa = (uint32_t)(MEM32(ebp + -4)) & 0xFFFFFFFFu; _fb = (uint32_t)(0) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(ebp + -4), 0 (32-bit) */
    POP32(esp, esi);
    if (CMP_NE(_fa, _fb)) goto loc_002216A2; /* jne: not equal / not zero */

loc_0022169C: ;
    PUSH32(esp, eax);
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x002216A2u); sub_000B2855(); /* call 0x000B2855 */

loc_002216A2: ;
    eax = MEM32(ebp + -4);

loc_002216A5: ;
    esp = ebp;
    POP32(esp, ebp); /* leave */
    esp += 20; return; /* ret 16 */

}

/**
 * sub_002216A9
 * Original: 0x002216A9 - 0x002216B5 (12 bytes, 3 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_002216A9(void)
{
    extern void dah_xinput_close_bridge(void);
    dah_xinput_close_bridge();
    return;


loc_002216A9: ;
    ecx = MEM32(esp + 4);
    PUSH32(esp, 0x002216B2u); sub_00223A12(); /* call 0x00223A12 */

loc_002216B2: ;
    esp += 8; return; /* ret 4 */

}

/**
 * sub_002216B5
 * Original: 0x002216B5 - 0x00221728 (115 bytes, 41 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_002216B5(void)
{
    extern void dah_xinput_get_state_bridge(void);
    dah_xinput_get_state_bridge();
    return;

    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_002216B5: ;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, ebx);
    PUSH32(esp, esi);
    ebx = 0; /* xor self */
    { uint32_t _icall_target = MEM32(0x225B30); PUSH32(esp, 0x002216BFu); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_002216BF: ;
    edx = MEM32(esp + 0xC);
    ecx = MEM32(edx + 0xA3);
    _fa = (uint32_t)(MEM8(ecx + 0x28)) & 0xFFu; _fb = (uint32_t)(0x10) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(ecx + 0x28), 0x10 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_002216D4; /* je: equal / zero */

loc_002216CF: ;
    PUSH32(esp, 0x57);
    POP32(esp, esi);
    goto loc_00221719;

loc_002216D4: ;
    ecx = MEM32(edx);
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, ecx (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_002216E0; /* je: equal / zero */

loc_002216DA: ;
    _fa = (uint32_t)(MEM8(ecx + 4)) & 0xFFu; _fb = (uint32_t)(2) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(ecx + 4), 2 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_002216E5; /* je: equal / zero */

loc_002216E0: ;
    ebx = 0x48F;

loc_002216E5: ;
    ecx = MEM32(edx + 8);
    PUSH32(esp, edi);
    edi = MEM32(esp + 0x14);
    MEM32(edi) = ecx;
    MEM8(edx + 0xA2) = MEM8(edx + 0xA2) & 0xEF;
    ecx = MEM32(edx + 0xA3);
    ecx = MEM32(ecx + 8);
    ecx = ZX8(MEM8(ecx));
    esi = edx + 0x14;
    edx = ecx;
    edi = edi + 4;
    ecx = ecx >> 2;
    memcpy((void*)XBOX_PTR(edi), (void*)XBOX_PTR(esi), ecx * 4);
    esi += ecx * 4; edi += ecx * 4; ecx = 0; /* rep movsd */
    ecx = edx;
    ecx = ecx & 3;
    memcpy((void*)XBOX_PTR(edi), (void*)XBOX_PTR(esi), ecx);
    esi += ecx; edi += ecx; ecx = 0; /* rep movsb */
    esi = ebx;
    POP32(esp, edi);

loc_00221719: ;
    SET_LO8(ecx, LO8(eax));
    { uint32_t _icall_esp = g_esp;
    { uint32_t _icall_target = MEM32(0x225B2C); PUSH32(esp, 0x00221721u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00221721: ;
    eax = esi;
    POP32(esp, esi);
    POP32(esp, ebx);
    esp += 12; return; /* ret 8 */

}

/**
 * sub_00221728
 * Original: 0x00221728 - 0x0022175B (51 bytes, 17 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00221728(void)
{
    extern void dah_xinput_set_state_bridge(void);
    dah_xinput_set_state_bridge();
    return;

    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00221728: ;
    ecx = MEM32(esp + 4);
    eax = ecx + 0xA3;
    edx = MEM32(eax);
    _fa = (uint32_t)(MEM8(edx + 0x28)) & 0xFFu; _fb = (uint32_t)(0x20) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(edx + 0x28), 0x20 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0022173F; /* je: equal / zero */

loc_0022173A: ;
    PUSH32(esp, 0x57);
    POP32(esp, eax);
    goto loc_00221758;

loc_0022173F: ;
    edx = MEM32(esp + 8);
    MEM8(edx + 0x40) = 0;
    eax = MEM32(eax);
    eax = MEM32(eax + 0xC);
    SET_LO8(eax, MEM8(eax));
    SET_LO8(eax, LO8(eax) + 2);
    MEM8(edx + 0x41) = LO8(eax);
    PUSH32(esp, 0x00221758u); sub_00223AA6(); /* call 0x00223AA6 */

loc_00221758: ;
    esp += 12; return; /* ret 8 */

}

/**
 * sub_0022175B
 * Original: 0x0022175B - 0x002217C3 (104 bytes, 34 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0022175B(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_0022175B: ;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, ebx);
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    edi = MEM32(esp + 0x10);
    esi = edi + 3;
    esi = esi & 0xFFFFFFFCu;
    { uint32_t _icall_target = MEM32(0x225B30); PUSH32(esp, 0x0022176Eu); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_0022176E: ;
    _fa = (uint32_t)(MEM32(0x21F9D8)) & 0xFFFFFFFFu; _fb = (uint32_t)(esi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(0x21F9D8), esi (32-bit) */
    SET_LO8(ecx, LO8(eax));
    if (CMP_B(_fa, _fb)) goto loc_002217A8; /* jb: below (unsigned <) */

loc_00221778: ;
    ebx = 0x80001000u;
    ebx = ebx - MEM32(0x21F9D8);
    MEM32(0x21F9D8) = MEM32(0x21F9D8) - esi;
    { uint32_t _icall_esp = g_esp;
    { uint32_t _icall_target = MEM32(0x225B2C); PUSH32(esp, 0x0022178Fu); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_0022178F: ;
    ecx = esi;
    edx = ecx;
    ecx = ecx >> 2;
    eax = 0xCCCCCCCCu;
    edi = ebx;
    { uint32_t _i; for (_i = 0; _i < ecx; _i++) MEM32(edi + _i*4) = eax; }
    edi += ecx * 4; ecx = 0; /* rep stosd */
    ecx = edx;
    ecx = ecx & 3;
    memset((void*)XBOX_PTR(edi), (uint8_t)eax, ecx);
    edi += ecx; ecx = 0; /* rep stosb */
    goto loc_002217BB;

loc_002217A8: ;
    { uint32_t _icall_esp = g_esp;
    { uint32_t _icall_target = MEM32(0x225B2C); PUSH32(esp, 0x002217AEu); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_002217AE: ;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, MEM32(esp + 0x14));
    PUSH32(esp, edi);
    { uint32_t _icall_target = MEM32(0x225B6C); PUSH32(esp, 0x002217B9u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_002217B9: ;
    ebx = eax;

loc_002217BB: ;
    POP32(esp, edi);
    POP32(esp, esi);
    eax = ebx;
    POP32(esp, ebx);
    esp += 12; return; /* ret 8 */

}

/**
 * sub_002217C3
 * Original: 0x002217C3 - 0x002217D6 (19 bytes, 6 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_002217C3(void)
{

loc_002217C3: ;
    eax = MEM32(ecx + 0xC);
    PUSH32(esp, MEM32(esp + 4));
    eax = eax + 0x18;
    PUSH32(esp, eax);
    PUSH32(esp, 0x002217D3u); sub_00222EC1(); /* call 0x00222EC1 */

loc_002217D3: ;
    esp += 8; return; /* ret 4 */

}

/**
 * sub_002217D6
 * Original: 0x002217D6 - 0x002217DA (4 bytes, 2 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_002217D6(void)
{

loc_002217D6: ;
    eax = MEM32(ecx + 0x1C);
    esp += 4; return; /* ret */

}

/**
 * sub_002217DA
 * Original: 0x002217DA - 0x002217E7 (13 bytes, 4 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_002217DA(void)
{

loc_002217DA: ;
    edx = MEM32(esp + 4);
    eax = MEM32(ecx + 0x1C);
    MEM32(ecx + 0x1C) = edx;
    esp += 8; return; /* ret 4 */

}

/**
 * sub_002217E7
 * Original: 0x002217E7 - 0x002217EB (4 bytes, 2 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_002217E7(void)
{

loc_002217E7: ;
    SET_LO8(eax, MEM8(ecx + 2));
    esp += 4; return; /* ret */

}

/**
 * sub_002217EB
 * Original: 0x002217EB - 0x002217F5 (10 bytes, 3 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_002217EB(void)
{

loc_002217EB: ;
    SET_LO8(eax, MEM8(esp + 4));
    MEM8(ecx + 7) = LO8(eax);
    esp += 8; return; /* ret 4 */

}

/**
 * sub_002217F5
 * Original: 0x002217F5 - 0x00221863 (110 bytes, 36 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_002217F5(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_002217F5: ;
    eax = MEM32(esp + 4);
    ecx = 0xC000000Fu;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, ecx (32-bit) */
    if (CMP_G(_fas, _fbs)) goto loc_00221842; /* jg: greater (signed >) */

loc_00221802: ;
    if (CMP_EQ(_fa, _fb)) goto loc_0022183B; /* je: equal / zero */

loc_00221804: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0x80000000u) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0x80000000u (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_00221827; /* je: equal / zero */

loc_0022180B: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0x80000100u) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0x80000100u (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_00221836; /* je: equal / zero */

loc_00221812: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0x80000800u) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0x80000800u (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_0022182F; /* je: equal / zero */

loc_00221819: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0xBFFFFFFFu) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0xBFFFFFFFu (32-bit) */
    if (CMP_LE(_fas, _fbs)) goto loc_00221854; /* jle: less or equal (signed <=) */

loc_00221820: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0xC000000Eu) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0xC000000Eu (32-bit) */
    if (CMP_G(_fas, _fbs)) goto loc_00221854; /* jg: greater (signed >) */

loc_00221827: ;
    eax = 0x45D;

loc_0022182C: ;
    esp += 8; return; /* ret 4 */

loc_0022182F: ;
    eax = 0x5AA;
    goto loc_0022182C;

loc_00221836: ;
    PUSH32(esp, 0xE);

loc_00221838: ;
    POP32(esp, eax);
    goto loc_0022182C;

loc_0022183B: ;
    eax = 0x4C7;
    goto loc_0022182C;

loc_00221842: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0xC0000010u) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0xC0000010u (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_00221827; /* je: equal / zero */

loc_00221849: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0022185F; /* je: equal / zero */

loc_0022184D: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0x40000000) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0x40000000 (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_00221858; /* je: equal / zero */

loc_00221854: ;
    PUSH32(esp, 0x1F);
    goto loc_00221838;

loc_00221858: ;
    eax = 0x3E5;
    goto loc_0022182C;

loc_0022185F: ;
    eax = 0; /* xor self */
    goto loc_0022182C;

}

/**
 * sub_00221863
 * Original: 0x00221863 - 0x00221869 (6 bytes, 2 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00221863(void)
{

loc_00221863: ;
    eax = MEM32(0x286C5C);
    esp += 4; return; /* ret */

}

/**
 * sub_00221869
 * Original: 0x00221869 - 0x002218DF (118 bytes, 49 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00221869(void)
{
    uint32_t ebp;
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00221869: ;
    PUSH32(esp, ebp);
    ebp = esp;
    g_ebp = ebp; /* publish frame for frameless callees */
    ecx = MEM32(0x286C5C);
    PUSH32(esp, ebx);
    PUSH32(esp, esi);
    esi = ZX16(MEM16(0x286C0E));
    PUSH32(esp, edi);
    esi = esi + 0x286C0C;
    edi = 0; /* xor self */

loc_00221884: ;
    SET_LO8(edx, MEM8(ecx));
    _fa = (uint32_t)(LO8(edx)) & 0xFFu; _fb = (uint32_t)(LO8(edx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(edx), LO8(edx) (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_002218D6; /* je: equal / zero */

loc_0022188A: ;
    eax = ZX8(LO8(edx));
    ecx = ecx + eax;
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(esi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp ecx, esi (32-bit) */
    if (CMP_AE(_fa, _fb)) goto loc_002218D6; /* jae: above or equal (unsigned >=) */

loc_00221893: ;
    SET_LO8(eax, MEM8(ecx + 1));
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(5) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp LO8(eax), 5 (8-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_002218CE; /* jne: not equal / not zero */

loc_0022189A: ;
    SET_LO8(edx, MEM8(ecx + 3));
    SET_LO8(edx, LO8(edx) & 3);
    _fa = (uint32_t)(LO8(edx)) & 0xFFu; _fb = (uint32_t)(MEM8(ebp + 8)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp LO8(edx), MEM8(ebp + 8) (8-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_002218CE; /* jne: not equal / not zero */

loc_002218A5: ;
    _fa = (uint32_t)(MEM8(ebp + 8)) & 0xFFu; _fb = (uint32_t)(0) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(ebp + 8), 0 (8-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_002218CE; /* je: equal / zero */

loc_002218AB: ;
    edx = 0; /* xor self */
    SET_LO8(edx, MEM8(ecx + 2));
    ebx = 0; /* xor self */
    edx = edx >> 7;
    edx = ~edx;
    edx = edx & 1;
    _fa = (uint32_t)(MEM8(ebp + 0xC)) & 0xFFu; _fb = (uint32_t)(LO8(ebx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(ebp + 0xC), LO8(ebx) (8-bit) */
    SET_LO8(ebx, (CMP_EQ(_fa, _fb)) ? 1 : 0); /* sete */
    _fa = (uint32_t)(edx) & 0xFFFFFFFFu; _fb = (uint32_t)(ebx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edx, ebx (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_002218CE; /* jne: not equal / not zero */

loc_002218C4: ;
    SET_LO8(edx, MEM8(ebp + 0x10));
    MEM8(ebp + 0x10) = MEM8(ebp + 0x10) - 1;
    _fa = (uint32_t)(LO8(edx)) & 0xFFu; _fb = (uint32_t)(LO8(edx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(edx), LO8(edx) (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_002218D4; /* je: equal / zero */

loc_002218CE: ;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(4) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp LO8(eax), 4 (8-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_00221884; /* jne: not equal / not zero */

loc_002218D2: ;
    goto loc_002218D6;

loc_002218D4: ;
    edi = ecx;

loc_002218D6: ;
    eax = edi;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebx);
    POP32(esp, ebp);
    esp += 16; return; /* ret 12 */

}

/**
 * sub_002218DF
 * Original: 0x002218DF - 0x002218E3 (4 bytes, 2 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_002218DF(void)
{

loc_002218DF: ;
    eax = MEM32(ecx + 0x14);
    esp += 4; return; /* ret */

}

/**
 * sub_002218E3
 * Original: 0x002218E3 - 0x00221969 (134 bytes, 49 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_002218E3(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_002218E3: ;
    PUSH32(esp, ebx);
    PUSH32(esp, edi);
    edi = ecx;
    ebx = 0; /* xor self */
    _fa = (uint32_t)(MEM8(edi)) & 0xFFu; _fb = (uint32_t)(5) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(edi), 5 (8-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_00221911; /* jne: not equal / not zero */

loc_002218EE: ;
    PUSH32(esp, 0x002218F3u); sub_00220776(); /* call 0x00220776 */

loc_002218F3: ;
    ebx = eax;
    eax = MEM32(ebx + 8);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00221911; /* je: equal / zero */

loc_002218FC: ;
    MEM32(edi + 8) = eax;
    eax = MEM32(esp + 0xC);
    MEM32(eax + 4) = MEM32(eax + 4) & 0;
    PUSH32(esp, eax);
    PUSH32(esp, 0x0022190Du); sub_002231A4(); /* call 0x002231A4 */

loc_0022190D: ;
    eax = 0; /* xor self */
    goto loc_00221964;

loc_00221911: ;
    SET_LO8(eax, MEM8(edi + 5));
    PUSH32(esp, esi);
    esi = MEM32(esp + 0x10);
    MEM8(esi + 0x14) = LO8(eax);
    MEM8(esi + 0x15) = 0;
    MEM8(esi + 0x16) = 0;
    SET_LO16(eax, ZX8(MEM8(edi + 6)));
    MEM16(esi + 0x1C) = LO16(eax);
    SET_LO8(eax, MEM8(edi + 4));
    MEM32(esi + 0x18) = MEM32(esi + 0x18) & 0;
    SET_LO8(eax, LO8(eax) >> 7);
    MEM8(esi + 0x1E) = LO8(eax);
    MEM8(esi + 1) = 2;
    eax = MEM32(edi + 0xC);
    PUSH32(esp, esi);
    eax = eax + 0x18;
    PUSH32(esp, eax);
    PUSH32(esp, 0x0022194Bu); sub_00223032(); /* call 0x00223032 */

loc_0022194B: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_S(_fas, _fbs)) goto loc_0022195F; /* jl: less (signed <) */

loc_0022194F: ;
    _fa = (uint32_t)(ebx) & 0xFFFFFFFFu; _fb = (uint32_t)(ebx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ebx, ebx (32-bit) */
    ecx = MEM32(esi + 0x10);
    MEM32(edi + 8) = ecx;
    if (TEST_Z(_fa, _fb)) goto loc_0022195F; /* je: equal / zero */

loc_00221959: ;
    ecx = MEM32(esi + 0x10);
    MEM32(ebx + 8) = ecx;

loc_0022195F: ;
    MEM32(esi + 0x10) = MEM32(esi + 0x10) & 0;
    POP32(esp, esi);

loc_00221964: ;
    POP32(esp, edi);
    POP32(esp, ebx);
    esp += 8; return; /* ret 4 */

}

/**
 * sub_00221969
 * Original: 0x00221969 - 0x002219D5 (108 bytes, 38 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00221969(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00221969: ;
    PUSH32(esp, esi);
    esi = ecx;
    PUSH32(esp, edi);
    edi = MEM32(esi + 8);
    MEM32(esi + 8) = MEM32(esi + 8) & 0;
    _fa = (uint32_t)(MEM8(esi)) & 0xFFu; _fb = (uint32_t)(5) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(esi), 5 (8-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_002219A2; /* jne: not equal / not zero */

loc_00221979: ;
    PUSH32(esp, 0x0022197Eu); sub_00220776(); /* call 0x00220776 */

loc_0022197E: ;
    ecx = eax;
    PUSH32(esp, 0x00221985u); sub_0022078D(); /* call 0x0022078D */

loc_00221985: ;
    goto loc_00221993;

loc_00221987: ;
    _fa = (uint32_t)(MEM32(eax + 8)) & 0xFFFFFFFFu; _fb = (uint32_t)(edi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(eax + 8), edi (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_002219C3; /* je: equal / zero */

loc_0022198C: ;
    ecx = eax;
    PUSH32(esp, 0x00221993u); sub_002207A4(); /* call 0x002207A4 */

loc_00221993: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_00221987; /* jne: not equal / not zero */

loc_00221997: ;
    ecx = esi;
    PUSH32(esp, 0x0022199Eu); sub_00220776(); /* call 0x00220776 */

loc_0022199E: ;
    MEM32(eax + 8) = MEM32(eax + 8) & 0;

loc_002219A2: ;
    eax = MEM32(esp + 0xC);
    MEM32(eax + 0x18) = MEM32(eax + 0x18) & 0;
    PUSH32(esp, eax);
    MEM8(eax + 1) = 0x43;
    MEM32(eax + 0x10) = edi;
    eax = MEM32(esi + 0xC);
    eax = eax + 0x18;
    PUSH32(esp, eax);
    PUSH32(esp, 0x002219BEu); sub_00223032(); /* call 0x00223032 */

loc_002219BE: ;
    POP32(esp, edi);
    POP32(esp, esi);
    esp += 8; return; /* ret 4 */

loc_002219C3: ;
    eax = MEM32(esp + 0xC);
    MEM32(eax + 4) = MEM32(eax + 4) & 0;
    PUSH32(esp, eax);
    PUSH32(esp, 0x002219D1u); sub_002231A4(); /* call 0x002231A4 */

loc_002219D1: ;
    eax = 0; /* xor self */
    goto loc_002219BE;

}

/**
 * sub_002219D5
 * Original: 0x002219D5 - 0x00221A06 (49 bytes, 19 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_002219D5(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_002219D5: ;
    PUSH32(esp, 0x002219DAu); sub_0022078D(); /* call 0x0022078D */

loc_002219DA: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00221A03; /* je: equal / zero */

loc_002219DE: ;
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    edi = ZX8(MEM8(esp + 0xC));
    esi = 0xFFFFFF7Fu;
    edi = edi & esi;

loc_002219EC: ;
    ecx = ZX8(MEM8(eax + 4));
    ecx = ecx & esi;
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(edi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp ecx, edi (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_00221A01; /* je: equal / zero */

loc_002219F6: ;
    ecx = eax;
    PUSH32(esp, 0x002219FDu); sub_002207A4(); /* call 0x002207A4 */

loc_002219FD: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_002219EC; /* jne: not equal / not zero */

loc_00221A01: ;
    POP32(esp, edi);
    POP32(esp, esi);

loc_00221A03: ;
    esp += 8; return; /* ret 4 */

}

/**
 * sub_00221A06
 * Original: 0x00221A06 - 0x00221A4E (72 bytes, 25 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00221A06(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00221A06: ;
    eax = MEM32(esp + 4);
    PUSH32(esp, ebx);
    ebx = eax;
    ebx = ebx - MEM32(0x286C60);
    PUSH32(esp, esi);
    esi = ecx;
    MEM8(eax + 3) = 0x80;
    ecx = ecx - MEM32(0x286C60);
    ebx = (uint32_t)((int32_t)ebx >> 5);
    ecx = (uint32_t)((int32_t)ecx >> 5);
    MEM8(eax + 1) = LO8(ecx);
    ecx = esi;
    PUSH32(esp, 0x00221A30u); sub_0022078D(); /* call 0x0022078D */

loc_00221A30: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_00221A40; /* jne: not equal / not zero */

loc_00221A34: ;
    MEM8(esi + 2) = LO8(ebx);
    goto loc_00221A49;

loc_00221A39: ;
    ecx = eax;
    PUSH32(esp, 0x00221A40u); sub_002207A4(); /* call 0x002207A4 */

loc_00221A40: ;
    _fa = (uint32_t)(MEM8(eax + 3)) & 0xFFu; _fb = (uint32_t)(0x80) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(eax + 3), 0x80 (8-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_00221A39; /* jne: not equal / not zero */

loc_00221A46: ;
    MEM8(eax + 3) = LO8(ebx);

loc_00221A49: ;
    POP32(esp, esi);
    POP32(esp, ebx);
    esp += 8; return; /* ret 4 */

}

/**
 * sub_00221A4E
 * Original: 0x00221A4E - 0x00221AAA (92 bytes, 40 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00221A4E(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_00221A4E: ;
    PUSH32(esp, ebx);
    PUSH32(esp, ebp);
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    ebp = ecx;
    PUSH32(esp, 0x00221A59u); sub_0022078D(); /* call 0x0022078D */

loc_00221A59: ;
    esi = MEM32(esp + 0x14);
    edi = eax;
    _fa = (uint32_t)(edi) & 0xFFFFFFFFu; _fb = (uint32_t)(esi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edi, esi (32-bit) */
    SET_LO8(ebx, 1);
    if (CMP_NE(_fa, _fb)) goto loc_00221A73; /* jne: not equal / not zero */

loc_00221A65: ;
    SET_LO8(eax, MEM8(esi + 3));
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(0x80) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp LO8(eax), 0x80 (8-bit) */
    MEM8(ebp + 2) = LO8(eax);
    if (CMP_NE(_fa, _fb)) goto loc_00221A99; /* jne: not equal / not zero */

loc_00221A6F: ;
    SET_LO8(ebx, 0); /* xor self */
    goto loc_00221A99;

loc_00221A73: ;
    _fa = (uint32_t)(edi) & 0xFFFFFFFFu; _fb = (uint32_t)(edi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test edi, edi (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00221A99; /* je: equal / zero */

loc_00221A77: ;
    ecx = edi;
    PUSH32(esp, 0x00221A7Eu); sub_002207A4(); /* call 0x002207A4 */

loc_00221A7E: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(esi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, esi (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_00221A8F; /* je: equal / zero */

loc_00221A82: ;
    ecx = edi;
    PUSH32(esp, 0x00221A89u); sub_002207A4(); /* call 0x002207A4 */

loc_00221A89: ;
    edi = eax;
    _fa = (uint32_t)(edi) & 0xFFFFFFFFu; _fb = (uint32_t)(edi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test edi, edi (32-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_00221A77; /* jne: not equal / not zero */

loc_00221A8F: ;
    _fa = (uint32_t)(edi) & 0xFFFFFFFFu; _fb = (uint32_t)(edi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test edi, edi (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00221A99; /* je: equal / zero */

loc_00221A93: ;
    SET_LO8(eax, MEM8(esi + 3));
    MEM8(edi + 3) = LO8(eax);

loc_00221A99: ;
    POP32(esp, edi);
    MEM8(esi + 3) = 0x80;
    MEM8(esi + 1) = 0x80;
    POP32(esp, esi);
    POP32(esp, ebp);
    SET_LO8(eax, LO8(ebx));
    POP32(esp, ebx);
    esp += 8; return; /* ret 4 */

}

/**
 * sub_00221AAA
 * Original: 0x00221AAA - 0x00221B1F (117 bytes, 41 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00221AAA(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00221AAA: ;
    eax = MEM32(esp + 4);
    edx = MEM32(eax + 4);
    edx = ZX8(MEM8(edx + 4));
    edx = edx & 0x7F;
    edx--;
    _fa = (uint32_t)(edx) & 0xFFFFFFFFu; _fb = (uint32_t)(4) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edx, 4 (32-bit) */
    MEM32(ecx + 0x14) = edx;
    if (CMP_L(_fas, _fbs)) goto loc_00221ACA; /* jl: less (signed <) */

loc_00221AC1: ;
    MEM32(ecx + 0x14) = 0x20;
    goto loc_00221B1C;

loc_00221ACA: ;
    PUSH32(esp, esi);
    esi = MEM32(esp + 0xC);
    edx = edx ^ 2;
    MEM32(ecx + 0x14) = edx;
    PUSH32(esp, edi);
    edi = MEM32(eax + esi * 4);
    _fa = (uint32_t)(MEM8(edi)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(edi), 1 (8-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_00221AFA; /* jne: not equal / not zero */

loc_00221ADE: ;
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(1) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp esi, 1 (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_00221B1A; /* je: equal / zero */

loc_00221AE3: ;
    _fa = (uint32_t)(MEM8(0x21F924)) & 0xFFu; _fb = (uint32_t)(0) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(0x21F924), 0 (8-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_00221AF1; /* je: equal / zero */

loc_00221AEC: ;
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(2) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp esi, 2 (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_00221B1A; /* je: equal / zero */

loc_00221AF1: ;
    MEM32(ecx + 0x14) = 0x20;
    goto loc_00221B1A;

loc_00221AFA: ;
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(1) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp esi, 1 (32-bit) */
    if (CMP_BE(_fa, _fb)) goto loc_00221B1A; /* jbe: below or equal (unsigned <=) */

loc_00221AFF: ;
    eax = MEM32(eax + 8);
    eax = ZX8(MEM8(eax + 4));
    eax = eax & 0x7F;
    eax--;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(3) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 3 (32-bit) */
    if (CMP_A(_fa, _fb)) goto loc_00221AF1; /* ja: above (unsigned >) */

loc_00221B0F: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(2) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 2 (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_00221B1A; /* jne: not equal / not zero */

loc_00221B14: ;
    edx = edx + 0x10;
    MEM32(ecx + 0x14) = edx;

loc_00221B1A: ;
    POP32(esp, edi);
    POP32(esp, esi);

loc_00221B1C: ;
    esp += 12; return; /* ret 8 */

}

/**
 * sub_00221B1F
 * Original: 0x00221B1F - 0x00221C09 (234 bytes, 89 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00221B1F(void)
{
    uint32_t ebp;
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00221B1F: ;
    PUSH32(esp, ebp);
    ebp = esp;
    g_ebp = ebp; /* publish frame for frameless callees */
    esp = esp - 0x14;
    PUSH32(esp, ebx);
    PUSH32(esp, esi);
    esi = MEM32(ebp + 8);
    SET_LO8(eax, MEM8(esi + 1));
    ebx = 0; /* xor self */
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(0x40) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), 0x40 (8-bit) */
    MEM8(ebp + -1) = LO8(ebx);
    if (TEST_Z(_fa, _fb)) goto loc_00221B5F; /* je: equal / zero */

loc_00221B36: ;
    _fa = (uint32_t)(MEM32(esi + 8)) & 0xFFFFFFFFu; _fb = (uint32_t)(ebx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(esi + 8), ebx (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_00221B5F; /* jne: not equal / not zero */

loc_00221B3B: ;
    edx = ebp + -12;
    MEM32(ebp + -8) = edx;
    MEM32(ebp + -12) = edx;
    edx = ebp + -20;
    MEM8(ebp + -1) = 1;
    MEM8(ebp + -20) = LO8(ebx);
    MEM8(ebp + -18) = 4;
    MEM32(ebp + -16) = ebx;
    MEM32(esi + 8) = 0x22369A;
    MEM32(esi + 0xC) = edx;

loc_00221B5F: ;
    eax = ZX8(LO8(eax));
    eax--;
    eax--;
    if ((eax == 0)) goto loc_00221BB5; /* je: equal / zero */

loc_00221B66: ;
    eax = eax - 7;
    if ((eax == 0)) goto loc_00221BAD; /* je: equal / zero */

loc_00221B6B: ;
    eax = eax - 0x37;
    if ((eax == 0)) goto loc_00221B97; /* je: equal / zero */

loc_00221B70: ;
    eax = eax - 3;
    if ((eax == 0)) goto loc_00221B8F; /* je: equal / zero */

loc_00221B75: ;
    eax = eax - 0x3F;
    if ((eax == 0)) goto loc_00221B87; /* je: equal / zero */

loc_00221B7A: ;
    eax = eax - 0x41;
    if ((eax != 0)) goto loc_00221BCA; /* jne: not equal / not zero */

loc_00221B7F: ;
    PUSH32(esp, esi);
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00221B85u); sub_00221969(); /* call 0x00221969 */

loc_00221B85: ;
    goto loc_00221BD7;

loc_00221B87: ;
    PUSH32(esp, esi);
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00221B8Du); sub_002218E3(); /* call 0x002218E3 */

loc_00221B8D: ;
    goto loc_00221BD7;

loc_00221B8F: ;
    eax = ecx + 0x18;
    MEM32(esi + 0x18) = eax;
    goto loc_00221BCA;

loc_00221B97: ;
    _fa = (uint32_t)(MEM32(esi + 0x10)) & 0xFFFFFFFFu; _fb = (uint32_t)(ebx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(esi + 0x10), ebx (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_00221BA2; /* jne: not equal / not zero */

loc_00221B9C: ;
    eax = MEM32(ecx + 8);
    MEM32(esi + 0x10) = eax;

loc_00221BA2: ;
    _fa = (uint32_t)(MEM8(esi + 0x29)) & 0xFFu; _fb = (uint32_t)(9) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(esi + 0x29), 9 (8-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_00221BCA; /* jne: not equal / not zero */

loc_00221BA8: ;
    MEM32(ecx + 0x18) = ebx;
    goto loc_00221BCA;

loc_00221BAD: ;
    SET_LO8(eax, MEM8(ecx + 5));
    MEM8(esi + 0x14) = LO8(eax);
    goto loc_00221BCA;

loc_00221BB5: ;
    SET_LO8(eax, MEM8(ecx + 5));
    MEM8(esi + 0x14) = LO8(eax);
    eax = ecx + 0x18;
    MEM32(esi + 0x18) = eax;
    SET_LO8(eax, MEM8(ecx + 4));
    SET_LO8(eax, LO8(eax) >> 7);
    MEM8(esi + 0x1E) = LO8(eax);

loc_00221BCA: ;
    eax = MEM32(ecx + 0xC);
    PUSH32(esp, esi);
    eax = eax + 0x18;
    PUSH32(esp, eax);
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00221BD7u); sub_00223032(); /* call 0x00223032 */

loc_00221BD7: ;
    _fa = (uint32_t)(MEM8(ebp + -1)) & 0xFFu; _fb = (uint32_t)(LO8(ebx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(ebp + -1), LO8(ebx) (8-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_00221C03; /* je: equal / zero */

loc_00221BDC: ;
    ecx = eax;
    ecx = ecx & 0xC0000000u;
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(0x40000000) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp ecx, 0x40000000 (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_00221BFD; /* jne: not equal / not zero */

loc_00221BEC: ;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, ebx);
    PUSH32(esp, ebx);
    PUSH32(esp, ebx);
    PUSH32(esp, ebx);
    eax = ebp + -20;
    PUSH32(esp, eax);
    { uint32_t _icall_target = MEM32(0x225B48); PUSH32(esp, 0x00221BFAu); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00221BFA: ;
    eax = MEM32(esi + 4);

loc_00221BFD: ;
    MEM32(esi + 8) = ebx;
    MEM32(esi + 0xC) = ebx;

loc_00221C03: ;
    POP32(esp, esi);
    POP32(esp, ebx);
    esp = ebp;
    POP32(esp, ebp); /* leave */
    esp += 8; return; /* ret 4 */

}

/**
 * sub_00221C09
 * Original: 0x00221C09 - 0x00221C4B (66 bytes, 25 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00221C09(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00221C09: ;
    PUSH32(esp, esi);
    esi = MEM32(esp + 8);
    eax = esi + 4;
    edx = MEM32(eax);
    _fa = (uint32_t)(MEM8(edx)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(edx), 1 (8-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_00221C23; /* jne: not equal / not zero */

loc_00221C18: ;
    SET_LO8(edx, MEM8(edx + 4));
    SET_LO8(edx, LO8(edx) & 0x7F);
    _fa = (uint32_t)(LO8(edx)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp LO8(edx), 1 (8-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_00221C2C; /* je: equal / zero */

loc_00221C23: ;
    MEM32(ecx + 0x14) = 0x20;
    goto loc_00221C47;

loc_00221C2C: ;
    edx = MEM32(esp + 0xC);
    _fa = (uint32_t)(edx) & 0xFFFFFFFFu; _fb = (uint32_t)(1) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edx, 1 (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_00221C3B; /* jne: not equal / not zero */

loc_00221C35: ;
    MEM32(ecx + 0x14) = MEM32(ecx + 0x14) & 0;
    goto loc_00221C47;

loc_00221C3B: ;
    esi = MEM32(esi);
    edx--;
    PUSH32(esp, edx);
    PUSH32(esp, eax);
    MEM32(eax) = esi;
    PUSH32(esp, 0x00221C47u); sub_00221AAA(); /* call 0x00221AAA */

loc_00221C47: ;
    POP32(esp, esi);
    esp += 12; return; /* ret 8 */

}

/**
 * sub_00221C4B
 * Original: 0x00221C4B - 0x00221C96 (75 bytes, 32 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00221C4B(void)
{
    uint32_t ebp;
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00221C4B: ;
    PUSH32(esp, ebp);
    ebp = esp;
    g_ebp = ebp; /* publish frame for frameless callees */
    esp = esp - 0x18;
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    edi = ecx;
    PUSH32(esp, 5);
    POP32(esp, esi);
    MEM32(ebp + -4) = edi;

loc_00221C5B: ;
    ecx = MEM32(ebp + esi * 4 + -24);
    esi--;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00221C65u); sub_00220776(); /* call 0x00220776 */

loc_00221C65: ;
    _fa = (uint32_t)(MEM8(eax)) & 0xFFu; _fb = (uint32_t)(0) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(eax), 0 (8-bit) */
    MEM32(ebp + esi * 4 + -24) = eax;
    if (CMP_NE(_fa, _fb)) goto loc_00221C5B; /* jne: not equal / not zero */

loc_00221C6E: ;
    edx = MEM32(0x225AA8);
    PUSH32(esp, 5);
    POP32(esp, eax);
    eax = eax - esi;
    _fa = (uint32_t)(MEM8(edx)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(edx), 1 (8-bit) */
    ecx = ebp + esi * 4 + -24;
    PUSH32(esp, eax);
    PUSH32(esp, ecx);
    ecx = edi;
    if (TEST_Z(_fa, _fb)) goto loc_00221C8D; /* je: equal / zero */

loc_00221C86: ;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00221C8Bu); sub_00221C09(); /* call 0x00221C09 */

loc_00221C8B: ;
    goto loc_00221C92;

loc_00221C8D: ;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00221C92u); sub_00221AAA(); /* call 0x00221AAA */

loc_00221C92: ;
    POP32(esp, edi);
    POP32(esp, esi);
    esp = ebp;
    POP32(esp, ebp); /* leave */
    esp += 4; return; /* ret */

}

/**
 * sub_00221CE6
 * Original: 0x00221CE6 - 0x00221D43 (93 bytes, 29 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00221CE6(void)
{

loc_00221CE6: ;
    PUSH32(esp, esi);
    esi = MEM32(esp + 8);
    PUSH32(esp, edi);
    ecx = esi;
    PUSH32(esp, 0x00221CF3u); sub_002217D6(); /* call 0x002217D6 */

loc_00221CF3: ;
    SET_LO16(edi, ZX8(MEM8(eax + 3)));
    edx = 0; /* xor self */
    ecx = eax + 8;
    MEM8(ecx) = 0x30;
    PUSH32(esp, ecx);
    ecx = esi;
    MEM8(eax + 9) = 0x40;
    MEM32(eax + 0x10) = 0x2225CA;
    MEM32(eax + 0x14) = esi;
    MEM32(eax + 0x18) = edx;
    MEM32(eax + 0x20) = edx;
    MEM32(eax + 0x1C) = edx;
    MEM8(eax + 0x24) = LO8(edx);
    MEM8(eax + 0x25) = LO8(edx);
    MEM8(eax + 0x26) = LO8(edx);
    MEM8(eax + 0x30) = 0x23;
    MEM8(eax + 0x31) = 1;
    MEM16(eax + 0x32) = 1;
    MEM16(eax + 0x34) = LO16(edi);
    MEM16(eax + 0x36) = LO16(edx);
    PUSH32(esp, 0x00221D3Eu); sub_00221B1F(); /* call 0x00221B1F */

loc_00221D3E: ;
    POP32(esp, edi);
    POP32(esp, esi);
    esp += 8; return; /* ret 4 */

}

/**
 * sub_00221D43
 * Original: 0x00221D43 - 0x00221D79 (54 bytes, 19 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00221D43(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00221D43: ;
    PUSH32(esp, esi);
    esi = MEM32(esp + 8);
    SET_LO8(eax, MEM8(esi));
    SET_LO8(eax, LO8(eax) >> 4);
    SET_LO8(eax, LO8(eax) & 1);
    if ((LO8(eax) == 0)) goto loc_00221D62; /* je: equal / zero */

loc_00221D51: ;
    _fa = (uint32_t)(MEM32(esp + 0xC)) & 0xFFFFFFFFu; _fb = (uint32_t)(0) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(esp + 0xC), 0 (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_00221D62; /* jne: not equal / not zero */

loc_00221D58: ;
    PUSH32(esp, 0x00221D5Du); sub_00220989(); /* call 0x00220989 */

loc_00221D5D: ;
    MEM8(esi) = MEM8(esi) & 0xEF;
    goto loc_00221D75;

loc_00221D62: ;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_00221D75; /* jne: not equal / not zero */

loc_00221D66: ;
    _fa = (uint32_t)(MEM32(esp + 0xC)) & 0xFFFFFFFFu; _fb = (uint32_t)(0) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(esp + 0xC), 0 (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_00221D75; /* je: equal / zero */

loc_00221D6D: ;
    PUSH32(esp, 0x00221D72u); sub_00220982(); /* call 0x00220982 */

loc_00221D72: ;
    MEM8(esi) = MEM8(esi) | 0x10;

loc_00221D75: ;
    POP32(esp, esi);
    esp += 12; return; /* ret 8 */

}

/**
 * sub_00221DEA
 * Original: 0x00221DEA - 0x00221E4D (99 bytes, 28 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00221DEA(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00221DEA: ;
    _fa = (uint32_t)(MEM32(0x286D18)) & 0xFFFFFFFFu; _fb = (uint32_t)(0) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(0x286D18), 0 (32-bit) */
    PUSH32(esp, esi);
    esi = 0x286CD0;
    if (CMP_EQ(_fa, _fb)) goto loc_00221E14; /* je: equal / zero */

loc_00221DF9: ;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, esi);
    { uint32_t _icall_target = MEM32(0x225B58); PUSH32(esp, 0x00221E00u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00221E00: ;
    PUSH32(esp, 0);
    PUSH32(esp, MEM32(0x286D18));
    PUSH32(esp, 0x00221E0Du); sub_00221D43(); /* call 0x00221D43 */

loc_00221E0D: ;
    MEM32(0x286D18) = MEM32(0x286D18) & 0;

loc_00221E14: ;
    edx = MEM32(esp + 8);
    _fa = (uint32_t)(edx) & 0xFFFFFFFFu; _fb = (uint32_t)(edx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test edx, edx (32-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_00221E23; /* jne: not equal / not zero */

loc_00221E1C: ;
    eax = 0xFA0A1F00u;
    goto loc_00221E32;

loc_00221E23: ;
    _fa = (uint32_t)(edx) & 0xFFFFFFFFu; _fb = (uint32_t)(3) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edx, 3 (32-bit) */
    eax = 0xFFF48E50u;
    if (CMP_EQ(_fa, _fb)) goto loc_00221E32; /* je: equal / zero */

loc_00221E2D: ;
    eax = 0xFFB3B4C0u;

loc_00221E32: ;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 0x286CF8);
    ecx = ecx | 0xFFFFFFFFu;
    PUSH32(esp, ecx);
    PUSH32(esp, eax);
    PUSH32(esp, esi);
    MEM32(0x286D14) = edx;
    { uint32_t _icall_target = MEM32(0x225B28); PUSH32(esp, 0x00221E49u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00221E49: ;
    POP32(esp, esi);
    esp += 8; return; /* ret 4 */

}

/**
 * sub_00221E4D
 * Original: 0x00221E4D - 0x00221F9B (334 bytes, 117 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00221E4D(void)
{
    uint32_t ebp;
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00221E4D: ;
    PUSH32(esp, ebp);
    ebp = esp;
    g_ebp = ebp; /* publish frame for frameless callees */
    PUSH32(esp, ebx);
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    edi = MEM32(ebp + 8);
    ecx = edi;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00221E5Du); sub_002217D6(); /* call 0x002217D6 */

loc_00221E5D: ;
    esi = eax;
    SET_LO16(eax, MEM16(esi + 0x3A));
    ebx = 0; /* xor self */
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(0x10) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), 0x10 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00221EC4; /* je: equal / zero */

loc_00221E69: ;
    _fa = (uint32_t)(MEM32(0x286D14)) & 0xFFFFFFFFu; _fb = (uint32_t)(1) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(0x286D14), 1 (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_00221EBC; /* jne: not equal / not zero */

loc_00221E72: ;
    _fa = (uint32_t)(MEM32(0x286CC8)) & 0xFFFFFFFFu; _fb = (uint32_t)(ebx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(0x286CC8), ebx (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_00221EBC; /* je: equal / zero */

loc_00221E7A: ;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 0x286CD0);
    edi = 0; /* xor self */
    { uint32_t _icall_target = MEM32(0x225B58); PUSH32(esp, 0x00221E87u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00221E87: ;
    SET_LO16(eax, MEM16(esi + 0x38));
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(2) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), 2 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00221E9F; /* je: equal / zero */

loc_00221E8F: ;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(0x10) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), 0x10 (8-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_00221E9F; /* jne: not equal / not zero */

loc_00221E93: ;
    _fa = (uint32_t)(HI8(eax)) & 0xFFu; _fb = (uint32_t)(2) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test HI8(eax), 2 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00221EA4; /* je: equal / zero */

loc_00221E98: ;
    edi = 0x1000000;
    goto loc_00221EA4;

loc_00221E9F: ;
    edi = 0x80000600u;

loc_00221EA4: ;
    eax = MEM32(0x286CC8);
    ecx = MEM32(ebp + 8);
    PUSH32(esp, eax);
    PUSH32(esp, edi);
    MEM32(0x286CC8) = ebx;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00221EB9u); sub_00220A30(); /* call 0x00220A30 */

loc_00221EB9: ;
    edi = MEM32(ebp + 8);

loc_00221EBC: ;
    MEM8(esi + 0x3A) = MEM8(esi + 0x3A) & 0xEF;
    PUSH32(esp, 0x14);
    goto loc_00221F3B;

loc_00221EC4: ;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), 1 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00221F15; /* je: equal / zero */

loc_00221EC8: ;
    ecx = 0; /* xor self */
    SET_LO8(ecx, MEM8(esi + 3));
    MEM8(ebp + 8) = LO8(ecx);
    SET_LO8(eax, 1);
    ecx--;
    SET_LO8(eax, LO8(eax) << LO8(ecx));
    _fa = (uint32_t)(MEM8(esi + 0x38)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(esi + 0x38), 1 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00221EF5; /* je: equal / zero */

loc_00221EDB: ;
    _fa = (uint32_t)(MEM8(esi + 5)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(esi + 5), LO8(eax) (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00221EEA; /* je: equal / zero */

loc_00221EE0: ;
    PUSH32(esp, MEM32(ebp + 8));
    ecx = edi;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00221EEAu); sub_00220BAC(); /* call 0x00220BAC */

loc_00221EEA: ;
    PUSH32(esp, edi);
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00221EF0u); sub_00221CE6(); /* call 0x00221CE6 */

loc_00221EF0: ;
    goto loc_00221F94;

loc_00221EF5: ;
    SET_LO8(ecx, MEM8(esi + 5));
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(ecx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(ecx) (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00221F0D; /* je: equal / zero */

loc_00221EFC: ;
    PUSH32(esp, MEM32(ebp + 8));
    SET_LO8(eax, ~LO8(eax));
    SET_LO8(eax, LO8(eax) & LO8(ecx));
    ecx = edi;
    MEM8(esi + 5) = LO8(eax);
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00221F0Du); sub_00220BAC(); /* call 0x00220BAC */

loc_00221F0D: ;
    MEM8(esi + 0x3A) = MEM8(esi + 0x3A) & 0xFE;
    PUSH32(esp, 0x10);
    goto loc_00221F3B;

loc_00221F15: ;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(2) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), 2 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00221F21; /* je: equal / zero */

loc_00221F19: ;
    SET_LO16(eax, LO16(eax) & 0xFFFD);
    PUSH32(esp, 0x11);
    goto loc_00221F37;

loc_00221F21: ;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(4) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), 4 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00221F2D; /* je: equal / zero */

loc_00221F25: ;
    SET_LO16(eax, LO16(eax) & 0xFFFB);
    PUSH32(esp, 0x12);
    goto loc_00221F37;

loc_00221F2D: ;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(8) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), 8 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00221F85; /* je: equal / zero */

loc_00221F31: ;
    SET_LO16(eax, LO16(eax) & 0xFFF7);
    PUSH32(esp, 0x13);

loc_00221F37: ;
    MEM16(esi + 0x3A) = LO16(eax);

loc_00221F3B: ;
    POP32(esp, ecx);
    MEM16(esi + 0x32) = LO16(ecx);
    SET_LO16(ecx, ZX8(MEM8(esi + 3)));
    eax = esi + 8;
    MEM16(esi + 0x34) = LO16(ecx);
    PUSH32(esp, eax);
    ecx = edi;
    MEM8(eax) = 0x30;
    MEM8(esi + 9) = 0x40;
    MEM32(esi + 0x10) = 0x22259A;
    MEM32(esi + 0x14) = edi;
    MEM32(esi + 0x18) = ebx;
    MEM32(esi + 0x20) = ebx;
    MEM32(esi + 0x1C) = ebx;
    MEM8(esi + 0x24) = LO8(ebx);
    MEM8(esi + 0x25) = LO8(ebx);
    MEM8(esi + 0x26) = LO8(ebx);
    MEM8(esi + 0x30) = 0x23;
    MEM8(esi + 0x31) = 1;
    MEM16(esi + 0x36) = LO16(ebx);
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00221F83u); sub_00221B1F(); /* call 0x00221B1F */

loc_00221F83: ;
    goto loc_00221F94;

loc_00221F85: ;
    MEM16(esi + 0x3A) = MEM16(esi + 0x3A) & 0;
    PUSH32(esp, edi);
    esi = esi + 8;
    PUSH32(esp, esi);
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00221F94u); sub_0022259A(); /* call 0x0022259A */

loc_00221F94: ;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebx);
    POP32(esp, ebp);
    esp += 8; return; /* ret 4 */

}

/**
 * sub_00221FFE
 * Original: 0x00221FFE - 0x002220E5 (231 bytes, 60 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00221FFE(void)
{
    uint32_t ebp;
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00221FFE: ;
    PUSH32(esp, ebp);
    ebp = esp;
    g_ebp = ebp; /* publish frame for frameless callees */
    PUSH32(esp, ecx);
    ecx = MEM32(ebp + 8);
    PUSH32(esp, ebx);
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x0022200Du); sub_002217D6(); /* call 0x002217D6 */

loc_0022200D: ;
    ecx = 0; /* xor self */
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, ecx (32-bit) */
    PUSH32(esp, 4);
    SET_LO8(edx, 3);
    POP32(esp, esi);
    MEM32(ebp + -4) = 1;
    edi = 0x221C96;
    if (CMP_EQ(_fa, _fb)) goto loc_002220CE; /* je: equal / zero */

loc_00222028: ;
    SET_LO8(ebx, MEM8(ebp + 0xC));
    _fa = (uint32_t)(MEM8(eax + 2)) & 0xFFu; _fb = (uint32_t)(LO8(ebx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(eax + 2), LO8(ebx) (8-bit) */
    if (CMP_B(_fa, _fb)) goto loc_002220CE; /* jb: below (unsigned <) */

loc_00222034: ;
    _fa = (uint32_t)(MEM8(ebp + 0x14)) & 0xFFu; _fb = (uint32_t)(LO8(ecx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(ebp + 0x14), LO8(ecx) (8-bit) */
    eax = MEM32(ebp + 0x10);
    MEM32(0x286CC8) = eax;
    if (CMP_EQ(_fa, _fb)) goto loc_00222052; /* je: equal / zero */

loc_00222041: ;
    edx = 0; /* xor self */
    edx++;
    esi = edx;
    edi = 0x221CC2;
    MEM32(ebp + -4) = 2;

loc_00222052: ;
    PUSH32(esp, MEM32(ebp + -4));
    SET_LO16(eax, ZX8(LO8(ebx)));
    MEM32(0x286CA0) = edi;
    edi = MEM32(ebp + 8);
    MEM8(0x286C98) = 0x30;
    MEM8(0x286C99) = 0x40;
    MEM32(0x286CA4) = edi;
    MEM32(0x286CA8) = ecx;
    MEM32(0x286CB0) = ecx;
    MEM32(0x286CAC) = ecx;
    MEM8(0x286CB4) = LO8(ecx);
    MEM8(0x286CB5) = LO8(ecx);
    MEM8(0x286CB6) = LO8(ecx);
    MEM8(0x286CC0) = 0x23;
    MEM8(0x286CC1) = LO8(edx);
    MEM16(0x286CC2) = LO16(esi);
    MEM16(0x286CC4) = LO16(eax);
    MEM16(0x286CC6) = LO16(ecx);
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x002220C0u); sub_00221DEA(); /* call 0x00221DEA */

loc_002220C0: ;
    PUSH32(esp, 0x286C98);
    ecx = edi;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x002220CCu); sub_00221B1F(); /* call 0x00221B1F */

loc_002220CC: ;
    goto loc_002220DE;

loc_002220CE: ;
    PUSH32(esp, MEM32(ebp + 0x10));
    ecx = MEM32(ebp + 8);
    PUSH32(esp, 0x80000300u);
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x002220DEu); sub_00220A30(); /* call 0x00220A30 */

loc_002220DE: ;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebx);
    esp = ebp;
    POP32(esp, ebp); /* leave */
    esp += 20; return; /* ret 16 */

}

/**
 * sub_002220E5
 * Original: 0x002220E5 - 0x00222107 (34 bytes, 9 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_002220E5(void)
{

loc_002220E5: ;
    eax = MEM32(esp + 4);
    ecx = MEM32(esp + 8);
    PUSH32(esp, eax);
    MEM8(eax) = 0x1C;
    MEM8(eax + 1) = 0xC3;
    MEM32(eax + 8) = 0x221F9B;
    MEM32(eax + 0xC) = ecx;
    PUSH32(esp, 0x00222104u); sub_00221B1F(); /* call 0x00221B1F */

loc_00222104: ;
    esp += 12; return; /* ret 8 */

}

/**
 * sub_00222107
 * Original: 0x00222107 - 0x00222139 (50 bytes, 16 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00222107(void)
{

loc_00222107: ;
    PUSH32(esp, esi);
    esi = MEM32(esp + 8);
    ecx = esi;
    PUSH32(esp, 0x00222113u); sub_002217D6(); /* call 0x002217D6 */

loc_00222113: ;
    edx = MEM32(eax + 0x3C);
    ecx = eax + 8;
    MEM8(ecx) = 0x1C;
    PUSH32(esp, ecx);
    ecx = esi;
    MEM8(eax + 9) = 0x43;
    MEM32(eax + 0x10) = 0x2220E5;
    MEM32(eax + 0x14) = esi;
    MEM32(eax + 0x18) = edx;
    PUSH32(esp, 0x00222135u); sub_00221B1F(); /* call 0x00221B1F */

loc_00222135: ;
    POP32(esp, esi);
    esp += 8; return; /* ret 4 */

}

/**
 * sub_00222280
 * Original: 0x00222280 - 0x002222D0 (80 bytes, 33 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00222280(void)
{
    uint32_t ebp;
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00222280: ;
    PUSH32(esp, ebp);
    ebp = esp;
    g_ebp = ebp; /* publish frame for frameless callees */
    PUSH32(esp, ecx);
    ecx = MEM32(ebp + 8);
    PUSH32(esp, ebx);
    PUSH32(esp, esi);
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x0022228Eu); sub_002217D6(); /* call 0x002217D6 */

loc_0022228E: ;
    esi = eax;
    MEM8(esi) = MEM8(esi) | 2;
    ebx = 0; /* xor self */
    ebx++;
    MEM8(ebp + -4) = LO8(ebx);

loc_00222299: ;
    _fa = (uint32_t)(MEM8(esi + 5)) & 0xFFu; _fb = (uint32_t)(LO8(ebx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(esi + 5), LO8(ebx) (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_002222B0; /* je: equal / zero */

loc_0022229E: ;
    PUSH32(esp, MEM32(ebp + -4));
    ecx = MEM32(ebp + 8);
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x002222A9u); sub_00220BAC(); /* call 0x00220BAC */

loc_002222A9: ;
    SET_LO8(eax, LO8(ebx));
    SET_LO8(eax, ~LO8(eax));
    MEM8(esi + 5) = MEM8(esi + 5) & LO8(eax);

loc_002222B0: ;
    ebx = ebx << 1;
    MEM8(ebp + -4) = MEM8(ebp + -4) + 1;
    SET_LO8(eax, MEM8(ebp + -4));
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(MEM8(esi + 2)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp LO8(eax), MEM8(esi + 2) (8-bit) */
    if (CMP_BE(_fa, _fb)) goto loc_00222299; /* jbe: below or equal (unsigned <=) */

loc_002222BD: ;
    _fa = (uint32_t)(MEM8(esi)) & 0xFFu; _fb = (uint32_t)(8) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(esi), 8 (8-bit) */
    POP32(esp, esi);
    POP32(esp, ebx);
    if (TEST_Z(_fa, _fb)) goto loc_002222CC; /* je: equal / zero */

loc_002222C4: ;
    PUSH32(esp, MEM32(ebp + 8));
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x002222CCu); sub_00222107(); /* call 0x00222107 */

loc_002222CC: ;
    esp = ebp;
    POP32(esp, ebp); /* leave */
    esp += 8; return; /* ret 4 */

}

/**
 * sub_002224C7
 * Original: 0x002224C7 - 0x0022259A (211 bytes, 74 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_002224C7(void)
{
    uint32_t ebp;
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_002224C7: ;
    PUSH32(esp, ebp);
    ebp = esp;
    g_ebp = ebp; /* publish frame for frameless callees */
    PUSH32(esp, ebx);
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    edi = MEM32(ebp + 8);
    ecx = edi;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x002224D7u); sub_002217D6(); /* call 0x002217D6 */

loc_002224D7: ;
    SET_LO8(ebx, MEM8(eax + 4));
    ecx = 0; /* xor self */
    SET_LO8(edx, 1);
    MEM8(eax + 3) = LO8(ecx);
    MEM8(ebp + 0xB) = LO8(ebx);

loc_002224E4: ;
    _fa = (uint32_t)(MEM8(ebp + 0xB)) & 0xFFu; _fb = (uint32_t)(LO8(edx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(ebp + 0xB), LO8(edx) (8-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_002224F8; /* jne: not equal / not zero */

loc_002224E9: ;
    MEM8(eax + 3) = MEM8(eax + 3) + 1;
    SET_LO8(ebx, MEM8(eax + 3));
    SET_LO8(edx, LO8(edx) << 1);
    _fa = (uint32_t)(LO8(ebx)) & 0xFFu; _fb = (uint32_t)(MEM8(eax + 2)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp LO8(ebx), MEM8(eax + 2) (8-bit) */
    if (CMP_BE(_fa, _fb)) goto loc_002224E4; /* jbe: below or equal (unsigned <=) */

loc_002224F6: ;
    goto loc_00222500;

loc_002224F8: ;
    SET_LO8(edx, ~LO8(edx));
    SET_LO8(edx, LO8(edx) & MEM8(eax + 4));
    MEM8(eax + 4) = LO8(edx);

loc_00222500: ;
    SET_LO8(ebx, MEM8(eax + 3));
    _fa = (uint32_t)(LO8(ebx)) & 0xFFu; _fb = (uint32_t)(MEM8(eax + 2)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp LO8(ebx), MEM8(eax + 2) (8-bit) */
    MEM8(eax + 0x26) = LO8(ecx);
    MEM8(eax + 0x24) = 2;
    MEM32(eax + 0x14) = edi;
    esi = eax + 8;
    if (CMP_BE(_fa, _fb)) goto loc_00222543; /* jbe: below or equal (unsigned <=) */

loc_00222515: ;
    edx = MEM32(eax + 0x3C);
    MEM32(eax + 0x18) = edx;
    edx = eax + 0x38;
    MEM32(eax + 0x20) = edx;
    edx = ZX8(MEM8(eax + 7));
    PUSH32(esp, ecx);
    PUSH32(esp, eax);
    MEM8(esi) = 0x28;
    MEM8(eax + 9) = 0x41;
    MEM32(eax + 0x10) = 0x2222D0;
    MEM32(eax + 0x1C) = edx;
    MEM8(eax + 0x25) = 1;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00222541u); sub_00221D43(); /* call 0x00221D43 */

loc_00222541: ;
    goto loc_0022258B;

loc_00222543: ;
    _fa = (uint32_t)(LO8(ebx)) & 0xFFu; _fb = (uint32_t)(LO8(ecx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp LO8(ebx), LO8(ecx) (8-bit) */
    edx = eax + 0x38;
    PUSH32(esp, 4);
    MEM32(eax + 0x20) = edx;
    POP32(esp, edx);
    MEM16(eax + 0x32) = LO16(ecx);
    MEM8(eax + 0x31) = LO8(ecx);
    MEM8(eax + 0x25) = LO8(ecx);
    MEM32(eax + 0x18) = ecx;
    MEM8(eax + 9) = 0x40;
    MEM8(esi) = 0x30;
    MEM16(eax + 0x36) = LO16(edx);
    MEM32(eax + 0x1C) = edx;
    if (CMP_NE(_fa, _fb)) goto loc_00222578; /* jne: not equal / not zero */

loc_0022256B: ;
    MEM32(eax + 0x10) = 0x22239C;
    MEM8(eax + 0x30) = 0xA0;
    goto loc_00222587;

loc_00222578: ;
    MEM32(eax + 0x10) = 0x2221CA;
    MEM8(eax + 0x30) = 0xA3;
    SET_LO16(ecx, ZX8(LO8(ebx)));

loc_00222587: ;
    MEM16(eax + 0x34) = LO16(ecx);

loc_0022258B: ;
    PUSH32(esp, esi);
    ecx = edi;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00222593u); sub_00221B1F(); /* call 0x00221B1F */

loc_00222593: ;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebx);
    POP32(esp, ebp);
    esp += 8; return; /* ret 4 */

}

/**
 * sub_0022259A
 * Original: 0x0022259A - 0x002225CA (48 bytes, 16 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0022259A(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_0022259A: ;
    PUSH32(esp, esi);
    esi = MEM32(esp + 0xC);
    ecx = esi;
    PUSH32(esp, 0x002225A6u); sub_002217D6(); /* call 0x002217D6 */

loc_002225A6: ;
    _fa = (uint32_t)(MEM8(eax)) & 0xFFu; _fb = (uint32_t)(2) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(eax), 2 (8-bit) */
    PUSH32(esp, esi);
    if (TEST_Z(_fa, _fb)) goto loc_002225B3; /* je: equal / zero */

loc_002225AC: ;
    PUSH32(esp, 0x002225B1u); sub_00222107(); /* call 0x00222107 */

loc_002225B1: ;
    goto loc_002225C6;

loc_002225B3: ;
    _fa = (uint32_t)(MEM16(eax + 0x3A)) & 0xFFFFu; _fb = (uint32_t)(0) & 0xFFFFu;
    _fas = (int32_t)(int16_t)(_fa); _fbs = (int32_t)(int16_t)(_fb); /* cmp MEM16(eax + 0x3A), 0 (16-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_002225C1; /* je: equal / zero */

loc_002225BA: ;
    PUSH32(esp, 0x002225BFu); sub_00221E4D(); /* call 0x00221E4D */

loc_002225BF: ;
    goto loc_002225C6;

loc_002225C1: ;
    PUSH32(esp, 0x002225C6u); sub_002224C7(); /* call 0x002224C7 */

loc_002225C6: ;
    POP32(esp, esi);
    esp += 12; return; /* ret 8 */

}

/**
 * sub_00222771
 * Original: 0x00222771 - 0x00222897 (294 bytes, 90 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00222771(void)
{
    uint32_t ebp;
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00222771: ;
    PUSH32(esp, ebp);
    ebp = esp;
    g_ebp = ebp; /* publish frame for frameless callees */
    ecx = MEM32(ebp + 0xC);
    PUSH32(esp, ebx);
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x0022277Fu); sub_002217D6(); /* call 0x002217D6 */

loc_0022277F: ;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 0x286CD0);
    edi = eax;
    { uint32_t _icall_target = MEM32(0x225B58); PUSH32(esp, 0x0022278Cu); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_0022278C: ;
    esi = MEM32(ebp + 8);
    ebx = 0; /* xor self */
    _fa = (uint32_t)(MEM32(esi + 4)) & 0xFFFFFFFFu; _fb = (uint32_t)(ebx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(esi + 4), ebx (32-bit) */
    if (CMP_L(_fas, _fbs)) goto loc_00222887; /* jl: less (signed <) */

loc_0022279A: ;
    SET_LO16(ecx, MEM16(0x286C6A));
    edx = 0; /* xor self */
    _fa = (uint32_t)(LO16(ecx)) & 0xFFFFu; _fb = (uint32_t)(0x30) & 0xFFFFu;
    _fas = (int32_t)(int16_t)(_fa); _fbs = (int32_t)(int16_t)(_fb); /* cmp LO16(ecx), 0x30 (16-bit) */
    eax = 0x286C68;
    if (CMP_A(_fa, _fb)) goto loc_00222887; /* ja: above (unsigned >) */

loc_002227B2: ;
    ecx = ZX16(LO16(ecx));
    _fa = (uint32_t)(MEM32(esi + 0x14)) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(esi + 0x14), ecx (32-bit) */
    MEM32(ebp + 8) = ecx;
    if (CMP_B(_fa, _fb)) goto loc_00222887; /* jb: below (unsigned <) */

loc_002227C1: ;
    SET_LO8(eax, MEM8(eax));
    ecx = ZX8(LO8(eax));
    edx = edx + ecx;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(ebx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp LO8(eax), LO8(ebx) (8-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_00222887; /* je: equal / zero */

loc_002227D0: ;
    _fa = (uint32_t)(edx) & 0xFFFFFFFFu; _fb = (uint32_t)(MEM32(ebp + 8)) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edx, MEM32(ebp + 8) (32-bit) */
    if (CMP_AE(_fa, _fb)) goto loc_00222887; /* jae: above or equal (unsigned >=) */

loc_002227D9: ;
    eax = edx + 0x286C68;
    _fa = (uint32_t)(MEM8(eax + 1)) & 0xFFu; _fb = (uint32_t)(5) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(eax + 1), 5 (8-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_002227C1; /* jne: not equal / not zero */

loc_002227E5: ;
    _fa = (uint32_t)(MEM16(eax + 4)) & 0xFFFFu; _fb = (uint32_t)(4) & 0xFFFFu;
    _fas = (int32_t)(int16_t)(_fa); _fbs = (int32_t)(int16_t)(_fb); /* cmp MEM16(eax + 4), 4 (16-bit) */
    if (CMP_A(_fa, _fb)) goto loc_002227F4; /* ja: above (unsigned >) */

loc_002227EC: ;
    SET_LO8(ecx, MEM8(eax + 4));
    MEM8(edi + 7) = LO8(ecx);
    goto loc_002227F8;

loc_002227F4: ;
    MEM8(edi + 7) = 4;

loc_002227F8: ;
    SET_LO8(ecx, MEM8(eax + 2));
    MEM8(edi + 1) = LO8(ecx);
    MEM8(esi) = 0x20;
    MEM8(esi + 1) = 2;
    MEM32(esi + 8) = ebx;
    SET_LO8(ecx, MEM8(eax + 2));
    MEM8(esi + 0x15) = LO8(ecx);
    SET_LO8(eax, MEM8(eax + 3));
    ecx = MEM32(ebp + 0xC);
    SET_LO8(eax, LO8(eax) & 3);
    MEM8(esi + 0x16) = LO8(eax);
    MEM8(esi + 0x17) = 0x10;
    SET_LO16(eax, ZX8(MEM8(edi + 7)));
    PUSH32(esp, esi);
    MEM16(esi + 0x1C) = LO16(eax);
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x0022282Cu); sub_00221B1F(); /* call 0x00221B1F */

loc_0022282C: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_S(_fas, _fbs)) goto loc_00222887; /* jl: less (signed <) */

loc_00222830: ;
    eax = MEM32(esi + 0x10);
    MEM32(edi + 0x3C) = eax;
    edi = MEM32(ebp + 0xC);
    MEM8(esi) = 0x30;
    MEM8(esi + 1) = 0x40;
    MEM32(esi + 8) = 0x2226F5;
    MEM32(esi + 0xC) = edi;
    MEM32(esi + 0x10) = ebx;
    MEM32(esi + 0x18) = ebx;
    MEM32(esi + 0x14) = ebx;
    MEM8(esi + 0x1C) = LO8(ebx);
    MEM8(esi + 0x1D) = LO8(ebx);
    MEM8(esi + 0x1E) = LO8(ebx);
    MEM8(esi + 0x28) = LO8(ebx);
    MEM8(esi + 0x29) = 9;
    SET_LO16(eax, ZX8(MEM8(0x286C6D)));
    PUSH32(esp, ebx);
    MEM16(esi + 0x2A) = LO16(eax);
    MEM16(esi + 0x2C) = LO16(ebx);
    MEM16(esi + 0x2E) = LO16(ebx);
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x0022287Du); sub_00221DEA(); /* call 0x00221DEA */

loc_0022287D: ;
    PUSH32(esp, esi);
    ecx = edi;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00222885u); sub_00221B1F(); /* call 0x00221B1F */

loc_00222885: ;
    goto loc_00222890;

loc_00222887: ;
    PUSH32(esp, MEM32(ebp + 0xC));
    PUSH32(esp, esi);
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00222890u); sub_002220E5(); /* call 0x002220E5 */

loc_00222890: ;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebx);
    POP32(esp, ebp);
    esp += 12; return; /* ret 8 */

}

/**
 * sub_00222979
 * Original: 0x00222979 - 0x00222A08 (143 bytes, 56 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00222979(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_00222979: ;
    PUSH32(esp, ecx);
    PUSH32(esp, ebx);
    PUSH32(esp, ebp);
    PUSH32(esp, esi);
    esi = ecx;
    _fa = (uint32_t)(MEM8(esi + 0x460)) & 0xFFu; _fb = (uint32_t)(0) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(esi + 0x460), 0 (8-bit) */
    ebp = edx;
    SET_LO8(ebx, 1);
    if (CMP_BE(_fa, _fb)) goto loc_00222A03; /* jbe: below or equal (unsigned <=) */

loc_0022298C: ;
    MEM8(esp + 0xC) = LO8(ebx);
    PUSH32(esp, edi);

loc_00222991: ;
    SET_LO16(eax, ZX8(LO8(ebx)));
    _fa = (uint32_t)(MEM16(ebp)) & 0xFFFFu; _fb = (uint32_t)(LO16(eax)) & 0xFFFFu;
    _fas = (int32_t)(int16_t)(_fa); _fbs = (int32_t)(int16_t)(_fb); /* test MEM16(ebp), LO16(eax) (16-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_002229EE; /* je: equal / zero */

loc_0022299B: ;
    ecx = 0; /* xor self */
    SET_LO16(ecx, MEM16(ebp + 2));
    ecx = ecx & eax;
    _fa = (uint32_t)(LO16(ecx)) & 0xFFFFu; _fb = (uint32_t)(LO16(ecx)) & 0xFFFFu;
    _fas = (int32_t)(int16_t)(_fa); _fbs = (int32_t)(int16_t)(_fb); /* test LO16(ecx), LO16(ecx) (16-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_002229D0; /* je: equal / zero */

loc_002229A8: ;
    ecx = esi + 0x461;
    SET_LO8(eax, MEM8(ecx));
    _fa = (uint32_t)(LO8(ebx)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(ebx), LO8(eax) (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_002229C0; /* je: equal / zero */

loc_002229B4: ;
    PUSH32(esp, MEM32(esp + 0x10));
    PUSH32(esp, esi);
    PUSH32(esp, 0x002229BEu); sub_00220CE9(); /* call 0x00220CE9 */

loc_002229BE: ;
    goto loc_002229C4;

loc_002229C0: ;
    SET_LO8(eax, LO8(eax) | LO8(ebx));
    MEM8(ecx) = LO8(eax);

loc_002229C4: ;
    PUSH32(esp, MEM32(esp + 0x10));
    PUSH32(esp, esi);
    PUSH32(esp, 0x002229CEu); sub_002209B9(); /* call 0x002209B9 */

loc_002229CE: ;
    goto loc_002229EE;

loc_002229D0: ;
    edi = esi + 0x461;
    SET_LO8(eax, MEM8(edi));
    _fa = (uint32_t)(LO8(ebx)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(ebx), LO8(eax) (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_002229EE; /* je: equal / zero */

loc_002229DC: ;
    PUSH32(esp, MEM32(esp + 0x10));
    SET_LO8(ecx, LO8(ebx));
    SET_LO8(ecx, ~LO8(ecx));
    SET_LO8(ecx, LO8(ecx) & LO8(eax));
    PUSH32(esp, esi);
    MEM8(edi) = LO8(ecx);
    PUSH32(esp, 0x002229EEu); sub_00220CE9(); /* call 0x00220CE9 */

loc_002229EE: ;
    MEM8(esp + 0x10) = MEM8(esp + 0x10) + 1;
    SET_LO8(eax, MEM8(esp + 0x10));
    SET_LO8(ebx, LO8(ebx) << 1);
    SET_LO8(eax, LO8(eax) - 1);
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(MEM8(esi + 0x460)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp LO8(eax), MEM8(esi + 0x460) (8-bit) */
    if (CMP_B(_fa, _fb)) goto loc_00222991; /* jb: below (unsigned <) */

loc_00222A02: ;
    POP32(esp, edi);

loc_00222A03: ;
    POP32(esp, esi);
    POP32(esp, ebp);
    POP32(esp, ebx);
    POP32(esp, ecx);
    esp += 4; return; /* ret */

}

/**
 * sub_00222A08
 * Original: 0x00222A08 - 0x00222A55 (77 bytes, 25 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00222A08(void)
{
    uint32_t ebp;

loc_00222A08: ;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, ebp);
    ebp = esp;
    g_ebp = ebp; /* publish frame for frameless callees */
    eax = MEM32(ebp + 8);
    ecx = MEM32(ebp + 0x10);
    edx = MEM32(ebp + 0xC);
    MEM32(eax + 0x470) = ecx;
    ecx = MEM32(ebp + 0x14);
    PUSH32(esp, esi);
    MEM32(eax + 0x474) = ecx;
    ecx = MEM32(eax);
    MEM16(ebp + 8) = 0x10;
    esi = MEM32(ebp + 8);
    MEM32(ecx + edx * 4 + 0x50) = esi;
    esi = eax + 0x4A0;
    PUSH32(esp, esi);
    edx = edx | 0xFFFFFFFFu;
    PUSH32(esp, edx);
    ecx = 0xFFF0BDC0u;
    PUSH32(esp, ecx);
    eax = eax + 0x478;
    PUSH32(esp, eax);
    { uint32_t _icall_target = MEM32(0x225B28); PUSH32(esp, 0x00222A50u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00222A50: ;
    POP32(esp, esi);
    POP32(esp, ebp);
    esp += 20; return; /* ret 16 */

}

/**
 * sub_00222A55
 * Original: 0x00222A55 - 0x00222A72 (29 bytes, 11 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00222A55(void)
{
    uint32_t ebp;

loc_00222A55: ;
    PUSH32(esp, ebp);
    ebp = esp;
    g_ebp = ebp; /* publish frame for frameless callees */
    PUSH32(esp, ecx);
    eax = MEM32(ebp + 8);
    eax = MEM32(eax);
    ecx = MEM32(ebp + 0xC);
    MEM16(ebp + -4) = 1;
    edx = MEM32(ebp + -4);
    MEM32(eax + ecx * 4 + 0x50) = edx;
    esp = ebp;
    POP32(esp, ebp); /* leave */
    esp += 12; return; /* ret 8 */

}

/**
 * sub_00222A9D
 * Original: 0x00222A9D - 0x00222B5C (191 bytes, 64 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00222A9D(void)
{
    uint32_t ebp;
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00222A9D: ;
    PUSH32(esp, ebp);
    ebp = esp;
    g_ebp = ebp; /* publish frame for frameless callees */
    esp = esp - 0x1C;
    PUSH32(esp, esi);
    esi = ecx;
    eax = MEM32(esi);
    edx = ZX8(MEM8(esi + 0x460));
    ecx = eax + 0x54;
    eax = MEM32(ecx);
    PUSH32(esp, edi);
    eax = 0; /* xor self */
    _fa = (uint32_t)(edx) & 0xFFFFFFFFu; _fb = (uint32_t)(edx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test edx, edx (32-bit) */
    edi = ebp + -8;
    MEM32(edi) = eax; edi += 4; /* stosd */
    MEM32(ebp + -12) = 1;
    if (CMP_BE(_fa & _fb, 0)) goto loc_00222B4E; /* jbe: below or equal (unsigned <=) */

loc_00222ACA: ;
    MEM32(ebp + -16) = ecx;
    MEM32(ebp + -20) = edx;
    PUSH32(esp, ebx);

loc_00222AD1: ;
    edi = MEM32(ecx);
    MEM32(ebp + -4) = edi;
    _fa = (uint32_t)(MEM8(ebp + -2)) & 0xFFu; _fb = (uint32_t)(0x10) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(ebp + -2), 0x10 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00222B1B; /* je: equal / zero */

loc_00222ADC: ;
    ecx = MEM32(esi + 0x474);
    ebx = esi + 0x470;
    eax = MEM32(ebx);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    MEM32(ebp + -28) = eax;
    MEM32(ebp + -24) = ecx;
    if (TEST_Z(_fa, _fb)) goto loc_00222B1B; /* je: equal / zero */

loc_00222AF4: ;
    eax = esi + 0x478;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, eax);
    { uint32_t _icall_target = MEM32(0x225B58); PUSH32(esp, 0x00222B01u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00222B01: ;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, MEM32(ebp + -24));
    MEM32(ebx) = MEM32(ebx) & 0;
    MEM32(esi + 0x474) = MEM32(esi + 0x474) & 0;
    edi = edi & 0x200;
    edi = edi << 0xF;
    PUSH32(esp, edi);
    { uint32_t _icall_target = MEM32(ebp + -28); PUSH32(esp, 0x00222B1Bu); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00222B1B: ;
    _fa = (uint32_t)(MEM8(ebp + -2)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(ebp + -2), 1 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00222B32; /* je: equal / zero */

loc_00222B21: ;
    eax = MEM32(ebp + -12);
    MEM16(ebp + -8) = MEM16(ebp + -8) | LO16(eax);
    _fa = (uint32_t)(MEM8(ebp + -4)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(ebp + -4), 1 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00222B32; /* je: equal / zero */

loc_00222B2E: ;
    MEM16(ebp + -6) = MEM16(ebp + -6) | LO16(eax);

loc_00222B32: ;
    MEM16(ebp + -4) = MEM16(ebp + -4) & 0;
    ecx = MEM32(ebp + -16);
    eax = MEM32(ebp + -4);
    MEM32(ebp + -12) = MEM32(ebp + -12) << 1;
    MEM32(ecx) = eax;
    ecx = ecx + 4;
    MEM32(ebp + -20) = MEM32(ebp + -20) - 1;
    MEM32(ebp + -16) = ecx;
    if ((MEM32(ebp + -20) != 0)) goto loc_00222AD1; /* jne: not equal / not zero */

loc_00222B4D: ;
    POP32(esp, ebx);

loc_00222B4E: ;
    edx = ebp + -8;
    ecx = esi;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00222B58u); sub_00222979(); /* call 0x00222979 */

loc_00222B58: ;
    POP32(esp, edi);
    POP32(esp, esi);
    esp = ebp;
    POP32(esp, ebp); /* leave */
    esp += 4; return; /* ret */

}

/**
 * sub_00222B5C
 * Original: 0x00222B5C - 0x00222B6F (19 bytes, 6 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00222B5C(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00222B5C: ;
    eax = MEM32(0x287888);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00222B6E; /* je: equal / zero */

loc_00222B65: ;
    ecx = MEM32(eax + 0x18);
    MEM32(0x287888) = ecx;

loc_00222B6E: ;
    esp += 4; return; /* ret */

}

/**
 * sub_00222B6F
 * Original: 0x00222B6F - 0x00222CE3 (372 bytes, 133 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00222B6F(void)
{
    uint32_t ebp;
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00222B6F: ;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, ebp);
    ebp = esp;
    g_ebp = ebp; /* publish frame for frameless callees */
    esp = esp - 0xC;
    MEM32(ebp + -8) = MEM32(ebp + -8) & 0;
    PUSH32(esp, ebx);
    PUSH32(esp, esi);
    ebx = edx;
    MEM32(ebp + -12) = ecx;
    { uint32_t _icall_target = MEM32(0x225B30); PUSH32(esp, 0x00222B86u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00222B86: ;
    MEM8(ebp + -1) = LO8(eax);
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00222B8Eu); sub_00222B5C(); /* call 0x00222B5C */

loc_00222B8E: ;
    esi = eax;
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(esi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test esi, esi (32-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_00222BA0; /* jne: not equal / not zero */

loc_00222B94: ;
    MEM32(ebp + -8) = 0x80000100u;
    goto loc_00222CCE;

loc_00222BA0: ;
    PUSH32(esp, edi);
    eax = 0; /* xor self */
    PUSH32(esp, 0xC);
    POP32(esp, ecx);
    edi = esi;
    { uint32_t _i; for (_i = 0; _i < ecx; _i++) MEM32(edi + _i*4) = eax; }
    edi += ecx * 4; ecx = 0; /* rep stosd */
    eax = esi;
    eax = eax - MEM32(0x287880);
    MEM32(esi + 0x14) = eax;
    SET_LO8(eax, MEM8(ebx + 0x16));
    MEM8(esi + 0x11) = LO8(eax);
    SET_LO8(eax, MEM8(ebx + 0x17));
    MEM8(esi + 0x13) = LO8(eax);
    eax = 0; /* xor self */
    SET_LO8(eax, MEM8(ebx + 0x1E));
    PUSH32(esp, eax);
    eax = 0; /* xor self */
    SET_LO8(eax, MEM8(esi + 0x11));
    PUSH32(esp, eax);
    eax = 0; /* xor self */
    SET_LO16(eax, MEM16(ebx + 0x1C));
    PUSH32(esp, eax);
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00222BD9u); sub_002231B8(); /* call 0x002231B8 */

loc_00222BD9: ;
    MEM16(esi + 0x22) = LO16(eax);
    eax = 0; /* xor self */
    SET_LO8(eax, MEM8(ebx + 0x14));
    eax = eax ^ MEM32(esi);
    eax = eax & 0x7F;
    MEM32(esi) = MEM32(esi) ^ eax;
    eax = ZX8(MEM8(ebx + 0x15));
    ecx = MEM32(esi);
    eax = eax << 7;
    eax = eax ^ ecx;
    eax = eax & 0x780;
    eax = eax ^ ecx;
    _fa = (uint32_t)(MEM8(esi + 0x11)) & 0xFFu; _fb = (uint32_t)(0) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(esi + 0x11), 0 (8-bit) */
    MEM32(esi) = eax;
    if (CMP_NE(_fa, _fb)) goto loc_00222C0C; /* jne: not equal / not zero */

loc_00222C03: ;
    eax = eax & 0xFFFFE7FFu;
    MEM32(esi) = eax;
    goto loc_00222C26;

loc_00222C0C: ;
    _fa = (uint32_t)(MEM8(ebx + 0x15)) & 0xFFu; _fb = (uint32_t)(0x80) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(ebx + 0x15), 0x80 (8-bit) */
    PUSH32(esp, 0);
    POP32(esp, ecx);
    SET_LO8(ecx, (TEST_NZ(_fa, _fb)) ? 1 : 0); /* setne */
    ecx++;
    ecx = ecx << 0xB;
    ecx = ecx ^ eax;
    ecx = ecx & 0x1800;
    ecx = ecx ^ eax;
    MEM32(esi) = ecx;

loc_00222C26: ;
    ecx = MEM32(esi);
    eax = 0; /* xor self */
    SET_LO8(eax, MEM8(ebx + 0x1E));
    ecx = ecx & 0xFFFF5FFFu;
    eax = eax & 1;
    eax = eax | 2;
    eax = eax << 0xD;
    eax = eax | ecx;
    MEM32(esi) = eax;
    ecx = ZX16(MEM16(ebx + 0x1C));
    ecx = ecx << 0x10;
    ecx = ecx ^ eax;
    ecx = ecx & 0x7FF0000;
    ecx = ecx ^ eax;
    eax = 0; /* xor self */
    MEM32(esi) = ecx;
    MEM32(esi + 0xC) = eax;
    MEM32(esi + 8) = eax;
    MEM32(esi + 4) = eax;
    edx = MEM32(ebx + 0x18);
    _fa = (uint32_t)(edx) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edx, eax (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_00222C8C; /* je: equal / zero */

loc_00222C65: ;
    eax = ecx;
    edi = 0; /* xor self */
    ecx = ecx >> 7;
    ecx = ecx & 0xF;
    edi++;
    eax = eax & 0x1800;
    edi = edi << LO8(ecx);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0x1000) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0x1000 (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_00222C81; /* jne: not equal / not zero */

loc_00222C7E: ;
    edi = edi << 0x10;

loc_00222C81: ;
    _fa = (uint32_t)(MEM32(edx)) & 0xFFFFFFFFu; _fb = (uint32_t)(edi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test MEM32(edx), edi (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00222C8C; /* je: equal / zero */

loc_00222C85: ;
    MEM32(esi + 8) = 2;

loc_00222C8C: ;
    SET_LO8(eax, MEM8(esi + 0x11));
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    POP32(esp, edi);
    if (TEST_Z(_fa, _fb)) goto loc_00222CA7; /* je: equal / zero */

loc_00222C94: ;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(2) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp LO8(eax), 2 (8-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_00222CA7; /* je: equal / zero */

loc_00222C98: ;
    ecx = MEM32(ebp + -12);
    edx = esi;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00222CA2u); sub_00224281(); /* call 0x00224281 */

loc_00222CA2: ;
    MEM32(ebp + -8) = eax;
    goto loc_00222CB1;

loc_00222CA7: ;
    ecx = MEM32(ebp + -12);
    edx = esi;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00222CB1u); sub_00224167(); /* call 0x00224167 */

loc_00222CB1: ;
    _fa = (uint32_t)(MEM32(ebp + -8)) & 0xFFFFFFFFu; _fb = (uint32_t)(0) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(ebp + -8), 0 (32-bit) */
    if (CMP_L(_fas, _fbs)) goto loc_00222CBC; /* jl: less (signed <) */

loc_00222CB7: ;
    MEM32(ebx + 0x10) = esi;
    goto loc_00222CCE;

loc_00222CBC: ;
    MEM32(ebx + 0x10) = MEM32(ebx + 0x10) & 0;
    eax = MEM32(0x287888);
    MEM32(esi + 0x18) = eax;
    MEM32(0x287888) = esi;

loc_00222CCE: ;
    esi = MEM32(ebp + -8);
    SET_LO8(ecx, MEM8(ebp + -1));
    MEM32(ebx + 4) = esi;
    { uint32_t _icall_esp = g_esp;
    { uint32_t _icall_target = MEM32(0x225B2C); PUSH32(esp, 0x00222CDDu); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00222CDD: ;
    eax = esi;
    POP32(esp, esi);
    POP32(esp, ebx);
    esp = ebp;
    POP32(esp, ebp); /* leave */
    esp += 4; return; /* ret */

}

/**
 * sub_00222CE3
 * Original: 0x00222CE3 - 0x00222D04 (33 bytes, 12 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00222CE3(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00222CE3: ;
    ecx = MEM32(edx + 0x10);
    eax = MEM32(ecx + 8);
    eax = eax & 1;
    MEM32(edx + 0x14) = eax;
    _fa = (uint32_t)(MEM8(ecx + 0x26)) & 0xFFu; _fb = (uint32_t)(0) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(ecx + 0x26), 0 (8-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_00222CFB; /* jne: not equal / not zero */

loc_00222CF5: ;
    _fa = (uint32_t)(MEM8(ecx + 0x27)) & 0xFFu; _fb = (uint32_t)(0) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(ecx + 0x27), 0 (8-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_00222D01; /* je: equal / zero */

loc_00222CFB: ;
    eax = eax | 2;
    MEM32(edx + 0x14) = eax;

loc_00222D01: ;
    eax = 0; /* xor self */
    esp += 4; return; /* ret */

}

/**
 * sub_00222D04
 * Original: 0x00222D04 - 0x00222D32 (46 bytes, 17 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00222D04(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00222D04: ;
    eax = MEM32(edx + 0x10);
    edx = MEM32(edx + 0x14);
    _fa = (uint32_t)(LO8(edx)) & 0xFFu; _fb = (uint32_t)(4) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(edx), 4 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00222D13; /* je: equal / zero */

loc_00222D0F: ;
    MEM32(eax + 8) = MEM32(eax + 8) & 0xFFFFFFFDu;

loc_00222D13: ;
    _fa = (uint32_t)(LO8(edx)) & 0xFFu; _fb = (uint32_t)(8) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(edx), 8 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00222D1C; /* je: equal / zero */

loc_00222D18: ;
    MEM32(eax + 8) = MEM32(eax + 8) | 2;

loc_00222D1C: ;
    _fa = (uint32_t)(LO8(edx)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(edx), 1 (8-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_00222D2F; /* jne: not equal / not zero */

loc_00222D21: ;
    ecx = MEM32(eax + 8);
    _fa = (uint32_t)(LO8(ecx)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(ecx), 1 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00222D2F; /* je: equal / zero */

loc_00222D29: ;
    ecx = ecx & 0xFFFFFFFEu;
    MEM32(eax + 8) = ecx;

loc_00222D2F: ;
    eax = 0; /* xor self */
    esp += 4; return; /* ret */

}

/**
 * sub_00222D32
 * Original: 0x00222D32 - 0x00222D6B (57 bytes, 22 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00222D32(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00222D32: ;
    eax = MEM32(ecx + 0x41C);
    PUSH32(esp, esi);
    esi = 0; /* xor self */
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(edx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, edx (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_00222D4C; /* je: equal / zero */

loc_00222D3F: ;
    esi = eax;
    eax = MEM32(eax + 0x24);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(edx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, edx (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_00222D3F; /* jne: not equal / not zero */

loc_00222D48: ;
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(esi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test esi, esi (32-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_00222D57; /* jne: not equal / not zero */

loc_00222D4C: ;
    eax = MEM32(eax + 0x24);
    MEM32(ecx + 0x41C) = eax;
    goto loc_00222D5D;

loc_00222D57: ;
    eax = MEM32(eax + 0x24);
    MEM32(esi + 0x24) = eax;

loc_00222D5D: ;
    eax = ecx + 0x420;
    _fa = (uint32_t)(edx) & 0xFFFFFFFFu; _fb = (uint32_t)(MEM32(eax)) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edx, MEM32(eax) (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_00222D69; /* jne: not equal / not zero */

loc_00222D67: ;
    MEM32(eax) = esi;

loc_00222D69: ;
    POP32(esp, esi);
    esp += 4; return; /* ret */

}

/**
 * sub_00222D6B
 * Original: 0x00222D6B - 0x00222DA4 (57 bytes, 22 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00222D6B(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00222D6B: ;
    eax = MEM32(ecx + 0x424);
    PUSH32(esp, esi);
    esi = 0; /* xor self */
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(edx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, edx (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_00222D85; /* je: equal / zero */

loc_00222D78: ;
    esi = eax;
    eax = MEM32(eax + 0x24);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(edx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, edx (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_00222D78; /* jne: not equal / not zero */

loc_00222D81: ;
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(esi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test esi, esi (32-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_00222D90; /* jne: not equal / not zero */

loc_00222D85: ;
    eax = MEM32(eax + 0x24);
    MEM32(ecx + 0x424) = eax;
    goto loc_00222D96;

loc_00222D90: ;
    eax = MEM32(eax + 0x24);
    MEM32(esi + 0x24) = eax;

loc_00222D96: ;
    eax = ecx + 0x428;
    _fa = (uint32_t)(edx) & 0xFFFFFFFFu; _fb = (uint32_t)(MEM32(eax)) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edx, MEM32(eax) (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_00222DA2; /* jne: not equal / not zero */

loc_00222DA0: ;
    MEM32(eax) = esi;

loc_00222DA2: ;
    POP32(esp, esi);
    esp += 4; return; /* ret */

}

/**
 * sub_00222DA4
 * Original: 0x00222DA4 - 0x00222DD3 (47 bytes, 21 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00222DA4(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00222DA4: ;
    eax = MEM32(ecx + 0x28);
    PUSH32(esp, esi);
    esi = 0; /* xor self */
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(edx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, edx (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_00222DBB; /* je: equal / zero */

loc_00222DAE: ;
    esi = eax;
    eax = MEM32(eax + 0x24);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(edx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, edx (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_00222DAE; /* jne: not equal / not zero */

loc_00222DB7: ;
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(esi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test esi, esi (32-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_00222DC3; /* jne: not equal / not zero */

loc_00222DBB: ;
    eax = MEM32(eax + 0x24);
    MEM32(ecx + 0x28) = eax;
    goto loc_00222DC9;

loc_00222DC3: ;
    eax = MEM32(eax + 0x24);
    MEM32(esi + 0x24) = eax;

loc_00222DC9: ;
    _fa = (uint32_t)(edx) & 0xFFFFFFFFu; _fb = (uint32_t)(MEM32(ecx + 0x2C)) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edx, MEM32(ecx + 0x2C) (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_00222DD1; /* jne: not equal / not zero */

loc_00222DCE: ;
    MEM32(ecx + 0x2C) = esi;

loc_00222DD1: ;
    POP32(esp, esi);
    esp += 4; return; /* ret */

}

/**
 * sub_00222DD3
 * Original: 0x00222DD3 - 0x00222E49 (118 bytes, 46 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00222DD3(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_00222DD3: ;
    PUSH32(esp, ecx);
    PUSH32(esp, edi);
    edi = edx;
    _fa = (uint32_t)(MEM8(edi + 0x26)) & 0xFFu; _fb = (uint32_t)(0) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(edi + 0x26), 0 (8-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_00222E46; /* je: equal / zero */

loc_00222DDD: ;
    eax = ZX8(MEM8(edi + 0x11));
    eax = eax - 0;
    PUSH32(esp, ebx);
    PUSH32(esp, ebp);
    if ((eax == 0)) goto loc_00222E05; /* je: equal / zero */

loc_00222DE8: ;
    eax--;
    eax--;
    if ((eax == 0)) goto loc_00222DF7; /* je: equal / zero */

loc_00222DEC: ;
    eax--;
    if ((eax != 0)) goto loc_00222E44; /* jne: not equal / not zero */

loc_00222DEF: ;
    ebx = edi + 0x28;
    ebp = edi + 0x2C;
    goto loc_00222E11;

loc_00222DF7: ;
    ebx = ecx + 0x424;
    ebp = ecx + 0x428;
    goto loc_00222E11;

loc_00222E05: ;
    ebx = ecx + 0x41C;
    ebp = ecx + 0x420;

loc_00222E11: ;
    PUSH32(esp, esi);

loc_00222E12: ;
    esi = MEM32(ebx);
    _fa = (uint32_t)(MEM32(esi + 0x10)) & 0xFFFFFFFFu; _fb = (uint32_t)(edi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(esi + 0x10), edi (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_00222E30; /* jne: not equal / not zero */

loc_00222E19: ;
    eax = MEM32(esi + 0x24);
    MEM32(ebx) = eax;
    MEM32(esi + 4) = 0xC000000Fu;
    MEM8(edi + 0x26) = MEM8(edi + 0x26) - 1;
    PUSH32(esp, esi);
    PUSH32(esp, 0x00222E2Eu); sub_002231A4(); /* call 0x002231A4 */

loc_00222E2E: ;
    goto loc_00222E37;

loc_00222E30: ;
    MEM32(esp + 0x10) = esi;
    ebx = esi + 0x24;

loc_00222E37: ;
    _fa = (uint32_t)(MEM32(ebp)) & 0xFFFFFFFFu; _fb = (uint32_t)(esi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(ebp), esi (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_00222E12; /* jne: not equal / not zero */

loc_00222E3C: ;
    eax = MEM32(esp + 0x10);
    MEM32(ebp) = eax;
    POP32(esp, esi);

loc_00222E44: ;
    POP32(esp, ebp);
    POP32(esp, ebx);

loc_00222E46: ;
    POP32(esp, edi);
    POP32(esp, ecx);
    esp += 4; return; /* ret */

}

/**
 * sub_00222E49
 * Original: 0x00222E49 - 0x00222E86 (61 bytes, 24 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00222E49(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00222E49: ;
    PUSH32(esp, esi);
    esi = edx;
    MEM8(esi + 0x20) = MEM8(esi + 0x20) + 1;
    _fa = (uint32_t)(MEM8(esi + 0x10)) & 0xFFu; _fb = (uint32_t)(0x20) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(esi + 0x10), 0x20 (8-bit) */
    PUSH32(esp, edi);
    edi = ecx;
    if (TEST_NZ(_fa, _fb)) goto loc_00222E83; /* jne: not equal / not zero */

loc_00222E58: ;
    MEM8(esi + 1) = MEM8(esi + 1) | 0x40;
    PUSH32(esp, 0x00222E61u); sub_0022466C(); /* call 0x0022466C */

loc_00222E61: ;
    eax++;
    MEM32(esi + 0x1C) = eax;
    _fa = (uint32_t)(MEM32(edi + 0x438)) & 0xFFFFFFFFu; _fb = (uint32_t)(0) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(edi + 0x438), 0 (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_00222E72; /* je: equal / zero */

loc_00222E6E: ;
    MEM8(esi + 0x10) = MEM8(esi + 0x10) | 0x40;

loc_00222E72: ;
    ecx = MEM32(edi);
    PUSH32(esp, 4);
    POP32(esp, eax);
    MEM32(ecx + 0xC) = eax;
    ecx = MEM32(edi);
    MEM32(ecx + 0x10) = eax;
    MEM8(esi + 0x10) = MEM8(esi + 0x10) | 0x20;

loc_00222E83: ;
    POP32(esp, edi);
    POP32(esp, esi);
    esp += 4; return; /* ret */

}

/**
 * sub_00222EC1
 * Original: 0x00222EC1 - 0x00222F78 (183 bytes, 61 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00222EC1(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00222EC1: ;
    PUSH32(esp, esi);
    esi = MEM32(esp + 0xC);
    _fa = (uint32_t)(MEM8(esi + 0x22)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(esi + 0x22), 1 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00222ED6; /* je: equal / zero */

loc_00222ECC: ;
    eax = 0x40020000;
    goto loc_00222F74;

loc_00222ED6: ;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, ebx);
    PUSH32(esp, edi);
    { uint32_t _icall_target = MEM32(0x225B30); PUSH32(esp, 0x00222EDEu); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00222EDE: ;
    edi = MEM32(esi + 0x10);
    _fa = (uint32_t)(MEM8(edi + 0x10)) & 0xFFu; _fb = (uint32_t)(0x10) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(edi + 0x10), 0x10 (8-bit) */
    SET_LO8(ebx, LO8(eax));
    if (TEST_NZ(_fa, _fb)) goto loc_00222F63; /* jne: not equal / not zero */

loc_00222EE9: ;
    SET_LO16(eax, MEM16(esi + 0x22));
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(2) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), 2 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00222F43; /* je: equal / zero */

loc_00222EF1: ;
    eax = ZX8(MEM8(edi + 0x11));
    eax = eax - 0;
    if ((eax == 0)) goto loc_00222F20; /* je: equal / zero */

loc_00222EFA: ;
    eax--;
    eax--;
    if ((eax == 0)) goto loc_00222F13; /* je: equal / zero */

loc_00222EFE: ;
    eax--;
    if ((eax == 0)) goto loc_00222F08; /* je: equal / zero */

loc_00222F01: ;
    esi = 0x80000600u;
    goto loc_00222F68;

loc_00222F08: ;
    edx = esi;
    ecx = edi;
    PUSH32(esp, 0x00222F11u); sub_00222DA4(); /* call 0x00222DA4 */

loc_00222F11: ;
    goto loc_00222F2B;

loc_00222F13: ;
    ecx = MEM32(esp + 0x10);
    edx = esi;
    PUSH32(esp, 0x00222F1Eu); sub_00222D6B(); /* call 0x00222D6B */

loc_00222F1E: ;
    goto loc_00222F2B;

loc_00222F20: ;
    ecx = MEM32(esp + 0x10);
    edx = esi;
    PUSH32(esp, 0x00222F2Bu); sub_00222D32(); /* call 0x00222D32 */

loc_00222F2B: ;
    MEM8(edi + 0x26) = MEM8(edi + 0x26) - 1;
    MEM8(esi + 0x22) = MEM8(esi + 0x22) | 1;
    PUSH32(esp, esi);
    MEM32(esi + 4) = 0xC000000Fu;
    PUSH32(esp, 0x00222F3Fu); sub_002231A4(); /* call 0x002231A4 */

loc_00222F3F: ;
    esi = 0; /* xor self */
    goto loc_00222F68;

loc_00222F43: ;
    ecx = MEM32(esp + 0x10);
    SET_LO16(eax, LO16(eax) | 1);
    MEM16(esi + 0x22) = LO16(eax);
    eax = ecx + 0x42C;
    edx = MEM32(eax);
    MEM32(esi + 0x24) = edx;
    edx = edi;
    MEM32(eax) = esi;
    PUSH32(esp, 0x00222F63u); sub_00222E49(); /* call 0x00222E49 */

loc_00222F63: ;
    esi = 0x40020000;

loc_00222F68: ;
    SET_LO8(ecx, LO8(ebx));
    { uint32_t _icall_esp = g_esp;
    { uint32_t _icall_target = MEM32(0x225B2C); PUSH32(esp, 0x00222F70u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00222F70: ;
    POP32(esp, edi);
    eax = esi;
    POP32(esp, ebx);

loc_00222F74: ;
    POP32(esp, esi);
    esp += 12; return; /* ret 8 */

}

/**
 * sub_00222F78
 * Original: 0x00222F78 - 0x00222FDF (103 bytes, 40 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00222F78(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_00222F78: ;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, ebx);
    PUSH32(esp, ebp);
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    edi = edx;
    esi = MEM32(edi + 0x10);
    ebp = ecx;
    { uint32_t _icall_target = MEM32(0x225B30); PUSH32(esp, 0x00222F89u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00222F89: ;
    MEM8(esi + 0x10) = MEM8(esi + 0x10) | 0x10;
    edx = esi;
    ecx = ebp;
    SET_LO8(ebx, LO8(eax));
    PUSH32(esp, 0x00222F98u); sub_00222DD3(); /* call 0x00222DD3 */

loc_00222F98: ;
    SET_LO8(eax, MEM8(esi + 0x11));
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00222FAE; /* je: equal / zero */

loc_00222F9F: ;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(2) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp LO8(eax), 2 (8-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_00222FAE; /* je: equal / zero */

loc_00222FA3: ;
    edx = esi;
    ecx = ebp;
    PUSH32(esp, 0x00222FACu); sub_0022445D(); /* call 0x0022445D */

loc_00222FAC: ;
    goto loc_00222FB7;

loc_00222FAE: ;
    edx = esi;
    ecx = ebp;
    PUSH32(esp, 0x00222FB7u); sub_002241A4(); /* call 0x002241A4 */

loc_00222FB7: ;
    edx = esi;
    ecx = ebp;
    PUSH32(esp, 0x00222FC0u); sub_00222E49(); /* call 0x00222E49 */

loc_00222FC0: ;
    eax = ebp + 0x434;
    ecx = MEM32(eax);
    MEM32(edi + 0x14) = ecx;
    SET_LO8(ecx, LO8(ebx));
    MEM32(eax) = edi;
    { uint32_t _icall_esp = g_esp;
    { uint32_t _icall_target = MEM32(0x225B2C); PUSH32(esp, 0x00222FD5u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00222FD5: ;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebp);
    eax = 0x40000000;
    POP32(esp, ebx);
    esp += 4; return; /* ret */

}

/**
 * sub_00222FDF
 * Original: 0x00222FDF - 0x00223032 (83 bytes, 33 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00222FDF(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_00222FDF: ;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, ecx);
    PUSH32(esp, ebx);
    PUSH32(esp, ebp);
    PUSH32(esp, esi);
    esi = edx;
    PUSH32(esp, edi);
    edi = MEM32(esi + 0x10);
    ebp = ecx;
    ebx = 0; /* xor self */
    { uint32_t _icall_target = MEM32(0x225B30); PUSH32(esp, 0x00222FF3u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00222FF3: ;
    edx = edi;
    ecx = ebp;
    MEM8(esp + 0x13) = LO8(eax);
    PUSH32(esp, 0x00223000u); sub_00222DD3(); /* call 0x00222DD3 */

loc_00223000: ;
    _fa = (uint32_t)(MEM8(edi + 0x27)) & 0xFFu; _fb = (uint32_t)(LO8(ebx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(edi + 0x27), LO8(ebx) (8-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_00223020; /* je: equal / zero */

loc_00223005: ;
    eax = ebp + 0x430;
    ecx = MEM32(eax);
    MEM32(esi + 0x14) = ecx;
    edx = edi;
    ecx = ebp;
    MEM32(eax) = esi;
    PUSH32(esp, 0x0022301Bu); sub_00222E49(); /* call 0x00222E49 */

loc_0022301B: ;
    ebx = 0x40000000;

loc_00223020: ;
    SET_LO8(ecx, MEM8(esp + 0x13));
    { uint32_t _icall_esp = g_esp;
    { uint32_t _icall_target = MEM32(0x225B2C); PUSH32(esp, 0x0022302Au); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_0022302A: ;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebp);
    eax = ebx;
    POP32(esp, ebx);
    POP32(esp, ecx);
    esp += 4; return; /* ret */

}

/**
 * sub_00223032
 * Original: 0x00223032 - 0x0022314A (280 bytes, 98 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00223032(void)
{
    uint32_t ebp;
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00223032: ;
    PUSH32(esp, ebp);
    ebp = esp;
    g_ebp = ebp; /* publish frame for frameless callees */
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    edi = MEM32(ebp + 0xC);
    eax = ZX8(MEM8(edi + 1));
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0xC) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0xC (32-bit) */
    if (CMP_G(_fas, _fbs)) goto loc_002230CA; /* jg: greater (signed >) */

loc_00223047: ;
    if (CMP_EQ(_fa, _fb)) goto loc_002230BE; /* je: equal / zero */

loc_00223049: ;
    PUSH32(esp, 2);
    POP32(esp, ecx);
    eax = eax - ecx;
    if ((eax == 0)) goto loc_002230B2; /* je: equal / zero */

loc_00223050: ;
    eax = eax - ecx;
    if ((eax == 0)) goto loc_002230A6; /* je: equal / zero */

loc_00223054: ;
    eax--;
    if ((eax == 0)) goto loc_00223097; /* je: equal / zero */

loc_00223057: ;
    eax = eax - ecx;
    if ((eax == 0)) goto loc_00223085; /* je: equal / zero */

loc_0022305B: ;
    eax = eax - ecx;
    if ((eax == 0)) goto loc_00223076; /* je: equal / zero */

loc_0022305F: ;
    eax = eax - ecx;
    if ((eax != 0)) goto loc_00223118; /* jne: not equal / not zero */

loc_00223067: ;
    ecx = MEM32(ebp + 8);
    edx = edi;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00223071u); sub_0022504C(); /* call 0x0022504C */

loc_00223071: ;
    goto loc_00223129;

loc_00223076: ;
    ecx = MEM32(ebp + 8);
    edx = edi;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00223080u); sub_00224DD2(); /* call 0x00224DD2 */

loc_00223080: ;
    goto loc_00223129;

loc_00223085: ;
    ecx = MEM32(ebp + 8);
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x0022308Du); sub_0022466C(); /* call 0x0022466C */

loc_0022308D: ;
    MEM32(edi + 0x14) = eax;
    esi = 0; /* xor self */
    goto loc_0022312B;

loc_00223097: ;
    ecx = MEM32(ebp + 8);
    edx = edi;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x002230A1u); sub_00222D04(); /* call 0x00222D04 */

loc_002230A1: ;
    goto loc_00223129;

loc_002230A6: ;
    ecx = MEM32(ebp + 8);
    edx = edi;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x002230B0u); sub_00222CE3(); /* call 0x00222CE3 */

loc_002230B0: ;
    goto loc_00223129;

loc_002230B2: ;
    ecx = MEM32(ebp + 8);
    edx = edi;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x002230BCu); sub_00222B6F(); /* call 0x00222B6F */

loc_002230BC: ;
    goto loc_00223129;

loc_002230BE: ;
    ecx = MEM32(ebp + 8);
    edx = edi;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x002230C8u); sub_002251B3(); /* call 0x002251B3 */

loc_002230C8: ;
    goto loc_00223129;

loc_002230CA: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0xD) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0xD (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_0022311F; /* je: equal / zero */

loc_002230CF: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0x3F) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0x3F (32-bit) */
    if (CMP_LE(_fas, _fbs)) goto loc_00223118; /* jle: less or equal (signed <=) */

loc_002230D4: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0x41) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0x41 (32-bit) */
    if (CMP_LE(_fas, _fbs)) goto loc_0022310C; /* jle: less or equal (signed <=) */

loc_002230D9: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0x43) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0x43 (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_00223100; /* je: equal / zero */

loc_002230DE: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0x46) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0x46 (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_002230F4; /* je: equal / zero */

loc_002230E3: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0x4A) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0x4A (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_00223118; /* jne: not equal / not zero */

loc_002230E8: ;
    ecx = MEM32(ebp + 8);
    edx = edi;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x002230F2u); sub_00224F7F(); /* call 0x00224F7F */

loc_002230F2: ;
    goto loc_00223129;

loc_002230F4: ;
    ecx = MEM32(ebp + 8);
    edx = edi;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x002230FEu); sub_00222FDF(); /* call 0x00222FDF */

loc_002230FE: ;
    goto loc_00223129;

loc_00223100: ;
    ecx = MEM32(ebp + 8);
    edx = edi;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x0022310Au); sub_00222F78(); /* call 0x00222F78 */

loc_0022310A: ;
    goto loc_00223129;

loc_0022310C: ;
    ecx = MEM32(ebp + 8);
    edx = edi;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00223116u); sub_0022597C(); /* call 0x0022597C */

loc_00223116: ;
    goto loc_00223129;

loc_00223118: ;
    esi = 0x80000200u;
    goto loc_0022312B;

loc_0022311F: ;
    ecx = MEM32(ebp + 8);
    edx = edi;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00223129u); sub_002252D2(); /* call 0x002252D2 */

loc_00223129: ;
    esi = eax;

loc_0022312B: ;
    eax = esi;
    eax = eax & 0xC0000000u;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0x40000000) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0x40000000 (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_00223142; /* je: equal / zero */

loc_00223139: ;
    PUSH32(esp, edi);
    MEM32(edi + 4) = esi;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00223142u); sub_002231A4(); /* call 0x002231A4 */

loc_00223142: ;
    POP32(esp, edi);
    eax = esi;
    POP32(esp, esi);
    POP32(esp, ebp);
    esp += 12; return; /* ret 8 */

}

/**
 * sub_0022314A
 * Original: 0x0022314A - 0x002231A4 (90 bytes, 35 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0022314A(void)
{

loc_0022314A: ;
    eax = MEM32(esp + 4);
    PUSH32(esp, edi);
    edx = ecx;
    MEM32(edx + 0x98) = eax;
    eax = MEM32(esp + 0xC);
    MEM32(edx + 0x9C) = eax;
    eax = 0; /* xor self */
    MEM8(edx + 0xA0) = 0;
    MEM8(edx + 0xA1) = 0;
    PUSH32(esp, 0xC);
    POP32(esp, ecx);
    edi = edx;
    { uint32_t _i; for (_i = 0; _i < ecx; _i++) MEM32(edi + _i*4) = eax; }
    edi += ecx * 4; ecx = 0; /* rep stosd */
    MEM16(edi) = LO16(eax); edi += 2; /* stosw */
    eax = 0; /* xor self */
    PUSH32(esp, 0xC);
    POP32(esp, ecx);
    edi = edx + 0x32;
    { uint32_t _i; for (_i = 0; _i < ecx; _i++) MEM32(edi + _i*4) = eax; }
    edi += ecx * 4; ecx = 0; /* rep stosd */
    MEM16(edi) = LO16(eax); edi += 2; /* stosw */
    eax = 0; /* xor self */
    PUSH32(esp, 0xC);
    POP32(esp, ecx);
    edi = edx + 0x64;
    { uint32_t _i; for (_i = 0; _i < ecx; _i++) MEM32(edi + _i*4) = eax; }
    edi += ecx * 4; ecx = 0; /* rep stosd */
    MEM16(edi) = LO16(eax); edi += 2; /* stosw */
    eax = 0; /* xor self */
    edi = edx + 0xA4;
    MEM32(edi) = eax; edi += 4; /* stosd */
    MEM32(edi) = eax; edi += 4; /* stosd */
    MEM32(edi) = eax; edi += 4; /* stosd */
    MEM32(edi) = eax; edi += 4; /* stosd */
    eax = edx;
    POP32(esp, edi);
    esp += 12; return; /* ret 8 */

}

/**
 * sub_002231A4
 * Original: 0x002231A4 - 0x002231B8 (20 bytes, 8 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_002231A4(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_002231A4: ;
    eax = MEM32(esp + 4);
    ecx = MEM32(eax + 8);
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, ecx (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_002231B5; /* je: equal / zero */

loc_002231AF: ;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, MEM32(eax + 0xC));
    PUSH32(esp, eax);
    { uint32_t _icall_target = ecx; PUSH32(esp, 0x002231B5u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_002231B5: ;
    esp += 8; return; /* ret 4 */

}

/**
 * sub_002231B8
 * Original: 0x002231B8 - 0x00223201 (73 bytes, 26 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_002231B8(void)
{
    uint32_t ebp;
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_002231B8: ;
    PUSH32(esp, ebp);
    ebp = esp;
    g_ebp = ebp; /* publish frame for frameless callees */
    esp = esp - 0x10;
    eax = ZX8(MEM8(ebp + 0xC));
    MEM32(ebp + -16) = MEM32(ebp + -16) & 0;
    MEM32(ebp + -8) = MEM32(ebp + -8) & 0;
    MEM32(ebp + -12) = 9;
    MEM32(ebp + -4) = 0xD;
    ecx = MEM32(ebp + eax * 4 + -16);
    eax = ZX16(MEM16(ebp + 8));
    eax = eax + ecx;
    eax = (uint32_t)((int32_t)eax * (int32_t)0x38);
    PUSH32(esp, esi);
    PUSH32(esp, 6);
    edx = 0; /* xor self */
    POP32(esp, esi);
    { uint64_t _dividend = ((uint64_t)edx << 32) | eax;
      eax = (uint32_t)(_dividend / (uint32_t)esi);
      edx = (uint32_t)(_dividend % (uint32_t)esi); }
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, ecx (32-bit) */
    POP32(esp, esi);
    if (TEST_NZ(_fa, _fb)) goto loc_002231F4; /* jne: not equal / not zero */

loc_002231F2: ;
    eax = 0; /* xor self */

loc_002231F4: ;
    _fa = (uint32_t)(MEM8(ebp + 0x10)) & 0xFFu; _fb = (uint32_t)(0) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(ebp + 0x10), 0 (8-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_002231FD; /* je: equal / zero */

loc_002231FA: ;
    eax = eax << 3;

loc_002231FD: ;
    esp = ebp;
    POP32(esp, ebp); /* leave */
    esp += 16; return; /* ret 12 */

}

/**
 * sub_00223201
 * Original: 0x00223201 - 0x00223236 (53 bytes, 22 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00223201(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00223201: ;
    PUSH32(esp, esi);
    eax = 0x21F914;
    esi = 0x21F920;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(esi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, esi (32-bit) */
    ecx = eax;
    if (CMP_AE(_fa, _fb)) goto loc_0022322C; /* jae: above or equal (unsigned >=) */

loc_00223212: ;
    edx = MEM32(esp + 8);

loc_00223216: ;
    eax = MEM32(ecx);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00223225; /* je: equal / zero */

loc_0022321C: ;
    _fa = (uint32_t)(HI8(edx)) & 0xFFu; _fb = (uint32_t)(MEM8(eax + 1)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp HI8(edx), MEM8(eax + 1) (8-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_00223225; /* jne: not equal / not zero */

loc_00223221: ;
    _fa = (uint32_t)(LO8(edx)) & 0xFFu; _fb = (uint32_t)(MEM8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp LO8(edx), MEM8(eax) (8-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_00223232; /* je: equal / zero */

loc_00223225: ;
    ecx = ecx + 4;
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(esi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp ecx, esi (32-bit) */
    if (CMP_B(_fa, _fb)) goto loc_00223216; /* jb: below (unsigned <) */

loc_0022322C: ;
    eax = 0; /* xor self */

loc_0022322E: ;
    POP32(esp, esi);
    esp += 8; return; /* ret 4 */

loc_00223232: ;
    eax = MEM32(ecx);
    goto loc_0022322E;

}

/**
 * sub_00223236
 * Original: 0x00223236 - 0x00223251 (27 bytes, 8 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00223236(void)
{

loc_00223236: ;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 0x286DB0);
    ecx = ecx | 0xFFFFFFFFu;
    PUSH32(esp, ecx);
    eax = 0xFD050F80u;
    PUSH32(esp, eax);
    PUSH32(esp, 0x286D88);
    { uint32_t _icall_target = MEM32(0x225B28); PUSH32(esp, 0x00223250u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00223250: ;
    esp += 4; return; /* ret */

}

/**
 * sub_00223262
 * Original: 0x00223262 - 0x00223285 (35 bytes, 12 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00223262(void)
{

loc_00223262: ;
    PUSH32(esp, esi);
    esi = ecx;
    ecx = MEM32(esi);
    PUSH32(esp, 0);
    PUSH32(esp, 0x0022326Eu); sub_002217DA(); /* call 0x002217DA */

loc_0022326E: ;
    ecx = MEM32(esi);
    PUSH32(esp, 0x00223275u); sub_00220A35(); /* call 0x00220A35 */

loc_00223275: ;
    MEM32(esi) = MEM32(esi) & 0;
    MEM8(esi + 4) = MEM8(esi + 4) & 0xFE;
    MEM16(0x286D32) = MEM16(0x286D32) - 1;
    POP32(esp, esi);
    esp += 4; return; /* ret */

}

/**
 * sub_00223285
 * Original: 0x00223285 - 0x002232EF (106 bytes, 42 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00223285(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_00223285: ;
    PUSH32(esp, ecx);
    PUSH32(esp, ebx);
    PUSH32(esp, ebp);
    ebx = 0; /* xor self */
    ebp = 0; /* xor self */
    _fa = (uint32_t)(MEM16(0x286D30)) & 0xFFFFu; _fb = (uint32_t)(LO16(ebx)) & 0xFFFFu;
    _fas = (int32_t)(int16_t)(_fa); _fbs = (int32_t)(int16_t)(_fb); /* cmp MEM16(0x286D30), LO16(ebx) (16-bit) */
    PUSH32(esp, edi);
    MEM32(esp + 0xC) = edx;
    edi = ecx;
    if (CMP_BE(_fa, _fb)) goto loc_002232E8; /* jbe: below or equal (unsigned <=) */

loc_0022329C: ;
    PUSH32(esp, esi);

loc_0022329D: ;
    eax = MEM32(0x286D34);
    esi = ZX8(LO8(ebx));
    esi = (uint32_t)((int32_t)esi * (int32_t)0x16);
    eax = eax + esi;
    _fa = (uint32_t)(MEM8(eax + 4)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(eax + 4), 1 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_002232D8; /* je: equal / zero */

loc_002232B0: ;
    ecx = MEM32(eax);
    PUSH32(esp, 0x002232B7u); sub_002218DF(); /* call 0x002218DF */

loc_002232B7: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(MEM32(esp + 0x10)) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, MEM32(esp + 0x10) (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_002232D8; /* jne: not equal / not zero */

loc_002232BD: ;
    eax = MEM32(0x286D34);
    eax = eax + esi;
    _fa = (uint32_t)(MEM32(eax + 0xE)) & 0xFFFFFFFFu; _fb = (uint32_t)(edi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(eax + 0xE), edi (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_002232D8; /* jne: not equal / not zero */

loc_002232C9: ;
    SET_LO8(ecx, MEM8(eax + 4));
    _fa = (uint32_t)(LO8(ecx)) & 0xFFu; _fb = (uint32_t)(8) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(ecx), 8 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_002232D8; /* je: equal / zero */

loc_002232D1: ;
    _fa = (uint32_t)(LO8(ecx)) & 0xFFu; _fb = (uint32_t)(2) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(ecx), 2 (8-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_002232D8; /* jne: not equal / not zero */

loc_002232D6: ;
    ebp = eax;

loc_002232D8: ;
    SET_LO8(ebx, LO8(ebx) + 1);
    SET_LO16(eax, ZX8(LO8(ebx)));
    _fa = (uint32_t)(LO16(eax)) & 0xFFFFu; _fb = (uint32_t)(MEM16(0x286D30)) & 0xFFFFu;
    _fas = (int32_t)(int16_t)(_fa); _fbs = (int32_t)(int16_t)(_fb); /* cmp LO16(eax), MEM16(0x286D30) (16-bit) */
    if (CMP_B(_fa, _fb)) goto loc_0022329D; /* jb: below (unsigned <) */

loc_002232E7: ;
    POP32(esp, esi);

loc_002232E8: ;
    POP32(esp, edi);
    eax = ebp;
    POP32(esp, ebp);
    POP32(esp, ebx);
    POP32(esp, ecx);
    esp += 4; return; /* ret */

}

/**
 * sub_002232EF
 * Original: 0x002232EF - 0x0022339A (171 bytes, 62 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_002232EF(void)
{
    uint32_t ebp;
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_002232EF: ;
    PUSH32(esp, ebp);
    ebp = esp;
    g_ebp = ebp; /* publish frame for frameless callees */
    PUSH32(esp, ecx);
    PUSH32(esp, ebx);
    PUSH32(esp, esi);
    esi = ecx;
    MEM32(esi + 0x5A) = MEM32(esi + 0x5A) & 0;
    PUSH32(esp, edi);
    edi = MEM32(esi);
    ebx = esi + 0x52;
    MEM8(ebx) = 0x20;
    MEM8(esi + 0x53) = 0x82;
    ecx = MEM32(edi);
    PUSH32(esp, ebx);
    MEM32(ebp + -4) = edx;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00223313u); sub_00221B1F(); /* call 0x00221B1F */

loc_00223313: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_S(_fas, _fbs)) goto loc_00223395; /* jl: less (signed <) */

loc_00223317: ;
    MEM8(esi + 0xA2) = MEM8(esi + 0xA2) | 2;
    MEM32(esi + 0x5A) = MEM32(esi + 0x5A) & 0;
    MEM8(ebx) = 0x20;
    MEM8(esi + 0x53) = 2;
    SET_LO8(eax, MEM8(edi + 8));
    MEM8(esi + 0x67) = LO8(eax);
    eax = MEM32(ebp + -4);
    MEM8(esi + 0x68) = 3;
    SET_LO8(eax, MEM8(eax + 1));
    MEM8(esi + 0x69) = LO8(eax);
    MEM16(esi + 0x6E) = 0x20;
    ecx = MEM32(edi);
    PUSH32(esp, ebx);
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x0022334Au); sub_00221B1F(); /* call 0x00221B1F */

loc_0022334A: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_S(_fas, _fbs)) goto loc_00223395; /* jl: less (signed <) */

loc_0022334E: ;
    ecx = MEM32(esi + 0x62);
    MEM32(esi + 0xC) = ecx;
    ecx = MEM32(ebp + -4);
    _fa = (uint32_t)(MEM8(ecx)) & 0xFFu; _fb = (uint32_t)(2) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(ecx), 2 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00223395; /* je: equal / zero */

loc_0022335C: ;
    _fa = (uint32_t)(MEM8(edi + 9)) & 0xFFu; _fb = (uint32_t)(0) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(edi + 9), 0 (8-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_00223395; /* je: equal / zero */

loc_00223362: ;
    MEM32(esi + 0x5A) = MEM32(esi + 0x5A) & 0;
    MEM8(ebx) = 0x20;
    MEM8(esi + 0x53) = 2;
    SET_LO8(eax, MEM8(edi + 9));
    MEM8(esi + 0x67) = LO8(eax);
    MEM8(esi + 0x68) = 3;
    SET_LO8(eax, MEM8(ecx + 2));
    MEM8(esi + 0x69) = LO8(eax);
    MEM16(esi + 0x6E) = 0x20;
    ecx = MEM32(edi);
    PUSH32(esp, ebx);
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x0022338Bu); sub_00221B1F(); /* call 0x00221B1F */

loc_0022338B: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_S(_fas, _fbs)) goto loc_00223395; /* jl: less (signed <) */

loc_0022338F: ;
    ecx = MEM32(esi + 0x62);
    MEM32(esi + 0x10) = ecx;

loc_00223395: ;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebx);
    esp = ebp;
    POP32(esp, ebp); /* leave */
    esp += 4; return; /* ret */

}

/**
 * sub_0022339A
 * Original: 0x0022339A - 0x0022344B (177 bytes, 54 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0022339A(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_0022339A: ;
    PUSH32(esp, esi);
    esi = MEM32(esp + 0xC);
    _fa = (uint32_t)(MEM8(esi + 0xA2)) & 0xFFu; _fb = (uint32_t)(2) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(esi + 0xA2), 2 (8-bit) */
    eax = MEM32(esi);
    ecx = MEM32(eax);
    PUSH32(esp, edi);
    if (TEST_Z(_fa, _fb)) goto loc_002233CB; /* je: equal / zero */

loc_002233AD: ;
    eax = MEM32(esp + 0xC);
    MEM8(eax) = 0x1C;
    MEM8(eax + 1) = 0xC3;
    MEM32(eax + 8) = 0x22339A;
    MEM32(eax + 0xC) = esi;
    MEM8(esi + 0xA2) = MEM8(esi + 0xA2) & 0xFD;
    goto loc_00223415;

loc_002233CB: ;
    edi = 0; /* xor self */
    _fa = (uint32_t)(MEM32(esi + 0xC)) & 0xFFFFFFFFu; _fb = (uint32_t)(edi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(esi + 0xC), edi (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_002233F2; /* je: equal / zero */

loc_002233D2: ;
    eax = MEM32(esp + 0xC);
    MEM8(eax) = 0x1C;
    MEM8(eax + 1) = 0x43;
    MEM32(eax + 8) = 0x22339A;
    MEM32(eax + 0xC) = esi;
    edx = MEM32(esi + 0xC);
    MEM32(eax + 0x10) = edx;
    MEM32(esi + 0xC) = edi;
    goto loc_00223415;

loc_002233F2: ;
    _fa = (uint32_t)(MEM32(esi + 0x10)) & 0xFFFFFFFFu; _fb = (uint32_t)(edi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(esi + 0x10), edi (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_0022341D; /* je: equal / zero */

loc_002233F7: ;
    eax = MEM32(esp + 0xC);
    MEM8(eax) = 0x1C;
    MEM8(eax + 1) = 0x43;
    MEM32(eax + 8) = 0x22339A;
    MEM32(eax + 0xC) = esi;
    edx = MEM32(esi + 0x10);
    MEM32(eax + 0x10) = edx;
    MEM32(esi + 0x10) = edi;

loc_00223415: ;
    PUSH32(esp, eax);
    PUSH32(esp, 0x0022341Bu); sub_00221B1F(); /* call 0x00221B1F */

loc_0022341B: ;
    goto loc_00223446;

loc_0022341D: ;
    MEM32(eax + 0x12) = edi;
    MEM32(esi) = edi;
    _fa = (uint32_t)(MEM8(eax + 4)) & 0xFFu; _fb = (uint32_t)(2) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(eax + 4), 2 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0022342F; /* je: equal / zero */

loc_00223428: ;
    ecx = eax;
    PUSH32(esp, 0x0022342Fu); sub_00223262(); /* call 0x00223262 */

loc_0022342F: ;
    _fa = (uint32_t)(MEM8(esi + 0xA2)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(esi + 0xA2), 1 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00223446; /* je: equal / zero */

loc_00223438: ;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, edi);
    PUSH32(esp, edi);
    PUSH32(esp, MEM32(esi + 0x9E));
    { uint32_t _icall_target = MEM32(0x225B40); PUSH32(esp, 0x00223446u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00223446: ;
    POP32(esp, edi);
    POP32(esp, esi);
    esp += 12; return; /* ret 8 */

}

/**
 * sub_00223607
 * Original: 0x00223607 - 0x00223634 (45 bytes, 20 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00223607(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_00223607: ;
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    PUSH32(esp, MEM32(ecx + 4));
    esi = edx;
    edi = MEM32(esi + 0xC);
    PUSH32(esp, 0x00223616u); sub_002217F5(); /* call 0x002217F5 */

loc_00223616: ;
    _fa = (uint32_t)(edi) & 0xFFFFFFFFu; _fb = (uint32_t)(edi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test edi, edi (32-bit) */
    MEM32(esi) = eax;
    if (TEST_Z(_fa, _fb)) goto loc_00223631; /* je: equal / zero */

loc_0022361C: ;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 0);
    PUSH32(esp, 0);
    PUSH32(esp, edi);
    { uint32_t _icall_target = MEM32(0x225B40); PUSH32(esp, 0x00223627u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00223627: ;
    ecx = edi;
    POP32(esp, edi);
    POP32(esp, esi);
    g_seh_ebp = ebp; RECOMP_ITAIL(MEM32(0x225A44)); return; /* indirect tail jmp */

loc_00223631: ;
    POP32(esp, edi);
    POP32(esp, esi);
    esp += 4; return; /* ret */

}

/**
 * sub_002236AB
 * Original: 0x002236AB - 0x002236F8 (77 bytes, 35 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_002236AB(void)
{
    uint32_t ebp;
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_002236AB: ;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, ebp);
    ebp = esp;
    g_ebp = ebp; /* publish frame for frameless callees */
    esp = esp - 0xC;
    MEM32(ebp + -8) = MEM32(ebp + -8) | 0xFFFFFFFFu;
    PUSH32(esp, ebx);
    PUSH32(esp, esi);
    esi = MEM32(0x225B48);
    PUSH32(esp, edi);
    eax = ebp + -12;
    PUSH32(esp, eax);
    edi = 0; /* xor self */
    PUSH32(esp, edi);
    PUSH32(esp, edi);
    PUSH32(esp, edi);
    PUSH32(esp, MEM32(ebp + 8));
    ebx = edx;
    MEM32(ebp + -4) = ecx;
    MEM32(ebp + -12) = 0xFFF85EE0u;
    { uint32_t _icall_target = esi; PUSH32(esp, 0x002236D8u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_002236D8: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0x102) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0x102 (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_002236F1; /* jne: not equal / not zero */

loc_002236DF: ;
    ecx = MEM32(ebp + -4);
    PUSH32(esp, ebx);
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x002236E8u); sub_002217C3(); /* call 0x002217C3 */

loc_002236E8: ;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, edi);
    PUSH32(esp, edi);
    PUSH32(esp, edi);
    PUSH32(esp, edi);
    PUSH32(esp, MEM32(ebp + 8));
    { uint32_t _icall_target = esi; PUSH32(esp, 0x002236F1u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_002236F1: ;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebx);
    esp = ebp;
    POP32(esp, ebp); /* leave */
    esp += 8; return; /* ret 4 */

}

/**
 * sub_0022381F
 * Original: 0x0022381F - 0x0022383D (30 bytes, 11 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0022381F(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_0022381F: ;
    edx = ecx + 0xA2;
    SET_LO8(eax, MEM8(edx));
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(4) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), 4 (8-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_0022383C; /* jne: not equal / not zero */

loc_0022382B: ;
    PUSH32(esp, ecx);
    ecx = ecx + 0x82;
    SET_LO8(eax, LO8(eax) | 4);
    PUSH32(esp, ecx);
    MEM8(edx) = LO8(eax);
    PUSH32(esp, 0x0022383Cu); sub_0022339A(); /* call 0x0022339A */

loc_0022383C: ;
    esp += 4; return; /* ret */

}

/**
 * sub_0022394C
 * Original: 0x0022394C - 0x002239D7 (139 bytes, 27 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0022394C(void)
{

loc_0022394C: ;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, esi);
    PUSH32(esp, 0x286D88);
    { uint32_t _icall_target = MEM32(0x225B58); PUSH32(esp, 0x00223958u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00223958: ;
    esi = MEM32(esp + 0xC);
    eax = 0; /* xor self */
    MEM8(0x286D50) = 0x30;
    MEM8(0x286D51) = 0x40;
    MEM32(0x286D58) = 0x223782;
    MEM32(0x286D5C) = esi;
    MEM32(0x286D60) = eax;
    MEM32(0x286D68) = eax;
    MEM32(0x286D64) = eax;
    MEM8(0x286D6C) = LO8(eax);
    MEM8(0x286D6D) = 1;
    MEM8(0x286D6E) = LO8(eax);
    MEM8(0x286D78) = 0x21;
    MEM8(0x286D79) = 0xA;
    MEM16(0x286D7A) = LO16(eax);
    SET_LO16(ecx, ZX8(MEM8(esi + 5)));
    MEM16(0x286D7C) = LO16(ecx);
    MEM16(0x286D7E) = LO16(eax);
    PUSH32(esp, 0x002239C7u); sub_00223236(); /* call 0x00223236 */

loc_002239C7: ;
    ecx = MEM32(esi);
    PUSH32(esp, 0x286D50);
    PUSH32(esp, 0x002239D3u); sub_00221B1F(); /* call 0x00221B1F */

loc_002239D3: ;
    POP32(esp, esi);
    esp += 12; return; /* ret 8 */

}

/**
 * sub_00223A12
 * Original: 0x00223A12 - 0x00223AA6 (148 bytes, 49 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00223A12(void)
{
    uint32_t ebp;
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00223A12: ;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, ebp);
    ebp = esp;
    g_ebp = ebp; /* publish frame for frameless callees */
    esp = esp - 0x14;
    PUSH32(esp, ebx);
    PUSH32(esp, esi);
    esi = ecx;
    { uint32_t _icall_target = MEM32(0x225B30); PUSH32(esp, 0x00223A22u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00223A22: ;
    MEM8(ebp + -1) = LO8(eax);
    eax = MEM32(esi + 0xA3);
    eax = MEM32(eax + 0x1C);
    ebx = 0; /* xor self */
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(ebx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, ebx (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_00223A38; /* je: equal / zero */

loc_00223A34: ;
    ecx = esi;
    { uint32_t _icall_esp = g_esp;
    { uint32_t _icall_target = eax; PUSH32(esp, 0x00223A38u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00223A38: ;
    _fa = (uint32_t)(MEM32(esi)) & 0xFFFFFFFFu; _fb = (uint32_t)(ebx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(esi), ebx (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_00223A7F; /* je: equal / zero */

loc_00223A3C: ;
    MEM8(esi + 0xA2) = MEM8(esi + 0xA2) | 1;
    eax = ebp + -12;
    MEM32(ebp + -8) = eax;
    MEM32(ebp + -12) = eax;
    eax = ebp + -20;
    ecx = esi;
    MEM8(ebp + -20) = LO8(ebx);
    MEM8(ebp + -18) = 4;
    MEM32(ebp + -16) = ebx;
    MEM32(esi + 0x9E) = eax;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00223A66u); sub_0022381F(); /* call 0x0022381F */

loc_00223A66: ;
    SET_LO8(ecx, MEM8(ebp + -1));
    { uint32_t _icall_esp = g_esp;
    { uint32_t _icall_target = MEM32(0x225B2C); PUSH32(esp, 0x00223A6Fu); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00223A6F: ;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, ebx);
    PUSH32(esp, ebx);
    PUSH32(esp, ebx);
    PUSH32(esp, ebx);
    eax = ebp + -20;
    PUSH32(esp, eax);
    { uint32_t _icall_target = MEM32(0x225B48); PUSH32(esp, 0x00223A7Du); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00223A7D: ;
    goto loc_00223A88;

loc_00223A7F: ;
    SET_LO8(ecx, MEM8(ebp + -1));
    { uint32_t _icall_esp = g_esp;
    { uint32_t _icall_target = MEM32(0x225B2C); PUSH32(esp, 0x00223A88u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00223A88: ;
    eax = MEM32(esi + 0xA3);
    MEM8(eax + 1) = MEM8(eax + 1) + 1;
    eax = MEM32(0x286D38);
    MEM32(esi + 0xA7) = eax;
    MEM32(0x286D38) = esi;
    POP32(esp, esi);
    POP32(esp, ebx);
    esp = ebp;
    POP32(esp, ebp); /* leave */
    esp += 4; return; /* ret */

}

/**
 * sub_00223AA6
 * Original: 0x00223AA6 - 0x00223BD4 (302 bytes, 100 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00223AA6(void)
{
    uint32_t ebp;
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00223AA6: ;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, ebp);
    ebp = esp;
    g_ebp = ebp; /* publish frame for frameless callees */
    PUSH32(esp, ecx);
    PUSH32(esp, ecx);
    PUSH32(esp, ebx);
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    edi = MEM32(ecx);
    esi = edx;
    MEM32(ebp + -8) = ecx;
    { uint32_t _icall_target = MEM32(0x225B30); PUSH32(esp, 0x00223ABBu); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00223ABB: ;
    ebx = 0; /* xor self */
    _fa = (uint32_t)(edi) & 0xFFFFFFFFu; _fb = (uint32_t)(ebx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edi, ebx (32-bit) */
    MEM8(ebp + -2) = LO8(eax);
    if (CMP_EQ(_fa, _fb)) goto loc_00223BBE; /* je: equal / zero */

loc_00223AC8: ;
    _fa = (uint32_t)(MEM8(edi + 4)) & 0xFFu; _fb = (uint32_t)(2) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(edi + 4), 2 (8-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_00223BBE; /* jne: not equal / not zero */

loc_00223AD2: ;
    _fa = (uint32_t)(MEM8(edi + 0xD)) & 0xFFu; _fb = (uint32_t)(LO8(ebx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(edi + 0xD), LO8(ebx) (8-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_00223AE2; /* jne: not equal / not zero */

loc_00223AD7: ;
    MEM32(esi) = 0x32;
    goto loc_00223BC4;

loc_00223AE2: ;
    eax = MEM32(esi + 4);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(ebx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, ebx (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_00223B01; /* je: equal / zero */

loc_00223AE9: ;
    ecx = esi + 0xC;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, ecx);
    PUSH32(esp, MEM32(0x225AE4));
    PUSH32(esp, eax);
    { uint32_t _icall_target = MEM32(0x225A48); PUSH32(esp, 0x00223AFAu); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00223AFA: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (CMP_GE(_fas & _fbs, 0)) goto loc_00223B04; /* jge: greater or equal (signed >=) */

loc_00223AFE: ;
    MEM32(esi + 4) = ebx;

loc_00223B01: ;
    MEM32(esi + 0xC) = ebx;

loc_00223B04: ;
    ecx = esi + 0x40;
    SET_LO8(eax, MEM8(ecx));
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(ebx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp LO8(eax), LO8(ebx) (8-bit) */
    MEM8(ebp + -1) = LO8(eax);
    if (CMP_NE(_fa, _fb)) goto loc_00223B1B; /* jne: not equal / not zero */

loc_00223B10: ;
    SET_LO8(eax, MEM8(edi + 0xD));
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(MEM8(esi + 0x41)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp LO8(eax), MEM8(esi + 0x41) (8-bit) */
    if (CMP_AE(_fa, _fb)) goto loc_00223B1B; /* jae: above or equal (unsigned >=) */

loc_00223B18: ;
    MEM8(esi + 0x41) = LO8(eax);

loc_00223B1B: ;
    eax = MEM32(edi + 0xE);
    _fa = (uint32_t)(MEM8(eax + 0x28)) & 0xFFu; _fb = (uint32_t)(2) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(eax + 0x28), 2 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00223B27; /* je: equal / zero */

loc_00223B24: ;
    ecx = esi + 0x42;

loc_00223B27: ;
    edx = MEM32(ebp + -8);
    _fa = (uint32_t)(MEM32(edx + 0x10)) & 0xFFFFFFFFu; _fb = (uint32_t)(ebx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(edx + 0x10), ebx (32-bit) */
    eax = esi + 0x10;
    MEM32(esi + 0x1C) = esi;
    MEM32(esi + 0x18) = 0x22383D;
    if (CMP_EQ(_fa, _fb)) goto loc_00223B5F; /* je: equal / zero */

loc_00223B3C: ;
    MEM8(eax) = 0x28;
    MEM8(esi + 0x11) = 0x41;
    edx = MEM32(edx + 0x10);
    MEM32(esi + 0x28) = ecx;
    ecx = ZX8(MEM8(esi + 0x41));
    MEM32(esi + 0x20) = edx;
    MEM32(esi + 0x24) = ecx;
    MEM8(esi + 0x2C) = 1;
    MEM8(esi + 0x2D) = LO8(ebx);
    MEM8(esi + 0x2E) = LO8(ebx);
    goto loc_00223BA6;

loc_00223B5F: ;
    MEM32(esi + 0x28) = ecx;
    SET_LO8(ecx, MEM8(esi + 0x41));
    edx = ZX8(LO8(ecx));
    MEM32(esi + 0x24) = edx;
    SET_LO16(edx, ZX8(MEM8(ebp + -1)));
    SET_LO16(edx, LO16(edx) | 0x200);
    MEM8(eax) = 0x30;
    MEM8(esi + 0x11) = 0x40;
    MEM32(esi + 0x20) = ebx;
    MEM8(esi + 0x2C) = 1;
    MEM8(esi + 0x2D) = LO8(ebx);
    MEM8(esi + 0x2E) = LO8(ebx);
    MEM8(esi + 0x38) = 0x21;
    MEM8(esi + 0x39) = 9;
    MEM16(esi + 0x3A) = LO16(edx);
    SET_LO16(edx, ZX8(MEM8(edi + 5)));
    SET_LO16(ecx, ZX8(LO8(ecx)));
    MEM16(esi + 0x3C) = LO16(edx);
    MEM16(esi + 0x3E) = LO16(ecx);

loc_00223BA6: ;
    ecx = MEM32(ebp + -8);
    MEM32(esi + 8) = ecx;
    ecx = MEM32(edi);
    PUSH32(esp, eax);
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00223BB4u); sub_00221B1F(); /* call 0x00221B1F */

loc_00223BB4: ;
    PUSH32(esp, eax);
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00223BBAu); sub_002217F5(); /* call 0x002217F5 */

loc_00223BBA: ;
    MEM32(esi) = eax;
    goto loc_00223BC4;

loc_00223BBE: ;
    MEM32(esi) = 0x48F;

loc_00223BC4: ;
    SET_LO8(ecx, MEM8(ebp + -2));
    { uint32_t _icall_esp = g_esp;
    { uint32_t _icall_target = MEM32(0x225B2C); PUSH32(esp, 0x00223BCDu); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00223BCD: ;
    eax = MEM32(esi);
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebx);
    esp = ebp;
    POP32(esp, ebp); /* leave */
    esp += 4; return; /* ret */

}

/**
 * sub_00223BD4
 * Original: 0x00223BD4 - 0x00223CB2 (222 bytes, 55 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00223BD4(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00223BD4: ;
    PUSH32(esp, esi);
    esi = MEM32(esp + 0xC);
    ecx = MEM32(esi);
    PUSH32(esp, 0x00223BE0u); sub_00221863(); /* call 0x00221863 */

loc_00223BE0: ;
    SET_LO8(ecx, MEM8(eax + 5));
    _fa = (uint32_t)(LO8(ecx)) & 0xFFu; _fb = (uint32_t)(3) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp LO8(ecx), 3 (8-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_00223C87; /* jne: not equal / not zero */

loc_00223BEC: ;
    _fa = (uint32_t)(MEM8(eax + 7)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(eax + 7), 1 (8-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_00223C6B; /* jne: not equal / not zero */

loc_00223BF2: ;
    eax = 0; /* xor self */
    MEM8(0x286D50) = 0x30;
    MEM8(0x286D51) = 0x40;
    MEM32(0x286D58) = 0x2238C1;
    MEM32(0x286D5C) = esi;
    MEM32(0x286D60) = eax;
    MEM32(0x286D68) = eax;
    MEM32(0x286D64) = eax;
    MEM8(0x286D6C) = LO8(eax);
    MEM8(0x286D6D) = 1;
    MEM8(0x286D6E) = LO8(eax);
    MEM8(0x286D78) = 0x21;
    MEM8(0x286D79) = 0xB;
    MEM16(0x286D7A) = LO16(eax);
    SET_LO16(ecx, ZX8(MEM8(esi + 5)));
    MEM16(0x286D7C) = LO16(ecx);
    MEM16(0x286D7E) = LO16(eax);
    PUSH32(esp, 0x00223C5Du); sub_00223236(); /* call 0x00223236 */

loc_00223C5D: ;
    ecx = MEM32(esi);
    PUSH32(esp, 0x286D50);
    PUSH32(esp, 0x00223C69u); sub_00221B1F(); /* call 0x00221B1F */

loc_00223C69: ;
    goto loc_00223CAE;

loc_00223C6B: ;
    _fa = (uint32_t)(LO8(ecx)) & 0xFFu; _fb = (uint32_t)(3) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp LO8(ecx), 3 (8-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_00223C87; /* jne: not equal / not zero */

loc_00223C70: ;
    _fa = (uint32_t)(MEM8(eax + 7)) & 0xFFu; _fb = (uint32_t)(2) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(eax + 7), 2 (8-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_00223C87; /* jne: not equal / not zero */

loc_00223C76: ;
    PUSH32(esp, 0x00223C7Bu); sub_00223236(); /* call 0x00223236 */

loc_00223C7B: ;
    PUSH32(esp, esi);
    PUSH32(esp, MEM32(esp + 0xC));
    PUSH32(esp, 0x00223C85u); sub_0022394C(); /* call 0x0022394C */

loc_00223C85: ;
    goto loc_00223CAE;

loc_00223C87: ;
    MEM8(esi + 4) = MEM8(esi + 4) & 0xFE;
    PUSH32(esp, edi);
    edi = MEM32(esi);
    eax = 0; /* xor self */
    MEM32(esi) = eax;
    MEM16(0x286D32) = MEM16(0x286D32) - 1;
    PUSH32(esp, eax);
    ecx = edi;
    PUSH32(esp, 0x00223CA1u); sub_002217DA(); /* call 0x002217DA */

loc_00223CA1: ;
    PUSH32(esp, 0x80000400u);
    ecx = edi;
    PUSH32(esp, 0x00223CADu); sub_00220E01(); /* call 0x00220E01 */

loc_00223CAD: ;
    POP32(esp, edi);

loc_00223CAE: ;
    POP32(esp, esi);
    esp += 12; return; /* ret 8 */

}

/**
 * sub_00223DA6
 * Original: 0x00223DA6 - 0x00223FF6 (592 bytes, 182 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00223DA6(void)
{
    uint32_t ebp;
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    int _cf = 0; /* carry flag */

loc_00223DA6: ;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, ebp);
    ebp = esp;
    g_ebp = ebp; /* publish frame for frameless callees */
    _cf = (int)((uint32_t)(esp) < (uint32_t)(0x28));
    esp = esp - 0x28;
    eax = MEM32(ebp + 8);
    PUSH32(esp, ebx);
    PUSH32(esp, esi);
    ebx = 0; /* xor self */
    esi = ecx;
    PUSH32(esp, edi);
    edi = edx;
    MEM32(ebp + -16) = esi;
    MEM32(ebp + -8) = ebx;
    MEM32(ebp + -12) = ebx;
    MEM32(eax) = ebx;
    { uint32_t _icall_target = MEM32(0x225B30); PUSH32(esp, 0x00223DC9u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00223DC9: ;
    edx = edi;
    ecx = esi;
    MEM8(ebp + -1) = LO8(eax);
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00223DD5u); sub_00223285(); /* call 0x00223285 */

loc_00223DD5: ;
    edx = eax;
    _fa = (uint32_t)(edx) & 0xFFFFFFFFu; _fb = (uint32_t)(ebx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edx, ebx (32-bit) */
    MEM32(ebp + -20) = edx;
    if (CMP_NE(_fa, _fb)) goto loc_00223DEA; /* jne: not equal / not zero */

loc_00223DDE: ;
    MEM32(ebp + -8) = 0x48F;
    goto loc_00223FD5;

loc_00223DEA: ;
    _fa = (uint32_t)(MEM32(edx + 0x12)) & 0xFFFFFFFFu; _fb = (uint32_t)(ebx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(edx + 0x12), ebx (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_00223DFB; /* je: equal / zero */

loc_00223DEF: ;
    MEM32(ebp + -8) = 0x20;
    goto loc_00223FD5;

loc_00223DFB: ;
    SET_LO8(eax, MEM8(esi + 1));
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_00223E0E; /* jne: not equal / not zero */

loc_00223E02: ;
    MEM32(ebp + -8) = 0xE;
    goto loc_00223FD5;

loc_00223E0E: ;
    SET_LO8(eax, LO8(eax) - 1);
    MEM8(esi + 1) = LO8(eax);
    ebx = MEM32(0x286D38);
    eax = MEM32(ebx + 0xA7);
    MEM32(0x286D38) = eax;
    eax = 0; /* xor self */
    PUSH32(esp, 0x2A);
    POP32(esp, ecx);
    edi = ebx;
    { uint32_t _i; for (_i = 0; _i < ecx; _i++) MEM32(edi + _i*4) = eax; }
    edi += ecx * 4; ecx = 0; /* rep stosd */
    MEM16(edi) = LO16(eax); edi += 2; /* stosw */
    MEM8(edi) = LO8(eax); edi++; /* stosb */
    edi = MEM32(ebp + 0xC);
    SET_LO8(ecx, MEM8(ebx + 0xA2));
    MEM32(ebx) = edx;
    MEM32(ebx + 0xA3) = esi;
    SET_LO8(eax, MEM8(edi));
    _cf = 0; /* logical op clears CF */
    SET_LO8(eax, LO8(eax) & 1);
    _cf = 0; /* logical op clears CF */
    SET_LO8(ecx, LO8(ecx) & 0xE7);
    if (3) _cf = (int)(((LO8(eax)) >> (8 - (3))) & 1);
    SET_LO8(eax, LO8(eax) << 3);
    _cf = 0; /* logical op clears CF */
    SET_LO8(eax, LO8(eax) | LO8(ecx));
    MEM8(ebx + 0xA2) = LO8(eax);
    MEM32(edx + 0x12) = ebx;
    edx = edi;
    ecx = ebx;
    MEM32(ebp + -24) = ebx;
    MEM32(ebp + -12) = 1;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00223E69u); sub_002232EF(); /* call 0x002232EF */

loc_00223E69: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_S(_fas, _fbs)) goto loc_00223FCC; /* jl: less (signed <) */

loc_00223E71: ;
    edx = MEM32(esi + 0x18);
    _fa = (uint32_t)(edx) & 0xFFFFFFFFu; _fb = (uint32_t)(edx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test edx, edx (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00223E8A; /* je: equal / zero */

loc_00223E78: ;
    ecx = ebx;
    { uint32_t _icall_esp = g_esp;
    { uint32_t _icall_target = edx; PUSH32(esp, 0x00223E7Cu); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00223E7C: ;
    _cf = (int)((eax) != 0);
    eax = (uint32_t)(-(int32_t)eax);
    eax = _cf ? 0xFFFFFFFF : 0; /* sbb self (CF extend) */
    _cf = 0; /* logical op clears CF */
    eax = eax & 0x7FFFFF00;
    _cf = (int)((((uint64_t)(eax) + (uint64_t)(0x80000100u)) >> 32) & 1);
    eax = eax + 0x80000100u;

loc_00223E8A: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_S(_fas, _fbs)) goto loc_00223FCC; /* jl: less (signed <) */

loc_00223E92: ;
    esi = MEM32(esi + 8);
    ecx = ZX8(MEM8(esi));
    esi = MEM32(esi + 1);
    edx = ecx;
    if (2) _cf = (int)(((ecx) >> ((2) - 1)) & 1);
    ecx = ecx >> 2;
    eax = ebx + 0x34;
    edi = eax;
    memcpy((void*)XBOX_PTR(edi), (void*)XBOX_PTR(esi), ecx * 4);
    esi += ecx * 4; edi += ecx * 4; ecx = 0; /* rep movsd */
    ecx = edx;
    _cf = 0; /* logical op clears CF */
    ecx = ecx & 3;
    memcpy((void*)XBOX_PTR(edi), (void*)XBOX_PTR(esi), ecx);
    esi += ecx; edi += ecx; ecx = 0; /* rep movsb */
    PUSH32(esp, 7);
    esi = eax;
    eax = MEM32(ebp + -16);
    edi = ebx + 0x14;
    POP32(esp, ecx);
    memcpy((void*)XBOX_PTR(edi), (void*)XBOX_PTR(esi), ecx * 4);
    esi += ecx * 4; edi += ecx * 4; ecx = 0; /* rep movsd */
    MEM16(edi) = MEM16(esi); esi += 2; edi += 2; /* movsw */
    _fa = (uint32_t)(MEM8(eax + 0x28)) & 0xFFu; _fb = (uint32_t)(0x40) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(eax + 0x28), 0x40 (8-bit) */
    esi = MEM32(ebp + -20);
    if (TEST_NZ(_fa, _fb)) goto loc_00223F79; /* jne: not equal / not zero */

loc_00223ECA: ;
    _cf = 0; /* logical op clears CF */
    MEM32(ebp + -36) = MEM32(ebp + -36) & 0;
    eax = ebp + -32;
    MEM32(ebp + -28) = eax;
    MEM32(ebp + -32) = eax;
    eax = ZX8(MEM8(esi + 0xC));
    _cf = 0; /* logical op clears CF */
    MEM32(ebx + 0x62) = MEM32(ebx + 0x62) & 0;
    ecx = ebp + -40;
    MEM32(ebx + 0x5E) = ecx;
    ecx = ebx + 0x32;
    edi = ebx + 0x52;
    MEM8(edi) = 0x30;
    MEM8(ebx + 0x53) = 0x40;
    MEM32(ebx + 0x5A) = 0x22369A;
    MEM32(ebx + 0x6A) = ecx;
    MEM32(ebx + 0x66) = eax;
    MEM8(ebx + 0x6E) = 2;
    MEM8(ebx + 0x6F) = 1;
    MEM8(ebx + 0x70) = 0;
    MEM8(ebx + 0x7A) = 0xA1;
    MEM8(ebx + 0x7B) = 1;
    MEM16(ebx + 0x7C) = 0x100;
    SET_LO16(ecx, ZX8(MEM8(esi + 5)));
    MEM16(ebx + 0x7E) = LO16(ecx);
    MEM16(ebx + 0x80) = LO16(eax);
    ecx = MEM32(esi);
    PUSH32(esp, edi);
    MEM8(ebp + -40) = 1;
    MEM8(ebp + -38) = 4;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00223F39u); sub_00221B1F(); /* call 0x00221B1F */

loc_00223F39: ;
    SET_LO8(ecx, MEM8(ebp + -1));
    { uint32_t _icall_esp = g_esp;
    { uint32_t _icall_target = MEM32(0x225B2C); PUSH32(esp, 0x00223F42u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00223F42: ;
    ecx = MEM32(esi);
    eax = ebp + -40;
    PUSH32(esp, eax);
    edx = edi;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00223F4Fu); sub_002236AB(); /* call 0x002236AB */

loc_00223F4F: ;
    { uint32_t _icall_esp = g_esp;
    { uint32_t _icall_target = MEM32(0x225B30); PUSH32(esp, 0x00223F55u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00223F55: ;
    _fa = (uint32_t)(MEM32(ebx)) & 0xFFFFFFFFu; _fb = (uint32_t)(0) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(ebx), 0 (32-bit) */
    MEM8(ebp + -1) = LO8(eax);
    if (CMP_EQ(_fa, _fb)) goto loc_00223DDE; /* je: equal / zero */

loc_00223F61: ;
    _fa = (uint32_t)(MEM8(esi + 4)) & 0xFFu; _fb = (uint32_t)(2) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(esi + 4), 2 (8-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_00223DDE; /* jne: not equal / not zero */

loc_00223F6B: ;
    _fa = (uint32_t)(MEM32(ebx + 0x56)) & 0xFFFFFFFFu; _fb = (uint32_t)(0) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(ebx + 0x56), 0 (32-bit) */
    if (CMP_L(_fas, _fbs)) goto loc_00223F79; /* jl: less (signed <) */

loc_00223F71: ;
    eax = MEM32(ebp + -16);
    ecx = ebx;
    { uint32_t _icall_esp = g_esp;
    { uint32_t _icall_target = MEM32(eax + 0x24); PUSH32(esp, 0x00223F79u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00223F79: ;
    ecx = MEM32(ebx + 0xC);
    MEM32(ebx + 0x62) = ecx;
    ecx = ebx + 0x32;
    eax = ebx + 0x52;
    MEM8(eax) = 0x28;
    MEM8(ebx + 0x53) = 0x41;
    MEM32(ebx + 0x5A) = 0x22344B;
    MEM32(ebx + 0x5E) = ebx;
    MEM32(ebx + 0x6A) = ecx;
    ecx = ZX8(MEM8(esi + 0xC));
    MEM32(ebx + 0x66) = ecx;
    MEM8(ebx + 0x6E) = 2;
    MEM8(ebx + 0x6F) = 1;
    MEM8(ebx + 0x70) = 0;
    _cf = 0; /* logical op clears CF */
    MEM8(esi + 4) = MEM8(esi + 4) & 0xF;
    _fa = (uint32_t)(MEM8(ebx + 0xA2)) & 0xFFu; _fb = (uint32_t)(8) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(ebx + 0xA2), 8 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00223FC1; /* je: equal / zero */

loc_00223FB9: ;
    ecx = MEM32(esi);
    PUSH32(esp, eax);
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00223FC1u); sub_00221B1F(); /* call 0x00221B1F */

loc_00223FC1: ;
    eax = MEM32(ebp + 8);
    _cf = 0; /* logical op clears CF */
    MEM32(ebp + -12) = MEM32(ebp + -12) & 0;
    MEM32(eax) = ebx;
    goto loc_00223FD5;

loc_00223FCC: ;
    PUSH32(esp, eax);
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00223FD2u); sub_002217F5(); /* call 0x002217F5 */

loc_00223FD2: ;
    MEM32(ebp + -8) = eax;

loc_00223FD5: ;
    SET_LO8(ecx, MEM8(ebp + -1));
    { uint32_t _icall_esp = g_esp;
    { uint32_t _icall_target = MEM32(0x225B2C); PUSH32(esp, 0x00223FDEu); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00223FDE: ;
    _fa = (uint32_t)(MEM32(ebp + -12)) & 0xFFFFFFFFu; _fb = (uint32_t)(0) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(ebp + -12), 0 (32-bit) */
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebx);
    if (CMP_EQ(_fa, _fb)) goto loc_00223FEF; /* je: equal / zero */

loc_00223FE7: ;
    ecx = MEM32(ebp + -24);
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00223FEFu); sub_00223A12(); /* call 0x00223A12 */

loc_00223FEF: ;
    eax = MEM32(ebp + -8);
    esp = ebp;
    POP32(esp, ebp); /* leave */
    esp += 12; return; /* ret 8 */

}

/**
 * sub_0022414A
 * Original: 0x0022414A - 0x00224167 (29 bytes, 7 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0022414A(void)
{

loc_0022414A: ;
    eax = MEM32(esp + 4);
    MEM32(eax + 8) = MEM32(eax + 8) | 0xFFFFFFFFu;
    MEM8(eax + 0x1F) = 0xFF;
    ecx = MEM32(0x28788C);
    MEM32(eax + 0x14) = ecx;
    MEM32(0x28788C) = eax;
    esp += 8; return; /* ret 4 */

}

/**
 * sub_00224167
 * Original: 0x00224167 - 0x002241A4 (61 bytes, 23 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00224167(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00224167: ;
    _fa = (uint32_t)(MEM8(edx + 0x11)) & 0xFFu; _fb = (uint32_t)(0) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(edx + 0x11), 0 (8-bit) */
    eax = MEM32(ecx);
    PUSH32(esp, esi);
    if (CMP_NE(_fa, _fb)) goto loc_0022417B; /* jne: not equal / not zero */

loc_00224170: ;
    esi = ecx + 0x40C;
    eax = eax + 0x20;
    goto loc_00224184;

loc_0022417B: ;
    esi = ecx + 0x410;
    eax = eax + 0x28;

loc_00224184: ;
    ecx = MEM32(esi);
    MEM32(edx + 0x18) = ecx;
    MEM32(esi) = edx;
    ecx = MEM32(edx + 0x18);
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, ecx (32-bit) */
    POP32(esp, esi);
    if (TEST_NZ(_fa, _fb)) goto loc_00224198; /* jne: not equal / not zero */

loc_00224193: ;
    MEM32(edx + 0xC) = MEM32(edx + 0xC) & ecx;
    goto loc_0022419E;

loc_00224198: ;
    ecx = MEM32(ecx + 0x14);
    MEM32(edx + 0xC) = ecx;

loc_0022419E: ;
    ecx = MEM32(edx + 0x14);
    MEM32(eax) = ecx;
    esp += 4; return; /* ret */

}

/**
 * sub_002241A4
 * Original: 0x002241A4 - 0x002241F4 (80 bytes, 33 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_002241A4(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_002241A4: ;
    _fa = (uint32_t)(MEM8(edx + 0x11)) & 0xFFu; _fb = (uint32_t)(0) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(edx + 0x11), 0 (8-bit) */
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    if (CMP_NE(_fa, _fb)) goto loc_002241B9; /* jne: not equal / not zero */

loc_002241AC: ;
    esi = ecx + 0x40C;
    ecx = MEM32(ecx);
    ecx = ecx + 0x20;
    goto loc_002241C4;

loc_002241B9: ;
    esi = ecx + 0x410;
    ecx = MEM32(ecx);
    ecx = ecx + 0x28;

loc_002241C4: ;
    eax = MEM32(esi);
    edi = 0; /* xor self */

loc_002241C8: ;
    _fa = (uint32_t)(edx) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edx, eax (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_002241D5; /* je: equal / zero */

loc_002241CC: ;
    edi = eax;
    eax = MEM32(eax + 0x18);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_002241C8; /* jne: not equal / not zero */

loc_002241D5: ;
    _fa = (uint32_t)(edi) & 0xFFFFFFFFu; _fb = (uint32_t)(edi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test edi, edi (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_002241E7; /* je: equal / zero */

loc_002241D9: ;
    ecx = MEM32(eax + 0x18);
    MEM32(edi + 0x18) = ecx;
    eax = MEM32(eax + 0xC);
    MEM32(edi + 0xC) = eax;
    goto loc_002241F1;

loc_002241E7: ;
    edx = MEM32(eax + 0x18);
    MEM32(esi) = edx;
    eax = MEM32(eax + 0xC);
    MEM32(ecx) = eax;

loc_002241F1: ;
    POP32(esp, edi);
    POP32(esp, esi);
    esp += 4; return; /* ret */

}

/**
 * sub_002241F4
 * Original: 0x002241F4 - 0x0022420A (22 bytes, 12 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_002241F4(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_002241F4: ;
    eax = 0; /* xor self */
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, ecx (32-bit) */
    if (CMP_BE(_fa & _fb, 0)) goto loc_00224209; /* jbe: below or equal (unsigned <=) */

loc_002241FA: ;
    PUSH32(esp, esi);

loc_002241FB: ;
    esi = edx;
    esi = esi & 1;
    edx = edx >> 1;
    ecx--;
    eax = esi + eax * 2;
    if ((ecx != 0)) goto loc_002241FB; /* jne: not equal / not zero */

loc_00224208: ;
    POP32(esp, esi);

loc_00224209: ;
    esp += 4; return; /* ret */

}

/**
 * sub_0022420A
 * Original: 0x0022420A - 0x00224281 (119 bytes, 50 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0022420A(void)
{
    uint32_t ebp;
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_0022420A: ;
    PUSH32(esp, ebp);
    ebp = esp;
    g_ebp = ebp; /* publish frame for frameless callees */
    PUSH32(esp, ecx);
    PUSH32(esp, esi);
    esi = ecx;
    SET_LO8(ecx, MEM8(ebp + 8));
    _fa = (uint32_t)(LO8(ecx)) & 0xFFu; _fb = (uint32_t)(0x20) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp LO8(ecx), 0x20 (8-bit) */
    PUSH32(esp, edi);
    edi = edx;
    if (CMP_B(_fa, _fb)) goto loc_00224232; /* jb: below (unsigned <) */

loc_0022421C: ;
    edx = ZX8(LO8(ecx));
    PUSH32(esp, 5);
    edx = edx - 0x20;
    POP32(esp, ecx);
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x0022422Au); sub_002241F4(); /* call 0x002241F4 */

loc_0022422A: ;
    ecx = MEM32(esi + 8);
    MEM32(ecx + eax * 4) = edi;
    goto loc_0022427B;

loc_00224232: ;
    SET_LO8(eax, LO8(ecx));
    SET_LO8(eax, LO8(eax) << 1);
    PUSH32(esp, ebx);
    SET_LO8(eax, LO8(eax) + 1);
    SET_LO8(ebx, LO8(ecx));
    MEM8(ebp + -4) = LO8(eax);
    MEM8(ebp + 0xB) = 0;
    SET_LO8(ebx, LO8(ebx) << 1);

loc_00224244: ;
    eax = ZX8(LO8(eax));
    eax = eax << 4;
    eax = eax + esi + 0xC;
    _fa = (uint32_t)(MEM32(eax + 8)) & 0xFFFFFFFFu; _fb = (uint32_t)(0) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(eax + 8), 0 (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_00224262; /* jne: not equal / not zero */

loc_00224254: ;
    PUSH32(esp, MEM32(ebp + -4));
    edx = edi;
    ecx = esi;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00224260u); sub_0022420A(); /* call 0x0022420A */

loc_00224260: ;
    goto loc_00224268;

loc_00224262: ;
    eax = MEM32(eax + 0xC);
    MEM32(eax + 0xC) = edi;

loc_00224268: ;
    SET_LO8(eax, LO8(ebx));
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    MEM8(ebp + -4) = LO8(eax);
    if (TEST_Z(_fa, _fb)) goto loc_0022427A; /* je: equal / zero */

loc_00224271: ;
    MEM8(ebp + 0xB) = MEM8(ebp + 0xB) + 1;
    _fa = (uint32_t)(MEM8(ebp + 0xB)) & 0xFFu; _fb = (uint32_t)(2) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(ebp + 0xB), 2 (8-bit) */
    if (CMP_B(_fa, _fb)) goto loc_00224244; /* jb: below (unsigned <) */

loc_0022427A: ;
    POP32(esp, ebx);

loc_0022427B: ;
    POP32(esp, edi);
    POP32(esp, esi);
    esp = ebp;
    POP32(esp, ebp); /* leave */
    esp += 8; return; /* ret 4 */

}

/**
 * sub_00224281
 * Original: 0x00224281 - 0x0022445D (476 bytes, 172 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00224281(void)
{
    uint32_t ebp;
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00224281: ;
    PUSH32(esp, ebp);
    ebp = esp;
    g_ebp = ebp; /* publish frame for frameless callees */
    esp = esp - 0x10;
    PUSH32(esp, ebx);
    PUSH32(esp, esi);
    esi = edx;
    _fa = (uint32_t)(MEM8(esi + 0x11)) & 0xFFu; _fb = (uint32_t)(3) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(esi + 0x11), 3 (8-bit) */
    PUSH32(esp, edi);
    if (CMP_NE(_fa, _fb)) goto loc_002242E5; /* jne: not equal / not zero */

loc_00224292: ;
    SET_LO8(eax, 0x20);
    _fa = (uint32_t)(MEM8(esi + 0x13)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(esi + 0x13), LO8(eax) (8-bit) */
    if (CMP_AE(_fa, _fb)) goto loc_002242A2; /* jae: above or equal (unsigned >=) */

loc_00224299: ;
    SET_LO8(edx, MEM8(esi + 0x13));

loc_0022429C: ;
    SET_LO8(eax, LO8(eax) >> 1);
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(edx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp LO8(eax), LO8(edx) (8-bit) */
    if (CMP_A(_fa, _fb)) goto loc_0022429C; /* ja: above (unsigned >) */

loc_002242A2: ;
    SET_LO8(ebx, LO8(eax));
    SET_LO8(ebx, LO8(ebx) << 1);
    SET_LO8(ebx, LO8(ebx) - 1);
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(ebx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp LO8(eax), LO8(ebx) (8-bit) */
    edi = 0x2EE0;
    MEM8(ebp + -1) = LO8(eax);
    if (CMP_A(_fa, _fb)) goto loc_002242F1; /* ja: above (unsigned >) */

loc_002242B4: ;
    eax = ZX8(LO8(eax));
    eax = eax << 4;
    edx = eax + ecx + 0x10;

loc_002242BE: ;
    eax = 0; /* xor self */
    SET_LO16(eax, MEM16(edx + -2));
    SET_LO16(eax, LO16(eax) + MEM16(edx + 2));
    SET_LO16(eax, LO16(eax) + MEM16(edx));
    _fa = (uint32_t)(LO16(eax)) & 0xFFFFu; _fb = (uint32_t)(LO16(edi)) & 0xFFFFu;
    _fas = (int32_t)(int16_t)(_fa); _fbs = (int32_t)(int16_t)(_fb); /* cmp LO16(eax), LO16(edi) (16-bit) */
    if (CMP_AE(_fa, _fb)) goto loc_002242D8; /* jae: above or equal (unsigned >=) */

loc_002242D0: ;
    edi = eax;
    SET_LO8(eax, MEM8(ebp + -1));
    MEM8(ebp + -5) = LO8(eax);

loc_002242D8: ;
    MEM8(ebp + -1) = MEM8(ebp + -1) + 1;
    edx = edx + 0x10;
    _fa = (uint32_t)(MEM8(ebp + -1)) & 0xFFu; _fb = (uint32_t)(LO8(ebx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(ebp + -1), LO8(ebx) (8-bit) */
    if (CMP_BE(_fa, _fb)) goto loc_002242BE; /* jbe: below or equal (unsigned <=) */

loc_002242E3: ;
    goto loc_002242F1;

loc_002242E5: ;
    SET_LO16(edi, MEM16(ecx + 0x10));
    SET_LO16(edi, LO16(edi) + MEM16(ecx + 0xE));
    MEM8(ebp + -5) = 0;

loc_002242F1: ;
    SET_LO16(eax, MEM16(esi + 0x22));
    edi = ZX16(LO16(edi));
    edx = ZX16(LO16(eax));
    edx = edx + edi;
    edi = ZX16(MEM16(ecx + 0x414));
    _fa = (uint32_t)(edx) & 0xFFFFFFFFu; _fb = (uint32_t)(edi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edx, edi (32-bit) */
    if (CMP_LE(_fas, _fbs)) goto loc_00224312; /* jle: less or equal (signed <=) */

loc_00224308: ;
    eax = 0x80000800u;
    goto loc_00224458;

loc_00224312: ;
    SET_LO8(edx, MEM8(ebp + -5));
    edi = ZX8(LO8(edx));
    edi = edi << 4;
    edi = edi + ecx + 0xC;
    MEM8(esi + 0x12) = LO8(edx);
    MEM16(edi + 2) = MEM16(edi + 2) + LO16(eax);
    _fa = (uint32_t)(LO8(edx)) & 0xFFu; _fb = (uint32_t)(LO8(edx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(edx), LO8(edx) (8-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_00224331; /* jne: not equal / not zero */

loc_0022432A: ;
    SET_LO8(eax, 1);
    MEM8(ebp + -1) = LO8(eax);
    goto loc_00224342;

loc_00224331: ;
    SET_LO8(eax, LO8(edx));
    SET_LO8(eax, LO8(eax) << 1);
    MEM8(ebp + -1) = LO8(eax);
    SET_LO8(eax, LO8(edx));
    SET_LO8(eax, LO8(eax) << 1);
    SET_LO8(eax, LO8(eax) + 1);
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(0x40) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp LO8(eax), 0x40 (8-bit) */
    if (CMP_A(_fa, _fb)) goto loc_00224382; /* ja: above (unsigned >) */

loc_00224342: ;
    _fa = (uint32_t)(MEM8(ebp + -1)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(ebp + -1), LO8(eax) (8-bit) */
    if (CMP_A(_fa, _fb)) goto loc_00224374; /* ja: above (unsigned >) */

loc_00224347: ;
    edx = ZX8(MEM8(ebp + -1));
    edx = edx << 4;
    edx = edx + ecx + 0x12;
    MEM32(ebp + -16) = edx;
    SET_LO8(edx, LO8(eax));
    SET_LO8(edx, LO8(edx) - MEM8(ebp + -1));
    SET_LO8(edx, LO8(edx) + 1);
    edx = ZX8(LO8(edx));
    MEM32(ebp + -12) = edx;
    edx = MEM32(ebp + -16);

loc_00224365: ;
    SET_LO16(ebx, MEM16(esi + 0x22));
    MEM16(edx) = MEM16(edx) + LO16(ebx);
    edx = edx + 0x10;
    MEM32(ebp + -12) = MEM32(ebp + -12) - 1;
    if ((MEM32(ebp + -12) != 0)) goto loc_00224365; /* jne: not equal / not zero */

loc_00224374: ;
    MEM8(ebp + -1) = MEM8(ebp + -1) << 1;
    SET_LO8(eax, LO8(eax) << 1);
    SET_LO8(eax, LO8(eax) + 1);
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(0x40) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp LO8(eax), 0x40 (8-bit) */
    if (CMP_BE(_fa, _fb)) goto loc_00224342; /* jbe: below or equal (unsigned <=) */

loc_0022437F: ;
    SET_LO8(edx, MEM8(ebp + -5));

loc_00224382: ;
    _fa = (uint32_t)(LO8(edx)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp LO8(edx), 1 (8-bit) */
    MEM8(ebp + -1) = LO8(edx);
    if (CMP_BE(_fa, _fb)) goto loc_002243EB; /* jbe: below or equal (unsigned <=) */

loc_0022438A: ;
    SET_LO8(eax, MEM8(ebp + -1));
    edx = ZX8(MEM8(ebp + -1));
    SET_LO8(eax, LO8(eax) ^ 1);
    eax = ZX8(LO8(eax));
    edx = edx << 4;
    edx = edx + ecx + 0xC;
    eax = eax << 4;
    ebx = 0; /* xor self */
    SET_LO16(ebx, MEM16(edx + 4));
    SET_LO16(edx, MEM16(edx + 2));
    eax = eax + ecx + 0xC;
    MEM16(ebp + -12) = LO16(edx);
    edx = ZX16(MEM16(eax + 4));
    eax = ZX16(MEM16(eax + 2));
    edx = edx + eax;
    eax = ZX16(MEM16(ebp + -12));
    MEM32(ebp + -16) = ebx;
    ebx = ZX16(LO16(ebx));
    eax = eax + ebx;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(edx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, edx (32-bit) */
    if (CMP_LE(_fas, _fbs)) goto loc_002243EB; /* jle: less or equal (signed <=) */

loc_002243CC: ;
    SET_LO8(eax, MEM8(ebp + -1));
    ebx = MEM32(ebp + -16);
    edx = MEM32(ebp + -12);
    SET_LO8(eax, LO8(eax) >> 1);
    edx = edx + ebx;
    ebx = ZX8(LO8(eax));
    ebx = ebx << 4;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp LO8(eax), 1 (8-bit) */
    MEM16(ebx + ecx + 0x10) = LO16(edx);
    MEM8(ebp + -1) = LO8(eax);
    if (CMP_A(_fa, _fb)) goto loc_0022438A; /* ja: above (unsigned >) */

loc_002243EB: ;
    _fa = (uint32_t)(MEM8(ebp + -1)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(ebp + -1), 1 (8-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_002243FD; /* jne: not equal / not zero */

loc_002243F1: ;
    SET_LO16(eax, MEM16(ecx + 0x20));
    SET_LO16(eax, LO16(eax) + MEM16(ecx + 0x1E));
    MEM16(ecx + 0x10) = LO16(eax);

loc_002243FD: ;
    eax = MEM32(edi + 8);
    edx = 0; /* xor self */
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(edx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, edx (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_0022443C; /* jne: not equal / not zero */

loc_00224406: ;
    SET_LO8(eax, MEM8(ebp + -5));
    goto loc_0022440F;

loc_0022440B: ;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0022441D; /* je: equal / zero */

loc_0022440F: ;
    SET_LO8(eax, LO8(eax) >> 1);
    ebx = ZX8(LO8(eax));
    ebx = ebx << 4;
    _fa = (uint32_t)(MEM32(ebx + ecx + 0x14)) & 0xFFFFFFFFu; _fb = (uint32_t)(edx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(ebx + ecx + 0x14), edx (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_0022440B; /* je: equal / zero */

loc_0022441D: ;
    eax = ZX8(LO8(eax));
    eax = eax << 4;
    eax = MEM32(eax + ecx + 0x14);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(edx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, edx (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_00224431; /* je: equal / zero */

loc_0022442B: ;
    eax = MEM32(eax + 0x14);
    MEM32(esi + 0xC) = eax;

loc_00224431: ;
    MEM32(edi + 8) = esi;
    MEM32(edi + 0xC) = esi;
    MEM32(esi + 0x18) = edx;
    goto loc_0022444B;

loc_0022443C: ;
    MEM32(esi + 0x18) = eax;
    MEM32(edi + 8) = esi;
    eax = MEM32(esi + 0x18);
    eax = MEM32(eax + 0x14);
    MEM32(esi + 0xC) = eax;

loc_0022444B: ;
    PUSH32(esp, MEM32(ebp + -5));
    edx = MEM32(esi + 0x14);
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00224456u); sub_0022420A(); /* call 0x0022420A */

loc_00224456: ;
    eax = 0; /* xor self */

loc_00224458: ;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebx);
    esp = ebp;
    POP32(esp, ebp); /* leave */
    esp += 4; return; /* ret */

}

/**
 * sub_0022445D
 * Original: 0x0022445D - 0x002245D6 (377 bytes, 138 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0022445D(void)
{
    uint32_t ebp;
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_0022445D: ;
    PUSH32(esp, ebp);
    ebp = esp;
    g_ebp = ebp; /* publish frame for frameless callees */
    esp = esp - 0x14;
    SET_LO16(eax, MEM16(edx + 0x22));
    MEM32(ebp + -4) = MEM32(ebp + -4) & 0;
    PUSH32(esp, ebx);
    SET_LO8(ebx, MEM8(edx + 0x12));
    MEM16(ebp + -16) = LO16(eax);
    eax = ZX8(LO8(ebx));
    PUSH32(esp, esi);
    eax = eax << 4;
    esi = ecx;
    PUSH32(esp, edi);
    edi = eax + esi + 0xC;
    eax = MEM32(edi + 8);
    MEM32(ebp + -20) = edx;
    MEM8(ebp + -12) = LO8(ebx);

loc_0022448A: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(edx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, edx (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_00224498; /* je: equal / zero */

loc_0022448E: ;
    MEM32(ebp + -4) = eax;
    eax = MEM32(eax + 0x18);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_0022448A; /* jne: not equal / not zero */

loc_00224498: ;
    ecx = MEM32(eax + 0x18);
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, ecx (32-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_002244D3; /* jne: not equal / not zero */

loc_0022449F: ;
    ecx = MEM32(ebp + -4);
    edx = 0; /* xor self */
    _fa = (uint32_t)(LO8(ebx)) & 0xFFu; _fb = (uint32_t)(LO8(ebx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(ebx), LO8(ebx) (8-bit) */
    MEM32(edi + 0xC) = ecx;
    MEM32(ebp + -8) = edx;
    if (TEST_Z(_fa, _fb)) goto loc_002244DB; /* je: equal / zero */

loc_002244AE: ;
    SET_LO8(edx, LO8(ebx));
    goto loc_002244B6;

loc_002244B2: ;
    _fa = (uint32_t)(LO8(edx)) & 0xFFu; _fb = (uint32_t)(LO8(edx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(edx), LO8(edx) (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_002244C5; /* je: equal / zero */

loc_002244B6: ;
    SET_LO8(edx, LO8(edx) >> 1);
    ecx = ZX8(LO8(edx));
    ecx = ecx << 4;
    _fa = (uint32_t)(MEM32(ecx + esi + 0x14)) & 0xFFFFFFFFu; _fb = (uint32_t)(0) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(ecx + esi + 0x14), 0 (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_002244B2; /* je: equal / zero */

loc_002244C5: ;
    ecx = ZX8(LO8(edx));
    ecx = ecx << 4;
    ecx = MEM32(ecx + esi + 0x14);
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, ecx (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_002244D8; /* je: equal / zero */

loc_002244D3: ;
    edx = MEM32(ecx + 0x14);
    goto loc_002244DB;

loc_002244D8: ;
    edx = MEM32(ebp + -8);

loc_002244DB: ;
    ecx = MEM32(ebp + -4);
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, ecx (32-bit) */
    eax = MEM32(eax + 0x18);
    if (TEST_NZ(_fa, _fb)) goto loc_002244F4; /* jne: not equal / not zero */

loc_002244E5: ;
    PUSH32(esp, MEM32(ebp + -12));
    ecx = esi;
    MEM32(edi + 8) = eax;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x002244F2u); sub_0022420A(); /* call 0x0022420A */

loc_002244F2: ;
    goto loc_002244FA;

loc_002244F4: ;
    MEM32(ecx + 0x18) = eax;
    MEM32(ecx + 0xC) = edx;

loc_002244FA: ;
    SET_LO16(eax, MEM16(ebp + -16));
    MEM16(edi + 2) = MEM16(edi + 2) - LO16(eax);
    _fa = (uint32_t)(LO8(ebx)) & 0xFFu; _fb = (uint32_t)(LO8(ebx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(ebx), LO8(ebx) (8-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_002245CD; /* jne: not equal / not zero */

loc_0022450A: ;
    SET_LO8(eax, 1);
    SET_LO8(ecx, LO8(eax));

loc_0022450E: ;
    _fa = (uint32_t)(LO8(ecx)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp LO8(ecx), LO8(eax) (8-bit) */
    if (CMP_A(_fa, _fb)) goto loc_0022453A; /* ja: above (unsigned >) */

loc_00224512: ;
    edx = ZX8(LO8(ecx));
    edx = edx << 4;
    edi = edx + esi + 0x12;
    SET_LO8(edx, LO8(eax));
    SET_LO8(edx, LO8(edx) - LO8(ecx));
    SET_LO8(edx, LO8(edx) + 1);
    edx = ZX8(LO8(edx));
    MEM32(ebp + -4) = edx;

loc_00224528: ;
    edx = MEM32(ebp + -20);
    SET_LO16(edx, MEM16(edx + 0x22));
    MEM16(edi) = MEM16(edi) - LO16(edx);
    edi = edi + 0x10;
    MEM32(ebp + -4) = MEM32(ebp + -4) - 1;
    if ((MEM32(ebp + -4) != 0)) goto loc_00224528; /* jne: not equal / not zero */

loc_0022453A: ;
    SET_LO8(eax, LO8(eax) << 1);
    SET_LO8(ecx, LO8(ecx) << 1);
    SET_LO8(eax, LO8(eax) + 1);
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(0x40) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp LO8(eax), 0x40 (8-bit) */
    if (CMP_BE(_fa, _fb)) goto loc_0022450E; /* jbe: below or equal (unsigned <=) */

loc_00224544: ;
    _fa = (uint32_t)(LO8(ebx)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp LO8(ebx), 1 (8-bit) */
    if (CMP_BE(_fa, _fb)) goto loc_002245BA; /* jbe: below or equal (unsigned <=) */

loc_00224549: ;
    SET_LO8(edx, LO8(ebx));
    SET_LO8(edx, LO8(edx) ^ 1);
    ecx = ZX8(LO8(edx));
    ecx = ecx << 4;
    ecx = ecx + esi + 0xC;
    edi = ZX16(MEM16(ecx + 4));
    ecx = ZX16(MEM16(ecx + 2));
    edi = edi + ecx;
    ecx = ZX8(LO8(ebx));
    ecx = ecx << 4;
    MEM32(ebp + -4) = edi;
    ecx = ecx + esi + 0xC;
    edi = ZX16(MEM16(ecx + 4));
    ecx = ZX16(MEM16(ecx + 2));
    SET_LO8(eax, LO8(ebx));
    edi = edi + ecx;
    SET_LO8(eax, LO8(eax) >> 1);
    _fa = (uint32_t)(edi) & 0xFFFFFFFFu; _fb = (uint32_t)(MEM32(ebp + -4)) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edi, MEM32(ebp + -4) (32-bit) */
    if (CMP_G(_fas, _fbs)) goto loc_00224594; /* jg: greater (signed >) */

loc_00224582: ;
    ecx = ZX8(LO8(eax));
    ecx = ecx << 4;
    ecx = ZX16(MEM16(ecx + esi + 0x10));
    _fa = (uint32_t)(MEM32(ebp + -4)) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(ebp + -4), ecx (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_002245B7; /* je: equal / zero */

loc_00224592: ;
    SET_LO8(ebx, LO8(edx));

loc_00224594: ;
    ecx = ZX8(LO8(ebx));
    ecx = ecx << 4;
    ecx = ecx + esi + 0xC;
    SET_LO16(edx, MEM16(ecx + 4));
    SET_LO16(edx, LO16(edx) + MEM16(ecx + 2));
    ecx = ZX8(LO8(eax));
    ecx = ecx << 4;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp LO8(eax), 1 (8-bit) */
    MEM16(ecx + esi + 0x10) = LO16(edx);
    SET_LO8(ebx, LO8(eax));
    if (CMP_A(_fa, _fb)) goto loc_00224549; /* ja: above (unsigned >) */

loc_002245B7: ;
    _fa = (uint32_t)(LO8(ebx)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp LO8(ebx), 1 (8-bit) */

loc_002245BA: ;
    if (CMP_NE(_fa, _fb)) goto loc_002245C8; /* jne: not equal / not zero */

loc_002245BC: ;
    SET_LO16(eax, MEM16(esi + 0x20));
    SET_LO16(eax, LO16(eax) + MEM16(esi + 0x1E));
    MEM16(esi + 0x10) = LO16(eax);

loc_002245C8: ;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebx);
    esp = ebp;
    POP32(esp, ebp); /* leave */
    esp += 4; return; /* ret */

loc_002245CD: ;
    SET_LO8(ecx, LO8(ebx));
    SET_LO8(eax, LO8(ebx));
    goto loc_0022453A;

}

/**
 * sub_0022466C
 * Original: 0x0022466C - 0x00224690 (36 bytes, 10 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0022466C(void)
{

loc_0022466C: ;
    eax = MEM32(ecx + 8);
    edx = MEM32(ecx + 0x418);
    ecx = ZX16(MEM16(eax + 0x80));
    eax = ecx;
    eax = eax ^ edx;
    ecx = ecx & 0x7FFF;
    eax = eax & 0x8000;
    ecx = ecx | edx;
    eax = eax + ecx;
    esp += 4; return; /* ret */

}

/**
 * sub_00224690
 * Original: 0x00224690 - 0x002247A3 (275 bytes, 97 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00224690(void)
{
    uint32_t ebp;
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00224690: ;
    PUSH32(esp, ebp);
    ebp = esp;
    g_ebp = ebp; /* publish frame for frameless callees */
    PUSH32(esp, ecx);
    edx = MEM32(ecx + 0x418);
    PUSH32(esp, ebx);
    PUSH32(esp, esi);
    /* TODO: cli  */
    eax = MEM32(ecx + 8);
    eax = ZX16(MEM16(eax + 0x80));
    ebx = MEM32(-25157620);
    /* TODO: sti  */
    esi = eax;
    eax = eax & 0x7FFF;
    esi = esi ^ edx;
    eax = eax | edx;
    esi = esi & 0x8000;
    esi = esi + eax;
    eax = esi;
    eax = eax - MEM32(ecx + 0x4D8);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0x14) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0x14 (32-bit) */
    MEM32(ebp + -4) = eax;
    if (CMP_B(_fa, _fb)) goto loc_0022479F; /* jb: below (unsigned <) */

loc_002246D5: ;
    edx = MEM32(ecx + 0x4D0);
    PUSH32(esp, edi);
    edi = esi + esi * 2;
    edi = edi << 4;
    edi = edi - ebx;
    _fa = (uint32_t)(edx) & 0xFFFFFFFFu; _fb = (uint32_t)(edx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test edx, edx (32-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_00224700; /* jne: not equal / not zero */

loc_002246E8: ;
    MEM32(ecx + 0x4D4) = MEM32(ecx + 0x4D4) & 0;
    MEM32(ecx + 0x4D0) = edi;
    MEM32(ecx + 0x4D8) = esi;
    goto loc_0022479E;

loc_00224700: ;
    eax = edi;
    eax = eax - edx;
    if (((int32_t)eax >= 0)) goto loc_00224709; /* jns: not sign (positive) */

loc_00224706: ;
    eax = eax + 0x2F;

loc_00224709: ;
    PUSH32(esp, 0x30);
    edx = ((int32_t)eax < 0) ? 0xFFFFFFFF : 0; /* cdq */
    POP32(esp, ebx);
    { int64_t _dividend = ((int64_t)(int32_t)edx << 32) | eax;
      eax = (uint32_t)((int32_t)(_dividend / (int32_t)ebx));
      edx = (uint32_t)((int32_t)(_dividend % (int32_t)ebx)); }
    ebx = MEM32(ecx + 0x4D4);
    edx = eax;
    edx = edx - ebx;
    if ((edx != 0)) goto loc_00224730; /* jne: not equal / not zero */

loc_0022471B: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0022479E; /* je: equal / zero */

loc_0022471F: ;
    _fa = (uint32_t)(MEM32(ebp + -4)) & 0xFFFFFFFFu; _fb = (uint32_t)(0x61A8) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(ebp + -4), 0x61A8 (32-bit) */
    if (CMP_BE(_fa, _fb)) goto loc_0022479E; /* jbe: below or equal (unsigned <=) */

loc_00224728: ;
    MEM32(ecx + 0x4D8) = esi;
    goto loc_0022475A;

loc_00224730: ;
    _fa = (uint32_t)(edx) & 0xFFFFFFFFu; _fb = (uint32_t)(3) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edx, 3 (32-bit) */
    MEM32(ecx + 0x4D4) = eax;
    MEM32(ecx + 0x4D8) = esi;
    if (CMP_G(_fas, _fbs)) goto loc_002246E8; /* jg: greater (signed >) */

loc_00224741: ;
    _fa = (uint32_t)(edx) & 0xFFFFFFFFu; _fb = (uint32_t)(0xFFFFFFFDu) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edx, 0xFFFFFFFDu (32-bit) */
    if (CMP_L(_fas, _fbs)) goto loc_002246E8; /* jl: less (signed <) */

loc_00224746: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0022479E; /* je: equal / zero */

loc_0022474A: ;
    _fa = (uint32_t)(edx) & 0xFFFFFFFFu; _fb = (uint32_t)(edx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test edx, edx (32-bit) */
    if (CMP_LE(_fas & _fbs, 0)) goto loc_00224754; /* jle: less or equal (signed <=) */

loc_0022474E: ;
    _fa = (uint32_t)(ebx) & 0xFFFFFFFFu; _fb = (uint32_t)(ebx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ebx, ebx (32-bit) */
    if (CMP_GE(_fas & _fbs, 0)) goto loc_0022475A; /* jge: greater or equal (signed >=) */

loc_00224752: ;
    _fa = (uint32_t)(edx) & 0xFFFFFFFFu; _fb = (uint32_t)(edx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test edx, edx (32-bit) */

loc_00224754: ;
    if (CMP_GE(_fas & _fbs, 0)) goto loc_0022479E; /* jge: greater or equal (signed >=) */

loc_00224756: ;
    _fa = (uint32_t)(ebx) & 0xFFFFFFFFu; _fb = (uint32_t)(ebx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ebx, ebx (32-bit) */
    if (CMP_G(_fas & _fbs, 0)) goto loc_0022479E; /* jg: greater (signed >) */

loc_0022475A: ;
    ecx = MEM32(ecx);
    edx = MEM32(ecx + 0x34);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    esi = edx;
    eax = 0x3FFF;
    if (CMP_LE(_fas & _fbs, 0)) goto loc_00224779; /* jle: less or equal (signed <=) */

loc_0022476A: ;
    esi = esi & eax;
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(0x2EE1) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp esi, 0x2EE1 (32-bit) */
    if (CMP_AE(_fa, _fb)) goto loc_0022478C; /* jae: above or equal (unsigned >=) */

loc_00224774: ;
    esi = edx + 1;
    goto loc_00224786;

loc_00224779: ;
    esi = esi & eax;
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(0x2ED1) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp esi, 0x2ED1 (32-bit) */
    if (CMP_BE(_fa, _fb)) goto loc_0022478C; /* jbe: below or equal (unsigned <=) */

loc_00224783: ;
    esi = edx + -1;

loc_00224786: ;
    esi = esi ^ edx;
    esi = esi & eax;
    edx = edx ^ esi;

loc_0022478C: ;
    eax = edx;
    eax = ~eax;
    eax = eax ^ edx;
    eax = eax & 0x7FFFFFFF;
    edx = ~edx;
    eax = eax ^ edx;
    MEM32(ecx + 0x34) = eax;

loc_0022479E: ;
    POP32(esp, edi);

loc_0022479F: ;
    POP32(esp, esi);
    POP32(esp, ebx);
    esp = ebp;
    POP32(esp, ebp); /* leave */
    esp += 4; return; /* ret */

}

/**
 * sub_002247A3
 * Original: 0x002247A3 - 0x0022481F (124 bytes, 48 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_002247A3(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_002247A3: ;
    PUSH32(esp, ebx);
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    edi = MEM32(esp + 0x10);
    esi = edx;
    MEM8(esi + 0x27) = MEM8(esi + 0x27) - 1;
    eax = MEM32(edi + 0x18);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    ebx = ecx;
    if (TEST_Z(_fa, _fb)) goto loc_002247C6; /* je: equal / zero */

loc_002247B8: ;
    ecx = ZX16(MEM16(edi + 0x20));
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 1);
    PUSH32(esp, ecx);
    PUSH32(esp, eax);
    { uint32_t _icall_target = MEM32(0x225B8C); PUSH32(esp, 0x002247C6u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_002247C6: ;
    _fa = (uint32_t)(MEM8(edi + 0x22)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(edi + 0x22), 1 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0022480F; /* je: equal / zero */

loc_002247CC: ;
    eax = MEM32(ebx + 0x42C);
    ecx = 0; /* xor self */
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0022480F; /* je: equal / zero */

loc_002247D8: ;
    _fa = (uint32_t)(edi) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edi, eax (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_002247E5; /* je: equal / zero */

loc_002247DC: ;
    ecx = eax;
    eax = MEM32(eax + 0x24);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_002247D8; /* jne: not equal / not zero */

loc_002247E5: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0022480F; /* je: equal / zero */

loc_002247E9: ;
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, ecx (32-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_002247F8; /* jne: not equal / not zero */

loc_002247ED: ;
    ecx = MEM32(eax + 0x24);
    MEM32(ebx + 0x42C) = ecx;
    goto loc_002247FE;

loc_002247F8: ;
    edx = MEM32(eax + 0x24);
    MEM32(ecx + 0x24) = edx;

loc_002247FE: ;
    MEM32(eax + 0x24) = MEM32(eax + 0x24) & 0;
    MEM8(esi + 0x20) = MEM8(esi + 0x20) - 1;
    if ((MEM8(esi + 0x20) != 0)) goto loc_0022480F; /* jne: not equal / not zero */

loc_00224807: ;
    MEM8(esi + 0x10) = MEM8(esi + 0x10) & 0xDF;
    MEM8(esi + 1) = MEM8(esi + 1) & 0xBF;

loc_0022480F: ;
    MEM8(edi + 0x22) = MEM8(edi + 0x22) | 8;
    PUSH32(esp, edi);
    PUSH32(esp, 0x00224819u); sub_002231A4(); /* call 0x002231A4 */

loc_00224819: ;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebx);
    esp += 8; return; /* ret 4 */

}

/**
 * sub_0022481F
 * Original: 0x0022481F - 0x00224851 (50 bytes, 15 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0022481F(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_0022481F: ;
    eax = ZX8(MEM8(edx + 0x11));
    eax = eax - 0;
    if ((eax == 0)) goto loc_00224844; /* je: equal / zero */

loc_00224828: ;
    eax--;
    eax--;
    if ((eax == 0)) goto loc_00224838; /* je: equal / zero */

loc_0022482C: ;
    eax--;
    if ((eax != 0)) goto loc_00224850; /* jne: not equal / not zero */

loc_0022482F: ;
    MEM16(edx + 0x24) = MEM16(edx + 0x24) - 1;
    g_seh_ebp = ebp; sub_002257E4(); return; /* tail jmp 0x002257E4 */

loc_00224838: ;
    MEM16(0x2878A6) = MEM16(0x2878A6) + 1;
    g_seh_ebp = ebp; sub_00225837(); return; /* tail jmp 0x00225837 */

loc_00224844: ;
    MEM16(0x2878A2) = MEM16(0x2878A2) + 1;
    g_seh_ebp = ebp; sub_00225884(); return; /* tail jmp 0x00225884 */

loc_00224850: ;
    esp += 4; return; /* ret */

}

/**
 * sub_00224851
 * Original: 0x00224851 - 0x00224945 (244 bytes, 87 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00224851(void)
{
    uint32_t ebp;
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00224851: ;
    PUSH32(esp, ebp);
    ebp = esp;
    g_ebp = ebp; /* publish frame for frameless callees */
    esp = esp - 0x10;
    eax = MEM32(edx);
    PUSH32(esp, ebx);
    ebx = MEM32(edx + 0x18);
    PUSH32(esp, esi);
    eax = eax >> 0x1C;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(9) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 9 (32-bit) */
    PUSH32(esp, edi);
    edi = MEM32(edx + 0x14);
    MEM32(ebp + -8) = ecx;
    MEM32(ebp + -16) = ebx;
    MEM8(ebp + -1) = 1;
    if (CMP_NE(_fa, _fb)) goto loc_002248C0; /* jne: not equal / not zero */

loc_00224874: ;
    _fa = (uint32_t)(MEM8(ebx + 0x1D)) & 0xFFu; _fb = (uint32_t)(0) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(ebx + 0x1D), 0 (8-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_002248C0; /* je: equal / zero */

loc_0022487A: ;
    eax = MEM32(edx + 4);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_002248AF; /* je: equal / zero */

loc_00224881: ;
    ecx = MEM32(edx + 0xC);
    esi = 0xFFF;
    eax = eax & esi;
    ecx = ecx & esi;
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp ecx, eax (32-bit) */
    MEM32(ebp + -12) = eax;
    if (CMP_L(_fas, _fbs)) goto loc_0022489F; /* jl: less (signed <) */

loc_00224894: ;
    eax = ZX8(MEM8(edx + 0x1D));
    eax = eax - ecx;
    eax = eax + MEM32(ebp + -12);
    goto loc_002248AC;

loc_0022489F: ;
    esi = ZX8(MEM8(edx + 0x1D));
    esi = esi - ecx;
    eax = esi + eax + -4096;

loc_002248AC: ;
    eax--;
    goto loc_002248B3;

loc_002248AF: ;
    eax = ZX8(MEM8(edx + 0x1D));

loc_002248B3: ;
    MEM32(ebx + 0x14) = MEM32(ebx + 0x14) + eax;
    MEM32(ebx + 4) = MEM32(ebx + 4) & 0;
    MEM8(ebp + -1) = 0;
    goto loc_002248D9;

loc_002248C0: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0xF) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0xF (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_002248CC; /* jne: not equal / not zero */

loc_002248C5: ;
    MEM32(ebx + 4) = 0xC000000Fu;

loc_002248CC: ;
    eax = MEM32(edx);
    eax = eax >> 0x1C;
    eax = eax | 0xC0000000u;
    MEM32(ebx + 4) = eax;

loc_002248D9: ;
    esi = MEM32(edi + 8);
    esi = esi & 0xFFFFFFF0u;

loc_002248DF: ;
    SET_LO8(ebx, MEM8(edx + 0x1C));
    PUSH32(esp, edx);
    SET_LO8(ebx, LO8(ebx) & 2);
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x002248EBu); sub_0022414A(); /* call 0x0022414A */

loc_002248EB: ;
    ecx = MEM32(ebp + -8);
    edx = edi;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x002248F5u); sub_0022481F(); /* call 0x0022481F */

loc_002248F5: ;
    eax = MEM32(0x287880);
    edx = eax + esi;
    _fa = (uint32_t)(MEM8(edx + 0x1E)) & 0xFFu; _fb = (uint32_t)(2) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(edx + 0x1E), 2 (8-bit) */
    esi = MEM32(edx + 8);
    if (CMP_NE(_fa, _fb)) goto loc_0022490C; /* jne: not equal / not zero */

loc_00224906: ;
    _fa = (uint32_t)(MEM8(ebp + -1)) & 0xFFu; _fb = (uint32_t)(0) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(ebp + -1), 0 (8-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_00224910; /* je: equal / zero */

loc_0022490C: ;
    _fa = (uint32_t)(LO8(ebx)) & 0xFFu; _fb = (uint32_t)(LO8(ebx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(ebx), LO8(ebx) (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_002248DF; /* je: equal / zero */

loc_00224910: ;
    eax = MEM32(edx + 0x10);
    eax = eax ^ MEM32(edi + 8);
    eax = eax & 0xF;
    eax = eax ^ MEM32(edx + 0x10);
    _fa = (uint32_t)(LO8(ebx)) & 0xFFu; _fb = (uint32_t)(LO8(ebx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(ebx), LO8(ebx) (8-bit) */
    MEM32(edi + 8) = eax;
    if (TEST_Z(_fa, _fb)) goto loc_00224930; /* je: equal / zero */

loc_00224923: ;
    PUSH32(esp, MEM32(ebp + -16));
    ecx = MEM32(ebp + -8);
    edx = edi;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00224930u); sub_002247A3(); /* call 0x002247A3 */

loc_00224930: ;
    _fa = (uint32_t)(MEM8(edi + 0x11)) & 0xFFu; _fb = (uint32_t)(0) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(edi + 0x11), 0 (8-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_0022493C; /* je: equal / zero */

loc_00224936: ;
    _fa = (uint32_t)(MEM8(ebp + -1)) & 0xFFu; _fb = (uint32_t)(0) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(ebp + -1), 0 (8-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_00224940; /* jne: not equal / not zero */

loc_0022493C: ;
    MEM32(edi + 8) = MEM32(edi + 8) & 0xFFFFFFFEu;

loc_00224940: ;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebx);
    esp = ebp;
    POP32(esp, ebp); /* leave */
    esp += 4; return; /* ret */

}

/**
 * sub_00224945
 * Original: 0x00224945 - 0x002249F1 (172 bytes, 64 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00224945(void)
{
    uint32_t ebp;
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00224945: ;
    PUSH32(esp, ebp);
    ebp = esp;
    g_ebp = ebp; /* publish frame for frameless callees */
    PUSH32(esp, ecx);
    PUSH32(esp, ecx);
    PUSH32(esp, esi);
    esi = edx;
    _fa = (uint32_t)(MEM8(esi + 0x1E)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(esi + 0x1E), 1 (8-bit) */
    eax = MEM32(esi + 0x14);
    PUSH32(esp, edi);
    edi = MEM32(esi + 0x18);
    MEM32(ebp + -4) = ecx;
    MEM32(ebp + -8) = eax;
    if (CMP_NE(_fa, _fb)) goto loc_0022497A; /* jne: not equal / not zero */

loc_00224960: ;
    eax = MEM32(esi + 0xC);
    ecx = MEM32(0x287880);
    eax = eax + ecx + -7;
    PUSH32(esp, eax);
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00224973u); sub_0022414A(); /* call 0x0022414A */

loc_00224973: ;
    MEM16(0x2878A2) = MEM16(0x2878A2) + 1;

loc_0022497A: ;
    _fa = (uint32_t)(MEM8(esi + 3)) & 0xFFu; _fb = (uint32_t)(0xF0) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(esi + 3), 0xF0 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0022498C; /* je: equal / zero */

loc_00224980: ;
    ecx = MEM32(ebp + -4);
    edx = esi;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x0022498Au); sub_00224851(); /* call 0x00224851 */

loc_0022498A: ;
    goto loc_002249ED;

loc_0022498C: ;
    eax = MEM32(esi + 4);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    PUSH32(esp, ebx);
    if (TEST_Z(_fa, _fb)) goto loc_002249BA; /* je: equal / zero */

loc_00224994: ;
    ecx = MEM32(esi + 0xC);
    edx = 0xFFF;
    eax = eax & edx;
    ebx = eax;
    eax = ZX8(MEM8(esi + 0x1D));
    ecx = ecx & edx;
    eax = eax - ecx;
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ebx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp ecx, ebx (32-bit) */
    if (CMP_L(_fas, _fbs)) goto loc_002249B0; /* jl: less (signed <) */

loc_002249AC: ;
    eax = eax + ebx;
    goto loc_002249B7;

loc_002249B0: ;
    eax = eax + ebx + -4096;

loc_002249B7: ;
    eax--;
    goto loc_002249BE;

loc_002249BA: ;
    eax = ZX8(MEM8(esi + 0x1D));

loc_002249BE: ;
    MEM32(edi + 0x14) = MEM32(edi + 0x14) + eax;
    SET_LO8(ebx, MEM8(esi + 0x1C));
    PUSH32(esp, esi);
    SET_LO8(ebx, LO8(ebx) & 2);
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x002249CDu); sub_0022414A(); /* call 0x0022414A */

loc_002249CD: ;
    edx = MEM32(ebp + -8);
    ecx = MEM32(ebp + -4);
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x002249D8u); sub_0022481F(); /* call 0x0022481F */

loc_002249D8: ;
    _fa = (uint32_t)(LO8(ebx)) & 0xFFu; _fb = (uint32_t)(LO8(ebx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(ebx), LO8(ebx) (8-bit) */
    POP32(esp, ebx);
    if (TEST_Z(_fa, _fb)) goto loc_002249ED; /* je: equal / zero */

loc_002249DD: ;
    edx = MEM32(ebp + -8);
    ecx = MEM32(ebp + -4);
    MEM32(edi + 4) = MEM32(edi + 4) & 0;
    PUSH32(esp, edi);
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x002249EDu); sub_002247A3(); /* call 0x002247A3 */

loc_002249ED: ;
    POP32(esp, edi);
    POP32(esp, esi);
    esp = ebp;
    POP32(esp, ebp); /* leave */
    esp += 4; return; /* ret */

}

/**
 * sub_002249F1
 * Original: 0x002249F1 - 0x00224AF3 (258 bytes, 87 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_002249F1(void)
{
    uint32_t ebp;
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_002249F1: ;
    PUSH32(esp, ebp);
    ebp = esp;
    g_ebp = ebp; /* publish frame for frameless callees */
    esp = esp - 0x18;
    PUSH32(esp, ebx);
    PUSH32(esp, edi);
    edi = edx;
    ebx = ecx;
    edx = 0; /* xor self */
    _fa = (uint32_t)(MEM32(ebx + 0x42C)) & 0xFFFFFFFFu; _fb = (uint32_t)(edx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(ebx + 0x42C), edx (32-bit) */
    MEM32(ebp + -20) = edi;
    MEM32(ebp + -8) = ebx;
    MEM32(ebp + -4) = edx;
    if (CMP_EQ(_fa, _fb)) goto loc_00224AE2; /* je: equal / zero */

loc_00224A14: ;
    PUSH32(esp, esi);
    goto loc_00224A1A;

loc_00224A17: ;
    edi = MEM32(ebp + -20);

loc_00224A1A: ;
    ecx = MEM32(ebx + 0x42C);
    eax = MEM32(ecx + 0x24);
    MEM32(ebx + 0x42C) = eax;
    esi = MEM32(ecx + 0x10);
    _fa = (uint32_t)(edi) & 0xFFFFFFFFu; _fb = (uint32_t)(MEM32(esi + 0x1C)) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edi, MEM32(esi + 0x1C) (32-bit) */
    if (CMP_AE(_fa, _fb)) goto loc_00224A3C; /* jae: above or equal (unsigned >=) */

loc_00224A31: ;
    MEM32(ecx + 0x24) = edx;
    MEM32(ebp + -4) = ecx;
    goto loc_00224AD1;

loc_00224A3C: ;
    SET_LO8(eax, MEM8(esi + 0x10));
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(0x40) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), 0x40 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00224A4E; /* je: equal / zero */

loc_00224A43: ;
    edi++;
    SET_LO8(eax, LO8(eax) & 0xBF);
    MEM32(esi + 0x1C) = edi;
    MEM8(esi + 0x10) = LO8(eax);
    goto loc_00224A31;

loc_00224A4E: ;
    eax = MEM32(esi + 8);
    edi = MEM32(0x287880);
    MEM32(ebp + -12) = MEM32(ebp + -12) & 0;
    MEM32(ebp + -24) = eax;
    eax = eax & 0xFFFFFFF0u;
    edx = edi + eax;
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(MEM32(edx + 0x18)) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp ecx, MEM32(edx + 0x18) (32-bit) */
    MEM32(ebp + -16) = eax;
    if (CMP_EQ(_fa, _fb)) goto loc_00224A84; /* je: equal / zero */

loc_00224A6C: ;
    ebx = MEM32(esi + 4);

loc_00224A6F: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(ebx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, ebx (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_00224A81; /* je: equal / zero */

loc_00224A73: ;
    MEM32(ebp + -12) = eax;
    eax = MEM32(edx + 8);
    edx = edi + eax;
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(MEM32(edx + 0x18)) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp ecx, MEM32(edx + 0x18) (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_00224A6F; /* jne: not equal / not zero */

loc_00224A81: ;
    ebx = MEM32(ebp + -8);

loc_00224A84: ;
    eax = MEM32(edx + 8);
    eax = eax ^ MEM32(ebp + -24);
    ecx = ebx;
    eax = eax & 0xF;
    eax = eax ^ MEM32(edx + 8);
    MEM32(esi + 8) = eax;
    MEM8(edx + 3) = MEM8(edx + 3) | 0xF0;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00224A9Eu); sub_00224945(); /* call 0x00224945 */

loc_00224A9E: ;
    eax = MEM32(ebp + -12);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00224AC4; /* je: equal / zero */

loc_00224AA5: ;
    ecx = MEM32(esi + 8);
    edx = MEM32(0x287880);
    ecx = ecx & 0xFFFFFFF0u;
    MEM32(edx + eax + 8) = ecx;
    eax = MEM32(esi + 8);
    eax = eax ^ MEM32(ebp + -16);
    eax = eax & 0xF;
    eax = eax ^ MEM32(ebp + -16);
    MEM32(esi + 8) = eax;

loc_00224AC4: ;
    MEM8(esi + 0x20) = MEM8(esi + 0x20) - 1;
    if ((MEM8(esi + 0x20) != 0)) goto loc_00224AD1; /* jne: not equal / not zero */

loc_00224AC9: ;
    MEM8(esi + 0x10) = MEM8(esi + 0x10) & 0xDF;
    MEM8(esi + 1) = MEM8(esi + 1) & 0xBF;

loc_00224AD1: ;
    _fa = (uint32_t)(MEM32(ebx + 0x42C)) & 0xFFFFFFFFu; _fb = (uint32_t)(0) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(ebx + 0x42C), 0 (32-bit) */
    edx = MEM32(ebp + -4);
    if (CMP_NE(_fa, _fb)) goto loc_00224A17; /* jne: not equal / not zero */

loc_00224AE1: ;
    POP32(esp, esi);

loc_00224AE2: ;
    eax = 0; /* xor self */
    _fa = (uint32_t)(edx) & 0xFFFFFFFFu; _fb = (uint32_t)(edx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test edx, edx (32-bit) */
    POP32(esp, edi);
    MEM32(ebx + 0x42C) = edx;
    SET_LO8(eax, (TEST_NZ(_fa, _fb)) ? 1 : 0); /* setne */
    POP32(esp, ebx);
    esp = ebp;
    POP32(esp, ebp); /* leave */
    esp += 4; return; /* ret */

}

/**
 * sub_00224AF3
 * Original: 0x00224AF3 - 0x00224B49 (86 bytes, 35 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00224AF3(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00224AF3: ;
    PUSH32(esp, ebx);
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    esi = edx;
    edi = ecx;
    SET_LO8(ebx, 0); /* xor self */

loc_00224AFC: ;
    eax = MEM32(esi + 8);
    ecx = eax;
    ecx = ecx & 0xFFFFFFF0u;
    if ((ecx == 0)) goto loc_00224B45; /* je: equal / zero */

loc_00224B06: ;
    edx = MEM32(0x287880);
    edx = edx + ecx;
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(MEM32(esi + 4)) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp ecx, MEM32(esi + 4) (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_00224B2F; /* je: equal / zero */

loc_00224B13: ;
    eax = MEM32(edx + 8);
    MEM8(edx + 3) = MEM8(edx + 3) | 0xF0;
    eax = eax ^ MEM32(esi + 8);
    ecx = edi;
    eax = eax & 0xF;
    eax = eax ^ MEM32(edx + 8);
    MEM32(esi + 8) = eax;
    PUSH32(esp, 0x00224B2Du); sub_00224945(); /* call 0x00224945 */

loc_00224B2D: ;
    goto loc_00224B41;

loc_00224B2F: ;
    MEM32(esi + 4) = MEM32(esi + 4) & 0;
    eax = eax & 0xF;
    PUSH32(esp, edx);
    MEM32(esi + 8) = eax;
    PUSH32(esp, 0x00224B3Fu); sub_0022414A(); /* call 0x0022414A */

loc_00224B3F: ;
    SET_LO8(ebx, 1);

loc_00224B41: ;
    _fa = (uint32_t)(LO8(ebx)) & 0xFFu; _fb = (uint32_t)(LO8(ebx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(ebx), LO8(ebx) (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00224AFC; /* je: equal / zero */

loc_00224B45: ;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebx);
    esp += 4; return; /* ret */

}

/**
 * sub_00224B49
 * Original: 0x00224B49 - 0x00224BD0 (135 bytes, 50 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00224B49(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_00224B49: ;
    PUSH32(esp, ecx);
    PUSH32(esp, ebx);
    PUSH32(esp, ebp);
    ebx = ecx;
    ebp = 0; /* xor self */
    _fa = (uint32_t)(MEM32(ebx + 0x430)) & 0xFFFFFFFFu; _fb = (uint32_t)(ebp) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(ebx + 0x430), ebp (32-bit) */
    MEM32(esp + 8) = edx;
    if (CMP_EQ(_fa, _fb)) goto loc_00224BBF; /* je: equal / zero */

loc_00224B5C: ;
    PUSH32(esp, esi);
    PUSH32(esp, edi);

loc_00224B5E: ;
    edi = MEM32(ebx + 0x430);
    eax = MEM32(edi + 0x24);
    MEM32(ebx + 0x430) = eax;
    esi = MEM32(edi + 0x10);
    _fa = (uint32_t)(edx) & 0xFFFFFFFFu; _fb = (uint32_t)(MEM32(esi + 0x1C)) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edx, MEM32(esi + 0x1C) (32-bit) */
    if (CMP_AE(_fa, _fb)) goto loc_00224B7C; /* jae: above or equal (unsigned >=) */

loc_00224B75: ;
    MEM32(edi + 0x14) = ebp;
    ebp = edi;
    goto loc_00224BB4;

loc_00224B7C: ;
    SET_LO8(eax, MEM8(esi + 0x10));
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(0x40) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), 0x40 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00224B90; /* je: equal / zero */

loc_00224B83: ;
    ecx = edx + 1;
    SET_LO8(eax, LO8(eax) & 0xBF);
    MEM32(esi + 0x1C) = ecx;
    MEM8(esi + 0x10) = LO8(eax);
    goto loc_00224B75;

loc_00224B90: ;
    edx = esi;
    ecx = ebx;
    PUSH32(esp, 0x00224B99u); sub_00224AF3(); /* call 0x00224AF3 */

loc_00224B99: ;
    MEM8(esi + 0x20) = MEM8(esi + 0x20) - 1;
    if ((MEM8(esi + 0x20) != 0)) goto loc_00224BA6; /* jne: not equal / not zero */

loc_00224B9E: ;
    MEM8(esi + 0x10) = MEM8(esi + 0x10) & 0xDF;
    MEM8(esi + 1) = MEM8(esi + 1) & 0xBF;

loc_00224BA6: ;
    MEM32(edi + 4) = MEM32(edi + 4) & 0;
    PUSH32(esp, edi);
    PUSH32(esp, 0x00224BB0u); sub_002231A4(); /* call 0x002231A4 */

loc_00224BB0: ;
    edx = MEM32(esp + 0x10);

loc_00224BB4: ;
    _fa = (uint32_t)(MEM32(ebx + 0x430)) & 0xFFFFFFFFu; _fb = (uint32_t)(0) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(ebx + 0x430), 0 (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_00224B5E; /* jne: not equal / not zero */

loc_00224BBD: ;
    POP32(esp, edi);
    POP32(esp, esi);

loc_00224BBF: ;
    eax = 0; /* xor self */
    MEM32(ebx + 0x430) = ebp;
    _fa = (uint32_t)(ebp) & 0xFFFFFFFFu; _fb = (uint32_t)(ebp) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ebp, ebp (32-bit) */
    POP32(esp, ebp);
    SET_LO8(eax, (TEST_NZ(_fa, _fb)) ? 1 : 0); /* setne */
    POP32(esp, ebx);
    POP32(esp, ecx);
    esp += 4; return; /* ret */

}

/**
 * sub_00224BD0
 * Original: 0x00224BD0 - 0x00224CAA (218 bytes, 75 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00224BD0(void)
{
    uint32_t ebp;
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00224BD0: ;
    PUSH32(esp, ebp);
    ebp = esp;
    g_ebp = ebp; /* publish frame for frameless callees */
    esp = esp - 0xC;
    PUSH32(esp, ebx);
    ebx = ecx;
    ecx = 0; /* xor self */
    _fa = (uint32_t)(MEM32(ebx + 0x434)) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(ebx + 0x434), ecx (32-bit) */
    MEM32(ebp + -8) = edx;
    MEM32(ebp + -4) = ecx;
    if (CMP_EQ(_fa, _fb)) goto loc_00224C9A; /* je: equal / zero */

loc_00224BED: ;
    PUSH32(esp, esi);
    PUSH32(esp, edi);

loc_00224BEF: ;
    esi = MEM32(ebx + 0x434);
    eax = MEM32(esi + 0x14);
    MEM32(ebx + 0x434) = eax;
    edi = MEM32(esi + 0x10);
    eax = MEM32(ebp + -8);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(MEM32(edi + 0x1C)) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, MEM32(edi + 0x1C) (32-bit) */
    if (CMP_AE(_fa, _fb)) goto loc_00224C11; /* jae: above or equal (unsigned >=) */

loc_00224C09: ;
    MEM32(esi + 0x14) = ecx;
    MEM32(ebp + -4) = esi;
    goto loc_00224C88;

loc_00224C11: ;
    SET_LO8(eax, MEM8(edi + 0x10));
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(0x40) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), 0x40 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00224C1F; /* je: equal / zero */

loc_00224C18: ;
    SET_LO8(eax, LO8(eax) & 0xBF);
    MEM8(edi + 0x10) = LO8(eax);
    goto loc_00224C09;

loc_00224C1F: ;
    _fa = (uint32_t)(MEM8(esi + 1)) & 0xFFu; _fb = (uint32_t)(0x4A) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(esi + 1), 0x4A (8-bit) */
    ecx = ebx;
    if (CMP_NE(_fa, _fb)) goto loc_00224C30; /* jne: not equal / not zero */

loc_00224C27: ;
    edx = esi;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00224C2Eu); sub_00224FC3(); /* call 0x00224FC3 */

loc_00224C2E: ;
    goto loc_00224C88;

loc_00224C30: ;
    edx = edi;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00224C37u); sub_00224AF3(); /* call 0x00224AF3 */

loc_00224C37: ;
    edx = MEM32(esi + 0x18);
    _fa = (uint32_t)(edx) & 0xFFFFFFFFu; _fb = (uint32_t)(edx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test edx, edx (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00224C70; /* je: equal / zero */

loc_00224C3E: ;
    ecx = MEM32(edi);
    MEM32(ebp + -12) = ecx;
    ecx = ecx >> 7;
    eax = 0; /* xor self */
    ecx = ecx & 0xF;
    eax++;
    eax = eax << LO8(ecx);
    ecx = MEM32(ebp + -12);
    ecx = ecx & 0x1800;
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(0x1000) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp ecx, 0x1000 (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_00224C62; /* jne: not equal / not zero */

loc_00224C5F: ;
    eax = eax << 0x10;

loc_00224C62: ;
    _fa = (uint32_t)(MEM8(edi + 8)) & 0xFFu; _fb = (uint32_t)(2) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(edi + 8), 2 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00224C6C; /* je: equal / zero */

loc_00224C68: ;
    MEM32(edx) = MEM32(edx) | eax;
    goto loc_00224C70;

loc_00224C6C: ;
    eax = ~eax;
    MEM32(edx) = MEM32(edx) & eax;

loc_00224C70: ;
    eax = MEM32(0x287888);
    MEM32(edi + 0x18) = eax;
    MEM32(0x287888) = edi;
    MEM32(esi + 4) = MEM32(esi + 4) & 0;
    PUSH32(esp, esi);
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00224C88u); sub_002231A4(); /* call 0x002231A4 */

loc_00224C88: ;
    _fa = (uint32_t)(MEM32(ebx + 0x434)) & 0xFFFFFFFFu; _fb = (uint32_t)(0) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(ebx + 0x434), 0 (32-bit) */
    ecx = MEM32(ebp + -4);
    if (CMP_NE(_fa, _fb)) goto loc_00224BEF; /* jne: not equal / not zero */

loc_00224C98: ;
    POP32(esp, edi);
    POP32(esp, esi);

loc_00224C9A: ;
    eax = 0; /* xor self */
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, ecx (32-bit) */
    MEM32(ebx + 0x434) = ecx;
    SET_LO8(eax, (TEST_NZ(_fa, _fb)) ? 1 : 0); /* setne */
    POP32(esp, ebx);
    esp = ebp;
    POP32(esp, ebp); /* leave */
    esp += 4; return; /* ret */

}

/**
 * sub_00224CAA
 * Original: 0x00224CAA - 0x00224DC0 (278 bytes, 96 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00224CAA(void)
{
    uint32_t ebp;
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00224CAA: ;
    PUSH32(esp, ebp);
    ebp = esp;
    g_ebp = ebp; /* publish frame for frameless callees */
    PUSH32(esp, ecx);
    PUSH32(esp, ecx);
    PUSH32(esp, ebx);
    PUSH32(esp, esi);
    esi = MEM32(ebp + 0xC);
    ebx = MEM32(esi);
    eax = esi + 0x438;
    ecx = MEM32(eax);
    PUSH32(esp, edi);
    MEM32(ebp + -4) = ecx;
    edi = 0; /* xor self */
    ecx = esi;
    MEM8(ebp + 0xF) = 0;
    MEM32(eax) = edi;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00224CD1u); sub_00224690(); /* call 0x00224690 */

loc_00224CD1: ;
    _fa = (uint32_t)(MEM8(ebp + -4)) & 0xFFu; _fb = (uint32_t)(2) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(ebp + -4), 2 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00224D2E; /* je: equal / zero */

loc_00224CD7: ;
    ecx = MEM32(esi + 8);
    ecx = ecx + 0x84;
    eax = MEM32(ecx);
    eax = eax & 0xFFFFFFF0u;
    MEM32(ecx) = edi;
    if ((eax == 0)) goto loc_00224D1A; /* je: equal / zero */

loc_00224CE9: ;
    ecx = MEM32(0x287880);
    ecx = ecx + eax;
    eax = MEM32(ecx + 8);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    MEM32(ecx + 8) = edi;
    edi = ecx;
    if (TEST_NZ(_fa, _fb)) goto loc_00224CE9; /* jne: not equal / not zero */

loc_00224CFD: ;
    edx = edi;
    _fa = (uint32_t)(MEM8(edx + 2)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(edx + 2), 1 (8-bit) */
    edi = MEM32(edi + 8);
    ecx = esi;
    if (TEST_Z(_fa, _fb)) goto loc_00224D11; /* je: equal / zero */

loc_00224D0A: ;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00224D0Fu); sub_0022532C(); /* call 0x0022532C */

loc_00224D0F: ;
    goto loc_00224D16;

loc_00224D11: ;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00224D16u); sub_00224945(); /* call 0x00224945 */

loc_00224D16: ;
    _fa = (uint32_t)(edi) & 0xFFFFFFFFu; _fb = (uint32_t)(edi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test edi, edi (32-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_00224CFD; /* jne: not equal / not zero */

loc_00224D1A: ;
    MEM32(ebp + -4) = MEM32(ebp + -4) & 0xFFFFFFFDu;
    MEM32(ebx + 0xC) = 2;
    eax = MEM32(esi);
    MEM32(eax + 8) = 6;

loc_00224D2E: ;
    _fa = (uint32_t)(MEM8(ebp + -4)) & 0xFFu; _fb = (uint32_t)(4) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(ebp + -4), 4 (8-bit) */
    PUSH32(esp, 4);
    POP32(esp, edi);
    if (TEST_Z(_fa, _fb)) goto loc_00224D41; /* je: equal / zero */

loc_00224D37: ;
    MEM32(ebp + -4) = MEM32(ebp + -4) & 0xFFFFFFFBu;
    MEM32(ebx + 0xC) = edi;
    MEM32(ebx + 0x14) = edi;

loc_00224D41: ;
    ecx = esi;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00224D48u); sub_0022466C(); /* call 0x0022466C */

loc_00224D48: ;
    edx = eax;
    ecx = esi;
    MEM32(ebp + -8) = edx;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00224D54u); sub_002249F1(); /* call 0x002249F1 */

loc_00224D54: ;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00224D5C; /* je: equal / zero */

loc_00224D58: ;
    MEM8(ebp + 0xF) = 1;

loc_00224D5C: ;
    edx = MEM32(ebp + -8);
    ecx = esi;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00224D66u); sub_00224B49(); /* call 0x00224B49 */

loc_00224D66: ;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00224D6E; /* je: equal / zero */

loc_00224D6A: ;
    MEM8(ebp + 0xF) = 1;

loc_00224D6E: ;
    edx = MEM32(ebp + -8);
    ecx = esi;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00224D78u); sub_00224BD0(); /* call 0x00224BD0 */

loc_00224D78: ;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00224D80; /* je: equal / zero */

loc_00224D7C: ;
    MEM8(ebp + 0xF) = 1;

loc_00224D80: ;
    _fa = (uint32_t)(MEM8(ebp + 0xF)) & 0xFFu; _fb = (uint32_t)(0) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(ebp + 0xF), 0 (8-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_00224D90; /* je: equal / zero */

loc_00224D86: ;
    eax = MEM32(esi);
    MEM32(eax + 0xC) = edi;
    eax = MEM32(esi);
    MEM32(eax + 0x10) = edi;

loc_00224D90: ;
    _fa = (uint32_t)(MEM8(ebp + -4)) & 0xFFu; _fb = (uint32_t)(0x40) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(ebp + -4), 0x40 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00224DA8; /* je: equal / zero */

loc_00224D96: ;
    ecx = esi;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00224D9Du); sub_00222A9D(); /* call 0x00222A9D */

loc_00224D9D: ;
    MEM32(ebp + -4) = MEM32(ebp + -4) & 0xFFFFFFBFu;
    MEM32(ebx + 0xC) = 0x40;

loc_00224DA8: ;
    eax = MEM32(ebp + -4);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00224DB2; /* je: equal / zero */

loc_00224DAF: ;
    MEM32(ebx + 0xC) = eax;

loc_00224DB2: ;
    POP32(esp, edi);
    POP32(esp, esi);
    MEM32(ebx + 0x10) = 0x80000000u;
    POP32(esp, ebx);
    esp = ebp;
    POP32(esp, ebp); /* leave */
    esp += 20; return; /* ret 16 */

}

/**
 * sub_00224DC0
 * Original: 0x00224DC0 - 0x00224DD2 (18 bytes, 6 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00224DC0(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00224DC0: ;
    eax = MEM32(0x2878A8);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00224DD1; /* je: equal / zero */

loc_00224DC9: ;
    ecx = MEM32(eax);
    MEM32(0x2878A8) = ecx;

loc_00224DD1: ;
    esp += 4; return; /* ret */

}

/**
 * sub_00224DD2
 * Original: 0x00224DD2 - 0x00224F7F (429 bytes, 148 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00224DD2(void)
{
    uint32_t ebp;
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00224DD2: ;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, ebp);
    ebp = esp;
    g_ebp = ebp; /* publish frame for frameless callees */
    esp = esp - 0x14;
    eax = MEM32(0x2878AC);
    PUSH32(esp, ebx);
    PUSH32(esp, edi);
    ebx = edx;
    MEM32(ebp + -20) = ecx;
    MEM32(ebp + -8) = eax;
    { uint32_t _icall_target = MEM32(0x225B30); PUSH32(esp, 0x00224DEDu); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00224DED: ;
    MEM8(ebp + -2) = LO8(eax);
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00224DF5u); sub_00224DC0(); /* call 0x00224DC0 */

loc_00224DF5: ;
    edi = eax;
    _fa = (uint32_t)(edi) & 0xFFFFFFFFu; _fb = (uint32_t)(edi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test edi, edi (32-bit) */
    MEM32(ebp + -12) = edi;
    if (TEST_NZ(_fa, _fb)) goto loc_00224E08; /* jne: not equal / not zero */

loc_00224DFE: ;
    edi = 0x80000100u;
    goto loc_00224F6D;

loc_00224E08: ;
    PUSH32(esp, esi);
    esi = MEM32(ebp + -8);
    esi = esi << 6;
    eax = 0; /* xor self */
    ecx = esi + 0x30;
    edx = ecx;
    ecx = ecx >> 2;
    { uint32_t _i; for (_i = 0; _i < ecx; _i++) MEM32(edi + _i*4) = eax; }
    edi += ecx * 4; ecx = 0; /* rep stosd */
    ecx = edx;
    ecx = ecx & 3;
    memset((void*)XBOX_PTR(edi), (uint8_t)eax, ecx);
    edi += ecx; ecx = 0; /* rep stosb */
    eax = MEM32(ebp + -12);
    esi = esi + eax;
    MEM32(esi + 0x2C) = eax;
    eax = esi;
    eax = eax - MEM32(0x287880);
    MEM8(esi + 0x11) = 1;
    MEM32(esi + 0x14) = eax;
    eax = 0; /* xor self */
    MEM8(esi + 0x13) = 1;
    SET_LO16(eax, MEM16(ebx + 0x16));
    PUSH32(esp, 0);
    PUSH32(esp, 1);
    PUSH32(esp, eax);
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00224E4Du); sub_002231B8(); /* call 0x002231B8 */

loc_00224E4D: ;
    edx = MEM32(ebp + -8);
    MEM16(esi + 0x22) = LO16(eax);
    MEM8(esi + 0x24) = LO8(edx);
    SET_LO8(eax, MEM8(ebx + 0x18));
    SET_LO8(eax, LO8(eax) & 1);
    MEM8(esi + 0x10) = LO8(eax);
    eax = 0; /* xor self */
    SET_LO8(eax, MEM8(ebx + 0x14));
    PUSH32(esp, 0);
    eax = eax ^ MEM32(esi);
    eax = eax & 0x7F;
    MEM32(esi) = MEM32(esi) ^ eax;
    eax = ZX8(MEM8(ebx + 0x15));
    ecx = MEM32(esi);
    eax = eax << 7;
    eax = eax ^ ecx;
    eax = eax & 0x780;
    eax = eax ^ ecx;
    MEM32(esi) = eax;
    _fa = (uint32_t)(MEM8(ebx + 0x15)) & 0xFFu; _fb = (uint32_t)(0x80) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(ebx + 0x15), 0x80 (8-bit) */
    POP32(esp, ecx);
    SET_LO8(ecx, (TEST_NZ(_fa, _fb)) ? 1 : 0); /* setne */
    eax = eax & 0xFFFFC7FFu;
    ecx++;
    ecx = ecx & 3;
    ecx = ecx | 0x18;
    ecx = ecx << 0xB;
    ecx = ecx | eax;
    MEM32(esi) = ecx;
    eax = ZX16(MEM16(ebx + 0x16));
    eax = eax << 0x10;
    eax = eax ^ ecx;
    eax = eax & 0x7FF0000;
    eax = eax ^ ecx;
    ecx = MEM32(esi + 8);
    MEM32(esi) = eax;
    eax = MEM32(esi + 0x2C);
    eax = eax - MEM32(0x287880);
    ecx = ecx ^ eax;
    ecx = ecx & 0xF;
    ecx = ecx ^ eax;
    MEM32(esi + 8) = ecx;
    SET_LO8(ecx, 0); /* xor self */
    _fa = (uint32_t)(edx) & 0xFFFFFFFFu; _fb = (uint32_t)(edx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test edx, edx (32-bit) */
    MEM32(esi + 4) = eax;
    MEM8(ebp + -1) = LO8(ecx);
    if (CMP_BE(_fa & _fb, 0)) goto loc_00224F2D; /* jbe: below or equal (unsigned <=) */

loc_00224ED0: ;
    eax = 0; /* xor self */

loc_00224ED2: ;
    edx = MEM32(esi + 0x2C);
    eax = eax << 6;
    edi = eax + edx;
    MEM32(ebp + -16) = edi;
    edi = edi - MEM32(0x287880);
    edx = MEM32(ebp + -16);
    edi = edi + 0x40;
    SET_LO8(ecx, LO8(ecx) - 1);
    MEM8(edx + 0x2D) = LO8(ecx);
    edx = MEM32(esi + 0x2C);
    SET_LO8(ecx, MEM8(ebp + -1));
    MEM8(eax + edx + 0x2C) = LO8(ecx);
    edx = MEM32(esi + 0x2C);
    MEM32(eax + edx + 0x20) = esi;
    edx = MEM32(esi + 0x2C);
    MEM32(eax + edx + 0x28) = MEM32(eax + edx + 0x28) & 0;
    edx = MEM32(esi + 0x2C);
    MEM32(eax + edx + 0x24) = MEM32(eax + edx + 0x24) & 0;
    edx = MEM32(esi + 0x2C);
    edx = edx + eax;
    MEM8(edx + 2) = MEM8(edx + 2) | 1;
    edx = MEM32(esi + 0x2C);
    SET_LO8(ecx, LO8(ecx) + 1);
    MEM32(eax + edx + 8) = edi;
    eax = ZX8(LO8(ecx));
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(MEM32(ebp + -8)) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, MEM32(ebp + -8) (32-bit) */
    MEM8(ebp + -1) = LO8(ecx);
    if (CMP_B(_fa, _fb)) goto loc_00224ED2; /* jb: below (unsigned <) */

loc_00224F2D: ;
    edx = MEM32(esi + 0x2C);
    eax = ZX8(LO8(ecx));
    eax = eax << 6;
    MEM32(eax + edx + -56) = MEM32(eax + edx + -56) & 0;
    eax = MEM32(esi + 0x2C);
    SET_LO8(ecx, LO8(ecx) - 1);
    MEM8(eax + 0x2D) = LO8(ecx);
    ecx = MEM32(ebp + -20);
    edx = esi;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00224F4Du); sub_00224281(); /* call 0x00224281 */

loc_00224F4D: ;
    edi = eax;
    _fa = (uint32_t)(edi) & 0xFFFFFFFFu; _fb = (uint32_t)(edi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test edi, edi (32-bit) */
    if (TEST_S(_fas, _fbs)) goto loc_00224F58; /* jl: less (signed <) */

loc_00224F53: ;
    MEM32(ebx + 0x10) = esi;
    goto loc_00224F6C;

loc_00224F58: ;
    MEM32(ebx + 0x10) = MEM32(ebx + 0x10) & 0;
    ecx = MEM32(0x2878A8);
    eax = MEM32(ebp + -12);
    MEM32(eax) = ecx;
    MEM32(0x2878A8) = eax;

loc_00224F6C: ;
    POP32(esp, esi);

loc_00224F6D: ;
    SET_LO8(ecx, MEM8(ebp + -2));
    MEM32(ebx + 4) = edi;
    { uint32_t _icall_esp = g_esp;
    { uint32_t _icall_target = MEM32(0x225B2C); PUSH32(esp, 0x00224F79u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00224F79: ;
    eax = edi;
    POP32(esp, edi);
    POP32(esp, ebx);
    esp = ebp;
    POP32(esp, ebp); /* leave */
    esp += 4; return; /* ret */

}

/**
 * sub_00224F7F
 * Original: 0x00224F7F - 0x00224FC3 (68 bytes, 27 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00224F7F(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_00224F7F: ;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, ebx);
    PUSH32(esp, ebp);
    PUSH32(esp, esi);
    esi = edx;
    ebp = MEM32(esi + 0x10);
    PUSH32(esp, edi);
    edi = ecx;
    { uint32_t _icall_target = MEM32(0x225B30); PUSH32(esp, 0x00224F90u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00224F90: ;
    edx = ebp;
    ecx = edi;
    SET_LO8(ebx, LO8(eax));
    PUSH32(esp, 0x00224F9Bu); sub_0022445D(); /* call 0x0022445D */

loc_00224F9B: ;
    edx = ebp;
    ecx = edi;
    PUSH32(esp, 0x00224FA4u); sub_00222E49(); /* call 0x00222E49 */

loc_00224FA4: ;
    eax = edi + 0x434;
    ecx = MEM32(eax);
    MEM32(esi + 0x14) = ecx;
    SET_LO8(ecx, LO8(ebx));
    MEM32(eax) = esi;
    { uint32_t _icall_esp = g_esp;
    { uint32_t _icall_target = MEM32(0x225B2C); PUSH32(esp, 0x00224FB9u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00224FB9: ;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebp);
    eax = 0x40000000;
    POP32(esp, ebx);
    esp += 4; return; /* ret */

}

/**
 * sub_00224FC3
 * Original: 0x00224FC3 - 0x0022504C (137 bytes, 52 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00224FC3(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_00224FC3: ;
    PUSH32(esp, ebx);
    PUSH32(esp, ebp);
    ebp = edx;
    PUSH32(esp, esi);
    esi = MEM32(ebp + 0x10);
    SET_LO8(eax, MEM8(esi + 0x25));
    ebx = ZX8(MEM8(esi + 0x26));
    ecx = ZX8(LO8(eax));
    ebx = ebx - ecx;
    ecx = ZX8(MEM8(esi + 0x24));
    ebx = ebx + ecx;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00225025; /* je: equal / zero */

loc_00224FE1: ;
    PUSH32(esp, edi);

loc_00224FE2: ;
    ecx = ZX8(MEM8(esi + 0x24));
    eax = ebx;
    edx = 0; /* xor self */
    { uint64_t _dividend = ((uint64_t)edx << 32) | eax;
      eax = (uint32_t)(_dividend / (uint32_t)ecx);
      edx = (uint32_t)(_dividend % (uint32_t)ecx); }
    MEM8(esi + 0x25) = MEM8(esi + 0x25) - 1;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 1);
    ebx = edx;
    edi = ebx;
    edi = edi << 6;
    edi = edi + MEM32(esi + 0x2C);
    ebx++;
    PUSH32(esp, MEM32(edi + 4));
    { uint32_t _icall_target = MEM32(0x225B94); PUSH32(esp, 0x00225005u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00225005: ;
    eax = MEM32(edi + 0xC);
    ecx = MEM32(edi + 4);
    ecx = ecx ^ eax;
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(0xFFFFF000u) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, 0xFFFFF000u (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0022501E; /* je: equal / zero */

loc_00225015: ;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 1);
    PUSH32(esp, eax);
    { uint32_t _icall_target = MEM32(0x225B94); PUSH32(esp, 0x0022501Eu); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_0022501E: ;
    _fa = (uint32_t)(MEM8(esi + 0x25)) & 0xFFu; _fb = (uint32_t)(0) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(esi + 0x25), 0 (8-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_00224FE2; /* jne: not equal / not zero */

loc_00225024: ;
    POP32(esp, edi);

loc_00225025: ;
    eax = ZX8(MEM8(esi + 0x24));
    MEM8(esi + 0x25) = MEM8(esi + 0x25) - 1;
    eax = eax << 6;
    esi = esi - eax;
    eax = MEM32(0x2878A8);
    MEM32(esi) = eax;
    MEM32(0x2878A8) = esi;
    MEM32(ebp + 4) = MEM32(ebp + 4) & 0;
    PUSH32(esp, ebp);
    PUSH32(esp, 0x00225048u); sub_002231A4(); /* call 0x002231A4 */

loc_00225048: ;
    POP32(esp, esi);
    POP32(esp, ebp);
    POP32(esp, ebx);
    esp += 4; return; /* ret */

}

/**
 * sub_0022504C
 * Original: 0x0022504C - 0x002251B3 (359 bytes, 130 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0022504C(void)
{
    uint32_t ebp;
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_0022504C: ;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, ebp);
    ebp = esp;
    g_ebp = ebp; /* publish frame for frameless callees */
    esp = esp - 0x24;
    MEM32(ebp + -20) = MEM32(ebp + -20) & 0;
    PUSH32(esp, esi);
    esi = edx;
    PUSH32(esp, edi);
    edi = MEM32(esi + 0x10);
    MEM32(ebp + -16) = esi;
    MEM32(ebp + -36) = ecx;
    MEM32(ebp + -32) = edi;
    { uint32_t _icall_target = MEM32(0x225B30); PUSH32(esp, 0x0022506Cu); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_0022506C: ;
    SET_LO8(ecx, MEM8(edi + 0x24));
    _fa = (uint32_t)(LO8(ecx)) & 0xFFu; _fb = (uint32_t)(MEM8(edi + 0x25)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp LO8(ecx), MEM8(edi + 0x25) (8-bit) */
    MEM8(ebp + -1) = LO8(eax);
    if (CMP_NE(_fa, _fb)) goto loc_00225083; /* jne: not equal / not zero */

loc_00225077: ;
    MEM32(ebp + -20) = 0xC0000D00u;
    goto loc_00225198;

loc_00225083: ;
    eax = ZX8(MEM8(edi + 0x26));
    PUSH32(esp, ebx);
    ebx = eax;
    ebx = ebx << 6;
    ebx = ebx + MEM32(edi + 0x2C);
    eax++;
    edx = ((int32_t)eax < 0) ? 0xFFFFFFFF : 0; /* cdq */
    ecx = ZX8(LO8(ecx));
    { int64_t _dividend = ((int64_t)(int32_t)edx << 32) | eax;
      eax = (uint32_t)((int32_t)(_dividend / (int32_t)ecx));
      edx = (uint32_t)((int32_t)(_dividend % (int32_t)ecx)); }
    esi = MEM32(esi + 0x18);
    MEM32(ebp + -12) = MEM32(ebp + -12) & 0;
    MEM32(ebp + -28) = esi;
    MEM8(edi + 0x26) = LO8(edx);
    eax = MEM32(esi + 0x18);
    MEM32(ebx + 0x24) = eax;
    eax = MEM32(esi + 0x1C);
    MEM32(ebx + 0x28) = eax;
    eax = MEM32(ebp + -16);
    MEM32(ebx + 0x20) = edi;
    eax = ZX8(MEM8(eax + 0x14));
    eax = eax << 0x15;
    eax = eax ^ MEM32(ebx);
    eax = eax & 0xE00000;
    MEM32(ebx) = MEM32(ebx) ^ eax;
    ecx = MEM32(esi);
    eax = MEM32(ebx);
    ecx--;
    ecx = ecx << 0x18;
    ecx = ecx ^ eax;
    ecx = ecx & 0x7000000;
    ecx = ecx ^ eax;
    MEM32(ebx) = ecx;
    eax = MEM32(esi + 4);
    eax = eax & 0xFFF;
    _fa = (uint32_t)(MEM32(esi)) & 0xFFFFFFFFu; _fb = (uint32_t)(0) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(esi), 0 (32-bit) */
    MEM32(ebp + -24) = eax;
    if (CMP_BE(_fa, _fb)) goto loc_00225115; /* jbe: below or equal (unsigned <=) */

loc_002250EA: ;
    ecx = esi + 8;
    MEM32(ebp + -8) = ecx;
    ecx = ebx + 0x10;

loc_002250F3: ;
    edx = eax;
    SET_LO16(edx, LO16(edx) | 0xE000);
    MEM16(ecx) = LO16(edx);
    edx = MEM32(ebp + -8);
    edx = ZX16(MEM16(edx));
    MEM32(ebp + -8) = MEM32(ebp + -8) + 2;
    eax = eax + edx;
    MEM32(ebp + -12) = MEM32(ebp + -12) + 1;
    edx = MEM32(ebp + -12);
    ecx++;
    ecx++;
    _fa = (uint32_t)(edx) & 0xFFFFFFFFu; _fb = (uint32_t)(MEM32(esi)) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edx, MEM32(esi) (32-bit) */
    if (CMP_B(_fa, _fb)) goto loc_002250F3; /* jb: below (unsigned <) */

loc_00225115: ;
    eax = eax - MEM32(ebp + -24);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 0);
    PUSH32(esp, eax);
    PUSH32(esp, MEM32(esi + 4));
    MEM32(ebp + -24) = eax;
    { uint32_t _icall_target = MEM32(0x225B8C); PUSH32(esp, 0x00225127u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00225127: ;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, MEM32(esi + 4));
    { uint32_t _icall_target = MEM32(0x225B88); PUSH32(esp, 0x00225130u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00225130: ;
    ecx = MEM32(ebp + -24);
    MEM32(ebx + 4) = eax;
    eax = MEM32(esi + 4);
    eax = eax + ecx + -1;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, eax);
    { uint32_t _icall_target = MEM32(0x225B88); PUSH32(esp, 0x00225144u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00225144: ;
    MEM32(ebx + 0xC) = eax;
    _fa = (uint32_t)(MEM8(edi + 0x10)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(edi + 0x10), 1 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0022515D; /* je: equal / zero */

loc_0022514D: ;
    esi = ebx + 0x10;
    edi = ebx + 0x30;
    MEM32(edi) = MEM32(esi); esi += 4; edi += 4; /* movsd */
    MEM32(edi) = MEM32(esi); esi += 4; edi += 4; /* movsd */
    MEM32(edi) = MEM32(esi); esi += 4; edi += 4; /* movsd */
    MEM32(edi) = MEM32(esi); esi += 4; edi += 4; /* movsd */
    esi = MEM32(ebp + -28);
    edi = MEM32(ebp + -32);

loc_0022515D: ;
    _fa = (uint32_t)(MEM8(edi + 0x10)) & 0xFFu; _fb = (uint32_t)(2) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(edi + 0x10), 2 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00225183; /* je: equal / zero */

loc_00225163: ;
    ecx = MEM32(ebp + -36);
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x0022516Bu); sub_0022466C(); /* call 0x0022466C */

loc_0022516B: ;
    ecx = MEM32(edi + 0x28);
    eax++;
    edx = ecx;
    edx = edx - eax;
    _fa = (uint32_t)(edx) & 0xFFFFFFFFu; _fb = (uint32_t)(edx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test edx, edx (32-bit) */
    if (CMP_LE(_fas & _fbs, 0)) goto loc_00225179; /* jle: less or equal (signed <=) */

loc_00225177: ;
    eax = ecx;

loc_00225179: ;
    MEM16(ebx) = LO16(eax);
    ecx = MEM32(esi);
    ecx = ecx + eax;
    MEM32(edi + 0x28) = ecx;

loc_00225183: ;
    MEM8(edi + 0x25) = MEM8(edi + 0x25) + 1;
    SET_LO8(eax, MEM8(edi + 0x25));
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(MEM8(edi + 0x24)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp LO8(eax), MEM8(edi + 0x24) (8-bit) */
    esi = MEM32(ebp + -16);
    if (CMP_EQ(_fa, _fb)) goto loc_00225197; /* je: equal / zero */

loc_00225191: ;
    eax = MEM32(ebx + 8);
    MEM32(edi + 4) = eax;

loc_00225197: ;
    POP32(esp, ebx);

loc_00225198: ;
    SET_LO8(ecx, MEM8(ebp + -1));
    { uint32_t _icall_esp = g_esp;
    { uint32_t _icall_target = MEM32(0x225B2C); PUSH32(esp, 0x002251A1u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_002251A1: ;
    edi = MEM32(ebp + -20);
    PUSH32(esp, esi);
    MEM32(esi + 4) = edi;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x002251ADu); sub_002231A4(); /* call 0x002231A4 */

loc_002251AD: ;
    eax = edi;
    POP32(esp, edi);
    POP32(esp, esi);
    esp = ebp;
    POP32(esp, ebp); /* leave */
    esp += 4; return; /* ret */

}

/**
 * sub_002251B3
 * Original: 0x002251B3 - 0x002252D2 (287 bytes, 98 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_002251B3(void)
{
    uint32_t ebp;
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_002251B3: ;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, ebp);
    ebp = esp;
    g_ebp = ebp; /* publish frame for frameless callees */
    esp = esp - 0x18;
    MEM32(ebp + -16) = MEM32(ebp + -16) & 0;
    PUSH32(esp, ebx);
    ebx = MEM32(0x225B30);
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    edi = edx;
    esi = MEM32(edi + 0x10);
    MEM32(ebp + -12) = edi;
    MEM32(ebp + -8) = ecx;
    { uint32_t _icall_target = ebx; PUSH32(esp, 0x002251D3u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_002251D3: ;
    _fa = (uint32_t)(MEM8(esi + 0x10)) & 0xFFu; _fb = (uint32_t)(2) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(esi + 0x10), 2 (8-bit) */
    MEM8(ebp + -1) = LO8(eax);
    if (TEST_Z(_fa, _fb)) goto loc_002251E6; /* je: equal / zero */

loc_002251DC: ;
    esi = 0xC0000E00u;
    goto loc_002252B2;

loc_002251E6: ;
    ecx = MEM32(ebp + -8);
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x002251EEu); sub_0022466C(); /* call 0x0022466C */

loc_002251EE: ;
    SET_LO8(edx, MEM8(esi + 0x10));
    _fa = (uint32_t)(LO8(edx)) & 0xFFu; _fb = (uint32_t)(4) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(edx), 4 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00225230; /* je: equal / zero */

loc_002251F6: ;
    SET_LO8(edx, LO8(edx) & 0xFB);
    _fa = (uint32_t)(MEM32(esi + 0x1C)) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(esi + 0x1C), eax (32-bit) */
    MEM8(esi + 0x10) = LO8(edx);
    if (CMP_NE(_fa, _fb)) goto loc_00225228; /* jne: not equal / not zero */

loc_00225201: ;
    SET_LO8(ecx, MEM8(ebp + -1));
    { uint32_t _icall_esp = g_esp;
    { uint32_t _icall_target = MEM32(0x225B2C); PUSH32(esp, 0x0022520Au); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_0022520A: ;
    MEM32(ebp + -20) = MEM32(ebp + -20) | 0xFFFFFFFFu;
    eax = ebp + -24;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, eax);
    PUSH32(esp, 0);
    PUSH32(esp, 0);
    MEM32(ebp + -24) = 0xFFFFD8F0u;
    { uint32_t _icall_target = MEM32(0x225AFC); PUSH32(esp, 0x00225223u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00225223: ;
    { uint32_t _icall_esp = g_esp;
    { uint32_t _icall_target = ebx; PUSH32(esp, 0x00225225u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00225225: ;
    MEM8(ebp + -1) = LO8(eax);

loc_00225228: ;
    ecx = MEM32(ebp + -8);
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00225230u); sub_0022466C(); /* call 0x0022466C */

loc_00225230: ;
    _fa = (uint32_t)(MEM8(esi + 0x10)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(esi + 0x10), 1 (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00225245; /* je: equal / zero */

loc_00225236: ;
    SET_LO8(ecx, MEM8(esi + 0x24));
    _fa = (uint32_t)(LO8(ecx)) & 0xFFu; _fb = (uint32_t)(MEM8(esi + 0x25)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp LO8(ecx), MEM8(esi + 0x25) (8-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_00225245; /* je: equal / zero */

loc_0022523E: ;
    esi = 0xC0001000u;
    goto loc_002252B2;

loc_00225245: ;
    _fa = (uint32_t)(MEM8(edi + 0x18)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(edi + 0x18), 1 (8-bit) */
    ecx = eax + 1;
    if (TEST_NZ(_fa, _fb)) goto loc_00225260; /* jne: not equal / not zero */

loc_0022524E: ;
    edx = MEM32(edi + 0x14);
    eax = edx;
    eax = eax - ecx;
    if (((int32_t)eax < 0)) goto loc_002252CB; /* js: sign (negative) */

loc_00225257: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0x400) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0x400 (32-bit) */
    if (CMP_G(_fas, _fbs)) goto loc_002252CB; /* jg: greater (signed >) */

loc_0022525E: ;
    ecx = edx;

loc_00225260: ;
    SET_LO8(edx, MEM8(esi + 0x24));
    SET_LO8(eax, LO8(edx));
    SET_LO8(eax, LO8(eax) - MEM8(esi + 0x25));
    edi = ZX8(LO8(edx));
    SET_LO8(eax, LO8(eax) + MEM8(esi + 0x26));
    eax = ZX8(LO8(eax));
    edx = ((int32_t)eax < 0) ? 0xFFFFFFFF : 0; /* cdq */
    { int64_t _dividend = ((int64_t)(int32_t)edx << 32) | eax;
      eax = (uint32_t)((int32_t)(_dividend / (int32_t)edi));
      edx = (uint32_t)((int32_t)(_dividend % (int32_t)edi)); }
    edi = MEM32(esi + 0x2C);

loc_00225277: ;
    edx = ZX8(LO8(edx));
    eax = edx;
    eax = eax << 6;
    MEM16(edi + eax) = LO16(ecx);
    edi = MEM32(esi + 0x2C);
    eax = ZX8(MEM8(edi + eax + 3));
    ebx = ZX8(MEM8(esi + 0x24));
    eax = eax & 7;
    ecx = ecx + eax + 1;
    eax = edx + 1;
    edx = ((int32_t)eax < 0) ? 0xFFFFFFFF : 0; /* cdq */
    { int64_t _dividend = ((int64_t)(int32_t)edx << 32) | eax;
      eax = (uint32_t)((int32_t)(_dividend / (int32_t)ebx));
      edx = (uint32_t)((int32_t)(_dividend % (int32_t)ebx)); }
    _fa = (uint32_t)(LO8(edx)) & 0xFFu; _fb = (uint32_t)(MEM8(esi + 0x26)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp LO8(edx), MEM8(esi + 0x26) (8-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_00225277; /* jne: not equal / not zero */

loc_002252A1: ;
    MEM8(esi + 1) = MEM8(esi + 1) & 0xBF;
    MEM8(esi + 0x10) = MEM8(esi + 0x10) | 2;
    edi = MEM32(ebp + -12);
    MEM32(esi + 0x28) = ecx;
    esi = MEM32(ebp + -16);

loc_002252B2: ;
    SET_LO8(ecx, MEM8(ebp + -1));
    { uint32_t _icall_esp = g_esp;
    { uint32_t _icall_target = MEM32(0x225B2C); PUSH32(esp, 0x002252BBu); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_002252BB: ;
    PUSH32(esp, edi);
    MEM32(edi + 4) = esi;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x002252C4u); sub_002231A4(); /* call 0x002231A4 */

loc_002252C4: ;
    POP32(esp, edi);
    eax = esi;
    POP32(esp, esi);
    POP32(esp, ebx);
    esp = ebp;
    POP32(esp, ebp); /* leave */
    esp += 4; return; /* ret */

loc_002252CB: ;
    esi = 0xC0000B00u;
    goto loc_002252B2;

}

/**
 * sub_002252D2
 * Original: 0x002252D2 - 0x0022532C (90 bytes, 37 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_002252D2(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_002252D2: ;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, ecx);
    PUSH32(esp, ebx);
    PUSH32(esp, ebp);
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    edi = edx;
    esi = MEM32(edi + 0x10);
    ebx = ecx;
    ebp = 0; /* xor self */
    { uint32_t _icall_target = MEM32(0x225B30); PUSH32(esp, 0x002252E6u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_002252E6: ;
    _fa = (uint32_t)(MEM8(esi + 0x10)) & 0xFFu; _fb = (uint32_t)(2) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(esi + 0x10), 2 (8-bit) */
    MEM8(esp + 0x13) = LO8(eax);
    if (TEST_Z(_fa, _fb)) goto loc_0022530C; /* je: equal / zero */

loc_002252F0: ;
    MEM8(esi + 1) = MEM8(esi + 1) | 0x40;
    ecx = ebx;
    PUSH32(esp, 0x002252FBu); sub_0022466C(); /* call 0x0022466C */

loc_002252FB: ;
    eax++;
    eax++;
    MEM32(esi + 0x1C) = eax;
    SET_LO8(eax, MEM8(esi + 0x10));
    SET_LO8(eax, LO8(eax) & 0xFD);
    SET_LO8(eax, LO8(eax) | 4);
    MEM8(esi + 0x10) = LO8(eax);
    goto loc_00225311;

loc_0022530C: ;
    ebp = 0xC0000F00u;

loc_00225311: ;
    SET_LO8(ecx, MEM8(esp + 0x13));
    { uint32_t _icall_esp = g_esp;
    { uint32_t _icall_target = MEM32(0x225B2C); PUSH32(esp, 0x0022531Bu); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_0022531B: ;
    PUSH32(esp, edi);
    MEM32(edi + 4) = ebp;
    PUSH32(esp, 0x00225324u); sub_002231A4(); /* call 0x002231A4 */

loc_00225324: ;
    POP32(esp, edi);
    POP32(esp, esi);
    eax = ebp;
    POP32(esp, ebp);
    POP32(esp, ebx);
    POP32(esp, ecx);
    esp += 4; return; /* ret */

}

/**
 * sub_0022532C
 * Original: 0x0022532C - 0x0022541C (240 bytes, 97 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0022532C(void)
{
    uint32_t ebp;
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_0022532C: ;
    PUSH32(esp, ebp);
    ebp = esp;
    g_ebp = ebp; /* publish frame for frameless callees */
    esp = esp - 0x2C;
    PUSH32(esp, ebx);
    ebx = edx;
    eax = MEM32(ebx);
    PUSH32(esp, esi);
    edx = MEM32(ebx + 0x20);
    MEM32(ebx + 8) = MEM32(ebx + 8) & 0;
    esi = eax;
    esi = esi >> 0x1C;
    MEM32(ebp + -44) = esi;
    eax = eax >> 0x18;
    eax = eax & 7;
    PUSH32(esp, edi);
    eax++;
    MEM32(ebp + -40) = eax;
    eax = MEM32(ebx + 0x28);
    esi = ebx + 0x10;
    MEM32(ebp + -8) = esi;
    edi = ebp + -36;
    MEM32(edi) = MEM32(esi); esi += 4; edi += 4; /* movsd */
    MEM32(edi) = MEM32(esi); esi += 4; edi += 4; /* movsd */
    MEM32(edi) = MEM32(esi); esi += 4; edi += 4; /* movsd */
    MEM32(ebp + -16) = eax;
    eax = MEM32(ebx + 0x24);
    MEM32(edi) = MEM32(esi); esi += 4; edi += 4; /* movsd */
    edi = MEM32(edx + 0x2C);
    MEM32(ebp + -20) = eax;
    eax = ZX8(MEM8(ebx + 0x2D));
    esi = ebx;
    esi = esi - MEM32(0x287880);
    eax = eax << 6;
    MEM32(eax + edi + 8) = esi;
    _fa = (uint32_t)(MEM8(edx + 0x10)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test MEM8(edx + 0x10), 1 (8-bit) */
    MEM32(ebp + -4) = edx;
    MEM32(ebp + -12) = esi;
    if (TEST_Z(_fa, _fb)) goto loc_002253D3; /* je: equal / zero */

loc_0022538D: ;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00225392u); sub_0022466C(); /* call 0x0022466C */

loc_00225392: ;
    ecx = MEM32(ebp + -4);
    esi = eax;
    eax = MEM32(ecx + 0x28);
    esi++;
    edx = eax;
    edx = edx - esi;
    if (((int32_t)edx < 0)) goto loc_002253A3; /* js: sign (negative) */

loc_002253A1: ;
    esi = eax;

loc_002253A3: ;
    edi = MEM32(ebp + -8);
    MEM16(ebx) = LO16(esi);
    eax = 0; /* xor self */
    SET_LO8(eax, MEM8(ebx + 3));
    eax = eax & 7;
    eax = eax + esi + 1;
    MEM32(ecx + 0x28) = eax;
    esi = ebx + 0x30;
    MEM32(edi) = MEM32(esi); esi += 4; edi += 4; /* movsd */
    MEM32(edi) = MEM32(esi); esi += 4; edi += 4; /* movsd */
    MEM32(edi) = MEM32(esi); esi += 4; edi += 4; /* movsd */
    MEM32(edi) = MEM32(esi); esi += 4; edi += 4; /* movsd */
    eax = ZX8(MEM8(ecx + 0x26));
    esi = ZX8(MEM8(ecx + 0x24));
    eax++;
    edx = ((int32_t)eax < 0) ? 0xFFFFFFFF : 0; /* cdq */
    { int64_t _dividend = ((int64_t)(int32_t)edx << 32) | eax;
      eax = (uint32_t)((int32_t)(_dividend / (int32_t)esi));
      edx = (uint32_t)((int32_t)(_dividend % (int32_t)esi)); }
    esi = MEM32(ebp + -12);
    MEM8(ecx + 0x26) = LO8(edx);
    goto loc_0022540A;

loc_002253D3: ;
    edi = MEM32(0x225B94);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 1);
    PUSH32(esp, MEM32(ebx + 4));
    { uint32_t _icall_target = edi; PUSH32(esp, 0x002253E0u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_002253E0: ;
    eax = MEM32(ebx + 0xC);
    ecx = MEM32(ebx + 4);
    ecx = ecx ^ eax;
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(0xFFFFF000u) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, 0xFFFFF000u (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_002253F5; /* je: equal / zero */

loc_002253F0: ;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 1);
    PUSH32(esp, eax);
    { uint32_t _icall_target = edi; PUSH32(esp, 0x002253F5u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_002253F5: ;
    ecx = MEM32(ebp + -4);
    SET_LO8(eax, MEM8(ecx + 0x25));
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(MEM8(ecx + 0x24)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp LO8(eax), MEM8(ecx + 0x24) (8-bit) */
    SET_LO8(edx, (CMP_EQ(_fa, _fb)) ? 1 : 0); /* sete */
    SET_LO8(eax, LO8(eax) - 1);
    _fa = (uint32_t)(LO8(edx)) & 0xFFu; _fb = (uint32_t)(LO8(edx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(edx), LO8(edx) (8-bit) */
    MEM8(ecx + 0x25) = LO8(eax);
    if (TEST_Z(_fa, _fb)) goto loc_0022540D; /* je: equal / zero */

loc_0022540A: ;
    MEM32(ecx + 4) = esi;

loc_0022540D: ;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, MEM32(ebp + -16));
    eax = ebp + -44;
    PUSH32(esp, eax);
    { uint32_t _icall_target = MEM32(ebp + -20); PUSH32(esp, 0x00225417u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_00225417: ;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebx);
    esp = ebp;
    POP32(esp, ebp); /* leave */
    esp += 4; return; /* ret */

}

/**
 * sub_0022541C
 * Original: 0x0022541C - 0x0022543C (32 bytes, 9 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0022541C(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_0022541C: ;
    eax = MEM32(0x28788C);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_0022542E; /* je: equal / zero */

loc_00225425: ;
    ecx = MEM32(eax + 0x14);
    MEM32(0x28788C) = ecx;

loc_0022542E: ;
    SET_LO8(ecx, MEM8(esp + 4));
    MEM8(eax + 2) = MEM8(eax + 2) & 0xFE;
    MEM8(eax + 0x1F) = LO8(ecx);
    esp += 8; return; /* ret 4 */

}

/**
 * sub_0022543C
 * Original: 0x0022543C - 0x0022545B (31 bytes, 9 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0022543C(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_0022543C: ;
    SET_LO16(eax, MEM16(esp + 4));
    _fa = (uint32_t)(MEM16(0x2878A2)) & 0xFFFFu; _fb = (uint32_t)(LO16(eax)) & 0xFFFFu;
    _fas = (int32_t)(int16_t)(_fa); _fbs = (int32_t)(int16_t)(_fb); /* cmp MEM16(0x2878A2), LO16(eax) (16-bit) */
    if (CMP_AE(_fa, _fb)) goto loc_0022544E; /* jae: above or equal (unsigned >=) */

loc_0022544A: ;
    eax = 0; /* xor self */
    goto loc_00225458;

loc_0022544E: ;
    MEM16(0x2878A2) = MEM16(0x2878A2) - LO16(eax);
    eax = 0; /* xor self */
    eax++;

loc_00225458: ;
    esp += 8; return; /* ret 4 */

}

/**
 * sub_0022545B
 * Original: 0x0022545B - 0x0022547A (31 bytes, 9 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0022545B(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_0022545B: ;
    SET_LO16(eax, MEM16(esp + 4));
    _fa = (uint32_t)(MEM16(0x2878A6)) & 0xFFFFu; _fb = (uint32_t)(LO16(eax)) & 0xFFFFu;
    _fas = (int32_t)(int16_t)(_fa); _fbs = (int32_t)(int16_t)(_fb); /* cmp MEM16(0x2878A6), LO16(eax) (16-bit) */
    if (CMP_AE(_fa, _fb)) goto loc_0022546D; /* jae: above or equal (unsigned >=) */

loc_00225469: ;
    eax = 0; /* xor self */
    goto loc_00225477;

loc_0022546D: ;
    MEM16(0x2878A6) = MEM16(0x2878A6) - LO16(eax);
    eax = 0; /* xor self */
    eax++;

loc_00225477: ;
    esp += 8; return; /* ret 4 */

}

/**
 * sub_0022547A
 * Original: 0x0022547A - 0x002254AC (50 bytes, 22 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0022547A(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_0022547A: ;
    PUSH32(esp, edi);
    edi = edx;
    edx = 0; /* xor self */
    SET_LO16(edx, MEM16(edi + 2));
    eax = 0; /* xor self */
    edx = edx & 0x7FF;
    _fa = (uint32_t)(MEM32(ecx + 0x14)) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(ecx + 0x14), eax (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_002254A1; /* je: equal / zero */

loc_00225490: ;
    eax = MEM32(ecx + 0x14);
    PUSH32(esp, esi);
    esi = ZX16(LO16(edx));
    edx = 0; /* xor self */
    { uint64_t _dividend = ((uint64_t)edx << 32) | eax;
      eax = (uint32_t)(_dividend / (uint32_t)esi);
      edx = (uint32_t)(_dividend % (uint32_t)esi); }
    POP32(esp, esi);
    _fa = (uint32_t)(edx) & 0xFFFFFFFFu; _fb = (uint32_t)(edx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test edx, edx (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_002254A1; /* je: equal / zero */

loc_002254A0: ;
    eax++;

loc_002254A1: ;
    _fa = (uint32_t)(MEM8(edi + 0x11)) & 0xFFu; _fb = (uint32_t)(0) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(edi + 0x11), 0 (8-bit) */
    POP32(esp, edi);
    if (CMP_NE(_fa, _fb)) goto loc_002254AB; /* jne: not equal / not zero */

loc_002254A8: ;
    eax = eax + 3;

loc_002254AB: ;
    esp += 4; return; /* ret */

}

/**
 * sub_002254AC
 * Original: 0x002254AC - 0x002254E6 (58 bytes, 25 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_002254AC(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_002254AC: ;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, ebx);
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    esi = ecx;
    PUSH32(esp, MEM32(esi));
    edi = edx;
    { uint32_t _icall_target = MEM32(0x225B88); PUSH32(esp, 0x002254BBu); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_002254BB: ;
    ecx = MEM32(esi);
    ecx = ecx & 0xFFF;
    edx = 0x1000;
    edx = edx - ecx;
    ecx = MEM32(esp + 0x10);
    MEM32(ecx) = edx;
    ebx = MEM32(edi);
    _fa = (uint32_t)(edx) & 0xFFFFFFFFu; _fb = (uint32_t)(ebx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edx, ebx (32-bit) */
    if (CMP_BE(_fa, _fb)) goto loc_002254D8; /* jbe: below or equal (unsigned <=) */

loc_002254D6: ;
    MEM32(ecx) = ebx;

loc_002254D8: ;
    edx = MEM32(ecx);
    MEM32(edi) = MEM32(edi) - edx;
    ecx = MEM32(ecx);
    MEM32(esi) = MEM32(esi) + ecx;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebx);
    esp += 8; return; /* ret 4 */

}

/**
 * sub_002254E6
 * Original: 0x002254E6 - 0x002257E4 (766 bytes, 247 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_002254E6(void)
{
    uint32_t ebp;
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_002254E6: ;
    PUSH32(esp, ebp);
    ebp = esp;
    g_ebp = ebp; /* publish frame for frameless callees */
    esp = esp - 0x28;
    eax = 0; /* xor self */
    PUSH32(esp, ebx);
    ebx = edx;
    SET_LO16(eax, MEM16(ebx + 2));
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    edi = MEM32(ebp + 8);
    MEM32(ebp + -32) = ecx;
    SET_LO8(ecx, MEM8(ecx + 0x45C));
    MEM8(ebp + -24) = LO8(ecx);
    eax = eax & 0x7FF;
    MEM32(ebp + -40) = eax;
    eax = MEM32(edi + 0x14);
    MEM32(ebp + -16) = eax;
    eax = 0; /* xor self */
    MEM8(ebx + 0x26) = MEM8(ebx + 0x26) - 1;
    MEM8(ebx + 0x27) = MEM8(ebx + 0x27) + 1;
    SET_LO16(ecx, MEM16(edi + 0x22));
    SET_LO16(ecx, LO16(ecx) & 0xFFFD);
    SET_LO16(ecx, LO16(ecx) | 4);
    MEM16(edi + 0x22) = LO16(ecx);
    esi = MEM32(ebx + 4);
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp esi, eax (32-bit) */
    MEM32(ebp + -20) = eax;
    MEM8(ebp + 0xB) = LO8(eax);
    MEM32(ebp + -28) = eax;
    MEM32(ebp + -12) = eax;
    MEM32(ebp + -8) = eax;
    if (CMP_EQ(_fa, _fb)) goto loc_0022554C; /* je: equal / zero */

loc_00225543: ;
    eax = MEM32(0x287880);
    esi = esi + eax;
    goto loc_00225565;

loc_0022554C: ;
    PUSH32(esp, MEM32(ebp + -24));
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00225554u); sub_0022541C(); /* call 0x0022541C */

loc_00225554: ;
    esi = eax;
    eax = MEM32(esi + 0x10);
    eax = eax ^ MEM32(ebx + 8);
    eax = eax & 0xF;
    eax = eax ^ MEM32(esi + 0x10);
    MEM32(ebx + 8) = eax;

loc_00225565: ;
    _fa = (uint32_t)(MEM8(ebx + 0x11)) & 0xFFu; _fb = (uint32_t)(0) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(ebx + 0x11), 0 (8-bit) */
    MEM32(ebp + -4) = esi;
    if (CMP_NE(_fa, _fb)) goto loc_002255D4; /* jne: not equal / not zero */

loc_0022556E: ;
    eax = 0; /* xor self */
    SET_LO8(eax, 0xFE);
    SET_LO8(eax, LO8(eax) - MEM8(ebp + -24));
    PUSH32(esp, eax);
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x0022557Bu); sub_0022541C(); /* call 0x0022541C */

loc_0022557B: ;
    ecx = MEM32(edi + 0x28);
    PUSH32(esp, MEM32(ebp + -24));
    MEM32(eax) = ecx;
    ecx = MEM32(edi + 0x2C);
    MEM32(ebp + -36) = eax;
    MEM32(eax + 4) = ecx;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00225591u); sub_0022541C(); /* call 0x0022541C */

loc_00225591: ;
    esi = eax;
    eax = MEM32(ebp + -4);
    ecx = MEM32(eax);
    ecx = ecx & 0x3FFFF;
    ecx = ecx | 0xE2E00000u;
    MEM32(eax) = ecx;
    ecx = MEM32(ebp + -36);
    edx = MEM32(ecx + 0x10);
    MEM32(eax + 4) = edx;
    edx = MEM32(esi + 0x10);
    MEM32(eax + 8) = edx;
    ecx = MEM32(ecx + 0x10);
    ecx = ecx + 7;
    MEM8(ebp + 0xB) = 2;
    MEM32(eax + 0xC) = ecx;
    MEM32(eax + 0x14) = ebx;
    MEM8(eax + 0x1C) = 0;
    MEM8(eax + 0x1E) = 1;
    MEM8(eax + 0x1D) = 0;
    MEM32(eax + 0x18) = edi;

loc_002255D4: ;
    _fa = (uint32_t)(MEM32(ebp + -16)) & 0xFFFFFFFFu; _fb = (uint32_t)(0) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(ebp + -16), 0 (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_002255F0; /* je: equal / zero */

loc_002255DA: ;
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, 0);
    PUSH32(esp, MEM32(ebp + -16));
    PUSH32(esp, MEM32(edi + 0x18));
    { uint32_t _icall_target = MEM32(0x225B8C); PUSH32(esp, 0x002255E8u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_002255E8: ;
    eax = MEM32(edi + 0x18);
    MEM32(ebp + -36) = eax;
    goto loc_002255F4;

loc_002255F0: ;
    MEM8(edi + 0x1C) = 1;

loc_002255F4: ;
    _fa = (uint32_t)(MEM32(ebp + -16)) & 0xFFFFFFFFu; _fb = (uint32_t)(0) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(ebp + -16), 0 (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_0022570F; /* je: equal / zero */

loc_002255FE: ;
    eax = ebp + -20;
    PUSH32(esp, eax);
    edx = ebp + -16;
    ecx = ebp + -36;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x0022560Du); sub_002254AC(); /* call 0x002254AC */

loc_0022560D: ;
    MEM32(ebp + -4) = eax;

loc_00225610: ;
    edx = MEM32(ebp + -20);
    eax = MEM32(ebp + -12);
    ecx = MEM32(ebp + -40);
    eax = eax + edx;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, ecx (32-bit) */
    if (CMP_AE(_fa, _fb)) goto loc_00225631; /* jae: above or equal (unsigned >=) */

loc_0022561F: ;
    _fa = (uint32_t)(edx) & 0xFFFFFFFFu; _fb = (uint32_t)(edx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test edx, edx (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_002256E9; /* je: equal / zero */

loc_00225627: ;
    _fa = (uint32_t)(MEM32(ebp + -16)) & 0xFFFFFFFFu; _fb = (uint32_t)(0) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(ebp + -16), 0 (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_002256E9; /* jne: not equal / not zero */

loc_00225631: ;
    _fa = (uint32_t)(MEM32(ebp + -12)) & 0xFFFFFFFFu; _fb = (uint32_t)(0) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(ebp + -12), 0 (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_00225659; /* je: equal / zero */

loc_00225637: ;
    ecx = ecx - MEM32(ebp + -12);
    eax = MEM32(ebp + -28);
    _fa = (uint32_t)(edx) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edx, ecx (32-bit) */
    MEM32(esi + 4) = eax;
    if (CMP_AE(_fa, _fb)) goto loc_00225646; /* jae: above or equal (unsigned >=) */

loc_00225644: ;
    ecx = edx;

loc_00225646: ;
    SET_LO8(eax, MEM8(ebp + -12));
    MEM32(ebp + -4) = MEM32(ebp + -4) + ecx;
    SET_LO8(eax, LO8(eax) + LO8(ecx));
    edx = edx - ecx;
    MEM32(ebp + -12) = MEM32(ebp + -12) & 0;
    MEM8(esi + 0x1D) = LO8(eax);
    goto loc_00225677;

loc_00225659: ;
    _fa = (uint32_t)(edx) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edx, ecx (32-bit) */
    eax = MEM32(ebp + -4);
    MEM32(esi + 4) = eax;
    if (CMP_AE(_fa, _fb)) goto loc_0022566F; /* jae: above or equal (unsigned >=) */

loc_00225663: ;
    MEM32(ebp + -4) = MEM32(ebp + -4) + edx;
    MEM32(ebp + -20) = MEM32(ebp + -20) & 0;
    MEM8(esi + 0x1D) = LO8(edx);
    goto loc_0022567A;

loc_0022566F: ;
    MEM32(ebp + -4) = MEM32(ebp + -4) + ecx;
    MEM8(esi + 0x1D) = LO8(ecx);
    edx = edx - ecx;

loc_00225677: ;
    MEM32(ebp + -20) = edx;

loc_0022567A: ;
    eax = MEM32(ebp + -4);
    ecx = MEM32(esi);
    MEM8(ebp + 0xB) = MEM8(ebp + 0xB) ^ 1;
    eax--;
    MEM32(esi + 0xC) = eax;
    eax = ZX8(MEM8(ebp + 0xB));
    PUSH32(esp, MEM32(ebp + -24));
    ecx = ecx & 0xFFBFFFF;
    ecx = ecx | 0xE0000000u;
    eax = eax << 0x18;
    eax = eax ^ ecx;
    eax = eax & 0x3000000;
    eax = eax ^ ecx;
    MEM32(esi) = ecx;
    eax = eax | 0xE00000;
    ecx = 0; /* xor self */
    MEM32(esi) = eax;
    MEM32(esi + 0x14) = ebx;
    MEM8(esi + 0x1C) = 0;
    MEM8(esi + 0x1E) = 0;
    SET_LO8(ecx, MEM8(edi + 0x1C));
    eax = eax & 0xF3E7FFFFu;
    MEM32(esi + 0x18) = edi;
    MEM32(ebp + -8) = esi;
    ecx = ecx & 3;
    ecx = ecx << 0x13;
    ecx = ecx | eax;
    MEM32(esi) = ecx;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x002256D9u); sub_0022541C(); /* call 0x0022541C */

loc_002256D9: ;
    ecx = MEM32(ebp + -8);
    esi = eax;
    eax = MEM32(esi + 0x10);
    MEM32(ecx + 8) = eax;
    goto loc_00225610;

loc_002256E9: ;
    _fa = (uint32_t)(MEM32(ebp + -16)) & 0xFFFFFFFFu; _fb = (uint32_t)(0) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(ebp + -16), 0 (32-bit) */
    eax = MEM32(ebp + -4);
    MEM32(ebp + -28) = eax;
    MEM32(ebp + -12) = edx;
    if (CMP_NE(_fa, _fb)) goto loc_002255FE; /* jne: not equal / not zero */

loc_002256FC: ;
    _fa = (uint32_t)(MEM32(ebp + -8)) & 0xFFFFFFFFu; _fb = (uint32_t)(0) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(ebp + -8), 0 (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_0022570F; /* je: equal / zero */

loc_00225702: ;
    _fa = (uint32_t)(MEM8(edi + 0x1D)) & 0xFFu; _fb = (uint32_t)(0) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(edi + 0x1D), 0 (8-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_0022570F; /* je: equal / zero */

loc_00225708: ;
    eax = MEM32(ebp + -8);
    MEM8(eax + 2) = MEM8(eax + 2) | 4;

loc_0022570F: ;
    _fa = (uint32_t)(MEM8(ebx + 0x11)) & 0xFFu; _fb = (uint32_t)(0) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(ebx + 0x11), 0 (8-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_0022577F; /* jne: not equal / not zero */

loc_00225715: ;
    MEM8(esi + 2) = MEM8(esi + 2) & 0xFB;
    ecx = MEM32(esi);
    eax = 0; /* xor self */
    _fa = (uint32_t)(MEM8(edi + 0x1C)) & 0xFFu; _fb = (uint32_t)(2) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(edi + 0x1C), 2 (8-bit) */
    PUSH32(esp, MEM32(ebp + -24));
    SET_LO8(eax, (CMP_NE(_fa, _fb)) ? 1 : 0); /* setne */
    MEM32(ebp + -8) = esi;
    eax++;
    eax = eax << 0x13;
    eax = eax ^ ecx;
    eax = eax & 0x180000;
    eax = eax ^ ecx;
    ecx = 0; /* xor self */
    MEM32(esi) = eax;
    SET_LO8(ecx, MEM8(edi + 0x1E));
    MEM32(esi + 4) = MEM32(esi + 4) & 0;
    MEM32(esi + 0xC) = MEM32(esi + 0xC) & 0;
    eax = eax & 0x1FFFFF;
    MEM32(esi + 0x14) = ebx;
    MEM8(esi + 0x1C) = 2;
    MEM8(esi + 0x1E) = 2;
    ecx = ecx & 7;
    ecx = ecx | 0xFFFFFF18u;
    ecx = ecx << 0x15;
    ecx = ecx | eax;
    MEM32(esi) = ecx;
    MEM32(esi + 0x18) = edi;
    MEM8(esi + 0x1D) = 0;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00225772u); sub_0022541C(); /* call 0x0022541C */

loc_00225772: ;
    ecx = MEM32(ebp + -8);
    esi = eax;
    eax = MEM32(esi + 0x10);
    MEM32(ecx + 8) = eax;
    goto loc_00225797;

loc_0022577F: ;
    ecx = ZX8(MEM8(edi + 0x1E));
    eax = MEM32(ebp + -8);
    ecx = ecx << 0x15;
    ecx = ecx ^ MEM32(eax);
    MEM8(eax + 0x1C) = 2;
    ecx = ecx & 0xE00000;
    MEM32(eax) = MEM32(eax) ^ ecx;

loc_00225797: ;
    MEM8(esi + 0x1E) = 3;
    SET_LO16(eax, MEM16(edi + 0x14));
    MEM32(edi + 0x14) = MEM32(edi + 0x14) & 0;
    MEM16(edi + 0x20) = LO16(eax);
    _fa = (uint32_t)(MEM8(ebx + 0x20)) & 0xFFu; _fb = (uint32_t)(0) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp MEM8(ebx + 0x20), 0 (8-bit) */
    eax = MEM32(esi + 0x10);
    MEM32(ebx + 4) = eax;
    if (CMP_NE(_fa, _fb)) goto loc_002257B7; /* jne: not equal / not zero */

loc_002257B3: ;
    MEM8(ebx + 1) = MEM8(ebx + 1) & 0xBF;

loc_002257B7: ;
    SET_LO8(ebx, MEM8(ebx + 0x11));
    _fa = (uint32_t)(LO8(ebx)) & 0xFFu; _fb = (uint32_t)(LO8(ebx)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(ebx), LO8(ebx) (8-bit) */
    if (TEST_NZ(_fa, _fb)) goto loc_002257CC; /* jne: not equal / not zero */

loc_002257BE: ;
    eax = MEM32(ebp + -32);
    eax = MEM32(eax);
    MEM32(eax + 8) = 2;
    goto loc_002257DD;

loc_002257CC: ;
    _fa = (uint32_t)(LO8(ebx)) & 0xFFu; _fb = (uint32_t)(2) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* cmp LO8(ebx), 2 (8-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_002257DD; /* jne: not equal / not zero */

loc_002257D1: ;
    eax = MEM32(ebp + -32);
    eax = MEM32(eax);
    MEM32(eax + 8) = 4;

loc_002257DD: ;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebx);
    esp = ebp;
    POP32(esp, ebp); /* leave */
    esp += 8; return; /* ret 4 */

}

/**
 * sub_002257E4
 * Original: 0x002257E4 - 0x00225837 (83 bytes, 34 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_002257E4(void)
{
    uint32_t ebp;
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_002257E4: ;
    PUSH32(esp, ebp);
    ebp = esp;
    g_ebp = ebp; /* publish frame for frameless callees */
    PUSH32(esp, ecx);
    PUSH32(esp, esi);
    esi = edx;
    _fa = (uint32_t)(MEM32(esi + 0x28)) & 0xFFFFFFFFu; _fb = (uint32_t)(0) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(esi + 0x28), 0 (32-bit) */
    MEM32(ebp + -4) = ecx;
    if (CMP_EQ(_fa, _fb)) goto loc_00225834; /* je: equal / zero */

loc_002257F4: ;
    PUSH32(esp, ebx);

loc_002257F5: ;
    eax = MEM32(esi + 0x28);
    SET_LO16(edx, MEM16(esi + 0x24));
    ebx = ZX16(MEM16(eax + 0x20));
    ecx = ZX16(LO16(edx));
    ecx = ecx + ebx;
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(3) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp ecx, 3 (32-bit) */
    if (CMP_G(_fas, _fbs)) goto loc_00225833; /* jg: greater (signed >) */

loc_0022580A: ;
    ecx = MEM32(eax + 0x24);
    _fa = (uint32_t)(ecx) & 0xFFFFFFFFu; _fb = (uint32_t)(ecx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ecx, ecx (32-bit) */
    MEM32(esi + 0x28) = ecx;
    if (TEST_NZ(_fa, _fb)) goto loc_00225817; /* jne: not equal / not zero */

loc_00225814: ;
    MEM32(esi + 0x2C) = MEM32(esi + 0x2C) & ecx;

loc_00225817: ;
    SET_LO16(ecx, MEM16(eax + 0x20));
    SET_LO16(ecx, LO16(ecx) + LO16(edx));
    MEM16(esi + 0x24) = LO16(ecx);
    ecx = MEM32(ebp + -4);
    PUSH32(esp, eax);
    edx = esi;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x0022582Du); sub_002254E6(); /* call 0x002254E6 */

loc_0022582D: ;
    _fa = (uint32_t)(MEM32(esi + 0x28)) & 0xFFFFFFFFu; _fb = (uint32_t)(0) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(esi + 0x28), 0 (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_002257F5; /* jne: not equal / not zero */

loc_00225833: ;
    POP32(esp, ebx);

loc_00225834: ;
    POP32(esp, esi);
    esp = ebp;
    POP32(esp, ebp); /* leave */
    esp += 4; return; /* ret */

}

/**
 * sub_00225837
 * Original: 0x00225837 - 0x00225884 (77 bytes, 26 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00225837(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00225837: ;
    PUSH32(esp, esi);
    esi = ecx;
    _fa = (uint32_t)(MEM32(esi + 0x424)) & 0xFFFFFFFFu; _fb = (uint32_t)(0) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(esi + 0x424), 0 (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_00225882; /* je: equal / zero */

loc_00225843: ;
    PUSH32(esp, edi);

loc_00225844: ;
    edi = MEM32(esi + 0x424);
    eax = 0; /* xor self */
    SET_LO16(eax, MEM16(edi + 0x20));
    PUSH32(esp, eax);
    PUSH32(esp, 0x00225856u); sub_0022545B(); /* call 0x0022545B */

loc_00225856: ;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_00225881; /* je: equal / zero */

loc_0022585A: ;
    eax = MEM32(edi + 0x24);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    MEM32(esi + 0x424) = eax;
    if (TEST_NZ(_fa, _fb)) goto loc_0022586D; /* jne: not equal / not zero */

loc_00225867: ;
    MEM32(esi + 0x428) = MEM32(esi + 0x428) & eax;

loc_0022586D: ;
    edx = MEM32(edi + 0x10);
    PUSH32(esp, edi);
    ecx = esi;
    PUSH32(esp, 0x00225878u); sub_002254E6(); /* call 0x002254E6 */

loc_00225878: ;
    _fa = (uint32_t)(MEM32(esi + 0x424)) & 0xFFFFFFFFu; _fb = (uint32_t)(0) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(esi + 0x424), 0 (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_00225844; /* jne: not equal / not zero */

loc_00225881: ;
    POP32(esp, edi);

loc_00225882: ;
    POP32(esp, esi);
    esp += 4; return; /* ret */

}

/**
 * sub_00225884
 * Original: 0x00225884 - 0x002258D1 (77 bytes, 26 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00225884(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00225884: ;
    PUSH32(esp, esi);
    esi = ecx;
    _fa = (uint32_t)(MEM32(esi + 0x41C)) & 0xFFFFFFFFu; _fb = (uint32_t)(0) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(esi + 0x41C), 0 (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_002258CF; /* je: equal / zero */

loc_00225890: ;
    PUSH32(esp, edi);

loc_00225891: ;
    edi = MEM32(esi + 0x41C);
    eax = 0; /* xor self */
    SET_LO16(eax, MEM16(edi + 0x20));
    PUSH32(esp, eax);
    PUSH32(esp, 0x002258A3u); sub_0022543C(); /* call 0x0022543C */

loc_002258A3: ;
    _fa = (uint32_t)(LO8(eax)) & 0xFFu; _fb = (uint32_t)(LO8(eax)) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(eax), LO8(eax) (8-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_002258CE; /* je: equal / zero */

loc_002258A7: ;
    eax = MEM32(edi + 0x24);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    MEM32(esi + 0x41C) = eax;
    if (TEST_NZ(_fa, _fb)) goto loc_002258BA; /* jne: not equal / not zero */

loc_002258B4: ;
    MEM32(esi + 0x420) = MEM32(esi + 0x420) & eax;

loc_002258BA: ;
    edx = MEM32(edi + 0x10);
    PUSH32(esp, edi);
    ecx = esi;
    PUSH32(esp, 0x002258C5u); sub_002254E6(); /* call 0x002254E6 */

loc_002258C5: ;
    _fa = (uint32_t)(MEM32(esi + 0x41C)) & 0xFFFFFFFFu; _fb = (uint32_t)(0) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(esi + 0x41C), 0 (32-bit) */
    if (CMP_NE(_fa, _fb)) goto loc_00225891; /* jne: not equal / not zero */

loc_002258CE: ;
    POP32(esp, edi);

loc_002258CF: ;
    POP32(esp, esi);
    esp += 4; return; /* ret */

}

/**
 * sub_002258D1
 * Original: 0x002258D1 - 0x00225904 (51 bytes, 17 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_002258D1(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_002258D1: ;
    eax = MEM32(esp + 4);
    _fa = (uint32_t)(MEM16(eax + 0x20)) & 0xFFFFu; _fb = (uint32_t)(3) & 0xFFFFu;
    _fas = (int32_t)(int16_t)(_fa); _fbs = (int32_t)(int16_t)(_fb); /* cmp MEM16(eax + 0x20), 3 (16-bit) */
    if (CMP_BE(_fa, _fb)) goto loc_002258E3; /* jbe: below or equal (unsigned <=) */

loc_002258DC: ;
    eax = 0x80000500u;
    goto loc_00225901;

loc_002258E3: ;
    PUSH32(esp, esi);
    esi = MEM32(edx + 0x2C);
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(esi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test esi, esi (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_002258F0; /* je: equal / zero */

loc_002258EB: ;
    MEM32(esi + 0x24) = eax;
    goto loc_002258F3;

loc_002258F0: ;
    MEM32(edx + 0x28) = eax;

loc_002258F3: ;
    MEM32(edx + 0x2C) = eax;
    PUSH32(esp, 0x002258FBu); sub_002257E4(); /* call 0x002257E4 */

loc_002258FB: ;
    eax = 0x40000000;
    POP32(esp, esi);

loc_00225901: ;
    esp += 8; return; /* ret 4 */

}

/**
 * sub_00225904
 * Original: 0x00225904 - 0x00225940 (60 bytes, 16 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00225904(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00225904: ;
    SET_LO16(eax, MEM16(edx + 0x20));
    _fa = (uint32_t)(LO16(eax)) & 0xFFFFu; _fb = (uint32_t)(MEM16(0x2878A4)) & 0xFFFFu;
    _fas = (int32_t)(int16_t)(_fa); _fbs = (int32_t)(int16_t)(_fb); /* cmp LO16(eax), MEM16(0x2878A4) (16-bit) */
    if (CMP_BE(_fa, _fb)) goto loc_00225917; /* jbe: below or equal (unsigned <=) */

loc_00225911: ;
    eax = 0x80000500u;
    esp += 4; return; /* ret */

loc_00225917: ;
    eax = ecx + 0x424;
    _fa = (uint32_t)(MEM32(eax)) & 0xFFFFFFFFu; _fb = (uint32_t)(0) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(eax), 0 (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_0022592D; /* je: equal / zero */

loc_00225922: ;
    eax = MEM32(ecx + 0x428);
    MEM32(eax + 0x24) = edx;
    goto loc_0022592F;

loc_0022592D: ;
    MEM32(eax) = edx;

loc_0022592F: ;
    MEM32(ecx + 0x428) = edx;
    PUSH32(esp, 0x0022593Au); sub_00225837(); /* call 0x00225837 */

loc_0022593A: ;
    eax = 0x40000000;
    esp += 4; return; /* ret */

}

/**
 * sub_00225940
 * Original: 0x00225940 - 0x0022597C (60 bytes, 16 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00225940(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00225940: ;
    SET_LO16(eax, MEM16(edx + 0x20));
    _fa = (uint32_t)(LO16(eax)) & 0xFFFFu; _fb = (uint32_t)(MEM16(0x2878A0)) & 0xFFFFu;
    _fas = (int32_t)(int16_t)(_fa); _fbs = (int32_t)(int16_t)(_fb); /* cmp LO16(eax), MEM16(0x2878A0) (16-bit) */
    if (CMP_BE(_fa, _fb)) goto loc_00225953; /* jbe: below or equal (unsigned <=) */

loc_0022594D: ;
    eax = 0x80000500u;
    esp += 4; return; /* ret */

loc_00225953: ;
    eax = ecx + 0x41C;
    _fa = (uint32_t)(MEM32(eax)) & 0xFFFFFFFFu; _fb = (uint32_t)(0) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp MEM32(eax), 0 (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_00225969; /* je: equal / zero */

loc_0022595E: ;
    eax = MEM32(ecx + 0x420);
    MEM32(eax + 0x24) = edx;
    goto loc_0022596B;

loc_00225969: ;
    MEM32(eax) = edx;

loc_0022596B: ;
    MEM32(ecx + 0x420) = edx;
    PUSH32(esp, 0x00225976u); sub_00225884(); /* call 0x00225884 */

loc_00225976: ;
    eax = 0x40000000;
    esp += 4; return; /* ret */

}

/**
 * sub_0022597C
 * Original: 0x0022597C - 0x00225A02 (134 bytes, 53 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0022597C(void)
{
    uint32_t ebp;
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_0022597C: ;
    PUSH32(esp, ebp);
    ebp = esp;
    g_ebp = ebp; /* publish frame for frameless callees */
    PUSH32(esp, ecx);
    PUSH32(esp, ebx);
    PUSH32(esp, esi);
    esi = edx;
    PUSH32(esp, edi);
    edi = MEM32(esi + 0x10);
    ebx = ecx;
    edx = edi;
    ecx = esi;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x00225993u); sub_0022547A(); /* call 0x0022547A */

loc_00225993: ;
    MEM16(esi + 0x20) = LO16(eax);
    { uint32_t _icall_esp = g_esp;
    { uint32_t _icall_target = MEM32(0x225B30); PUSH32(esp, 0x0022599Du); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_0022599D: ;
    MEM8(edi + 0x26) = MEM8(edi + 0x26) + 1;
    MEM32(esi + 0x24) = MEM32(esi + 0x24) & 0;
    MEM8(ebp + -1) = LO8(eax);
    MEM16(esi + 0x22) = 2;
    eax = ZX8(MEM8(edi + 0x11));
    eax = eax - 0;
    if ((eax == 0)) goto loc_002259DB; /* je: equal / zero */

loc_002259B6: ;
    eax--;
    eax--;
    if ((eax == 0)) goto loc_002259D0; /* je: equal / zero */

loc_002259BA: ;
    eax--;
    if ((eax == 0)) goto loc_002259C4; /* je: equal / zero */

loc_002259BD: ;
    ebx = 0x80000600u;
    goto loc_002259EA;

loc_002259C4: ;
    PUSH32(esp, esi);
    edx = edi;
    ecx = ebx;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x002259CEu); sub_002258D1(); /* call 0x002258D1 */

loc_002259CE: ;
    goto loc_002259E4;

loc_002259D0: ;
    edx = esi;
    ecx = ebx;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x002259D9u); sub_00225904(); /* call 0x00225904 */

loc_002259D9: ;
    goto loc_002259E4;

loc_002259DB: ;
    edx = esi;
    ecx = ebx;
    g_ebp = ebp; /* frame stays current across calls */
    PUSH32(esp, 0x002259E4u); sub_00225940(); /* call 0x00225940 */

loc_002259E4: ;
    ebx = eax;
    _fa = (uint32_t)(ebx) & 0xFFFFFFFFu; _fb = (uint32_t)(ebx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test ebx, ebx (32-bit) */
    if (CMP_GE(_fas & _fbs, 0)) goto loc_002259F2; /* jge: greater or equal (signed >=) */

loc_002259EA: ;
    MEM16(esi + 0x22) = MEM16(esi + 0x22) & 0;
    MEM8(edi + 0x26) = MEM8(edi + 0x26) - 1;

loc_002259F2: ;
    SET_LO8(ecx, MEM8(ebp + -1));
    { uint32_t _icall_esp = g_esp;
    { uint32_t _icall_target = MEM32(0x225B2C); PUSH32(esp, 0x002259FBu); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); } /* indirect call */
    }

loc_002259FB: ;
    POP32(esp, edi);
    POP32(esp, esi);
    eax = ebx;
    POP32(esp, ebx);
    esp = ebp;
    POP32(esp, ebp); /* leave */
    esp += 4; return; /* ret */

}
