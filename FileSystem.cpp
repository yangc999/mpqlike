
#include "FileSystem.h"

using namespace pkg;

static FileSystem* s_fileSystem = nullptr;

FileSystem::FileSystem()
{

}

FileSystem::~FileSystem()
{

}

FileSystem* FileSystem::getInstance()
{
    if (s_fileSystem == nullptr)
    {
        s_fileSystem = new FileSystem();
    }
    return s_fileSystem;
}

bool FileSystem::loadPackage(const char* path)
{
    for (auto it = pkgMap.begin(); it != pkgMap.end(); it++)
    {
        if (it->second->match(path))
            return true;
    }
    FileFormat* format = new (std::nothrow) FileFormat(path);
    if (format != nullptr)
    {
        pkgMap.insert(std::pair<const char*, FileFormat*>(format->origin(), format));
        return true;
    }
    return false;
}

bool FileSystem::unloadPackage(const char* path)
{
    for (auto it = pkgMap.begin(); it != pkgMap.end(); it++)
    {
        if (it->second->match(path))
        {
            delete it->second;
            pkgMap.erase(it);
            return true;
        }
    }
    return false;
}

bool FileSystem::fileExist(const char* path)
{
    for (auto it = pkgMap.begin(); it != pkgMap.end(); it++)
    {
        if (it->second->match(path))
            return true;
    }
    return false;
}

bool FileSystem::fileContent(const char* path, Buffer& buf)
{
    for (auto it = pkgMap.begin(); it != pkgMap.end(); it++)
    {
        if (it->second->match(path))
            return it->second->read(path, buf);
    }
    return false;
}

int FileSystem::fileSize(const char* path)
{
    for (auto it : pkgMap)
    {
        if (it.second->match(path))
            return it.second->size(path);
    }
    return 0;
}