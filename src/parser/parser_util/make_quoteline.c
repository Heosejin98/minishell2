/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_quoteline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seheo <seheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 12:13:44 by seheo             #+#    #+#             */
/*   Updated: 2023/01/11 00:55:06 by seheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	*remove_quote(char *s, char c)
{
	char	*result;
	int		i;
	int		j;
	int		cnt;

	i = 0;
	cnt = 0;
	while (s[i])
	{
		if (s[i] == c)
			cnt++;
		i++;
	}
	result = (char *)malloc((ft_strlen(s) - cnt + 1) * sizeof(char *));
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != c)
			result[j++] = s[i];
		i++;
	}
	result[j] = 0;
	return (result);
}

int	find_env(char *s)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	while (s[i])
	{
		if (s[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

void	make_single_quote(char *s, t_lst *list)
{
	char	*node;

	node = remove_quote(s, '\'');
	insert_node(list, l_size(list), node);
	free(node);
}

char	*loop_convert(char *s)
{
	char	*env_convert;
	char	*temp;

	env_convert = convert_env(s);
	while (find_env(env_convert))
	{
		temp = env_convert;
		env_convert = convert_env(env_convert);
		free(temp);
	}
	return (env_convert);
}

void	make_quoteline(t_lst *list, char *s)
{
	char	*env_convert;
	char	*node;

	if (ft_strchr("\"", s[0]))
	{
		env_convert = loop_convert(s);
		if (ft_strncmp("(null)", env_convert, 6) == 0)
		{	
			node = remove_quote(s, '\"');
			insert_node(list, l_size(list), node);
		}
		else
		{
			node = remove_quote(env_convert, '\"');
			insert_node(list, l_size(list), node);
		}
		free(env_convert);
		free(node);
	}
	else if (ft_strchr("\'", s[0]))
		make_single_quote(s, list);
}
