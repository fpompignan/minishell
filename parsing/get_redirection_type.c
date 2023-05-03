/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redirection_type.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fassier- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 12:54:30 by fassier-          #+#    #+#             */
/*   Updated: 2022/05/23 13:05:58 by fassier-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_process	get_operator(t_process process)
{
	int	i;

	if (process.tokens)
	{
		i = 0;
		while (process.tokens[i].word)
		{
			if (!ft_strcmp(process.tokens[i].word, "<"))
				process.tokens[i].type = FILE_IN;
			else if (!ft_strcmp(process.tokens[i].word, "<<"))
				process.tokens[i].type = HERE_DOC;
			else if (!ft_strcmp(process.tokens[i].word, ">"))
				process.tokens[i].type = FILE_OUT;
			else if (!ft_strcmp(process.tokens[i].word, ">>"))
				process.tokens[i].type = FILE_OUT_SUR;
			i++;
		}
	}
	return (process);
}

static int	is_redir_operator(t_token token)
{
	return ((token.type == FILE_IN) + (token.type == HERE_DOC)
		+ (token.type == FILE_OUT) + (token.type == FILE_OUT_SUR));
}

static int	attribution_filename(int i)
{
	return ((i == FILE_IN) * OPEN_FILE
		+ (i == HERE_DOC) * LIMITOR
		+ (i == FILE_OUT) * EXIT_FILE
		+ (i == FILE_OUT_SUR) * EXIT_FILE_A);
}

static int	affiche_error(void)
{
	printf("minishell: parse error near \\n\n");
	return (0);
}

int	get_filename_type(t_process *process)
{
	int	i;

	i = 0;
	while (process->tokens[i].is_last == 0)
	{
		if (is_redir_operator(process->tokens[i]))
		{
			if (process->tokens[i + 1].is_last
				|| is_redir_operator(process->tokens[i + 1]))
			{
				printf("minishell: syntax error near unexpected token '%s'\n",
					process->tokens[i + 1].word);
				g_global.status = 1;
				return (0);
			}
			if (process->tokens[i + 1].type == WORD)
				process->tokens[i + 1].type
					= attribution_filename(process->tokens[i].type);
			else
				return (affiche_error());
		}
		i++;
	}
	return (1);
}
