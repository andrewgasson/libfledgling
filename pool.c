#include <assert.h>
#include <stdlib.h>
#include "list.h"
#include "pool.h"

static PoolHandle makehandle(int version, int index);

void
poolclear(Pool *pool)
{
	int i;

	assert(pool != NULL);

	for (i = 0; i < pool->capacity; i++) {
		if (pool->entries[i].reserved) {
			pool->despawn(pool->entries[i].value);
			pool->entries[i].reserved = 0;
		}
	}

	pool->count = 0;
	pool->lowestunreserved = 0;
}

int
poolcollect(List *outlist, int listgrowth, Pool *pool, int (*collect)(void *value))
{
	assert(collect != NULL);

	if (listcreate(&outlist, listgrowth, listgrowth)) {
		int i;
		int count;

		count = 0;

		for (i = 0; i < pool->capacity; i++) {
			if (pool->entries[i].reserved && collect(pool->entries[i].value)) {
				if (!listappend(&outlist, pool->entries[i].value)) {
					listdestroy(&outlist);
					return 0;
				}

				count++;
			}

			if (count == pool->count)
				break;
		}

		return 1;
	} else {
		return 0;
	}
}

int
poolcreate(Pool *pool, int capacity, size_t sizeofentryvalue, int (*spawn)(void *value), void (*despawn)(void *value))
{
	int i;

	assert(pool != NULL);
	assert(pool->entries == NULL);
	assert(capacity > 0);
	assert(spawn != NULL);
	assert(despawn != NULL);

	pool->count = 0;
	pool->lowestunreserved = 0;
	pool->sizeofentryvalue = sizeofentryvalue;
	pool->spawn = spawn;
	pool->despawn = despawn;
	pool->entries = malloc(sizeof(*pool->entries) * capacity);

	if (!pool->entries) {
		pool->capacity = 0;
		return 0;
	}
	
	for (i = 0; i < capacity; i++) {
		pool->entries[i].reserved = 0;
		pool->entries[i].version = 0;
		pool->entries[i].value = malloc(sizeofentryvalue);

		/* If malloc fails at any index, loop back and free */
		if (!pool->entries[i].value) {
			for (i - 1; i >= 0; i--)
				free(pool->entries[i].value);
			
			free(pool->entries);
			pool->entries = NULL;
			pool->capacity = 0;
			return 0;
		}
	}

	pool->capacity = capacity;
	return 1;
}

void
pooldespawn(Pool *pool, PoolHandle handle)
{
	assert(handle.index >= 0);
	assert(handle.index < pool->capacity);

	if (pool->entries[handle.index].reserved) {
		pool->count--;
		pool->entries[handle.index].reserved = 0;
		pool->despawn(pool->entries[handle.index].value);

		if (handle.index < pool->lowestunreserved)
			pool->lowestunreserved = handle.index;
	}
}

void
pooldestroy(Pool *pool)
{
	int i;

	assert(pool != NULL);
	assert(pool->entries != NULL);

	for (i = pool->capacity - 1; i >= 0; i--) {
		if (pool->entries[i].reserved)
			pool->despawn(pool->entries[i].value);

		free(pool->entries[i].value);
	}

	free(pool->entries);
	pool->entries = NULL;

	pool->capacity = 0;
	pool->count = 0;
	pool->lowestunreserved = 0;
	pool->sizeofentryvalue = 0;
	pool->spawn = NULL;
	pool->despawn = NULL;
}

void
poolforeach(Pool *pool, void (*update)(void *value))
{
	int i;
	int count;

	count = 0;

	for (i = 0; i < pool->capacity; i++) {
		if (pool->entries[i].reserved) {
			update(pool->entries[i].value);
			count++;
		}

		if (count == pool->count)
			break;
	}
}

void*
poolget(Pool *pool, PoolHandle handle)
{
	return poolhandleisvalid(pool, handle) ? pool->entries[handle.index].value : NULL;
}

int
poolhandleisvalid(Pool *pool, PoolHandle handle)
{
	/* Pool capacity is supposed to be constant, so assert for bounds check */
	assert(handle.index >= 0);
	assert(handle.index < pool->capacity);

	return pool->entries[handle.index].reserved
		&& handle.version == pool->entries[handle.index].version;
}

int
poolspawn(PoolHandle *outhandle, Pool *pool)
{
	int i;

	for (i = pool->lowestunreserved; i < pool->capacity; i++) {
		if (!pool->entries[i].reserved) {
			if (pool->spawn(pool->entries[i].value)) {
				pool->count++;
				pool->lowestunreserved = i + 1;
				pool->entries[i].reserved = 1;
				pool->entries[i].version++;
				return 1;
			} else {
				return 0;
			}
		}
	}

	return 0;
}

static
PoolHandle
makehandle(int version, int index)
{
	return (PoolHandle){ .version = version, .index = index };
}
