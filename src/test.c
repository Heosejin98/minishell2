#include "../include/minishell.h"

void make_token_test()
{
	char **argv = ft_split("asd \"1\"\"1\" \"1\" qwe123", ' ');
	t_deque buf;

	buf = make_tokens(argv);

	int i = 0;
	while (!is_empty(buf))
	{
		t_token t = output_front(&buf);
		while (t.cmdline[i])
		{
			printf("%s \n", t.cmdline[i]);
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

	dest = convert_env("asd $PATH asd");
	printf("%s\n", dest);
	free(dest);

	dest = convert_env("asd $PATH! asd");
	printf("%s\n", dest);
	free(dest);

	dest = convert_env("asd $PATHASDSADWE asd");
	printf("%s\n", dest);
	free(dest);
}