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

void set_arg(char *percent, t_flags *flags, va_list ap)
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

int check_len(long long n, t_flags *flags, int type)
{
    int len;
    
    len = 1;
    if (type == 0)
    {
        if (n == 0 && flags->dot && flags->dot_width == 0)
            return (0);
        if (n < 0)
        {
            n *= -1;
            flags->arg *= -1;
            flags->minus = 1;
        }
        while ((n /= 10) != 0)
            len++;
    }
    else if (type == 1)
    {
        if (n == 0 && flags->dot && flags->dot_width == 0)
            return (0);
        while ((n /= 16) != 0)
            len++;
    }
    return (len);
}

int set_len(char *percent, t_flags *flags)
{
    int len;

    len = 0;
    if (*percent == 's')
    {
        if (flags->dot)
        {
            while (flags->string[len] && (len < flags->dot_width || flags->dot_width < 0))
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
    }
    else if (*percent == 'd' || *percent == 'i' || *percent == 'u')
    {
        // printf("\narg: %d\n", flags->arg);
        len = check_len(flags->arg, flags, 0);
    }
    else if (*percent == 'c' || *percent == '%')
        len = 1;
    else if (*percent == 'x' || *percent == 'X')
        len = check_len(flags->arg, flags, 1);
    else if (*percent == 'p')
    {
        len = check_len(flags->arg, flags, 1);
        len += 2;
    }
    return (len);
}


void set_width(t_flags *flags, int len)
{
    if(flags->minus)
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