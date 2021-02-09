/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 20:18:55 by ulee              #+#    #+#             */
/*   Updated: 2020/11/07 19:41:36 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		itoa_len(long long num)
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

char	*ft_itoa(int n)
{
	char		*result;
	long long	n_copy;
	int			minus;
	int			len;

	minus = 0;
	n_copy = n;
	len = itoa_len(n);
	if (n_copy < 0)
	{
		n_copy *= -1;
		minus = 1;
	}
	if (!(result = (char *)malloc(sizeof(char) * (len + 1))))
		return (0);
	result[len--] = 0;
	while (len >= 0)
	{
		result[len] = n_copy % 10 + '0';
		n_copy /= 10;
		len--;
	}
	if (minus)
		result[0] = '-';
	return (result);
}
