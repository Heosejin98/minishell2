/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seheo <seheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 12:14:44 by seheo             #+#    #+#             */
/*   Updated: 2023/01/06 12:14:44 by seheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_dictionary	get_env(char **envp)
{
	int				i;
	char			**temp;
	t_dictionary	env;

	dictionary_init(&env);
	i = 0;
	while (envp[i])
	{
		temp = ft_split(envp[i], '=');
		dictionary_add(&env, temp[0], temp[1]);
		free(temp);
		i++;
	}
	return (env);
}
