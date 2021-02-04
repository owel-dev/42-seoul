#include "ft_printf.h"


void check_flag(char **percent, char c, t_flags *flags, int isdot)
{
    if (**percent == c)
    {
        if (c == '-')
			flags->width_minus = 1;
        else if (c == '*')
        {
            if (isdot)
                flags->dot_star = 1;
            else
                flags->star = 1;
        }
        else if (c == '.')
            flags->dot = 1;
        (*percent)++;
    }
}

void check_width(char **percent, t_flags *flags, int isdot)
{
    if (!isdot)
    {
        while (ft_isdigit(**percent))
        {
            if (!flags->width && **percent - '0' == 0)
                flags->zero = 1;
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

void check_format(char **percent, t_flags *flags)
{
    check_flag(percent, '-', flags, 0);
    check_width(percent, flags, 0);
    check_flag(percent, '*', flags, 0);
    check_flag(percent, '.', flags, 0);
    check_width(percent, flags, 1);
    check_flag(percent, '*', flags, 1);
	if (flags->zero && flags->width_minus)
	{
		flags->zero = 0;
		flags->width_minus = 0;
	}
}