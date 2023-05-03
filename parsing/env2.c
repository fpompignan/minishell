/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douattar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 15:08:06 by douattar          #+#    #+#             */
/*   Updated: 2022/05/24 19:22:00 by fassier-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	condition1(char **result, t_process *process)
{
	if (result == NULL)
		exit_minishell(process);
}

static char	**find_variables_env(char **env, t_process *process)
{
	char	**result;
	int		nb_var;
	int		i;
	int		j;

	nb_var = get_nb_variable_env(env);
	result = malloc(sizeof(char *) * (nb_var + 1));
	condition1(result, process);
	result[nb_var] = NULL;
	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] != '=')
			j++;
		result[i] = malloc(sizeof(char) * (j + 1));
		if (result[i] == NULL)
			exit_minishell(process);
		j = -1;
		while (env[i][++j] != '=')
			result[i][j] = env[i][j];
		result[i][j] = '\0';
		i++;
	}
	return (result);
}

t_process	*get_var_env(t_process *process, char **env)
{
	int	i;

	i = 0;
	while (process[i].is_last == 0)
		process[i++].var_env = find_variables_env(env, process);
	return (process);
}
