// vim: set sts=4 ts=8 sw=4 tw=99 et:
#pragma once

#include <unordered_map>
#include <utility>

// :TODO:
template <typename V, typename I = int>
class CUtlDict
{
  public:
    char* GetElementName(I i);
    char const* GetElementName(I i) const;
    I First() const;
    I Next(I i) const;
    I InvalidIndex() const { return -1; }

  private:
    //std::unordered_map<std::string, V> impl_;
};
