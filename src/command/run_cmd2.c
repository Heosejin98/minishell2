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

	pid = fork();
	if (pid < 0)
		minish_exit("minish: fork");
	if (pid > 0)
	{
		if (t->next)
			close(t->pipe_fd[0]);
		wait(&g_system_var.status);
		printf("\t%s: %d\n", t->cmdline[0], g_system_var.status); //for testing!
	}
	if (pid == 0)
	{
		perror("test");
		if (t->prev)
			close(t->prev->pipe_fd[1]);
		if (is_builtin(t->cmdline[0]))
			run_builtin(t->cmdline);
		else
		{
			path = find_path(t->cmdline[0]);
			execve(path, t->cmdline, NULL);
		}
	}
}

void	run_token(t_token *t)
{
	while (t->next)
	{
		create_pipe(t);
		set_in_out(t->redir);
		run_cmdline(t);
		t = t->next;
	}
	set_in_out(t->redir);
	run_cmdline(t);
	reset_in_out();
}