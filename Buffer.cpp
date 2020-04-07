
#include "Buffer.h"

using namespace pkg;

Buffer::Buffer(int size = 4)
{
    _data = (char*)malloc(size);
    _size = size;
}

Buffer::~Buffer()
{
    if (_data != nullptr)
    {
        free(_data);
    }
}

char* Buffer::data()
{
    return _data;
}

int Buffer::size()
{
    return _size;
}

bool Buffer::resize(int size)
{

}
