#include "../../include/minishell.h"

void	reset_in_out(void)
{
	dup2(g_system_var.fdin, STDIN_FILENO);
	dup2(g_system_var.fdout, STDOUT_FILENO);
}

void	set_in_out(t_redir	*redir)
{
	int	tmp;

	while (redir)
	{
		if (redir->type == IN_REDIR || redir->type == HERE_DOC)
		{
			tmp = open(redir->file_name, O_CREAT | O_RDONLY, 0744);
			if (tmp == -1)
			{
				perror("set_in_out: open");
				exit(1);
			}
			dup2(tmp, STDIN_FILENO);
		}
		if (redir->type == OUT_REDIR)
		{
			tmp = open(redir->file_name, O_CREAT | O_WRONLY | O_TRUNC, 0744);
			if (tmp == -1)
			{
				perror("set_in_out: open");
				exit(1);
			}
			dup2(tmp, STDOUT_FILENO);
		}
		if (redir->type == APP_REDIR)
		{
			tmp = open(redir->file_name, O_CREAT | O_WRONLY | O_APPEND, 0744);
			if (tmp == -1)
			{
				perror("set_in_out: open");
				exit(1);
			}
			dup2(tmp, STDOUT_FILENO);
		}
		redir = redir->next;
	}
} //too long

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
