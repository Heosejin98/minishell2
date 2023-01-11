/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seheo <seheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 12:14:08 by seheo             #+#    #+#             */
/*   Updated: 2023/01/11 15:11:16 by seheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	count_words(const char *str, char c)
{
	int	i;

	i = 0;
	while (*str)
	{
		if (*str != c)
		{
			i++;
		}
		str++;
	}
	return (i);
}

char	*word_dup(const char *str, int start, \
					int finish, t_lexer_info *info)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc((finish - start + 1) * sizeof(char));
	if (!word)
		return (NULL);
	while (start < finish)
		word[i++] = str[start++];
	word[i] = '\0';
	info->index = -1;
	return (word);
}

static void	check_quotat(t_lexer_info *split_info, char const *s, char **split)
{
	char	*temp;

	temp = ft_substr(s, split_info->i, ft_strlen(s));
	split_info->index = split_info->i;
	if (s[split_info->i] == '\'')
		split_info->flag = 1;
	else if (s[split_info->i] == '\"')
		split_info->flag = 2;
	if (split[0] != NULL)
	{
		if (ft_strcmp(split[0], "export") == 0 && ft_strchr(temp, '\"'))
		{
			split_info->flag = 3;
		}
	}
	free(temp);
}

static char	**spt(char **split, char c, char const *s, t_lexer_info *info)
{
	while (info->i <= ft_strlen(s))
	{
		if (s[info->i] != c && info->index < 0)
			check_quotat(info, s, split);
		else if ((s[info->i] == c || info->i == ft_strlen(s)) \
					&& info->index >= 0 && info->flag == 0)
			split[info->j++] = word_dup(s, info->index, info->i, info);
		else if (info->flag == 1 && s[info->i] == '\'')
		{
			if (s[info->i + 1] == ' ' || s[info->i + 1] == 0)
				split[info->j++] = word_dup(s, info->index, info->i + 1, info);
			info->flag = 0;
		}
		else if (info->flag == 2 && s[info->i] == '\"')
		{
			if (s[info->i + 1] == ' ' || s[info->i + 1] == 0)
				split[info->j++] = word_dup(s, info->index, info->i + 1, info);
			info->flag = 0;
		}
		else if (info->flag == 3)
			export_lexer(split, s, info);
		info->i++;
	}
	split[info->j] = 0;
	return (split);
}

char	**lexer(char const *s)
{
	char			**split;
	t_lexer_info	*info;

	info = (t_lexer_info *)malloc(sizeof(t_lexer_info));
	info->flag = 0;
	info->i = 0;
	info->j = 0;
	info->index = -1;
	info->q_cnt = 0;
	if (!s)
		return (NULL);
	split = (char **)malloc((count_words(s, ' ') + 1) * sizeof(char *));
	split[0] = NULL;
	if (!(split))
		return (0);
	split = spt(split, ' ', s, info);
	free(info);
	return (split);
}
