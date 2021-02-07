#include "ft_printf.h"

int		ft_isdigit(int c)
{
	return ('0' <= c && c <= '9');
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
