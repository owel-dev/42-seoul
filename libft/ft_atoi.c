/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 20:18:18 by ulee              #+#    #+#             */
/*   Updated: 2021/10/12 20:00:18 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	long long	num;
	int			is_minus;

	is_minus = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == '-')
		is_minus = 1;
	if (*str == '-' || *str == '+')
		str++;
	num = 0;
	while (ft_isdigit(*str))
	{
		num *= 10;
		num += *str - '0';
		if (num > 2147483648 && is_minus == 1)
			return (-1);
		if (num > 2147483647 && is_minus == 0)
			return (-1);
		str++;
	}
	if (is_minus)
		num *= -1;
	return (num);
}
