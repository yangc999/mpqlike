#ifndef __PKG_FIlE_FORMAT_H__
#define __PKG_FIlE_FORMAT_H__

#include <string>
#include <vector>
#include <map>
#include <exception>
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
    std::map<unsigned int, size_t> hashTable;
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