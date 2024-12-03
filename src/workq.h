#pragma once

#include "thread.h"

// Max simultaneous work queue entries to process.
inline constexpr u16 WORKQ_MAX_ENTRIES = 256;

typedef void (*workq_callback)(const struct Workq*, void*);

struct Workq_Entry
{
    workq_callback  callback;
    void*           data;
};

// Circular FIFO work queue with synced entry addition and process.
// Supports multiple producers multiple consumers thread model.
struct Workq
{
    semaphore_handle    semaphore;
    Workq_Entry         entries[WORKQ_MAX_ENTRIES];
    volatile u32        entry_to_add;
    volatile u32        entry_to_process;
    volatile u32        added_entry_count;
    volatile u32        processed_entry_count;
};

Workq   workq_create(semaphore_handle semaphore);
bool    workq_active(Workq* wq);
void    workq_add(Workq* wq, void* data, workq_callback callback);
bool    workq_process(Workq* wq);
void    workq_wait(Workq* wq, u32 ms);
