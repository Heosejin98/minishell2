#include "../../include/minishell.h"

static	int	ft_scan_dir(char *dir_name, char *cmd)
{
	DIR				*dir;
	struct dirent	*dirp;

	dir = opendir(dir_name);
	if (!dir)
	{
		perror("minish: opendir");
		exit(1);
	}
	while (1)
	{
		dirp = readdir(dir);
		if (!dirp)
			break ;
		if (ft_strcmp(dirp->d_name, cmd) == 0)
		{
			closedir(dir);
			return (1);
		}
	}
	closedir(dir);
	return (0);
}

static char	*make_absolute_path(char *path, char *cmd)
{
	char	*res;
	char	*tmp;

	tmp = ft_strjoin(path, "/");
	res = ft_strjoin(tmp, cmd);
	free(tmp);
	return (res);
}

char	*find_path(char *cmd)
{
	int				i;
	char			**candidate;
	DIR				*dir;
	char			*tmp;

	if (*cmd == '\\' || !ft_strncmp(cmd, "./", 2))
		return (ft_strdup(cmd));
	candidate = ft_split(dictionary_search(g_system_var.env, "PATH"), ':');
	i = 0;
	while (candidate[i])
	{
		if (ft_scan_dir(candidate[i], cmd))
			return (make_absolute_path(candidate[i], cmd));
		i++;
	}
	return (make_absolute_path(".", cmd));
}

void	find_cmd(char **cmd)
{
	char			*tmp;
	char		*start;
	size_t			len;

	if (**cmd != '\\')
		return ;
	start = ft_strrchr(*cmd, '\\');
	len = ft_strlen(start);
	tmp = ft_substr(start, 1, len);
	free(*cmd);
	*cmd = tmp;
}

void	minish_exit(char *msg)
{
	ft_putstr_fd("minish: ", STDERR_FILENO);
	perror(msg);
	exit(1);
}