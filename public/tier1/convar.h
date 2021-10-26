// vim: set sts=4 ts=8 sw=4 tw=99 et:
#pragma once

#include <functional>
#include <string>
#include <vector>

#include "utlstring.h"
#include "utlvector.h"

class ConCommandBase;
class ConCommand;
class ConVar;
class ICvar;

static constexpr char CVAR_INTERFACE_VERSION[] = "VEngineCvar007";

static constexpr int FCVAR_SPONLY = (1 << 6);
static constexpr int FCVAR_NOTIFY = (1 << 8);
static constexpr int FCVAR_DONTRECORD = (1<<17);

class IConCommandBaseAccessor
{
public:
    virtual bool RegisterConCommandBase(ConCommandBase* base) = 0;
};

class ConCommandBase
{
    friend void ConVar_Register(int, IConCommandBaseAccessor*);
    friend void ConVar_Unregister();

  protected:
    static ConCommandBase* sCommandList;

  public:
    explicit ConCommandBase(const char* name)
      : next_(sCommandList),
        name_(name)
    {
        sCommandList = this;
    }

    virtual const char* GetName() const { return name_; }
    virtual bool IsCommand() const = 0;
    virtual const char *GetHelpText() const { return help_; }

    virtual bool IsFlagSet(int flag) const {
        return !!(m_nFlags & flag);
    }

    ConCommandBase* next() const { return next_; }

    static void RegisterAll(ICvar* cvar);

    void Init();
    void AddFlags(int flags) {
        m_nFlags |= flags;
    }

    void set_owner_token(void* ptr) { owner_token_ = ptr; }
    void* owner_token() const { return owner_token_; }

  private:
    ConCommandBase* next_;
    const char* name_;
    void* owner_token_ = nullptr;

  protected:
    const char* help_ = nullptr;

  public:
    int m_nFlags = 0;
};

class ICvar
{
  public:
    virtual void RegisterConCommand(ConCommandBase* base) = 0;
    virtual void UnregisterConCommand(ConCommandBase* base) = 0;
    virtual ConCommand* FindCommand(const char* name) = 0;
    virtual ConCommandBase* FindCommandBase(const char* name) = 0;
    virtual const char* GetCommandLineValue(const char* var) = 0;
    virtual ConVar* FindVar(const char *var_name) = 0;
    virtual void CallGlobalChangeCallbacks(ConVar *var, const char *pOldString, float flOldValue) = 0;
    virtual void RemoveOwnedCmds(void* token) = 0;

  protected:
    class IIteratorImpl
    {
      public:
        virtual ~IIteratorImpl() {}
        virtual void SetFirst() = 0;
        virtual void Next() = 0;
        virtual bool IsValid() = 0;
        virtual ConCommandBase* Get() = 0;
        virtual void DeleteThis() = 0;
    };

    virtual IIteratorImpl* NewConCmdIterator() = 0;

  public:
    class Iterator
    {
      public:
        Iterator(ICvar* icvar)
          : impl_(icvar->NewConCmdIterator())
        {}
        ~Iterator() { impl_->DeleteThis(); }
        void SetFirst() { impl_->SetFirst(); }
        bool IsValid() { return impl_->IsValid(); }
        ConCommandBase* Get() { return impl_->Get(); }
        void Next() { impl_->Next(); }

      private:
        IIteratorImpl* impl_;
    };
};

class IConVar
{
  public:
    virtual void SetValue(const char* value) = 0;
    virtual void SetValue(float value) = 0;
    virtual void SetValue(int value) = 0;
    virtual const char* GetName() const = 0;
};

typedef void (*FnChangeCallback_t)(IConVar *var, const char *pOldValue, float flOldValue);

class ConVar : public ConCommandBase, public IConVar
{
  public:
    ConVar(const char* name, const char* value, int flags = 0);
    ConVar(const char* name, const char* value, int flags, const char* help);
    ConVar(const char* name, const char* value, int flags, const char* help, bool bMin,
           float fMin, bool bMax, float fMax, FnChangeCallback_t callback = nullptr);

    virtual const char* GetName() const override { return ConCommandBase::GetName(); }
    char const* GetString() const { return str_value_.c_str(); }
    virtual float GetFloat() const;
    virtual int GetInt() const;
    virtual bool IsCommand() const override { return false; }
    virtual void SetValue(const char* value) override;
    virtual void SetValue(float value) override;
    virtual void SetValue(int value) override;
    bool GetMin(float& minVal) const {
        minVal = m_fMinVal;
        return m_bHasMin;
    }
    bool GetMax(float& maxVal) const {
        maxVal = m_fMaxVal;
        return m_bHasMax;
    }
    bool GetBool() const { return !!GetInt(); }

    void Revert() { SetValue(def_); }

    const char* GetDefault() const { return def_; }

  private:
    const char* def_;
    std::string str_value_;
    FnChangeCallback_t callback_;

  public:
    bool m_bHasMin = false;
    float m_fMinVal = 0.0f;
    bool m_bHasMax = false;
    float m_fMaxVal = 0.0f;
};

class CCommand
{
  public:
    CCommand(std::string&& cmdline, std::vector<std::string>&& args)
      : cmdline_(std::move(cmdline)),
        args_(std::move(args))
    {}

    static constexpr int COMMAND_MAX_LENGTH = 512;

    const char* ArgS() const { return cmdline_.c_str(); }
    int ArgC() const { return (int)args_.size(); }
    const char* Arg(int index) const { return args_[index].c_str(); }
    const char* operator[](int index) const { return Arg(index); }

    static constexpr int MaxCommandLength() { return COMMAND_MAX_LENGTH - 1; }

  private:
    std::string cmdline_;
    std::vector<std::string> args_;
};

class ConCommand : public ConCommandBase
{
  public:
    ConCommand(const char* name, std::function<void(const CCommand&)> callback,
               const char* help = nullptr, int flags = 0)
      : ConCommandBase(name),
        callback_(callback)
    {
        if (help)
            help_ = help;
        Init();
    }

    virtual void Dispatch(const CCommand& cmd) {
        callback_(cmd);
    }
    virtual bool IsCommand() const override { return true; }
    virtual bool CanAutoComplete() { return false; }
    virtual int AutoCompleteSuggest(const char *partial, CUtlVector<CUtlString>& commands) {
        return 0;
    }

  private:
    std::function<void(const CCommand&)> callback_;
};

#define CON_COMMAND(name, help) \
    static void name(const CCommand& args); \
    static ConCommand name##_command(#name, name, help); \
    static void name(const CCommand& args)

void ConVar_Register(int flag = 0, IConCommandBaseAccessor* accessor = nullptr);
void ConVar_Unregister();

extern ICvar* g_pCVar;
