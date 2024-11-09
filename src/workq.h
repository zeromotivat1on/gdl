#pragma once

#define WQ_MAX_ENTRIES      256
#define WQ_MAX_WAIT_TIME    SM_MAX_WAIT_TIME

typedef void (*WqCallback)(const struct WorkQueue*, void*);

struct WqEntry
{
    WqCallback  Callback;
    void*       Data;
};

// Circular FIFO work queue with synced entry addition and process.
// Supports multiple producers multiple consumers thread model.
struct WorkQueue
{
    void*           Semaphore;
    WqEntry         Entries[WQ_MAX_ENTRIES];
    volatile u32    EntryToAdd;
    volatile u32    EntryToProcess;
    volatile u32    AddedEntryCount;
    volatile u32    ProcessedEntryCount;
};

WorkQueue   wqinit(void* semaphore);
bool        wqactive(WorkQueue* wq);
void        wqadd(WorkQueue* wq, void* data, WqCallback callback);
bool        wqprocess(WorkQueue* wq);
void        wqwait(WorkQueue* wq, u32 ms);
