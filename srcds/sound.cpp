// vim: set sts=4 ts=8 sw=4 tw=99 et:
#include "sound.h"

#include "tier0/dbg.h"
#include "tier1/interface.h"

static EngineSound sEngineSound;

EXPOSE_SINGLE_INTERFACE_GLOBALVAR(EngineSound, IEngineSound, IENGINESOUND_SERVER_INTERFACE_VERSION,
		                  sEngineSound);

int EngineSound::EmitSound(IRecipientFilter& filter, int iEntIndex, int iChannel,
                           const char *pSoundEntry, unsigned int nSoundEntryHash,
                           const char *pSample, float flVolume, float flAttenuation,
                           int nSeed, int iFlags, int iPitch, 
                           const Vector *pOrigin, const Vector *pDirection,
                           CUtlVector<Vector>* pUtlVecOrigins,
                           bool bUpdatePositions, float soundtime,
                           int speakerentity) 
{
    Error("%s not implemented", __func__);
    return -1;
}

int EngineSound::EmitSound(IRecipientFilter& filter, int iEntIndex, int iChannel,
                           const char *pSoundEntry, unsigned int nSoundEntryHash,
                           const char *pSample, float flVolume, soundlevel_t level,
                           int nSeed, int iFlags, int iPitch, 
                           const Vector *pOrigin, const Vector *pDirection,
                           CUtlVector<Vector>* pUtlVecOrigins,
                           bool bUpdatePositions, float soundtime,
                           int speakerentity) 
{
    Error("%s not implemented", __func__);
    return -1;
}

void EngineSound::EmitSentenceByIndex(IRecipientFilter& filter, int iEntIndex, int iChannel,
                                      int iSentenceIndex, float flVolume, soundlevel_t iSoundlevel,
                                      int nSeed, int iFlags, int iPitch,
                                      const Vector *pOrigin,
                                      const Vector *pDirection,
                                      CUtlVector<Vector>* pUtlVecOrigins,
                                      bool bUpdatePositions, float soundtime,
                                      int speakerentity) 
{
    Error("%s not implemented", __func__);
}

bool EngineSound::PrecacheSound(const char *pSample, bool bPreload, bool bIsUISound)  {
    Error("%s not implemented", __func__);
    return false;
}

void EngineSound::PrefetchSound(const char *pSample) {
    Error("%s not implemented", __func__);
}

void EngineSound::StopSound(int iEntIndex, int iChannel, const char *pSample,
                            unsigned int nSoundEntryHash)
{
    Error("%s not implemented", __func__);
}

bool EngineSound::IsSoundPrecached(const char *pSample) {
    Error("%s not implemented", __func__);
    return false;
}

float EngineSound::GetSoundDuration(const char *pSample) {
    Error("%s not implemented", __func__);
    return 0.0f;
}

float EngineSound::GetDistGainFromSoundLevel(soundlevel_t soundlevel, float dist) {
    Error("%s not implemented", __func__);
    return 0.0f;
}

static SoundEmitterSystemBase sSoundEmitterSystemBase;

EXPOSE_SINGLE_INTERFACE_GLOBALVAR(SoundEmitterSystemBase, ISoundEmitterSystemBase, SOUNDEMITTERSYSTEM_INTERFACE_VERSION,
		                  sSoundEmitterSystemBase);

int SoundEmitterSystemBase::GetSoundIndex(const char *pName) const
{
    Error("%s not implemented", __func__);
    return -1;
}

bool SoundEmitterSystemBase::IsValidIndex(int index)
{
    Error("%s not implemented", __func__);
    return false;
}

gender_t SoundEmitterSystemBase::GetActorGender(char const *actormodel)
{
    Error("%s not implemented", __func__);
    return GENDER_NONE;
}
bool SoundEmitterSystemBase::GetParametersForSoundEx(const char *soundname, HSOUNDSCRIPTHASH& handle,
                                                     CSoundParameters& params, gender_t gender,
                                                     bool isbeingemitted)
{
    Error("%s not implemented", __func__);
    return false;
}

CSoundParametersInternal *SoundEmitterSystemBase::InternalGetParametersForSound(int index)
{
    Error("%s not implemented", __func__);
    return nullptr;
}

const char *SoundEmitterSystemBase::GetWaveName(CUtlSymbol& sym)
{
    Error("%s not implemented", __func__);
    return nullptr;
}
