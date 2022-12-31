#include "../../include/minishell.h"

char	*find_path(char *cmd)
{
	int		i;
	char	**candidate;
	DIR		*dir;
	struct dirent *dirp;
	char	*tmp;

	candidate = ft_split(dictionary_search(g_system_var.env, "PATH"), ':');
	if (!candidate)
		;
	i = 0;
	while (candidate[i])
	{
		dir = opendir(candidate[i]);
		while (1)
		{
			dirp = readdir(dir);
			if (!dirp)
				break ;
			if (strcmp(dirp->d_name, cmd)==0)
			{
				closedir(dir);
				tmp = ft_strjoin("/", cmd); //leaks
				return (ft_strjoin(candidate[i], tmp));
			}
		}
		closedir(dir);
		i++;
	}
	return (ft_strjoin("./", cmd));
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
	if (t->prev)
		close(t->prev->pipe_fd[0]);
	reset_in_out();
}

int		is_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "echo") \
	|| !ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "env") \
	|| !ft_strcmp(cmd, "export") || !ft_strcmp(cmd, "unset"))
		return (1);
	return (0);

}
void	run_cmdline(t_token *t)
{
	pid_t	pid;
	char	*path;

	if (is_builtin(t->cmdline[0]))
	{
		run_builtin(t->cmdline);
		return ;
	}
	pid = fork();
	if (pid < 0)
	{
		perror("fork: ");
		exit(1);
	}
	if (pid > 0)
	{
		if (t->next)
			close(t->pipe_fd[0]);
		wait(&g_system_var.status);
	}
	if (pid == 0)
	{
		if (t->prev)
			close(t->prev->pipe_fd[1]);
		path = find_path(t->cmdline[0]);
		execve(path, t->cmdline, NULL);
	}
}

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
}