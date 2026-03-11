/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonsele <yoonsele@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 10:36:26 by yoonsele          #+#    #+#             */
/*   Updated: 2022/12/04 17:25:44 by yoonsele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../kernel.h"

int	ft_write_hex(unsigned long long nb, char *base)
{
	static int	cnt;

	cnt = 0;
	if (nb > 15)
		ft_write_hex(nb / 16, base);
	terminal_write_char(base[nb % 16]);
	cnt += 1;
	return (cnt);
}

int	ft_printf_p(va_list ap)
{
	void	*ptr;
	char	*base;

	ptr = (void *)va_arg(ap, void *);
	terminal_write_char('0');
	terminal_write_char('x');
	base = "0123456789abcdef";
	return (ft_write_hex((unsigned long long)ptr, base) + 2);
}

int	ft_printf_x(va_list ap)
{
	unsigned int	x;
	char			*base;

	x = va_arg(ap, unsigned int);
	base = "0123456789abcdef";
	return (ft_write_hex(x, base));
}

int	ft_printf_xx(va_list ap)
{
	unsigned int	xx;
	char			*base;

	xx = va_arg(ap, unsigned int);
	base = "0123456789ABCDEF";
	return (ft_write_hex(xx, base));
}
