#include "pch.h"
#include "sparse_set.h"
#include "mem.h"

void sparse_set_init(SparseSet* ss, Arena* arena, u32 max_dense_count, u32 max_sparse_count, u32 dense_item_size)
{
    ss->dense_items = arena_push_size(arena, max_dense_count * dense_item_size);
    ss->dense_indices = arena_push_array(arena, max_dense_count, u32);
    ss->sparse_indices = arena_push_array(arena, max_sparse_count, u32);
    ss->dense_count = 0;
    ss->dense_item_size = dense_item_size;
    ss->max_dense_count = max_dense_count;
    ss->max_sparse_count = max_sparse_count;

    memset(ss->sparse_indices, 0xFF, max_sparse_count * sizeof(u32));
}

bool sparse_set_has(const SparseSet* ss, u32 idx)
{
    ASSERT(idx < ss->max_sparse_count);
    
    const u32 dense_idx = ss->sparse_indices[idx];
    return dense_idx < ss->dense_count && dense_idx != INVALID_DENSE_INDEX;
}

bool sparse_set_insert(SparseSet* ss, u32 idx, const void* dense_item)
{
    ASSERT(idx < ss->max_sparse_count);

    if (sparse_set_has(ss, idx))
        return false;

    const u32 last_dense_idx = ss->dense_count++; 
    ss->sparse_indices[idx] = last_dense_idx;
    ss->dense_indices[last_dense_idx] = idx;
    memcpy(ss->dense_items + last_dense_idx * ss->dense_item_size, dense_item, ss->dense_item_size);

    return true;
}

bool sparse_set_insert_zero(SparseSet* ss, u32 idx)
{
    ASSERT(idx < ss->max_sparse_count);

    if (sparse_set_has(ss, idx))
        return false;

    const u32 last_dense_idx = ss->dense_count++; 
    ss->sparse_indices[idx] = last_dense_idx;
    ss->dense_indices[last_dense_idx] = idx;
    memset(ss->dense_items + last_dense_idx * ss->dense_item_size, 0, ss->dense_item_size);

    return true;
}

bool sparse_set_remove(SparseSet* ss, u32 idx)
{
    ASSERT(idx < ss->max_sparse_count);

    if (!sparse_set_has(ss, idx))
        return false;

    const u32 last_dense_idx = --ss->dense_count;
    const u32 dense_idx = ss->sparse_indices[idx];
    const u32 last_dense_item_idx = ss->dense_indices[last_dense_idx];

    ss->sparse_indices[last_dense_item_idx] = dense_idx;
    ss->dense_indices[dense_idx] = last_dense_item_idx;
    ss->sparse_indices[idx] = INVALID_DENSE_INDEX;
    
    memcpy(ss->dense_items + dense_idx * ss->dense_item_size, ss->dense_items + last_dense_idx * ss->dense_item_size, ss->dense_item_size);
    
    return true;
}

void* sparse_set_get(const SparseSet* ss, u32 idx)
{
    ASSERT(idx < ss->max_sparse_count);

    const u32 dense_idx = ss->sparse_indices[idx];
    if (dense_idx < ss->dense_count)
    {
        return ss->dense_items + dense_idx * ss->dense_item_size;    
    }
    
    return nullptr;
}

void sparse_set_clear(SparseSet* ss)
{
    ss->dense_count = 0;
}
