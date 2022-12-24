/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seheo <seheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 18:31:24 by seheo             #+#    #+#             */
/*   Updated: 2022/12/24 18:43:52 by seheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/minishell.h"

t_queue make_tokens(char **lexer)
{
    t_queue q;
	t_token buf_token;

	buf_token.next = NULL;
	init_queue(&q);
	
	int i = 0;
	int j = 0;
	while (lexer[i])
	{
		buf_token.content = lexer[i];
		if (ft_isalpha(lexer[i][0]))		
			buf_token.type = CMD;
		else if (lexer[i][0] == '-')
			buf_token.type = OPTION;
		else if (ft_strchr(lexer[i], '<'))
		{
			if (ft_strlen(lexer[i]) == 2)
			{
				buf_token.type = HERE_DOC;
				g_system_var.hd_cnt++;
				i++;
				buf_token.content = lexer[i];
			}
			else
			{
				buf_token.type = IN_RDIR;
				i++;
				buf_token.content = lexer[i];
			}
		}
		else if (ft_strchr(lexer[i], '>'))
		{
			if (ft_strlen(lexer[i]) == 2)
			{
				buf_token.type = APP_RDIR;
				i++;
				buf_token.content = lexer[i];
			}
			else
			{
				buf_token.type = OUT_RDIR;
				i++;
				buf_token.content = lexer[i];
			}
		}
		else if (lexer[i][0] == '|')
			buf_token.type = PIPE;
		enqueue(&q, buf_token);
		i++;
	}

    return q;
}