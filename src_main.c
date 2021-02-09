#include "ft_printf.h"


void check_format(char **percent, t_flags *flags)
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
    delete_multiflag(flags);
	if (flags->width_minus && flags->zero)
	{
		flags->width_minus = 0;
		flags->zero = 0;
	}
}

void set_format(char *percent, t_flags *flags, va_list ap)
{
    int len;

    set_star(ap, flags);
    set_arg(percent, flags, ap);
    len = set_len(percent, flags);
    set_width(flags, len);
}

int print_format(char *percent, t_flags *flags)
{
    int len;

	len = 0;
    if (flags->width_minus == 1)
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