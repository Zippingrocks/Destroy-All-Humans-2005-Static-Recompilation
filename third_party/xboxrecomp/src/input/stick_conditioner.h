#ifndef XBOX_STICK_CONDITIONER_H
#define XBOX_STICK_CONDITIONER_H

#include <stdint.h>

/* Convert a square host-stick range into the circular range expected by an
 * Xbox game, remove center noise, and remap the remaining travel smoothly. */
void xbox_condition_stick(int16_t raw_x, int16_t raw_y,
                          unsigned deadzone, double response_curve,
                          int16_t *out_x, int16_t *out_y);

#endif
