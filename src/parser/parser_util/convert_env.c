#include "../../../include/minishell.h"

static int	ft_isalp_or_num(int c)
{	
	if ((c >= '0' && c <= '9'))
		return (1);
	else if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	else
		return (0);
}

static void	init_env_idx(const char *s, t_env_convert_info *env_idx)
{	
	int	i;

	i = 0;
	env_idx->flag = -1;
	env_idx->start_idx = 0;
	while (s[i])
	{
		if (s[i++] == '$')
			env_idx->flag = 0;
	}
	if (env_idx->flag == -1)
		return ;
	while (s[env_idx->start_idx] != '$')
		env_idx->start_idx++;

	env_idx->end_idx = env_idx->start_idx + 1;
	while (ft_isalp_or_num(s[env_idx->end_idx]))
		env_idx->end_idx++;

	env_idx->str_end_idx = env_idx->end_idx;
	while (s[env_idx->str_end_idx])
		env_idx->str_end_idx++;
}

static char	*env_join(char *result, t_env_convert_info env_idx, const char *s)
{
	char	*temp_substr;
	char 	*end;

	temp_substr = ft_substr(s, env_idx.end_idx, env_idx.str_end_idx);
	end = ft_strjoin(result, temp_substr);
	free(temp_substr);
	free(result);
	return (end);
}

char	*convert_env(const char *s)
{
	t_env_convert_info	env_idx;
	char				*result;
	char				*env_v;
	char				*temp;

	init_env_idx(s, &env_idx);
	if (env_idx.flag == -1)
		return (ft_strdup(s));
	result = ft_substr(s, 0, env_idx.start_idx);
	env_v = ft_substr(s, env_idx.start_idx + 1, env_idx.end_idx);
	if (dictionary_search(g_system_var.env, env_v) != NULL)
	{
		temp = result;
		result = ft_strjoin(result, dictionary_search(g_system_var.env, env_v));
		free(temp);
	}
	else
	{
		free(result);
		free(env_v);
		return (ft_strdup("(null)"));
	}
	free(env_v);
	return (env_join(result, env_idx, s));
}
