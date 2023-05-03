/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douattar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 14:31:48 by douattar          #+#    #+#             */
/*   Updated: 2022/05/18 12:35:17 by douattar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_strcopy(char *str, int l)
{
	char	*res;
	int		i;

	if (str == NULL)
		return (NULL);
	if (str[0] == '\0')
	{
		res = malloc(sizeof(char *));
		if (res == NULL)
			return (NULL);
		res[0] = '\0';
		return (res);
	}
	res = (char *)malloc(sizeof(char) * (l + 1));
	if (res == NULL)
		return (NULL);
	i = 0;
	while (str[i] != '\0' && i < l)
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

t_env	*new_var(char *variable)
{
	t_env	*res;
	int		i;

	if (variable == NULL)
		return (NULL);
	i = 0;
	while (variable[i] != '\0' && variable[i] != '=')
		i++;
	if (variable[i] == '\0')
		return (NULL);
	variable[i] = '\0';
	res = (t_env *)malloc(sizeof(t_env));
	if (res == NULL)
		return (NULL);
	res->name = ft_strcopy(variable, ft_strlen(variable));
	res->content = ft_strcopy(variable + i + 1, ft_strlen(variable + i + 1));
	res->next = NULL;
	return (res);
}

char	*get_env(t_env *env, const char *var)
{
	int		length;
	int		l;

	length = ft_strlen(var);
	while (env != NULL)
	{
		l = ft_strlen(env->name);
		if (l == length && ft_strncmp(env->name, var, length) == 0)
			return (env->content);
		env = env->next;
	}
	return (NULL);
}
