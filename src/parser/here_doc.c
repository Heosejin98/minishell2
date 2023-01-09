/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seheo <seheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 12:14:02 by seheo             #+#    #+#             */
/*   Updated: 2023/01/06 12:14:03 by seheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/token.h"

void	heredoc_signal(int sig)
{
	if (sig == SIGINT)
	{	
		g_system_var.hd_flag = 1;
		write(2, "\n", 1);
		heredoc_unlink();
		exit(EXIT_FAILURE);
	}
}

static void	heredoc_child(char *end_str, int hd_num)
{
	int		hd_fd;
	char	*line;
	char	*hd_filename;
	char	*temp;

	temp = ft_itoa(hd_num);
	hd_filename = ft_strjoin("here_doc", temp);
	free(temp);
	hd_fd = open(hd_filename, O_CREAT | O_RDWR | O_TRUNC, 0744);
	if (hd_fd == -1)
		minish_exit(hd_filename, 1);
	line = readline("heredoc> ");
	while (line && ft_strncmp(line, end_str, ft_strlen(line)) != 0)
	{
		if (ft_strchr(line, '$'))
			line = convert_env(line);
		ft_putstr_fd(line, hd_fd);
		ft_putstr_fd("\n", hd_fd);
		free(line);
		line = readline("heredoc> ");
	}
	close(hd_fd);
	exit(EXIT_SUCCESS);
}

void	heredoc_file_maker(char *end_str, int hd_num)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	else if (pid == 0)
	{
		signal(SIGINT, heredoc_signal);
		heredoc_child(end_str, hd_num);
		exit(EXIT_FAILURE);
	}
	else
	{
		signal(SIGINT, heredoc_signal2);
		waitpid(pid, &pid, 0);
	}
}
