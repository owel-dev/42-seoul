#include "ft_printf.h"

int	itoa_len(long long num)
{
	int		len;

	len = 1;
	if (num < 0)
		len++;
	while ((num / 10) != 0)
	{
		num /= 10;
		len++;
	}
	return (len);
}

char    *set_long(long long n, t_flags *flags)
{
    int len;
	int negative;
    char *result;

	negative = 0;
	len = itoa_len(n);
	(void)flags;
	if (n == 0 && flags->dot && flags->dot_width == 0)
	{
		return (ft_strdup(""));
	}
	if (n < 0)
	{
        n *= -1;
		negative = 1;
	}
    if (!(result = (char *)malloc(sizeof(char) * (len + 1))))
		return (0);
    result[len] = 0;
	while (len--)
	{
		result[len] = n % 10 + '0';
		n /= 10;
	}
	if (negative)
		result[0] = '-';
    // printf("\nreturn: %s\n", result);
    return (result);
}

char *set_char(int c, t_flags *flags)
{
    char *result;

    result = (char *)malloc(sizeof(char) * 2);
    result[0] = c;
    result[1] = 0;
    
    flags->dot_width = 0;
    flags->dot = 0;
    return (result);
}

char *set_string(char *s, t_flags *flags)
{
    char *result;
    int len;

    len = ft_strlen(s);
    if (flags->dot)
    {
        if (flags->dot_width < len && flags->dot_width >= 0)
        {
            result = (char *)malloc(sizeof(char) * flags->dot_width + 1);
            ft_strlcpy(result, s, flags->dot_width + 1);
        }
        else
            result = ft_strdup(s);
    }
    else
        result = ft_strdup(s);
    flags->dot_width = 0;
    flags->dot = 0;
    return (result);
}

char *set_hex(size_t n, char type)
{
    char *hex;
    char *buffer;
    int len;
    size_t n_copy;

	if (type == 'X')
		hex = "0123456789ABCDEF";
	else
		hex = "0123456789abcdef";
    len = 0;
	// printf("\nn: %llu\n", n);
    n_copy = n;
    while (n_copy != 0)
	{
		n_copy /= 16;
		len++;
	}
	// printf("\nlen: %d\n", len);
    buffer = (char *)malloc(sizeof(char) * len + 1);
    buffer[len] = 0;
	while (len--)
	{
		buffer[len] = hex[(n % 16)];
		n /= 16;
	}
	// printf("\nbuffer: %s\n", buffer);
	return (buffer);
}

char *set_add(void *add, char type)
{
    size_t n;
    char *result;
    char *pre;

    n = (size_t)add;
    result = set_hex(n, type);
    pre = "0x";
    result = ft_strjoin(pre, result);
    return (result);
}