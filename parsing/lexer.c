/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fassier- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:35:19 by fassier-          #+#    #+#             */
/*   Updated: 2022/05/24 19:34:48 by fassier-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_process	*get_tokens(t_process *process, int *action)
{
	if (!check_error_redir(process))
	{
		*action = 0;
		return (process);
	}
	process = get_token_init(process);
	process = get_token_word(process);
	return (process);
}

t_process	*get_process(char *line, t_process *process)
{
	process = get_process_init(line, process);
	process = get_process_str(line, process);
	return (process);
}

static void	check_only_invisible(char *line, int *action)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\a' && line[i] != '\b'
			&& line[i] != '\t' && line[i] != '\n' && line[i] != '\r'
			&& line[i] != '\v' && line[i] != '\f')
			return ;
		i++;
	}
	*action = 0;
}

t_process	*lexer(char *line, t_process *process, int *action)
{
	check_only_invisible(line, action);
	if (*action == 0)
		return (process);
	process = get_process(line, process);
	process = get_tokens(process, action);
	return (process);
}
