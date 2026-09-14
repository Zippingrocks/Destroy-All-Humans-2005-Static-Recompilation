#ifndef DAH_PROJECTION_INVERSE_H
#define DAH_PROJECTION_INVERSE_H
#include <math.h>
#include <string.h>

/* Repair only the Xbox perspective matrix shape used by DAH:
 *
 *   a 0 0 0
 *   0 b 0 0
 *   0 0 c e
 *   0 0 d 0
 *
 * The retail forward matrix remains authoritative.  A healthy cached inverse
 * is left untouched; a corrupt cache is reconstructed analytically. */
static float dah_matrix_identity_error(const float a[16], const float b[16])
{
    float worst = 0.0f;
    for (unsigned row = 0; row < 4u; ++row) {
        for (unsigned col = 0; col < 4u; ++col) {
            float sum = 0.0f;
            for (unsigned k = 0; k < 4u; ++k)
                sum += a[row * 4u + k] * b[k * 4u + col];
            float error = fabsf(sum - (row == col ? 1.0f : 0.0f));
            if (error > worst) worst = error;
        }
    }
    return worst;
}

static int dah_repair_projection_inverse(float inverse[16], const float p[16])
{
    static const unsigned zeros[] = {1,2,3,4,6,7,8,9,12,13,15};
    float candidate[16] = {0};
    if (!inverse || !p) return 0;
    for (unsigned i = 0; i < 16u; ++i)
        if (!isfinite(inverse[i]) || !isfinite(p[i])) return 0;
    for (unsigned i = 0; i < sizeof(zeros) / sizeof(zeros[0]); ++i)
        if (fabsf(p[zeros[i]]) > 1e-6f) return 0;
    if (fabsf(p[0]) < 1e-6f || fabsf(p[5]) < 1e-6f ||
        fabsf(p[11]) < 1e-6f || fabsf(p[14]) < 1e-6f)
        return 0;
    if (dah_matrix_identity_error(inverse, p) < 1e-3f) return 0;
    candidate[0] = 1.0f / p[0];
    candidate[5] = 1.0f / p[5];
    candidate[11] = 1.0f / p[14];
    candidate[14] = 1.0f / p[11];
    candidate[15] = -p[10] / (p[11] * p[14]);
    if (dah_matrix_identity_error(candidate, p) > 1e-3f ||
        dah_matrix_identity_error(p, candidate) > 1e-3f)
        return 0;
    memcpy(inverse, candidate, sizeof(candidate));
    return 1;
}
#endif
