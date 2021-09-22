// vim: set sts=4 ts=8 sw=4 tw=99 et:
#pragma once

class CUtlString
{
  public:
    operator const char*() const { return impl_.data(); }

  private:
    std::string impl_;
};
