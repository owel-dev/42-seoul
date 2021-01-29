#include "ft_printf.h"




// 메인 printf함수
int ft_printf(const char *s, ...)
{
    va_list ap;
    t_flags flags;
    int len = 0;
    char *percent;
    int arg;
    
    va_start(ap, s);
    while ((percent = ft_strchr(s, '%')))
    {
        len += putstr_count(s, percent - s);
        ft_memset(&flags, 0, sizeof(t_flags));
        percent++;
        check_string(&percent, &flags);
        if (*percent == 'd')
        {	
            get_width(&flags, get_arg(&arg, ap, &flags));
            if (!flags.minus)
                output_plus(&flags, arg);
            else
                output_minus(&flags, arg);
        }
        percent++;
        s = percent;
    }
    len += putstr_count(s, 0);
    return (len);
}

int main()
{
    ft_printf("ft_printf: hello [%10d] world\n", 7);
    printf("   printf: hello [%10d] world\n", 7);
    write(1, "\n", 1);

    ft_printf("ft_printf: hello [%4d] world\n", 77777);
    printf("   printf: hello [%4d] world\n", 77777);
    write(1, "\n", 1);

    ft_printf("ft_printf: hello [%-10d] world\n", 7);
    printf("   printf: hello [%-10d] world\n", 7);
    write(1, "\n", 1);

    ft_printf("ft_printf: hello [%-4d] world\n", 77777);
    printf("   printf: hello [%-4d] world\n", 77777);
    write(1, "\n", 1);

    ft_printf("ft_printf: hello [%.10d] world\n", 7);
    printf("   printf: hello [%.10d] world\n", 7);
    write(1, "\n", 1);

    ft_printf("ft_printf: hello [%.4d] world\n", 77777);
    printf("   printf: hello [%.4d] world\n", 77777);
    write(1, "\n", 1);

    ft_printf("ft_printf: hello [%10.6d] world\n", 7);
    printf("   printf: hello [%10.6d] world\n", 7);
    write(1, "\n", 1);

    ft_printf("ft_printf: hello [%-10.6d] world\n", 7);
    printf("   printf: hello [%-10.6d] world\n", 7);
    write(1, "\n", 1);

    ft_printf("ft_printf: hello [%*d] world\n", 10, 7);
    printf("   printf: hello [%*d] world\n", 10, 7);
    write(1, "\n", 1);

    ft_printf("ft_printf: hello [%*d] world\n", -10, 7);
    printf("   printf: hello [%*d] world\n", -10, 7);
    write(1, "\n", 1);

    ft_printf("ft_printf: hello [%.*d] world\n", 10, 7);
    printf("   printf: hello [%.*d] world\n", 10, 7);
    write(1, "\n", 1);

    ft_printf("ft_printf: hello [%0*d] world\n", 10, 7);
    printf("   printf: hello [%0*d] world\n", 10, 7);
    write(1, "\n", 1);

    ft_printf("ft_printf: hello [%*.*d] world\n", 10, 2, 777);
    printf("   printf: hello [%*.*d] world\n", 10, 2, 777);
    write(1, "\n", 1);

    ft_printf("ft_printf: hello [%*.*d] world\n", -10, 2, 777);
    printf("   printf: hello [%*.*d] world\n", -10, 2, 777);
    write(1, "\n", 1);

    ft_printf("ft_printf: hello [%-4.7d] world\n",12345);
    printf("   printf: hello [%-4.7d] world\n",12345);
    write(1, "\n", 1);

    ft_printf("ft_printf: hello [%-7.3d] world\n",12345);
    printf("   printf: hello [%-7.3d] world\n",12345);
    write(1, "\n", 1);

    ft_printf("ft_printf: hello [%010.7d] world\n",12345);
    printf("   printf: hello [%010.7d] world\n",12345);
    write(1, "\n", 1);

    ft_printf("ft_printf: hello [%010.3d] world\n",12345);
    printf("   printf: hello [%010.3d] world\n",12345);
    write(1, "\n", 1);
}