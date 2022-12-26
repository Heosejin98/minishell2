/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seheo <seheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 18:31:24 by seheo             #+#    #+#             */
/*   Updated: 2022/12/24 23:36:08 by seheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	count_row(char **strings)
{
	int	i;

	i = 0;
	while (strings[i])
		i++;
	return (i);
}

void	make_cmdline(t_token *token, const char *s)
{
	char	**new_cmdline;
	char	**ptr;
	int		i;

	ptr = token->cmdline;
	new_cmdline = (char **)malloc((count_row(token->cmdline) + 2) \
				* sizeof(char *));
	i = 0;
	while (token->cmdline[i])
	{
		if (ft_strchr(s, '$'))
			new_cmdline[i] = convert_env(token->cmdline[i]);
		else
			new_cmdline[i] = ft_strdup(token->cmdline[i]);
		free(ptr[i]);
		i++;
	}
	new_cmdline[i] = ft_strdup(s);
	new_cmdline[i + 1] = NULL;
	token->cmdline = new_cmdline;
	free(ptr[i]);
}

t_deque	make_tokens(char **lexer)
{
	t_deque	q;
	t_token	buf_token;
	int		i;

	buf_token.cmdline = ft_calloc(1, sizeof(char *));
	i = 0;
	init_deque(&q);
	while (lexer[i])
	{
		if (ft_strchr("|", lexer[i][0]))
		{
			input_back(&q, buf_token);
			buf_token.cmdline = NULL;
			buf_token.redir = NULL;
		}
		else if (ft_strchr("<>", lexer[i][0]))
		{}
		else
			make_cmdline(&buf_token, lexer[i]);
		i++;
	}
	input_back(&q, buf_token);
    return (q);
}