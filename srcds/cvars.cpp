// vim: set sts=4 ts=8 sw=4 tw=99 et:
#include "cvars.h"

#include <string.h>

#include "tier0/commandline.h"
#include "tier0/dbg.h"
#include "tier1/interface.h"

static CommandManager sCommandManager;

EXPOSE_SINGLE_INTERFACE_GLOBALVAR(CommandManager, ICvar, CVAR_INTERFACE_VERSION, sCommandManager);

CommandManager::CommandManager()
{
    g_pCVar = this;
}

CommandManager::~CommandManager()
{
    g_pCVar = nullptr;
}

void
CommandManager::RegisterConCommand(ConCommandBase* base)
{
    commands_.emplace(base->GetName(), base);
}

void
CommandManager::UnregisterConCommand(ConCommandBase* base)
{
    if (auto iter = commands_.find(base->GetName()); iter != commands_.end())
        commands_.erase(iter);
}

ConCommand*
CommandManager::FindCommand(const char* name)
{
    if (auto iter = commands_.find(name); iter != commands_.end()) {
        if (iter->second->IsCommand())
            return reinterpret_cast<ConCommand*>(iter->second);
    }
    return nullptr;
}

ConCommandBase*
CommandManager::FindCommandBase(const char* name)
{
    if (auto iter = commands_.find(name); iter != commands_.end())
        return iter->second;
    return nullptr;
}

void
CommandManager::RemoveOwnedCmds(void* token)
{
    auto iter = commands_.begin();
    while (iter != commands_.end()) {
        if (iter->second->owner_token() == token)
            iter = commands_.erase(iter);
        else
            iter++;
    }
}

const char*
CommandManager::GetCommandLineValue(const char* var)
{
    return CommandLine()->ParmValue(var, nullptr);
}

auto
CommandManager::NewConCmdIterator() -> ICvar::IIteratorImpl*
{
    std::vector<ConCommandBase*> cmds;
    for (const auto& p : commands_)
        cmds.emplace_back(p.second);

    std::sort(cmds.begin(), cmds.end(), [](ConCommandBase* a, ConCommandBase* b) -> bool {
        return strcmp(a->GetName(), b->GetName()) < 0;
    });

    return new CmdIterator(std::move(cmds));
}

ConVar* CommandManager::FindVar(const char *name) {
    auto cmd = FindCommandBase(name);
    if (cmd && !cmd->IsCommand())
        return static_cast<ConVar*>(cmd);
    return nullptr;
}

void CommandManager::CallGlobalChangeCallbacks(ConVar *var, const char *pOldString, float flOldValue) {
    Error("%s not yet implemented\n", __func__);
}

CommandManager::CmdIterator::CmdIterator(std::vector<ConCommandBase*>&& cmds)
  : cmds_(std::move(cmds)),
    iter_(cmds.begin())
{
}
