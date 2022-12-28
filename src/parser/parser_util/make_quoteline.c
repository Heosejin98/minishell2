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
	result = (char *)malloc((ft_strlen(s) - cnt + 1) * sizeof(char *));
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != '\"')
			result[j++] = s[i];
		i++;
	}
	result[j] = 0;
	free(s);
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
	result = (char *)malloc((ft_strlen(s) - cnt + 1) * sizeof(char *));
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != '\'')
			result[j++] = s[i];
		i++;
	}
	result[j] = 0;
	free(s);
	return (result);
}

void	make_quoteline(t_lst *list, char *s)
{
	char	*env_convert;
	char	*node;

	if (ft_strchr("\"", s[0]))
	{
		env_convert = convert_env(s);
		if (ft_strncmp("(null)", env_convert, 6) == 0)
		{	
			node = remove_d_quote(s);
			insert_node(list, l_size(list), node);
			free(node);
		}
		else
		{
			node = remove_d_quote(env_convert);
			insert_node(list, l_size(list), node);
			free(node);
		}
	}
	else
	{
		node = remove_quote(s);
		insert_node(list, l_size(list), node);
		free(node);
	}
}
