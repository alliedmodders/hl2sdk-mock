// vim: set sts=4 ts=8 sw=4 tw=99 et:
#include "engine.h"

#include <amtl/am-string.h>
#include "server.h"
#include "tier0/logging.h"
#include "tier1/interface.h"

static Engine sInstance;

EXPOSE_SINGLE_INTERFACE_GLOBALVAR(Engine, IVEngineServer, "VEngineServer023", sInstance);

Engine* Engine::get() {
    return &sInstance;
}

Engine::Engine() {
    edicts_.resize(MAX_EDICTS);
    vars_.maxEntities = (int)edicts_.size();
    vars_.pEdicts = &edicts_[0];
    vars_.interval_per_tick = 1.0 / 60.0f;
}

void
Engine::ClientPrintf(edict_t* edict, const char* msg)
{
    LogManager::get()->Log(LogLevel::Message, "ClientPrintf: %s", msg);
}

void
Engine::ServerCommand(const char* str)
{
    Server::get()->AddCommand(str);
}

void
Engine::LogPrint(const char* msg)
{
    LogManager::get()->Log(LogLevel::Normal, "%s", msg);
}

void
Engine::GetGameDir(char* buffer, int length)
{
    ke::SafeStrcpy(buffer, length, game_dir_.c_str());
}

edict_t*
Engine::CreateFakeClient(const char*)
{
    Error("%s not implemented", __func__);
    return nullptr;
}

bool
Engine::LockNetworkStringTables(bool)
{
    Error("%s not implemented", __func__);
    return false;
}

INetChannelInfo*
Engine::GetPlayerNetInfo(int playerIndex)
{
    Error("%s not implemented", __func__);
    return nullptr;
}

void
Engine::EmitAmbientSound(int entindex, const Vector &pos, const char *samp, float vol,
                         soundlevel_t soundlevel, int fFlags, int pitch,
                         float delay)
{
    Error("%s not implemented", __func__);
}

void
Engine::FadeClientVolume(const edict_t *pEdict, float fadePercent, float fadeOutSeconds,
                         float holdTime, float fadeInSeconds)
{
    Error("%s not implemented", __func__);
}

bool
Engine::GetPlayerInfo(int ent_num, player_info_t *pinfo)
{
    Error("%s not implemented", __func__);
    return false;
}

int Engine::PrecacheModel(const char *s, bool preload)
{
    Error("%s not implemented", __func__);
    return 0;
}

int Engine::PrecacheSentenceFile(const char *s, bool preload)
{
    Error("%s not implemented", __func__);
    return 0;
}

int Engine::PrecacheDecal(const char *name, bool preload)
{
    Error("%s not implemented", __func__);
    return 0;
}

int Engine::PrecacheGeneric(const char *s, bool preload)
{
    Error("%s not implemented", __func__);
    return 0;
}

void Engine::SetFakeClientConVarValue(edict_t *pEntity, const char *cvar, const char *value)
{
    Error("%s not implemented", __func__);
}

bool Engine::IsModelPrecached(char const *s) const
{
    Error("%s not implemented", __func__);
    return false;
}

bool Engine::IsDecalPrecached(char const *s) const
{
    Error("%s not implemented", __func__);
    return false;
}

bool Engine::IsGenericPrecached(char const *s) const
{
    Error("%s not implemented", __func__);
    return false;
}

void Engine::Message_DetermineMulticastRecipients(bool usepas, const Vector& origin,
                                                  CPlayerBitVec& playerbits)
{
    Error("%s not implemented", __func__);
}

edict_t *Engine::CreateEdict(int iForceEdictIndex)
{
    Error("%s not implemented", __func__);
    return nullptr;
}

void Engine::RemoveEdict(edict_t *e)
{
    Error("%s not implemented", __func__);
}

int Engine::GetEntityCount()
{
    Error("%s not implemented", __func__);
    return 0;
}

void
Engine::ServerExecute()
{
    Server::get()->ExecuteAll();
}

int
Engine::GetPlayerUserId(const edict_t *e)
{
    Error("%s not implemented", __func__);
    return 0;
}

void
Engine::InsertServerCommand(const char *str)
{
    Server::get()->InsertCommand(str);
}

const char *Engine::GetClientConVarValue(int clientIndex, const char *name) {
    Error("%s not implemented", __func__);
    return "";
}

void Engine::ClientCommand(edict_t *pEdict, const char *szFmt, ...) {
    Error("%s not implemented", __func__);
}

QueryCvarCookie_t Engine::StartQueryCvarValue(edict_t *pPlayerEntity, const char *pName) {
    Error("%s not implemented", __func__);
    return -1;
}

bf_write *Engine::UserMessageBegin(IRecipientFilter *filter, int msg_type, const char* name) {
    Error("%s not implemented", __func__);
    return nullptr;
}

void Engine::MessageEnd() {
    Error("%s not implemented", __func__);
}

const char *Engine::GetPlayerNetworkIDString(const edict_t *e) {
    Error("%s not implemented", __func__);
    return "";
}

const CSteamID* Engine::GetClientSteamID(edict_t *pPlayerEdict) {
    Error("%s not implemented", __func__);
    return nullptr;
}

bool Engine::IsClientFullyAuthenticated(edict_t *pEdict) {
    Error("%s not implemented", __func__);
    return false;
}

void Engine::ChangeLevel(const char *s1, const char *s2) {
    map_ = s1;
    vars_.mapname = MAKE_STRING(map_.c_str());
}

CSharedEdictChangeInfo* Engine::GetSharedEdictChangeInfo() {
    Error("%s not implemented", __func__);
    return nullptr;
}

IChangeInfoAccessor* Engine::GetChangeAccessor(const edict_t *pEdict) {
    Error("%s not implemented", __func__);
    return nullptr;
}

int Engine::IsMapValid(const char *filename) {
    Error("%s not implemented", __func__);
    return 0;
}

const char *Engine::GetMapEntitiesString() {
    Error("%s not implemented", __func__);
    return "";
}

void Engine::Think() {
    // We don't do pausing yet.
    vars_.tickcount++;
    vars_.curtime = double(vars_.interval_per_tick) * vars_.tickcount;
}

class ServerPluginHelpers : public IServerPluginHelpers
{
  public:
    void CreateMessage(edict_t *pEntity, DIALOG_TYPE type, KeyValues *data,
                       IServerPluginCallbacks *plugin) override;
    void ClientCommand(edict_t *ent, const char *cmd) override;
    QueryCvarCookie_t StartQueryCvarValue(edict_t *pPlayerEntity, const char *pName) override;
} sServerPluginHelpers;

EXPOSE_SINGLE_INTERFACE_GLOBALVAR(ServerPluginHelpers, IServerPluginHelpers,
                                  INTERFACEVERSION_ISERVERPLUGINHELPERS, sServerPluginHelpers);

void ServerPluginHelpers::CreateMessage(edict_t *pEntity, DIALOG_TYPE type, KeyValues *data,
                                        IServerPluginCallbacks *plugin)
{
    Error("%s not implemented", __func__);
}

void ServerPluginHelpers::ClientCommand(edict_t *ent, const char *cmd) {
    Error("%s not implemented", __func__);
}

QueryCvarCookie_t ServerPluginHelpers::StartQueryCvarValue(edict_t *pPlayerEntity,
                                                           const char *pName)
{
    Error("%s not implemented", __func__);
    return InvalidQueryCvarCookie;
}
