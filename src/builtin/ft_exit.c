/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seheo <seheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 12:13:00 by seheo             #+#    #+#             */
/*   Updated: 2023/01/06 12:13:01 by seheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	isdigit_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	ft_exit(char **cmds)
{
	int	code;

	if (!cmds[1])
	{
		ft_putendl_fd("exit", STDERR_FILENO);
		exit(0);
	}
	if (!isdigit_str(cmds[1]))
	{
		ft_putstr_fd("minish: exit: ", STDERR_FILENO);
		ft_putstr_fd(cmds[1], STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		exit(255);
	}
	if (cmds[2])
	{
		ft_putstr_fd("minish: exit: ", STDERR_FILENO);
		ft_putendl_fd(": too many arguments", STDERR_FILENO);
		g_system_var.status = 2;
		return ;
	}
	ft_putendl_fd("exit", STDERR_FILENO);
	code = ft_atoi(cmds[1]);
	exit(code);
}
