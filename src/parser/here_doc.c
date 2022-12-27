#include "../../include/minishell.h"

void	chang_heredoc_redir(t_deque tokens)
{
	t_token	*t_ptr;
	t_redir	*r_ptr;

	t_ptr = tokens.front;
	while (t_ptr != NULL)
	{	
		r_ptr = t_ptr->redir->front;
		while (r_ptr != NULL)
		{
			if (r_ptr->type == HERE_DOC)
			{
				//write(1, "asd", 4);
				printf("[.here_doc_%d] -%s \n", r_ptr->hd_number, r_ptr->file_name);
			}
			r_ptr = r_ptr->next;
		}
		free(r_ptr);
		t_ptr = t_ptr->next;
	}
	free(t_ptr);
}
