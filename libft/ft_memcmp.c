/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 20:19:28 by ulee              #+#    #+#             */
/*   Updated: 2020/11/06 16:10:45 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*c_s1;
	unsigned char	*c_s2;
	size_t			i;

	if (n == 0)
		return (0);
	c_s1 = (unsigned char *)s1;
	c_s2 = (unsigned char *)s2;
	i = 0;
	while (i < n - 1)
	{
		if (*c_s1 != *c_s2)
			return (*c_s1 - *c_s2);
		c_s1++;
		c_s2++;
		i++;
	}
	return (*c_s1 - *c_s2);
}
