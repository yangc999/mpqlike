
#include <cstdlib>
#include <cstring>

namespace pkg
{

class Buffer
{
private:
    char* _data;
    int _size;
public:
    Buffer(int size = 4);
    ~Buffer();
    int size();
    char* data();
    bool resize(int size);
};

}