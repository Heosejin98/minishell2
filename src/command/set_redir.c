/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seheo <seheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 12:13:26 by seheo             #+#    #+#             */
/*   Updated: 2023/01/06 12:13:26 by seheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	get_open_mode(enum e_redir_type type)
{
	int	oflag;

	oflag = 0;
	if (type == IN_REDIR || type == HERE_DOC)
		oflag = (O_RDONLY);
	else if (type == OUT_REDIR)
		oflag = (O_CREAT | O_WRONLY | O_TRUNC);
	else if (type == APP_REDIR)
		oflag = (O_CREAT | O_WRONLY | O_APPEND);
	return (oflag);
}

static char	*get_title(t_redir *redir)
{
	char	*title;

	if (redir->type == HERE_DOC)
		title = ft_strjoin("here_doc", ft_itoa(redir->hd_number));
	else
		title = ft_strdup(redir->file_name);
	return (title);
}

static int	check_valid_filename(int oflag, char *title)
{
	if (oflag == IN_REDIR && access(title, F_OK) == -1)
	{
		ft_putstr_fd("minish: ", STDERR_FILENO);
		perror(title);
		g_system_var.status = 1;
		return (1);
	}
	return (0);
}

int	set_in_out(t_redir *redir)
{
	int		tmp;
	int		oflag;
	char	*title;

	while (redir)
	{
		title = get_title(redir);
		oflag = get_open_mode(redir->type);
		if (check_valid_filename(oflag, title))
			return (1);
		tmp = open(title, oflag, 0744);
		free(title);
		if (tmp == -1)
			minish_exit("open", 1);
		if (redir->type == IN_REDIR || redir->type == HERE_DOC)
			dup2(tmp, STDIN_FILENO);
		else if (redir->type == OUT_REDIR || redir->type == APP_REDIR)
			dup2(tmp, STDOUT_FILENO);
		close(tmp);
		redir = redir->next;
	}
	return (0);
}

void	reset_in_out(void)
{
	dup2(g_system_var.fdin, STDIN_FILENO);
	dup2(g_system_var.fdout, STDOUT_FILENO);
}
