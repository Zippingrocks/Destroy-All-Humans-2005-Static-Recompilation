/* Retail vehicle/attachment update callback observed from 0x0001E9E6.
 * Byte-checked lift; see tools/lift_vehicle_attachment_callback.py. */
#define RECOMP_GENERATED_CODE
#include "recomp_funcs.h"

void sub_0001D030(void)
{
    uint32_t ebp;
    ebp = g_ebp;
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
    ebp = g_seh_ebp;

loc_0001D030: ;
    PUSH32(esp, ecx);
    eax = MEM32(esp + 8);
    PUSH32(esp, esi);
    PUSH32(esp, eax);
    esi = ecx;
    PUSH32(esp, 0x0001D03Eu); sub_00021200();

loc_0001D03E: ;
    ecx = MEM32(esi + 8);
    SET_LO8(eax, MEM8(ecx + 0x58));
    _fa = LO8(eax); _fb = LO8(eax);
    _fas = (int32_t)(int8_t)_fa; _fbs = (int32_t)(int8_t)_fb;
    if (TEST_Z(_fa, _fb)) goto loc_0001D0FA;

loc_0001D04C: ;
    ecx = MEM32(esi + 4);
    edx = MEM32(ecx);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, edi);
    { uint32_t _icall_target = MEM32(edx + 0xF8); PUSH32(esp, 0x0001D058u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); }
    }

loc_0001D058: ;
    edi = eax;
    eax = MEM32(esi + 4);
    ecx = MEM32(eax + 0x12C);
    ecx >>= 6;
    _fa = LO8(ecx); _fb = 1;
    _fas = (int32_t)(int8_t)_fa; _fbs = 1;
    if (TEST_Z(_fa, _fb)) goto loc_0001D0FF;

loc_0001D06F: ;
    _fa = MEM32(edi + 0x10); _fb = 4;
    _fas = (int32_t)_fa; _fbs = 4;
    if (CMP_EQ(_fa, _fb)) goto loc_0001D0F9;

loc_0001D079: ;
    edx = MEM32(edi + 0x30);
    eax = edx;
    PUSH32(esp, eax);
    MEM32(esp + 0xC) = edx;
    PUSH32(esp, 0x0001D088u); sub_000D41A0();

loc_0001D088: ;
    g_fp_cmp = RECOMP_FCMP(fp_top(), MEMF(0x227154)); fp_pop();
    eax = (eax & 0xFFFF0000u) | (uint32_t)(uint16_t)(((g_fp_top & 7u) << 11) | (g_fp_cmp == 2 ? 0x4500u : g_fp_cmp < 0 ? 0x0100u : g_fp_cmp > 0 ? 0x0000u : 0x4000u));
    _fa = HI8(eax); _fb = 0x41;
    _fas = (int32_t)(int8_t)_fa; _fbs = 0x41;
    if (RECOMP_PARITY8(_fa & _fb)) goto loc_0001D0F9;

loc_0001D095: ;
    eax = MEM32(esi + 4);
    PUSH32(esp, ebp);
    ecx = eax + 0x4E8;
    PUSH32(esp, 0x0001D0A4u); sub_00109F70();

loc_0001D0A4: ;
    ebp = eax;
    _fa = ebp; _fb = ebp;
    _fas = (int32_t)_fa; _fbs = (int32_t)_fb;
    if (TEST_Z(_fa, _fb)) goto loc_0001D0F8;

loc_0001D0AA: ;
    edx = MEM32(esi + 4);
    eax = MEM32(edx + 0x198);
    _fa = eax; _fb = eax;
    _fas = (int32_t)_fa; _fbs = (int32_t)_fb;
    PUSH32(esp, ebx);
    ebx = edx + 0x198;
    if (TEST_Z(_fa, _fb)) goto loc_0001D0F7;

loc_0001D0BE: ;
    ecx = ebx;
    PUSH32(esp, 0x0001D0C5u); sub_000326F0();

loc_0001D0C5: ;
    _fa = eax; _fb = eax;
    _fas = (int32_t)_fa; _fbs = (int32_t)_fb;
    if (TEST_Z(_fa, _fb)) goto loc_0001D0CD;

loc_0001D0C9: ;
    _fa = eax; _fb = ebp;
    _fas = (int32_t)_fa; _fbs = (int32_t)_fb;
    if (CMP_EQ(_fa, _fb)) goto loc_0001D0F7;

loc_0001D0CD: ;
    fp_push(MEMF(esi + 0x68));
    fp_top() -= MEMF(esp + 0x18);
    MEMF(esi + 0x68) = (float)fp_top();
    g_fp_cmp = RECOMP_FCMP(fp_top(), MEMF(0x225C20)); fp_pop();
    eax = (eax & 0xFFFF0000u) | (uint32_t)(uint16_t)(((g_fp_top & 7u) << 11) | (g_fp_cmp == 2 ? 0x4500u : g_fp_cmp < 0 ? 0x0100u : g_fp_cmp > 0 ? 0x0000u : 0x4000u));
    _fa = HI8(eax); _fb = 5;
    _fas = (int32_t)(int8_t)_fa; _fbs = 5;
    if (RECOMP_PARITY8(_fa & _fb)) goto loc_0001D0F7;

loc_0001D0E4: ;
    esi = MEM32(esi + 8);
    eax = MEM32(esi + 0x50);
    ecx = MEM32(esi + 0x54);
    edx = MEM32(edi);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, eax);
    PUSH32(esp, ecx);
    PUSH32(esp, ebx);
    ecx = edi;
    { uint32_t _icall_target = MEM32(edx + 0x2C); PUSH32(esp, 0x0001D0F7u); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); }
    }

loc_0001D0F7: ;
    POP32(esp, ebx);
loc_0001D0F8: ;
    POP32(esp, ebp);
loc_0001D0F9: ;
    POP32(esp, edi);
loc_0001D0FA: ;
    POP32(esp, esi);
    POP32(esp, ecx);
    esp += 8; return;

loc_0001D0FF: ;
    ecx = 0x278A58;
    PUSH32(esp, 0x0001D109u); sub_000D42C0();

loc_0001D109: ;
    fp_top() *= MEMF(0x227168);
    fp_top() += MEMF(0x227164);
    MEMF(esi + 0x68) = (float)fp_top(); fp_pop();
    eax = MEM32(edi + 0x10);
    _fa = eax; _fb = 4;
    _fas = (int32_t)_fa; _fbs = 4;
    if (CMP_NE(_fa, _fb)) goto loc_0001D0F9;

loc_0001D120: ;
    edx = MEM32(edi + 0x28);
    eax = MEM32(edi + 0x44);
    ecx = edx;
    MEM32(esp + 0x10) = edx;
    PUSH32(esp, ecx);
    edx = eax;
    PUSH32(esp, edx);
    MEM32(esp + 0x10) = eax;
    PUSH32(esp, 0x0001D139u); sub_00013F60();

loc_0001D139: ;
    PUSH32(esp, ecx);
    MEMF(esp) = (float)fp_top(); fp_pop();
    PUSH32(esp, 0x0001D142u); sub_000D41A0();

loc_0001D142: ;
    g_fp_cmp = RECOMP_FCMP(fp_top(), MEMF(0x244F50)); fp_pop();
    eax = (eax & 0xFFFF0000u) | (uint32_t)(uint16_t)(((g_fp_top & 7u) << 11) | (g_fp_cmp == 2 ? 0x4500u : g_fp_cmp < 0 ? 0x0100u : g_fp_cmp > 0 ? 0x0000u : 0x4000u));
    _fa = HI8(eax); _fb = 5;
    _fas = (int32_t)(int8_t)_fa; _fbs = 5;
    if (RECOMP_PARITY8(_fa & _fb)) goto loc_0001D0F9;

loc_0001D14F: ;
    eax = MEM32(esi + 8);
    ecx = MEM32(eax + 0x50);
    eax = MEM32(eax + 0x54);
    edx = MEM32(edi);
    { uint32_t _icall_esp = g_esp;
    PUSH32(esp, ecx);
    ecx = MEM32(esi + 4);
    ecx += 0x198;
    PUSH32(esp, eax);
    PUSH32(esp, ecx);
    ecx = edi;
    { uint32_t _icall_target = MEM32(edx + 0x20); PUSH32(esp, 0x0001D16Bu); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); }
    }

loc_0001D16B: ;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ecx);
    esp += 8; return;

    #undef fp_push
    #undef fp_pop
    #undef fp_top
    #undef fp_st
    #undef fp_st1
}
