/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douattar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 10:40:14 by douattar          #+#    #+#             */
/*   Updated: 2022/05/26 11:31:01 by douattar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// A function to know if a variable exist
static int	exist(t_env *env, const char *var)
{
	int	n;

	n = ft_strlen(var);
	while (env != NULL)
	{
		if (ft_strlen(env->name) == n)
		{
			if (ft_strncmp(var, env->name, n) == 0)
				return (TRUE);
		}
		env = env->next;
	}
	return (FALSE);
}

static void	update(t_env **env)
{
	char	cwd[PATH_MAX];
	char	**arg;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return ;
	arg = malloc(sizeof(char *) * 2);
	arg[1] = NULL;
	if (exist(*env, "PWD"))
	{
		arg[0] = ft_strjoin("OLDPWD=", get_env(*env, "PWD"));
		ft_export(arg, env);
	}
	else
	{
		arg[0] = ft_strcpy("OLDPWD");
		ft_unset(arg, env);
	}
	free(arg[0]);
	arg[0] = ft_strjoin("PWD=", cwd);
	ft_export(arg, env);
	free(arg[0]);
	free(arg);
}

static int	check_cd(char **str, t_env **env)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
		i++;
	if (i > 1)
	{
		write(2, "minishell: cd: too many arguments\n", 34);
		return (1);
	}
	else if (str[0][0] == '\0')
		return (0);
	if (chdir(str[0]) == -1)
	{
		perror("minishell: cd");
		return (1);
	}
	update(env);
	return (0);
}

int	cd(char **str, t_env **env)
{
	char	*home;

	if (str != NULL && str[0] != NULL)
		return (check_cd(str, env));
	home = get_env(*env, "HOME");
	if (home == NULL)
	{
		write(2, "minishell: cd: HOME not set\n", 28);
		return (1);
	}
	else if (home[0] == '\0')
		return (0);
	if (chdir(home) == -1)
	{
		perror("minishell: cd");
		return (1);
	}
	update(env);
	return (0);
}
