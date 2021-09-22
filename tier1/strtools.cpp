// vim: set sts=4 ts=8 sw=4 tw=99 et:
#include "strtools.h"

#include <amtl/am-string.h>

void
V_strncpy(char* dest, const char* src, int maxlen)
{
    ke::SafeStrcpy(dest, maxlen, src);
}

void
V_binarytohex(const byte *in, int inputbytes, char *out, int outsize)
{
    std::string str;
    for (int i = 0; i < inputbytes; i++)
        str += ke::StringPrintf("%02x", in[i]);
    ke::SafeStrcpy(out, outsize, str.c_str());
}

void V_strcat(char *dest, const char *src, int cchDest) {
    ke::SafeStrcat(dest, cchDest, src);
}
