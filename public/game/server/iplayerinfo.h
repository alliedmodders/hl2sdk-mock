// vim: set sts=4 ts=8 sw=4 tw=99 et:
#pragma once

#include <edict.h>

static constexpr char INTERFACEVERSION_PLAYERINFOMANAGER[] = "PlayerInfoManager002";

class IPlayerInfo
{
  public:
    virtual int GetTeamIndex() const = 0;
    virtual bool IsObserver() = 0;
    virtual int GetFragCount() = 0;
    virtual int GetDeathCount() = 0;
    virtual int GetArmorValue() = 0;
    virtual const Vector GetAbsOrigin() = 0;
    virtual const QAngle GetAbsAngles() = 0;
    virtual const Vector GetPlayerMins() = 0;
    virtual const Vector GetPlayerMaxs() = 0;
    virtual const char *GetWeaponName() = 0;
    virtual const char *GetModelName() = 0;
    virtual const int GetHealth() = 0;
    virtual void ChangeTeam(int iTeamNum) = 0;
    virtual const char* GetName() = 0;
    virtual bool IsDead() = 0;
};

class IPlayerInfoManager
{
  public:
    virtual IPlayerInfo *GetPlayerInfo(edict_t *pEdict) = 0;
    virtual CGlobalVars* GetGlobalVars() = 0;
};
