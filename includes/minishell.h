/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douattar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 15:10:41 by douattar          #+#    #+#             */
/*   Updated: 2022/05/18 17:53:46 by douattar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define TRUE 1
# define FALSE 0
# define BUFFER_SIZE 1 

# define RED "\x1B[31m"
# define GRN "\x1B[32m"
# define YEL "\x1B[33m"
# define BLU "\x1B[34m"
# define MAG "\x1B[35m"
# define CYN "\x1B[36m"
# define WHT "\x1B[37m"
# define RESET "\x1B[0m"

# include "struct.h"
# include "utils.h"
# include "vars.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <limits.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include "ft_printf.h"
# include "libft.h"
# include "execute.h"
# include "parse.h"

void	ft_minishell(char *str, t_env **env);
char	*set_prompt(t_env *envp);
#endif
