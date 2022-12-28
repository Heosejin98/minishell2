#include "../../include/minishell.h"

char	*find_path(char *cmd)
{
	int		i;
	char	**candidate;
	DIR		*dir;
	struct dirent *dirp;

	candidate = ft_split(dictionary_search(g_system_var.env, "PATH"), ':');
	if (!candidate)
		;
	i = 0;
	while (candidate[i])
	{
		dir = opendir(candidate[i]);
		dirp = readdir(dir);
		if (strcmp(dirp->d_name, cmd)==0)
		{
			closedir(dir);
			return (ft_strjoin(dirp->d_name, cmd));
		}
		closedir(dir);
		i++;
	}
	return (ft_strjoin("./", cmd));
}

char	*run_cmd(char **cmds)
{
	pid_t	pid;
	int		ret;
	char	*cmd;

	//setting redirection
	//fork
	pid = fork();
	if (pid < 0)
		exit(1);
	if (pid == 0)
	{
		cmd = find_path(cmds[0]);
//		ret = execve(cmd, cmds, env); env 이중 배열로 변환
		if (ret == -1)
		{
			perror("ls: ");
			return ;
		}
	}
	else
	{
		wait(&(g_system_var.status));
	}
}