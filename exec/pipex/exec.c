/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douattar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 13:49:56 by douattar          #+#    #+#             */
/*   Updated: 2022/05/26 12:03:43 by douattar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_free(t_process *pro, char **env, t_env **envp)
{
	int	i;

	i = 0;
	free_double(env);
	clear_tab(*envp);
	while (pro[i].is_last == 0)
	{
		free(pro[i].heredoc);
		i++;
	}
	free_process(pro);
}

void	command_in_pipe(t_process *pro, char **env, t_env **envp, t_exec f)
{
	char	**path;
	int		index;

	path = get_path(*envp);
	index = ft_redirect(pro[f.i].redir, pro[f.i].heredoc);
	if (index != -1)
	{
		free_double(path);
		error_free(pro, env, envp);
		exit(g_global.status);
	}
	else if (pro[f.i].function != NO_FUNCTION)
	{
		reset();
		if (pro[f.i].function == EXECVE)
			command_line(pro[f.i].arguments, path, env);
		else
			built_in(pro, f.i, envp, env);
		base_signal();
	}
	free_double(path);
	free_int(f.pipeline, f.n);
	error_free(pro, env, envp);
	exit(g_global.status);
}

// Execute the command ask in a pipe
static int	execute(t_process *pro, char **env, t_env **envp, t_exec n)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid == 0)
	{
		n.i = 0;
		n.n = 1;
		n.pipeline = NULL;
		close(n.file->oldin);
		close(n.file->oldout);
		command_in_pipe(pro, env, envp, n);
	}
	return (pid);
}

// Execute command without pipe
static void	ft_execone(t_process *pro, t_env **envp, char **env)
{
	int			status;
	t_exec		low;
	t_fileno	file;

	file.oldin = dup(STDIN_FILENO);
	file.oldout = dup(STDOUT_FILENO);
	pro->heredoc = ft_heredoc(pro->redir, *envp);
	pro->n = 0;
	if (g_global.status != 130 && ft_redirect(pro->redir, pro->heredoc) == -1)
	{
		if (pro->function == EXECVE)
		{
			low.file = &file;
			if (execute(pro, env, envp, low) > -1)
				wait(&status);
			if (g_global.status == 0)
				g_global.status = WEXITSTATUS(status);
		}
		else if (pro->function != NO_FUNCTION)
			g_global.status = built_in(pro, 0, envp, env);
	}
	reset_standard(file);
	destroy_heredoc(pro->heredoc);
}

void	ft_exec(t_process *pro, int n, char **envp, t_env **start)
{
	ignore();
	if (n == 1)
		ft_execone(pro, start, envp);
	else if (n > 1)
	{
		base_signal();
		ft_exec_multiple(pro, n, envp, start);
	}
	if (pro != NULL)
		free_process(pro);
	base_signal();
}
