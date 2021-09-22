// vim: set sts=4 ts=8 sw=4 tw=99 et:
#pragma once

static constexpr char INTERFACEVERSION_VOICESERVER[] = "VoiceServer002";

class IVoiceServer
{
  public:
    virtual bool SetClientListening(int iReceiver, int iSender, bool bListen) = 0;
};
