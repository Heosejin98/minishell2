#include "../../include/minishell.h"

void	create_pipe(t_token *token)
{
	int	ret;
	
	ret = pipe(token->pipe_fd);
	if (ret == -1)
	{
		perror("pipe: ");
		exit(1);
	}
	if (token->prev)
		dup2(token->prev->pipe_fd[0], STDIN_FILENO);
	else
		close(token->prev->pipe_fd[0]);
	if (token->next)
		dup2(token->pipe_fd[1], STDOUT_FILENO);
	else
		close(token->prev->pipe_fd[1]);
}