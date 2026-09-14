#ifndef DAH_VIEW_BASIS_H
#define DAH_VIEW_BASIS_H
#include <math.h>

/* Repair the specific malformed affine-view signature observed during DAH's
 * title render: two orthogonal basis columns retain their directions but have
 * million-scale lengths. Work on the render copy only. Healthy, non-finite,
 * translated and non-affine matrices are not changed. */
static int dah_repair_view_basis(float m[16])
{
    float a[3]={m[0],m[4],m[8]}, b[3]={m[1],m[5],m[9]}, c[3]={m[2],m[6],m[10]};
    float na=sqrtf(a[0]*a[0]+a[1]*a[1]+a[2]*a[2]);
    float nb=sqrtf(b[0]*b[0]+b[1]*b[1]+b[2]*b[2]);
    float nc=sqrtf(c[0]*c[0]+c[1]*c[1]+c[2]*c[2]);
    float x[3],nx,alignment;
    for(unsigned i=0;i<16;++i) if(!isfinite(m[i])) return 0;
    if (fabsf(m[3])>1e-6f || fabsf(m[7])>1e-6f || fabsf(m[11])>1e-6f ||
        fabsf(m[15]-1.0f)>1e-6f || na<0.25f || na>4.0f ||
        nb<100000.0f || nc<100000.0f) return 0;
    for(unsigned i=0;i<3;++i){b[i]/=nb;c[i]/=nc;}
    /* The surviving directions must really be perpendicular. */
    if(fabsf(b[0]*c[0]+b[1]*c[1]+b[2]*c[2])>0.01f) return 0;
    x[0]=b[1]*c[2]-b[2]*c[1];
    x[1]=b[2]*c[0]-b[0]*c[2];
    x[2]=b[0]*c[1]-b[1]*c[0];
    nx=sqrtf(x[0]*x[0]+x[1]*x[1]+x[2]*x[2]);
    if(nx<0.99f) return 0;
    for(unsigned i=0;i<3;++i)x[i]/=nx;
    alignment=x[0]*a[0]+x[1]*a[1]+x[2]*a[2];
    if(alignment<0.0f)for(unsigned i=0;i<3;++i)x[i]=-x[i];
    m[0]=x[0];m[4]=x[1];m[8]=x[2];
    m[1]=b[0];m[5]=b[1];m[9]=b[2];
    m[2]=c[0];m[6]=c[1];m[10]=c[2];
    return 1;
}
#endif
