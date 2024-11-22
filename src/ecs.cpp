#include "pch.h"
#include "ecs.h"
#include "hash.h"
#include "mem.h"
#include "sparse_set.h"

static u64 ecs_hash_component_type(const void* item)
{
    return (u64)*(sid*)item;
}

void ecs_init(ECS* ecs, Arena* arena, u32 max_entities, u16 max_component_type_count)
{
    ecs->max_entity_count = max_entities;
    
    ecs->entity_count = 0;
    ecs->entities = arena_push_array(arena, max_entities, Entity);
    memset(ecs->entities, INVALID_ENTITY, max_entities * sizeof(Entity));

    ecs->free_entity_count = 0;
    ecs->free_entities = arena_push_array(arena, max_entities, Entity);
    memset(ecs->free_entities, INVALID_ENTITY, max_entities * sizeof(Entity));

    hash_table_init(&ecs->components_table, arena, max_component_type_count, sizeof(sid), sizeof(SparseSet), ecs_hash_component_type);
}

Entity ecs_entity_new(ECS* ecs)
{
    if (ecs->free_entity_count > 0)
    {
        const u32 last_free_idx = --ecs->free_entity_count;
        const u32 idx = ecs->free_entities[last_free_idx];
        ecs->entities[idx] = idx;
        ecs->free_entities[idx] = INVALID_ENTITY;
        return ecs->entities[idx];
    }

    const u32 idx = ecs->entity_count++;
    ASSERT(idx < ecs->max_entity_count);
    ecs->entities[idx] = idx;
    return ecs->entities[idx];
}

void ecs_entity_del(ECS* ecs, Entity e)
{
    ASSERT(e != INVALID_ENTITY);
    ASSERT(e < ecs->max_entity_count);

    if (ecs->entities[e] == INVALID_ENTITY)
    {
        msg_warning("Attempt to delete invalid entity (%d)", e);
        return;
    }

    ecs->entities[e] = INVALID_ENTITY;
    const u32 idx = ecs->free_entity_count++;
    ASSERT(idx < ecs->max_entity_count);
    ecs->free_entities[idx] = e;

    for (u32 i = 0; i < ecs->components_table.max_item_count; ++i)
    {
        if (ecs->components_table.hashed_keys[i] == 0)
            continue;

        const sid key = *(sid*)(ecs->components_table.keys + i * ecs->components_table.key_size);
        ecs_component_del(ecs, e, key);
    }
}

void ecs_entity_iterate(ECS* ecs, const sid* cts, u8 cts_count, ecs_entity_iterate_callback callback)
{
    ASSERT(cts_count > 0);

    SparseSet* ct_sparse_set = (SparseSet*)hash_table_get(&ecs->components_table, &cts[0]);

    if (!ct_sparse_set)
    {
        msg_error("[gdl]: Failed to get component sparse set from sid (%u)", cts[0]);
        return;
    }
    
    u64 smallest_dense_count = ct_sparse_set->dense_count;
    u64 smallest_set_index = 0;
    
    for (u64 i = 1; i < cts_count; ++i)
    {
        ct_sparse_set = (SparseSet*)hash_table_get(&ecs->components_table, &cts[i]);

        if (!ct_sparse_set)
        {
            msg_error("[gdl]: Failed to get component sparse set from sid (%u)", cts[i]);
            return;
        }
        
        const u64 dense_count = ct_sparse_set->dense_count;
        if (dense_count < smallest_dense_count)
        {
            smallest_set_index = i;
            smallest_dense_count = dense_count;
        }
    }

    const SparseSet* smallest_set = (SparseSet*)hash_table_get(&ecs->components_table, &cts[smallest_set_index]);
    for (u64 i = 0; i < smallest_set->dense_count; ++i)
    {
        const Entity e = smallest_set->dense_indices[i];
        bool has_all_components = true;

        for (u64 j = 0; j < cts_count; ++j)
        {
            if (j == smallest_set_index)
                continue;

            const SparseSet* other_set = (SparseSet*)hash_table_get(&ecs->components_table, &cts[j]);
            if (!sparse_set_has(other_set, e))
            {
                has_all_components = false;
                break;
            }
        }

        if (has_all_components)
        {
            callback(ecs, e);
        }
    }
}

void ecs_component_reg(ECS* ecs, Arena* arena, sid ct, u16 ct_size)
{
    SparseSet component_set;
    sparse_set_init(&component_set, arena, ecs->max_entity_count, ecs->max_entity_count, ct_size);
    hash_table_insert(&ecs->components_table, &ct, &component_set);
}

bool ecs_component_add(ECS* ecs, Entity e, sid ct)
{
    ASSERT(e != INVALID_ENTITY);
    ASSERT(e < ecs->max_entity_count);

    if (SparseSet* ct_sparse_set = (SparseSet*)hash_table_get(&ecs->components_table, &ct))
    {
        return sparse_set_insert_zero(ct_sparse_set, e);
    }
    
    return false;
}

void* ecs_component_get(ECS* ecs, Entity e, sid ct)
{
    ASSERT(e != INVALID_ENTITY);
    ASSERT(e < ecs->max_entity_count);
   
    if (SparseSet* ct_sparse_set = (SparseSet*)hash_table_get(&ecs->components_table, &ct))
    {
        return sparse_set_get(ct_sparse_set, e);
    }
    
    return nullptr;
}

bool ecs_component_del(ECS* ecs, Entity e, sid ct)
{
    ASSERT(e != INVALID_ENTITY);
    ASSERT(e < ecs->max_entity_count);

    if (SparseSet* ct_sparse_set = (SparseSet*)hash_table_get(&ecs->components_table, &ct))
    {
        return sparse_set_remove(ct_sparse_set, e);
    }

    return false;
}
