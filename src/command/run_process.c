/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seheo <seheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 12:13:22 by seheo             #+#    #+#             */
/*   Updated: 2023/01/06 12:17:32 by seheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	set_child_pipe(t_token *t, int *prev_pipe, int *cur_pipe)
{
	if (prev_pipe[0] == -1 && !t->next)
		;
	else if (prev_pipe[0] == -1)
	{
		close(cur_pipe[0]);
		dup2(cur_pipe[1], STDOUT_FILENO);
		close(cur_pipe[1]);
	}
	else if (!t->next)
	{
		dup2(prev_pipe[0], STDIN_FILENO);
		close(prev_pipe[0]);
	}
	else
	{
		dup2(prev_pipe[0], STDIN_FILENO);
		close(prev_pipe[0]);
		close(cur_pipe[0]);
		dup2(cur_pipe[1], STDOUT_FILENO);
		close(cur_pipe[1]);
	}
}

static void	fail_to_run(char *cmd)
{
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putendl_fd(": command not found", STDERR_FILENO);
	exit(127);
}

void	run_child(t_token *t, int *prev_pipe, int *cur_pipe)
{
	char	*path;

	set_child_pipe(t, prev_pipe, cur_pipe);
	if (t->redir->count != 0)
	{
		set_in_out(t->redir->front);
	}
	if (is_builtin(t->cmdline[0]))
	{
		run_builtin(t->cmdline);
		exit(g_system_var.status);
	}
	else
	{
		path = find_path(t->cmdline[0]);
		find_cmd(&(t->cmdline[0]));
		if (execve(path, t->cmdline, NULL) == -1)
			fail_to_run(t->cmdline[0]);
		free(path);
	}
}

void	run_parent(t_token *t, int *prev_pipe, int *cur_pipe)
{
	if (prev_pipe[0] == -1 && !t->next)
		;
	else if (prev_pipe[0] == -1)
		close(cur_pipe[1]);
	else if (!t->next)
		close(prev_pipe[0]);
	else
	{
		close(prev_pipe[0]);
		close(cur_pipe[1]);
	}
}

void	wait_children(void)
{
	int	e_status;

	while (waitpid(-1, &e_status, 0) >= 0)
	{
		if (WIFEXITED(e_status))
			g_system_var.status = WEXITSTATUS(e_status);
		else if (WIFSIGNALED(e_status))
			g_system_var.status = 128 + WTERMSIG(e_status);
	}
}
