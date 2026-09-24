#ifndef DAH_COLOR_MASK_H
#define DAH_COLOR_MASK_H
#include <stdint.h>

/* NV097_SET_COLOR_MASK (also decoded this way by xemu pgraph.c):
 * B=bit0, G=bit8, R=bit16, A=bit24. D3D8/D3D11 use R,G,B,A bits0..3.
 * Reserved parameter bits do not enable a channel. Zero preserves all color
 * channels while allowing the draw's independent depth/stencil operations. */
static unsigned dah_nv2a_color_write_mask(uint32_t nv_mask)
{
    return ((nv_mask & 0x00010000u) ? 1u : 0u) |
           ((nv_mask & 0x00000100u) ? 2u : 0u) |
           ((nv_mask & 0x00000001u) ? 4u : 0u) |
           ((nv_mask & 0x01000000u) ? 8u : 0u);
}
#endif
