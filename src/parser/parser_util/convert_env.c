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

char	*convert_env(const char *s)
{
	t_env_convert_info	env_idx;
	char				*result;
	char				*key;
	char				*temp;
	char				*t;

	init_env_idx(s, &env_idx);
	result = ft_substr(s, 0, env_idx.start_idx);
	key = ft_substr(s, env_idx.start_idx + 1, env_idx.end_idx);
	if (dictionary_search(g_system_var.env, key) != NULL)
	{
		temp = result;
		result = ft_strjoin(result, dictionary_search(g_system_var.env, key));
		free(temp);
	}
	else
	{
		temp = result;
		t = ft_substr(s, env_idx.start_idx, ft_strlen(s));
		result = ft_strjoin(result, t);
		free(t);
		free(temp);
		free(key);
		return (result);
	}
	free(key);
	temp = result;
	t = ft_substr(s, env_idx.end_idx, env_idx.str_end_idx);
	result = ft_strjoin(result, t);
	free(t);
	free(temp);
	return (result);
}
