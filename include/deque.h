#ifndef DEQUE_H
# define DEQUE_H

# include "minishell.h"
# include "struct.h"

typedef struct s_deque
{
	t_token	*front;
	t_token	*back;
}	t_deque;

void		init_deque(t_deque *deque);
void		input_front(t_deque *deque, t_token data);
void		input_back(t_deque *deque, t_token data);
t_token		output_front(t_deque *deque);
t_token		output_back(t_deque *deque);
int			is_empty(t_deque deque);

#endif

