/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_process_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fassier- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:31:23 by fassier-          #+#    #+#             */
/*   Updated: 2022/05/16 14:39:50 by fassier-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_process(t_process *process)
{
	process->str = NULL;
	process->tokens = NULL;
	process->function = 0;
	process->is_last = 0;
	process->var_env = NULL;
	process->realname_env = NULL;
	process->fd_in = 0;
	process->fd_out = 0;
	process->redir = NULL;
	process->arguments = NULL;
}

int	forward_to_next_quote(char *line, int i)
{
	int	j;

	j = i + 1;
	while (line[j] != line[i])
		j++;
	return (j + 1);
}

t_process	*get_process_init(char *line, t_process *process)
{
	int	nb_process;
	int	i;

	nb_process = get_nb_process(line);
	process = malloc(sizeof(t_process) * (nb_process + 1));
	if (process == NULL)
	{
		printf("minishell: error: malloc fail\n");
		free(line);
		exit(1);
	}
	i = 0;
	while (i < nb_process)
		init_process(&process[i++]);
	process[nb_process].is_last = 1;
	return (process);
}

static void	maj(int *begin, int *i)
{
	*begin = *i + 1;
	*i = *i + 1;
}

t_process	*get_process_str(char *line, t_process *process)
{
	int	i;
	int	begin;
	int	k;

	i = 0;
	k = 0;
	begin = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '"')
		{
			i = forward_to_next_quote(line, i);
			if (line[i] == '\0')
				break ;
		}
		else if (line[i] == '|')
		{
			process[k++].str = ft_strndup_sp(line + begin, i - begin, process);
			maj(&begin, &i);
		}
		else
			i++;
	}
	process[k].str = ft_strndup_sp(line + begin, i - begin, process);
	return (process);
}
