/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douattar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 19:32:44 by douattar          #+#    #+#             */
/*   Updated: 2022/05/23 11:17:35 by douattar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "minishell.h"

// Exec
void			error_free(t_process *pro, char **env, t_env **envp);
void			ft_exec(t_process *pro, int n, char **envp, t_env **start);
void			command_in_pipe(t_process *pro, \
		char **env, t_env **envp, t_exec f);
int				built_in(t_process *pro, int i, t_env **envp, char **env);

// Utils
int				**create_pipeline(int process);
void			command_line(char *const *line, char **path, char **envp);
void			close_pipeline(int **pipeline, int n);
void			change_standard(int	**pipeline, int n, int i);
void			ft_heredoc_multiple(t_process *pro, int n, t_env *env);
void			free_int(int **table, int n);

// Signal
void			int_handler(int sig);
void			base_signal(void);
void			reset(void);
void			heredoc_signal(int sig);
void			ignore(void);

// Multiple
unsigned char	ft_exec_multiple(t_process *pro, \
		int n, char **env, t_env **nvp);

#endif
