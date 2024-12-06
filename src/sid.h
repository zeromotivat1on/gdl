#pragma once

#include "hash.h"
#include "hash_table.h"

#define SID(str) generate_sid(str)

typedef u64 sid;

inline Hash_Table g_sid_table;

inline u64 sid_table_hash_func(void* value)
{
    return *(sid*)value;
}

inline void init_sid(Arena* arena, u32 max_sid_count, u32 max_sid_size)
{
    hash_table_init(&g_sid_table, arena, max_sid_count, sizeof(u64), max_sid_size, (hash_table_hash_func)sid_table_hash_func);
}

inline sid hash_sid(const char* str)
{
    return hash_fnv(str);
}
    
inline sid generate_sid(const char* str)
{
    const sid hash = hash_sid(str);
    hash_table_add(&g_sid_table, &hash, str);
    return hash;
}

inline const char* string_from_sid(sid n)
{
    return (const char*)hash_table_find(&g_sid_table, &n);
}

inline bool is_unique_sid(sid n)
{
    return hash_table_find(&g_sid_table, &n) == nullptr;
}

inline bool is_unique_sid(const char* str)
{
    return is_unique_sid(hash_sid(str));
}
