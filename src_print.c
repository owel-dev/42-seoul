#include "ft_printf.h"

int 	print_string(const char *s, int len)
{
	int 	i;

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

int 	print_spaces(t_flags *flags)
{
	int 	len;

	len = 0;
	while (flags->print_space > 0)
	{
		write(1, " ", 1);
		len++;
		flags->print_space--;
	}
	return (len);
}

int 	print_zeros(t_flags *flags)
{
	int 	len;

	len = 0;
	while (flags->print_zero > 0)
	{
		write(1, "0", 1);
		len++;
		flags->print_zero--;
	}
	return (len);
}

int 	print_arg(char *percent, t_flags *flags)
{
	int 	len;

	len = 0;
	if (*percent == 'd' || *percent == 'i')
		len += print_int(flags, 'd');
	else if (*percent == 'u')
		len += print_int(flags, 'u');
	else if (*percent == 'c')
		len += print_char(flags);
	else if (*percent == 's')
		len += print_chars(flags);
	else if (*percent == 'x')
		len += print_hex(flags, 'x');
	else if (*percent == 'X')
		len += print_hex(flags, 'X');
	else if (*percent == 'p')
		len += print_hex(flags, 'p');
	else if (*percent == '%')
		len += write(1, "%", 1);
	return (len);
}


int 	print_minus(t_flags *flags, int position)
{
	int 	len;

	len = 0;
	if (flags->minus)
	{
		if (position == 0)
		{
			if (flags->print_zero > 0)
			{
				write(1, "-", 1);
				flags->minus = 0;
				len++;
			}
		}
		else if (position == 1)
		{
			write(1, "-", 1);
			len++;
		}
	}
	return (len);
}
