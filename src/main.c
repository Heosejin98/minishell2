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
	test = &errno;
}

void	handler(int sig)
{
	perror("num");
	if (sig == SIGINT)
	{
		ft_putendl_fd("", STDOUT_FILENO);
		if (rl_on_new_line() == -1)
			exit(1);
		rl_replace_line("", 1);
		rl_redisplay();
	}
}

//prompt
// static void	minishell_start(void)
// {
// 	char	*cmd_line;

// 	while (1)
// 	{
// 		cmd_line = readline("minishell😲 ");
// 		if (!cmd_line)
// 			exit(0);
// 		if (*cmd_line != 0)
// 			add_history(cmd_line);
// 		//parsing and run
// 		free(cmd_line);
// 	}
// 	g_system_var.hd_flag = 0;
// }

void	do_exit(void)
{
	//system("leaks minishell -q");
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	// signal(SIGINT, handler);
	// signal(SIGQUIT, SIG_IGN);
	atexit(do_exit);
	init_system_var(envp);
	tcsetattr(STDIN_FILENO, TCSANOW, &g_system_var.nodisplay_set);
	//builtin_tester3();
    minishell_start();
	tcsetattr(STDIN_FILENO, TCSANOW, &g_system_var.display_set);
}
