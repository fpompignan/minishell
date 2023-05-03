/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fassier- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 15:52:27 by fassier-          #+#    #+#             */
/*   Updated: 2022/05/16 15:46:36 by douattar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_process	*got_env(t_process *process, char **env)
{
	process = get_var_env(process, env);
	process = get_realname_env(process, env);
	return (process);
}

int	count_arg(t_process *process)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (process->tokens[i].is_last == 0)
	{
		if (process->tokens[i].type == 0 || process->tokens[i].type == 1)
			count++;
		i++;
	}
	return (count);
}

int	get_tab_arg(t_process *process)
{
	int	i;
	int	j;

	process->arguments = malloc(sizeof(char *) * (count_arg(process) + 1));
	if (!process->arguments)
		return (0);
	i = 0;
	j = 0;
	while (process->tokens[i].is_last == 0)
	{
		if (process->tokens[i].type == 0 || process->tokens[i].type == 1)
		{
			process->arguments[j] = f_strdup(process->tokens[i].word);
			if (!process->arguments[j])
				return (0);
			j++;
		}
		i++;
	}
	process->arguments[j] = NULL;
	return (1);
}	

int	parser(t_process *process)
{
	int	i;

	i = 0;
	while (process[i].is_last == 0)
	{
		process[i] = get_operator(process[i]);
		if (!get_filename_type(&process[i]))
			return (0);
		process[i] = remove_quotes(process[i]);
		process[i] = get_function(process[i]);
		if (!get_tab_redir(&process[i]))
			exit_minishell(process);
		if (!get_tab_arg(&process[i]))
			exit_minishell(process);
		i++;
	}
	return (1);
}
