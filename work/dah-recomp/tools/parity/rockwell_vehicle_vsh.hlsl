/* Auto-generated NV2A vertex shader */

cbuffer VSH_Constants : register(b1) {
    float4 c[192];
};

struct VS_IN {
    float4 v0 : ATTR0;
};

struct VS_OUT {
    float4 oPos : SV_POSITION;
    float4 oD0  : COLOR0;
    float4 oD1  : COLOR1;
    float4 oT0  : TEXCOORD0;
    float4 oT1  : TEXCOORD1;
    float4 oT2  : TEXCOORD2;
    float4 oT3  : TEXCOORD3;
    float  oFog : FOG;
    float  oPts : PSIZE;
    float4 oB0  : TEXCOORD4;
    float4 oB1  : TEXCOORD5;
};

VS_OUT main(VS_IN input) {
    /* Temporary registers */
    float4 R0 = float4(0,0,0,0);
    float4 R1 = float4(0,0,0,0);
    float4 R2 = float4(0,0,0,0);
    float4 R3 = float4(0,0,0,0);
    float4 R4 = float4(0,0,0,0);
    float4 R5 = float4(0,0,0,0);
    float4 R6 = float4(0,0,0,0);
    float4 R7 = float4(0,0,0,0);
    float4 R8 = float4(0,0,0,0);
    float4 R9 = float4(0,0,0,0);
    float4 R10 = float4(0,0,0,0);
    float4 R11 = float4(0,0,0,0);
    float4 R12 = float4(0,0,0,0);
    int a0 = 0;

    /* Input register aliases */
    float4 v0 = input.v0;

    /* Output registers (initialized to zero) */
    float4 oPos = float4(0,0,0,1);
    float4 oD0  = float4(0,0,0,1);
    float4 oD1  = float4(0,0,0,1);
    float4 oFog = float4(0,0,0,0);
    float4 oPts = float4(0,0,0,0);
    float4 oB0  = float4(0,0,0,0);
    float4 oB1  = float4(0,0,0,0);
    float4 oT0  = float4(0,0,0,0);
    float4 oT1  = float4(0,0,0,0);
    float4 oT2  = float4(0,0,0,0);
    float4 oT3  = float4(0,0,0,0);

    /* R12 is aliased to oPos */
    #define R12 oPos

    /* --- Program body (26 instructions) --- */

    /* Instruction 0 */

    /* Instruction 1 */

    /* Instruction 2 */

    /* Instruction 3 */

    /* Instruction 4 */

    /* Instruction 5 */

    /* Instruction 6 */

    /* Instruction 7 */

    /* Instruction 8 */

    /* Instruction 9 */

    /* Instruction 10 */

    /* Instruction 11 */

    /* Instruction 12 */

    /* Instruction 13 */

    /* Instruction 14 */

    /* Instruction 15 */

    /* Instruction 16 */

    /* Instruction 17 */

    /* Instruction 18 */

    /* Instruction 19 */

    /* Instruction 20 */

    /* Instruction 21 */

    /* Instruction 22 */

    /* Instruction 23 */

    /* Instruction 24 */

    /* Instruction 25 */

    #undef R12

    /* Write outputs */
    VS_OUT o;
    o.oPos = oPos;
    o.oD0  = saturate(oD0);
    o.oD1  = saturate(oD1);
    o.oT0  = oT0;
    o.oT1  = oT1;
    o.oT2  = oT2;
    o.oT3  = oT3;
    o.oFog = oFog.x;
    o.oPts = oPts.x;
    o.oB0  = saturate(oB0);
    o.oB1  = saturate(oB1);
    return o;
}
