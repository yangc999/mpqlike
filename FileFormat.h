
#include <string>
#include <vector>
#include <hash_map>
#include "Hash.h"

namespace pkg
{
    
typedef struct blockInfo
{
    int blockBegin;
    int blockLength;
} blockInfo;

class FileFormat
{
private:
    std::string _path;
    __gnu_cxx::hash_map<int, int> hashTable;
    std::vector<blockInfo*> blockTable;
public:
    FileFormat(const char* path);
    ~FileFormat();
    bool valid();
    const char* origin();
    bool match(const char* path);
    char* read(const char* path);
    int size(const char* path);
};

}