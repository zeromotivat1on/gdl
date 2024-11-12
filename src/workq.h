#pragma once

#include "thread.h"

#define WORK_QUEUE_MAX_ENTRIES      256
#define WORK_QUEUE_MAX_WAIT_TIME    SEMAPHORE_MAX_WAIT_TIME

typedef void (*WorkqCallback)(const struct Workq*, void*);

struct WorkqEntry
{
    WorkqCallback   callback;
    void*           data;
};

// Circular FIFO work queue with synced entry addition and process.
// Supports multiple producers multiple consumers thread model.
struct Workq
{
    hsemaphore      semaphore;
    WorkqEntry      entries[WORK_QUEUE_MAX_ENTRIES];
    volatile u32    entry_to_add;
    volatile u32    entry_to_process;
    volatile u32    added_entry_count;
    volatile u32    processed_entry_count;
};

Workq   workq_create(void* semaphore);
bool    workq_active(Workq* wq);
void    workq_add(Workq* wq, void* data, WorkqCallback callback);
bool    workq_process(Workq* wq);
void    workq_wait(Workq* wq, u32 ms);
