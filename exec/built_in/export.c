/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douattar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 10:43:00 by douattar          #+#    #+#             */
/*   Updated: 2022/05/20 14:47:39 by douattar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	len(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != '+' && str[i] != '=')
		i++;
	return (i);
}

// This function change the content of variable.
static void	change(char **arg, t_env *env)
{
	int		i;
	int		l;
	char	*temp;

	i = 0;
	while (arg[i] != NULL)
	{
		l = ft_strlen(env->name);
		if (arg[i][0] == '\0' || l != len(arg[i]))
		{
			i++;
			continue ;
		}
		if (ft_strncmp(arg[i], env->name, l) == 0)
		{
			temp = env->content;
			if (arg[i][l] == '+')
				env->content = ft_strjoin(env->content, arg[i] + l + 2);
			else
				env->content = ft_strcpy(arg[i] + l + 1);
			free(temp);
			arg[i][0] = '\0';
		}
		i++;
	}
}

static void	add(char **arg, t_env **envp)
{
	t_env	*block;
	int		i;
	int		l;

	i = 0;
	while (arg[i] != NULL)
	{
		block = new_var(arg[i]);
		if (block == NULL)
		{
			i++;
			continue ;
		}
		block->next = *envp;
		*envp = block;
		l = len((*envp)->name);
		if (((*envp)->name)[l - 1] == '+')
			((*envp)->name)[l - 1] = '\0';
		i++;
	}
}

int	ft_export(char **arg, t_env **envp)
{
	t_env	*block;
	int		i;

	valid_params(arg);
	block = *envp;
	while (block != NULL)
	{
		change(arg, block);
		block = block->next;
	}
	i = 0;
	while (arg[i] != NULL && arg[i][0] == '\0')
		i++;
	if (arg[i] == NULL)
		return (0);
	add(arg, envp);
	return (0);
}
