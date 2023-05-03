/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douattar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 11:31:36 by douattar          #+#    #+#             */
/*   Updated: 2022/05/19 12:25:05 by douattar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd(const char **str)
{
	char	cwd[PATH_MAX];

	(void)str;
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		write(1, cwd, ft_strlen(cwd));
		write(1, "\n", 1);
	}
	else
		perror("pwd");
	return (cwd == NULL);
}
