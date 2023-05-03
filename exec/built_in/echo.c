/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douattar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 13:11:13 by douattar          #+#    #+#             */
/*   Updated: 2022/04/16 18:02:30 by douattar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	starting_point(char **str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i] != NULL && str[i][0] == '-' && str[i][1] != '\0')
	{
		j = 1;
		while (str[i][j] != '\0' && str[i][j] == 'n')
			j++;
		if (str[i][j] != '\0')
			break ;
		i++;
	}
	return (i);
}

int	ft_echo(char **str)
{
	int	i;
	int	n;

	if (str != NULL)
		i = starting_point(str);
	n = i;
	while (str[i] != NULL)
	{
		write(STDOUT_FILENO, str[i], ft_strlen(str[i]));
		i++;
		if (str[i] != NULL)
			write(STDOUT_FILENO, " ", 1);
	}
	if (n == 0)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}
