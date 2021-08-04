# libfledgling
A collection of utilities written in C. Intentionally minimalistic. Licensed under `CC0-1.0`. If you need additional behaviour, hack it in.

## ini.h
A line-by-line `.cfg` or `.ini` file reader.

- ASCII only
- Comments must be on their own line
- Property values are strings and additional parsing is DIY

### Example
```C
#include <stdio.h>
#include "ini.h"

int 
main(void)
{
	Ini inifile;

	if (iniopen(&inifile, "test.ini")) {
		int initype;

		while ((initype = ininext(&inifile)) != IniEof) {
			if (initype == IniSection) {
				printf(
					"Found section: \"%s\"\n",
					inifile.section);
			} else {
				printf(
					"Found property: \"%s\" is \"%s\" from \"%s\"\n",
					inifile.key,
					inifile.value,
					inifile.section);
			}
		}

		iniclose(&inifile);
	}

	return 0;
}
```

## list.h
A generic array list data structure.

### Example
```C
#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int 
main(void)
{
	int i;
	List list;
	int *data0;
	int *data1;
	int *data2;

	/* List uses void pointers, so give it allocated data or globals */
	data0 = malloc(sizeof(*data0));
	data1 = malloc(sizeof(*data1));
	data2 = malloc(sizeof(*data2));
	*data0 = 16;
	*data1 = 32;
	*data2 = 64;

	/* On failure, values are zero'd and entries is NULL */
	list = listalloc(2, 2);

	if (!list.entries) {
		printf("Allocation failed\n");
		return 0;
	}

	listappend(&list, data0);
	listappend(&list, data1);
	listappend(&list, data2);

	for (i = 0; i < list.count; i++) {
		/* To retrieve data, cast to pointer of its type, then deref */
		printf("Entry #%d is %d\n", i, *(int*)list.entries[i]);
	}

	/* Always remove data from the list before freeing it */
	listremove(&list, listindex(list, data0));
	listremove(&list, listindex(list, data1));
	listremove(&list, listindex(list, data2));
	free(data2);
	free(data1);
	free(data0);

	return 0;
}
```
