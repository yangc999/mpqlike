#ifndef __FILE_STREAM_H__
#define __FILE_STREAM_H__

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
    bool readInt8(char* dst);
    bool readUInt8(unsigned char* dst);
    bool readInt16(short* dst);
    bool readUInt16(unsigned short* dst);
    bool readInt32(int* dst);
    bool readUInt32(unsigned int* dst);
    bool readInt64(long* dst);
    bool readUInt64(unsigned long* dst);
    bool readStr(unsigned char* dst, int length);
    bool offset(int off);
};

}

#endif