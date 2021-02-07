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
        len += print_string(s, percent - s);
        percent++;
        ft_memset(&flags, 0, sizeof(t_flags));
        check_format(&percent, &flags);
        set_format(percent, &flags, ap);
        len += print_format(percent, &flags);
        s = ++percent;
    }
    len += print_string(s, -1);
    return (len);
}
