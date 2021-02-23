/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 20:20:27 by ulee              #+#    #+#             */
/*   Updated: 2021/02/15 04:57:38 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int		str_len;
	char	*str_cast;

	str_len = ft_strlen(str);
	str_cast = (char *)str;
	if (c == '\0')
		return (str_cast + str_len);
	while (str_len != 0)
	{
		str_len--;
		if (str_cast[str_len] == c)
			return (&str_cast[str_len]);
	}
	return (NULL);
}
