/* Exact 21-instruction retail post-process vertex program used by the
 * animated CRT screens in Pox's Lab.  The effect samples a PGRAPH render
 * target with a per-frame lookup-table offset written to oT0. */
#ifndef DAH_POX_VERTEX_H
#define DAH_POX_VERTEX_H

#include "dah_farm_vertex.h"

static const uint32_t dah_pox_program[21][4] = {
    {0x00000000u,0x00C4801Bu,0x08369800u,0x28B00000u},
    {0x00000000u,0x00C4A01Bu,0x0836B800u,0x24B00000u},
    {0x00000000u,0x00C4C01Bu,0x0836D800u,0x22B00000u},
    {0x00000000u,0x00C4E01Bu,0x0836F800u,0x21B01800u},
    {0x00000000u,0x0040401Au,0xB4345800u,0x20A0E800u},
    {0x00000000u,0x0637C01Bu,0xEC0013FEu,0xD0A8F818u},
    {0x00000000u,0x02176000u,0x08001002u,0xF0B0F82Cu},
    {0x00000000u,0x0080201Au,0xC4002868u,0x70A0E800u},
    {0x00000000u,0x004FC015u,0xC42BD800u,0x2C200000u},
    {0x00000000u,0x0A000000u,0x08001000u,0x90B40000u},
    {0x00000000u,0x0A000000u,0x08001154u,0x90340000u},
    {0x00000000u,0x02000000u,0x08001156u,0xD0380004u},
    {0x00000000u,0x0000001Bu,0x0836106Cu,0x20B00000u},
    {0x00000000u,0x004FE015u,0x342BF800u,0x2C300000u},
    {0x00000000u,0x004FE055u,0x34ABF800u,0x24300000u},
    {0x00000000u,0x00600000u,0x34001154u,0xD8300000u},
    {0x00000000u,0x0000001Bu,0x0836106Cu,0x20B00000u},
    {0x00000000u,0x01A00000u,0x34001000u,0x20000000u},
    {0x00000000u,0x002C0015u,0x0C001000u,0x2C200002u},
    {0x00000000u,0x00400215u,0x25FE3000u,0x2CB00000u},
    {0x00000000u,0x00600015u,0xC4001056u,0xD0B0C849u}
};

static unsigned dah_pox_program_kind(const uint32_t *p, const uint8_t *valid)
{
    if (!p || !valid) return 0u;
    for (unsigned i = 0; i < 21u * 4u; ++i)
        if (!valid[i] || p[i] != ((const uint32_t *)dah_pox_program)[i]) return 0u;
    return 17u;
}

static int dah_pox_constant_valid(const uint8_t valid[192 * 4], unsigned index)
{
    if (!valid || index >= 192u) return 0;
    for (unsigned component = 0; component < 4u; ++component)
        if (!valid[index * 4u + component]) return 0;
    return 1;
}

static int dah_pox_vertex(const float pos[4], const float packed[4],
                          const float c[192][4], const uint8_t valid[192 * 4],
                          DahMenuVertex *out)
{
    float clip[4], projected[3], frac_x, frac_y, lookup_value;
    int address;
    if (!pos || !packed || !c || !valid || !out) return 0;

    for (unsigned i = 0; i < 4u; ++i) clip[i] = dah_farm_dph(pos, c[36u + i]);
    {
        float rcc = dah_menu_rcc(clip[3]);
        for (unsigned i = 0; i < 3u; ++i) {
            projected[i] = dah_farm_mul(dah_farm_mul(clip[i], c[2][i]), rcc) + c[1][i];
            out->screen[i] = projected[i];
        }
    }
    out->screen[3] = clip[3];
    for (unsigned i = 0; i < 4u; ++i) out->diffuse[i] = c[190][i];
    out->fog = c[187][0];

    frac_x = projected[0] * c[126][0];
    frac_y = projected[1] * c[126][1];
    frac_x -= floorf(frac_x);
    frac_y -= floorf(frac_y);
    /* Instructions 13 and 14 both multiply R3.y by c127.y. */
    lookup_value = frac_x * c[127][0] +
                   frac_y * c[127][1] * c[127][1];
    address = 96 + (int)floorf(lookup_value + 0.001f);
    if (address < 0 || address >= 192 || !dah_pox_constant_valid(valid, (unsigned)address))
        return 0;
    out->uv[0] = projected[0] + c[address][0] * packed[3];
    out->uv[1] = projected[1] + c[address][1] * packed[3];

    for (unsigned i = 0; i < 4u; ++i)
        if (!dah_menu_finite(out->screen[i]) || !dah_menu_finite(out->diffuse[i])) return 0;
    return dah_menu_finite(out->uv[0]) && dah_menu_finite(out->uv[1]) &&
           dah_menu_finite(out->fog);
}

/* Common 16-instruction UI mesh program used by the Pox display layers. */
static const uint32_t dah_pox_ui_program[16][4] = {
    {0x00000000u,0x00C4801Bu,0x0836186Cu,0x28200FF8u},
    {0x00000000u,0x00C4A01Bu,0x0836186Cu,0x24200FF8u},
    {0x00000000u,0x00C4C01Bu,0x0836186Cu,0x22200FF8u},
    {0x00000000u,0x00C4E01Bu,0x0836186Cu,0x21301800u},
    {0x00000000u,0x0025E01Bu,0x0C36106Cu,0x2F400FF8u},
    {0x00000000u,0x0640401Bu,0x24361BFCu,0xD018E800u},
    {0x00000000u,0x0066001Bu,0x4436106Cu,0x3F500FF8u},
    {0x00000000u,0x0080201Bu,0xC400286Cu,0x3070E800u},
    {0x00000000u,0x0049801Bu,0x5436186Cu,0x2F600FF8u},
    {0x00000000u,0x0069A01Bu,0x6436106Cu,0x3F700FF8u},
    {0x00000000u,0x00E9C41Bu,0x0836186Cu,0x20708848u},
    {0x00000000u,0x0042801Au,0x7434186Cu,0x2E800FF8u},
    {0x00000000u,0x0062601Au,0x84361068u,0x3E700FF8u},
    {0x00000000u,0x00E9E41Bu,0x0836186Cu,0x20704848u},
    {0x00000000u,0x0040021Bu,0x7436106Cu,0x2070F818u},
    {0x00000000u,0x00E7001Bu,0x0836186Cu,0x2070F829u}
};

static unsigned dah_pox_ui_program_kind(const uint32_t *p, const uint8_t *valid)
{
    if (!p || !valid) return 0u;
    for (unsigned i = 0; i < 16u * 4u; ++i)
        if (!valid[i] || p[i] != ((const uint32_t *)dah_pox_ui_program)[i]) return 0u;
    return 18u;
}

static int dah_pox_ui_vertex(const float pos[4], const float color[4],
                             const float tex[4], const float c[192][4],
                             DahMenuVertex *out)
{
    float clip[4], rcc;
    if (!pos || !color || !tex || !c || !out) return 0;
    for (unsigned i = 0; i < 4u; ++i) clip[i] = dah_farm_dph(pos, c[36u + i]);
    rcc = dah_menu_rcc(clip[3]);
    for (unsigned i = 0; i < 3u; ++i)
        out->screen[i] = dah_farm_mul(dah_farm_mul(clip[i], c[2][i]), rcc) + c[1][i];
    out->screen[3] = clip[3];
    out->uv[0] = dah_farm_dp4(tex, c[78]);
    out->uv[1] = dah_farm_dp4(tex, c[79]);
    /* The second DP4 writes R7 before the final MUL R7,v1 -> oD0. */
    for (unsigned i = 0; i < 4u; ++i) out->diffuse[i] = out->uv[1] * color[i];
    out->fog = dah_farm_dp4(pos, c[56]);
    for (unsigned i = 0; i < 4u; ++i)
        if (!dah_menu_finite(out->screen[i]) || !dah_menu_finite(out->diffuse[i])) return 0;
    return dah_menu_finite(out->uv[0]) && dah_menu_finite(out->uv[1]) &&
           dah_menu_finite(out->fog);
}

#endif
