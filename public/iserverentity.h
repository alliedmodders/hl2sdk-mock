// vim: set sts=4 ts=8 sw=4 tw=99 et:
#pragma once

#include "iserverunknown.h"
#include "string_t.h"

class IServerEntity : public IServerUnknown
{
  public:
    virtual string_t GetModelName() const = 0;
};
