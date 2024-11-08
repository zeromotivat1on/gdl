#pragma once

// -----
// Types
// -----

struct u128
{
    u64 Buckets[2];
};

struct u256
{
    u64 Buckets[4];
};

struct u512
{
    u64 Buckets[8];
};

// --------------
// Bit operations
// --------------

inline void bitset(u64* buckets, u64 idx)
{
    buckets[idx / 64] |= (1ull << (idx % 64));
}

inline void bitclear(u64* buckets, u64 idx)
{
    buckets[idx / 64] &= ~(1ull << (idx % 64));
}

inline void bittoggle(u64* buckets, u64 idx)
{
    buckets[idx / 64] ^= (1ull << (idx % 64));
}

inline bool bitcheck(const u64* buckets, u64 idx)
{
    return (buckets[idx / 64] & (1ull << (idx % 64))) != 0;
}

inline void bitsetall(u64* buckets, u64 count)
{
    memset(buckets, 0xFF, count * sizeof(u64));
}

inline void bitclearall(u64* buckets, u64 count)
{
    memset(buckets, 0, count * sizeof(u64));
}

inline void bitand(u64* resbuckets, const u64* lbuckets, const u64* rbuckets, u64 count)
{
    for (u64 i = 0; i < count; ++i)
    {
        resbuckets[i] = lbuckets[i] & rbuckets[i];
    }
}

inline void bitor(u64* resbuckets, const u64* lbuckets, const u64* rbuckets, u64 count)
{
    for (u64 i = 0; i < count; ++i)
    {
        resbuckets[i] = lbuckets[i] | rbuckets[i];
    }
}

inline void bitxor(u64* resbuckets, const u64* lbuckets, const u64* rbuckets, u64 count)
{
    for (u64 i = 0; i < count; ++i)
    {
        resbuckets[i] = lbuckets[i] ^ rbuckets[i];
    }
}

inline void bitnot(u64* resbuckets, const u64* buckets, u64 count)
{
    for (u64 i = 0; i < count; ++i)
    {
        resbuckets[i] = ~buckets[i];
    }
}
