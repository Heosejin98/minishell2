/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soylee <soylee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 23:41:29 by soylee            #+#    #+#             */
/*   Updated: 2022/04/30 10:52:56 by soylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(int c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	else
		return (0);
}

static int	check_sign(const char *str, int *idx)
{
	int	sign;

	if (str[*idx] == '+')
	{
		sign = 1;
		(*idx)++;
	}
	else if (str[*idx] == '-')
	{
		sign = -1;
		(*idx)++;
	}
	else
		sign = 1;
	return (sign);
}

int	check_max(int sign, int decimal)
{
	int	dq;
	int	dr;
	int	max;
	int	last;

	dq = decimal / 10;
	dr = decimal % 10;
	max = INT_MAX / 10;
	if (sign == 1)
		last = (char)(INT_MAX % 10) + '0';
	else
		last = (char)(INT_MIN % 10) + '0';
	if (dq < max)
		return (0);
	else if (dq > max)
		return (sign);
	else if (dr > last)
		return (sign);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	int	idx;
	int	sign;
	int	decimal;
	int	check_tag;

	idx = 0;
	while (ft_isspace(str[idx]))
		idx++;
	sign = check_sign(str, &idx);
	decimal = 0;
	while (ft_isdigit(str[idx]))
	{
		decimal *= 10;
		decimal += str[idx] - '0';
		check_tag = check_max(sign, decimal);
		if (check_tag == 1)
			return (INT_MAX);
		else if (check_tag == -1)
			return (INT_MIN);
		idx++;
	}
	return (sign * decimal);
}
