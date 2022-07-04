// vim: set sts=4 ts=8 sw=4 tw=99 et:
#pragma once

#include "basehandle.h"

template <typename T>
class CHandle : public CBaseHandle
{
  public:
    CHandle();
    CHandle(T *val);
    T* Get() const;
    void Set(const T* val);
};

template<class T>
CHandle<T>::CHandle()
{
}

template<class T>
CHandle<T>::CHandle(T *val)
{
	Term();
	Set(val);
}

template<typename T>
inline T* CHandle<T>::Get() const
{
    return (T*)CBaseHandle::Get();
}

template<class T>
void CHandle<T>::Set(const T* val)
{
    CBaseHandle::Set(reinterpret_cast<const IHandleEntity*>(val));
}
