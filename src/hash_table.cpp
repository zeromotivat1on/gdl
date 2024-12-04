#include "pch.h"
#include "hash_table.h"
#include "hash.h"
#include "memory.h"

static inline bool table_key_valid(const Hash_Table* ht, const void* key, u64 key_hash, u32 key_idx)
{
    return ht->hashed_keys[key_idx] == key_hash && memcmp(key, ht->keys + key_idx * ht->key_size, ht->key_size) == 0;
}

void table_init(Hash_Table* ht, Arena* arena, u32 max_item_count, u32 key_size, u32 value_size, table_hash_func hash_func)
{
    ASSERT(hash_func);
    
    ht->hash_func = hash_func;
    ht->keys = arena_push_size(arena, max_item_count * key_size);
    ht->values = arena_push_size(arena, max_item_count * value_size);
    ht->hashed_keys = (u64*)arena_push_zero(arena, max_item_count * sizeof(u64));
    ht->item_count = 0;
    ht->max_item_count = max_item_count;
    ht->value_size = value_size;
    ht->key_size = key_size;
}

void* table_find(const Hash_Table* ht, const void* key)
{
    ASSERT(key);
    
    const u64 hash = ht->hash_func(key);
    u32 idx = hash % ht->max_item_count;

    while (ht->hashed_keys[idx] != 0)
    {
        if (table_key_valid(ht, key, hash, idx))
        {
            return ht->values + idx * ht->value_size;
        }

        idx++;
        
        if (idx >= ht->max_item_count)
        {
            idx = 0;
        }
    }

    return nullptr;
}

void table_insert(Hash_Table* ht, const void* key, const void* value)
{
    ASSERT(key);
    ASSERT(value);
    
    const u64 hash = ht->hash_func(key);
    u32 idx = hash % ht->max_item_count;

    while (ht->hashed_keys[idx] != 0)
    {
        if (table_key_valid(ht, key, hash, idx))
        {
            memcpy(ht->values + idx * ht->value_size, value, ht->value_size);
            return;
        }

        idx++;
        
        if (idx >= ht->max_item_count)
        {
            idx = 0;
        }
    }

    ht->item_count++;
    ASSERT(ht->item_count <= ht->max_item_count);
    
    ht->hashed_keys[idx] = hash;
    memcpy(ht->keys + idx * ht->key_size, key, ht->key_size);
    memcpy(ht->values + idx * ht->value_size, value, ht->value_size);
}

bool table_remove(Hash_Table* ht, const void* key)
{
    ASSERT(key)
    
    const u64 hash = ht->hash_func(key);
    u32 idx = hash % ht->max_item_count;

    while (ht->hashed_keys[idx] != 0)
    {
        if (table_key_valid(ht, key, hash, idx))
        {
            ht->item_count--;
            ht->hashed_keys[idx] = 0;
            memset(ht->keys + idx * ht->key_size, 0, ht->key_size);
            memset(ht->values + idx * ht->value_size, 0, ht->value_size);
            return true;
        }

        idx++;
        
        if (idx >= ht->max_item_count)
        {
            idx = 0;
        }
    }

    return false;
}

void table_rehash(Hash_Table* ht, Arena* arena, u32 max_item_count)
{
    u8* new_keys = arena_push_size(arena, max_item_count * ht->key_size);
    u8* new_values = arena_push_size(arena, max_item_count * ht->value_size);
    u64* new_hashed_keys = (u64*)arena_push_zero(arena, max_item_count * sizeof(u64));

    for (u32 i = 0; i < ht->max_item_count; ++i)
    {
        if (ht->hashed_keys[i] == 0)
            continue;

        u32 new_idx = ht->hashed_keys[i] % max_item_count;

        // Handle linear probing.
        while (new_hashed_keys[new_idx] != 0)
        {
            new_idx = (new_idx + 1) % max_item_count;
        }
       
        new_hashed_keys[new_idx] = ht->hashed_keys[i];
        memcpy(new_keys + new_idx * ht->key_size, ht->keys + i * ht->key_size, ht->key_size);
        memcpy(new_values + new_idx * ht->value_size, ht->values + i * ht->value_size, ht->value_size);
    }

    ht->keys = new_keys;
    ht->values = new_values;
    ht->hashed_keys = new_hashed_keys;
    ht->max_item_count = max_item_count;
}
