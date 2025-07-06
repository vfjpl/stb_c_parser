#include "stb_c_lexer.h"
#include "utils.h"
#include <stdlib.h>
#include <stdio.h>

static void print_tokens(const char* filename)
{
	string_t str = util_readfile(filename);

	char buff[4096] = {0};
	stb_lexer lexer = {0};
	stb_c_lexer_init(&lexer, str.buf, str.buf + str.size, buff, sizeof(buff));

	while(stb_c_lexer_get_token(&lexer))
	{
		printf("%.*s\n", (int)(lexer.parse_point - lexer.where_firstchar), lexer.where_firstchar);
	}

	free(str.buf);
}

int main(void)
{
	print_tokens("stb_c_lexer_implementation.c");
	print_tokens("utils.h");
	print_tokens("utils.c");
	print_tokens("main.c");
	print_tokens("stb_c_lexer.h");
}
