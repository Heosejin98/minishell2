#ifndef RUN_H
# define RUN_H

# include "struct.h"

enum	PIPE_STATE{NONE = -1, IN, OUT};
void	run_token(t_token *t);
int		is_builtin(char *cmd);
void	run_cmdline(t_token *t, int *prev_pipe, int *cur_pipe );
void	run_builtin(char **cmds);

void	reset_in_out(void);
void	set_in_out(t_redir	*redir);
//void	unlink_heredoc(t_redir *redir);

void	create_pipe(int *prev, int *sh_pipe);

char	*find_path(char *cmd);
void	minish_exit(char *msg);

#endif