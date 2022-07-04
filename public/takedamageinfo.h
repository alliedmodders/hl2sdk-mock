// vim: set sts=4 ts=8 sw=4 tw=99 et:
#pragma once

#include <float.h>
#include "game/baseentity.h"
#include "mathlib/vector.h"

static constexpr float BASEDAMAGE_NOT_SPECIFIED = FLT_MAX;

struct FireBulletsInfo_t
{
  int m_iShots;
};

class CTakeDamageInfo
{
  public:
    CTakeDamageInfo();
    CBaseEntity* GetInflictor() const;
    void SetInflictor(CBaseEntity* entity);
    CBaseEntity* GetWeapon() const;
    void SetWeapon(CBaseEntity* entity);
    CBaseEntity* GetAttacker() const;
    void SetAttacker(CBaseEntity* entity);
    float GetDamage() const;
    void SetDamage(float flDamage);
    float GetMaxDamage() const;
    float GetBaseDamage() const;
    Vector GetDamageForce() const;
    Vector GetDamagePosition() const;
    Vector GetReportedPosition() const;
    int GetDamageType() const;
    void SetDamageType(int bitsDamageType);
    int GetDamageCustom() const;
    int GetAmmoType() const;
    void SetAmmoType(int ammoType);

    Vector m_vecDamageForce;
    Vector m_vecDamagePosition;
    Vector m_vecReportedPosition;
    EHANDLE m_hInflictor;
    EHANDLE m_hAttacker;
    EHANDLE m_hWeapon;
    float m_flDamage;
    float m_flMaxDamage;
    float m_flBaseDamage;
    int m_bitsDamageType;
    int m_iDamageCustom;
    int m_iAmmoType;
    float m_flRadius;
};

inline CBaseEntity* CTakeDamageInfo::GetInflictor() const {
    return m_hInflictor.Get();
}
inline void CTakeDamageInfo::SetInflictor(CBaseEntity* entity) {
    m_hInflictor = entity;
}
inline CBaseEntity* CTakeDamageInfo::GetWeapon() const {
    return m_hWeapon.Get();
}
inline void CTakeDamageInfo::SetWeapon(CBaseEntity* entity) {
    m_hWeapon = entity;
}
inline CBaseEntity* CTakeDamageInfo::GetAttacker() const {
    return m_hAttacker.Get();
}
inline void CTakeDamageInfo::SetAttacker(CBaseEntity* entity) {
    m_hAttacker = entity;
}
inline float CTakeDamageInfo::GetDamage() const {
    return m_flDamage;
}
inline void CTakeDamageInfo::SetDamage(float flDamage) {
    m_flDamage = flDamage;
}
inline float CTakeDamageInfo::GetMaxDamage() const {
    return m_flMaxDamage;
}
inline float CTakeDamageInfo::GetBaseDamage() const {
    return m_flBaseDamage;
}
inline Vector CTakeDamageInfo::GetDamageForce() const {
    return m_vecDamageForce;
}
inline Vector CTakeDamageInfo::GetDamagePosition() const {
    return m_vecDamagePosition;
}
inline Vector CTakeDamageInfo::GetReportedPosition() const {
    return m_vecReportedPosition;
}
inline int CTakeDamageInfo::GetDamageType() const {
    return m_bitsDamageType;
}
inline void CTakeDamageInfo::SetDamageType(int bitsDamageType) {
    m_bitsDamageType = bitsDamageType;
}
inline int CTakeDamageInfo::GetDamageCustom() const {
    return m_iDamageCustom;
}
inline int CTakeDamageInfo::GetAmmoType() const {
    return m_iAmmoType;
}
inline void CTakeDamageInfo::SetAmmoType(int ammoType) {
    m_iAmmoType = ammoType;
}
