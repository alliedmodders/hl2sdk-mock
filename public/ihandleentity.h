// vim: set sts=4 ts=8 sw=4 tw=99 et:
#pragma once

#include "basehandle.h"

class IHandleEntity
{
  public:
    virtual const CBaseHandle& GetRefEHandle() const = 0;
};
