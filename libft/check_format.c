/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 02:42:16 by ulee              #+#    #+#             */
/*   Updated: 2021/02/10 03:24:10 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	check_flag(char **percent, char c, t_flags *flags, int isdot)
{
	if (**percent == c)
	{
		if (c == '-')
			flags->width_minus++;
		else if (c == '*')
		{
			if (isdot)
				flags->dot_star++;
			else
				flags->star++;
		}
		else if (c == '.')
			flags->dot++;
		(*percent)++;
	}
}

void	check_width(char **percent, t_flags *flags, int isdot)
{
	if (!isdot)
	{
		while (ft_isdigit(**percent))
		{
			if (!flags->width && **percent - '0' == 0)
				flags->zero++;
			else
				flags->width = flags->width * 10 + **percent - '0';
			(*percent)++;
		}
		if (**percent == '-')
		{
			flags->dot_width = 1;
			(*percent)++;
		}
	}
	else
	{
		while (ft_isdigit(**percent))
		{
			flags->dot_width = flags->dot_width * 10 + **percent - '0';
			(*percent)++;
		}
	}
}
