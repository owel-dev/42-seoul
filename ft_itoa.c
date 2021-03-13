/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 20:18:55 by ulee              #+#    #+#             */
/*   Updated: 2021/03/14 03:51:33 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	itoa_len(int num)
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
	int			is_minus;
	int			len;

	is_minus = 0;
	n_copy = n;
	len = itoa_len(n);
	if (n_copy < 0)
	{
		n_copy *= -1;
		is_minus = 1;
	}
	result = (char *)malloc(sizeof(char) * (len + 1));
	if (result == NULL)
		return (NULL);
	result[len--] = 0;
	while (len >= 0)
	{
		result[len--] = n_copy % 10 + '0';
		n_copy /= 10;
	}
	if (is_minus)
		result[0] = '-';
	return (result);
}
