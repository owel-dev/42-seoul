/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 20:19:30 by ulee              #+#    #+#             */
/*   Updated: 2020/11/15 19:09:21 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *d, const void *s, size_t n)
{
	size_t			i;
	unsigned char	*d2;
	unsigned char	*s2;

	if (d == 0 && s == 0)
		return (d);
	d2 = (unsigned char *)d;
	s2 = (unsigned char *)s;
	i = 1;
	while (i <= n)
	{
		*d2++ = *s2++;
		i++;
	}
	return (d);
}
