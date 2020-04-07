#ifndef __FIlE_FORMAT_H__
#define __FIlE_FORMAT_H__

#include <string>
#include <vector>
#include <unordered_map>
#include <exception>
#include "Hash.h"
#include "Buffer.h"

namespace pkg
{

typedef struct blockInfo
{
    unsigned int blockBegin;
    unsigned int blockLength;
} blockInfo;

class FileFormat
{
private:
    std::string _path;
    std::unordered_map<unsigned int, unsigned int> hashTable;
    std::vector<blockInfo*> blockTable;
public:
    FileFormat(const char* path);
    ~FileFormat();
    bool valid();
    const char* origin();
    bool match(const char* path);
    bool read(const char* path, Buffer& buf);
    int size(const char* path);
};

}

#endif