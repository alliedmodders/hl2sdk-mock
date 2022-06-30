// vim: set sts=4 ts=8 sw=4 tw=99 et:
#pragma once

#include "const.h"
#include "mathlib/vector.h"

static constexpr char INTERFACEVERSION_ENGINETRACE_SERVER[] = "EngineTraceServer003";

static constexpr int CONTENTS_EMPTY = 0;
static constexpr int CONTENTS_SOLID = 0x1;
static constexpr int CONTENTS_WINDOW = 0x2;
static constexpr int CONTENTS_AUX = 0x4;
static constexpr int CONTENTS_GRATE = 0x8;
static constexpr int CONTENTS_SLIME = 0x10;
static constexpr int CONTENTS_WATER = 0x20;
static constexpr int CONTENTS_BLOCKLOS = 0x40;
static constexpr int CONTENTS_OPAQUE = 0x80;
static constexpr int CONTENTS_TESTFOGVOLUME = 0x100;
static constexpr int CONTENTS_UNUSED = 0x200;
static constexpr int CONTENTS_BLOCKLIGHT = 0x400;
static constexpr int CONTENTS_TEAM1 = 0x800;
static constexpr int CONTENTS_TEAM2 = 0x1000;
static constexpr int CONTENTS_IGNORE_NODRAW_OPAQUE = 0x2000;
static constexpr int CONTENTS_MOVEABLE = 0x4000;
static constexpr int CONTENTS_AREAPORTAL = 0x8000;
static constexpr int CONTENTS_PLAYERCLIP = 0x10000;
static constexpr int CONTENTS_MONSTERCLIP = 0x20000;
static constexpr int CONTENTS_CURRENT_0 = 0x40000;
static constexpr int CONTENTS_CURRENT_90 = 0x80000;
static constexpr int CONTENTS_CURRENT_180 = 0x100000;
static constexpr int CONTENTS_CURRENT_270 = 0x200000;
static constexpr int CONTENTS_CURRENT_UP = 0x400000;
static constexpr int CONTENTS_CURRENT_DOWN = 0x800000;
static constexpr int CONTENTS_ORIGIN = 0x1000000;
static constexpr int CONTENTS_MONSTER = 0x2000000;
static constexpr int CONTENTS_DEBRIS = 0x4000000;
static constexpr int CONTENTS_DETAIL = 0x8000000;
static constexpr int CONTENTS_TRANSLUCENT = 0x10000000;
static constexpr int CONTENTS_LADDER = 0x20000000;
static constexpr int CONTENTS_HITBOX = 0x40000000;
static constexpr int MASK_SOLID = (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_MONSTER|CONTENTS_GRATE);

struct Ray_t
{
    void Init(Vector const& start, Vector const& end) {
        (void)start;
        (void)end;
    }
    void Init(Vector const& start, Vector const& end, Vector const& mins, Vector const& maxs) {
        (void)start;
        (void)end;
        (void)mins;
        (void)maxs;
    }
};

class ITraceFilter
{
  public:
};

class CTraceFilter : public ITraceFilter
{
  public:
};

class CTraceFilterEntitiesOnly : public ITraceFilter
{
  public:
};

class CTraceFilterHitAll : public ITraceFilter
{
  public:
};

class ICollideable;
class IHandleEntity;
class CGameTrace;
typedef CGameTrace trace_t;

class IEngineTrace
{
  public:
    virtual void TraceRay(const Ray_t &ray, unsigned int fMask, ITraceFilter *pTraceFilter, trace_t *pTrace) = 0;
    virtual void ClipRayToEntity(const Ray_t &ray, unsigned int fMask, IHandleEntity *pEnt, trace_t *pTrace) = 0;
    virtual int GetPointContents(const Vector &vecAbsPosition, int contentsMask = MASK_ALL,
                                 IHandleEntity** ppEntity = nullptr) = 0;
    virtual int GetPointContents_Collideable(ICollideable *pCollide, const Vector &vecAbsPosition) = 0;
    virtual bool PointOutsideWorld(const Vector &ptTest) = 0;
};
