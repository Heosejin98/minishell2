#include "../../include/minishell.h"

void	ft_env(char **cmds)
{
	t_dictionary_node	*node;

	if (!check_valid_opt(cmds, 0, "env [-]"))
		return ;
	node = g_system_var.env.head;
	while (node)
	{
		printf("%s=%s\n", node->key, node->value);
		node = node->link;
	}
}
