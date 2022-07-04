// vim: set sts=4 ts=8 sw=4 tw=99 et:
#pragma once

#include "edict.h"
#include "ehandle.h"

class CBaseEntity
{
  public:
    edict_t* edict() const { return edict_; }

  private:
    edict_t* edict_;
};

typedef CHandle<CBaseEntity> EHANDLE;
