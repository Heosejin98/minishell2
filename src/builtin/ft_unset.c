#include "../../include/minishell.h"

void	ft_unset(char *key)
{
	if (dictionary_search(g_system_var.env, key))
		dictionary_delete(&g_system_var.env, key);
}