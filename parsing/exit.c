/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fassier- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:18:13 by fassier-          #+#    #+#             */
/*   Updated: 2022/05/24 17:51:55 by fassier-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens[i].is_last == 0)
	{
		free(tokens[i].word);
		i++;
	}
	free (tokens);
}	

void	free_process(t_process *process)
{
	int	i;

	i = 0;
	if (process)
	{
		while (process[i].is_last == 0)
		{
			if (process[i].str)
				free(process[i].str);
			if (process[i].tokens)
				free_tokens(process[i].tokens);
			if (process[i].var_env)
				free_array(process[i].var_env);
			if (process[i].realname_env)
				free_array(process[i].realname_env);
			if (process[i].redir)
				free_array(process[i].redir);
			if (process[i].arguments)
				free_array(process[i].arguments);
			i++;
		}
		free(process);
		process = NULL;
	}
}

void	exit_minishell(t_process *process)
{
	printf("minishell: error malloc\n");
	free_process(process);
	exit(1);
}
