/* Exact low EFLAGS byte produced by COMISS/UCOMISS, for the LAHF idiom. */
#ifndef RECOMP_SSE_FLAGS_H
#define RECOMP_SSE_FLAGS_H

#include <stdint.h>
#include <string.h>

/* With masked SIMD exceptions, COMISS and UCOMISS produce identical flags:
 * greater=02, less=03, equal=42, unordered=47. SF/AF are cleared and LAHF
 * reserves bit 1 as one. Compare IEEE-754 encodings so NaNs and signed zero
 * stay correct even when the host compiler enables fast floating-point math.
 * This models flags, not MXCSR exception status or unmasked guest traps.
 */
static inline uint8_t RECOMP_COMISS_LAHF(float lhs, float rhs)
{
    uint32_t a, b;
    memcpy(&a, &lhs, sizeof(a));
    memcpy(&b, &rhs, sizeof(b));
    const uint32_t am = a & 0x7fffffffu, bm = b & 0x7fffffffu;
    if (am > 0x7f800000u || bm > 0x7f800000u) return 0x47u;
    if (a == b || (am == 0 && bm == 0)) return 0x42u;
    const int less = ((a ^ b) & 0x80000000u)
        ? ((a & 0x80000000u) != 0)
        : ((a & 0x80000000u) ? (am > bm) : (am < bm));
    return (uint8_t)(less ? 0x03u : 0x02u);
}

#endif
