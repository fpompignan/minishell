/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douattar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 11:45:45 by douattar          #+#    #+#             */
/*   Updated: 2022/05/11 17:25:43 by douattar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

// env
t_env	*create_tab(char **envp);
t_env	*new_var(char *variable);
char	*get_env(t_env *env, const char *var);

// env_clear
void	clear_env(t_env *block);
void	clear_tab(t_env	*start);
int		number_element(t_env *start);
char	*line_env(t_env *start);
char	**duplicate_env(t_env *start);

char	*ft_strcpy(const char *str);
void	free_double(char **array);
char	**get_path(t_env *envp);

#endif
