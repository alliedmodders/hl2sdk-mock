// vim: set sts=4 ts=8 sw=4 tw=99 et:
#pragma once

#include "IEngineTrace.h"

class EngineTrace : public IEngineTrace
{
  public:
    void TraceRay(const Ray_t &ray, unsigned int fMask, ITraceFilter *pTraceFilter, trace_t *pTrace) override;
    void ClipRayToEntity(const Ray_t &ray, unsigned int fMask, IHandleEntity *pEnt, trace_t *pTrace) override;
    int GetPointContents(const Vector &vecAbsPosition, int contentsMask = MASK_ALL,
                                 IHandleEntity** ppEntity = nullptr) override;
    int GetPointContents_Collideable(ICollideable *pCollide, const Vector &vecAbsPosition) override;
    bool PointOutsideWorld(const Vector &ptTest) override;
};
