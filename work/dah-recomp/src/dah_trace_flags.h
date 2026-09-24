#ifndef DAH_TRACE_FLAGS_H
#define DAH_TRACE_FLAGS_H

#include <stdlib.h>

/* These diagnostics are configured in the launch environment. Cache their
 * presence once per translation unit and guest thread so matrix operations do
 * not repeatedly scan the host's entire environment. Preserve getenv's original
 * presence semantics, including a value of "0" still meaning enabled. */
static inline int dah_matrix_trace_enabled(void)
{
    static RECOMP_TLS int cached = -1;
    if (cached < 0) cached = getenv("DAH_MATRIX_TRACE") != NULL;
    return cached;
}

static inline int dah_model_trace_enabled(void)
{
    static RECOMP_TLS int cached = -1;
    if (cached < 0) cached = getenv("DAH_MODEL_TRACE") != NULL;
    return cached;
}

#endif
