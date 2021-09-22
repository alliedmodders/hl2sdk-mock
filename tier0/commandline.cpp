// vim: set sts=4 ts=8 sw=4 tw=99 et:
#include "commandline.h"

#include <limits.h>

#include <fstream>
#include <streambuf>

#include <amtl/am-string.h>

using namespace std::string_literals;

CommandLineImpl sCommandLine;

void
CommandLineImpl::Init(int argc, char** argv)
{
    for (int i = 0; i < argc; i++)
        argv_.emplace_back(argv[i]);

    // Force cmdline_ to be set.
    GetCmdLine();

    int game_idx = FindParm("-game");
    if (game_idx == -1) {
        argv_.emplace_back("-game"s);
        argv_.emplace_back("mock"s);
        cmdline_ += " -game mock"s;
    } else if (game_idx == (int)argv_.size() - 1) {
        argv_.emplace_back("mock"s);
    } else if (argv_[game_idx + 1] != "mock") {
        argv_[game_idx + 1] = "mock"s;
    }
}

int
CommandLineImpl::FindParm(const char* key) const
{
    for (size_t i = 0; i < argv_.size(); i++) {
        if (argv_[i] == key)
            return (int)i;
    }
    return -1;
}

const char*
CommandLineImpl::ParmValue(const char* key, const char* defval) const
{
    for (size_t i = 0; i < argv_.size(); i++) {
        if (argv_[i] == key) {
            if (i == argv_.size() - 1)
                return defval;
            return argv_[i + 1].c_str();
        }
    }
    return defval;
}

int
CommandLineImpl::ParmValue(const char* key, int defval) const
{
    const char* val = ParmValue(key, nullptr);
    if (!val)
        return defval;

    errno = 0;

    char *endptr;
    auto rv = strtol(val, &endptr, 10);
    if ((rv == LONG_MAX || rv == LONG_MIN) && errno == ERANGE)
        return defval;
    if (!rv && (endptr == val || *endptr != '\0'))
        return defval;
    return rv;
}

const char*
CommandLineImpl::GetCmdLine() const
{
    if (!cmdline_.empty())
        return cmdline_.c_str();
#ifdef _WIN32
    cmdline_ = ke::Join(" ", argv_);
#else
    std::ifstream cmdline("/proc/self/cmdline");
    cmdline_ = std::string(std::istreambuf_iterator<char>(cmdline),
                           std::istreambuf_iterator<char>());
#endif

    return cmdline_.c_str();
}

ICommandLine* CommandLine() {
    return &sCommandLine;
}

CommandLineImpl*
CommandLineImpl::get()
{
    return &sCommandLine;
}

std::vector<std::string>
ParseArgs(const std::string& cmdline)
{
    std::vector<std::string> args;

    size_t i = 0;
    while (true) {
        while (i < cmdline.size() && isspace(cmdline[i]))
            i++;
        if (i >= cmdline.size())
            break;

        bool quoted = false;
        if (cmdline[i] == '"' && i != cmdline.size() - 1) {
            quoted = true;
            i++;
        }

        std::string arg;
        while (i < cmdline.size()) {
            if (quoted) {
                if (cmdline[i] == '"') {
                    i++;
                    break;
                }
            } else if (cmdline[i] == '"') {
                i++;
                continue;
            } else if (isspace(cmdline[i])) {
                i++;
                break;
            }
            arg.push_back(cmdline[i]);
            i++;
        }
        args.emplace_back(std::move(arg));
    }

    return args;
}
