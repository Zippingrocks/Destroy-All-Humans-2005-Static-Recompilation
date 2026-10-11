#define RECOMP_GENERATED_CODE
#include "recomp_funcs.h"

/**
 * sub_0012AEE0
 * Original: 0x0012AEE0 - 0x0012AF02 (34 bytes, 11 insns)
 *
 * Retail type-query callback from vtable 0x002375F8.  Ordinary discovery
 * missed this complete function because it starts directly after 0012AED0.
 * The live October 10 run reached it through 00051010 while resolving an
 * object's supported interface/type hashes.
 */
void sub_0012AEE0(void)
{
    uint32_t argument;

    argument = MEM32(esp + 4u);
    eax = argument;
    if (argument == 0x1CCAFDCCu || argument == 0x7E1FE4E4u) {
        SET_LO8(eax, 1u);
    } else {
        SET_LO8(eax, argument == 0xFFEE9E41u ? 1u : 0u);
    }
    esp += 8u; /* ret 4 */
}
