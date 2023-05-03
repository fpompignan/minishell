/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fassier- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 16:46:53 by fassier-          #+#    #+#             */
/*   Updated: 2022/05/25 10:05:38 by fassier-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_process	*parse(char *commande, char **env)
{
	t_process	*process;
	int			action;

	process = NULL;
	action = 1;
	if (commande[0] != '\0' && get_nb_process(commande) != 0)
	{
		add_history(commande);
		process = lexer(commande, process, &action);
		if (action)
		{
			process = got_env(process, env);
			process = lexer2(process);
			action = parser(process);
		}	
		if (action)
			return (process);
	}
	return (process);
}
