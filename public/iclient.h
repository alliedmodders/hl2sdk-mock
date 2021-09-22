// vim: set sts=4 ts=8 sw=4 tw=99 et:
#pragma once

#include "imovehelper.h"
#include "inetmsghandler.h"

class IClient : public INetChannelHandler
{
  public:
    virtual void Disconnect(const char *reason, ...) = 0;
    virtual void Inactivate() = 0;
    virtual void Reconnect() = 0;
    virtual int GetUserID() const = 0;
    virtual int GetPlayerSlot() const = 0;
};

