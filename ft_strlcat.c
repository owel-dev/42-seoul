/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 20:20:00 by ulee              #+#    #+#             */
/*   Updated: 2020/11/06 19:33:52 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *d, const char *s, size_t dstsize)
{
	size_t d_len;
	size_t s_len;
	size_t i;
	size_t j;

	d_len = ft_strlen(d);
	s_len = ft_strlen(s);
	j = d_len;
	i = 0;
	if (d_len + 1 < dstsize && 0 < dstsize)
	{
		while (s[i] && d_len + i + 1 < dstsize)
		{
			d[j] = s[i];
			j++;
			i++;
		}
		d[j] = 0;
	}
	if (d_len >= dstsize)
		d_len = dstsize;
	return (d_len + s_len);
}
