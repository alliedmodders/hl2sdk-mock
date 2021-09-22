// vim: set sts=4 ts=8 sw=4 tw=99 et:
#pragma once

static constexpr int FLOW_OUTGOING = 0;
static constexpr int FLOW_INCOMING = 1;
static constexpr int MAX_FLOWS = 2;

class INetChannelInfo
{
  public:
    virtual float GetTimeConnected() const = 0;
    virtual int GetDataRate() const = 0;
    virtual bool IsTimingOut() const = 0;
    virtual float GetLatency(int flow) const = 0;
    virtual float GetAvgLatency(int flow) const = 0;
    virtual float GetAvgLoss(int flow) const = 0;
    virtual float GetAvgPackets(int flow) const = 0;
    virtual float GetAvgData(int flow) const = 0;
    virtual float GetAvgChoke(int flow) const = 0;
};
