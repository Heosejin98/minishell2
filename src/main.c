#include "../include/minishell.h"



void	init_system_var(char **envp)
{
	g_system_var.hd_cnt = 0;
	g_system_var.status = 0;
	g_system_var.old_std_fdin = dup(STDIN_FILENO);
	g_system_var.old_std_fdout = dup(STDOUT_FILENO);
	g_system_var.env = get_env(envp);
	g_system_var.hd_flag = 0;
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	init_system_var(envp);


	minishell_start();
	//test_heredoc();
	//test_lexer();
	//test_convert_env();
	//test_make_token();
	//test_make_toke_pipe();
	//test_make_redir();
	//system("leaks minishell");
	

}
