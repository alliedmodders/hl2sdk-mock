// vim: set sts=4 ts=8 sw=4 tw=99 et:
#include "voice.h"

#include "tier0/dbg.h"
#include "tier1/interface.h"

static VoiceServer sVoiceServer;

EXPOSE_SINGLE_INTERFACE_GLOBALVAR(VoiceServer, IVoiceServer, INTERFACEVERSION_VOICESERVER,
		                  sVoiceServer);

bool VoiceServer::SetClientListening(int iReceiver, int iSender, bool bListen)
{
    Error("%s not implemented", __func__);
    return false;
}
