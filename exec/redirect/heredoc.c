/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douattar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 10:33:32 by douattar          #+#    #+#             */
/*   Updated: 2022/05/23 17:02:33 by douattar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check(char *temp, char *end, int length)
{
	if (temp == NULL)
	{
		write(2, "minishell: warning: here-document at line", 41);
		ft_printf(" %d ", g_global.line);
		write(2, "delimited by end-of-file (wanted `", 34);
		write(2, end, ft_strlen(end));
		write(2, "')\n", 3);
		return (TRUE);
	}
	return (ft_strncmp(temp, end, length) == 0 && ft_strlen(temp) == length);
}

static void	floo(char *str, int fd, t_env *env)
{
	char	*temp;

	temp = ft_replace(str, env);
	write(fd, temp, ft_strlen(temp));
	write(fd, "\n", 1);
	if (temp != str)
		free(temp);
}

static int	do_here(char *name, char *end, t_env *env)
{
	int		fd;
	int		length;
	char	*str;

	fd = open(name, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd < 0 || access(name, F_OK) < 0)
		return (TRUE);
	length = ft_strlen(end);
	str = NULL;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, heredoc_signal);
	while (str == NULL)
	{
		str = readline("heredoc> ");
		if (g_global.status != 0 || check(str, end, length))
			break ;
		floo(str, fd, env);
		free(str);
		str = NULL;
	}
	ignore();
	free(str);
	close(fd);
	return (FALSE);
}

static int	new_world(char **redirect, t_exec all, char **res, t_env *env)
{
	char	*temp;

	temp = create_temp(redirect[all.i]);
	if (temp == NULL || do_here(temp, redirect[all.i] + 3, env))
	{
		free(temp);
		destroy_heredoc(redirect);
		return (1);
	}
	free(redirect[all.i]);
	redirect[all.i] = ft_strjoin("< ", temp);
	res[all.n] = temp;
	return (0);
}

char	**ft_heredoc(char **redirect, t_env *env)
{
	t_exec	all;
	char	**res;

	if (redirect == NULL || g_global.status != 0)
		return (NULL);
	all.i = 0;
	all.n = 0;
	res = heredoc_number(redirect);
	if (res == NULL)
		return (NULL);
	while (redirect[all.i] != NULL)
	{
		if (ft_strncmp(redirect[all.i], "<< ", 3) == 0)
		{
			if (new_world(redirect, all, res, env) || g_global.status == 130)
			{
				free_double(res);
				return (NULL);
			}
			all.n++;
		}
		all.i++;
	}
	res[all.n] = NULL;
	return (res);
}
