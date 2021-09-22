// vim: set sts=4 ts=8 sw=4 tw=99 et:
#pragma once

static constexpr int INVALID_STRING_TABLE = -1;
static constexpr unsigned short INVALID_STRING_INDEX = -1;

typedef int TABLEID;

#define MIN(a, b) ((a) < (b) ? (a) : (b))

static constexpr char INTERFACENAME_NETWORKSTRINGTABLESERVER[] = "VEngineServerStringTable001";

class INetworkStringTable
{
  public:
    virtual TABLEID GetTableId() const = 0;
    virtual int GetNumStrings() const = 0;
    virtual int GetMaxStrings() const = 0;
    virtual const char* GetTableName() const = 0;
    virtual int FindStringIndex(const char* str) const = 0;
    virtual const char* GetString(int i) const = 0;
    virtual const void* GetStringUserData(int i, int* len) const = 0;
    virtual void SetStringUserData(int  i, int len, const void* userdata) = 0;
    virtual int AddString(bool server, const char* val, int length = -1,
                          const void* userdata = nullptr) = 0;
};

class INetworkStringTableContainer
{
  public:
    virtual INetworkStringTable* FindTable(const char* name) const = 0;
    virtual INetworkStringTable* GetTable(int i) const = 0;
    virtual int GetNumTables() const = 0;
};
