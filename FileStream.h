
#include <fstream>
#include <iostream>
#include <string>

namespace pkg
{

class FileStream
{
private:
    const std::string _path;
    std::ifstream _in;
public:
    FileStream(const char* path);
    ~FileStream();
    bool readInt8(char* dst, int begin);
    bool readUInt8(unsigned char* dst, int begin);
    bool readInt16(short* dst, int begin);
    bool readUInt16(unsigned short* dst, int begin);
    bool readInt32(int* dst, int begin);
    bool readUInt32(unsigned int* dst, int begin);
    bool readInt64(long* dst, int begin);
    bool readUInt64(unsigned long* dst, int begin);
    bool readStr(char* dst, int begin, int end);
};

}