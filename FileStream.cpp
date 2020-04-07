
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

bool FileStream::readInt8(char* dst)
{
    if (!_in.is_open())
        return false;
    _in.read(dst, sizeof(char));
    return true;
}

bool FileStream::readUInt8(unsigned char* dst)
{
    if (!_in.is_open())
        return false;
    _in.read((char*)dst, sizeof(char));
    return true;
}

bool FileStream::readInt16(short* dst)
{
    if (!_in.is_open())
        return false;
    _in.read((char*)dst, sizeof(short));
    return true;
}

bool FileStream::readUInt16(unsigned short* dst)
{
    if (!_in.is_open())
        return false;
    _in.read((char*)dst, sizeof(short));
    return true;
}

bool FileStream::readInt32(int* dst)
{
    if (!_in.is_open())
        return false;
    _in.read((char*)dst, sizeof(int));
    return true;
}

bool FileStream::readUInt32(unsigned int* dst)
{
    if (!_in.is_open())
        return false;
    _in.read((char*)dst, sizeof(int));
    return true;
}

bool FileStream::readInt64(long* dst)
{
    if (!_in.is_open())
        return false;
    _in.read((char*)dst, sizeof(long));
    return true;
}

bool FileStream::readUInt64(unsigned long* dst)
{
    if (!_in.is_open())
        return false;
    _in.read((char*)dst, sizeof(long));
    return true;
}

bool FileStream::readStr(char* dst, int length)
{
    if (!_in.is_open())
        return false;
    _in.read(dst, length);
    return true;
}

bool FileStream::offset(int off)
{
    if (!_in.is_open())
        return false;
    _in.seekg(off);
    return true;
}