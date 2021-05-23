/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 02:41:53 by ulee              #+#    #+#             */
/*   Updated: 2021/02/10 22:11:45 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf(const char *s, ...)
{
	va_list		ap;
	t_flags		flags;
	int			len;
	char		*percent;

	len = 0;
	va_start(ap, s);
	percent = ft_strchr(s, '%');
	while (percent != NULL)
	{
		len += print_string(s, percent - s);
		ft_memset(&flags, 0, sizeof(t_flags));
		percent++;
		check_format(&percent, &flags);
		set_format(percent, &flags, ap);
		len += print_format(percent, &flags);
		s = ++percent;
		percent = ft_strchr(s, '%');
	}
	len += print_string(s, -1);
	va_end(ap);
	return (len);
}
