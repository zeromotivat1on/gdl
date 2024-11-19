#include "pch.h"
#include "include/gdl.h"

void test_window();
void test_workq();
void test_sparse_set();

int main()
{
    //test_window();
    // test_workq();
    test_sparse_set();
    
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
            printf("Sparse set item (%u) at index (%u)\n", *item, i);
        }
    }

    printf("Removing some items from sparse set\n");
    sparse_set_remove(&ss, 0);
    sparse_set_remove(&ss, 1);
    sparse_set_remove(&ss, 2);

    for (s32 i = 0; i < 10; ++i)
    {
        if (u64* item = (u64*)sparse_set_get(&ss, i))
        {
            printf("Sparse set item (%u) at index (%u)\n", *item, i);
        }
    }

    printf("Adding some items to sparse set\n");
    const u64 val_to_add = 12345;
    sparse_set_insert(&ss, 0, &val_to_add);
    sparse_set_insert_zero(&ss, 1);
    sparse_set_insert_zero(&ss, 2);
    
    for (s32 i = 0; i < 10; ++i)
    {
        if (u64* item = (u64*)sparse_set_get(&ss, i))
        {
            printf("Sparse set item (%u) at index (%u)\n", *item, i);
        }
    }
}
