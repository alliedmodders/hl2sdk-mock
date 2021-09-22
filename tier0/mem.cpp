// vim: set sts=4 ts=8 sw=4 tw=99 et:
#include "tier0/dbg.h"

#include <mutex>
#include <thread>

struct alloc_entry {
    void* block;
    alloc_entry* next;
};

thread_local alloc_entry* sAllocEntries;

void*
MemAllocScratch(int size)
{
    auto entry = new alloc_entry;
    entry->block = malloc(size);
    entry->next = sAllocEntries;
    sAllocEntries = entry;
    return sAllocEntries->block;
}

void
MemFreeScratch()
{
    free(sAllocEntries->block);
    auto next = sAllocEntries->next;
    delete sAllocEntries;
    sAllocEntries = next;
}
