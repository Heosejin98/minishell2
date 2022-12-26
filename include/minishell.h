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

t_system_var	g_system_var;
void			rl_replace_line(const char *text, int clear_undo);

t_dictionary	get_env(char **envp);
#endif
