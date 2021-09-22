// vim: set sts=4 ts=8 sw=4 tw=99 et:
#pragma once

#define VPROF_BUDGETGROUP_OTHER_UNACCOUNTED "Unaccounted"

enum VProfReportType_t {
    VPRT_FULL
};

class VProfiler
{
  public:
    void Pause() {}
    void OutputReport(VProfReportType_t) {}
    void Resume() {}
    bool IsEnabled() { return false; }
    void EnterScope(const char*, int, const char*, bool, int) {}
    void ExitScope() {}
};

extern VProfiler g_VProfCurrentProfile;
