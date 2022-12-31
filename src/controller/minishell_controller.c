#include "../../include/minishell.h"

void	cmd_run(char *line)
{
	t_deque	p_token;
	t_token buf_token;
	char	**lexer_line;
	int 	i;

	lexer_line = lexer(line);
	p_token = make_tokens(lexer_line);

	while (!is_empty(p_token))
	{
		i = 0;
		buf_token = output_front(&p_token);
		// buf_token.cmdline 한 파이프 단위의 cmdlin
		ft_free_strs(buf_token.cmdline);
		// buf_token.redir 한 파이프의 리다이렉션
		// redir_que로 되어있다
		// 큐에서 꺼내서 버퍼에 담아서 사용
		// file_name은 malloc 해줘서 free 해야댐
		// while (buf_token.redir->count != 0)
		// {
		// 	t_redir buf_redir = dequeue_redir(buf_token.redir);
		//  free(buf_redir.file_name);
		// }
	}
	free(lexer_line);
}


void	cmd_run_tester(char *line)
{
	t_deque	p_token;
	char	**lexer_line;

	lexer_line = lexer(line);
	p_token = make_tokens(lexer_line);

	if (g_system_var.hd_flag == 0)
	{
		while (!is_empty(p_token))
		{
			int i = 0;
			t_token t = output_front(&p_token);
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
			printf("|\n");
		}
		ft_free_strs(lexer_line);
	}
	else
	{
		while (!is_empty(p_token))
		{
			int i = 0;
			t_token t = output_front(&p_token);
			ft_free_strs(t.cmdline);
			while (t.redir->count != 0)
			{	
				t_redir t_re = dequeue_redir(t.redir);
				free(t_re.file_name);
			}
		}
		ft_free_strs(lexer_line);
	}
}


void	sig_readline(int signo)
{
	if (signo == SIGINT)
	{
		g_system_var.status = EXIT_FAILURE;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
	}
	return ;
}

static char	*set_read_line()
{
	char	*line;

	signal(SIGINT, sig_readline);
	signal(SIGQUIT, SIG_IGN);
	line = readline("minishell$ ");
	if (!line)
	{
		ft_putstr_fd("\033[1A", STDOUT_FILENO);
		ft_putstr_fd("\033[7C", STDOUT_FILENO);
		ft_putstr_fd(" exit\n", STDOUT_FILENO);
	}
	return (line);
}

void	minishell_start(void)
{
	char	*cmd_line;

	while (1)
	{	
		g_system_var.hd_flag = 0;
		signal(SIGINT, sig_readline);
		signal(SIGQUIT, SIG_IGN);
		cmd_line = set_read_line();
		cmd_run_tester(cmd_line);
	}
}
