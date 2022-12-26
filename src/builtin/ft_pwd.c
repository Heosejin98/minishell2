#include "../../include/minishell.h"

void	ft_pwd(char **cmds)
{
	char	*wd;

	wd = getcwd(NULL, 0);
	//옵션있으면 에러
	if (!wd)
	{
		perror("minish: pwd: ");
		g_system_var.status = 2;
		return ;
	}
	printf("%s\n", wd);
	free(wd);
}