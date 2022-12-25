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

char	*ft_substr(char const *src, unsigned int n, size_t m)
{
	int		len;
	int		i;
	char	*dest;

	i = 0;
	len = n - m;
	dest = (char *)malloc(sizeof(char) * (len + 1));

	while (i < n && (*(src + i) != '\0'))
	{
		*dest = *(src + i);
		i++;
		dest++;
	}
	*dest = '\0';
	return (dest - len);
}

