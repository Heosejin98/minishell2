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

void	run_cmdline(t_token *t, int *prev_pipe, int *cur_pipe)
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
			close(cur_pipe[0]);
		perror("test1");
		wait(&g_system_var.status);
		//printf("\t%s: %d\n", t->cmdline[0], g_system_var.status); //for testing!
	}
	if (pid == 0)
	{
		if (prev_pipe[0] != -1)
			close(prev_pipe[2]);
		if (is_builtin(t->cmdline[0]))
			run_builtin(t->cmdline);
		else
		{
			perror("test@");
			ft_putendl_fd(ft_itoa(*test), 2);
			path = find_path(t->cmdline[0]);
			ft_putendl_fd(path, STDERR_FILENO);
			ft_putendl_fd(t->cmdline[0], 2);
			ft_putendl_fd(t->cmdline[1], 2);
			ft_putendl_fd(ft_itoa(*test), 2);
			execve(path, t->cmdline, NULL);
			
		}
	}
	ft_putendl_fd("here", 2);
}

void	run_token(t_token *t)
{
	t_redir		buf_redir;
	int			sh_pipe[2];
	int			prev_pipe[3];
	int			ret;
	
	prev_pipe[0] = -1;
 	while (t)
	{
		prev_pipe[1] = sh_pipe[0];
		prev_pipe[2] = sh_pipe[1];
		if (t->next)
			create_pipe(prev_pipe, sh_pipe);
		if (t->redir->count != 0)
		{
			buf_redir = dequeue_redir(t->redir);
			set_in_out(&buf_redir);
		}
		run_cmdline(t, prev_pipe, sh_pipe);
		perror("test");
		reset_in_out();
		t = t->next;
	}
	//unlink_heredoc(t->redir);
}