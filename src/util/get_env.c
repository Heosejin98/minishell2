#include "../../include/minishell.h"

t_dictionary	get_env(char **envp)
{
	int				i;
	char			**temp;
	t_dictionary	env;

	dictionary_init(&env);
	i = 0;
	while (envp[i])
	{
		temp = ft_split(envp[i], '=');
		dictionary_add(&env, temp[0], temp[1]);
		free(temp[0]);
		free(temp[1]);
		free(temp);
		i++;
	}
	return (env);
}
