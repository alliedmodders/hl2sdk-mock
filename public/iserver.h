// vim: set sts=4 ts=8 sw=4 tw=99 et:
#pragma once

class IClient;

class IServer
{
  public:
    virtual IClient* GetClient(int client) = 0;
    virtual void GetNetStats(float &avgIn, float &avgOut) = 0;
};
