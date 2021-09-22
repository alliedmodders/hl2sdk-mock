// vim: set sts=4 ts=8 sw=4 tw=99 et:
#pragma once

class CUtlBuffer
{
  public:
    int TellPut() const { return 0; }
    int TellMaxPut() const { return 0; }
    void Purge() {}
    void GetString(char* pString, int nMaxChars = 0) {
        if (nMaxChars)
            *pString = '\0';
    }
};
