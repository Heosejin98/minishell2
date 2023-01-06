/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seheo <seheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 12:13:11 by seheo             #+#    #+#             */
/*   Updated: 2023/01/06 12:13:12 by seheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_pwd(char **cmds)
{
	char	*wd;

	if (!check_valid_opt(cmds, 0, "pwd [-]"))
		return ;
	wd = getcwd(NULL, 0);
	if (!wd)
	{
		perror("minishell: getcwd");
		exit(1);
	}
	printf("%s\n", wd);
	free(wd);
	g_system_var.status = 0;
}
