// vim: set sts=4 ts=8 sw=4 tw=99 et:
#include "gameevents.h"

#include <assert.h>

#include "tier0/dbg.h"
#include "tier1/interface.h"

static GameEventManager sGameEventManager;

EXPOSE_SINGLE_INTERFACE_GLOBALVAR(GameEventManager, IGameEventManager2,
		                  INTERFACEVERSION_GAMEEVENTSMANAGER2, sGameEventManager);

IGameEvent *GameEventManager::CreateEvent(const char *name, bool bForce, int *pCookie) {
    Error("%s not implemented", __func__);
    return nullptr;
}

bool GameEventManager::FireEvent(IGameEvent *event, bool bDontBroadcast) {
    depth_++;
    for (const auto& p : hooks_) {
        for (const auto& listener : p.second) {
            if (to_remove_.count(listener))
                continue;
            listener->FireGameEvent(event);
        }
    }
    depth_--;

    if (!depth_) {
        for (const auto& entry : to_remove_)
            RemoveListenerImpl(entry);
        to_remove_.clear();
    }
    return true;
}

void GameEventManager::FreeEvent(IGameEvent *event) {
    delete event;
}

IGameEvent *GameEventManager::DuplicateEvent(IGameEvent *event) {
    Error("%s not implemented", __func__);
    return nullptr;
}

bool GameEventManager::AddListener(IGameEventListener2 *listener, const char *name,
                                    bool bServerSide)
{
    hooks_[name].emplace_back(listener);
    return true;
}

void GameEventManager::RemoveListener(IGameEventListener2 *listener) {
    if (depth_)
        to_remove_.emplace(listener);
    else
        RemoveListenerImpl(listener);
}

void GameEventManager::RemoveListenerImpl(IGameEventListener2* listener) {
    assert(!depth_);
    for (auto& p : hooks_)
        p.second.remove(listener);
}

bool GameEventManager::FindListener(IGameEventListener2 *listener, const char *name) {
    auto hi = hooks_.find(name);
    if (hi == hooks_.end())
        return false;
    for (const auto& entry : hi->second) {
        if (entry == listener)
            return true;
    }
    return false;
}
