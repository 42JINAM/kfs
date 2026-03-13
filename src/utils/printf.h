#ifndef PRINTF_H
# define PRINTF_H

# include <stdarg.h>

int	printf(const char *format, ...);
int	ft_printf_c(va_list ap);
int	ft_printf_s(va_list ap);
int	ft_printf_p(va_list ap);
int	ft_printf_x(va_list ap);
int	ft_printf_xx(va_list ap);

#endif
