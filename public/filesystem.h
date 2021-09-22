// vim: set sts=4 ts=8 sw=4 tw=99 et:
#pragma once

#include <stdio.h>

static constexpr char BASEFILESYSTEM_INTERFACE_VERSION[] = "VBaseFileSystem011";
static constexpr char FILESYSTEM_INTERFACE_VERSION[] = "VFileSystem017";

typedef void* FileHandle_t;
typedef int FileFindHandle_t;

enum FileSystemSeek_t
{
    FILESYSTEM_SEEK_HEAD = SEEK_SET,
    FILESYSTEM_SEEK_CURRENT = SEEK_CUR,
    FILESYSTEM_SEEK_TAIL = SEEK_END
};

class IBaseFileSystem
{
  public:
    virtual FileHandle_t Open(const char* name, const char* options,
                              const char* path_id = nullptr) = 0;
    virtual unsigned int Size(FileHandle_t file) = 0;
    virtual unsigned int Size(const char* file, const char* pathID = nullptr) = 0;
    virtual int Read(void* output, int size, FileHandle_t file) = 0;
    virtual void Close(FileHandle_t file) = 0;
    virtual bool FileExists(const char *path, const char *path_id = nullptr) = 0;
    virtual int Write(void const* pInput, int size, FileHandle_t file) = 0;
    virtual void Seek(FileHandle_t file, int pos, FileSystemSeek_t seekType) = 0;
    virtual unsigned int Tell(FileHandle_t file) = 0;
    virtual int FPrintf(FileHandle_t file, const char *pFormat, ...) = 0;
    virtual void Flush(FileHandle_t file) = 0;
    virtual bool IsOk(FileHandle_t file) = 0;
    virtual void RemoveFile(char const* pRelativePath, const char *pathID = nullptr) = 0;
    virtual bool RenameFile(char const *pOldPath, char const *pNewPath, const char *pathID = nullptr) = 0;
    virtual bool IsDirectory(const char *pFileName, const char *pathID = nullptr) = 0;
    virtual void CreateDirHierarchy(const char *path, const char *pathID = nullptr) = 0;
    virtual const char *FindFirstEx(const char *pWildCard, const char *pPathID, FileFindHandle_t *pHandle) = 0;
    virtual const char *FindNext(FileFindHandle_t handle) = 0;
    virtual bool FindIsDirectory(FileFindHandle_t handle) = 0;
    virtual void FindClose(FileFindHandle_t handle) = 0;
    virtual char *ReadLine(char *pOutput, int maxChars, FileHandle_t file) = 0;
    virtual bool EndOfFile(FileHandle_t file) = 0;
};

class CSysModule;

class IFileSystem : public IBaseFileSystem
{
  public:
    virtual CSysModule *LoadModule(const char *pFileName, const char *pPathID = 0, bool bValidatedDllOnly = true) = 0;
    virtual void UnloadModule(CSysModule *pModule) = 0;
};
