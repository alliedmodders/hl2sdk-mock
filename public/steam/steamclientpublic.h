// vim: set sts=4 ts=8 sw=4 tw=99 et:
#pragma once

#include <stdint.h>

enum EUniverse {
    k_EUniverseInvalid = 0,
    k_EUniversePublic = 1,
    k_EUniverseBeta = 2,
    k_EUniverseInternal = 3,
    k_EUniverseDev = 4,
    k_EUniverseRC = 5,
    k_EUniverseMax
};

enum EAccountType {
    k_EAccountTypeInvalid = 0,            
    k_EAccountTypeIndividual = 1,
    k_EAccountTypeMultiseat = 2,
    k_EAccountTypeGameServer = 3,
    k_EAccountTypeAnonGameServer = 4,
    k_EAccountTypePending = 5,
    k_EAccountTypeContentServer = 6,
    k_EAccountTypeClan = 7,
    k_EAccountTypeChat = 8,
    k_EAccountTypeAnonUser = 10,
    k_EAccountTypeMax
};

class CSteamID
{
  public:
    CSteamID() {}
    CSteamID(uint64_t val) {}
    uint64_t ConvertToUint64() const { return 0; }
    bool IsValid() const { return false; }
    EUniverse GetEUniverse() const { return k_EUniverseInvalid; }
    uint32_t GetAccountID() const { return 0; }
    uint32_t GetUnAccountInstance() const { return 0; }
    EAccountType GetEAccountType() const { return k_EAccountTypeInvalid; }

    bool operator !=(const CSteamID& other) const {
        return false;
    }
};

const CSteamID k_steamIDNil;
