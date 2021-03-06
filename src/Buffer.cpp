
#include <cstdlib>
#include <cstring>
#include "Buffer.h"

using namespace pkg;

Buffer::Buffer(size_t size)
{
    _data = (unsigned char*)malloc(size);
    if (_data != nullptr)
        _size = size;
}

Buffer::~Buffer()
{
    if (_data != nullptr)
        free(_data);
}

unsigned char* Buffer::data()
{
    return _data;
}

size_t Buffer::size()
{
    return _size;
}

bool Buffer::resign(const unsigned char* src, size_t size)
{
    if (_data != nullptr)
    {
        _data = (unsigned char*)realloc(_data, size);
        if (_data != nullptr)
        {
            _size = size;
            if (src != nullptr)
                memcpy(_data, src, size);
            return true;
        }
    }
    return false;
}
