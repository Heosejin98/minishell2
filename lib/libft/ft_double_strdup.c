/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_double_strdup.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seheo <seheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 15:24:00 by seheo             #+#    #+#             */
/*   Updated: 2022/10/02 15:29:33 by seheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_double_strdup(char **arr)
{
	char	**cpy;
	int		i;

	if (arr == NULL)
		return (NULL);
	cpy = ft_calloc(ft_double_strlen(arr) + 1, sizeof(*cpy));
	if (cpy == NULL)
		return (NULL);
	i = 0;
	while (arr[i])
	{
		cpy[i] = ft_strdup(arr[i]);
		i++;
	}
	return (cpy);
}
