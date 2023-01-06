/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seheo <seheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 12:12:49 by seheo             #+#    #+#             */
/*   Updated: 2023/01/06 12:12:51 by seheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
