/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_determinate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douattar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 17:42:10 by douattar          #+#    #+#             */
/*   Updated: 2021/12/15 11:17:32 by douattar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	choose(const char *str, va_list ap)
{
	unsigned int	exp;

	exp = 0;
	if (*str == 'c')
		return (display_char((char)va_arg(ap, int)));
	else if (*str == 's')
		return (display_str((char *)va_arg(ap, char *)));
	else if (*str == 'd' || *str == 'i')
		return (display_decimal((int)va_arg(ap, int)));
	else if (*str == 'u')
		return (ft_putunsigned_fd((unsigned int)va_arg(ap, unsigned int)));
	else if (*str == 'x' || *str == 'X')
	{
		exp = (unsigned int)va_arg(ap, unsigned int);
		return (display_hexadecimal(exp, *str));
	}
	else if (*str == 'p')
		return (display_pointeur((void *)va_arg(ap, void *)));
	return (-1);
}
