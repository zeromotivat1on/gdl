#include "pch.h"
#include "include/gdl.h"
#include <stdio.h>
#include <malloc.h>

void test_window();
void test_workq();
void test_sparse_set();
void test_hash_table();
void test_sid();
void test_ecs();

int main()
{
    //test_window();
    test_workq();
    //test_sparse_set();
    //test_hash_table();
    //test_sid();
    //test_ecs();
    
    return 0;
}

// Window

void test_window()
{
    init_input_tables();
    
    Window_Info winfo = STRUCT_ZERO(Window_Info);
    winfo.title = "GDL Window";
    winfo.width = 1280;
    winfo.height = 720;
    winfo.x = 400;
    winfo.y = 100;

    Window* win = (Window*)alloca(WINDOW_ALLOC_SIZE);
    memset(win, 0, WINDOW_ALLOC_SIZE);

    if (!init_window(win, &winfo))
    {
        return;
    }
    
    while(is_window_active(win))
    {
        update_window(win);

        for (s16 key = 0; key < KEY_COUNT; ++key)
        {
            if (key_pressed(win, key))
            {
                printf("Key pressed: %s\n", key_name(key));
            }
        }

        for (s16 button = 0; button < MOUSE_BUTTON_COUNT; ++button)
        {
            if (mouse_pressed(win, button))
            {
                printf("Mouse button pressed: %d\n", button);
            }
        }

        sleep_thread(33);
    }
}

// Workq

critical_section_handle g_crit_section = nullptr;
volatile s32 g_callback_call_count = 0;
volatile s32 g_thread_add_count = 0;

void test_workq_callback(const Work_Queue* wq, void* data)
{
    try_enter_critical_section(g_crit_section);
    msg_log("Thread (%u) workq callback with data (%s)", current_thread_id(), (const char*)data);
    leave_critical_section(g_crit_section);
    
    atomic_increment(&g_callback_call_count);
}

u32 test_workq_thread_process(void* data)
{
    Work_Queue* wq = (Work_Queue*)data;
    ASSERT(wq);

    while(true)
    {
        if (!wq->process())
        {
            wq->wait(WAIT_INFINITE);
        }
    }

    return 0;
}

u32 test_workq_thread_add(void* data)
{
    Work_Queue* wq = (Work_Queue*)data;
    ASSERT(wq);

    while(wq->active())
    {
        wq->add("String Producer", test_workq_callback);
        atomic_increment(&g_thread_add_count);
        sleep_thread(1);
    }

    return 0;
}

void test_workq()
{
    msg_log("Thread (%u) Work_Queue setup", current_thread_id());

    g_crit_section = ::operator new(CRITICAL_SECTION_ALLOC_SIZE);
    init_critical_section(g_crit_section, 0);
    
    Work_Queue wq;
    wq.init(create_semaphore(0, 5));

    wq.add("String A1", test_workq_callback);
    wq.add("String A2", test_workq_callback);
    wq.add("String A3", test_workq_callback);
    wq.add("String A4", test_workq_callback);
    wq.add("String A5", test_workq_callback);
    wq.add("String A6", test_workq_callback);
    wq.add("String A7", test_workq_callback);
    wq.add("String A8", test_workq_callback);
    wq.add("String A9", test_workq_callback);

    //create_thread(test_workq_thread_add, &wq, THREAD_CREATE_IMMEDIATE);
    //sleep_thread(100);
    
    create_thread(test_workq_thread_process, &wq, THREAD_CREATE_IMMEDIATE);
    create_thread(test_workq_thread_process, &wq, THREAD_CREATE_IMMEDIATE);
    //create_thread(test_workq_thread_process, &wq, THREAD_CREATE_IMMEDIATE);
    //create_thread(test_workq_thread_process, &wq, THREAD_CREATE_IMMEDIATE);
    //create_thread(test_workq_thread_process, &wq, THREAD_CREATE_IMMEDIATE);

    while(wq.active()) {}

    delete_critical_section(g_crit_section);
    
    msg_log("Work_Queue entries done %d out of (%d + 9) = %d", g_callback_call_count, g_thread_add_count, g_thread_add_count + 9);
}

// Sparse_Set

void test_sparse_set()
{
    const u64 size = 20 * sizeof(u64);
    void* mem = alloca(size);

    Arena arena;
    arena.init(mem, size);
    
    Sparse_Set ss;
    ss.init(&arena, 10, 10, sizeof(u64));

    for (s32 i = 0; i < 10; ++i)
    {
        const u64 val = i + 10;
        ss.add(i, &val);
    }

    for (s32 i = 0; i < 10; ++i)
    {
        if (u64* item = (u64*)ss.get(i))
        {
            msg_log("Sparse set item (%u) at index (%u)", *item, i);
        }
    }

    msg_log("Removing some items from sparse set");
    ss.remove(0);
    ss.remove(1);
    ss.remove(2);

    for (s32 i = 0; i < 10; ++i)
    {
        if (u64* item = (u64*)ss.get(i))
        {
            msg_log("Sparse set item (%u) at index (%u)", *item, i);
        }
    }

    msg_log("Adding some items to sparse set");
    const u64 val_to_add = 12345;
    ss.add(0, &val_to_add);
    ss.add_zero(1);
    ss.add_zero(2);
    
    for (s32 i = 0; i < 10; ++i)
    {
        if (u64* item = (u64*)ss.get(i))
        {
            msg_log("Sparse set item (%u) at index (%u)", *item, i);
        }
    }
}

// HashTable

void test_hash_table()
{
    const u32 item_count = 1000;
    const u32 key_size = 4;
    const u32 val_size = sizeof(u64);
    const u64 size = (item_count * key_size) + (item_count * val_size) + (item_count * sizeof(u64));
    void* mem = alloca(size);

    Arena arena;
    arena.init(mem, size);

    Hash_Table ht;
    ht.init(&arena, item_count, key_size, val_size, (Hash_Table::Hash_Func*)hash_pcg32);
    msg_log("Hash table load factor = %.3f", ht.load_factor());
    
    const u64 val = 1;
    const u32 key = 12345;
    
    ht.add(&key, &val);
    msg_log("Hash table key-value (%u, %u)", key, *(u64*)ht.find(&key));
    msg_log("Hash table load factor = %.3f", ht.load_factor());
    
    ht.remove(&key);
    msg_log("Hash table remove at (%u)", key);
    msg_log("Hash table has value at (%u) = %d", key, ht.find(&key) != nullptr);
    msg_log("Hash table load factor = %.3f", ht.load_factor());
}

// sid

void test_sid()
{
    const u32 sid_count = 1024;
    const u32 sid_size = 64;
    const u64 size = sid_count * (sid_size + sizeof(u64) + sizeof(sid));
    
    void* mem = alloca(size);
    Arena arena;
    arena.init(mem, size);
    
    init_sid(&arena, sid_count, sid_size);

    const sid test_sid = SID("TransformComponent");
    msg_log("Sid hash = %u, value = %s", test_sid, string_from_sid(test_sid));
    msg_log("Sid table load factor = %.3f", g_sid_table.load_factor());

    const sid test_sid_same_1 = SID("TransformComponent1");
    const sid test_sid_same_2 = SID("TransformComponent2");
    const sid test_sid_same_3 = SID("TransformComponent3");
    msg_log("Sid hash = %u, value = %s", test_sid_same_1, string_from_sid(test_sid_same_1));
    msg_log("Sid hash = %u, value = %s", test_sid_same_2, string_from_sid(test_sid_same_2));
    msg_log("Sid hash = %u, value = %s", test_sid_same_3, string_from_sid(test_sid_same_3));
    msg_log("Sid table load factor = %.3f", g_sid_table.load_factor());
}

// ecs

void test_ecs()
{
    const u64 size = KB(512);
    
    void* mem = alloca(size);
    Arena arena;
    arena.init(mem, size);

    init_sid(&arena, 32, 64);
    
    Ecs ecs;
    ecs.init(&arena, 100, 8);

    ecs.register_component(&arena, SID("vec2"), sizeof(vec2));
    // ^^^ function version ^^^ // vvv macro version vvv
    register_component_struct(&ecs, &arena, vec2);
    
    const Entity e0 = ecs.new_entity();
    ecs.add_component(e0, SID("vec2"));

    vec2* e0vec2 = (vec2*)ecs.get_component(e0, SID("vec2"));
    // ^^^ function version ^^^ // vvv macro version vvv
    e0vec2 = get_component_struct(&ecs, e0, vec2);
    
    e0vec2->x = 10.12f;
    e0vec2->y = 20.96f;

    msg_log("Ecs entity (%u) component (%s) = (%.2f, %.2f)", e0, "vec2", e0vec2->x, e0vec2->y);

    // NOTE: now if item in sparse set is removed, dense item data is zeroed, maybe come up with a better solution?
    ecs.delete_entity(e0);
    msg_log("Deleted entity (%u)", e0);
    // return nullptr
    //e0vec2 = (vec2*)ecs_component_get(&ecs, e0, SID("vec2"));
    msg_log("Ecs entity (%u) component (%s) = (%.2f, %.2f)", e0, "vec2", e0vec2->x, e0vec2->y);
}
