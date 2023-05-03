/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error_redir2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fassier- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 13:10:34 by fassier-          #+#    #+#             */
/*   Updated: 2022/05/23 13:10:44 by fassier-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	return_err(int i, char c, char d)
{
	if (i == 1)
		printf("minishell: syntax error near unexpected token '%c'\n", c);
	if (i == 2)
		printf("minishell: syntax error near unexpected token '%c%c'\n", c, d);
	g_global.status = 2;
	return (0);
}

int	check_chevron_r(t_process process, int i)
{
	if (process.str[i + 1] == '<' && process.str[i + 2] == '>')
		return (return_err(2, '<', '>'));
	if (process.str[i + 1] == '<' && process.str[i + 2] == '<')
		return (return_err(2, '<', '<'));
	if (process.str[i + 1] == '<')
		return (return_err(1, '<', '<'));
	if (process.str[i + 1] == '>' && process.str[i + 2] == '>'
		&& process.str[i + 3] == '>')
		return (return_err(2, '>', '>'));
	if (process.str[i + 1] == '>' && process.str[i + 2] == '>')
		return (return_err(1, '>', '>'));
	return (1);
}

int	check_chevron_l(t_process process, int i)
{
	if (process.str[i + 1] == '<' && process.str[i + 2] == '<'
		&& process.str[i + 3] == '<')
		return (return_err(1, '<', '<'));
	if (process.str[i + 1] == '<' && process.str[i + 2] == '>'
		&& process.str[i + 3] == '>')
		return (return_err(2, '>', '>'));
	if (process.str[i + 1] == '<' && process.str[i + 2] == '<'
		&& process.str[i + 3] == '>')
		return (return_err(1, '>', '>'));
	if (process.str[i + 1] == '<' && process.str[i + 2] == '>')
		return (return_err(1, '>', '>'));
	if (process.str[i + 1] == '>' && process.str[i + 2] == '<')
		return (return_err(1, '<', '<'));
	if (process.str[i + 1] == '>' && process.str[i + 2] == '>')
		return (return_err(1, '>', '>'));
	return (1);
}
