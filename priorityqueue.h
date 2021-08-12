typedef struct PriorityValue PriorityValue;
typedef struct PriorityQueue PriorityQueue;

struct PriorityValue {
	int priority;
	void *value;
};

struct PriorityQueue {
	int capacity;
	int growth;
	int count;
	PriorityValue **entries;
};

int prqueuecreate(PriorityQueue*, int, int);
void prqueuedestroy(PriorityQueue*);
int prqueuegrow(PriorityQueue*);
void *prqueuepeek(PriorityQueue*);
void *prqueuepop(PriorityQueue*);
int prqueuepush(PriorityQueue*, int, void*);
