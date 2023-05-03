/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douattar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 12:21:10 by douattar          #+#    #+#             */
/*   Updated: 2022/05/21 19:30:11 by douattar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*actual_cwd(const char *home)
{
	char	*res;
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (NULL);
	if (home == NULL || home[0] == '\0')
		return (ft_strcpy(cwd));
	if (ft_strncmp(home, cwd, ft_strlen(home)) == 0)
	{
		res = ft_strjoin("~", cwd + ft_strlen(home));
		if (res == NULL)
			return (NULL);
	}
	else
		res = ft_strcpy(cwd);
	return (res);
}

char	*set_prompt(t_env *envp)
{
	char	*res;
	char	*temp;
	char	*cwd;

	cwd = actual_cwd(get_env(envp, "HOME"));
	if (cwd == NULL)
		return (NULL);
	temp = ft_strjoin(GRN "[minishell " RESET, cwd);
	if (temp == NULL)
		return (NULL);
	free(cwd);
	if (temp == NULL)
		return (NULL);
	res = ft_strjoin(temp, GRN "]$ " RESET);
	free(temp);
	return (res);
}
