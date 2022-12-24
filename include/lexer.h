/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seheo <seheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 16:46:11 by seheo             #+#    #+#             */
/*   Updated: 2022/12/24 18:44:57 by seheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

typedef struct s_lexer_info
{
	size_t	i;
	size_t	j;
	int		index;
    int		flag;
}	t_lexer_info;

char	**lexer(char const *s);

#endif
