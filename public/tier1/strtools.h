// vim: set sts=4 ts=8 sw=4 tw=99 et:
#pragma once

#include <string.h>

#include "tier0/platform.h"

#define Q_strncpy V_strncpy
#define Q_binarytohex V_binarytohex
#define Q_strcmp strcmp

void V_strncpy(char* dest, const char* src, int maxlen);
void V_binarytohex(const byte *in, int inputbytes, char *out, int outsize);
void V_strcat(char *dest, const char *src, int cchDest);
