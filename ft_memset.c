/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 20:19:35 by ulee              #+#    #+#             */
/*   Updated: 2021/02/13 03:03:24 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *array, int value, size_t byte_size)
{
	size_t	i;

	i = 0;
	while (i < byte_size)
	{
		((unsigned char *)array)[i] = value;
		i++;
	}
	return (array);
}
