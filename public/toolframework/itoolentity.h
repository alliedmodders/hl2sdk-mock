// vim: set sts=4 ts=8 sw=4 tw=99 et:
#pragma once

class Vector;

typedef void* EntitySearchResult;

static constexpr char VSERVERTOOLS_INTERFACE_VERSION[] = "VSERVERTOOLS001";

class IServerTools
{
  public:
    virtual void *CreateEntityByName(const char *szClassName) = 0;
    virtual void DispatchSpawn(void *pEntity) = 0;
    virtual EntitySearchResult NextEntity(EntitySearchResult iter) = 0;
    virtual bool SetKeyValue(void *pEntity, const char *szField, const char *szValue) = 0;
    virtual bool SetKeyValue(void *pEntity, const char *szField, float flValue) = 0;
    virtual bool SetKeyValue(void *pEntity, const char *szField, const Vector &vecValue) = 0;

    EntitySearchResult FirstEntity() { return NextEntity(nullptr); }
};
