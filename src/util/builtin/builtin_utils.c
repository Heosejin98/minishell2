#include "../../../include/minishell.h"

int	is_option(char *line)
{
	if (line && *line == '-' && line + 1)
		return (1);
	return (0);
}

char	abstract_opt(char *line)
{
	line++;
	while (*line && *(line + 1))
	{
		if (*line != *(line + 1))
			return (0);
		line++;
	}
	return (*line);
}

int	check_valid_opt(char **cmds, char opt, char *usage)
{
	int		i;
	char	ab_opt;

	i = 1;
	while (cmds[i])
	{
		ab_opt = abstract_opt(cmds[i]);
		if (is_option(cmds[i]) && ab_opt != opt)
		{
			perror_opt(cmds[0], ab_opt, usage);
			return (0);
		}
		i++;
	}
	return (1);
}

void	perror_opt(char *cmd, char opt, char *usage)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": -", STDERR_FILENO);
	ft_putchar_fd(opt, STDERR_FILENO);
	ft_putendl_fd(": invalid option", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": usage: ", STDERR_FILENO);
	ft_putendl_fd(usage, STDERR_FILENO);
	g_system_var.status = 2;
}

int	is_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "echo") \
	|| !ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "env") \
	|| !ft_strcmp(cmd, "export") || !ft_strcmp(cmd, "unset") \
	|| !ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}
