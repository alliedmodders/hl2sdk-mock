// vim: set sts=4 ts=8 sw=4 tw=99 et:
#include "networkstringtable.h"

#include "tier0/dbg.h"
#include "tier1/interface.h"

static NetworkStringTableContainer sNetworkStringTableContainer;

EXPOSE_SINGLE_INTERFACE_GLOBALVAR(NetworkStringTableContainer, INetworkStringTableContainer, INTERFACENAME_NETWORKSTRINGTABLESERVER,
		                  sNetworkStringTableContainer);

INetworkStringTable* NetworkStringTableContainer::FindTable(const char* name) const
{
    Error("%s not implemented", __func__);
    return nullptr;
}

INetworkStringTable* NetworkStringTableContainer::GetTable(int i) const
{
    Error("%s not implemented", __func__);
    return nullptr;
}

int NetworkStringTableContainer::GetNumTables() const
{
    Error("%s not implemented", __func__);
    return 0;
}
