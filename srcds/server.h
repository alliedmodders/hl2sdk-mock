// vim: set sts=4 ts=8 sw=4 tw=99 et:
#pragma once

#include <chrono>
#include <deque>
#include <functional>
#include <future>
#include <list>
#include <memory>
#include <mutex>
#include <thread>
#include <unordered_map>
#include <vector>

#include <amtl/os/am-shared-library.h>
#include "engine.h"
#include "iserverplugin.h"
#include "tier0/logmanager.h"
#include "tier1/convar.h"

class Server final : public ILoggingListener
{
  public:
    Server();
    ~Server();

    void PostMessage(std::function<void()>&& msg);
    void InsertMessage(std::function<void()>&& msg);

    template <typename T, typename Callback>
    T RecvMessage(Callback&& msg) {
        std::promise<T> promise;
        auto future = promise.get_future();

        auto callback = [&promise, msg{std::move(msg)}]() -> void {
            promise.set_value(msg());
        };
        PostMessage(std::move(callback));

        future.wait();
        return future.get();
    }

    // Everything beyond must be called on the server thread.
    bool Start();
    void Shutdown();
    void Run();
    void DoFrame();
    void PluginLoad(std::string path_in);
    void AddCommand(std::string str);
    void InsertCommand(std::string str);
    void DispatchCommand(std::string str);
    void ExecuteAll();
    void Interrupt() { interrupt_ = true; }
    void ChangeLevel(const char* map);

    static Server* get() { return sInstance; }

    // Some commands, like changelevel, must be run at the top of a frame to
    // avoid re-entrancy issues. This flag allows the interactive console to
    // make sure to keep running until the command has fully completed.
    bool pending_action() const { return pending_action_; }
    void set_pending_action() { pending_action_ = true; }

    const std::string& dist_dir() const { return dist_dir_; }
    void set_dist_dir(const std::string& dir) { dist_dir_ = dir; }

  private:
    void LoadPlugins();
    void ProcessMessages();
    void Log(const LoggingContext_t* cx, const char* message) override;
    void* CreateInterface(const char* name, int* ret);

    static Server* sInstance;
    static void* CreateInterfaceWrapper(const char* name, int* ret);

    struct Plugin {
        int version = 0;
        IServerPluginCallbacks* callbacks = nullptr;
        ke::RefPtr<ke::SharedLib> lib;
        std::string path;
    };

  private:
    std::string dist_dir_;
    std::mutex mutex_;
    std::thread::id thread_id_;
    std::deque<std::function<void()>> messages_;
    std::vector<std::unique_ptr<Plugin>> plugins_;
    ke::RefPtr<ke::SharedLib> game_;
    CreateInterfaceFn game_ci_ = nullptr;
    IServerGameDLL* gamedll_ = nullptr;
    IServerGameClients* game_clients_ = nullptr;
    bool shutting_down_ = false;
    bool interrupt_ = false;
    int maxclients_ = 8;
    bool pending_action_ = false;
};
