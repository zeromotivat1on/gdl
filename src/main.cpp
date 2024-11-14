#include "pch.h"
#include "include/gdl.h"

void test_window();
void test_workq();

int main()
{
    //test_window();
    test_workq();

    return 0;
}

// Window

void test_window()
{
    WindowInfo winfo = STRUCT_ZERO(WindowInfo);
    winfo.title = "GDL Window";
    winfo.width = 1280;
    winfo.height = 720;
    winfo.x = 400;
    winfo.y = 100;

    void* win = ::operator new(WINDOW_ALLOC_SIZE);
    memset(win, 0, WINDOW_ALLOC_SIZE);

    if (!window_create(win, &winfo))
    {
        return;
    }

    window_key_tables_init(win);
    
    while(window_active(win))
    {
        window_update(win);

        for (s16 key = 0; key < KEY_COUNT; ++key)
        {
            if (key_pressed(win, key))
            {
                printf("Key pressed: %s\n", key_name(win, key));
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

hmutex g_mutex_msg = mutex_create(false);
volatile s32 g_callback_call_count = 0;
volatile s32 g_thread_add_count = 0;

void test_workq_callback(const Workq* wq, void* data)
{
    mutex_wait(g_mutex_msg, WAIT_INFINITE);
    msg_log("Thread (%u) workq callback with data (%s)", thread_curr_id(), (const char*)data);
    mutex_release(g_mutex_msg);
    
    atomic_inc(&g_callback_call_count);
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
        atomic_inc(&g_thread_add_count);
        thread_sleep(1);
    }

    return 0;
}

void test_workq()
{
    msg_log("Thread (%u) workq setup", thread_curr_id());

    Workq wq = workq_create(semaphore_create(0, 3));

    workq_add(&wq, "String A1", test_workq_callback);
    workq_add(&wq, "String A2", test_workq_callback);
    workq_add(&wq, "String A3", test_workq_callback);
    workq_add(&wq, "String A4", test_workq_callback);
    workq_add(&wq, "String A5", test_workq_callback);
    workq_add(&wq, "String A6", test_workq_callback);
    workq_add(&wq, "String A7", test_workq_callback);
    workq_add(&wq, "String A8", test_workq_callback);
    workq_add(&wq, "String A9", test_workq_callback);

    thread_create(test_workq_thread_add, &wq, THREAD_IMMEDIATE);
    thread_sleep(5);
    
    thread_create(test_workq_thread_process, &wq, THREAD_IMMEDIATE);
    thread_create(test_workq_thread_process, &wq, THREAD_IMMEDIATE);
    thread_create(test_workq_thread_process, &wq, THREAD_IMMEDIATE);

    while(workq_active(&wq)) {}

    msg_log("Workq entries done %d out of (%d + 9) = %d", g_callback_call_count, g_thread_add_count, g_thread_add_count + 9);
}
