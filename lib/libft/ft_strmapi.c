/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejin <sejin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 01:20:39 by sejin             #+#    #+#             */
/*   Updated: 2022/03/26 01:20:55 by sejin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*output;
	size_t	i;

	if (!s || !f)
		return (0);
	i = 0;
	output = (char *)ft_calloc(ft_strlen(s) + 1, sizeof(char));
	if (!output)
		return (0);
	while (i < ft_strlen(s))
	{
		output[i] = f(i, s[i]);
		i++;
	}
	output[i] = 0;
	return (output);
}
