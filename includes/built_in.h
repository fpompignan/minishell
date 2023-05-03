/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douattar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 19:41:12 by douattar          #+#    #+#             */
/*   Updated: 2022/05/20 12:02:11 by douattar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H

# include "minishell.h"

int		cd(char **str, t_env **env);
int		ft_echo(char **str);
int		ft_env(t_env *env);
int		ft_exit(t_process *pro, int i, t_env **envp, char **env);
int		ft_export(char **arg, t_env **envp);
int		pwd(const char **str);
int		ft_unset(char **arg, t_env **env);
void	valid_params(char **arg);
#endif
