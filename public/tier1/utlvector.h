// vim: set sts=4 ts=8 sw=4 tw=99 et:
#pragma once

#include <vector>

template <typename T>
class CUtlVector
{
  public:
    int AddToTail(const T& src) {
        impl_.emplace_back(src);
        return (int)impl_.size() - 1;
    }

    T& operator [](int i) { return impl_[i]; }
    int Count() const { return (int)impl_.size(); }

  private:
    std::vector<T> impl_;
};
