// vim: set sts=4 ts=8 sw=4 tw=99 et:
#pragma once

#include "tier0/platform.h"

struct color32 {
    byte r, g, b, a;
};

class Color
{
  public:
    Color() : rgba() {}
    Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
    {
        rgba[0] = r;
        rgba[1] = g;
        rgba[2] = b;
        rgba[3] = a;
    }
    int r() const { return rgba[0]; }
    int g() const { return rgba[1]; }
    int b() const { return rgba[2]; }
    int a() const { return rgba[3]; }
    unsigned char rgba[4];
};
