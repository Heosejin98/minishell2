#include "../../include/minishell.h"

void	create_pipe(int *prev, int *sh_pipe)
{
	int	ret;

	ret = pipe(sh_pipe);
	if (ret == -1)
		minish_exit("pipe");
}

void	set_in_out(t_redir *redir)
{
	int	tmp;
	int	oflag;

	while (redir)
	{
		oflag = 0;
		if (redir->type  == IN_REDIR || redir->type == HERE_DOC)
			oflag = (O_CREAT | O_RDONLY);
		else if (redir->type == OUT_REDIR)
			oflag = (O_CREAT | O_WRONLY | O_TRUNC);
		else if (redir->type == APP_REDIR)
			oflag = (O_CREAT | O_WRONLY | O_APPEND);
		tmp = open(redir->file_name, oflag, 0744);
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

void	unlink_heredoc(t_redir *redir)
{
	while (redir)
	{
		if (redir->type == HERE_DOC)
		{
			unlink(redir->file_name);
		}
		redir = redir->next;
	}
}
