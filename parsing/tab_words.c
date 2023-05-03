/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_words.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fassier- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:00:10 by fassier-          #+#    #+#             */
/*   Updated: 2022/05/16 15:12:46 by douattar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*transform_space_in_quoteline(char *line)
{
	int		i;
	char	quote;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '"')
		{
			quote = line[i];
			i++;
			while (line[i] != quote)
			{
				if (line[i] == ' ')
					line[i] = '\n';
				i++;
			}
		}
		i++;
	}
	return (line);
}

static char	*retransform_space_in_quoteline(char *line)
{
	int		i;
	char	quote;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '"')
		{
			quote = line[i];
			i++;
			while (line[i] != quote)
			{
				if (line[i] == '\n')
					line[i] = ' ';
				i++;
			}
		}
		i++;
	}
	return (line);
}

static char	*transform_tab_in_space(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\t')
			line[i] = ' ';
		i++;
	}
	return (line);
}

char	**get_tab_word_for_token(char *line)
{
	char	*str;
	char	**result;
	int		i;

	str = put_space_close_redir(line);
	str = transform_tab_in_space(str);
	str = transform_space_in_quoteline(str);
	result = f_split(str, " ");
	if (result == NULL)
		return (NULL);
	i = 0;
	while (result[i])
	{
		result[i] = retransform_space_in_quoteline(result[i]);
		i++;
	}
	free(str);
	return (result);
}
