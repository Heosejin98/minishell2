#include "../../../include/minishell.h"

void	redir_here_doc_file(char *end_str, int hd_num);

static int	is_redirandfilename(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (ft_strchr("><", s[i]))
			i++;
		else
			return (i);
	}
	return (0);
}

static int	get_redir_size(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (ft_strchr("><", s[i]))
			i++;
		else
			return (i);
	}
	return (i);
}

static int	get_redir_type(char *s, int redir_size)
{
	if (redir_size == 2)
	{
		if (s[0] == '<')
			return (HERE_DOC);
		else
			return (APP_REDIR);
	}
	else if (redir_size == 1)
	{
		if (s[0] == '>')
			return (OUT_REDIR);
		else
			return (IN_REDIR);
	}
	return (IN_REDIR);
}

void	is_only_redir(t_redir *buf_redir, char **s, int *idx, int redir_size)
{
	buf_redir->type = get_redir_type(s[*idx], redir_size);
	if (s[*idx + 1] == NULL)
	{	
		buf_redir->file_name = ft_strdup("\n");
	}
	else
	{
		buf_redir->file_name = ft_strdup(s[*idx + 1]);
		*idx += 1;
	}
	if (buf_redir->type == HERE_DOC)
	{
		buf_redir->hd_number = ++g_system_var.hd_cnt;
		heredoc_file_maker(buf_redir->file_name, buf_redir->hd_number);
	}
}

void	make_redir(t_redir_queue *r_que, char **s, int *idx)
{
	char	*t_re;
	char	*t_fname;
	int		redir_size;
	t_redir	buf_redir;

	buf_redir.hd_number = 0;
	redir_size = get_redir_size(s[*idx]);
	if (is_redirandfilename(s[*idx]))
	{	
		buf_redir.type = get_redir_type(s[*idx], redir_size);
		t_fname = ft_substr(s[*idx], redir_size, ft_strlen(s[*idx]));
		buf_redir.file_name = t_fname;
		if (buf_redir.type == HERE_DOC)
		{
			buf_redir.hd_number = ++g_system_var.hd_cnt;
			heredoc_file_maker(buf_redir.file_name, buf_redir.hd_number);
		}
		add_redir(r_que, buf_redir);
	}
	else
	{	
		is_only_redir(&buf_redir, s, idx, redir_size);
		add_redir(r_que, buf_redir);
	}
}
