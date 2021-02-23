/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 20:18:25 by ulee              #+#    #+#             */
/*   Updated: 2021/02/13 03:03:28 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_bzero(void *array, size_t byte_size)
{
	size_t	i;

	i = 0;
	while (i < byte_size)
	{
		((unsigned char *)array)[i] = 0;
		i++;
	}
	return (array);
}
