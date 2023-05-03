/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fassier- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 15:51:46 by fassier-          #+#    #+#             */
/*   Updated: 2022/05/26 15:10:21 by fassier-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_quote_before(t_process process, int to, int dollar)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	while (i < dollar)
	{
		if (process.tokens[to].word[i] == '"')
			quote++;
		i++;
	}
	if (quote % 2 == 1)
		return (1);
	return (0);
}

int	find_space(char *line)
{
	int	i;
	int	pass;

	i = 0;
	pass = 0;
	while (line[i])
	{
		if (line[i] == '$')
			pass = 1;
		if (line[i] == ' ' && pass == 1)
			return (i);
		i++;
	}
	return (0);
}

t_process	manage(t_process process, int space, int to, int *brake)
{
	char	*suite;

	suite = f_strdup(process.tokens[to].word + space);
	process.tokens[to].word[space] = '\0';
	process.tokens[to].word = f_strjoin2(process.tokens[to].word, suite);
	*brake = 1;
	free(suite);
	return (process);
}

t_process	manage2(t_process process, int space, int dollar, int to)
{
	char	*suite;

	suite = f_strdup(process.tokens[to].word + space);
	process.tokens[to].word[dollar - 1] = '\0';
	process.tokens[to].word = f_strjoin2(process.tokens[to].word, suite);
	free(suite);
	return (process);
}

t_process	manage3(t_process process, int to, int dollar, int i)
{
	process.tokens[to].word[dollar] = '\0';
	process.tokens[to].word = f_strjoin2(process.tokens[to].word,
			remove_quotes_line(process.tokens[to].word + dollar + i));
	return (process);
}
