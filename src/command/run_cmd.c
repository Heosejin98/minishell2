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
	if (!ft_strcmp(cmds[0], "exit"))
		ft_exit(cmds);
}

void	run_cmdline(t_token *t, int *prev_pipe, int *cur_pipe)
{
	t_redir		buf_redir;
	pid_t	pid;
	char	*path;
	int		tmp;

	pid = fork();
	if (pid < 0)
		minish_exit("minishell: fork");
	if (pid > 0)
	{
		if (wait(&tmp) == -1)
			minish_exit("minishell: wait");
		else
		{
			if (WIFEXITED(tmp))
				g_system_var.status =  WEXITSTATUS(tmp);
			else if (WIFSIGNALED(tmp))
				g_system_var.status = 128 + WTERMSIG(tmp);
		}
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
		{
			run_builtin(t->cmdline);
			exit(g_system_var.status);
		}
		else
		{
			path = find_path(t->cmdline[0]);
			find_cmd(&(t->cmdline[0]));
			if (execve(path, t->cmdline, NULL) == -1)
			{
				if (!ft_strcmp(t->cmdline[0], "$?"))
					ft_putnbr_fd(g_system_var.status, STDERR_FILENO);
				else
					ft_putstr_fd(t->cmdline[0], STDERR_FILENO);
				ft_putendl_fd(": command not found", STDERR_FILENO);
				exit(127);
			}
			free(path);
		}
	}
}

void	no_pipe_builtin(t_token *t)
{
	t_redir	buf_redir;

	if (t->redir->count != 0)
	{
		buf_redir = dequeue_redir(t->redir);
		set_in_out(&buf_redir);
	}
	run_builtin(t->cmdline);
	reset_in_out();
}

void	run_token(t_token *t)
{
	t_redir		buf_redir;
	int			sh_pipe[2];
	int			prev_pipe[2];
	int			ret;
	
	sh_pipe[0] = -1;
	if (!t->next && is_builtin(t->cmdline[0]))
	{
		no_pipe_builtin(t);
		return ;
	}
 	while (t)
	{
		prev_pipe[0] = sh_pipe[0];
		prev_pipe[1] = sh_pipe[1];
		if (t->next)
			create_pipe(prev_pipe, sh_pipe);
		run_cmdline(t, prev_pipe, sh_pipe);
		t = t->next;
	}
	if (t && t->redir && t->redir->count != 0)
	{
		buf_redir = dequeue_redir(t->redir);
		unlink_heredoc(&buf_redir);
	}
}