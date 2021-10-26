// vim: set sts=4 ts=8 sw=4 tw=99 et:
#pragma once

#include <filesystem>
#include <mutex>
#include <string>
#include <unordered_map>
#include <vector>

#include "filesystem.h"

class FileSystem final : public IFileSystem
{
  public:
    FileHandle_t Open(const char* name, const char* options,
                      const char* path_id = nullptr) override;
    unsigned int Size(FileHandle_t file) override;
    int Read(void* output, int size, FileHandle_t file) override;
    void Close(FileHandle_t file) override;
    bool FileExists(const char *path, const char *path_id = nullptr) override;
    int Write(void const* pInput, int size, FileHandle_t file) override;
    void Seek(FileHandle_t file, int pos, FileSystemSeek_t seekType) override;
    unsigned int Tell(FileHandle_t file) override;
    int FPrintf(FileHandle_t file, const char *pFormat, ...) override;
    void Flush(FileHandle_t file) override;
    bool IsOk(FileHandle_t file) override;
    void RemoveFile(char const* pRelativePath, const char *pathID = nullptr) override;
    bool RenameFile(char const *pOldPath, char const *pNewPath, const char *pathID = nullptr) override;
    bool IsDirectory(const char *pFileName, const char *pathID = nullptr) override;
    void CreateDirHierarchy(const char *path, const char *pathID = nullptr) override;
    const char *FindFirstEx(const char *pWildCard, const char *pPathID, FileFindHandle_t *pHandle) override;
    const char *FindNext(FileFindHandle_t handle) override;
    bool FindIsDirectory(FileFindHandle_t handle) override;
    void FindClose(FileFindHandle_t handle) override;
    char *ReadLine(char *pOutput, int maxChars, FileHandle_t file) override;
    bool EndOfFile(FileHandle_t file) override;
    unsigned int Size(const char* file, const char* pathID = nullptr) override;
    CSysModule *LoadModule(const char *pFileName, const char *pPathID = 0, bool bValidatedDllOnly = true) override;
    void UnloadModule(CSysModule *pModule) override;

    static FileSystem* get();

  private:
    std::mutex mutex_;
};
