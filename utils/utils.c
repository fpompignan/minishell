/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douattar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 09:28:22 by douattar          #+#    #+#             */
/*   Updated: 2022/05/20 14:50:25 by douattar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strcpy(const char *str)
{
	int		i;
	char	*res;

	if (str == NULL)
		return (NULL);
	res = malloc(sizeof(char *) * (ft_strlen(str) + 1));
	i = 0;
	while (str[i] != '\0')
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

void	free_double(char **array)
{
	int	i;

	if (array == NULL)
		return ;
	i = 0;
	while (array[i] != NULL)
	{
		if (array[i] > (char *)0)
			free(array[i]);
		i++;
	}
	free(array);
}

char	**get_path(t_env *envp)
{
	while (envp != NULL)
	{
		if (ft_strncmp(envp->name, "PATH", 4) == 0)
			return (ft_split(envp->content, ':'));
		envp = envp->next;
	}
	return (NULL);
}
