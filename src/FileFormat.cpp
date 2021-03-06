
#include <cstring>
#include "FileFormat.h"
#include "FileStream.h"
#include "FileBlock.h"
#include "Hash.h"

using namespace pkg;

FileFormat::FileFormat(const char* path):_path(path) 
{
    FileStream fs(_path.c_str());
    unsigned int fileCount;
    unsigned hashPos;
    unsigned blockPos;
    char header[3] = {0};

    if (!fs.readStr((unsigned char*)header, sizeof(header)) || strncmp(header, "PKG", 3) != 0)
        throw "header failed";

    if (!fs.readUInt32(&fileCount) || fileCount <= 0)
        throw "file count failed";

    if (!fs.readUInt32(&hashPos) || hashPos <= 0)
        throw "hash pos failed";

    if (!fs.readUInt32(&blockPos) || blockPos <= 0)
        throw "block pos failed";

    fs.offset(hashPos);
    for (size_t i = 0; i < fileCount; i++)
    {
        unsigned int hashCode;
        if (!fs.readUInt32(&hashCode) || hashCode <= 0)
            throw "hash code failed";
        hashTable.insert(std::pair<unsigned int, unsigned int>(hashCode, i));
    }

    fs.offset(blockPos);
    for (size_t i = 0; i < fileCount; i++)
    {
        unsigned int blockBegin;
        unsigned int blockLen;
        if (!fs.readUInt32(&blockBegin) || blockBegin <= 0)
            throw "block pos failed";
        if (!fs.readUInt32(&blockLen) || blockLen <= 0)
            throw "block len failed";
        blockInfo* blkInfo = (blockInfo*)malloc(sizeof(blockInfo));
        if (blkInfo != nullptr)
        {
            blkInfo->blockBegin = blockBegin;
            blkInfo->blockLength = blockLen;
            blockTable.push_back(blkInfo);
        }
    }
}

FileFormat::~FileFormat()
{
    hashTable.clear();
    for (auto it = blockTable.begin(); it != blockTable.end(); it++)
        free(*it);
    blockTable.clear();
}

const char* FileFormat::origin()
{
    return _path.c_str();
}

bool FileFormat::match(const char* path)
{
    unsigned int hashValue = Hash(path, strlen(path));
    if (hashTable.find(hashValue) != hashTable.end())
        return true;
    return false;
}

bool FileFormat::read(const char* path, Buffer& buf)
{
    unsigned int hashValue = Hash(path, strlen(path));
    if (hashTable.find(hashValue) != hashTable.end())
    {
        blockInfo* blkInf = blockTable[hashTable[hashValue]];
        FileStream fs(_path.c_str());
        Buffer bf;
        bf.resign(nullptr, blkInf->blockLength);
        fs.offset(blkInf->blockBegin);
        fs.readStr(bf.data(), blkInf->blockLength);
        FileBlock fb(bf);
        return fb.decode(buf);
    }
    return true;
}

size_t FileFormat::size(const char* path)
{
    unsigned int hashValue = Hash(path, strlen(path));
    if (hashTable.find(hashValue) != hashTable.end())
    {
        blockInfo* blkInf = blockTable[hashTable[hashValue]];
        FileStream fs(_path.c_str());
        Buffer bf;
        bf.resign(nullptr, blkInf->blockLength);
        fs.offset(blkInf->blockBegin);
        fs.readStr(bf.data(), blkInf->blockLength);
        FileBlock fb(bf);
        return fb.size();
    }
    return 0;
}
