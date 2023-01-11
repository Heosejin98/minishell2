/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seheo <seheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 15:02:30 by seheo             #+#    #+#             */
/*   Updated: 2023/01/11 15:10:42 by seheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	export_lexer(char **split, char const *s, t_lexer_info *info)
{
	char	*temp;

	if (s[info->i] == '\"')
		info->q_cnt++;
	if (info->q_cnt == 2)
	{
		if (s[info->i + 1] == ' ' || s[info->i + 1] == 0)
		{
			temp = word_dup(s, info->index, info->i + 1, info);
			split[info->j++] = remove_quote(temp, '\"');
			free(temp);
		}
		info->flag = 0;
		info->q_cnt = 0;
	}
}
