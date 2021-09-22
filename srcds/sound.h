// vim: set sts=4 ts=8 sw=4 tw=99 et:
#pragma once

#include "IEngineSound.h"

class EngineSound : public IEngineSound
{
  public:
    int EmitSound(IRecipientFilter& filter, int iEntIndex, int iChannel,
                          const char *pSoundEntry, unsigned int nSoundEntryHash,
                          const char *pSample, float flVolume, float flAttenuation,
                          int nSeed, int iFlags = 0, int iPitch = PITCH_NORM, 
                          const Vector *pOrigin = nullptr, const Vector *pDirection = nullptr,
                          CUtlVector<Vector>* pUtlVecOrigins = nullptr,
                          bool bUpdatePositions = true, float soundtime = 0.0f,
                          int speakerentity = -1) override;

    int EmitSound(IRecipientFilter& filter, int iEntIndex, int iChannel,
                          const char *pSoundEntry, unsigned int nSoundEntryHash,
                          const char *pSample, float flVolume, soundlevel_t level,
                          int nSeed, int iFlags = 0, int iPitch = PITCH_NORM, 
                          const Vector *pOrigin = nullptr, const Vector *pDirection = nullptr,
                          CUtlVector<Vector>* pUtlVecOrigins = nullptr,
                          bool bUpdatePositions = true, float soundtime = 0.0f,
                          int speakerentity = -1) override;
    void EmitSentenceByIndex(IRecipientFilter& filter, int iEntIndex, int iChannel,
                                     int iSentenceIndex, float flVolume, soundlevel_t iSoundlevel,
                                     int nSeed, int iFlags = 0, int iPitch = PITCH_NORM,
                                     const Vector *pOrigin = nullptr,
                                     const Vector *pDirection = nullptr,
                                     CUtlVector<Vector>* pUtlVecOrigins = nullptr,
                                     bool bUpdatePositions = true, float soundtime = 0.0f,
                                     int speakerentity = -1) override;


    bool PrecacheSound(const char *pSample, bool bPreload = false, bool bIsUISound = false) override;
    void PrefetchSound(const char *pSample) override;
    float GetSoundDuration(const char *pSample) override;  
    void StopSound(int iEntIndex, int iChannel, const char *pSample, unsigned int nSoundEntryHash) override;
    float GetDistGainFromSoundLevel(soundlevel_t soundlevel, float dist) override;
    bool IsSoundPrecached(const char *pSample) override;
};
