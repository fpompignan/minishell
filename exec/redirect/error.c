/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douattar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 20:50:03 by douattar          #+#    #+#             */
/*   Updated: 2022/05/17 10:33:53 by douattar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_filename(char *redirect)
{
	int	i;

	i = 0;
	while (redirect[i] != ' ' && redirect[i] != '\0')
		i++;
	if (redirect[i] == ' ')
		return (i + 1);
	return (-1);
}

int	redirect_error(char **str, int i)
{
	char	*res;
	int		j;

	g_global.status = 1;
	j = get_filename(str[i]);
	if (j == -1)
		return (j);
	if (str[i][0] == '<')
		res = ft_strcpy(str[i] + j);
	else if (str[i][0] == '>')
		res = ft_strjoin("minishell: ", str[i] + j);
	perror(res);
	free(res);
	return (i);
}
