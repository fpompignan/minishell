/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fassier- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:14:04 by fassier-          #+#    #+#             */
/*   Updated: 2022/05/16 14:40:50 by fassier-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	suite(char *str, int *i, int *count)
{
	if (str[*i - 1] != ' ' && str[*i - 1] != '<' && str[*i - 1] != '>')
	{
		*count = *count + 2;
		*i = *i + 1;
		if (str[*i] == '<' || str[*i] == '>')
			*i = *i + 1;
		while (str[*i] == ' ')
			*i = *i + 1;
	}	
	else
	{
		*i = *i + 1;
		if (str[*i] == '<' || str[*i] == '>')
			*i = *i + 1;
		if (str[*i] != ' ')
			*count = *count + 1;
	}
}

int	get_nb_tokens(t_process process)
{
	int		i;
	int		count;
	char	*line;

	line = f_strjoin("  ", process.str);
	i = forward_to_first_nonspace_char(line);
	count = 1;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '"')
			i = forward_to_next_quote(line, i);
		else if ((line[i] == ' ' || line[i] == '\t')
			&& (line[i + 1] != ' ' && line[i + 1] != '\0'))
		{
			count++;
			i++;
		}
		else if (line[i] == '>' || line[i] == '<')
			suite(line, &i, &count);
		else
			i++;
	}
	free(line);
	return (count);
}

static int	init_tokens(t_process *process)
{
	int	nb;
	int	i;

	nb = get_nb_tokens(*process);
	process->tokens = malloc(sizeof(t_token) * (nb + 1));
	if (process->tokens == NULL)
		return (0);
	i = 0;
	while (i <= nb)
	{
		process->tokens[i].word = NULL;
		process->tokens[i].type = 0;
		process->tokens[i].is_last = 0;
		i++;
	}
	process->tokens[nb].is_last = 1;
	return (1);
}

t_process	*get_token_init(t_process *process)
{
	int	i;

	i = 0;
	while (process[i].is_last == 0)
	{
		if (!init_tokens(&process[i]))
		{
			printf("minishell: error malloc\n");
			exit_minishell(process);
		}
		i++;
	}
	return (process);
}

t_process	*get_token_word(t_process *process)
{
	int		i;
	int		j;
	char	**tab_word;

	i = 0;
	while (process[i].is_last == 0)
	{
		tab_word = get_tab_word_for_token(process[i].str);
		if (tab_word == NULL)
			exit_minishell(process);
		j = 0;
		while (process[i].tokens[j].is_last == 0)
		{
			process[i].tokens[j].word = f_strdup(tab_word[j]);
			if (process[i].tokens[j].word == NULL)
				exit_minishell(process);
			j++;
		}
		free_array(tab_word);
		i++;
	}
	return (process);
}
