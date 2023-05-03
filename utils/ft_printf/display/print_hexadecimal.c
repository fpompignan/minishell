/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hexadecimal.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douattar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 11:57:35 by douattar          #+#    #+#             */
/*   Updated: 2021/12/10 15:26:51 by douattar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"

int	display_hexadecimal(int nb, char c)
{
	return (print_int_to_hexadecimal((unsigned int)nb, c - 23));
}

int	print_int_to_hexadecimal(long unsigned int nb, char letter)
{
	char	texte[1];
	int		res;

	*texte = nb % 16 + '0';
	if (nb % 16 > 9)
		*texte += letter - '0' - 10;
	if (nb / 16 == 0)
	{
		write(1, texte, 1);
		return (1);
	}
	else
	{
		res = print_int_to_hexadecimal(nb / 16, letter);
		write(1, texte, 1);
		return (res + 1);
	}
}

int	display_pointeur(void *p)
{
	long unsigned int	res;

	res = (long unsigned int)p;
	write(1, "0x", 2);
	return (print_int_to_hexadecimal(res, 'a') + 2);
}
