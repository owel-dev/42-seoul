/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 20:19:25 by ulee              #+#    #+#             */
/*   Updated: 2021/02/15 04:54:54 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *array, int target, size_t byte_size)
{
	while (byte_size != 0)
	{
		if (*(const unsigned char *)array == (unsigned char)target)
			return ((void *)array);
		byte_size--;
		array++;
	}
	return (NULL);
}
