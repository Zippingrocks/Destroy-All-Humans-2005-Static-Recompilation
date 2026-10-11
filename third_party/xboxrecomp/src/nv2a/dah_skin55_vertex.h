/* Retail 55-instruction four-influence skin VSH, exact gameplay capture.
 * Only the full 220-word signature enables this path. */
#ifndef DAH_SKIN55_VERTEX_H
#define DAH_SKIN55_VERTEX_H
#include "dah_skin_vertex.h"
static const uint32_t dah_skin55_program[55][4] = {
    {0x00000000u,0x0057E61Bu,0x3837F800u,0x2FA00000u},
    {0x00000000u,0x003760FFu,0xBC001000u,0x21B00000u},
    {0x00000000u,0x01A00000u,0xA4001000u,0x20000000u},
    {0x00000000u,0x00E9C81Bu,0x4837D800u,0x20B08848u},
    {0x00000000u,0x00AAC21Au,0x1834D800u,0x28500002u},
    {0x00000000u,0x00AAE21Au,0x1834F800u,0x24500002u},
    {0x00000000u,0x00AB021Au,0x18351800u,0x22500002u},
    {0x00000000u,0x00EAC01Bu,0x0836D800u,0x28000002u},
    {0x00000000u,0x00EAE01Bu,0x0836F800u,0x24000002u},
    {0x00000000u,0x00EB001Bu,0x08371800u,0x22000002u},
    {0x00000000u,0x01A00055u,0xA4001000u,0x20000000u},
    {0x00000000u,0x0040041Au,0x54005000u,0x2E900000u},
    {0x00000000u,0x00AAC21Au,0x1834D800u,0x28600002u},
    {0x00000000u,0x00AAE21Au,0x1834F800u,0x24600002u},
    {0x00000000u,0x00AB021Au,0x18351800u,0x22600002u},
    {0x00000000u,0x00EAC01Bu,0x0836D800u,0x21800002u},
    {0x00000000u,0x00EAE01Bu,0x0836F800u,0x24800002u},
    {0x00000000u,0x00EB001Bu,0x08371800u,0x22800002u},
    {0x00000000u,0x01A000AAu,0xA4001000u,0x20000000u},
    {0x00000000u,0x0040041Au,0x04005000u,0x2EA00000u},
    {0x00000000u,0x00AAC21Au,0x1834D800u,0x28700002u},
    {0x00000000u,0x00AAE21Au,0x1834F800u,0x24700002u},
    {0x00000000u,0x00AB021Au,0x18351800u,0x22700002u},
    {0x00000000u,0x0080041Au,0x64AA506Au,0x5E900000u},
    {0x00000000u,0x00EAC01Bu,0x0836D800u,0x28200002u},
    {0x00000000u,0x00EAE01Bu,0x0836F800u,0x24200002u},
    {0x00000000u,0x00EB001Bu,0x08371800u,0x22200002u},
    {0x00000000u,0x01A000FFu,0xA4001000u,0x20000000u},
    {0x00000000u,0x008004DAu,0x84AA506Au,0x9EA00000u},
    {0x00000000u,0x00AAC21Au,0x1834D800u,0x28800002u},
    {0x00000000u,0x00AAE21Au,0x1834F800u,0x24800002u},
    {0x00000000u,0x00AB021Au,0x18351800u,0x22800002u},
    {0x00000000u,0x0080041Au,0x7554506Au,0x5E900000u},
    {0x00000000u,0x00EAC01Bu,0x0836D800u,0x28300002u},
    {0x00000000u,0x00EAE01Bu,0x0836F800u,0x24300002u},
    {0x00000000u,0x00EB001Bu,0x08371800u,0x22300002u},
    {0x00000000u,0x0080041Au,0x2554506Au,0x9EA00000u},
    {0x00000000u,0x0080041Au,0x85FE506Au,0x5E900000u},
    {0x00000000u,0x0080041Au,0x35FE506Au,0x9EB00000u},
    {0x00000000u,0x00A5C01Au,0x9435D800u,0x28000000u},
    {0x00000000u,0x00C4801Bu,0xB4369800u,0x28A00000u},
    {0x00000000u,0x0EC4A01Bu,0xB436B800u,0x14A40000u},
    {0x00000000u,0x00C4C01Bu,0xB436D800u,0x22A00000u},
    {0x00000000u,0x0045E01Bu,0xFCAA2800u,0x2F900000u},
    {0x00000000u,0x0066001Bu,0x9400106Cu,0x3F900000u},
    {0x00000000u,0x00C4E01Bu,0xB436F800u,0x21A01800u},
    {0x00000000u,0x0049801Bu,0x94379800u,0x2F000000u},
    {0x00000000u,0x0069A01Bu,0x0400106Fu,0x7F200000u},
    {0x00000000u,0x0040401Au,0xA4345800u,0x20B0E800u},
    {0x00000000u,0x0642801Au,0x24349BFEu,0x9E280000u},
    {0x00000000u,0x02000000u,0x0800106Cu,0x90B0181Cu},
    {0x00000000u,0x0080201Au,0xC4002868u,0x70A0E800u},
    {0x00000000u,0x0062601Au,0x24001068u,0xF0A0E818u},
    {0x00000000u,0x00E7001Bu,0xB4371800u,0x20B0F828u},
    {0x00000000u,0x00E9E81Bu,0x4837F800u,0x20B04849u}
};
static unsigned dah_skin55_program_kind(const uint32_t *p,const uint8_t *valid)
{
    if(!p||!valid)return 0u;
    for(unsigned i=0;i<55u*4u;++i)
        if(!valid[i]||p[i]!=((const uint32_t*)dah_skin55_program)[i])return 0u;
    return 15u;
}
/* Same four-influence transform and diffuse calculation as the 57-token
 * program, but this variant has no oT1 output: c24,c25,c190 need not exist. */
static int dah_skin55_vertex(const float v[5][4],const float c[192][4],
                             const uint8_t valid[192*4],DahMenuVertex *out)
{
    float p[4]={0,0,0,0},n[3]={0,0,0},clip[4];
    if(!v||!c||!valid||!out)return 0;
    p[3]=c[187][3];
    for(unsigned influence=0;influence<4u;++influence){
        if(v[2][influence]==0.0f)continue;
        float palette=dah_farm_mul(v[3][influence],c[191][influence]);
        if(!dah_menu_finite(palette)||palette< -1000.0f||palette>1000.0f)return 0;
        int base=86+(int)floorf(palette+0.001f);
        if(base<0||base+2>=192)return 0;
        for(unsigned axis=0;axis<3u;++axis){
            unsigned ci=(unsigned)(base+(int)axis);
            for(unsigned component=0;component<4u;++component)
                if(!valid[ci*4u+component]||!dah_menu_finite(c[ci][component]))return 0;
            p[axis]+=dah_farm_mul(v[2][influence],dah_farm_dp4(v[0],c[ci]));
            n[axis]+=dah_farm_mul(v[2][influence],dah_menu_dot3(v[1],c[ci]));
        }
    }
    for(unsigned axis=0;axis<4u;++axis)clip[axis]=dah_farm_dph(p,c[36u+axis]);
    float reciprocal=dah_menu_rcc(clip[3]);
    for(unsigned axis=0;axis<3u;++axis)
        out->screen[axis]=dah_farm_mul(dah_farm_mul(clip[axis],c[2][axis]),reciprocal)+c[1][axis];
    out->screen[3]=clip[3];
    float diffuse_factor=fmaxf(dah_menu_dot3(n,c[46]),0.0f);
    for(unsigned axis=0;axis<4u;++axis){
        float lit=(dah_farm_mul(c[47][axis],diffuse_factor)+c[48][axis])*c[76][axis]+c[77][axis];
        out->diffuse[axis]=axis<3u?dah_farm_mul(lit,c[20][axis])+c[19][axis]:lit;
    }
    out->uv[0]=dah_farm_dp4(v[4],c[78]);
    out->uv[1]=dah_farm_dp4(v[4],c[79]);
    out->fog=dah_farm_dp4(p,c[56]);
    for(unsigned i=0;i<4u;++i)
        if(!dah_menu_finite(out->screen[i])||!dah_menu_finite(out->diffuse[i]))return 0;
    return dah_menu_finite(out->uv[0])&&dah_menu_finite(out->uv[1])&&dah_menu_finite(out->fog);
}
#endif
