#include "../../include/minishell.h"

void	ft_pwd(char **cmds)
{
	char	*wd;

	if (!check_valid_opt(cmds, 0, "pwd [-]"))
		return ;
	wd = getcwd(NULL, 0);
	if (!wd)
	{
		perror("minish: getcwd");
		exit(1);
	}
	printf("%s\n", wd);
	free(wd);
	g_system_var.status = 0;
}
