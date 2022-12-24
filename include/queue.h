/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seheo <seheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 16:47:38 by seheo             #+#    #+#             */
/*   Updated: 2022/12/24 20:35:31 by seheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUEUE_H
# define QUEUE_H

# include "minishell.h"
# include "struct.h"

typedef struct s_queue 
{
    t_token *front;
    t_token *rear; 
    int count; 
}   t_queue;

void init_queue(t_queue *queue);
int is_empty(t_queue *queue);
void enqueue(t_queue *queue, t_token data);
t_token dequeue(t_queue *queue);

#endif

