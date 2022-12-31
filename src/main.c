#include "../include/minishell.h"

void	init_system_var(char **envp)
{
	g_system_var.hd_cnt = 0;
	g_system_var.status = 0;
	g_system_var.fdin = dup(STDIN_FILENO);
	g_system_var.fdout = dup(STDOUT_FILENO);
	g_system_var.env = get_env(envp);
	tcgetattr(STDIN_FILENO, &g_system_var.display_set);
	g_system_var.nodisplay_set = g_system_var.display_set;
	g_system_var.nodisplay_set.c_lflag &= ~(ICANON | ECHOCTL);
	g_system_var.nodisplay_set.c_cc[VMIN] = 1;
	g_system_var.nodisplay_set.c_cc[VTIME] = 0;
}

void	handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		if (rl_on_new_line() == -1)
			exit(1);
		rl_replace_line("", 1);
		rl_redisplay();
	}
}

//prompt
static void	minishell_start(void)
{
	char	*cmd_line;

	while (1)
	{
		cmd_line = readline("minishell😲 ");
		if (!cmd_line)
			exit(0);
		if (*cmd_line != 0)
			add_history(cmd_line);
		//parsing and run
		free(cmd_line);
	}
}

void	do_exit(void)
{
	//system("leaks minishell -q");
}

void	builtin_tester(void)
{
	// //ls -al | cat Makefile > a.txt
	t_token	*token = ft_calloc(1, sizeof(t_token));
	t_token	*token1 = ft_calloc(1, sizeof(t_token));

	char line[256] = "unset -a";
	token->cmdline = ft_split(line, ' ');
	 token->redir = NULL;
	// token->redir = ft_calloc(1, sizeof(t_redir));
	// token->redir->type = OUT_REDIR;
	// token->redir->file_name = ft_strdup("b.txt");
	// token->redir->hd_number = 0;
	// token->redir->next = NULL;
	token->next = NULL;
	token->prev = NULL;

	char line1[256] = "env";
	token1->cmdline = ft_split(line1, ' ');
	
	// token1->redir = NULL;
	token1->redir = ft_calloc(1, sizeof(t_redir));
	token1->redir->type = APP_REDIR;
	token1->redir->file_name = ft_strdup("a.txt");
	token1->redir->hd_number = 0;
	token1->redir->next = NULL;
	token1->next = NULL;
	token1->prev = token;

	// t_token	*token = ft_calloc(1, sizeof(t_token));
	// t_token	*token1 = ft_calloc(1, sizeof(t_token));

	// char line[256] = "cd src";
	// token->cmdline = ft_split(line, ' ');
	//  token->redir = NULL;
	// // token->redir = ft_calloc(1, sizeof(t_redir));
	// // token->redir->type = OUT_REDIR;
	// // token->redir->file_name = ft_strdup("b.txt");
	// // token->redir->hd_number = 0;
	// // token->redir->next = NULL;
	// token->next = token1;
	// token->prev = NULL;

	// char line1[256] = "pwd";
	// token1->cmdline = ft_split(line1, ' ');
	
	// token1->redir = NULL;
	// // token1->redir = ft_calloc(1, sizeof(t_redir));
	// // token1->redir->type = APP_REDIR;
	// // token1->redir->file_name = ft_strdup("a.txt");
	// // token1->redir->hd_number = 0;
	// // token1->redir->next = NULL;
	// token1->next = NULL;
	// token1->prev = token;
	run_token(token);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
	atexit(do_exit);
	init_system_var(envp);
	tcsetattr(STDIN_FILENO, TCSANOW, &g_system_var.nodisplay_set);
	builtin_tester();
    //minishell_start();
	tcsetattr(STDIN_FILENO, TCSANOW, &g_system_var.display_set);
}