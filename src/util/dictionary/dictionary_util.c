#include "../../../include/minishell.h"

void	dic_del_util(t_dictionary_node *ptr, t_dictionary *head)
{
	if (head->count == 1)
	{
		free(ptr);
		head->head = NULL;
	}
	else if (ptr->link == NULL)
	{
		ptr->prev->link = NULL;
		free(ptr);
	}
	else
	{
		if (ptr->prev == NULL)
		{
			head->head = ptr->link;
			head->head->prev = NULL;
		}
		else
		{
			ptr->link->prev = ptr->prev;
			ptr->prev->link = ptr->link;
		}
		free(ptr);
	}
}

t_dictionary_node	*dic_add_util(t_dictionary_node *temp, \
char *key, void *value)
{	
	temp = (t_dictionary_node *)malloc(sizeof(t_dictionary_node));
	temp->key = key;
	temp->value = value;
	temp->link = NULL;
	temp->prev = NULL;
	return (temp);
}

t_dictionary_node	*dic_add_util2(t_dictionary_node *temp, \
char *key, void *value)
{	
	temp->link = (t_dictionary_node *)malloc(sizeof(t_dictionary_node));
	temp->link->key = key;
	temp->link->value = value;
	temp->link->link = NULL;
	temp->link->prev = temp;
	return (temp);
}
