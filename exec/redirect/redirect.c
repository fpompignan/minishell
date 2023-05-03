/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douattar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 15:29:38 by douattar          #+#    #+#             */
/*   Updated: 2022/05/24 10:29:21 by douattar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_standard(t_fileno file)
{
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	dup2(file.oldin, STDIN_FILENO);
	dup2(file.oldout, STDOUT_FILENO);
	close(file.oldin);
	close(file.oldout);
}

static int	on_output(const char *output)
{
	int	fd;

	if (output == NULL)
		return (TRUE);
	fd = open(output, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd < 0)
		return (TRUE);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (FALSE);
}

static int	on_standard(const char *input)
{
	int	fd;

	if (input == NULL)
		return (TRUE);
	fd = open(input, O_RDONLY);
	if (fd < 0)
		return (TRUE);
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (FALSE);
}

static int	on_append(const char *app)
{
	int	fd;

	if (app == NULL)
		return (TRUE);
	fd = open(app, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd < 0)
		return (TRUE);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (FALSE);
}

int	ft_redirect(char **str, char **here)
{
	int		i;

	i = 0;
	(void)here;
	while (str != NULL && str[i] != NULL)
	{
		if (ft_strncmp(str[i], "< ", 2) == 0 && on_standard(str[i] + 2))
			return (redirect_error(str, i));
		if (ft_strncmp(str[i], "> ", 2) == 0 && on_output(str[i] + 2))
			return (redirect_error(str, i));
		if (ft_strncmp(str[i], ">> ", 3) == 0 && on_append(str[i] + 3))
			return (redirect_error(str, i));
		i++;
	}
	return (-1);
}
