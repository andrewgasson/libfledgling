typedef struct List List;

struct List {
	int capacity;
	int growth;
	int count;
	void **entries; /* array of pointers to void pointers */
};

List listalloc(int, int);
int listappend(List*, void*);
int listcompact(List*);
List listcopy(List);
void listfree(List*);
int listgrow(List*);
int listindex(List, void*);
int listinsert(List*, int, void*);
void listremove(List*, int);
void listreverse(List*);
void listswap(List*, int, int);
int listtally(List, void*);
void listunique(List*, void*);
