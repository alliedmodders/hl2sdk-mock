// vim: set sts=4 ts=8 sw=4 tw=99 et:
#pragma once

#include <assert.h>

#include "platform.h"

#ifdef NDEBUG
# define Assert(cond)
#else
# define Assert(cond) assert((cond))
#endif

DLL_EXPORT void ConMsg(const char* msg, ...);
DLL_EXPORT void Msg(const char* msg, ...);
DLL_EXPORT void Warning(const char* msg, ...);
DLL_EXPORT void Error(const char* msg, ...);
DLL_EXPORT void DevMsg(const char* msg, ...);
