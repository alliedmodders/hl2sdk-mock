// vim: set sts=4 ts=8 sw=4 tw=99 et:
#pragma once

#include <stdlib.h>

#include "platform.h"

DLL_EXPORT void* MemAllocScratch(int size);
DLL_EXPORT void MemFreeScratch();
