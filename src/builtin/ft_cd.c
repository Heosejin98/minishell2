#include "../../include/minishell.h"

static char	*find_real_path(char *path)
{
	t_dictionary_node	*home;
	char				*real_path;

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

static void	set_cd_env(void)
{
	char	*oldpwd;
	char	*pwd;
	char	*real_path;

	oldpwd = dictionary_search(g_system_var.env, "OLDPWD");
	pwd = dictionary_search(g_system_var.env, "PWD");
	if (oldpwd)
		dictionary_delete(&g_system_var.env, "OLDPWD");
	dictionary_add(&g_system_var.env, ft_strdup("OLDPWD"), ft_strdup(pwd));
	if (pwd)
		dictionary_delete(&g_system_var.env, "PWD");
	real_path = getcwd(NULL, 0);
	if (!real_path)
	{
		perror("minish: cd: ");
		g_system_var.status = 2;
		return ;
	}
	dictionary_add(&g_system_var.env, ft_strdup("PWD"), real_path);
}

void	ft_cd(char **cmds)
{
	int		ret;
	char	*real_path;

	if (is_option(cmds[1]))
	{
		perror_opt(cmds[0], abstract_opt(cmds[1]), "cd [-] [dir]");
		return ;
	}
	real_path = find_real_path(cmds[1]);
	ret = chdir(real_path);
	free(real_path);
	if (ret == -1)
	{
		perror("minish: cd");
		g_system_var.status = 2;
		return ;
	}
	set_cd_env();
	g_system_var.status = 0;
}
