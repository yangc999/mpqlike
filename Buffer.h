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
    unsigned char* data();
    bool resign(const unsigned char* src, size_t size);
};

}

#endif