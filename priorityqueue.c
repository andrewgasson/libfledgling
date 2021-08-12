/* TODO: Completely remake! Should use sort on insertion for O(1) peeks, and O(log n) pops (moving pointers is cheap). */
#include <assert.h>
#include <stdlib.h>
#include "priorityqueue.h"

int
prqueuecreate(PriorityQueue *queue, int capacity, int growth)
{
	assert(queue != NULL);
	assert(queue->entries == NULL);
	assert(capacity >= 0 && growth >= 0);
	assert(capacity > 0 || growth > 0);

	queue->entries = malloc(sizeof(*queue->entries) * capacity);

	if (queue->entries) {
		queue->capacity = capacity;
		queue->growth = growth;
		queue->count = 0;
		return 1;
	} else {
		queue->capacity = 0;
		queue->growth = 0;
		queue->count = 0;
		return 0;
	}
}

void
prqueuedestroy(PriorityQueue *queue)
{
	assert(queue != NULL);
	assert(queue->entries != NULL);

	queue->capacity = 0;
	queue->growth = 0;
	queue->count = 0;
	free(queue->entries);
	queue->entries = NULL;
}

int
prqueuegrow(PriorityQueue *queue)
{
	//
}

void*
prqueuepeek(PriorityQueue *queue)
{
	assert(queue != NULL);
	assert(queue->entries != NULL);

	if (queue->count > 0) {
		int i;
		int toppriority;
		void *topentry;

		toppriority = queue->entries[0]->priority;
		topentry = queue->entries[0]->value;

		for (i = 1; i < queue->count; i++) {
			if (queue->entries[i]->priority > toppriority) {
				toppriority = queue->entries[i]->priority;
				topentry = queue->entries[i]->value;
			}
		}

		return topentry;
	}

	return NULL;
}

void*
prqueuepop(PriorityQueue *queue)
{
	assert(queue != NULL);
	assert(queue->entries != NULL);

	if (queue->count > 0) {
		int i;
		int topindex;
		int toppriority;
		void *topentry;

		topindex = 0;
		toppriority = queue->entries[0]->priority;
		topentry = queue->entries[0]->value;

		for (i = 1; i < queue->count; i++) {
			if (queue->entries[i]->priority > toppriority) {
				topindex = i;
				toppriority = queue->entries[i]->priority;
				topentry = queue->entries[i]->value;
			}
		}

		for (i = toppriority; i < queue->count - 1; i++)
			queue->entries[i] = queue->entries[i + 1];

		queue->entries[queue->count] = NULL;
		queue->count--;
		return topentry;
	}

	return NULL;
}

int
prqueuepush(PriorityQueue *queue, int priority, void *value)
{
	// Remember, need to allocate a new PriorityValue
}
