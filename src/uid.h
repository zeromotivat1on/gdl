#pragma once

#include "hash.h"

#define UID()   uidgen()
#define UID(n)  uidgen(n)

typedef u64 uid;

inline uid uidhash(u64 n)
{
    return hashpcg64(n);
}

inline uid uidgen()
{
    const u64 ctime = (u64)(tmcurr() << 32);
    const u64 stime = (u64)tmsysboot();
    return uidhash(ctime + stime);
}

inline uid uidgen(u64 input)
{
    return uidhash(input);
}
