/* Retail callbacks observed immediately before crash CE45648D31F5AFCD.
 * Byte-checked against the retail XBE; see
 * tools/lift_crash_callbacks_20261011.py. */
#define RECOMP_GENERATED_CODE
#include "recomp_funcs.h"

/**
 * sub_0001F500
 * Original: 0x0001F500 - 0x0001F657 (343 bytes, 127 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0001F500(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_0001F500: ;
    esp = esp - 0x50;
    PUSH32(esp, esi);
    esi = MEM32(esp + 0x58);
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(esi) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test esi, esi (32-bit) */
    PUSH32(esp, edi);
    edi = ecx;
    if (TEST_Z(_fa, _fb)) goto loc_0001F64D; /* je: equal / zero */

loc_0001F513: ;
    eax = MEM32(esi);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0x9C519AA2u) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0x9C519AA2u (32-bit) */
    PUSH32(esp, ebx);
    if (CMP_A(_fa, _fb)) goto loc_0001F606; /* ja: above (unsigned >) */

loc_0001F521: ;
    if (CMP_EQ(_fa, _fb)) goto loc_0001F59B; /* je: equal / zero */

loc_0001F523: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0x15118CEB) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0x15118CEB (32-bit) */
    if (CMP_EQ(_fa, _fb)) goto loc_0001F534; /* je: equal / zero */

loc_0001F52A: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0x4ED3433F) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0x4ED3433F (32-bit) */
    goto loc_0001F60B;

loc_0001F534: ;
    eax = MEM32(esp + 0x64);
    eax = MEM32(eax + 0x14);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0xFFFFFFFFu) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0xFFFFFFFFu (32-bit) */
    PUSH32(esp, 1);
    if (CMP_EQ(_fa, _fb)) goto loc_0001F573; /* je: equal / zero */

loc_0001F542: ;
    ecx = esp + 0x68;
    PUSH32(esp, ecx);
    ecx = esp + 0x14;
    MEM32(esp + 0x6C) = eax;
    PUSH32(esp, 0x0001F554u); sub_00041780(); /* call 0x00041780 */

loc_0001F554: ;
    PUSH32(esp, eax);
    PUSH32(esp, esi);
    ecx = edi;
    PUSH32(esp, 0x0001F55Du); sub_0001E9F0(); /* call 0x0001E9F0 */

loc_0001F55D: ;
    ecx = esp + 0xC;
    SET_LO8(ebx, LO8(eax));
    PUSH32(esp, 0x0001F568u); sub_00029B30(); /* call 0x00029B30 */

loc_0001F568: ;
    SET_LO8(eax, LO8(ebx));
    POP32(esp, ebx);
    POP32(esp, edi);
    POP32(esp, esi);
    esp = esp + 0x50;
    esp += 12; return; /* ret 8 */

loc_0001F573: ;
    ecx = esp + 0x20;
    PUSH32(esp, 0x0001F57Cu); sub_00041730(); /* call 0x00041730 */

loc_0001F57C: ;
    PUSH32(esp, eax);
    PUSH32(esp, esi);
    ecx = edi;
    PUSH32(esp, 0x0001F585u); sub_0001E9F0(); /* call 0x0001E9F0 */

loc_0001F585: ;
    ecx = esp + 0x1C;
    SET_LO8(ebx, LO8(eax));
    PUSH32(esp, 0x0001F590u); sub_00029B30(); /* call 0x00029B30 */

loc_0001F590: ;
    SET_LO8(eax, LO8(ebx));
    POP32(esp, ebx);
    POP32(esp, edi);
    POP32(esp, esi);
    esp = esp + 0x50;
    esp += 12; return; /* ret 8 */

loc_0001F59B: ;
    ecx = MEM32(esp + 0x64);
    eax = MEM32(ecx + 0x14);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0xFFFFFFFFu) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0xFFFFFFFFu (32-bit) */
    PUSH32(esp, 1);
    if (CMP_EQ(_fa, _fb)) goto loc_0001F5DA; /* je: equal / zero */

loc_0001F5A9: ;
    edx = esp + 0x64;
    PUSH32(esp, edx);
    ecx = esp + 0x34;
    MEM32(esp + 0x68) = eax;
    PUSH32(esp, 0x0001F5BBu); sub_00041780(); /* call 0x00041780 */

loc_0001F5BB: ;
    PUSH32(esp, eax);
    PUSH32(esp, esi);
    ecx = edi;
    PUSH32(esp, 0x0001F5C4u); sub_0001E9F0(); /* call 0x0001E9F0 */

loc_0001F5C4: ;
    ecx = esp + 0x2C;
    SET_LO8(ebx, LO8(eax));
    PUSH32(esp, 0x0001F5CFu); sub_00029B30(); /* call 0x00029B30 */

loc_0001F5CF: ;
    SET_LO8(eax, LO8(ebx));
    POP32(esp, ebx);
    POP32(esp, edi);
    POP32(esp, esi);
    esp = esp + 0x50;
    esp += 12; return; /* ret 8 */

loc_0001F5DA: ;
    ecx = ecx + 4;
    PUSH32(esp, ecx);
    ecx = esp + 0x44;
    PUSH32(esp, 0x0001F5E7u); sub_00041740(); /* call 0x00041740 */

loc_0001F5E7: ;
    PUSH32(esp, eax);
    PUSH32(esp, esi);
    ecx = edi;
    PUSH32(esp, 0x0001F5F0u); sub_0001E9F0(); /* call 0x0001E9F0 */

loc_0001F5F0: ;
    ecx = esp + 0x3C;
    SET_LO8(ebx, LO8(eax));
    PUSH32(esp, 0x0001F5FBu); sub_00029B30(); /* call 0x00029B30 */

loc_0001F5FB: ;
    SET_LO8(eax, LO8(ebx));
    POP32(esp, ebx);
    POP32(esp, edi);
    POP32(esp, esi);
    esp = esp + 0x50;
    esp += 12; return; /* ret 8 */

loc_0001F606: ;
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(0xD6E30158u) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp eax, 0xD6E30158u (32-bit) */

loc_0001F60B: ;
    if (_flags /* je: equal / zero */) goto loc_0001F623;

loc_0001F60D: ;
    eax = MEM32(esp + 0x64);
    PUSH32(esp, eax);
    PUSH32(esp, esi);
    ecx = edi;
    PUSH32(esp, 0x0001F61Au); sub_0001E4D0(); /* call 0x0001E4D0 */

loc_0001F61A: ;
    POP32(esp, ebx);
    POP32(esp, edi);
    POP32(esp, esi);
    esp = esp + 0x50;
    esp += 12; return; /* ret 8 */

loc_0001F623: ;
    PUSH32(esp, 1);
    ecx = esp + 0x50;
    PUSH32(esp, 0x0001F62Eu); sub_00041730(); /* call 0x00041730 */

loc_0001F62E: ;
    PUSH32(esp, eax);
    PUSH32(esp, esi);
    ecx = edi;
    PUSH32(esp, 0x0001F637u); sub_0001E9F0(); /* call 0x0001E9F0 */

loc_0001F637: ;
    ecx = esp + 0x4C;
    SET_LO8(ebx, LO8(eax));
    PUSH32(esp, 0x0001F642u); sub_00029B30(); /* call 0x00029B30 */

loc_0001F642: ;
    SET_LO8(eax, LO8(ebx));
    POP32(esp, ebx);
    POP32(esp, edi);
    POP32(esp, esi);
    esp = esp + 0x50;
    esp += 12; return; /* ret 8 */

loc_0001F64D: ;
    POP32(esp, edi);
    SET_LO8(eax, 0); /* xor self */
    POP32(esp, esi);
    esp = esp + 0x50;
    esp += 12; return; /* ret 8 */

}

/**
 * sub_00075330
 * Original: 0x00075330 - 0x00075338 (8 bytes, 3 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00075330(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_00075330: ;
    ecx = ecx + 0x14;
    eax = MEM32(ecx);
    g_seh_ebp = ebp; RECOMP_ITAIL(MEM32(eax + 0x34)); return; /* indirect tail jmp */

}

