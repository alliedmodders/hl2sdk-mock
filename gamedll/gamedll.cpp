// vim: set sts=4 ts=8 sw=4 tw=99 et:
#include "gamedll.h"

#include <amtl/am-string.h>
#include "tier0/platform.h"

ServerGame sGame;
PlayerInfoManager sPlayerManager;
ServerGameClients sGameClients;
ServerGameEnts sGameEnts;
CGlobalVars* gpGlobals = nullptr;

EXPOSE_SINGLE_INTERFACE_GLOBALVAR(ServerGame, IServerGameDLL, INTERFACEVERSION_SERVERGAMEDLL,
                                  sGame);
EXPOSE_SINGLE_INTERFACE_GLOBALVAR(PlayerInfoManager, IPlayerInfoManager,
                                  INTERFACEVERSION_PLAYERINFOMANAGER, sPlayerManager);
EXPOSE_SINGLE_INTERFACE_GLOBALVAR(ServerGameClients, IServerGameClients,
                                  INTERFACEVERSION_SERVERGAMECLIENTS, sGameClients);
EXPOSE_SINGLE_INTERFACE_GLOBALVAR(ServerGameEnts, IServerGameEnts,
                                  INTERFACEVERSION_SERVERGAMEENTS, sGameEnts);

bool ServerGame::DLLInit(CreateInterfaceFn engineFactory, CreateInterfaceFn physicsFactory,
                         CreateInterfaceFn fileSystemFactory, CGlobalVars *pGlobals)
{
    gpGlobals = pGlobals;
    return true;
}

void
ServerGame::DLLShutdown()
{
}

bool
ServerGame::LevelInit(char const* map, char const* entities, char const* old_level,
                      char const* landmark, bool load_game, bool background)
{
    return true;
}

void
ServerGame::LevelShutdown()
{
}

void ServerGame::ServerActivate(edict_t *pEdictList, int edictCount, int clientMax) {
}

void ServerGame::ServerHibernationUpdate(bool bHibernating) {
}

const char*
ServerGame::GetGameDescription()
{
    return "Mock Game";
}

bool
ServerGame::GameInit()
{
    return true;
}

bool
ServerGame::GetUserMessageInfo(int msg_type, char* name, int maxlength, int& size)
{
    if (msg_type == 0) {
        ke::SafeStrcpy(name, maxlength, "MockMsg");
        size = 0;
        return true;
    }
    return false;
}

void
ServerGame::GameFrame(bool simulating)
{
}

void
ServerGame::Think(bool final_tick)
{
}

void ServerGame::OnQueryCvarValueFinished(QueryCvarCookie_t iCookie, edict_t *pPlayerEntity,
                                          EQueryCvarValueStatus eStatus, const char *pCvarName,
                                          const char *pCvarValue)
{
}

ServerClass*
ServerGame::GetAllServerClasses()
{
    return nullptr;
}

IPlayerInfo *PlayerInfoManager::GetPlayerInfo(edict_t *pEdict) {
    Error("%s not implemented", __func__);
    return nullptr;
}

CGlobalVars*
PlayerInfoManager::GetGlobalVars()
{
    return gpGlobals;
}

void
ServerGameClients::ClientCommand(edict_t* edict, const CCommand& args)
{
    Error("%s not implemented", __func__);
}

void
ServerGameClients::ClientEarPosition(edict_t *pEntity, Vector *pEarOrigin)
{
    Error("%s not implemented", __func__);
}

void
ServerGameClients::ClientSettingsChanged(edict_t *pEdict)
{
    Error("%s not implemented", __func__);
}

int
ServerGameClients::GetMaxHumanPlayers()
{
    return 16;
}

void
ServerGameClients::ClientCommandKeyValues(edict_t *pEntity, KeyValues *pKeyValues)
{
    Error("%s not implemented", __func__);
}

bool ServerGameClients::ClientConnect(edict_t *pEntity, const char *pszName, const char *pszAddress,
                                      char *reject, int maxrejectlen) {
    Error("%s not implemented", __func__);
    return true;
}

void ServerGameClients::ClientPutInServer( edict_t *pEntity, char const *playername) {
    Error("%s not implemented", __func__);
}

void ServerGameClients::ClientDisconnect(edict_t *pEntity) {
    Error("%s not implemented", __func__);
}

void ServerGameClients::SetCommandClient(int index) {
}

edict_t* ServerGameEnts::BaseEntityToEdict(CBaseEntity* ent) {
    Error("%s not implemented", __func__);
    return nullptr;
}