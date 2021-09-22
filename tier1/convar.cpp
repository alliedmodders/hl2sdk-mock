// vim: set sts=4 ts=8 sw=4 tw=99 et:
#include "convar.h"

ConCommandBase* ConCommandBase::sCommandList = nullptr;

ICvar* g_pCVar = nullptr;
static IConCommandBaseAccessor* sConCommandBaseAccessor = nullptr;

void ConCommandBase::Init() {
    if (sConCommandBaseAccessor)
        sConCommandBaseAccessor->RegisterConCommandBase(this);
}

void
ConCommandBase::RegisterAll(ICvar* cvar)
{
    for (auto iter = sCommandList; iter; iter = iter->next_)
        cvar->RegisterConCommand(iter);
}

ConVar::ConVar(const char* name, const char* value, int flags)
  : ConCommandBase(name),
    def_(value),
    str_value_(value)
{
    Init();
}

ConVar::ConVar(const char* name, const char* value, int flags, const char* help)
  : ConCommandBase(name),
    def_(value),
    str_value_(value)
{
    m_nFlags = flags;
    help_ = help;

    Init();
}

ConVar::ConVar(const char* name, const char* value, int flags, const char* help, bool bMin,
               float fMin, bool bMax, float fMax, FnChangeCallback_t callback)
  : ConCommandBase(name),
    def_(value),
    str_value_(value),
    callback_(callback),
    m_bHasMin(bMin),
    m_fMinVal(fMin),
    m_bHasMax(fMax),
    m_fMaxVal(fMax)
{
    help_ = help;

    Init();
}

void
ConVar::SetValue(const char* value)
{
    if (str_value_ == value)
        return;

    if (callback_)
        callback_(this, str_value_.c_str(), GetFloat());
    str_value_ = value;
}

void
ConVar::SetValue(float value)
{
    SetValue(std::to_string(value).c_str());
}

void
ConVar::SetValue(int value)
{
    SetValue(std::to_string(value).c_str());
}

float ConVar::GetFloat() const {
    return atof(str_value_.c_str());
}

int ConVar::GetInt() const {
    return atoi(str_value_.c_str());
}

static bool sConvarsRegistered = false;

void ConVar_Register(int flag, IConCommandBaseAccessor* accessor) {
    if (sConvarsRegistered || !g_pCVar)
        return;
    sConvarsRegistered = true;

    for (auto iter = ConCommandBase::sCommandList; iter; iter = iter->next()) {
        iter->AddFlags(flag);
        iter->set_owner_token(&sConvarsRegistered);
        if (accessor)
            accessor->RegisterConCommandBase(iter);
        else
            g_pCVar->RegisterConCommand(iter);
    }

    sConCommandBaseAccessor = accessor;
}

void ConVar_Unregister() {
    if (!sConvarsRegistered || !g_pCVar)
        return;
    g_pCVar->RemoveOwnedCmds(&sConvarsRegistered);
    sConvarsRegistered = false;
    sConCommandBaseAccessor = nullptr;
}
