/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_format.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 02:42:13 by ulee              #+#    #+#             */
/*   Updated: 2021/05/19 11:28:01 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	set_star(va_list ap, t_flags *flags)
{
	int		arg;

	if (flags->star)
	{
		arg = va_arg(ap, int);
		if (arg < 0)
		{
			flags->zero = 0;
			flags->width_minus = 1;
			arg *= -1;
		}
		flags->width = arg;
	}
	if (flags->dot_star)
	{
		arg = va_arg(ap, int);
		flags->dot_width = arg;
	}
}

void	set_arg(char *percent, t_flags *flags, va_list ap)
{
	if (*percent == 's')
	{
		flags->string = va_arg(ap, char *);
		if (flags->string == NULL)
			flags->string = "(null)";
	}
	else if (*percent == 'd' || *percent == 'i' || *percent == 'c')
		flags->arg = va_arg(ap, int);
	else if (*percent == 'u' || *percent == 'x' || *percent == 'X')
		flags->arg = va_arg(ap, unsigned int);
	else if (*percent == 'p')
		flags->arg = (long long)va_arg(ap, void *);
	else if (*percent == '%')
		flags->arg = -1;
}

int		set_len(char *percent, t_flags *flags)
{
	int		len;

	len = 0;
	if (*percent == 's')
		len += check_strlen(flags);
	else if (*percent == 'd' || *percent == 'i' || *percent == 'u')
		len = check_len(flags->arg, flags);
	else if (*percent == 'c' || *percent == '%')
		len = 1;
	else if (*percent == 'x' || *percent == 'X')
		len = check_hexlen(flags->arg, flags);
	else if (*percent == 'p')
	{
		len = check_hexlen(flags->arg, flags);
		len += 2;
	}
	return (len);
}

void	set_width(t_flags *flags, int len)
{
	if (flags->minus)
		flags->width--;
	if (flags->zero && flags->dot && flags->dot_width >= 0)
	{
		flags->print_zero = flags->dot_width - len;
		if (flags->print_zero > 0)
			flags->print_space = flags->width - flags->dot_width;
		else
			flags->print_space = flags->width - len;
	}
	else if (flags->zero)
		flags->print_zero = flags->width - len;
	else if (flags->width && flags->dot)
	{
		flags->print_zero = flags->dot_width - len;
		if (flags->print_zero > 0)
			flags->print_space = flags->width - flags->dot_width;
		else
			flags->print_space = flags->width - len;
	}
	else
	{
		flags->print_space = flags->width - len;
		flags->print_zero = flags->dot_width - len;
	}
}
