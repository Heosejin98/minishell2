/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link_list.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seheo <seheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 12:15:28 by seheo             #+#    #+#             */
/*   Updated: 2023/01/06 12:15:28 by seheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINK_LIST_H
# define LINK_LIST_H

# include "minishell.h"

typedef struct s_lst
{
	char			*data;
	struct s_lst	*next;
}	t_lst;

void	insert_node(t_lst *node, const int index, char *data);
void	delete_node(t_lst *node, const int index);
int		search(t_lst *node, const char *val);
char	*l_data(t_lst *node, const int index);
int		l_size(t_lst *node);
void	print_ll(t_lst *node);
#endif
