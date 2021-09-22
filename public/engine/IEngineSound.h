// vim: set sts=4 ts=8 sw=4 tw=99 et:
#pragma once

#include "tier1/utlvector.h"

class IRecipientFilter;
class Vector;

typedef unsigned int HSOUNDSCRIPTHASH;

static constexpr int CHAN_AUTO = 0;
static constexpr int PITCH_NORM = 100;
static constexpr float VOL_NORM = 1.0f;
static constexpr float ATTN_NORM = 0.8f;

#define ATTN_TO_SNDLVL(a) (soundlevel_t)(int)((a) ? (50 + 20 / ((float)a)) : 0 )
#define SNDLVL_TO_ATTN( a ) ( (a > 50) ? (20.0f / (float)(a - 50)) : ( (a == 0) ? (0.0f) : (4.0f) ) )

enum soundlevel_t {
    SNDLVL_NORM = 75,
    SNDLVL_MAX = 255
};

static constexpr char IENGINESOUND_SERVER_INTERFACE_VERSION[] = "IEngineSoundServer003";

class IEngineSound
{
  public:
    virtual int EmitSound(IRecipientFilter& filter, int iEntIndex, int iChannel,
                          const char *pSoundEntry, unsigned int nSoundEntryHash,
                          const char *pSample, float flVolume, float flAttenuation,
                          int nSeed, int iFlags = 0, int iPitch = PITCH_NORM, 
                          const Vector *pOrigin = nullptr, const Vector *pDirection = nullptr,
                          CUtlVector<Vector>* pUtlVecOrigins = nullptr,
                          bool bUpdatePositions = true, float soundtime = 0.0f,
                          int speakerentity = -1) = 0;

    virtual int EmitSound(IRecipientFilter& filter, int iEntIndex, int iChannel,
                          const char *pSoundEntry, unsigned int nSoundEntryHash,
                          const char *pSample, float flVolume, soundlevel_t level,
                          int nSeed, int iFlags = 0, int iPitch = PITCH_NORM, 
                          const Vector *pOrigin = nullptr, const Vector *pDirection = nullptr,
                          CUtlVector<Vector>* pUtlVecOrigins = nullptr,
                          bool bUpdatePositions = true, float soundtime = 0.0f,
                          int speakerentity = -1) = 0;
    virtual void EmitSentenceByIndex(IRecipientFilter& filter, int iEntIndex, int iChannel,
                                     int iSentenceIndex, float flVolume, soundlevel_t iSoundlevel,
                                     int nSeed, int iFlags = 0, int iPitch = PITCH_NORM,
                                     const Vector *pOrigin = nullptr,
                                     const Vector *pDirection = nullptr,
                                     CUtlVector<Vector>* pUtlVecOrigins = nullptr,
                                     bool bUpdatePositions = true, float soundtime = 0.0f,
                                     int speakerentity = -1) = 0;


    virtual bool PrecacheSound(const char *pSample, bool bPreload = false, bool bIsUISound = false) = 0;
    virtual void PrefetchSound(const char *pSample) = 0;
    virtual float GetSoundDuration(const char *pSample) = 0;  
    virtual void StopSound(int iEntIndex, int iChannel, const char *pSample, unsigned int nSoundEntryHash) = 0;
    virtual float GetDistGainFromSoundLevel(soundlevel_t soundlevel, float dist) = 0;
    virtual bool IsSoundPrecached(const char *pSample) = 0;
};
