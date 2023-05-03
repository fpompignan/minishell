/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_nbre_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fassier- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 13:52:37 by fassier-          #+#    #+#             */
/*   Updated: 2022/05/23 13:07:47 by fassier-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	display_error_quote(void)
{
	printf("Error: quote not closed\n");
	return (0);
}

static int	display_error_simple_pipe(void)
{
	printf("minishell: syntax error near unexpected token '|'\n");
	g_global.status = 2;
	return (1);
}

static int	display_error_double_pipe(void)
{
	printf("minishell: syntax error near unexpected token '||'\n");
	g_global.status = 2;
	return (1);
}

static int	syntax_error_pipe(char *line, int i)
{
	int	j;

	if (i == 0 && line[1] == '|')
		return (display_error_double_pipe());
	if (i == 0)
		return (display_error_simple_pipe());
	j = i - 1;
	while (line[j] == ' ')
		j--;
	if (line[j] == '|' || line[j] == '\0')
		return (display_error_simple_pipe());
	j = i + 1;
	while (line[j] == ' ')
		j++;
	if (line[j] == '|' || line[j] == '\0')
		return (display_error_simple_pipe());
	return (0);
}

/*static int	syntax_error_pipe(char *line, int i)
{
	int	error;
	int	j;

	error = 0;
	if (i == 0)
		return (display_error_double_pipe());
	if (i == 0)
		error = 1;
	j = i - 1;
	while (line[j] == ' ')
		j--;
	if (line[j] == '|' || line[j] == '\0')
		error = 1;
	j = i + 1;
	while (line[j] == ' ')
		j++;
	if (line[j] == '|' || line[j] == '\0')
		error = 1;
	if (error)
	{
		printf("minishell: syntax error near unexpected token '|'\n");
		g_global.status = 2;
		return (1);
	}
	return (0);
}*/

int	get_nb_process(char *line)
{
	char	quote;
	int		count;
	int		i;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '"')
		{
			quote = line[i++];
			while (line[i] && line[i] != quote)
				i++;
			if (!line[i])
				return (display_error_quote());
		}
		if (line[i] == '|')
		{
			if (syntax_error_pipe(line, i))
				return (0);
			count++;
		}
		i++;
	}
	return (count + 1);
}
