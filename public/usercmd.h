// vim: set sts=4 ts=8 sw=4 tw=99 et:
#pragma once

#include <stdint.h>

#include "mathlib/mathlib.h"

class CUserCmd
{
  public:
    uint8_t impulse = 0;
    float forwardmove = 0;
    float sidemove = 0;
    float upmove = 0;
    QAngle viewangles;
    short mousedx = 0;
    short mousedy = 0;
    int buttons = 0;
    int weaponselect = 0;
    int weaponsubtype = 0;
    int command_number = 0;
    int tick_count = 0;
    int random_seed = 0;
};
