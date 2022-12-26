/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seheo <seheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 23:47:21 by sejin             #+#    #+#             */
/*   Updated: 2022/04/26 20:53:47 by seheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *src, unsigned int m, size_t n)
{
	unsigned int		len;
	unsigned int		i;
	char				*dest;

	len = n - m;
	dest = (char *)malloc(sizeof(char) * (len + 1));
	i = m;
	while (i < n && (*(src + i) != '\0'))
	{
		*dest = *(src + i);
		dest++;
		i++;
	}
	*dest = '\0';
	return (dest - len);
}
