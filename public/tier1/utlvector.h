// vim: set sts=4 ts=8 sw=4 tw=99 et:
#pragma once

#include <algorithm>
#include <vector>

template <typename T>
class CUtlVector
{
  public:
    int AddToTail(const T& src) {
        impl_.emplace_back(src);
        return (int)impl_.size() - 1;
    }
    bool FindAndRemove(const T& src) {
      auto pos = std::find(impl_.begin(), impl_.end(), src);
      if (pos == impl_.end())
        return false;
      impl_.erase(pos);
      return true;
    }

    T& operator [](int i) { return impl_[i]; }
    int Count() const { return (int)impl_.size(); }

  private:
    std::vector<T> impl_;
};
