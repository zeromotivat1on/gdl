#pragma once

typedef u64(*hash_table_hash_func)(const void* key);

struct Arena;

// Simple associative array in form of hash table.
// Collisions are handled by linear probing. Rehash is up to client.
struct Hash_Table
{
    hash_table_hash_func hash_func;

    u8*     keys;
    u8*     values;
    u64*    hashed_keys;
    u32     item_count;
    u32     max_item_count;
    u32     key_size;
    u32     value_size;
};

void    hash_table_init(Hash_Table* ht, Arena* arena, u32 max_item_count, u32 key_size, u32 value_size, hash_table_hash_func hash_func);
void*   hash_table_get(const Hash_Table* ht, const void* key);
void    hash_table_insert(Hash_Table* ht, const void* key, const void* value);
bool    hash_table_remove(Hash_Table* ht, const void* key);
void    hash_table_rehash(Hash_Table* ht, Arena* arena, u32 max_item_count);

inline f32 hash_table_load_factor(Hash_Table* ht)
{
    return (f32)ht->item_count / (f32)ht->max_item_count;
}
