typedef struct PoolHandle PoolHandle;
typedef struct Pool Pool;

struct PoolHandle {
	int version;
	int index;
};

struct Pool {
	int capacity;
	int count;
	int lowestunreserved; /* optimisation */
	size_t sizeofentryvalue;
	int (*spawn)(void*);
	void (*despawn)(void*);
	struct {
		short reserved;
		unsigned short version;
		void *value;
	} *entries;
};

void poolclear(Pool*);
int poolcollect(List*, int, Pool*, int(*)(void*));
int poolcreate(Pool*, int, size_t, int(*)(void*), void(*)(void*));
void pooldespawn(Pool*, PoolHandle);
void pooldestroy(Pool*);
void poolforeach(Pool*, void(*)(void*));
void *poolget(Pool*, PoolHandle);
int poolhandleisvalid(Pool*, PoolHandle);
int poolspawn(PoolHandle*, Pool*);
