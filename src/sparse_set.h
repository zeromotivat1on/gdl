#pragma once

inline constexpr u32 INVALID_DENSE_INDEX = UINT32_MAX;

struct Arena;

struct SparseSet
{
    u8*     dense_items;
    u32*    dense_indices;
    u32*    sparse_indices;
    u32     dense_count;
    u32     dense_item_size;
    u32     max_dense_count;
    u32     max_sparse_count;
};

void        sparse_set_init(SparseSet* ss, void* dense_items, u32* dense_indices, u32* sparse_indices, u32 max_dense_count, u32 max_sparse_count, u32 dense_item_size);
void        sparse_set_init(SparseSet* ss, Arena* arena, u32 max_dense_count, u32 max_sparse_count, u32 dense_item_size);
bool        sparse_set_has(const SparseSet* ss, u32 idx);
bool        sparse_set_insert(SparseSet* ss, u32 idx, const void* dense_item);
bool        sparse_set_insert_zero(SparseSet* ss, u32 idx);
bool        sparse_set_remove(SparseSet* ss, u32 idx);
void*       sparse_set_get(const SparseSet* ss, u32 idx);
void        sparse_set_clear(SparseSet* ss);
