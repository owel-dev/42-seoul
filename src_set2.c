#include "ft_printf.h"

int 	check_len(long long n, t_flags *flags, int type)
{
	int 	len;
	
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

int 	check_strlen(t_flags *flags)
{
	int 	len;

	len = 0;
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
	return (len);
}
