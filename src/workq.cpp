#include "pch.h"
#include "workq.h"
#include "thread.h"

void workq_init(Workq* wq, semaphore_handle semaphore)
{
    *wq = STRUCT_ZERO(Workq);
    wq->semaphore = semaphore;
}

bool workq_active(Workq* wq)
{
    return wq->processed_entry_count != wq->added_entry_count;
}

void workq_add(Workq* wq, void* data, workq_callback callback)
{
    const u32 entry_to_add = wq->entry_to_add;
    const u32 next_entry_to_add = (entry_to_add + 1) % ARRAY_COUNT(wq->entries);

    ASSERT(next_entry_to_add != wq->entry_to_process); // overflow

    const u32 idx = atomic_cmp_swap((volatile s32*)&wq->entry_to_add, next_entry_to_add, entry_to_add);
    if (idx == entry_to_add)
    {
        Workq_Entry& entry = wq->entries[entry_to_add];
        entry.callback = callback;
        entry.data = data;

        atomic_increment((volatile s32*)&wq->added_entry_count);
        release_semaphore(wq->semaphore, 1, nullptr);
    }
}

bool workq_process(Workq* wq)
{
    const u32 entry_to_process = wq->entry_to_process;
    if (entry_to_process == wq->entry_to_add)
    {
        return false;
    }

    const u32 next_entry_to_process = (entry_to_process + 1) % ARRAY_COUNT(wq->entries);
    const u32 idx = atomic_cmp_swap((volatile s32*)&wq->entry_to_process, next_entry_to_process, entry_to_process);
    if (idx == entry_to_process)
    {
        Workq_Entry& entry = wq->entries[entry_to_process];
        entry.callback(wq, entry.data);
        atomic_increment((volatile s32*)&wq->processed_entry_count);
    }

    return true;
}

void workq_wait(Workq* wq, u32 ms)
{
    wait_semaphore(wq->semaphore, ms);
}
