#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <errno.h>
# include <signal.h>
# include <fcntl.h>
# include <termios.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <dirent.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <readline/history.h>

# include "../lib/libft/libft.h"
# include "struct.h"
# include "dictionary.h"
# include "builtin.h"
# include "run.h"
# include "errno.h"


/*  seheo  */
# include "lexer.h"
# include "deque.h"
# include "token.h"
# include "test.h"
# include "link_list.h"

t_system_var	g_system_var;

void			rl_replace_line(const char *text, int clear_undo);

t_dictionary	get_env(char **envp);
void			ft_free_strs(char **s);
void			minishell_start(void);

#endif
