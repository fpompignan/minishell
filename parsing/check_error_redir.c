/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error_redir.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fassier- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 15:24:48 by fassier-          #+#    #+#             */
/*   Updated: 2022/05/23 17:50:00 by fassier-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_error_redir1(t_process process)
{
	int	i;

	i = 0;
	while (process.str[i] != '\0')
		i++;
	i--;
	while (process.str[i] == ' ' || process.str[i] == '\t')
		i--;
	if (i > 2 && process.str[i] == '>' && process.str[i -1] == '>'
		&& process.str[i - 2] == '>' && process.str[i - 3] == '>')
		return (return_err(2, '>', '>'));
	if (i > 2 && process.str[i] == '<' && process.str[i -1] == '<'
		&& process.str[i - 2] == '<' && process.str[i - 3] == '<')
		return (return_err(1, '<', '<'));
	if (i > 1 && process.str[i] == '>' && process.str[i -1] == '<'
		&& process.str[i - 2] == '>')
		return (return_err(2, '<', '>'));
	if (i > 1 && process.str[i] == '>' && process.str[i -1] == '>'
		&& process.str[i - 2] == '>')
		return (return_err(1, '>', '>'));
	if (i > 1 && process.str[i] == '>' && process.str[i -1] == '<'
		&& process.str[i - 2] == '<')
		return (return_err(1, '>', '>'));
	return (1);
}

static int	check_error_redir2(t_process process)
{
	int	i;

	i = 0;
	while (process.str[i] != '\0')
		i++;
	i--;
	while (process.str[i] == ' ' || process.str[i] == '\t')
		i--;
	if (i > 0 && process.str[i] == '<' && process.str[i -1] == '>')
		return (return_err(1, '<', '<'));
	if (process.str[i] == '>' || process.str[i] == '<')
	{
		printf("minishell: syntax error near unexpected token 'newline'\n");
		g_global.status = 2;
		return (0);
	}
	return (1);
}

static int	check_error_redir3(t_process process)
{
	int	i;

	i = 0;
	while (process.str[i] != '\0')
	{
		if (process.str[i] == '\'' || process.str[i] == '"')
		{
			i = forward_to_next_quote(process.str, i);
			if (process.str[i] == '\0')
				break ;
			i--;
		}
		if (process.str[i] == '>')
		{
			if (!check_chevron_r(process, i))
				return (0);
		}
		if (process.str[i] == '<')
		{
			if (!check_chevron_l(process, i))
				return (0);
		}
		i++;
	}
	return (1);
}

int	check_error_redir(t_process *process)
{
	int	i;

	i = 0;
	while (process[i].is_last == 0)
	{	
		if (!check_error_redir1(process[i]) || !check_error_redir2(process[i])
			|| !check_error_redir3(process[i]))
			return (0);
		i++;
	}
	return (1);
}
