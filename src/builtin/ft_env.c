#include "../../include/minishell.h"

void	ft_env(void)
{
	dictionary_show(g_system_var.env);
}