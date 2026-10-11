/* Exact-program adapter for the 17-slot retail DAH shader captured at
 * PID16548 submission771. Not a general NV2A shader interpreter.
 * Field decoding reference: local xemu vsh-prog.c; the equations below are
 * the decoded retail program, including paired LIT/RCC register behavior.
 * Portable float arithmetic is not a claim of bit-exact NV2A GPU rounding.
 * No scene positions, textures, constants or lighting values are invented. */
#ifndef DAH_MENU_VERTEX_H
#define DAH_MENU_VERTEX_H
#include <stdint.h>
#include <string.h>
#include <math.h>

static const uint32_t dah_menu_program[17][4] = {
    {0,0x00A5C21A,0x1835D800,0x28000000},
    {0,0x00C4801B,0x08369800,0x28B00000},
    {0,0x0EC4A01B,0x0836B800,0x14B40000},
    {0,0x00C4C01B,0x0836D800,0x22B00000},
    {0,0x0045E01B,0xFCAA2800,0x2FA00000},
    {0,0x0066001B,0xA400106C,0x3FA00000},
    {0,0x00C4E01B,0x0836F800,0x21B01800},
    {0,0x0049801B,0xA4379800,0x2F000000},
    {0,0x0069A01B,0x0400106F,0x7F200000},
    {0,0x0040401A,0xB4345800,0x20A0E800},
    {0,0x0642801A,0x24349BFE,0xDE280000},
    {0,0x00E7001B,0x08371800,0x20B0F828},
    {0,0x0080201A,0xC4002868,0x70B0E800},
    {0,0x00E9C41B,0x2837D800,0x20B08848},
    {0,0x00E9E41B,0x2837F800,0x20B04848},
    {0,0x0062601A,0x24001068,0xF0B0E818},
    {0,0x02000000,0x0800106C,0x90B0181D}
};

static const uint32_t dah_menu_lit_program[17][4] = {
    {0x00000000u,0x00A5C21Au,0x1835D800u,0x28000000u},
    {0x00000000u,0x00C4801Bu,0x08369800u,0x28B00000u},
    {0x00000000u,0x0EC4A01Bu,0x0836B800u,0x14B40000u},
    {0x00000000u,0x00C4C01Bu,0x0836D800u,0x22B00000u},
    {0x00000000u,0x0045E01Bu,0xFCAA2800u,0x2FA00000u},
    {0x00000000u,0x0066001Bu,0xA400106Cu,0x3FA00000u},
    {0x00000000u,0x00C4E01Bu,0x0836F800u,0x21B01800u},
    {0x00000000u,0x0060061Au,0xA4001068u,0xEEA00000u},
    {0x00000000u,0x0040401Au,0xB4345800u,0x2090E800u},
    {0x00000000u,0x0649801Bu,0xA4379BFEu,0xDF080000u},
    {0x00000000u,0x00E7001Bu,0x08371800u,0x20B0F828u},
    {0x00000000u,0x0069A01Bu,0x0400106Fu,0x7F200000u},
    {0x00000000u,0x0080201Au,0xC4002868u,0x70B0E800u},
    {0x00000000u,0x0242801Au,0x2434986Cu,0x9E20181Cu},
    {0x00000000u,0x00E9C41Bu,0x2837D800u,0x20B08848u},
    {0x00000000u,0x00E9E41Bu,0x2837F800u,0x20B04848u},
    {0x00000000u,0x0062601Au,0x24001068u,0xF0B0E819u}
};

static const uint32_t dah_reflection_program[21][4] = {
    {0x00000000u,0x00A5C21Au,0x1835D800u,0x28000000u},
    {0x00000000u,0x00C4801Bu,0x08369800u,0x28B00000u},
    {0x00000000u,0x0EC4A01Bu,0x0836B800u,0x14B40000u},
    {0x00000000u,0x00C4C01Bu,0x0836D800u,0x22B00000u},
    {0x00000000u,0x0045E01Bu,0xFCAA2800u,0x2FA00000u},
    {0x00000000u,0x0066001Bu,0xA400106Cu,0x3FA00000u},
    {0x00000000u,0x00C4E01Bu,0x0836F800u,0x21B01800u},
    {0x00000000u,0x0060061Au,0xA4001068u,0xEEA00000u},
    {0x00000000u,0x0040401Au,0xB4345800u,0x2090E800u},
    {0x00000000u,0x0649801Bu,0xA4379BFEu,0xDF080000u},
    {0x00000000u,0x00A3021Au,0x18351800u,0x28400000u},
    {0x00000000u,0x0069A01Bu,0x0400106Fu,0x7F200000u},
    {0x00000000u,0x00A3221Au,0x18353800u,0x24400000u},
    {0x00000000u,0x0242801Au,0x2434986Cu,0x9E20181Cu},
    {0x00000000u,0x0080201Au,0xC4002868u,0x70B0E800u},
    {0x00000000u,0x00E9C41Bu,0x2837D800u,0x20B08848u},
    {0x00000000u,0x00E9E41Bu,0x2837F800u,0x20B04848u},
    {0x00000000u,0x00E7001Bu,0x08371800u,0x20A0F828u},
    {0x00000000u,0x0097C015u,0x442BD857u,0xB0A0C850u},
    {0x00000000u,0x02176000u,0x080013FEu,0xF0B03854u},
    {0x00000000u,0x0062601Au,0x24001068u,0xF0B0E819u}
};

static const uint32_t dah_hull_program[20][4]={
    {0x00000000u,0x00a5c21au,0x1835d800u,0x28000000u},
    {0x00000000u,0x00c4801bu,0x08369800u,0x28b00000u},
    {0x00000000u,0x0ec4a01bu,0x0836b800u,0x14b40000u},
    {0x00000000u,0x00c4c01bu,0x0836d800u,0x22b00000u},
    {0x00000000u,0x0045e01bu,0xfcaa2800u,0x2fa00000u},
    {0x00000000u,0x0066001bu,0xa400106cu,0x3fa00000u},
    {0x00000000u,0x00c4e01bu,0x0836f800u,0x21b01800u},
    {0x00000000u,0x0049801bu,0xa4379800u,0x2f000000u},
    {0x00000000u,0x0069a01bu,0x0400106fu,0x7f200000u},
    {0x00000000u,0x0040401au,0xb4345800u,0x20a0e800u},
    {0x00000000u,0x06a3021au,0x18351bfeu,0xd8480000u},
    {0x00000000u,0x02a3221au,0x1835386cu,0x9440181cu},
    {0x00000000u,0x0042801au,0x24349800u,0x2e200000u},
    {0x00000000u,0x0080201au,0xc4002868u,0x70b0e800u},
    {0x00000000u,0x00e9c41bu,0x2837d800u,0x20b08848u},
    {0x00000000u,0x00e9e41bu,0x2837f800u,0x20b04848u},
    {0x00000000u,0x00e7001bu,0x08371800u,0x20a0f828u},
    {0x00000000u,0x0097c015u,0x442bd857u,0xb0a0c850u},
    {0x00000000u,0x02176000u,0x080013feu,0xf0b03854u},
    {0x00000000u,0x0062601au,0x24001068u,0xf0b0e819u}
};
typedef struct DahMenuVertex {
    float screen[4]; /* xyz in NV2A screen/depth units, w = native clip W */
    float diffuse[4];
    float uv[2];
    float fog;
} DahMenuVertex;

static int dah_menu_program_matches(const uint32_t *words, const uint8_t *valid)
{
    if (!words || !valid) return 0;
    for (unsigned i=0;i<68u;++i)
        if (!valid[i] || words[i] != dah_menu_program[i/4u][i%4u]) return 0;
    return 1;
}

static int dah_menu_program_kind(const uint32_t *words, const uint8_t *valid)
{
    if (words && valid) { unsigned i; for(i=0;i<84u;i++) if(!valid[i] || words[i]!=dah_reflection_program[i/4][i%4]) break; if(i==84u) return 3; }
    if(words && valid) { unsigned i;for(i=0;i<80u;i++)if(!valid[i] || words[i]!=dah_hull_program[i/4][i%4])break;if(i==80u)return 4; }
    if (dah_menu_program_matches(words, valid)) return 1;
    if (!words || !valid) return 0;
    for (unsigned i=0;i<68u;++i)
        if (!valid[i] || words[i] != dah_menu_lit_program[i/4u][i%4u]) return 0;
    return 2;
}

static int dah_menu_finite(float x);
static int dah_menu_constants_ready(const float c[192][4],const uint8_t *valid)
{
    static const uint8_t used[]={1,2,19,20,36,37,38,39,46,47,48,56,76,77,78,79};
    if (!c || !valid) return 0;
    for (unsigned i=0;i<sizeof(used);++i)
        for(unsigned j=0;j<4;++j)
            if(!valid[used[i]*4u+j] || !dah_menu_finite(c[used[i]][j])) return 0;
    return 1;
}

static float dah_menu_dot3(const float *a,const float *b)
{
    return (a[0]*b[0]+a[1]*b[1])+a[2]*b[2];
}

static float dah_menu_dot4(const float *a,const float *b)
{
    return dah_menu_dot3(a,b)+a[3]*b[3];
}

/* NV2A RCC clamps a reciprocal magnitude to [2^-64,2^64], preserving sign.
 * Input validation rejects NaNs; signed zero and infinity retain sign here. */
static float dah_menu_rcc(float w)
{
    float r=1.0f/w, magnitude=fabsf(r);
    if(magnitude<0x1p-64f) magnitude=0x1p-64f;
    if(magnitude>0x1p64f) magnitude=0x1p64f;
    return copysignf(magnitude,r);
}

/* Inspect IEEE-754 binary32 directly; avoid repeated CRT double conversions
 * in the per-vertex validation path. */
static int dah_menu_finite(float x)
{
    uint32_t bits; memcpy(&bits,&x,sizeof(bits));
    return (bits & 0x7f800000u) != 0x7f800000u;
}
static int dah_menu_vertex_impl(const float pos[4],const float normal[4],
                           const float tex[4],const float c[192][4],const float extra[4],
                           DahMenuVertex *out)
{
    float clip[4],lit,reciprocal;
    DahMenuVertex result;
    if(!pos || !normal || !tex || !c || !out) return 0;
    for(unsigned i=0;i<4;++i)
        if(!dah_menu_finite(pos[i]) || !dah_menu_finite(normal[i]) || !dah_menu_finite(tex[i]) || (extra && !dah_menu_finite(extra[i]))) return 0;
    /* 0: DP3 R0.x,v1,c46; 2 paired ILU: LIT R1.y,R0.xxxx. */
    lit=fmaxf(dah_menu_dot3(normal,c[46]),0.0f);
    /* 1,2,3,6: DPH R11.xyzw,v0,c36..39. DPH supplies implicit W=1. */
    for(unsigned i=0;i<4;++i) clip[i]=dah_menu_dot3(pos,c[36+i])+c[36+i][3];
    /* 4,5,7,8 build R2; 10 writes RGB only; 15/16 output RGB/alpha. */
    for(unsigned i=0;i<4;++i) {
        float color=c[47][i]*lit;
        color=color+c[48][i];
        /* Captured variant: ADD R10.xyz,R10,v3 before material modulation. */
        if(extra && i<3u) color=color+extra[i];
        color=color*c[76][i];
        color=color+c[77][i];
        if(i<3u) { color=color*c[20][i]; color=color+c[19][i]; }
        result.diffuse[i]=color;
    }
    /* 9: MUL oPos.xyz,R11,c2; 10 paired RCC R1.x,R11.w;
     * 12: MAD oPos.xyz,R12,R1.x,c1. Do not drop the perspective divide. */
    reciprocal=dah_menu_rcc(clip[3]);
    for(unsigned i=0;i<3;++i) {
        float scaled=clip[i]*c[2][i];
        result.screen[i]=scaled*reciprocal+c[1][i];
    }
    result.screen[3]=clip[3];
    result.fog=dah_menu_dot4(pos,c[56]);
    result.uv[0]=dah_menu_dot4(tex,c[78]);
    result.uv[1]=dah_menu_dot4(tex,c[79]);
    /* Reject unrepresentable output; caller must also enforce its depth,
     * fog and rasterizer capabilities before issuing a host draw. */
    for(unsigned i=0;i<4;++i)
        if(!dah_menu_finite(result.screen[i]) || !dah_menu_finite(result.diffuse[i])) return 0;
    if(!dah_menu_finite(result.fog)||!dah_menu_finite(result.uv[0])||!dah_menu_finite(result.uv[1])) return 0;
    *out=result;
    return 1;
}
static int dah_menu_vertex(const float pos[4],const float normal[4],
                           const float tex[4],const float c[192][4],DahMenuVertex *out)
{
    return dah_menu_vertex_impl(pos,normal,tex,c,NULL,out);
}
#endif

