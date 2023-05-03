/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_in_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fassier- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 09:53:28 by fassier-          #+#    #+#             */
/*   Updated: 2022/05/25 09:53:41 by fassier-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_space(char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == ' ' && line[i + 1] != ' ')
			count++;
		i++;
	}
	return (count);
}

static char	**construction_tab(t_process process, int size, int to, int nb)
{
	char	**tab;
	int		i;
	int		j;
	int		k;
	char	**sp;

	tab = malloc(sizeof(char *) * (size + 1));
	sp = f_split(process.tokens[to].word, " ");
	i = 0;
	k = 0;
	while (k < nb)
	{
		if (i != to)
			tab[i++] = f_strdup(process.tokens[k++].word);
		else
		{
			j = 0;
			while (sp[j])
				tab[i++] = f_strdup(sp[j++]);
			k++;
		}	
	}
	tab[i] = NULL;
	free_array(sp);
	return (tab);
}

t_process	add_token(t_process process, int to)
{
	int		size;
	int		nb;
	char	**tab;
	int		i;

	nb = get_nb_tokens(process);
	size = nb + has_space(process.tokens[to].word);
	tab = construction_tab(process, size, to, nb);
	free_tokens(process.tokens);
	process.tokens = malloc(sizeof(t_token) * (size + 1));
	if (!process.tokens)
		exit_minishell(&process);
	i = 0;
	while (i <= size)
	{
		process.tokens[i].word = f_strdup(tab[i]);
		process.tokens[i].type = 0;
		process.tokens[i].is_last = 0;
		i++;
	}
	process.tokens[size].is_last = 1;
	free_array(tab);
	return (process);
}
