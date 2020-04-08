#ifndef __PKG_FILE_SYSTEM_H__
#define __PKG_FILE_SYSTEM_H__

#include <vector>
#include <unordered_map>
#include "FileFormat.h"
#include "Buffer.h"

namespace pkg
{

class FileSystem
{
private:
    std::unordered_map<std::string, FileFormat*> pkgMap;
    FileSystem();
public:
    ~FileSystem();
    static FileSystem* getInstance();
    bool loadPackage(const char* path);
    bool unloadPackage(const char* path);
    bool fileExist(const char* path);
    bool fileContent(const char* path, Buffer& buf);
    int fileSize(const char* path);
};

}

#endif