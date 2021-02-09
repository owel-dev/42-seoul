#include "ft_printf.h"

int 	ft_printf(const char *s, ...)
{
	va_list 	ap;
	t_flags 	flags;
	int 		len;
	char 		*percent;
	
	len = 0;
	va_start(ap, s);
	while ((percent = ft_strchr(s, '%')))
	{
		len += print_string(s, percent - s);
		ft_memset(&flags, 0, sizeof(t_flags));
		percent++;
		check_format(&percent, &flags);
		set_format(percent, &flags, ap);
		len += print_format(percent, &flags);
		s = ++percent;
	}
	len += print_string(s, -1);
	return (len);
}
