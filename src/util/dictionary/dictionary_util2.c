#include "../../../include/minishell.h"

static char	*ft_str_envjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (s1 == 0 || s2 == 0)
		return (0);
	i = 0;
	j = 0;
	str = (char *)ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 2, sizeof(char));
	if (str == 0)
		return (0);
	while (s1[i])
	{
		str[i] = (char)s1[i];
		i++;
	}
	str[i++] = '=';
	while (s2[j])
	{
		str[i + j] = (char)s2[j];
		j++;
	}
	str[i+j] = 0;
	return (str);
}


char **make_envp(t_dictionary head)
{
	t_dictionary_node	*temp;
	char				**envp;
	int					i;
	char				*str;
	
	envp = (char **)malloc(head.count * sizeof(char **));
	temp = head.head;
	i = 0;
	while (temp != NULL)
	{
		if (temp->key == NULL)
		{
			temp = temp->link;
			continue;
		}
		str = ft_str_envjoin(temp->key, temp->value);
		if (!str)
			envp[i] = ft_strdup("");
		else
			envp[i] = str;
		temp = temp->link;
		i++;
	}
	envp[i] = 0;
	return (envp);
}