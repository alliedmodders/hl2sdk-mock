// vim: set sts=4 ts=8 sw=4 tw=99 et:
#pragma once

#include <string>

#include "eiface.h"

class Engine final : public IVEngineServer
{
  public:
    Engine();
    void ClientPrintf(edict_t* edict, const char* msg) override;
    void ServerCommand(const char* str) override;
    void LogPrint(const char* msg) override;
    void GetGameDir(char* buffer, int length) override;
    bool IsDedicatedServer() override { return true; }
    void SetView(edict_t*, edict_t*) override {}
    void LightStyle(int, const char*) override {}
    void PlaybackTempEntity(IRecipientFilter&, float, const void*,
                            const SendTable*, int) override {}
    edict_t* CreateFakeClient(const char* name) override;
    bool LockNetworkStringTables(bool lock) override;
    INetChannelInfo* GetPlayerNetInfo(int playerIndex) override;
    void EmitAmbientSound(int entindex, const Vector &pos, const char *samp, float vol,
                          soundlevel_t soundlevel, int fFlags, int pitch,
                          float delay = 0.0f) override;
    void FadeClientVolume(const edict_t *pEdict, float fadePercent, float fadeOutSeconds,
                          float holdTime, float fadeInSeconds) override;
    bool GetPlayerInfo(int ent_num, player_info_t *pinfo) override;
    int PrecacheModel(const char *s, bool preload = false) override;
    int PrecacheSentenceFile(const char *s, bool preload = false) override;
    int PrecacheDecal(const char *name, bool preload = false) override;
    int PrecacheGeneric(const char *s, bool preload = false) override;
    void SetFakeClientConVarValue(edict_t *pEntity, const char *cvar, const char *value) override;
    bool IsModelPrecached(char const *s) const override;
    bool IsDecalPrecached(char const *s) const override;
    bool IsGenericPrecached(char const *s) const override;
    void Message_DetermineMulticastRecipients(bool usepas, const Vector& origin, CPlayerBitVec& playerbits) override;
    edict_t *CreateEdict(int iForceEdictIndex = -1) override;
    void RemoveEdict(edict_t *e) override;
    int GetEntityCount() override;
    void ServerExecute() override;
    int GetPlayerUserId(const edict_t *e) override;
    void InsertServerCommand(const char *str) override;
    const char *GetClientConVarValue(int clientIndex, const char *name) override;
    void ClientCommand(edict_t *pEdict, const char *szFmt, ...) override;
    QueryCvarCookie_t StartQueryCvarValue(edict_t *pPlayerEntity, const char *pName) override;
    bf_write *UserMessageBegin(IRecipientFilter *filter, int msg_type, const char* name) override;
    void MessageEnd() override;
    const char *GetPlayerNetworkIDString(const edict_t *e) override;
    const CSteamID* GetClientSteamID(edict_t *pPlayerEdict) override;
    bool IsClientFullyAuthenticated(edict_t *pEdict) override;
    void ChangeLevel(const char *s1, const char *s2) override;
    CSharedEdictChangeInfo* GetSharedEdictChangeInfo() override;
    IChangeInfoAccessor* GetChangeAccessor(const edict_t *pEdict) override;
    int IsMapValid(const char *filename) override;

    void Think();

    void set_game_dir(const std::string& dir) { game_dir_ = dir; }
    const std::string& game_dir() const { return game_dir_; }

    static Engine* get();

    edict_t* edicts() { return &edicts_[0]; }
    int num_edicts() const { return (int)edicts_.size(); }
    CGlobalVars& vars() { return vars_; }
    const std::string& map() const { return map_; }

  private:
    std::string game_dir_;
    std::vector<edict_t> edicts_;
    CGlobalVars vars_;
    std::string map_;
};
