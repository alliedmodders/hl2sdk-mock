// vim: set sts=4 ts=8 sw=4 tw=99 et:
#pragma once

static constexpr char INTERFACEVERSION_GAMEEVENTSMANAGER2[] = "GAMEEVENTSMANAGER002";

static constexpr int EVENT_DEBUG_ID_INIT = 42;

class IGameEvent
{
  public:
    virtual ~IGameEvent() {};
    virtual const char *GetName() const = 0;

    virtual bool IsReliable() const = 0;
    virtual bool IsLocal() const = 0;
    virtual bool IsEmpty(const char *keyName = nullptr) = 0;
    
    // Data access
    virtual bool GetBool(const char *keyName = nullptr, bool defaultValue = false) = 0;
    virtual int GetInt(const char *keyName = nullptr, int defaultValue = 0) = 0;
    virtual float GetFloat(const char *keyName = nullptr, float defaultValue = 0.0f) = 0;
    virtual const char *GetString(const char *keyName = nullptr, const char *defaultValue = "") = 0;
    virtual const void *GetPtr(const char *keyname = nullptr, const void *defaultValues = nullptr) = 0;

    virtual void SetBool(const char *keyName, bool value) = 0;
    virtual void SetInt(const char *keyName, int value) = 0;
    virtual void SetFloat(const char *keyName, float value) = 0;
    virtual void SetString(const char *keyName, const char *value) = 0;
    virtual void SetPtr(const char *keyname, const void *value) = 0;
};

class IGameEventListener2
{
  public:
    virtual ~IGameEventListener2() {}
    virtual void FireGameEvent(IGameEvent *event) = 0;
};

class IGameEventManager2
{
  public:
    virtual IGameEvent *CreateEvent(const char *name, bool bForce = false, int *pCookie = nullptr) = 0;
    virtual bool FireEvent(IGameEvent *event, bool bDontBroadcast = false) = 0;
    virtual void FreeEvent(IGameEvent *event) = 0;
    virtual IGameEvent *DuplicateEvent(IGameEvent *event) = 0;
    virtual bool AddListener(IGameEventListener2 *listener, const char *name, bool bServerSide) = 0;
    virtual void RemoveListener(IGameEventListener2 *listener) = 0;
    virtual bool FindListener(IGameEventListener2 *listener, const char *name) = 0;
};
