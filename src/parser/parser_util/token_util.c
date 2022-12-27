#include "../../../include/minishell.h"

void	init_token_info(t_token_info *t_info)
{
	t_info->i = 0;
	t_info->l_list = (t_lst *)malloc(sizeof(t_lst));
	t_info->q_redir = (t_redir_queue *)malloc(sizeof(t_redir_queue));
	t_info->buf_token.redir = NULL;
	t_info->buf_token.cmdline = NULL;
	t_info->buf_token.next = NULL;
	t_info->buf_token.prev = NULL;
	init_deque(&t_info->result);
}

void	reset_token_info(t_token_info *t_info)
{
	t_info->buf_token.redir = t_info->q_redir;
	list_to_strs(t_info->l_list, &t_info->buf_token);
	input_back(&t_info->result, t_info->buf_token);
	t_info->l_list = (t_lst *)malloc(sizeof(t_lst));
	t_info->buf_token.redir = NULL;
	t_info->buf_token.cmdline = NULL;
	t_info->buf_token.next = NULL;
	t_info->buf_token.prev = NULL;
	t_info->q_redir = (t_redir_queue *)malloc(sizeof(t_redir_queue));
	t_info->q_redir->count = 0;
	t_info->i++;
}