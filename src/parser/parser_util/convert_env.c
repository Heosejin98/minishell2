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
	env_idx->start_idx = 0;
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
	char	*temp;
	char	*temp_substr;

	temp = result;
	temp_substr = ft_substr(s, env_idx.end_idx, env_idx.str_end_idx);
	result = ft_strjoin(result, temp_substr);
	free(temp_substr);
	free(temp);
	return (result);
}

static void	free_temp(char *temp, char *temp_substr, char *env_v)
{
	free(temp_substr);
	free(temp);
	free(env_v);
}

char	*convert_env(const char *s)
{
	t_env_convert_info	env_idx;
	char				*result;
	char				*env_v;
	char				*temp;
	char				*temp_substr;

	init_env_idx(s, &env_idx);
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
		return (result = ft_strdup("(null)"));
	}
	free(env_v);
	return (env_join(result, env_idx, s));
}

/*
char	*convert_env(const char *s)
{
	t_env_convert_info	env_idx;
	char				*result;
	char				*env_v;
	char				*temp;
	char				*temp_substr;

	init_env_idx(s, &env_idx);
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
		temp = result;
		temp_substr = ft_substr(s, env_idx.start_idx, ft_strlen(s));
		result = ft_strjoin(result, temp_substr);
		free_temp(temp, temp_substr, env_v);
		return (result);
	}
	free(env_v);
	return (env_join(result, env_idx, s));
}
*/
