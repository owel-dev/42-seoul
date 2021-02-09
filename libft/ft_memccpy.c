/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 20:19:23 by ulee              #+#    #+#             */
/*   Updated: 2020/11/15 16:56:21 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *d, const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*d2;
	unsigned char	*s2;
	unsigned char	c2;

	d2 = (unsigned char *)d;
	s2 = (unsigned char *)s;
	c2 = c;
	i = 0;
	while (i < n)
	{
		d2[i] = s2[i];
		if (s2[i] == c2)
		{
			return (d2 + (i + 1));
		}
		i++;
	}
	return (0);
}
