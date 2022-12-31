#ifndef TOKEN_H
# define TOKEN_H

# include "minishell.h"
# include "link_list.h"

typedef struct s_env_convert_info
{
	int	start_idx;
	int	end_idx;
	int	str_end_idx;
	int	flag;
}	t_env_convert_info;

typedef struct s_token_info
{
	t_deque			result;
	t_token			buf_token;
	t_lst			*l_list;
	t_redir_queue	*q_redir;
	int				i;
}	t_token_info;

t_deque		make_tokens(char **lexer);
int			count_row(char **strings);
void		make_cmdline(t_lst *list, char *s);
void		make_quoteline(t_lst *list, char *s);
char		*convert_env(const char *s);

void		make_redir(t_redir_queue *buf_redir, char **s, int *idx);
void		add_redir(t_redir_queue *r_que, t_redir buf_redir);
t_redir		dequeue_redir(t_redir_queue *queue);

void		init_token_info(t_token_info *t_info);
void		reset_token_info(t_token_info *t_info);
void		list_to_strs(t_lst *list, t_token *buf_token);
int			repeat_char(char *s, char c);
char		*opt_convert(int *flag, int i, char *temp);

void		heredoc_file_maker(char *end_str, int hd_num);
void		heredoc_unlink(void);
#endif