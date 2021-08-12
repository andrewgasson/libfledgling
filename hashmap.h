typedef struct KeyValue KeyValue;
typedef struct HashList HashList;
typedef struct HashMap HashMap;

struct KeyValue {
	char *key;
	void *value;
};

struct HashList {
	int hash;
	LinkedList list; /* LinkedList of KeyValue */
};

struct HashMap {
	LinkedList hashlist; /* LinkedList of HashList */
};

int hashmapalloc(HashMap*);
void hashmapclear(HashMap*);
int hashmapcontains(HashMap*, char*);
HashMap hashmapcopy(HashMap*);
void hashmapfree(HashMap*);
void *hashmapget(HashMap*, char*);
List hashmapitems(HashMap*);
List hashmapkeys(HashMap*);
void hashmapremove(HashMap*, char*);
int hashmapset(HashMap*, char*, void*);
List hashmapvalues(HashMap*);
