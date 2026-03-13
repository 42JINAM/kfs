#ifndef UTILS_H
# define UTILS_H

# include "../terminal.h"

# include <stdarg.h>
# include <stdint.h>
# include <stddef.h>

int	    printf(const char *format, ...);
int	    ft_printf_c(va_list ap);
int	    ft_printf_s(va_list ap);
int	    ft_printf_p(va_list ap);
int	    ft_printf_x(va_list ap);
int	    ft_printf_xx(va_list ap);
void    test_printf(void);

void*   memset(void* bufptr, int value, size_t size);
void*   memcpy(void	*restrict dstptr, const void	*restrict srcptr, size_t size);

size_t	strlen(const char	*str);

#endif
