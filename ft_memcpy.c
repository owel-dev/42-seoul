/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 20:19:30 by ulee              #+#    #+#             */
/*   Updated: 2021/02/14 04:55:49 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
