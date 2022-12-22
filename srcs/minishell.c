/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chchin <chchin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 16:36:35 by wricky-t          #+#    #+#             */
/*   Updated: 2022/12/22 16:34:44 by brook            ###   ########.fr       */
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
		set_prompt(&ms);
		cmds = readline(ms.prompt);
		if (cmds == NULL)
		{
			ft_printf("exit\n");
			call_exit(&ms, NULL);
			break ;
		}
		cmds = check_dangling_quote(cmds);
		if (cmds != NULL && *cmds != '\0')
			add_history(cmds);
		call_buildin(&ms, cmds);
		// lexer(&ms, cmds);
		free(cmds);
		free(ms.prompt);
	}
	free(ms.prompt);
	return (0);
}
