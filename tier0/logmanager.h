// vim: set sts=4 ts=8 sw=4 tw=99 et:
#pragma once

#include <stdarg.h>

#include <mutex>
#include <vector>

#include "tier0/logging.h"

class LogManager
{
  public:
    LogManager();
    void LogVa(LogLevel level, const char* fmt, va_list ap);
    void Log(LogLevel level, const char* fmt, ...);

    static LogManager* get();

    void AddListener(ILoggingListener* listener);
    void RemoveListener(ILoggingListener* listener);

    void PushState();
    void PopState();

  private:
    std::mutex mutex_;
    struct State {
        std::vector<ILoggingListener*> listeners;
    };
    std::vector<State> state_;
};
