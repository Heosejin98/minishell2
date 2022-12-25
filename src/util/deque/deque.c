/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seheo <seheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 17:22:52 by seheo             #+#    #+#             */
/*   Updated: 2022/12/24 23:34:49 by seheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	init_deque(t_deque *deque)
{
	deque->front = NULL;
	deque->back = NULL;
}

void	input_front(t_deque *deque, t_token token)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	new_token->cmdline = token.cmdline;
	new_token->redir = token.redir;
	if (deque->front == NULL)
	{
		deque->front = new_token;
		deque->back = new_token;
		new_token->next = NULL;
		new_token->prev = NULL;
		return ;
	}
	deque->front->prev = new_token;
	new_token->next = deque->front;
	deque->front = new_token;
	new_token->prev = NULL;
}

void	input_back(t_deque *deque, t_token token)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	new_token->cmdline = token.cmdline;
	new_token->redir = token.redir;
	if (deque->front == NULL)
	{
		deque->front = new_token;
		deque->back = new_token;
		new_token->next = NULL;
		new_token->prev = NULL;
		return ;
	}
	deque->back->next = new_token;
	new_token->prev = deque->back;
	deque->back = new_token;
	new_token->next = NULL;
}

t_token	output_front(t_deque *deque)
{
	t_token	result;
	t_token	*temp;
	
	if (deque->front == NULL)
	{
		result.redir = NULL;
		result.cmdline = NULL;
		return (result);
	}
	result.redir = deque->front->redir;
	result.cmdline = deque->front->cmdline;
	result.cmdline = deque->front->cmdline;
	temp = deque->front;
	if (deque->front == deque->back)
	{
		deque->front = NULL;
		free(temp);
		deque->back = NULL;
		return (result);
	}
	deque->front = deque->front->next;
	deque->front->prev = NULL;
	free(temp);
	return (result);
}

t_token	output_back(t_deque *deque)
{
	t_token	result;
	t_token	*temp;

	if (deque->back == NULL)
	{
		result.redir = NULL;
		result.cmdline = NULL;
		return (result);
	}
	result.redir = deque->back->redir;
	result.cmdline = deque->back->cmdline;
	result.cmdline = deque->back->cmdline;
	temp = deque->back;
	if (deque->front == deque->back)
	{
		deque->front = NULL;
		deque->back = NULL;
		free(temp);
		return (result);
	}
	deque->back = deque->back->prev;
	deque->back->next = NULL;
	free(temp);
	return (result);
}
