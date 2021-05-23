/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_tree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 03:00:04 by ulee              #+#    #+#             */
/*   Updated: 2021/05/19 11:27:02 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		print_string(const char *str, int len)
{
	int		i;

	i = 0;
	if (len < -1 || len == 0)
		return (0);
	while (*str != '\0' && (i < len || len == -1))
	{
		write(1, str, 1);
		str++;
		i++;
	}
	return (i);
}

void	check_format(char **percent, t_flags *flags)
{
	while (!ft_istype(**percent))
	{
		check_flag(percent, '-', flags, 0);
		check_width(percent, flags, 0);
		check_flag(percent, '*', flags, 0);
		check_flag(percent, '.', flags, 0);
		check_width(percent, flags, 1);
		check_flag(percent, '*', flags, 1);
	}
	if (flags->width_minus && flags->zero)
		flags->zero = 0;
}

void	set_format(char *percent, t_flags *flags, va_list ap)
{
	int		len;

	set_star(ap, flags);
	set_arg(percent, flags, ap);
	len = set_len(percent, flags);
	set_width(flags, len);
}

int		print_format(char *percent, t_flags *flags)
{
	int		len;

	len = 0;
	if (flags->width_minus > 0)
	{
		len += print_minus(flags, 0);
		len += print_zeros(flags);
		len += print_minus(flags, 1);
		len += print_arg(percent, flags);
		len += print_spaces(flags);
	}
	else
	{
		len += print_spaces(flags);
		len += print_minus(flags, 0);
		len += print_zeros(flags);
		len += print_minus(flags, 1);
		len += print_arg(percent, flags);
	}
	return (len);
}
