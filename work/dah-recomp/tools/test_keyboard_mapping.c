#include <assert.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>

#include "dah_keyboard_mapping.h"

static void expect(int left, int right, int down, int up,
                   int16_t expected_x, int16_t expected_y)
{
    int16_t x = 123, y = 456;
    dah_keyboard_stick_axes(left, right, down, up, &x, &y);
    assert(x == expected_x);
    assert(y == expected_y);
}

int main(void)
{
    int16_t x, y;
    expect(0, 0, 0, 0, 0, 0);
    expect(0, 0, 0, 1, 0, INT16_MAX);
    expect(0, 0, 1, 0, 0, INT16_MIN);
    expect(1, 0, 0, 0, INT16_MIN, 0);
    expect(0, 1, 0, 0, INT16_MAX, 0);
    expect(1, 0, 0, 1, -23170, 23170);
    expect(0, 1, 0, 1, 23170, 23170);
    expect(1, 0, 1, 0, -23170, -23170);
    expect(0, 1, 1, 0, 23170, -23170);
    expect(0, 0, 1, 1, 0, 0);
    expect(1, 1, 0, 0, 0, 0);
    expect(1, 1, 1, 1, 0, 0);

    dah_keyboard_stick_axes(1, 0, 0, 1, &x, &y);
    assert(fabs(sqrt((double)x * x + (double)y * y) - 32767.0) < 1.0);
    puts("keyboard mapping tests passed");
    return 0;
}
