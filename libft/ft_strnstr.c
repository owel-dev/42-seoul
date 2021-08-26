/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 20:20:24 by ulee              #+#    #+#             */
/*   Updated: 2021/02/15 04:53:38 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *part, size_t len)
{
	if (*part == '\0')
		return ((char *)str);
	while (len != 0 && *str)
	{
		while (*str && *part && *str == *part)
			part++;
		if (*part == '\0')
			return ((char *)str);
		len--;
		str++;
	}
	return (NULL);
}
