#include "../../include/minishell.h"

void	ft_env(char **cmd)
{
	t_dictionary_node	*node;

	//option check
	//arg check

	node = g_system_var.env.head;
	while (node)
	{
		printf("%s=%s\n", node->key, node->value);
		node = node->link;
	}
}