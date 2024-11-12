#pragma once

#include "hash.h"
#include "time.h"

#define UID()   uid_gen()
#define UID(n)  uid_gen(n)

typedef u64 uid;

inline uid uid_hash(u64 n)
{
    return hash_pcg64(n);
}

inline uid uid_gen()
{
    const u64 ctime = (u64)(time_curr() << 32);
    const u64 stime = (u64)time_sys_boot();
    return uid_hash(ctime + stime);
}

inline uid uid_gen(u64 input)
{
    return uid_hash(input);
}
