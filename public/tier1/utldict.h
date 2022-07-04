// vim: set sts=4 ts=8 sw=4 tw=99 et:
#pragma once

#include <map>
#include <utility>

// :TODO:
template <class V, class I = int>
class CUtlDict
{
  public:
    char* GetElementName(I i);
    char const* GetElementName(I i) const;
    I First() const;
    I Next(I i) const;
    I InvalidIndex() const { return -1; }

  private:
    std::map<std::string, V> impl_;
};

template <class V, class I>
char* CUtlDict<V, I>::GetElementName(I i) {
  I cnt = 0;
  for (auto it = impl_.begin(); it != impl_.end(); ++it, ++cnt) {
    if (cnt == i)
      return const_cast<char*>(it->first.c_str());
  }
  return nullptr;
}

template <class V, class I>
char const* CUtlDict<V, I>::GetElementName(I i) const {
  I cnt = 0;
  for (auto it = impl_.cbegin(); it != impl_.cend(); ++it, ++cnt) {
    if (cnt == i)
      return it->first.c_str();
  }
  return nullptr;
}

template <class T, class I>
I CUtlDict<T, I>::First() const {
  if (impl_.empty())
    return InvalidIndex();
  return 0;
}

template <class T, class I>
I CUtlDict<T, I>::Next(I i) const {
  if (i < 0 || i >= impl_.size())
    return InvalidIndex();
  return i + 1;
}
