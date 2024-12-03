#pragma once

#include "hash.h"
#include "hash_table.h"

#define SID(str) sid_gen(str)

typedef u64 sid;

inline Hash_Table g_sid_table;

inline u64 sid_table_hash(void* value)
{
    return *(sid*)value;
}

inline void sid_init(Arena* arena, u32 max_sid_count, u32 max_sid_size)
{
    hash_table_init(&g_sid_table, arena, max_sid_count, sizeof(u64), max_sid_size, (hash_table_hash_func)sid_table_hash);
}

inline sid sid_hash(const char* str)
{
    return hash_fnv(str);
}
    
inline sid sid_gen(const char* str)
{
    const sid hash = sid_hash(str);
    hash_table_insert(&g_sid_table, &hash, str);
    return hash;
}

inline const char* sid_str(sid n)
{
    return (const char*)hash_table_get(&g_sid_table, &n);
}

inline bool sid_unique(sid n)
{
    return hash_table_get(&g_sid_table, &n) == nullptr;
}

inline bool sid_unique(const char* str)
{
    return sid_unique(sid_hash(str));
}
