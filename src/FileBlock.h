#ifndef __PKG_FILE_BLOCK_H__
#define __PKG_FILE_BLOCK_H__

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
    size_t size;
} fileInfo;

class FileBlock
{
private:
    fileInfo flInf;
    unsigned char* _content;
    size_t _size;
public:
    FileBlock(Buffer& buf);
    ~FileBlock();
    bool decode(Buffer& buf);
    int size();
};

}

#endif