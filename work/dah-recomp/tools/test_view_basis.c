#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "../src/recomp/dah_view_basis.h"
static float dot(const float*m,unsigned a,unsigned b){return m[a]*m[b]+m[a+4]*m[b+4]+m[a+8]*m[b+8];}
int main(void){
 float m[16]={1,0,0,0,0,1,0,0,0,0,1,0,3,4,5,1},copy[16];unsigned cases=0;
 memcpy(copy,m,sizeof m);assert(!dah_repair_view_basis(m)&&!memcmp(m,copy,sizeof m));++cases;
 for(unsigned k=0;k<1000;++k){float t=(float)k*.0062831853f,s=sinf(t),c=cosf(t);
   float q[16]={c,-s*1e6f,0,0,s,c*1e6f,0,0,0,0,2e6f,0,3,4,5,1};
   assert(dah_repair_view_basis(q));assert(fabsf(dot(q,0,0)-1)<1e-5f);assert(fabsf(dot(q,1,1)-1)<1e-5f);assert(fabsf(dot(q,2,2)-1)<1e-5f);
   assert(fabsf(dot(q,0,1))<1e-5f&&fabsf(dot(q,0,2))<1e-5f&&fabsf(dot(q,1,2))<1e-5f);assert(q[12]==3&&q[13]==4&&q[14]==5);++cases;}
 {float q[16]={1,1e6f,1e6f,0,0,1e6f,1e6f,0,0,0,1,0,0,0,0,1};memcpy(copy,q,sizeof q);assert(!dah_repair_view_basis(q)&&!memcmp(q,copy,sizeof q));++cases;}
 {float q[16]={1,1e6f,0,0,0,0,1e6f,0,0,0,0,0,0,0,0,1};q[5]=NAN;memcpy(copy,q,sizeof q);assert(!dah_repair_view_basis(q)&&!memcmp(q,copy,sizeof q));++cases;}
 printf("PASS %u view-basis cases; gated signature, handed orthonormal reconstruction, translation preservation, healthy/nonfinite rejection\n",cases);return 0;
}
