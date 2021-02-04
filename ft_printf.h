#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

typedef struct s_flags{
    int len;
    int minus;
    int zero;
    int width_minus;
    int width;
    int dot;
    int dot_width;
    int star;
    int dot_star;
} t_flags;

int     ft_printf(const char *s, ...);

int		ft_isdigit(int c);
void	*ft_memset(void *str, int c, size_t n);
void	*ft_memcpy(void *d, const void *s, size_t n);
char	*ft_strchr(const char *s, int c);
size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);


void    check_flag(char **percent, char c, t_flags *flags, int isdot);
void    check_width(char **percent, t_flags *flags, int isdot);
void    check_format(char **percent, t_flags *flags);


void    set_width(t_flags *flags, int len);
void    set_arg(char *percent, char **arg, va_list ap, t_flags *flags);
void    set_star(va_list ap, t_flags *flags);
void    set_format(char *percent, char **arg, t_flags *flags, va_list ap);


int	    itoa_len(long long num);
char    *set_long(long long n);
char    *set_char(int c, t_flags *flags);
char    *set_string(char *s, t_flags *flags);
char    *set_hex(size_t n, char type);
char    *set_add(void *add, char type);


void    print_width(t_flags *flags);
void    print_dotwidth(t_flags *flags);
int     print_string(const char *s, int len);
int     print_format(char *percent, char **arg, t_flags *flags, va_list ap);

