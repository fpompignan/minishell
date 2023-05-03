/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douattar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 09:26:01 by douattar          #+#    #+#             */
/*   Updated: 2022/05/19 17:03:17 by douattar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Create a name for a file
static char	*create_name(char *here, int n)
{
	char	*res;
	char	*temp;
	char	*number;

	temp = ft_strjoin("/tmp/", here);
	if (temp == NULL)
		return (NULL);
	if (n == 0)
		return (temp);
	number = ft_itoa(n);
	if (number == NULL)
	{
		free(temp);
		return (NULL);
	}
	res = ft_strjoin(temp, number);
	free(number);
	free(temp);
	return (res);
}

static int	count_here(char **redirect)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (redirect[i] != NULL)
	{
		if (ft_strncmp(redirect[i], "<< ", 3) == 0)
			res++;
		i++;
	}
	return (res);
}

// Create a temp file that doesn't exist
char	*create_temp(char *here)
{
	char	*file;
	int		i;

	file = NULL;
	i = 0;
	while (file == NULL)
	{
		file = create_name(here, i);
		if (file == NULL)
			return (NULL);
		if (access(file, F_OK) == 0)
		{
			free(file);
			file = NULL;
		}
		i++;
	}
	return (file);
}

// Knowing the number of heredoc possible
char	**heredoc_number(char **redirect)
{
	int		i;
	int		length;
	char	**res;

	length = count_here(redirect);
	if (length == 0)
		return ((char **)(NULL));
	res = (char **)malloc(sizeof(char *) * (length + 1));
	if (res == NULL)
		return (res);
	i = 0;
	while (i < length)
	{
		res[i] = NULL;
		i++;
	}
	res[i] = NULL;
	return (res);
}

void	destroy_heredoc(char **heredoc)
{
	int	i;

	if (heredoc == NULL)
		return ;
	i = 0;
	while (heredoc[i] != NULL)
	{
		unlink(heredoc[i]);
		i++;
	}
	free_double(heredoc);
}
