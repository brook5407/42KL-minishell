/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 12:42:56 by wricky-t          #+#    #+#             */
/*   Updated: 2022/12/28 15:43:07 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//testing
void	visualize_expected(t_parse_hlpr *phlpr)
{
	int	i;

	i = -1;
	printf("\n");
	printf("| ");
	printf("%-6s", "CMD");
	printf("%-6s", "E_CMD");
	printf("%-6s", "STR");
	printf("%-6s", "R_IN");
	printf("%-6s", "R_OUT");
	printf("%-6s", "HDOC");
	printf("%-6s", "APPD");
	printf("%-6s", "PIPE");
	printf("|\n| ");
	while (++i < TYPE_TOTAL)
		printf("%-6d", phlpr->expected[i]);
	printf("|\n\n");
}
// testing

/**
 * TODO:
 * 1. A function to iterate through the token list (ft_lstiteri)
 * 2. A function that expect a token. If the token is not expected, meaning
 *    grammar is wrong.
 * 		a. First token of a grammar can be either a command, redirection.
 * 		b. The token after a redirection confirm is a file. The next token
 *         of redirection must be a [STR], cannot be a pipe.
 * 		c. After a file, can be pipe, another redirection, argument.
 *         If the argument list is empty, the [STR] could be the command.
 *      d. Pipe marks a new beginning of a simple grammar.
 * 3. A struct as a parser helper. Record what's the previous token type,
 * 	  what's expected next.
 * 4. Error handler. Show error based on the incorrect grammar.
 */

void	parser(t_minishell *ms)
{
	t_parse_hlpr	phlpr;

	(void)ms;
	init_parser_helper(&phlpr);
}
