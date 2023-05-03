/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douattar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 17:42:07 by douattar          #+#    #+#             */
/*   Updated: 2021/12/15 11:17:34 by douattar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	condition(int *i, const char *format, va_list *ap, int res);

int	ft_printf(const char *format, ...)
{
	int		i;
	int		res;
	va_list	ap;

	res = 0;
	i = 0;
	if (!format)
		return (-1);
	va_start(ap, format);
	while (format[i])
	{
		res = condition(&i, (const char *)format, &ap, res);
		i++;
	}
	return (res);
}

static int	condition(int *i, const char *format, va_list *ap, int res)
{
	int		number;

	number = 0;
	if (format[*i] == '%')
	{
		if (format[*i + 1] != format[*i])
		{
			number = choose(format + *i + 1, *ap);
			if (number == -1)
				number = 0;
			res += number;
		}
		else
		{
			write(1, "%", 1);
			res++;
		}
		*i += 1;
	}
	else
	{
		write(1, format + *i, 1);
		res++;
	}
	return (res);
}
