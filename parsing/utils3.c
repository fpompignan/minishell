/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fassier- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 12:34:19 by fassier-          #+#    #+#             */
/*   Updated: 2022/05/24 15:42:47 by fassier-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_dollar(char *str)
{
	int	i;
	int	quote;
	int	move;

	i = 0;
	quote = 0;
	while (str[i])
	{
		move = 0;
		if (str[i] == '"')
			quote++;
		if (str[i] == '\'' && quote % 2 == 0)
		{
			i = forward_to_next_quote(str, i);
			move = 1;
			if (str[i] == '\0')
				return (-1);
		}
		if (str[i] == '$')
			return (i);
		if (!move)
			i++;
	}
	return (-1);
}

/*int	find_dollar(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			i = forward_to_next_quote(str, i);
			if (str[i] == '\0')
				return (-1);
		}
		if (str[i] == '$')
			return (i);
		i++;
	}
	return (-1);
}*/

int	get_nb_variable_env(char **env)
{
	int	i;

	if (!env)
		return (0);
	i = 0;
	while (env[i])
		i++;
	return (i);
}

int	f_isalnum(char c)
{
	if (c >= 48 && c <= 57)
		return (1);
	if (c >= 65 && c <= 90)
		return (1);
	if (c >= 97 && c <= 122)
		return (1);
	return (0);
}

int	has_quote(t_process process, int to, int dollar)
{
	int	i;

	i = 0;
	while (process.tokens[to].word[dollar + i])
	{
		if (process.tokens[to].word[dollar + i] == '"'
			|| process.tokens[to].word[dollar + i] == '\'')
			return (i);
		i++;
	}
	return (-1);
}

int	quote_after_var(t_process process, int num_token, int dollar)
{
	int	j;

	j = 0;
	while (f_isalnum(process.tokens[num_token].word[dollar + 1 + j])
		|| process.tokens[num_token].word[dollar + 1 + j] == '_')
		j++;
	if (process.tokens[num_token].word[dollar + 1 + j] == '\0')
		return (0);
	return (dollar + 1 + j);
}
