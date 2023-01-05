#include "../../../include/minishell.h"

void	dictionary_show(t_dictionary dic)
{
	t_dictionary_node	*temp;

	temp = dic.head;
	while (temp != NULL)
	{
		ft_putendl_fd(ft_strjoin(temp->key, temp->value), 2);
		//printf("%s=\"%s\"\n", temp->key, temp->value);
		temp = temp->link;
	}
}

int	dictionary_add(t_dictionary *head, char *key, char *value)
{
	t_dictionary_node	*temp;

	temp = head->head;
	while (1)
	{
		if (head->count == 0)
		{
			head->head = dic_add_util(temp, key, value);
			break ;
		}
		else if (ft_strcmp(temp->key, key) == 0)
			return (false);
		else if (temp->link == NULL)
		{
			dic_add_util2(temp, key, value);
			break ;
		}
		else
			temp = temp->link;
	}
	head->count++;
	return (true);
}

int	dictionary_delete(t_dictionary *head, char *key)
{
	t_dictionary_node	*ptr;
	t_dictionary_node	*pre;

	pre = NULL;
	ptr = head->head;
	while (true)
	{
		if (ptr == NULL)
			return (false);
		else if (ft_strcmp(ptr->key, key) == 0)
			break ;
		ptr = ptr->link;
	}
	dic_del_util(ptr, head);
	head->count--;
	return (true);
}

void	*dictionary_search(t_dictionary head, char *key)
{
	t_dictionary_node	*temp;

	temp = head.head;
	while (1)
	{
		if (temp == NULL)
			return (NULL);
		if (ft_strcmp(temp->key, key) == 0)
			return (temp->value);
		temp = temp->link;
	}
}

void	dictionary_init(t_dictionary *head)
{
	head->count = 0;
	head->head = NULL;
}
