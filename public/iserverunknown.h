// vim: set sts=4 ts=8 sw=4 tw=99 et:
#pragma once

#include "ihandleentity.h"

class CBaseEntity;
class IServerNetworkable;

class IServerUnknown : public IHandleEntity
{
  public:
    virtual CBaseEntity* GetBaseEntity();
    virtual IServerNetworkable* GetNetworkable() = 0;
};
