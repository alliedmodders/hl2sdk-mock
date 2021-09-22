// vim: set sts=4 ts=8 sw=4 tw=99 et:
#include "console.h"

#include <ctype.h>
#include <stdio.h>

#include <iostream>
#include <string>

#include <amtl/am-string.h>

#include "tier0/dbg.h"
#include "server.h"

#if 0
void
Console::Run()
{
    Server* server = Server::get();

    while (true) {
        fprintf(stdout, "> ");
        fflush(stdout);

        std::string cmdline;
        std::getline(std::cin, cmdline);

        auto args = ParseArgs(cmdline);
        if (args.empty())
            continue;
        if (args[0] == "quit" || args[0] == "exit")
            break;

        auto iter = commands_.find(args[0]);
        if (iter == commands_.end()) {
            fprintf(stdout, "Unknown command.\n");
            continue;
        }

        ConCommandBase* base = iter->second;
        if (base->IsCommand()) {
            ConCommand* cmd = reinterpret_cast<ConCommand*>(base);
            CCommand ccmd(std::move(cmdline), std::move(args));

            server->PostMessage([cmd, ccmd{std::move(ccmd)}]() -> void {
                cmd->Dispatch(ccmd);
            });
            continue;
        }

        ConVar* cvar = reinterpret_cast<ConVar*>(base);
        if (args.empty()) {
            auto value = server->RecvMessage<std::string>([cvar]() -> std::string {
                return cvar->GetString();
            });

            fprintf(stdout, "%s\n", value.c_str());
        } else {
            auto value = args[1];

            server->PostMessage([cvar, value{std::move(value)}]() -> void {
                cvar->SetValue(value.c_str());
            });
        }
    }
}

#endif
