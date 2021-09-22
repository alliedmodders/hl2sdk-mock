// vim: set sts=4 ts=8 sw=4 tw=99 et:
#include "tier1/interface.h"

#include <amtl/os/am-shared-library.h>

#include "tier0/platform.h"

static InterfaceReg* sInterfaceList;

InterfaceReg::InterfaceReg(InstantiateInterfaceFn fn, const char* name)
  : m_CreateFn(fn),
    m_pName(name),
    m_pNext(sInterfaceList)
{
    sInterfaceList = this;
}

class CSysModule : public ke::SharedLib
{
  public:
    CSysModule(const char* path) : ke::SharedLib(path)
    {}
};

CSysModule* OpenCSysModule(const char* path) {
    auto lib = new CSysModule(path);
    if (!lib->valid()) {
        delete lib;
        return nullptr;
    }
    return lib;
}

void CloseCSysModule(CSysModule* mod) {
    delete mod;
}

CreateInterfaceFn Sys_GetFactory(CSysModule *pModule) {
    return pModule->get<CreateInterfaceFn>("CreateInterface");
}

DLL_EXPORT void* CreateInterface(const char* name, int* rc) {
    for (auto iter = sInterfaceList; iter; iter = iter->m_pNext) {
        if (strcmp(iter->m_pName, name) == 0) {
            if (rc)
                *rc = IFACE_OK;
            return iter->m_CreateFn();
        }
    }
    if (rc)
        *rc = IFACE_FAILED;
    return nullptr;
}
