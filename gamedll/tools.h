// vim: set sts=4 ts=8 sw=4 tw=99 et:
#pragma once

#include "toolframework/itoolentity.h"

class ServerTools : public IServerTools
{
  public:
    void *CreateEntityByName(const char *szClassName) override;
    void DispatchSpawn(void *pEntity) override;
    EntitySearchResult NextEntity(EntitySearchResult iter) override;
    bool SetKeyValue(void *pEntity, const char *szField, const char *szValue) override;
    bool SetKeyValue(void *pEntity, const char *szField, float flValue) override;
    bool SetKeyValue(void *pEntity, const char *szField, const Vector &vecValue) override;
};
