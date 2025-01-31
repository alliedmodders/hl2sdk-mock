// vim: set sts=4 ts=8 sw=4 tw=99 et:
#include "fs.h"

#include <filesystem>
#include <cstdarg>

#include "tier0/dbg.h"
#include "tier1/interface.h"

FileSystem sFileSystem;

EXPOSE_SINGLE_INTERFACE_GLOBALVAR(FileSystem, IBaseFileSystem, BASEFILESYSTEM_INTERFACE_VERSION,
                                  sFileSystem);
EXPOSE_SINGLE_INTERFACE_GLOBALVAR(FileSystem, IFileSystem, FILESYSTEM_INTERFACE_VERSION,
                                  sFileSystem);

FileSystem* FileSystem::get() {
    return &sFileSystem;
}

FileHandle_t
FileSystem::Open(const char* name, const char* options, const char* path_id)
{
    return fopen(name, options);
}

bool
FileSystem::FileExists(const char *path, const char *path_id)
{
    if (FILE* fp = fopen(path, "rb")) {
        fclose(fp);
        return true;
    }
    return false;
}

unsigned int
FileSystem::Size(FileHandle_t hfile)
{
    auto file = reinterpret_cast<FILE*>(hfile);
    auto pos = ftell(file);
    if (pos < 0) {
        Error("ftell failed\n");
        return 0;
    }

    if (fseek(file, 0, SEEK_END)) {
        Error("fseek SEEK_END failed\n");
        return 0;
    }

    auto size = ftell(file);
    if (fseek(file, pos, SEEK_SET)) {
        Error("fseek SEEK_SET failed\n");
        return 0;
    }
    return size;
}

int
FileSystem::Read(void* output, int size, FileHandle_t hfile)
{
    auto file = reinterpret_cast<FILE*>(hfile);
    return (int)fread(output, 1, size, file);
}

void
FileSystem::Close(FileHandle_t hfile)
{
    auto file = reinterpret_cast<FILE*>(hfile);
    fclose(file);
}

int FileSystem::Write(void const* pInput, int size, FileHandle_t file) {
    auto fp = reinterpret_cast<FILE*>(file);
    return fwrite(pInput, 1, size, fp);
}

void FileSystem::Seek(FileHandle_t file, int pos, FileSystemSeek_t seekType) {
    auto fp = reinterpret_cast<FILE*>(file);
    fseek(fp, pos, (int)seekType);
}

unsigned int FileSystem::Tell(FileHandle_t file) {
    auto fp = reinterpret_cast<FILE*>(file);
    return ftell(fp);
}

int FileSystem::FPrintf(FileHandle_t file, const char *pFormat, ...) {
    auto fp = reinterpret_cast<FILE*>(file);

    va_list ap;
    va_start(ap, pFormat);
    auto n =vfprintf(fp, pFormat, ap);
    va_end(ap);
    return n;
}

void FileSystem::Flush(FileHandle_t file) {
    auto fp = reinterpret_cast<FILE*>(file);
    fflush(fp);
}

bool FileSystem::IsOk(FileHandle_t file) {
    auto fp = reinterpret_cast<FILE*>(file);
    return ferror(fp) != 0;
}

void FileSystem::RemoveFile(char const* pRelativePath, const char *pathID) {
    std::error_code ec;
    std::filesystem::remove(pRelativePath);
}

bool FileSystem::RenameFile(char const *pOldPath, char const *pNewPath, const char *pathID) {
    std::error_code ec;
    std::filesystem::rename(pOldPath, pNewPath);
    return !!ec;
}

bool FileSystem::IsDirectory(const char *pFileName, const char *pathID) {
    std::error_code ec;
    return std::filesystem::is_directory(pFileName, ec);
}

void FileSystem::CreateDirHierarchy(const char *path, const char *pathID) {
    std::error_code ec;
    std::filesystem::create_directories(path, ec);
}

const char* FileSystem::FindFirstEx(const char *pWildCard, const char *pPathID,
                                    FileFindHandle_t *pHandle)
{
    *pHandle = -1;
    return nullptr;
}

const char* FileSystem::FindNext(FileFindHandle_t handle) {
    return nullptr;
}

bool FileSystem::FindIsDirectory(FileFindHandle_t handle) {
    return false;
}

void FileSystem::FindClose(FileFindHandle_t handle) {
}

char *FileSystem::ReadLine(char *pOutput, int maxChars, FileHandle_t file) {
    auto fp = reinterpret_cast<FILE*>(file);
    return fgets(pOutput, maxChars, fp);
}

bool FileSystem::EndOfFile(FileHandle_t file) {
    auto fp = reinterpret_cast<FILE*>(file);
    return feof(fp);
}

unsigned int FileSystem::Size(const char* file, const char* pathID) {
    auto h = Open(file, "rb", pathID);
    if (!h)
        return 0;
    auto s = Size(h);
    Close(h);
    return s;
}

CSysModule *FileSystem::LoadModule(const char *pFileName, const char *pPathID,
                                   bool bValidatedDllOnly)
{
    return OpenCSysModule(pFileName);
}

void FileSystem::UnloadModule(CSysModule *pModule) {
    CloseCSysModule(pModule);
}

int FileSystem::GetSearchPath(const char* pathID, bool bGetPackFiles, char* pPath, int nMaxLen) {
    return 0;
}
