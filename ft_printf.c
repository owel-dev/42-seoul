#include "ft_printf.h"

// 메인 printf함수
int ft_printf(const char *s, ...)
{
    va_list ap;
    t_flags flags;
    int len;
    char *percent;
    char *arg;
    
    len = 0;
    va_start(ap, s);
    while ((percent = ft_strchr(s, '%')))
    {
        len += print_string(s, percent - s);
        // printf("\n1: %d\n",len);
        percent++;
        ft_memset(&flags, 0, sizeof(t_flags));
        check_format(&percent, &flags);
        set_format(percent, &arg, &flags, ap);
        len += print_format(&arg, &flags);
        // printf("\n2: %d\n",len);

        s = ++percent;
    }
    len += print_string(s, -1);
    // printf("\n3: %d\n",len);

    return (len);
}
