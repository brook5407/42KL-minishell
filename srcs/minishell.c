/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 16:36:35 by wricky-t          #+#    #+#             */
/*   Updated: 2022/12/09 13:30:56 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * Minishell
 * 
 * 1. Read line from command line
 * 2. Lexical analysis
 * 3. Parser
 * 4. Executer
 */
int	main(int ac, char **av, char **ev)
{
	char		*cmds;
	t_minishell	ms;

	(void)ac;
	(void)av;
	init_minishell(&ms, ev);
	while (1)
	{
		cmds = readline(ms.prompt);
		if (cmds == NULL)
			break ;
		add_history(cmds);
		lexer(&ms, cmds);
		free(cmds);
	}
	system("leaks -q minishell");
	return (0);
}
