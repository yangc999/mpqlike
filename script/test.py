#! /usr/bin/python

import xxhash
import zlib
import struct
import os
import sys

def readUInt8(fp):
    return struct.unpack("=B", fp.read(1))[0]

def readUInt32(fp):
    return struct.unpack("=I", fp.read(4))[0]

def find(pkg, filename):
    if os.path.exists(pkg) and os.path.isfile(pkg):
        fp = open(pkg, "r")
        fp.seek(3)
        count = readUInt32(fp)
        hashOff = readUInt32(fp)
        blockOff = readUInt32(fp)
        hashs = []
        fp.seek(hashOff)
        for i in range(count):
            hashs.append(readUInt32(fp))
        hashValue = xxhash.xxh32(filename, seed=0).intdigest()
        return hashs.index(hashValue)

def show(pkg, filename):
    if os.path.exists(pkg) and os.path.isfile(pkg):
        fp = open(pkg, "r")
        fp.seek(3)
        count = readUInt32(fp)
        hashOff = readUInt32(fp)
        blockOff = readUInt32(fp)
        hashs = []
        blocks = []
        fp.seek(hashOff)
        for i in range(count):
            hashs.append(readUInt32(fp))
        fp.seek(blockOff)
        for i in range(count):
            off = readUInt32(fp)
            length = readUInt32(fp)
            blocks.append((off, length))
        print("blocks:")
        print(blocks)
        hashValue = xxhash.xxh32(filename, seed=0).intdigest()
        blk = blocks[hashs.index(hashValue)]
        fp.seek(blk[0])
        detail = fp.read(blk[1])
        print("file detail:%s" % detail.encode("hex"))
        flag = struct.unpack("=B", detail[0:1])[0]
        size = struct.unpack("=I", detail[1:5])[0]
        content = struct.unpack("={}s".format(blk[1]-5), detail[5:])[0]
        decode = zlib.decompress(content)
        print(len(decode))
        return decode

if __name__ == "__main__":
    if sys.argv[1] == "find":
        print(find(sys.argv[2], sys.argv[3]))
    elif sys.argv[1] == "show":
        print(show(sys.argv[2], sys.argv[3]))