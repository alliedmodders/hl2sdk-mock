// vim: set sts=4 ts=8 sw=4 tw=99 et:
#pragma once

#include "networkstringtabledefs.h"

class NetworkStringTableContainer : public INetworkStringTableContainer
{
  public:
    INetworkStringTable* FindTable(const char* name) const override;
    INetworkStringTable* GetTable(int i) const override;
    int GetNumTables() const override;
};
