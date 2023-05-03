/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fassier- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:39:14 by fassier-          #+#    #+#             */
/*   Updated: 2022/05/16 14:38:50 by fassier-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_process	find_token_function(t_process process)
{
	int	i;

	i = 0;
	while (process.tokens[i].is_last == 0)
	{
		if (process.tokens[i].type == WORD)
		{
			process.tokens[i].type = FUNCTION;
			break ;
		}
		i++;
	}
	return (process);
}

static t_process	get_token_function(t_process process, char *builtin[])
{
	int	i;
	int	j;

	i = 0;
	while (process.tokens[i].is_last == 0)
	{
		if (process.tokens[i].type == FUNCTION)
		{
			j = 0;
			while (builtin[j])
			{
				if (!ft_strcmp(builtin[j], process.tokens[i].word))
				{
					process.function = j + 2;
					return (process);
				}
				j++;
			}
			process.function = EXECVE;
			return (process);
		}
		i++;
	}
	process.function = NO_FUNCTION;
	return (process);
}

t_process	get_function(t_process process)
{
	char	*builtin[8];

	builtin[0] = "echo";
	builtin[1] = "cd";
	builtin[2] = "pwd";
	builtin[3] = "export";
	builtin[4] = "unset";
	builtin[5] = "env";
	builtin[6] = "exit";
	builtin[7] = NULL;
	process = find_token_function(process);
	process = get_token_function(process, builtin);
	return (process);
}
