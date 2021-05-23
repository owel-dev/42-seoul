/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 11:23:53 by ulee              #+#    #+#             */
/*   Updated: 2021/05/19 11:26:00 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		itoa_len(int num)
{
	int		len;

	len = 1;
	if (num < 0)
		len++;
	while ((num / 10) != 0)
	{
		num /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int num)
{
	char		*result;
	long long	num_cast;
	int			is_minus;
	int			len;

	is_minus = 0;
	num_cast = num;
	len = itoa_len(num);
	if (num_cast < 0)
	{
		num_cast *= -1;
		is_minus = 1;
	}
	result = (char *)malloc(sizeof(char) * (len + 1));
	if (result == NULL)
		return (NULL);
	result[len--] = 0;
	while (len >= 0)
	{
		result[len--] = num_cast % 10 + '0';
		num_cast /= 10;
	}
	if (is_minus)
		result[0] = '-';
	return (result);
}
