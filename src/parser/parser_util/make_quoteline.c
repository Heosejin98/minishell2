#include "../../../include/minishell.h"


static char	*remove_d_quote(char *s)
{
	char	*result;
	int		i;
	int		j;
	int		cnt;

	i = 0;
	cnt = 0;

	while (s[i])
	{
		if (s[i] == '\"')
			cnt++;
		i++;
	}
	result = (char *)malloc((ft_strlen(s) - cnt) * sizeof(char *));
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != '\"')
			result[j++] = s[i];
		i++;
	}
	result[j] = 0;
	return (result);
}

static char	*remove_quote(char *s)
{
	char	*result;
	int		i;
	int		j;
	int		cnt;

	i = 0;
	cnt = 0;
	while (s[i])
	{
		if (s[i] == '\'')
			cnt++;
		i++;
	}
	result = (char *)malloc((ft_strlen(s) - cnt) * sizeof(char *));
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != '\'')
			result[j++] = s[i];
		i++;
	}
	result[j] = 0;
	return (result);
}

void	make_quoteline(t_lst *list, char *s)
{
	char	*env_convert;

	if (ft_strchr("\"", s[0]))
	{
		env_convert = convert_env(s);
		insert_node(list, l_size(list), remove_d_quote(env_convert));
		free(env_convert);
	}
	else
		insert_node(list, l_size(list), remove_quote(s));
}
