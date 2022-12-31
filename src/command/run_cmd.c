#include "../../include/minishell.h"

void	run_builtin(char **cmds)
{
	if (!ft_strcmp(cmds[0], "cd"))
		ft_cd(cmds);
	if (!ft_strcmp(cmds[0], "echo"))
		ft_echo(cmds);
	if (!ft_strcmp(cmds[0], "pwd"))
		ft_pwd(cmds);
	if (!ft_strcmp(cmds[0], "env"))
		ft_env(cmds);
	if (!ft_strcmp(cmds[0], "export"))
		ft_export(cmds);
	if (!ft_strcmp(cmds[0], "unset"))
		ft_unset(cmds);
	exit(g_system_var.status);
}

void	run_cmdline(t_token *t)
{
	pid_t	pid;
	char	*path;
	t_token *prev;

	prev = t;
	pid = fork();
	if (pid < 0)
		minish_exit("minish: fork");
	if (pid > 0)
	{
		if (t->next)
			close(t->pipe_fd[0]);
		perror("test1");
		wait(&g_system_var.status);
		//printf("\t%s: %d\n", t->cmdline[0], g_system_var.status); //for testing!
	}
	if (pid == 0)
	{
		if (t->prev)
			close(t->prev->pipe_fd[1]);
		if (is_builtin(t->cmdline[0]))
			run_builtin(t->cmdline);
		else
		{
			perror("test@");
			path = find_path(t->cmdline[0]);
			execve(path, t->cmdline, NULL);
		}
	}
}

void	run_token(t_token *t)
{
	t_redir buf_redir;

	
	while (t->next)
	{
		create_pipe(t);
		if (t->redir->count != 0)
		{
			buf_redir = dequeue_redir(t->redir);
			set_in_out(&buf_redir);
		}
		run_cmdline(t);
		t = t->next;
		perror("test");
	}
	if (t->redir->count != 0)
	{
		buf_redir = dequeue_redir(t->redir);
		set_in_out(&buf_redir);
	}
	run_cmdline(t);
	perror("test");
	reset_in_out();
}