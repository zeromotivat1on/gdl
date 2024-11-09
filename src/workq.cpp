#include "pch.h"
#include "workq.h"
#include "thread.h"

WorkQueue wqinit(void* semaphore)
{
    WorkQueue wq = STRUCT_ZERO(WorkQueue);
    wq.Semaphore = semaphore;
    return wq;
}

bool wqactive(WorkQueue* wq)
{
    return wq->ProcessedEntryCount != wq->AddedEntryCount;
}

void wqadd(WorkQueue* wq, void* data, WqCallback callback)
{
    const u32 entryToAdd = wq->EntryToAdd;
    const u32 nextEntryToAdd = (entryToAdd + 1) % ARRAY_COUNT(wq->Entries);

    ASSERT(nextEntryToAdd != wq->EntryToProcess);

    const u32 idx = atmcmpswap((volatile s32*)&wq->EntryToAdd, nextEntryToAdd, entryToAdd);
    if (idx == entryToAdd)
    {
        WqEntry& entry = wq->Entries[entryToAdd];
        entry.Callback = callback;
        entry.Data = data;

        atminc((volatile s32*)&wq->ProcessedEntryCount);
        smrelease(wq->Semaphore);
    }
}

bool wqprocess(WorkQueue* wq)
{
    const u32 entryToProcess = wq->EntryToProcess;
    if (entryToProcess == wq->EntryToAdd)
    {
        return false;
    }

    const u32 nextEntryToProcess = (entryToProcess + 1) % ARRAY_COUNT(wq->Entries);
    const u32 idx = atmcmpswap((volatile s32*)&wq->EntryToProcess, nextEntryToProcess, entryToProcess);
    if (idx == entryToProcess)
    {
        WqEntry& entry = wq->Entries[entryToProcess];
        entry.Callback(wq, entry.Data);
        atminc((volatile s32*)&wq->AddedEntryCount);
    }

    return true;
}

void wqwait(WorkQueue* wq, u32 ms)
{
    smwait(wq->Semaphore, ms);
}
