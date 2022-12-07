/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chchin <chchin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 16:36:35 by wricky-t          #+#    #+#             */
/*   Updated: 2022/12/07 10:59:38 by chchin           ###   ########.fr       */
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
int	main(int argc, char **argv, char **envp)
{
	char	*cmds;

	if (argc != 1 || argv[1])
	{
		printf("This program does not accept arguments\n");
		exit(0);
	}
	while (1)
	{
		cmds = readline("> ");
		if (cmds == NULL)
			break ;
		// lexer(cmds);
		if (!ft_strncmp(cmds, "cd", 2))
			call_cd(ft_strchr(cmds, ' ') + 1);
		else if (!ft_strncmp(cmds, "pwd", 3))
			call_pwd(NULL);
		else if (!ft_strncmp(cmds, "env", 3))
			call_env(envp);
		free(cmds);
	}
	return (0);
}
