// vim: set sts=4 ts=8 sw=4 tw=99 et:
#include "logmanager.h"

#include <algorithm>

#include <amtl/am-string.h>

LogManager*
LogManager::get()
{
    static LogManager sLogMan;
    return &sLogMan;
}

LogManager::LogManager()
{
    state_.emplace_back();
}

void
LogManager::AddListener(ILoggingListener* listener)
{
    std::lock_guard<std::mutex> lock(mutex_);
    state_.back().listeners.emplace_back(listener);
}

void
LogManager::RemoveListener(ILoggingListener* listener)
{
    std::lock_guard<std::mutex> lock(mutex_);
    auto iter = std::remove(state_.back().listeners.begin(), state_.back().listeners.end(),
                            listener);
    state_.back().listeners.erase(iter, state_.back().listeners.end());
}

void
LogManager::LogVa(LogLevel level, const char* fmt, va_list ap)
{
    auto message = ke::StringPrintfVa(fmt, ap);

    LoggingContext_t context;
    context.severity = level;

    std::lock_guard<std::mutex> lock(mutex_);
    for (const auto& listener : state_.back().listeners) {
        listener->Log(&context, message.c_str());
    }
}

void
LogManager::Log(LogLevel level, const char* fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    LogVa(level, fmt, ap);
    va_end(ap);
}

void
LogManager::PushState()
{
    state_.emplace_back();
}

void
LogManager::PopState()
{
    // Never pop the default state.
    if (state_.size() == 1)
        return;
}

void LoggingSystem_PushLoggingState(bool bThreadLocal, bool bClearState) {
    assert(!bThreadLocal);
    assert(!bClearState);
    LogManager::get()->PushState();
}

void LoggingSystem_PopLoggingState(bool bThreadLocal) {
    assert(!bThreadLocal);
    LogManager::get()->PopState();
}

void LoggingSystem_RegisterLoggingListener(ILoggingListener *pListener) {
    LogManager::get()->AddListener(pListener);
}
