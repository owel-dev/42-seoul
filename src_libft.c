#include "ft_printf.h"

int		ft_isdigit(int c)
{
	return ('0' <= c && c <= '9');
}

int     ft_istype(int c)
{
    int i;
    int flag;
    char type[10] = "diucsxXp%";
    
    flag = 0;
    i = 0;
    while (type[i])
    {
        if (c == type[i])
            flag = 1;
        i++;
    }
    return (flag);
}

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

void delete_multiflag(t_flags *flags)
{
    if (flags->minus > 1)
        flags->minus = 0;
    if (flags->zero > 1)
        flags->zero = 0;
}
