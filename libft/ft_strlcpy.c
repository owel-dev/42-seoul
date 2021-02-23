/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 20:20:03 by ulee              #+#    #+#             */
/*   Updated: 2021/02/14 06:28:51 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *copy, const char *origin, size_t char_count)
{
	size_t	i;

	if (copy == NULL && origin == NULL)
		return (0);
	i = 0;
	if (char_count > 0)
	{
		while (i < (char_count - 1) && origin[i])
		{
			copy[i] = origin[i];
			i++;
		}
		copy[i] = '\0';
	}
	return (ft_strlen(origin));
}
