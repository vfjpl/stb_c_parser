#include "utils.h"
#include <stdlib.h>
#include <stdio.h>

string_t util_readfile(const char* filename)
{
	string_t str = {0};
	FILE* file = fopen(filename, "re");
	if(!file) return str;
	fseek(file, 0, SEEK_END);
	str.size = ftell(file);
	rewind(file);
	str.buf = (char*)malloc(str.size + 1);
	fread(str.buf, 1, str.size, file);
	str.buf[str.size] = '\0';
	fclose(file);
	return str;
}
