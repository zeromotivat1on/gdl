#include "pch.h"
#include "include/gdl.h"

void test_window();
void test_workq();
void test_sparse_set();
void test_hash_table();
void test_sid();

int main()
{
    //test_window();
    //test_workq();
    //test_sparse_set();
    test_hash_table();
    test_sid();
    
    return 0;
}

// Window

void test_window()
{
    input_tables_init();
    
    WindowInfo winfo = STRUCT_ZERO(WindowInfo);
    winfo.title = "GDL Window";
    winfo.width = 1280;
    winfo.height = 720;
    winfo.x = 400;
    winfo.y = 100;

    Window* win = (Window*)alloca(WINDOW_ALLOC_SIZE);
    memset(win, 0, WINDOW_ALLOC_SIZE);

    if (!window_init(win, &winfo))
    {
        return;
    }
    
    while(window_active(win))
    {
        window_update(win);

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

        thread_sleep(33);
    }
}

// Workq

hcritsec g_crit_section = nullptr;
volatile s32 g_callback_call_count = 0;
volatile s32 g_thread_add_count = 0;

void test_workq_callback(const Workq* wq, void* data)
{
    critical_section_try_enter(g_crit_section);
    msg_log("Thread (%u) workq callback with data (%s)", thread_curr_id(), (const char*)data);
    critical_section_leave(g_crit_section);
    
    atomic_increment(&g_callback_call_count);
}

u32 test_workq_thread_process(void* data)
{
    Workq* wq = (Workq*)data;
    ASSERT(wq);

    while(true)
    {
        if (!workq_process(wq))
        {
            workq_wait(wq, WAIT_INFINITE);
        }
    }

    return 0;
}

u32 test_workq_thread_add(void* data)
{
    Workq* wq = (Workq*)data;
    ASSERT(wq);

    while(workq_active(wq))
    {
        workq_add(wq, "String Producer", test_workq_callback);
        atomic_increment(&g_thread_add_count);
        thread_sleep(1);
    }

    return 0;
}

void test_workq()
{
    msg_log("Thread (%u) workq setup", thread_curr_id());

    g_crit_section = ::operator new(CRITICAL_SECTION_ALLOC_SIZE);
    critical_section_init(g_crit_section, 0);
    
    Workq wq = workq_create(semaphore_create(0, 5));

    workq_add(&wq, "String A1", test_workq_callback);
    workq_add(&wq, "String A2", test_workq_callback);
    workq_add(&wq, "String A3", test_workq_callback);
    workq_add(&wq, "String A4", test_workq_callback);
    workq_add(&wq, "String A5", test_workq_callback);
    workq_add(&wq, "String A6", test_workq_callback);
    workq_add(&wq, "String A7", test_workq_callback);
    workq_add(&wq, "String A8", test_workq_callback);
    workq_add(&wq, "String A9", test_workq_callback);

    thread_create(test_workq_thread_add, &wq, THREAD_CREATE_IMMEDIATE);
    thread_sleep(100);
    
    thread_create(test_workq_thread_process, &wq, THREAD_CREATE_IMMEDIATE);
    thread_create(test_workq_thread_process, &wq, THREAD_CREATE_IMMEDIATE);
    thread_create(test_workq_thread_process, &wq, THREAD_CREATE_IMMEDIATE);
    thread_create(test_workq_thread_process, &wq, THREAD_CREATE_IMMEDIATE);
    thread_create(test_workq_thread_process, &wq, THREAD_CREATE_IMMEDIATE);

    while(workq_active(&wq)) {}

    critical_section_delete(g_crit_section);
    
    msg_log("Workq entries done %d out of (%d + 9) = %d", g_callback_call_count, g_thread_add_count, g_thread_add_count + 9);
}

// SparseSet

void test_sparse_set()
{
    const u64 size = 20 * sizeof(u64);
    void* mem = alloca(size);
    Arena arena = arena_create(mem, size);
    
    SparseSet ss;
    sparse_set_init(&ss, &arena, 10, 10, sizeof(u64));

    for (s32 i = 0; i < 10; ++i)
    {
        const u64 val = i + 10;
        sparse_set_insert(&ss, i, &val);
    }

    for (s32 i = 0; i < 10; ++i)
    {
        if (u64* item = (u64*)sparse_set_get(&ss, i))
        {
            msg_log("Sparse set item (%u) at index (%u)\n", *item, i);
        }
    }

    msg_log("Removing some items from sparse set\n");
    sparse_set_remove(&ss, 0);
    sparse_set_remove(&ss, 1);
    sparse_set_remove(&ss, 2);

    for (s32 i = 0; i < 10; ++i)
    {
        if (u64* item = (u64*)sparse_set_get(&ss, i))
        {
            msg_log("Sparse set item (%u) at index (%u)\n", *item, i);
        }
    }

    msg_log("Adding some items to sparse set\n");
    const u64 val_to_add = 12345;
    sparse_set_insert(&ss, 0, &val_to_add);
    sparse_set_insert_zero(&ss, 1);
    sparse_set_insert_zero(&ss, 2);
    
    for (s32 i = 0; i < 10; ++i)
    {
        if (u64* item = (u64*)sparse_set_get(&ss, i))
        {
            msg_log("Sparse set item (%u) at index (%u)\n", *item, i);
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
    Arena arena = arena_create(mem, size);

    HashTable ht;
    hash_table_init(&ht, &arena, item_count, key_size, val_size, (hash_table_hash_func)hash_pcg32);
    msg_log("Hash table load factor = %.3f", hash_table_load_factor(&ht));
    
    const u64 val = 1;
    const u32 key = 12345;
    
    hash_table_insert(&ht, &key, &val);
    msg_log("Hash table key-value (%u, %u)", key, *(u64*)hash_table_get(&ht, &key));
    msg_log("Hash table load factor = %.3f", hash_table_load_factor(&ht));
    
    hash_table_remove(&ht, &key);
    msg_log("Hash table remove at (%u)", key);
    msg_log("Hash table has value at (%u) = %d", key, hash_table_get(&ht, &key) != nullptr);
    msg_log("Hash table load factor = %.3f", hash_table_load_factor(&ht));
}

// sid

void test_sid()
{
    const u32 sid_count = 1024;
    const u32 sid_size = 64;
    const u64 size = sid_count * (sid_size + sizeof(u64) + sizeof(sid));
    
    void* mem = alloca(size);
    Arena arena = arena_create(mem, size);
    
    sid_init(&arena, sid_count, sid_size);

    const sid test_sid = SID("TransformComponent");
    msg_log("Sid hash = %u, value = %s", test_sid, sid_str(test_sid));
    msg_log("Sid table load factor = %.3f", hash_table_load_factor(&g_sid_table));

    const sid test_sid_same_1 = SID("TransformComponent1");
    const sid test_sid_same_2 = SID("TransformComponent2");
    const sid test_sid_same_3 = SID("TransformComponent3");
    msg_log("Sid hash = %u, value = %s", test_sid_same_1, sid_str(test_sid_same_1));
    msg_log("Sid hash = %u, value = %s", test_sid_same_2, sid_str(test_sid_same_2));
    msg_log("Sid hash = %u, value = %s", test_sid_same_3, sid_str(test_sid_same_3));
    msg_log("Sid table load factor = %.3f", hash_table_load_factor(&g_sid_table));
}
