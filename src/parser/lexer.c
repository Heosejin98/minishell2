#include "../../include/minishell.h"

static int	count_words(const char *str, char c)
{
	int	i;
	int	trigger;

	i = 0;
	trigger = 0;
	while (*str)
	{
		if (*str != c && trigger == 0)
		{
			trigger = 1;
			i++;
		}
		else if (*str == c)
			trigger = 0;
		str++;
	}
	return (i);
}

static char	*word_dup(const char *str, int start, \
					int finish, t_lexer_info *info)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc((finish - start + 1) * sizeof(char));
	if (!word)
		return (NULL);
	while (start < finish)
		word[i++] = str[start++];
	word[i] = '\0';
	info->index = -1;
	return (word);
}

static void	check_quotat(t_lexer_info *split_info, char const *s)
{
	split_info->index = split_info->i;
	if (s[split_info->i] == '\'')
		split_info->flag = 1;
	else if (s[split_info->i] == '\"')
		split_info->flag = 2;
}

static char	**spt(char **split, char c, char const *s, t_lexer_info *info)
{
	while (info->i <= ft_strlen(s))
	{
		if (s[info->i] != c && info->index < 0)
			check_quotat(info, s);
		else if ((s[info->i] == c || info->i == ft_strlen(s)) \
					&& info->index >= 0 && info->flag == 0)
			split[info->j++] = word_dup(s, info->index, info->i, info);
		else if (info->flag == 1 && s[info->i] == '\'')
		{
			if (s[info->i + 1] == ' ' || s[info->i + 1] == 0)
				split[info->j++] = word_dup(s, info->index, info->i + 1, info);
			info->flag = 0;
		}
		else if (info->flag == 2 && s[info->i] == '\"')
		{
			if (s[info->i + 1] == ' ' || s[info->i + 1] == 0)
				split[info->j++] = word_dup(s, info->index, info->i + 1, info);
			info->flag = 0;
		}
		info->i++;
	}
	split[info->j] = 0;
	return (split);
}

char	**lexer(char const *s)
{
	char			**split;
	t_lexer_info	*info;

	info = (t_lexer_info *)malloc(sizeof(t_lexer_info));
	info->flag = 0;
	info->i = 0;
	info->j = 0;
	info->index = -1;
	if (!s)
		return (NULL);
	split = malloc((count_words(s, ' ') + 1) * sizeof(char *));
	if (!(split))
		return (0);
	split = spt(split, ' ', s, info);
	free(info);
	return (split);
}
