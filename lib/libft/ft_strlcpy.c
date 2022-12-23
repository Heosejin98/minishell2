/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejin <sejin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 21:52:19 by sejin             #+#    #+#             */
/*   Updated: 2022/03/26 17:52:27 by seheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	src_len;

	i = 0;
	src_len = ft_strlen(src);
	if (!dest || !src)
		return (0);
	while (i < (size - 1) && src[i] != 0 && size != 0)
	{
		dest[i] = src[i];
		i++;
	}	
	if (size > 0)
		dest[i] = 0;
	return (src_len);
}
