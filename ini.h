typedef struct Ini Ini;

enum {
	IniEof,
	IniSection,
	IniProperty
};

enum {
	IniStringSize = 256
};

struct Ini {
	void *file;
	char section[IniStringSize]; /* null-terminated */
	char key[IniStringSize]; /* null-terminated */
	char value[IniStringSize]; /* null-terminated */
};

int iniopen(Ini*, char*);
void iniclose(Ini*);
int ininext(Ini*);
