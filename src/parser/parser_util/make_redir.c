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
	}
	if (buf_redir->type == HERE_DOC)
	{
		buf_redir->hd_number = ++g_system_var.hd_cnt;
		redir_here_doc_file(buf_redir->file_name, buf_redir->hd_number);
	}
	*idx += 1;

}

void	redir_unlink(void)
{
	int		hd_cnt;
	char	*filename;

	hd_cnt = 0;
	while (hd_cnt <= g_system_var.hd_cnt)
	{
		filename = ft_strjoin(".here_doc", ft_itoa(hd_cnt));
		if (access(filename, F_OK) == 0)
			unlink(filename);
		free(filename);
		hd_cnt++;
	}
}

void	sig_here_doc(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_on_new_line();
		redir_unlink();
		exit(EXIT_FAILURE);
	}
}

int	check_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (WCOREFLAG | WTERMSIG(status));
}

void	ft_perror(char *err_msg1, char *err_msg2)
{
	ft_putstr_fd("minish: ", STDERR_FILENO);
	ft_putstr_fd(err_msg1, STDERR_FILENO);
	ft_putendl_fd(err_msg2, STDERR_FILENO);
}

static void	redir_here_doc_child(char *end_str, int hd_num)
{
	int		hd_fd;
	char	*line;
	char	*hd_filename;

	signal(SIGINT, SIG_DFL);
	hd_filename = ft_strjoin(".here_doc", ft_itoa(hd_num));
	hd_fd = open(hd_filename, O_CREAT | O_RDWR | O_TRUNC, 0744);
	if (hd_fd == -1)
	{
		ft_perror(hd_filename, ": No such file or directory");
		exit(EXIT_FAILURE);
	}
	line = readline("> ");
	while (line && ft_strncmp(line, end_str, ft_strlen(end_str)) != 0)
	{
		if (ft_strchr(line, '$'))
			line = convert_env(line);
		ft_putstr_fd(line, hd_fd);
		ft_putstr_fd("\n", hd_fd);
		free(line);
		line = readline("> ");
	}
	close(hd_fd);
	exit(EXIT_SUCCESS);
}


void	redir_here_doc_file(char *end_str, int hd_num)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	else if (pid == 0)
	{
		signal(SIGINT, sig_here_doc);
		redir_here_doc_child(end_str, hd_num);
		exit(EXIT_FAILURE);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &pid, 0);
		if (check_status(pid) == 130)
			exit(1);
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
			redir_here_doc_file(buf_redir.file_name, buf_redir.hd_number);
		}
		add_redir(r_que, buf_redir);
	}
	else
	{	
		is_only_redir(&buf_redir, s, idx, redir_size);
		add_redir(r_que, buf_redir);
	}
}
