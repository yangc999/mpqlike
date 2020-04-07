#ifndef __FILE_SYSTEM_H__
#define __FILE_SYSTEM_H__

#include <vector>
#include <hash_map>
#include "FileFormat.h"
#include "Buffer.h"

namespace pkg
{

class FileSystem
{
private:
    __gnu_cxx::hash_map<const char*, FileFormat*> pkgMap;
public:
    FileSystem();
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