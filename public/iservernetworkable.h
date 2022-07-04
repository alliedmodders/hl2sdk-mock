// vim: set sts=4 ts=8 sw=4 tw=99 et:
#pragma once

#include "ihandleentity.h"

class ServerClass;
struct edict_t;

class CCheckTransmitInfo
{
  public:
    edict_t* m_pClientEnt;
};

class IServerNetworkable
{
  public:
    virtual IHandleEntity* GetEntityHandle() = 0;
    virtual ServerClass* GetServerClass() = 0;
    virtual CBaseEntity* GetBaseEntity() = 0;
    virtual edict_t *GetEdict() const = 0;
};
