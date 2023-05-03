/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_clear.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douattar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 23:08:34 by douattar          #+#    #+#             */
/*   Updated: 2022/05/09 19:50:43 by douattar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_env(t_env *block)
{
	if (block == NULL)
		return ;
	if (block->content != NULL)
		free(block->content);
	if (block->name != NULL)
		free(block->name);
	free(block);
}

void	clear_tab(t_env	*start)
{
	if (start == NULL)
		return ;
	else
	{
		clear_tab(start->next);
		clear_env(start);
	}
}

int	number_element(t_env *start)
{
	int		res;

	res = 0;
	while (start != NULL)
	{
		start = start->next;
		res++;
	}
	return (res);
}

char	*line_env(t_env *start)
{
	char	*res;
	int		length;
	int		index;
	int		i;

	length = (ft_strlen(start->content) + ft_strlen(start->name) + 1);
	res = malloc(sizeof(char *) * (length + 1));
	index = 0;
	while (start->name[index] != '\0')
	{
		res[index] = start->name[index];
		index++;
	}
	res[index] = '=';
	index++;
	i = 0;
	while (start->content[i] != '\0')
	{
		res[index] = start->content[i];
		index++;
		i++;
	}
	res[index] = '\0';
	return (res);
}

char	**duplicate_env(t_env *start)
{
	char	**res;
	int		i;

	if (start == NULL)
		return ((char **)(NULL));
	res = malloc(sizeof(char **) * (number_element(start) + 1));
	i = 0;
	while (start != NULL)
	{
		res[i++] = line_env(start);
		start = start->next;
	}
	res[i] = NULL;
	return (res);
}
