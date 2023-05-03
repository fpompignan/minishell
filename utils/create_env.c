/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douattar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 12:34:50 by douattar          #+#    #+#             */
/*   Updated: 2022/05/19 14:33:12 by douattar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	shlvl_plus(t_env **var)
{
	char	*temp;
	char	**str;
	char	*number;

	str = malloc(sizeof(char *) * 2);
	if (var == NULL || str == NULL)
		return ;
	temp = get_env(*var, "SHLVL");
	if (temp == NULL)
		str[0] = ft_strcpy("SHLVL=1");
	else
	{
		number = ft_itoa(ft_atoi(temp) + 1);
		if (number == NULL)
			return ;
		str[0] = ft_strjoin("SHLVL=", number);
		free(number);
	}
	str[1] = NULL;
	ft_export(str, var);
	free(str[0]);
	free(str);
}

static t_env	*create_tab_from_null(void)
{
	t_env	*res;
	char	*str;

	str = ft_strcpy("_=./minishell");
	if (str == NULL)
		return (NULL);
	res = new_var(str);
	if (res == NULL)
		return (NULL);
	free(str);
	shlvl_plus(&res);
	return (res);
}

t_env	*create_tab(char **envp)
{
	t_env	*res;
	t_env	*temp;
	int		i;

	if (envp == NULL || envp[0] == NULL)
		return (create_tab_from_null());
	res = new_var(envp[0]);
	if (res == NULL)
		return (NULL);
	temp = res;
	i = 1;
	while (envp[i] != NULL)
	{
		temp->next = new_var(envp[i]);
		if (temp->next == NULL)
			return (NULL);
		temp = temp->next;
		i++;
	}
	shlvl_plus(&res);
	temp = NULL;
	return (res);
}
