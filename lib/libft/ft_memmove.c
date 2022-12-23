/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seheo <seheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 21:46:58 by sejin             #+#    #+#             */
/*   Updated: 2022/04/26 21:18:59 by seheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*new_src;
	char	*new_dst;
	size_t	i;

	if (!dst && !src)
		return (NULL);
	new_src = (char *)src;
	new_dst = (char *)dst;
	i = 0;
	if (new_dst > new_src)
		while (len-- > 0)
			new_dst[len] = new_src[len];
	else
	{
		while (i < len)
		{
			new_dst[i] = new_src[i];
			i++;
		}
	}
	return (dst);
}
