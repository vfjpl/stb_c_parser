#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

typedef struct
{
	long size;
	char* buf;
} string_t;

string_t util_readfile(const char* filename);

#endif // UTILS_H_INCLUDED
