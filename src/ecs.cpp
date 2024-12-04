#include "pch.h"
#include "ecs.h"
#include "hash.h"
#include "memory.h"
#include "sparse_set.h"

static u64 ecs_hash_component_type(const void* item)
{
    return (u64)*(sid*)item;
}

void init_ecs(Ecs* ecs, Arena* arena, u32 max_entities, u16 max_component_type_count)
{
    ecs->max_entity_count = max_entities;
    
    ecs->entity_count = 0;
    ecs->entities = arena_push_array(arena, max_entities, Entity);
    memset(ecs->entities, INVALID_ENTITY, max_entities * sizeof(Entity));

    ecs->free_entity_count = 0;
    ecs->free_entities = arena_push_array(arena, max_entities, Entity);
    memset(ecs->free_entities, INVALID_ENTITY, max_entities * sizeof(Entity));

    table_init(&ecs->components_table, arena, max_component_type_count, sizeof(sid), sizeof(Sparse_Set), ecs_hash_component_type);
}

Entity new_entity(Ecs* ecs)
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

void delete_entity(Ecs* ecs, Entity e)
{
    ASSERT(e != INVALID_ENTITY);
    ASSERT(e < ecs->max_entity_count);

    if (ecs->entities[e] == INVALID_ENTITY)
    {
        msg_warning("[gdl]: Attempt to delete invalid entity (%d)", e);
        return;
    }

    ecs->entity_count--;
    ecs->entities[e] = INVALID_ENTITY;
    const u32 idx = ecs->free_entity_count++;
    ASSERT(idx < ecs->max_entity_count);
    ecs->free_entities[idx] = e;

    for (u32 i = 0; i < ecs->components_table.max_item_count; ++i)
    {
        if (ecs->components_table.hashed_keys[i] == 0)
            continue;

        const sid key = *(sid*)(ecs->components_table.keys + i * ecs->components_table.key_size);
        delete_component(ecs, e, key);
    }
}

void iterate_entities(Ecs* ecs, const sid* cs, u8 count, entity_iterate_callback callback)
{
    ASSERT(count > 0);

    Sparse_Set* component_set = (Sparse_Set*)table_find(&ecs->components_table, &cs[0]);

    if (!component_set)
    {
        msg_error("[gdl]: Failed to get component sparse set from sid (%u)", cs[0]);
        return;
    }
    
    u64 smallest_dense_count = component_set->dense_count;
    u64 smallest_set_index = 0;
    
    for (u64 i = 1; i < count; ++i)
    {
        component_set = (Sparse_Set*)table_find(&ecs->components_table, &cs[i]);

        if (!component_set)
        {
            msg_error("[gdl]: Failed to get component sparse set from sid (%u)", cs[i]);
            return;
        }
        
        const u64 dense_count = component_set->dense_count;
        if (dense_count < smallest_dense_count)
        {
            smallest_set_index = i;
            smallest_dense_count = dense_count;
        }
    }

    const Sparse_Set* smallest_set = (Sparse_Set*)table_find(&ecs->components_table, &cs[smallest_set_index]);
    for (u64 i = 0; i < smallest_set->dense_count; ++i)
    {
        const Entity e = smallest_set->dense_indices[i];
        bool has_all_components = true;

        for (u64 j = 0; j < count; ++j)
        {
            if (j == smallest_set_index)
                continue;

            const Sparse_Set* other_set = (Sparse_Set*)table_find(&ecs->components_table, &cs[j]);
            if (!sparse_has(other_set, e))
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

void regtister_component(Ecs* ecs, Arena* arena, sid c, u16 size)
{
    Sparse_Set component_set;
    sparse_init(&component_set, arena, ecs->max_entity_count, ecs->max_entity_count, size);
    table_insert(&ecs->components_table, &c, &component_set);
}

bool add_component(Ecs* ecs, Entity e, sid c)
{
    ASSERT(e != INVALID_ENTITY);
    ASSERT(e < ecs->max_entity_count);

    if (Sparse_Set* component_set = (Sparse_Set*)table_find(&ecs->components_table, &c))
    {
        return sparse_insert_zero(component_set, e);
    }
    
    return false;
}

void* get_component(Ecs* ecs, Entity e, sid c)
{
    ASSERT(e != INVALID_ENTITY);
    ASSERT(e < ecs->max_entity_count);
   
    if (Sparse_Set* component_set = (Sparse_Set*)table_find(&ecs->components_table, &c))
    {
        return sparse_get(component_set, e);
    }
    
    return nullptr;
}

bool remove_component(Ecs* ecs, Entity e, sid c)
{
    ASSERT(e != INVALID_ENTITY);
    ASSERT(e < ecs->max_entity_count);

    if (Sparse_Set* component_set = (Sparse_Set*)table_find(&ecs->components_table, &c))
    {
        return sparse_remove(component_set, e);
    }

    return false;
}
