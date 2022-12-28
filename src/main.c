#include "../include/minishell.h"

void	init_system_var(char **envp)
{
	g_system_var.hd_cnt = 0;
	g_system_var.status = 0;
	g_system_var.old_std_fdin = dup(STDIN_FILENO);
	g_system_var.old_std_fdout = dup(STDOUT_FILENO);
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
	char line[256] = "echo $PATH A -n   b c dfdfksdfjl \"a\"b c";
	char **cmds = ft_split(line, ' ');
	if (!ft_strcmp(cmds[0], "cd"))
		ft_cd(cmds);
	if (!ft_strcmp(cmds[0], "env"))
		ft_env(cmds);
	if (!ft_strcmp(cmds[0], "export"))
		ft_export(cmds);
	if (!ft_strcmp(cmds[0], "pwd"))
		ft_pwd(cmds);
	if (!ft_strcmp(cmds[0], "unset"))
		ft_unset(cmds);
	if (!ft_strcmp(cmds[0], "echo"))
		ft_echo(cmds);
	if (!ft_strcmp(cmds[0], "$?"))
		printf("%d\n"); //bash: 0: command not found
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
