// vim: set sts=4 ts=8 sw=4 tw=99 et:
#pragma once

class SendTable;

class ServerClass
{
  public:
    const char* GetName() const { return "ServerClass"; }

    SendTable* m_pTable;
    ServerClass* m_pNext;
    int m_ClassID;
};
