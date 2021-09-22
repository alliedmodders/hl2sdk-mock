// vim: set sts=4 ts=8 sw=4 tw=99 et:
#pragma once

#include <list>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include "igameevents.h"

class GameEventManager : public IGameEventManager2
{
  public:
    IGameEvent *CreateEvent(const char *name, bool bForce = false, int *pCookie = nullptr) override;
    bool FireEvent(IGameEvent *event, bool bDontBroadcast = false) override;
    void FreeEvent(IGameEvent *event) override;
    IGameEvent *DuplicateEvent(IGameEvent *event) override;
    bool AddListener(IGameEventListener2 *listener, const char *name, bool bServerSide) override;
    void RemoveListener(IGameEventListener2 *listener) override;
    bool FindListener(IGameEventListener2 *listener, const char *name) override;

  private:
    void RemoveListenerImpl(IGameEventListener2* listener);

  private:
    size_t depth_ = 0;
    std::unordered_map<std::string, std::list<IGameEventListener2*>> hooks_;
    std::unordered_set<IGameEventListener2*> to_remove_;
};
