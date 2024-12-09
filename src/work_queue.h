#pragma once

#include "thread.h"

// Circular FIFO work queue with synced entry addition and process.
// Supports multiple producers multiple consumers thread model.
struct Work_Queue
{
    // Called after one processed entry.
    using Callback = void(const Work_Queue* wq, void* data);
    
    struct Entry
    {
        Callback*   callback;
        void*       data;
    };
    
    // Max simultaneous work queue entries to process.
    static constexpr u16 MAX_ENTRY_COUNT = 256;
    
    semaphore_handle    semaphore;
    Entry               entries[MAX_ENTRY_COUNT];
    volatile u32        entry_to_add;
    volatile u32        entry_to_process;
    volatile u32        added_entry_count;
    volatile u32        processed_entry_count;
    
    void init(semaphore_handle semaphore);
    bool active();
    void add(void* data, Callback callback);
    bool process();
    void wait(u32 ms);
};

