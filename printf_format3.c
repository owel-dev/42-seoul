/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src_types2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 03:03:04 by ulee              #+#    #+#             */
/*   Updated: 2021/02/10 03:46:17 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_num(t_flags *flags, size_t arg, char type)
{
	char	output;
	int		len;

	len = 1;
	if (type == 'd')
	{
		if (arg >= 10)
			len += print_num(flags, arg / 10, type);
		output = (arg % 10) + '0';
		write(1, &output, 1);
	}
	else if (type == 'u')
	{
		if ((unsigned int)arg >= 10)
			len += print_num(flags, (unsigned int)arg / 10, type);
		output = ((unsigned int)arg % 10) + '0';
		write(1, &output, 1);
	}
	return (len);
}

int	print_numhex(t_flags *flags, size_t arg, char type, char *base)
{
	int	len;

	len = 1;
	if ((type == 'X' || type == 'x') && arg == 0 && flags->dot && \
flags->dot_width == 0)
		return (0);
	if (type == 'p' && arg == 0)
		return (0);
	if (arg >= 16)
		len += print_numhex(flags, arg / 16, type, base);
	write(1, &base[arg % 16], 1);
	return (len);
}
