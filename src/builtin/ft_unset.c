#include "../../include/minishell.h"

void	ft_unset(char *key)
{
	dictionary_delete(&g_system_var.env, key);
}