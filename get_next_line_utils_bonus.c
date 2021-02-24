/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 21:06:05 by ulee              #+#    #+#             */
/*   Updated: 2021/01/22 09:28:20 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (*str != '\0')
	{
		str++;
		len++;
	}
	return (len);
}

void 	*ft_memcpy(void *copy, const void *origin, size_t byte_size)
{
	size_t	i;

	if (copy == NULL && origin == NULL)
		return (copy);
	i = 0;
	while (i < byte_size)
	{
		((unsigned char *)copy)[i] = ((const unsigned char *)origin)[i];
		i++;
	}
	return (copy);
}

char	*ft_strchr(const char *str, int c)
{
	while (*str != c)
	{
		if (*str == '\0')
			return (NULL);
		str++;
	}
	return ((char *)str);
}

char	*ft_strdup(const char *s)
{
	char	*result;
	int		len;

	len = ft_strlen(s);
	result = malloc(sizeof(char) * (len + 1));
	if (result == NULL)
		return (NULL);
	ft_memcpy(result, s, len);
	result[len] = 0;
	return (result);
}

char	*ft_strjoin(char const *first, char const *second)
{
	char	*result;
	int		first_len;
	int		second_len;

	if (first == NULL && second == NULL)
		return (NULL);
	if (first == NULL || second == NULL)
	{
		if (first == NULL)
			return (ft_strdup(second));
		return (ft_strdup(first));
	}
	first_len = ft_strlen(first);
	second_len = ft_strlen(second);
	result = (char *)malloc(sizeof(char) * (first_len + second_len + 1));
	if (result == NULL)
		return (NULL);
	ft_memcpy(result, first, first_len);
	ft_memcpy(result + first_len, second, second_len + 1);
	result[first_len + second_len] = '\0';
	return (result);
}
