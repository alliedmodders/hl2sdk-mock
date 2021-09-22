// vim: set sts=4 ts=8 sw=4 tw=99 et:
#pragma once

#include <stdint.h>

class bf_write
{
  public:
    bf_write(void* data, size_t buflen) {}
    void WriteOneBit(int i) {}
    void WriteByte(uint8_t b) {}
    void WriteChar(char c) {}
    void WriteShort(int16_t s) {}
    void WriteWord(int32_t i) {}
    void WriteLong(int64_t i) {}
    void WriteFloat(float f) {}
    void WriteString(const char* f) {}
    void WriteBitAngle(float f, int) {}
    void WriteBitCoord(float f) {}
    void WriteBitAngles(const QAngle& v) {}
    void WriteBitVec3Coord(const Vector& v) {}
    void WriteBitVec3Normal(const Vector& v) {}
    void WriteUBitLong(unsigned int data, int numbits, bool bCheckRange=true) {}
    unsigned char* GetBasePointer() { return nullptr; }
    int GetNumBytesWritten() { return 0; }
    int GetNumBitsWritten() { return 0; }
    void Reset() {}
    void WriteBitsFromBuffer(const void*, int) {}
};

class bf_read
{
  public:
    bf_read() {}
    bf_read(const void *pData, int nBytes, int nBits = -1) {}
    void StartReading(const void* data, int bytes, int startBit = 0, int nbits = -1) { }
    int ReadOneBit() { return 0; }
    uint8_t ReadByte() { return 0; }
    char ReadChar() { return 0; }
    int16_t ReadShort() { return 0; }
    int32_t ReadWord() { return 0; }
    int64_t ReadLong() { return 0; }
    float ReadFloat() { return 0; }
    bool ReadString(char* buf, int buflen, bool bline = false, int* outchars = nullptr) { return false; }
    float ReadBitAngle(int) { return 0; }
    float ReadBitCoord() { return 0; }
    void ReadBitAngles(QAngle& v) { }
    void ReadBitVec3Coord(Vector& v) { }
    void ReadBitVec3Normal(Vector& v) { }
    int GetNumBitsLeft() { return 0; }
    bool IsOverflowed() { return false; }
};
