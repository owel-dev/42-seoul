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

void check_flag(char **percent, char c, t_flags *flags)
{
    if (**percent == c)
    {
        if (c == '-')
            flags->minus = 1;
        else if (c == '*')
            flags->star = 1;
        else if (c == '.')
            flags->dot = 1;
        (*percent)++;
    }
}