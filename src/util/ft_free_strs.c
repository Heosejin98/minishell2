#include "../../include/minishell.h"

void	ft_free_strs(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		free(s[i++]);
}
