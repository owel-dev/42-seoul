/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 21:47:47 by ulee              #+#    #+#             */
/*   Updated: 2021/07/22 23:31:52 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(char *one, char *two)
{
	int		i;

	i = 0;
	if (one == 0 || two == 0)
		return (-1);
	while (one[i] || two[i])
	{
		if (one[i] != two[i])
			return (one[i] - two[i]);
		i++;
	}
	if (one[i] == '\0' && two[i] == '\0')
		return (0);
	return (one[i] - two[i]);
}
