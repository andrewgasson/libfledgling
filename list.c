#include <assert.h>
#include <stdlib.h>
#include "list.h"

int
listappend(List *list, void *entry)
{
	if (list->count == list->capacity) {
		if (!listgrow(list))
			return 0;
	}

	list->entries[list->count] = entry;
	list->count++;
	return 1;
}

int
listcompact(List *list)
{
	if (list->count == list->capacity) {
		return 1;
	} else {
		int remainder;
		int newcapacity;
		void **newentries;

		remainder = list->count % list->growth;
		newcapacity = list->count;

		if (remainder != 0)
			newcapacity += list->growth - remainder;

		newentries = realloc(list->entries, sizeof(void*) * newcapacity);

		if (newentries) {
			list->entries = newentries;
			list->capacity = newcapacity;
			return 1;
		} else {
			return 0;
		}
	}
}

int
listcreate(List *outlist, int capacity, int growth)
{
	assert(outlist != NULL);
	assert(outlist->entries == NULL);

	outlist->entries = malloc(sizeof(void*) * capacity);

	if (outlist->entries) {
		int i;

		outlist->capacity = capacity;
		outlist->growth = growth;
		outlist->count = 0;

		for (i = 0; i < outlist->capacity; i++)
			outlist->entries[i] = NULL;

		return 1;
	} else {
		outlist->capacity = 0;
		outlist->growth = growth;
		outlist->count = 0;
		return 0;
	}
}

int
listcopy(List *dstlist, List srclist)
{
	assert(dstlist != NULL);
	assert(dstlist->entries == NULL);

	dstlist->entries = malloc(sizeof(void*) * srclist.capacity);

	if (dstlist->entries) {
		int i;

		dstlist->capacity = srclist.capacity;
		dstlist->growth = srclist.growth;
		dstlist->count = srclist.count;

		for (i = 0; i < dstlist->capacity; i++)
			dstlist->entries[i] = srclist.entries[i];

		return 1;
	} else {
		dstlist->capacity = 0;
		dstlist->growth = 0;
		dstlist->count = 0;
		return 0;
	}
}

void
listdestroy(List *list)
{
	assert(list != NULL);
	assert(list->entries == NULL);

	list->capacity = 0;
	list->growth = 0;
	list->count = 0;

	free(list->entries);
	list->entries = NULL;
}

int
listgrow(List *list)
{
	if (list->growth > 0) {
		int newcapacity;
		void **newentries;

		newcapacity = list->capacity + list->growth;
		newentries = realloc(list->entries, sizeof(void*) * newcapacity);

		if (newentries) {
			list->entries = newentries;
			list->capacity = newcapacity;
			return 1;
		}
	}

	return 0;
}

int
listindex(List list, void *entry)
{
	int i;

	for (i = 0; i < list.count; i++) {
		if (list.entries[i] == entry)
			return i;
	}

	return -1;
}

int
listinsert(List *list, int index, void *entry)
{
	int i;

	if (list->count == list->capacity) {
		if (!listgrow(list))
			return 0;
	}

	for (i = list->count; i > index; i--)
		list->entries[i] = list->entries[i - 1];

	list->entries[index] = entry;
	list->count++;
	return 1;
}

void
listremove(List *list, int index)
{
	int i;

	if (index == -1)
		return;

	for (i = index; i < list->count - 1; i++)
		list->entries[i] = list->entries[i + 1];

	list->entries[list->count] = NULL;
	list->count--;
}

void
listreverse(List *list)
{
	if (list->count > 1) {
		int i;
		int middle;

		middle = list->count / 2;

		for (i = 0; i < middle; i++)
			listswap(list, i, list->count - 1 - i);
	}
}

void
listswap(List *list, int index0, int index1)
{
	void *store;

	store = list->entries[index0];
	list->entries[index0] = list->entries[index1];
	list->entries[index1] = store;
}

int
listtally(List list, void *entry)
{
	int i;
	int tally;

	tally = 0;

	for (i = 0; i < list.count; i++) {
		if (list.entries[i] == entry)
			tally++;
	}

	return tally;
}

void
listunique(List *list, void *entry)
{
	int start;
	int end;

	for (start = 0; start < list->count; start++) {
		if (list->entries[start] == entry)
			break;
	}

	for (end = list->count - 1; end > start; end--) {
		if (list->entries[end] == entry)
			listremove(list, end);
	}
}
