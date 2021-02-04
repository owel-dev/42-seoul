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