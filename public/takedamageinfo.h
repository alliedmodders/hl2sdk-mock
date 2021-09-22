// vim: set sts=4 ts=8 sw=4 tw=99 et:
#pragma once

struct FireBulletsInfo_t
{
};

class CTakeDamageInfo
{
  public:
    Vector m_vecDamageForce;
    Vector m_vecDamagePosition;
    EHANDLE m_hInflictor;
    EHANDLE m_hWeapon;
};
