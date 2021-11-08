// vim: set sts=4 ts=8 sw=4 tw=99 et:
#include "server.h"

#include <assert.h>

#include <filesystem>
#include <iostream>

#include "engine.h"
#include "fs.h"
#include "tier0/commandline.h"

using namespace std::chrono_literals;
using namespace std::string_literals;

Server* Server::sInstance = nullptr;

#if defined(_WIN32)
static constexpr char kLibraryExt[] = ".dll";
#elif defined(__linux__)
static constexpr char kLibraryExt[] = ".so";
#else
static constexpr char kLibraryExt[] = ".dylib";
#endif

Server::Server()
{
    assert(!sInstance);
    sInstance = this;
    thread_id_ = std::this_thread::get_id();
}

Server::~Server()
{
    assert(sInstance == this);
    sInstance = nullptr;
}

bool
Server::Start()
{
    LogManager::get()->AddListener(this);
    ConVar_Register();

    auto path = "gamedll"s + kLibraryExt;

    if (!dist_dir_.empty())
        path = dist_dir_ + "/" + path;

    char error[255];
    game_ = ke::SharedLib::Open(path.c_str(), error, sizeof(error));
    if (!game_) {
        Error("Could not open gamedll %s: %s\n", path.c_str(), error);
        return false;
    }
    game_ci_ = game_->get<CreateInterfaceFn>("CreateInterface");
    if (!game_ci_) {
        Error("Could not load gamedll: no CreateInterface\n");
        return false;
    }

    gamedll_ =
        reinterpret_cast<IServerGameDLL*>(game_ci_(INTERFACEVERSION_SERVERGAMEDLL, nullptr));
    if (!gamedll_) {
        Error("Could not load gamedll: %s not found\n", INTERFACEVERSION_SERVERGAMEDLL);
        return false;
    }

    game_clients_ =
        reinterpret_cast<IServerGameClients*>(game_ci_(INTERFACEVERSION_SERVERGAMECLIENTS, nullptr));
    if (!game_clients_) {
        Error("Could not load gamedll: %s not found\n", INTERFACEVERSION_SERVERGAMECLIENTS);
        return false;
    }

    // Notify gamedll of load.
    auto engine = Engine::get();
    if (!gamedll_->DLLInit(CreateInterfaceWrapper, nullptr, nullptr, &engine->vars())) {
        Error("Could not load gamedll: DLLInit returned false\n");
    }

    // Game is done loading. Load metamod and plugins.
    LoadPlugins();
    AddCommand("meta game");
    AddCommand("meta list");
    ProcessMessages();

    // Init and activate the server.
    if (!gamedll_->GameInit()) {
        Error("Could not load gamedll: GameInit returned false\n");
        return false;
    }
    if (auto val = CommandLine()->ParmValue("+maxplayers")) {
        if (auto ival = atoi(val); ival > 0)
            maxclients_ = ival;
    }

    // Load map if specified.
    auto map_name = CommandLine()->ParmValue("+map");
    if (map_name)
        ChangeLevel(map_name);

    return true;
}

void Server::Shutdown() {
    shutting_down_ = true;

    while (!plugins_.empty()) {
        auto plugin = std::move(plugins_.back());
        plugins_.pop_back();
        plugin->callbacks->Unload();
    }

    if (gamedll_)
        gamedll_->DLLShutdown();

    LogManager::get()->RemoveListener(this);
}

void
Server::Run()
{
    while (!interrupt_) {
        DoFrame();
        if (interrupt_)
            break;

        // Gross.
        int ms = int(Engine::get()->vars().interval_per_tick * 1000.0f);
        std::this_thread::sleep_for(std::chrono::milliseconds(ms));
    }

    interrupt_ = false;
}

void
Server::DoFrame()
{
    std::function<void()> work;
    {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!messages_.empty()) {
            work = std::move(messages_.front());
            messages_.pop_front();
        }
    }

    // Set before calling work, in case more state changes happen.
    pending_action_ = false;

    if (work)
        work();

    Engine::get()->Think();
}

void
Server::PostMessage(std::function<void()>&& msg)
{
    std::lock_guard<std::mutex> lock(mutex_);
    messages_.emplace_back(std::move(msg));
}

void
Server::InsertMessage(std::function<void()>&& msg)
{
    std::lock_guard<std::mutex> lock(mutex_);
    messages_.emplace_front(std::move(msg));
}

void
Server::ProcessMessages()
{
    assert(std::this_thread::get_id() == thread_id_);

    decltype(messages_) work;
    {
        std::lock_guard<std::mutex> lock(mutex_);
        work = std::move(messages_);
    }

    while (!work.empty()) {
        auto msg = std::move(work.front());
        work.pop_front();

        msg();
    }
}

void
Server::ExecuteAll()
{
    ProcessMessages();
}

void
Server::Log(const LoggingContext_t* cx, const char* message)
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (cx->severity == LogLevel::Warning)
        fprintf(stdout, "WARNING: ");
    else if (cx->severity == LogLevel::Error)
        fprintf(stdout, "ERROR: ");
    fprintf(stdout, "%s", message);

    if (!ke::EndsWith(message, "\n"))
        fprintf(stdout, "\n");
}

void Server::PluginLoad(std::string path_in) {
    assert(std::this_thread::get_id() == thread_id_);

    if (shutting_down_) {
        Error("Cannot load plugin %s during shutdown\n", path_in.c_str());
        return;
    }

    if (!std::filesystem::exists(path_in) && !ke::EndsWith(path_in, kLibraryExt))
        path_in += kLibraryExt;

    const char* path = path_in.c_str();

    char buffer[255];
    ke::RefPtr<ke::SharedLib> lib = ke::SharedLib::Open(path, buffer, sizeof(buffer));
    if (!lib) {
        Msg("Could not open %s: %s\n", path, buffer);
        return;
    }

    auto plugin = std::make_unique<Plugin>();
    plugin->path = path;
    plugin->lib = lib;

    auto ci = lib->get<CreateInterfaceFn>("CreateInterface");
    if (!ci) {
        Msg("Could not open %s: CreateInterface not found\n", path);
        return;
    }

    for (int i = 4; i >= 1; i--) {
        auto iface_name = ke::StringPrintf("ISERVERPLUGINCALLBACKS%03d", i);

        int ret;
        if (auto iface = ci(iface_name.c_str(), &ret)) {
            plugin->version = i;
            plugin->callbacks = reinterpret_cast<IServerPluginCallbacks*>(iface);
            break;
        }
    }
    if (!plugin->callbacks) {
        Msg("Could not load %s: No IServerPlugin callbacks\n", path);
        return;
    }
    if (!plugin->callbacks->Load(&CreateInterfaceWrapper, game_ci_)) {
        Msg("Could not load %s: load failed\n", path);
        return;
    }
    plugins_.emplace_back(std::move(plugin));

    Msg("Successfully loaded %s\n", path);
}

void
Server::AddCommand(std::string str)
{
    auto fun = [this, str{std::move(str)}]() mutable {
        DispatchCommand(std::move(str));
    };
    PostMessage(std::move(fun));
}

void
Server::InsertCommand(std::string str)
{
    auto fun = [this, str{std::move(str)}]() mutable {
        DispatchCommand(std::move(str));
    };
    InsertMessage(std::move(fun));
}

void
Server::DispatchCommand(std::string str)
{
    auto args = ParseArgs(str);
    if (args.empty())
        return;

    auto cmd = g_pCVar->FindCommandBase(args[0].c_str());
    if (!cmd) {
        ConMsg("Unknown command: %s\n", args[0].c_str());
        return;
    }

    for (const auto& plugin : plugins_)
        plugin->callbacks->SetCommandClient(-1);
    game_clients_->SetCommandClient(-1);

    if (cmd->IsCommand()) {
        CCommand ccargs(std::move(str), std::move(args));
        static_cast<ConCommand*>(cmd)->Dispatch(ccargs);
    } else if (args.size() == 1) {
        auto cvar = static_cast<ConVar*>(cmd);
        ConMsg("%s\n", cvar->GetString());
    } else {
        auto cvar = static_cast<ConVar*>(cmd);
        cvar->SetValue(args[1].c_str());
    }
}

void*
Server::CreateInterfaceWrapper(const char* name, int* ret)
{
    return Server::get()->CreateInterface(name, ret);
}

void*
Server::CreateInterface(const char* name, int* ret)
{
    if (strcmp(name, "MOCK_ENGINE") == 0) {
        if (ret)
            *ret = IFACE_OK;
        return Engine::get();
    }

    return ::CreateInterface(name, ret);
}

void Server::ChangeLevel(const char* map) {
    auto engine = Engine::get();
    if (!engine->map().empty()) {
        for (const auto& plugin : plugins_)
            plugin->callbacks->LevelShutdown();
        gamedll_->LevelShutdown();
    }

    auto old_map = engine->map();
    engine->ChangeLevel(map, "");

    for (const auto& plugin : plugins_)
        plugin->callbacks->LevelInit(map);

    gamedll_->LevelInit(engine->map().c_str(), "", old_map.c_str(), "", true, false);

    gamedll_->ServerActivate(engine->edicts(), engine->num_edicts(), maxclients_);
    for (const auto& plugin : plugins_)
        plugin->callbacks->ServerActivate(engine->edicts(), engine->num_edicts(), maxclients_);
}

void Server::LoadPlugins() {
    std::error_code ec;
    const std::filesystem::path addons{"addons"};
    for (const auto& entry : std::filesystem::directory_iterator{addons, ec}) {
        if (!ke::EndsWith(entry.path(), ".vdf"))
            continue;

        auto kv = std::make_unique<KeyValues>("Plugins");
        kv->LoadFromFile(nullptr, entry.path().c_str());

        if (auto file = kv->GetString("file", nullptr))
            PluginLoad(file);
    }
    if (ec) {
        Error("Could not open plugin directory %s: %s\n", addons.c_str(),
              ec.message().c_str());
    }
}

CON_COMMAND(plugin_load, "Load a plugin")
{
    Server* server = Server::get();
    if (args.ArgC() <= 1) {
        Msg("Usage: plugin_load <path>\n");
        return;
    }

    server->PluginLoad(args[1]);
}

CON_COMMAND(cvarlist, "List cvars/concommands")
{
    const char* prefix = nullptr;
    if (args.ArgC() > 2)
        prefix = args[1];

    ICvar::Iterator iter(g_pCVar);
    for (iter.SetFirst(); iter.IsValid(); iter.Next()) {
        auto cmd = iter.Get();
        if (prefix && !ke::StartsWith(cmd->GetName(), prefix))
            continue;

        auto help = cmd->GetHelpText();
        if (help && help[0])
            ConMsg("  %s - %s\n", cmd->GetName(), help);
        else
            ConMsg("  %s\n", cmd->GetName());
    }
}

CON_COMMAND(changelevel, "Change the map")
{
    if (args.ArgC() <= 1) {
        Msg("Usage: changelevel <map>\n");
        return;
    }

    std::string map = args.Arg(1);

    Server* server = Server::get();
    server->set_pending_action();
    server->InsertMessage([server, map]() -> void {
        server->ChangeLevel(map.c_str());
    });
}
