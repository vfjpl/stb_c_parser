#include "stb_c_lexer.h"
#include "utils.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

static FILE* preprocessed_fopen(const char* filename)
{
	const char* tmp_filename = tmpnam(NULL);
	string_t str = util_asprintf("cpp %s > %s", filename, tmp_filename);
	system(str.ptr);
	FILE* file = fopen(tmp_filename, "re");
	remove(tmp_filename);
	free(str.ptr);
	return file;
}

static string_t preprocess_file(const char* filename)
{
	string_t str = {0};
	FILE* file = preprocessed_fopen(filename);
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

static void print_tokens(const char* filename, bool preprocess)
{
	string_t str = preprocess ? preprocess_file(filename) : util_readfile(filename);

	char buff[4096] = {0};
	stb_lexer lexer = {0};
	stb_c_lexer_init(&lexer, str.buptrf, str.ptr + str.size, buff, sizeof(buff));

	stb_lex_location loc = {0};
	while(stb_c_lexer_get_token(&lexer))
	{
		stb_c_lexer_get_location(&lexer, lexer.where_firstchar, &loc);
		//printf("%3d:%3d : %.*s\n", loc.line_number, loc.line_offset, (int)(lexer.parse_point - lexer.where_firstchar), lexer.where_firstchar);
	}

	free(str.ptr);
}

int main(void)
{
	print_tokens("stb_c_lexer_implementation.c", false);
	print_tokens("stb_c_lexer_implementation.c", true);
	print_tokens("utils.h", false);
	print_tokens("utils.h", true);
	print_tokens("utils.c", false);
	print_tokens("utils.c", true);
	print_tokens("main.c", false);
	print_tokens("main.c", true);
	print_tokens("stb_c_lexer.h", false);
	print_tokens("stb_c_lexer.h", true);
}
