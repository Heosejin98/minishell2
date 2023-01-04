#include "../../include/minishell.h"

void	cmd_run(char *line)
{
	t_deque	p_token;
	t_token	buf_token;
	char	**lexer_line;
	int		i;

	lexer_line = lexer(line);
	p_token = make_tokens(lexer_line);
	if (!is_empty(p_token))
	{
		buf_token = output_front(&p_token);
		// if (buf_token.next == NULL)
		// 	run_token(&)
		// else 
		// 	run_token_pipe(&buf_token);
		run_token(&buf_token);
		ft_free_strs(buf_token.cmdline);
	}
	ft_free_strs(lexer_line);
}

void	cmd_run_tester(char *line)
{
	t_deque	p_token;
	char	**lexer_line;
	t_redir	t_re;
	int		i;
	t_token	t;

	lexer_line = lexer(line);
	p_token = make_tokens(lexer_line);
	if (g_system_var.hd_flag == 0)
	{
		while (!is_empty(p_token))
		{
			i = 0;
			t = output_front(&p_token);
			while (t.cmdline[i])
			{
				printf("%s \n", t.cmdline[i]);
				i++;
			}
			ft_free_strs(t.cmdline);
			while (t.redir->count != 0)
			{	
				t_re = dequeue_redir(t.redir);
				if (t_re.file_name[0] == '\n')
					printf("error");
				else
					printf("type - %d | file name - %s | hd_num - %d\n", \
				t_re.type, t_re.file_name, t_re.hd_number);
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
			i = 0;
			t = output_front(&p_token);
			ft_free_strs(t.cmdline);
			while (t.redir->count != 0)
			{
				t_re = dequeue_redir(t.redir);
				free(t_re.file_name);
			}
		}
		ft_free_strs(lexer_line);
	}
}

void	sig_readline(int signo)
{
	g_system_var.status = 128 + signo;
	if (signo == SIGINT)
	{
		if (waitpid(-1, NULL, WNOHANG) == (-1))
		{
			ft_putendl_fd("", STDOUT_FILENO);
			if (rl_on_new_line() == -1)
				exit(1);
			rl_replace_line("", 1);
			rl_redisplay();
		}
		else
		{
			ft_putendl_fd("", STDOUT_FILENO);
		}
	}
	return ;
}

static char	*set_read_line(void)
{
	char	*line;

	signal(SIGINT, sig_readline);
	signal(SIGQUIT, SIG_IGN);
	line = readline("🎃 minishell 🎃 ");
	if (!line)
	{
		//ft_putstr_fd("\033[1A", STDOUT_FILENO);
		//ft_putstr_fd("\033[7C", STDOUT_FILENO);
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		exit(g_system_var.status);
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
		if (cmd_line[0] == 0)
		{
			free(cmd_line);
			continue ;
		}
		if (!cmd_line)
			exit(0);
		if (*cmd_line != 0)
			add_history(cmd_line);
		cmd_run(cmd_line);
		free(cmd_line);
	}
}
