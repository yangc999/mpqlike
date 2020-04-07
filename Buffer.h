#ifndef __BUFFER_H__
#define __BUFFER_H__

#include <cstdlib>
#include <cstring>

namespace pkg
{

class Buffer
{
private:
    unsigned char* _data;
    size_t _size;
public:
    Buffer(size_t size = 4);
    ~Buffer();
    size_t size();
    char* data();
    bool resign(const char* src, size_t size);
};

}

#endif