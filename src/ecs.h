#pragma once

#include "sid.h"
#include "hash_table.h"

using Entity = u32;

inline constexpr Entity INVALID_ENTITY = (Entity)INDEX_NONE;

struct Arena;

struct Ecs
{
    using Iterate_Callback = void(const Ecs* ecs, Entity e);    
    
    Entity*     entities;
    Entity*     free_entities;

    Hash_Table  components_table;   // sid to Sparse_Set

    u32         entity_count;
    u32         max_entity_count;
    u32         free_entity_count;

    void        init(Arena* arena, u32 max_entities, u16 max_component_type_count);
    Entity      new_entity();
    void        delete_entity(Entity e);
    void        iterate_entities(const sid* cs, u8 count, Iterate_Callback callback) const;
    void        register_component(Arena* arena, sid c, u16 size);
    bool        add_component(Entity e, sid c);
    void*       get_component(Entity e, sid c) const;
    bool        remove_component(Entity e, sid c);
};

#define register_component_struct(ecs, arena, c)    (ecs)->register_component(arena, SID(#c), sizeof(c))
#define add_component_struct(ecs, e, c)             (ecs)->add_component(e, SID(#c))
#define get_component_struct(ecs, e, c)             (c*)(ecs)->get_component(e, SID(#c))
