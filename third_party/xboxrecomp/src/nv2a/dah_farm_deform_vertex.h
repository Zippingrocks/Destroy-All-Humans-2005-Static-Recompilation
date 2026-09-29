/* Exact retail farm deformation programs recovered from the xemu reference.
 * These programs render animated/deformed scenery that must not be approximated
 * by the ordinary static farm vertex path: rejecting one vertex rejects the
 * complete indexed strip and presents as missing or flickering geometry. */
#ifndef DAH_FARM_DEFORM_VERTEX_H
#define DAH_FARM_DEFORM_VERTEX_H
#include "dah_farm_vertex.h"

static const uint32_t dah_farm_deform_program[36][4] = {
 {0x00000000u,0x0057E61Au,0x3835F800u,0x2EA00000u},{0x00000000u,0x02176000u,0x0800106Eu,0xF0B0F81Cu},
 {0x00000000u,0x03B78000u,0xA400106Fu,0x3000F83Cu},{0x00000000u,0x00EAC01Bu,0x0836D800u,0x28500002u},
 {0x00000000u,0x00EAE01Bu,0x0836F800u,0x24500002u},{0x00000000u,0x00EB001Bu,0x08371800u,0x22500002u},
 {0x00000000u,0x01A00055u,0xA4001000u,0x20000000u},{0x00000000u,0x00EAC21Bu,0x1836D800u,0x28600002u},
 {0x00000000u,0x00EAE21Bu,0x1836F800u,0x24600002u},{0x00000000u,0x00EB021Bu,0x18371800u,0x22600002u},
 {0x00000000u,0x01A000AAu,0xA4001000u,0x20000000u},{0x00000000u,0x0060001Au,0x64001469u,0x5E000000u},
 {0x00000000u,0x00EAC41Bu,0x2836D800u,0x28700002u},{0x00000000u,0x00EAE41Bu,0x2836F800u,0x24700002u},
 {0x00000000u,0x00EB041Bu,0x28371800u,0x22700002u},{0x00000000u,0x0060001Au,0x74001469u,0x5EB00000u},
 {0x00000000u,0x0000001Bu,0x0836106Cu,0x20A00000u},{0x00000000u,0x00400085u,0x04C16800u,0x2E200000u},
 {0x00000000u,0x00800060u,0x050B6C68u,0x9E200000u},{0x00000000u,0x0000001Bu,0x0836106Cu,0x20B00000u},
 {0x00000000u,0x00A0001Au,0x24344800u,0x21200000u},{0x00000000u,0x08000000u,0x080013FCu,0x90210000u},
 {0x00000000u,0x0000001Bu,0x0836106Cu,0x20A00000u},{0x00000000u,0x0040001Au,0x25FE4800u,0x2E800000u},
 {0x00000000u,0x00A5C01Au,0xEC350800u,0x28B00000u},{0x00000000u,0x0000001Bu,0x0836106Cu,0x20A00000u},
 {0x00000000u,0x0177A000u,0xB401B800u,0x28B00000u},{0x00000000u,0x0045C000u,0xB5FFD800u,0x21B00000u},
 {0x00000000u,0x0085C0FFu,0xB435D869u,0x5E000000u},{0x00000000u,0x00C4801Bu,0x04369800u,0x28B00000u},
 {0x00000000u,0x00C4A01Bu,0x0436B800u,0x24B00000u},{0x00000000u,0x00C4C01Bu,0x0436D800u,0x22B00000u},
 {0x00000000u,0x00C4E01Bu,0x0436F800u,0x21B01800u},{0x00000000u,0x0040401Au,0xB4345800u,0x20A0E800u},
 {0x00000000u,0x06000000u,0x080013FEu,0xD0B80000u},{0x00000000u,0x0080201Au,0xC4016868u,0x70B0E801u}
};

static const uint32_t dah_farm_push_program[13][4] = {
 {0x00000000u,0x00A5C21Au,0xEC343000u,0x28B00000u},{0x00000000u,0x02176000u,0x0800106Eu,0xF0A0F81Cu},
 {0x00000000u,0x0177A000u,0xB401B800u,0x28B00000u},{0x00000000u,0x0045C000u,0xB5FFD800u,0x21B00000u},
 {0x00000000u,0x0085C0FFu,0xB435D868u,0x2E000000u},{0x00000000u,0x02178000u,0x0800106Fu,0x30A0F83Cu},
 {0x00000000u,0x00C4801Bu,0x04369800u,0x28B00000u},{0x00000000u,0x00C4A01Bu,0x0436B800u,0x24B00000u},
 {0x00000000u,0x00C4C01Bu,0x0436D800u,0x22B00000u},{0x00000000u,0x00C4E01Bu,0x0436F800u,0x21B01800u},
 {0x00000000u,0x0040401Au,0xB4345800u,0x20A0E800u},{0x00000000u,0x06000000u,0x080013FEu,0xD0B80000u},
 {0x00000000u,0x0080201Au,0xC4016868u,0x70B0E801u}
};

static const uint32_t dah_farm_constant_program[8][4] = {
 {0x00000000u,0x00C4801Bu,0x0836186Cu,0x28B00FF8u},{0x00000000u,0x00C4A01Bu,0x0836186Cu,0x24B00FF8u},
 {0x00000000u,0x00C4C01Bu,0x0836186Cu,0x22B00FF8u},{0x00000000u,0x00C4E01Bu,0x0836186Cu,0x21B01800u},
 {0x00000000u,0x0037601Bu,0x0C36106Cu,0x2070F818u},{0x00000000u,0x0640401Bu,0xB4361BFEu,0xD018E800u},
 {0x00000000u,0x0037801Bu,0x0C36106Cu,0x2070F838u},{0x00000000u,0x0080201Bu,0xC400286Cu,0x3070E801u}
};

static int dah_farm_exact_words(const uint32_t *words,const uint8_t *valid,
                                const uint32_t *expected,unsigned count)
{
    if(!words||!valid)return 0;
    for(unsigned i=0;i<count*4u;++i)if(!valid[i]||words[i]!=expected[i])return 0;
    return 1;
}

/* Kinds continue the shared exact-program namespace used by the renderer. */
static unsigned dah_farm_deform_program_kind(const uint32_t *words,const uint8_t *valid)
{
    if(dah_farm_exact_words(words,valid,&dah_farm_deform_program[0][0],36u))return 22u;
    if(dah_farm_exact_words(words,valid,&dah_farm_push_program[0][0],13u))return 23u;
    if(dah_farm_exact_words(words,valid,&dah_farm_constant_program[0][0],8u))return 24u;
    return 0u;
}

static int dah_farm_deform_constants(const uint8_t *valid,unsigned base)
{
    if(base+2u>=192u)return 0;
    for(unsigned i=0;i<3u;++i)for(unsigned j=0;j<4u;++j)
        if(!valid[(base+i)*4u+j])return 0;
    return 1;
}

static void dah_farm_deform_finish(const float position[4],const float c[192][4],
                                   DahMenuVertex *result)
{
    float clip[4];
    for(unsigned j=0;j<4u;++j)clip[j]=dah_farm_dph(position,c[36u+j]);
    float reciprocal=dah_menu_rcc(clip[3]);
    for(unsigned j=0;j<3u;++j)
        result->screen[j]=dah_farm_mul(dah_farm_mul(clip[j],c[2][j]),reciprocal)+c[1][j];
    result->screen[3]=clip[3];
    result->uv[0]=result->uv[1]=0.0f;
    result->fog=1.0f;
}

static int dah_farm_deform_vertex(const float v[4][4],const float c[192][4],
                                  const uint8_t *valid,DahMenuVertex *out)
{
    float r10[3],p0[3],p1[3],p2[3],edge0[3],edge1[3],cross[3],normal[3],position[4]={0,0,0,1};
    int base[3];
    if(!v||!c||!valid||!out)return 0;
    for(unsigned i=0;i<4u;++i)for(unsigned j=0;j<4u;++j)if(!dah_menu_finite(v[i][j]))return 0;
    for(unsigned j=0;j<3u;++j){
        r10[j]=dah_farm_mul(v[3][j],c[191][j]);
        if(!dah_menu_finite(r10[j]))return 0;
        base[j]=(int)floorf(r10[j]+0.001f)+86;
        if(base[j]<0||!dah_farm_deform_constants(valid,(unsigned)base[j]))return 0;
    }
    for(unsigned j=0;j<3u;++j){
        p0[j]=dah_farm_dp4(v[0],c[base[0]+j]);
        p1[j]=dah_farm_dp4(v[1],c[base[1]+j]);
        p2[j]=dah_farm_dp4(v[2],c[base[2]+j]);
    }
    for(unsigned j=0;j<3u;++j){edge0[j]=p1[j]-p0[j];edge1[j]=p2[j]-p0[j];}
    cross[0]=dah_farm_mul(edge0[1],edge1[2])-dah_farm_mul(edge0[2],edge1[1]);
    cross[1]=dah_farm_mul(edge0[2],edge1[0])-dah_farm_mul(edge0[0],edge1[2]);
    cross[2]=dah_farm_mul(edge0[0],edge1[1])-dah_farm_mul(edge0[1],edge1[0]);
    float length2=dah_menu_dot3(cross,cross);
    float inv_length=length2==0.0f?INFINITY:(isinf(length2)?0.0f:1.0f/sqrtf(fabsf(length2)));
    for(unsigned j=0;j<3u;++j)normal[j]=dah_farm_mul(cross[j],inv_length);
    float facing=dah_menu_dot3(c[46],normal);
    float push=(facing<c[189][0]?1.0f:0.0f)*c[46][3];
    for(unsigned j=0;j<3u;++j)position[j]=dah_farm_mul(push,c[46][j])+p0[j];
    dah_farm_deform_finish(position,c,out);
    memcpy(out->diffuse,c[187],sizeof(out->diffuse));
    for(unsigned j=0;j<4u;++j)if(!dah_menu_finite(out->screen[j])||!dah_menu_finite(out->diffuse[j]))return 0;
    return 1;
}

static int dah_farm_push_vertex(const float position_in[4],const float normal[4],
                                const float c[192][4],DahMenuVertex *out)
{
    float position[4]={position_in[0],position_in[1],position_in[2],position_in[3]};
    float facing=dah_menu_dot3(c[46],normal);
    float push=(facing<c[189][0]?1.0f:0.0f)*c[46][3];
    for(unsigned j=0;j<3u;++j)position[j]=dah_farm_mul(push,c[46][j])+position_in[j];
    dah_farm_deform_finish(position,c,out);
    memcpy(out->diffuse,c[187],sizeof(out->diffuse));
    for(unsigned j=0;j<4u;++j)if(!dah_menu_finite(out->screen[j])||!dah_menu_finite(out->diffuse[j]))return 0;
    return 1;
}

static int dah_farm_constant_vertex(const float position[4],const float c[192][4],
                                    DahMenuVertex *out)
{
    dah_farm_deform_finish(position,c,out);
    memcpy(out->diffuse,c[187],sizeof(out->diffuse));
    /* This program leaves oFog unwritten. The NV2A wrapper supplies the
     * disabled-fog value later; zero is the exact programmable output. */
    out->fog=0.0f;
    for(unsigned j=0;j<4u;++j)if(!dah_menu_finite(out->screen[j])||!dah_menu_finite(out->diffuse[j]))return 0;
    return 1;
}
#endif
