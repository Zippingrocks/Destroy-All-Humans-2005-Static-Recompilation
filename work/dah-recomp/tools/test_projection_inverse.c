#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include "../src/recomp/dah_projection_inverse.h"

int main(void)
{
    const float p[16] = {
        -2.41421342f,0,0,0, 0,3.21895123f,0,0,
        0,0,1.00003994f,1, 0,0,-0.0100003993f,0
    };
    float broken[16] = {
        .941626847f,3203280.0f,9200206.0f,0,
        .410110831f,-4295001.0f,-12335760.0f,0,
        .672665238f,15388787.0f,-5357988.0f,0,
        -68.8674f,-523703000.0f,844646000.0f,1
    };
    float healthy[16];
    assert(dah_repair_projection_inverse(broken,p));
    assert(dah_matrix_identity_error(broken,p) < 1e-3f);
    assert(dah_matrix_identity_error(p,broken) < 1e-3f);
    memcpy(healthy,broken,sizeof healthy);
    assert(!dah_repair_projection_inverse(healthy,p));
    assert(!memcmp(healthy,broken,sizeof healthy));
    {
        float non_projection[16] = {1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1};
        assert(!dah_repair_projection_inverse(broken,non_projection));
    }
    puts("PASS projection inverse: corrupt cache repaired from retail forward matrix; healthy/non-projection inputs preserved");
    return 0;
}
