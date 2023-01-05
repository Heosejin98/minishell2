#include "../../../include/minishell.h"

void	insert_node(t_lst *head, const int index, char *data)
{
	int		k;
	t_lst	*pre_node;
	t_lst	*insert;

	insert = (t_lst *)malloc(sizeof(t_lst));
	pre_node = head;
	k = index;
	insert->data = data;
	while (k-- && pre_node != NULL)
		pre_node = pre_node->next;
	if (pre_node == NULL)
	{
		free(insert);
		return ;
	}
	insert->next = pre_node->next;
	pre_node->next = insert;
}

void	delete_node(t_lst *head, const int index)
{
	int		k;
	t_lst	*temp;
	t_lst	*garbage;

	garbage = NULL;
	temp = head;
	k = index;
	while (k-- && temp != NULL)
		temp = temp->next;
	if (temp == NULL || temp->next == NULL)
		return ;
	garbage = temp->next;
	temp->next = garbage->next;
	free(garbage);
}

int	search(t_lst *head, const char *val)
{
	int		index;
	t_lst	*temp;

	if (head->next == NULL)
		return (-1);
	index = 0;
	temp = head->next;
	while (temp->data != val)
	{
		++index;
		temp = temp->next;
		if (temp == NULL)
			return (-1);
	}
	return (index);
}

char	*l_data(t_lst *head, const int index)
{
	int		k;
	t_lst	*temp;

	if (head->next == NULL)
		return ("(null)");
	k = index;
	temp = head->next;
	while (k--)
		temp = temp->next;
	return (temp->data);
}

int	l_size(t_lst *head)
{
	t_lst	*temp;
	int		len;

	temp = head->next;
	len = 0;
	while (temp != NULL)
	{
		++len;
		temp = temp->next;
	}
	return (len);
}
