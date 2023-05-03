/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 18:02:14 by marvin            #+#    #+#             */
/*   Updated: 2022/05/24 09:47:03 by douattar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	depassed_limit(const char *str)
{
	int			i;
	const char	*max;

	i = 0;
	max = "9223372036854775807";
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			max = "9223372036854775808";
		str++;
	}
	if (ft_strlen(str) < ft_strlen(max))
		return (FALSE);
	else if (ft_strlen(str) > ft_strlen(max))
		return (TRUE);
	while (str[i] == max[i] && str[i] != '\0')
		i++;
	return (str[i] > max[i]);
}

static int	is_number(const char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (FALSE);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] != '\0' && '0' <= str[i] && str[i] <= '9')
		i++;
	if (str[i] != '\0')
		return (TRUE);
	return (depassed_limit(str));
}

static void	none_numbers(t_process *pro, int i, t_env **envp, char **env)
{
	write(2, "minishell: exit: ", 17);
	write(2, pro[i].arguments[1], ft_strlen(pro[i].arguments[1]));
	write(2, ": numeric argument required\n", 28);
	error_free(pro, env, envp);
	exit(2);
}

static void	check_pid(t_process *pro, int i)
{
	if (pro[i].n == 0 && pro[i + 1].is_last)
		write(2, "exit\n", 5);
}

int	ft_exit(t_process *pro, int i, t_env **envp, char **env)
{
	unsigned char	status;

	check_pid(pro, i);
	status = g_global.old;
	if (pro[i].arguments == NULL)
	{
		error_free(pro, env, envp);
		exit(status);
	}
	if (is_number(pro[i].arguments[1]))
		none_numbers(pro, i, envp, env);
	else if (pro[i].arguments[1] != NULL && pro[i].arguments[2] == NULL)
		status = (unsigned char)(ft_atoi(pro[i].arguments[1]));
	if (pro[i].arguments[1] == NULL || pro[i].arguments[2] == NULL)
	{
		error_free(pro, env, envp);
		exit(status);
	}
	else
		write(2, "minishell: exit: too many arguments\n", 36);
	status = 1;
	return (status);
}
