// vim: set sts=4 ts=8 sw=4 tw=99 et:
#pragma once

#include <stdlib.h>

#include <algorithm>

static inline void RandomSeed(int seed) {
    srand(seed);
}

static inline float RandomFloat(float flMinVal = 0.0f, float flMaxVal = 1.0f) {
    float x = (float)rand() / float(RAND_MAX);
    x *= (flMaxVal - flMinVal);
    x += flMinVal;
    return x;
}

static inline int RandomInt(int iMinVal, int iMaxVal) {
    int r = rand();
    return (r % (iMaxVal - iMinVal)) + iMinVal;
}
