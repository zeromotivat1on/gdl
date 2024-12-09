#pragma once

#include "hash.h"
#include "hash_table.h"

#define SID(str) generate_sid(str)

typedef u64 sid;

inline Hash_Table g_sid_table;

inline u64 sid_table_hash_func(const void* value)
{
    return *(sid*)value;
}

inline void init_sid(Arena* arena, u32 max_sid_count, u32 max_sid_size)
{
    g_sid_table.init(arena, max_sid_count, sizeof(u64), max_sid_size, sid_table_hash_func);
}

inline sid hash_sid(const char* str)
{
    return hash_fnv(str);
}

inline bool is_unique_sid(sid n)
{
    return g_sid_table.find(&n) == nullptr;
}

inline bool is_unique_sid(const char* str)
{
    return is_unique_sid(hash_sid(str));
}

inline sid generate_sid(const char* str)
{
    const sid hash = hash_sid(str);
    if (is_unique_sid(hash))
        g_sid_table.add(&hash, str);
    return hash;
}

inline const char* string_from_sid(sid n)
{
    return (const char*)g_sid_table.find(&n);
}
