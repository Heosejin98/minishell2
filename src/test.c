#include "../include/minishell.h"

void	builtin_tester(void)
{
	t_token	*token = ft_calloc(1, sizeof(t_token));
	t_token	*token1 = ft_calloc(1, sizeof(t_token));

	token->cmdline = ft_split("ls -la", ' ');
	token->redir = ft_calloc(1, sizeof(t_redir_queue));

	token->redir->count = 0;
	token->next = token1;
	token->prev = NULL;

	token1->cmdline = ft_split("cat Makefile", ' ');
	token1->redir = ft_calloc(1, sizeof(t_redir_queue));
	token1->redir->count = 1;
	token1->redir->front = ft_calloc(1, sizeof(t_redir));
	token1->redir->front->file_name = ft_strdup("a");
	token1->redir->front->type = APP_REDIR;
	token1->redir->front->next = NULL;
	token1->next = NULL;

	run_token(token);
}

void	builtin_tester2(void)
{
	t_token	*token = ft_calloc(1, sizeof(t_token));

	token->cmdline = ft_split("ls -la", ' ');
	token->redir = ft_calloc(1, sizeof(t_redir));

	token->redir->count = 0;
	token->next = NULL;
	token->prev = NULL;

	run_token(token);
}

void	builtin_tester3(void)
{

	t_token	*token = ft_calloc(1, sizeof(t_token));
	t_token	*token1 = ft_calloc(1, sizeof(t_token));
	t_token *token2 = ft_calloc(1, sizeof(t_token));

	token->cmdline = ft_split("ls -la", ' ');
	token->redir = ft_calloc(1, sizeof(t_redir));

	token->redir->count = 0;
	token->next = token1;
	token->prev = NULL;

	token1->cmdline = ft_split("grep 1", ' ');
	token1->redir = ft_calloc(1, sizeof(t_redir));
	token1->redir->count = 0;
	token1->next = token2;

	token2->cmdline = ft_split("wc", ' ');	
	token2->redir = ft_calloc(1, sizeof(t_redir));
	token2->redir->count = 0;
	token2->next = NULL;

	run_token(token);
}


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
	i = 0;
	s = ft_split(">>a", ' ');
	make_redir(&q, s, &i);
	
	i = 0;
	s = ft_split("<< a", ' ');
	make_redir(&q, s, &i);
	free(s);

	i = 0;
	s = ft_split("<<a", ' ');
	make_redir(&q, s, &i);
	free(s);

	i = 0;
	s = ft_split("<<", ' ');
	make_redir(&q, s, &i);
	free(s);

	while (q.count != 0)
	{
		t_redir t = dequeue_redir(&q);
		if (t.file_name[0] == '\n')
			printf("error");
		else
			printf("type - %d | file name - %s | hd_num - %d\n", t.type, t.file_name, t.hd_number);
	}
}


void test_heredoc()
{
	char 	**argv = lexer("echo $PATH >> x >>x <<x \"$PATH \"\'as\'dasd\"\" | grep | cat << a");
	t_deque	buf;

	buf = make_tokens(argv);
}


void test_make_token()
{
	char 	**argv = lexer(">> a >> b");
	t_deque	buf;

	buf = make_tokens(argv);

	while (!is_empty(buf))
	{
		int i = 0;
		t_token t = output_front(&buf);
		while (t.cmdline[i])
		{
			printf("%s \n", t.cmdline[i]);
			i++;
		}
		
		ft_free_strs(t.cmdline);
		while (t.redir->count != 0)
		{	
			t_redir t_re = dequeue_redir(t.redir);
			if (t_re.file_name[0] == '\n')
				printf("error");
			else
				printf("type - %d | file name - %s | hd_num - %d\n", t_re.type, t_re.file_name, t_re.hd_number);
			free(t_re.file_name);
		}
		free(t.redir);
		printf("|\n");
	}

	ft_free_strs(argv);
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
