/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seheo <seheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 12:13:58 by seheo             #+#    #+#             */
/*   Updated: 2023/01/06 12:16:58 by seheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	init_token_info(t_token_info *t_info)
{
	t_info->i = 0;
	t_info->l_list = (t_lst *)malloc(sizeof(t_lst));
	t_info->l_list->next = NULL;
	t_info->q_redir = (t_redir_queue *)malloc(sizeof(t_redir_queue));
	t_info->q_redir->count = 0;
	t_info->buf_token.redir = NULL;
	t_info->buf_token.cmdline = NULL;
	t_info->buf_token.next = NULL;
	init_deque(&t_info->result);
}

void	reset_token_info(t_token_info *t_info)
{
	t_info->buf_token.redir = t_info->q_redir;
	list_to_strs(t_info->l_list, &t_info->buf_token);
	input_back(&t_info->result, t_info->buf_token);
	t_info->l_list = (t_lst *)malloc(sizeof(t_lst));
	t_info->l_list->next = NULL;
	t_info->buf_token.redir = NULL;
	t_info->buf_token.cmdline = NULL;
	t_info->buf_token.next = NULL;
	t_info->q_redir = (t_redir_queue *)malloc(sizeof(t_redir_queue));
	t_info->q_redir->count = 0;
	t_info->i++;
}

int	repeat_char(char *s, char c)
{
	int	i;
	int	repeat_flag;

	repeat_flag = 0;
	i = 1;
	while (s[i])
	{
		if (s[i] == c)
		{
			repeat_flag = 1;
			break ;
		}
		i++;
	}
	return (repeat_flag);
}

char	*opt_convert(int *flag, int i, char *temp)
{
	char	*result;

	if (*flag == 0 && i > 0 && ft_strncmp("-n", temp, 2) == 0)
	{
		if (repeat_char(temp, 'n'))
		{
			result = ft_strdup("-n");
			return (result);
		}
	}
	else if (i > 0 && flag == 0 && temp[0] != '-')
			*flag = 1;
	result = ft_strdup(temp);
	return (result);
}
