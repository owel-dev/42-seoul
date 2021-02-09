/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 20:18:18 by ulee              #+#    #+#             */
/*   Updated: 2020/11/22 16:14:34 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_isspace(int c)
{
	return (((9 <= c && c <= 13) || c == ' ') ? 1 : 0);
}

int		ft_atoi(const char *str)
{
	long sign;
	long num;

	while (ft_isspace(*str))
		str++;
	sign = 1;
	if (*str == '-')
		sign *= -1;
	if (*str == '-' || *str == '+')
		str++;
	num = 0;
	while (ft_isdigit(*str))
	{
		num *= 10;
		num += *str - '0';
		if (num > 2147483648 && sign == 1)
			return (-1);
		if (num > 2147483648 && sign == -1)
			return (0);
		str++;
	}
	return (num * sign);
}
