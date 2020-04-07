
#include "FileFormat.h"
#include <vector>
#include <hash_map>

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
    char* fileContent(const char* path);
    int fileSize(const char* path);
};

}