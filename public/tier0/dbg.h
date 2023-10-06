// vim: set sts=4 ts=8 sw=4 tw=99 et:
#pragma once

#include <assert.h>

#include "platform.h"

#ifdef NDEBUG
# define Assert(cond)
#else
# define Assert(cond) assert((cond))
#endif

void ConMsg(const char* msg, ...);
void Msg(const char* msg, ...);
void Warning(const char* msg, ...);
void Error(const char* msg, ...);
void DevMsg(const char* msg, ...);
