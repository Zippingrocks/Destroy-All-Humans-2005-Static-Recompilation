/* Retail frontend virtual callbacks omitted by function discovery.
 * Verified against work/default.xbe: 1022D0..10236E, 1023E0..102419,
 * and 103F20..103F59. The connected property/destructor entries at 101220,
 * 104480, and 104510 close the observed frontend vtables only.
 * Preserve native return cleanup and base forwarding. */
#define RECOMP_GENERATED_CODE
#include "recomp_funcs.h"

/* Retail lowercase primitive, 13E6CF..13E700. Consult the original CRT
 * classification table/locale helper; do not replace it with host locale. */
void sub_0013E6CF(void)
{
    int multibyte = (int32_t)MEM32(0x00259BF0u) > 1;
    PUSH32(esp, esi);
    esi = MEM32(esp + 8u);
    if (multibyte) {
        PUSH32(esp, 1u);
        PUSH32(esp, esi);
        PUSH32(esp, 0x0013E6E5u); sub_0013F82A();
        POP32(esp, ecx);
        POP32(esp, ecx);
    } else {
        eax = MEM32(0x00259BE8u);
        eax = (uint32_t)MEM8(eax + esi * 2u);
        eax &= 1u;
    }
    eax = eax != 0u ? esi + 0x20u : esi;
    POP32(esp, esi);
    esp += 4u; /* cdecl RET; caller owns character argument */
}

/* Lua string.lower, 1933D0..193454. The original buffer holds512 bytes;
 * flushing and finalization remain in the original Lua buffer functions.
 * Length, not NUL termination, controls the native byte transformation. */
void sub_001933D0(void)
{
    esp -= 0x210u;
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    eax = esp + 8u;
    PUSH32(esp, eax);
    edx = 1u;
    esi = ecx;
    PUSH32(esp, 0x001933E9u); sub_00191960();
    edx = esp + 0xCu;
    ecx = esi;
    edi = eax;
    PUSH32(esp, 0x001933F6u); sub_001917E0();
    eax = MEM32(esp + 8u);
    esi = 0u;
    if (eax != 0u) {
        do {
            eax = MEM32(esp + 0xCu);
            ecx = esp + 0x218u;
            if (eax >= ecx) {
                ecx = esp + 0xCu;
                PUSH32(esp, 0x00193418u); sub_00191620();
            }
            edx = (uint32_t)MEM8(esi + edi);
            PUSH32(esp, edx);
            PUSH32(esp, 0x00193422u); sub_0013E6CF();
            ecx = MEM32(esp + 0x10u);
            MEM8(ecx) = LO8(eax);
            edx = MEM32(esp + 0x10u);
            eax = MEM32(esp + 0xCu);
            esp += 4u;
            ++edx;
            ++esi;
            MEM32(esp + 0xCu) = edx;
        } while (esi < eax);
    }
    ecx = esp + 0xCu;
    PUSH32(esp, 0x00193446u); sub_001916D0();
    POP32(esp, edi);
    eax = 1u;
    POP32(esp, esi);
    esp += 0x214u; /* release0x210 locals; RET */
}

/* Renderer-mode virtual reached directly through restored E3BE0. */
void sub_000E0510(void)
{
    eax = MEM32(esp + 4u);
    PUSH32(esp, esi);
    esi = ecx;
    MEM32(esi + 0x27Cu) = eax;
    PUSH32(esp, 0x000E0522u); sub_001DA870();
    eax = MEM32(esi + 0x27Cu);
    if (eax == 2u) {
        eax = 0u;
        MEM32(esi + 0x2C8u) = 2u;
        esi += 0x298u;
        PUSH32(esp, esi);
        PUSH32(esp, 0x000E0549u); sub_001DAB20();
    } else if (eax == 1u) {
        eax = 0u;
        MEM32(esi + 0x2C8u) = 1u;
        esi += 0x298u;
        PUSH32(esp, esi);
        PUSH32(esp, 0x000E0563u); sub_001DAB20();
    } else {
        if (eax == 0u) MEM32(esi + 0x2C8u) = 0x80000001u;
        else eax -= 2u;
        esi += 0x298u;
        PUSH32(esp, esi);
        PUSH32(esp, 0x000E057Du); sub_001DAB20();
    }
    POP32(esp, esi);
    esp += 8u; /* RET4 */
}

/* Script natives retained as data in their registration tables. */
void sub_0008BA90(void)
{
    PUSH32(esp, esi);
    PUSH32(esp, 1u);
    esi = ecx;
    PUSH32(esp, 0x0008BA9Au); sub_00139520();
    edx = 0u;
    ecx = eax;
    PUSH32(esp, 0x0008BAA3u); sub_000D54A0();
    PUSH32(esp, eax);
    PUSH32(esp, 0x0008BAA9u); sub_00089840();
    ecx = eax;
    PUSH32(esp, 0x0008BAB0u); sub_0008AD60();
    ecx = esi;
    if (eax != 0u) {
        eax = MEM32(eax + 8u);
        PUSH32(esp, eax);
        PUSH32(esp, 0x0008BABFu); sub_00139120();
    } else {
        PUSH32(esp, 0x0008BACBu); sub_001390F0();
    }
    eax = 1u;
    POP32(esp, esi);
    esp += 4u;
}

void sub_000E3BE0(void)
{
    eax = MEM32(0x00250E60u);
    PUSH32(esp, esi);
    esi = MEM32(eax);
    PUSH32(esp, 1u);
    PUSH32(esp, 0x000E3BEFu); sub_001394F0();
    ecx = MEM32(0x00250E60u);
    {
        uint32_t call_esp = esp;
        uint32_t target = MEM32(esi + 0x20u);
        PUSH32(esp, eax);
        PUSH32(esp, 0x000E3BF9u);
        RECOMP_ICALL_SAFE(target, call_esp);
    }
    eax = 0u;
    POP32(esp, esi);
    esp += 4u;
}

/* Native timer/script event virtual, 11C180..11C29E. Keep the accumulated
 * x87 value live after its float store: rounding it before the expiry compare
 * changes a boundary tick. TEST AH masks below include unordered as on x87. */
void sub_0011C180(void)
{
    PUSH32(esp, ebx);
    ebx = MEM32(esp + 8u);
    PUSH32(esp, esi);
    esi = ecx;
    if (MEM32(ebx + 4u) != 0x6BFC080Fu) goto timer_event_forward;
    g_fp_top = (g_fp_top + 7u) & 7u;
    g_fp_stack[g_fp_top] = (double)MEMF(ebx + 8u);
    eax = MEM32(esi + 0x10u);
    g_fp_stack[g_fp_top] += (double)MEMF(esi + 0x18u);
    MEMF(esi + 0x18u) = (float)g_fp_stack[g_fp_top];
    if (eax != 1u) goto timer_event_inactive;
    g_fp_top = (g_fp_top + 7u) & 7u;
    g_fp_stack[g_fp_top] = (double)MEMF(esi + 0x20u);
    g_fp_cmp = RECOMP_FCMP(g_fp_stack[g_fp_top], (double)MEMF(0x00225C20u));
    g_fp_top = (g_fp_top + 1u) & 7u;
    SET_LO16(eax, ((g_fp_top & 7u) << 11) |
        (g_fp_cmp == 2 ? 0x4500u : g_fp_cmp < 0 ? 0x0100u : g_fp_cmp > 0 ? 0u : 0x4000u));
    if (HI8(eax) & 0x41u) {
        g_fp_top = (g_fp_top + 1u) & 7u; /* 11C28F: FSTP ST(0) */
        goto timer_event_forward;
    }
    g_fp_top = (g_fp_top + 7u) & 7u;
    g_fp_stack[g_fp_top] = (double)MEMF(esi + 0x1Cu);
    g_fp_stack[g_fp_top] += (double)MEMF(esi + 0x20u);
    {
        unsigned next = (g_fp_top + 1u) & 7u;
        double value = g_fp_stack[g_fp_top];
        g_fp_stack[g_fp_top] = g_fp_stack[next];
        g_fp_stack[next] = value;
        g_fp_cmp = RECOMP_FCMP(g_fp_stack[g_fp_top], g_fp_stack[next]);
        g_fp_top = (g_fp_top + 2u) & 7u; /* FXCH; FCOMPP */
    }
    SET_LO16(eax, ((g_fp_top & 7u) << 11) |
        (g_fp_cmp == 2 ? 0x4500u : g_fp_cmp < 0 ? 0x0100u : g_fp_cmp > 0 ? 0u : 0x4000u));
    if (HI8(eax) & 1u) goto timer_event_forward;
    SET_LO8(eax, MEM8(esi + 0x24u));
    MEM32(esi + 0x10u) = 0u;
    if (!LO8(eax)) goto timer_event_forward;
    PUSH32(esp, 0u);
    PUSH32(esp, 0x0011C1E8u); sub_0011C080();
    PUSH32(esp, ebx);
    PUSH32(esp, 0x0011C1EEu); sub_00111650();
    goto timer_event_return;

timer_event_inactive:
    g_fp_top = (g_fp_top + 1u) & 7u;
    if (eax != 0u) goto timer_event_forward;
    eax = MEM32(esi + 0x14u);
    if ((int32_t)eax < 0) goto timer_event_forward;
    ecx = MEM32(0x00286768u);
    PUSH32(esp, edi);
    edi = MEM32(ecx + 0x3048u);
    PUSH32(esp, eax);
    ecx = edi;
    PUSH32(esp, 0x0011C21Du); sub_001391E0();
    edx = MEM32(esi + 0x28u);
    PUSH32(esp, edx);
    ecx = edi;
    PUSH32(esp, 0x0011C228u); sub_00139140();
    eax = MEM32(esi + 0x2Cu);
    PUSH32(esp, eax);
    ecx = edi;
    PUSH32(esp, 0x0011C233u); sub_00139140();
    eax = MEM32(esi + 0x30u);
    ecx = edi;
    if (eax != 0u) {
        PUSH32(esp, eax);
        PUSH32(esp, 0x0011C242u); sub_00139160();
    } else {
        PUSH32(esp, 0x0011C249u); sub_001390F0();
    }
    eax = MEM32(esi + 0x34u);
    ecx = edi;
    if (eax != 0u) {
        PUSH32(esp, eax);
        PUSH32(esp, 0x0011C258u); sub_00139160();
        PUSH32(esp, 0u);
        PUSH32(esp, 4u);
        ecx = edi;
        PUSH32(esp, 0x0011C263u); sub_00139210();
        POP32(esp, edi);
        PUSH32(esp, ebx);
        ecx = esi;
        PUSH32(esp, 0x0011C26Cu); sub_00111650();
    } else {
        PUSH32(esp, 0x0011C276u); sub_001390F0();
        PUSH32(esp, 0u);
        PUSH32(esp, 4u);
        ecx = edi;
        PUSH32(esp, 0x0011C281u); sub_00139210();
        POP32(esp, edi);
        PUSH32(esp, ebx);
        ecx = esi;
        PUSH32(esp, 0x0011C28Au); sub_00111650();
    }
    goto timer_event_return;

timer_event_forward:
    PUSH32(esp, ebx);
    ecx = esi;
    PUSH32(esp, 0x0011C299u); sub_00111650();
timer_event_return:
    POP32(esp, esi);
    POP32(esp, ebx);
    esp += 8u; /* RET 4 */
}

void sub_001022D0(void)
{
    eax = MEM32(esp + 4u);
    PUSH32(esp, esi);
    esi = ecx;
    if (eax > 0x90F2A209u) {
        if (eax == 0x91F03F7Cu) {
            uint32_t call_esp = esp;
            uint32_t target;
            ecx = MEM32(esi + 0xB0u);
            edx = MEM32(ecx);
            target = MEM32(edx + 8u);
            PUSH32(esp, 0x00102368u);
            RECOMP_ICALL_SAFE(target, call_esp);
            eax = 0u;
        } else {
            goto property_forward;
        }
    } else if (eax == 0x90F2A209u) {
        edx = MEM32(esp + 0xCu);
        PUSH32(esp, edx);
        PUSH32(esp, 0x00102332u); sub_000FBCB0();
        ecx = eax;
        PUSH32(esp, 0x00102339u); sub_00139510();
        MEMF(esi + 0xB8u) = (float)g_fp_stack[g_fp_top];
        g_fp_top = (g_fp_top + 1u) & 7u;
        eax = 0u;
    } else if (eax == 0x3F367A0Au) {
        ecx = MEM32(esp + 0xCu);
        PUSH32(esp, ecx);
        PUSH32(esp, 0x00102315u); sub_000FBCB0();
        ecx = eax;
        PUSH32(esp, 0x0010231Cu); sub_00139510();
        MEMF(esi + 0xBCu) = (float)g_fp_stack[g_fp_top];
        g_fp_top = (g_fp_top + 1u) & 7u;
        eax = 0u;
    } else if (eax == 0x42841248u) {
        eax = MEM32(esp + 0xCu);
        PUSH32(esp, eax);
        PUSH32(esp, 0x001022F8u); sub_000FBCB0();
        ecx = eax;
        PUSH32(esp, 0x001022FFu); sub_00139510();
        MEMF(esi + 0xB4u) = (float)g_fp_stack[g_fp_top];
        g_fp_top = (g_fp_top + 1u) & 7u;
        eax = 0u;
    } else {
property_forward:
        ecx = MEM32(esp + 0xCu);
        PUSH32(esp, ecx);
        PUSH32(esp, eax);
        ecx = esi;
        PUSH32(esp, 0x00102359u); sub_000F99F0();
    }
    POP32(esp, esi);
    esp += 12u; /* ret 8 */
}

void sub_001023E0(void)
{
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    edi = MEM32(esp + 0xCu);
    esi = ecx;
    if (MEM32(edi + 4u) == 9u) {
        eax = esi + 0x68u;
        PUSH32(esp, eax);
        ecx = esi + 0x78u;
        PUSH32(esp, ecx);
        ecx = esi;
        PUSH32(esp, 0x001023FDu); sub_000F88F0();
        if (LO8(eax) != 0u) {
            uint32_t call_esp = esp;
            uint32_t target;
            ecx = MEM32(esi + 0xB0u);
            edx = MEM32(ecx);
            target = MEM32(edx + 4u);
            PUSH32(esp, 0x0010240Cu);
            RECOMP_ICALL_SAFE(target, call_esp);
        }
    }
    PUSH32(esp, edi);
    ecx = esi;
    PUSH32(esp, 0x00102414u); sub_000F93F0();
    POP32(esp, edi);
    POP32(esp, esi);
    esp += 8u; /* ret 4 */
}

void sub_00103F20(void)
{
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    edi = MEM32(esp + 0xCu);
    esi = ecx;
    if (MEM32(edi + 4u) == 9u) {
        eax = esi + 0x68u;
        PUSH32(esp, eax);
        ecx = esi + 0x78u;
        PUSH32(esp, ecx);
        ecx = esi;
        PUSH32(esp, 0x00103F3Du); sub_000F88F0();
        if (LO8(eax) != 0u) {
            uint32_t call_esp = esp;
            uint32_t target;
            ecx = MEM32(esi + 0xB0u);
            edx = MEM32(ecx);
            target = MEM32(edx + 8u);
            PUSH32(esp, 0x00103F4Cu);
            RECOMP_ICALL_SAFE(target, call_esp);
        }
    }
    PUSH32(esp, edi);
    ecx = esi;
    PUSH32(esp, 0x00103F54u); sub_000F93F0();
    POP32(esp, edi);
    POP32(esp, esi);
    esp += 8u; /* ret 4 */
}

void sub_00101220(void)
{
    eax = MEM32(esp + 4u);
    PUSH32(esp, esi);
    esi = ecx;
    if (eax == 0x0720E37Au) {
        ecx = MEM32(esp + 0xCu);
        PUSH32(esp, ecx);
        PUSH32(esp, 0x0010129Fu); sub_000FBCB0();
        ecx = eax;
        PUSH32(esp, 0x001012A6u); sub_00139510();
        esi = MEM32(esi + 0xB0u);
        MEMF(esi + 4u) = (float)g_fp_stack[g_fp_top];
        g_fp_top = (g_fp_top + 1u) & 7u;
        MEM8(esi + 0x10u) = 1u;
        eax = 0u;
    } else if (eax == 0x8A40881Au) {
        eax = MEM32(esp + 0xCu);
        PUSH32(esp, eax);
        PUSH32(esp, 0x0010127Bu); sub_000FBCB0();
        ecx = eax;
        PUSH32(esp, 0x00101282u); sub_00139510();
        esi = MEM32(esi + 0xB0u);
        MEMF(esi + 8u) = (float)g_fp_stack[g_fp_top];
        g_fp_top = (g_fp_top + 1u) & 7u;
        MEM8(esi + 0x10u) = 1u;
        eax = 0u;
    } else if (eax == 0xF746A230u) {
        edx = MEM32(esp + 0xCu);
        PUSH32(esp, edx);
        PUSH32(esp, 0x00101257u); sub_000FBCB0();
        ecx = eax;
        PUSH32(esp, 0x0010125Eu); sub_00139510();
        esi = MEM32(esi + 0xB0u);
        MEMF(esi + 0xCu) = (float)g_fp_stack[g_fp_top];
        g_fp_top = (g_fp_top + 1u) & 7u;
        MEM8(esi + 0x10u) = 1u;
        eax = 0u;
    } else {
        ecx = MEM32(esp + 0xCu);
        PUSH32(esp, ecx);
        PUSH32(esp, eax);
        ecx = esi;
        PUSH32(esp, 0x00101249u); sub_000F99F0();
    }
    POP32(esp, esi);
    esp += 12u; /* ret 8 */
}

void sub_00104480(void)
{
    uint32_t ebp = g_ebp;
    eax = MEM32(esp + 4u);
    esp -= 0x20u;
    PUSH32(esp, edi);
    edi = ecx;
    if (eax != 0xA71A3D94u) {
        ecx = MEM32(esp + 0x2Cu);
        PUSH32(esp, ecx);
        PUSH32(esp, eax);
        ecx = edi;
        PUSH32(esp, 0x0010449Eu); sub_000F99F0();
    } else {
        PUSH32(esp, ebx);
        PUSH32(esp, ebp);
        PUSH32(esp, esi);
        esi = MEM32(esp + 0x38u);
        PUSH32(esp, esi);
        PUSH32(esp, 0x001044B2u); sub_000FBCB0();
        ecx = eax;
        PUSH32(esp, 0x001044B9u); sub_001394F0();
        edx = esi + 1u;
        PUSH32(esp, edx);
        ebx = eax;
        PUSH32(esp, 0x001044C4u); sub_000FBCB0();
        ecx = eax;
        PUSH32(esp, 0x001044CBu); sub_001394F0();
        ebp = eax;
        eax = esi + 2u;
        PUSH32(esp, eax);
        ecx = esp + 0x24u;
        PUSH32(esp, ecx);
        ecx = edi;
        PUSH32(esp, 0x001044DDu); sub_000F8800();
        esi += 6u;
        PUSH32(esp, esi);
        edx = esp + 0x14u;
        PUSH32(esp, edx);
        ecx = edi;
        PUSH32(esp, 0x001044EDu); sub_000F8800();
        eax = esp + 0x10u;
        PUSH32(esp, eax);
        ecx = esp + 0x24u;
        PUSH32(esp, ecx);
        ecx = MEM32(edi + 0xB0u);
        PUSH32(esp, ebp);
        PUSH32(esp, ebx);
        PUSH32(esp, 0x00104504u); sub_001A3400();
        POP32(esp, esi);
        POP32(esp, ebp);
        POP32(esp, ebx);
        eax = 0u;
    }
    POP32(esp, edi);
    esp += 0x20u;
    esp += 12u; /* ret 8 */
}

void sub_00104510(void)
{
    PUSH32(esp, esi);
    esi = ecx;
    ecx = MEM32(esi + 0xB0u);
    MEM32(esi) = 0x00235628u;
    if (ecx != 0u) {
        uint32_t call_esp = esp;
        uint32_t target;
        eax = MEM32(ecx);
        target = MEM32(eax);
        PUSH32(esp, 1u);
        PUSH32(esp, 0x00104529u);
        RECOMP_ICALL_SAFE(target, call_esp);
    }
    ecx = esi;
    PUSH32(esp, 0x00104530u); sub_000F86E0();
    if ((MEM8(esp + 8u) & 1u) != 0u) {
        PUSH32(esp, esi);
        PUSH32(esp, 0x0010453Du); sub_0006B710();
        esp += 4u;
    }
    eax = esi;
    POP32(esp, esi);
    esp += 8u; /* ret 4 */
}
