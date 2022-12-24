/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seheo <seheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 17:22:52 by seheo             #+#    #+#             */
/*   Updated: 2022/12/24 17:38:26 by seheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/minishell.h"

void init_queue(t_queue *queue)
{
    queue->front = queue->rear = NULL; 
    queue->count = 0;
}
 
int is_empty(t_queue *queue)
{
    return queue->count == 0;
}
 
void enqueue(t_queue *queue, t_token data)
{
    t_token *new_token = (t_token *)malloc(sizeof(t_token)); // new_token 생성
    new_token->content = data.content;
    new_token->type = data.type;
    new_token->next = NULL;
 
    if (is_empty(queue))
        queue->front = new_token;       
    else
        queue->rear->next = new_token;
    queue->rear = new_token;   
    queue->count++;
}
 
t_token dequeue(t_queue *queue)
{
    t_token data;
    t_token *ptr;

    if (is_empty(queue))
    {
        printf("Error : Queue is empty!\n");
        return data;
    }
    ptr = queue->front;
    data.content = ptr->content;
    data.type = ptr->type;  
    queue->front = ptr->next;
    free(ptr);
    queue->count--;
    
    return data;
}