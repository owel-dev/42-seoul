#include "ft_printf.h"

void set_star(va_list ap, t_flags *flags)
{
    int arg;

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

void set_arg(char *percent, char **arg, va_list ap, t_flags *flags)
{
    if (*percent == 'd' || *percent == 'i')
        *arg = set_long(va_arg(ap, int), flags);
    else if (*percent == 'u')
        *arg = set_long(va_arg(ap, unsigned int), flags);
    else if (*percent == 'c')
    {
        *arg = set_char(va_arg(ap, int), flags);
        if (ft_strlen(*arg) == 0)
            flags->width--;
    }
    else if (*percent == 's')
        *arg = set_string(va_arg(ap, char *), flags);
    else if (*percent == 'x')
    {
        *arg = set_hex(va_arg(ap, unsigned int), 'x');
    }
    else if (*percent == 'X')
        *arg = set_hex(va_arg(ap, unsigned int), 'X');
    else if (*percent == 'p')
        *arg = set_add(va_arg(ap, void *), 'x');
    else if (*percent == '%')
    {

    }
        // *arg = set_hex(va_arg(ap, void *), 'X');
	// printf("\n*arg: %s\n", *arg);
    
}

void set_width(t_flags *flags, int len)
{
    flags->dot_width = flags->dot_width - len;
    if (flags->dot_width < 0)
        flags->width = flags->width - len;
    else
        flags->width = flags->width - flags->dot_width - len;
    // printf("\nwidth: %d\n", flags->width);
    // printf("\ndot_width: %d\n", flags->dot_width);
}




void set_format(char *percent, char **arg, t_flags *flags, va_list ap)
{
    set_star(ap, flags);
    set_arg(percent, arg, ap, flags);
    set_width(flags, ft_strlen(*arg));
}