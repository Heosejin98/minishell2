/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seheo <seheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 12:15:46 by seheo             #+#    #+#             */
/*   Updated: 2023/01/06 12:15:46 by seheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RUN_H
# define RUN_H

# include "struct.h"

void	run_builtin(char **cmds);
void	run_cmdline(t_token *t, int *prev_pipe, int *cur_pipe);
void	no_pipe_builtin(t_token *t);
void	run_token(t_token *t);

void	run_child(t_token *t, int *prev_pipe, int *cur_pipe);
void	run_parent(t_token *t, int *prev_pipe, int *cur_pipe);
void	wait_children(void);

int		set_in_out(t_redir *redir);
void	reset_in_out(void);
void	unlink_heredoc(t_redir_queue *redir);

char	*find_path(char *cmd);
void	find_cmd(char **cmd);
void	minish_exit(char *msg, int code);

#endif