// vim: set sts=4 ts=8 sw=4 tw=99 et:
#include "tier1/convar.h"

class CommandManager : public ICvar
{
  public:
    CommandManager();
    ~CommandManager();

    void RegisterConCommand(ConCommandBase* base) override;
    void UnregisterConCommand(ConCommandBase* base) override;
    ConCommand* FindCommand(const char* name) override;
    ConCommandBase* FindCommandBase(const char* name) override;
    const char* GetCommandLineValue(const char* var) override;
    IIteratorImpl* NewConCmdIterator() override;
    ConVar* FindVar(const char *var_name) override;
    void CallGlobalChangeCallbacks(ConVar *var, const char *pOldString, float flOldValue) override;
    void RemoveOwnedCmds(void* token) override;

    class CmdIterator : public ICvar::IIteratorImpl
    {
      public:
        CmdIterator(std::vector<ConCommandBase*>&& cmds);
        void SetFirst() override { iter_ = cmds_.begin(); }
        void Next() override { iter_++; }
        bool IsValid() override { return iter_ != cmds_.end(); }
        ConCommandBase* Get() override { return *iter_; }
        void DeleteThis() override { delete this; }

      private:
        std::vector<ConCommandBase*> cmds_;
        std::vector<ConCommandBase*>::iterator iter_;
    };

  private:
    std::unordered_map<std::string, ConCommandBase*> commands_;
};
