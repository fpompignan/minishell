/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_unsigned.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douattar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 15:23:14 by douattar          #+#    #+#             */
/*   Updated: 2021/12/10 15:23:16 by douattar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"

int	ft_putunsigned_fd(unsigned int nb)
{
	char	str[1];
	int		res;

	str[0] = nb % 10 + '0';
	if (nb < 10)
	{
		write(1, str, 1);
		return (1);
	}
	else
	{
		res = ft_putunsigned_fd(nb / 10);
		write(1, str, 1);
		return (res + 1);
	}
}
