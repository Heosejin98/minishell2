#include "../../include/minishell.h"

void	ft_pwd(void)
{
	char	*wd;

	wd = getcwd(NULL, 0);
	if (!wd)
	{
		//print error
		g_system_var.status = 2;
		return ;
	}
	printf("%s\n", wd);
	free(wd);
}