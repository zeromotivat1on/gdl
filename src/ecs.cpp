#include "pch.h"
#include "ecs.h"
#include "hash.h"
#include "memory.h"
#include "sparse_set.h"

static u64 ecs_hash_component_type(const void* item)
{
    return (u64)*(sid*)item;
}

void Ecs::init(Arena* arena, u32 max_entities, u16 max_component_type_count)
{
    max_entity_count = max_entities;
    
    entity_count = 0;
    entities = arena_push_array(arena, max_entities, Entity);
    memset(entities, INVALID_ENTITY, max_entities * sizeof(Entity));

    free_entity_count = 0;
    free_entities = arena_push_array(arena, max_entities, Entity);
    memset(free_entities, INVALID_ENTITY, max_entities * sizeof(Entity));

    components_table.init(arena, max_component_type_count, sizeof(sid), sizeof(Sparse_Set), ecs_hash_component_type);
}

Entity Ecs::new_entity()
{
    if (free_entity_count > 0)
    {
        const u32 last_free_idx = --free_entity_count;
        const u32 idx = free_entities[last_free_idx];
        entities[idx] = idx;
        free_entities[idx] = INVALID_ENTITY;
        return entities[idx];
    }

    const u32 idx = entity_count++;
    ASSERT(idx < max_entity_count);
    entities[idx] = idx;
    return entities[idx];
}

void Ecs::delete_entity(Entity e)
{
    ASSERT(e != INVALID_ENTITY);
    ASSERT(e < max_entity_count);

    if (entities[e] == INVALID_ENTITY)
    {
        msg_warning("[gdl]: Attempt to delete invalid entity (%d)", e);
        return;
    }

    entity_count--;
    entities[e] = INVALID_ENTITY;
    const u32 idx = free_entity_count++;
    ASSERT(idx < max_entity_count);
    free_entities[idx] = e;

    for (u32 i = 0; i < components_table.max_item_count; ++i)
    {
        if (components_table.hashes[i] == 0)
            continue;

        const sid key = *(sid*)(components_table.keys + i * components_table.key_size);
        remove_component(e, key);
    }
}

void Ecs::iterate_entities(const sid* cs, u8 count, Iterate_Callback callback) const
{
    ASSERT(count > 0);

    Sparse_Set* component_set = (Sparse_Set*)components_table.find(&cs[0]);

    if (!component_set)
    {
        msg_error("[gdl]: Failed to get component sparse set from sid (%u)", cs[0]);
        return;
    }
    
    u64 smallest_dense_count = component_set->dense_count;
    u64 smallest_set_index = 0;
    
    for (u64 i = 1; i < count; ++i)
    {
        component_set = (Sparse_Set*)components_table.find(&cs[i]);

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

    const Sparse_Set* smallest_set = (Sparse_Set*)components_table.find(&cs[smallest_set_index]);
    for (u64 i = 0; i < smallest_set->dense_count; ++i)
    {
        const Entity e = smallest_set->dense_indices[i];
        bool has_all_components = true;

        for (u64 j = 0; j < count; ++j)
        {
            if (j == smallest_set_index)
                continue;

            const Sparse_Set* other_set = (Sparse_Set*)components_table.find(&cs[j]);
            if (!other_set->has(e))
            {
                has_all_components = false;
                break;
            }
        }

        if (has_all_components)
        {
            callback(this, e);
        }
    }
}

void Ecs::register_component(Arena* arena, sid c, u16 size)
{
    Sparse_Set component_set;
    component_set.init(arena, max_entity_count, max_entity_count, size);
    components_table.add(&c, &component_set);
}

bool Ecs::add_component(Entity e, sid c)
{
    ASSERT(e != INVALID_ENTITY);
    ASSERT(e < max_entity_count);

    if (Sparse_Set* component_set = (Sparse_Set*)components_table.find(&c))
    {
        return component_set->add_zero(e);
    }
    
    return false;
}

void* Ecs::get_component(Entity e, sid c) const
{
    ASSERT(e != INVALID_ENTITY);
    ASSERT(e < max_entity_count);
   
    if (Sparse_Set* component_set = (Sparse_Set*)components_table.find(&c))
    {
        return component_set->get(e);
    }
    
    return nullptr;
}

bool Ecs::remove_component(Entity e, sid c)
{
    ASSERT(e != INVALID_ENTITY);
    ASSERT(e < max_entity_count);

    if (Sparse_Set* component_set = (Sparse_Set*)components_table.find(&c))
    {
        return component_set->remove(e);
    }

    return false;
}
