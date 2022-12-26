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

void	ft_cd(char *path)
{
	int				ret;
	char			*real_path;
	t_dictionary_node	*oldpwd;
	t_dictionary_node	*pwd;

	real_path = find_real_path(path);
	ret = chdir(real_path);
	if (ret == -1)
	{
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