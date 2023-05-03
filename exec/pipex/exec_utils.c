/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douattar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 15:32:27 by douattar          #+#    #+#             */
/*   Updated: 2022/05/23 11:46:54 by douattar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	**create_pipeline(int process)
{
	int	**res;
	int	i;

	res = malloc(sizeof(int *) * (process));
	if (res == NULL)
	{
		g_global.status = 1;
		return (NULL);
	}
	i = 0;
	while (i < process)
	{
		res[i] = malloc(sizeof(int) * 2);
		if (res[i] == NULL || pipe(res[i]) == -1)
		{
			g_global.status = 1;
			return (NULL);
		}
		i++;
	}
	return (res);
}

void	change_standard(int	**pipeline, int n, int i)
{
	if (i > 0)
		dup2(pipeline[i - 1][0], STDIN_FILENO);
	if (i < n - 1)
		dup2(pipeline[i][1], STDOUT_FILENO);
	close_pipeline(pipeline, n - 1);
}

void	close_pipeline(int **pipeline, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		close(pipeline[i][0]);
		close(pipeline[i][1]);
		i++;
	}
}

void	ft_heredoc_multiple(t_process *pro, int n, t_env *env)
{
	int	i;

	i = 0;
	while (i < n && g_global.status == 0)
	{
		pro[i].heredoc = ft_heredoc(pro[i].redir, env);
		i++;
	}
	if (g_global.status == 130)
	{
		i = 0;
		while (i < n)
		{
			destroy_heredoc(pro[i].heredoc);
			pro[i].heredoc = NULL;
			i++;
		}
	}
}

void	base_signal(void)
{
	signal(SIGINT, int_handler);
	signal(SIGQUIT, SIG_IGN);
}
