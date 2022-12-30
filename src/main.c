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
		free(cmd_line);
	}
}

void	do_exit(void)
{
	//system("leaks minishell");
}

void	builtin_tester(void)
{
	t_token	*token = ft_calloc(1, sizeof(t_token));
	char line[256] = "ls -l";
	token->cmdline = ft_split(line, ' ');
	
	token->redir = ft_calloc(1, sizeof(t_redir));
	token->redir->type = OUT_REDIR;
	token->redir->file_name = ft_strdup("a.txt");
	token->redir->hd_number = 0;
	token->redir->next = NULL;
	token->next = NULL;
	token->prev = NULL;
	run_token(token);
	// if (!ft_strcmp(cmds[0], "cd"))
	// 	ft_cd(cmds);
	// if (!ft_strcmp(cmds[0], "env"))
	// 	ft_env(cmds);
	// if (!ft_strcmp(cmds[0], "export"))
	// 	ft_export(cmds);
	// if (!ft_strcmp(cmds[0], "pwd"))
	// 	ft_pwd(cmds);
	// if (!ft_strcmp(cmds[0], "unset"))
	// 	ft_unset(cmds);
	// if (!ft_strcmp(cmds[0], "echo"))
	// 	ft_echo(cmds);
	// if (!ft_strcmp(cmds[0], "$?"))
	// 	printf("%d\n", g_system_var.status); //bash: 0: command not found
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
    minishell_start();
	tcsetattr(STDIN_FILENO, TCSANOW, &g_system_var.display_set);
}
