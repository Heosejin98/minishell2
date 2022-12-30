#include "../../../include/minishell.h"

int	is_empty(t_deque deque)
{
	if (deque.back == NULL && deque.front == NULL)
		return (1);
	return (0);
}
