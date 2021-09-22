// vim: set sts=4 ts=8 sw=4 tw=99 et:
#pragma once

class CLC_VoiceData;

class INetChannelHandler
{
  public:
};

class IClientMessageHandler : public INetChannelHandler
{
  public:
    virtual bool ProcessVoiceData(CLC_VoiceData* data) = 0;
};
