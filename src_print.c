#include "ft_printf.h"

void print_width(t_flags *flags)
{
    if (flags->zero && !flags->dot)
    {
        while ((flags->width)-- > 0)
            write(1, "0", 1);
    }
    else
    {
        while ((flags->width)-- > 0)
            write(1, " ", 1);
    }
}

void print_dotwidth(t_flags *flags)
{
    if (flags->dot)
    {
        while ((flags->dot_width)-- > 0)
            write(1, "0", 1);
    }
}

int print_string(const char *s, int len)
{
    int i;

    i = 0;
    if (len < -1 || len == 0)
        return (0);
    while (*s && (i < len || len == -1))
    {
        write(1, s, 1);
        s++;
        i++;
    }
    return (i);
}

int print_format(char *percent, char **arg, t_flags *flags, va_list ap)
{
    int len;

    if (flags->minus)
        write(1, "-", 1);
    if (!flags->width_minus)
    {
        print_width(flags);
        print_dotwidth(flags);
        len = print_string(*arg, -1);
    }
    else
    {
        print_dotwidth(flags);
        len = print_string(*arg, -1);
        print_width(flags);
    }
    return (len);
}