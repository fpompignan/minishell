/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douattar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 11:56:36 by douattar          #+#    #+#             */
/*   Updated: 2022/05/26 12:21:50 by douattar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_process(t_process *pro)
{
	int	i;

	i = 0;
	while (pro[i].is_last == 0)
		i++;
	return (i);
}

void	ft_minishell(char *str, t_env **env)
{
	char		**envp;
	t_process	*res;

	if (str[0] == '\0')
		return ;
	g_global.old = g_global.status;
	g_global.status = 0;
	envp = duplicate_env(*env);
	res = parse(str, envp);
	if (res == NULL)
	{
		if (g_global.status == 0)
			g_global.status = g_global.old;
	}
	else
	{
		g_global.line++;
		ft_exec(res, count_process(res), envp, env);
	}
	free_double(envp);
}
