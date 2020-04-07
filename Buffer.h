#ifndef __PKG_BUFFER_H__
#define __PKG_BUFFER_H__

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