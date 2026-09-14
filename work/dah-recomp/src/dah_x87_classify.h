#ifndef DAH_X87_CLASSIFY_H
#define DAH_X87_CLASSIFY_H
#include <stdint.h>
#include <string.h>

/* FXAM's condition codes for a live value in this runtime's double-backed
 * x87 stack. FLD m64 normalizes binary64 subnormals in the 80-bit register;
 * they are NORMAL, not x87 extended denormals. The runtime does not represent
 * empty tags, unsupported extended encodings, or extended-only denormals.
 * Exception/sticky status is not modeled here: only C3/C2/C1/C0 and TOP,
 * exactly the status fields consumed by the CRT classifier. */
static inline uint16_t dah_x87_fxam_live_status(double value, uint32_t top)
{
    uint64_t bits;
    uint16_t classification;
    memcpy(&bits, &value, sizeof(bits));
    if ((bits & UINT64_C(0x7FFFFFFFFFFFFFFF)) == 0)
        classification = 0x4000u; /* zero */
    else if ((bits & UINT64_C(0x7FF0000000000000)) == UINT64_C(0x7FF0000000000000))
        classification = (bits & UINT64_C(0x000FFFFFFFFFFFFF)) ? 0x0100u : 0x0500u;
    else
        classification = 0x0400u; /* finite nonzero */
    return (uint16_t)(classification | ((bits >> 63) ? 0x0200u : 0u) | ((top & 7u) << 11));
}
#endif
