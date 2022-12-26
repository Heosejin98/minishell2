#include "../../include/minishell.h"

static void	print_env_export(void)
{
	t_dictionary_node	*tmp;

	tmp = g_system_var.env.head;
	while (!tmp)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		if (tmp->key)
		{
			ft_putstr_fd(tmp->key, STDOUT_FILENO);
			if (tmp->value)
			{
				ft_putstr_fd("=", STDOUT_FILENO);
				ft_putendl_fd(tmp->value, STDOUT_FILENO);
			}
			tmp = tmp->link;
		}
	}
}

static void	add_env_export(char *env)
{
	char	**tmp;

	tmp = ft_split(env, '=');
	if (dictionary_search(g_system_var.env, tmp[0]))
		dictionary_delete(&g_system_var.env, tmp[0]);
	if (tmp[1])
		dictionary_add(&g_system_var.env, tmp[0], tmp[1]);
	else
		dictionary_add(&g_system_var.env, tmp[0], ft_strdup(""));
	free(tmp);
}

void	ft_export(char **cmds)
{
	int	i;

	if (!cmds[1])
	{
		print_env_export();
		return ;
	}
	i = 1;
	while (cmds[i])
	{
		//no option
		add_env_export(cmds[i]);
		i++;
	}
}