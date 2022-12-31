#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

typedef struct s_lexer_info
{
	size_t	i;
	size_t	j;
	int		index;
	int		flag;
}	t_lexer_info;

char	**lexer(char const *s);

#endif
