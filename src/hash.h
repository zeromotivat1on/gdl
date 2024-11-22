#pragma once

// ---
// PCG
// ---

inline u32 hash_pcg32(u32 input)
{
    u32 state = input * 747796405u + 2891336453u;
    u32 word = ((state >> ((state >> 28u) + 4u)) ^ state) * 277803737u;
    return (word >> 22u) ^ word;
}

inline u64 hash_pcg64(u64 input)
{
    return hash_pcg32((u32)input) + hash_pcg32(input >> 32);
}

// ------
// FNV-1a
// ------

inline constexpr u64 FNV_BASIS = 14695981039346656037ull;
inline constexpr u64 FNV_PRIME = 1099511628211ull;

inline u64 hash_fnv(const char* str)
{
    u64 hash = FNV_BASIS;
    for (const char* p = str; *p; ++p)
    {
        hash ^= (u64)(u8)(*p);
        hash *= FNV_PRIME;
    }

    return hash;
}
