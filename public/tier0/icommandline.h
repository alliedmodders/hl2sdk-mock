// vim: set sts=4 ts=8 sw=4 tw=99 et:
#pragma once

class ICommandLine
{
  public:
    virtual const char* ParmValue(const char* key, const char* defval = nullptr) const = 0;
    virtual int ParmValue(const char* key, int defval) const = 0;
    virtual const char* GetCmdLine() const = 0;
    virtual int FindParm(const char* key) const = 0;
};

extern ICommandLine* CommandLine();
