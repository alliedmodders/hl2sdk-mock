// vim: set sts=4 ts=8 sw=4 tw=99 et:
#pragma once

#include <amtl/am-string.h>

#if 0
template <typename T> static inline T*
InvokeCreateInterface(CreateInterfaceFn fn, const char* name, int start = 0, int direction = 0) {
    int iter = start;
    while (true) {
        std::string fq = name;
        if (start)
            fq = ke::StringPrintf("%s%03d", name, iter);

        int rv;
        if (auto iface = fn(fq.c_str(), &rv))
            return reinterpret_cast<T*>(iface);
        if (!direction || iter < 1)
            return nullptr;
    }
}
#endif
