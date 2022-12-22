// vim: set sts=4 ts=8 sw=4 tw=99 et:
#pragma once

#include "bitvec.h"
#include "const.h"
#include "convar.h"
#include "edict.h"
#include "engine/iserverplugin.h"
#include "engine/IEngineSound.h"
#include "game/server/iplayerinfo.h"
#include "inetchannelinfo.h"
#include "iserverentity.h"
#include "mathlib/mathlib.h"
#include "networkstringtabledefs.h"
#include "string_t.h"
#include "tier0/dbg.h"
#include "tier0/logging.h"
#include "tier0/mem.h"
#include "tier1/strtools.h"

static constexpr char INTERFACEVERSION_SERVERGAMEDLL[] = "ServerGameDLL005";
static constexpr char INTERFACEVERSION_VENGINESERVER[] = "VEngineServer023";

typedef int QueryCvarCookie_t;
static constexpr int InvalidQueryCvarCookie = -1;

class IServerGameDLL
{
public:
    virtual bool DLLInit(CreateInterfaceFn engineFactory, CreateInterfaceFn physicsFactory,
                         CreateInterfaceFn fileSystemFactory, CGlobalVars *pGlobals) = 0;
    virtual void DLLShutdown() = 0;
    virtual bool LevelInit(char const* map, char const* entities, char const* old_level,
                           char const* landmark, bool load_game, bool background) = 0;
    virtual void LevelShutdown() = 0;
    virtual void ServerActivate(edict_t *pEdictList, int edictCount, int clientMax) = 0;
    virtual void ServerHibernationUpdate(bool bHibernating) = 0;
    virtual const char* GetGameDescription() = 0;
    virtual bool GameInit() = 0;
    virtual bool GetUserMessageInfo(int msg_type, char* name, int maxlength, int& size) = 0;
    virtual ServerClass* GetAllServerClasses() = 0;
    virtual void GameFrame(bool simulating) = 0;
    virtual void Think(bool final_tick) = 0;
    virtual void OnQueryCvarValueFinished(QueryCvarCookie_t iCookie, edict_t *pPlayerEntity,
                                          EQueryCvarValueStatus eStatus, const char *pCvarName,
                                          const char *pCvarValue) = 0;
};

class bf_write;
class CSteamID;
class IRecipientFilter;
class SendTable;
struct player_info_t;

class IVEngineServer 
{
public:
    virtual void ClientPrintf(edict_t* edict, const char* msg) = 0;
    virtual void ServerCommand(const char* str) = 0;
    virtual void LogPrint(const char* msg) = 0;
    virtual void GetGameDir(char* buffer, int length) = 0;
    virtual bool IsDedicatedServer() = 0;
    virtual void SetView(edict_t* client, edict_t* view_ent) = 0;
    virtual void LightStyle(int style, const char* val) = 0;
    virtual void PlaybackTempEntity(IRecipientFilter& filter, float delay, const void* sender,
                                    const SendTable* st, int classID) = 0;
    virtual edict_t* CreateFakeClient(const char* name) = 0;
    virtual bool LockNetworkStringTables(bool lock) = 0;
    virtual INetChannelInfo* GetPlayerNetInfo(int playerIndex) = 0;
    virtual void EmitAmbientSound(int entindex, const Vector &pos, const char *samp, float vol,
                                  soundlevel_t soundlevel, int fFlags, int pitch,
                                  float delay = 0.0f) = 0;
    virtual void FadeClientVolume(const edict_t *pEdict, float fadePercent, float fadeOutSeconds,
                                  float holdTime, float fadeInSeconds) = 0;
    virtual bool GetPlayerInfo(int ent_num, player_info_t *pinfo) = 0;
    virtual int PrecacheModel(const char *s, bool preload = false) = 0;
    virtual int PrecacheSentenceFile(const char *s, bool preload = false) = 0;
    virtual int PrecacheDecal(const char *name, bool preload = false) = 0;
    virtual int PrecacheGeneric(const char *s, bool preload = false) = 0;
    virtual void SetFakeClientConVarValue(edict_t *pEntity, const char *cvar, const char *value) = 0;
    virtual bool IsModelPrecached(char const *s) const = 0;
    virtual bool IsDecalPrecached(char const *s) const = 0;
    virtual bool IsGenericPrecached(char const *s) const = 0;
    virtual void Message_DetermineMulticastRecipients(bool usepas, const Vector& origin, CPlayerBitVec& playerbits) = 0;
    virtual edict_t *CreateEdict(int iForceEdictIndex = -1) = 0;
    virtual void RemoveEdict(edict_t *e) = 0;
    virtual int GetEntityCount() = 0;
    virtual void ServerExecute() = 0;
    virtual int GetPlayerUserId(const edict_t *e) = 0; 
    virtual void InsertServerCommand(const char *str) = 0;
    virtual const char* GetClientConVarValue(int clientIndex, const char *name) = 0;
    virtual void ClientCommand(edict_t *pEdict, const char *szFmt, ...) = 0;
    virtual QueryCvarCookie_t StartQueryCvarValue(edict_t *pPlayerEntity, const char *pName) = 0;
    virtual bf_write* UserMessageBegin(IRecipientFilter *filter, int msg_type, const char* name) = 0;
    virtual void MessageEnd() = 0;
    virtual const char* GetPlayerNetworkIDString(const edict_t *e) = 0;
    virtual const CSteamID* GetClientSteamID(edict_t *pPlayerEdict) = 0;
    virtual bool IsClientFullyAuthenticated(edict_t *pEdict) = 0;
    virtual void ChangeLevel(const char *s1, const char *s2) = 0;
    virtual CSharedEdictChangeInfo* GetSharedEdictChangeInfo() = 0;
    virtual IChangeInfoAccessor* GetChangeAccessor(const edict_t *pEdict) = 0;
    virtual int IsMapValid(const char *filename) = 0;
    virtual const char *GetMapEntitiesString() = 0;
};

static constexpr char INTERFACEVERSION_SERVERGAMECLIENTS[] = "ServerGameClients004";

class IServerGameClients
{
public:
    virtual void ClientCommand(edict_t* edict, const CCommand& args) = 0;
    virtual void ClientEarPosition(edict_t *pEntity, Vector *pEarOrigin) = 0;
    virtual void ClientSettingsChanged(edict_t *pEdict) = 0;
    virtual int GetMaxHumanPlayers() = 0;
    virtual void ClientCommandKeyValues(edict_t *pEntity, KeyValues *pKeyValues) = 0;
    virtual bool ClientConnect(edict_t *pEntity, const char *pszName, const char *pszAddress, char *reject, int maxrejectlen) = 0;
    virtual void ClientPutInServer(edict_t *pEntity, char const *playername) = 0;
    virtual void ClientDisconnect(edict_t *pEntity) = 0;
    virtual void SetCommandClient(int index) = 0;
};

static constexpr char INTERFACEVERSION_SERVERGAMEENTS[] = "ServerGameEnts001";

class CBaseEntity;

class IServerGameEnts
{
  public:
    virtual edict_t* BaseEntityToEdict(CBaseEntity* ent) = 0;
};
