#include "ft_printf.h"

int print_width(t_flags *flags)
{
	int len;

	len = 0;
    if (flags->zero && !flags->dot)
    {
        while ((flags->width)-- > 0)
		{
            write(1, "0", 1);
			len++;
		}
    }
    else
    {
        while ((flags->width)-- > 0)
		{
            write(1, " ", 1);
			len++;
		}
    }
	return (len);
}

int print_dotwidth(t_flags *flags)
{
	int len;

	len = 0;
    if (flags->dot)
    {
        while ((flags->dot_width)-- > 0)
		{
            write(1, "0", 1);
			len++;
		}
    }
	return (len);
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

int print_format(char **arg, t_flags *flags)
{
    int len;

	len = 0;
    if (flags->minus)
        write(1, "-", 1);
    if (!flags->width_minus)
    {
        len += print_width(flags);
        len += print_dotwidth(flags);
        len += print_string(*arg, -1);
    }
    else
    {
        len += print_dotwidth(flags);
        len += print_string(*arg, -1);
        len += print_width(flags);
    }
    return (len);
}