#include "ft_printf.h"

// 메인 printf함수
int ft_printf(const char *s, ...)
{
    va_list ap;
    t_flags flags;
    int len;
    char *percent;
    
    len = 0;
    va_start(ap, s);
    while ((percent = ft_strchr(s, '%')))
    {
        len += putstr_count(s, percent - s);
        ft_memset(&flags, 0, sizeof(t_flags));
        percent++;
        check_flag_width(&percent, &flags);
        has_star(ap, &flags);
        len += print_arg(percent, &flags, ap);
        percent++;
        s = percent;
    }
    len += putstr_count(s, 0);
    return (len);
}
