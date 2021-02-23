/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 20:19:32 by ulee              #+#    #+#             */
/*   Updated: 2021/02/15 04:56:04 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *copy, const void *origin, size_t byte_size)
{
	unsigned char			*copy_cast;
	const unsigned char		*origin_cast;

	if (copy == NULL && origin == NULL)
		return (NULL);
	if (copy < origin)
	{
		copy_cast = copy;
		origin_cast = origin;
		while (byte_size--)
			*copy_cast++ = *origin_cast++;
	}
	else
	{
		copy_cast = (unsigned char *)copy + (byte_size - 1);
		origin_cast = (unsigned char *)origin + (byte_size - 1);
		while (byte_size--)
			*copy_cast-- = *origin_cast--;
	}
	return (copy);
}
