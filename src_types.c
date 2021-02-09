#include "ft_printf.h"

int 	print_num(t_flags *flags, size_t arg, char type)
{
	char 	output;
	int 	len;

	len = 1;
	if (type == 'd')
	{
		if (arg >= 10)
			len += print_num(flags, arg / 10, type);
		output = (arg % 10) + '0';
		write(1, &output, 1);
	}
	else if (type == 'u')
	{
		if ((unsigned int)arg >= 10)
			len += print_num(flags, (unsigned int)arg / 10, type);
		output = ((unsigned int)arg % 10) + '0';
		write(1, &output, 1);
	}
	return (len);
}

int 	print_numhex(t_flags *flags, size_t arg, char type, char *base)
{
	int 	len;

	len = 1;
	if ((type == 'X' || type == 'x') && arg == 0 && flags->dot && flags->dot_width == 0)
			return (0);
		if (type == 'p' && arg == 0)
			return (0);
		if (arg >= 16)
			len += print_numhex(flags, arg / 16, type, base);
		write(1, &base[arg % 16], 1);
	return (len);
	
}

int 	print_int(t_flags *flags, char type)
{
	int 		len;
	long long 	num;

	len = 0;
	num = flags->arg;
	if (num == 0 && flags->dot && flags->dot_width == 0)
		return (0);
	len += print_num(flags, num, type);
	return (len);
}

int print_char(t_flags *flags)
{
	char c;
	c = flags->arg;
	if (c == 0)
	{
		write(1, "", 1);
		return (1);
	}
	write(1, &c, 1);
	return (1);
}

int 	print_chars(t_flags *flags)
{
	char 	*str;
	int 	len;

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

int 	print_hex(t_flags *flags, char type)
{
	int 	len;
	char 	*base;
	size_t 	arg;

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
		len += write(1, "0x", 2);
		if (flags->arg == 0)
			len += write(1, "0", 1);
	}
	len += print_numhex(flags, arg, type, base);
	return (len);
}