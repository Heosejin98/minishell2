/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dictionary.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seheo <seheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 12:15:19 by seheo             #+#    #+#             */
/*   Updated: 2023/01/06 12:15:19 by seheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DICTIONARY_H
# define DICTIONARY_H

# include "minishell.h"

/* dictionary */
void				dictionary_show(t_dictionary dic);
int					dictionary_add(t_dictionary *head, char *key, char *value);
void				*dictionary_search(t_dictionary head, char *key);
int					dictionary_delete(t_dictionary *head, char *key);
void				dictionary_init(t_dictionary *head);
void				dictionary_destroy(t_dictionary *head);

/* dictionary_util */
void				dic_del_util(t_dictionary_node *ptr, t_dictionary *head);
t_dictionary_node	*dic_add_util(t_dictionary_node *temp,
						char *key, char *value);
t_dictionary_node	*dic_add_util2(t_dictionary_node *temp,
						char *key, char *value);	
#endif