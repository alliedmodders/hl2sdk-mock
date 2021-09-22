// vim: set sts=4 ts=8 sw=4 tw=99 et:
#pragma once

#include "inetchannelinfo.h"

typedef  struct netpacket_s {
} netpacket_t;

class bf_write;
class INetChannelHandler;

class INetChannel : public INetChannelInfo
{
  public:
    virtual void ProcessPacket(struct netpacket_s* packet, bool reader) = 0;
    virtual bool SendFile(const char* file, unsigned int transfer_id, bool replay_demo) = 0;
    virtual void DenyFile(const char *file, unsigned int transfer_id, bool replay_demo) = 0;
    virtual INetChannelHandler *GetMsgHandler() const = 0;
    virtual bool SendData(bf_write &msg, bool bReliable = true) = 0;
    virtual int GetNumBitsWritten(bool bReliable) = 0;
};
