/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 20:20:00 by ulee              #+#    #+#             */
/*   Updated: 2021/02/14 07:02:01 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *first, const char *second, size_t total_len)
{
	size_t	first_len;
	size_t	second_len;

	second_len = ft_strlen(second);
	first_len = ft_strlen(first);
	if (first_len >= total_len)
		return (total_len + second_len);
	if (first_len + second_len < total_len)
	{
		ft_memcpy(first + first_len, second, second_len);
		first[first_len + second_len] = '\0';
	}
	else
	{
		ft_memcpy(first + first_len, second, total_len - first_len - 1);
		first[total_len - 1] = '\0';
	}
	return (first_len + second_len);
}
