#ifndef DAH_X87_ROUND_H
#define DAH_X87_ROUND_H
#include <math.h>
#include <stdint.h>
/* FRNDINT's numeric result follows the guest RC bits, independently of the
 * host floating-point environment. Exception/status flags are handled separately. */
static inline double dah_x87_round(double value, uint16_t control)
{
    if (!isfinite(value) || value == 0.0) return value;
    switch ((control >> 10) & 3u) {
    case 1: return floor(value);
    case 2: return ceil(value);
    case 3: return trunc(value);
    default: {
        if (fabs(value) >= 0x1p52) return value;
        double result = floor(value);
        double fraction = value - result;
        if (fraction > 0.5 || (fraction == 0.5 && fmod(result, 2.0) != 0.0))
            result += 1.0;
        return copysign(result, value);
    }
    }
}

#endif
