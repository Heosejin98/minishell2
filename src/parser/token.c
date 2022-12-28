#include "../../include/minishell.h"

int	count_row(char **strings)
{
	int	i;

	i = 0;
	while (strings[i])
		i++;
	return (i);
}

void	make_cmdline(t_lst *list, char *s)
{	
	char *env;

	
	if (ft_strchr(s, '$'))
	{
		env = convert_env(s);
		insert_node(list, l_size(list), env);
		free(env);
	}
	else
		insert_node(list, l_size(list), s);
}

void	list_to_strs(t_lst *list, t_token *buf_token)
{
	int		i;
	char	*temp;

	i = 0;
	buf_token->cmdline = (char **)malloc((l_size(list) + 1) * sizeof(char *));
	while (l_size(list) != 0)
	{
		temp = l_data(list, 0);
		if (ft_strcmp(temp, "(null)") == 0)
		{
			delete_node(list, 0);
			free(temp);
			continue ;
		}
		else
			buf_token->cmdline[i] = ft_strdup(temp);
		free(temp);
		delete_node(list, 0);
		i++;
	}
	buf_token->cmdline[i] = 0;
}

t_deque	make_tokens(char **lexer)
{
	t_token_info	t_i;

	init_token_info(&t_i);
	while (lexer[t_i.i])
	{
		if (ft_strchr("|", lexer[t_i.i][0]))
			reset_token_info(&t_i);
		else if (ft_strchr("<>", lexer[t_i.i][0]))
		{
			make_redir(t_i.q_redir, lexer, &t_i.i);
			t_i.buf_token.redir = t_i.q_redir;
			t_i.i++;
		}
		else if (ft_strchr("\"\'", lexer[t_i.i][0]))
		{
			make_quoteline(t_i.l_list, lexer[t_i.i++]);
		}
		else
			make_cmdline(t_i.l_list, lexer[t_i.i++]);
	}
	list_to_strs(t_i.l_list, &t_i.buf_token);
	t_i.buf_token.redir = t_i.q_redir;
	input_back(&t_i.result, t_i.buf_token);
	ft_free_strs(lexer);
	return (t_i.result);
}
