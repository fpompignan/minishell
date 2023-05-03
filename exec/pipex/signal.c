/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douattar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 12:02:51 by douattar          #+#    #+#             */
/*   Updated: 2022/05/26 11:59:43 by douattar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	int_handler(int sig)
{
	if (SIGINT == sig)
	{
		g_global.status = 130;
		rl_on_new_line();
		write(1, "\n", 1);
		rl_replace_line("", 1);
		rl_redisplay();
	}
}

void	heredoc_signal(int sig)
{
	if (SIGINT == sig)
	{
		g_global.status = 130;
		write(1, "\n", 1);
		close(0);
	}
}

void	exec_signal(int sig)
{
	if (SIGQUIT == sig)
	{
		g_global.status = 131;
		write(1, "Quit (core dumped)\n", 19);
	}
	else if (sig == SIGINT)
		heredoc_signal(sig);
}

void	ignore(void)
{
	signal(SIGINT, exec_signal);
	signal(SIGQUIT, exec_signal);
}

void	reset(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
