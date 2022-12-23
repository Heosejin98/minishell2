/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seheo <seheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 16:08:08 by seheo             #+#    #+#             */
/*   Updated: 2022/12/23 20:30:18 by seheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"


typedef struct _s_dictionary
{
	char			    	*key;
	char				    *value;
	struct _s_dictionary    *link;
}	_t_dictionary;

typedef struct s_dictionary 
{
    int                     count;
    struct _s_dictionary    *head;
}   t_dictionary;

typedef struct s_system_var
{
	int				status;
	int				hd_cnt;
	t_dictionary    *env;
	char			*prev_path;
	int				old_std_fdin;
	int				old_std_fdout;
	struct termios	nodisplay_set;
	struct termios	display_set;
}	t_system_var;

typedef struct s_token
{
	enum e_token_type	type;
	char				*content;
	struct s_token		*next;
}	t_token;

typedef struct s_parse_tree
{
	enum e_node_type 	n_type;
	t_token				token;	
	struct s_parse_tree	*left;
	struct s_parse_tree	*right;
}	t_parse_tree;

enum	e_node_type
{
	TN_PIPE,
	TN_CMD,
	TN_REDIR,
	TN_REDIRS,
	TN_SIMPLE_CMD,
};

enum	e_token_type
{	
	ARGV,
	IN_RDIR,
	OUT_RDIR,
	APP_RDIR,
	HERE_DOC,
	FILE_NAME
};
