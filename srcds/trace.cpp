// vim: set sts=4 ts=8 sw=4 tw=99 et:
#include "trace.h"

#include "tier0/dbg.h"
#include "tier1/interface.h"

static EngineTrace sEngineTrace;

EXPOSE_SINGLE_INTERFACE_GLOBALVAR(EngineTrace, IEngineTrace, INTERFACEVERSION_ENGINETRACE_SERVER,
		                  sEngineTrace);

void EngineTrace::TraceRay(const Ray_t &ray, unsigned int fMask, ITraceFilter *pTraceFilter, trace_t *pTrace)
{
    Error("%s not implemented", __func__);
}

void EngineTrace::ClipRayToEntity(const Ray_t &ray, unsigned int fMask, IHandleEntity *pEnt, trace_t *pTrace)
{
    Error("%s not implemented", __func__);
}

int EngineTrace::GetPointContents(const Vector &vecAbsPosition, int contentsMask,
                                  IHandleEntity** ppEntity)
{
    Error("%s not implemented", __func__);
    return CONTENTS_EMPTY;
}

int EngineTrace::GetPointContents_Collideable(ICollideable *pCollide, const Vector &vecAbsPosition)
{
    Error("%s not implemented", __func__);
    return CONTENTS_EMPTY;
}

bool EngineTrace::PointOutsideWorld(const Vector &ptTest)
{
    Error("%s not implemented", __func__);
    return false;
}
