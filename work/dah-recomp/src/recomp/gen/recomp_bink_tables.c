/* Retail BINK32 callbacks from the static table at 0x0029BFA0.
 * Isolated lifts preserve entry boundaries and return ABI. */
#define RECOMP_GENERATED_CODE
#include "recomp_funcs.h"
#include "dah_timing.h"
#include "recomp_mmx.h"

/**
 * sub_00217680
 * Original: 0x00217680 - 0x002176CB (75 bytes, 20 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00217680(void)
{
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

loc_00217680: ;
    edx = MEM32(esp + 8);
    _fa = (uint32_t)(edx) & 0xFFFFFFFFu; _fb = (uint32_t)(edx) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test edx, edx (32-bit) */
    if (TEST_Z(_fa, _fb)) goto loc_002176CA; /* je: equal / zero */

loc_00217688: ;
    goto loc_00217690;

    /* nop */

loc_00217690: ;
    ecx = MEM32(0x299F18);
    eax = ZX8(MEM8(ecx));
    eax = MEM32(eax * 4 + 0x299B10);
    ecx++;
    MEM32(0x299F18) = ecx;
    ecx = MEM32(0x299F10);
    MEM32(ecx) = eax;
    ecx = MEM32(0x299F10);
    MEM32(ecx + 4) = eax;
    ecx = MEM32(0x299F10);
    ecx = ecx + 8;
    edx--;
    MEM32(0x299F10) = ecx;
    if ((edx != 0)) goto loc_00217690; /* jne: not equal / not zero */

loc_002176CA: ;
    esp += 4; return; /* ret */

}


/**
 * sub_00217B70
 * Original: 0x00217B70 - 0x00217C39 (201 bytes, 59 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00217B70(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_00217B70: ;
    eax = MEM32(esp + 8);
    _fa = (uint32_t)(eax) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* test eax, eax (32-bit) */
    PUSH32(esp, ebx);
    ebx = MEM32(esp + 8);
    if (TEST_Z(_fa, _fb)) goto loc_00217C37; /* je: equal / zero */

loc_00217B81: ;
    PUSH32(esp, ebp);
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    ebp = eax;
    goto loc_00217B90;

    /* nop */
    /* nop */

loc_00217B90: ;
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
    edx = MEM32(0x299F30);
    MEM32(edx + ecx) = eax;
    edx = MEM32(0x299F10);
    edx = edx + 4;
    ebx++;
    _fa = (uint32_t)(LO8(ebx)) & 0xFFu; _fb = (uint32_t)(1) & 0xFFu;
    _fas = (int32_t)(int8_t)(_fa); _fbs = (int32_t)(int8_t)(_fb); /* test LO8(ebx), 1 (8-bit) */
    MEM32(0x299F10) = edx;
    if (TEST_NZ(_fa, _fb)) goto loc_00217C2D; /* jne: not equal / not zero */

loc_00217C15: ;
    ecx = MEM32(0x299F20);
    eax = MEM32(0x299F24);
    ecx++;
    eax++;
    MEM32(0x299F20) = ecx;
    MEM32(0x299F24) = eax;

loc_00217C2D: ;
    ebp--;
    if ((ebp != 0)) goto loc_00217B90; /* jne: not equal / not zero */

loc_00217C34: ;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebp);

loc_00217C37: ;
    POP32(esp, ebx);
    esp += 4; return; /* ret */

}


/**
 * sub_00218530
 * Original: 0x00218530 - 0x00218805 (725 bytes, 177 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00218530(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    uint64_t mm0, mm1, mm2, mm3, mm4, mm5, mm6, mm7;
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_00218530: ;
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
    mm7 = ((uint64_t)MEM32((uint32_t)(0x25a7e8)) | ((uint64_t)MEM32((uint32_t)(0x25a7e8) + 4u) << 32)); /* MMX 0x0021855A: movq mm7, qword ptr [0x25a7e8] */

loc_00218561: ;
    mm4 = (uint64_t)(uint32_t)(MEM32((uint32_t)(edx))); /* MMX 0x00218561: movd mm4, dword ptr [edx] */
    mm0 = MMX_PXOR(mm0, mm0); /* MMX 0x00218564: pxor mm0, mm0 */
    eax = 0; /* xor self */
    edx = edx + 4;
    SET_LO8(eax, MEM8(ebp));
    mm4 = MMX_PUNPCKLBW(mm4, mm0); /* MMX 0x0021856F: punpcklbw mm4, mm0 */
    mm2 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29b738))); /* MMX 0x00218572: movd mm2, dword ptr [eax*4 + 0x29b738] */
    mm1 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29af38))); /* MMX 0x0021857A: movd mm1, dword ptr [eax*4 + 0x29af38] */
    SET_LO8(eax, MEM8(ebp + 1));
    ebp = ebp + 2;
    mm4 = MMX_PSUBUSW(mm4, ((uint64_t)MEM32((uint32_t)(0x25a7d8)) | ((uint64_t)MEM32((uint32_t)(0x25a7d8) + 4u) << 32))); /* MMX 0x00218588: psubusw mm4, qword ptr [0x25a7d8] */
    mm6 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29b738))); /* MMX 0x0021858F: movd mm6, dword ptr [eax*4 + 0x29b738] */
    mm1 = MMX_PUNPCKLDQ(mm1, (uint64_t)MEM32((uint32_t)(eax*4 + 0x29af38))); /* MMX 0x00218597: punpckldq mm1, dword ptr [eax*4 + 0x29af38] */
    SET_LO8(eax, MEM8(ebx));
    mm4 = MMX_PSLLW(mm4, 2u); /* MMX 0x002185A1: psllw mm4, 2 */
    mm4 = MMX_PMULHW(mm4, ((uint64_t)MEM32((uint32_t)(0x25a7e0)) | ((uint64_t)MEM32((uint32_t)(0x25a7e0) + 4u) << 32))); /* MMX 0x002185A5: pmulhw mm4, qword ptr [0x25a7e0] */
    mm5 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29b338))); /* MMX 0x002185AC: movd mm5, dword ptr [eax*4 + 0x29b338] */
    mm3 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29bb38))); /* MMX 0x002185B4: movd mm3, dword ptr [eax*4 + 0x29bb38] */
    mm2 = MMX_PADDW(mm2, mm5); /* MMX 0x002185BC: paddw mm2, mm5 */
    SET_LO8(eax, MEM8(ebx + 1));
    ebx = ebx + 2;
    mm5 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29b338))); /* MMX 0x002185C5: movd mm5, dword ptr [eax*4 + 0x29b338] */
    mm3 = MMX_PUNPCKLDQ(mm3, (uint64_t)MEM32((uint32_t)(eax*4 + 0x29bb38))); /* MMX 0x002185CD: punpckldq mm3, dword ptr [eax*4 + 0x29bb38] */
    mm6 = MMX_PADDW(mm6, mm5); /* MMX 0x002185D5: paddw mm6, mm5 */
    SET_LO8(eax, MEM8(ebp));
    mm2 = MMX_PUNPCKLDQ(mm2, mm6); /* MMX 0x002185DB: punpckldq mm2, mm6 */
    mm1 = MMX_PSRLQ(mm1, 0x10u); /* MMX 0x002185DE: psrlq mm1, 0x10 */
    mm6 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29af38))); /* MMX 0x002185E2: movd mm6, dword ptr [eax*4 + 0x29af38] */
    mm2 = MMX_PSRLQ(mm2, 0x10u); /* MMX 0x002185EA: psrlq mm2, 0x10 */
    mm5 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29b738))); /* MMX 0x002185EE: movd mm5, dword ptr [eax*4 + 0x29b738] */
    mm3 = MMX_PSRLQ(mm3, 0x10u); /* MMX 0x002185F6: psrlq mm3, 0x10 */
    SET_LO8(eax, MEM8(ebx));
    mm6 = MMX_PSLLQ(mm6, 0x30u); /* MMX 0x002185FC: psllq mm6, 0x30 */
    mm1 = MMX_POR(mm1, mm6); /* MMX 0x00218600: por mm1, mm6 */
    mm6 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29b338))); /* MMX 0x00218603: movd mm6, dword ptr [eax*4 + 0x29b338] */
    mm5 = MMX_PADDW(mm5, mm6); /* MMX 0x0021860B: paddw mm5, mm6 */
    mm6 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29bb38))); /* MMX 0x0021860E: movd mm6, dword ptr [eax*4 + 0x29bb38] */
    mm5 = MMX_PSLLQ(mm5, 0x30u); /* MMX 0x00218616: psllq mm5, 0x30 */
    mm6 = MMX_PSLLQ(mm6, 0x30u); /* MMX 0x0021861A: psllq mm6, 0x30 */
    mm2 = MMX_POR(mm2, mm5); /* MMX 0x0021861E: por mm2, mm5 */
    mm3 = MMX_POR(mm3, mm6); /* MMX 0x00218621: por mm3, mm6 */
    mm1 = MMX_PADDW(mm1, mm4); /* MMX 0x00218624: paddw mm1, mm4 */
    mm2 = MMX_PADDW(mm2, mm4); /* MMX 0x00218627: paddw mm2, mm4 */
    mm1 = MMX_PADDSW(mm1, mm7); /* MMX 0x0021862A: paddsw mm1, mm7 */
    mm3 = MMX_PADDW(mm3, mm4); /* MMX 0x0021862D: paddw mm3, mm4 */
    mm1 = MMX_PSUBUSW(mm1, mm7); /* MMX 0x00218630: psubusw mm1, mm7 */
    mm2 = MMX_PADDSW(mm2, mm7); /* MMX 0x00218633: paddsw mm2, mm7 */
    mm4 = mm1; /* MMX 0x00218636: movq mm4, mm1 */
    mm2 = MMX_PSUBUSW(mm2, mm7); /* MMX 0x00218639: psubusw mm2, mm7 */
    mm1 = MMX_PUNPCKLWD(mm1, mm0); /* MMX 0x0021863C: punpcklwd mm1, mm0 */
    mm5 = mm2; /* MMX 0x0021863F: movq mm5, mm2 */
    mm2 = MMX_PUNPCKLWD(mm2, mm0); /* MMX 0x00218642: punpcklwd mm2, mm0 */
    mm3 = MMX_PADDSW(mm3, mm7); /* MMX 0x00218645: paddsw mm3, mm7 */
    mm2 = MMX_PSLLD(mm2, 8u); /* MMX 0x00218648: pslld mm2, 8 */
    mm3 = MMX_PSUBUSW(mm3, mm7); /* MMX 0x0021864C: psubusw mm3, mm7 */
    mm4 = MMX_PUNPCKHWD(mm4, mm0); /* MMX 0x0021864F: punpckhwd mm4, mm0 */
    mm6 = mm3; /* MMX 0x00218652: movq mm6, mm3 */
    mm3 = MMX_PUNPCKLWD(mm3, mm0); /* MMX 0x00218655: punpcklwd mm3, mm0 */
    mm3 = MMX_PSLLD(mm3, 0x10u); /* MMX 0x00218658: pslld mm3, 0x10 */
    mm1 = MMX_POR(mm1, mm2); /* MMX 0x0021865C: por mm1, mm2 */
    mm1 = MMX_POR(mm1, mm3); /* MMX 0x0021865F: por mm1, mm3 */
    mm5 = MMX_PUNPCKHWD(mm5, mm0); /* MMX 0x00218662: punpckhwd mm5, mm0 */
    mm6 = MMX_PUNPCKHWD(mm6, mm0); /* MMX 0x00218665: punpckhwd mm6, mm0 */
    mm5 = MMX_PSLLD(mm5, 8u); /* MMX 0x00218668: pslld mm5, 8 */
    MEM32((uint32_t)(edi)) = (uint32_t)mm1; MEM32((uint32_t)(edi) + 4u) = (uint32_t)(mm1 >> 32); /* MMX 0x0021866C: movq qword ptr [edi], mm1 */
    mm6 = MMX_PSLLD(mm6, 0x10u); /* MMX 0x0021866F: pslld mm6, 0x10 */
    mm4 = MMX_POR(mm4, mm5); /* MMX 0x00218673: por mm4, mm5 */
    edi = edi + 0x10;
    mm4 = MMX_POR(mm4, mm6); /* MMX 0x00218679: por mm4, mm6 */
    eax = MEM32(0x299F10);
    MEM32((uint32_t)(edi - 8)) = (uint32_t)mm4; MEM32((uint32_t)(edi - 8) + 4u) = (uint32_t)(mm4 >> 32); /* MMX 0x00218681: movq qword ptr [edi - 8], mm4 */
    _fa = (uint32_t)(edi) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edi, eax (32-bit) */
    if (CMP_B(_fa, _fb)) goto loc_00218561; /* jb: below (unsigned <) */

loc_0021868D: ;
    MEM32(0x299F18) = edx;
    edi = MEM32(0x299F14);
    edx = MEM32(0x299F1C);
    ebp = MEM32(0x299F20);
    ebx = MEM32(0x299F24);
    eax = MEM32(esp + 0x14);
    eax = eax << 4;
    eax = eax + edi;
    MEM32(0x299F14) = eax;
    mm7 = ((uint64_t)MEM32((uint32_t)(0x25a7e8)) | ((uint64_t)MEM32((uint32_t)(0x25a7e8) + 4u) << 32)); /* MMX 0x002186B9: movq mm7, qword ptr [0x25a7e8] */

loc_002186C0: ;
    mm4 = (uint64_t)(uint32_t)(MEM32((uint32_t)(edx))); /* MMX 0x002186C0: movd mm4, dword ptr [edx] */
    mm0 = MMX_PXOR(mm0, mm0); /* MMX 0x002186C3: pxor mm0, mm0 */
    eax = 0; /* xor self */
    edx = edx + 4;
    SET_LO8(eax, MEM8(ebp));
    mm4 = MMX_PUNPCKLBW(mm4, mm0); /* MMX 0x002186CE: punpcklbw mm4, mm0 */
    mm2 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29b738))); /* MMX 0x002186D1: movd mm2, dword ptr [eax*4 + 0x29b738] */
    mm1 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29af38))); /* MMX 0x002186D9: movd mm1, dword ptr [eax*4 + 0x29af38] */
    SET_LO8(eax, MEM8(ebp + 1));
    ebp = ebp + 2;
    mm4 = MMX_PSUBUSW(mm4, ((uint64_t)MEM32((uint32_t)(0x25a7d8)) | ((uint64_t)MEM32((uint32_t)(0x25a7d8) + 4u) << 32))); /* MMX 0x002186E7: psubusw mm4, qword ptr [0x25a7d8] */
    mm6 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29b738))); /* MMX 0x002186EE: movd mm6, dword ptr [eax*4 + 0x29b738] */
    mm1 = MMX_PUNPCKLDQ(mm1, (uint64_t)MEM32((uint32_t)(eax*4 + 0x29af38))); /* MMX 0x002186F6: punpckldq mm1, dword ptr [eax*4 + 0x29af38] */
    SET_LO8(eax, MEM8(ebx));
    mm4 = MMX_PSLLW(mm4, 2u); /* MMX 0x00218700: psllw mm4, 2 */
    mm4 = MMX_PMULHW(mm4, ((uint64_t)MEM32((uint32_t)(0x25a7e0)) | ((uint64_t)MEM32((uint32_t)(0x25a7e0) + 4u) << 32))); /* MMX 0x00218704: pmulhw mm4, qword ptr [0x25a7e0] */
    mm5 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29b338))); /* MMX 0x0021870B: movd mm5, dword ptr [eax*4 + 0x29b338] */
    mm3 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29bb38))); /* MMX 0x00218713: movd mm3, dword ptr [eax*4 + 0x29bb38] */
    mm2 = MMX_PADDW(mm2, mm5); /* MMX 0x0021871B: paddw mm2, mm5 */
    SET_LO8(eax, MEM8(ebx + 1));
    ebx = ebx + 2;
    mm5 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29b338))); /* MMX 0x00218724: movd mm5, dword ptr [eax*4 + 0x29b338] */
    mm3 = MMX_PUNPCKLDQ(mm3, (uint64_t)MEM32((uint32_t)(eax*4 + 0x29bb38))); /* MMX 0x0021872C: punpckldq mm3, dword ptr [eax*4 + 0x29bb38] */
    mm6 = MMX_PADDW(mm6, mm5); /* MMX 0x00218734: paddw mm6, mm5 */
    SET_LO8(eax, MEM8(ebp));
    mm2 = MMX_PUNPCKLDQ(mm2, mm6); /* MMX 0x0021873A: punpckldq mm2, mm6 */
    mm1 = MMX_PSRLQ(mm1, 0x10u); /* MMX 0x0021873D: psrlq mm1, 0x10 */
    mm6 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29af38))); /* MMX 0x00218741: movd mm6, dword ptr [eax*4 + 0x29af38] */
    mm2 = MMX_PSRLQ(mm2, 0x10u); /* MMX 0x00218749: psrlq mm2, 0x10 */
    mm5 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29b738))); /* MMX 0x0021874D: movd mm5, dword ptr [eax*4 + 0x29b738] */
    mm3 = MMX_PSRLQ(mm3, 0x10u); /* MMX 0x00218755: psrlq mm3, 0x10 */
    SET_LO8(eax, MEM8(ebx));
    mm6 = MMX_PSLLQ(mm6, 0x30u); /* MMX 0x0021875B: psllq mm6, 0x30 */
    mm1 = MMX_POR(mm1, mm6); /* MMX 0x0021875F: por mm1, mm6 */
    mm6 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29b338))); /* MMX 0x00218762: movd mm6, dword ptr [eax*4 + 0x29b338] */
    mm5 = MMX_PADDW(mm5, mm6); /* MMX 0x0021876A: paddw mm5, mm6 */
    mm6 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29bb38))); /* MMX 0x0021876D: movd mm6, dword ptr [eax*4 + 0x29bb38] */
    mm5 = MMX_PSLLQ(mm5, 0x30u); /* MMX 0x00218775: psllq mm5, 0x30 */
    mm6 = MMX_PSLLQ(mm6, 0x30u); /* MMX 0x00218779: psllq mm6, 0x30 */
    mm2 = MMX_POR(mm2, mm5); /* MMX 0x0021877D: por mm2, mm5 */
    mm3 = MMX_POR(mm3, mm6); /* MMX 0x00218780: por mm3, mm6 */
    mm1 = MMX_PADDW(mm1, mm4); /* MMX 0x00218783: paddw mm1, mm4 */
    mm2 = MMX_PADDW(mm2, mm4); /* MMX 0x00218786: paddw mm2, mm4 */
    mm1 = MMX_PADDSW(mm1, mm7); /* MMX 0x00218789: paddsw mm1, mm7 */
    mm3 = MMX_PADDW(mm3, mm4); /* MMX 0x0021878C: paddw mm3, mm4 */
    mm1 = MMX_PSUBUSW(mm1, mm7); /* MMX 0x0021878F: psubusw mm1, mm7 */
    mm2 = MMX_PADDSW(mm2, mm7); /* MMX 0x00218792: paddsw mm2, mm7 */
    mm4 = mm1; /* MMX 0x00218795: movq mm4, mm1 */
    mm2 = MMX_PSUBUSW(mm2, mm7); /* MMX 0x00218798: psubusw mm2, mm7 */
    mm1 = MMX_PUNPCKLWD(mm1, mm0); /* MMX 0x0021879B: punpcklwd mm1, mm0 */
    mm5 = mm2; /* MMX 0x0021879E: movq mm5, mm2 */
    mm2 = MMX_PUNPCKLWD(mm2, mm0); /* MMX 0x002187A1: punpcklwd mm2, mm0 */
    mm3 = MMX_PADDSW(mm3, mm7); /* MMX 0x002187A4: paddsw mm3, mm7 */
    mm2 = MMX_PSLLD(mm2, 8u); /* MMX 0x002187A7: pslld mm2, 8 */
    mm3 = MMX_PSUBUSW(mm3, mm7); /* MMX 0x002187AB: psubusw mm3, mm7 */
    mm4 = MMX_PUNPCKHWD(mm4, mm0); /* MMX 0x002187AE: punpckhwd mm4, mm0 */
    mm6 = mm3; /* MMX 0x002187B1: movq mm6, mm3 */
    mm3 = MMX_PUNPCKLWD(mm3, mm0); /* MMX 0x002187B4: punpcklwd mm3, mm0 */
    mm3 = MMX_PSLLD(mm3, 0x10u); /* MMX 0x002187B7: pslld mm3, 0x10 */
    mm1 = MMX_POR(mm1, mm2); /* MMX 0x002187BB: por mm1, mm2 */
    mm1 = MMX_POR(mm1, mm3); /* MMX 0x002187BE: por mm1, mm3 */
    mm5 = MMX_PUNPCKHWD(mm5, mm0); /* MMX 0x002187C1: punpckhwd mm5, mm0 */
    mm6 = MMX_PUNPCKHWD(mm6, mm0); /* MMX 0x002187C4: punpckhwd mm6, mm0 */
    mm5 = MMX_PSLLD(mm5, 8u); /* MMX 0x002187C7: pslld mm5, 8 */
    MEM32((uint32_t)(edi)) = (uint32_t)mm1; MEM32((uint32_t)(edi) + 4u) = (uint32_t)(mm1 >> 32); /* MMX 0x002187CB: movq qword ptr [edi], mm1 */
    mm6 = MMX_PSLLD(mm6, 0x10u); /* MMX 0x002187CE: pslld mm6, 0x10 */
    mm4 = MMX_POR(mm4, mm5); /* MMX 0x002187D2: por mm4, mm5 */
    edi = edi + 0x10;
    mm4 = MMX_POR(mm4, mm6); /* MMX 0x002187D8: por mm4, mm6 */
    eax = MEM32(0x299F14);
    MEM32((uint32_t)(edi - 8)) = (uint32_t)mm4; MEM32((uint32_t)(edi - 8) + 4u) = (uint32_t)(mm4 >> 32); /* MMX 0x002187E0: movq qword ptr [edi - 8], mm4 */
    _fa = (uint32_t)(edi) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edi, eax (32-bit) */
    if (CMP_B(_fa, _fb)) goto loc_002186C0; /* jb: below (unsigned <) */

loc_002187EC: ;
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
 * sub_0021F040
 * Original: 0x0021F040 - 0x0021F1FA (442 bytes, 129 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0021F040(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    uint64_t mm0, mm1, mm2, mm3, mm4, mm5, mm6, mm7;
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_0021F040: ;
    PUSH32(esp, ebx);
    PUSH32(esp, ebp);
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    mm0 = ((uint64_t)MEM32((uint32_t)(0x25a7d8)) | ((uint64_t)MEM32((uint32_t)(0x25a7d8) + 4u) << 32)); /* MMX 0x0021F044: movq mm0, qword ptr [0x25a7d8] */
    mm2 = ((uint64_t)MEM32((uint32_t)(0x25a7b0)) | ((uint64_t)MEM32((uint32_t)(0x25a7b0) + 4u) << 32)); /* MMX 0x0021F04B: movq mm2, qword ptr [0x25a7b0] */
    mm5 = ((uint64_t)MEM32((uint32_t)(0x25a7e0)) | ((uint64_t)MEM32((uint32_t)(0x25a7e0) + 4u) << 32)); /* MMX 0x0021F052: movq mm5, qword ptr [0x25a7e0] */
    esi = MEM32(0x299F10);
    ecx = MEM32(0x299F18);
    eax = MEM32(esp + 0x14);
    eax = eax << 5;
    eax = eax + esi;
    edi = edi;

loc_0021F070: ;
    mm3 = (uint64_t)(uint32_t)(MEM32((uint32_t)(ecx))); /* MMX 0x0021F070: movd mm3, dword ptr [ecx] */
    mm4 = MMX_PXOR(mm4, mm4); /* MMX 0x0021F073: pxor mm4, mm4 */
    mm6 = (uint64_t)(uint32_t)(MEM32((uint32_t)(ecx + 4))); /* MMX 0x0021F076: movd mm6, dword ptr [ecx + 4] */
    mm3 = MMX_PUNPCKLBW(mm3, mm4); /* MMX 0x0021F07A: punpcklbw mm3, mm4 */
    mm3 = MMX_PSUBUSW(mm3, mm0); /* MMX 0x0021F07D: psubusw mm3, mm0 */
    mm6 = MMX_PUNPCKLBW(mm6, mm4); /* MMX 0x0021F080: punpcklbw mm6, mm4 */
    mm6 = MMX_PSUBUSW(mm6, mm0); /* MMX 0x0021F083: psubusw mm6, mm0 */
    mm3 = MMX_PSLLW(mm3, 2u); /* MMX 0x0021F086: psllw mm3, 2 */
    mm3 = MMX_PMULHW(mm3, mm5); /* MMX 0x0021F08A: pmulhw mm3, mm5 */
    mm6 = MMX_PSLLW(mm6, 2u); /* MMX 0x0021F08D: psllw mm6, 2 */
    mm7 = ((uint64_t)MEM32((uint32_t)(0x25a7e8)) | ((uint64_t)MEM32((uint32_t)(0x25a7e8) + 4u) << 32)); /* MMX 0x0021F091: movq mm7, qword ptr [0x25a7e8] */
    mm6 = MMX_PMULHW(mm6, mm5); /* MMX 0x0021F098: pmulhw mm6, mm5 */
    ecx = ecx + 8;
    esi = esi + 0x40;
    mm3 = MMX_PADDSW(mm3, mm7); /* MMX 0x0021F0A1: paddsw mm3, mm7 */
    mm3 = MMX_PSUBUSW(mm3, mm7); /* MMX 0x0021F0A4: psubusw mm3, mm7 */
    mm6 = MMX_PADDSW(mm6, mm7); /* MMX 0x0021F0A7: paddsw mm6, mm7 */
    mm1 = mm3; /* MMX 0x0021F0AA: movq mm1, mm3 */
    mm3 = MMX_PUNPCKLWD(mm3, mm3); /* MMX 0x0021F0AD: punpcklwd mm3, mm3 */
    mm1 = MMX_PUNPCKHWD(mm1, mm1); /* MMX 0x0021F0B0: punpckhwd mm1, mm1 */
    mm3 = MMX_PMULLW(mm3, mm2); /* MMX 0x0021F0B3: pmullw mm3, mm2 */
    mm1 = MMX_PMULLW(mm1, mm2); /* MMX 0x0021F0B6: pmullw mm1, mm2 */
    mm6 = MMX_PSUBUSW(mm6, mm7); /* MMX 0x0021F0B9: psubusw mm6, mm7 */
    mm4 = mm6; /* MMX 0x0021F0BC: movq mm4, mm6 */
    mm6 = MMX_PUNPCKLWD(mm6, mm6); /* MMX 0x0021F0BF: punpcklwd mm6, mm6 */
    mm4 = MMX_PUNPCKHWD(mm4, mm4); /* MMX 0x0021F0C2: punpckhwd mm4, mm4 */
    mm6 = MMX_PMULLW(mm6, mm2); /* MMX 0x0021F0C5: pmullw mm6, mm2 */
    mm7 = mm3; /* MMX 0x0021F0C8: movq mm7, mm3 */
    mm3 = MMX_PUNPCKLDQ(mm3, mm3); /* MMX 0x0021F0CB: punpckldq mm3, mm3 */
    mm7 = MMX_PUNPCKHDQ(mm7, mm7); /* MMX 0x0021F0CE: punpckhdq mm7, mm7 */
    mm4 = MMX_PMULLW(mm4, mm2); /* MMX 0x0021F0D1: pmullw mm4, mm2 */
    MEM32((uint32_t)(esi - 0x40)) = (uint32_t)mm3; MEM32((uint32_t)(esi - 0x40) + 4u) = (uint32_t)(mm3 >> 32); /* MMX 0x0021F0D4: movq qword ptr [esi - 0x40], mm3 */
    mm3 = mm1; /* MMX 0x0021F0D8: movq mm3, mm1 */
    MEM32((uint32_t)(esi - 0x38)) = (uint32_t)mm7; MEM32((uint32_t)(esi - 0x38) + 4u) = (uint32_t)(mm7 >> 32); /* MMX 0x0021F0DB: movq qword ptr [esi - 0x38], mm7 */
    mm1 = MMX_PUNPCKLDQ(mm1, mm1); /* MMX 0x0021F0DF: punpckldq mm1, mm1 */
    mm3 = MMX_PUNPCKHDQ(mm3, mm3); /* MMX 0x0021F0E2: punpckhdq mm3, mm3 */
    mm7 = mm6; /* MMX 0x0021F0E5: movq mm7, mm6 */
    MEM32((uint32_t)(esi - 0x30)) = (uint32_t)mm1; MEM32((uint32_t)(esi - 0x30) + 4u) = (uint32_t)(mm1 >> 32); /* MMX 0x0021F0E8: movq qword ptr [esi - 0x30], mm1 */
    mm6 = MMX_PUNPCKLDQ(mm6, mm6); /* MMX 0x0021F0EC: punpckldq mm6, mm6 */
    MEM32((uint32_t)(esi - 0x28)) = (uint32_t)mm3; MEM32((uint32_t)(esi - 0x28) + 4u) = (uint32_t)(mm3 >> 32); /* MMX 0x0021F0EF: movq qword ptr [esi - 0x28], mm3 */
    mm7 = MMX_PUNPCKHDQ(mm7, mm7); /* MMX 0x0021F0F3: punpckhdq mm7, mm7 */
    MEM32((uint32_t)(esi - 0x20)) = (uint32_t)mm6; MEM32((uint32_t)(esi - 0x20) + 4u) = (uint32_t)(mm6 >> 32); /* MMX 0x0021F0F6: movq qword ptr [esi - 0x20], mm6 */
    mm3 = mm4; /* MMX 0x0021F0FA: movq mm3, mm4 */
    MEM32((uint32_t)(esi - 0x18)) = (uint32_t)mm7; MEM32((uint32_t)(esi - 0x18) + 4u) = (uint32_t)(mm7 >> 32); /* MMX 0x0021F0FD: movq qword ptr [esi - 0x18], mm7 */
    mm4 = MMX_PUNPCKLDQ(mm4, mm4); /* MMX 0x0021F101: punpckldq mm4, mm4 */
    mm3 = MMX_PUNPCKHDQ(mm3, mm3); /* MMX 0x0021F104: punpckhdq mm3, mm3 */
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp esi, eax (32-bit) */
    MEM32((uint32_t)(esi - 0x10)) = (uint32_t)mm4; MEM32((uint32_t)(esi - 0x10) + 4u) = (uint32_t)(mm4 >> 32); /* MMX 0x0021F109: movq qword ptr [esi - 0x10], mm4 */
    MEM32((uint32_t)(esi - 8)) = (uint32_t)mm3; MEM32((uint32_t)(esi - 8) + 4u) = (uint32_t)(mm3 >> 32); /* MMX 0x0021F10D: movq qword ptr [esi - 8], mm3 */
    if (CMP_B(_fa, _fb)) goto loc_0021F070; /* jb: below (unsigned <) */

loc_0021F117: ;
    MEM32(0x299F10) = esi;
    MEM32(0x299F18) = ecx;
    edi = MEM32(0x299F14);
    edx = MEM32(0x299F1C);
    eax = MEM32(esp + 0x14);
    eax = eax << 5;
    eax = eax + edi;
    /* nop */
    /* nop */

loc_0021F140: ;
    mm3 = (uint64_t)(uint32_t)(MEM32((uint32_t)(edx))); /* MMX 0x0021F140: movd mm3, dword ptr [edx] */
    mm4 = MMX_PXOR(mm4, mm4); /* MMX 0x0021F143: pxor mm4, mm4 */
    mm6 = (uint64_t)(uint32_t)(MEM32((uint32_t)(edx + 4))); /* MMX 0x0021F146: movd mm6, dword ptr [edx + 4] */
    mm3 = MMX_PUNPCKLBW(mm3, mm4); /* MMX 0x0021F14A: punpcklbw mm3, mm4 */
    mm3 = MMX_PSUBUSW(mm3, mm0); /* MMX 0x0021F14D: psubusw mm3, mm0 */
    mm6 = MMX_PUNPCKLBW(mm6, mm4); /* MMX 0x0021F150: punpcklbw mm6, mm4 */
    mm6 = MMX_PSUBUSW(mm6, mm0); /* MMX 0x0021F153: psubusw mm6, mm0 */
    mm3 = MMX_PSLLW(mm3, 2u); /* MMX 0x0021F156: psllw mm3, 2 */
    mm3 = MMX_PMULHW(mm3, mm5); /* MMX 0x0021F15A: pmulhw mm3, mm5 */
    mm6 = MMX_PSLLW(mm6, 2u); /* MMX 0x0021F15D: psllw mm6, 2 */
    mm7 = ((uint64_t)MEM32((uint32_t)(0x25a7e8)) | ((uint64_t)MEM32((uint32_t)(0x25a7e8) + 4u) << 32)); /* MMX 0x0021F161: movq mm7, qword ptr [0x25a7e8] */
    mm6 = MMX_PMULHW(mm6, mm5); /* MMX 0x0021F168: pmulhw mm6, mm5 */
    edx = edx + 8;
    edi = edi + 0x40;
    mm3 = MMX_PADDSW(mm3, mm7); /* MMX 0x0021F171: paddsw mm3, mm7 */
    mm3 = MMX_PSUBUSW(mm3, mm7); /* MMX 0x0021F174: psubusw mm3, mm7 */
    mm6 = MMX_PADDSW(mm6, mm7); /* MMX 0x0021F177: paddsw mm6, mm7 */
    mm1 = mm3; /* MMX 0x0021F17A: movq mm1, mm3 */
    mm3 = MMX_PUNPCKLWD(mm3, mm3); /* MMX 0x0021F17D: punpcklwd mm3, mm3 */
    mm1 = MMX_PUNPCKHWD(mm1, mm1); /* MMX 0x0021F180: punpckhwd mm1, mm1 */
    mm3 = MMX_PMULLW(mm3, mm2); /* MMX 0x0021F183: pmullw mm3, mm2 */
    mm1 = MMX_PMULLW(mm1, mm2); /* MMX 0x0021F186: pmullw mm1, mm2 */
    mm6 = MMX_PSUBUSW(mm6, mm7); /* MMX 0x0021F189: psubusw mm6, mm7 */
    mm4 = mm6; /* MMX 0x0021F18C: movq mm4, mm6 */
    mm6 = MMX_PUNPCKLWD(mm6, mm6); /* MMX 0x0021F18F: punpcklwd mm6, mm6 */
    mm4 = MMX_PUNPCKHWD(mm4, mm4); /* MMX 0x0021F192: punpckhwd mm4, mm4 */
    mm6 = MMX_PMULLW(mm6, mm2); /* MMX 0x0021F195: pmullw mm6, mm2 */
    mm7 = mm3; /* MMX 0x0021F198: movq mm7, mm3 */
    mm3 = MMX_PUNPCKLDQ(mm3, mm3); /* MMX 0x0021F19B: punpckldq mm3, mm3 */
    mm7 = MMX_PUNPCKHDQ(mm7, mm7); /* MMX 0x0021F19E: punpckhdq mm7, mm7 */
    mm4 = MMX_PMULLW(mm4, mm2); /* MMX 0x0021F1A1: pmullw mm4, mm2 */
    MEM32((uint32_t)(edi - 0x40)) = (uint32_t)mm3; MEM32((uint32_t)(edi - 0x40) + 4u) = (uint32_t)(mm3 >> 32); /* MMX 0x0021F1A4: movq qword ptr [edi - 0x40], mm3 */
    mm3 = mm1; /* MMX 0x0021F1A8: movq mm3, mm1 */
    MEM32((uint32_t)(edi - 0x38)) = (uint32_t)mm7; MEM32((uint32_t)(edi - 0x38) + 4u) = (uint32_t)(mm7 >> 32); /* MMX 0x0021F1AB: movq qword ptr [edi - 0x38], mm7 */
    mm1 = MMX_PUNPCKLDQ(mm1, mm1); /* MMX 0x0021F1AF: punpckldq mm1, mm1 */
    mm3 = MMX_PUNPCKHDQ(mm3, mm3); /* MMX 0x0021F1B2: punpckhdq mm3, mm3 */
    mm7 = mm6; /* MMX 0x0021F1B5: movq mm7, mm6 */
    MEM32((uint32_t)(edi - 0x30)) = (uint32_t)mm1; MEM32((uint32_t)(edi - 0x30) + 4u) = (uint32_t)(mm1 >> 32); /* MMX 0x0021F1B8: movq qword ptr [edi - 0x30], mm1 */
    mm6 = MMX_PUNPCKLDQ(mm6, mm6); /* MMX 0x0021F1BC: punpckldq mm6, mm6 */
    MEM32((uint32_t)(edi - 0x28)) = (uint32_t)mm3; MEM32((uint32_t)(edi - 0x28) + 4u) = (uint32_t)(mm3 >> 32); /* MMX 0x0021F1BF: movq qword ptr [edi - 0x28], mm3 */
    mm7 = MMX_PUNPCKHDQ(mm7, mm7); /* MMX 0x0021F1C3: punpckhdq mm7, mm7 */
    MEM32((uint32_t)(edi - 0x20)) = (uint32_t)mm6; MEM32((uint32_t)(edi - 0x20) + 4u) = (uint32_t)(mm6 >> 32); /* MMX 0x0021F1C6: movq qword ptr [edi - 0x20], mm6 */
    mm3 = mm4; /* MMX 0x0021F1CA: movq mm3, mm4 */
    MEM32((uint32_t)(edi - 0x18)) = (uint32_t)mm7; MEM32((uint32_t)(edi - 0x18) + 4u) = (uint32_t)(mm7 >> 32); /* MMX 0x0021F1CD: movq qword ptr [edi - 0x18], mm7 */
    mm4 = MMX_PUNPCKLDQ(mm4, mm4); /* MMX 0x0021F1D1: punpckldq mm4, mm4 */
    mm3 = MMX_PUNPCKHDQ(mm3, mm3); /* MMX 0x0021F1D4: punpckhdq mm3, mm3 */
    _fa = (uint32_t)(edi) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edi, eax (32-bit) */
    MEM32((uint32_t)(edi - 0x10)) = (uint32_t)mm4; MEM32((uint32_t)(edi - 0x10) + 4u) = (uint32_t)(mm4 >> 32); /* MMX 0x0021F1D9: movq qword ptr [edi - 0x10], mm4 */
    MEM32((uint32_t)(edi - 8)) = (uint32_t)mm3; MEM32((uint32_t)(edi - 8) + 4u) = (uint32_t)(mm3 >> 32); /* MMX 0x0021F1DD: movq qword ptr [edi - 8], mm3 */
    if (CMP_B(_fa, _fb)) goto loc_0021F140; /* jb: below (unsigned <) */

loc_0021F1E7: ;
    MEM32(0x299F14) = edi;
    MEM32(0x299F1C) = edx;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebp);
    POP32(esp, ebx);
    esp += 8; return; /* ret 4 */

}


/**
 * sub_0021F200
 * Original: 0x0021F200 - 0x0021F479 (633 bytes, 161 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0021F200(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    uint64_t mm0, mm1, mm2, mm3, mm4, mm5, mm6, mm7;
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_0021F200: ;
    PUSH32(esp, ebx);
    PUSH32(esp, ebp);
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    edi = MEM32(0x299F10);
    edx = MEM32(0x299F18);
    ebp = MEM32(0x299F20);
    ebx = MEM32(0x299F24);
    eax = MEM32(esp + 0x14);
    eax = eax << 5;
    eax = eax + edi;
    MEM32(0x299F10) = eax;
    mm7 = ((uint64_t)MEM32((uint32_t)(0x25a7e8)) | ((uint64_t)MEM32((uint32_t)(0x25a7e8) + 4u) << 32)); /* MMX 0x0021F22A: movq mm7, qword ptr [0x25a7e8] */

loc_0021F231: ;
    mm4 = (uint64_t)(uint32_t)(MEM32((uint32_t)(edx))); /* MMX 0x0021F231: movd mm4, dword ptr [edx] */
    mm0 = MMX_PXOR(mm0, mm0); /* MMX 0x0021F234: pxor mm0, mm0 */
    eax = 0; /* xor self */
    edx = edx + 4;
    SET_LO8(eax, MEM8(ebp));
    mm4 = MMX_PUNPCKLBW(mm4, mm0); /* MMX 0x0021F23F: punpcklbw mm4, mm0 */
    mm2 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29b738))); /* MMX 0x0021F242: movd mm2, dword ptr [eax*4 + 0x29b738] */
    mm1 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29af38))); /* MMX 0x0021F24A: movd mm1, dword ptr [eax*4 + 0x29af38] */
    SET_LO8(eax, MEM8(ebp + 1));
    ebp = ebp + 2;
    mm4 = MMX_PSUBUSW(mm4, ((uint64_t)MEM32((uint32_t)(0x25a7d8)) | ((uint64_t)MEM32((uint32_t)(0x25a7d8) + 4u) << 32))); /* MMX 0x0021F258: psubusw mm4, qword ptr [0x25a7d8] */
    mm6 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29b738))); /* MMX 0x0021F25F: movd mm6, dword ptr [eax*4 + 0x29b738] */
    mm1 = MMX_PUNPCKLDQ(mm1, (uint64_t)MEM32((uint32_t)(eax*4 + 0x29af38))); /* MMX 0x0021F267: punpckldq mm1, dword ptr [eax*4 + 0x29af38] */
    SET_LO8(eax, MEM8(ebx));
    mm4 = MMX_PSLLW(mm4, 2u); /* MMX 0x0021F271: psllw mm4, 2 */
    mm4 = MMX_PMULHW(mm4, ((uint64_t)MEM32((uint32_t)(0x25a7e0)) | ((uint64_t)MEM32((uint32_t)(0x25a7e0) + 4u) << 32))); /* MMX 0x0021F275: pmulhw mm4, qword ptr [0x25a7e0] */
    mm5 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29b338))); /* MMX 0x0021F27C: movd mm5, dword ptr [eax*4 + 0x29b338] */
    mm3 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29bb38))); /* MMX 0x0021F284: movd mm3, dword ptr [eax*4 + 0x29bb38] */
    mm2 = MMX_PADDW(mm2, mm5); /* MMX 0x0021F28C: paddw mm2, mm5 */
    SET_LO8(eax, MEM8(ebx + 1));
    ebx = ebx + 2;
    mm5 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29b338))); /* MMX 0x0021F295: movd mm5, dword ptr [eax*4 + 0x29b338] */
    mm3 = MMX_PUNPCKLDQ(mm3, (uint64_t)MEM32((uint32_t)(eax*4 + 0x29bb38))); /* MMX 0x0021F29D: punpckldq mm3, dword ptr [eax*4 + 0x29bb38] */
    mm6 = MMX_PADDW(mm6, mm5); /* MMX 0x0021F2A5: paddw mm6, mm5 */
    mm2 = MMX_PUNPCKLDQ(mm2, mm6); /* MMX 0x0021F2A8: punpckldq mm2, mm6 */
    mm1 = MMX_PADDW(mm1, mm4); /* MMX 0x0021F2AB: paddw mm1, mm4 */
    mm2 = MMX_PADDW(mm2, mm4); /* MMX 0x0021F2AE: paddw mm2, mm4 */
    mm1 = MMX_PADDSW(mm1, mm7); /* MMX 0x0021F2B1: paddsw mm1, mm7 */
    mm3 = MMX_PADDW(mm3, mm4); /* MMX 0x0021F2B4: paddw mm3, mm4 */
    mm1 = MMX_PSUBUSW(mm1, mm7); /* MMX 0x0021F2B7: psubusw mm1, mm7 */
    mm2 = MMX_PADDSW(mm2, mm7); /* MMX 0x0021F2BA: paddsw mm2, mm7 */
    mm4 = mm1; /* MMX 0x0021F2BD: movq mm4, mm1 */
    mm2 = MMX_PSUBUSW(mm2, mm7); /* MMX 0x0021F2C0: psubusw mm2, mm7 */
    mm1 = MMX_PUNPCKLWD(mm1, mm0); /* MMX 0x0021F2C3: punpcklwd mm1, mm0 */
    mm5 = mm2; /* MMX 0x0021F2C6: movq mm5, mm2 */
    mm2 = MMX_PUNPCKLWD(mm2, mm0); /* MMX 0x0021F2C9: punpcklwd mm2, mm0 */
    mm3 = MMX_PADDSW(mm3, mm7); /* MMX 0x0021F2CC: paddsw mm3, mm7 */
    mm2 = MMX_PSLLD(mm2, 8u); /* MMX 0x0021F2CF: pslld mm2, 8 */
    mm3 = MMX_PSUBUSW(mm3, mm7); /* MMX 0x0021F2D3: psubusw mm3, mm7 */
    mm4 = MMX_PUNPCKHWD(mm4, mm0); /* MMX 0x0021F2D6: punpckhwd mm4, mm0 */
    mm6 = mm3; /* MMX 0x0021F2D9: movq mm6, mm3 */
    mm3 = MMX_PUNPCKLWD(mm3, mm0); /* MMX 0x0021F2DC: punpcklwd mm3, mm0 */
    mm3 = MMX_PSLLD(mm3, 0x10u); /* MMX 0x0021F2DF: pslld mm3, 0x10 */
    mm1 = MMX_POR(mm1, mm2); /* MMX 0x0021F2E3: por mm1, mm2 */
    mm1 = MMX_POR(mm1, mm3); /* MMX 0x0021F2E6: por mm1, mm3 */
    mm5 = MMX_PUNPCKHWD(mm5, mm0); /* MMX 0x0021F2E9: punpckhwd mm5, mm0 */
    mm3 = mm1; /* MMX 0x0021F2EC: movq mm3, mm1 */
    mm6 = MMX_PUNPCKHWD(mm6, mm0); /* MMX 0x0021F2EF: punpckhwd mm6, mm0 */
    mm5 = MMX_PSLLD(mm5, 8u); /* MMX 0x0021F2F2: pslld mm5, 8 */
    edi = edi + 0x20;
    mm1 = MMX_PUNPCKLDQ(mm1, mm1); /* MMX 0x0021F2F9: punpckldq mm1, mm1 */
    mm4 = MMX_POR(mm4, mm5); /* MMX 0x0021F2FC: por mm4, mm5 */
    mm3 = MMX_PUNPCKHDQ(mm3, mm3); /* MMX 0x0021F2FF: punpckhdq mm3, mm3 */
    MEM32((uint32_t)(edi - 0x20)) = (uint32_t)mm1; MEM32((uint32_t)(edi - 0x20) + 4u) = (uint32_t)(mm1 >> 32); /* MMX 0x0021F302: movq qword ptr [edi - 0x20], mm1 */
    mm6 = MMX_PSLLD(mm6, 0x10u); /* MMX 0x0021F306: pslld mm6, 0x10 */
    MEM32((uint32_t)(edi - 0x18)) = (uint32_t)mm3; MEM32((uint32_t)(edi - 0x18) + 4u) = (uint32_t)(mm3 >> 32); /* MMX 0x0021F30A: movq qword ptr [edi - 0x18], mm3 */
    mm4 = MMX_POR(mm4, mm6); /* MMX 0x0021F30E: por mm4, mm6 */
    mm6 = mm4; /* MMX 0x0021F311: movq mm6, mm4 */
    mm4 = MMX_PUNPCKLDQ(mm4, mm4); /* MMX 0x0021F314: punpckldq mm4, mm4 */
    mm6 = MMX_PUNPCKHDQ(mm6, mm6); /* MMX 0x0021F317: punpckhdq mm6, mm6 */
    eax = MEM32(0x299F10);
    MEM32((uint32_t)(edi - 0x10)) = (uint32_t)mm4; MEM32((uint32_t)(edi - 0x10) + 4u) = (uint32_t)(mm4 >> 32); /* MMX 0x0021F31F: movq qword ptr [edi - 0x10], mm4 */
    MEM32((uint32_t)(edi - 8)) = (uint32_t)mm6; MEM32((uint32_t)(edi - 8) + 4u) = (uint32_t)(mm6 >> 32); /* MMX 0x0021F323: movq qword ptr [edi - 8], mm6 */
    _fa = (uint32_t)(edi) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edi, eax (32-bit) */
    if (CMP_B(_fa, _fb)) goto loc_0021F231; /* jb: below (unsigned <) */

loc_0021F32F: ;
    MEM32(0x299F18) = edx;
    edi = MEM32(0x299F14);
    edx = MEM32(0x299F1C);
    ebp = MEM32(0x299F20);
    ebx = MEM32(0x299F24);
    eax = MEM32(esp + 0x14);
    eax = eax << 5;
    eax = eax + edi;
    MEM32(0x299F14) = eax;
    mm7 = ((uint64_t)MEM32((uint32_t)(0x25a7e8)) | ((uint64_t)MEM32((uint32_t)(0x25a7e8) + 4u) << 32)); /* MMX 0x0021F35B: movq mm7, qword ptr [0x25a7e8] */

loc_0021F362: ;
    mm4 = (uint64_t)(uint32_t)(MEM32((uint32_t)(edx))); /* MMX 0x0021F362: movd mm4, dword ptr [edx] */
    mm0 = MMX_PXOR(mm0, mm0); /* MMX 0x0021F365: pxor mm0, mm0 */
    eax = 0; /* xor self */
    edx = edx + 4;
    SET_LO8(eax, MEM8(ebp));
    mm4 = MMX_PUNPCKLBW(mm4, mm0); /* MMX 0x0021F370: punpcklbw mm4, mm0 */
    mm2 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29b738))); /* MMX 0x0021F373: movd mm2, dword ptr [eax*4 + 0x29b738] */
    mm1 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29af38))); /* MMX 0x0021F37B: movd mm1, dword ptr [eax*4 + 0x29af38] */
    SET_LO8(eax, MEM8(ebp + 1));
    ebp = ebp + 2;
    mm4 = MMX_PSUBUSW(mm4, ((uint64_t)MEM32((uint32_t)(0x25a7d8)) | ((uint64_t)MEM32((uint32_t)(0x25a7d8) + 4u) << 32))); /* MMX 0x0021F389: psubusw mm4, qword ptr [0x25a7d8] */
    mm6 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29b738))); /* MMX 0x0021F390: movd mm6, dword ptr [eax*4 + 0x29b738] */
    mm1 = MMX_PUNPCKLDQ(mm1, (uint64_t)MEM32((uint32_t)(eax*4 + 0x29af38))); /* MMX 0x0021F398: punpckldq mm1, dword ptr [eax*4 + 0x29af38] */
    SET_LO8(eax, MEM8(ebx));
    mm4 = MMX_PSLLW(mm4, 2u); /* MMX 0x0021F3A2: psllw mm4, 2 */
    mm4 = MMX_PMULHW(mm4, ((uint64_t)MEM32((uint32_t)(0x25a7e0)) | ((uint64_t)MEM32((uint32_t)(0x25a7e0) + 4u) << 32))); /* MMX 0x0021F3A6: pmulhw mm4, qword ptr [0x25a7e0] */
    mm5 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29b338))); /* MMX 0x0021F3AD: movd mm5, dword ptr [eax*4 + 0x29b338] */
    mm3 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29bb38))); /* MMX 0x0021F3B5: movd mm3, dword ptr [eax*4 + 0x29bb38] */
    mm2 = MMX_PADDW(mm2, mm5); /* MMX 0x0021F3BD: paddw mm2, mm5 */
    SET_LO8(eax, MEM8(ebx + 1));
    ebx = ebx + 2;
    mm5 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29b338))); /* MMX 0x0021F3C6: movd mm5, dword ptr [eax*4 + 0x29b338] */
    mm3 = MMX_PUNPCKLDQ(mm3, (uint64_t)MEM32((uint32_t)(eax*4 + 0x29bb38))); /* MMX 0x0021F3CE: punpckldq mm3, dword ptr [eax*4 + 0x29bb38] */
    mm6 = MMX_PADDW(mm6, mm5); /* MMX 0x0021F3D6: paddw mm6, mm5 */
    mm2 = MMX_PUNPCKLDQ(mm2, mm6); /* MMX 0x0021F3D9: punpckldq mm2, mm6 */
    mm1 = MMX_PADDW(mm1, mm4); /* MMX 0x0021F3DC: paddw mm1, mm4 */
    mm2 = MMX_PADDW(mm2, mm4); /* MMX 0x0021F3DF: paddw mm2, mm4 */
    mm1 = MMX_PADDSW(mm1, mm7); /* MMX 0x0021F3E2: paddsw mm1, mm7 */
    mm3 = MMX_PADDW(mm3, mm4); /* MMX 0x0021F3E5: paddw mm3, mm4 */
    mm1 = MMX_PSUBUSW(mm1, mm7); /* MMX 0x0021F3E8: psubusw mm1, mm7 */
    mm2 = MMX_PADDSW(mm2, mm7); /* MMX 0x0021F3EB: paddsw mm2, mm7 */
    mm4 = mm1; /* MMX 0x0021F3EE: movq mm4, mm1 */
    mm2 = MMX_PSUBUSW(mm2, mm7); /* MMX 0x0021F3F1: psubusw mm2, mm7 */
    mm1 = MMX_PUNPCKLWD(mm1, mm0); /* MMX 0x0021F3F4: punpcklwd mm1, mm0 */
    mm5 = mm2; /* MMX 0x0021F3F7: movq mm5, mm2 */
    mm2 = MMX_PUNPCKLWD(mm2, mm0); /* MMX 0x0021F3FA: punpcklwd mm2, mm0 */
    mm3 = MMX_PADDSW(mm3, mm7); /* MMX 0x0021F3FD: paddsw mm3, mm7 */
    mm2 = MMX_PSLLD(mm2, 8u); /* MMX 0x0021F400: pslld mm2, 8 */
    mm3 = MMX_PSUBUSW(mm3, mm7); /* MMX 0x0021F404: psubusw mm3, mm7 */
    mm4 = MMX_PUNPCKHWD(mm4, mm0); /* MMX 0x0021F407: punpckhwd mm4, mm0 */
    mm6 = mm3; /* MMX 0x0021F40A: movq mm6, mm3 */
    mm3 = MMX_PUNPCKLWD(mm3, mm0); /* MMX 0x0021F40D: punpcklwd mm3, mm0 */
    mm3 = MMX_PSLLD(mm3, 0x10u); /* MMX 0x0021F410: pslld mm3, 0x10 */
    mm1 = MMX_POR(mm1, mm2); /* MMX 0x0021F414: por mm1, mm2 */
    mm1 = MMX_POR(mm1, mm3); /* MMX 0x0021F417: por mm1, mm3 */
    mm5 = MMX_PUNPCKHWD(mm5, mm0); /* MMX 0x0021F41A: punpckhwd mm5, mm0 */
    mm3 = mm1; /* MMX 0x0021F41D: movq mm3, mm1 */
    mm6 = MMX_PUNPCKHWD(mm6, mm0); /* MMX 0x0021F420: punpckhwd mm6, mm0 */
    mm5 = MMX_PSLLD(mm5, 8u); /* MMX 0x0021F423: pslld mm5, 8 */
    edi = edi + 0x20;
    mm1 = MMX_PUNPCKLDQ(mm1, mm1); /* MMX 0x0021F42A: punpckldq mm1, mm1 */
    mm4 = MMX_POR(mm4, mm5); /* MMX 0x0021F42D: por mm4, mm5 */
    mm3 = MMX_PUNPCKHDQ(mm3, mm3); /* MMX 0x0021F430: punpckhdq mm3, mm3 */
    MEM32((uint32_t)(edi - 0x20)) = (uint32_t)mm1; MEM32((uint32_t)(edi - 0x20) + 4u) = (uint32_t)(mm1 >> 32); /* MMX 0x0021F433: movq qword ptr [edi - 0x20], mm1 */
    mm6 = MMX_PSLLD(mm6, 0x10u); /* MMX 0x0021F437: pslld mm6, 0x10 */
    MEM32((uint32_t)(edi - 0x18)) = (uint32_t)mm3; MEM32((uint32_t)(edi - 0x18) + 4u) = (uint32_t)(mm3 >> 32); /* MMX 0x0021F43B: movq qword ptr [edi - 0x18], mm3 */
    mm4 = MMX_POR(mm4, mm6); /* MMX 0x0021F43F: por mm4, mm6 */
    mm6 = mm4; /* MMX 0x0021F442: movq mm6, mm4 */
    mm4 = MMX_PUNPCKLDQ(mm4, mm4); /* MMX 0x0021F445: punpckldq mm4, mm4 */
    mm6 = MMX_PUNPCKHDQ(mm6, mm6); /* MMX 0x0021F448: punpckhdq mm6, mm6 */
    eax = MEM32(0x299F14);
    MEM32((uint32_t)(edi - 0x10)) = (uint32_t)mm4; MEM32((uint32_t)(edi - 0x10) + 4u) = (uint32_t)(mm4 >> 32); /* MMX 0x0021F450: movq qword ptr [edi - 0x10], mm4 */
    MEM32((uint32_t)(edi - 8)) = (uint32_t)mm6; MEM32((uint32_t)(edi - 8) + 4u) = (uint32_t)(mm6 >> 32); /* MMX 0x0021F454: movq qword ptr [edi - 8], mm6 */
    _fa = (uint32_t)(edi) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edi, eax (32-bit) */
    if (CMP_B(_fa, _fb)) goto loc_0021F362; /* jb: below (unsigned <) */

loc_0021F460: ;
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
 * sub_0021F480
 * Original: 0x0021F480 - 0x0021F78B (779 bytes, 193 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0021F480(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    uint64_t mm0, mm1, mm2, mm3, mm4, mm5, mm6, mm7;
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_0021F480: ;
    PUSH32(esp, ebx);
    PUSH32(esp, ebp);
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    edi = MEM32(0x299F10);
    edx = MEM32(0x299F18);
    ebp = MEM32(0x299F20);
    ebx = MEM32(0x299F24);
    eax = MEM32(esp + 0x14);
    eax = eax << 5;
    eax = eax + edi;
    MEM32(0x299F10) = eax;
    mm7 = ((uint64_t)MEM32((uint32_t)(0x25a7e8)) | ((uint64_t)MEM32((uint32_t)(0x25a7e8) + 4u) << 32)); /* MMX 0x0021F4AA: movq mm7, qword ptr [0x25a7e8] */

loc_0021F4B1: ;
    mm4 = (uint64_t)(uint32_t)(MEM32((uint32_t)(edx))); /* MMX 0x0021F4B1: movd mm4, dword ptr [edx] */
    mm0 = MMX_PXOR(mm0, mm0); /* MMX 0x0021F4B4: pxor mm0, mm0 */
    eax = 0; /* xor self */
    edx = edx + 4;
    SET_LO8(eax, MEM8(ebp));
    mm4 = MMX_PUNPCKLBW(mm4, mm0); /* MMX 0x0021F4BF: punpcklbw mm4, mm0 */
    mm2 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29b738))); /* MMX 0x0021F4C2: movd mm2, dword ptr [eax*4 + 0x29b738] */
    mm1 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29af38))); /* MMX 0x0021F4CA: movd mm1, dword ptr [eax*4 + 0x29af38] */
    SET_LO8(eax, MEM8(ebp + 1));
    ebp = ebp + 2;
    mm4 = MMX_PSUBUSW(mm4, ((uint64_t)MEM32((uint32_t)(0x25a7d8)) | ((uint64_t)MEM32((uint32_t)(0x25a7d8) + 4u) << 32))); /* MMX 0x0021F4D8: psubusw mm4, qword ptr [0x25a7d8] */
    mm6 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29b738))); /* MMX 0x0021F4DF: movd mm6, dword ptr [eax*4 + 0x29b738] */
    mm1 = MMX_PUNPCKLDQ(mm1, (uint64_t)MEM32((uint32_t)(eax*4 + 0x29af38))); /* MMX 0x0021F4E7: punpckldq mm1, dword ptr [eax*4 + 0x29af38] */
    SET_LO8(eax, MEM8(ebx));
    mm4 = MMX_PSLLW(mm4, 2u); /* MMX 0x0021F4F1: psllw mm4, 2 */
    mm4 = MMX_PMULHW(mm4, ((uint64_t)MEM32((uint32_t)(0x25a7e0)) | ((uint64_t)MEM32((uint32_t)(0x25a7e0) + 4u) << 32))); /* MMX 0x0021F4F5: pmulhw mm4, qword ptr [0x25a7e0] */
    mm5 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29b338))); /* MMX 0x0021F4FC: movd mm5, dword ptr [eax*4 + 0x29b338] */
    mm3 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29bb38))); /* MMX 0x0021F504: movd mm3, dword ptr [eax*4 + 0x29bb38] */
    mm2 = MMX_PADDW(mm2, mm5); /* MMX 0x0021F50C: paddw mm2, mm5 */
    SET_LO8(eax, MEM8(ebx + 1));
    ebx = ebx + 2;
    mm5 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29b338))); /* MMX 0x0021F515: movd mm5, dword ptr [eax*4 + 0x29b338] */
    mm3 = MMX_PUNPCKLDQ(mm3, (uint64_t)MEM32((uint32_t)(eax*4 + 0x29bb38))); /* MMX 0x0021F51D: punpckldq mm3, dword ptr [eax*4 + 0x29bb38] */
    mm6 = MMX_PADDW(mm6, mm5); /* MMX 0x0021F525: paddw mm6, mm5 */
    SET_LO8(eax, MEM8(ebp));
    mm2 = MMX_PUNPCKLDQ(mm2, mm6); /* MMX 0x0021F52B: punpckldq mm2, mm6 */
    mm1 = MMX_PSRLQ(mm1, 0x10u); /* MMX 0x0021F52E: psrlq mm1, 0x10 */
    mm6 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29af38))); /* MMX 0x0021F532: movd mm6, dword ptr [eax*4 + 0x29af38] */
    mm2 = MMX_PSRLQ(mm2, 0x10u); /* MMX 0x0021F53A: psrlq mm2, 0x10 */
    mm5 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29b738))); /* MMX 0x0021F53E: movd mm5, dword ptr [eax*4 + 0x29b738] */
    mm3 = MMX_PSRLQ(mm3, 0x10u); /* MMX 0x0021F546: psrlq mm3, 0x10 */
    SET_LO8(eax, MEM8(ebx));
    mm6 = MMX_PSLLQ(mm6, 0x30u); /* MMX 0x0021F54C: psllq mm6, 0x30 */
    mm1 = MMX_POR(mm1, mm6); /* MMX 0x0021F550: por mm1, mm6 */
    mm6 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29b338))); /* MMX 0x0021F553: movd mm6, dword ptr [eax*4 + 0x29b338] */
    mm5 = MMX_PADDW(mm5, mm6); /* MMX 0x0021F55B: paddw mm5, mm6 */
    mm6 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29bb38))); /* MMX 0x0021F55E: movd mm6, dword ptr [eax*4 + 0x29bb38] */
    mm5 = MMX_PSLLQ(mm5, 0x30u); /* MMX 0x0021F566: psllq mm5, 0x30 */
    mm6 = MMX_PSLLQ(mm6, 0x30u); /* MMX 0x0021F56A: psllq mm6, 0x30 */
    mm2 = MMX_POR(mm2, mm5); /* MMX 0x0021F56E: por mm2, mm5 */
    mm3 = MMX_POR(mm3, mm6); /* MMX 0x0021F571: por mm3, mm6 */
    mm1 = MMX_PADDW(mm1, mm4); /* MMX 0x0021F574: paddw mm1, mm4 */
    mm2 = MMX_PADDW(mm2, mm4); /* MMX 0x0021F577: paddw mm2, mm4 */
    mm1 = MMX_PADDSW(mm1, mm7); /* MMX 0x0021F57A: paddsw mm1, mm7 */
    mm3 = MMX_PADDW(mm3, mm4); /* MMX 0x0021F57D: paddw mm3, mm4 */
    mm1 = MMX_PSUBUSW(mm1, mm7); /* MMX 0x0021F580: psubusw mm1, mm7 */
    mm2 = MMX_PADDSW(mm2, mm7); /* MMX 0x0021F583: paddsw mm2, mm7 */
    mm4 = mm1; /* MMX 0x0021F586: movq mm4, mm1 */
    mm2 = MMX_PSUBUSW(mm2, mm7); /* MMX 0x0021F589: psubusw mm2, mm7 */
    mm1 = MMX_PUNPCKLWD(mm1, mm0); /* MMX 0x0021F58C: punpcklwd mm1, mm0 */
    mm5 = mm2; /* MMX 0x0021F58F: movq mm5, mm2 */
    mm2 = MMX_PUNPCKLWD(mm2, mm0); /* MMX 0x0021F592: punpcklwd mm2, mm0 */
    mm3 = MMX_PADDSW(mm3, mm7); /* MMX 0x0021F595: paddsw mm3, mm7 */
    mm2 = MMX_PSLLD(mm2, 8u); /* MMX 0x0021F598: pslld mm2, 8 */
    mm3 = MMX_PSUBUSW(mm3, mm7); /* MMX 0x0021F59C: psubusw mm3, mm7 */
    mm4 = MMX_PUNPCKHWD(mm4, mm0); /* MMX 0x0021F59F: punpckhwd mm4, mm0 */
    mm6 = mm3; /* MMX 0x0021F5A2: movq mm6, mm3 */
    mm3 = MMX_PUNPCKLWD(mm3, mm0); /* MMX 0x0021F5A5: punpcklwd mm3, mm0 */
    mm3 = MMX_PSLLD(mm3, 0x10u); /* MMX 0x0021F5A8: pslld mm3, 0x10 */
    mm1 = MMX_POR(mm1, mm2); /* MMX 0x0021F5AC: por mm1, mm2 */
    mm1 = MMX_POR(mm1, mm3); /* MMX 0x0021F5AF: por mm1, mm3 */
    mm5 = MMX_PUNPCKHWD(mm5, mm0); /* MMX 0x0021F5B2: punpckhwd mm5, mm0 */
    mm3 = mm1; /* MMX 0x0021F5B5: movq mm3, mm1 */
    mm6 = MMX_PUNPCKHWD(mm6, mm0); /* MMX 0x0021F5B8: punpckhwd mm6, mm0 */
    mm5 = MMX_PSLLD(mm5, 8u); /* MMX 0x0021F5BB: pslld mm5, 8 */
    edi = edi + 0x20;
    mm1 = MMX_PUNPCKLDQ(mm1, mm1); /* MMX 0x0021F5C2: punpckldq mm1, mm1 */
    mm4 = MMX_POR(mm4, mm5); /* MMX 0x0021F5C5: por mm4, mm5 */
    mm3 = MMX_PUNPCKHDQ(mm3, mm3); /* MMX 0x0021F5C8: punpckhdq mm3, mm3 */
    MEM32((uint32_t)(edi - 0x20)) = (uint32_t)mm1; MEM32((uint32_t)(edi - 0x20) + 4u) = (uint32_t)(mm1 >> 32); /* MMX 0x0021F5CB: movq qword ptr [edi - 0x20], mm1 */
    mm6 = MMX_PSLLD(mm6, 0x10u); /* MMX 0x0021F5CF: pslld mm6, 0x10 */
    MEM32((uint32_t)(edi - 0x18)) = (uint32_t)mm3; MEM32((uint32_t)(edi - 0x18) + 4u) = (uint32_t)(mm3 >> 32); /* MMX 0x0021F5D3: movq qword ptr [edi - 0x18], mm3 */
    mm4 = MMX_POR(mm4, mm6); /* MMX 0x0021F5D7: por mm4, mm6 */
    mm6 = mm4; /* MMX 0x0021F5DA: movq mm6, mm4 */
    mm4 = MMX_PUNPCKLDQ(mm4, mm4); /* MMX 0x0021F5DD: punpckldq mm4, mm4 */
    mm6 = MMX_PUNPCKHDQ(mm6, mm6); /* MMX 0x0021F5E0: punpckhdq mm6, mm6 */
    eax = MEM32(0x299F10);
    MEM32((uint32_t)(edi - 0x10)) = (uint32_t)mm4; MEM32((uint32_t)(edi - 0x10) + 4u) = (uint32_t)(mm4 >> 32); /* MMX 0x0021F5E8: movq qword ptr [edi - 0x10], mm4 */
    MEM32((uint32_t)(edi - 8)) = (uint32_t)mm6; MEM32((uint32_t)(edi - 8) + 4u) = (uint32_t)(mm6 >> 32); /* MMX 0x0021F5EC: movq qword ptr [edi - 8], mm6 */
    _fa = (uint32_t)(edi) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edi, eax (32-bit) */
    if (CMP_B(_fa, _fb)) goto loc_0021F4B1; /* jb: below (unsigned <) */

loc_0021F5F8: ;
    MEM32(0x299F18) = edx;
    edi = MEM32(0x299F14);
    edx = MEM32(0x299F1C);
    ebp = MEM32(0x299F20);
    ebx = MEM32(0x299F24);
    eax = MEM32(esp + 0x14);
    eax = eax << 5;
    eax = eax + edi;
    MEM32(0x299F14) = eax;
    mm7 = ((uint64_t)MEM32((uint32_t)(0x25a7e8)) | ((uint64_t)MEM32((uint32_t)(0x25a7e8) + 4u) << 32)); /* MMX 0x0021F624: movq mm7, qword ptr [0x25a7e8] */

loc_0021F62B: ;
    mm4 = (uint64_t)(uint32_t)(MEM32((uint32_t)(edx))); /* MMX 0x0021F62B: movd mm4, dword ptr [edx] */
    mm0 = MMX_PXOR(mm0, mm0); /* MMX 0x0021F62E: pxor mm0, mm0 */
    eax = 0; /* xor self */
    edx = edx + 4;
    SET_LO8(eax, MEM8(ebp));
    mm4 = MMX_PUNPCKLBW(mm4, mm0); /* MMX 0x0021F639: punpcklbw mm4, mm0 */
    mm2 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29b738))); /* MMX 0x0021F63C: movd mm2, dword ptr [eax*4 + 0x29b738] */
    mm1 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29af38))); /* MMX 0x0021F644: movd mm1, dword ptr [eax*4 + 0x29af38] */
    SET_LO8(eax, MEM8(ebp + 1));
    ebp = ebp + 2;
    mm4 = MMX_PSUBUSW(mm4, ((uint64_t)MEM32((uint32_t)(0x25a7d8)) | ((uint64_t)MEM32((uint32_t)(0x25a7d8) + 4u) << 32))); /* MMX 0x0021F652: psubusw mm4, qword ptr [0x25a7d8] */
    mm6 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29b738))); /* MMX 0x0021F659: movd mm6, dword ptr [eax*4 + 0x29b738] */
    mm1 = MMX_PUNPCKLDQ(mm1, (uint64_t)MEM32((uint32_t)(eax*4 + 0x29af38))); /* MMX 0x0021F661: punpckldq mm1, dword ptr [eax*4 + 0x29af38] */
    SET_LO8(eax, MEM8(ebx));
    mm4 = MMX_PSLLW(mm4, 2u); /* MMX 0x0021F66B: psllw mm4, 2 */
    mm4 = MMX_PMULHW(mm4, ((uint64_t)MEM32((uint32_t)(0x25a7e0)) | ((uint64_t)MEM32((uint32_t)(0x25a7e0) + 4u) << 32))); /* MMX 0x0021F66F: pmulhw mm4, qword ptr [0x25a7e0] */
    mm5 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29b338))); /* MMX 0x0021F676: movd mm5, dword ptr [eax*4 + 0x29b338] */
    mm3 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29bb38))); /* MMX 0x0021F67E: movd mm3, dword ptr [eax*4 + 0x29bb38] */
    mm2 = MMX_PADDW(mm2, mm5); /* MMX 0x0021F686: paddw mm2, mm5 */
    SET_LO8(eax, MEM8(ebx + 1));
    ebx = ebx + 2;
    mm5 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29b338))); /* MMX 0x0021F68F: movd mm5, dword ptr [eax*4 + 0x29b338] */
    mm3 = MMX_PUNPCKLDQ(mm3, (uint64_t)MEM32((uint32_t)(eax*4 + 0x29bb38))); /* MMX 0x0021F697: punpckldq mm3, dword ptr [eax*4 + 0x29bb38] */
    mm6 = MMX_PADDW(mm6, mm5); /* MMX 0x0021F69F: paddw mm6, mm5 */
    SET_LO8(eax, MEM8(ebp));
    mm2 = MMX_PUNPCKLDQ(mm2, mm6); /* MMX 0x0021F6A5: punpckldq mm2, mm6 */
    mm1 = MMX_PSRLQ(mm1, 0x10u); /* MMX 0x0021F6A8: psrlq mm1, 0x10 */
    mm6 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29af38))); /* MMX 0x0021F6AC: movd mm6, dword ptr [eax*4 + 0x29af38] */
    mm2 = MMX_PSRLQ(mm2, 0x10u); /* MMX 0x0021F6B4: psrlq mm2, 0x10 */
    mm5 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29b738))); /* MMX 0x0021F6B8: movd mm5, dword ptr [eax*4 + 0x29b738] */
    mm3 = MMX_PSRLQ(mm3, 0x10u); /* MMX 0x0021F6C0: psrlq mm3, 0x10 */
    SET_LO8(eax, MEM8(ebx));
    mm6 = MMX_PSLLQ(mm6, 0x30u); /* MMX 0x0021F6C6: psllq mm6, 0x30 */
    mm1 = MMX_POR(mm1, mm6); /* MMX 0x0021F6CA: por mm1, mm6 */
    mm6 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29b338))); /* MMX 0x0021F6CD: movd mm6, dword ptr [eax*4 + 0x29b338] */
    mm5 = MMX_PADDW(mm5, mm6); /* MMX 0x0021F6D5: paddw mm5, mm6 */
    mm6 = (uint64_t)(uint32_t)(MEM32((uint32_t)(eax*4 + 0x29bb38))); /* MMX 0x0021F6D8: movd mm6, dword ptr [eax*4 + 0x29bb38] */
    mm5 = MMX_PSLLQ(mm5, 0x30u); /* MMX 0x0021F6E0: psllq mm5, 0x30 */
    mm6 = MMX_PSLLQ(mm6, 0x30u); /* MMX 0x0021F6E4: psllq mm6, 0x30 */
    mm2 = MMX_POR(mm2, mm5); /* MMX 0x0021F6E8: por mm2, mm5 */
    mm3 = MMX_POR(mm3, mm6); /* MMX 0x0021F6EB: por mm3, mm6 */
    mm1 = MMX_PADDW(mm1, mm4); /* MMX 0x0021F6EE: paddw mm1, mm4 */
    mm2 = MMX_PADDW(mm2, mm4); /* MMX 0x0021F6F1: paddw mm2, mm4 */
    mm1 = MMX_PADDSW(mm1, mm7); /* MMX 0x0021F6F4: paddsw mm1, mm7 */
    mm3 = MMX_PADDW(mm3, mm4); /* MMX 0x0021F6F7: paddw mm3, mm4 */
    mm1 = MMX_PSUBUSW(mm1, mm7); /* MMX 0x0021F6FA: psubusw mm1, mm7 */
    mm2 = MMX_PADDSW(mm2, mm7); /* MMX 0x0021F6FD: paddsw mm2, mm7 */
    mm4 = mm1; /* MMX 0x0021F700: movq mm4, mm1 */
    mm2 = MMX_PSUBUSW(mm2, mm7); /* MMX 0x0021F703: psubusw mm2, mm7 */
    mm1 = MMX_PUNPCKLWD(mm1, mm0); /* MMX 0x0021F706: punpcklwd mm1, mm0 */
    mm5 = mm2; /* MMX 0x0021F709: movq mm5, mm2 */
    mm2 = MMX_PUNPCKLWD(mm2, mm0); /* MMX 0x0021F70C: punpcklwd mm2, mm0 */
    mm3 = MMX_PADDSW(mm3, mm7); /* MMX 0x0021F70F: paddsw mm3, mm7 */
    mm2 = MMX_PSLLD(mm2, 8u); /* MMX 0x0021F712: pslld mm2, 8 */
    mm3 = MMX_PSUBUSW(mm3, mm7); /* MMX 0x0021F716: psubusw mm3, mm7 */
    mm4 = MMX_PUNPCKHWD(mm4, mm0); /* MMX 0x0021F719: punpckhwd mm4, mm0 */
    mm6 = mm3; /* MMX 0x0021F71C: movq mm6, mm3 */
    mm3 = MMX_PUNPCKLWD(mm3, mm0); /* MMX 0x0021F71F: punpcklwd mm3, mm0 */
    mm3 = MMX_PSLLD(mm3, 0x10u); /* MMX 0x0021F722: pslld mm3, 0x10 */
    mm1 = MMX_POR(mm1, mm2); /* MMX 0x0021F726: por mm1, mm2 */
    mm1 = MMX_POR(mm1, mm3); /* MMX 0x0021F729: por mm1, mm3 */
    mm5 = MMX_PUNPCKHWD(mm5, mm0); /* MMX 0x0021F72C: punpckhwd mm5, mm0 */
    mm3 = mm1; /* MMX 0x0021F72F: movq mm3, mm1 */
    mm6 = MMX_PUNPCKHWD(mm6, mm0); /* MMX 0x0021F732: punpckhwd mm6, mm0 */
    mm5 = MMX_PSLLD(mm5, 8u); /* MMX 0x0021F735: pslld mm5, 8 */
    edi = edi + 0x20;
    mm1 = MMX_PUNPCKLDQ(mm1, mm1); /* MMX 0x0021F73C: punpckldq mm1, mm1 */
    mm4 = MMX_POR(mm4, mm5); /* MMX 0x0021F73F: por mm4, mm5 */
    mm3 = MMX_PUNPCKHDQ(mm3, mm3); /* MMX 0x0021F742: punpckhdq mm3, mm3 */
    MEM32((uint32_t)(edi - 0x20)) = (uint32_t)mm1; MEM32((uint32_t)(edi - 0x20) + 4u) = (uint32_t)(mm1 >> 32); /* MMX 0x0021F745: movq qword ptr [edi - 0x20], mm1 */
    mm6 = MMX_PSLLD(mm6, 0x10u); /* MMX 0x0021F749: pslld mm6, 0x10 */
    MEM32((uint32_t)(edi - 0x18)) = (uint32_t)mm3; MEM32((uint32_t)(edi - 0x18) + 4u) = (uint32_t)(mm3 >> 32); /* MMX 0x0021F74D: movq qword ptr [edi - 0x18], mm3 */
    mm4 = MMX_POR(mm4, mm6); /* MMX 0x0021F751: por mm4, mm6 */
    mm6 = mm4; /* MMX 0x0021F754: movq mm6, mm4 */
    mm4 = MMX_PUNPCKLDQ(mm4, mm4); /* MMX 0x0021F757: punpckldq mm4, mm4 */
    mm6 = MMX_PUNPCKHDQ(mm6, mm6); /* MMX 0x0021F75A: punpckhdq mm6, mm6 */
    eax = MEM32(0x299F14);
    MEM32((uint32_t)(edi - 0x10)) = (uint32_t)mm4; MEM32((uint32_t)(edi - 0x10) + 4u) = (uint32_t)(mm4 >> 32); /* MMX 0x0021F762: movq qword ptr [edi - 0x10], mm4 */
    MEM32((uint32_t)(edi - 8)) = (uint32_t)mm6; MEM32((uint32_t)(edi - 8) + 4u) = (uint32_t)(mm6 >> 32); /* MMX 0x0021F766: movq qword ptr [edi - 8], mm6 */
    _fa = (uint32_t)(edi) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edi, eax (32-bit) */
    if (CMP_B(_fa, _fb)) goto loc_0021F62B; /* jb: below (unsigned <) */

loc_0021F772: ;
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
 * sub_0021F7A0
 * Original: 0x0021F7A0 - 0x0021F8EC (332 bytes, 98 insns)
 * CC: cdecl, 0 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_0021F7A0(void)
{
    uint32_t ebp;
    ebp = g_ebp;  /* frameless: caller's frame */
    int _flags = 0; /* fallback flag var */
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_fa; (void)_fb; (void)_fas; (void)_fbs;
    uint64_t mm0, mm1, mm2, mm3, mm4, mm5, mm6, mm7;
    ebp = g_seh_ebp; /* fpo_leaf: inherit caller's frame */

loc_0021F7A0: ;
    PUSH32(esp, ebx);
    PUSH32(esp, ebp);
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    mm7 = ((uint64_t)MEM32((uint32_t)(0x25a7e8)) | ((uint64_t)MEM32((uint32_t)(0x25a7e8) + 4u) << 32)); /* MMX 0x0021F7A4: movq mm7, qword ptr [0x25a7e8] */
    mm0 = ((uint64_t)MEM32((uint32_t)(0x25a7d8)) | ((uint64_t)MEM32((uint32_t)(0x25a7d8) + 4u) << 32)); /* MMX 0x0021F7AB: movq mm0, qword ptr [0x25a7d8] */
    mm2 = ((uint64_t)MEM32((uint32_t)(0x25a7c0)) | ((uint64_t)MEM32((uint32_t)(0x25a7c0) + 4u) << 32)); /* MMX 0x0021F7B2: movq mm2, qword ptr [0x25a7c0] */
    mm5 = ((uint64_t)MEM32((uint32_t)(0x25a7e0)) | ((uint64_t)MEM32((uint32_t)(0x25a7e0) + 4u) << 32)); /* MMX 0x0021F7B9: movq mm5, qword ptr [0x25a7e0] */
    esi = MEM32(0x299F10);
    ecx = MEM32(0x299F18);
    eax = MEM32(esp + 0x14);
    eax = eax << 4;
    eax = eax + esi;
    /* nop */
    /* nop */

loc_0021F7E0: ;
    mm3 = (uint64_t)(uint32_t)(MEM32((uint32_t)(ecx))); /* MMX 0x0021F7E0: movd mm3, dword ptr [ecx] */
    mm4 = MMX_PXOR(mm4, mm4); /* MMX 0x0021F7E3: pxor mm4, mm4 */
    mm6 = (uint64_t)(uint32_t)(MEM32((uint32_t)(ecx + 4))); /* MMX 0x0021F7E6: movd mm6, dword ptr [ecx + 4] */
    mm3 = MMX_PUNPCKLBW(mm3, mm4); /* MMX 0x0021F7EA: punpcklbw mm3, mm4 */
    mm3 = MMX_PSUBUSW(mm3, mm0); /* MMX 0x0021F7ED: psubusw mm3, mm0 */
    mm6 = MMX_PUNPCKLBW(mm6, mm4); /* MMX 0x0021F7F0: punpcklbw mm6, mm4 */
    mm6 = MMX_PSUBUSW(mm6, mm0); /* MMX 0x0021F7F3: psubusw mm6, mm0 */
    mm3 = MMX_PSLLW(mm3, 2u); /* MMX 0x0021F7F6: psllw mm3, 2 */
    mm3 = MMX_PMULHW(mm3, mm5); /* MMX 0x0021F7FA: pmulhw mm3, mm5 */
    mm6 = MMX_PSLLW(mm6, 2u); /* MMX 0x0021F7FD: psllw mm6, 2 */
    mm6 = MMX_PMULHW(mm6, mm5); /* MMX 0x0021F801: pmulhw mm6, mm5 */
    /* nop */
    ecx = ecx + 8;
    esi = esi + 0x20;
    mm3 = MMX_PADDSW(mm3, mm7); /* MMX 0x0021F80B: paddsw mm3, mm7 */
    mm3 = MMX_PSUBUSW(mm3, mm7); /* MMX 0x0021F80E: psubusw mm3, mm7 */
    mm6 = MMX_PADDSW(mm6, mm7); /* MMX 0x0021F811: paddsw mm6, mm7 */
    mm1 = mm3; /* MMX 0x0021F814: movq mm1, mm3 */
    mm3 = MMX_PUNPCKLWD(mm3, mm3); /* MMX 0x0021F817: punpcklwd mm3, mm3 */
    mm1 = MMX_PUNPCKHWD(mm1, mm1); /* MMX 0x0021F81A: punpckhwd mm1, mm1 */
    mm3 = MMX_PMULLW(mm3, mm2); /* MMX 0x0021F81D: pmullw mm3, mm2 */
    mm1 = MMX_PMULLW(mm1, mm2); /* MMX 0x0021F820: pmullw mm1, mm2 */
    mm6 = MMX_PSUBUSW(mm6, mm7); /* MMX 0x0021F823: psubusw mm6, mm7 */
    mm4 = mm6; /* MMX 0x0021F826: movq mm4, mm6 */
    mm6 = MMX_PUNPCKLWD(mm6, mm6); /* MMX 0x0021F829: punpcklwd mm6, mm6 */
    mm4 = MMX_PUNPCKHWD(mm4, mm4); /* MMX 0x0021F82C: punpckhwd mm4, mm4 */
    mm6 = MMX_PMULLW(mm6, mm2); /* MMX 0x0021F82F: pmullw mm6, mm2 */
    MEM32((uint32_t)(esi - 0x20)) = (uint32_t)mm3; MEM32((uint32_t)(esi - 0x20) + 4u) = (uint32_t)(mm3 >> 32); /* MMX 0x0021F832: movq qword ptr [esi - 0x20], mm3 */
    mm4 = MMX_PMULLW(mm4, mm2); /* MMX 0x0021F836: pmullw mm4, mm2 */
    MEM32((uint32_t)(esi - 0x18)) = (uint32_t)mm1; MEM32((uint32_t)(esi - 0x18) + 4u) = (uint32_t)(mm1 >> 32); /* MMX 0x0021F839: movq qword ptr [esi - 0x18], mm1 */
    MEM32((uint32_t)(esi - 0x10)) = (uint32_t)mm6; MEM32((uint32_t)(esi - 0x10) + 4u) = (uint32_t)(mm6 >> 32); /* MMX 0x0021F83D: movq qword ptr [esi - 0x10], mm6 */
    MEM32((uint32_t)(esi - 8)) = (uint32_t)mm4; MEM32((uint32_t)(esi - 8) + 4u) = (uint32_t)(mm4 >> 32); /* MMX 0x0021F841: movq qword ptr [esi - 8], mm4 */
    _fa = (uint32_t)(esi) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp esi, eax (32-bit) */
    if (CMP_B(_fa, _fb)) goto loc_0021F7E0; /* jb: below (unsigned <) */

loc_0021F849: ;
    MEM32(0x299F10) = esi;
    MEM32(0x299F18) = ecx;
    edi = MEM32(0x299F14);
    edx = MEM32(0x299F1C);
    eax = MEM32(esp + 0x14);
    eax = eax << 4;
    eax = eax + edi;
    /* nop */

loc_0021F870: ;
    mm3 = (uint64_t)(uint32_t)(MEM32((uint32_t)(edx))); /* MMX 0x0021F870: movd mm3, dword ptr [edx] */
    mm4 = MMX_PXOR(mm4, mm4); /* MMX 0x0021F873: pxor mm4, mm4 */
    mm6 = (uint64_t)(uint32_t)(MEM32((uint32_t)(edx + 4))); /* MMX 0x0021F876: movd mm6, dword ptr [edx + 4] */
    mm3 = MMX_PUNPCKLBW(mm3, mm4); /* MMX 0x0021F87A: punpcklbw mm3, mm4 */
    mm3 = MMX_PSUBUSW(mm3, mm0); /* MMX 0x0021F87D: psubusw mm3, mm0 */
    mm6 = MMX_PUNPCKLBW(mm6, mm4); /* MMX 0x0021F880: punpcklbw mm6, mm4 */
    mm6 = MMX_PSUBUSW(mm6, mm0); /* MMX 0x0021F883: psubusw mm6, mm0 */
    mm3 = MMX_PSLLW(mm3, 2u); /* MMX 0x0021F886: psllw mm3, 2 */
    mm3 = MMX_PMULHW(mm3, mm5); /* MMX 0x0021F88A: pmulhw mm3, mm5 */
    mm6 = MMX_PSLLW(mm6, 2u); /* MMX 0x0021F88D: psllw mm6, 2 */
    mm6 = MMX_PMULHW(mm6, mm5); /* MMX 0x0021F891: pmulhw mm6, mm5 */
    /* nop */
    edx = edx + 8;
    edi = edi + 0x20;
    mm3 = MMX_PADDSW(mm3, mm7); /* MMX 0x0021F89B: paddsw mm3, mm7 */
    mm3 = MMX_PSUBUSW(mm3, mm7); /* MMX 0x0021F89E: psubusw mm3, mm7 */
    mm6 = MMX_PADDSW(mm6, mm7); /* MMX 0x0021F8A1: paddsw mm6, mm7 */
    mm1 = mm3; /* MMX 0x0021F8A4: movq mm1, mm3 */
    mm3 = MMX_PUNPCKLWD(mm3, mm3); /* MMX 0x0021F8A7: punpcklwd mm3, mm3 */
    mm1 = MMX_PUNPCKHWD(mm1, mm1); /* MMX 0x0021F8AA: punpckhwd mm1, mm1 */
    mm3 = MMX_PMULLW(mm3, mm2); /* MMX 0x0021F8AD: pmullw mm3, mm2 */
    mm1 = MMX_PMULLW(mm1, mm2); /* MMX 0x0021F8B0: pmullw mm1, mm2 */
    mm6 = MMX_PSUBUSW(mm6, mm7); /* MMX 0x0021F8B3: psubusw mm6, mm7 */
    mm4 = mm6; /* MMX 0x0021F8B6: movq mm4, mm6 */
    mm6 = MMX_PUNPCKLWD(mm6, mm6); /* MMX 0x0021F8B9: punpcklwd mm6, mm6 */
    mm4 = MMX_PUNPCKHWD(mm4, mm4); /* MMX 0x0021F8BC: punpckhwd mm4, mm4 */
    mm6 = MMX_PMULLW(mm6, mm2); /* MMX 0x0021F8BF: pmullw mm6, mm2 */
    MEM32((uint32_t)(edi - 0x20)) = (uint32_t)mm3; MEM32((uint32_t)(edi - 0x20) + 4u) = (uint32_t)(mm3 >> 32); /* MMX 0x0021F8C2: movq qword ptr [edi - 0x20], mm3 */
    mm4 = MMX_PMULLW(mm4, mm2); /* MMX 0x0021F8C6: pmullw mm4, mm2 */
    MEM32((uint32_t)(edi - 0x18)) = (uint32_t)mm1; MEM32((uint32_t)(edi - 0x18) + 4u) = (uint32_t)(mm1 >> 32); /* MMX 0x0021F8C9: movq qword ptr [edi - 0x18], mm1 */
    MEM32((uint32_t)(edi - 0x10)) = (uint32_t)mm6; MEM32((uint32_t)(edi - 0x10) + 4u) = (uint32_t)(mm6 >> 32); /* MMX 0x0021F8CD: movq qword ptr [edi - 0x10], mm6 */
    MEM32((uint32_t)(edi - 8)) = (uint32_t)mm4; MEM32((uint32_t)(edi - 8) + 4u) = (uint32_t)(mm4 >> 32); /* MMX 0x0021F8D1: movq qword ptr [edi - 8], mm4 */
    _fa = (uint32_t)(edi) & 0xFFFFFFFFu; _fb = (uint32_t)(eax) & 0xFFFFFFFFu;
    _fas = (int32_t)(int32_t)(_fa); _fbs = (int32_t)(int32_t)(_fb); /* cmp edi, eax (32-bit) */
    if (CMP_B(_fa, _fb)) goto loc_0021F870; /* jb: below (unsigned <) */

loc_0021F8D9: ;
    MEM32(0x299F14) = edi;
    MEM32(0x299F1C) = edx;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebp);
    POP32(esp, ebx);
    esp += 8; return; /* ret 4 */

}



