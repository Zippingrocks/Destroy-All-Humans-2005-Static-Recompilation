/* Exact Pox's Lab character programs captured from the retail game.
 * The first program is a four-influence skin shader. The second applies four
 * morph targets from attributes 10..13 before the same skin and lighting path. */
#ifndef DAH_POX_SKIN_VERTEX_H
#define DAH_POX_SKIN_VERTEX_H
#include "dah_skin_vertex.h"
static const uint32_t dah_pox_skin_program[62][4] = {
    {0x00000000u,0x0057E61Bu,0x3837F800u,0x2FA00000u},
    {0x00000000u,0x003760FFu,0xBC001000u,0x21B03850u},
    {0x00000000u,0x01A00000u,0xA4001000u,0x20000000u},
    {0x00000000u,0x00E9C81Bu,0x4837D800u,0x20B08848u},
    {0x00000000u,0x00AAC21Au,0x1834D800u,0x28500002u},
    {0x00000000u,0x00AAE21Au,0x1834F800u,0x24500002u},
    {0x00000000u,0x00AB021Au,0x18351800u,0x22500002u},
    {0x00000000u,0x00EAC01Bu,0x0836D800u,0x28000002u},
    {0x00000000u,0x0040041Au,0x54005000u,0x2E900000u},
    {0x00000000u,0x00EAE01Bu,0x0836F800u,0x24000002u},
    {0x00000000u,0x00EB001Bu,0x08371800u,0x22000002u},
    {0x00000000u,0x01A00055u,0xA4001000u,0x20000000u},
    {0x00000000u,0x00400458u,0x04005000u,0x27800000u},
    {0x00000000u,0x00AAC21Au,0x1834D800u,0x28600002u},
    {0x00000000u,0x00AAE21Au,0x1834F800u,0x24600002u},
    {0x00000000u,0x00AB021Au,0x18351800u,0x22600002u},
    {0x00000000u,0x00EAC01Bu,0x0836D800u,0x21700002u},
    {0x00000000u,0x0080041Au,0x64AA506Au,0x5E900000u},
    {0x00000000u,0x00EAE01Bu,0x0836F800u,0x28700002u},
    {0x00000000u,0x00EB001Bu,0x08371800u,0x22700002u},
    {0x00000000u,0x01A000AAu,0xA4001000u,0x20000000u},
    {0x00000000u,0x008004CAu,0x74AA536Au,0x1EA00000u},
    {0x00000000u,0x00AAC21Au,0x1834D800u,0x28700002u},
    {0x00000000u,0x00AAE21Au,0x1834F800u,0x24700002u},
    {0x00000000u,0x00AB021Au,0x18351800u,0x22700002u},
    {0x00000000u,0x00EAC01Bu,0x0836D800u,0x28200002u},
    {0x00000000u,0x0080041Au,0x7554506Au,0x5E900000u},
    {0x00000000u,0x00EAE01Bu,0x0836F800u,0x24200002u},
    {0x00000000u,0x00EB001Bu,0x08371800u,0x22200002u},
    {0x00000000u,0x01A000FFu,0xA4001000u,0x20000000u},
    {0x00000000u,0x0080041Au,0x2554506Au,0x9EA00000u},
    {0x00000000u,0x00AAC21Au,0x1834D800u,0x28800002u},
    {0x00000000u,0x00AAE21Au,0x1834F800u,0x24800002u},
    {0x00000000u,0x00AB021Au,0x18351800u,0x22800002u},
    {0x00000000u,0x00EAC01Bu,0x0836D800u,0x28300002u},
    {0x00000000u,0x0080041Au,0x85FE506Au,0x5E900000u},
    {0x00000000u,0x00EAE01Bu,0x0836F800u,0x24300002u},
    {0x00000000u,0x0048401Bu,0x2C012800u,0x2F000000u},
    {0x00000000u,0x0088201Bu,0x1CAB286Cu,0x1F000000u},
    {0x00000000u,0x0088001Bu,0x0D55286Cu,0x1F000000u},
    {0x00000000u,0x00EB001Bu,0x08371800u,0x22300002u},
    {0x00000000u,0x0137601Bu,0x04377800u,0x2F000000u},
    {0x00000000u,0x0157A01Bu,0x0437B800u,0x2F000000u},
    {0x00000000u,0x0046201Bu,0x1C000800u,0x2F800000u},
    {0x00000000u,0x0080041Au,0x35FE506Au,0x9EB00000u},
    {0x00000000u,0x0086401Bu,0x2CAA086Eu,0x1FA00000u},
    {0x00000000u,0x0086601Bu,0x3D54086Eu,0x9FA00000u},
    {0x00000000u,0x0085E01Bu,0xFDFE086Eu,0x9FA00000u},
    {0x00000000u,0x00C4801Bu,0xB4369800u,0x21800000u},
    {0x00000000u,0x0066001Bu,0xA400106Cu,0x3FA00000u},
    {0x00000000u,0x00C4A01Bu,0xB436B800u,0x24800000u},
    {0x00000000u,0x0049801Bu,0xA4379800u,0x2F000000u},
    {0x00000000u,0x0069A01Bu,0x0400106Fu,0x7F200000u},
    {0x00000000u,0x00C4C01Bu,0xB436D800u,0x22800000u},
    {0x00000000u,0x00C4E01Bu,0xB436F800u,0x21A01800u},
    {0x00000000u,0x004040DAu,0x84345800u,0x20B0E800u},
    {0x00000000u,0x0642801Au,0x24349BFEu,0x9E280000u},
    {0x00000000u,0x02A3001Au,0x9435186Cu,0x9840181Cu},
    {0x00000000u,0x00A3201Au,0x94353800u,0x24400000u},
    {0x00000000u,0x0080201Au,0xC4002868u,0x70A0E800u},
    {0x00000000u,0x0062601Au,0x24001068u,0xF0A0E818u},
    {0x00000000u,0x00E7001Bu,0xB4371800u,0x20B0F828u},
};
static const uint32_t dah_pox_morph_program[62][4] = {
    {0x00000000u,0x0057E61Bu,0x3837F800u,0x2FA00000u},
    {0x00000000u,0x0020001Bu,0x08001000u,0x2FB00000u},
    {0x00000000u,0x01A00000u,0xA4001000u,0x20000000u},
    {0x00000000u,0x008AB41Au,0xA800B86Au,0xDEB00000u},
    {0x00000000u,0x008AB61Au,0xB8AAB86Au,0xDEB00000u},
    {0x00000000u,0x008AB81Au,0xC954B86Au,0xDEB00000u},
    {0x00000000u,0x008ABA1Au,0xD9FEB86Au,0xDEB00000u},
    {0x00000000u,0x00AAC21Au,0x1834D800u,0x28500002u},
    {0x00000000u,0x00AAE21Au,0x1834F800u,0x24500002u},
    {0x00000000u,0x00AB021Au,0x18351800u,0x22500002u},
    {0x00000000u,0x00EAC01Bu,0xB436D800u,0x28000002u},
    {0x00000000u,0x0040041Au,0x54005000u,0x2E900000u},
    {0x00000000u,0x00EAE01Bu,0xB436F800u,0x24000002u},
    {0x00000000u,0x00EB001Bu,0xB4371800u,0x22000002u},
    {0x00000000u,0x01A00055u,0xA4001000u,0x20000000u},
    {0x00000000u,0x00400458u,0x04005000u,0x27800000u},
    {0x00000000u,0x00AAC21Au,0x1834D800u,0x28600002u},
    {0x00000000u,0x00AAE21Au,0x1834F800u,0x24600002u},
    {0x00000000u,0x00AB021Au,0x18351800u,0x22600002u},
    {0x00000000u,0x00EAC01Bu,0xB436D800u,0x21700002u},
    {0x00000000u,0x0080041Au,0x64AA506Au,0x5E900000u},
    {0x00000000u,0x00EAE01Bu,0xB436F800u,0x28700002u},
    {0x00000000u,0x00EB001Bu,0xB4371800u,0x22700002u},
    {0x00000000u,0x01A000AAu,0xA4001000u,0x20000000u},
    {0x00000000u,0x008004CAu,0x74AA536Au,0x1EA00000u},
    {0x00000000u,0x00AAC21Au,0x1834D800u,0x28700002u},
    {0x00000000u,0x00AAE21Au,0x1834F800u,0x24700002u},
    {0x00000000u,0x00AB021Au,0x18351800u,0x22700002u},
    {0x00000000u,0x00EAC01Bu,0xB436D800u,0x28200002u},
    {0x00000000u,0x0080041Au,0x7554506Au,0x5E900000u},
    {0x00000000u,0x00EAE01Bu,0xB436F800u,0x24200002u},
    {0x00000000u,0x00EB001Bu,0xB4371800u,0x22200002u},
    {0x00000000u,0x01A000FFu,0xA4001000u,0x20000000u},
    {0x00000000u,0x0080041Au,0x2554506Au,0x9EA00000u},
    {0x00000000u,0x00AAC21Au,0x1834D800u,0x28800002u},
    {0x00000000u,0x00AAE21Au,0x1834F800u,0x24800002u},
    {0x00000000u,0x00AB021Au,0x18351800u,0x22800002u},
    {0x00000000u,0x00EAC01Bu,0xB436D800u,0x28300002u},
    {0x00000000u,0x0080041Au,0x85FE506Au,0x5E900000u},
    {0x00000000u,0x00EAE01Bu,0xB436F800u,0x24300002u},
    {0x00000000u,0x0048401Bu,0x2C012800u,0x2F000000u},
    {0x00000000u,0x0088201Bu,0x1CAB286Cu,0x1F000000u},
    {0x00000000u,0x0088001Bu,0x0D55286Cu,0x1F000000u},
    {0x00000000u,0x00EB001Bu,0xB4371800u,0x22300002u},
    {0x00000000u,0x0137601Bu,0x04377800u,0x2F000000u},
    {0x00000000u,0x0157A01Bu,0x0437B800u,0x2F000000u},
    {0x00000000u,0x0046201Bu,0x1C000800u,0x2FB00000u},
    {0x00000000u,0x0080041Au,0x35FE506Au,0x9EA00000u},
    {0x00000000u,0x003760FFu,0xBC001000u,0x21A03850u},
    {0x00000000u,0x0086401Bu,0x2CAA086Eu,0xDFB00000u},
    {0x00000000u,0x0086601Bu,0x3D54086Eu,0xDFB00000u},
    {0x00000000u,0x0085E01Bu,0xFDFE086Eu,0xDFB00000u},
    {0x00000000u,0x00C4801Bu,0xA4369800u,0x21800000u},
    {0x00000000u,0x0066001Bu,0xB400106Cu,0x3FB00000u},
    {0x00000000u,0x00C4A01Bu,0xA436B800u,0x24800000u},
    {0x00000000u,0x0049801Bu,0xB4379800u,0x2F000000u},
    {0x00000000u,0x0069A01Bu,0x0400106Fu,0x7F200000u},
    {0x00000000u,0x00C4C01Bu,0xA436D800u,0x22800000u},
    {0x00000000u,0x00C4E01Bu,0xA436F800u,0x21B01800u},
    {0x00000000u,0x004040DAu,0x84345800u,0x20A0E800u},
    {0x00000000u,0x0642801Au,0x24349BFEu,0xDE280000u},
    {0x00000000u,0x02A3001Au,0x9435186Cu,0x9840181Cu},
};
static const uint32_t dah_pox_static_program[24][4] = {
    {0x00000000u,0x0048421Bu,0x2C003000u,0x2F000000u},
    {0x00000000u,0x00C4801Bu,0x08369800u,0x28B00000u},
    {0x00000000u,0x0088221Bu,0x1CAA306Cu,0x1F000000u},
    {0x00000000u,0x0088021Bu,0x0D54306Cu,0x1F000000u},
    {0x00000000u,0x00C4A01Bu,0x0836B800u,0x24B00000u},
    {0x00000000u,0x0137601Bu,0x04377800u,0x2F000000u},
    {0x00000000u,0x0157A01Bu,0x0437B800u,0x2F000000u},
    {0x00000000u,0x0046201Bu,0x1C000800u,0x2FA00000u},
    {0x00000000u,0x0086401Bu,0x2CAA086Eu,0x9FA00000u},
    {0x00000000u,0x0086601Bu,0x3D54086Eu,0x9FA00000u},
    {0x00000000u,0x0085E01Bu,0xFDFE086Eu,0x9FA00000u},
    {0x00000000u,0x00C4C01Bu,0x0836D800u,0x22B00000u},
    {0x00000000u,0x0066001Bu,0xA400106Cu,0x3FA00000u},
    {0x00000000u,0x00C4E01Bu,0x0836F800u,0x21B01800u},
    {0x00000000u,0x0049801Bu,0xA4379800u,0x2F000000u},
    {0x00000000u,0x0069A01Bu,0x0400106Fu,0x7F200000u},
    {0x00000000u,0x0040401Au,0xB4345800u,0x20A0E800u},
    {0x00000000u,0x0642801Au,0x24349BFEu,0xDE280000u},
    {0x00000000u,0x00E7001Bu,0x08371800u,0x20B0F828u},
    {0x00000000u,0x0080201Au,0xC4002868u,0x70B0E800u},
    {0x00000000u,0x00E9C41Bu,0x2837D800u,0x20B08848u},
    {0x00000000u,0x00E9E41Bu,0x2837F800u,0x20B04848u},
    {0x00000000u,0x0062601Au,0x24001068u,0xF0B0E818u},
    {0x00000000u,0x02000000u,0x0800106Cu,0x90B0181Du},
};
static unsigned dah_pox_skin_program_kind(const uint32_t *p,const uint8_t *valid)
{
    if(!p||!valid)return 0u;
    for(unsigned i=0;i<62u*4u;++i)
        if(!valid[i]||p[i]!=((const uint32_t*)dah_pox_skin_program)[i])return 0u;
    return 19u;
}
static unsigned dah_pox_morph_program_kind(const uint32_t *p,const uint8_t *valid)
{
    if(!p||!valid)return 0u;
    for(unsigned i=0;i<62u*4u;++i)
        if(!valid[i]||p[i]!=((const uint32_t*)dah_pox_morph_program)[i])return 0u;
    return 20u;
}
static unsigned dah_pox_static_program_kind(const uint32_t *p,const uint8_t *valid)
{
    if(!p||!valid)return 0u;
    for(unsigned i=0;i<24u*4u;++i)
        if(!valid[i]||p[i]!=((const uint32_t*)dah_pox_static_program)[i])return 0u;
    return 21u;
}
static int dah_pox_skin_lighting(const float normal[3],const float c[192][4],
                                 const uint8_t valid[192*4],DahMenuVertex *out)
{
    static const unsigned needed[]={47,48,49,50,51,64,65,66,76,77,187,189,19,20};
    float direction[4],lit[4];
    for(unsigned n=0;n<sizeof(needed)/sizeof(needed[0]);++n)
        for(unsigned axis=0;axis<4u;++axis)
            if(!valid[needed[n]*4u+axis]||!dah_menu_finite(c[needed[n]][axis]))return 0;
    for(unsigned axis=0;axis<4u;++axis){
        float d=dah_farm_mul(c[66][axis],normal[0]);
        d=dah_farm_mul(c[65][axis],normal[1])+d;
        d=dah_farm_mul(c[64][axis],normal[2])+d;
        direction[axis]=fmaxf(fminf(d,c[187][axis]),c[189][axis]);
    }
    for(unsigned axis=0;axis<4u;++axis){
        float l=dah_farm_mul(c[49][axis],direction[0]);
        l=dah_farm_mul(c[50][axis],direction[1])+l;
        l=dah_farm_mul(c[51][axis],direction[2])+l;
        l=dah_farm_mul(c[47][axis],direction[3])+l+c[48][axis];
        lit[axis]=dah_farm_mul(l,c[76][axis])+c[77][axis];
        out->diffuse[axis]=axis<3u?dah_farm_mul(lit[axis],c[20][axis])+c[19][axis]:lit[axis];
        if(!dah_menu_finite(out->diffuse[axis]))return 0;
    }
    return 1;
}
static int dah_pox_skin_vertex(const float v[9][4],const float c[192][4],
                               const uint8_t valid[192*4],int morph,
                               DahMenuVertex *out,float uv1[2])
{
    float inputs[5][4],normal[3];
    if(!v||!c||!valid||!out||!uv1)return 0;
    memcpy(inputs,v,sizeof inputs);
    if(morph){
        for(unsigned m=0;m<4u;++m){
            if(!valid[85u*4u+m]||!dah_menu_finite(c[85][m]))return 0;
            if(c[85][m]==0.0f)continue;
            for(unsigned axis=0;axis<3u;++axis){
                if(!dah_menu_finite(v[5u+m][axis]))return 0;
                inputs[0][axis]=dah_farm_mul(v[5u+m][axis],c[85][m])+inputs[0][axis];
            }
        }
    }
    if(!dah_skin_vertex(inputs,c,valid,out,uv1,NULL,normal))return 0;
    return dah_pox_skin_lighting(normal,c,valid,out);
}
static int dah_pox_static_vertex(const float position[4],const float normal[4],
                                 const float uv[4],const float c[192][4],
                                 const uint8_t valid[192*4],DahMenuVertex *out)
{
    float clip[4];
    if(!position||!normal||!uv||!c||!valid||!out)return 0;
    for(unsigned axis=0;axis<4u;++axis)clip[axis]=dah_farm_dph(position,c[36u+axis]);
    float reciprocal=dah_menu_rcc(clip[3]);
    for(unsigned axis=0;axis<3u;++axis)
        out->screen[axis]=dah_farm_mul(dah_farm_mul(clip[axis],c[2][axis]),reciprocal)+c[1][axis];
    out->screen[3]=clip[3];
    out->uv[0]=dah_farm_dp4(uv,c[78]);
    out->uv[1]=dah_farm_dp4(uv,c[79]);
    out->fog=dah_farm_dp4(position,c[56]);
    if(!dah_pox_skin_lighting(normal,c,valid,out))return 0;
    for(unsigned axis=0;axis<4u;++axis)
        if(!dah_menu_finite(out->screen[axis]))return 0;
    return dah_menu_finite(out->uv[0])&&dah_menu_finite(out->uv[1])&&dah_menu_finite(out->fog);
}
#endif
