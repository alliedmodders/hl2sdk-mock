// vim: set sts=4 ts=8 sw=4 tw=99 et:
#pragma once

template <int NumBits>
class CBitVec
{
  public:
    int FindNextSetBit(int index) { return -1; }
};

typedef CBitVec<255> CPlayerBitVec;
