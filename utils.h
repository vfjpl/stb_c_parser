#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

typedef struct
{
	char* ptr;
	long size;
} string_t;

string_t util_asprintf(const char* format, ...);
string_t util_readfile(const char* filename);

#endif // UTILS_H_INCLUDED
