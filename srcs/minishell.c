/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 16:36:35 by wricky-t          #+#    #+#             */
/*   Updated: 2023/01/08 18:21:44 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief Get the dangling quote
 *
 * Iterate through the string and look for QUOTES (" & '). If there's, check for
 * another one to ensure that the found quote is enclosed. If there's, ignore the
 * characters in between the found quotes and increment the pointer to (2nd found
 * quote + 1). After that, iterate the string from there and look for another
 * dangling quote. If the second quote is not found, return the starting quote.
 * The caller should use the return value to ask user for the closing quote.
*/
static char	get_dangling_quote(char *cmds)
{
	char	*start_quote;
	char	*end_quote;

	while (*cmds != '\0')
	{
		start_quote = ft_strchr(QUOTES, *cmds);
		if (start_quote != NULL)
		{
			end_quote = ft_strchr(cmds + 1, *cmds);
			if (end_quote != NULL)
			{
				cmds = end_quote + 1;
				continue ;
			}
			else if (end_quote == NULL)
				return (*start_quote);
		}
		if (*cmds == '\0')
			break ;
		cmds++;
	}
	return (0);
}

/**
 * @brief Check if there's a dangling quote
 *
 * 1. Get the dangling quote first if have. If no, get_dangling_quote
 * 	  will return 0.
 * 2. Manually add newline after the current command. Readline function does not
 * 	  read '\n'.
 * 3. Read line to get the closing quote
 * 4. Check through the user input string to see if the closing quote
 * 	  has been provided
 * 5. Join the user input string to the cmds no matter what
 * 6. If the closing quote is in the string, break the loop.
 * 7. If the closing quote is not in the string, manually add '\n' because
 *    readline does not read '\n'
 * 8. Return the latest cmds str
*/
static char	*check_dangling_quote(char *cmds)
{
	char	dang_quote;
	char	*enclosed;
	char	*line;

	dang_quote = get_dangling_quote(cmds);
	if (dang_quote == 0)
		return (cmds);
	while (1)
	{
		cmds = ft_strjoin_free(cmds, "\n");
		line = readline("quote > ");
		if (line == NULL)
			break ;
		enclosed = ft_strchr(line, dang_quote);
		cmds = ft_strjoin_free(cmds, line);
		free(line);
		if (enclosed != NULL)
			break ;
	}
	cmds = check_dangling_quote(cmds);
	return (cmds);
}

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
		init_signal();
		cmds = readline(ms.prompt);
		if (cmds == NULL)
			call_exit(&ms, NULL);
		cmds = check_dangling_quote(cmds);
		if (cmds != NULL && *cmds != '\0')
			add_history(cmds);
		lexer(&ms, cmds);
		parser(&ms);
		executor(ms.cmds, ev);
		ft_lstclear(&ms.tokens, free_token);
		ft_lstclear(&ms.cmds, free_cmd_block);
		free(ms.prompt);
	}
	return (0);
}
