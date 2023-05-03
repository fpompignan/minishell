/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fassier- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 17:59:08 by fassier-          #+#    #+#             */
/*   Updated: 2022/05/26 15:42:05 by fassier-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_model(char *str, int dollar)
{
	char	*model;
	int		j;

	j = 0;
	model = NULL;
	while (f_isalnum(str[dollar + 1 + j])
		|| str[dollar + 1 + j] == '_')
		j++;
	model = ft_strndup(str + dollar + 1, j);
	return (model);
}

static void	init_replace(t_rep *rep, char *str)
{
	rep->i = 0;
	rep->dollar = find_dollar(str);
	rep->temp = rep->dollar;
	rep->model = NULL;
}

static char	*action_replace1(t_rep *rep, char *str, t_env *env, char *result)
{
	char	*cpy;

	cpy = ft_strndup(str + rep->i, (rep->temp - f_strlen(rep->model)));
	result = f_strjoin2(result, cpy);
	free (cpy);
	if (rep->model)
		free(rep->model);
	rep->model = get_model(str, rep->dollar);
	rep->i = rep->dollar + f_strlen(rep->model) + 1;
	rep->var = f_strdup(get_env(env, rep->model));
	if (!rep->var)
	{
		rep->var = malloc(sizeof(char));
		if (!rep->var)
			return (NULL);
		rep->var[0] = '\0';
	}
	result = f_strjoin2(result, rep->var);
	return (result);
}

static int	action_replace2(t_rep *rep, char *str)
{
	free (rep->var);
	rep->temp = find_dollar(str + rep->dollar + 1);
	if (rep->temp == -1)
		return (0);
	rep->dollar = rep->dollar + rep->temp + 1;
	return (1);
}

char	*ft_replace(char *str, t_env *env)
{
	char	*result;
	t_rep	rep;
	char	*cp;

	if (!str)
		return (NULL);
	init_replace(&rep, str);
	if (rep.dollar == -1)
		return (str);
	result = malloc(sizeof(char));
	result[0] = '\0';
	while (rep.dollar != -1)
	{
		result = action_replace1(&rep, str, env, result);
		if (action_replace2(&rep, str) == 0)
			break ;
	}
	cp = ft_strndup(str + rep.i, f_strlen(str)
			- rep.dollar - f_strlen(rep.model));
	result = f_strjoin2(result, cp);
	free(cp);
	if (rep.model)
		free(rep.model);
	return (result);
}
