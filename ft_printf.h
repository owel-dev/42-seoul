#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

typedef struct s_flags{
    int len;
    int minus;
    int zero;
    int width;
    int dot;
    int dot_width;
    int star;
    int dot_star;
} t_flags;

int     ft_printf(const char *s, ...);
void	*ft_memset(void *str, int c, size_t n);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
int		ft_isdigit(int c);
int		ft_isspace(int c);
int		ft_atoi(const char *str);
char	*ft_strchr(const char *s, int c);
size_t	ft_strlen(const char *str);
void	ft_putnbr_fd(long long n, int fd);
int		itoa_len(long long num);
void    check_flag(char **percent, char c, t_flags *flags, int isdot);
void    check_disit(char **percent, t_flags *flags, int isdot);
int     set_arg_int(long long *arg, va_list ap);
int     set_arg_uint(long long *arg, va_list ap);


void    set_width(t_flags *flags, int len);
void    output_plus(t_flags *flags, long long arg);
void    output_minus(t_flags *flags, long long arg);
void    check_flag_width(char **percent, t_flags *flags);
int     putstr_count(const char *s, int len);
int     print_arg(char *percent, t_flags *flags, va_list ap);
void    has_star(va_list ap, t_flags *flags);

