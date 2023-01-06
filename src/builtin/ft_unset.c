/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seheo <seheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 12:13:16 by seheo             #+#    #+#             */
/*   Updated: 2023/01/06 12:17:20 by seheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_unset(char **cmds)
{
	int		i;

	i = 1;
	while (cmds[i])
	{
		if (is_option(cmds[i]))
		{
			perror_opt(cmds[0], abstract_opt(cmds[i]), "unset [-] [name ...]");
			return ;
		}
		if (dictionary_search(g_system_var.env, cmds[i]))
			dictionary_delete(&g_system_var.env, cmds[i]);
		i++;
	}
	g_system_var.status = 0;
}
