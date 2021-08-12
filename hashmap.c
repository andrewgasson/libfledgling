#include <stdlib.h>
#include "list.h"
#include "linkedlist.h"
#include "hashmap.h"

static int hashstring(int, char*);

HashMap
hashmapalloc(int seed)
{
	//
}

void
hashmapclear(HashMap *hashmap)
{
	//
}

int
hashmapcontains(HashMap *hashmap, char *key)
{
	//
}

HashMap
hashmapcopy(HashMap *hashmap)
{
	//
}

void
hashmapfree(HashMap *hashmap)
{
	//
}

void
*hashmapget(HashMap *hashmap, char *key)
{
	//
}

/* Return List of KeyValue */
List
hashmapitems(HashMap *hashmap)
{
	//
}

/* Return List of char* */
List
hashmapkeys(HashMap *hashmap)
{
	//
}

void
hashmapremove(HashMap *hashmap, char *key)
{
	//
}

int
hashmapset(HashMap *hashmap, char *key, void *value)
{
	//
}

/* Return List of void* */
List
hashmapvalues(HashMap *hashmap)
{
	//
}

static
int
hashstring(int seed, char *str)
{
	//
}
