/* Reference interpreter decodes the captured words using xemu's field DATA.
 * It does not reuse the header's decoded equations or arithmetic helpers. */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <float.h>
#include "dah_menu_vertex_fixture.h"
#include "menu_vertex_original.inc"
static unsigned cases,checks;
#define CHECK(c) do{++checks;if(!(c)){fprintf(stderr,"FAIL case%u line%u %s\n",cases,__LINE__,#c);exit(1);}}while(0)
static unsigned field(const uint32_t *p,enum Field f){return(p[field_map[f][0]]>>field_map[f][1])&((1u<<field_map[f][2])-1u);}
static float rcc_reference(float input){float value=1.0f/input;uint32_t bits;memcpy(&bits,&value,4);if(!(bits&0x80000000u)){if(value<0x1p-64f)value=0x1p-64f;if(value>0x1p64f)value=0x1p64f;}else{if(value< -0x1p64f)value= -0x1p64f;if(value> -0x1p-64f)value= -0x1p-64f;}return value;}
typedef struct{float r[13][4],o[16][4];}Machine;
static void operand(const uint32_t*p,unsigned input,const float v[3][4],const float c[192][4],const Machine*m,float out[4]){unsigned mux,reg,neg;enum Field sw;const float *src;
    if(input==0){mux=field(p,FLD_A_MUX);reg=field(p,FLD_A_R);neg=field(p,FLD_A_NEG);sw=FLD_A_SWZ_X;}
    else if(input==1){mux=field(p,FLD_B_MUX);reg=field(p,FLD_B_R);neg=field(p,FLD_B_NEG);sw=FLD_B_SWZ_X;}
    else{mux=field(p,FLD_C_MUX);reg=(field(p,FLD_C_R_HIGH)<<2)|field(p,FLD_C_R_LOW);neg=field(p,FLD_C_NEG);sw=FLD_C_SWZ_X;}
    if(mux==1){CHECK(reg<13);src=reg==12?m->o[0]:m->r[reg];}
    else if(mux==2){CHECK(field(p,FLD_V)<3);src=v[field(p,FLD_V)];}
    else{CHECK(mux==3&&field(p,FLD_CONST)<192);src=c[field(p,FLD_CONST)];}
    for(unsigned j=0;j<4;++j){unsigned selector=field(p,(enum Field)(sw+j));if(input==2&&field(p,FLD_ILU)>=2&&field(p,FLD_ILU)<=6)selector=field(p,sw);out[j]=src[selector]*(neg?-1.0f:1.0f);}
}
static void masked(float *dst,const float *value,unsigned mask){for(unsigned j=0;j<4;++j)if(mask&(8u>>j))dst[j]=value[j];}
static void execute(Machine*m,const uint32_t*p,const float v[3][4],const float c[192][4]){
    unsigned mac=field(p,FLD_MAC),ilu=field(p,FLD_ILU),reg=field(p,FLD_OUT_R),mm=field(p,FLD_OUT_MAC_MASK),im=field(p,FLD_OUT_ILU_MASK),om=field(p,FLD_OUT_O_MASK);
    float a[4]={0},b[4]={0},d[4]={0},mr[4]={0},ir[4]={0};
    // Snapshot every input before either pipe writes a temp or aliased output.
    if(mac)operand(p,0,v,c,m,a);if(mac==2||mac==4||mac>=5)operand(p,1,v,c,m,b);if(ilu||mac==3||mac==4)operand(p,2,v,c,m,d);
    for(unsigned j=0;j<4;++j){switch(mac){case 0:break;case 1:mr[j]=a[j];break;case 2:mr[j]=a[j]*b[j];break;case 3:mr[j]=a[j]+d[j];break;case 4:mr[j]=a[j]*b[j]+d[j];break;case 5:mr[j]=(a[0]*b[0]+a[1]*b[1])+a[2]*b[2];break;case 6:mr[j]=((a[0]*b[0]+a[1]*b[1])+a[2]*b[2])+b[3];break;case 7:mr[j]=((a[0]*b[0]+a[1]*b[1])+a[2]*b[2])+a[3]*b[3];break;default:CHECK(0);}}
    switch(ilu){case 0:break;case 1:memcpy(ir,d,sizeof ir);break;case 3:{float t=rcc_reference(d[0]);for(unsigned j=0;j<4;++j)ir[j]=t;break;}case 7:{float power=fminf(fmaxf(d[3],-127.99609375f),127.99609375f);ir[0]=ir[3]=1;ir[1]=fmaxf(d[0],0);ir[2]=d[0]>0?powf(fmaxf(d[1],0),power):0;break;}default:CHECK(0);}
    if(om){unsigned out=field(p,FLD_OUT_ADDRESS)&15u;CHECK(field(p,FLD_OUT_ORB)==1);masked(m->o[out],field(p,FLD_OUT_MUX)?ir:mr,om);}
    if(mac&&ilu&&reg==1)mm=0; /* paired MAC cannot overwrite R1 */
    if(ilu)masked(m->r[mac?1:reg],ir,im);
    if(mac)masked(reg==12?m->o[0]:m->r[reg],mr,mm);
}
static DahMenuVertex interpret(const float v[3][4],const float c[192][4]){Machine m={0};DahMenuVertex out;float lit=0;for(unsigned slot=0;slot<17;++slot){execute(&m,original_program[slot],v,c);if(slot==2){lit=m.r[1][1];CHECK(m.r[11][1]==m.r[11][1]);}if(slot==10)CHECK(m.r[1][1]==lit);CHECK(field(original_program[slot],FLD_FINAL)==(unsigned)(slot==16));}memcpy(out.screen,m.o[0],sizeof out.screen);memcpy(out.diffuse,m.o[3],sizeof out.diffuse);out.fog=m.o[5][0];out.uv[0]=m.o[9][0];out.uv[1]=m.o[9][1];return out;}
static uint32_t state=0x883194EF;
static float random_finite(void){state^=state<<13;state^=state>>17;state^=state<<5;return(float)((int32_t)(state&0xffffu)-32768)/1024.0f;}
static int near(float a,float b){return fabsf(a-b)<=2e-6f*fmaxf(1.0f,fmaxf(fabsf(a),fabsf(b)));}
static void compare_case(float v[3][4],float c[192][4]){DahMenuVertex expected,actual;++cases;expected=interpret(v,c);CHECK(dah_menu_vertex(v[0],v[1],v[2],c,&actual));for(unsigned i=0;i<4;++i){if(!near(actual.screen[i],expected.screen[i]))fprintf(stderr,"screen%u actual%.9g expected%.9g\n",i,actual.screen[i],expected.screen[i]);CHECK(near(actual.screen[i],expected.screen[i]));CHECK(near(actual.diffuse[i],expected.diffuse[i]));}CHECK(near(actual.uv[0],expected.uv[0]));CHECK(near(actual.uv[1],expected.uv[1]));CHECK(near(actual.fog,expected.fog));}
static void field_set(uint32_t *p,enum Field f,unsigned value){unsigned mask=((1u<<field_map[f][2])-1u)<<field_map[f][1];p[field_map[f][0]]=(p[field_map[f][0]]&~mask)|(value<<field_map[f][1]);}
static void paired_reference_probe(void){Machine m={0};float v[3][4]={{2,3,4,5}},c[192][4]={{0}};uint32_t instruction[4]={0};m.r[0][0]=7;field_set(instruction,FLD_MAC,1);field_set(instruction,FLD_ILU,1);field_set(instruction,FLD_A_MUX,2);field_set(instruction,FLD_C_MUX,1);field_set(instruction,FLD_OUT_R,0);field_set(instruction,FLD_OUT_MAC_MASK,8);field_set(instruction,FLD_OUT_ILU_MASK,8);execute(&m,instruction,v,c);CHECK(m.r[0][0]==2&&m.r[1][0]==7);field_set(instruction,FLD_OUT_R,1);m.r[1][0]=99;execute(&m,instruction,v,c);CHECK(m.r[1][0]==2);}
int main(void){float c[192][4]={{0}},v[3][4]={{0}};uint32_t words[68];uint8_t valid[768];DahMenuVertex result,unchanged;unsigned i,j;
    memcpy(words,original_program,sizeof words);memset(valid,1,sizeof valid);CHECK(dah_menu_program_matches(words,valid));CHECK(!dah_menu_program_matches(NULL,valid));CHECK(!dah_menu_program_matches(words,NULL));
    for(i=0;i<68;++i){for(j=0;j<32;++j){++cases;words[i]^=1u<<j;CHECK(!dah_menu_program_matches(words,valid));words[i]^=1u<<j;}valid[i]=0;CHECK(!dah_menu_program_matches(words,valid));valid[i]=1;}
    CHECK(dah_menu_constants_ready(c,valid));CHECK(!dah_menu_constants_ready(NULL,valid));CHECK(!dah_menu_constants_ready(c,NULL));
    for(i=0;i<768;++i){int used=0;for(j=0;j<sizeof used_constants/sizeof used_constants[0];++j)if(i/4==used_constants[j])used=1;valid[i]=0;CHECK(dah_menu_constants_ready(c,valid)==!used);valid[i]=1;c[i/4][i%4]=NAN;CHECK(dah_menu_constants_ready(c,valid)==!used);c[i/4][i%4]=INFINITY;CHECK(dah_menu_constants_ready(c,valid)==!used);c[i/4][i%4]=0;}
    paired_reference_probe();
    for(i=0;i<12000;++i){for(j=0;j<12;++j)v[j/4][j%4]=random_finite();for(j=0;j<768;++j)c[j/4][j%4]=random_finite();compare_case(v,c);}
    {const float ws[]={0.0f,-0.0f,0x1p-149f,-0x1p-149f,0x1p-65f,-0x1p-65f,0x1p-64f,-0x1p-64f,0x1p64f,-0x1p64f,0x1p65f,-0x1p65f,FLT_MAX,-FLT_MAX,INFINITY,-INFINITY};for(i=0;i<sizeof ws/sizeof ws[0];++i){float a=dah_menu_rcc(ws[i]),b=rcc_reference(ws[i]);++cases;CHECK(a==b&&signbit(a)==signbit(b));}for(i=0;i<14;++i){memset(c,0,sizeof c);memset(v,0,sizeof v);c[36][3]=1;c[37][3]=2;c[38][3]=3;c[39][3]=ws[i];c[2][0]=c[2][1]=c[2][2]=1;c[47][0]=2;c[48][3]=3;c[76][3]=4;c[77][3]=5;c[19][3]=9;c[20][3]=10;compare_case(v,c);}}
    memset(c,0,sizeof c);memset(v,0,sizeof v);memset(&result,0xCD,sizeof result);unchanged=result;for(i=0;i<12;++i){v[i/4][i%4]=NAN;CHECK(!dah_menu_vertex(v[0],v[1],v[2],c,&result));CHECK(memcmp(&result,&unchanged,sizeof result)==0);v[i/4][i%4]=0;}c[36][3]=INFINITY;CHECK(!dah_menu_vertex(v[0],v[1],v[2],c,&result));CHECK(memcmp(&result,&unchanged,sizeof result)==0);
    CHECK(!dah_menu_vertex(NULL,v[1],v[2],c,&result));CHECK(!dah_menu_vertex(v[0],NULL,v[2],c,&result));CHECK(!dah_menu_vertex(v[0],v[1],NULL,c,&result));CHECK(!dah_menu_vertex(v[0],v[1],v[2],NULL,&result));CHECK(!dah_menu_vertex(v[0],v[1],v[2],c,NULL));
    printf("PASS %u vertex/guard cases,%u assertions; independent17-word decoder, paired pipes/R1 masks, R12 alias, DPH/LIT/RCC, screen/UV/RGBA/fog\n",cases,checks);return 0;
}
