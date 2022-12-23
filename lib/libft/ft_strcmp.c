/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seheo <seheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 17:54:42 by seheo             #+#    #+#             */
/*   Updated: 2022/10/02 16:06:06 by seheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	const unsigned char	*buf1;
	const unsigned char	*buf2;

	buf1 = (const unsigned char *)s1;
	buf2 = (const unsigned char *)s2;
	if (*buf1 != *buf2)
		return (*buf1 - *buf2);
	while (*buf1 && *buf2)
	{
		if (*buf1 != *buf2)
			return (*buf1 - *buf2);
		buf1++;
		buf2++;
	}
	if (*buf1 == '\0' && *buf2 != '\0')
		return (0 - *buf2);
	else if (*buf2 == '\0' && *buf1 != '\0')
		return (*buf1);
	return (0);
}
