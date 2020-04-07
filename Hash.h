#ifndef __PKG_HASH_H__
#define __PKG_HASH_H__

#include "xxhash64.h"

namespace pkg
{

size_t Hash(const char* key, size_t len)
{
    XXHash64 base(0);
    if (base.add(key, len))
        return base.hash();
    return 0;
}

}

#endif