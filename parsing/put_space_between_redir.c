/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_space_between_redir.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fassier- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 15:30:01 by fassier-          #+#    #+#             */
/*   Updated: 2022/05/16 14:42:38 by fassier-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_operator(char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '"')
			i = forward_to_next_quote(line, i);
		else if (line[i] == '<' || line[i] == '>')
		{
			count++;
			i++;
			if (line[i] == '<' || line[i] == '>')
				i++;
		}
		else
			i++;
	}
	return (count);
}

/*int    count_operator(char *line)
{
    int    i;
    int    count;

    i = 0;
    count    = 0;
    while (line[i])
    {
        if (line[i] == '\'' || line[i] == '"')
            i = forward_to_next_quote(line, i);
        else if (line[i] == '<' || line[i] == '>')
        {
		count++;
		i++;
            	if (line[i] == '<' || line[i] == '>')
                	i++;
        }
        else
            i++;
    }
    return (count);
}*/

static char	*put_space(char *result, char *line, int *i, int *j)
{
	if (line[*i + 1] == '<' || line[*i + 1] == '>')
	{
		result[*j] = ' ';
		result[*j + 1] = line[*i + 1];
		result[*j + 2] = line[*i + 1];
		result[*j + 3] = ' ';
		*j = *j + 4;
		*i = *i + 2;
	}
	else
	{
		result[*j] = ' ';
		result[*j + 1] = line[*i];
		result[*j + 2] = ' ';
		*j = *j + 3;
		*i = *i + 1;
	}
	return (result);
}

static char	*copy(char *result, char *line, int *i, int *j)
{
	result[*j] = line[*i];
	*i = *i + 1;
	*j = *j + 1;
	return (result);
}

static void	init_i_j_k(int *i, int *j, int *k)
{
	*i = 0;
	*j = 0;
	*k = 0;
}

char	*put_space_close_redir(char *line)
{
	char	*result;
	int		i;
	int		j;
	int		k;

	result = malloc (sizeof(char)
			* (f_strlen(line) + 1 + (2 * count_operator(line))));
	if (!result)
		return (NULL);
	init_i_j_k(&i, &j, &k);
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '"')
		{
			k = forward_to_next_quote(line, i);
			while (i < k)
				result = copy(result, line, &i, &j);
		}
		else if (line[i] == '<' || line[i] == '>')
			result = put_space(result, line, &i, &j);
		else
			result = copy(result, line, &i, &j);
	}
	result[j] = '\0';
	return (result);
}
