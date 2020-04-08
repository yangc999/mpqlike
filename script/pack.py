
import xxhash
import zlib
import struct
import os
import sys

'''
***FILE FORMAT***
[HEADER**COUNT,HASH_OFFSET,BLOCK_OFFSET**HASH..HASH**BLOCK..BLOCK**FILE..FILE**HEADER]
'''

def baseDir(path):
    if os.path.isfile(path):
        return os.path.dir(path)
    elif os.path.isdir(path):
        return path

def packFileList(path):
    files = []
    if os.path.isfile(path):
        files.append(path)
    elif os.path.isdir(path):
        for root, dirs, files in os.walk(path):
            for name in files:
                if name[0] != ".":
                    files.append(os.path.join(path, name))
            for name in dirs:
                if name[0] != ".":
                    sub = packFileList(os.path.join(path, name))
                    files.extend(sub)
    return files

def packFileBlock(path):
    target = open(path, "ra")
    content = target.read()
    compressed = zlib.compress(content)
    return struct.pack(">B", 1) + struct.pack(">L", len(content)) + struct.pack(">s", compressed)

def writeHeader(fp):
    fp.write(struct.pack(">s", "PKG"))

def writeBlank(fp):
    fp.write(struct.pack(">s", " "))

def writeUInt8(fp, dig):
    fp.write(struct.pack(">B", dig))

def writeUInt32(fp, dig):
    fp.write(struct.pack(">I", dig))
    
def writeUInt64(fp, dig):
    fp.write(struct.pack(">Q", dig))

def writeData(fp, data):
    fp.write(struct.pack(">s", data))

def move(fp, offset):
    fp.seek(offset)

if __name__ == "__main__":
    path = sys.argv[1]
    if os.path.exists(path):
        realPath = os.path.abspath(path)
        root = baseDir(realPath)
        # visit dir to get paths of all files
        files = packFileList(realPath)
        count = len(files)
        # calculate hash for each related path
        relatedPaths = [(path.replace(root, "")) for path in files]
        hashs = [(xxhash.xxh64(path, seed=0).intdigest()) for path in relatedPaths]
        # gen file
        binPath = os.getcwd() + "/data.pkg"
        if os.path.exists(binPath):
            os.remove(binPath)
        binFile = open(binPath, "ab+")
        # calculate offset
        hashOffset = 3 + 1 + 4 + 8 + 8 + 1
        blockOffset = hashOffset + 8*count + 1
        fileOffset = blockOffset + 16*count + 1
        blocks = []
        # write file begin
        writeHeader(binFile)
        writeBlank(binFile)
        writeUInt32(binFile, count)
        writeUInt64(binFile, hashOffset)
        writeUInt64(binFile, blockOffset)
        writeBlank(binFile)
        # write hash
        for h in hashs:
            writeUInt64(binFile, h)
        # write file
        move(binFile, fileOffset)
        filesBegin = fileOffset
        for p in files:
            handler = open(p)
            content = handler.read()
            encode = zlib.compress(content)
            writeUInt8(binFile, 1)
            writeUInt64(binFile, len(content))
            writeData(binFile, encode)
            length = 1 + 8 + len(encode)
            blocks.append((filesBegin, length))
            filesBegin = filesBegin + length
        # write block
        move(binFile, blockOffset)
        for b in blocks:
            writeUInt64(binFile, b[0])
            writeUInt64(binFile, b[1])
        writeBlank(binFile)
        writeHeader(binFile)
        binFile.close()