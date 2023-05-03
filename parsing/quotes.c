/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fassier- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 15:09:22 by fassier-          #+#    #+#             */
/*   Updated: 2022/05/24 15:53:29 by fassier-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	remove_suite(int *k, char *str)
{
	int	i;
	int	quote;
	int	begin;

	i = *k;
	quote = str[i];
	while (str[i + 1] != quote)
	{
		str[i] = str[i + 1];
		i++;
	}
	str[i] = str[i + 2];
	begin = i;
	while (str[i + 2] != '\0')
	{
		str[i] = str[i + 2];
		i++;
	}
	str[i] = '\0';
	*k = begin;
}

char	*remove_quotes_line(char *str)
{
	int	k;

	k = 0;
	while (str[k])
	{
		if ((str[k] == '\'' || str[k] == '"') && str[k + 1] != '\0')
			remove_suite(&k, str);
		else
			k++;
	}
	return (str);
}

/*char	*remove_quotes_line(char *str)
{
	int	k;

	k = 0;
	while (str[k])
	{
		if (str[k] == '\'' || str[k] == '"')
			remove_suite(&k, str);
		else
			k++;
	}
	return (str);
}*/

t_process	remove_quotes(t_process process)
{
	int	i;

	i = 0;
	while (process.tokens[i].is_last == 0)
	{
		process.tokens[i].word = remove_quotes_line(process.tokens[i].word);
		i++;
	}
	return (process);
}
