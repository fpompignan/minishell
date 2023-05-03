/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fassier- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 16:46:53 by fassier-          #+#    #+#             */
/*   Updated: 2022/05/24 17:27:10 by douattar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_global	g_global;

static void	global_init(void)
{
	g_global.status = 0;
	g_global.line = 0;
}

static t_env	*init_main(char **envp)
{
	base_signal();
	global_init();
	return (create_tab(envp));
}

static char	*do_prompt(t_env *env)
{
	char	*str;
	char	*prompt;

	prompt = set_prompt(env);
	if (prompt == NULL)
		str = readline("minishell> ");
	else
		str = readline(prompt);
	free(prompt);
	return (str);
}

int	main(int argc, char **argv, char **envp)
{
	char	*str;
	t_env	*env;

	(void)argc;
	(void)argv;
	env = init_main(envp);
	str = NULL;
	while (str == NULL)
	{
		str = do_prompt(env);
		if (str == NULL)
			break ;
		ft_minishell(str, &env);
		free(str);
		str = NULL;
	}
	rl_clear_history();
	clear_tab(env);
	write(1, "exit\n", 5);
	return (g_global.status);
}
