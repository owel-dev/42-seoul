#include "ft_printf.h"

int print_num(t_flags *flags, size_t arg, char type, char *base)
{
	char output;
    int len;

    len = 1;
    // printf("\narg: %d\n", arg);
    // printf("\ntype: %c\n", type);

    if (type == 'd')
    {
        if (arg >= 10)
            len += print_num(flags, arg / 10, type, base);
        output = (arg % 10) + '0';
        write(1, &output, 1);
    }
    else if (type == 'u')
    {
        if ((unsigned int)arg >= 10)
            len += print_num(flags, (unsigned int)arg / 10, type, base);
        output = ((unsigned int)arg % 10) + '0';
        write(1, &output, 1);
    }
    else if (type == 'x' || type == 'X' || type == 'p')
    {
        // printf("\narg: %d\n", arg);
        if (type == 'p' && arg == 0)
            return (len);
        if (arg >= 16)
		    len += print_num(flags, arg / 16, type, base);
        write(1, &base[arg % 16], 1);
    }
    return (len);
}

int print_int(t_flags *flags, char type)
{
    int len;
    long long num;
    char *base;

    base = NULL;
	len = 0;
    num = flags->arg;
    // printf("\narg: %u\n", num);
	if (num == 0 && flags->dot && flags->dot_width == 0)
		return (0);
    // printf("\narg: %d\n", arg);
    len += print_num(flags, num, type, NULL);
    return (len);
}

int print_char(t_flags *flags)
{
    size_t c;
    c = flags->arg;

    if (c == 0)
        return (0);
    write(1, &c, 1);
    return (1);
}

int print_chars(t_flags *flags)
{
    char *str;
    int len;

    str = flags->string;
    len = 0;
    if (flags->dot)
    {
        while (str[len] && len < flags->dot_width)
            write(1, &str[len++], 1);
    }
    else
    {
        while (str[len])
            write(1, &str[len++], 1);
    }
    return (len);
}

int print_hex(t_flags *flags, char type)
{
    int len;
    char *base;
    size_t arg;

    len = 0;
    base = NULL;
	if (type == 'X')
		base = "0123456789ABCDEF";
	else if (type == 'x' || type == 'p')
    {
		base = "0123456789abcdef";
    }
    arg = (size_t)flags->arg;
    if (type == 'p')
    {
        write(1, "0x", 2);
        if (flags->arg == 0)
            write(1, "0", 1);
    }
    len += print_num(flags, arg, type, base);
	return (len);
}