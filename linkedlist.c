#include <assert.h>
#include <stdlib.h>
#include "linkedlist.h"

int
linkedlistalloc(LinkedList *list)
{
	assert(list != NULL);

	list->prev = NULL;
	list->next = NULL;
	list->entry = NULL;

	return 1;
}

int
linkedlistappend(LinkedList *list, void *entry)
{
	assert(list != NULL);
	assert(entry != NULL);

	if (list->entry == NULL) {
		list->entry = entry;
		return 1;
	} else {
		LinkedList *node;

		node = list;

		while (node->next != NULL)
			node = node->next;
		
		node->next = malloc(sizeof(LinkedList));

		if (node->next) {
			node->next->prev = node;
			node->next->next = NULL;
			node->next->entry = entry;
			return 1;
		} else {
			return 0;
		}
	}
}

// TODO: Errors are a real problem. Might need to create an error library so 
// that we never have to return on malloc failure or something...
//
// Right now, this implies there's already an allocated dstlist...
int
linkedlistcopy(LinkedList *dstlist, LinkedList srclist)
{
	if (!linkedlistalloc(&dstlist)) {
		return 0;
	} else {
		LinkedList *dstnode;
		LinkedList *srcnode;

		dstnode = dstlist;
		srcnode = &srclist;

		while (srcnode) {
			if (dstlist->next == NU)

			dstlist->entry 
		}
	}
}

void
linkedlistfree(LinkedList *list)
{
	//
}

int
linkedlistindex(LinkedList list, void *entry)
{
	//
}

int
linkedlistinsert(LinkedList *list, int index, void *entry)
{
	//
}

void
linkedlistremove(LinkedList *list, int index)
{
	//
}

void
linkedlistreverse(LinkedList *list)
{
	//
}

void
linkedlistswap(LinkedList *list, int index0, int index1)
{
	//
}

int
linkedlisttally(LinkedList list, void *entry)
{
	//
}

void
linkedlistunique(LinkedList *list, void *entry)
{
	//
}
