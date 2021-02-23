/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 20:18:55 by ulee              #+#    #+#             */
/*   Updated: 2021/02/15 04:58:46 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	itoa_len(int num)
{
	int	len;

	len = 1;
	if (num < 0)
		len++;
	while ((num / 10) != 0)
	{
		len++;
		num /= 10;
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
	result = (char *)calloc(sizeof(char), (len + 1));
	if (result == NULL)
		return (NULL);
	while (len != 0)
	{
		len--;
		result[len] = num_cast % 10 + '0';
		num_cast /= 10;
	}
	if (is_minus)
		result[0] = '-';
	return (result);
}
