#ifndef DICTIONARY_H
# define DICTIONARY_H

# include "minishell.h"

/* dictionary */
void				dictionary_show(t_dictionary dic);
int					dictionary_add(t_dictionary *head, char *key, void *value);
void				*dictionary_search(t_dictionary head, char *key);
int					dictionary_delete(t_dictionary *head, char *key);
void				dictionary_init(t_dictionary *head);
void				dictionary_destroy(t_dictionary *head);

/* dictionary_util */
void				dic_del_util(t_dictionary_node *ptr, t_dictionary *head);
t_dictionary_node	*dic_add_util(t_dictionary_node *temp,
						char *key, void *value);
t_dictionary_node	*dic_add_util2(t_dictionary_node *temp,
						char *key, void *value);	
#endif