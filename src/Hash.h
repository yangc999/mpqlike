#ifndef __PKG_HASH_H__
#define __PKG_HASH_H__

#include "xxhash32.h"
#include "xxhash64.h"

namespace pkg
{

unsigned int Hash(const char* key, size_t len)
{
    XXHash32 base(0);
    if (base.add(key, len))
        return base.hash();
    return 0;
}

}

#endif