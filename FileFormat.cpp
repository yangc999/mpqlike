
#include "FileFormat.h"
#include "FileStream.h"
#include "FileBlock.h"

using namespace pkg;

FileFormat::FileFormat(const char* path):_path(std::string(path))
{

}

FileFormat::~FileFormat()
{

}

bool FileFormat::valid()
{
    return false;
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

char* FileFormat::read(const char* path)
{
    int hashValue = (int)path;
    if (hashTable.find(hashValue) != hashTable.end())
    {
        blockInfo* blkInf = blockTable[hashTable[hashValue]];
        FileStream fs(_path.c_str);
        FileBlock fb(fs.readStr(blkInf->blockBegin, blkInf->blockLength), blkInf->blockLength);
        return fb.decode();
    }
    return nullptr;
}

int FileFormat::size(const char* path)
{
    int hashValue = (int)path;
    if (hashTable.find(hashValue) != hashTable.end())
    {
        blockInfo* blkInf = blockTable[hashTable[hashValue]];
        FileStream fs(_path.c_str);
        FileBlock fb(fs.readStr(blkInf->blockBegin, blkInf->blockLength));
        return fb.size();
    }
    return 0;
}
