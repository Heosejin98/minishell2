/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seheo <seheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 20:43:50 by sejin             #+#    #+#             */
/*   Updated: 2022/04/26 19:09:23 by seheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	size_t	s_len;

	s_len = ft_strlen(str);
	while (s_len != 0 && str[s_len] != (char)c)
		s_len--;
	if (str[s_len] == (char)c)
		return ((char *)(str + s_len));
	return (0);
}
