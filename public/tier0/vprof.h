// vim: set sts=4 ts=8 sw=4 tw=99 et:
#pragma once

#include "platform.h"

#define VPROF_BUDGETGROUP_OTHER_UNACCOUNTED "Unaccounted"

enum VProfReportType_t {
    VPRT_FULL
};

class VProfiler
{
  public:
    VProfiler();
    void Pause() {}
    void OutputReport(VProfReportType_t) {}
    void Resume() {}
    bool IsEnabled() { return false; }
    void EnterScope(const char*, int, const char*, bool, int) {}
    void ExitScope() {}

  private:
    int state_ = 0;
};

#ifdef VPROF_IMPLEMENTATION
DLL_EXPORT VProfiler g_VProfCurrentProfile;
#else
DLL_IMPORT VProfiler g_VProfCurrentProfile;
#endif
