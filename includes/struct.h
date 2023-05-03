/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douattar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 17:08:14 by douattar          #+#    #+#             */
/*   Updated: 2022/05/24 10:27:37 by douattar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_fileno
{
	int	oldin;
	int	oldout;
}	t_fileno;

typedef struct s_exec { // Un four tout
	int			**pipeline;
	int			i;
	int			n;
	t_fileno	*file;
}	t_exec;

typedef struct s_commande {
	const char	*line;
	char		**arguments;
	char		**redirections;
}	t_commande;

typedef struct s_global {
	char					*shell;	
	unsigned char			status;
	unsigned char			old;
	unsigned long long int	line;
}	t_global;

typedef struct s_env {
	char			*name;
	char			*content;
	struct s_env	*next;
}	t_env;

// temporaire francois
typedef enum e_function
{
	NO_FUNCTION,
	EXECVE,
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT,
}	t_function;

typedef enum e_type
{
	WORD,
	FUNCTION,
	FILE_IN,
	HERE_DOC,
	FILE_OUT,
	FILE_OUT_SUR,
	OPEN_FILE,
	LIMITOR,
	EXIT_FILE,
	EXIT_FILE_A
}	t_type;

typedef struct s_token
{
	char	*word;
	t_type	type;
	int		is_last;
}	t_token;

typedef struct s_process
{
	char		*str;
	t_token		*tokens;
	t_function	function;
	char		**var_env;
	char		**realname_env;
	int			fd_in;
	int			fd_out;
	int			is_last;
	char		**redir;
	char		**heredoc;
	char		**arguments;
	int			n;
}	t_process;

typedef struct s_rep
{
	int		dollar;
	int		temp;
	char	*model;
	int		i;
	char	*var;
}	t_rep;

#endif
