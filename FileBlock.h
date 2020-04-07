
namespace pkg
{

enum EncodeType
{
    FLAT = 0,
    ZIP = 1
};

typedef struct fileInfo
{
    EncodeType encTp;
    int size;
} fileInfo;

class FileBlock
{
private:
    fileInfo flInf;
public:
    FileBlock(char* chunk);
    ~FileBlock();
    char* decode();
    int size();
};

}