#pragma once

struct Arena;

struct Hash_Table
{
    using Hash_Func = u64(const void* key);
    using Cmp_Func = bool(const void* lkey, const void* rkey, u32 key_size);

    static bool default_cmp_func(const void* lkey, const void* rkey, u32 key_size);
    
    Hash_Func*  hash_func;
    Cmp_Func*   cmp_func;

    u8*     keys;
    u8*     values;
    u64*    hashes;
    u32     item_count;
    u32     max_item_count;
    u32     key_size;
    u32     value_size;

    void    init(Arena* arena, u32 max_item_count, u32 key_size, u32 value_size, Hash_Func hash_func, Cmp_Func cmp_func = nullptr);
    void*   find(const void* key) const;
    void*   add(const void* key, const void* value);
    bool    remove(const void* key);
    void    rehash(Arena* arena, u32 max_item_count);
    f32     load_factor() const;
};
