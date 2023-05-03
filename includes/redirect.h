/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douattar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 19:38:30 by douattar          #+#    #+#             */
/*   Updated: 2022/05/24 10:09:56 by douattar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECT_H
# define REDIRECT_H

# include "minishell.h"

// error
int		redirect_error(char **str, int i);

// heredoc
char	**ft_heredoc(char **redirect, t_env *env);
int		ft_redirect(char **str, char **here);
void	reset_standard(t_fileno file);

// here2
char	*create_temp(char *here);
char	**heredoc_number(char **redirect);
void	destroy_heredoc(char **heredoc);
#endif
