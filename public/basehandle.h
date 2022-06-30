// vim: set sts=4 ts=8 sw=4 tw=99 et:
#pragma once

#include "const.h"

class IHandleEntity;

class CBaseHandle
{
  public:
    CBaseHandle() : index_(INVALID_EHANDLE_INDEX) {}
    CBaseHandle(unsigned long index) : index_(index) {}
    int ToInt() const { return 0; }
    void Term() {}
    int GetEntryIndex() const { return 0; }
    int GetSerialNumber() const { return 0; }
    const CBaseHandle& Set(const IHandleEntity *pEntity) {
        (void)pEntity;
        return *this;
    }
    bool IsValid() const { return index_ != INVALID_EHANDLE_INDEX; }

    bool operator ==(unsigned long index) const {
        return index_ == index;
    }
    bool operator !=(const CBaseHandle& other) const {
        return index_ != other.index_;
    }

    IHandleEntity* Get() const {
      return nullptr;
    }

  private:
    unsigned long index_;
};
