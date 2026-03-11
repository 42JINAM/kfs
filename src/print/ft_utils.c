/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonsele <yoonsele@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 10:36:26 by yoonsele          #+#    #+#             */
/*   Updated: 2022/12/13 16:57:01 by yoonsele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../kernel.h"

// char	*ft_zero(void)
// {
// 	char	*rtn;

// 	rtn = (char *)malloc(2);
// 	if (!rtn)
// 		return (0);
// 	rtn[0] = '0';
// 	rtn[1] = 0;
// 	return (rtn);
// }

// char	*ft_reverse(char *str)
// {
// 	int		len;
// 	int		i;
// 	char	*res;

// 	len = strlen(str);
// 	res = (char *)malloc(len + 1);
// 	if (!res)
// 		return (0);
// 	i = 0;
// 	while (i < len)
// 	{
// 		res[i] = str[len - i - 1];
// 		i++;
// 	}
// 	res[i] = 0;
// 	return (res);
// }

int	ft_find_digit(unsigned int n)
{
	int	cnt;

	cnt = 0;
	while (n)
	{
		n /= 10;
		cnt++;
	}
	return (cnt);
}

// char	*ft_utoa(unsigned int n)
// {
// 	int		digit;
// 	char	*res;
// 	char	*tmp;

// 	digit = ft_find_digit(n);
// 	res = (char *)malloc(sizeof(char) * (digit + 1));
// 	if (!res)
// 		return (0);
// 	tmp = res;
// 	tmp += (digit - 1);
// 	while (n)
// 	{
// 		*tmp = n % 10 + '0';
// 		tmp--;
// 		n /= 10;
// 	}
// 	res[digit] = 0;
// 	return (res);
// }
