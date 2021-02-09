/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 20:20:32 by ulee              #+#    #+#             */
/*   Updated: 2020/11/15 18:51:43 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t n)
{
	char	*result;
	size_t	i;
	size_t	len;

	if (s == NULL)
		return (NULL);
	if (!(result = malloc(sizeof(char) * (n + 1))))
		return (NULL);
	len = ft_strlen(s);
	i = 0;
	while (i < n && i + start < len)
	{
		result[i] = s[start + i];
		i++;
	}
	result[i] = 0;
	return (result);
}
