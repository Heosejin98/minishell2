/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seheo <seheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 18:40:17 by seheo             #+#    #+#             */
/*   Updated: 2022/12/24 23:12:05 by seheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

typedef struct s_env_convert_info
{
	int	start_idx;
	int	end_idx;
	int	str_end_idx;
}	t_env_convert_info;

t_deque		make_tokens(char **lexer);
void		make_cmdline(t_token *token, const char *s);
char		*convert_env(const char *s);
#endif