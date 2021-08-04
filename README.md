# libfledgling

A collection of utilities written in C. Intentionally minimalistic. Licensed under [CC0 1.0 Universal](https://creativecommons.org/publicdomain/zero/1.0/). If you need additional behaviour, hack it in.

## ini.h

A line-by-line `.cfg` or `.ini` file reader.

- ASCII only
- Comments must be on their own line
- Property values are strings and additional parsing is [DIY](https://en.wikipedia.org/wiki/Do_it_yourself)

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
					"Found property: \"%s\" is \"%s\" under \"%s\"\n",
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
		/* Cast entry to a pointer of its type and then deref it */
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

## FAQ

### What's up with the coding style?

It's inspired by [Plan 9](https://github.com/plan9foundation/plan9) and encourages simplicity. But if you don't like it, change it.

### Who is this library for?

Myself. The aim is to take commonly reused code and simplify it for future projects and study.

### Why are there no include guards?

When headers in C don't include other headers and define only constants and declarations, conflicts don't happen. If you need include guards, add them.

### Will you ever add *feature* to *x*?

If I have a need for it, maybe. Otherwise, probably not. Implementations are intentionally naive to allow for easier modification and extension.
