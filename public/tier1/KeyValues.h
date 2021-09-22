// vim: set sts=4 ts=8 sw=4 tw=99 et:
#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "tier0/platform.h"
#include "Color.h"

class CUtlBuffer;
class IBaseFileSystem;

class KeyValues
{
  public:
    explicit KeyValues(const char* name);
    KeyValues(const char* name, const char* firstKey, const char* firstValue);

    virtual ~KeyValues() {}
    virtual void deleteThis() { delete this; }

    bool LoadFromFile(IBaseFileSystem* fs, const char* resname, const char* pathID = nullptr);
    bool LoadFromBuffer(const char* resname, const char* buffer, IBaseFileSystem* fs = nullptr);
    void RecursiveSaveToFile(CUtlBuffer& buf, int indentLevel) {}
    bool SaveToFile(IBaseFileSystem* fs, const char* resourceName, const char* pathID = nullptr) { return false; }

    KeyValues* FindKey(const char* key, bool create = false);
    KeyValues* FindKey(int keySymbol) { return nullptr; }
    const char *GetString(const char *keyName = nullptr, const char *defaultValue = "");
    int GetInt(const char *keyName = nullptr, int defaultValue = 0) {
        return defaultValue;
    }
    float GetFloat(const char *keyName = nullptr, float defaultValue = 0.0f) {
        return defaultValue;
    }
    Color GetColor(const char *keyName = nullptr, const Color &defaultColor = Color(0, 0, 0, 0 )) {
        return defaultColor;
    }
    uint64 GetUint64(const char *keyName = nullptr, uint64 defaultValue = 0) {
        return defaultValue;
    }
    void SetString(const char *keyName, const char *value) {}
    void SetInt(const char *keyName, int value) {}
    void SetUint64(const char *keyName, uint64 value) {}
    void SetFloat(const char *keyName, float value) {}
    void SetColor(const char *keyName, Color value) {}
    const char *GetName() const { return name_.c_str(); }
    void SetName(const char *setName) { name_ = setName; }
    void SetStringValue(const char* value) { value_ = value; }
    void RemoveSubKey(KeyValues *subKey) {}

    void UsesEscapeSequences(bool state) {}

    void CopySubkeys(KeyValues *pParent) const {}
    int GetNameSymbol() const { return -1; }

    KeyValues* GetFirstTrueSubKey() { return nullptr; }
    KeyValues* GetNextTrueSubKey() { return nullptr; }
    KeyValues* GetFirstSubKey() { return nullptr; }
    KeyValues *GetNextKey() { return nullptr; }

    enum types_t
    {
        TYPE_NONE = 0,
        TYPE_STRING,
        TYPE_INT,
        TYPE_FLOAT,
        TYPE_PTR,
        TYPE_WSTRING,
        TYPE_COLOR,
        TYPE_UINT64,
        TYPE_COMPILED_INT_BYTE,
        TYPE_COMPILED_INT_0,
        TYPE_COMPILED_INT_1,
        TYPE_NUMTYPES, 
    };
    types_t GetDataType(const char *keyName = nullptr) { return TYPE_NONE; }

  private:
    std::string name_;
    std::string value_;
    std::unordered_map<std::string, std::unique_ptr<KeyValues>> dict_;
    std::vector<std::unique_ptr<KeyValues>> subkeys_;

    // Helper for the SubKey iterators.
    KeyValues* sub_next_ = nullptr;
};
