/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interrogation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fassier- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 16:17:15 by fassier-          #+#    #+#             */
/*   Updated: 2022/05/20 12:46:17 by fassier-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_process	rep2(t_process process, int to, int dollar)
{
	int		quote;
	char	*suite;
	char	*status;

	quote = quote_after_var(process, to, dollar);
	if (!quote)
	{
		process.tokens[to].word[dollar] = '\0';
		process.tokens[to].word
			= f_strjoin2(process.tokens[to].word, ft_itoa(g_global.old));
	}
	else
	{
		suite = f_strdup(process.tokens[to].word + quote + 1);
		process.tokens[to].word[dollar] = '\0';
		status = ft_itoa(g_global.old);
		process.tokens[to].word
			= f_strjoin2(process.tokens[to].word, status);
		process.tokens[to].word = f_strjoin2(process.tokens[to].word, suite);
		free(suite);
		free(status);
	}
	return (process);
}

int	is_point_inter(t_process process, int to, int dollar)
{
	if (process.tokens[to].word[dollar + 1] != '\0')
	{
		if (process.tokens[to].word[dollar + 1] == '?')
			return (1);
	}
	return (0);
}
