// vim: set sts=4 ts=8 sw=4 tw=99 et:
#pragma once

#include "platform.h"

enum class LogLevel {
    Warning,
    Normal,
    Message,
    Error
};

struct LoggingContext_t
{
    LogLevel severity;
};

class ILoggingListener
{
  public:
    virtual void Log(const LoggingContext_t *pContext, const char *pMessage) = 0;
};

DLL_FUNCTION void LoggingSystem_PushLoggingState(bool bThreadLocal = false, bool bClearState = true);
DLL_FUNCTION void LoggingSystem_PopLoggingState(bool bThreadLocal = false);
DLL_FUNCTION void LoggingSystem_RegisterLoggingListener(ILoggingListener *pListener);
