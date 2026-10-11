/* Exact 9-instruction retail unlit vertex-color program captured in Farm.
 * The signature is deliberately all 36 instruction words, not the shared
 * 00C4801B first word used by several unrelated XBE vertex shaders. */
#ifndef DAH_UNLIT_VERTEX_H
#define DAH_UNLIT_VERTEX_H
#include "dah_farm_vertex.h"
static const uint32_t dah_unlit9_program[9][4] = {
    {0x00000000u,0x00C4801Bu,0x0836186Cu,0x28B00FF8u},
    {0x00000000u,0x00C4A01Bu,0x0836186Cu,0x24B00FF8u},
    {0x00000000u,0x00C4C01Bu,0x0836186Cu,0x22B00FF8u},
    {0x00000000u,0x00C4E01Bu,0x0836186Cu,0x21B01800u},
    {0x00000000u,0x0020021Bu,0x0836106Cu,0x2070F848u},
    {0x00000000u,0x0640401Bu,0xB4361BFEu,0xD018E800u},
    {0x00000000u,0x0020041Bu,0x0836106Cu,0x2070F818u},
    {0x00000000u,0x0080201Bu,0xC400286Cu,0x3070E800u},
    {0x00000000u,0x00376000u,0x0C36106Cu,0x2070F829u}
};
static unsigned dah_unlit9_program_kind(const uint32_t *p, const uint8_t *valid)
{
    if (!p || !valid) return 0u;
    for (unsigned i = 0; i < 9u * 4u; ++i)
        if (!valid[i] || p[i] != ((const uint32_t *)dah_unlit9_program)[i]) return 0u;
    return 14u;
}
/* Decoded NV2A program:
 * 0..3: DPH(v0,c36..39) => R11.xyzw / oPos.w
 * 4: MOV(v1) => oT0
 * 5: MUL(R11,c2), RCC(R11.w) => oPos.xyz / R1.x
 * 6: MOV(v2) => oD0
 * 7: MAD(R12,R1.x,c1) => oPos.xyz
 * 8: MOV(c187.x) => oFog
 */
static int dah_unlit9_vertex(const float pos[4], const float uv[4],
                             const float color[4], const float c[192][4],
                             DahMenuVertex *out)
{
    float clip[4];
    if (!pos || !uv || !color || !c || !out) return 0;
    for (unsigned i = 0; i < 4u; ++i) clip[i] = dah_farm_dph(pos, c[36u + i]);
    float rcc = dah_menu_rcc(clip[3]);
    for (unsigned i = 0; i < 3u; ++i)
        out->screen[i] = dah_farm_mul(dah_farm_mul(clip[i], c[2][i]), rcc) + c[1][i];
    out->screen[3] = clip[3];
    for (unsigned i = 0; i < 4u; ++i) out->diffuse[i] = color[i];
    out->uv[0] = uv[0]; out->uv[1] = uv[1];
    out->fog = c[187][0];
    for (unsigned i = 0; i < 4u; ++i)
        if (!dah_menu_finite(out->screen[i]) || !dah_menu_finite(out->diffuse[i])) return 0;
    return dah_menu_finite(out->uv[0]) && dah_menu_finite(out->uv[1]) &&
           dah_menu_finite(out->fog);
}
#endif
