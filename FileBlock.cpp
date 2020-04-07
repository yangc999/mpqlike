
#include "FileBlock.h"

using namespace pkg;

FileBlock::FileBlock(Buffer& buf)
{
    memcpy(&flInf.encTp, buf.data(), sizeof(int));
    memcpy(&flInf.size, buf.data()+sizeof(int), sizeof(int));
    content = (unsigned char*)malloc(flInf.size);
    memcpy(content, buf.data()+2*sizeof(int), buf.size()-sizeof(int)*2);
}

FileBlock::~FileBlock()
{
    if (content != nullptr)
    {
        free(content);
    }
}

bool FileBlock::decode(Buffer& buf)
{
    return true;
}

int FileBlock::size()
{
    return flInf.size;
}
