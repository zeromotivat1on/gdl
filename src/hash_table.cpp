#include "pch.h"
#include "hash_table.h"
#include "hash.h"
#include "memory.h"

bool Hash_Table::default_cmp_func(const void* lkey, const void* rkey, u32 key_size)
{
    return memcmp(lkey, rkey, key_size) == 0;
}

void Hash_Table::init(Arena* arena, u32 max_item_count, u32 key_size, u32 value_size, Hash_Func hash_func, Cmp_Func cmp_func)
{
    ASSERT(hash_func);
    
    this->hash_func = hash_func;
    this->cmp_func = cmp_func ? cmp_func : Hash_Table::default_cmp_func;
    this->keys = (u8*)arena->push_zero(max_item_count * key_size);
    this->values = (u8*)arena->push_zero(max_item_count * value_size);
    this->hashes = (u64*)arena->push_zero(max_item_count * sizeof(u64));
    this->item_count = 0;
    this->max_item_count = max_item_count;
    this->value_size = value_size;
    this->key_size = key_size;
}

void* Hash_Table::find(const void* key) const
{
    ASSERT(key);
    
    const u64 hash = hash_func(key);
    u32 idx = hash % max_item_count;

    while (hashes[idx] != 0)
    {
        const void* table_key = keys + idx * key_size;
        if (hashes[idx] == hash && cmp_func(key, table_key, key_size))
        {
            return values + idx * value_size;
        }
        
        idx++;
        
        if (idx >= max_item_count)
        {
            idx = 0;
        }
    }

    return nullptr;
}

void* Hash_Table::add(const void* key, const void* value)
{
    ASSERT(key);
    ASSERT(value);
    ASSERT(load_factor() < 1.0f);
    
    const u64 hash = hash_func(key);
    u32 idx = hash % max_item_count;

    while (hashes[idx] != 0)
    {
        idx++;
        
        if (idx >= max_item_count)
        {
            idx = 0;
        }
    }

    item_count++;
    ASSERT(item_count <= max_item_count);
    
    hashes[idx] = hash;
    memcpy(keys + idx * key_size, key, key_size);
    memcpy(values + idx * value_size, value, value_size);

    return values + idx * value_size;
}

bool Hash_Table::remove(const void* key)
{
    ASSERT(key)
    
    const u64 hash = hash_func(key);
    u32 idx = hash % max_item_count;

    while (hashes[idx] != 0)
    {
        const void* table_key = keys + idx * key_size;
        if (hashes[idx] == hash && cmp_func(key, table_key, key_size))
        {
            item_count--;
            hashes[idx] = 0;
            memset(keys + idx * key_size, 0, key_size);
            memset(values + idx * value_size, 0, value_size);
            return true;
        }

        idx++;
        
        if (idx >= max_item_count)
        {
            idx = 0;
        }
    }

    return false;
}

void Hash_Table::rehash(Arena* arena, u32 max_item_count)
{
    u8* new_keys = (u8*)arena->push(max_item_count * key_size);
    u8* new_values = (u8*)arena->push(max_item_count * value_size);
    u64* new_hashes = (u64*)arena->push(max_item_count * sizeof(u64));

    for (u32 i = 0; i < max_item_count; ++i)
    {
        if (hashes[i] == 0)
            continue;

        u32 new_idx = hashes[i] % max_item_count;

        while (new_hashes[new_idx] != 0)
        {
            new_idx = (new_idx + 1) % max_item_count;
        }
       
        new_hashes[new_idx] = hashes[i];
        memcpy(new_keys + new_idx * key_size, keys + i * key_size, key_size);
        memcpy(new_values + new_idx * value_size, values + i * value_size, value_size);
    }

    keys = new_keys;
    values = new_values;
    hashes = new_hashes;
    max_item_count = max_item_count;
}

f32 Hash_Table::load_factor() const
{
    return (f32)item_count / (f32)max_item_count;
}
