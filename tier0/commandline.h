// vim: set sts=4 ts=8 sw=4 tw=99 et:
#pragma once
#include "tier0/icommandline.h"

#include <string>
#include <vector>

class CommandLineImpl final : public ICommandLine
{
  public:
    void Init(int argc, char** argv);
    const char* ParmValue(const char* key, const char* defval = nullptr) const override;
    int ParmValue(const char* key, int defval) const override;
    const char* GetCmdLine() const override;
    int FindParm(const char* key) const override;

    static CommandLineImpl* get();

  private:
    std::vector<std::string> orig_argv_;
    std::vector<std::string> argv_;
    mutable std::string cmdline_;
};

std::vector<std::string> ParseArgs(const std::string& cmdline);
