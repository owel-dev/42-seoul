/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 20:19:23 by ulee              #+#    #+#             */
/*   Updated: 2021/05/19 11:22:31 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *copy, const void *origin, int target, \
	size_t byte_size)
{
	unsigned char		*copy_cast;
	const unsigned char	*origin_cast;
	unsigned char		target_cast;
	size_t				i;

	copy_cast = copy;
	origin_cast = origin;
	target_cast = target;
	i = 0;
	while (i < byte_size)
	{
		copy_cast[i] = origin_cast[i];
		if (copy_cast[i] == target_cast)
			return (copy + (i + 1));
		i++;
	}
	return (NULL);
}
