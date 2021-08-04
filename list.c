#include <stdlib.h>
#include "list.h"

List
listalloc(int capacity, int growth)
{
	List ret;

	ret.entries = malloc(sizeof(void*) * capacity);

	if (ret.entries) {
		int i;

		ret.capacity = capacity;
		ret.growth = growth;
		ret.count = 0;

		for (i = 0; i < ret.capacity; i++)
			ret.entries[i] = NULL;
	} else {
		ret.capacity = 0;
		ret.growth = growth;
		ret.count = 0;
	}

	return ret;
}

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
		int r;
		int newcapacity;
		void **newentries;

		r = list->count % list->growth;
		newcapacity = list->count;

		if (r != 0)
			newcapacity += list->growth - r;

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

List
listcopy(List other)
{
	List ret;

	ret.entries = malloc(sizeof(void*) * other.capacity);

	if (ret.entries) {
		int i;

		ret.capacity = other.capacity;
		ret.growth = other.growth;
		ret.count = other.count;

		for (i = 0; i < ret.capacity; i++)
			ret.entries[i] = other.entries[i];
	} else {
		ret.capacity = 0;
		ret.growth = 0;
		ret.count = 0;
	}

	return ret;
}

void
listfree(List *list)
{
	list->capacity = 0;
	list->growth = 0;
	list->count = 0;

	if (list->entries) {
		free(list->entries);
		list->entries = NULL;
	}
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
