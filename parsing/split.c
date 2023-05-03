/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fassier- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 17:06:17 by fassier-          #+#    #+#             */
/*   Updated: 2022/05/16 14:43:07 by fassier-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	char_is_separator(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i] != '\0')
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	if (c == '\0')
		return (1);
	return (0);
}

static int	count_words(char *str, char *charset)
{
	int	i;
	int	words;

	words = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (char_is_separator(str[i + 1], charset) == 1
			&& char_is_separator(str[i], charset) == 0)
			words++;
		i++;
	}
	return (words);
}

static void	write_word(char *dest, char *from, char *charset)
{
	int	i;

	i = 0;
	while (char_is_separator(from[i], charset) == 0)
	{
		dest[i] = from[i];
		i++;
	}
	dest[i] = '\0';
}

static int	write_split(char **split, char *str, char *charset)
{
	int		i;
	int		j;
	int		word;

	word = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (char_is_separator(str[i], charset) == 1)
			i++;
		else
		{
			j = 0;
			while (char_is_separator(str[i + j], charset) == 0)
				j++;
			split[word] = malloc(sizeof(char) * (j + 1));
			if (split[word] == NULL)
				return (1);
			write_word(split[word], str + i, charset);
			i += j;
			word++;
		}
	}
	return (0);
}

char	**f_split(char *str, char *charset)
{
	char	**res;
	int		words;

	words = count_words(str, charset);
	res = malloc(sizeof(char *) * (words + 1));
	if (res == NULL)
		return (NULL);
	res[words] = 0;
	if (write_split(res, str, charset) == 1)
	{
		free_array(res);
		return (NULL);
	}
	return (res);
}
