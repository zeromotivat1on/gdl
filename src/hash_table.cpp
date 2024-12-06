#include "pch.h"
#include "hash_table.h"
#include "hash.h"
#include "memory.h"

static inline bool hash_table_default_cmp(const void* lkey, const void* rkey, u32 key_size)
{
    return memcmp(lkey, rkey, key_size) == 0;
}

void hash_table_init(Hash_Table* ht, Arena* arena, u32 max_item_count, u32 key_size, u32 value_size, hash_table_hash_func hash_func, hash_table_cmp_func cmp_func)
{
    ASSERT(hash_func);
    
    ht->hash_func = hash_func;
    ht->cmp_func = cmp_func ? cmp_func : hash_table_default_cmp;
    ht->keys = arena_push_size(arena, max_item_count * key_size);
    ht->values = arena_push_size(arena, max_item_count * value_size);
    ht->hashes = (u64*)arena_push_zero(arena, max_item_count * sizeof(u64));
    ht->item_count = 0;
    ht->max_item_count = max_item_count;
    ht->value_size = value_size;
    ht->key_size = key_size;
}

void* hash_table_find(const Hash_Table* ht, const void* key)
{
    ASSERT(key);
    
    const u64 hash = ht->hash_func(key);
    u32 idx = hash % ht->max_item_count;

    while (ht->hashes[idx] != 0)
    {
        const void* table_key = ht->keys + idx * ht->key_size;
        if (ht->hashes[idx] == hash && ht->cmp_func(key, table_key, ht->key_size))
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

void* hash_table_add(Hash_Table* ht, const void* key, const void* value)
{
    ASSERT(key);
    ASSERT(value);
    ASSERT(hash_table_load_factor(ht) < 1.0f);
    
    const u64 hash = ht->hash_func(key);
    u32 idx = hash % ht->max_item_count;

    while (ht->hashes[idx] != 0)
    {
        idx++;
        
        if (idx >= ht->max_item_count)
        {
            idx = 0;
        }
    }

    ht->item_count++;
    ASSERT(ht->item_count <= ht->max_item_count);
    
    ht->hashes[idx] = hash;
    memcpy(ht->keys + idx * ht->key_size, key, ht->key_size);
    memcpy(ht->values + idx * ht->value_size, value, ht->value_size);

    return ht->values + idx * ht->value_size;
}

bool hash_table_remove(Hash_Table* ht, const void* key)
{
    ASSERT(key)
    
    const u64 hash = ht->hash_func(key);
    u32 idx = hash % ht->max_item_count;

    while (ht->hashes[idx] != 0)
    {
        const void* table_key = ht->keys + idx * ht->key_size;
        if (ht->hashes[idx] == hash && ht->cmp_func(key, table_key, ht->key_size))
        {
            ht->item_count--;
            ht->hashes[idx] = 0;
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

void hash_table_rehash(Hash_Table* ht, Arena* arena, u32 max_item_count)
{
    u8* new_keys = arena_push_size(arena, max_item_count * ht->key_size);
    u8* new_values = arena_push_size(arena, max_item_count * ht->value_size);
    u64* new_hashes = (u64*)arena_push_zero(arena, max_item_count * sizeof(u64));

    for (u32 i = 0; i < ht->max_item_count; ++i)
    {
        if (ht->hashes[i] == 0)
            continue;

        u32 new_idx = ht->hashes[i] % max_item_count;

        while (new_hashes[new_idx] != 0)
        {
            new_idx = (new_idx + 1) % max_item_count;
        }
       
        new_hashes[new_idx] = ht->hashes[i];
        memcpy(new_keys + new_idx * ht->key_size, ht->keys + i * ht->key_size, ht->key_size);
        memcpy(new_values + new_idx * ht->value_size, ht->values + i * ht->value_size, ht->value_size);
    }

    ht->keys = new_keys;
    ht->values = new_values;
    ht->hashes = new_hashes;
    ht->max_item_count = max_item_count;
}
