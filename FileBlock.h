#ifndef __FILE_BLOCK_H__
#define __FILE_BLOCK_H__

#include <cstring>
#include "Buffer.h"

namespace pkg
{

enum EncodeType
{
    FLAT = 0,
    ZIP = 1
};

typedef struct fileInfo
{
    EncodeType encTp;
    int size;
} fileInfo;

class FileBlock
{
private:
    fileInfo flInf;
    unsigned char* content;
public:
    FileBlock(Buffer& buf);
    ~FileBlock();
    bool decode(Buffer& buf);
    int size();
};

}

#endif