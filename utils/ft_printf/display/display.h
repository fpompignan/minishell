/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douattar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 11:58:38 by douattar          #+#    #+#             */
/*   Updated: 2021/12/11 10:50:31 by douattar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPLAY_H
# define DISPLAY_H
# include "../ft_printf.h"

int	count_digit(int nb);
int	display_char(char c);
int	display_str(char *str);
int	display_decimal(int nb);
int	print_int_to_hexadecimal(long unsigned int nb, char letter);
int	display_hexadecimal(int nb, char c);
int	display_unsigned(unsigned int nb);
int	ft_putunsigned_fd(unsigned int nb);
int	print_int_to_hexadecimal(long unsigned int nb, char letter);
int	display_pointeur(void *p);
#endif
