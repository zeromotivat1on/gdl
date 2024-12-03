#pragma once

#include "hash.h"
#include "time.h"

#define UID generate_uid()

typedef u64 uid;

inline uid hash_uid(u64 n)
{
    return hash_pcg64(n);
}

inline uid generate_uid()
{
    const u64 high = (u64)(current_time() << 32);
    const u64 low = (u64)time_since_sys_boot();
    return hash_uid(high + low);
}

inline uid generate_uid(u64 input)
{
    return hash_uid(input);
}
