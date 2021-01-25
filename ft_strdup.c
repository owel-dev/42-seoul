/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 20:19:56 by ulee              #+#    #+#             */
/*   Updated: 2020/11/22 16:01:35 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*result;
	int		len;

	len = ft_strlen(s);
	if (!(result = malloc(sizeof(char) * (len + 1))))
		return (0);
	ft_memcpy(result, s, len);
	result[len] = 0;
	return (result);
}
