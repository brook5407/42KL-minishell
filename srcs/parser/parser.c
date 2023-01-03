/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 12:42:56 by wricky-t          #+#    #+#             */
/*   Updated: 2023/01/03 13:31:34 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// testing
void	visualize_expected(t_parser *hlpr)
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
		printf("%-6d", hlpr->expected[i]);
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

/**
 * Parser process
 *
 * 1. Initialize parser_helper (should pass to a grammar checker in every
 *    iteration)
 * 2. Iterate through the token_list
 * 3. In each iteration
 * 		i.	 Get the type of that token
 *      ii.	 Check if the token match what's expected
 *      iii. If...
 * 			 a. ... it's expected
 * 				- save it into the node
 * 					- based on the grammar, where to stored the value
 * 					  will be different as well (check previous token)
 * 				- set next's token grammar rules
 * 				- move on to the next token
 *           b. ... it's not expected
 * 				- handle error
 *              - stop the current cmd block, move to the end
 * 					- might have to free what's been saved in the node
 *              - or stop when there's another pipeline and start
 *                parsing again.
 * 4. At the end of the whole process, the output is a cmd_list
 *
 * IDEA:
 * 1. Add prev_token in parser_helper
 * 2. Create a function that visualize each node in cmd_list
 * 3. Create functions that help building the cmd_list (builder functions)
 */

void	grammar_checker(t_minishell *ms, t_parser *hlpr, t_token *token)
{
	(void)ms;
	// apply guarding here
	if (is_type_on(hlpr, token->type) == 1)
		printf("Yeap, this is acceptable.\n");
	else
		printf("Nah bro what's this\n");
}

void	parser(t_minishell *ms)
{
	t_token		*token;
	t_list		*token_lst;
	t_parser	hlpr;

	token_lst = ms->tokens;
	init_parser(&hlpr); // get ready for parsing, handle one cmd_block (simple command)
	while (token_lst != NULL)
	{
		token = token_lst->content; // typecast content to t_token
		builder_helper(ms, &hlpr, token); // build the cmd block
		set_next_grammar(&hlpr, token->type); // set the grammar of next token
		token_lst = token_lst->next; // iterate through the token list
	}
	add_as_cmd_block(ms, &hlpr); // add the cmd block to the cmd list
}
