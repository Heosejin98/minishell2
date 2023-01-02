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
	t_redir		buf_redir;
	pid_t	pid;
	char	*path;
	int		tmp;

	// signal(SIGINT, SIG_DFL);
	// 	signal(SIGQUIT, SIG_DFL);
	pid = fork();
	if (pid < 0)
		minish_exit("minishell: fork");
	if (pid > 0)
	{
		if (wait(&tmp) == -1)
			minish_exit("minishell: wait");
		else
			g_system_var.status =  WEXITSTATUS(tmp);
		if (prev_pipe[0] == -1 && !t->next)
			;
		else if (prev_pipe[0] == -1) 
		{
			close(cur_pipe[1]);
		}
		else if (!t->next)
		{
			close(prev_pipe[0]);
		}
		else
		{
			close(prev_pipe[0]);
			close(cur_pipe[1]);
		}
		// printf("\t%s: %d\n", t->cmdline[0], g_system_var.status); //for testing!
	}
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (prev_pipe[0] == -1 && !t->next)
				;
		else if (prev_pipe[0] == -1)
		{
			close(cur_pipe[0]);
			dup2(cur_pipe[1], STDOUT_FILENO);
			close(cur_pipe[1]);
		}
		else if (!t->next)
		{
			dup2(prev_pipe[0], STDIN_FILENO);
			close(prev_pipe[0]);
		}
		else
		{
			dup2(prev_pipe[0], STDIN_FILENO);
			close(prev_pipe[0]);
			close(cur_pipe[0]);
			dup2(cur_pipe[1], STDOUT_FILENO);
			close(cur_pipe[1]);
		}
		if (t->redir->count != 0)
		{
			buf_redir = dequeue_redir(t->redir);
			set_in_out(&buf_redir);
		}
		if (is_builtin(t->cmdline[0]))
			run_builtin(t->cmdline);
		else
		{
			path = find_path(t->cmdline[0]);
			if (execve(path, t->cmdline, NULL) == -1)
			{
				ft_putstr_fd("minishell: command not found: ", STDERR_FILENO);
				ft_putendl_fd(t->cmdline[0], STDERR_FILENO);
				exit(127);
			}
		}
	}
	// signal(SIGINT, sig_readline);
	// 	signal(SIGQUIT, SIG_IGN);
}

void	run_token(t_token *t)
{
	t_redir		buf_redir;
	int			sh_pipe[2];
	int			prev_pipe[2];
	int			ret;
	
	sh_pipe[0] = -1;
 	while (t)
	{
		prev_pipe[0] = sh_pipe[0];
		prev_pipe[1] = sh_pipe[1];
		if (t->next)
			create_pipe(prev_pipe, sh_pipe);
		run_cmdline(t, prev_pipe, sh_pipe);
		reset_in_out();
		t = t->next;
	}
	//unlink_heredoc(t->redir);
}