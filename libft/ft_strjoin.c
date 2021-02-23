/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 20:19:58 by ulee              #+#    #+#             */
/*   Updated: 2021/02/15 04:49:35 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
	ft_strlcpy(result + first_len, second, second_len + 1);
	return (result);
}
