/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   etc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 02:46:27 by ulee              #+#    #+#             */
/*   Updated: 2021/07/22 23:30:20 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_istype(int c)
{
	int		i;
	int		flag;
	char	*type;

	type = TYPE;
	flag = 0;
	i = 0;
	while (type[i])
	{
		if (c == type[i])
			flag = 1;
		i++;
	}
	return (flag);
}

int	check_len(long long n, t_flags *flags)
{
	int		len;

	len = 1;
	if (n == 0 && flags->dot && flags->dot_width == 0)
		return (0);
	if (n < 0)
	{
		n *= -1;
		flags->arg *= -1;
		flags->minus = 1;
	}
	while ((n / 10) != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

int	check_hexlen(long long n, t_flags *flags)
{
	int		len;

	len = 1;
	if (n == 0 && flags->dot && flags->dot_width == 0)
		return (0);
	while ((n / 16) != 0)
	{
		n /= 16;
		len++;
	}
	return (len);
}

int	check_strlen(t_flags *flags)
{
	int		len;

	len = 0;
	if (flags->dot)
	{
		while (flags->string[len] && (len < flags->dot_width || \
		flags->dot_width < 0))
			len++;
	}
	else
	{
		while (flags->string[len])
			len++;
	}
	if (flags->dot_width > len || flags->dot_width < 0)
	{
		flags->dot = 0;
		flags->dot_width = 0;
	}
	return (len);
}

void	delete_multiflag(t_flags *flags)
{
	if (flags->minus > 1)
		flags->minus = 0;
	if (flags->zero > 1)
		flags->zero = 0;
}
