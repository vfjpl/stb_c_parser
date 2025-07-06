#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

typedef struct
{
	char* buf;
	long size;
} string_t;

string_t util_asprintf(const char* format, ...);
string_t util_readfile(const char* filename);

#endif // UTILS_H_INCLUDED
