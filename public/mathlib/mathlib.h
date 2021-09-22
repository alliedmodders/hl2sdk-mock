// vim: set sts=4 ts=8 sw=4 tw=99 et:
#pragma once

#include <math.h>

#include "vector.h"

typedef Vector AngularImpulse;

struct cplane_t
{
    Vector normal;
    float dist;
    uint8_t type;
    uint8_t signbits;
    uint8_t pad[2];
};

static inline void MathLib_Init(float gamma = 2.2f, float texGamma = 2.2f, float brightness = 0.0f,
                                int overbright = 2.0f, bool bAllow3DNow = true, bool bAllowSSE = true,
                                bool bAllowSSE2 = true, bool bAllowMMX = true)
{
}

static inline int RoundFloatToInt(float f) {
    return round(f);
}
