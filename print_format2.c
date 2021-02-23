/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src_types.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 03:00:33 by ulee              #+#    #+#             */
/*   Updated: 2021/02/10 03:45:15 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_int(t_flags *flags, char type)
{
	int			len;
	long long	num;

	len = 0;
	num = flags->arg;
	if (num == 0 && flags->dot && flags->dot_width == 0)
		return (0);
	len += print_num(flags, num, type);
	return (len);
}

int	print_char(t_flags *flags)
{
	char	c;

	c = flags->arg;
	if (c == 0)
	{
		write(1, "", 1);
		return (1);
	}
	write(1, &c, 1);
	return (1);
}

int	print_chars(t_flags *flags)
{
	char	*str;
	int		len;

	str = flags->string;
	len = 0;
	if (flags->dot)
	{
		while (str[len] && len < flags->dot_width)
			write(1, &str[len++], 1);
	}
	else
	{
		while (str[len])
			write(1, &str[len++], 1);
	}
	return (len);
}

int	print_hex(t_flags *flags, char type)
{
	int		len;
	char	*base;
	size_t	arg;

	len = 0;
	base = NULL;
	if (type == 'X')
		base = "0123456789ABCDEF";
	else if (type == 'x' || type == 'p')
	{
		base = "0123456789abcdef";
	}
	arg = (size_t)flags->arg;
	if (type == 'p')
	{
		len += write(1, "0x", 2);
		if (flags->arg == 0)
			len += write(1, "0", 1);
	}
	len += print_numhex(flags, arg, type, base);
	return (len);
}
