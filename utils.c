#include "utils.h"
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>

string_t util_asprintf(const char* format, ...)
{
	va_list args;
	va_start(args, format);
	string_t str = {0};
	str.size = vasprintf(&str.ptr, format, args);
	va_end(args);
	return str;
}

string_t util_readfile(const char* filename)
{
	string_t str = {0};
	FILE* file = fopen(filename, "re");
	if(file)
	{
		fseek(file, 0, SEEK_END);
		str.size = ftell(file);
		rewind(file);
		str.ptr = (char*)malloc(str.size + 1);
		fread(str.ptr, 1, str.size, file);
		str.ptr[str.size] = '\0';
		fclose(file);
	}
	return str;
}
