/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 20:19:32 by ulee              #+#    #+#             */
/*   Updated: 2020/11/15 19:09:39 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	unsigned char		*c_dst;
	unsigned char		*c_src;

	if (dst == NULL && src == NULL)
		return (NULL);
	if (dst < src)
	{
		c_dst = (unsigned char *)dst;
		c_src = (unsigned char *)src;
		while (n--)
			*c_dst++ = *c_src++;
	}
	else
	{
		c_dst = (unsigned char *)dst + (n - 1);
		c_src = (unsigned char *)src + (n - 1);
		while (n--)
			*c_dst-- = *c_src--;
	}
	return (dst);
}
