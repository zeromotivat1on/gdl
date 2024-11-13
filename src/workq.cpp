#include "pch.h"
#include "workq.h"
#include "thread.h"

Workq workq_create(hsemaphore semaphore)
{
    Workq wq = STRUCT_ZERO(Workq);
    wq.semaphore = semaphore;
    return wq;
}

bool workq_active(Workq* wq)
{
    return wq->processed_entry_count != wq->added_entry_count;
}

void workq_add(Workq* wq, void* data, WorkqCallback callback)
{
    const u32 entry_to_add = wq->entry_to_add;
    const u32 next_entry_to_add = (entry_to_add + 1) % ARRAY_COUNT(wq->entries);

    PANIC(next_entry_to_add == wq->entry_to_process);

    const u32 idx = atomic_cmp_swap((volatile s32*)&wq->entry_to_add, next_entry_to_add, entry_to_add);
    if (idx == entry_to_add)
    {
        WorkqEntry& entry = wq->entries[entry_to_add];
        entry.callback = callback;
        entry.data = data;

        atomic_inc((volatile s32*)&wq->processed_entry_count);
        semaphore_release(wq->semaphore, 1, nullptr);
    }
}

bool workq_process(Workq* wq)
{
    const u32 entry_to_trocess = wq->entry_to_process;
    if (entry_to_trocess == wq->entry_to_add)
    {
        return false;
    }

    const u32 next_entry_to_process = (entry_to_trocess + 1) % ARRAY_COUNT(wq->entries);
    const u32 idx = atomic_cmp_swap((volatile s32*)&wq->entry_to_process, next_entry_to_process, entry_to_trocess);
    if (idx == entry_to_trocess)
    {
        WorkqEntry& entry = wq->entries[entry_to_trocess];
        entry.callback(wq, entry.data);
        atomic_inc((volatile s32*)&wq->added_entry_count);
    }

    return true;
}

void workq_wait(Workq* wq, u32 ms)
{
    semaphore_wait(wq->semaphore, ms);
}
