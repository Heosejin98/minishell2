#include "../../include/minishell.h"

void	cmd_run(char *line)
{
	t_deque	p_token;
	t_token buf_token;
	char	**lexer_line;
	int 	i;

	lexer_line = lexer(line);
	p_token = make_tokens(lexer_line);

	if (!is_empty(p_token))
	{
		buf_token = output_front(&p_token);
		run_token(&buf_token);
		ft_free_strs(buf_token.cmdline);
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
	line = readline("minishell 🎃 ");
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
		cmd_line = set_read_line();
		if (!cmd_line)
			exit(0);
		if (*cmd_line != 0)
			add_history(cmd_line);
		cmd_run(cmd_line);
	}
}
