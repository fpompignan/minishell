/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multiple.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douattar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 10:12:14 by douattar          #+#    #+#             */
/*   Updated: 2022/05/26 12:03:42 by douattar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_int(int **table, int n)
{
	int	i;

	i = 0;
	if (table == NULL)
		return ;
	while (i < n)
	{
		free(table[i]);
		i++;
	}
	free(table);
}

static int	execute(t_process *pro, char **env, t_env **envp, t_exec full)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		return (1);
	if (pid == 0)
	{
		reset();
		change_standard(full.pipeline, full.n, pro[full.i].n);
		command_in_pipe(pro, env, envp, full);
	}
	return (pid);
}

static void	prologue_of_pipex(t_process *pro, int n, t_exec *full, t_env *env)
{
	full->i = 0;
	full->n = n;
	ft_heredoc_multiple(pro, n, env);
	if (g_global.status == 0)
		full->pipeline = create_pipeline(n);
}

static void	sigint_no_problem(int sig)
{
	if (SIGINT == sig)
	{
		g_global.status = 130;
		write(1, "\n", 1);
	}
}

unsigned char	ft_exec_multiple(t_process *pro, int n, char **env, t_env **nvp)
{
	t_exec	full;
	int		status;
	int		pid;
	int		found;

	prologue_of_pipex(pro, n, &full, *nvp);
	if (g_global.status != 0)
		return (0);
	signal(SIGINT, sigint_no_problem);
	while (full.i < n)
	{
		pro[full.i].n = full.i;
		pid = execute(pro, env, nvp, full);
		full.i++;
	}
	close_pipeline(full.pipeline, n);
	while (full.i--)
	{
		found = wait(&status);
		destroy_heredoc(pro[full.i].heredoc);
		if (pid == found && g_global.status == 0)
			g_global.status = WEXITSTATUS(status);
	}
	free_int(full.pipeline, full.n);
	return ((unsigned char)(0));
}
