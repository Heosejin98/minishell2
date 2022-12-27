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
	if (ft_strchr(s, '$'))
		insert_node(list, l_size(list), convert_env(s));
	else
		insert_node(list, l_size(list), s);
}

void	list_to_strs(t_lst *list, t_token *buf_token)
{
	int		i;
	char	*temp;

	i = 0;
	buf_token->cmdline = (char **)malloc(l_size(list) * sizeof(char *));
	while (l_size(list) != 0)
	{
		temp = l_data(list, 0);
		if (ft_strcmp(temp, "(null)") == 0)
		{
			delete_node(list, 0);
			continue ;
		}
		else
			buf_token->cmdline[i] = ft_strdup(temp);
		delete_node(list, 0);
		i++;
	}
	buf_token->cmdline[i] = 0;
}



t_deque	make_tokens(char **lexer)
{
	t_deque			result;
	t_token			buf_token;
	t_lst			*l_list;
	t_redir_queue	*q_redir;
	int				i;

	i = 0;
	l_list = (t_lst *)malloc(sizeof(t_lst));
	q_redir = (t_redir_queue *)malloc(sizeof(t_redir_queue));
	buf_token.redir = NULL;
	buf_token.cmdline = NULL;
	buf_token.next = NULL;
	buf_token.prev = NULL;
	init_deque(&result);
	while (lexer[i])
	{
		if (ft_strchr("|", lexer[i][0]))
		{
			buf_token.redir = q_redir;
			list_to_strs(l_list, &buf_token);
			input_back(&result, buf_token);
			l_list = (t_lst *)malloc(sizeof(t_lst));
			buf_token.redir = NULL;
			buf_token.cmdline = NULL;
			buf_token.next = NULL;
			buf_token.prev = NULL;
			q_redir = (t_redir_queue *)malloc(sizeof(t_redir_queue));
			q_redir->count = 0;
			i++;
		}
		else if (ft_strchr("<>", lexer[i][0]))
		{
			make_redir(q_redir, lexer, &i);
			buf_token.redir = q_redir;
			i++;
		}
		else if (ft_strchr("\"\'", lexer[i][0]))
			make_quoteline(l_list, lexer[i++]);
		else
			make_cmdline(l_list, lexer[i++]);
	}
	list_to_strs(l_list, &buf_token);
	input_back(&result, buf_token);
	ft_free_strs(lexer);
    return (result);
}
