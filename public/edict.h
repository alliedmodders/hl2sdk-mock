// vim: set sts=4 ts=8 sw=4 tw=99 et:
#pragma once

#include "gametrace.h"
#include "icollideable.h"
#include "iserverentity.h"
#include "iservernetworkable.h"
#include "iserverunknown.h"

static constexpr int FL_EDICT_CHANGED = (1<<0);

class IChangeInfoAccessor
{
  public:
};

class CBaseEdict
{
  public:
    IServerEntity* GetIServerEntity() { return nullptr; }
    const IServerEntity* GetIServerEntity() const { return nullptr; }
    IChangeInfoAccessor *GetChangeAccessor();
    const IChangeInfoAccessor *GetChangeAccessor() const;
};

struct edict_t : public CBaseEdict
{
    bool IsFree() const { return false; }
    IServerNetworkable* GetNetworkable() const { return nullptr; }
    IServerUnknown* GetUnknown() const { return nullptr; }
    ICollideable* GetCollideable() const { return nullptr; }
    void StateChanged() {}
    void StateChanged(unsigned short offset) {}

    int m_fStateFlags;
};

class CGlobalVars {
  public:
    edict_t* pEdicts;
    int maxEntities;
    float curtime;
    int tickcount;
    float frametime;
    string_t mapname;
    float interval_per_tick;
    int maxClients;
};

class CSharedEdictChangeInfo
{
  public:
};
