typedef struct Csv Csv;

enum {
	CsvStringSize = 256
};

struct Csv {
	void *file;
	int row;
	int column;
	char value[CsvStringSize]; /* null-terminated */
};

int csvopen(Csv*, char*);
void csvclose(Csv*);
int csvnextcolumn(Csv*);
int csvnextrow(Csv*);
