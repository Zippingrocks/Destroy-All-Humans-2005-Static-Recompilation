/* Original save-confirmation callback, decoded from retail XBE 8A3F0..8A50B.
 * Preserve the original state machine and guest calling convention. */
#define RECOMP_GENERATED_CODE
#include "recomp_funcs.h"
void sub_0008A3F0(void)
{
    eax = MEM32(esp + 4);
    PUSH32(esp, esi);
    esi = ecx;
    ecx = MEM32(esi + 8);
    eax = (eax & 0xFFFFFF00u) | (eax == 0);
    ecx--;
    if (ecx > 18) goto done;
    ecx = MEM8(0x0008A4F8u + ecx);
    switch (ecx) {
    case 0:
        if ((eax & 255) != 0) {
            PUSH32(esp, 3);
            ecx = esi;
            MEM32(esi + 8) = 2;
            PUSH32(esp, 0x0008A42Bu);
            sub_00089C30();
        }
        MEM32(esi + 8) = 3;
        break;
    case 1:
        if (MEM32(esi + 0x18) == 1) {
            edx = (eax & 255) == 0 ? 15 : 7;
            MEM32(esi + 8) = edx;
        } else {
            eax = (eax & 255) != 0 ? 6 : 17;
            MEM32(esi + 8) = eax;
        }
        break;
    case 2:
        eax = (eax & 255) != 0 ? 7 : 17;
        MEM32(esi + 8) = eax;
        break;
    case 3:
        eax = (eax & 255) != 0 ? 9 : 14;
        MEM32(esi + 8) = eax;
        break;
    case 4:
        MEM8(esi + 0x14) = 1;
        if ((eax & 255) != 0) MEM32(esi + 8) = 16;
        break;
    case 5:
        if ((eax & 255) != 0) MEM32(esi + 8) = 14;
        break;
    case 6:
        if ((eax & 255) != 0) {
            MEM8(esi + 0x14) = 0;
            MEM32(esi + 8) = 16;
        } else MEM32(esi + 8) = 17;
        break;
    case 7:
        if ((eax & 255) != 0) MEM32(esi + 8) = 21;
        break;
    }
done:
    POP32(esp, esi);
    esp += 8; /* ret 4 */
}
void sub_0008BC00(void)
{
    PUSH32(esp, 0x0008BC05u);
    sub_00089820();
    eax = 0;
    esp += 4;
}
