#include "../../include/minishell.h"

static char	*find_real_path(char *path)
{
	_t_dictionary	*home;
	char			*real_path;

	if (!(*path))
	{
		home = dictionary_search(g_system_var.env, "HOME");
		if (!home)
	 		real_path = ft_strdup("");
		else
			real_path = ft_strdup(home->value);
	}
	else
		real_path = ft_strdup(path);
	if (*real_path == 0)
	{
		free(real_path);
		real_path = getcwd(NULL, 0);
	}
	return (real_path);
}

static int	check_option(char *path)
{
	if (*path == '-')
	{
		ft_putstr_fd("minish: cd: -", STDERR_FILENO);
		ft_putstr_fd(path[1], STDERR_FILENO);
		ft_putendl_fd(": invalid option", STDERR_FILENO);
		return (1);
	}
	return (0);
}

void	ft_cd(char *path)
{
	int				ret;
	char			*real_path;
	_t_dictionary	*oldpwd;
	_t_dictionary	*pwd;

	real_path = find_real_path(path);
	ret = chdir(real_path);
	if (ret == -1)
	{
		if (!check_option(real_path))
			perror("minish: cd: ");
		free(real_path);
		g_system_var.status = 2;
		return ;
	}
	oldpwd = dictionary_search(g_system_var.env, "OLDPWD");
	if (oldpwd)
		dictionary_delete(&g_system_var.env, "OLDPWD");
	dictionary_add(&g_system_var.env, ft_strdup("OLDPWD"), ft_strdup(pwd->value));
	pwd = dictionary_search(g_system_var.env, "PWD");
	if (pwd)
		dictionary_delete(&g_system_var.env, "PWD");
	dictionary_add(&g_system_var.env, ft_strdup("PWD"), real_path);
	g_system_var.status = 0;
}