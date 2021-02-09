/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 20:20:27 by ulee              #+#    #+#             */
/*   Updated: 2020/11/03 21:11:11 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	char	*str2;
	int		len;

	str2 = (char *)str;
	if (c == 0)
		return (str2 + ft_strlen(str));
	len = ft_strlen(str);
	while (len >= 0)
	{
		if (str[len] == c)
			return (&str2[len]);
		len--;
	}
	return (0);
}
