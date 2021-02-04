#include "ft_printf.h"

void	*ft_memset(void *str, int c, size_t n)
{
    size_t i;

    i = 0;
    while (i < n)
    {
        ((char *)str)[i] = c;
        i++;
    }
    return (str);
}

void	ft_putchar_fd(char c, int fd)
{
    write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
    if (s == NULL)
        return (void)NULL;
    while (*s)
    {
        ft_putchar_fd(*s, fd);
        s++;
    }
}

int		ft_isdigit(int c)
{
    return ('0' <= c && c <= '9');
}

int		ft_isspace(int c)
{
    return (((9 <= c && c <= 13) || c == ' ') ? 1 : 0);
}

int		ft_atoi(const char *str)
{
    long sign;
    long num;

    while (ft_isspace(*str))
        str++;
    sign = 1;
    if (*str == '-')
        sign *= -1;
    if (*str == '-' || *str == '+')
        str++;
    num = 0;
    while (ft_isdigit(*str))
    {
        num *= 10;
        num += *str - '0';
        if (num > 2147483648 && sign == 1)
            return (-1);
        if (num > 2147483648 && sign == -1)
            return (0);
        str++;
    }
    return (num * sign);
}

char	*ft_strchr(const char *s, int c)
{
    while (*s != c)
    {
        if (!*s)
            return (0);
        s++;
    }
    return ((char *)s);
}

size_t	ft_strlen(const char *str)
{
    size_t len;

    len = 0;
    while (*str++)
        len++;
    return (len);
}

void	*ft_memcpy(void *d, const void *s, size_t n)
{
	size_t			i;
	unsigned char	*d2;
	unsigned char	*s2;

	if (d == 0 && s == 0)
		return (d);
	d2 = (unsigned char *)d;
	s2 = (unsigned char *)s;
	i = 1;
	while (i <= n)
	{
		*d2++ = *s2++;
		i++;
	}
	return (d);
}

char	*ft_strdup(const char *s)
{
	char	*result;
	int		len;

	len = ft_strlen(s);
	if (!(result = malloc(sizeof(char) * (len + 1))))
		return (0);
	ft_memcpy(result, s, len);
	result[len] = 0;
	return (result);
}

char			*ft_strjoin(char const *s1, char const *s2)
{
	char		*result;
	char		*result2;
	int			s1_len;
	int			s2_len;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	else if (s1 == NULL || s2 == NULL)
		return (s1 == NULL ? ft_strdup(s2) : ft_strdup(s1));
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	if (!(result = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1))))
		return (0);
	result2 = result;
	while (*s1)
		*result2++ = *s1++;
	while (*s2)
		*result2++ = *s2++;
	*result2 = 0;
	return (result);
}

size_t		ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t		i;

	if (dst == NULL && src == NULL)
		return (0);
	i = 0;
	if (size > 0)
	{
		while (src[i] && i + 1 < size)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = 0;
	}
	while (src[i])
		i++;
	return (i);
}

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

char    *set_long(long long n)
{
    int len;
	int negative;
    char *result;

	negative = 0;
	len = itoa_len(n);
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

char *set_char(int c)
{
    char *result;

    result = (char *)malloc(sizeof(char) * 2);
    result[0] = c;
    result[1] = 0;
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
    // printf("\nlen: %d\n", len);
    // printf("\nresult: %s\n", result);
    // printf("\nstring: %s\n", s);
    // printf("\ndot_width: %d\n", flags->dot_width);
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
    len = 1;
    n_copy = n;
    while ((n_copy / 16) != 0)
	{
		n_copy /= 16;
		len++;
	}
    buffer = (char *)malloc(sizeof(char) * len + 1);
    buffer[len] = 0;
	while (len--)
	{
		buffer[len] = hex[(n % 16)];
		n /= 16;
	}
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
    // printf("\nwidth: %d\n", flags->width);
    // printf("\ndot_width: %d\n", flags->dot_width);
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

void set_star(va_list ap, t_flags *flags)
{
    int arg;

    if (flags->star)
    {
        arg = va_arg(ap, int);
        if (arg < 0)
        {
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
    {
        *arg = set_long(va_arg(ap, int));
        // printf("\narg: %s\n", *arg);
    }
    else if (*percent == 'u')
        *arg = set_long(va_arg(ap, unsigned int));
    else if (*percent == 'c')
    {
        *arg = set_char(va_arg(ap, int));
        if (ft_strlen(*arg) == 0)
            flags->width--;
        flags->dot_width = 0;
        flags->dot = 0;
    }
    else if (*percent == 's')
    {
        *arg = set_string(va_arg(ap, char *), flags);
        flags->dot_width = 0;
        flags->dot = 0;
    }
    else if (*percent == 'x')
    {
        *arg = set_hex(va_arg(ap, size_t), 'x');
    }
    else if (*percent == 'X')
    {
        *arg = set_hex(va_arg(ap, size_t), 'X');
    }
    else if (*percent == 'p')
    {
        *arg = set_add(va_arg(ap, void *), 'x');
    }
    // else if (*percent == '%')
    // {
    //     *arg = set_hex(va_arg(ap, void *), 'X');
    // }
    // printf("\nlen: %d\n", ft_strlen(*arg));

}

void set_format(char *percent, char **arg, t_flags *flags, va_list ap)
{
    set_star(ap, flags);
    set_arg(percent, arg, ap, flags);
    // printf("\nprint: %s\n", *arg);
    // printf("\n###########\n");
    set_width(flags, ft_strlen(*arg));
    // printf("\nstrlen: %d\n", ft_strlen(*arg));
    // printf("\nc: %c\n", ft_strlen(**arg));

}

void print_width(t_flags *flags)
{
    // printf("\nwidth: %d\n", flags->width);
    // printf("\ndot_width: %d\n", flags->dot_width);
    // printf("\nzero: %d\n", flags->zero);
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

int print_format(char *percent, t_flags *flags, va_list ap)
{
    int len;
    char *arg;

    set_format(percent, &arg, flags, ap);
    if (flags->minus)
        write(1, "-", 1);
    if (!flags->width_minus)
    {
        print_width(flags);
        print_dotwidth(flags);
        len = print_string(arg, -1);
    }
    else
    {
        print_dotwidth(flags);
        len = print_string(arg, -1);
        print_width(flags);
    }
    return (len);
}
