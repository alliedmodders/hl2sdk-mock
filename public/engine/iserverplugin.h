// vim: set sts=4 ts=8 sw=4 tw=99 et:
#pragma once

#include "tier1/interface.h"
#include "tier1/KeyValues.h"
#include "eiface.h"

enum PLUGIN_RESULT {
    PLUGIN_CONTINUE = 0,
    PLUGIN_OVERRIDE,
    PLUGIN_STOP,
};

enum EQueryCvarValueStatus {
    eQueryCvarValueStatus_ValueIntact = 0,
    eQueryCvarValueStatus_CvarNotFound = 1,
    eQueryCvarValueStatus_NotACvar = 2,
    eQueryCvarValueStatus_CvarProtected = 3
};

typedef int QueryCvarCookie_t;

static constexpr char INTERFACEVERSION_ISERVERPLUGINCALLBACKS[] = "ISERVERPLUGINCALLBACKS004";

class IServerPluginCallbacks
{
  public:
    virtual bool Load(CreateInterfaceFn interfaceFactory, CreateInterfaceFn gameServerFactory) = 0;
    virtual void Unload(void) = 0;
    virtual void Pause(void) = 0;
    virtual void UnPause(void) = 0;
    virtual const char *GetPluginDescription(void) = 0;      
    virtual void LevelInit(char const *pMapName) = 0;
    virtual void ServerActivate(edict_t *pEdictList, int edictCount, int clientMax) = 0;
    virtual void GameFrame(bool simulating) = 0;
    virtual void LevelShutdown(void) = 0;
    virtual void ClientActive(edict_t *pEntity) = 0;
    virtual void ClientFullyConnect(edict_t *pEntity) = 0;
    virtual void ClientDisconnect(edict_t *pEntity) = 0;
    virtual void ClientPutInServer(edict_t *pEntity, char const *playername) = 0;
    virtual void SetCommandClient(int index) = 0;
    virtual void ClientSettingsChanged(edict_t *pEdict) = 0;
    virtual PLUGIN_RESULT ClientConnect(bool *bAllowConnect, edict_t *pEntity, const char *pszName, const char *pszAddress, char *reject, int maxrejectlen) = 0;
    virtual PLUGIN_RESULT ClientCommand(edict_t *pEntity, const CCommand &args) = 0;
    virtual PLUGIN_RESULT NetworkIDValidated(const char *pszUserName, const char *pszNetworkID) = 0;
    virtual void OnQueryCvarValueFinished(QueryCvarCookie_t iCookie, edict_t *pPlayerEntity, EQueryCvarValueStatus eStatus, const char *pCvarName, const char *pCvarValue) = 0;
    virtual void OnEdictAllocated(edict_t *edict) = 0;
    virtual void OnEdictFreed(const edict_t *edict) = 0;    
    virtual bool BNetworkCryptKeyCheckRequired(uint32_t unFromIP, uint16_t usFromPort, uint32_t unAccountIdProvidedByClient,
        bool bClientWantsToUseCryptKey) = 0;
    virtual bool BNetworkCryptKeyValidate(uint32_t unFromIP, uint16_t usFromPort, uint32_t unAccountIdProvidedByClient,
        int nEncryptionKeyIndexFromClient, int numEncryptedBytesFromClient, uint8_t *pbEncryptedBufferFromClient,
        uint8_t *pbPlainTextKeyForNetchan) = 0;
};

static constexpr char INTERFACEVERSION_ISERVERPLUGINHELPERS[] = "ISERVERPLUGINHELPERS001";

enum DIALOG_TYPE
{
    DIALOG_MSG = 0,
    DIALOG_MENU,
    DIALOG_TEXT,
    DIALOG_ENTRY,
    DIALOG_ASKCONNECT
};

class IServerPluginHelpers
{
  public:
    virtual void CreateMessage(edict_t *pEntity, DIALOG_TYPE type, KeyValues *data, IServerPluginCallbacks *plugin) = 0;
    virtual void ClientCommand(edict_t *ent, const char *cmd) = 0; 
    virtual QueryCvarCookie_t StartQueryCvarValue(edict_t *pPlayerEntity, const char *pName) = 0;
};
