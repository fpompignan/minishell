/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douattar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 12:39:52 by douattar          #+#    #+#             */
/*   Updated: 2022/05/23 14:16:07 by douattar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	error(char *str)
{
	write(2, "minishell: export: `", 20);
	write(2, str, ft_strlen(str));
	write(2, "': not a valid identifier\n", 26);
	g_global.status = 1;
	str[0] = '\0';
	return (1);
}

static int	check(int i, int j, char **arg)
{
	if (j == 0 && arg[i][j] != '_' && ft_isalpha(arg[i][j]) == FALSE)
	{
		error(arg[i]);
		arg[i][0] = '\0';
	}
	if (j > 0 && (!ft_isalnum(arg[i][j])) && arg[i][j] != '_')
	{
		if ((arg[i][j] != '+' || arg[i][j + 1] != '='))
		{
			error(arg[i]);
			arg[i][0] = '\0';
		}
	}
	return (arg[i][0] == '\0');
}

void	valid_params(char **arg)
{
	int	i;
	int	j;

	i = 0;
	while (arg[i] != NULL)
	{
		j = 0;
		while (arg[i][j] != '\0' && arg[i][j] != '=')
		{
			if (check(i, j, arg))
			{
				error(arg[i]);
				break ;
			}
			j++;
		}
		if (j == 0)
			error(arg[i]);
		else if (arg[i][j] != '=')
			arg[i][0] = '\0';
		i++;
	}
}
