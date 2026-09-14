/* Missing arms of the retail render-target format encoder at 0x001E0420.
 * Original bytes and the complete two-table dispatch are tested by
 * tools/test_d3d_format_callbacks.mjs. These are tail entries: no new guest
 * return address or arguments are pushed before the original shared tail. */
#define RECOMP_GENERATED_CODE
#include "recomp_funcs.h"

void sub_001E0436(void)
{
    eax = 8; /* 001E0436: b808000000 */
    sub_001E043B(); /* original fallthrough */
}

void sub_001E045D(void)
{
    eax = 8; /* 001E045D: b808000000 */
    sub_001E0462(); /* original fallthrough */
}

void sub_001E0489(void)
{
    eax = 4; /* 001E0489: b804000000 */
    sub_001E043B(); /* 001E048E: ebab */
}

void sub_001E0497(void)
{
    eax = 3; /* 001E0497: b803000000 */
    sub_001E043B(); /* 001E049C: eb9d */
}

void sub_001E049E(void)
{
    eax = 3; /* 001E049E: b803000000 */
    sub_001E0462(); /* 001E04A3: ebbd */
}

void sub_001E04AC(void)
{
    eax = 1; /* 001E04AC: b801000000 */
    sub_001E0462(); /* 001E04B1: ebaf */
}

void sub_001E04B3(void)
{
    eax = 9; /* 001E04B3: b809000000 */
    sub_001E0462(); /* 001E04B8: eba8 */
}

void sub_001E04BA(void)
{
    eax = 10; /* 001E04BA: b80a000000 */
    sub_001E0462(); /* 001E04BF: eba1 */
}

void sub_001E04C1(void)
{
    eax |= 0x20; /* 001E04C1: 83c820 */
    sub_001E04C4(); /* original fallthrough: ret 8 */
}

void sub_001E04D5(void)
{
    eax |= 0x10; /* 001E04D5: 83c810 */
    esp += 12; /* 001E04D8: c20800 -- ret 8 */
}
