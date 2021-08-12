#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "csv.h"

int
csvopen(Csv *csv, char *filepath)
{
	csv->file = fopen(filepath, "r");
	csv->column = 0;
	csv->row = 0;
	memset(csv->value, '\0', CsvStringSize);
	return csv->file != NULL;
}

void
csvclose(Csv *csv)
{
	csv->column = 0;
	csv->row = 0;
	memset(csv->value, '\0', CsvStringSize);
	fclose(csv->file);
	csv->file = NULL;
}

int
csvnextcolumn(Csv *csv)
{
	// TODO
}

int
csvnextrow(Csv *csv)
{
	// TODO
}
