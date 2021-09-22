// vim: set sts=4 ts=8 sw=4 tw=99 et:
#pragma once

class IRecipientFilter
{
  public:
    virtual ~IRecipientFilter() {}
    virtual int GetRecipientCount() const = 0;
    virtual int GetRecipientIndex(int index) const = 0;
    virtual bool IsReliable() const = 0;
    virtual bool IsInitMessage() const = 0;
};
