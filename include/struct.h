/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seheo <seheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 16:08:08 by seheo             #+#    #+#             */
/*   Updated: 2022/12/23 17:58:42 by seheo            ###   ########.fr       */
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