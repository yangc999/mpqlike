
#include <cstdlib>
#include <cstring>
#include "FileBlock.h"
#include "zlib.h"

using namespace pkg;

FileBlock::FileBlock(Buffer& buf)
{
    memcpy(&flInf.encTp, buf.data(), sizeof(int));
    memcpy(&flInf.size, buf.data()+sizeof(int), sizeof(int));
    _size = buf.size()-2*sizeof(int);
    _content = (unsigned char*)malloc(_size);
    if (_content != nullptr)
        memcpy(_content, buf.data()+2*sizeof(int), _size);
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
