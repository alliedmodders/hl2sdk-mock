// vim: set sts=4 ts=8 sw=4 tw=99 et:
#pragma once

#include "cmodel.h"
#include "mathlib/mathlib.h"

class CBaseEntity;

class CBaseTrace
{
  public:
    Vector startpos;
    Vector endpos;
    cplane_t plane;
    float fraction;
    bool allsolid;
    bool startsolid;
    unsigned short dispFlags;
};

class CGameTrace : public CBaseTrace
{
  public:
    bool DidHit() const;

    CBaseEntity* m_pEnt;
    float fractionleftsolid;
    csurface_t surface;
    short physicsbone;
    int hitbox;
    int hitgroup;
};

typedef CGameTrace trace_t;
