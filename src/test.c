#include "../include/minishell.h"

void test_make_token()
{
	char **argv = lexer("echo $PAT \'asdasdas\'d");
	t_deque buf;

	buf = make_tokens(argv);

	int i = 0;
	while (!is_empty(buf))
	{
		t_token t = output_front(&buf);
		while (t.cmdline[i])
		{
			printf("%s \n", t.cmdline[i]);
			free(t.cmdline[i]);
			i++;
		}
	}
}

void test_lexer()
{
	char **s = lexer("echo \"a\"b");
	int i = 0;

	while (s[i])
	{
		printf("[%d] - %s\n", i, s[i]);
		i++;
	}
	
	printf("\n");

	s = lexer("echo \"abc\"aa\"\"");
	i = 0;
	while (s[i])
	{
		printf("[%d] - %s\n", i, s[i]);
		i++;
	}

	printf("\n");
	
	s = lexer("echo \"abc\"aa\"");
	i = 0;
	while (s[i])
	{
		printf("[%d] - %s\n", i, s[i]);
		i++;
	}

	printf("\n");
	
	s = lexer("echo \"abc\"aa\"  asdasdas qweqew");
	i = 0;
	while (s[i])
	{
		printf("[%d] - %s\n", i, s[i]);
		i++;
	}

	printf("\n");
	
	s = lexer("echo \'abc\"aa\"\'  asdasdas qweqew");
	i = 0;
	while (s[i])
	{
		printf("[%d] - %s\n", i, s[i]);
		i++;
	}
}

void test_convert_env()
{
	char *dest;

	dest = convert_env("asd1 $PATH asd1");
	printf("%s\n", dest);
	free(dest);

	dest = convert_env("asd2 $PATH! asd2");
	printf("%s\n", dest);
	free(dest);

	dest = convert_env("asd3 $PATHASDSADWE asd3");
	printf("%s\n", dest);
	free(dest);
}