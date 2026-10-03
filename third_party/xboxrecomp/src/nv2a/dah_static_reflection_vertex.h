/* Static reflection/lighting program used by small Hangar display meshes.
 * Captured from the Archives screen at submission 16501.  This path matters
 * for emissive details such as the red Crypto eyes: dropping the 57-index
 * strip removes the detail completely even though the main skin is present. */
#ifndef DAH_STATIC_REFLECTION_VERTEX_H
#define DAH_STATIC_REFLECTION_VERTEX_H
#include "dah_farm_vertex.h"

static const uint32_t dah_static_reflection_program[32][4] = {
    {0x00000000u,0x00E4001Bu,0x08361800u,0x28500000u},
    {0x00000000u,0x00E4201Bu,0x08363800u,0x24500000u},
    {0x00000000u,0x00E4401Bu,0x08365800u,0x22500000u},
    {0x00000000u,0x00A5C21Au,0x1835D800u,0x28000000u},
    {0x00000000u,0x02B7601Au,0x5434ABFEu,0xF1501854u},
    {0x00000000u,0x0EA4021Au,0x18341800u,0x18440000u},
    {0x00000000u,0x08A4221Au,0x18343BFDu,0x54410000u},
    {0x00000000u,0x0045E01Bu,0xFCAA2800u,0x2FB00000u},
    {0x00000000u,0x0040001Au,0x57FE2800u,0x2E500000u},
    {0x00000000u,0x00A4421Au,0x18345800u,0x22400000u},
    {0x00000000u,0x0066001Bu,0xB400106Cu,0x3FB00000u},
    {0x00000000u,0x00A0001Au,0x54348800u,0x21500000u},
    {0x00000000u,0x0060061Au,0xB4001068u,0xEEB00000u},
    {0x00000000u,0x006000FFu,0x540013FDu,0x51500000u},
    {0x00000000u,0x0049801Bu,0xB4379800u,0x2F000000u},
    {0x00000000u,0x0040001Au,0x45FEA800u,0x2E400000u},
    {0x00000000u,0x0069A01Bu,0x0400106Fu,0x7F200000u},
    {0x00000000u,0x0060001Au,0x44001469u,0x5EB00000u},
    {0x00000000u,0x02C4801Bu,0x0836986Cu,0x91A0181Cu},
    {0x00000000u,0x00C4A01Bu,0x0836B800u,0x24A00000u},
    {0x00000000u,0x00C4C01Bu,0x0836D800u,0x22A00000u},
    {0x00000000u,0x00C4E01Bu,0x0836F800u,0x21B01800u},
    {0x00000000u,0x004040DAu,0xA4345800u,0x20A0E800u},
    {0x00000000u,0x0642801Au,0x24349BFEu,0xDE280000u},
    {0x00000000u,0x00E7001Bu,0x08371800u,0x20B0F828u},
    {0x00000000u,0x0080201Au,0xC4002868u,0x70B0E800u},
    {0x00000000u,0x0062601Au,0x24001068u,0xF0B0E818u},
    {0x00000000u,0x00E9C41Bu,0x2837D800u,0x20A08848u},
    {0x00000000u,0x00E9E41Bu,0x2837F800u,0x20A04848u},
    {0x00000000u,0x00A3801Au,0xB4359800u,0x20A08850u},
    {0x00000000u,0x00A3A01Au,0xB435B800u,0x20A02850u},
    {0x00000000u,0x00A3C01Au,0xB435D800u,0x20B04851u}
};

/* Flight-saucer reflection variant captured at Farm submission 8618. It uses
 * the same math and outputs as the static reflection lift, but takes only
 * position, packed normal, and UV; the material has no v3 colour addend. */
static const uint32_t dah_saucer_reflection_program[31][4] = {
    {0x00000000u,0x00E4001Bu,0x08361800u,0x28500000u},
    {0x00000000u,0x00E4201Bu,0x08363800u,0x24500000u},
    {0x00000000u,0x00E4401Bu,0x08365800u,0x22500000u},
    {0x00000000u,0x00A5C21Au,0x1835D800u,0x28000000u},
    {0x00000000u,0x02B7601Au,0x5434ABFEu,0xF1501854u},
    {0x00000000u,0x0EA4021Au,0x18341800u,0x18440000u},
    {0x00000000u,0x08A4221Au,0x18343BFDu,0x54410000u},
    {0x00000000u,0x00A4421Au,0x18345800u,0x22400000u},
    {0x00000000u,0x0040001Au,0x57FE2800u,0x2E500000u},
    {0x00000000u,0x0045E01Bu,0xFCAA2800u,0x2FB00000u},
    {0x00000000u,0x00A0001Au,0x54348800u,0x21500000u},
    {0x00000000u,0x0066001Bu,0xB400106Cu,0x3FB00000u},
    {0x00000000u,0x006000FFu,0x540013FDu,0x51500000u},
    {0x00000000u,0x0049801Bu,0xB4379800u,0x2F000000u},
    {0x00000000u,0x0040001Au,0x45FEA800u,0x2E400000u},
    {0x00000000u,0x0069A01Bu,0x0400106Fu,0x7F200000u},
    {0x00000000u,0x0060001Au,0x44001469u,0x5EB00000u},
    {0x00000000u,0x02C4801Bu,0x0836986Cu,0x91A0181Cu},
    {0x00000000u,0x00C4A01Bu,0x0836B800u,0x24A00000u},
    {0x00000000u,0x00C4C01Bu,0x0836D800u,0x22A00000u},
    {0x00000000u,0x00C4E01Bu,0x0836F800u,0x21B01800u},
    {0x00000000u,0x004040DAu,0xA4345800u,0x20A0E800u},
    {0x00000000u,0x0642801Au,0x24349BFEu,0xDE280000u},
    {0x00000000u,0x00E7001Bu,0x08371800u,0x20B0F828u},
    {0x00000000u,0x0080201Au,0xC4002868u,0x70B0E800u},
    {0x00000000u,0x0062601Au,0x24001068u,0xF0B0E818u},
    {0x00000000u,0x00E9C41Bu,0x2837D800u,0x20A08848u},
    {0x00000000u,0x00E9E41Bu,0x2837F800u,0x20A04848u},
    {0x00000000u,0x00A3801Au,0xB4359800u,0x20A08850u},
    {0x00000000u,0x00A3A01Au,0xB435B800u,0x20A02850u},
    {0x00000000u,0x00A3C01Au,0xB435D800u,0x20B04851u}
};

static unsigned dah_static_reflection_program_kind(const uint32_t *p,
                                                    const uint8_t *valid)
{
    if (!p || !valid) return 0u;
    unsigned i;
    for (i = 0; i < 32u * 4u; ++i)
        if (!valid[i] || p[i] != ((const uint32_t *)dah_static_reflection_program)[i])
            break;
    if (i == 32u * 4u) return 29u;
    for (i = 0; i < 31u * 4u; ++i)
        if (!valid[i] || p[i] != ((const uint32_t *)dah_saucer_reflection_program)[i])
            break;
    return i == 31u * 4u ? 30u : 0u;
}

static int dah_static_reflection_vertex(const float v[4][4],
                                        const float c[192][4],
                                        DahMenuVertex *out, float tex1[4])
{
    float local[3], normal[3], unit[3], reflected[3], clip[4], color[4];
    float length_squared, inverse_length, doubled, diffuse_factor, reciprocal;
    if (!v || !c || !out || !tex1) return 0;
    for (unsigned i = 0; i < 4u; ++i)
        for (unsigned j = 0; j < 4u; ++j)
            if (!isfinite(v[i][j])) return 0;

    for (unsigned axis = 0; axis < 3u; ++axis) {
        local[axis] = dah_farm_dp4(v[0], c[32u + axis]);
        normal[axis] = dah_menu_dot3(v[1], c[32u + axis]);
    }
    length_squared = dah_menu_dot3(local, local);
    inverse_length = length_squared == 0.0f ? INFINITY :
        1.0f / sqrtf(fabsf(length_squared));
    for (unsigned axis = 0; axis < 3u; ++axis)
        unit[axis] = dah_farm_mul(-inverse_length, local[axis]);
    doubled = dah_menu_dot3(unit, normal);
    doubled += doubled;
    for (unsigned axis = 0; axis < 3u; ++axis)
        reflected[axis] = dah_farm_mul(normal[axis], doubled) - unit[axis];

    diffuse_factor = fmaxf(dah_menu_dot3(v[1], c[46]), 0.0f);
    for (unsigned component = 0; component < 4u; ++component)
        color[component] = dah_farm_mul(c[47][component], diffuse_factor) +
                           c[48][component];
    for (unsigned component = 0; component < 3u; ++component)
        color[component] += v[3][component];
    for (unsigned component = 0; component < 4u; ++component)
        color[component] = dah_farm_mul(color[component], c[76][component]) +
                           c[77][component];
    for (unsigned component = 0; component < 3u; ++component)
        out->diffuse[component] = dah_farm_mul(color[component], c[20][component]) +
                                  c[19][component];
    out->diffuse[3] = color[3];

    for (unsigned component = 0; component < 4u; ++component)
        clip[component] = dah_farm_dph(v[0], c[36u + component]);
    reciprocal = dah_menu_rcc(clip[3]);
    for (unsigned component = 0; component < 3u; ++component)
        out->screen[component] = dah_farm_mul(
            dah_farm_mul(clip[component], c[2][component]), reciprocal) +
            c[1][component];
    out->screen[3] = clip[3];
    out->fog = dah_farm_dp4(v[0], c[56]);
    out->uv[0] = dah_farm_dp4(v[2], c[78]);
    out->uv[1] = dah_farm_dp4(v[2], c[79]);
    tex1[0] = dah_menu_dot3(reflected, c[28]);
    tex1[1] = dah_menu_dot3(reflected, c[30]);
    tex1[2] = dah_menu_dot3(reflected, c[29]);
    tex1[3] = c[187][3];

    for (unsigned component = 0; component < 4u; ++component)
        if (!isfinite(out->screen[component]) ||
            !isfinite(out->diffuse[component]) || !isfinite(tex1[component]))
            return 0;
    return isfinite(out->uv[0]) && isfinite(out->uv[1]) && isfinite(out->fog);
}

#endif
