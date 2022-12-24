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

# include "../../../include/minishell.h"

void init_deque(t_deque *deque)
{
    deque->front = NULL;
    deque->back = NULL;
}
 
void input_front(t_deque *deque, t_token token)
{
    t_token *new_token = (t_token *)malloc(sizeof(t_token));
    new_token->content = token.content;
    new_token->type = token.type;

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

void input_back(t_deque *deque, t_token token)
{
    t_token *new_token = (t_token *)malloc(sizeof(t_token));
    new_token->content = token.content;
    new_token->type = token.type;
 
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

t_token output_front(t_deque *deque)
{
    t_token result;
    t_token *temp = NULL;

    if (deque->front == NULL)
    {
        result.type = NONE;
        return (result);
    }
    result.type = deque->front->type;
    result.cmdline = deque->front->cmdline;
    result.content = deque->front->content;
    temp = deque->front;
    deque->front = deque->front->next;
    deque->front->prev = NULL;
    free(temp);
    
    return (result);
}

t_token output_back(t_deque *deque)
{
    t_token result;
    t_token *temp = NULL;

    if (deque->back == NULL)
    {
        result.type = NONE;
        return (result);
    }
    result.type = deque->back->type;
    result.cmdline = deque->back->cmdline;
    result.content = deque->back->content;
    temp = deque->back;
    deque->back = deque->back->prev;
    deque->back->next = NULL;
    free(temp);
    
    return result;
}