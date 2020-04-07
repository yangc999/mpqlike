
#include "FileFormat.h"
#include "FileStream.h"
#include "FileBlock.h"

using namespace pkg;

FileFormat::FileFormat(const char* path):_path(std::string(path)) 
{
    FileStream fs(_path.c_str);
    unsigned int hashPos;
    unsigned int hashCount;
    unsigned int blockPos;
    unsigned int blockCount;
    char header[3];

    if (!fs.readStr(header, sizeof(header)) || strcmp(header, "PKG") != 0)
        throw "header failed";

    if (!fs.readUInt32(&hashPos) || hashPos <= 0)
        throw "hash pos failed";

    if (!fs.readUInt32(&hashCount) || hashCount <= 0)
        throw "hash count failed";

    if (!fs.readUInt32(&blockPos) || blockPos <= 0)
        throw "block pos failed";

    if (!fs.readUInt32(&blockCount) || blockCount <= 0)
        throw "block count failed";

    fs.offset(hashPos);
    for (size_t i = 0; i < hashCount; i++)
    {
        unsigned int hashCode;
        if (!fs.readUInt32(&hashCode) || hashCode <= 0)
            throw "hash code failed";
        hashTable.insert(std::pair<unsigned int, unsigned int>(hashCode, i));
    }

    fs.offset(blockPos);
    for (size_t i = 0; i < blockCount; i++)
    {
        unsigned int blockPos;
        unsigned int blockLen;
        if (!fs.readUInt32(&blockPos) || blockPos <= 0)
            throw "block pos failed";
        if (!fs.readUInt32(&blockLen) || blockLen <= 0)
            throw "block len failed";
        blockInfo* blkInfo = (blockInfo*)malloc(sizeof(blockInfo));
        blockTable.push_back(blkInfo);  
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
    int hashValue = (int)path;
    if (hashTable.find(hashValue) != hashTable.end())
        return true;
    return false;
}

bool FileFormat::read(const char* path, Buffer& buf)
{
    int hashValue = (int)path;
    if (hashTable.find(hashValue) != hashTable.end())
    {
        blockInfo* blkInf = blockTable[hashTable[hashValue]];
        FileStream fs(_path.c_str);
        Buffer bf;
        bf.resign(nullptr, blkInf->blockLength);
        fs.offset(blkInf->blockBegin);
        fs.readStr(bf.data(), blkInf->blockLength);
        FileBlock fb(bf);
        return fb.decode(buf);
    }
    return true;
}

int FileFormat::size(const char* path)
{
    int hashValue = (int)path;
    if (hashTable.find(hashValue) != hashTable.end())
    {
        blockInfo* blkInf = blockTable[hashTable[hashValue]];
        FileStream fs(_path.c_str);
        Buffer bf;
        bf.resign(nullptr, blkInf->blockLength);
        fs.offset(blkInf->blockBegin);
        fs.readStr(bf.data(), blkInf->blockLength);
        FileBlock fb(bf);
        return fb.size();
    }
    return 0;
}
