/* Generated only from the verified retail XBE for crash
 * DAH-192507A8B0B8C19F.  The vtable at 0x00227A50 stores 0x00025060 in its
 * first slot; the original function discovery stopped at 0x00025060 and
 * therefore omitted this adjacent retail event handler. */
#define RECOMP_GENERATED_CODE
#include "recomp_funcs.h"

/**
 * sub_00025060
 * Original: 0x00025060 - 0x00025123 (195 bytes plus five-entry jump table)
 * Category: game_vtable
 * CC: thiscall, 2 params, returns int_or_void
 * Frame: fpo_leaf
 */
void sub_00025060(void)
{
    uint32_t event = MEM32(esp + 4);
    uint32_t kind = MEM32(event);
    uint32_t object = 0;
    uint32_t target;
    uint32_t saved_esp;

    switch (kind) {
    case 5u:
        PUSH32(esp, 0x3D8DB9BBu);
        PUSH32(esp, 0x000250E9u); sub_00024D10();
        esp += 12; return; /* ret 8 */
    case 6u:
        PUSH32(esp, 0xA789E4E2u);
        PUSH32(esp, 0x000250F6u); sub_00024D10();
        esp += 12; return; /* ret 8 */
    case 7u:
        object = MEM32(ecx + 0xD0u);
        if (!object) { esp += 12; return; }
        ecx = object;
        eax = MEM32(ecx);
        MEM32(esp + 4) = 0u;
        MEM32(esp + 8) = 0u;
        RECOMP_ITAIL(MEM32(eax + 0x4Cu));
        return;
    case 8u:
        eax = MEM32(ecx + 0x50u) - 7u;
        if (eax == 0u)
            object = MEM32(ecx + 0xB4u);
        else if (eax == 1u)
            object = MEM32(ecx + 0xBCu);
        break;
    case 9u:
        eax = MEM32(ecx + 0x50u) - 7u;
        if (eax == 0u)
            object = MEM32(ecx + 0xB8u);
        else if (eax == 1u)
            object = MEM32(ecx + 0xC0u);
        break;
    default:
        MEM32(esp + 4) = event;
        sub_00022270();
        return;
    }

    if (object) {
        ecx = object;
        eax = MEM32(ecx);
        target = MEM32(eax + 0x18u);
        saved_esp = esp;
        PUSH32(esp, 0x00025095u);
        RECOMP_ICALL_SAFE(target, saved_esp);
    }
    esp += 12; return; /* ret 8 */
}
