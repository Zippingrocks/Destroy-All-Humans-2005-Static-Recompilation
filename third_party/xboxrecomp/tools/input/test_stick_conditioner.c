#include <assert.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "stick_conditioner.h"

static double magnitude(int16_t x, int16_t y)
{
    return sqrt((double)x * x + (double)y * y);
}

int main(void)
{
    int16_t x, y, linear_x, curved_x;

    xbox_condition_stick(0, 0, 7849, 1.0, &x, &y);
    assert(x == 0 && y == 0);
    xbox_condition_stick(5000, -5000, 7849, 1.0, &x, &y);
    assert(x == 0 && y == 0);
    xbox_condition_stick(7849, 0, 7849, 1.0, &x, &y);
    assert(x == 0 && y == 0);

    xbox_condition_stick(32767, 0, 7849, 1.0, &x, &y);
    assert(x == 32767 && y == 0);
    xbox_condition_stick(-32768, 0, 7849, 1.0, &x, &y);
    assert(x <= -32766 && y == 0);

    xbox_condition_stick(32767, 32767, 7849, 1.0, &x, &y);
    assert(abs(x - y) <= 1);
    assert(magnitude(x, y) >= 32765.0 && magnitude(x, y) <= 32768.0);

    xbox_condition_stick(20000, 0, 8689, 1.0, &linear_x, &y);
    xbox_condition_stick(20000, 0, 8689, 1.35, &curved_x, &y);
    assert(curved_x > 0 && curved_x < linear_x && linear_x < 20000);

    xbox_condition_stick(15000, 12000, 7849, 1.0, &x, &y);
    assert(x > 0 && y > 0);
    assert(fabs((double)x / (double)y - 1.25) < 0.01);

    puts("stick conditioner tests passed");
    return 0;
}
