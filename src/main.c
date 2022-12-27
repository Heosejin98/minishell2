#include "../include/minishell.h"

void	init_system_var(char **envp)
{
	g_system_var.hd_cnt = 0;
	g_system_var.status = 0;
	g_system_var.old_std_fdin = dup(STDIN_FILENO);
	g_system_var.old_std_fdout = dup(STDOUT_FILENO);
	g_system_var.env = get_env(envp);
}

static void	minishell_start(void)
{
	char	*cmd_line;

	while (1)
	{
		cmd_line = readline("minishell$ ");
	}
}

int	main(int argc, char **argv1, char **envp)
{
	(void)argc;
	(void)argv1;
	init_system_var(envp);

	//test_lexer();
	//test_convert_env();
	test_make_token();
	//test_make_toke_pipe();
	//system("leaks minishell");
	//test_make_redir();
   

}
