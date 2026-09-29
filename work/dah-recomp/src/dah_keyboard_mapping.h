#ifndef DAH_KEYBOARD_MAPPING_H
#define DAH_KEYBOARD_MAPPING_H

#include <stdint.h>

/* Convert four digital directions to an Xbox-stick vector.  Opposites cancel
 * deterministically.  Diagonals lie on the same radius as a full cardinal
 * input instead of producing an impossible square-corner magnitude. */
static inline void dah_keyboard_stick_axes(int left, int right,
                                           int down, int up,
                                           int16_t *out_x, int16_t *out_y)
{
    int16_t x = left == right ? 0 : (left ? INT16_MIN : INT16_MAX);
    int16_t y = down == up ? 0 : (down ? INT16_MIN : INT16_MAX);

    if (x && y) {
        /* round(32767 / sqrt(2)); radial magnitude is 32767.28 */
        x = x < 0 ? (int16_t)-23170 : (int16_t)23170;
        y = y < 0 ? (int16_t)-23170 : (int16_t)23170;
    }
    if (out_x) *out_x = x;
    if (out_y) *out_y = y;
}

#endif
