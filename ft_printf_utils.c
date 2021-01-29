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

void	ft_putnbr_fd(int n, int fd)
{
    if (fd < 0)
        return ;
    if (n == -2147483648)
    {
        write(fd, "-2147483648", 11);
        return ;
    }
    if (n < 0)
    {
        write(fd, "-", 1);
        n *= -1;
    }
    if (n >= 10)
        ft_putnbr_fd(n / 10, fd);
    ft_putchar_fd(n % 10 + '0', fd);
}

int		itoa_len(long long num)
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

void check_flag(char **percent, char c, t_flags *flags, int isdot)
{
    if (**percent == c)
    {
        if (c == '-')
            flags->minus = 1;
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

int get_arg(int *arg, va_list ap, t_flags *flags)
{
    if (flags->star)
    {
        *arg = va_arg(ap, int);
        if (*arg < 0)
        {
            flags->minus = 1;
            *arg *= -1;
        }
        flags->width = *arg;
    }

    if (flags->dot_star)
    {
        *arg = va_arg(ap, int);
        flags->dot_width = *arg;
    }

    *arg = va_arg(ap, int);
    return (itoa_len(*arg));
}

void set_width(t_flags *flags, int len)
{
    flags->dot_width = flags->dot_width - len;
    if (flags->dot_width < 0)
        flags->width = flags->width - len;
    else
        flags->width = flags->width - flags->dot_width - len;
}

void output_plus(t_flags *flags, int arg)
{
    if (flags->zero && !flags->dot)
    {
        while((flags->width)-- > 0)
            write(1, "0", 1);
    }
    else
    {
        while((flags->width)-- > 0)
            write(1, " ", 1);
    }
    if (flags->dot && flags->dot_width > 0)
    {
        while((flags->dot_width)-- > 0)
            write(1, "0", 1);
    }
    ft_putnbr_fd(arg, 1);
}

void output_minus(t_flags *flags, int arg)
{
    if (flags->dot && flags->dot > 0)
    {
        while ((flags->dot_width)-- > 0)
            write(1, "0", 1);
    }
    ft_putnbr_fd(arg, 1);
    if (flags->zero)
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

void check_flag_width(char **percent, t_flags *flags)
{
    check_flag(percent, '-', flags, 0);
    check_width(percent, flags, 0);
    check_flag(percent, '*', flags, 0);
    check_flag(percent, '.', flags, 0);
    check_width(percent, flags, 1);
    check_flag(percent, '*', flags, 1);
}

int putstr_count(const char *s, int len)
{
    int i;

    i = 0;
    while (*s && (i < len || len == 0))
    {
        write(1, s, 1);
        s++;
        i++;
    }
    return (i);
}

int print_arg(char *percent, t_flags *flags, va_list ap)
{
    int arg;
    if (*percent == 'd')
        {	
            set_width(flags, get_arg(&arg, ap, flags));
            if (!flags->minus)
                output_plus(flags, arg);
            else
                output_minus(flags, arg);
        }
    return (0);
}