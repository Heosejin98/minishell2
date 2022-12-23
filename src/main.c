/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seheo <seheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 14:54:53 by seheo             #+#    #+#             */
/*   Updated: 2022/12/23 18:35:18 by seheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/minishell.h"

void init_system_var(char **envp) 
{
    (void)envp;
    g_system_var.hd_cnt = 0;
	g_system_var.status = 0;
	g_system_var.old_std_fdin = dup(STDIN_FILENO);
	g_system_var.old_std_fdout = dup(STDOUT_FILENO);
	g_system_var.env = get_env(envp);
}

static void	minishell_start(void)
{
	char	*cmd_line;

	while (1)
	{
		cmd_line = readline("minishell$ ");
	}
}


int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
    init_system_var(envp);
    minishell_start();
}