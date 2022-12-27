#include "../include/minishell.h"


void test_make_toke_pipe()
{
	char **argv = lexer("echo $PATH \"$PATH \"\'as\'dasd\"\" | ls asd");
	t_deque buf;

	buf = make_tokens(argv);

	while (!is_empty(buf))
	{
		t_token t = output_front(&buf);
		int i = 0;
		while (t.cmdline[i])
		{
			printf("%s \n", t.cmdline[i]);
			free(t.cmdline[i]);
			i++;
		}
	}
}

void test_make_redir()
{
	t_redir_queue	q;
	t_redir 		redir;
	char 			**s;

	q.front = NULL;
	q.rear = NULL;
	q.count = 0;
	int i = 0;
	s = ft_split(">> a", ' ');
	make_redir(&q, s, &i);
	s = ft_split(">>a", ' ');
	make_redir(&q, s, &i);

	s = ft_split("<< a", ' ');
	make_redir(&q, s, &i);


	s = ft_split("<<a", ' ');
	make_redir(&q, s, &i);


	s = ft_split("<<", ' ');
	make_redir(&q, s, &i);

	while (q.count != 0)
	{
		t_redir t = dequeue_redir(&q);
		if (t.file_name[0] == '\n')
			printf("error");
		else
			printf("type - %d | file name - %s | hd_num - %d\n", t.type, t.file_name, t.hd_number);
	}
}


void test_make_token()
{
	char **argv = lexer("echo $PATH >> x >>x <<x \"$PATH \"\'as\'dasd\"\" | grep | cat >> a");
	t_deque buf;

	buf = make_tokens(argv);

	
	while (!is_empty(buf))
	{
		int i = 0;
		t_token t = output_front(&buf);
		while (t.cmdline[i])
		{
			printf("%s \n", t.cmdline[i]);
			free(t.cmdline[i]);
			i++;
		}
		while (t.redir->count != 0)
		{
			t_redir t_re = dequeue_redir(t.redir);
			if (t_re.file_name[0] == '\n')
				printf("error");
			else
				printf("type - %d | file name - %s | hd_num - %d\n", t_re.type, t_re.file_name, t_re.hd_number);
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