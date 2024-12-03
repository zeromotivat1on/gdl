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
};

void        sparse_set_init(Sparse_Set* ss, Arena* arena, u32 max_dense_count, u32 max_sparse_count, u32 dense_item_size);
bool        sparse_set_has(const Sparse_Set* ss, u32 idx);
bool        sparse_set_insert(Sparse_Set* ss, u32 idx, const void* dense_item);
bool        sparse_set_insert_zero(Sparse_Set* ss, u32 idx);
bool        sparse_set_remove(Sparse_Set* ss, u32 idx);
void*       sparse_set_get(const Sparse_Set* ss, u32 idx);
void        sparse_set_clear(Sparse_Set* ss);
