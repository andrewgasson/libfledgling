typedef struct LinkedList LinkedList;

struct LinkedList {
	LinkedList *prev;
	LinkedList *next;
	void *entry;
};

int linkedlistalloc(LinkedList*);
int linkedlistappend(LinkedList*, void*);
int linkedlistcopy(LinkedList*, LinkedList);
void linkedlistfree(LinkedList*);
int linkedlistindex(LinkedList, void*);
int linkedlistinsert(LinkedList*, int, void*);
void linkedlistremove(LinkedList*, int);
void linkedlistreverse(LinkedList*);
void linkedlistswap(LinkedList*, int, int);
int linkedlisttally(LinkedList, void*);
void linkedlistunique(LinkedList*, void*);
