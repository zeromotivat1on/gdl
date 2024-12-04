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

    Hash_Table  components_table;   // sid to Sparse_Set

    u32         entity_count;
    u32         max_entity_count;
    u32         free_entity_count;
};

void    init_ecs(Ecs* ecs, Arena* arena, u32 max_entities, u16 max_component_type_count);
Entity  new_entity(Ecs* ecs);
void    delete_entity(Ecs* ecs, Entity e);
void    iterate_entities(Ecs* ecs, const sid* cs, u8 count, entity_iterate_callback callback);
void    regtister_component(Ecs* ecs, Arena* arena, sid c, u16 size);
bool    add_component(Ecs* ecs, Entity e, sid c);
void*   get_component(Ecs* ecs, Entity e, sid c);
bool    remove_component(Ecs* ecs, Entity e, sid c);

#define register_component_struct(ecs, arena, c)    regtister_component(ecs, arena, SID(#c), sizeof(c))
#define add_component_struct(ecs, e, c)             add_component(ecs, e, SID(#c))
#define get_component_struct(ecs, e, c)             (c*)get_component(ecs, e, SID(#c))
