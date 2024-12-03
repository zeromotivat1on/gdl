#pragma once

#include "sid.h"
#include "hash_table.h"

typedef u32 Entity;
typedef void(*entity_iterate_callback)(struct Ecs* ecs, Entity e);

inline constexpr Entity INVALID_ENTITY = (Entity)INDEX_NONE;

struct Arena;

struct Ecs
{
    Entity*     entities;
    Entity*     free_entities;

    Hash_Table   components_table;   // sid to SparseSet

    u32         entity_count;
    u32         max_entity_count;
    u32         free_entity_count;
};

void    ecs_init(Ecs* ecs, Arena* arena, u32 max_entities, u16 max_component_type_count);
Entity  ecs_entity_new(Ecs* ecs);
void    ecs_entity_del(Ecs* ecs, Entity e);
void    ecs_entity_iterate(Ecs* ecs, const sid* cts, u8 cts_count, entity_iterate_callback callback);
void    ecs_component_reg(Ecs* ecs, Arena* arena, sid ct, u16 ct_size);
bool    ecs_component_add(Ecs* ecs, Entity e, sid ct);
void*   ecs_component_get(Ecs* ecs, Entity e, sid ct);
bool    ecs_component_del(Ecs* ecs, Entity e, sid ct);

#define ecs_component_reg_struct(ecs, arena, ct)    ecs_component_reg(ecs, arena, SID(MACRO_STRING(ct)), sizeof(ct))
#define ecs_component_add_struct(ecs, e, ct)        ecs_component_add(ecs, e, SID(MACRO_STRING(ct)))
#define ecs_component_get_struct(ecs, e, ct)        (ct*)ecs_component_get(ecs, e, SID(MACRO_STRING(ct)))
