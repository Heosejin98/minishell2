/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seheo <seheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 12:13:39 by seheo             #+#    #+#             */
/*   Updated: 2023/01/06 12:13:40 by seheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	heredoc_unlink(void)
{
	int		hd_cnt;
	char	*filename;
	char	*temp;

	hd_cnt = 1;
	while (hd_cnt <= g_system_var.hd_cnt)
	{
		temp = ft_itoa(g_system_var.hd_cnt);
		filename = ft_strjoin("here_doc", temp);
		free(temp);
		if (access(filename, F_OK) == 0)
			unlink(filename);
		free(filename);
		hd_cnt++;
	}
}

void	heredoc_signal2(int sig)
{
	if (sig == SIGINT)
	{	
		g_system_var.hd_flag = 1;
	}
}
