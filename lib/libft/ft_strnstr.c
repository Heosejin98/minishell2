/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejin <sejin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 22:39:29 by sejin             #+#    #+#             */
/*   Updated: 2022/03/24 22:07:30 by sejin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *search, size_t len)
{
	size_t	i;
	int		j;

	if (*search == '\0')
		return ((char *)str);
	i = 0;
	while (str[i] != '\0' && i < len)
	{
		if (str[i] == search[0])
		{
			j = 0;
			while (search[j] && str[i + j] && i + j < len
				&& str[i + j] == search[j])
				j++;
			if (search[j] == '\0')
				return ((char *)str + i);
		}
		i++;
	}
	return (0);
}
