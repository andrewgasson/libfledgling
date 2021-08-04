#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "ini.h"

static void trim(char*);

int iniopen(Ini *ini, char *filepath)
{
	ini->file = fopen(filepath, "r");
	memset(ini->section, '\0', IniStringSize);
	memset(ini->key, '\0', IniStringSize);
	memset(ini->value, '\0', IniStringSize);
	return ini->file != NULL;
}

void iniclose(Ini *ini)
{
	memset(ini->section, '\0', IniStringSize);
	memset(ini->key, '\0', IniStringSize);
	memset(ini->value, '\0', IniStringSize);
	fclose(ini->file);
}

/* Return IniEof, IniSection, or IniProperty. Skips comments and empty lines. */
int ininext(Ini *ini)
{
	int eof;
	int bufferlen;
	char buffer[IniStringSize];

	memset(ini->key, '\0', IniStringSize);
	memset(ini->value, '\0', IniStringSize);

parsebegin:
	eof = fgets(buffer, IniStringSize, ini->file) == NULL;

	if (eof)
		return IniEof;

	trim(buffer);

	if (isspace(buffer[0]) || buffer[0] == '#' || buffer[0] == ';')
		goto parsebegin;
	
	bufferlen = strnlen(buffer, IniStringSize);

	if (buffer[0] == '[') {
		int i;

		memset(ini->section, '\0', IniStringSize);

		for (i = 1; i < bufferlen; i++) {
			if (buffer[i] == ']')
				break;
			else
				ini->section[i - 1] = buffer[i];
		}

		trim(ini->section);
		return IniSection;
	} else {
		int i;
		int j;

		for (i = 0; i < bufferlen; i++) {
			if (buffer[i] == '=')
				break;
			else
				ini->key[i] = buffer[i];
		}

		trim(ini->key);
		i++;
		j = 0;

		for (; i < bufferlen; i++) {
			ini->value[j] = buffer[i];
			j++;
		}

		trim(ini->value);
		return IniProperty;
	}
}

static void trim(char *str)
{
	int i;
	int len;
	int start;
	int end;

	len = strlen(str);
	start = 0;
	end = 0;

	for (i = 0; i < len; i++) {
		if (!isspace(str[i])) {
			start = i;
			end = i;
			break;
		}
	}

	for (; i < len; i++) {
		if (!isspace(str[i]))
			end = i;
	}

	if (end < len)
		end++;

	for (i = 0; i < (end - start); i++)
		str[i] = str[i + start];

	for (i = (end - start); i < len; i++)
		str[i] = '\0';
}
