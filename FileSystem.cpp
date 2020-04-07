
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
    for (auto it : pkgMap)
    {
        if (it.second->match(path))
            return true;
    }
    FileFormat *format = new FileFormat(path);
    if (format->valid())
    {
        pkgMap.insert(std::pair<const char*, FileFormat*>(format->origin(), format));
        return true;
    }
    return false;
}

bool FileSystem::unloadPackage(const char* path)
{
    for (auto it : pkgMap)
    {
        if (it.second->match(path))
            return true;
    }
}

bool FileSystem::fileExist(const char* path)
{
    for (auto it : pkgMap)
    {
        if (it.second->match(path))
            return true;
    }
    return false;
}

char* FileSystem::fileContent(const char* path)
{
    for (auto it : pkgMap)
    {
        if (it.second->match(path))
            return it.second->read(path);
    }
    return nullptr;
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