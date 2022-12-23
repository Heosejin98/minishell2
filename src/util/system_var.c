/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seheo <seheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 16:07:01 by seheo             #+#    #+#             */
/*   Updated: 2022/12/23 16:23:31 by seheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/struct.h"
# include "../../include/minishell.h"

static t_system_var	**_get_system_var(char *envp[], bool reset)
{
	static t_system_var	**static_sys_var;
	static_sys_var = NULL;

	if (envp == NULL && !reset)
		return (static_sys_var);
	if (reset)
	{
		static_sys_var = NULL;
		return (NULL);
	}
	static_sys_var = envp;
	return (static_sys_var);
}

void	init_system_var(char *envp[])
{
	t_system_var	**sys_var;
	sys_var = (t_system_var *)malloc(sizeof(t_system_var));


	_get_envp(envp, false);
}

t_system_var	**get_envp(void)
{
	return (_get_envp(NULL, false));
}

void	reset_envp(void)
{
	_get_envp(NULL, true);
}
