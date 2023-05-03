/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_simple.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douattar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 11:57:43 by douattar          #+#    #+#             */
/*   Updated: 2021/12/11 09:55:14 by douattar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"

int	count_digit(int nb)
{
	if (nb <= 9 && nb >= -9)
		return (1);
	else
		return (count_digit(nb / 10) + 1);
}

int	display_char(char c)
{
	ft_putchar_fd(c, 1);
	return (1);
}

int	display_str(char *str)
{
	if (!str)
	{
		write(1, "(null)", 6);
		return (6);
	}
	if (*str == '\0')
		return (-1);
	ft_putstr_fd(str, 1);
	return (ft_strlen(str));
}

int	display_decimal(int nb)
{
	ft_putnbr_fd(nb, 1);
	return (count_digit(nb) + (nb < 0));
}

int	display_unsigned(unsigned int nb)
{
	ft_putnbr_fd((unsigned int)nb, 1);
	return (count_digit(nb));
}
