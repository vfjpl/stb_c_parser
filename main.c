#include "stb_c_lexer.h"
#include "utils.h"
#include <stdlib.h>
#include <stdio.h>

static FILE* cpreprocessed_fopen(const char* filename)
{
	const char* tmp_filename = tmpnam(NULL);
	string_t str = util_asprintf("cpp %s > %s", filename, tmp_filename);
	system(str.buf);
	FILE* file = fopen(tmp_filename, "re");
	remove(tmp_filename);
	free(str.buf);
	return file;
}

static string_t cpreprocess_file(const char* filename)
{
	string_t str = {0};
	FILE* file = cpreprocessed_fopen(filename);
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

static void print_tokens(const char* filename)
{
	string_t str = cpreprocess_file(filename);

	char buff[4096] = {0};
	stb_lexer lexer = {0};
	stb_c_lexer_init(&lexer, str.buf, str.buf + str.size, buff, sizeof(buff));

	stb_lex_location loc = {0};
	while(stb_c_lexer_get_token(&lexer))
	{
		stb_c_lexer_get_location(&lexer, lexer.where_firstchar, &loc);
		printf("%3d:%3d : %.*s\n", loc.line_number, loc.line_offset, (int)(lexer.parse_point - lexer.where_firstchar), lexer.where_firstchar);
	}

	free(str.buf);
}

int main(void)
{
	print_tokens("stb_c_lexer_implementation.c");
	putchar('\n');
	print_tokens("utils.h");
	putchar('\n');
	print_tokens("utils.c");
	putchar('\n');
	print_tokens("main.c");
	putchar('\n');
	print_tokens("stb_c_lexer.h");
}
