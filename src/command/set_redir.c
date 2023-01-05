#include "../../include/minishell.h"

static int	get_open_mode(enum e_redir_type type)
{
	int	oflag;

	oflag = 0;
	if (type == IN_REDIR || type == HERE_DOC)
		oflag = (O_CREAT | O_RDONLY);
	else if (type == OUT_REDIR)
		oflag = (O_CREAT | O_WRONLY | O_TRUNC);
	else if (type == APP_REDIR)
		oflag = (O_CREAT | O_WRONLY | O_APPEND);
	return (oflag);
}

void	set_in_out(t_redir *redir)
{
	int		tmp;
	int		oflag;
	char	*title;

	while (redir)
	{
		oflag = get_open_mode(redir->type);
		if (redir->type == HERE_DOC)
			title = ft_strjoin("here_doc", ft_itoa(redir->hd_number));
		else
			title = ft_strdup(redir->file_name);
		tmp = open(title, oflag, 0744);
		free(title);
		if (tmp == -1)
			minish_exit("open: ");
		if (redir->type == IN_REDIR || redir->type == HERE_DOC)
			dup2(tmp, STDIN_FILENO);
		else if (redir->type == OUT_REDIR || redir->type == APP_REDIR)
			dup2(tmp, STDOUT_FILENO);
		close(tmp);
		redir = redir->next;
	}
}

void	reset_in_out(void)
{
	dup2(g_system_var.fdin, STDIN_FILENO);
	dup2(g_system_var.fdout, STDOUT_FILENO);
}

