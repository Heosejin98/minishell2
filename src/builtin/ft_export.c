/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seheo <seheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 12:13:07 by seheo             #+#    #+#             */
/*   Updated: 2023/01/06 12:17:14 by seheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	print_env_export(void)
{
	t_dictionary_node	*tmp;

	tmp = g_system_var.env.head;
	while (tmp)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		if (tmp->key)
		{
			ft_putstr_fd(tmp->key, STDOUT_FILENO);
			if (tmp->value)
			{
				ft_putstr_fd("=", STDOUT_FILENO);
				ft_putendl_fd(tmp->value, STDOUT_FILENO);
			}
			tmp = tmp->link;
		}
	}
}

static void	add_env_export(char *env)
{
	char	**tmp;

	tmp = ft_split(env, '=');
	if (dictionary_search(g_system_var.env, tmp[0]))
		dictionary_delete(&g_system_var.env, tmp[0]);
	if (tmp[1])
		dictionary_add(&g_system_var.env, tmp[0], tmp[1]);
	else
		dictionary_add(&g_system_var.env, tmp[0], ft_strdup(""));
	free(tmp);
}

static int	check_valid_arg(char *arg)
{
	if (*arg == '=')
	{
		ft_putstr_fd("minish: export: \'", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putendl_fd("\': not a avalid identifier", STDERR_FILENO);
		return (0);
	}
	return (1);
}

void	ft_export(char **cmds)
{
	int	i;

	if (!check_valid_opt(cmds, 0, "export [-] [name[=value] ...]"))
		return ;
	if (!cmds[1])
	{
		print_env_export();
		g_system_var.status = 0;
		return ;
	}
	i = 1;
	while (cmds[i])
	{
		if (check_valid_arg(cmds[i]))
			add_env_export(cmds[i]);
		i++;
	}
	g_system_var.status = 0;
}
