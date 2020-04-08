
#include <cstdlib>
#include <cstring>
#include "FileBlock.h"
#include "zlib.h"

using namespace pkg;

FileBlock::FileBlock(Buffer& buf)
{
    unsigned char tp;
    unsigned int size;
    memcpy(&tp, buf.data(), sizeof(char));
    memcpy(&size, buf.data()+sizeof(char), sizeof(int));
    flInf.encTp = (EncodeType)tp;
    flInf.size = size;
    _size = buf.size()-sizeof(char)-sizeof(int);
    _content = (unsigned char*)malloc(_size);
    if (_content != nullptr)
        memcpy(_content, buf.data()+sizeof(char)+sizeof(int), _size);
}

FileBlock::~FileBlock()
{
    if (_content != nullptr)
        free(_content);
}

bool FileBlock::decode(Buffer& buf)
{
    switch (flInf.encTp)
    {
    case FLAT:
        return buf.resign(_content, flInf.size);
        break;

    case ZIP:
        Bytef* buff = (Bytef*)malloc(flInf.size);
        if (buff != nullptr)
        {
            size_t bufLen;
            bool ok = false;
            int err = ::uncompress(buff, &bufLen, _content, _size);
            if (err == Z_OK)
                ok = buf.resign(buff, bufLen);
            free(buff);
            return ok;
        }
        return false;
        break;

    default:
        break;
    }
    return false;
}

int FileBlock::size()
{
    return flInf.size;
}
