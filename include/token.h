#ifndef TOKEN_H
# define TOKEN_H

# include "minishell.h"
# include "link_list.h"

typedef struct s_env_convert_info
{
	int	start_idx;
	int	end_idx;
	int	str_end_idx;
}	t_env_convert_info;

t_deque		make_tokens(char **lexer);
int			count_row(char **strings);
void		make_cmdline(t_lst *list, char *s);
void		make_quoteline(t_lst *list, char *s);
char		*convert_env(const char *s);

void		make_redir(t_redir_queue *buf_redir, char **s, int *idx);
void		add_redir(t_redir_queue *r_que, t_redir buf_redir);
t_redir		dequeue_redir(t_redir_queue *queue);


#endif