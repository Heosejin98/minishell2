#ifndef STRUCT_H
# define STRUCT_H
# include "minishell.h"

typedef struct s_dictionary_node
{
	char						*key;
	char						*value;
	struct s_dictionary_node	*link;
	struct s_dictionary_node	*prev;
}	t_dictionary_node;

typedef struct s_dictionary
{
	int							count;
	struct s_dictionary_node	*head;
}	t_dictionary;

typedef struct s_system_var
{
	int				status;
	int				hd_cnt;
	t_dictionary	env;
	char			*prev_path;
	int				old_std_fdin;
	int				old_std_fdout;
	struct termios	nodisplay_set;
	struct termios	display_set;
	int				hd_flag;
}	t_system_var;

enum	e_redir_type
{
	IN_REDIR,
	OUT_REDIR,
	APP_REDIR,
	HERE_DOC
};

typedef struct s_redir
{
	enum e_redir_type	type;
	char				*file_name;
	int					hd_number;
	struct s_redir		*next;
}	t_redir;

typedef struct s_redir_queue
{
	t_redir	*front;
	t_redir	*rear;
	int		count;
}	t_redir_queue;

typedef struct s_token
{
	t_redir_queue		*redir;
	char				**cmdline;
	struct s_token		*next;
	struct s_token		*prev;
}	t_token;
#endif