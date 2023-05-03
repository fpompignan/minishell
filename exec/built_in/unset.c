/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douattar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 14:59:55 by douattar          #+#    #+#             */
/*   Updated: 2022/05/23 11:10:30 by douattar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	delete_next(char **arg, t_env *next)
{
	int		i;
	int		l;
	t_env	*temp;

	i = 0;
	while (arg[i] != NULL && next->next != NULL)
	{
		l = (ft_strlen(next->next->name) == ft_strlen(arg[i]));
		if (l && !(arg[i][0] == '_' && arg[i][1] == '\0'))
		{
			if (ft_strncmp(arg[i], next->next->name, l) == 0)
			{
				temp = next->next;
				next->next = next->next->next;
				clear_env(temp);
				i = -1;
			}
		}
		i++;
	}
	return (next->next != NULL);
}

static int	delete_block(char **arg, t_env **env)
{
	int		i;
	int		l;
	t_env	*temp;

	i = 0;
	while (*env != NULL && arg[i] != NULL)
	{
		l = ft_strlen((*env)->name);
		if (l == ft_strlen(arg[i]) && ft_strncmp(arg[i], (*env)->name, l) == 0)
		{
			temp = *env;
			*env = (*env)->next;
			clear_env(temp);
			i = -1;
		}
		i++;
	}
	return (*env == NULL);
}

static void	error_unset(char *str)
{
	write(2, "minishell: unset: `", 19);
	write(2, str, ft_strlen(str));
	write(2, "': not a valid identifier\n", 26);
	g_global.status = 1;
	str[0] = '\0';
}

static int	valid(char **arg)
{
	int	i;
	int	j;

	i = 0;
	while (arg[i] != NULL)
	{
		j = 0;
		while (arg[i][j] != '\0')
		{
			if (j == 0 && arg[i][j] != '_')
			{
				if (!(ft_isalpha(arg[i][j])))
					break ;
			}
			else if ((!ft_isalnum(arg[i][j])) && arg[i][j] != '_')
				break ;
			j++;
		}
		if (arg[i][j] != '\0' || j == 0)
			error_unset(arg[i]);
		i++;
	}
	return (-1);
}

int	ft_unset(char **arg, t_env **env)
{
	t_env	*block;

	valid(arg);
	if (delete_block(arg, env))
		return (g_global.status);
	block = *env;
	while (delete_next(arg, block))
		block = block->next;
	return (g_global.status);
}
