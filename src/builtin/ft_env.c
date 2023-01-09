/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seheo <seheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 12:12:55 by seheo             #+#    #+#             */
/*   Updated: 2023/01/06 12:12:56 by seheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_env(char **cmds)
{
	t_dictionary_node	*node;

	if (!check_valid_opt(cmds, 0, "env [-]"))
	{
		g_system_var.status = 2;
		return ;
	}
	node = g_system_var.env.head;
	while (node)
	{
		if (node->value && ft_strlen(node->value))
			printf("%s=%s\n", node->key, node->value);
		node = node->link;
	}
	g_system_var.status = 0;
}
