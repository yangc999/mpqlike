#! /usr/bin/python

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
    flist = []
    if os.path.isfile(path):
        flist.append(path)
    elif os.path.isdir(path):
        for root, dirs, files in os.walk(path):
            files[:] = [f for f in files if not f[0] == "."]
            dirs[:] = [d for d in dirs if not d[0] == "."]
            for name in files:
                flist.append(os.path.join(root, name))
    return flist

def packFileBlock(path):
    target = open(path, "r")
    content = target.read()
    compressed = zlib.compress(content)
    print("compressed length:%d" % len(compressed))
    target.close()
    return struct.pack("=BL%ds0c" % len(compressed), 1, len(content), compressed)

def writeHeader(fp):
    fp.write(struct.pack("=3s", "PKG"))

def writeBlank(fp):
    fp.write(struct.pack("=s", " "))

def writeUInt8(fp, dig):
    fp.write(struct.pack("=B", dig))

def writeUInt32(fp, dig):
    fp.write(struct.pack("=I", dig))

def writeData(fp, data):
    fp.write(struct.pack("=%ds" % len(data), data))

def move(fp, offset):
    fp.seek(offset)

if __name__ == "__main__":
    path = sys.argv[1]
    if os.path.exists(path):
        realPath = os.path.abspath(path)
        print("real path:" + realPath)
        root = baseDir(realPath)
        print("root path:" + root)
        # visit dir to get paths of all files
        files = packFileList(realPath)
        print("pack files:")
        print(files)
        count = len(files)
        # calculate hash for each related path
        relatedPaths = [(path.replace(root + "/", "")) for path in files]
        print("related path:")
        print(relatedPaths)
        hashs = [(xxhash.xxh32(path, seed=0).intdigest()) for path in relatedPaths]
        print("hashs:")
        print(hashs)
        # gen file
        binPath = os.getcwd() + "/data.pkg"
        if os.path.exists(binPath):
            os.remove(binPath)
        binFile = open(binPath, "wb+")
        # calculate offset
        hashOffset = 3 + 4 + 4 + 4
        blockOffset = hashOffset + 4 * count
        fileOffset = blockOffset + 8 * count
        blocks = []
        # write file begin
        writeHeader(binFile)
        writeUInt32(binFile, count)
        writeUInt32(binFile, hashOffset)
        writeUInt32(binFile, blockOffset)
        # write hash
        for h in hashs:
            writeUInt32(binFile, h)
        # write file
        move(binFile, fileOffset)
        filesBegin = fileOffset
        for p in files:
            pack = packFileBlock(p)
            length = len(pack)
            print("pack file:%s" % pack.encode("hex"))
            writeData(binFile, pack)
            blocks.append((filesBegin, length))
            filesBegin = filesBegin + length
        writeHeader(binFile)
        # write block
        move(binFile, blockOffset)
        print("blocks:")
        print(blocks)
        for b in blocks:
            writeUInt32(binFile, b[0])
            writeUInt32(binFile, b[1])
        binFile.close()
