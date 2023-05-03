/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_var_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fassier- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 17:00:13 by fassier-          #+#    #+#             */
/*   Updated: 2022/05/26 15:22:11 by fassier-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	find_variable_env(t_process process, int num_token, int dollar)
{
	char	*model;
	int		i;
	int		j;

	j = 0;
	model = NULL;
	if (process.tokens[num_token].word[dollar + 1] == '\0')
		return (-1);
	while (f_isalnum(process.tokens[num_token].word[dollar + 1 + j])
		|| process.tokens[num_token].word[dollar + 1 + j] == '_')
		j++;
	model = ft_strndup(process.tokens[num_token].word + dollar + 1, j);
	i = 0;
	while (process.var_env[i])
	{
		if (!ft_strcmp(process.var_env[i], model))
		{
			free(model);
			return (i);
		}
		i++;
	}
	free(model);
	return (-1);
}

static t_process	rep(t_process process, int to, int dollar, int var)
{
	int		quote;
	char	*suite;

	quote = quote_after_var(process, to, dollar);
	if (!quote)
	{
		process.tokens[to].word[dollar] = '\0';
		process.tokens[to].word
			= f_strjoin2(process.tokens[to].word, process.realname_env[var]);
		if (has_space(process.realname_env[var]))
			process = add_token(process, to);
	}
	else
	{
		suite = f_strdup(process.tokens[to].word + quote);
		process.tokens[to].word[dollar] = '\0';
		process.tokens[to].word
			= f_strjoin2(process.tokens[to].word, process.realname_env[var]);
		process.tokens[to].word = f_strjoin2(process.tokens[to].word, suite);
		free(suite);
		if (has_space(process.realname_env[var]))
			process = add_token(process, to);
	}
	return (process);
}

static t_process	rep3(t_process process, int to, int dollar, int *brake)
{
	int	i;
	int	space;

	i = has_quote(process, to, dollar);
	if (i == -1)
		process.tokens[to].word[dollar] = '\0';
	else
	{
		if (has_quote_before(process, to, dollar))
		{
			process.tokens[to].word
				= remove_quotes_line(process.tokens[to].word);
			space = find_space(process.tokens[to].word);
			if (space == 0)
				process.tokens[to].word[dollar - 1] = '\0';
			else if (space == dollar)
				process = manage(process, space, to, brake);
			else
				process = manage2(process, space, dollar, to);
		}
		else
			process = manage3(process, to, dollar, i);
	}
	return (process);
}

/*static t_process	rep3(t_process process, int to, int dollar, int *brake)
{
	int	i;
	int	space;
	char 	*suite;

	i = has_quote(process, to, dollar);
	if (i == -1)
		process.tokens[to].word[dollar] = '\0';
	else
	{
		if (has_quote_before(process, to, dollar))
		{
			process.tokens[to].word = remove_quotes_line(process.tokens[to].word);
			space = find_space(process.tokens[to].word);
			if (space == 0)
				process.tokens[to].word[dollar - 1] = '\0';
			else if (space == dollar)
			{
				suite = f_strdup(process.tokens[to].word + space);
				process.tokens[to].word[dollar] = '\0';
				process.tokens[to].word = f_strjoin2(process.tokens[to].word, suite);
				*brake = 1;
				free(suite);
			}
			else
			{
				suite = f_strdup(process.tokens[to].word + space);
				process.tokens[to].word[dollar - 1] = '\0';
				process.tokens[to].word = f_strjoin2(process.tokens[to].word, suite);
				free(suite);
			}
		}
		else
		{
		process.tokens[to].word[dollar] = '\0';
		process.tokens[to].word = f_strjoin2(process.tokens[to].word,
					remove_quotes_line(process.tokens[to].word + dollar + i));
		}
	}
	return (process);
}*/

static t_process	gestion_var_env(t_process process, int num_token)
{
	int	dollar;
	int	num_var;
	int	brake;

	brake = 0;
	dollar = find_dollar(process.tokens[num_token].word);
	while (dollar != -1)
	{
		num_var = find_variable_env(process, num_token, dollar);
		if (process.tokens[num_token].word[dollar + 1] == '\0')
			break ;
		else if (is_point_inter(process, num_token, dollar))
			process = rep2(process, num_token, dollar);
		else if (num_var != -1)
			process = rep(process, num_token, dollar, num_var);
		else
			process = rep3(process, num_token, dollar, &brake);
		if (brake)
			break ;
		dollar = find_dollar(process.tokens[num_token].word);
	}
	return (process);
}

t_process	*lexer2(t_process *process)
{
	int	i;
	int	j;

	i = 0;
	while (process[i].is_last == 0)
	{
		j = 0;
		while (process[i].tokens[j].is_last == 0)
		{
			process[i] = gestion_var_env(process[i], j);
			j++;
		}
		i++;
	}
	return (process);
}
