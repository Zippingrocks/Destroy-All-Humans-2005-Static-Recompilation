#ifndef DAH_FOG_COLOR_H
#define DAH_FOG_COLOR_H
#include <stdint.h>
/* NV097_SET_FOG_COLOR carries ABGR; D3DRS_FOGCOLOR expects ARGB.
 * Matches xemu pgraph SET_FOG_COLOR channel masks, including alpha. */
static uint32_t dah_nv2a_fog_color_argb(uint32_t raw)
{
    return (raw & 0xFF00FF00u) | ((raw & 0x000000FFu) << 16u) |
           ((raw & 0x00FF0000u) >> 16u);
}
#endif
