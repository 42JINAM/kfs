/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonsele <yoonsele@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 10:36:26 by yoonsele          #+#    #+#             */
/*   Updated: 2022/12/13 16:57:11 by yoonsele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../kernel.h"

int	ft_printf_c(va_list ap)
{
	char	c;

	c = (char)va_arg(ap, int);
	terminal_write_char(c);
	return (1);
}

int	ft_printf_s(va_list ap)
{
	char	*s;

	s = va_arg(ap, char *);
	if (!s) {
		terminal_write_line("(null)");
		return (6);
	}
	else {
		terminal_write_line(s);
		return (strlen(s));
	}
}

// int	ft_printf_di(va_list ap)
// {
// 	int		d;
// 	char	*res;
// 	int		tmp;

// 	d = va_arg(ap, int);
// 	res = ft_itoa(d);
// 	if (!res)
// 		return (-1);
// 	terminal_write_line(res);
// 	tmp = strlen(res);
// 	free(res);
// 	return (tmp);
// }

// int	ft_printf_u(va_list ap)
// {
// 	unsigned int	u;
// 	int				tmp;
// 	char			*res;

// 	u = va_arg(ap, int);
// 	if (u == 0)
// 		res = ft_zero();
// 	else
// 		res = ft_utoa(u);
// 	if (!res)
// 		return (-1);
// 	terminal_write_line(res);
// 	tmp = strlen(res);
// 	free(res);
// 	return (tmp);
// }

