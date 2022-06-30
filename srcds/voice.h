// vim: set sts=4 ts=8 sw=4 tw=99 et:
#pragma once

#include "ivoiceserver.h"

class VoiceServer : public IVoiceServer
{
  public:
    virtual bool SetClientListening(int iReceiver, int iSender, bool bListen) override;
};
