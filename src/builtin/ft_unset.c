#include "../../include/minishell.h"

void	ft_unset(char **cmds)
{
	int	i;
	char	opt;

	i = 1;
	while (cmds[i])
	{
		if (is_option(cmds[i]))
		{
			perror_opt(cmds[0], cmds[i], "unset [name ...]");
			return ;
		}
		if (dictionary_search(g_system_var.env, cmds[i]))
			dictionary_delete(&g_system_var.env, cmds[i]);
		i++;
	}
}