#pragma once

inline constexpr u32 INVALID_DENSE_INDEX = UINT32_MAX;

struct Arena;

struct Sparse_Set
{
    u8*     dense_items;
    u32*    dense_indices;
    u32*    sparse_indices;
    u32     dense_count;
    u32     dense_item_size;
    u32     max_dense_count;
    u32     max_sparse_count;

    void    init(Arena* arena, u32 max_dense_count, u32 max_sparse_count, u32 dense_item_size);
    bool    has(const u32 idx) const;
    bool    add(u32 idx, const void* dense_item);
    bool    add_zero(u32 idx);
    bool    remove(u32 idx);
    void*   get(const u32 idx) const;
    void    clear();
};
