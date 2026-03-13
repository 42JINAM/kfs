#include "printf.h"

int	ft_format(const char **format, va_list ap)
{
	(*format)++;
	if (**format == 'c')
		return (ft_printf_c(ap));
	else if (**format == 's')
		return (ft_printf_s(ap));
	else if (**format == 'p')
		return (ft_printf_p(ap));
	else if (**format == 'x')
		return (ft_printf_x(ap));
	else if (**format == 'X')
		return (ft_printf_xx(ap));
	else if (**format == '%') {
		terminal_write_char('%');
		return (1);
	}
	else
		return (-1);
}

int printf_internal(const char *format, va_list ap)
{
    int len = 0;
    int tmp;

    while (*format)
    {
        if (*format == '%')
            tmp = ft_format(&format, ap);
        else
        {
            terminal_write_char(*format);
            tmp = 1;
        }
        len += tmp;
        format++;
    }
    return len;
}

int	printf(const char *format, ...)
{
	va_list	ap;
	int		len;

	va_start (ap, format);
	len = printf_internal(format, ap);
	va_end(ap);
	return (len);
}
