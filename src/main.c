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

void	do_exit(void) //삭제 필수
{
	system("leaks minishell");
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	atexit(do_exit); //삭제 필수
	init_system_var(envp);
	tcsetattr(STDIN_FILENO, TCSANOW, &g_system_var.nodisplay_set);
	minishell_start();
	tcsetattr(STDIN_FILENO, TCSANOW, &g_system_var.display_set);
}
