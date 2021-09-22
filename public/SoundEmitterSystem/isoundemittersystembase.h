// vim: set sts=4 ts=8 sw=4 tw=99 et:
#pragma once

#include "IEngineSound.h"
#include "utlsymbol.h"

enum gender_t
{
    GENDER_NONE = 0,
    GENDER_MALE,
    GENDER_FEMALE,
};

struct SoundFile
{
    CUtlSymbol symbol;
};

struct CSoundParameters
{
    int channel = CHAN_AUTO;
    int pitch = PITCH_NORM;
    soundlevel_t soundlevel = SNDLVL_NORM;
    float volume = VOL_NORM;
    char soundname[128] = {};
};

struct CSoundParametersInternal
{
    int NumSoundNames() const { return 0; }
    SoundFile* GetSoundNames() { return nullptr; }
};

static constexpr char SOUNDEMITTERSYSTEM_INTERFACE_VERSION[] = "VSoundEmitter003";

class ISoundEmitterSystemBase
{
  public:
    virtual int GetSoundIndex(const char *pName) const = 0;
    virtual bool IsValidIndex(int index) = 0;
    virtual gender_t GetActorGender(char const *actormodel) = 0;
    virtual bool GetParametersForSoundEx(const char *soundname, HSOUNDSCRIPTHASH& handle,
                                         CSoundParameters& params, gender_t gender,
                                         bool isbeingemitted = false) = 0;
    virtual CSoundParametersInternal *InternalGetParametersForSound(int index) = 0;
    virtual const char *GetWaveName(CUtlSymbol& sym) = 0;
};
