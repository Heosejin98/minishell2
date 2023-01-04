#include "../../include/minishell.h"

void	set_in_out(t_redir *redir)
{
	int	tmp;
	int	oflag;
	char	*title;

	while (redir)
	{
		oflag = 0;
		if (redir->type == IN_REDIR || redir->type == HERE_DOC)
			oflag = (O_CREAT | O_RDONLY);
		else if (redir->type == OUT_REDIR)
			oflag = (O_CREAT | O_WRONLY | O_TRUNC);
		else if (redir->type == APP_REDIR)
			oflag = (O_CREAT | O_WRONLY | O_APPEND);
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
		free(redir->file_name);
		close(tmp);
		redir = redir->next;
	}
}

void	reset_in_out(void)
{
	dup2(g_system_var.fdin, STDIN_FILENO);
	dup2(g_system_var.fdout, STDOUT_FILENO);
}

void	unlink_heredoc(t_redir_queue *redir)
{ //작동 중  시시그그널널 받받아아도  삭삭제제
	t_redir	tmp;
	char	*title;

	if (redir->count == 0)
		return ;
	tmp = dequeue_redir(redir);
	if (tmp.type != HERE_DOC)
		return ;
	title = ft_strjoin("here_doc", ft_itoa(tmp.hd_number));
	unlink(title);
	free(title);
}
