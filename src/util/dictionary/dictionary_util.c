/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dictionary_util.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seheo <seheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 12:14:31 by seheo             #+#    #+#             */
/*   Updated: 2023/01/06 12:14:31 by seheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	free_value_key(t_dictionary_node *ptr, t_dictionary *head, int flag)
{
	free(ptr->key);
	free(ptr->value);
	if (flag == 1)
		head->head = NULL;
}

void	dic_del_util(t_dictionary_node *ptr, t_dictionary *head)
{
	if (head->count == 1)
		free_value_key(ptr, head, 1);
	else if (ptr->link == NULL)
	{
		free_value_key(ptr, head, 0);
		ptr->prev->link = NULL;
		free(ptr);
	}
	else
	{
		if (ptr->prev == NULL)
		{
			free_value_key(ptr, head, 0);
			head->head = ptr->link;
			head->head->prev = NULL;
		}
		else
		{
			free_value_key(ptr, head, 0);
			ptr->link->prev = ptr->prev;
			ptr->prev->link = ptr->link;
		}
		free(ptr);
	}
}

t_dictionary_node	*dic_add_util(t_dictionary_node *temp, \
char *key, char *value)
{	
	temp = (t_dictionary_node *)malloc(sizeof(t_dictionary_node));
	temp->key = key;
	temp->value = value;
	temp->link = NULL;
	temp->prev = NULL;
	return (temp);
}

t_dictionary_node	*dic_add_util2(t_dictionary_node *temp, \
char *key, char *value)
{	
	temp->link = (t_dictionary_node *)malloc(sizeof(t_dictionary_node));
	if (key == NULL)
		key = ft_strdup("");
	if (value == NULL)
		value = ft_strdup("");
	temp->link->key = key;
	temp->link->value = value;
	temp->link->link = NULL;
	temp->link->prev = temp;
	return (temp);
}

void	dictionary_destroy(t_dictionary *head)
{
	t_dictionary_node	*temp;

	temp = head->head;
	while (temp != NULL)
	{
		head->head = temp->link;
		head->count--;
		free(temp->key);
		free(temp->value);
		free(temp);
		temp = head->head;
	}
}
