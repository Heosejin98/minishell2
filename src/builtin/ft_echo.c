#include "../../include/minishell.h"

void	ft_echo(char **cmds)
{
	int	i;
	int	tag;

	i = 1;
	tag = 1;
	while (cmds[i])
	{
		if (ft_strncmp("-n", cmds[i], 3) == 0)
		{
			tag = 0;
		}
		else
		{
			ft_putstr_fd(cmds[i], STDOUT_FILENO);
			if (cmds[i + 1])
				ft_putstr_fd(" ", STDOUT_FILENO);
		}
		i++;
	}
	if (tag)
		ft_putendl_fd("", STDOUT_FILENO);
	g_system_var.status = 0;
}
