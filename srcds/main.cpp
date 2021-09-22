// vim: set sts=4 ts=8 sw=4 tw=99 et:
#include <stdio.h>
#include <string.h>

#include <iostream>
#include <string>

#include "console.h"
#include "fs.h"
#include "server.h"
#include "tier0/commandline.h"

#ifdef _WIN32
# define NOMINMAX
# define WIN32_LEAN_AND_MEAN
# include <windows.h>
#else
# include <signal.h>
# include <unistd.h>
#endif

using namespace std::string_literals;

class ServerConsole
{
  public:
    bool Run();
    void Interrupt();
    void PostQuit() { quitting_ = true; }
    void EnterRunMode() { run_mode_ = true; }
    void RunOneFrame() { run_one_frame_ = true; }

  private:
    bool Setup();
    bool InstallHandlers();

  private:
    Server server_;
    bool quitting_ = false;
    bool run_mode_ = false;
    bool run_one_frame_ = false;
} sServerConsole;

int main(int argc, char** argv)
{
    CommandLineImpl::get()->Init(argc, argv);

    auto fs = FileSystem::get();
    for (int i = 1; i < argc; i++) {
        if (argv[i] == "+in"s && i != argc - 1)
            fs->AddSearchPath(argv[i + 1]);
    }

    return sServerConsole.Run() ? 0 : 1;
}

bool ServerConsole::Run() {
    if (!Setup())
        return false;
    if (!InstallHandlers()) {
        server_.Shutdown();
        return false;
    }

    fprintf(stdout, "Entering interactive mode.\n");
    fprintf(stdout, "Use \"run\", \"continue\", or \"think\" to process frames.\n");

    while (!quitting_) {
        fprintf(stdout, "> ");
        fflush(stdout);

        std::string cmdline;
        std::getline(std::cin, cmdline);

        server_.DispatchCommand(std::move(cmdline));
        while (run_one_frame_ || server_.pending_action()) {
            bool diag = run_one_frame_;
            run_one_frame_ = false;

            server_.DoFrame();

            if (diag && !run_one_frame_)
                ConMsg("Completed frame %d\n", Engine::get()->vars().tickcount);
        }

        if (run_mode_) {
            fprintf(stdout, "Entering run mode.\n");
            server_.Run();
            run_mode_ = false;
            fprintf(stdout, "Re-entering command mode.\n");
            fflush(stdin);
        }
    }

    server_.Shutdown();
    return true;
}

bool ServerConsole::Setup() {
    if (auto game_dir = CommandLine()->ParmValue("-game_dir"))
        Engine::get()->set_game_dir(game_dir);
    else
        Engine::get()->set_game_dir(".");

    const char* dir = Engine::get()->game_dir().c_str();
    if (chdir(dir)) {
        fprintf(stderr, "chdir %s failed: %s\n", dir, strerror(errno));
        return false;
    }

    if (!server_.Start())
        return false;
    return true;
}

void ServerConsole::Interrupt() {
    server_.Interrupt();
}

#ifdef _WIN32
BOOL WINAPI ControlHandler(DWORD signal) {
    if (signal == CTRL_C_EVENT)
        sServerConsole.Interrupt();
    return TRUE;
}
#else
void ControlHandler(int) {
    sServerConsole.Interrupt();
}
#endif

bool ServerConsole::InstallHandlers() {
#ifdef _WIN32
    if (!::SetConsoleCtrlHandler(ControlHandler, TRUE)) {
        fprintf(stderr, "Could not install console handler: %d\n", ::GetLastError());
        return false;
    }
#else
    struct sigaction handler;
    handler.sa_handler = ControlHandler;
    if (sigemptyset(&handler.sa_mask)) {
        fprintf(stderr, "sigemptyset failed: %s\n", strerror(errno));
        return false;
    }
    handler.sa_flags = SA_RESTART;
    if (sigaction(SIGINT, &handler, nullptr)) {
        fprintf(stderr, "sigaction SIGINT failed: %s\n", strerror(errno));
        return false;
    }
#endif
    return true;
}

CON_COMMAND(think, "Run a single frame.") {
    sServerConsole.RunOneFrame();
}

CON_COMMAND(quit, "Quit/exit srcds") {
    sServerConsole.PostQuit();
}
static ConCommand exit_cmd("exit", quit, "Quit/exit srcds");

CON_COMMAND(run, "Enter run mode") {
    sServerConsole.EnterRunMode();
}
static ConCommand continue_cmd("continue", run, "Enter run mode");
