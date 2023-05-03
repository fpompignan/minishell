/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douattar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 11:12:24 by douattar          #+#    #+#             */
/*   Updated: 2022/05/24 09:55:15 by douattar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	built_in(t_process *pro, int i, t_env **envp, char **env)
{
	ft_redirect(pro[i].redir, pro[i].heredoc);
	if (pro[i].function == CD)
		return (cd(pro[i].arguments + 1, envp));
	else if (pro[i].function == ECHO)
		return (ft_echo(pro[i].arguments + 1));
	else if (pro[i].function == ENV)
		return (ft_env(*envp));
	else if (pro[i].function == EXPORT)
		return (ft_export(pro[i].arguments + 1, envp));
	else if (pro[i].function == PWD)
		return (pwd((const char **)(NULL)));
	else if (pro[i].function == UNSET)
		return (ft_unset(pro[i].arguments + 1, envp));
	else if (pro[i].function == EXIT)
	{
		return (ft_exit(pro, i, envp, env));
	}
	return (0);
}

char	*search_path(char *const *line, char **path)
{
	int		i;
	char	*str;
	char	*temp;

	i = 0;
	str = NULL;
	temp = NULL;
	while (str == NULL && path[i] != NULL)
	{
		temp = ft_strjoin(path[i], "/");
		str = ft_strjoin(temp, line[0]);
		free(temp);
		if (access(str, X_OK) == -1)
		{
			free(str);
			str = NULL;
		}
		i++;
	}
	return (str);
}

static int	is_directory(const char *path)
{
	struct stat	statbuf;

	if (stat(path, &statbuf) != 0)
		return (0);
	return (S_ISDIR(statbuf.st_mode));
}

static void	with_path(char *const *line, char **envp)
{
	if (line[0][0] == '\0')
	{
		g_global.status = 127;
		write(2, "minishell:  : command not found\n", 32);
	}
	else if (is_directory(line[0]))
	{
		write(2, "minishell: ", 11);
		write(2, line[0], ft_strlen(line[0]));
		write(2, ": Is a directory\n", 17);
		g_global.status = 126;
	}
	else if (access(line[0], F_OK) != 0 || access(line[0], X_OK) != 0)
	{
		perror(line[0]);
		g_global.status = 126;
		if (access(line[0], F_OK) != 0)
			g_global.status += 1;
	}
	else
	{
		reset();
		execve(line[0], line, envp);
	}
}

void	command_line(char *const *line, char **path, char **envp)
{
	char	*str;

	if (line == NULL || envp == NULL)
		return ;
	if (line[0][0] == '\0' || path == NULL || \
			ft_strchr(line[0], '/') != NULL || line[0][0] == '.')
	{
		with_path(line, envp);
		return ;
	}
	str = search_path(line, path);
	if (str == NULL)
	{
		write(2, "minishell: ", 11);
		write(2, line[0], ft_strlen(line[0]));
		write(2, ": command not found\n", 20);
		g_global.status = 127;
		return ;
	}
	reset();
	execve(str, line, envp);
	free(str);
}
