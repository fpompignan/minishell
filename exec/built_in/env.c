/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douattar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 12:55:29 by douattar          #+#    #+#             */
/*   Updated: 2022/04/19 10:35:01 by douattar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_env *env)
{
	if (env == NULL)
		return (0);
	while (env != NULL)
	{
		write(1, env->name, ft_strlen(env->name));
		write(1, "=", 1);
		write(1, env->content, ft_strlen(env->content));
		write(1, "\n", 1);
		env = env->next;
	}
	return (0);
}
