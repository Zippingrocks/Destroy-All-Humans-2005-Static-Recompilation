#include "stick_conditioner.h"

#include <math.h>

static int16_t stick_round_and_clamp(double value)
{
    long rounded = (long)(value >= 0.0 ? value + 0.5 : value - 0.5);
    if (rounded > 32767) return 32767;
    if (rounded < -32768) return -32768;
    return (int16_t)rounded;
}

void xbox_condition_stick(int16_t raw_x, int16_t raw_y,
                          unsigned deadzone, double response_curve,
                          int16_t *out_x, int16_t *out_y)
{
    const double maximum = 32767.0;
    double x = (double)raw_x;
    double y = (double)raw_y;
    double magnitude = sqrt(x * x + y * y);
    double usable, normalized, output_magnitude, scale;

    if (!out_x || !out_y) return;
    if (deadzone >= 32767u) deadzone = 32766u;
    if (response_curve < 0.25) response_curve = 0.25;
    if (response_curve > 4.0) response_curve = 4.0;

    if (magnitude <= (double)deadzone || magnitude == 0.0) {
        *out_x = 0;
        *out_y = 0;
        return;
    }

    /* A diagonal can exceed 32767 in a square host coordinate system. Keep
     * its direction, but cap its radial magnitude to the Xbox stick circle. */
    usable = magnitude < maximum ? magnitude : maximum;
    normalized = (usable - (double)deadzone) /
                 (maximum - (double)deadzone);
    if (normalized < 0.0) normalized = 0.0;
    if (normalized > 1.0) normalized = 1.0;
    output_magnitude = pow(normalized, response_curve) * maximum;
    scale = output_magnitude / magnitude;

    *out_x = stick_round_and_clamp(x * scale);
    *out_y = stick_round_and_clamp(y * scale);
}
