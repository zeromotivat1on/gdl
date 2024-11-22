#pragma once

#include "sid.h"
#include "hash_table.h"

typedef u32 Entity;
typedef void(*ecs_entity_iterate_callback)(struct ECS* ecs, Entity e);

inline constexpr Entity INVALID_ENTITY = (Entity)INDEX_NONE;

struct Arena;

struct ECS
{
    Entity*     entities;
    Entity*     free_entities;

    HashTable   components_table;   // sid to SparseSet

    u32         entity_count;
    u32         max_entity_count;
    u32         free_entity_count;
};

// NOTE: Maybe store components in hash tables with keys as string == component type name?
// ecs_component_register(ecs, sid(component_name), component_size);
//#define ecs_component_struct(ecs, e, type) (type*)ecs_component_get(ecs, e, MACRO_STRING(type));
//CameraComponent/auto* camera = ecs_component_struct(ecs, entity, CameraComponent);

void    ecs_init(ECS* ecs, Arena* arena, u32 max_entities, u16 max_component_type_count);
Entity  ecs_entity_new(ECS* ecs);
void    ecs_entity_del(ECS* ecs, Entity e);
void    ecs_entity_iterate(ECS* ecs, sid* cts, u8 cts_count, ecs_entity_iterate_callback callback);
void    ecs_component_reg(ECS* ecs, Arena* arena, sid ct, u16 ct_size);
bool    ecs_component_add(ECS* ecs, Entity e, sid ct);
void*   ecs_component_get(ECS* ecs, Entity e, sid ct);
bool    ecs_component_del(ECS* ecs, Entity e, sid ct);

#define ecs_component_reg_struct(ecs, arena, ct) ecs_component_reg(ecs, arena, SID(MACRO_STRING(ct)), sizeof(ct))
#define ecs_component_add_struct(ecs, e, ct)    ecs_component_add(ecs, e, SID(MACRO_STRING(ct)))
#define ecs_component_get_struct(ecs, e, ct)    (ct*)ecs_component_get(ecs, e, SID(MACRO_STRING(ct)))

// Create debug cube entity with default transform.
Entity ecs_entity_new_debug_cube(ECS* ecs);
