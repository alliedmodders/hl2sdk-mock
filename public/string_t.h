// vim: set sts=4 ts=8 sw=4 tw=99 et:
#pragma once

class string_t
{
  public:
    const char* ToCStr() const { return value_; }

    bool operator ==(const string_t& other) const {
        return value_ == other.value_;
    }

  protected:
    const char* value_;
};

class castable_string_t : public string_t
{
  public:
    castable_string_t() { value_ = nullptr; }
    castable_string_t(const char* from) { value_ = from; }
};

#define MAKE_STRING(str) castable_string_t((str))
#define STRING(str) ((str).ToCStr())
#define NULL_STRING string_t()
