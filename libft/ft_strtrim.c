/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 20:20:29 by ulee              #+#    #+#             */
/*   Updated: 2020/11/22 17:08:04 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *str, char const *remove_char)
{
	const char	*str_end;
	size_t		len;
	char		*result;

	if (str == NULL)
		return (NULL);
	if (remove_char == NULL)
		return (ft_strdup(str));
	while (*str != '\0' && ft_strchr(remove_char, *str) != NULL)
		str++;
	str_end = str + (ft_strlen(str) - 1);
	while (*str != '\0' && ft_strrchr(remove_char, *str_end) != NULL)
		str_end--;
	len = str_end - str + 2;
	result = (char *)malloc(sizeof(char) * len);
	if (result == NULL)
		return (NULL);
	ft_strlcpy(result, str, len);
	return (result);
}
