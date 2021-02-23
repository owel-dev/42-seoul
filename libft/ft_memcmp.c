/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 20:19:28 by ulee              #+#    #+#             */
/*   Updated: 2021/02/14 05:25:33 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *first, const void *second, size_t byte_size)
{
	size_t				i;
	const unsigned char	*first_cast;
	const unsigned char	*second_cast;

	if (byte_size == 0)
		return (0);
	first_cast = first;
	second_cast = second;
	i = 0;
	while (i < byte_size - 1)
	{
		if (first_cast[i] != second_cast[i])
			return (first_cast[i] - second_cast[i]);
		i++;
	}
	return (first_cast[i] - second_cast[i]);
}
