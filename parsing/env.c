/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fassier- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 13:01:11 by fassier-          #+#    #+#             */
/*   Updated: 2022/05/24 19:19:40 by fassier-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	find_suite(char **env, int i, char **result)
{
	int	j;
	int	k;

	j = 0;
	while (env[i][j] != '=')
		j++;
	j++;
	k = 0;
	while (env[i][j] != '\0')
	{
		result[i][k] = env[i][j];
		j++;
		k++;
	}
	result[i][k] = '\0';
}

static char	**find_realname_env(char **env, t_process *process)
{
	char	**result;
	int		nb_var;
	int		i;
	int		j;

	nb_var = get_nb_variable_env(env);
	result = malloc(sizeof(char *) * (nb_var + 1));
	if (result == NULL)
		exit_minishell(process);
	result[nb_var] = NULL;
	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] != '=')
			j++;
		result[i] = malloc(sizeof(char) * (f_strlen(env[i]) - j));
		if (result[i] == NULL)
			exit_minishell(process);
		find_suite(env, i, result);
		i++;
	}
	return (result);
}

/*static char	**find_realname_env(char **env, t_process *process)
{
	char	**result;
	int	nb_var;
	int	i;
	int	j;
	int	k;

	nb_var = get_nb_variable_env(env);
	result = malloc(sizeof(char *) * (nb_var + 1));
	if (result == NULL)
		exit_minishell(process);
	result[nb_var] = NULL;
	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] != '=')
			j++;
		result[i] = malloc(sizeof(char) * (ft_strlen(env[i]) - j));
		if (result[i] == NULL)
			exit_minishell(process);
		j = 0;
		while (env[i][j] != '=')
			j++;
		j++;
		k = 0;
		while (env[i][j] != '\0')
		{
			result[i][k] = env[i][j];
			j++;
			k++;
		}
		result[i][k] = '\0';
		i++;
	}
	return (result);
}*/

t_process	*get_realname_env(t_process *process, char **env)
{
	int	i;

	i = 0;
	while (process[i].is_last == 0)
		process[i++].realname_env = find_realname_env(env, process);
	return (process);
}
