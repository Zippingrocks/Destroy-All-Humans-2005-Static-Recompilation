/* Original 57-instruction retail four-influence skin VSH, XBE offset 0x25037C.
 * The first 40 instruction words matched the live Farm capture byte for byte.
 * Keep this specialized path gated by all 228 instruction words and the exact
 * observed 40-byte interleaved array layout. */
#ifndef DAH_SKIN_VERTEX_H
#define DAH_SKIN_VERTEX_H
#include "dah_farm_vertex.h"
static const uint32_t dah_skin_program[57][4] = {
    {0x00000000u, 0x0057E61Bu, 0x3837F800u, 0x2FA00000u},
    {0x00000000u, 0x003760FFu, 0xBC001000u, 0x21B03850u},
    {0x00000000u, 0x01A00000u, 0xA4001000u, 0x20000000u},
    {0x00000000u, 0x00E9C81Bu, 0x4837D800u, 0x20B08848u},
    {0x00000000u, 0x00AAC21Au, 0x1834D800u, 0x28500002u},
    {0x00000000u, 0x00AAE21Au, 0x1834F800u, 0x24500002u},
    {0x00000000u, 0x00AB021Au, 0x18351800u, 0x22500002u},
    {0x00000000u, 0x00EAC01Bu, 0x0836D800u, 0x28000002u},
    {0x00000000u, 0x0040041Au, 0x54005000u, 0x2E900000u},
    {0x00000000u, 0x00EAE01Bu, 0x0836F800u, 0x24000002u},
    {0x00000000u, 0x00EB001Bu, 0x08371800u, 0x22000002u},
    {0x00000000u, 0x01A00055u, 0xA4001000u, 0x20000000u},
    {0x00000000u, 0x00400458u, 0x04005000u, 0x27800000u},
    {0x00000000u, 0x00AAC21Au, 0x1834D800u, 0x28600002u},
    {0x00000000u, 0x00AAE21Au, 0x1834F800u, 0x24600002u},
    {0x00000000u, 0x00AB021Au, 0x18351800u, 0x22600002u},
    {0x00000000u, 0x00EAC01Bu, 0x0836D800u, 0x21700002u},
    {0x00000000u, 0x0080041Au, 0x64AA506Au, 0x5E900000u},
    {0x00000000u, 0x00EAE01Bu, 0x0836F800u, 0x28700002u},
    {0x00000000u, 0x00EB001Bu, 0x08371800u, 0x22700002u},
    {0x00000000u, 0x01A000AAu, 0xA4001000u, 0x20000000u},
    {0x00000000u, 0x008004CAu, 0x74AA536Au, 0x1EA00000u},
    {0x00000000u, 0x00AAC21Au, 0x1834D800u, 0x28700002u},
    {0x00000000u, 0x00AAE21Au, 0x1834F800u, 0x24700002u},
    {0x00000000u, 0x00AB021Au, 0x18351800u, 0x22700002u},
    {0x00000000u, 0x00EAC01Bu, 0x0836D800u, 0x28200002u},
    {0x00000000u, 0x0080041Au, 0x7554506Au, 0x5E900000u},
    {0x00000000u, 0x00EAE01Bu, 0x0836F800u, 0x24200002u},
    {0x00000000u, 0x00EB001Bu, 0x08371800u, 0x22200002u},
    {0x00000000u, 0x01A000FFu, 0xA4001000u, 0x20000000u},
    {0x00000000u, 0x0080041Au, 0x2554506Au, 0x9EA00000u},
    {0x00000000u, 0x00AAC21Au, 0x1834D800u, 0x28800002u},
    {0x00000000u, 0x00AAE21Au, 0x1834F800u, 0x24800002u},
    {0x00000000u, 0x00AB021Au, 0x18351800u, 0x22800002u},
    {0x00000000u, 0x00EAC01Bu, 0x0836D800u, 0x28300002u},
    {0x00000000u, 0x0080041Au, 0x85FE506Au, 0x5E900000u},
    {0x00000000u, 0x00EAE01Bu, 0x0836F800u, 0x24300002u},
    {0x00000000u, 0x00EB001Bu, 0x08371800u, 0x22300002u},
    {0x00000000u, 0x00A5C01Au, 0x9435D800u, 0x28000000u},
    {0x00000000u, 0x0080041Au, 0x35FE506Au, 0x9EB00000u},
    {0x00000000u, 0x0EA3001Au, 0x94351800u, 0x18440000u},
    {0x00000000u, 0x00C4801Bu, 0xB4369800u, 0x28A00000u},
    {0x00000000u, 0x0045E01Bu, 0xFCAA2800u, 0x2F800000u},
    {0x00000000u, 0x0066001Bu, 0x8400106Cu, 0x3F800000u},
    {0x00000000u, 0x00C4A01Bu, 0xB436B800u, 0x24A00000u},
    {0x00000000u, 0x0049801Bu, 0x84379800u, 0x2F000000u},
    {0x00000000u, 0x0069A01Bu, 0x0400106Fu, 0x7F200000u},
    {0x00000000u, 0x00C4C01Bu, 0xB436D800u, 0x22A00000u},
    {0x00000000u, 0x00C4E01Bu, 0xB436F800u, 0x21A01800u},
    {0x00000000u, 0x0040401Au, 0xA4345800u, 0x20B0E800u},
    {0x00000000u, 0x0642801Au, 0x24349BFEu, 0x9E280000u},
    {0x00000000u, 0x02A3201Au, 0x9435386Cu, 0x9440181Cu},
    {0x00000000u, 0x0080201Au, 0xC4002868u, 0x70A0E800u},
    {0x00000000u, 0x0062601Au, 0x24001068u, 0xF0A0E818u},
    {0x00000000u, 0x00E7001Bu, 0xB4371800u, 0x20B0F828u},
    {0x00000000u, 0x00E9E81Bu, 0x4837F800u, 0x20B04848u},
    {0x00000000u, 0x0097C015u, 0x442BD857u, 0xB0B0C851u}
};
static unsigned dah_skin_program_kind(const uint32_t *p, const uint8_t *valid)
{
    if (!p || !valid) return 0u;
    for (unsigned i = 0; i < 57u * 4u; ++i)
        if (!valid[i] || p[i] != ((const uint32_t *)dah_skin_program)[i]) return 0u;
    return 13u;
}
static int dah_skin_vertex(const float v[5][4], const float c[192][4],
                           const uint8_t valid[192 * 4], DahMenuVertex *out,
                           float uv1[2], float skinned_out[3], float normal_out[3])
{
    float p[4] = {0.0f, 0.0f, 0.0f, 0.0f};
    float n[3] = {0.0f, 0.0f, 0.0f};
    float clip[4];
    if (!v || !c || !valid || !out || !uv1) return 0;
    p[3] = c[187][3];
    for (unsigned influence = 0; influence < 4u; ++influence) {
        /* An unused palette slot contributes exactly zero to both the MUL
         * and MAD chains in the retail VSH. The live first character draw
         * leaves later bone constants unwritten (and zero), while its byte
         * indices can still name those slots. Do not reject the whole mesh
         * for constants that this vertex has zero weight for. */
        if (v[2][influence] == 0.0f) continue;
        float palette = dah_farm_mul(v[3][influence], c[191][influence]);
        if (!dah_menu_finite(palette) || palette < -1000.0f || palette > 1000.0f)
            return 0;
        int base = 86 + (int)floorf(palette + 0.001f);
        if (base < 0 || base + 2 >= 192) return 0;
        for (unsigned axis = 0; axis < 3u; ++axis) {
            unsigned ci = (unsigned)(base + (int)axis);
            for (unsigned component = 0; component < 4u; ++component)
                if (!valid[ci * 4u + component] || !dah_menu_finite(c[ci][component]))
                    return 0;
            p[axis] += dah_farm_mul(v[2][influence], dah_farm_dp4(v[0], c[ci]));
            n[axis] += dah_farm_mul(v[2][influence], dah_menu_dot3(v[1], c[ci]));
        }
    }
    if (skinned_out) memcpy(skinned_out, p, 3u * sizeof(float));
    if (normal_out) memcpy(normal_out, n, 3u * sizeof(float));
    for (unsigned axis = 0; axis < 4u; ++axis)
        clip[axis] = dah_farm_dph(p, c[36u + axis]);
    float reciprocal = dah_menu_rcc(clip[3]);
    for (unsigned axis = 0; axis < 3u; ++axis)
        out->screen[axis] = dah_farm_mul(dah_farm_mul(clip[axis], c[2][axis]), reciprocal)
                            + c[1][axis];
    out->screen[3] = clip[3];
    float diffuse_factor = fmaxf(dah_menu_dot3(n, c[46]), 0.0f);
    for (unsigned axis = 0; axis < 4u; ++axis) {
        float lit = (dah_farm_mul(c[47][axis], diffuse_factor) + c[48][axis])
                    * c[76][axis] + c[77][axis];
        out->diffuse[axis] = axis < 3u ? dah_farm_mul(lit, c[20][axis]) + c[19][axis] : lit;
    }
    out->uv[0] = dah_farm_dp4(v[4], c[78]);
    out->uv[1] = dah_farm_dp4(v[4], c[79]);
    uv1[0] = dah_farm_mul(dah_menu_dot3(n, c[24]), c[190][0]) + c[190][0];
    uv1[1] = dah_farm_mul(dah_menu_dot3(n, c[25]), c[190][1]) + c[190][1];
    out->fog = dah_farm_dp4(p, c[56]);
    for (unsigned i = 0; i < 4u; ++i)
        if (!dah_menu_finite(out->screen[i]) || !dah_menu_finite(out->diffuse[i])) return 0;
    return dah_menu_finite(out->uv[0]) && dah_menu_finite(out->uv[1]) &&
           dah_menu_finite(uv1[0]) && dah_menu_finite(uv1[1]) &&
           dah_menu_finite(out->fog);
}
#endif
