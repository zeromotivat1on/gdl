#pragma once

// -----
// Types
// -----

struct u128
{
    u64 buckets[2];
};

struct u256
{
    u64 buckets[4];
};

struct u512
{
    u64 buckets[8];
};

// --------------------
// Large bit operations
// --------------------

inline void bit_set(u64* buckets, u64 idx)
{
    buckets[idx / 64] |= (1ull << (idx % 64));
}

inline void bit_clear(u64* buckets, u64 idx)
{
    buckets[idx / 64] &= ~(1ull << (idx % 64));
}

inline void bit_toggle(u64* buckets, u64 idx)
{
    buckets[idx / 64] ^= (1ull << (idx % 64));
}

inline bool bit_check(const u64* buckets, u64 idx)
{
    return (buckets[idx / 64] & (1ull << (idx % 64))) != 0;
}

inline void bit_set_all(u64* buckets, u64 count)
{
    memset(buckets, 0xFF, count * sizeof(u64));
}

inline void bit_clear_all(u64* buckets, u64 count)
{
    memset(buckets, 0, count * sizeof(u64));
}

inline void bit_and(u64* resbuckets, const u64* lbuckets, const u64* rbuckets, u64 count)
{
    for (u64 i = 0; i < count; ++i)
    {
        resbuckets[i] = lbuckets[i] & rbuckets[i];
    }
}

inline void bit_or(u64* res_buckets, const u64* lbuckets, const u64* rbuckets, u64 count)
{
    for (u64 i = 0; i < count; ++i)
    {
        res_buckets[i] = lbuckets[i] | rbuckets[i];
    }
}

inline void bit_xor(u64* res_buckets, const u64* lbuckets, const u64* rbuckets, u64 count)
{
    for (u64 i = 0; i < count; ++i)
    {
        res_buckets[i] = lbuckets[i] ^ rbuckets[i];
    }
}

inline void bit_not(u64* res_buckets, const u64* buckets, u64 count)
{
    for (u64 i = 0; i < count; ++i)
    {
        res_buckets[i] = ~buckets[i];
    }
}
