// vim: set sts=4 ts=8 sw=4 tw=99 et:
#pragma once

#include "eiface.h"
#include "game/server/iplayerinfo.h"

class PlayerInfoManager final : public IPlayerInfoManager
{
  public:
    IPlayerInfo *GetPlayerInfo(edict_t *pEdict) override;
    CGlobalVars *GetGlobalVars() override;
};

class ServerGameClients final : public IServerGameClients
{
  public:
    void ClientCommand(edict_t* edict, const CCommand& args) override;
    void ClientEarPosition(edict_t *pEntity, Vector *pEarOrigin) override;
    void ClientSettingsChanged(edict_t *pEdict) override;
    int GetMaxHumanPlayers() override;
    void ClientCommandKeyValues(edict_t *pEntity, KeyValues *pKeyValues) override;
    bool ClientConnect(edict_t *pEntity, const char *pszName, const char *pszAddress, char *reject, int maxrejectlen) override;
    void ClientPutInServer( edict_t *pEntity, char const *playername) override;
    void ClientDisconnect(edict_t *pEntity) override;
    void SetCommandClient(int index) override;
};

class ServerGame final : public IServerGameDLL
{
  public:
    bool DLLInit(CreateInterfaceFn engineFactory, CreateInterfaceFn physicsFactory,
                 CreateInterfaceFn fileSystemFactory, CGlobalVars *pGlobals) override;
    void DLLShutdown() override;
    void ServerActivate(edict_t *pEdictList, int edictCount, int clientMax) override;
    void ServerHibernationUpdate(bool bHibernating) override;
    bool LevelInit(char const* map, char const* entities, char const* old_level,
                   char const* landmark, bool load_game, bool background) override;
    void LevelShutdown() override;
    const char* GetGameDescription() override;
    bool GameInit() override;
    bool GetUserMessageInfo(int msg_type, char* name, int maxlength, int& size) override;
    ServerClass* GetAllServerClasses() override;
    void GameFrame(bool simulating) override;
    void Think(bool final_tick) override;
    void OnQueryCvarValueFinished(QueryCvarCookie_t iCookie, edict_t *pPlayerEntity,
                                  EQueryCvarValueStatus eStatus, const char *pCvarName,
                                  const char *pCvarValue) override;
};
