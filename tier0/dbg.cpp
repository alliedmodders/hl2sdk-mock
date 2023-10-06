// vim: set sts=4 ts=8 sw=4 tw=99 et:
#include "tier0/dbg.h"

#include <stdarg.h>

#include "logmanager.h"

void ConMsg(const char* msg, ...)
{
    va_list ap;
    va_start(ap, msg);
    LogManager::get()->LogVa(LogLevel::Message, msg, ap);
    va_end(ap);
}

void Msg(const char* msg, ...)
{
    va_list ap;
    va_start(ap, msg);
    LogManager::get()->LogVa(LogLevel::Message, msg, ap);
    va_end(ap);
}

void Warning(const char* msg, ...)
{
    va_list ap;
    va_start(ap, msg);
    LogManager::get()->LogVa(LogLevel::Warning, msg, ap);
    va_end(ap);
}

void Error(const char* msg, ...)
{
    va_list ap;
    va_start(ap, msg);
    LogManager::get()->LogVa(LogLevel::Error, msg, ap);
    va_end(ap);
}

void DevMsg(const char* msg, ...)
{
    va_list ap;
    va_start(ap, msg);
    LogManager::get()->LogVa(LogLevel::Message, msg, ap);
    va_end(ap);
}
