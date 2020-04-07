
#include "FileStream.h"

using namespace pkg;

FileStream::FileStream(const char* path):_path(std::string(path))
{
    _in.open(path, std::ios::in | std::ios::binary);
}

FileStream::~FileStream()
{
    _in.close();
}

bool FileStream::readInt8(char* dst, int begin)
{
    _in.read(dst, sizeof(char));
}

bool FileStream::readUInt8(unsigned char* dst, int begin)
{
    _in.read((char*)dst, sizeof(char));
}

bool FileStream::readInt16(short* dst, int begin)
{
    _in.read((char*)dst, sizeof(short));
}

bool FileStream::readUInt16(unsigned short* dst, int begin)
{
    _in.read((char*)dst, sizeof(short));
}

bool FileStream::readInt32(int* dst, int begin)
{
    _in.read((char*)dst, sizeof(int));
}

bool FileStream::readUInt32(unsigned int* dst, int begin)
{
    _in.read((char*)dst, sizeof(int));
}

bool FileStream::readInt64(long* dst, int begin)
{
    _in.read((char*)dst, sizeof(long));
}

bool FileStream::readUInt64(unsigned long* dst, int begin)
{
    _in.read((char*)dst, sizeof(long));
}

bool FileStream::readStr(char* dst, int begin, int len)
{
    
}