#include "pch.h"
#include "sparse_set.h"
#include "memory.h"

void Sparse_Set::init(Arena* arena, u32 max_dense_count, u32 max_sparse_count, u32 dense_item_size)
{
    this->dense_items = arena_push_size(arena, max_dense_count * dense_item_size);
    this->dense_indices = arena_push_array(arena, max_dense_count, u32);
    this->sparse_indices = arena_push_array(arena, max_sparse_count, u32);
    this->dense_count = 0;
    this->dense_item_size = dense_item_size;
    this->max_dense_count = max_dense_count;
    this->max_sparse_count = max_sparse_count;

    memset(this->sparse_indices, 0xFF, max_sparse_count * sizeof(u32));
}

bool Sparse_Set::has(u32 idx) const
{
    ASSERT(idx < max_sparse_count);
    
    const u32 dense_idx = sparse_indices[idx];
    return dense_idx < dense_count && dense_idx != INVALID_DENSE_INDEX;
}

bool Sparse_Set::add(u32 idx, const void* dense_item)
{
    ASSERT(idx < max_sparse_count);

    if (has(idx))
        return false;

    const u32 last_dense_idx = dense_count++; 
    sparse_indices[idx] = last_dense_idx;
    dense_indices[last_dense_idx] = idx;
    memcpy(dense_items + last_dense_idx * dense_item_size, dense_item, dense_item_size);

    return true;
}

bool Sparse_Set::add_zero(u32 idx)
{
    ASSERT(idx < max_sparse_count);

    if (has(idx))
        return false;

    const u32 last_dense_idx = dense_count++; 
    sparse_indices[idx] = last_dense_idx;
    dense_indices[last_dense_idx] = idx;
    memset(dense_items + last_dense_idx * dense_item_size, 0, dense_item_size);

    return true;
}

bool Sparse_Set::remove(u32 idx)
{
    ASSERT(idx < max_sparse_count);

    if (!has(idx))
        return false;

    const u32 last_dense_idx = --dense_count;
    const u32 dense_idx = sparse_indices[idx];
    const u32 last_dense_item_idx = dense_indices[last_dense_idx];

    sparse_indices[last_dense_item_idx] = dense_idx;
    dense_indices[dense_idx] = last_dense_item_idx;
    sparse_indices[idx] = INVALID_DENSE_INDEX;
    
    memcpy(dense_items + dense_idx * dense_item_size, dense_items + last_dense_idx * dense_item_size, dense_item_size);
    memset(dense_items + last_dense_idx * dense_item_size, 0, dense_item_size);
    
    return true;
}

void* Sparse_Set::get(const u32 idx) const
{
    ASSERT(idx < max_sparse_count);

    const u32 dense_idx = sparse_indices[idx];
    if (dense_idx < dense_count && dense_idx != INVALID_DENSE_INDEX)
    {
        return dense_items + dense_idx * dense_item_size;    
    }
    
    return nullptr;
}

void Sparse_Set::clear()
{
    dense_count = 0;
}
