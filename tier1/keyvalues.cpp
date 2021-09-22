// vim: set sts=4 ts=8 sw=4 tw=99 et:
#include "KeyValues.h"

#include <ctype.h>
#include <stdio.h>

#include <memory>

#include "filesystem.h"
#include "tier0/dbg.h"

KeyValues::KeyValues(const char* name)
  : name_(name)
{
}

KeyValues::KeyValues(const char* name, const char* firstKey, const char* firstValue)
  : name_(name)
{
    auto kv = FindKey(firstKey);
    if (!firstValue)
        firstValue = "";
    kv->SetStringValue(firstValue);
}

static bool ReadFromFile(const char* file, std::string* str) {
    std::unique_ptr<FILE, decltype(&::fclose)> fp(fopen(file, "rb"), &::fclose);
    if (!fp)
        return false;

    fseek(fp.get(), 0, SEEK_END);
    auto size = ftell(fp.get());
    fseek(fp.get(), 0, SEEK_SET);

    str->resize(size, '\0');
    fread(str->data(), 1, size, fp.get());
    return true;
}

static bool ReadFromFile(IBaseFileSystem* fs, const char* path, std::string* str) {
    auto h = fs->Open(path, "rb");
    if (!h)
        return false;

    auto size = fs->Size(h);
    str->resize(size, '\0');
    fs->Read(str->data(), size, h);
    return true;
}

static inline const char* SkipSpaces(const char* ptr) {
    while (*ptr > 0 && isspace(*ptr))
        ptr++;
    return ptr;
}

bool
KeyValues::LoadFromBuffer(const char* resname, const char* buffer, IBaseFileSystem* fs)
{
    std::vector<KeyValues*> work;
    KeyValues* kv = this;

    const char* ptr = buffer;
    while (*ptr) {
        ptr = SkipSpaces(ptr);

        // Skip comments.
        if (*ptr == '/' && (*(ptr + 1) == '/' || (*ptr + 1) == '*')) {
            while (*ptr && *ptr != '\n')
                ptr++;
            continue;
        }

        // EOF after skipping?
        if (!*ptr)
            break;

        if (*ptr == '}') {
            ptr++;
            if (work.empty()) {
                Error("Extra close brace in VDF: %s\n", resname);
                break;
            }
            kv = work.back();
            work.pop_back();
            continue;
        }

        const char* key_start = ptr++;
        while (*ptr) {
            char c = *ptr;
            if (c == '"') {
                ptr++;
                break;
            }
            if (c > 0 && isspace(c) && *key_start != '"')
                break;
            ptr++;
        }

        std::string key_name;
        if (*key_start == '"')
            key_name = std::string(key_start + 1, ptr - key_start - 2);
        else
            key_name = std::string(key_start, ptr - key_start);

        ptr = SkipSpaces(ptr);
        if (!*ptr) {
            // Broken file?
            Error("Maybe broken VDF file: %s\n", resname);
            break;
        }

        if (*ptr == '{') {
            ptr++;
            work.emplace_back(kv);
            auto sub = std::make_unique<KeyValues>(key_name.c_str());
            if (!kv->subkeys_.empty())
                kv->subkeys_.back()->sub_next_ = sub.get();
            kv->subkeys_.emplace_back(std::move(sub));
            kv = kv->subkeys_.back().get();
            continue;
        }

        ptr = SkipSpaces(ptr);

        const char* val_start = ptr++;
        while (*ptr) {
            char c = *ptr;
            if (c == '"') {
                ptr++;
                break;
            }
            if (c > 0 && isspace(c) && *key_start != '"')
                break;
            ptr++;
        }

        std::string val_str;
        if (*val_start == '"')
            val_str = std::string(val_start + 1, ptr - val_start - 2);
        else
            val_str = std::string(val_start, ptr - val_start);

        auto ptr = dict_.find(key_name);
        if (ptr == dict_.end()) {
            auto p = dict_.emplace(key_name, std::make_unique<KeyValues>(key_name.c_str()));
            ptr = p.first;
        }
        ptr->second->SetStringValue(val_str.c_str());
    }

    if (!work.empty())
        Error("Missing close brace in VDF file: %s\n", resname);

    return true;
}

bool
KeyValues::LoadFromFile(IBaseFileSystem* fs, const char* resname, const char* pathID)
{
    std::string buffer;
    if (fs) {
        if (!ReadFromFile(fs, resname, &buffer))
            return false;
    } else if (!ReadFromFile(resname, &buffer)) {
        return false;
    }
    return LoadFromBuffer(resname, buffer.c_str(), fs);
}

const char*
KeyValues::GetString(const char* key, const char* def)
{
    auto kv = FindKey(key, false);
    if (!kv)
        return def;
    return kv->value_.c_str();
}

KeyValues*
KeyValues::FindKey(const char* key, bool create)
{
    if (!key || !key[0])
        return this;
    auto iter = dict_.find(key);
    if (iter == dict_.end()) {
        if (!create)
            return nullptr;
        auto p = dict_.emplace(key, std::make_unique<KeyValues>(key));
        iter = p.first;
    }
    return iter->second.get();
}
