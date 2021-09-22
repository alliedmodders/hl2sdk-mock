// vim: set sts=4 ts=8 sw=4 tw=99 et:
#pragma once

#include "tier0/platform.h"

#define IFACE_OK 0
#define IFACE_FAILED 1

typedef void* (*InstantiateInterfaceFn)();
typedef void* (*CreateInterfaceFn)(const char* name, int* ret);

class InterfaceReg
{
  public:
    InterfaceReg(InstantiateInterfaceFn fn, const char* name);

  public:
    InstantiateInterfaceFn m_CreateFn;
    const char* m_pName;
    InterfaceReg* m_pNext;
};

DLL_EXPORT void* CreateInterface(const char* name, int* ret);

#define EXPOSE_SINGLE_INTERFACE_GLOBALVAR(className, ifaceName, versionName, globalVar) \
    static void* __Create##className##ifaceName##_interface() { \
        return static_cast<ifaceName*>(&globalVar); \
    } \
    static InterfaceReg __g_Create##className##ifaceName##_reg(__Create##className##ifaceName##_interface, versionName);

class CSysModule;

CSysModule* OpenCSysModule(const char* path);
void CloseCSysModule(CSysModule* mod);
CreateInterfaceFn Sys_GetFactory(CSysModule *pModule);
