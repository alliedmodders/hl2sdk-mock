// vim: set sts=4 ts=8 sw=4 tw=99 et:
#include "tools.h"

#include "tier0/dbg.h"
#include "tier1/interface.h"

static ServerTools sServerTools;

EXPOSE_SINGLE_INTERFACE_GLOBALVAR(ServerTools, IServerTools, VSERVERTOOLS_INTERFACE_VERSION,
				  sServerTools);

void* ServerTools::CreateEntityByName(const char *szClassName) {
    Error("%s not implemented", __func__);
    return nullptr;
}

void ServerTools::DispatchSpawn(void *pEntity) {
    Error("%s not implemented", __func__);
}

bool ServerTools::SetKeyValue(void *pEntity, const char *szField, const char *szValue) {
    Error("%s not implemented", __func__);
    return false;
}

bool ServerTools::SetKeyValue(void *pEntity, const char *szField, float flValue) {
    Error("%s not implemented", __func__);
    return false;
}

bool ServerTools::SetKeyValue(void *pEntity, const char *szField, const Vector &vecValue) {
    Error("%s not implemented", __func__);
    return false;
}

EntitySearchResult ServerTools::NextEntity(EntitySearchResult iter) {
    Error("%s not implemented", __func__);
    return nullptr;
}
