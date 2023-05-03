/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tab_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fassier- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 16:39:11 by fassier-          #+#    #+#             */
/*   Updated: 2022/05/16 15:11:49 by douattar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_redir_type(t_process *process, int i)
{
	if (process->tokens[i].type == 2 || process->tokens[i].type == 3
		|| process->tokens[i].type == 4 || process->tokens[i].type == 5)
		return (1);
	else
		return (0);
}

static void	ft_malloc_redir(t_process *process)
{
	process->redir = malloc(sizeof(char *)
			* (count_operator(process->str) + 1));
}

int	get_tab_redir(t_process *process)
{
	int	i;
	int	j;

	ft_malloc_redir(process);
	if (!process->redir)
		return (0);
	i = 0;
	j = 0;
	while (process->tokens[i].is_last == 0)
	{
		if (is_redir_type(process, i))
		{
			process->redir[j] = f_strjoin(process->tokens[i].word, " ");
			process->redir[j]
				= f_strjoin2(process->redir[j], process->tokens[i + 1].word);
			if (!process->redir[j])
				return (0);
			i = i + 2;
			j++;
		}
		else
			i++;
	}
	process->redir[j] = NULL;
	return (1);
}
