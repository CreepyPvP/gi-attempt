#include "memory.h"

#include <stdlib.h>
#include <assert.h>

Arena scratch = {};

Arena InitializeArena()
{
    Arena arena = {};
    arena.capacity = MegaByte(4);
    arena.memory = (u8 *) malloc(arena.capacity);
    return arena;
}

TempMemory BeginTempRegion(Arena *arena)
{
    TempMemory temp = {};
    temp.arena = &scratch;
    temp.offset = scratch.offset;
    return temp;
}

void EndTempRegion(TempMemory temp)
{
    temp.arena->offset = temp.offset;
}

TempMemory ScratchAllocate()
{
    return BeginTempRegion(&scratch);
}

u8 *AllocateBytes(Arena *arena, u64 size, u64 align)
{
    u64 start = (arena->offset + align - 1) & ~(align - 1);
    u64 end = start + size;
    assert(start + size <= arena->capacity);
    arena->offset = end;
    return arena->memory + start;
}
